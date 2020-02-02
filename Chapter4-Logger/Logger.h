#pragma once
/////////////////////////////////////////////////////////////////////
// Logger.h - send log messages to multiple current std::ostreams  //
// ver 1.0                                                         //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 *---------------------
 * Send a sequence of log messages to one or more std::ostreams
 * - default stream is std::cout
 * - can add std::ofstream and std::ostringstream instances as well
 * - logger expects all std::ofstream instances to be created on the heap
 * - helper std::ostream makeStream(const std::string& filename) does that.
 * - use it like this: logger.add(makeStream("someFileName"));
 * - logger closes and deletes all std::ofstream pointers.
 * - logger.write accepts a T t instance to write and, optionally, a 
 *   level: debug or demo or results
 * - calling logger.level(Level::debug) will make write do nothing unless
 *   called like this: 
 *     logger.write(t, Level::debug);
 *     logger.write(t, Level::debug + Level::aLevel);
 *     aLevel = Level::demo or Level::results or level::demo + Level::results
 * - The package also provides a factory, makeLogger, that returns an 
 *   instance of a static logger.  That allows any code that compiles 
 *   Logger.cpp and includes Logger.h to share the same logger.
 * - All writes enQueue a message that a write thread services.  That
 *   was done so that log.write returns quickly, while the write thread
 *   does the slow writing to streams.
 *
 *  Required Files:
 * -----------------
 *  Logger.h, Logger.cpp
 *  DateTime.h, DateTime.cpp
 *  Cpp11-BlockingQueue.h
 *  Display.h
 *
 *  Maintenance History:
 * ----------------------
 *  ver 1.0 : 25 Nov 2019
 *  - first release
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include "Cpp11-BlockingQueue.h"
#include "DateTime.h"
#include "Display.h"

namespace Utilities {
  
  enum Level { results = 1, demo = 2, debug = 4, all = 7 };

  template <typename T, size_t C = 0>
  struct ILogger {
    virtual ~ILogger() {}
    virtual ILogger<T, C>& add(std::ostream*) = 0;
    virtual ILogger<T, C>& write(T t, size_t level = Level::all) = 0;
    virtual void head(T t = "") = 0;
    virtual void prefix(T prfix = "\n  ") = 0;
    virtual void wait() = 0;
    virtual void waitForWrites() = 0;
    virtual void level(size_t lv) = 0;
    virtual void name(const std::string& nm) = 0;
  };

  template <typename T, size_t C = 0>
  class Logger : public ILogger<T, C> {
  public:
    Logger(const std::string& nm = "");
    ~Logger();
    ILogger<T, C>& add(std::ostream* pOstrm);
    virtual ILogger<T, C>& write(T t, size_t level = 0x7);
    virtual void head(T t = "");
    virtual void prefix(T prfix = "\n  ");
    virtual void level(size_t lv);
    void name(const std::string& nm);
    std::string name();
    void wait();
    void waitForWrites();
  protected:
    std::vector<std::ostream*> dstStrm;
    BlockingQueue<T> blockingQueue_;
    void threadProc();
    std::string name_;
    std::thread writeThread_;
    T head_;
    std::string prefix_ = "\n  ";
    size_t level_ = 0x7; // Level::debug + Level::demo + Level::results;
  };
  /*--- object factory ----------------------------------------------
   *
   *  Creates static logger, so everyone calling makeLogger with
   *  the same value for C will use the same logger.
   */
  template<typename T, size_t C>
  inline ILogger<T, C>& makeLogger() {
    static Logger<T, C> logger;
    return logger;
  }
  /*--- initialize logger with name -------------------------------*/

  template<typename T, size_t C>
  Logger<T, C>::Logger(const std::string& nm) : name_(nm) {
    dstStrm.push_back(&std::cout);
    std::thread temp(&Logger<T, C>::threadProc, this);
    writeThread_ = std::move(temp);
  }
  /*--- wait for all writes to be sent ----------------------------*/

  template<typename T, size_t C>
  Logger<T, C>::~Logger() {
    if (writeThread_.joinable())
      writeThread_.detach();
    for (auto ptrStrm : dstStrm) {
      std::ofstream* ptrOfStrm = dynamic_cast<std::ofstream*>(ptrStrm);
      if (ptrOfStrm) {
        ptrOfStrm->close();
        delete ptrOfStrm;
      }
    }
  }
  /*--- reset name ------------------------------------------------*/

  template<typename T, size_t C>
  void Logger<T, C>::name(const std::string& nm) {
    name_ = nm;
  }
  /*--- retrieve name ---------------------------------------------*/

  template<typename T, size_t C>
  std::string Logger<T, C>::name() {
    return name_;
  }
  /*--- deQ thread processing -------------------------------------*/

  template<typename T, size_t C>
  void Logger<T,C>::threadProc() {
    while (true) {
      T t = blockingQueue_.deQ();
      if (t == "quit")
        break;
      for (auto item : dstStrm) {
        (*item) << t;
      }
    }
  }
  /*--- enQ stop message and wait for write thread exit -----------*/

  template<typename T, size_t C>
  void Logger<T, C>::wait() {
    blockingQueue_.enQ("quit");
    writeThread_.join();
  }
  /*--- wait for Q to empty before writing again ------------------*/

  template<typename T, size_t C>
  void Logger<T, C>::waitForWrites() {
    while (blockingQueue_.size() > 0)
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
  /*--- add another stream for concurrent writes ------------------*/

  template<typename T, size_t C>
  ILogger<T, C>& Logger<T, C>::add(std::ostream* pOstrm) {
    if(pOstrm != nullptr)
      dstStrm.push_back(pOstrm);
    return *this;
  }
  /*-----------------------------------------------------------------
  *  write a log message
  *  - probably one of many in a log stream
  */

  template<typename T, size_t C>
  ILogger<T, C>& Logger<T, C>::write(T t, size_t lv) {
    if (lv & level_) {
      blockingQueue_.enQ(prefix_ + t);
    }
    return *this;
  }
  /*-----------------------------------------------------------------
   *  write a head message
   *  - expected to be the first in a log conversation
   */
  template<typename T, size_t C>
  void Logger<T, C>::head(T t) {
    T temp = (t.size() > 0) ? t : name();
    T prfix = (prefix_ == "") ? "\n" : prefix_;
    head_ = temp + prfix + DateTime().now();
    write(head_);
  }
  /*--- set message prefix ----------------------------------------*/

  template<typename T, size_t C>
  void Logger<T,C>::prefix(T prfix) {
    prefix_ = prfix;
  }
  /*-----------------------------------------------------------------
   *  set logging level
   *  - results ==> normal output
   *  - demo    ==> demonstration output
   *  - debug   --> show debugging information
   *  can be any combination, e.g., demo + results
   */
  template<typename T, size_t C>
  void Logger<T, C>::level(size_t lv) {
    level_ = lv;
  }
  /*--- helper to open file stream --------------------------------*/

  inline std::ostream* makeStream(const std::string& fileName) {
    std::ofstream* pOfstrm = new std::ofstream;
    pOfstrm->open(fileName);
    if (pOfstrm->good())
      return pOfstrm;
    else
      return nullptr;
  }

  inline void Assert(bool predicate, const std::string& message = "", size_t ln = 0, bool doThrow = false) {
    if (predicate)
      return;
    std::string sentMsg = "Assertion raised";
    if (ln > 0)
      sentMsg += " at line number " + std::to_string(ln);
    if (message.size() > 0)
      sentMsg += "\n  message: \"" + message + "\"";
    if (doThrow)
      throw std::exception(sentMsg.c_str());
    else
      std::cout << "\n  " + sentMsg;
  }

  inline void Requires(bool predicate, const std::string& message, size_t lineNo, bool doThrow = false) {
    if (predicate)
      return;
    std::string sentMsg = "Requires " + message + " raised";
    sentMsg += " at line number " + std::to_string(lineNo);
    if (doThrow)
      throw std::exception(sentMsg.c_str());
    else
      std::cout << "\n  " + sentMsg;
  }

  inline void Ensures(bool predicate, const std::string& message, size_t lineNo, bool doThrow = false) {
    if (predicate)
      return;
    std::string sentMsg = "Ensures " + message + " raised";
    sentMsg += " at line number " + std::to_string(lineNo);
    if (doThrow)
      throw std::exception(sentMsg.c_str());
    else
      std::cout << "\n  " + sentMsg;
  }
}