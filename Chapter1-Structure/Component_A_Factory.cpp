///////////////////////////////////////////////////////////////
// Component_A_Factory.cpp - implements creational function  //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "Component_A_Factory.h"
#include "Component_A.h"

/*-----------------------------------------------
  factory function for Component_A
  - Note the difference between the parameters for
    unique_ptr as return value and inside
    createComponent_A.
  - factory implementation must be defined after
    the component class declaration, which is 
    located in Component_A.h.
*/
std::unique_ptr<IComponent_A> createComponent_A(const std::string& id) {
  return std::unique_ptr<Component_A>(new Component_A(id));
}