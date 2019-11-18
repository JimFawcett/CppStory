/////////////////////////////////////////////////////////////////////
// ToHTML.cpp - convert file, named on command line to web page    //
// ver 1.0                                                         //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////
/*
 * Required Files:
 * ---------------
 *   ToHTML.cpp
 *
 * Maintenance History:
 * --------------------
 * ver 1.0 : 17 Nov 2019
 * - first release
 */

#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

/*---------------------------------------------------------
   Test to see if file to write already exists
  -------------------------------------------------------*/
bool fileExists(const std::string& filename) {
  std::ifstream test(filename);
  if (test.good()) {
    test.close();
    return true;
  }
  test.close();
  return false;
}
/*---------------------------------------------------------
   Read text file into string
   - if open successful read file and return contents 
   - otherwise return empty string
  -------------------------------------------------------*/
std::string fileToString(const std::string& filename) {
  std::ostringstream out("can't open " + filename);
  std::ifstream in;
  in.open(filename, std::ios::in);
  if (in.good()) {
    out.str("");
    out << in.rdbuf();
  }
  in.close();
  return out.str();
}
/*---------------------------------------------------------
   Convert to HTML fragment
   - convert markup chars to escape sequences
   - enclose in <pre></pre> tags
  -------------------------------------------------------*/
std::string webify(const std::string& fileString) {
  std::ostringstream out;
  out << "<pre>";
  for (auto ch : fileString) {
    switch (ch) {
    case '<':
      out << "&lt;";
      break;
    case '>':
      out << "&gt;";
      break;
    case '&':
      out << "&amp;";
      break;
    default:
      out << ch;
    }
  }
  out << "</pre>";
  return out.str();
}
/*--------------------------------------------------------- 
   make destination file name 
   - insert count before src file ext
   - append ".html"
  -------------------------------------------------------*/
std::string makeName(
  const std::string& baseName, 
  size_t count, 
  const std::string& ext = ".html"
) 
{
  std::string newName = baseName;
  size_t pos = newName.find_last_of('.');
  if (pos < newName.size()) {
    newName.insert(pos, std::to_string(count));
  }
  else {
    newName += std::to_string(count);
  }
  return newName + ext;
}
/*---------------------------------------------------------
   Write webified file contents to computed file name
   - returns name of converted file
   - returned name is empty if conversion fails
  -------------------------------------------------------*/
std::string makeWebPage(const std::string& srcFileName) {
  size_t count = 0;
  std::string fileName;
  do {
    std::ofstream out;
    ++count;
    fileName = makeName(srcFileName, count);
    if (fileExists(fileName))
      continue;
    out.open(fileName);
    if (out.good()) {
      std::string fileString = fileToString(srcFileName);
      std::string webified = webify(fileString);
      out << webified;
      out.close();
      break;
    }
    if (count > 10) {
      fileName = "";
      break;
    }
  } while (true);
  return fileName;
}

int main(int argc, char* argv[]) {
 
  if (argc != 2) {
    std::cout << "\n  please enter file to convert on command line\n\n";
    return 1;
  }

  std::string name = argv[1];
  std::string convertedFileName = makeWebPage(name);
  if (convertedFileName.size() > 0) {
    std::cout << "\n  converted \"" << name;
    std::cout << " to \"" << convertedFileName << "\"\n\n";
    return 0;
  }
  else {
    std::cout << "\n  can't convert file \"" << name << "\"";
    return 1;
  }
}