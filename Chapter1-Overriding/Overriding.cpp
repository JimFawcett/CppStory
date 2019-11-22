/////////////////////////////////////////////////////////////////////
// Overriding.cpp - Demonstrate overriding virtual functions       //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////

#include "Overriding.h"

int main() {

  std::cout << "\n  Demonstrating Overriding";
  std::cout << "\n ==========================\n";

  /* form project team */
  ProjMgr Frank("Frank");

  TeamLead Ashok("Ashok");
  Dev Joe("Joe");
  Dev Charley("Charley");
  Dev Sue("Sue");

  TeamLead Ming("Ming");
  Dev Barbara("Barbara");
  Dev Samir("Samir");

  std::vector<SWDev*> ProjectTeam{
    &Frank,
    &Ashok, &Joe, &Charley, &Sue,
    &Ming, &Barbara, &Samir
  };

  /* get to work */

  show("Monday, starting work");
  for (auto swDev : ProjectTeam) {
    swDev->doWork();
  }
  show("\n  That's all Folks\n\n");
}
