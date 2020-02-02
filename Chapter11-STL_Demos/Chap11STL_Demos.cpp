// Chap11STL_Demos.cpp

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include "../Chapter8-Display/Chap8Display.h"

template<typename Cont, typename Op>
void doProc(Cont c, Op op) {
  std::for_each(c.begin(), c.end(), op);
}

/////////////////////////////////////////////////////
// wasn't able to get this to work yet
//
//template<typename Cont, typename Algo, typename Op>
//void doProc(Cont c, Algo algo, Op op) {
//  algo(c.begin(), c.end(), op);
//}

template<typename V>
auto op = [](V v) {
  static bool first = true;
  if (first) {
    std::cout << "\n  " << v;
    first = false;
  }
  else {
    std::cout << ", " << v;
  }
};

template<typename V>
class Op {
public:
  void operator()(V v) {
    if (first) {
      std::cout << "\n  " << v;
      first = false;
    }
    else {
      std::cout << ", " << v;
    }
  }
private:
  bool first = true;
};

template<typename C>
bool contains(C c, typename C::value_type v) {
  typename C::iterator iter = std::find(c.begin(), c.end(), v);
  return iter != c.end();
}

template<typename C>
void show(C& c) {
  std::cout << "  ";
  for_each(c.begin(), c.end(), Op<typename C::value_type>());
}

template<typename T>
using Vec = std::vector<T>;

template<typename T>
using Lst = std::list<T>;

template<typename T>
using vecIterator = typename std::vector<T>::iterator;

template<typename C>
struct Collection {
  Collection(C& c, Op<typename C::value_type> op_) : op(op_) {
    first = c.begin();
    last = c.end();
  }
  typename C::iterator first;
  typename C::iterator last;
  Op<typename C::value_type> op;
};

template<typename C>
void foreach(Collection<C> rng) {
  std::for_each(rng.first, rng.last, rng.op);
}


int main() {

  displayDemo("-- traditional algo use --");
  Vec<int> vecInt{ 1, 2, 3, 4, 5 };
  std::for_each(vecInt.begin(), vecInt.end(), Op<int>());

  displayDemo("\n  -- using generic synonyms --");
  Collection<Vec<int>> rVI(vecInt, Op<int>());
  std::for_each(rVI.first, rVI.last, rVI.op);
  foreach(rVI);

  displayDemo("\n  -- using synonyms --");
  auto first1 = vecInt.begin();
  auto last1 = vecInt.end();
  auto rng1 = std::pair{ first1, last1 };
  auto shop1 = Op<int>();
  auto forEachOne1 = [](decltype(first1) f, decltype(last1) l, decltype(shop1) s) {
    for_each(f, l, s);
  };
  forEachOne1(first1, last1, shop1);

  Lst<double> lstDbl{ 1.0, -0.5, 0.0, 0.5 };
  auto first2 = lstDbl.begin();
  auto last2 = lstDbl.end();
  auto rng2 = std::pair{ first2, last2 };
  auto shop2 = Op<double>();
  auto forEachOne2 = [](decltype(first2) f, decltype(last2) l, decltype(shop2) s) {
    for_each(f, l, s);
  };
  forEachOne2(rng2.first, rng2.second, shop2);


  displayDemo("\n  -- all the rest --");
  int val = 3;
  std::cout << std::boolalpha;
  std::cout << "\n  vecInt contains " << val << ": " << contains(vecInt, val);
  vecIterator<int> iter = std::find(vecInt.begin(), vecInt.end(), val);
  std::cout << "\n  found " << val << " at location " << iter - vecInt.begin();
  val = 0;
  std::cout << "\n  vecInt contains " << val << ": " << contains(vecInt, val);

  displayDemo("\n  -- copy with ostream_inserter --");
  auto outIter = std::ostream_iterator<int>(std::cout, " ");
  putline(1, "  ");
  std::copy(vecInt.begin(), vecInt.end(), outIter);

  displayDemo("\n  -- copy with back_inserter --");
  Vec<int> dstVec;
  auto binserter = std::back_inserter(dstVec);
  auto begin = [&vecInt]() { return vecInt.begin(); };
  auto end = [&vecInt]() { return vecInt.end(); };
  std::copy(begin(), --end(), binserter);
  show(dstVec);

  displayDemo("\n  -- copy with inserter --");
  auto inserter = std::inserter(dstVec, ++++dstVec.begin());
  std::copy(begin(), end(), inserter);
  show(dstVec);

  putline();
  Vec<double> vecDbl{ 1.0, -1.0, 0.5 };
  std::list<int> listInt{ 1, 2, 3, 4, 5 };
  doProc(vecInt, Op<int>());
  doProc(vecDbl, op<double>);
  doProc(listInt, Op<int>());

  putline(2);
}
