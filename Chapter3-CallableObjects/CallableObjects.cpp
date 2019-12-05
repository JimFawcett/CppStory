// CallableObjects.cpp

#include <iostream>
#include <string>
#include <functional>
#include "../Display/Display.h"

std::string suffix(size_t i) {
  std::string sfx;
  switch (i)
  {
  case 1:
    sfx = "st";
    break;
  case 2:
    sfx = "nd";
    break;
  case 3:
    sfx = "rd";
    break;
  default:
    sfx = "th";
    break;
  }
  return sfx;
}

void f(const std::string& type, size_t i) {
  std::cout << "\n  " << std::to_string(i) << suffix(i) + " invocation, a " + type;
}

void(*pFun)(const std::string&, size_t) = f;

class F {
public:
  void operator()(const std::string& type, size_t i) {
    std::cout << "\n  " << std::to_string(i) << suffix(i) + " invocation, a " + type;
  }
};

class C {
public:
  void method(const std::string& type, size_t i) {
    std::cout << "\n  " << std::to_string(i) << suffix(i) + " invocation, a " + type;
  }
};

using MPtr = void(C::*)(const std::string&, size_t);
MPtr pMethod = &C::method;

auto lam = [](const std::string& type, size_t i) {
  std::cout << "\n  " << std::to_string(i) << suffix(i) + " invocation, a " + type;
};

template<typename T>
void doInvoke(T t, const std::string& type, size_t count) {
  t(type, count);
}

template<typename U, typename V>
void doInvoke(U u, V v, const std::string& type, size_t count) {
  (u.*v)(type, count);
}

int main() {
  displayDemo("--- Callable Objects Demo ---");

  doInvoke(f, "function", 1);
  doInvoke(pFun, "function pointer", 2);
  doInvoke(F(), "functor", 3);
  doInvoke(lam, "lambda", 4);
  doInvoke(C(), pMethod, "method pointer", 5);
  putline();
  /* 
    std::invoke is more powerful than doInvoke as it takes an arbitry
    number of arguments.
    - the first may be a function, function pointer, or functor
      that take any number of arguments
    - the first may also be a method pointer.  That requires the second
      to be an instance of the class.  It accepts an arbitrary number
      of succeeding arguments.
    That is implemented with a variadic template.  Those will be discussed
    in Chapter #4 - Templates.
  */
  std::invoke(f, "function via std::invoke", 1);
  std::invoke(pFun, "function pointer via std::invoke", 2);
  std::invoke(F(), "functor via std::invoke", 3);
  std::invoke(lam, "lambda via std::invoke", 4);
  std::invoke(pMethod, C(), "method pointer via std::invoke", 5);
  std::cout << "\n\n";
}