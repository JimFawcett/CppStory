// Chap7VariadicClassComp.cpp

#include "Chap8VariadicClassComp.h"
#include "../Chapter8-Display/Chap8Display.h"
#include <iostream>
#include <vector>

int main()
{
  displayTitle("Variadic Class Data by Composition");

  DataStructure<int, float, std::string> data1(1, 2.1f, "Hello");

  std::cout << "\n  " << data1.get<0>();
  std::cout << "\n  " << data1.get<1>();
  std::cout << "\n  " << data1.get<2>();
  putline();

  DataStructure<int, float, std::string> data2{ 2, 3.1f, "Hello again" };
  std::cout << "\n  " << data2.get<0>();
  std::cout << "\n  " << data2.get<1>();
  std::cout << "\n  " << data2.get<2>();
  putline();

  DataStructure<std::vector<int>> data3(std::vector<int>{1, 2, 3, 4, 5});
  std::vector<int> out = data3.get<0>();
  std::cout << "\n  ";
  for (auto item : out) {
    std::cout << item << " ";
  }
  putline(2);
  return 0;
}