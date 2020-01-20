/////////////////////////////////////////////////////////////////////////
// Sizes.cpp - explore storage sizes for common C++ types              //
//                                                                     //
// Jim Fawcett, Emeritus Teaching Professor, EECS, Syracuse University //
/////////////////////////////////////////////////////////////////////////

#include "../Chapter7-Display/Chap7Display.h"
//#include "../Display/Display.h"
#include <climits>
#include <algorithm>
#include <iostream>

void demoLimits()
{
  displayDemo("-- limits --");
  std::cout << "\n  bits in byte =       CHAR_BIT = " << CHAR_BIT;
  std::cout << "\n  min value of char =  CHAR_MIN = " << CHAR_MIN;
  std::cout << "\n  max value of char =  CHAR_MAX = " << CHAR_MAX;
  std::cout << "\n  min value of int =    INT_MIN = " << INT_MIN;
  std::cout << "\n  max value of int =    INT_MAX = " << INT_MAX;
  std::cout << "\n  min value of float =  FLT_MIN = " << FLT_MIN;
  std::cout << "\n  max value of float =  FLT_MAX = " << FLT_MAX;
  std::cout << "\n  min value of double = DBL_MIN = " << DBL_MIN;
  std::cout << "\n  max value of double = DBL_MAX = " << DBL_MAX;
  std::cout << std::endl;
}
/*---- integral types ----*/

void demoIntegralTypes()
{
  displayDemo("-- integral types --");
  void();  // type with no values
  std::nullptr_t dNullptr;        displayType(dNullptr); // dNullptr <==> nullptr 
  std::byte Byte;                 displayType(Byte);
  bool Bool;                      displayType(Bool);
  char Char;                      displayType(Char);
  signed char SChar;              displayType(SChar);
  unsigned char USChar;           displayType(USChar);
  char16_t Char16_t;              displayType(Char16_t);
  char32_t Char32_t;              displayType(Char32_t);
  short int Sint;                 displayType(Sint);
  int Int;                        displayType(Int);
  unsigned int Uint;              displayType(Uint);
  long int Lint;                  displayType(Lint);
  unsigned long int ULint;        displayType(ULint);
  long long int LLint;            displayType(LLint, " <==> long long int");
  unsigned long long int ULLint;  displayType(ULLint, " <==> unsigned long long int");
  std::size_t STDsize_t;          displayType(STDsize_t, " <==> size_t");
  putline();
  std::cout << "\n  demonstrate integer roll-over:";
  unsigned int i = UINT_MAX;
  unsigned int j = i + 1;
  std::cout << "\n  i = UINT_MAX : " << i;
  std::cout << "\n  i + 1 = " << j;
  std::cout << "\n";

  std::cout << std::endl;
}
/*---- character types ----*/

void demoCharTypes()
{
  displayDemo("-- character types --");
  char Char;  displayType(Char);
  unsigned char Uchar; displayType(Uchar);
  wchar_t Wchar;       displayType(Wchar);
  //char8_t Char8_t;   displayType(Char8_t);  C++20
  char16_t Char16_t;   displayType(Char16_t);
  char32_t Char32_t;   displayType(Char32_t);
  std::cout << std::endl;
}
/*---- float types ----*/

void demoFloatTypes()
{
  displayDemo("-- float types --");
  float Float;          displayType(Float);
  double Double;        displayType(Double);
  long double Ldouble;  displayType(Ldouble);
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
  double* pDouble = &pi;  displayType(pDouble);
  double& rDouble = pi;   displayType(rDouble, ", note: is double&");
  size_t drefSize = sizeof(double&);
  std::string drefName = typeid(double&).name();
  std::cout << "\n  " << drefSize << " = size of " << drefName << " <==> sizeof(double&)";
  std::cout << std::endl;
  std::cout << "\n  pDouble:   " << pDouble << " --> " << reinterpret_cast<int>(pDouble);
  std::cout << "\n  ++pDouble: " << ++pDouble << " --> " << reinterpret_cast<int>(pDouble);

  displayDemo("\n  -- arrays --");
  int iArray[]{ 1, 2, 3, 4 }; displayType(iArray);

  displayDemo("\n  -- std::strings --");
  std::string str1{};
  displayType(str1, ",\n       is std::string{}");
  std::string str2{ "a std::string" };
  displayType(str2, ",\n       is std::string{ \"a std::string\" }");

  displayDemo("\n  -- structs --");
  struct Empty {}; displayType(Empty{}, ",\n      is struct {}");
  struct  Struct { int a; double b; const char* c; }
  aStruct{ 1, 1.5, "a literal string" }; 
  displayType(aStruct, ",\n       is struct { 1, 1.5, \"a literal string\" }");

  displayDemo("\n  -- function pointers --");
  void(*pFun)(const std::string&); pFun = testFun1;
  pFun("executing testFun1(const std::string&)");
  displayType(pFun);
  using PtrFun = std::string(*)(); PtrFun pF = testFun2;
  std::cout << pF();
  displayType(pF);

  std::cout << std::endl;
}
/*---- STL Container types ----*/

void demoSTLTypes()
{
  displayDemo("-- vector<double> --");
  std::vector<double>vDbl0{};
  displayType(vDbl0, ",\n       is std::vector<double>{}");
  std::vector<double> vDbl5{ -0.5, 0, 0.5, 1.0, 1.5 };  
  displayType(vDbl5, ",\n       is std::vector<double>{ -0.5, 0, 0.5, 1.0, 1.5 }");

  displayDemo("\n  -- vector<double>::iterator --");
  std::vector<double>::iterator vIter{ vDbl5.begin() };
  displayType(vIter, ",\n       is vector<double>::iterator");

  displayDemo("\n  -- unordered_map<std::string, int> --");
  std::unordered_map<std::string, int> uMapSI0{};
  displayType(uMapSI0, ",\n       is std::unordered_map<std::string, int>{}");
  std::unordered_map<std::string, int> uMapSI3{ {"one", 1}, {"two", 2}, {"three", 3} };
  displayType(uMapSI3, ",\n       is std::unordered_map<std::string, int>{ {\"one\", 1}, ... }");

  displayDemo("\n  -- unordered_map<std::string,int>::iterator --");
  std::unordered_map<std::string, int>::iterator mIter{ uMapSI3.begin() };
  displayType(mIter, ",\n       is std::unordered_map<std::string, int>::iterator");
  std::cout << std::endl;

  displayDemo("\n  -- display vector contents in rows of N --");
  std::vector<int> test{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
  size_t N = 4;
  auto fold = [N](auto t) {
    static size_t count = UINT_MAX - 1;
    if (++count > N) {
      count = 1;
      std::cout << "\n  ";
    }
    std::cout << t << " ";
  };
  std::for_each(test.begin(), test.end(), fold);
  std::cout << std::endl;
}
/*---- miscellaneous types ----*/

class XwithDouble { double d; } x1;
class XwithRef {
public:
  XwithRef(double d) : dr(d) {}
  double& dr;
} x2(1.5);

void demoMiscellaneousTypes()
{
  displayDemo("-- miscellaneous types --");

  std::byte Byte; displayType(Byte);

  std::vector<int>::size_type sType{ 3 }; 
  displayType(sType, ", is size_type");

  std::tuple<int, double, std::string> tType{ 1, 1.5, "two" };
  displayType(tType);

  std::unique_ptr<double> uPtr{ std::make_unique<double>(3.14159) };
  displayType(uPtr);
  std::shared_ptr<double> sPtr{ std::make_shared<double>(2 * 3.14159) };
  displayType(sPtr);

  displayType(x1, "\t<==> instance of class with double member");
  displayType(x2, "\t<==> instance of class with double& member");
  displayTypeArgument<XwithDouble>("\t<==> class with double member");
  displayTypeArgument<XwithRef>("\t<==> class with double& member");

  displayTypeArgument<std::nullptr_t>();
  displayType(std::cout, "\t<==> std::cout");
  displayTypeArgument<std::ostream>("\t<==> std::ostream");

  int i{ 42 };
  auto f = [i](const std::string& s) {
    std::cout << s << i;
  };
  f("\n  The meaning of life is ");
  displayType(f);
  std::cout << std::endl;

  std::string str("content of a std::string");
  const char* pContents = str.c_str();
  displayType(str);
  displayType(pContents);

  std::cout << "\n  " << str;
  std::cout << "\n  string size = " << (str.size() + 1) * sizeof(char);  // count terminating null
  std::cout << "\n  allocation size = " << str.capacity() * sizeof(char);
  std::cout << std::endl;
}
int main()
{
  displayTitle("Type sizes");
  demoLimits();
  demoIntegralTypes();
  demoCharTypes();
  demoFloatTypes();
  demoCompoundTypes();
  demoSTLTypes();
  demoMiscellaneousTypes();
  std::cout << "\n";
}