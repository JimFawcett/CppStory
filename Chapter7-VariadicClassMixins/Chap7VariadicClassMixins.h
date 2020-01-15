#pragma once
/////////////////////////////////////////////////////////////////
// Chap7VariadicClassMixins.cpp - demonstrates variadic mixins //
//                                                             //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2018   //
/////////////////////////////////////////////////////////////////

#include <iostream>

namespace Chap7 {

  class A {
  public:
    A() { std::cout << "\n  an A here"; }
    A(const A& a) { std::cout << "\n  copy A here"; }
    virtual ~A() {}
  };

  class B {
  public:
    B() { std::cout << "\n  a B here"; }
    B(const B& b) { std::cout << "\n  copy B here"; }
    virtual ~B() {}
  };

  class C {
  public:
    C() { std::cout << "\n  a C here"; }
    C(const C& c) { std::cout << "\n  copy C here"; }
    virtual ~C() {}
    void do_C_op() { std::cout << "\n  doing C's operation"; }
  };

  template<typename... Mixins>
  class D : public Mixins...
  {
  private:
    bool hasMixins = false;
  public:
    // D() fails to compile because same as D(const Mixins& ... mixins)
    // when there are no mixins
    // D() { std::cout << "\n  a D here"; }
    D(const Mixins& ... mixins) : Mixins(mixins)... {
      if (sizeof...(mixins) == 0)
        std::cout << "\n  a D here";
      else
      {
        hasMixins = true;
        std::cout << "\n  copy D here";
      }
    }
    virtual ~D() {}
    void say()
    {
      if (!hasMixins)
        std::cout << "\n  class D with no mixins here";
      else
        //std::cout << "\n  class D with mixins here";
        std::cout << "\n  " << typeid(this).name();
      //std::cout << "\n  " << typeid(this).raw_name();
      C* pC = dynamic_cast<C*>(this);
      if (pC)
        pC->do_C_op();
      std::cout << "\n";
    }
  };
}
