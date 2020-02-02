// TemplateFunctions.cpp

#include <string>
#include <iostream>
#include "../Chapter8-Display/Chap8Display.h"

namespace Chap6 {

  template<typename T1, typename T2>
  auto max(T1 t1, T2 t2) {
    displayDemo("--- using generic template ---");
    return t1 > t2 ? t1 : t2;
  }

  using pChar = const char*;
  auto max(pChar s1, pChar s2) {
    displayDemo("--- using overload for const char* ---");
    return ((strcmp(s1, s2) > 0) ? s1 : s2);
  }

  template<typename T>
  void f(T t) {
    std::cout << "\n  typeid(t).name() = " << typeid(t).name();
  }

  template<class R, class A1, class A2, class A3>
  R g(A1 a1, A2& a2, A3&& a3) {
    std::cout << "\n  typeid(a1).name() = " << typeid(a1).name();
    std::cout << "\n  typeid(a3).name() = " << typeid(a2).name();
    std::cout << "\n  typeid(a3).name() = " << typeid(a3).name();
    int numArgs = 3;
    return numArgs;
  }

  template<typename T>
  T h() {
    static T t = "static string";
    return t;
  }

  auto genericLambda = [](auto arg) {
    std::cout << "\n  the type of genericLambda's arg is: " << typeid(arg).name();
    std::cout << "\n  arg's value is: " << arg;
  };
}

int main() {

  using namespace Chap6;

  displayTitle("Demonstrate Template Functions");

  displaySubtitle("Demo max<T1, T2>");
  auto test1 = max(4, 2);
  std::cout << "\n  max(4,2) returns " << test1;
  std::cout << "\n  the return type of the last statement is: ";
  std::cout << typeid(test1).name();

  auto test2 = max(3.5, 2L); // fail with one arg
  std::cout << "\n  max(3.5, 2L) returns " << test2;
  std::cout << "\n  the return type of the last statement is: ";
  std::cout << typeid(test2).name();
  
  auto test3 = max(3.5, 4L);  // fail with one arg
  std::cout << "\n  max(3.5, 4L) returns " << test3;
  std::cout << "\n  the return type of the last statement is: ";
  std::cout << typeid(test3).name();

  auto test4 = max("aardvark", "zebra");
  std::cout << "\n  max(\"aardvark\", \"zebra\") returns " << test4;
  std::cout << "\n  the return type of the last statement is: ";
  std::cout << typeid(test4).name();

  auto test5 = max(std::string("a string"), "b string");  // fail with one type
  std::cout << "\n  max(std::string(\"a string\"), \"b string\") returns " 
            << "\"" << test5 << "\"";
  decltype(test5) what;
  std::cout << "\n  the return type of the last statement is:";
  std::cout << "\n  " << typeid(what).name();
  std::cout << "\n\n";

  displaySubtitle("Demo template forms");

  int i{ 3 };
  f(i);

  double d{ 3.1415927 };
  const std::string s = "a demo string";
  int j = g<int>(d, s, 'z');

  std::cout << "\n  " << h<std::string>();
  putline();

  displaySubtitle("Demo generic lambda");
  genericLambda(double{ 3.5 });
  genericLambda("this is a string");

  std::cout << "\n\n";
}