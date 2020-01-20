/////////////////////////////////////////////////////////////////////
// Data.cpp - Initialization Examples for Chapter 2                //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include "../Chapter7-Display/Chap7Display.h"
//#include "../Display/Display.h"

#pragma warning (disable : 4244)  // intentionally narrowing conversions

class Y {};

class X {
public:
  explicit operator Y ();
};

X::operator Y () {
  std::cout << "\n  casting X to Y";
  return Y();
}

void demoCast() {
  displayDemo("--- demo cast ---");

  X x;
  Y y = static_cast<Y>(x);
  std::cout << "\n";
}
void demoInitialization() {
  displayDemo("--- demo initialization ---");

  int i = 1.75;  // compiles with warning
  // int j{ 1.75 };  compile failure

  auto [a, b] = std::pair{ 2, 3.1415927 };
  std::cout << "\n  auto [a, b] = std::pair{2, 3.1415927 }; ==> a = " << a << " and b = " << b;
  std::cout << "\n";
  auto [c, d, e] = std::tuple{ 'a', -2.5, "a string" };
  displayValues(c, d, e);

  struct S {
    int a;
    double b;
    std::string c;
  };
  S s{ 1, 1.5, "two" };
  displayType(s, "\n  <= struct S{ int a; double b; std::string c; } s{ 1, 1.5, \"two\" }", false);
  auto [sa, sb, sc] = s;
  displayValues(sa, sb, sc);

  std::tuple tp{ 1, 1.5, "two" };
  auto [ta, tb, tc] = tp;

  displayType(
    tp, 
    " <= std::tuple tp{ 1, 1.5, \"two\" }", 
    false
  );
  displayValues(ta, tb, tc);

  class Z {
  public:
    Z(const std::string& s, bool cool) : str_(s), cool_(cool) {}
    void say() {
      std::cout << "\n  " << str_;
      if (cool_)
        std::cout << "\n  Z is cool";
      else
        std::cout << "\n  Z is not cool";
    }
  private:
    std::string str_;
    bool cool_;
  };

  Z z{ "a string for Z" , true };
  z.say();
  putline();
}

void demoStructuredBinding() {
  displayDemo("--- demo structured binding ---");
  std::vector<int> test{ 1, 2, 3, 4 };
  //auto [v1, v2] = test;
  struct S {
    std::vector<int> vecInt;
    std::vector<double> vecDbl;
  };
  S s{ {1, 3, 4}, {1.5, 2.0, 2.5} };
  auto [v1, v2] = s;
  displayValues(v1, v2);
}

void demoFloatGranularity(size_t Max) {
  displayDemo("--- demo float granularity ---\n");

  float f{ 1.0 };
  std::cout.setf(std::ios::adjustfield, std::ios::left);
  std::cout.setf(std::ios::showpoint);
  std::cout.precision(6);
  std::cout << "\n  " << std::setw(22) << "float f = " << f;
  //displayValues({ f }, " = float f");
 
  for (size_t i = 0; i < Max; ++i) {
    f = (f + 1.0)/3.0;
    std::cout << "\n  " << std::setw(22) << "f = (f + 1.0)/3.0 ==> " << f;
    //displayValues({ f }, " <== f = (f + 1.0)/3.0");
  }
  
  std::cout << "\n\n  Reversing process:\n";

  for (size_t i = 0; i < Max; ++i) {
    f = 3.0 * f - 1.0;;
    std::cout << "\n  " << std::setw(22) << "f = 3.0 * f - 1.0 ==> " << f;
  }
  std::cout << std::endl;
}

int main() {

  demoInitialization();
  demoStructuredBinding();
  demoCast();
  demoFloatGranularity(5);
  demoFloatGranularity(10);
  
  std::cout << "\n\n";
}