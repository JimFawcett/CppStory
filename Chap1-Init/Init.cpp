// Init.cpp

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
  displayDemo("-- initialize integers --");
  int i1 = 1;
  int i2(2);
  int i3 = { 3 };
  int i4{ 4 };
  display({ i1, i2, i3, i4 });  // 1, 2, 3, 4

  displayDemo("\n  -- initialize strings --");
  std::string s1 = "one";
  std::string s2("two");
  std::string s3 = { "three" };
  std::string s4{ "four" };  // C++17
  display({ s1, s2, s3, s4 });

  displayDemo("\n  -- initialize doubles --");
  double pi1 = 3.1415927;
  double pi2(pi1 * 2);
  double pi3 = { pi1 * 3 };
  double pi4{ pi1 * 4 };
  display({ pi1, pi2, pi3, pi4 });

  displayDemo("\n  -- initialize std::pairs --");
  std::pair<int, double> pair1 = std::pair(1, 1.5);
  std::pair<int, double> pair2(std::pair<int, double>(2, 2.5));
  std::pair<int, double> pair3 = { 3, 3.5 };
  std::pair<int, double> pair4{ 4, 4.5 };
  display({ pair1, pair2, pair2, pair4 });

  displayDemo("\n  -- initialize std::vector --");
  std::vector<int> iVec{ 1, 2, 3, 4 };
  std::vector<double> dVec{ -0.5, 0, 0.5, 1.5 };
  std::vector<std::pair<int, double>> pVec{ pair1, pair2, pair3, pair4 };
  vDisplay(iVec, dVec, pVec);

  displayDemo("\n  -- initialize std::unordered_maps --");
  std::unordered_map<std::string, int> umap1 = { {"one", 1} };
  std::unordered_map<std::string, int> umap2{ { "two", 2}, {"three", 3} };
  display({ umap1, umap2 });

  displayDemo("\n  -- initialize pointers and references --");
  double* pDouble{ &pi1 };  
  display({ pDouble }, " is double*"); 
  display({ *pDouble }, " is *(double*)");
  double& rDouble{ pi1 };
  display({ rDouble }, " is double&");

  displayDemo("\n  -- initialize smart pointers --");
  std::unique_ptr<double> uPtr1{ std::make_unique<double>(pi1) };
  std::unique_ptr<double> uPtr2{ std::move(uPtr1) };
  //display({ *uPtr1 }, " is *unique_ptr<double>");  // throws because uPtr1 is now invalid
  display({ *uPtr2 }, " is *unique_ptr<double>");
  std::shared_ptr<double> sPtr1{ std::make_shared<double>(pi2) };
  std::shared_ptr<double> sPtr2{ sPtr1 };
  display({ *sPtr1 }, " is *shared_ptr<double>");
  display({ *sPtr2 }, " is *shared_ptr<double>");
}
int main()
{
  displayTitle("Type Value Initialization");
  demoInit();
  std::cout << "\n\n";
}