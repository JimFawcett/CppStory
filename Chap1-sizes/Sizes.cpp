/////////////////////////////////////////////////////////////////////////
// Sizes.cpp - explore storage sizes for common C++ types              //
//                                                                     //
// Jim Fawcett, Emeritus Teaching Professor, EECS, Syracuse University //
/////////////////////////////////////////////////////////////////////////

#include "../Display/Display.h"

/*---- integral types ----*/

void demoIntegralTypes()
{
  displayDemo("-- integral types --");
  void();  // type with no values
  std::nullptr_t dNullptr;        displayType(dNullptr); // dNullptr <==> nullptr  
  bool Bool;                      displayType(Bool);
  int Int;                        displayType(Int);
  unsigned int Uint;              displayType(Uint);
  short int Sint;                 displayType(Sint);
  long int Lint;                  displayType(Lint);
  unsigned long int ULint;        displayType(ULint);
  long long int LLint;            displayType(LLint);
  unsigned long long int ULLint;  displayType(ULLint);
  std::size_t STDsize_t;          displayType(STDsize_t, " <==> size_t");
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
}
/*---- miscellaneous types ----*/

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
  std::cout << std::endl;
}
int main()
{
  displayTitle("Type sizes");
  demoIntegralTypes();
  demoCharTypes();
  demoFloatTypes();
  demoCompoundTypes();
  demoSTLTypes();
  demoMiscellaneousTypes();
  std::cout << "\n";
}