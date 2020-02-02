///////////////////////////////////////////////////////////////
// Component_B.cpp - implements Component_B operations       //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "Component_B.h"
#include "Component_A_Factory.h"
#include <iostream>
#include <string>

Component_B::Component_B() {
  std::cout << "\n  default construction of Component_B instance";
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
