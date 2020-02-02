#pragma once
/////////////////////////////////////////////////////////////////////
// ProjMgr.h - defines attributes for Project Managers             //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "SW_Eng.h"
#include <iostream>

namespace Chap4 {

  class ProjMgr : public SW_Eng {
  public:
    ProjMgr(IPerson::Stats stats);
    virtual void doWork();
    virtual void attendMeeting();
  private:
    //IPerson* pPer_;
  };
}
