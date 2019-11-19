// STL_DataStructures.cpp

#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <time.h>
#include <iomanip>
#include "../Chapter2-STL/DateTime.h"

namespace CustomContainers {

  class FileInfoContainer {
  public:
    // file to path structure
    using File = std::string;
    using Path = std::string;
    using PathSet = std::set<Path>;
    using PathRef = PathSet::iterator;
    using PathRefs = std::vector<PathRef>;
    using FileInfo = std::unordered_map<File, PathRefs>;
    using iterator = FileInfo::iterator;

    // path to file structure
    using FileList = std::vector<File>;
    using PathList = std::map<Path, FileList>;

    FileInfoContainer& add(const File& file, const Path& path);
    PathList invertFileInfo();
    iterator begin() { return fileInfo_.begin(); }
    iterator end() { return fileInfo_.end(); }
    size_t fileCount();
    size_t pathCount();

  private:
    FileInfo fileInfo_;
    PathSet pathSet_;
  };

  using FIC = FileInfoContainer;
  FileInfoContainer& FileInfoContainer::add(const FIC::File& file, const FIC::Path& path) {
    auto prPS = pathSet_.insert(path);
    auto iter = fileInfo_.find(file);
    if (iter == fileInfo_.end()) {
      PathRefs pr{ prPS.first };
      fileInfo_[file] = pr;
    }
    else {
      fileInfo_[file].push_back(prPS.first);
    }
    return *this;
  }

  FileInfoContainer::PathList FileInfoContainer::invertFileInfo() {
    return PathList();
  }

  size_t FileInfoContainer::fileCount() {
    return fileInfo_.size();
  }

  size_t FileInfoContainer::pathCount() {
    return pathSet_.size();
  }

  void showFiles(FileInfoContainer& fic) {
    for (auto fileItem : fic) {
      std::cout << "\n  " << fileItem.first;
      for (auto pathItem : fileItem.second) {
        std::cout << "\n    " << *pathItem;
      }
    }
    std::cout << "\n\n  number of files: " << fic.fileCount();
    std::cout << "\n  number of paths: " << fic.pathCount();
  }
}

/////////////////////////////////////////////////////////////////////
// FileSystem-based dir navigator

namespace fs = std::filesystem;
using namespace std::chrono_literals;

using Patterns = std::set<std::string>;

/*-------------------------------------------------------------------
 *  size of file in bytes
*/
std::uintmax_t ComputeFileSize(const fs::path& pathToCheck)
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
 *  helper function to remove gratuitous quotes from fs objects
*/
std::string stripQuotes(std::string src) {
  src.erase(std::remove(src.begin(), src.end(), '"'));
  return src;
}
/*-------------------------------------------------------------------
 * display file name, size, and time-date
 *
 *  Uses help from DateTime utility
*/
void DisplayFileInfo(
  const std::filesystem::directory_entry& entry, 
  std::string& lead, 
  std::filesystem::path& filename
)
{
  Utilities::DateTime dt;
  auto ftime = fs::last_write_time(entry);
  const std::time_t cftime = to_time_t(ftime);
  std::cout << "    " << std::setw(26) << stripQuotes(filename.u8string()) << ", "
    << std::setw(6) << ComputeFileSize(entry);
  std::cout << ",  " << dt.ctime(&cftime);
}
/*-------------------------------------------------------------------
 *  Recursive directory tree walk
 */
void DisplayDirTree(const fs::path& pathToShow, int level, const Patterns& pats)
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
        std::cout << "\n  " << stripQuotes(currDir.u8string()) << "\n";
        for (auto file : files) {
          auto [ent, ld, fn] = file;
          DisplayFileInfo(ent, ld, fn);
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
void DisplayDirectoryTree(const fs::path& pathToShow, const Patterns& pats) {

  DisplayDirTree(pathToShow, 1, pats);
}

int main() {
  using namespace CustomContainers;
  
  FileInfoContainer fic;
  fic.add("file1", "path1").add("file1", "path2");
  fic.add("file2", "path1");
  fic.add("file3", "path3").add("file4", "path2");

  showFiles(fic);
  std::cout << "\n";

  Patterns pats;
  pats.insert(".html");
  pats.insert(".h");
  pats.insert(".cpp");
  DisplayDirectoryTree("..", pats);
  std::cout << "\n\n";
}