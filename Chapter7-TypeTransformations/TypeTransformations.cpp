// TypeTransformations.cpp

#include <type_traits>
#include <iostream>
#include <boost/type_index.hpp>
#include "../Chapter8-Display/Chap8Display.h"

void testTrans0(int i) {
  displayDemo("--- testTrans0(int i) ---");
  std::cout << "\n  boost type of i is " << boost::typeindex::type_id_runtime(i).pretty_name();
  std::cout << "\n  boost type of decltype(i) is " << boost::typeindex::type_id_with_cvr<decltype(i)>().pretty_name();
}
void testTrans0(const int* pI) {
  displayDemo("--- testTrans0(const int* pI) ---");
  std::cout << "\n  boost type of pI is " << boost::typeindex::type_id_runtime(pI).pretty_name();
  std::cout << "\n  boost type of decltype(pI) is " << boost::typeindex::type_id_with_cvr<decltype(pI)>().pretty_name();
}
void testTrans0(int iarr[3]) {
  displayDemo("--- testTrans0(int iarr[3]) ---");
  std::cout << "\n  boost type of iarr is " << boost::typeindex::type_id_runtime(iarr).pretty_name();
  std::cout << "\n  boost type of decltype(iarr) is " << boost::typeindex::type_id_with_cvr<decltype(iarr)>().pretty_name();
}
void testTrans0(const char* strLit) {
  displayDemo("--- testTrans0(\"a string literal\") ---");
  std::cout << "\n  boost type of \"a string literal\" is " << boost::typeindex::type_id_runtime("a string literal").pretty_name();
  std::cout << "\n  boost type of decltype(\"a string literal\") is " << boost::typeindex::type_id_with_cvr<decltype("a string literal")>().pretty_name();
}
template<typename T>
void testTrans1(T t) {
  displayDemo("--- testTrans1(T t) ---");
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans2(T& t) {
  displayDemo("--- testTrans2(T& t) ---");
  std::cout << "\n  boost type of T& is " << boost::typeindex::type_id_with_cvr<T&>().pretty_name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans2C(const T& t) {
  displayDemo("--- testTrans2C(const T& t) ---");
  std::cout << "\n  boost type of const T& is " << boost::typeindex::type_id_with_cvr<const T&>().pretty_name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans3(T* t) {
  displayDemo("--- testTrans3(T* pT) ---");
  std::cout << "\n  boost type of T* is " << boost::typeindex::type_id_with_cvr<T*>().pretty_name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans3C(const T* t) {
  displayDemo("--- testTrans3C(const T* pT) ---");
  std::cout << "\n  boost type of const T* is " << boost::typeindex::type_id_with_cvr<const T*>().pretty_name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans4(T&& t) {
  displayDemo("--- testTrans4(T&& t) ---");
  std::cout << "\n  boost type of T&& is " << boost::typeindex::type_id_with_cvr<T&&>().pretty_name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}

void f(int iarr[4]) {
  *iarr *= 2;
}

void showArray(int iarr[], size_t size) {
  std::cout << "\n  ";
  for (size_t i = 0; i < size; ++i) {
    std::cout << *(iarr + i) << " ";
  }
  std::cout << std::endl;
}

int main() {

  displayTitle("Testing Type Decay");

  int i{ 42 };
  std::cout << "\n  ---  int i{ 42 }; ---";
  std::cout << "\n  before call Boost type of i is " << boost::typeindex::type_id_runtime(i).pretty_name();

  const int& j = i;
  std::cout << "\n\n  ---  const int& j = i; ---";
  std::cout << "\n  before call Boost type of j is " << boost::typeindex::type_id_runtime(j).pretty_name();

  const int* pI = &i;
  std::cout << "\n\n  ---  int* pI = &i; ---";
  std::cout << "\n  before call Boost type of pI is " << boost::typeindex::type_id_runtime(pI).pretty_name();

  int iarr[4];
  std::cout << "\n\n  ---  int iarr[4]; ---";
  std::cout << "\n  before call Boost type of iarr[4] is " << boost::typeindex::type_id_runtime(iarr).pretty_name();

  const char* strLit = "a string literal";
  std::cout << "\n\n  --- \"a string literal\"";
  std::cout << "\n  before call Boost type of " << strLit << " is " << boost::typeindex::type_id_runtime("a literal string").pretty_name();

  std::cout << "\n  --- 42";
  std::cout << "\n  before call Boost type of " << 42 << " is " << boost::typeindex::type_id_runtime(42).pretty_name();

  std::cout << "\n\n  testTrans0";
  std::cout << "\n\n  param is i declared as int i";
  testTrans0(i);
  std::cout << "\n\n  param is j declared as const int& j";
  testTrans0(j);
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans0(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans0(iarr);
  std::cout << "\n\n  param is \"a string literal\"";
  testTrans0("a string literal");
  std::cout << "\n\n  param is int literal 42";
  testTrans0(42);

  std::cout << "\n\n  testTrans1";
  std::cout << "\n\n  param is i declared as int i";
  testTrans1(i);
  std::cout << "\n\n  param is j declared as const int& j";
  testTrans1(j);
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans1(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans1(iarr);
  std::cout << "\n\n  param is \"a string literal\"";
  testTrans1("a string literal");
  std::cout << "\n\n  param is int literal 42";
  testTrans1(42);

  std::cout << "\n\n  testTrans2";
  std::cout << "\n\n  param is i declared as int i";
  testTrans2(i);
  std::cout << "\n\n  param is j declared as const int& j";
  testTrans2(j);
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans2(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans2(iarr);
  std::cout << "\n\n  param is \"a string literal\"";
  testTrans2("a string literal");
  // won't compile - trying to bind rvalue to lvalue reference
  //std::cout << "\n\n  param is int literal 42";
  //testTrans2(42);

  std::cout << "\n\n  testTrans2C";
  std::cout << "\n\n  param is i declared as int i";
  testTrans2C(i);
  std::cout << "\n\n  param is j declared as const int& j";
  testTrans2C(j);
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans2C(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans2C(iarr);
  std::cout << "\n\n  param is \"a string literal\"";
  testTrans2C("a string literal");
  std::cout << "\n\n  param is int literal 42";
  testTrans2C(42);

  std::cout << "\n\n  testTrans3";
  //std::cout << "\n\n  param is i declared as int i";
  //testTrans3(i);
  //std::cout << "\n\n  param is j declared as const int& j";
  //testTrans3(j);
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans3(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans3(iarr);
  std::cout << "\n\n  param is \"a string literal\"";
  testTrans3("a string literal");

  std::cout << "\n\n  testTrans3C";
  //std::cout << "\n\n  param is i declared as int i";
  //testTrans3(i);
  //std::cout << "\n\n  param is j declared as const int& j";
  //testTrans3(j);
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans3C(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans3C(iarr);
  std::cout << "\n\n  param is \"a string literal\"";
  testTrans3C("a string literal");

  std::cout << "\n\n  testTrans4";
  std::cout << "\n\n  param is i declared as int i";
  testTrans4(i);
  std::cout << "\n\n  param is j declared as const int& j";
  testTrans4(j);
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans4(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans4(iarr);
  std::cout << "\n\n  param is \"a string literal\"";
  testTrans4("a string literal");
  std::cout << "\n\n  param is int literal 42";
  testTrans4(42);
  putline();

  displaySubtitle("Passing Array");
  int iarray[4]{ 1, 2, 3, 4 };
  f(iarray);
  showArray(iarray, 4);

  std::cout << "\n\n";
}