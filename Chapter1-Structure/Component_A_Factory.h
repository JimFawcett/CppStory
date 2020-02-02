#pragma once
///////////////////////////////////////////////////////////////
// Component_A_Factory.h - implements creational function    //
//                                                           //
// Jim Fawcett, https://JimFawcett.github.io, Feb 2020       //
///////////////////////////////////////////////////////////////


#include <memory>
#include "IComponent_A.h"

inline std::unique_ptr<IComponent_A> createComponent_A(const std::string& id);

