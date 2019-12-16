// ReturnValueOptimization.cpp

#include <iostream>
#include "../Display/Display.h"

namespace Chap3 {

  class X {
  public:
    X() {
      std::cout << "\n  default construction of ";
      myCount_ = ++numObjs_;
      std::cout << "object #" << myCount_;
    }
    X(const X& x) {
      std::cout << "\n  copy construction of ";
      myCount_ = ++numObjs_;
      std::cout << "object #" << myCount_;
    }
    X(X&& x) noexcept {
      std::cout << "\n  move construction of ";
      myCount_ = ++numObjs_;
      std::cout << "object #" << myCount_;
    }
    X& operator=(const X& x) {
      std::cout << "\n  copy assignment of ";
      std::cout << "object #" << myCount_;
    }
    X& operator=(X&& x) noexcept {
      std::cout << "\n  move assignment of ";
      std::cout << "object #" << myCount_;
    }
    ~X() {
      std::cout << "\n  destruction of ";
      std::cout << "object #" << myCount_;
    }
    size_t id() {
      return myCount_;
    }
  private:
    static size_t numObjs_;
    size_t myCount_;
  };

  size_t X::numObjs_ = 0;  // static members must be defined outside class declaration
}
void showIn(const std::string& funName) {
  std::cout << "\n  entered " << funName;
}
void showOut(const std::string& funName) {
  std::cout << "\n  returned from " << funName;
}

Chap3::X test1() {
  showIn("test1 - return with move");
  Chap3::X x1;
  return x1;
}
Chap3::X test2() {
  showIn("test2 - return with RVO");
  return Chap3::X();
}
Chap3::X test3() {
  showIn("test2 - return with copy");
  static Chap3::X x;
  return x;
}

struct Cosmetic { ~Cosmetic() { putline(2); } }cosm;

int main() {
  using namespace Chap3;
  X x1 = test1();
  showOut("test1");
  putline();
  X x2 = test2();
  showOut("test2");
  putline();
  X x3 = test3();
  showOut("test3");
  std::cout << "\n\n";
}