///////////////////////////////////////////////////////////////////////////
// Person.cpp - Demonstration of basic class structure and operation     //
//                                                                       //
// Jim Fawcett, Emeritus Teaching Professor, EECS Syracuse University    //
///////////////////////////////////////////////////////////////////////////

#include "Person.h"

namespace Elementary {

  Person::Person(const Stats& sts) {
    personStats = sts;
  }

  Person::Stats Person::stats() const {
    return personStats;
  }

  void Person::stats(const Stats& sts) {
    personStats = sts;
  }

  Person::Name Person::name() const {
    return std::get<0>(personStats);
  }

  Person::Occupation Person::occupation() const {
    return std::get<1>(personStats);
  }

  void Person::occupation(const Occupation& occup) {
    std::get<1>(personStats) = occup;
  }

  Person::Age Person::age() const {
    return std::get<2>(personStats);
  }

  void Person::age(const Age& ag) {
    std::get<2>(personStats) = ag;
  }

  bool Person::isValid() const {
    return name() != "" && age() >= 0;
  }
}

namespace Intermediate {

  Person::Person(const Stats& sts) {
    personStats = sts;
  }

  Person::Name Person::name() const {
    return std::get<0>(personStats);
  }

  Person::Occupation& Person::occupation() {
    return std::get<1>(personStats);
  }

  Person::Age& Person::age() {
    return std::get<2>(personStats);
  }

  Person::Hobbies& Person::hobby()
  {
    return std::get<3>(personStats);
  }

  Person::Stats Person::stats() const {
    return personStats;
  }

  void Person::stats(const Stats& sts) {
    personStats = sts;
  }

  bool Person::isValid() const {
    auto [name, occup, age, hobby] = personStats;
    if (name == "" || age < 0)
      return false;
    return true;
  }

  Person Person::createPerson(const Stats& sts) {
    Person person(sts);
    if (person.occupation() == "")
      person.occupation() = "is unemployed";
    if (person.hobby() == "")
      person.hobby() = "- dull person, no hobbies";
    return person;
  }
}
