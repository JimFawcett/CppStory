/////////////////////////////////////////////////////////////////////
// STL_DataStructures.cpp - Data Structure for file and path info  //
// ver 1.0                                                         //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////
/*
 *  Package Operations:
 * ---------------------
 *  Uses class:
 *  - DirWalker<App>     - Navigates directory tree from specified root
 *                         calling functions doDir and doFile in instance
 *                         of App class.
 *  - DateTime           - Provides conversions from std::filesystem times
 *  Provides classes:
 *  - FileInfoContainer  - efficiently holds file and path information
 *  - AppCollectFileInfo - Provides receiver of DirWalker file and Dir events
 *
 *  Required Files:
 * -----------------
 *  - STL_DataStructures.cpp
 *  - DirWalker.h, DirWalker.cpp
 *  - DateTime
 *
 *  Maintenance History:
 * ----------------------
 *  ver 1.0 : 20 Nov 2019
 *  - first release
 */

#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <memory>
#include <time.h>
#include <iomanip>
#include "DateTime.h"
#include "DirWalker.h"

namespace CustomContainers {

  enum class Stats { File, Path };

  class FileInfoContainer {
  public:
    // file to path structure
    using File = std::string;
    using Path = std::string;
    using PathSet = std::set<Path>;
    using PathRef = PathSet::iterator;
    using PathRefs = std::vector<PathRef>;
    using FileInfo = std::map<File, PathRefs>;
    using iterator = FileInfo::iterator;
    using PathInfo = FileInfo;

    FileInfoContainer& add(const File& file, const Path& path);
    FileInfoContainer invertFileInfo(FileInfoContainer* pFIC);
    FileInfo fileInfo();
    iterator begin() { return fileInfo_.begin(); }
    iterator end() { return fileInfo_.end(); }
    size_t fileCount();
    size_t pathCount();

  private:
    FileInfo fileInfo_;
    PathSet pathSet_;
    PathInfo pathInfo_;
  };

  FileInfoContainer::FileInfo FileInfoContainer::fileInfo() {
    return fileInfo_;
  }
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

  FileInfoContainer FileInfoContainer::invertFileInfo(FileInfoContainer* pFIC) {
    FileInfoContainer pathInfoContainer_;
    FileInfo fileInfo_ = pFIC->fileInfo();
    for (auto item : fileInfo_) {
      File file = item.first;
      for (auto pathRefItem : item.second) {
        Path path = *pathRefItem;
        pathInfoContainer_.add(path, file);
      }
    }
    return pathInfoContainer_;
  }

  size_t FileInfoContainer::fileCount() {
    return fileInfo_.size();
  }

  size_t FileInfoContainer::pathCount() {
    return pathSet_.size();
  }

  void showFiles(FileInfoContainer& fic, const std::string& msg = "", Stats sts = Stats::File) {
    
    if (msg.size() > 0) {
      std::cout << msg;
    }
    for (auto fileItem : fic) {
      std::cout << "\n  " << fileItem.first;
      for (auto pathItem : fileItem.second) {
        std::cout << "\n    " << *pathItem;
      }
    }
    if (sts == Stats::File) {
      std::cout << "\n\n  number of files: " << fic.fileCount();
      std::cout << "\n  number of paths: " << fic.pathCount();
    }
    else {
      std::cout << "\n\n  number of files: " << fic.pathCount();
      std::cout << "\n  number of paths: " << fic.fileCount();
    }
    std::cout << std::endl;
  }
}

using namespace CustomContainers;

class AppCollectFileInfo
{
public:
  void doDir(const std::string& dirName) {
    currDir_ = dirName;
  }
  void doFile(const std::string& fileName, uintmax_t fileSize, const std::string& time_date) {
    fic_.add(fileName, currDir_);
  }
  FileInfoContainer& fileInfo() {
    return fic_;
  }
private:
  std::string currDir_;
  FileInfoContainer fic_;
};

std::string makeTitle(const std::string& title, char ul = '-') {
  std::string title_ = "\n  " +  title + "\n ";
  title_ += std::string(title.size() + 2, ul);
  return title_;
}

int main() {

  using namespace Utilities;

  FileInfoContainer fic;
  fic.add("file1", "path1").add("file1", "path2");
  fic.add("file2", "path1");
  fic.add("file3", "path3").add("file4", "path2");
  showFiles(fic, makeTitle("simple FileInfo demonstration"));

  DirWalker<AppCollectFileInfo> dw;
  std::set<std::string> patterns{ ".h", ".cpp", ".html" };
  dw.DisplayDirectoryTree("..", patterns);
  std::shared_ptr<AppCollectFileInfo> pInfo = dw.app();
  std::string title = makeTitle("FileInfo from path \"..\"");
  showFiles(pInfo->fileInfo(), title);
  std::cout << std::endl;

  FileInfoContainer pic = fic.invertFileInfo(&(pInfo->fileInfo()));
  std::string title2 = makeTitle("PathInfo from path \"..\"");
  showFiles(pic, title2, Stats::Path);
  std::cout << "\n";


}