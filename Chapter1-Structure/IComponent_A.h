#pragma once
///////////////////////////////////////////////////////////////
// IComponent_A.h - delares Component_A contract             //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <memory>

struct IComponent_A {
  virtual ~IComponent_A() {}
  virtual void say() = 0;
};

std::unique_ptr<IComponent_A> createComponent_A(const std::string& id);
