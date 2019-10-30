#include <iostream>
#include <string>
#include <sstream>
#include <initializer_list>
#include <type_traits>
#include <unordered_map>
#include "Chap1.h"

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

/*---- is_pair trait ----*/

template <typename T>
struct is_pair
{
  static const bool value = false;
};

template <class F, class S >
struct is_pair<std::pair<F,S>>
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

/*---- display selected type values ----*/

template <typename T>
void display(std::initializer_list<T> lst)
{
  std::string prefix = "\n  ";
  for (auto item : lst)
  {
    if constexpr (std::is_scalar<T>::value || is_string<T>::value)
    {
      std::cout << prefix << item;
    }
    else if constexpr (is_pair<T>::value)
    {
      std::cout << prefix << "{ " << item.first << ", " << item.second << " }";
    }
    else if constexpr (is_unordered_map<T>::value)
    {
      for (auto elem : item)
      {
        std::cout << prefix << "{ " << elem.first << ", " << elem.second << " }";
      }
    }
    prefix = ", ";
  }
}

/*---- demonstrate initialization ----*/

void demoInit()
{
  int i1 = 1;
  int i2(2);
  int i3 = { 3 };
  int i4{ 4 };

  display({ i1, i2, i3, i4 });  // 1, 2, 3, 4

  std::string s1 = "one";
  std::string s2("two");
  std::string s3 = { "three" };
  std::string s4{ "four" };  // C++17

  display({ s1, s2, s3, s4 });

  double pi1 = 3.1415927;
  double pi2(pi1 * 2);
  double pi3 = { pi1 * 3 };
  double pi4{ pi1 * 4 };

  display({ pi1, pi2, pi3, pi4 });

  std::pair<int, double> pair1 = std::pair(1, 1.5);
  std::pair<int, double> pair2(std::pair<int, double>(2, 2.5));
  std::pair<int, double> pair3 = { 3, 3.5 };
  std::pair<int, double> pair4{ 4, 4.5 };

  display({ pair1, pair2, pair2, pair4 });

  std::unordered_map<std::string, int> umap1 = { {"one", 1} };
  std::unordered_map<std::string, int> umap2{ { "two", 2}, {"three", 3} };

  display({ umap1, umap2 });
}
/*---- run demonstration ----*/

int main()
{
  demoInit();
  std::cout << std::endl;
}