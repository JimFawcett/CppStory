// STL.cpp

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include "../Chapter7-Display/Chap7Display.h"
//#include "../Display/Display.h"

template<typename T>
void show(T t) {
  for (auto item : t)
    std::cout << "\n  " << item;
}

int main() {

  std::vector<std::string> src{ 
    "first string", "second str", "third collection", "another string" 
  };
  std::vector<std::string> dst;

  std::string s = "string";          // lambda capture

  std::copy_if(
    src.begin(), src.end(),          // range of source to copy
    std::back_inserter(dst),         // insertion iterator push_backs into dst

    [&s](const std::string& item) {  // lambda predicate defines src items to push_back
      if (item.find(s) != std::string::npos) {
        return false;
      }
      return true;
    }
  );
  
  show(dst);
  putline(2);
}
