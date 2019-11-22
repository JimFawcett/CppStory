///////////////////////////////////////////////////////////////////////////
// Survey.cpp - Code for Survey Examples                                 //
//                                                                       //
// Jim Fawcett, Emeritus Teaching Professor, EECS Syracuse University    //
///////////////////////////////////////////////////////////////////////////
/*
*  Basic examples for CppStory Chapter1 - Survey
*
*  Required Files:
*  ---------------
*  Survey.cpp
*
*  Maintenance History:
*  --------------------
*  ver 1 : 16 Nov 2019
*  - first release
*/

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <optional>
#include <tuple>
#include <initializer_list>
#include <any>
#include <typeinfo>
#include "../Display/Display.h"

#pragma warning (disable : 4244)  // intentionally narrowing conversions

/*--- arraySize from Effective Modern C++, Meyers ---*/

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept {
  return N;
}

template<typename T>
void displaySizeAndType(T& t, const std::string& msg = "") {
  std::string typeName = typeid(t).name();
  std::cout << "\n  " << sizeof(t) << " = size of " << typeName;
  if (msg.size() > 0)
    std::cout << ",  " << msg;
}

char ul = '-';
auto showTitle = [=](const std::string& title) {
  std::cout << "\n  " << title;
  std::cout << "\n " << std::string(title.size() + 2, ul);
};

void demoArraysAndPointers(int argc, char* argv[]) {

  showTitle("Demo pointers and arrays");

  displaySizeAndType(argv, "\t\targv[] decayed to pointer");

  const char* args[] = { "one", "two", "three" };
  displaySizeAndType(args, "\targs[] still has array type");
  std::cout << std::endl;

  // int main(int argc, char* argv[]) {

  std::cout << "\n  displaying command line arguments using array";
  std::cout << "\n  ";
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << " ";
    if ((i + 1) % 2)
      std::cout << "\n  ";
  }
  std::cout << "\n  ";

  std::cout << "\n  displaying command line arguments using pointer";
  std::cout << "\n  ";
  char** ptr = argv;
  for (int i = 0; i < argc; ++i) {
    std::cout << *(ptr++) << " ";
    if ((i + 1) % 2)
      std::cout << "\n  ";
  }
  std::cout << "\n\n  ";

  std::cout << "\n  displaying args[]";
  std::cout << "\n  ";
  size_t sizeOfArgsArray = arraySize(args);
  for (size_t i = 0; i < sizeOfArgsArray; ++i) {
    std::cout << args[i] << " ";
  }
}

void demoSTL() {

  std::vector<int> test{ 1, 2, 3, 4, 5 };
  std::string prefix = "\n  ";
  auto show = [&](auto element) {
    std::cout << prefix << element;
    prefix = ", ";
  };
  std::for_each(test.begin(), test.end(), show);

  int sum = 0;
  auto sumer = [&sum](auto element) { sum += element; };
  std::for_each(test.begin(), test.end(), sumer);
  std::cout << "\n  sum = " << sum;
}

void demoOptional() {

  showTitle("demoOptional");

  std::ofstream ofstrm;

  /*--- attempt to open file for writing ---*/

  auto fout = [&ofstrm](const std::string& filename) {
    ofstrm.open(filename, std::ios::out);
    std::optional<std::ofstream*> opt = &ofstrm;
    if (!ofstrm.good())
      opt = nullptr;
    return opt;
  };
  /*--- attempt to write file ---*/

  auto opto = fout("testWrite.txt");
  if (opto.has_value()) {
    std::string test("\n  this is a test\n");
    auto foptr = opto.value();
    *foptr << test;
    foptr->close();
  }
  /*--- attempt to open file for reading ---*/

  std::ifstream ifstrm;

  auto fin = [&ifstrm](const std::string& filename) {
    ifstrm.open(filename, std::ios::in);
    std::optional<std::ifstream*> opt = &ifstrm;
    if (!ifstrm.good())
      opt = nullptr;
    return opt;
  };
  /*--- attempt to read file ---*/

  auto opti = fin("testWrite.txt");
  if (opti.has_value()) {
    auto fiptr = opti.value();
    std::cout << fiptr->rdbuf();
    fiptr->close();
  }
}
/*--------------------------------------------------------------------------------------
   purpose of static_cast is to create a new instance of a foreign type, based on
   data stored in the source type.
  --------------------------------------------------------------------------------------*/

void demoStaticCast() {
  
  displaySubtitle("static_cast");
  int i = 1.75;  // i = 1, with compiler warning of loss of significance
  int j = static_cast<int>(1.75);  // no compiler warning

  displayValues({ i }, ", conversion of 1.75 to 1 with no cast: compiler warning", "\n  ");
  displayValues({ j }, ", conversion of 1.75 to 1 with static_cast: no warning");
  std::cout << "\n";
}

/*--------------------------------------------------------------------------------------
   purpose of const_cast is to allow passing const data to functions that won't change
   value even though not declared const functions, OS API calls for example.
  --------------------------------------------------------------------------------------*/
void mockAPIfunction(std::string* pStr) {
  std::cout << "\n  inside mock API function: " << *pStr;
}

void demoConstCast(const std::string& str) {

  displaySubtitle("const_cast");

  std::cout << "\n  " << str;
  //mockAPIfunction(&str);  fails to compile since str is const

  /*--- useful operation using sRef ---*/
  std::string& sRef = const_cast<std::string&>(str);
  // created non-const reference to const str
  mockAPIfunction(&sRef);

  /*--- evil operation on sRef, violates contract of function interface ---*/
  sRef = "changed";
  std::cout << "\n  " << str;  // now has changed value
  std::cout << "\n";
}

/*--------------------------------------------------------------------------------------
  dynamic_cast grants access to derived class interfaces starting with base pointer
  --------------------------------------------------------------------------------------*/

class Base {
public:
  virtual ~Base() {}
  virtual void say() {
    std::cout << "\n  hello from Base::say() via " << typeid(*this).name();
  }
};

class Derived1 : public Base {
public:
  virtual ~Derived1() {}
  void say1() {
    std::cout << "\n  hello from Derived1::say1() via " << typeid(*this).name();
  }
};

class Derived2 : public Base {
public:
  virtual ~Derived2() {}
  void say2() {
    std::cout << "\n  hello from Derived2::say2() via " << typeid(*this).name();
  }
};

//auto putline = [](int n=1) { 
//  for(int i=0; i<n; ++i)
//    std::cout << std::endl; 
//};

void demoDynamicCast() {

  displaySubtitle("dynamic_cast");

  std::cout << "\n --- calls from objects ---\n";
  Base b; b.say();
  putline();
  Derived1 d1; d1.say(); d1.say1();
  putline();
  Derived2 d2; d2.say(); d2.say2();
  putline();

  std::cout << "\n --- call via base pointer ---\n";
  Base* pBase = &d1; pBase->say(); // pBase->say1(); not accessible from B*
  putline();

  std::cout << "\n --- call via dynamic_cast derived pointer ---\n";

  Derived1* pDer1 = dynamic_cast<Derived1*>(pBase);
  if (pDer1) {
    pDer1->say1();
  }
  putline();
}

/*--------------------------------------------------------------------------------------
  purpose of reinterpret_cast is to apply new type rules to an existing instance.
  - packing double's bytes into byte array
  - unpacking byte array into another double
  - illustrates how data might be marshalled over a socket channel, where the
    byte array pretends to be the socket channel
  --------------------------------------------------------------------------------------*/

void demoReinterpretCast() {

  displaySubtitle("reinterpret_cast");

  double d1{ 3.5 };
  double d2;
  size_t Max = sizeof(d1);

  std::unique_ptr<std::byte> pBuffer(new std::byte[Max]);  // owning pointer
  std::byte* pBuffIndex = pBuffer.get();  // non-owning pointer

  /* pack double d1 into byte array */

  std::byte* pByteSrc = reinterpret_cast<std::byte*>(&d1);
  std::byte* pSrcIndex = pByteSrc;  // non-owning pointers

  for (size_t i = 0; i < Max; ++i) {
    *pBuffIndex++ = *pSrcIndex++;
  }

  /* unpack byte array into double d2 */

  if (sizeof(d2) == sizeof(d1)) {
    std::byte* pByteDst = reinterpret_cast<std::byte*>(&d2);
    std::byte* pDstIndex = pByteDst;  // non-owning pointers
    pBuffIndex = pBuffer.get();
    for (size_t i = 0; i < Max; ++i) {
      *pDstIndex++ = *pBuffIndex++;
    }
  }
  std::cout << "\n  src double = " << d1;
  std::cout << "\n  dst double = " << d2;
  
  putline();
  // byte array on heap will be deallocated here
  // as std::unique_ptr goes out of scope
}

void demoCasts() {
  displaySubtitle("demoCasts");

  demoStaticCast();
  demoConstCast("const string");
  demoDynamicCast();
  demoReinterpretCast();
}

template<typename T>
T max(T t1, T t2) {
  std::cout << "\n -- using generic --";
  return t1 > t2 ? t1 : t2;
}

using pStr = const char*;

template<>
pStr max(pStr s1, pStr s2) {
  std::cout << "\n -- using specific overload --";
  return ((strcmp(s1, s2) > 0) ? s1 : s2);
}

void demoOverload() {

  displaySubtitle("demoTemplateFunctionOverload");
  int maxInt = max(2, 3);
  std::cout << "\n  max(2, 3) = " << maxInt;
  double maxDbl = max(2.5, 1.5);
  std::cout << "\n  max(2.5, 1) = " << maxDbl;
  const char* pS = max("aardvark", "zebra");
  std::cout << "\n  max(\"aardvark\", \"zebra\") = " << pS;
}
int main(int argc, char* argv[]) {

  demoArraysAndPointers(argc, argv);
  demoSTL();
  demoOptional();
  demoCasts();
  demoOverload();
  std::cout << "\n\n";
}