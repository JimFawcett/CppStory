// Chap7CustomTypeTraits.cpp

#include <vector>
#include <string>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <type_traits>
#include <iostream>
#include "../CustomTraits/CustomTraits.h"
#include "../Display/Display.h"

// http://www.cplusplus.com/reference/type_traits/integral_constant/

namespace Chap7 {

  /*---- is_array trait ----*/

  template<typename T>
  struct is_array : std::false_type {};

  template<typename T>
  struct is_array<T[]> : std::true_type {};

  /*---- is_stdarray trait ----*/

  template<typename T>
  struct is_stdarray : std::false_type {};

  template<typename T, size_t N>
  struct is_stdarray<std::array<T,N>> : std::true_type {};

  /*---- is_string trait ----*/

  template <typename T>
  struct is_string : std::false_type {};

  template <class T, class Traits, class Alloc>
  struct is_string<std::basic_string<T, Traits, Alloc>> : std::true_type {};

  /*---- is_vector trait ----*/

  template <typename T>
  struct is_vector : std::false_type {};

  template <class T>
  struct is_vector<std::vector<T>> : std::true_type {};

  /*---- is_deque trait ----*/

  template <typename T>
  struct is_deque : std::false_type {};

  template <class T>
  struct is_deque<std::deque<T>> : std::true_type {};

  /*---- is_forward_list trait ----*/

  template <typename T>
  struct is_forward_list : std::false_type {};

  template <class T>
  struct is_forward_list<std::forward_list<T>> : std::true_type {};

  /*---- is_list trait ----*/

  template <typename T>
  struct is_list : std::false_type {};

  template <class T>
  struct is_list<std::list<T>> : std::true_type {};

  /*---- is_set trait ----*/

  template <typename T>
  struct is_set : std::false_type {};

  template <class T>
  struct is_set<std::list<T>> : std::true_type {};

  /*---- is_pointer trait : pre C++11 style ----*/

  template <typename T>
  struct is_pointer
  {
    static const bool value = false;
  };

  template <typename T>
  struct is_pointer<T*>
  {
    static const bool value = true;
  };
  template<typename T, std::size_t N>
  struct is_array<T[N]> : std::true_type {};

  void put(const std::string& msg, size_t N = 50) {
    std::string tmp;
    if (msg.size() > N) {
      tmp = msg.substr(0, N-4) + " ...";
    }
    else {
      tmp = msg;
    }
    std::cout << "\n  " << tmp;
  }

  bool test(bool match, const std::string& msg) {
    if (match) {
      put(msg);
    }
    return match;
  }

  template<typename T>
  void query(T t, bool doPut = true) {
    bool r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;
    if(doPut) put(typeid(t).name());
    r1 = test(std::is_fundamental<T>::value, "type is fundamental");
    r2 = test(is_string<T>::value, "type is string");
    r3 = test(is_vector<T>::value, "type is vector");
    r4 = test(is_tuple<T>::value, "type is tuple");
    r5 = test(is_pair<T>::value, "type is pair");
    r6 = test(is_unordered_map<T>::value, "type is unordered_map");
    r7 = test(is_pointer<T>::value, "type is pointer");
    r8 = test(std::is_array<T>::value, "type is array");
    r9 = test(std::is_function<T>::value, "type is function");
    r10 = test(std::is_class<T>::value, "type is class");
    if (r1 || r2 || r3 || r4 || r5 || r6 || r7 || r8 || r9 || r10)
      return;
    put("don't recognize type");
  }
}

struct Foo {};

int main() {

  displayTitle("Demonstrate Custom Traits");

  displayDemo("--- std::integral_constant<bool,true> ---");
  std::cout << std::boolalpha;
  std::integral_constant<bool, true>::type typ;
  std::cout << "\n  " << typeid(typ).name();
  std::cout << "\n  " << typeid(std::integral_constant<bool, true>).name();
  auto val = std::integral_constant<bool, true>::value;
  std::cout << "\n  " << val;
  std::cout << "\n  " << static_cast<bool>(val);
  displayDemo("\n  --- std::true_type ---");
  std::cout << "\n  " << typeid(std::true_type).name();
  std::cout << "\n  " << std::true_type::value;
  displayDemo("\n  --- std::false_type ---");
  std::cout << "\n  " << typeid(std::false_type).name();
  std::cout << "\n  " << std::false_type::value;

  displayDemo("\n  --- type-traits ----");
  Chap7::query(std::string("a string"));
  putline();
  Chap7::query(int{ 3 });
  putline();
  Chap7::query(double{ 3.14159 });
  putline();
  Chap7::query(std::vector<int>{1, 2, 3});
  putline();
  Chap7::query(std::pair{ 1,2.5 });
  putline();
  Chap7::query(std::unordered_map<std::string, int>{});
  putline();
  Chap7::query(nullptr);
  putline();
  Chap7::query([] {});
  putline();
  Chap7::query(Foo{});
  putline();
  Foo foo;
  Chap7::query(&foo);
  putline();
  Foo farr[]{ foo, foo };
  int iarr[]{ 1,2,3 };
  Chap7::query(iarr);
  putline();
  Chap7::query(Chap7::query<int>);
  putline(2);
  std::cout << "\n  Foo farr[3] => Chap7::is_array<decltype(farr)>::value = " 
            << Chap7::is_array<decltype(farr)>::value;
  putline(2);
}
