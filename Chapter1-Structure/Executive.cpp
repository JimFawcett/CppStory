///////////////////////////////////////////////////////////////
// Executive.cpp - Orchestrates program operations           //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "IComponent_A.h"
#include "Component_B.h"
#include "../Chapter8-Display/Chap8Display.h"
#include <memory>

class Executive {
public:
  Executive();
  void demo();
private:
  void useA();
  void useB();
  std::unique_ptr<IComponent_A> pA_;
  Component_B b_;
};

Executive::Executive() {
  pA_ = createComponent_A("Component_A");
}

void Executive::useA() {
  pA_->say();
}

void Executive::useB() {
  b_.say();
}

void Executive::demo() {
  useA();
  useB();
}

int main() {
  Cosmetic<0> c; // emits two linefeeds at end of output

  displayTitle("Demonstrating Code Structure");

  displayDemo("-- using Component_A and Component_B directly --");

  std::unique_ptr<IComponent_A> pAcomp = createComponent_A("Executive's Component_A");
  pAcomp->say();

  Component_B bComp;
  bComp.say();

  displayDemo("\n  -- using Component_A and Component_B through Executive --");
  Executive exec;
  exec.demo();
  putline();
}

