#pragma once
// Chap7TMP_Application.h

template<typename T>
class Wrapper {
  Wrapper();
  template<class R>
  Wrapper& select(R r) const;
  template<class C>
  Wrapper& sort(C c);
  template<class P>
  Wrapper& where(P p);
  Wrapper& distinct();
  template<class R1, class R2>
  Wrapper& join(R1 r1, R2 r2);
  template<class V>
  bool contains(const V& v) const;
  size_t count();
};