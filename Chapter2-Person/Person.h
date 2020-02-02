#pragma once
///////////////////////////////////////////////////////////////////////////
// Person.h - Demonstration of basic class structure and operation       //
//                                                                       //
// Jim Fawcett, Emeritus Teaching Professor, EECS Syracuse University    //
///////////////////////////////////////////////////////////////////////////
/*
*  Basic example of class for CppStory Chapter1 - Survey
*
*  Required Files:
*  ---------------
*  Person.h, Person.cpp, Survey
*
*  Maintenance History:
*  --------------------
*  ver 1 : 06 Nov 2019
*  - first release
*/

#include <string>
#include <tuple>
#include "IPerson.h"

namespace Chap1 {

  class Person : public IPerson {
  public:
    Person();
    Person(const Stats& sts);
    ~Person();
    virtual Stats stats() const override;
    virtual void stats(const Stats& sts) override;
    virtual bool isValid() const override;
    virtual Name name() const override;
    virtual Occupation occupation() const override;
    virtual void occupation(const Occupation& occup) override;
    virtual Age age() const override;
    virtual void age(const Age& ag) override;

  protected:
    Stats personStats;
  };
}


