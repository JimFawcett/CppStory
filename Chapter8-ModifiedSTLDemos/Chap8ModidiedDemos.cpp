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
#include <type_traits>
#include "../Chapter7-Display/Chap7Display.h"

template<typename V>
class ShowOp {
public:
  ShowOp(const std::string& prefix = ", ") : prefix_(prefix) {}
  void operator()(V v) {
    if (first) {
      std::cout << "\n  " << v;
      first = false;
    }
    else {
      std::cout << prefix_ << v;
    }
  }
private:
  bool first = true;
  std::string prefix_ = ", ";
};

template<typename V>
class SumOp {
public:
  void operator()(V v) {
    sum_ += v;
  }
  V sum() { return sum_; }
private:
  V sum_;
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
  for_each(c.begin(), c.end(), ShowOp<typename C::value_type>());
}

template<typename T>
using Vec = std::vector<T>;

template<typename T>
using Lst = std::list<T>;

template<typename T>
using iterator = typename std::vector<T>::iterator;

template<typename O>
struct Null {};

template<typename C, template<typename> class Op = Null>
struct Collection {
  Collection(C& c, Op<typename C::value_type> op_ = Null<typename C::value_type>()) : op(op_) {
    first = c.begin();
    last = c.end();
  }
  typename C::iterator first;
  typename C::iterator last;
  Op<typename C::value_type> op;
};

template<typename C, template<typename> class Op>
typename Op<typename C::value_type> foreach(Collection<C, Op> rng, Op<typename C::value_type> op) {
  return std::for_each(rng.first, rng.last, op);
}

template<typename C, template<typename> class Op>
typename Op<typename C::value_type> foreach(Collection<C> rng, Op<typename C::value_type> op) {
  return std::for_each(rng.first, rng.last, op);
}

template<typename C, template<typename> class Op>
typename Op<typename C::value_type> foreach(Collection<C, Op> rng) {
  return std::for_each(rng.first, rng.last, rng.op);
}


//template<typename Cont, typename Op>
//void doProc(Cont c, Op op) {
//  std::for_each(c.begin(), c.end(), op);
//}
//
//template<typename Cont, typename Algo, typename Op>
//void doProc(Cont c, Algo algo, Op op) {
//  algo(c.begin(), c.end(), op);
//}

int main() {

  displayDemo("-- traditional algo use --");
  Vec<int> vecInt{ 1, 2, 3, 4, 5 };
  std::for_each(vecInt.begin(), vecInt.end(), ShowOp<int>());

  displayDemo("\n  -- using generic synonyms --");
  Vec<std::string> vecStr{ "Joe", "Sally", "Ashok", "Ming", "Hasim" };
  Collection<Vec<std::string>, ShowOp> rFriends(vecStr, ShowOp<std::string>());

  /*-- std algorithm with synonym arguments*/

  std::for_each(rFriends.first, rFriends.last, rFriends.op);

  /*-- prettified using range with embedded operation --*/

  foreach(rFriends);
  
  /*-- prettified using range and separate operation --*/

  //Op<std::string> op;
  //auto showCout = [&op](const std::string& s) { op(s); };
  ShowOp<std::string> showCout;
  foreach(rFriends, showCout);
  putline();

  Collection<Vec<int>, SumOp> vecIntColl(vecInt, SumOp<int>());
  SumOp<int> ret = foreach(vecIntColl, SumOp<int>());
  show(vecInt);
  std::cout << "\n  sum = " << ret.sum();

  //std::cout << "\n  sum = " << foreach<Collection<Vec<int>, SumOp<int>>(vecIntColl, SumOp<int>());

  displayDemo("\n  -- using synonyms --");
  auto first1 = vecInt.begin();
  auto last1 = vecInt.end();
  auto rng1 = std::pair{ first1, last1 };
  auto slop1 = ShowOp<int>();
  auto forEachOne1 = [](decltype(first1) f, decltype(last1) l, decltype(slop1) s) {
    for_each(f, l, s);
  };
  forEachOne1(first1, last1, slop1);

  Lst<double> lstDbl{ 1.0, -0.5, 0.0, 0.5 };
  auto first2 = lstDbl.begin();
  auto last2 = lstDbl.end();
  auto rng2 = std::pair{ first2, last2 };
  auto slop2 = ShowOp<double>();
  auto forEachOne2 = [](decltype(first2) f, decltype(last2) l, decltype(slop2) s) {
    for_each(f, l, s);
  };
  forEachOne2(rng2.first, rng2.second, slop2);

  displayDemo("\n  -- all the rest --");
  putline();
  Vec<double> vecDbl{ 1.0, -1.0, 0.5 };
  Collection<Vec<double>, SumOp> vecDblColl(vecDbl, SumOp<double>());
  
  Collection<Vec<double>> vecDblColl2(vecDbl);

  SumOp<double> retd = foreach(vecDblColl2, SumOp<double>());
  double sumd = foreach(vecDblColl2, SumOp<double>()).sum();
  show(vecDbl);
  std::cout << "\n  sumd = " << retd.sum();

  std::list<int> listInt{ 1, 2, 3, 2, 1 };
  Collection<Lst<int>> listIntColl(listInt);
  foreach(listIntColl, ShowOp<int>());
  int sumi = foreach(listIntColl, SumOp<int>()).sum();
  std::cout << "\n  sum of list = " << sumi;
  //foreach(vecDbl, SumOp<double>());
  //doProc(vecInt, ShowOp<int>());
  //doProc(vecDbl, ShowOp<double>());
  //doProc(listInt, ShowOp<int>());

  putline(2);
}
