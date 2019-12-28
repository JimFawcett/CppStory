// TemplateSpecialization

#include "../Display/Display.h"

enum class PropertyType { Numeric, SeqContr, AssocContr, Nil };

template<typename T, PropertyType PT = PropertyType::Nil >
class Property {
public:
  Property() : t_{ T() } {}

  Property(const T& t) : t_{ t } {}

  void operator()(const T& t) {
    t_ = t;
  }
  T operator()() {
    return t_;
  }
protected:
  T t_;
};

template<typename T>
class Property<T, PropertyType::Numeric> : public Property<T> {
public:
  Property() {}

  Property(const T& t) : Property<T>{ t } {}

  void operator+=(T t) {
    Property<T>::t_ += t;
  }
  T operator+(T t) {
    return Property<T>::t_ + t;
  }
  void operator-=(const T& t) {
    Property<T>::t_ -= t;
  }
  T operator-(const T& t) {
    return Property<T>::t_ - t;
  }
  void operator*=(const T& t) {
    Property<T>::t_ *= t;
  }
  T operator*(const T& t) {
    return Property<T>::t_ * t;
  }
  void operator/=(const T& t) {
    Property<T>::t_ /= t;
  }
  T operator/(const T& t) {
    return Property<T>::t_ / t;
  }
};

template<typename T>
class Property<T, PropertyType::SeqContr> : public Property<T> {
public:
  using iterator = typename T::iterator;

  Property() {}

  Property(const T& t) : Property<T>{ t } {}

  size_t size() {
    return Property < T>::t_.size();
  }
  typename T::value_type back() {
    return Property < T>::t_.back();
  }
  void push_back(const typename T::value_type& v) {
    Property<T>::t_.push_back(v);
  }
  void pop_back() {
    Property<T>::t_.pop_back();
  }
  typename T::value_type front() {
    return Property < T>::t_.back();
  }
  void push_front(const typename T::value_type& v) {
    Property<T>::t_.push_front(v);
  }
  void pop_front() {
    Property<T>::t_.pop_front();
  }
  iterator insert(iterator iter, const typename T::value_type& v) {
    return Property<T>::t_.insert(iter, v);
  }
  typename iterator erase(iterator iter) {
    return Property<T>::t_.erase(iter);
  }
  iterator begin() {
    return Property<T>::t_.begin();
  }
  iterator end() {
    return Property<T>::t_.end();
  }
};

#include <iostream>
#include <vector>

template<typename T>
using baseProp = Property<T>;

template<typename T>
using numProp = Property<T, PropertyType::Numeric>;

template<typename T>
using seqProp = Property<T, PropertyType::SeqContr>;

template<typename T>
void show(seqProp<T>& prop) {
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

int main() {

  displayTitle("Demonstrating template class specialization");

  displayDemo("--- basic property of Widget ---");
  baseProp<Widget> wProp;
  wProp().say();
  std::cout << std::endl;

  /*-- defining class using properties --*/

  class X {
  public:
    numProp<int> iProp;
    numProp<double> dProp;
    seqProp<std::vector<int>> viProp;
  };

  displayDemo("-- Property<int, PropertyType::Numeric> --");
  X x;
  x.iProp(1);
  std::cout << "\n  x.iProp(1) = " << x.iProp();
  x.iProp += 3;
  std::cout << "\n  x.iProp += 3 => x.iProp = " << x.iProp();
  x.iProp = -2;
  std::cout << "\n  x.iProp = -2 => x.iProp = " << x.iProp();
  putline();

  displayDemo("-- Property<double, PropertyType::Numeric> --");
  x.dProp(3.14159);
  x.dProp += 1.0;
  x.dProp(3.14159);
  std::cout << "\n  x.dProp(3.14159) = " << x.dProp();
  std::cout << std::endl;

  displayDemo("-- Property<std::vector<int>, PropertyType::SeqContr> --");
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
