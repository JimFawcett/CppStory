#pragma once

#include <iostream>
#include <type_traits>
#include <array>
#include <string>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

//#include "..//Display/Display.h"

template<typename T>
struct TypeRep {
  using type = T;
};

template<typename T, T v>
struct ValueRep {
  static constexpr T value = v;
};

template<typename T, T v>
struct ExpressionRep {
  using type = T;
  static constexpr T value = v;
  constexpr operator T() { return v; }
};

template<typename T, T v>
struct ExpRep2 {
  using type = T;
  static constexpr T value = v;
  constexpr operator T() { return v; }
  static constexpr T get() { return v; }
  static constexpr T addOne() { return (v + 1); }
  static constexpr T subOne() { return (v - 1); }
};

template<typename T, T v>
using integral_constant_t = typename std::integral_constant<T, v>::type;

template<typename T, T v>
auto integral_constant_v = std::integral_constant<T, v>::value;

template<typename T>
struct is_void : std::false_type {};

template<>
struct is_void<void> : std::true_type {};



// https://stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time/31105859#31105859

namespace impl {

  template<typename T> struct is_pair :std::false_type {};
  template <typename... Args> struct is_pair < std::pair<Args...>> :std::true_type {};

  template<typename T> struct is_tuple :std::false_type {};
  template <typename... Args> struct is_tuple < std::tuple<Args...>> :std::true_type {};

  template<typename T> struct is_array :std::false_type {};
  template <typename T, size_t N> struct is_array < std::array<T, N>> :std::true_type {};

  template<typename T> struct is_basic_string :std::false_type {};
  template <typename... Args> struct is_basic_string < std::basic_string<Args...>> :std::true_type {};

  template<typename T> struct is_vector :std::false_type {};
  template <typename... Args> struct is_vector < std::vector<Args...>> :std::true_type {};

  template<typename T> struct is_deque :std::false_type {};
  template <typename... Args> struct is_deque < std::deque<Args...>> :std::true_type {};

  template<typename T> struct is_forward_list :std::false_type {};
  template <typename... Args> struct is_forward_list < std::forward_list<Args...>> :std::true_type {};

  template<typename T> struct is_list :std::false_type {};
  template <typename... Args> struct is_list < std::list<Args...>> :std::true_type {};

  template<typename T> struct is_set :std::false_type {};
  template <typename... Args> struct is_set < std::set<Args...>> :std::true_type {};

  template<typename T> struct is_multiset :std::false_type {};
  template <typename... Args> struct is_multiset < std::multiset<Args...>> :std::true_type {};

  template<typename T> struct is_map :std::false_type {};
  template <typename... Args> struct is_map < std::map<Args...>> :std::true_type {};

  template<typename T> struct is_multimap :std::false_type {};
  template <typename... Args> struct is_multimap < std::multimap<Args...>> :std::true_type {};

  template<typename T> struct is_unordered_set :std::false_type {};
  template <typename... Args> struct is_unordered_set < std::unordered_set<Args...>> :std::true_type {};

  template<typename T> struct is_unordered_multiset :std::false_type {};
  template <typename... Args> struct is_unordered_multiset < std::unordered_multiset<Args...>> :std::true_type {};

  template<typename T> struct is_unordered_map :std::false_type {};
  template <typename... Args> struct is_unordered_map < std::unordered_map<Args...>> :std::true_type {};

  template<typename T> struct is_unordered_multimap :std::false_type {};
  template <typename... Args> struct is_unordered_multimap < std::unordered_multimap<Args...>> :std::true_type {};

  template<typename T> struct is_queue :std::false_type {};
  template <typename... Args> struct is_queue < std::queue<Args...>> :std::true_type {};

  template<typename T> struct is_stack :std::false_type {};
  template <typename... Args> struct is_stack < std::stack<Args...>> :std::true_type {};

  template<typename T> struct is_priority_queue :std::false_type {};
  template <typename... Args> struct is_priority_queue < std::priority_queue<Args...>> :std::true_type {};
}

template<typename T> struct is_pair {
  static constexpr bool const value = impl::is_pair<std::decay_t<T >> ::value;
};

template<typename T> struct is_tuple {
  static constexpr bool const value = impl::is_tuple<std::decay_t<T >> ::value;
};

template<typename T> struct is_string :std::false_type {};
template<> struct is_string<std::string> : std::true_type {};

template<typename T> struct is_array {
  static constexpr bool const value = impl::is_array<std::decay_t<T >> ::value;
};

template<typename T> struct is_basic_string {
  static constexpr bool const value = impl::is_basic_string<std::decay_t<T >> ::value;
};

template<typename T> struct is_vector {
  static constexpr bool const value = impl::is_vector<std::decay_t<T >> ::value;
};

template<typename T> struct is_deque {
  static constexpr bool const value = impl::is_deque<std::decay_t<T >> ::value;
};

template<typename T> struct is_forward_list {
  static constexpr bool const value = impl::is_forward_list<std::decay_t<T >> ::value;
};

template<typename T> struct is_list {
  static constexpr bool const value = impl::is_list<std::decay_t<T >> ::value;
};

template<typename T> struct is_set {
  static constexpr bool const value = impl::is_set<std::decay_t<T >> ::value;
};

template<typename T> struct is_multiset {
  static constexpr bool const value = impl::is_multiset<std::decay_t<T >> ::value;
};

template<typename T> struct is_map {
  static constexpr bool const value = impl::is_map<std::decay_t<T >> ::value;
};

template<typename T> struct is_multimap {
  static constexpr bool const value = impl::is_multimap<std::decay_t<T >> ::value;
};

template<typename T> struct is_unordered_set {
  static constexpr bool const value = impl::is_unordered_set<std::decay_t<T >> ::value;
};

template<typename T> struct is_unordered_multiset {
  static constexpr bool const value = impl::is_unordered_multiset<std::decay_t<T >> ::value;
};

template<typename T> struct is_unordered_map {
  static constexpr bool const value = impl::is_unordered_map<std::decay_t<T >> ::value;
};

template<typename T> struct is_unordered_multimap {
  static constexpr bool const value = impl::is_unordered_multimap<std::decay_t<T >> ::value;
};

template<typename T> struct is_stack {
  static constexpr bool const value = impl::is_stack<std::decay_t<T >> ::value;
};

template<typename T> struct is_queue {
  static constexpr bool const value = impl::is_queue<std::decay_t<T >> ::value;
};

template<typename T> struct is_priority_queue {
  static constexpr bool const value = impl::is_priority_queue<std::decay_t<T >> ::value;
};

std::string truncStr(const std::string& s) {
  if (s.size() < 47)
    return s;
  return s.substr(0, 46) + " ...";
}

template<typename T>
using is_seqcont = std::integral_constant<
  bool,
  is_array<T>::value ||
  is_string<T>::value ||
  is_basic_string<T>::value ||
  is_vector<T>::value ||
  is_deque<T>::value ||
  is_forward_list<T>::value ||
  is_list<T>::value
>;

template<typename T>
using is_assoccont = std::integral_constant<
  bool,
  is_set<T>::value ||
  is_multiset<T>::value ||
  is_map<T>::value ||
  is_multimap<T>::value ||
  is_unordered_set<T>::value ||
  is_unordered_multiset<T>::value ||
  is_unordered_map<T>::value ||
  is_unordered_multimap<T>::value
>;

template<typename T>
using is_adaptercont = std::integral_constant<
  bool,
  is_stack<T>::value ||
  is_queue<T>::value ||
  is_priority_queue<T>::value
>;

template<typename T>
void testSTL_Traits(const T& t) {
  if constexpr (is_seqcont<T>::value) {
    std::cout << "\n  is sequential container";
  }
  if constexpr (is_assoccont<T>::value) {
    std::cout << "\n  is associative container";
  }
  if constexpr (is_adaptercont<T>::value) {
    std::cout << "\n  is adapter container";
  }
  if constexpr (is_array<T>::value) {
    std::cout << "\n  is array: " << truncStr(typeid(t).name());
  }
  if constexpr (is_string<T>::value) {
    std::cout << "\n  is std::string: " << truncStr(typeid(t).name());
  }
  if constexpr (is_basic_string<T>::value) {
    std::cout << "\n  is std::basic_string: " << truncStr(typeid(t).name());
  }
  if constexpr (is_vector<T>::value) {
    std::cout << "\n  is std::vector: " << truncStr(typeid(t).name());
  }
  if constexpr (is_deque<T>::value) {
    std::cout << "\n  is std::deque: " << truncStr(typeid(t).name());
  }
  if constexpr (is_forward_list<T>::value) {
    std::cout << "\n  is std::forward_list: " << truncStr(typeid(t).name());
  }
  if constexpr (is_list<T>::value) {
    std::cout << "\n  is std::list: " << truncStr(typeid(t).name());
  }
  if constexpr (is_set<T>::value) {
    std::cout << "\n  is std::set: " << truncStr(typeid(t).name());
  }
  if constexpr (is_multiset<T>::value) {
    std::cout << "\n  is std::multiset: " << truncStr(typeid(t).name());
  }
  if constexpr (is_map<T>::value) {
    std::cout << "\n  is std::map: " << truncStr(typeid(t).name());
  }
  if constexpr (is_multimap<T>::value) {
    std::cout << "\n  is std::multimap: " << truncStr(typeid(t).name());
  }
  if constexpr (is_unordered_set<T>::value) {
    std::cout << "\n  is std::unordered_set: " << truncStr(typeid(t).name());
  }
  if constexpr (is_unordered_multiset<T>::value) {
    std::cout << "\n  is std::unordered_multiset: " << truncStr(typeid(t).name());
  }
  if constexpr (is_unordered_map<T>::value) {
    std::cout << "\n  is std::unordered_map: " << truncStr(typeid(t).name());
  }
  if constexpr (is_unordered_multimap<T>::value) {
    std::cout << "\n  is std::unordered_multimap: " << truncStr(typeid(t).name());
  }
  if constexpr (is_stack<T>::value) {
    std::cout << "\n  is std::stack: " << truncStr(typeid(t).name());
  }
  if constexpr (is_queue<T>::value) {
    std::cout << "\n  is std::queue: " << truncStr(typeid(t).name());
  }
  if constexpr (is_priority_queue<T>::value) {
    std::cout << "\n  is std::priority_queue: " << truncStr(typeid(t).name());
  }
}