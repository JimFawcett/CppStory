// TestingTypeTesters.cpp


#include <type_traits>
#include <iostream>
#include <boost/type_index.hpp>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

void testTrans0(int i) {
  displayDemo("--- testTrans0(int i) ---");
  std::cout << "\n  typeid of i is " << typeid(i).name();
  std::cout << "\n  typeid of decltype(i) is " << typeid(decltype(i)).name();
  std::cout << "\n  boost type of i is " << boost::typeindex::type_id_runtime(i).pretty_name();
  std::cout << "\n  boost type of decltype(i) is " << boost::typeindex::type_id_with_cvr<decltype(i)>().pretty_name();
}
void testTrans0(const int* pI) {
  displayDemo("--- testTrans0(const int* pI) ---");
  std::cout << "\n  typeid of pI is " << typeid(pI).name();
  std::cout << "\n  typeid of decltype(pI) is " << typeid(decltype(pI)).name();
  std::cout << "\n  boost type of pI is " << boost::typeindex::type_id_runtime(pI).pretty_name();
  std::cout << "\n  boost type of decltype(pI) is " << boost::typeindex::type_id_with_cvr<decltype(pI)>().pretty_name();
}
void testTrans0(int iarr[3]) {
  displayDemo("--- testTrans0(int iarr[3]) ---");
  std::cout << "\n  typeid of iarr is " << typeid(iarr).name();
  std::cout << "\n  typeid of decltype(iarr) is " << typeid(decltype(iarr)).name();
  std::cout << "\n  boost type of iarr is " << boost::typeindex::type_id_runtime(iarr).pretty_name();
  std::cout << "\n  boost type of decltype(iarr) is " << boost::typeindex::type_id_with_cvr<decltype(iarr)>().pretty_name();
}
template<typename T>
void testTrans1(T t) {
  displayDemo("--- testTrans1(T t) ---");
  std::cout << "\n  typeid of T is " << typeid(T).name();
  std::cout << "\n  typeid of t is " << typeid(t).name();
  std::cout << "\n  typeid of decltype(t) is " << typeid(decltype(t)).name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans2(T& t) {
  displayDemo("--- testTrans2(T& t) ---");
  std::cout << "\n  typeid of T is " << typeid(T).name();
  std::cout << "\n  typeid of t is " << typeid(t).name();
  std::cout << "\n  typeid of decltype(t) is " << typeid(decltype(t)).name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans2C(const T& t) {
  displayDemo("--- testTrans2C(const T& t) ---");
  std::cout << "\n  typeid of T is " << typeid(T).name();
  std::cout << "\n  typeid of t is " << typeid(t).name();
  std::cout << "\n  typeid of decltype(t) is " << typeid(decltype(t)).name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans3(T* t) {
  displayDemo("--- testTrans4(T&& t) ---");
  std::cout << "\n  typeid of T is " << typeid(T).name();
  std::cout << "\n  typeid of t is " << typeid(t).name();
  std::cout << "\n  typeid of decltype(t) is " << typeid(decltype(t)).name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans3C(const T* t) {
  displayDemo("--- testTrans4(T&& t) ---");
  std::cout << "\n  typeid of T is " << typeid(T).name();
  std::cout << "\n  typeid of t is " << typeid(t).name();
  std::cout << "\n  typeid of decltype(t) is " << typeid(decltype(t)).name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}
template<typename T>
void testTrans4(T&& t) {
  displayDemo("--- testTrans4(T&& t) ---");
  std::cout << "\n  typeid of T is " << typeid(T).name();
  std::cout << "\n  typeid of t is " << typeid(t).name();
  std::cout << "\n  typeid of decltype(t) is " << typeid(decltype(t)).name();
  std::cout << "\n  boost type of T is " << boost::typeindex::type_id_with_cvr<T>().pretty_name();
  std::cout << "\n  boost type of t is " << boost::typeindex::type_id_runtime(t).pretty_name();
  std::cout << "\n  boost type of decltype(t) is " << boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
}

int main() {

  displayTitle("Testing Type Decay");

  int i{ 42 };
  std::cout << "\n  ---  int i{ 42 }; ---";
  std::cout << "\n  before call typeid of i is " << typeid(i).name();
  std::cout << "\n  before call typeid of decltype(i) is " << typeid(decltype(i)).name();
  std::cout << "\n  before call Boost type of i is " << boost::typeindex::type_id_runtime(i).pretty_name();

  const int& j = i;
  std::cout << "\n\n  ---  const int& j = i; ---";
  std::cout << "\n  before call typeid of j is " << typeid(j).name();
  std::cout << "\n  before call typeid of decltype(j) is " << typeid(decltype(j)).name();
  std::cout << "\n  before call Boost type of j is " << boost::typeindex::type_id_runtime(j).pretty_name();

  const int* pI = &i;
  std::cout << "\n\n  ---  int* pI = &i; ---";
  std::cout << "\n  before call typeid of pI is " << typeid(pI).name();
  std::cout << "\n  before call typeid of decltype(pI) is " << typeid(decltype(pI)).name();
  std::cout << "\n  before call Boost type of pI is " << boost::typeindex::type_id_runtime(pI).pretty_name();

  int iarr[4];
  std::cout << "\n\n  ---  int iarr[4]; ---";
  std::cout << "\n  before call typeid of iarr is " << typeid(iarr).name();
  std::cout << "\n  before call typeid of decltype(iarr) is " << typeid(decltype(iarr)).name();
  std::cout << "\n  before call Boost type of iarr[4] is " << boost::typeindex::type_id_runtime(iarr).pretty_name();

  std::cout << "\n\n  testTrans0";
  std::cout << "\n\n  param is i declared as int i";
  testTrans0(i);
  std::cout << "\n\n  param is j declared as const int& j";
  testTrans0(j);
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans0(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans0(iarr);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
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
  std::cout << "\n\n  param is string literal \"a string literal\"";
  testTrans1("a string literal");
  std::cout << "\n\n  param is an int literal 42";
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
  std::cout << "\n\n  param is string literal \"a string literal\"";
  testTrans2("a string literal");
  /////////////////////////////////////////////////////
  //won't compile
  //std::cout << "\n\n  param is an int literal 42";
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
  std::cout << "\n\n  param is string literal \"a string literal\"";
  testTrans2C("a string literal");
  std::cout << "\n\n  param is an int literal 42";
  testTrans2C(42);

  std::cout << "\n\n  testTrans3";
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans3(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans3(iarr);
  std::cout << "\n\n  param is string literal \"a string literal\"";
  testTrans3("a string literal");

  std::cout << "\n\n  testTrans3C";
  std::cout << "\n\n  param is pI declared as const int* pI";
  testTrans3C(pI);
  std::cout << "\n\n  param is iarr declared as int iarr[4]";
  testTrans3C(iarr);
  std::cout << "\n\n  param is string literal \"a string literal\"";
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
  std::cout << "\n\n  param is string literal \"a string literal\"";
  testTrans4("a string literal");
  std::cout << "\n\n  param is an int literal 42";
  testTrans4(42);

  std::cout << "\n\n";
}