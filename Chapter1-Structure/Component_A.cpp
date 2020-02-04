///////////////////////////////////////////////////////////////
// Component_A.cpp - implements Component_A operations       //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "Component_A.h"
#include "../Chapter8-Display/Chap8Display.h"
#include <iostream>

/*-----------------------------------------------
  factory function for Component_A
  - Note the difference between the parameters for
    unique_ptr as return value and inside
    createComponent_A.
  - factory implementation must be defined after
    the component class declaration.
*/
std::unique_ptr<IComponent_A> createComponent_A(const std::string& id) {
  return std::unique_ptr<Component_A>(new Component_A(id));
}

Component_A::~Component_A() {
  std::cout << "\n  Component_A instance " << id_ << " destroyed";
}

Component_A::Component_A(const std::string& id) : id_{ id } {
  std::cout << "\n\n  constructing instance of Component_A ";
  std::cout << "\n  with id = " << id_;
}

Component_A::Component_A(const Component_A& comp_a) {
  id_ = "copy of " + comp_a.id_;
  std::cout << "\n  copy construction of Component_A " << id_;
}
Component_A& Component_A::operator=(const Component_A& comp_a) {
  if (this != &comp_a) {
    id_ = "assigned from " + comp_a.id_;
    std::cout << "\n  assignment of Component_A " << id_;
  }
  return *this;
}

void Component_A::say() {
  std::cout << "\n  Hi, component " << id_ << " here";
};

using ICompPtr = std::unique_ptr<IComponent_A>;

#ifdef TEST_COMPONENT_A

int main() {
  Cosmetic c;

  /*-- demonstrate that factory function works --*/
  
  ICompPtr aPtr = createComponent_A("first A");
  aPtr->say();

  /*-- exercise Component_A methods --*/

  Component_A a2{ "second A" };  // constr with id
  Component_A a3{ a2 };          // copy ctor
  Component_A a4;
  a4 = a3;
  a4.say();

  std::cout << "\n\n";
}

#endif
