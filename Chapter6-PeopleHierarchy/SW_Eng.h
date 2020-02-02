#pragma once
/////////////////////////////////////////////////////////////////////
// SW_Eng.h - defines attributes for all SW Eng's                  //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "Person.h"
#include "ISW_Eng.h"
#include <string>
#include <memory>

namespace Chap4 {

  class SW_Eng : public ISW_Eng, public Person {
  public:
    SW_Eng() {}
    SW_Eng(IPerson::Stats stats);
    virtual ~SW_Eng() {}
    virtual void doWork() = 0;
    virtual void attendMeeting() = 0;
    virtual IPerson* person();
    std::string nameAndTitle();
  protected:
    void getCoffee();
    void checkEmail();
    void developSoftware();
    void reviewTeamActivities();
    void performanceAppraisals();
    void introductions(const std::string& name);
    void presentStatus(const std::string& progress);
    void assignActionItems();
    IPerson* pPer_ = nullptr;
  };
}