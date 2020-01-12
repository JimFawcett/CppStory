/////////////////////////////////////////////////////////////////////
// VariadicFunctionTemplates.cpp - function displays its arguments //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#ifdef TEST_VARIADICFUNCTIONS_H

#include "Chap7VariadicFunctions.h"
#include "../Display/Display.h"

int main()
{
  std::cout <<
    "\n  Demonstrate Variatic Functions";
  std::cout <<
    "\n ================================\n";

  displayDemo("-- function with 5 args --\n");
  f(
    1, 3.5, 'z',
    "a literal string",
    std::string("a std::string")
  );
  putline();
  displayDemo("-- function with 2 args --\n");
  f('q', "only two args");

  std::cout << "\n\n";
  return 0;
}
#endif
