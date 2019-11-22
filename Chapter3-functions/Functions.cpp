// Functions.cpp

#include <iostream>
#include <string>
#include "../Display/Display.h"

void putLine(size_t n = 1) {
  for (size_t i = 0; i < n; ++i)
    std::cout << "\n";
}

template <typename T>
void message(T t) {
  std::cout << t;
}

template<class T>
using FP2 = void(*)(T t);

void demoFunctionPointers() {

  displayDemo("--- demoFunctionPointers ---");
  putLine();
  using FP1 = void(*)(size_t n);
  FP1 pl1 = putLine;
  FP2<size_t> pl2 = putLine;
  FP2<const std::string&> msg1 = message;
  
  auto& pl3 = putLine;
  auto& msg2 = message<const std::string&>;
  auto& msg3 = message<const char*>;

  ///////////////////////////////////////////////
  // code below fails to compile
  // Can't declare templates in function scope
  //
  // template<class T>
  // using FP2 = typename void(*)(T t);

  message("\n ------------------------");
  msg1("\n  testing PL1");
  pl1(1);
  msg2("\n  testing PL2");
  pl2(1);
  msg3("\n --------------");
  pl3(1);
  message("\n  done with testing");
  message("\n ------------------------\n");
}

int main() {
  demoFunctionPointers();
  putline(2);
}