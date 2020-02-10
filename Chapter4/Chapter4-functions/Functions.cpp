// Functions.cpp

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

void putLine(size_t n = 1) {
  for (size_t i = 0; i < n; ++i)
    std::cout << "\n";
}

size_t size(const std::string& s) {
  return s.size();
}

template <typename T>
void message(T t) {
  std::cout << t;
}

/* templates must be declared at namespace scope */

template<class Tr, class Ta>
using FP2 = Tr(*)(Ta t);

void demoFunctionPointers() {

  displayDemo("--- demoFunctionPointers ---");
  putLine();

  using FP1 = void(*)(size_t n);
  FP1 pl1 = putLine;

  FP2<void, size_t> pl2 = putLine;
  FP2<size_t, const std::string&> pSz = size;
  FP2<void, const std::string&> msg1 = message;
  
  auto& pl3 = putLine;
  auto& msg2 = message<const std::string&>;
  auto& msg3 = message<const char*>;
  auto& pSz2 = size;

  message("\n ------------------------");
  msg1("\n  testing PL1");
  pl1(1);
  msg2("\n  testing PL2");
  pl2(1);
  size_t sz = pSz("this is a string");
  msg2("\n  size of \"this is a string\" = " + std::to_string(sz));
  sz = pSz2("another, somewhat longer, string");
  msg2("\n  size of \"another, somewhat longer, string\" = " + std::to_string(sz));
  msg3("\n --------------");
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
  putLine();
}

class B {
public:
  void name(const std::string& aname) {
    name_ = aname;
  }
  std::string name() {
    return name_;
  }
protected:
  std::string name_;
};

class D : public B {
public:
  void occupation(const std::string& occup) {
    occupation_ = occup;
  }
  std::string occupation() {
    return occupation_;
  }
private:
  std::string occupation_;
}; 

void demoMethodPointers2()
{
  displayDemo("\n--- demoMethodPointers ---\n");

  using FP1 = void(D::B::*)(const std::string&);
  FP1 pNameSetter = &D::B::name;
  D d;
  (d.*pNameSetter)("Tom");

  using FP2 = std::string(D::B::*)();
  FP2 pNameGetter = &D::B::name;
  std::string name = (d.*pNameGetter)();
  std::cout << "\n  d1.name() --> " << name;

  using FP3 = void(D::*)(const std::string&);
  FP3 pOccupSetter = &D::occupation;
  (d.*pOccupSetter)("derivatives analyst");

  using FP4 = std::string(D::*)();
  FP4 pOccupGetter = &D::occupation;
  std::string myJob = (d.*pOccupGetter)();
  std::cout << "\n  d1.Occupation() -- > " << myJob;

  std::invoke(pNameSetter, d, "Darth Vader");
  std::string darth = std::invoke(pNameGetter, d);
  std::cout << "\n  his name is " << darth;

  /*-- alternate definitions --*/

  auto pOccuSetter2 = static_cast<std::string(D::*)()>(&D::occupation);
  auto pOccuGetter2 = static_cast<void(D::*)(const std::string&)>(&D::occupation);

  std::string(D:: * pOccuGetter3)() = &D::occupation;
  void(D:: * pOccuSetter3)(const std::string&) = &D::occupation;

  /*-- That's all folks --*/

  putLine();
}

void demoStdInvoke()
{
  displayDemo("--- demoStdInvoke ---");
  std::invoke(putLine, 1);
  size_t sz = std::invoke(size, "a test string");
  std::invoke(
    message<const std::string&>, "\n  size of \"a test string\" = " + 
    std::to_string(sz)
  );
}

class Functor {
public:
  template<typename T>
  void operator()(T element) {
    ++count_;
    std::cout << "\n  " << element;
  }
  size_t count() {
    return count_;
  }
  void name(const std::string& nm) {
    name_ = nm;
  }
  std::string name() {
    return name_;
  }
private:
  std::string name_;
  size_t count_ = 0;
};

void demoFunctors() {

  displayDemo("\n  --- demoFunctors ---\n");
  Functor fun;
  fun.name("counter");
  std::vector<std::string> numbers{ "one", "two", "three", "four", "five" };
  fun = std::for_each(numbers.begin(), numbers.end(), fun);
  std::cout << "\n  " << fun.name() << " processed " << fun.count() << " elements";
  putLine();
}

int main() {
  demoFunctionPointers();
  demoMethodPointers2();
  demoStdInvoke();
  demoFunctors();
  putline(2);
}