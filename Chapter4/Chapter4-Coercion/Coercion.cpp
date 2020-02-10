// Coercion.cpp

#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

void demoCoercion() {

  displayDemo("--- DemoCoercion ---");

  long int li{ 5 };
  int i = short int{ 2 };
  long long int lli{ 2L };
  double d{ 3.0F };
  displayValues(li, i, lli, d);
  displayType(li);
  displayType(i);
  displayType(lli);
  displayType(d);
}

int main() {
  demoCoercion();
  putline(2);
}