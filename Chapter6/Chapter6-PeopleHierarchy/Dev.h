#pragma once
/////////////////////////////////////////////////////////////////////
// Dev.h - defines attributes for developer                        //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "SW_Eng.h"
#include <iostream>

namespace Chap4 {

  class Dev : public SW_Eng {
  public:
    Dev(IPerson::Stats stats);
    virtual void doWork();
    virtual void attendMeeting();
  private:
    //IPerson* pPer_;
  };
}
