#pragma once
// ISoldier.h

#include <string>
#include <vector>
#include <tuple>
#include <memory>
#include "IPerson.h"

namespace Elementary {

  struct IDev : IPerson {

    using Projects = std::vector<std::string>;
    using Education = std::string;
    using Office = std::string;
    using DevStats = std::tuple<Stats, Education, Office, Projects>;

    virtual Projects projects() const = 0;
    virtual void projects(const Projects& prjs) = 0;
    virtual Education education() const = 0;
    virtual Office office() const = 0;
    virtual void devStats(const DevStats& dstats) = 0;
    virtual DevStats devStats() const = 0;
    virtual void meeting() = 0;
    virtual void work() = 0;
    
    //-------------------------------------------------
    // From Person
    //-------------------------------------------------
    //virtual Stats stats() const = 0;
    //virtual void stats(const Stats& sts) = 0;
    //virtual Name name() const = 0;
    //virtual Age age() const = 0;
    //virtual void age(const Age& ag) = 0;
  };

  inline std::unique_ptr<IDev> createDev();
}