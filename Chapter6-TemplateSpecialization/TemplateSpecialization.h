#pragma once
///////////////////////////////////////////////////////////////
// TemplateSpecialization.h - template specialization demo   //
//                                                           //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse Univ   //
///////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <type_traits>
//#include "Timer.h"

namespace Chap6 {

  /*--------------------------------------------------------- 
    unspecialized template class
    - U is a placeholder, used only to provide a place for
      specialization.
    - This is a simple demo, but could easily be expanded
      into a useful facility
  ---------------------------------------------------------*/

  struct TNull {};

  template<typename S>
  struct FNull {};

  template<
    typename S, 
    template<typename S> typename F = FNull, 
    typename T = TNull>
  class Logger { 
    /*-- used to set specialization structure */ 
  };

  template<typename S>
  class Logger<S, FNull, TNull> {
  public:
    Logger(std::ostream* pStr) : pStream_(pStr) {}
    ~Logger() {}
    void write(S s) {
      (*pStream_) << prefix_ << s;
    }
  private:
    std::string prefix_ = "\n  ";
    std::ostream* pStream_;
  };

  /*---------------------------------------------------------
    template class partial specialization on Formatter class
    Formatter class used to specialize Logger<S,Formatter,T>
    - this is partial class specialization since S and F
      are still unspecified
  ---------------------------------------------------------*/

  template<typename S>
  struct Formatter {
    const char* prefix_ = "\n  <-- ";
    const char* suffix_ = " -->";
    std::string transform(const S& s) {
      return prefix_ + s + suffix_;
    }
  };

  template<typename S, template<typename S> typename F>
  class Logger<S, F, TNull> {
  public:
    Logger(std::ostream* pStr) : pStream_(pStr) {}
    ~Logger() {}
    void write(S s) {
      (*pStream_) << f.transform(s);
    }
  private:
    std::string prefix_ = "\n  ";
    std::ostream* pStream_;
    F<S> f;
  };
  
  /*---------------------------------------------------------
    template class partial specialization on Timer class
    - See Timer.h for details
  ---------------------------------------------------------*/

  template<typename S, typename T>
  class Logger<S, FNull, T> {
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
    void write(S s) {
      (*pStream_) << prefix_ << std::setw(6) 
                  << timer_.elapsedMicroseconds() 
                  << " microsec : " << s;
    }
  private:
    std::string prefix_ = "\n  ";
    T timer_;
    std::ostream* pStream_;
  };
}