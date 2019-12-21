///////////////////////////////////////////////////////////////////////////
// Person.cpp - Demonstration of basic class structure and operation     //
//                                                                       //
// Jim Fawcett, Emeritus Teaching Professor, EECS Syracuse University    //
///////////////////////////////////////////////////////////////////////////

#include "Person.h"
#include <iostream>

namespace Chap1 {

  Person::Person() {}

  Person::Person(const Stats& sts) {
    personStats = sts;
  }

  Person::~Person() {
    std::cout << "\n  destroying Person instance \"" << name() << "\"";
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

//  std::unique_ptr<IPerson> createPerson(const IPerson::Stats& sts);


  std::unique_ptr<IPerson> createPerson(const IPerson::Stats& stats) {
    return std::make_unique<Person>(*new Person(stats));
  }
}

#ifdef TEST_PERSON

int main() {

  using namespace Chap1;
  //Person Jack({ "Jack", "Unemployed", 35 });
  std::unique_ptr<IPerson> pJack = createPerson({ "Jack", "Unemployed", 35 });
  checkedDisplay(*pJack);
}

#endif
