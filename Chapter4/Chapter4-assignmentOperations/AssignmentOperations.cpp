// AssignmentOperations.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

namespace Chap3 {

  template<typename T>
  void show(T src, T asn) {
    long int flags = std::cout.flags();
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << "\n  src: " << std::setw(9) << src << " asn: " << std::setw(9) << asn;
    std::cout.flags(flags);
  }

  void show(std::byte src, std::byte asn) {
    long int flags = std::cout.flags();
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout.setf(std::ios::showbase);
    std::cout << "\n  p1: " << std::hex << std::setw(9) << reinterpret_cast<int&>(src);
    std::cout << " p2: " << std::hex << std::setw(9) << reinterpret_cast<int&>(asn);
    std::cout.flags(flags);
  }

  void demoAssignFundamental() {

    displayDemo("--- demo assign fundamental types ---");

    std::byte b1{ 0xf };
    std::byte b2{ 0xe };
    b2 = b1;
    show(b1, b2);

    char c1{ 'z' };
    char c2{ 'a' };
    c2 = c1;
    show(c1, c2);

    int i1{ -3 };
    int i2{ 15 };
    i2 = i1;
    show(i1, i2);

    double d1{ 3.14159 };
    double d2{ 0.33333 };
    d2 = d1;
    show(d1, d2);
    putline();
  }
}

void showArray(int iArray[5], const std::string msg) {
  std::cout << "\n  " << msg << " array: ";
  for (size_t i = 0; i < 5; ++i) {
    std::cout << iArray[i] << " ";
  }
}
void demoAssignArray() {
  displayDemo("--- demo \"assign\" array-- - ");
  int iArray1[5]{ 1, 2, 3, 4, 5 };
  int iArray2[5]{ 4, 3, 2, 1, 0 };
  showArray(iArray1, "iArray1");
  showArray(iArray2, "iArray2");
  /*-- can't directly assign array without wrapping in a struct --*/
  std::cout << "\n  after assigning iArray1 to iArray2:";
  std::memcpy(iArray2, iArray1, 5 * sizeof(int));
  showArray(iArray2, "iArray2");
  putline();
}

struct S { int i; double d; char c; int iArr[3]; };

template<typename S>
void showStruct(S& s, const std::string& msg) {
  std::cout << "\n  " << msg << " struct: ";
  std::cout << "{ " << s.i << ", " << s.d << ", " << s.c << ", [ ";
  for (auto item : s.iArr) {
    std::cout << item << " ";
  }
  std::cout << "] }";
}
void demoAssignStruct() {
  displayDemo("--- demo assign struct ---");
  struct S { int i = 1; double d = 1.0 / 3.0; char c = 'Q'; int iArr[3]{ 1,2,3 }; } s1;
  S s2{ 2, 1.5, 'a', { 3, 2, 1 } };
  showStruct(s1, "s1");
  showStruct(s2, "s2");
  std::cout << "\n  after assignment s2 has values: ";
  s2 = s1;
  showStruct(s2, "s2");
  putline();
}

template<typename T>
void showPtr(T* pSrc, T* pasn) {
  long int flags = std::cout.flags();
  std::cout.setf(std::ios::left, std::ios::adjustfield);
  std::cout.setf(std::ios::showbase);
  std::cout << "\n  p1: " << std::hex << std::setw(9) << reinterpret_cast<int&>(pSrc);
  std::cout << " p2: " << std::hex << std::setw(9) << reinterpret_cast<int&>(pasn);
  std::cout.flags(flags);
}

void demoAssignPointers() {
  displayDemo("--- demo assign pointers ---");
  double d1{ 0.0 };
  double* p1{ &d1 };
  double d2{ 4.0 };
  double* p2{ &d2 };
  showPtr(p1, p2);
  std::cout << "\n  the contents pointed to by p1 and p2 are:";
  Chap3::show(*p1, *p2);
  p2 = p1;
  std::cout << "\n  after assigning p1 to p2:";
  showPtr(p1, p2);
  std::cout << "\n  changing contents of p1:";
  *p1 = 2;
  std::cout << "\n  the contents pointed to by p1 and p2 are:";
  Chap3::show(*p1, *p2);
  std::cout << "\n  illustrates that assigning pointer does not assign contents";
  putline();
}

int main() {

  using namespace Chap3;
  demoAssignFundamental();
  demoAssignArray();
  demoAssignStruct();
  demoAssignPointers();
  putline(2);
}