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
  
  std::cout << "\n\n";
}