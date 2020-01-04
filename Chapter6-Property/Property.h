#pragma once
/////////////////////////////////////////////////////////////////////
// Property.h - Useful C++ Properties class                        //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ    //
/////////////////////////////////////////////////////////////////////

#include "../Display/Display.h"

namespace Chap6 {

  /*----------------------------------------------------------------- 
    class Null is a default facility for managing property values.
    ---------------------------------------------------------------
     Typical use scenarios are:
     - locking to build thread-safe properties
     - property access logging
     - ensure property state has valid values
    ---------------------------------------------------------------
    - It doesn't change any values, but provides a place to do so.
    - To provide that, just make a copy of Null and put management
      processing in the methods set, get, constrain, and validate.
      Use renamed copy for second Property template parameter.
    - set manages values coming into property through ctors and
      copy assignment.
    - get manages values coming out via operator()().
    - constrain is used in Ops classes to manage inserted values.
  -----------------------------------------------------------------*/

  template<typename T>
  class Null {
  public:
    Null() : t_{ T() } {
      set(T());
    }
    Null(T& t) : t_{ t } {
      set(t);
    }
    Null(const Null<T>& null) {
      t_ = null.t_;
    }
    Null<T>& operator=(const Null<T>& null) {
      if (this != &null) {
        t_ = null.t_;
      }
      return *this;
    }
    virtual ~Null() {}
    void set(const T& t) {
      // put processing here for inputs via constructors
      t_ = t;
    }
    T& get() {
      // put processing here for outputs from operator()()
      return t_;
    }
    T& validate(T& t) {
      // put validation logic here
      // - not automatically called, but your code can use
      //   it to check for valid state values.
      return t;
    }
    T& constrain(T& t) {
      // put constraint processing here, used in methods
      // like insert
      return t;
    }
  private:
    T& t_;
  };
  /*-----------------------------------------------------------------
    BaseProperty class provides automatic invocation of Null methods
    for a standard getter, setter interface.
  -----------------------------------------------------------------*/
  template<typename T, template<typename T> typename C = Null>
  class BaseProperty {
  public:
    BaseProperty() : t_{ T() }, c_(t_) {}
    BaseProperty(const T& t) : t_{ t }, c_(t_) {
      c_.set(t);
    }

    // default copy ctor and copy assign are correct

    virtual ~BaseProperty() {}

    BaseProperty<T, C>& operator=(const T& t) {
      c_.set(t);
      return *this;
    }

    void operator()(const T& t) {
      c_.set(t);
      //t_ = t;
    }
    T operator()() {
      return c_.get();
      //return t_;
    }
  protected:
    T t_;
    C<T> c_;
  };

  /*-----------------------------------------------------------------
    NumericOps provides arithmetic methods for fundamental types
  -----------------------------------------------------------------*/
  template<typename T, template<typename T> typename C = Null>
  class NumericOps : public virtual BaseProperty<T, C> {
  public:
    NumericOps() {}
    NumericOps(const T& t) : BaseProperty<T, C>{ t } {
      set(t);
    }
    void set(const T& t) {
      BaseProperty<T, C>::c_.set(t);
    }
    T& get() {
      return BaseProperty<T, C>::c_.get();
    }
    T constrain(T& t) {
      return BaseProperty<T, C>::c_.constrain(t);
    }
    NumericOps<T, C>& operator=(const T& t) {
      set(t);
      return *this;
    }
    void operator+=(T t) {
      set(get() += t);
    }
    T operator+(T t) {
      return get() + constrain(t);
    }
    void operator-=(const T& t) {
      set(get() -= t);
    }
    T operator-(const T& t) {
      return get() - constrain(t);
    }
    void operator*=(const T& t) {
      set(get() *= t);
    }
    T operator*(const T& t) {
      return get() * constrain(t);
    }
    void operator/=(const T& t) {
      set(get() /= t);
    }
    T operator/(const T& t) {
      return get() / constrain(t);
    }
  };

  /*-----------------------------------------------------------------
    CommonContOps provides methods needed by all STL containers
  -----------------------------------------------------------------*/
  template<typename T, template<typename T> typename C = Null>
  class CommonContOps : virtual public BaseProperty<T, C> {
  public:
    using iterator = typename T::iterator;

    CommonContOps() {}
    CommonContOps(const T& t) : BaseProperty<T, C>{ t } {}
    CommonContOps<T, C>& operator=(const T& t) {
      BaseProperty<T, C>::c_.set(t);
      return *this;
    }
    void set(const T& t) {
      BaseProperty<T, C>::c_.set(t);
    }
    T& get() {
      return BaseProperty<T, C>::c_.get();
    }
    T& constrain(T& t) {
      return BaseProperty<T, C>::c_.constrain(t);
    }

    size_t size() {
      return BaseProperty < T>::t_.size();
    }
    iterator insert(iterator iter, const typename T::value_type& v) {
      return BaseProperty<T>::t_.insert(iter, v);
    }
    void clear() {
      BaseProperty<T>::t_.clear();
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

  /*-----------------------------------------------------------------
    SeqContOps provides methods needed by STL sequential containers
  -----------------------------------------------------------------*/
  template<typename T, template<typename T> typename C = Null>
  class SeqContOps : virtual public BaseProperty<T, C> {
  public:

    SeqContOps() {}
    SeqContOps(const T& t) : BaseProperty<T, C>{ t } {}
    SeqContOps<T, C>& operator=(const T& t) {
      BaseProperty<T, C>::c_.set(t);
      return *this;
    }

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

  /*-----------------------------------------------------------------
    AssocContOps provides methods needed by STL associative containers
  -----------------------------------------------------------------*/
  template<typename T, template<typename T> typename C = Null>
  class AssocContOps : virtual public BaseProperty<T, C> {
  public:

    AssocContOps() {}
    AssocContOps(const T& t) : BaseProperty<T, C>{ t } {}
    AssocContOps<T, C>& operator=(const T& t) {
      BaseProperty<T, C>::c_.set(t);
      return *this;
    }

    typename T::value_type& operator[](typename const T::key_type& key) {
      return BaseProperty<T>::t_[key];
    }
    typename std::pair<typename T::iterator, bool> insert(typename const T::value_type& val) {
      return BaseProperty<T>::t_.insert(val);
    }
    typename T::iterator find(typename const T::key_type& key) {
      BaseProperty<T>::t_.find(key);
    }
    bool contains(typename const T::key_type& key) {
      BaseProperty<T>::t_.contains(key);
    }
  };

  /*-------------------------------------------------------------------
    Generic Property class mixes in all of the above for STL containers
  -------------------------------------------------------------------*/
  template<typename T, template<typename T> typename C = Null>
  class Property : 
    public CommonContOps<T, C>, 
    public NumericOps<T, C>, 
    public SeqContOps<T, C>/*, 
    public AssocContOps<T,C>*/ {
  public:
    Property() {}
    Property(const T& t) : BaseProperty<T, C>{ t } {}
    Property<T, C>& operator=(const T& t) {
      BaseProperty<T, C>::c_.set(t);
      return *this;
    }
  };

  /*-----------------------------------------------------------------
    Property specialization for integers
  -----------------------------------------------------------------*/
  template<template<typename> typename Null>
  class Property<int, Null> : public NumericOps<int> {
  public:
    Property() {}
    Property(const int& t) : BaseProperty<int>{ t } {}
    Property<int, Null>& operator=(int& t) {
      BaseProperty<int, Null>::c_.set(t);
      return *this;
    }
  };

  /*-----------------------------------------------------------------
    Property specialization for doubles
  -----------------------------------------------------------------*/
  template<template<typename> typename Null>
  class Property<double, Null> : public NumericOps<double> {
  public:
    Property() {}
    Property(const double& t) : BaseProperty<double>{ t } {}
    Property<double, Null>& operator=(double& t) {
      BaseProperty<double, Null>::c_.set(t);
      return *this;
    }
  };
}
// see Property.cpp for example of custom property created for Widget