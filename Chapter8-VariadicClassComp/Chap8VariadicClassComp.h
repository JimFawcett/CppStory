#pragma once
///////////////////////////////////////////////////////////////
// Chap7VariadicClassComp.h - data composition               //
//                                                           //
// Minor adaption of code presented in riptutorial.com       //
// Stackoverflow documentation                               //
// https://riptutorial.com/cplusplus/example/19276/          //
// variadic-template-data-structures                         //
//                                                           //
// Builds a public data aggregator, like std::tuple,         //
// but uses composition instead of inheritance.              //
///////////////////////////////////////////////////////////////
/*
  This DataStructure class provides the same functionality as
  std::tuple.  It's presented  here to illustrate a technique
  for using variadic template classes.

  You should prefer to use std::tuple.
*/
template<typename ... T>
struct DataStructure {};

template<size_t id, typename T>
struct GetHelper;

template<typename T, typename ... Rest>
struct DataStructure<T, Rest ...>
{
  DataStructure(const T& first, const Rest& ... rest)
    : first(first), rest(rest...)
  {}

  T first;
  DataStructure<Rest ... > rest;

  template<size_t id>
  auto get()
  {
    return GetHelper<id, DataStructure<T, Rest...>>::get(*this);
  }
};

template<typename T, typename ... Rest>
struct GetHelper<0, DataStructure<T, Rest ... >>
{
  static T get(DataStructure<T, Rest...>& data)
  {
    return data.first;
  }
};

template<size_t id, typename T, typename ... Rest>
struct GetHelper<id, DataStructure<T, Rest ... >>
{
  static auto get(DataStructure<T, Rest...>& data)
  {
    return GetHelper<id - 1, DataStructure<Rest ...>>::get(data.rest);
  }
};

