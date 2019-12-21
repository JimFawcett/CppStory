/////////////////////////////////////////////////////////////////////
// Person.cpp - defines inner person attributes                    //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "IPerson.h"
#include <tuple>
#include <string>
#include <iostream>
#include "Person.h"

namespace Chap4 {

  Person::Person() {}

  Person::Person(const Stats& sts) {
    personStats = sts;
  }

  Person::~Person() {
    //std::cout << "\n  destroying Person instance \"" << name() << "\"";
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

  std::unique_ptr<IPerson> createPerson(const IPerson::Stats& stats) {
    return std::move(std::make_unique<Person>(*new Person(stats)));
  }

  template<typename P>
  void displayPerson(const P& person)
  {
    std::cout << "\n  " << person.name() << ", " << person.age() << ", " << person.occupation();
  }

  template<typename P>
  void displayInvalid(const P& person) {
    std::cout << "\n  " << person.name() << " has invalid data";
  }

  template<typename P>
  void checkedDisplay(const P& person) {
    displayPerson(person);
    if (!person.isValid())
      displayInvalid(person);
  }
}

#ifdef TEST_PERSON

int main() {

  using namespace Chap4;
  //Person Jack({ "Jack", "Unemployed", 35 });
  std::unique_ptr<IPerson> pJack = createPerson({ "Jack", "Unemployed", 35 });
  checkedDisplay(*pJack);
}

#endif
