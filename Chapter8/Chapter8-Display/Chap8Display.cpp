// Chap7Display.cpp

#include <tuple>
#include "Chap8Display.h"

int main() {

  displayTitle("Testing Chap7Display");

  displayDemo("--- displayTuple ---\n  ");

  std::tuple tp{ 1, 2.5 , 'a', "a string" };
  displayTuple(tp);
  putline(1, "  ");
  displayTuple(std::tuple{ 1, 2.5 , 'a', "a string" });

  displayDemo("\n  --- displayValues ---\n  ");
  displayValues(
    1, 3, 4.5, "a string", std::pair{ 1, "one" }
  );
  displayValues(
    std::vector<int>{-1, 0, 1}, 
    std::unordered_map<int, std::string>{
      {1, "one"}, { 2, "two" }
    }
  );
  displayValues({ 1.0, 1.5, 2.0, 2.5 });

  displayDemo("\n  --- displayType ---\n  ");
  displayType(1);
  displayType(2.5);
  displayType('z');
  displayType("another string");

  displayDemo("\n  --- displayOnlyType ---\n  ");
  displayOnlyType(1);
  displayOnlyType(2.5);
  displayOnlyType('z');
  displayOnlyType("another string");

  displayDemo("\n  --- displayTypeArgument ---\n  ");
  displayTypeArgument<int>();
  displayTypeArgument<double>();
  displayTypeArgument<char>();
  displayTypeArgument<std::string>();

  putline(2);
}