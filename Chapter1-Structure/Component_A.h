#pragma once
///////////////////////////////////////////////////////////////
// Component_A.h - declares Component_A operations           //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "IComponent_A.h"
#include <string>

class Component_A : public IComponent_A {
public:
  virtual ~Component_A();
  Component_A(const std::string& id = "unknown");
  Component_A(const Component_A& comp_a);
  Component_A& operator=(const Component_A& comp_a);
  virtual void say() override;
private:
  std::string id_;
};
