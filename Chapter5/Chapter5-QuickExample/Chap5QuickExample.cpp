// Chap5QuickExample.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

class Logger {
public:
  Logger() : pStream_(nullptr) {}
  Logger(std::ostream* pStr) : pStream_(pStr) {}
  Logger(const Logger& logger) = delete;
  ~Logger() {
    std::ofstream* pFStrm = 
      dynamic_cast<std::ofstream*>(pStream_);
    if (pFStrm != nullptr)
      pFStrm->close();
  }
  Logger& operator=(const Logger& logger) 
    = delete;
  void open(const std::string& fileName) {
    std::ofstream* pFStrm =
      dynamic_cast<std::ofstream*>(pStream_);
    if (pFStrm != nullptr)
      pFStrm->open(fileName);
  }
  void write(const std::string& msg) {
    (*pStream_) << prefix_ << msg;
  }
private:
  std::string prefix_ = "\n  ";
  std::ostream* pStream_;
};

std::unique_ptr<std::ofstream> 
makeOutFileStream(const std::string& fileName) {
  std::unique_ptr<std::ofstream> 
    pStrm(new std::ofstream(fileName));
  return pStrm;
}

std::unique_ptr<std::ifstream> 
makeInFileStream(const std::string& fileName) {
  std::unique_ptr<std::ifstream> 
    pStrm(new std::ifstream(fileName));
  return pStrm;
}

int main() {

  displayDemo("-- simple logger --");

  std::string fileName = "log.txt";
  /*---------------------------------------------
     Create anonymous scope for logging so
     logger destructor will be called before
     trying to open log file.
  */
  {
    auto pOStrm = makeOutFileStream(fileName);
    if (!pOStrm->good()) {
      std::cout << "\n  couldn't open \"" 
                << fileName << " for writing\n\n";
      return 1;
    }
    Logger logger(pOStrm.get());
    logger.write("first log item");
    logger.write("second log item");
    logger.write("last log item");
  }
  auto pIStrm = makeInFileStream(fileName);
  if (!pIStrm->good())
  {
    std::cout << "\n  couldn't open \"" 
              << fileName << " for reading\n\n";
    return 1;
  }
  std::cout << "\n  " << pIStrm->rdbuf();
  putline(2);
}
