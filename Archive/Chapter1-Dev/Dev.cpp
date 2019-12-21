// Dev.cpp

#include "Dev.h"
#include "../Chapter1-Person/PersonDisplay.h"
//#include "../Chapter1-Person/Person.h"
#include <iostream>

namespace Elementary {
  // using DevStats = std::tuple<Stats, Education, Office, Projects>;
  //Dev(const DevStats& dstats);
  //virtual Projects projects() const override;
  //virtual void projects(const Projects& prjs);
  //virtual Education education() const override;
  //virtual Office office() const override;
  //virtual void devStats(const DevStats& sstats);
  //virtual DevStats devStats() const override;
  //virtual void meeting();
  //virtual void work();

  Dev::Dev() {}

  Dev::Dev(const Dev::DevStats& dstats) : Person(std::get<0>(dstats)), devStats_(dstats) { }

  Dev::~Dev() {
    std::cout << "\n  destroying instance of Dev \"" << Person::name() << "\"";
  }

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
  // From IPerson
  //-------------------------------------------------
  //virtual Stats stats() const = 0;
  //virtual void stats(const Stats& sts) = 0;
  //virtual Name name() const = 0;
  //virtual Age age() const = 0;
  //virtual void age(const Age& ag) = 0;
  // From Person
  //virtual Stats stats() const override;
  //virtual void stats(const Stats& sts) override;
  //virtual bool isValid() const override;
  //virtual Name name() const override;
  //virtual Occupation occupation() const override;
  //virtual void occupation(const Occupation& occup) override;
  //virtual Age age() const override;
  //virtual void age(const Age& ag) override;

  //std::unique_ptr<IDev> createDev(const Dev::DevStats& dstats) {
  //  return std::make_unique<IDev>(*new Dev(dstats));
  //}
}

#ifdef TEST_DEV

int main() {

  using namespace Elementary;
  Person Jack({ "Jack", "Retired early", 35 });
  checkedDisplay(Jack);
  Jack.age(36);
  Jack.occupation("ran out of money - pumping gas");
  checkedDisplay(Jack);

  Dev Joe;
  IDev::Projects janeProjs{ "Testla navigation view", "Python side project" };
  Dev Jane({ { "Jane", "UI developer", 28 }, "MSCE Syracuse Univ", "B1-14", janeProjs });
}

#endif
