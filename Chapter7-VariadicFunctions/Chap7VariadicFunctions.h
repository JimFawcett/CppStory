#pragma once
///////////////////////////////////////////////////////////////////
// VariadicFunctionTemplates.h - function displays its arguments //
//                                                               //
// Jim Fawcett, Teaching Professor Emeritus, ECE, Syracuse Univ  //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

/*-- Helper function --*/

inline std::string strTrunc(
  const std::string& src, size_t Max = 50
) {
  if (src.size() > Max) {
    return src.substr(0, Max - 4) + " ...";
  }
  else {
    return src;
  }
}

/*-- Templ specializ'n stops recursive eval --*/

template<typename T>
void f(T t)
{
  std::cout << "\n  " << t << " : "
    << strTrunc(typeid(t).name(), 40)
    << std::endl;
}

/*-- Recursive definition of template function --
   Args is a "parameter pack
   https://en.cppreference.com
*/
template<typename T, typename... Args>
void f(T t, Args... args)
{
  std::cout << "\n  " << t << " : "
    << typeid(t).name() << std::endl;
  f(args...);
}
