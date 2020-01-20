// Chap7Vdisplay.cpp

#include "Chap7Vdisplay.h"
#include "../Chapter7-Display/Chap7Display.h"
//#include "../Display/Display.h"
#include <vector>
#include <unordered_map>
#include <string>

#ifdef TEST_CHAP7VDISPLAY
int main() {

  displayTitle("Demo Variadic Display Function");

  std::vector<int> vInt{ 1,2,3,4 };
  std::cout << "\n  ";
  print_container(vInt);

  std::unordered_map<int, std::string> mIntStr { {1, "one"}, { 2,"two" }, { 3, "three" }};
  std::cout << "\n  ";
  print_container(mIntStr);

  putline(2);
}
#endif
