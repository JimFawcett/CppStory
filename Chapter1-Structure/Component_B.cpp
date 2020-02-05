///////////////////////////////////////////////////////////////
// Component_B.cpp - implements Component_B operations       //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "Component_B.h"
#include <iostream>
#include <string>

class Helper {
public:
  static void context();
};
void Helper::context() {
#ifdef TEST_COMPONENT_B
  std::cout << "\n  Testing Component_B";
#else
  std::cout << "\n  Component_B used by other classes";
#endif
}
Component_B::Component_B() {
  std::cout << "\n\n  default construction of Component_B instance";
  Helper::context();
  pA_ = createComponent_A("B's Component_A");
}
Component_B::~Component_B() {
  std::cout << "\n  destruction of Component_B instance";
}
void Component_B::say() {
  std::cout << "\n  Component_B instance here, holding pointer to my Component_A";
  pA_->say();
}

#ifdef TEST_COMPONENT_B

int main() {
  Cosmetic c;
  Component_B b;
  b.say();
}

#endif
