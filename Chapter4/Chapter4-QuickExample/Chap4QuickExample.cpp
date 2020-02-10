// Chap4QuickExample.cpp

#include <iostream>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

/*-- define function dispatcher --*/

using FPtr = void(*)();

void fun1() { 
  std::cout << "\n  index == 1 => fun1 called"; 
}
void fun2() { 
  std::cout << "\n  index == 2 => fun2 called"; 
}
void fun3() { 
  std::cout << "\n  index == 3 => fun3 called"; 
}
void oophs() {
  std::string msg = "other index => ";
  msg += "can't find that function";
  std::cout << "\n  " << msg;
}

auto functionDispatcher(size_t index) {
  switch (index) {
  case 1:
    return &fun1;
    break;
  case 2:
    return &fun2;
    break;
  case 3:
    return &fun3;
    break;
  default:
    return &oophs;
  }
}

/*-- define callback --*/

void applicationSpecificCallback() {
  std::string msg = "Pretending to cleanup ";
  msg += "at end of function";
  std::cout << "\n  " << msg;
}

auto functionWithCallback(FPtr callback) {
  std::string msg = "Pretending to do some ";
  msg += "standard function";
  std::cout << "\n  " << msg;
  callback();
}

int main() {

  /* must use C++17 option to compile */

  displayDemo("-- function dispatcher --\n");
  functionDispatcher(1)();
  functionDispatcher(2)();
  functionDispatcher(3)();
  functionDispatcher(4)();

  displayDemo("\n  -- function with callback --");
  functionWithCallback(
    applicationSpecificCallback
  );

  std::cout << "\n\n";
}