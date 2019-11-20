/////////////////////////////////////////////////////////////////////
// DirWalker.cpp - Use std::filesystem to navigate directory tree  //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <chrono>
#include <time.h>
#include <iomanip>
#include "DateTime.h"
#include "DirWalker.h"

/////////////////////////////////////////////////////////////////////
// FileSystem-based dir navigator

using namespace Utilities;

/////////////////////////////////////////////////////////////////////
// AppDisplay
// - demonstration display class for DirWalker

struct AppDisplay {
  void doDir(const std::string& dirName) {
    std::cout << "\n\n  " << dirName;
  }
  void doFile(const std::string& fileName, uintmax_t fileSize, const std::string& time_date) {
    std::cout << "\n    " << fileName << ", " << fileSize << ", " << time_date;
  }
};

#ifdef TEST_DIRWALKER

int main() {

  std::cout << "\n  Demonstrate DirWalker<App>";
  std::cout << "\n ============================";
  Patterns pats;
  pats.insert(".html");
  pats.insert(".h");
  pats.insert(".cpp");
  DirWalker<AppDisplay> dw;
  dw.DisplayDirectoryTree("..", pats);
  std::cout << "\n\n";
}

#endif
