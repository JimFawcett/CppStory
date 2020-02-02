/////////////////////////////////////////////////////////////////////
// Classes.cpp - Demonstrate class anatomy                         //
//                                                                 //
// Jim Fawcett, Teaching Professor Emeritus, Syracuse University   //
/////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <initializer_list>
#include <any>
#include "../Chapter8-Display/Chap8Display.h"

namespace Chap4 {
  namespace Example1 {

    class Point {
    public:
      Point(const std::string& name = "none") 
        : name_(name), coordinates_{ 0.0, 0.0, 0.0 } {
      }
      std::string& name() {
        return name_;
      }
      double& operator[](size_t i) {
        if (i < 0 || 3 <= i)
          throw std::exception("invalid index");
        return coordinates_[i];
      }
      size_t size() const {
        return 3;
      }
    private:
      std::string name_;
      double coordinates_[3];
    };

    void show(Point p) {
      std::cout << "\n  " << p.name() << "\n  ";
      for (size_t i = 0; i < p.size(); ++i) {
        std::cout << p[i] << " ";
      }
      std::cout << std::endl;
    }
  }
  namespace Example2 {

    class Point {
    public:
      Point(const std::string& name = "none", size_t N = 3);
      std::string& name();
      double& operator[](size_t i);
      double operator[](size_t i) const;
      size_t size() const;
    private:
      std::string name_;
      std::vector<double> coordinates_;
    };
    /*--- constructor ---*/
    Point::Point(const std::string& name, size_t N)
      : name_(name), coordinates_(N) {
    }
    /*--- name accessor ---*/
    std::string& Point::name() {
      return name_;
    }
    /*--- indexer for non-const instances ---*/
    double& Point::operator[](size_t i) {
      if (i < 0 || coordinates_.size() <= i)
        throw std::exception("index out of range");
      return coordinates_[i];
    }
    /*--- indexer for const instances ---*/
    double Point::operator[](size_t i) const {
      if (i < 0 || coordinates_.size() <= i)
        throw std::exception("index out of range");
      return coordinates_[i];
    }
    /*--- buffer size accessor ---*/
    size_t Point::size() const {
      return coordinates_.size();
    }
  }

  /*--- generic display function ---*/
  template<typename T>
  void show(T t) {
    std::cout << "\n  " << t.name() << "\n  ";
    for (size_t i = 0; i < t.size(); ++i) {
      std::cout << t[i] << " ";
    }
    std::cout << std::endl;
  }

  namespace Example3 {

    class Point {
    public:
      Point(const std::string& name = "none", size_t N = 1);
      Point(const Point& x);
      ~Point();
      Point& operator=(const Point& x);
      std::string& name();
      double& operator[](size_t i);
      double operator[](size_t i) const;
      size_t size() const;
    private:
      std::string name_;
      double* pBuffer_ = nullptr;
      size_t bufSize_ = 0;
    };
    /*--- constructor ---*/
    Point::Point(const std::string& name, size_t N)
      : name_(name), bufSize_(N), pBuffer_(new double[N]) {
    }
    /*--- copy constructor ---*/
    Point::Point(const Point& x)
      : bufSize_(x.bufSize_), pBuffer_(new double[x.bufSize_]) {
      name_ = x.name_;
      memcpy(pBuffer_, x.pBuffer_, bufSize_ * sizeof(double));
    }
    /*--- destructor ---*/
    Point::~Point() {
      delete[] pBuffer_;
    }
    /*--- copy assignment operator ---*/
    Point& Point::operator=(const Point& x) {
      if (this != &x) {
        /* won't assign name */
        bufSize_ = x.bufSize_;
        delete pBuffer_;
        pBuffer_ = new double[bufSize_];
        memcpy(pBuffer_, x.pBuffer_, bufSize_ * sizeof(double));
      }
      return *this;
    }
    /*--- name accessor ---*/
    std::string& Point::name() {
      return name_;
    }
    /*--- indexer for non-const instances ---*/
    double& Point::operator[](size_t i) {
      if (i < 0 || bufSize_ <= i)
        throw std::exception("index out of range");
      return *(pBuffer_ + i);
    }
    /*--- indexer for const instances ---*/
    double Point::operator[](size_t i) const {
      if (i < 0 || bufSize_ <= i)
        throw std::exception("index out of range");
      return *(pBuffer_ + i);
    }
    /*--- buffer size accessor ---*/
    size_t Point::size() const {
      return bufSize_;
    }
  }

  void demoBasicClasses() {

    displayDemo("=== Demo Basic Classes ===");

    displayDemo("--- Example1::Point ---");
    Example1::Point p1("p1");
    p1[0] = 1.0;
    p1[1] = 2.0;
    p1[2] = 3.0;
    show(p1);
    displayDemo("--- copy construction of p2 using src p1 ---");
    Example1::Point p2{ p1 };
    p2.name() = "p2";
    show(p2);
    displayDemo("--- copy assignment of p3 from src p2");
    Example1::Point p3("p3");
    p3 = p2;
    p3.name() = "p3";
    show(p3);

    displayDemo("--- Example2::Point ---");
    Example2::Point p4("p4", 3);
    p4[0] = -1.0;
    p4[1] = 0.0;
    p4[2] = 1.0;
    show(p4);
    displayDemo("--- copy construction of p5 using src p4 ---");
    Example2::Point p5{ p4 };
    p5.name() = "p5";
    show(p5);
    displayDemo("--- copy assignment of p6 from src p5");
    Example2::Point p6("p6");
    p6 = p5;
    p6.name() = "p6";
    show(p6);

    displayDemo("--- Example3::Point ---");
    Example3::Point p7("p7", 3);
    p7[0] = -0.5;
    p7[1] = 0.0;
    p7[2] = 0.5;
    show(p7);
    displayDemo("--- copy construction of p8 using src p7 ---");
    Example3::Point p8{ p7 };
    p8.name() = "p8";
    show(p8);
    displayDemo("--- copy assignment of p9 from src p8");
    Example3::Point p9("p9");
    p9 = p8;
    show(p8);
  }

  bool Assert(bool predicate, const std::string& msg = "") {
    if (!predicate) {
      std::cout << "\n ---- " << msg << " ----";
      return true;  // asserted
    }
    return false;   // didn't assert
  }

  class Anatomy {
  public:
    Anatomy();                                       // default ctor
    Anatomy(const std::string& nameStr);             // promotion ctor
    Anatomy(const Anatomy& a);                       // copy ctor
    Anatomy(Anatomy&& a) noexcept;                   // move ctor
    Anatomy& operator=(const Anatomy& a);            // copy assignment
    Anatomy& operator=(Anatomy&& a) noexcept;        // move assignment
    ~Anatomy();                                      // dtor
    void name(const std::string& nameStr);
    std::string name() const;
    size_t objNumber() const;
    template<typename T>
    void setValue(const T& t);
    template<typename T>
    T getValue() const;
    void showMsg(size_t n, const std::string& msg);  // custom method
  private:
    std::string name_;
    static size_t count;
    size_t myCount = 0;
    std::any value;
    constexpr static size_t MaxMsg = 6;
    std::string invMsg[MaxMsg]{
      "default ctor invoked",
      "copy ctor invoked",
      "move ctor invoked",
      "copy assignment invoked",
      "move assignment invoked",
      "dtor invoked"
    };
  };

  size_t Anatomy::count = 0;

  void Anatomy::showMsg(size_t n, const std::string& msg) {
    if (Assert(0 <= n && n < MaxMsg))
      return;
    std::string localMsg = invMsg[n];
    std::cout << "\n  " << localMsg;
    if (msg.size() > 0)
      std::cout << ", " << msg;
  }
  /*--- default constructor ---*/
  Anatomy::Anatomy() : value(std::any()), name_("unknown") {
    myCount = ++count;
    showMsg(0, "obj #" + std::to_string(myCount));
  }
  /*--- promotion constructor ---*/
  Anatomy::Anatomy(const std::string& nameStr)
    : value(std::any()), name_(nameStr) {
    myCount = ++count;
    showMsg(0, "obj #" + std::to_string(myCount));
  }
  /*--- copy constructor ---*/
  Anatomy::Anatomy(const Anatomy& a)
    : value(a.value), name_(a.name_) {
    myCount = ++count;
    showMsg(1, "obj #" + std::to_string(myCount));
  }
  /*--- move constructor ---*/
  Anatomy::Anatomy(Anatomy&& a) noexcept
    : value(std::move(a.value)), name_(std::move(a.name_)) {
    myCount = ++count;
    showMsg(2, "obj #" + std::to_string(myCount));
  }
  /*--- copy assignment operator ---*/
  Anatomy& Anatomy::operator=(const Anatomy& a) {
    if (this != &a) {
      // don't want to rename, so no copy
      value = a.value;
    }
    showMsg(3, "obj #" + std::to_string(myCount));
    return *this;
  }
  /*--- move assignment operator ---*/
  Anatomy& Anatomy::operator=(Anatomy&& a) noexcept {
    if (this != &a) {
      // don't want to rename, so no copy
      value = std::move(a.value);
    }
    showMsg(4, "obj #" + std::to_string(myCount));
    return *this;
  }
  /*--- destructor ---*/
  Anatomy::~Anatomy() {
    showMsg(5, "obj #" + std::to_string(myCount));
    // name_ and value are composed, so their dtors will be called here
  }
  /*--- name setter ----*/
  void Anatomy::name(const std::string& nameStr) {
    name_ = nameStr;
  }

  std::string Anatomy::name() const {
    return name_;
  }
  /*--- objNumber getter ---*/
  size_t Anatomy::objNumber() const {
    return myCount;
  }
  /*--- value setter ---*/
  template<typename T>
  void Anatomy::setValue(const T& t) {
    value = t;
  }
  /*--- value getter ---*/
  template<typename T>
  T Anatomy::getValue() const {
    try {
      return std::any_cast<T>(value);
    }
    catch (...) {
      std::cout << " --- can't retrieve value for " << name_ << " ---";
      return T();
    }
  }
  /*--- Anatomy object factory ---*/
  template<typename T>
  Anatomy makeAnatomy(const T& t = T()) {
    Anatomy temp("created");
    temp.setValue(t);
    return temp;
  }
  /*--- show Anatomy state ---*/
  template<typename T>
  void showAnatomy(const Anatomy& a, size_t line = 0) {
    if (line > 0)
      std::cout << "\n  at line #" << line;
    std::cout << "\n  " << a.name() << ", obj#" << a.objNumber()
      << ", has value " << a.getValue<T>() << std::endl;
  }
}

struct Cosmetic {
  ~Cosmetic() { std::cout << "\n\n"; }
} cosm;

void demoClassAnatomy() {

  using namespace Chap4;

  std::cout << "\n  Demonstrate Class Anatomy";
  std::cout << "\n ===========================\n";

  Anatomy a1;
  a1.setValue(1.5);
  showAnatomy<double>(a1, __LINE__ - 2);

  Anatomy a2{ a1 };
  a2.name("a2");
  showAnatomy<double>(a2, __LINE__ - 2);

  a1 = a2;
  showAnatomy<double>(a1, __LINE__ - 1);

  Anatomy a3 = makeAnatomy(std::string("some string"));
  showAnatomy<std::string>(a3, __LINE__ - 1);

  Anatomy a4;
  a4 = makeAnatomy(5);
  showAnatomy<int>(a4, __LINE__ - 1);
}

int main() {

  using namespace Chap4;

  demoBasicClasses();
  putline();
  demoClassAnatomy();
  putline(2);
}