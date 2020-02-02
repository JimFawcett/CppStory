/////////////////////////////////////////////////////////////////
// Chap8VariadicClassMixins.cpp - demonstrates variadic mixins //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018   //
/////////////////////////////////////////////////////////////////

#include "Chap8VariadicClassMixins.h"

using namespace Chap7;

int main()
{
  std::cout << "\n  Demonstrating variadic mixin template classes";
  std::cout << "\n ===============================================\n";

  A a;
  B b;
  C c;
  D<> d;
  d.say();

  D<A> dA(a);
  dA.say();

  D<B, C> dBC(b, c);
  dBC.say();

  // Will fail to compile : incomplete argument list
  // D<B, C> dBC(b);

  std::cout << "\n\n";
  return 0;
}

