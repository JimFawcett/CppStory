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

class X {
public:
  void say() {
    std::cout << "\n  X::say() here";
  }
  template<typename T>
  void message(T t) {
    std::cout << t;
  }
};

template<typename T>
using FP1 = void(X::*)(T t);

void demoMethodPointers()
{
  displayDemo("--- demoMethodPointers ---");
  putLine();

  using FP2 = void(X::*)();
  FP2 pSay = &X::say;
  X x1;
  (x1.*pSay)();
  std::invoke(pSay, x1);

  FP1<const std::string&> pMsg = &X::message;
  (x1.*pMsg)("\n  a message from x1");
  std::invoke(pMsg, x1, "\n  another message from x1");
}

int main() {
  demoFunctionPointers();
  demoMethodPointers();
  putline(2);
}