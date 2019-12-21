#pragma once
/////////////////////////////////////////////////////////////////////
// ISW_Eng.h - defines interface for all SW Eng's                  //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "IPerson.h"

namespace Chap4 {

  struct ISW_Eng {
    virtual ~ISW_Eng() {}
    virtual void doWork() = 0;
    virtual void attendMeeting() = 0;
    virtual IPerson* person() = 0;
  };
}