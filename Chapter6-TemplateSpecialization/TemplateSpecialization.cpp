///////////////////////////////////////////////////////////////
// TemplateSpecialization.cpp - template specialization demo //
//                                                           //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse Univ   //
///////////////////////////////////////////////////////////////


#include "TemplateSpecialization.h"
#include <string>
#include "../Chapter7-Display/Chap7Display.h"
//#include "../Display/Display.h"
#include "Timer.h"

using namespace Chap6;

int main() {
  
  displayTitle("Demonstrate Logger Specialization");

  displayDemo("--- Unadorned Logger ---\n");
  /* using defaults F=FNull, T=TNull */
  Logger<std::string> log(&std::cout);
  log.write("first log item");
  log.write("second log item");

  displayDemo(
    "\n  --- Logger specialization for formatted logs ---\n"
  );
  /* using default T = TNull */
  Logger<std::string, Formatter> flog(&std::cout);
  flog.write("first formatted log item");
  flog.write("second formatted log item");

  displayDemo(
    "\n  --- Logger specialization for timed logs ---\n"
  );
  /* must cite FNull because defaults only at end */
  Logger<std::string, FNull, Timer> tlog(&std::cout);
  tlog.start();
  tlog.write("first timed log item");
  tlog.write("second timed log item");
  tlog.write("third timed log item");

  std::cout << "\n\n";
}