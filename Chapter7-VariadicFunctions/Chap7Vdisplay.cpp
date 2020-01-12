// Chap7Vdisplay.cpp

#include "Chap7Vdisplay.h"
#include "../Display/Display.h"
#include <vector>
#include <unordered_map>
#include <string>

int main() {

  std::vector<int> vInt{ 1,2,3,4 };
  print_container(vInt);

  std::unordered_map<int, std::string> mIntStr { {1, "one"}, { 2,"two" }, { 3, "three" }};
  print_container(mIntStr);

  putline(2);
}