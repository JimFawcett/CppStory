#pragma once
// Chap7TMP_Application.h

#include <vector>
#include <iostream>

template<typename T>
using Items = std::vector< typename T::value_type>;

template<typename T>
class Query {
public:
  using const_iterator = typename Items<T>::const_iterator;
  using iterator = typename Items<T>::iterator;
  const_iterator begin() const { return items_.cbegin(); }
  const_iterator end() const { return items_.cend(); }
  iterator begin() { return items_.begin(); }
  iterator end() { return items_.end(); }
  Query() {};
  Items<T> operator()();
  template<class R>
  Query<T>& select(R r);
  template<class C>
  Query<T>& sort(C c);
  template<class P>
  Query<T>& where(P p);
  Query<T>& distinct();
  template<class R1, class R2>
  Query<T>& join(R1 r1, R2 r2);
  template<class V>
  bool contains(const V& v) const;
  size_t count();
private:
  Items<T> items_;
};

template<typename T>
template<typename R>
Query<T>& Query<T>::select(R r) {
  items_.clear();
  for (auto item : r) {
    items_.push_back(item);
  }
  return *this;
}

template<typename T>
Items<T> Query<T>::operator()() {
  return items_;
}

template<typename T>
void show(const T& t) {
  std::cout << "\n  ";
  for (auto item : t) {
    std::cout << item << " ";
  }
}