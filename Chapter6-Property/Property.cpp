/////////////////////////////////////////////////////////////////////
// Property.cpp - Useful C++ Properties class                      //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "Property.h"

#include <iostream>
#include <vector>

template<typename P>
void show(P& prop) {
  std::cout << "\n  ";
  for (auto item : prop) {
    std::cout << item << " ";
  }
}

class Widget {
public:
  void say() {
    std::cout << "\n  Widget instance here";
  }
};

using namespace Chap6;

/*-----------------------------------------------------------------
  Property specialization for a custom Widget type
  - Use this as an example to provide Properties for other types.
-----------------------------------------------------------------*/
template< template<typename> typename Null>
class Property<Widget, Null> : public BaseProperty<Widget,Null> {
public:
  Property() : BaseProperty<Widget,Null>{ Widget() } {}
  Property(const Widget& t) : BaseProperty<Widget, Null>{ Widget() } {}
  Property<Widget, Null>& operator=(const Widget& t) {
    BaseProperty<Widget, Null>::c_.set(t);
    return *this;
  }
  void say() { Property<Widget,Null>::t_.say(); }
};

/*-----------------------------------------------------------------
  Property Demonstration
-----------------------------------------------------------------*/

int main() {

  displayTitle("Demonstrating template class specialization");

  displayDemo("\n  -- Testing base classes --");
  BaseProperty<int> iBProp(3);
  std::cout << "\n  " << iBProp();

  NumericOps<int> no(5);
  std::cout << "\n  " << no();

  displayDemo("\n  -- Property<std::vector<int>> --");
  std::vector<int> tv{ 1,2,3 };
  Property<std::vector<int>> viProperty(tv);
  show(viProperty);
  viProperty.pop_back();
  viProperty.push_back(15);
  Property<std::vector<int>>::iterator iterp = viProperty.begin();
  viProperty.insert(iterp + 1, -33);
  show(viProperty);

  displayDemo("\n  -- Property<Widget> --");

  Property<Widget,Null> wwProp;
  wwProp().say();
  wwProp.say();

  displayDemo("\n  -- class X properties --");

  /*-- defining class using properties --*/

  class X {
  public:
    X() {}
    Property<int> iProp;
    Property<double> dProp;
    Property<std::vector<int>> viProp;
    Property<Widget> wProp;
  };

  X x;
  x.iProp(1);
  std::cout << "\n  x.iProp(1) = " << x.iProp();
  x.iProp += 3;
  std::cout << "\n  x.iProp += 3 => x.iProp = " << x.iProp();
  x.iProp = x.iProp + 2;
  std::cout << "\n  x.iProp + 2 => x.iProp = " << x.iProp();
  //x.iProp(-2);
  x.iProp = -2;
  std::cout << "\n  x.iProp = -2 => x.iProp = " << x.iProp();
  std::cout << "\n  x.wProp.say() => "; x.wProp.say();

  displayDemo("\n  -- Property<double> --");
  x.dProp(3.14159);
  std::cout << "\n  x.dProp(3.14159) = " << x.dProp();
  x.dProp += 1.0;
  std::cout << "\n  x.dProp += 1.0 => " << x.dProp();

  displayDemo("\n  -- methods of Property<std::vector<int>> --");
  x.viProp.push_back(1);
  x.viProp.push_back(2);
  x.viProp.push_back(3);

  std::cout << "\n  contents of x.vProp are:";
  show(x.viProp);

  x.viProp.pop_back();
  std::cout << "\n  after pop_back, contents of x.vProp are:";
  show(x.viProp);
  x.viProp.insert(x.viProp.begin() + 1, -4);
  std::cout << "\n  after inserting -4 in the second position:";
  show(x.viProp);
  x.viProp.erase(x.viProp.begin() + x.viProp.size() - 1);
  std::cout << "\n  after erasing last element:";
  show(x.viProp);

  std::cout << "\n\n";
}
