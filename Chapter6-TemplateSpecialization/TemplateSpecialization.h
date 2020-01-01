#pragma once
///////////////////////////////////////////////////////////////
// TemplateSpecialization.h - template specialization demo   //
//                                                           //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse Univ   //
///////////////////////////////////////////////////////////////

#include "Timer.h"
#include <iostream>
#include <iomanip>
#include <type_traits>

namespace Chap6 {

  /*--------------------------------------------------------- 
    unspecialized template class
    - U is a placeholder, used only to provide a place for
      specialization.
    - This is a simple demo, but could easily be expanded
      into a useful facility
  ---------------------------------------------------------*/

  struct Null {};

  template<typename T, typename U = Null>
  class Logger {
  public:
    Logger(std::ostream* pStr) : pStream_(pStr) {}
    ~Logger() {}
    void write(T t) {
      if constexpr (std::is_empty<U>::value)
        (*pStream_) << prefix_ << t;
      else
        (*pStream_) << u.transform(t);
    }
  private:
    std::string prefix_ = "\n  ";
    std::ostream* pStream_;
    U u;
  };

  /*---------------------------------------------------------
    formatting class used to specialize Logger<T,Formatter>
    - this is partial class specialization since T is
      still unspecified
  ---------------------------------------------------------*/

  struct Formatter {
    const char* prefix_ = "\n  <-- ";
    const char* suffix_ = " -->";
    std::string transform(const std::string& s) {
      return prefix_ + s + suffix_;
    }
  };

  /*---------------------------------------------------------
    template class partial specialization on Timer class
    - See Timer.h for details
  ---------------------------------------------------------*/

  template<typename T>
  class Logger<T, Timer> {
  public:
    Logger(std::ostream* pStr) : pStream_(pStr) {}
    ~Logger() {
      timer_.stop();
    }
    void start() {
      timer_.start();
    }
    void stop() {
      timer_.stop();
    }
    void write(T t) {
      (*pStream_) << prefix_ << std::setw(6) 
                  << timer_.elapsedMicroseconds() 
                  << " microsec : " << t;
    }
  private:
    std::string prefix_ = "\n  ";
    Timer timer_;
    std::ostream* pStream_;
  };
}