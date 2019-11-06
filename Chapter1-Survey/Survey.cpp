// Survey.cpp

#include <string>
#include <iostream>
#include <tuple>
#include <initializer_list>
#include <any>

namespace Elementary {

  class Person {
  public:
    using Name = std::string;
    using Occupation = std::string;
    using Age = int;
    using Stats = std::tuple<Name, Occupation, Age>;

    Person(const Stats& sts);
    Stats stats() const;
    void stats(const Stats& sts);
    bool isValid();
    Name name() const;
    Occupation occupation() const;
    void occupation(const Occupation& occup);
    Age age() const;
    void age(const Age& ag);

  private:
    Stats personStats;
  };

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

  bool Person::isValid() {
    return name() != "" && age() >= 0;
  }
}

namespace Intermediate {

  class Person {
  public:

    using Name = std::string;
    using Occupation = std::string;
    using Age = int;
    using Hobbies = std::string;
    using Stats = std::tuple<Name, Occupation, Age, Hobbies>;

    Person() {};
    Person(const Stats& sts);
    static Person createPerson(const Stats& sts);
    Stats stats() const;
    void stats(const Stats& sts);
    bool isValid();
    Name name() const;
    Occupation& occupation();
    Age& age();
    Hobbies& hobby();

  private:
    Stats personStats;
  };

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

  bool Person::isValid() {
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

/* defining isElemntaryPerson type trait */

template<typename T>
struct isElementaryPerson {
  static const bool value = false;
};

template<>
struct isElementaryPerson<Elementary::Person> {
  static const bool value = true;
};

/* defining isIntermediatePerson type trait */

template<typename T>
struct isIntermediatePerson {
  static const bool value = false;
};

template<>
struct isIntermediatePerson<Intermediate::Person> {
  static const bool value = true;
};

/* generic displayPerson function needs type traits */

template<typename P>
void displayPerson(const P& person)
{
  if constexpr (isElementaryPerson<P>::value) {
    std::cout << "\n  " << person.name() << ", " << person.age() << ", " << person.occupation();
  }
  else if constexpr (isIntermediatePerson<P>::value) {
    std::cout << "\n  " << person.name() << ", " << std::get<2>(person.stats()) << ", " 
              << std::get<1>(person.stats()) << ", with hobby " << std::get<3>(person.stats());
  }
}

/* generic displayInvalid does not need type traits */

template<typename P>
void displayInvalid(const P& person) {
  std::cout << "\n  " << person.name() << " has invalid data";
}

template<typename P>
void checkedDisplay(P person) {
  displayPerson(person);
  if(!person.isValid())
    displayInvalid(person);
}

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