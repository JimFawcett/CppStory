// Polymorphism.cpp

#include "../../Chapter8/Chapter8-Display/Chap8Display.h"
#include "Polymorphism.h"
#include <iostream>
#include <string>

class B {
public:
  B(const std::string& name);
  virtual ~B() {}
  virtual void mf1();
  virtual void mf2();
  void who();
private:
  virtual std::string name();
  std::string name_;
};

B::B(const std::string& name) : name_(name) {}

void B::mf1() {
  std::cout << "\n  B::mf1() invoked";
}

void B::mf2() {
  std::cout << "\n  B::mf2() invoked";
}

std::string B::name() { return name_; }

void B::who() { std::cout << "\n  who returns name " << this->name(); }

class D : public B {
public:
  D(const std::string& name);
  virtual ~D() {}
  virtual void mf2() override;
  virtual void mf3();
private:
  virtual std::string name() override;
  std::string name_;
};

D::D(const std::string& name) : B("B"), name_(name) {}

void D::mf2() {
  std::cout << "\n  D::mf2() invoked";
}

void D::mf3() {
  std::cout << "\n  D::mf3() invoked";
}

std::string D::name() { return name_; }

int main() {

  displayDemo("--- polymorphism demo ---");

  displayDemo("\n  create B and invoke its methods");
  B b{ "B" };
  b.who();
  b.mf1();
  b.mf2();

  displayDemo("\n  create D and invoke its methods");
  D d{ "D" };
  d.who();
  d.mf1();
  d.mf2();
  d.mf3();

  displayDemo("\n  create B* pB = &b, and invoke methods");
  B* pB = &b;
  pB->who();
  pB->mf1();
  pB->mf2();

  displayDemo("\n  create B* pB = &d, and invoke methods");
  pB = &d;
  pB->who();
  pB->mf1();
  pB->mf2();
  //pB->mf3();  won't compile: mf2 not in base interface

  D* pD = dynamic_cast<D*>(pB);
  if (pD)
    pD->mf3();

  putline(2);
}