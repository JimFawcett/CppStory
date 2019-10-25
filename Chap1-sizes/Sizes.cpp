// Sizes.cpp

#include "../Display/Display.h"

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
int main()
{
  displayTitle("Type sizes");
  demoIntegralTypes();
  demoCharTypes();
  demoFloatTypes();
  demoCompoundTypes();
  demoSTLTypes();
  demoMiscellaneousTypes();
  std::cout << "\n\n";
}