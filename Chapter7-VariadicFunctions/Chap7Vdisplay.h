#pragma once
// Chap7Vdisplay.h

#include <iostream>

template <template <typename, typename...> class ContainerType,
  typename ValueType, typename... Args>
  void print_container(const ContainerType<ValueType, Args...>& c) {
  for (const auto& v : c) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}

// Implement << for pairs: this is needed to print out mappings where range
// iteration goes over (key, value) pairs.
template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& p) {
  out << "[" << p.first << ", " << p.second << "]";
  return out;
}
