// Soldier.cpp

#include "ISoldier.h"
#include "Person.h"
#include <iostream>

namespace Elementary {

  class Soldier : public ISoldier, public Person {
  public:
    Soldier(const SoldierStats& sstats);
    virtual Rank rank() const;
    virtual void rank(const Rank& rnk);
    void soldierStats(const SoldierStats& sstats);
    SoldierStats soldierStats();
    virtual Gear& gear();
    virtual void inspection() = 0;
    virtual void salute() = 0;

  protected:
    Rank rank_;
    Gear gear_;
  };

  Soldier::Soldier(const SoldierStats& sstats) 
    : Person(std::get<0>(sstats)), rank_(std::get<1>(sstats)) {}

  Soldier::Rank Soldier::rank() const {
    return rank_;
  }

  void Soldier::rank(const Rank& rnk) {
    rank_ = rnk;
  }

  void Soldier::soldierStats(const SoldierStats& sstats) {
    personStats = std::get<0>(sstats);
    rank_ = std::get<1>(sstats);
  }

  Soldier::SoldierStats Soldier::soldierStats() {
    return std::tuple<Stats, Rank>{ personStats, rank_ };
  }

  Soldier::Gear& Soldier::gear() {
    return gear_;
  }

  class Private : public Soldier {
    virtual void inspection() {
      salute();
      for (auto item : gear_)
        std::cout << "\n  present " << item;
    }
    virtual void salute() {
      std::cout << "\n  snappy salute";
    }
  };

  class Sergeant : public Soldier {
    virtual void inspection() {
      salute();
      for (auto item : gear_)
        std::cout << "\n  present " << item;
    }
    virtual void salute() {
      std::cout << "\n  crisp salute";
    }
  };

  class Captain : public Soldier {
    virtual void inspection() {
      salute();
      std::cout << "\n  Soldier, show your gear";
    }
    virtual void salute() {
      std::cout << "\n  casual salute";
    }
  };
}