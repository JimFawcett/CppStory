#pragma once
// PersonDisplay.h

#include "Person.h"

namespace Elementary {

  template<typename P>
  void displayPerson(const P& person)
  {
    if constexpr (isElementaryIPerson<P>::value) {
      std::cout << "\n  " << person.name() << ", " << person.age() << ", " << person.occupation();
    }
    else if constexpr (isElementaryPerson<P>::value) {
      std::cout << "\n  " << person.name() << ", " << person.age() << ", " << person.occupation();
      //std::cout << "\n  " << person.name() << ", " << std::get<2>(person.stats()) << ", "
      //  << std::get<1>(person.stats()) << ", with hobby " << std::get<3>(person.stats());
    }
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
}