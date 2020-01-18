// Chap7TMP_Application.cpp

#include "Chap7TMP_Application.h"

using VecInt = std::vector<int>;

int main() {

  Query<VecInt> wInt;
  wInt.select(Items<VecInt>{ 1,2,3,4,5 });
  show(wInt);

  std::cout << "\n\n";
}