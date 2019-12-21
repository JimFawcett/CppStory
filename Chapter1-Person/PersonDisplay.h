#pragma once
// PersonDisplay.h

#include "Person.h"

namespace Chap1 {

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
}