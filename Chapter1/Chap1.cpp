#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <initializer_list>
#include <type_traits>
#include <unordered_map>
#include <cstddef>
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
void display(const std::initializer_list<T>& lst)
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

/*---- demonstrations ----*/

void displayDemo(const std::string& msg)
{
  std::cout << "\n  " << msg;
}

/*---- demonstrate initialization ----*/

void demoInit()
{
  displayDemo("-- initialize integers --");
  int i1 = 1;
  int i2(2);
  int i3 = { 3 };
  int i4{ 4 };
  display({ i1, i2, i3, i4 });  // 1, 2, 3, 4

  displayDemo("\n  -- initialize strings --");
  std::string s1 = "one";
  std::string s2("two");
  std::string s3 = { "three" };
  std::string s4{ "four" };  // C++17
  display({ s1, s2, s3, s4 });

  displayDemo("\n  -- initialize doubles --");
  double pi1 = 3.1415927;
  double pi2(pi1 * 2);
  double pi3 = { pi1 * 3 };
  double pi4{ pi1 * 4 };
  display({ pi1, pi2, pi3, pi4 });

  displayDemo("\n  -- initialize std::pairs --");
  std::pair<int, double> pair1 = std::pair(1, 1.5);
  std::pair<int, double> pair2(std::pair<int, double>(2, 2.5));
  std::pair<int, double> pair3 = { 3, 3.5 };
  std::pair<int, double> pair4{ 4, 4.5 };
  display({ pair1, pair2, pair2, pair4 });

  displayDemo("\n  -- initialize std::unordered_maps --");
  std::unordered_map<std::string, int> umap1 = { {"one", 1} };
  std::unordered_map<std::string, int> umap2{ { "two", 2}, {"three", 3} };
  display({ umap1, umap2 });
}
/*---- display type sizes ----*/

template<typename T>
void display(const T& t, const std::string& msg = "")
{
  std::cout << "\n  " << sizeof(t) << " = size of ";
  std::string typeName = typeid(t).name();
  if (typeName.size() > 75)
    typeName = typeName.substr(0, 75) + "...";
  std::cout << typeName;
  if (msg.size() > 0)
    std::cout << msg;
}
/*---- demo types ----*/

void demoIntegralTypes()
{
  displayDemo("-- integral types --");
  void();  // type with no values
  std::nullptr_t dNullptr;        display(dNullptr); // dNullptr <==> nullptr  
  bool Bool;                      display(Bool);
  int Int;                        display(Int);
  unsigned int Uint;              display(Uint);
  short int Sint;                 display(Sint);
  long int Lint;                  display(Lint);
  unsigned long int ULint;        display(ULint);
  long long int LLint;            display(LLint);
  unsigned long long int ULLint;  display(ULLint);
  std::size_t STDsize_t;          display(STDsize_t, " <==> size_t");
  std::cout << std::endl;
}
/*---- character types ----*/
void demoCharTypes()
{
  displayDemo("-- character types --");
  char Char;  display(Char);
  unsigned char Uchar; display(Uchar);
  wchar_t Wchar; display(Wchar);
  //char8_t Char8_t;   display(Char8_t);  C++20
  char16_t Char16_t; display(Char16_t);
  char32_t Char32_t; display(Char32_t);
  std::cout << std::endl;
}
/*---- float types ----*/
void demoFloatTypes()
{
  displayDemo("-- float types --");
  float Float; display(Float);
  double Double; display(Double);
  long double Ldouble; display(Ldouble);
  std::cout << std::endl;
}
/*---- compound types ----*/

void testFun1(const std::string& msg)
{
  std::cout << "\n  " << msg;
}
std::string testFun2()
{
  return "\n  executing testFun2()";
}
void demoCompoundTypes()
{
  displayDemo("-- pointers and references --");
  double pi{ 3.14159 };
  double* pDouble = &pi;  display(pDouble);
  double& rDouble = pi;   display(rDouble, ", note: is double&");

  displayDemo("\n  -- arrays --");
  int iArray[]{ 1, 2, 3, 4 }; display(iArray);

  displayDemo("\n  -- structs --");
  struct Empty {}; display(Empty{});
  struct  Struct { int a; double b; const char* c; } 
  aStruct{ 1, 1.5, "a literal string" }; display(aStruct);

  displayDemo("\n  -- function pointers --");
  void(*pFun)(const std::string&); pFun = testFun1; 
  pFun("executing testFun1"); 
  display(pFun);
  
  using PtrFun = std::string(*)(); PtrFun pF = testFun2; 
  std::cout << "\n  " << pF();
  display(pF);

  std::cout << std::endl;
}
/*---- STL Container types ----*/
void demoSTLTypes()
{
  displayDemo("-- vector<double> --");
  std::vector<double>vDbl0{};                           display(vDbl0);
  std::vector<double> vDbl5{ -0.5, 0, 0.5, 1.0, 1.5 };  display(vDbl5);

  displayDemo("\n  -- unordered_map<std::string, int> --");
  std::unordered_map<std::string, int> uMapSI0{};        display(uMapSI0);
  std::unordered_map<std::string, int> uMapSI3{ {"one", 1}, {"two", 2}, {"three", 3} };
  display(uMapSI3);
  std::cout << std::endl;
}
/*---- miscellaneous types ----*/
void demoMiscellaneousTypes()
{
  displayDemo("-- miscellaneous types --");
  std::byte Byte; display(Byte);

  std::cout << std::endl;
}
/*---- run demonstration ----*/

void displayTitle(const std::string& title)
{
  std::cout << "\n  " << title;
  std::cout << "\n " << std::string(title.size() + 2, '=') << std::endl;
}
void displaySubtitle(const std::string& title)
{
  std::cout << "\n  " << title;
  std::cout << "\n " << std::string(title.size() + 2, '-');
}
int main()
{
  displayTitle("Demonstrating Types");
  displaySubtitle("Type sizes");
  demoIntegralTypes();
  demoCharTypes();
  demoFloatTypes();
  demoCompoundTypes();
  demoSTLTypes();
  demoMiscellaneousTypes();
  displaySubtitle("\n  Type value initialization");
  demoInit();
  std::cout << "\n\n";
}