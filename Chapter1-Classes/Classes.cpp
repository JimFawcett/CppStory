///////////////////////////////////////////////////////////////
// Classes.cpp - implements simple point                     //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "../Chapter8-Display/Chap8Display.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

class Point {
public:
  using iterator = std::vector<double>::iterator;
  using const_iterator = std::vector<double>::const_iterator;

  Point(const std::string& name = "none");
  Point(std::initializer_list<double> il);
  void name(const std::string& name);
  std::string name() const;
  double& operator[](size_t i);
  double operator[](size_t i) const;
  size_t size() const;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
private:
  std::string name_ = "unspecified";
  std::vector<double> coordinates_;
};

Point::Point(const std::string& name) : name_(name) {}

Point::Point(std::initializer_list<double> li) {
  for (auto item : li)
    coordinates_.push_back(item);
}

std::string Point::name() const { return name_; }

void Point::name(const std::string& name) { name_ = name; }

double& Point::operator[](size_t i) {
  if (i < 0 && coordinates_.size() <= i)
    throw(std::exception());
  return coordinates_[i];
}

double Point::operator[](size_t i) const {
  if (i < 0 && coordinates_.size() <= i)
    throw(std::exception());
  return coordinates_[i];
}

size_t Point::size() const {
  return coordinates_.size();
}

Point::iterator Point::begin() {
  return coordinates_.begin();
}

Point::iterator Point::end() {
  return coordinates_.end();
}

Point::const_iterator Point::begin() const {
  return coordinates_.cbegin();
}

Point::const_iterator Point::end() const {
  return coordinates_.cend();
}

void showPoint(const Point& pt) {
  std::cout << "\n  " << pt.name() << " : { ";
  for (auto item : pt)
    std::cout << item << " ";
  std::cout << " }";
}

int main() {

  displayTitle("Point Class Demo");

  Point pt1{ 0.5, 0.0, -0.5 };
  pt1.name("pt1");
  showPoint(pt1);
  putline();

  Point pt2{ 0.5, 1.0, 1.5 };
  pt2.name("pt2");
  showPoint(pt2);
  putline();

  Point pt3{ 0.0, 0.5, 1.5 };
  pt3.name("pt3");
  showPoint(pt3);
  putline();

  Point pt4{ pt3 };
  pt4.name("pt4 is copy of pt3");
  showPoint(pt4);

  Point pt5("pt5");
  pt5 = pt3;
  pt5.name("pt5 assigned from pt3");
  showPoint(pt5);
  putline();
  std::cout << "\n  So Point is a value type";
  putline(2);
}