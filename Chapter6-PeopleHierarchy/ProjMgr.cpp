/////////////////////////////////////////////////////////////////////
// ProjMgr.cpp - defines attributes for Project Managers           //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "ProjMgr.h"

namespace Chap4 {

  ProjMgr::ProjMgr(IPerson::Stats stats) : SW_Eng(stats) {
  }

  void ProjMgr::doWork() {
    std::cout << "\n  " << nameAndTitle() << ", starting work";
    getCoffee();
    checkEmail();
    reviewTeamActivities();
    performanceAppraisals();
    std::cout << std::endl;
  }

  void ProjMgr::attendMeeting() {

    std::cout << "\n  " << nameAndTitle() << ", attending meeting";
    introductions(pPer_->name());
    presentStatus("My teams have completed 85% of their assigned work for this sprint");
    std::cout << "\n  Take customer golfing - make sure he wins";
    std::cout << std::endl;
  }
}

#ifdef TEST_PROJMGR

using namespace Chap4;

int main() {
  ProjMgr projMgr({ "Deprin", "Project Manager", 28 });
  projMgr.doWork();
  projMgr.attendMeeting();
}

#endif