#pragma once
/////////////////////////////////////////////////////////////////////
// Person.h - defines inner person attributes                      //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "IPerson.h"

namespace Chap4 {

  class Person : public IPerson {
  public:
    virtual ~Person();
    Person();
    Person(const Stats& sts);
    virtual Stats stats() const;
    virtual void stats(const Stats& sts);
    virtual Name name() const;
    virtual Occupation occupation() const;
    virtual void occupation(const Occupation& occup);
    virtual Age age() const;
    virtual void age(const Age& ag);
    virtual bool isValid() const;
  private:
    Stats personStats;
  };
}
