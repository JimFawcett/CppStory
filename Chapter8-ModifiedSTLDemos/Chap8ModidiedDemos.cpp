// Chap8ModifiedDemos.cpp
// https://www.fluentcpp.com/2018/03/30/is-stdfor_each-obsolete/

#include <string>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <iostream>
#include <functional>
#include <algorithm>
#include "../Chapter7-Display/Chap7Display.h"

template<typename Cont, typename Op>
void doProc(Cont c, Op op) {
  std::for_each(c.begin(), c.end(), op);
}

template<typename Cont, typename Algo, typename Op>
void doProc(Cont c, Algo algo, Op op) {
  algo(c.begin(), c.end(), op);
  //std::for_each(c.begin(), c.end(), op);
}

//template<typename V>
//auto op = [](V v) {
//  static bool first = true;
//  if (first) {
//    std::cout << "\n  " << v;
//    first = false;
//  }
//  else {
//    std::cout << ", " << v;
//  }
//};

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
  //putline(1, "  ");
  std::cout << "  ";
  for_each(c.begin(), c.end(), Op<typename C::value_type>());
}

template<typename T>
using Vec = std::vector<T>;

template<typename T>
using Lst = std::list<T>;

template<typename T>
using iterator = typename std::vector<T>::iterator;

template<typename C>
struct Range {
  Range(C& c, Op<typename C::value_type> op_ = nullptr) : op(op_) {
    first = c.begin();
    last = c.end();
  }
  typename C::iterator first;
  typename C::iterator last;
  Op<typename C::value_type> op;
};

template<typename C>
void foreach(Range<C> rng) {
  std::for_each(rng.first, rng.last, rng.op);
}

template<typename C, typename Op>
void foreach(Range<C> rng, Op op) {
  std::for_each(rng.first, rng.last, op);
}

//template<typename Arg1, typename Arg2, typename Op>
//const auto doFor = std::for_each<Arg1, Arg2, Op>;

//auto f = std::bind(&std::for_each, _1, _2, _3);

int main() {

  displayDemo("-- traditional algo use --");
  Vec<int> vecInt{ 1, 2, 3, 4, 5 };
  std::for_each(vecInt.begin(), vecInt.end(), Op<int>());

  displayDemo("\n  -- using generic synonyms --");
  Vec<std::string> vecStr{ "Joe", "Sally", "Ashok", "Ming", "Hasim" };
  Range<Vec<std::string>> rFriends(vecStr, Op<std::string>());

  /*-- std algorithm with synonym arguments*/

  std::for_each(rFriends.first, rFriends.last, rFriends.op);

  /*-- prettified using range with embedded operation --*/

  foreach(rFriends);
  
  /*-- prettified using range and separate operation --*/

  Op<std::string> op;
  auto showCout = [&op](const std::string& s) { op(s); };
  foreach(rFriends, showCout);

  displayDemo("\n  -- using synonyms --");
  auto first1 = vecInt.begin();
  auto last1 = vecInt.end();
  auto rng1 = std::pair{ first1, last1 };
  auto slop1 = Op<int>();
  auto forEachOne1 = [](decltype(first1) f, decltype(last1) l, decltype(slop1) s) {
    for_each(f, l, s);
  };
  forEachOne1(first1, last1, slop1);

  Lst<double> lstDbl{ 1.0, -0.5, 0.0, 0.5 };
  auto first2 = lstDbl.begin();
  auto last2 = lstDbl.end();
  auto rng2 = std::pair{ first2, last2 };
  auto slop2 = Op<double>();
  auto forEachOne2 = [](decltype(first2) f, decltype(last2) l, decltype(slop2) s) {
    for_each(f, l, s);
  };
  forEachOne2(rng2.first, rng2.second, slop2);


  displayDemo("\n  -- all the rest --");
  putline();
  Vec<double> vecDbl{ 1.0, -1.0, 0.5 };
  std::list<int> listInt{ 1, 2, 3, 4, 5 };
  doProc(vecInt, Op<int>());
  doProc(vecDbl, Op<double>());
  doProc(listInt, Op<int>());

  //doProc(vecInt, doFor<Vec<int>::iterator, Vec<int>::iterator, Op<int>>, Op<int>());

  putline(2);
}
