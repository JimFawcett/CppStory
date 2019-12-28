#pragma once
/////////////////////////////////////////////////////////////////////
// TeamLead.h - defines attributes for Team Leaders                //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "Dev.h"
#include <iostream>

namespace Chap4 {

  class TeamLead : public Dev {
  public:
    TeamLead(IPerson::Stats stats);
    virtual void doWork();
    virtual void attendMeeting();
  private:
    //IPerson* pPer_;
  };
}
