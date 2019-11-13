// Overloading.cpp

#include <utility>
#include <optional>
#include <vector>
#include <iostream>

/*---- find first and last elements of collection, may throw ----*/

using PD = std::pair<double, double>;

PD firstAndLast(double dArr[], size_t N) {
  if (N < 1)
    throw std::exception("no contents in array");
  return PD{ dArr[0], dArr[N - 1] };
}

using PI = std::pair<int, int>;

PI firstAndLast(const std::vector<int>& vecInt) {
  if (vecInt.size() < 1)
    throw std::exception("no contents in vector");
  return PI{ vecInt[0], vecInt[vecInt.size() - 1] };
}

/*---- find first and last elements of collection, using optional ----*/

std::optional<PD> firstAndLastOpt(double dArr[], size_t N) {
  std::optional<PD> opt;
  if(N > 0)
    opt = std::pair{ dArr[0], dArr[N - 1] };
  return opt;
}

std::optional<PI> firstAndLastOpt(const std::vector<int>& vecInt) {
  std::optional<PI> opt;
  if (vecInt.size() > 0)
    opt = std::pair{ vecInt[0], vecInt[vecInt.size() - 1] };
  return opt;
}

/*---- demonstrate first and last ----*/

int main() {

  std::cout << "\n  Demonstrating Function Overloading";
  std::cout << "\n ====================================\n";

  double dArr[]{ 1.5, -0.5, 3.0 };
  std::vector<int> vecInt{ 1,2,3,4,5 };

  try {
    auto [firstd1, lastd1] = firstAndLast(dArr, 3);
    std::cout << "\n  first = " << firstd1 << ", last = " << lastd1;

    auto [firsti1, lasti1] = firstAndLast(vecInt);
    std::cout << "\n  first = " << firsti1 << ", last = " << lasti1;
  }
  catch (std::exception & ex) {
    std::cout << "\n  " << ex.what() << std::endl;
  }

  std::optional<PD> optd = firstAndLastOpt(dArr, 3);
  if (optd.has_value()) {
    auto [firstd2, lastd2] = optd.value();
    std::cout << "\n  first = " << firstd2 << ", last = " << lastd2;
  }
  else {
    std::cout << "\n  array query failed";
  }

  std::optional<PI> opti = firstAndLastOpt(vecInt);
  if (opti.has_value()) {
    auto [firsti2, lasti2] = opti.value();
    std::cout << "\n  first = " << firsti2 << ", last = " << lasti2;
  }
  else {
    std::cout << "\n  vector query failed";
  }
  
  std::cout << "\n\n";
}