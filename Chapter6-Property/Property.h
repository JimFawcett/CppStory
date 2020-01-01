#pragma once
// Property.h

#include "../Display/Display.h"

class Null {
public:
  virtual ~Null() {}
};

template<typename T>
class BaseProperty {
public:
  BaseProperty() : t_{ T() } {}
  BaseProperty(const T& t) : t_{ t } {
    //std::cout << "\n  in BaseProperty(const T& t) with t = " << t;
  }
  virtual ~BaseProperty() {}
//  using iterator = typename T::iterator;

  void operator()(const T& t) {
    //std::cout << "\n  BaseProperty<T,C>::operator()(const T&t) called";
    t_ = t;
  }
  T operator()() {
    //std::cout << "\n  BaseProperty<T,C>::operator()() called";
    return t_;
  }
protected:
  T t_;
};

template<typename T>
class NumericOps : public virtual BaseProperty<T> {
public:
  NumericOps() {}
  NumericOps(const T& t) : BaseProperty<T>{ t } {
    //std::cout << "\n  in NumericOps(const T& t) with t = " << t;
  }

  void operator+=(T t) {
    BaseProperty<T>::t_ += t;
  }
  T operator+(T t) {
    BaseProperty<T> bp;
    return bp += t;
//    return BaseProperty<T>::t_ + t;
  }
  void operator-=(const T& t) {
    BaseProperty<T>::t_ -= t;
  }
  T operator-(const T& t) {
    BaseProperty<T> bp;
    return bp -= t;
    //return BaseProperty<T>::t_ - t;
  }
  void operator*=(const T& t) {
    BaseProperty<T>::t_ *= t;
  }
  T operator*(const T& t) {
    BaseProperty<T> bp;
    return bp *= t;
    //return BaseProperty<T>::t_ * t;
  }
  void operator/=(const T& t) {
    BaseProperty<T>::t_ /= t;
  }
  T operator/(const T& t) {
    BaseProperty<T> bp;
    return bp / t;
    //return BaseProperty<T>::t_ / t;
  }
};

template<typename T>
class CommonContOps : virtual public BaseProperty<T> {
public:
  using iterator = typename T::iterator;

  CommonContOps() {}
  CommonContOps(const T& t) : BaseProperty<T>{ t } {}

  size_t size() {
    return BaseProperty < T>::t_.size();
  }
  iterator insert(iterator iter, const typename T::value_type& v) {
    return BaseProperty<T>::t_.insert(iter, v);
  }
  typename iterator erase(iterator iter) {
    return BaseProperty<T>::t_.erase(iter);
  }
  iterator begin() {
    return BaseProperty<T>::t_.begin();
  }
  iterator end() {
    return BaseProperty<T>::t_.end();
  }
};

template<typename T>
class SeqContOps : virtual public BaseProperty<T> {
public:

  SeqContOps() {}
  SeqContOps(const T& t) : BaseProperty<T>{ t } {}

  typename T::value_type back() {
    return BaseProperty < T>::t_.back();
  }
  void push_back(const typename T::value_type& v) {
    BaseProperty<T>::t_.push_back(v);
  }
  void pop_back() {
    BaseProperty<T>::t_.pop_back();
  }
  typename T::value_type front() {
    return BaseProperty < T>::t_.back();
  }
  void push_front(const typename T::value_type& v) {
    BaseProperty<T>::t_.push_front(v);
  }
  void pop_front() {
    BaseProperty<T>::t_.pop_front();
  }
};

template<typename T>
class Property : public CommonContOps<T>, public NumericOps<T>, public SeqContOps<T> {
public:
  Property() {}
  Property(const T& t) : BaseProperty<T>{ t } {}
};

template<>
class Property<int> : public NumericOps<int> {
public:
  Property() {}
  Property(const int& t) : BaseProperty<int>{ t } {}
};

template<>
class Property<double> : public NumericOps<double> {
public:
  Property() {}
  Property(const double& t) : BaseProperty<double>{ t } {}
};

//template<typename T, typename C>
//class Property : public BaseProperty<T> {
//public:
//  Property() {
//    //std::cout << "\n  default ctor Property<C,C>";
//  }
//  Property(const C& c) : BaseProperty<C,C>{ c } {
//    //std::cout << "\n  promo ctor Property<C,C>";
//  }
//};