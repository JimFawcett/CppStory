// Chap7TypeTraits.cpp

#include <iostream>
#include <type_traits>
#include "..//Display/Display.h"

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
  template<typename T> struct is_vector :std::false_type {};
  template <typename... Args> struct is_vector < std::vector<Args...>> :std::true_type {};
}
template<typename T> struct is_vector {
  static constexpr bool const value = impl::is_vector<std::decay_t<T >> ::value;
};

template <class T,
  typename std::enable_if<std::is_integral<T>::value,
  T>::type * = nullptr
>
void do_stuff(T& t) {
  std::cout << "\n  doing integral stuff with type " << typeid(t).name();
}

template <class T,
  typename std::enable_if<std::is_class<T>::value,
  T>::type * = nullptr
>
void do_stuff(T& t) {
  std::cout << "\n  doing class stuff with type " << typeid(t).name();
}

int main() {

  std::cout << "\n  " << typeid(TypeRep<double>::type).name();

  std::cout << "\n  " << ValueRep<int, 3>::value;

  std::cout << "\n  " << typeid(ExpressionRep<int, 3>::type).name() << ", " << ExpressionRep<int, 3>::value;

  std::cout << std::boolalpha;
  std::cout << "\n  " << typeid(ExpressionRep<bool, true>::type).name() << ", " << ExpressionRep<bool, true>::value;
  
  constexpr int v = 0;
  std::cout << "\n  " << typeid(ExpRep2<size_t, v>).name() << ", " << ExpRep2<size_t, v>::get();
  std::cout << "\n  " << ExpRep2<int, v>::addOne();
  std::cout << "\n  " << ExpRep2<int, v>();
  std::cout << "\n  " << ExpRep2<int, v>::subOne();
  putline();
  std::cout << "\n  " << typeid(std::integral_constant<int, 0>::type).name();
  std::cout << "\n  " << std::integral_constant<int, 0>::value;

  std::cout << "\n  " << typeid(integral_constant_t<int, 0>).name();
  std::cout << "\n  " << integral_constant_v<int, 0>;
  putline();

  std::cout << "\n  " << is_void<void>::value;
  std::cout << "\n  " << is_void<int>::value;
  
  displayDemo("--- is_vector ---");
  std::cout << "\n  " << is_vector<std::vector<int>>::value;
  std::cout << "\n  " << is_vector<std::vector<double>>::value;
  std::cout << "\n  " << is_vector<std::unordered_map<int, std::string>>::value;

  displayDemo("--- enable_if ---");
  class X {};
  X x;
  int i = 42;
  do_stuff(i);
  do_stuff(x);
  std::string s("a string");
  do_stuff(s);
  std::cout << "\n\n";
}