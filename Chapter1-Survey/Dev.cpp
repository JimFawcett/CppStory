// Soldier.cpp

#include "Dev.h"
#include "Person.h"
#include <iostream>

namespace Elementary {
  // using DevStats = std::tuple<Stats, Education, Office, Projects>;

  Dev::Dev(const Dev::DevStats& dstats) : Person(std::get<0>(dstats)) { }

  Dev::Projects Dev::projects() const {
    return std::get<3>(devStats_);
  }
  void Dev::projects(const Projects& prjs) {
    std::get<3>(devStats_) = prjs;
  }
  Dev::Education Dev::education() const {
    return std::get<1>(devStats_);
  }
  Dev::Office Dev::office() const {
    return std::get<2>(devStats_);
  }

  void Dev::devStats(const Dev::DevStats& dstats) {
    devStats_ = dstats;
  }
  Dev::DevStats Dev::devStats() const {
    return devStats_;
  }
  void Dev::meeting() {
    std::cout << "\n  listening to team-lead lay out plans";
    std::cout << "\n  occasionally asking questions";
  }
  void Dev::work() {
    std::cout << "\n  writing a lot of great code, and some not so great code";
    std::cout << "\n  drinking lots of coffee";
    std::cout << "\n  brainstorming with my friend at the next desk";
  }

  //-------------------------------------------------
  // From Person
  //-------------------------------------------------
  //virtual Stats stats() const = 0;
  //virtual void stats(const Stats& sts) = 0;
  //virtual Name name() const = 0;
  //virtual Age age() const = 0;
  //virtual void age(const Age& ag) = 0;

  inline std::unique_ptr<IDev> createDev(const Dev::DevStats& dstats) {
    return std::make_unique<IDev>(new Dev(dstats));
  }
};

