/////////////////////////////////////////////////////////////////////
// Dev.cpp - defines attributes for developer                      //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "Dev.h"

namespace Chap4 {

  Dev::Dev(IPerson::Stats stats) : SW_Eng(stats) {
  }

  void Dev::doWork() {
    std::cout << "\n  " << pPer_->name() << " starting work";
    getCoffee();
    checkEmail();
    developSoftware();
    std::cout << std::endl;
  }

  void Dev::attendMeeting() {

    std::cout << "\n  " << pPer_->name() << " attending meeting";
    introductions(pPer_->name());
    presentStatus("I've completed 90% of my assigned tasks for this sprint");
    std::cout << std::endl;
  }
}

#ifdef TEST_DEV

using namespace Chap4;

int main() {
  Dev dev({ "Jack", "UI developer", 28 });
  dev.doWork();
  dev.attendMeeting();
}

#endif