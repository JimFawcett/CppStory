// Chap7FoldExpressions.cpp

#include <iostream>
#include <string>
#include <sstream>
#include "../Chapter7-Display/Chap7Display.h"
//#include "../Display/Display.h"

template<typename ...Args>
void pushToCout1(Args&&... args) {
  (std::cout << ... << std::forward<Args>(args));
}

auto makeHelper(std::string prefix = ", ", std::string firstPrefix = "") {
  int debug = 0;
  auto f = [prefix, firstPrefix](auto a) mutable {
    static std::ostringstream out2;
    out2 << a;
    std::string temp = firstPrefix + out2.str();
    out2.str("");
    firstPrefix = prefix;
    return temp;
  };
  debug++;
  return f;
}

template<typename ...Args>
void pushToCout2(const Args&... args) {
  static auto f = makeHelper(", ");
  (std::cout << ... << (f(args)));
}

template<typename F, typename ...Args>
void pushToCout3(F f, const Args&... args) {
  (std::cout << ... << (f(args)));
}

template<typename ...Args>
auto accumulateOrs(Args... args) {
  return ((args) || ...);
}

template<typename ...Args>
auto accumulateAnds(Args... args) {
  return ((args) && ...);
}

template<typename T, typename ...Args>
auto sum(T t, Args... args) {
  return (t + ... + args);
}

int main() {

  displayTitle("Demonstrate Fold Expressions");

  displayDemo("-- pushToCout1 -- fold on operator<< --");
  std::cout << "\n  ";
  pushToCout1("argggghhh!", 1, 2.5, 'z');
  std::cout << "\n  ";
  pushToCout1('z', 2.5, 1, "argggghhh!");
  displayDemo("\n  -- pushToCout2 -- fold on operator<< --");
  std::cout << "\n  ";
  pushToCout2("aaaahhhhh!", 1, 2.5, 'z');
  std::cout << "\n  ";
  pushToCout2('z', 2.5, 1, "aaaahhhhh!");
  displayDemo("\n  -- pushToCout3 -- fold on operator<< --");
  std::cout << "\n  ";
  //auto f = makeHelper(", ");
  pushToCout3(makeHelper(), "aaaahhhhh!", 1, 2.5, 'z');
  std::cout << "\n  ";
  pushToCout3(makeHelper(), 'z', 2.5, 1, "aaaahhhhh!");

  displayDemo("\n  -- fold on logical operator --");
  std::cout << std::boolalpha;
  std::cout << "\n  " << accumulateOrs(0, 0, 0);
  std::cout << "\n  " << accumulateOrs(false, true, false);
  std::cout << "\n  " << accumulateAnds(false, true, false);

  displayDemo("\n  -- fold on addition operator --");
  std::cout << "\n  " << sum(1, 2.5, -2);
  std::string s1 = "first";
  std::string s2 = " and ";
  std::string s3 = "second";
  std::cout << "\n  " << sum(s1, s2, s3);
  std::cout << "\n\n";
}
