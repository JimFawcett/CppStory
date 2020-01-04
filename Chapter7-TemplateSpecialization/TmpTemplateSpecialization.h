#pragma once
/////////////////////////////////////////////////////////////////////
// TmpTemplateSpecialization.h

#include "Timer.h"
#include <iostream>
#include <iomanip>
#include <type_traits>

namespace Chap7 {

  /*---------------------------------------------------------
    unspecialized template class Logger
    - S is the type of logged entities, often std::string
      but could be a Message type.
    - F is a templated formatter, F<S>
    - T is a timer type.
    This is a relatively simple demo, but could easily
    be expanded into a useful facility.
  ---------------------------------------------------------*/

  template<typename F>
  struct FNull {};

  struct TNull {};

  template<
    typename S, 
    template<typename S> typename F = FNull , 
    typename T = TNull
  >
  class Logger {
  public:
    Logger(std::ostream* pStr) : pStream_(pStr) {}
    ~Logger() {}
    void write(S s) {
      if constexpr (std::is_empty<F<S>>::value)
        (*pStream_) << prefix_ << s;
      else
        (*pStream_) << f.transform(s);
    }
  private:
    std::string prefix_ = "\n  ";
    std::ostream* pStream_;
    F<S> f;
  };

  /*---------------------------------------------------------
    formatting class used to specialize Logger<T,Formatter>
    - this is partial class specialization since T is
      still unspecified
  ---------------------------------------------------------*/

  template<typename T>
  struct Formatter {
    const char* prefix_ = "\n  <-- ";
    const char* suffix_ = " -->";
    std::string transform(T& t) {
      return prefix_ + t + suffix_;
    }
  };

  /*---------------------------------------------------------
    template class partial specialization on Timer class
    - See Timer.h for details
  ---------------------------------------------------------*/

  template<typename T>
  class Logger<T, FNull, Timer> {
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