/////////////////////////////////////////////////////////////////////
// VariadicFunctionTemplates.cpp - function displays its arguments //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////


#include "Chap7VariadicFunctions.h"
#include "../Chapter7-Display/Chap7Display.h"
//#include "../Display/Display.h"
#ifdef TEST_VARIADICFUNCTIONS

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
