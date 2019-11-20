#pragma once
/////////////////////////////////////////////////////////////////////
// DirWalker.h - Use std::filesystem to navigate directory tree    //
// ver 1.0                                                         //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////
/*
 *  Package Operations:
 * ---------------------
 *  Walks directory tree starting from specified root.  Accepts an
 *  application template parameter that provides doDir and doFile
 *  methods to handle discovery of directories and files, respectively.
*
 *  This is a modified version of code provided by Bartlomiej Filipek:
 *  https://www.bfilipek.com/2017/08/cpp17-details-filesystem.html
 *
 *  Code consists of two classes:
 *    template<typename App = void> class DirWalker
 *    class AppDisplay
 *
 *  If you supply the optional AppDisplay class, it is expected to provide
 *  methods doDir and doFile
 *
 *  Required Files:
 * -----------------
 *  DirWalker.h, DirWalker.cpp
 *  DateTime.h, DateTime.cpp
 *
 *  Maintenance History:
 * ----------------------
 *  ver 1.0 : 19 Nov 2019
 *  - first release
 *
*/

#include <filesystem>
#include <set>
#include <string>

/////////////////////////////////////////////////////////////////////
// FileSystem-based dir navigator

namespace Utilities {

  namespace fs = std::filesystem;
  using namespace std::chrono_literals;

  using Patterns = std::set<std::string>;

  template<typename App = void>
  class DirWalker {
  public:
    DirWalker();
    void DisplayDirectoryTree(const fs::path& pathToShow, const Patterns& pats);
    void DisplayDirTree(const fs::path& pathToShow, int level, const Patterns& pats);
    std::unique_ptr<App> app();
  private:
    std::uintmax_t ComputeFileSize(const fs::path& pathToCheck);
    void DisplayFileInfo(
      const std::filesystem::directory_entry& entry,
      std::string& lead,
      std::filesystem::path& filename
    );
    std::unique_ptr<App> pApp_ = nullptr;
  };
}