#pragma once
/////////////////////////////////////////////////////////////////////
// Overriding.h - Demonstrate overriding virtual functions         //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>

/*--- abstract base class ---*/

class SWDev {
public:
  using WorkItems = std::vector<std::string>;

  SWDev(const std::string& name) : name_(name) {}
  virtual ~SWDev() {}
  virtual void doWork() = 0;
  void getCoffee();
  void name(const std::string& nm);
  std::string name();
protected:
  std::string name_ = "anonymous";
  static WorkItems workItem;
};

/*--- shared data ---*/

inline SWDev::WorkItems SWDev::workItem = {
  "process email",
  "pull requests for today's work",
  "work off bugs",
  "add new features",
  "write up developer evaluations",
  "write up project stories",
  "schedule agile meeting",
  "discuss requirements with customer",
  "go golfing with customer"
};

inline auto show = [](const std::string& task) {
  std::cout << "\n  " << task;
};

/*--- non-virtual functions, don't override ---*/

inline void SWDev::name(const std::string& name) {
  name_ = name;
}

inline std::string SWDev::name() {
  return name_;
}

inline void SWDev::getCoffee() {
  std::cout << "\n  get coffee from cafeteria, chat";
}

/*--- derived classes override virtual do work ---*/

class Dev : public SWDev {
public:
  Dev(const std::string& name) : SWDev(name) {}
  virtual void doWork() override {
    show("\n  Dev: " + name());
    getCoffee();
    show(workItem[0]);
    show(workItem[1]);
    show(workItem[2]);
    show(workItem[3]);
  }
};

class TeamLead : public SWDev {
public:
  TeamLead(const std::string& name) : SWDev(name) {}
  virtual void doWork() override {
    show("\n  TeamLead: " + name());
    getCoffee();
    show(workItem[0]);
    show(workItem[5]);
    show(workItem[6]);
    show(workItem[1]);
    show(workItem[2]);
    show(workItem[3]);
  }
};

class ProjMgr : public SWDev {
public:
  ProjMgr(const std::string& name) : SWDev(name) {}
  virtual void doWork() override {
    show("\n  Project Mgr: " + name());
    getCoffee();
    show(workItem[0]);
    show(workItem[4]);
    show(workItem[7]);
    show(workItem[8]);
  }
};

