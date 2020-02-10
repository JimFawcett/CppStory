#pragma once
///////////////////////////////////////////////////////////////
// Component_B.h - delares Component_B operations            //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include "IComponent_A.h"
#include <memory>

class Component_B {
public:
  Component_B();
  ~Component_B();
  Component_B(const Component_B&) = delete;
  Component_B& operator=(const Component_B&) = delete;
  void say();
private:
  std::unique_ptr<IComponent_A> pA_;
};