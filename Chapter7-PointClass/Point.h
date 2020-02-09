#pragma once
///////////////////////////////////////////////////////////////
// Point.h - template class version of point                 //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "../Chapter8-Display/Chap8Display.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

template<typename T>
class Point {
public:
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  Point(size_t N, const std::string& name = "none");
  Point(std::initializer_list<T> il);
  void name(const std::string& name);
  std::string name() const;
  T& operator[](size_t i);
  T operator[](size_t i) const;
  size_t size() const;
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
private:
  std::string name_ = "unspecified";
  std::vector<T> coordinates_;
};

template<typename T>
Point<T>::Point(size_t N, const std::string& name) : name_(name)
{
  coordinates_.reserve(N);
}

template<typename T>
Point<T>::Point(std::initializer_list<T> li) : name_("none") {
  for (auto item : li)
    coordinates_.push_back(item);
}

template<typename T>
std::string Point<T>::name() const { return name_; }

template<typename T>
void Point<T>::name(const std::string& name) { name_ = name; }

template<typename T>
T& Point<T>::operator[](size_t i) {
  if (i < 0 && coordinates_.size() <= i)
    throw(std::exception());
  return coordinates_[i];
}

template<typename T>
T Point<T>::operator[](size_t i) const {
  if (i < 0 && coordinates_.size() <= i)
    throw(std::exception());
  return coordinates_[i];
}

template<typename T>
size_t Point<T>::size() const {
  return coordinates_.size();
}

template<typename T>
typename Point<T>::iterator Point<T>::begin() {
  return coordinates_.begin();
}

template<typename T>
typename Point<T>::iterator Point<T>::end() {
  return coordinates_.end();
}

template<typename T>
typename Point<T>::const_iterator Point<T>::begin() const {
  return coordinates_.cbegin();
}

template<typename T>
typename Point<T>::const_iterator Point<T>::end() const {
  return coordinates_.cend();
}

template<typename T>
void showPoint(const Point<T>& pt) {
  std::cout << "\n  " << pt.name() << " : { ";
  for (auto item : pt)
    std::cout << item << " ";
  std::cout << " }";
}

