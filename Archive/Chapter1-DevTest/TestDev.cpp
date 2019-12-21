// TestDev.cpp

#include "../Chapter1-Dev/Dev.h"
#include "../Chapter1-Person/PersonDisplay.h"

int main() {

  using namespace Elementary;
  Person Jack({ "Jack", "Retired early", 35 });
  checkedDisplay(Jack);
  Jack.age(36);
  Jack.occupation("ran out of money - pumping gas");
  checkedDisplay(Jack);

  Dev Joe;
  IDev::Projects janeProjs{ "Testla navigation view", "Python side project" };
  Dev Jane({ { "Jane", "UI developer", 28 }, "MSCE Syracuse Univ", "B1-14", janeProjs });
}
