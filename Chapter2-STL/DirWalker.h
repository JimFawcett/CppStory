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
#include <memory>

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
    std::unique_ptr<App>& app();
  private:
    std::uintmax_t ComputeFileSize(const fs::path& pathToCheck);
    void DisplayFileInfo(
      const std::filesystem::directory_entry& entry,
      std::string& lead,
      std::filesystem::path& filename
    );
    std::unique_ptr<App> pApp_ = nullptr;
  };
  /*-------------------------------------------------------------------
 *  size of file in bytes
*/
  template<typename App>
  std::uintmax_t DirWalker<App>::ComputeFileSize(const fs::path& pathToCheck)
  {
    if (fs::exists(pathToCheck) && fs::is_regular_file(pathToCheck))
    {
      auto err = std::error_code{};
      auto filesize = fs::file_size(pathToCheck, err);
      if (filesize != static_cast<uintmax_t>(-1))
        return filesize;
    }
    return static_cast<uintmax_t>(-1);
  }
  /*-------------------------------------------------------------------
   *  helper function for file time evaluation
   *
   *  Converts chrono timepoint to time_t structure
  */
  template<typename TP>
  std::time_t to_time_t(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(
      tp - TP::clock::now() + system_clock::now()
      );
    return system_clock::to_time_t(sctp);
  }
  /*-------------------------------------------------------------------
   *  helper function to remove gratuitous quotes and newlines from fs objects
  */
  inline std::string stripChar(std::string src, char ch) {
    src.erase(std::remove(src.begin(), src.end(), ch));
    return src;
  }
  /*-------------------------------------------------------------------
   *  Constructor initializes application object pointer
   */
  template<typename App>
  DirWalker<App>::DirWalker() {
    if constexpr (!std::is_void<App>::value) {
      pApp_ = std::unique_ptr<App>(new App);
    }
    else {
      pApp_ = nullptr;
    }
  }
  /*-------------------------------------------------------------------
   *  return pointer to application instance
   */
  template<typename App>
  std::unique_ptr<App>& DirWalker<App>::app() {
    return pApp_;
  }
  /*-------------------------------------------------------------------
   * display file name, size, and time-date
   *
   *  Uses help from DateTime utility
  */
  template<typename App>
  void DirWalker<App>::DisplayFileInfo(
    const std::filesystem::directory_entry& entry,
    std::string& lead,
    std::filesystem::path& filename
  )
  {
    Utilities::DateTime dt;
    auto ftime = fs::last_write_time(entry);
    const std::time_t cftime = to_time_t(ftime);
    std::cout << "    " << std::setw(26) << stripChar(filename.u8string(), '"') << ", "
      << std::setw(6) << ComputeFileSize(entry);
    std::cout << ",  " << dt.ctime(&cftime);
  }
  /*-------------------------------------------------------------------
   *  Recursive directory tree walk
   */
  template<typename App>
  void DirWalker<App>::DisplayDirTree(const fs::path& pathToShow, int level, const Patterns& pats)
  {
    std::vector<std::pair<fs::directory_entry, size_t>> dirs;
    std::vector<std::tuple<fs::directory_entry, std::string, fs::path>> files;

    size_t fileCount = 0;
    if (fs::exists(pathToShow) && fs::is_directory(pathToShow))
    {
      auto lead = std::string(level * 3, ' ');
      for (const auto& entry : fs::directory_iterator(pathToShow))
      {
        auto filename = entry.path().filename();
        auto ext = filename.extension();
        if (fs::is_directory(entry.status())) {
          dirs.push_back({ entry, level + 1 });
        }
        else if (fs::is_regular_file(entry.status())) {
          if (pats.size() == 0 || pats.find(ext.u8string()) != pats.end()) {
            files.push_back({ entry, lead, filename });
            ++fileCount;
          }
        }
        else {
          if (pats.size() == 0 || pats.find(ext.u8string()) != pats.end()) {
            files.push_back({ entry, lead, filename });
            ++fileCount;
          }
        }
      }
      for (auto dir : dirs) {
        if (fileCount > 0) {
          auto currDir = fs::absolute(pathToShow);
          std::string dirName = stripChar(currDir.u8string(), '"');
          if constexpr (std::is_void<App>::value) {
            std::cout << "\n  " << dirName << "\n";
          }
          else {
            pApp_->doDir(dirName);
          }
          for (auto file : files) {
            auto [ent, ld, fn] = file;
            if constexpr (std::is_void<App>::value) {
              DisplayFileInfo(ent, ld, fn);
            }
            else {
              Utilities::DateTime dt;
              auto ftime = fs::last_write_time(ent);
              const std::time_t cftime = to_time_t(ftime);
              std::string time_date = dt.ctime(&cftime);
              time_date = stripChar(time_date, '\n');
              uintmax_t fileSize = ComputeFileSize(ent);
              std::string funName = stripChar(fn.u8string(), '"');
              pApp_->doFile(funName, fileSize, time_date);
            }
          }
          files.clear();
          fileCount = 0;
        }
        auto [de, sz] = dir;
        DisplayDirTree(de, sz, pats);
      }
    }
  }

  /*-------------------------------------------------------------------
   *  Directory tree walk starter
   */
  template<typename App>
  void DirWalker<App>::DisplayDirectoryTree(const fs::path& pathToShow, const Patterns& pats) {

    DisplayDirTree(pathToShow, 1, pats);
  }


}