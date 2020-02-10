// Chap7TypeTraits.cpp

#include "Chap8TypeTraits.h"
#include "../Chapter8-Display/Chap8Display.h"

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

  displayDemo("--- std containers ---");
  testSTL_Traits(std::array<int, 1>{1});
  testSTL_Traits(std::string{});
  testSTL_Traits(std::basic_string<char>{""});
  testSTL_Traits(std::vector<int>{});
  testSTL_Traits(std::deque<int>{});
  testSTL_Traits(std::forward_list<int>{});
  testSTL_Traits(std::list<int>{});
  testSTL_Traits(std::set<int>{});
  testSTL_Traits(std::multiset<int>{});
  testSTL_Traits(std::map<int,int>{});
  testSTL_Traits(std::multimap<int,int>{});
  testSTL_Traits(std::unordered_set<int>{});
  testSTL_Traits(std::unordered_multiset<int>{});
  testSTL_Traits(std::unordered_map<int, int>{});
  testSTL_Traits(std::unordered_multimap<int, int>{});
  testSTL_Traits(std::stack<int>{});
  testSTL_Traits(std::queue<int>{});
  testSTL_Traits(std::priority_queue<int>{});
  putline(2);
}