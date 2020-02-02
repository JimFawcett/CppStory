///////////////////////////////////////////////////////////////////////
// Chap7QuickExample.cpp - Illustrates Lazy Compilation of Templates //
//                                                                   //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ      //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "../Chapter8-Display/Chap8Display.h"

class Parameter {
public:
  void say() {
    std::cout << "\n  Parameter here";
  }
  /*---------------------------------------
    when commented out illustrates lazy
    compilation
   */
  //void shout() {
  //  std::string msg = "\n  [very loudly] ";
  //  msg += "Parameter here";
  //  std::cout << msg;
  //}
};

template<typename P>
class LazyDemo {
public:
  void say() {
    std::cout << "\n  LazyDemo here with ";
    p_.say();
  }
  void shout() {
    std::string msg = "\n  [very loudly] ";
    msg += "LazyDemo here with ";
    std::cout << msg;
    p_.shout();
  }
private:
  P p_;
};

int main() {

  displayDemo("-- Lazy Templ Compil --");

  LazyDemo<Parameter> ld;
  ld.say();

  /*---------------------------------------
     Uncommenting the next line will cause
     compilation error, because Parameter
     does not define shout.

     Note that compilation does not fail
     because LazyDemo::shout depends on
     Parameter::shout which is commented
     out. You only pay for what you need.
  */
  //ld.shout();

  std::cout << "\n\n";
}