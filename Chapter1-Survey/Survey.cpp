///////////////////////////////////////////////////////////////////////////
// Survey.cpp - Demonstrates Elementary::Person and Intermediate::Person //
//                                                                       //
// Jim Fawcett, Emeritus Teaching Professor, EECS Syracuse University    //
///////////////////////////////////////////////////////////////////////////
/*
*  Basic example of class for CppStory Chapter1 - Survey
*
*  Required Files:
*  ---------------
*  Person.h, Person.cpp, Survey.cpp
*
*  Maintenance History:
*  --------------------
*  ver 1 : 06 Nov 2019
*  - first release
*/

#include <string>
#include <iostream>
#include <tuple>
#include <initializer_list>
#include <any>
#include "Person.h"

int main() {

  {
    std::cout << "\n  Demonstrate Elementary Person Class";
    std::cout << "\n -------------------------------------";

    using namespace Elementary;
    Person Jack({ "Jack", "has retired early", 35 });
    checkedDisplay(Jack);
    Jack.age(36);
    Jack.occupation("ran out of money - pumping gas");
    checkedDisplay(Jack);
    std::cout << std::endl;
  }

  using namespace Intermediate;
  {
    std::cout << "\n  Demonstrate Intermediate Person Class";
    std::cout << "\n ---------------------------------------";

    Person John = Person::createPerson({ "John", "is a Dev", 42, "" });
    checkedDisplay(John);
    Person Mary = Person::createPerson({ "Mary", "", 28, "skydiving" });
    checkedDisplay(Mary);
    Person Joey = Person::createPerson({ "Joey", "", -2, "watching TV" });
    checkedDisplay(Joey);
    std::cout << std::endl;
  }
  std::cout << std::endl;
}