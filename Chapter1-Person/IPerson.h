#pragma once
// IPerson.h

#include <memory>
#include <string>

namespace Chap1 {

  struct IPerson {
    using Name = std::string;
    using Occupation = std::string;
    using Age = int;
    using Stats = std::tuple<Name, Occupation, Age>;

    virtual ~IPerson() {}
    virtual Stats stats() const = 0;
    virtual void stats(const Stats& sts) = 0;
    virtual Name name() const = 0;
    virtual Occupation occupation() const = 0;
    virtual void occupation(const Occupation& occup) = 0;
    virtual Age age() const = 0;
    virtual void age(const Age& ag) = 0;
    virtual bool isValid() const = 0;
  };

  template<typename P>
  void displayPerson(const P& person)
  {
    std::cout << "\n  " << person.name() << ", " << person.age() << ", " << person.occupation();
  }

  /* generic displayInvalid does not need type traits */

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

  std::unique_ptr<IPerson> createPerson(const IPerson::Stats& sts);
}
