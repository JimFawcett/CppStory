// Chap6QuickExample.cpp

#include <string>
#include <vector>
#include <iostream>
#include <locale>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

struct StrUtils {

  /*-----------------------------------------
     remove whitespace from front and back
     of string argument
     - does not remove newlines
  */
  std::string trim(const std::string& toTrim)
  {
    if (toTrim.size() == 0)
      return toTrim;
    std::string temp;
    std::locale loc;
    typename
      std::string::const_iterator iter =
      toTrim.begin();
    while (
      isspace(*iter, loc) && *iter != '\n'
      )
    {
      if (++iter == toTrim.end())
      {
        break;
      }
    }
    for (; iter != toTrim.end(); ++iter)
    {
      temp += *iter;
    }
    typename
      std::string::reverse_iterator riter;
    size_t pos = temp.size();
    for (
      riter = temp.rbegin();
      riter != temp.rend();
      ++riter
      )
    {
      --pos;
      if (
        !isspace(*riter, loc)
        || *riter == '\n'
        )
      {
        break;
      }
    }
    if (0 <= pos && pos < temp.size())
      temp.erase(++pos);
    return temp;
  }

  /*---------------------------------------------
    split sentinel separated strings into a
    vector of trimmed strings
  */
  template <typename T>
  std::vector<std::string> split(
    const std::string& toSplit,
    T splitOn = ','
  )
  {
    std::vector<std::string> splits;
    std::string temp;
    typename
      std::string::const_iterator iter;
    for (
      iter = toSplit.begin();
      iter != toSplit.end();
      ++iter
      )
    {
      if (*iter != splitOn)
      {
        temp += *iter;
      }
      else
      {
        splits.push_back(trim(temp));
        temp.clear();
      }
    }
    if (temp.length() > 0)
      splits.push_back(trim(temp));
    return splits;
  }
};
class stringEx :
  public std::string, private StrUtils {
public:
  stringEx() {}
  stringEx(const std::string& str)
    : std::string(str) {}
  stringEx(const char* pStr)
    : std::string(pStr) {}
  std::string trim() {
    StrUtils::trim(*this);
  }
  std::vector<std::string>
    splits(char splitOn = ',') {
    return StrUtils::split(*this, splitOn);
  }
};

/*--- show collection of string splits --------*/

void showSplits(
  const std::vector<std::string>& splits,
  std::ostream& out = std::cout
)
{
  out << "\n";
  for (auto item : splits)
  {
    if (item == "\n")
      out << "\n--" << "newline";
    else
      out << "\n--" << item;
  }
  out << "\n";
}

using Splits = std::vector<std::string>;

int main() {
  displayDemo("-- SuperString demo --\n");
  std::string arg = "one, ";
  arg += "this is two, ";
  arg += "and finally three";
  stringEx superStr{ arg };
  std::cout << "\n  superStr has the value: "
    << superStr;
  Splits splits = superStr.splits();
  std::cout << "\n  superStr splits are:";
  for (auto split : splits) {
    std::cout << "\n    " << split;
  }
  putline(2);
}
