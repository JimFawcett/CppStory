// TemplateClasses.cpp

#include <iostream>
#include <string>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

namespace Chap6 {

  template<typename T>
  class SynDemo {
  public:
    void value(T t);
    T value();
  private:
    T t_;
  };

  template<typename T>
  void SynDemo<T>::value(T t) {
    t_ = t;
  }

  template<typename T>
  T SynDemo<T>::value() {
    return t_;
  }
}

int main() {

  displayTitle("Demonstrating Template Syntax");

  using namespace Chap6;

  SynDemo<std::string> sd;
  sd.value("hello world");
  std::cout << "\n  " << sd.value();
  putline(2);
}