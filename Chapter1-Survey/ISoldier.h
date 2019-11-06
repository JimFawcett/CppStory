#pragma once
// ISoldier.h

#include <string>
#include <vector>
#include <tuple>
#include "IPerson.h"

namespace Elementary {

  struct ISoldier : IPerson {

    using Rank = std::string;
    using SoldierStats = std::tuple<Stats, Rank>;
    using Gear = std::vector<std::string>;

    virtual Rank rank() const = 0;
    virtual void rank(const Rank& rnk) = 0;
    void soldierStats(const SoldierStats& sstats);
    SoldierStats soldierStats();
    virtual void inspection() = 0;
    virtual void salute() = 0;
    virtual Gear& gear() = 0;
    
    //-------------------------------------------------
    // From Person
    //-------------------------------------------------
    //virtual Stats stats() const = 0;
    //virtual void stats(const Stats& sts) = 0;
    //virtual Name name() const = 0;
    //virtual Age age() const = 0;
    //virtual void age(const Age& ag) = 0;
  };
}