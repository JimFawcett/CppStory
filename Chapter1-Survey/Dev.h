#pragma once
// Dev.h

#include "IDev.h"
#include "Person.h"

namespace Elementary {

  class Dev : public IDev, public Person {
  public:
    //using Projects = std::vector<std::string>;
    //using Education = std::string;
    //using Office = std::string;
    //using DevStats = std::tuple<Stats, Education, Office, Projects>;

    Dev(const DevStats& dstats);
    virtual Projects projects() const override;
    virtual void projects(const Projects& prjs);
    virtual Education education() const override;
    virtual Office office() const override;
    virtual void devStats(const DevStats& sstats);
    virtual DevStats devStats() const override;
    virtual void meeting();
    virtual void work();

    //-------------------------------------------------
    // From Person
    //-------------------------------------------------
    //virtual Stats stats() const = 0;
    //virtual void stats(const Stats& sts) = 0;
    //virtual Name name() const = 0;
    //virtual Age age() const = 0;
    //virtual void age(const Age& ag) = 0;

  private:
    DevStats devStats_;
  };

  inline std::unique_ptr<IDev> createDev();
}