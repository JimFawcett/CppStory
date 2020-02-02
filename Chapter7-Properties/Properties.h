#pragma once
// Properties.h

#include "../Chapter8-Display/Chap8Display.h"

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
    return Property< T>::t_.size();
  }
  typename T::value_type back() {
    return Property< T>::t_.back();
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

