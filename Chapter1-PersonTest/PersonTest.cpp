// PersonTest.cpp

#include "../Chapter1-Person/Person.h"
#include "../Chapter1-Person/PersonDisplay.h"
#include <iostream>

struct Cosmetic { ~Cosmetic() { std::cout << "\n"; } } coz;

int main() {

  std::cout << "\n  Demonstrating Person class";
  std::cout << "\n ============================\n";

  using namespace Elementary;
  Person Curly;
  Curly.stats({ "Curly", "one of three Stooges", 52 });
  checkedDisplay(Curly);

  Person Jack({ "Jack", "Retired early", 35 });
  checkedDisplay(Jack);
  Jack.age(36);
  Jack.occupation("ran out of money - pumping gas");
  checkedDisplay(Jack);

  std::unique_ptr<IPerson> pMary = createPerson({ "Mary", "UI Designer", 28 });
  checkedDisplay(*pMary);
  std::cout << std::endl;
}
