///////////////////////////////////////////////////////////////
// Point.cpp - template class version of point               //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "Point.h"

int main() {

  displayTitle("Point Class Demo");

  Point<double> pt1{ 0.5, 0.0, -0.5 };
  pt1.name("pt1");
  showPoint(pt1);
  putline();

  Point<double> pt2{ 0.5, 1.0, 1.5 };
  pt2.name("pt2");
  showPoint(pt2);
  putline();

  Point<double> pt3{ 0.0, 0.5, 1.5 };
  pt3.name("pt3");
  showPoint(pt3);
  putline();

  Point<double> pt4{ pt3 };
  pt4.name("pt4 is copy of pt3");
  showPoint(pt4);

  Point<double> pt5(3, "pt5");
  pt5 = pt3;
  pt5.name("pt5 assigned from pt3");
  showPoint(pt5);
  putline();
  std::cout << "\n  So Point is a value type";
  putline(2);
}