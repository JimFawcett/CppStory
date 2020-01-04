///////////////////////////////////////////////////////////
// TmpTemplateSpecialization.cpp

#include "TmpTemplateSpecialization.h"
#include <string>
#include "../Display/Display.h"

using namespace Chap7;

int main() {

  displayTitle("Demonstrate Logger Specialization --- again and again");

  displayDemo("--- Generic Logger ---\n");
  Logger<std::string> log(&std::cout);
  log.write("first log item");
  log.write("second log item");

  displayDemo(
    "\n  --- Logger specialization for formatted logs ---\n"
  );
  Logger<std::string, Formatter> flog(&std::cout);
  flog.write("first formatted log item");
  flog.write("second formatted log item");

  displayDemo(
    "\n  --- Logger specialization for timed logs ---\n"
  );
  Logger<std::string, FNull, Timer> tlog(&std::cout);
  tlog.start();
  tlog.write("first timed log item");
  tlog.write("second timed log item");
  tlog.write("third timed log item");

  std::cout << "\n\n";
}