#pragma once
// CustomTraits.h

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>

/*---- is_string trait ----*/

template <typename T>
struct is_string
{
  static const bool value = false;
};

template <class T, class Traits, class Alloc>
struct is_string<std::basic_string<T, Traits, Alloc>>
{
  static const bool value = true;
};

/*---- is_vector trait ----*/

template <typename T>
struct is_vector
{
  static const bool value = false;
};

template <class T>
struct is_vector<std::vector<T>>
{
  static const bool value = true;
};

/*---- is_pair trait ----*/

template <typename T>
struct is_pair
{
  static const bool value = false;
};

template <class F, class S >
struct is_pair<std::pair<F, S>>
{
  static const bool value = true;
};

/*---- is_unordered_map trait ----*/

template <class T>
struct is_unordered_map
{
  static const bool value = false;
};

template <class K, class V>
struct is_unordered_map<std::unordered_map<K, V>>
{
  static const bool value = true;
};

