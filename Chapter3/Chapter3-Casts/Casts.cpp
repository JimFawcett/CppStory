// Casts.cpp

#include <string>
#include <iostream>
#include <cstddef>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

/*--------------------------------------------------------------------------------------
   purpose of static_cast is to create a new instance of a foreign type, based on
   data stored in the source type.
  --------------------------------------------------------------------------------------*/

void demoStaticCast() {

  displaySubtitle("static_cast");

  int i = 1.75;  // i = 1, with compiler warning of loss of significance
  int j = static_cast<int>(1.75);  // j = 1, no compiler warning
  std::cout << "\n  demoStaticCast output is compiler warning\n";

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

  mockAPIfunction(&sRef);  // succeeds since sRef is not const

  /*--- evil operation on sRef, violates contract of function interface ---*/
  /* don't do this */
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

  /* create byte array on heap referenced by std::unique_ptr<std::byte> */

  std::unique_ptr<std::byte> pBuffer(new std::byte[Max]);  // owning pointer
  std::byte* pBuffIndex = pBuffer.get();                   // non-owning pointer

  /* pack double d1 into byte array */

  std::byte* pByteSrc = reinterpret_cast<std::byte*>(&d1);
  std::byte* pSrcIndex = pByteSrc;  			   // non-owning pointers

  for (size_t i = 0; i < Max; ++i) {
    *pBuffIndex++ = *pSrcIndex++;
  }

  /* unpack byte array into double d2 */

  if (sizeof(d2) == sizeof(d1)) {
    std::byte* pByteDst = reinterpret_cast<std::byte*>(&d2);
    std::byte* pDstIndex = pByteDst;  			   // non-owning pointers
    pBuffIndex = pBuffer.get();
    for (size_t i = 0; i < Max; ++i) {
      *pDstIndex++ = *pBuffIndex++;
    }
  }

  /* show that src and dst have the same values */

  std::cout << "\n  src double = " << d1;
  std::cout << "\n  dst double = " << d2;

  // byte array on heap will be deallocated here
  // as std::unique_ptr goes out of scope
}

int main() {

  displayTitle("Demonstrating New Style Casts");

  demoStaticCast();
  demoConstCast("Test String");
  demoDynamicCast();
  demoReinterpretCast();
  putline(2);
}
