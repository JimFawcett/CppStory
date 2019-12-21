/////////////////////////////////////////////////////////////////////
// SW_Eng.cpp - defines attributes for all SW Eng's                //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "SW_Eng.h"
#include "Person.h"
#include <iostream>
#include <string>

namespace Chap4 {

  /*--- initialize inner person ---*/

  SW_Eng::SW_Eng(IPerson::Stats stats) {
    Person::stats(stats);
    pPer_ = person();
  }

  /*--- return inner person ---*/

  IPerson* SW_Eng::person() {
    return dynamic_cast<IPerson*>(this);
  }

  std::string SW_Eng::nameAndTitle() {
    return pPer_->name() + ", " + pPer_->occupation();
  }

  void SW_Eng::getCoffee() {
    std::cout << "\n    go to cafetria for coffee, chat with friends";
  }

  void SW_Eng::checkEmail() {
    std::cout << "\n    open mail server and slog through messages";
  }

  void SW_Eng::developSoftware() {
    std::cout << "\n    pull current work from repository";
    std::cout << "\n    chase bugs";
    std::cout << "\n    design new module";
    std::cout << "\n    start module implementation";
    std::cout << "\n    push current work to repository";
  }

  void SW_Eng::reviewTeamActivities() {
    std::cout << "\n    review current work status";
    std::cout << "\n    review each individual's accomplishments";
  }

  void SW_Eng::performanceAppraisals() {
    std::cout << "\n    summarize and record individual accomplishments";
    std::cout << "\n    summarize areas needing improvement";
    std::cout << "\n    summarize contributions to the team";
  }

  void SW_Eng::introductions(const std::string& name) {
    std::cout << "\n    Hi everyone, my name is " << name << " and I'm pleased to see you all";
  }
  void SW_Eng::presentStatus(const std::string& progress) {
    std::cout << "\n    I'm happy to report that " << progress;
  }
  void SW_Eng::assignActionItems() {
    std::cout << "\n    I will post action items for each of you before the end of the day";
  }

}