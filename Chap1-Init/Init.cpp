/////////////////////////////////////////////////////////////////////////
// Init.cpp - explore initialization for common C++ types              //
//                                                                     //
// Jim Fawcett, Emeritus Teaching Professor, EECS, Syracuse University //
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <unordered_map>
#include <cstddef>
#include "../Display/Display.h"

/*---- demonstrate initialization ----*/

void demoInit()
{
  displayDemo("-- initializer_list type --");
  std::initializer_list<int> ilInt{ 1, 2, 3 };
  std::cout << "\n ";
  for (auto item : ilInt)
  {
    std::cout << " " << item;
  }
  std::cout << std::endl;

  displayDemo("-- initialize integers --");
  int i1 = 1;      // classic initialization
  int i2(2);       // classic, but less frequently used
  int i3 = { 3 };  // 
  int i4{ 4 };     // preferred initialization syntax
  displayValues({ i1, i2, i3, i4 });  // 1, 2, 3, 4

  displayDemo("\n  -- initialize strings --");
  std::string s1 = "one";
  std::string s2("two");
  std::string s3 = { "three" };
  std::string s4{ "four" };  // C++17
  displayValues({ s1, s2, s3, s4 });

  displayDemo("\n  -- initialize doubles --");
  double pi1 = 3.1415927;
  double pi2(pi1 * 2);
  double pi3 = { pi1 * 3 };
  double pi4{ pi1 * 4 };
  displayValues({ pi1, pi2, pi3, pi4 });

  displayDemo("\n  -- initialize std::pairs --");
  std::pair<int, double> pair1 = std::pair(1, 1.5);
  std::pair<int, double> pair2(std::pair<int, double>(2, 2.5));
  std::pair<int, double> pair3 = { 3, 3.5 };
  std::pair<int, double> pair4{ 4, 4.5 };
  displayValues({ pair1, pair2, pair2, pair4 });

  displayDemo("\n  -- initialize std::vector --");
  std::vector<int> iVec{ 1, 2, 3, 4 };
  std::vector<double> dVec{ -0.5, 0, 0.5, 1.5 };
  std::vector<std::pair<int, double>> pVec{ pair1, pair2, pair3, pair4 };
  displayValues(iVec, dVec, pVec);

  displayDemo("\n  -- initialize std::unordered_maps --");
  std::unordered_map<std::string, int> umap1 = { {"one", 1} };
  std::unordered_map<std::string, int> umap2{ { "two", 2}, {"three", 3} };
  displayValues({ umap1, umap2 });

  displayDemo("\n  -- initialize pointers and references --");
  double* pDouble{ &pi1 };  
  displayValues({ pDouble }, " is double*");
  displayValues({ *pDouble }, " is *(double*)");
  double& rDouble{ pi1 };
  displayValues({ rDouble }, " is double&");

  displayDemo("\n  -- initialize smart pointers --");
  std::unique_ptr<double> uPtr1{ std::make_unique<double>(pi1) };
  std::unique_ptr<double> uPtr2{ std::move(uPtr1) };
  //display({ *uPtr1 }, " is *unique_ptr<double>");  // throws because uPtr1 is now invalid
  displayValues({ *uPtr2 }, " is *unique_ptr<double>");
  std::shared_ptr<double> sPtr1{ std::make_shared<double>(pi2) };
  std::shared_ptr<double> sPtr2{ sPtr1 };
  displayValues({ *sPtr1 }, " is *shared_ptr<double>");
  displayValues({ *sPtr2 }, " is *shared_ptr<double>");

  displayDemo("\n  -- structure bindings --");
  auto [i5, i6] = std::pair{ 5, 6 };
  displayValues({ i5, i6 });
  auto [d, i, s] = std::tuple<double, int, std::string>{ 2.5, 3, "four" };
  displayValues(d, i, s);
  
  /* initializer list must have all values of same type */
  // displayValues({ d, i, s });
}
int main()
{
  displayTitle("Type Value Initialization");
  demoInit();
  std::cout << "\n\n";
}