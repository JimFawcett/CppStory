// Chap6QuickExample.cpp

#include <iostream>
#include <typeinfo>
#include <tuple>
#include "../Chapter8-Display/Chap8Display.h"

// https://stackoverflow.com/questions/1198260/how-can-you-iterate-over-the-elements-of-an-stdtuple

namespace Chap7 {

  // displayTuple specialization stops recursion
  template<std::size_t I = 0, typename... Tp>
  inline typename std::enable_if<I == sizeof...(Tp), void>::type
  displayTuple(std::tuple<Tp...>& t) { }

  // recursive definition of displayTuple
  template<std::size_t I = 0, typename... Tp>
  inline typename std::enable_if < I < sizeof...(Tp), void>::type
  displayTuple(std::tuple<Tp...> & t)
  {
    std::cout << std::get<I>(t) << " ";
    displayTuple<I + 1, Tp...>(t);
  }

  // simpler recursive definition
  template<size_t I = 0, typename... Tp>
  void showTuple(std::tuple<Tp...>& t) {
    std::cout << std::get<I>(t) << " ";
    if constexpr (I + 1 != sizeof...(Tp))
      showTuple<I + 1>(t);
  }
}

int main() {

  displayTitle("Demonstrate TMP with std::tuple display");

  std::tuple t{ 1, 2.5, 'a', "a string" };
  std::cout << "\n  ";
  Chap7::displayTuple(t);
  putline();
  std::cout << "\n  ";
  Chap7::showTuple(t);

  std::cout << "\n\n";
}