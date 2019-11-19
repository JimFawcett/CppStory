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

auto putline = [](int n=1) { 
  for(int i=0; i<n; ++i)
    std::cout << std::endl; 
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
