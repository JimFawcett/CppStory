// Chap6QuickExample.cpp

#include <iostream>
#include <string>
#include "../Display/Display.h"

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
  */
  //ld.shout();

  std::cout << "\n\n";
}