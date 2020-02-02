// MemoryModel.cpp

#include <iostream>
#include <memory>
#include "../Chapter8-Display/Chap8Display.h"

size_t countAccesses() {
  static size_t visits = 0;
  return ++visits;
}

class WhereAmI {
public:
  WhereAmI() {
    std::cout << "\n  Constructing WhereAmI instance at address: "
              << this->location();
  }
  ~WhereAmI() {
    std::cout << "\n  WhereAmI instance destroyed";
  }
  std::uintptr_t location() {
    return reinterpret_cast<std::uintptr_t>(this);
  }
};

int main() {

  Cosmetic<0> c;

  displayTitle("Memory Model Demos");

  for (size_t i = 0; i < 5; ++i)
    std::cout << "\n  Counting accesses: " << countAccesses();
  putline();

  std::cout << "\n  Constructing a WhereAmI instance in static memory";
  static WhereAmI wai1;
  putline();

  std::cout << "\n  Constructing a WhereAmI instance in stack memory";
  WhereAmI wai2;
  putline();
  
  std::cout << "\n  Constructing a WhereAmI instance in heap memory";
  std::unique_ptr<WhereAmI>(new WhereAmI());
}

