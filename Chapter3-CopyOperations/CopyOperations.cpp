// CopyOperations.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include "../Display/Display.h"

namespace Chap3 {

  template<typename T>
  void show(T src, T cpy) {
    long int flags = std::cout.flags();
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << "\n  src: " << std::setw(9) << src << " cpy: " << std::setw(9) << cpy;
    std::cout.flags(flags);
  }

  void show(std::byte src, std::byte cpy) {
    long int flags = std::cout.flags();
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout.setf(std::ios::showbase);
    std::cout << "\n  src: " << std::hex << std::setw(9) << reinterpret_cast<int&>(src);
    std::cout << " cpy: " << std::hex << std::setw(9) << reinterpret_cast<int&>(cpy);
    std::cout.flags(flags);
  }

  void demoCopyFundamental() {

    displayDemo("--- demo copy fundamental types ---");

    std::byte b1{ 0xf };
    std::byte b2{ b1 };

    show(b1, b2);

    char c1{ 'z' };
    char c2{ c1 };
    show(c1, c2);

    int i1{ -3 };
    int i2{ i1 };
    show(i1, i2);

    double d1{ 3.14159 };
    double d2{ d1 };
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
void demoCopyArray() {
  displayDemo("--- demo copy array ---");
  int iArraySrc[5]{ 1, 2, 3, 4, 5 };
  int iArrayCpy[5];
  std::memcpy(iArrayCpy, iArraySrc, 5*sizeof(int));
  showArray(iArraySrc, "src");
  showArray(iArraySrc, "cpy");
  putline();
}

template<typename S>
void showStruct(S& s, const std::string& msg) {
  std::cout << "\n  " << msg << " struct: ";
  std::cout << "{ " << s.i << ", " << s.d << ", " << s.c << ", [ ";
  for (auto item : s.iArr) {
    std::cout << item << " ";
  }
  std::cout << "] }";
}
void demoCopyStruct() {
  displayDemo("--- demo copy struct ---");
  struct S { int i = 1; double d = 1.0 / 3.0; char c = 'Q'; int iArr[3]{ 1,2,3 }; } s1;
  S s2{ s1 };
  showStruct(s1, "src");
  showStruct(s2, "cpy");
  putline();
}

template<typename T>
void showPtr(T* pSrc, T* pCpy) {
  long int flags = std::cout.flags();
  std::cout.setf(std::ios::left, std::ios::adjustfield);
  std::cout.setf(std::ios::showbase);
  std::cout << "\n  src: " << std::hex << std::setw(9) << reinterpret_cast<int&>(pSrc);
  std::cout << " cpy: " << std::hex << std::setw(9) << reinterpret_cast<int&>(pCpy);
  std::cout.flags(flags);
}

void demoCopyPointers() {
  displayDemo("--- demo copy pointers ---");
  double dArr[5]{ 0.0, 0.5, 1.0, 1.5, 2.0 };
  double* pSrc = &dArr[0];
  double* pCpy{ pSrc };
  showPtr(pSrc, pCpy);
  std::cout << "\n  the contents pointed to by pSrc and pCpy are:";
  Chap3::show(*pSrc, *pCpy);
  *pSrc = -1.0;
  std::cout << "\n  after changing contents of pSrc:";
  Chap3::show(*pSrc, *pCpy);
  std::cout << "\n  illustrates that copying pointer does not copy contents";
  putline();
}

int main() {

  using namespace Chap3;
  demoCopyFundamental();
  demoCopyArray();
  demoCopyStruct();
  demoCopyPointers();
  putline(2);
}