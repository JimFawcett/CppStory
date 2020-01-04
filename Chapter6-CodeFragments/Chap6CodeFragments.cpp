// Chap6CodeFragments.cpp

#include <iostream>
#include "../Display/Display.h"

/*-----------------------------------------
   Classes used for Template Parameters
-----------------------------------------*/

class P0 {
public:
  void doProc() {
    std::cout << "\n  doing P0 processing";
  }
};

class Q0 {
public:
  void doProc() {
    std::cout << "\n  doing Q0 processing";
  }
};

class P1 {
public:
  void doProc() {
    std::cout << "\n  doing P1 processing";
  }
};

class Q1 {
public:
  void doProc() {
    std::cout << "\n  doing Q1 processing";
  }
};

/*-----------------------------------------
   Class used for generic operations
-----------------------------------------*/

template<typename P = P1, typename Q = Q1>
class X {
public:
  X() {
    std::cout << "\n  Generic X Template";
  }
  void doProc() {
    p_.doProc();
    q_.doProc();
  }
private:
  P p_;
  Q q_;
};

/*-----------------------------------------
   Class specialized to use Q1
-----------------------------------------*/

template<typename P>
class X<P, Q1> {
public:
  X() {
    std::cout << "\n  X Template partially specialized for Q1";
  }
  void doProc() {
    p_.doProc();
    q_.doProc();
  }
private:
  P p_;
  Q1 q_;
};

/*-----------------------------------------
   Class specialized to use P1
-----------------------------------------*/

template<typename Q>
class X<P1, Q> {
public:
  X() {
    std::cout << "\n  X Template partially specialized for P1";
  }
  void doProc() {
    p_.doProc();
    q_.doProc();
  }
private:
  P1 p_;
  Q q_;
};

template<>
class X<P1, Q1> {
public:
  X() {
    std::cout << "\n  X Template fully specialized for P1 and Q1";
  }
  void doProc() {
    p_.doProc();
    q_.doProc();
  }
private:
  P1 p_;
  Q1 q_;
};

int main() {

  displayDemo("-- generic processing --");
  X<P0, Q0> x1;
  x1.doProc();

  displayDemo("\n  -- using default template arguments --");
  X<> x2;
  x2.doProc();

  displayDemo("\n  -- Using full specialization --");
  X<P1, Q1> x3;
  x3.doProc();

  displayDemo("\n  -- Using specialization for P1 --");
  X<P1, Q0> x4;
  x4.doProc();

  displayDemo("\n  -- Using specialization for Q1 --");
  X<P0, Q1> x5;
  x5.doProc();

  putline(2);
}
