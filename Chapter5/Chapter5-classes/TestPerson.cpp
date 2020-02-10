// TestPerson.cpp

#include "../Chapter1-Survey/IPerson.h"

int main()
{
  using namespace Elementary;

  std::unique_ptr<IPerson> pJack = createPerson({ "Jack", "unemployed", 35 });
}