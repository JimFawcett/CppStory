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

namespace Elementary {
  //virtual Stats stats() const = 0;
  //virtual void stats(const Stats& sts) = 0;
  //virtual Name name() const = 0;
  //virtual Occupation occupation() const = 0;
  //virtual void occupation(const Occupation& occup) = 0;
  //virtual Age age() const = 0;
  //virtual void age(const Age& ag) = 0;

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

  template<typename T>
  struct isElementaryPerson {
    static const bool value = false;
  };

  template<>
  struct isElementaryPerson<Elementary::Person> {
    static const bool value = true;
  };

}

//namespace Intermediate {
//
//  class Person {
//  public:
//
//    using Name = std::string;
//    using Occupation = std::string;
//    using Age = int;
//    using Hobbies = std::string;
//    using Stats = std::tuple<Name, Occupation, Age, Hobbies>;
//
//    Person() {};
//    Person(const Stats& sts);
//    static Person createPerson(const Stats& sts);
//    Stats stats() const;
//    void stats(const Stats& sts);
//    bool isValid() const;
//    Name name() const;
//    Occupation& occupation();
//    Age& age();
//    Hobbies& hobby();
//
//  private:
//    Stats personStats;
//  };
//}

///* defining isElemntaryPerson type trait */
//
//template<typename T>
//struct isElementaryIPerson {
//  static const bool value = false;
//};
//
//template<>
//struct isElementaryIPerson<Elementary::IPerson> {
//  static const bool value = true;
//};
//
/* defining isIntermediatePerson type trait */

//template<typename T>
//struct isIntermediatePerson {
//  static const bool value = false;
//};
//
//template<>
//struct isIntermediatePerson<Intermediate::Person> {
//  static const bool value = true;
//};
//
/* generic displayPerson function needs type traits */
#include <iostream>

//template<typename P>
//void displayPerson(const P& person)
//{
//  if constexpr (isElementaryIPerson<P>::value) {
//    std::cout << "\n  " << person.name() << ", " << person.age() << ", " << person.occupation();
//  }
//  //else if constexpr (isIntermediatePerson<P>::value) {
//  //  std::cout << "\n  " << person.name() << ", " << std::get<2>(person.stats()) << ", "
//  //    << std::get<1>(person.stats()) << ", with hobby " << std::get<3>(person.stats());
//  //}
//}
//
///* generic displayInvalid does not need type traits */
//
//template<typename P>
//void displayInvalid(const P& person) {
//  std::cout << "\n  " << person.name() << " has invalid data";
//}
//
//template<typename P>
//void checkedDisplay(const P& person) {
//  displayPerson(person);
//  if (!person.isValid())
//    displayInvalid(person);
//}

