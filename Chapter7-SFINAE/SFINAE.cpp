// SFINAE.cpp

#include <iostream>
#include <vector>
#include "../Chapter8-Display/Chap8Display.h"

template<typename T, size_t N>
void show(const T (&array)[N]) {
  displayDemo("--- show array contents ---");
  std::cout << "\n  ";
  for (size_t i = 0; i < N; ++i)
    std::cout << array[i] << " ";
}

template<typename C>
void show(const C& cont) {
  displayDemo("--- show container contents ---");
  std::cout << "\n  ";
  for (auto item : cont) {
    std::cout << item << " ";
  }
}

int main() {

  displayTitle("SFINAE Demo");

  std::cout << "\n  displaying array:";
  double array[5]{ -0.5, 0.0, 0.5, 1.0, 1.5 };
  show(array);

  std::cout << "\n  displaying vector";
  std::vector<int> vInt{ -1, 0, 1, 2, 3 };
  show(vInt);

  // show(array);
  // attempted template argument deduction for both show functions
  // - show(const T (&array)[n]) succeeded, built, and used
  // - show(const C& cont) succeeded but less specific so not used

  // show(vInt)
  // attempted template argument deduction for both show functions
  // - show(const T (&array)[n]) failed, vInt is not an array, 
  //   but this is not a compilation error (SFINAE)
  // - show(const C& cont) succeeded, built, and used

  // show(3.14159);
  // argument deduction for show(const T (&array)[N]) fails
  // - double is not an array
  // argument deduction succeeds with show(const C& cont)
  // - compilation of body for double fails, i.e., 
  //   no iterator, begin(), or end() for range-based for

  std::cout << "\n\n";
}