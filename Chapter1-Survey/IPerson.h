#pragma once
// IPerson.h

#include <memory>

namespace Elementary {

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

  /* defining isElemntaryPerson type trait */

  template<typename T>
  struct isElementaryIPerson {
    static const bool value = false;
  };

  template<>
  struct isElementaryIPerson<Elementary::IPerson> {
    static const bool value = true;
  };

  template<typename P>
  void displayPerson(const P& person)
  {
    if constexpr (isElementaryIPerson<P>::value) {
      std::cout << "\n  " << person.name() << ", " << person.age() << ", " << person.occupation();
    }
    //else if constexpr (isIntermediatePerson<P>::value) {
    //  std::cout << "\n  " << person.name() << ", " << std::get<2>(person.stats()) << ", "
    //    << std::get<1>(person.stats()) << ", with hobby " << std::get<3>(person.stats());
    //}
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
