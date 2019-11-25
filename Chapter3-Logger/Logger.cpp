///////////////////////////////////////////////////////////////////////
// Logger.cpp - send log messages to multiple current std::ostreams  //
// ver 1.0                                                           //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University     //
///////////////////////////////////////////////////////////////////////

#include <string>
#include "Logger.h"

int main() {

  displayTitle("Testing Logger");
  using namespace Utilities;

  Logger<std::string> logger("test");
  logger.add(makeStream("test.log"));
  logger.add(makeStream("does not exist"));
  logger.prefix("  ");
  logger.head();
  logger.prefix("");
  logger.write("\n  Hi ").write("there ");
  logger.write("from Logger.cpp");
  logger.write("\n");
  logger.waitForWrites();

  logger.write("\n  setting level = results");
  logger.level(Level::results);
  logger.write("\n  a debug msg", Level::debug);
  logger.write("\n  a demo", Level::demo);
  logger.write("\n  a result", Level::results);
  logger.waitForWrites();

  logger.write("\n  setting level = demo");
  logger.level(Level::demo);
  logger.write("\n  a debug msg", Level::debug);
  logger.write("\n  a demo", Level::demo);
  logger.write("\n  a result", Level::results);
  logger.waitForWrites();

  logger.write("\n  setting level = debug");
  logger.level(Level::debug);
  logger.write("\n  a debug msg", Level::debug);
  logger.write("\n  a demo", Level::demo);
  logger.write("\n  a result", Level::results);
  logger.waitForWrites();

  logger.write("\n  setting level = results & demo");
  logger.level(Level::results + Level::demo);
  logger.write("\n  a debug msg", Level::debug);
  logger.write("\n  a demo", Level::demo);
  logger.write("\n  a result", Level::results);
  logger.waitForWrites();
  
  ILogger<std::string, 0>& logInstance = makeLogger<std::string, 0>();
  logInstance.add(makeStream("staticlog.log"));
  logInstance.head("test logger factory");
  logInstance.write("log msg #1").write("log msg #2");
  
  ILogger<std::string, 0>& logInstance2 = makeLogger<std::string, 0>();
  logInstance2.head("test 2nd instance of logger factory");
  logInstance2.write("log2 msg #1").write("log2 msg #2");
  logInstance2.write("log2 msg #3").write("log2 msg #4");

  const auto& logFactory = 
    []()->ILogger<std::string,0>& { 
      return makeLogger<std::string, 0>(); 
  };
  logFactory().write("\n  using makeLogger");

  logger.wait();
  logInstance.write("\n  done waiting for logger");
  logInstance.wait();
  putline(2);
}