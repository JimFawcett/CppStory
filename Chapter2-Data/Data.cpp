// Data.cpp

#include <iostream>
#include "../Display/Display.h"

class Y {};

class X {
public:
  explicit operator Y ();
};

X::operator Y () {
  std::cout << "\n  casting X to Y";
  return Y();
}

int main() {

  /*--- demo cast operator ---*/
  X x;
  Y y = static_cast<Y>(x);
  std::cout << "\n";

  /*--- demo initialization ---*/
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
  auto [f, g, h] = s;
  displayValues(f, g, h);

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

  std::cout << "\n\n";
}