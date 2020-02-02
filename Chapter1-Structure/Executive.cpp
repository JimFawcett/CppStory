///////////////////////////////////////////////////////////////
// Executive.cpp - Orchestrates program operations           //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "IComponent_A.h"
#include "Component_A_Factory.h"
#include "Component_B.h"
#include "../Chapter8-Display/Chap8Display.h"

int main() {
  Cosmetic<0> c;
  displayTitle("Demonstrating Code Structure");
  std::unique_ptr<IComponent_A> pAcomp = createComponent_A("Executives Component_A");
  pAcomp->say();

  Component_B bComp;
  bComp.say();
}

