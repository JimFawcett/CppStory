/////////////////////////////////////////////////////////////////////
// TeamLead.cpp - defines attributes for Team Leaders              //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "TeamLead.h"

namespace Chap4 {

  TeamLead::TeamLead(IPerson::Stats stats) : Dev(stats) {
  }

  void TeamLead::doWork() {
    std::cout << "\n  " << nameAndTitle() << ", starting work";
    getCoffee();
    checkEmail();
    reviewTeamActivities();
    developSoftware();
    std::cout << std::endl;
  }

  void TeamLead::attendMeeting() {

    std::cout << "\n  " << nameAndTitle() << ", attending meeting";
    introductions(pPer_->name());
    presentStatus("our team has completed 95% of our assigned stories for this sprint");
    std::cout << std::endl;
  }
}

#ifdef TEST_TEAMLEAD

using namespace Chap4;

int main() {
  TeamLead TeamLead({ "Jill", "Team Lead & backend developer", 32 });
  TeamLead.doWork();
  TeamLead.attendMeeting();
}

#endif