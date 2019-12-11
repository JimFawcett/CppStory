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
#include "../Display/Display.h"

namespace Chap4 {

  class X1 {
  public:
    X1(const std::string& name) : name_(name) {
      for (size_t i = 0; i < 5; ++i) {
        buffer[i] = i;
      }
    }
    std::string& name() {
      return name_;
    }
    int& operator[](size_t i) {
      if (i < 0 || 5 <= i)
        throw std::exception("invalid index");
      return buffer[i];
    }
    size_t size() const {
      return 5;
    }
  private:
    std::string name_;
    int buffer[5];
  };

  void show(X1 x) {
    std::cout << "\n  " << x.name() << "\n  ";
    for (size_t i = 0; i < x.size(); ++i) {
      std::cout << x[i] << " ";
    }
    std::cout << std::endl;
  }

  class X2 {
  public:
    X2(const std::string& name, size_t N = 1);
    std::string& name();
    int& operator[](size_t i);
    int operator[](size_t i) const;
    size_t size() const;
  private:
    std::string name_;
    std::vector<int> buffer_;
  };
  /*--- constructor ---*/
  X2::X2(const std::string& name, size_t N)
    : name_(name), buffer_(N) {
  }
  /*--- name accessor ---*/
  std::string& X2::name() {
    return name_;
  }
  /*--- indexer for non-const instances ---*/
  int& X2::operator[](size_t i) {
    if (i < 0 || buffer_.size() <= i)
      throw std::exception("index out of range");
    return buffer_[i];
  }
  /*--- indexer for const instances ---*/
  int X2::operator[](size_t i) const {
    if (i < 0 || buffer_.size() <= i)
      throw std::exception("index out of range");
    return buffer_[i];
  }
  /*--- buffer size accessor ---*/
  size_t X2::size() const {
    return buffer_.size();
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

  class X3 {
  public:
    X3(const std::string& name, size_t N = 1);
    X3(const X3& x);
    ~X3();
    X3& operator=(const X3& x);
    std::string& name();
    int& operator[](size_t i);
    int operator[](size_t i) const;
    size_t size() const;
  private:
    std::string name_;
    int* pBuffer_ = nullptr;
    size_t bufSize_ = 0;
  };
  /*--- constructor ---*/
  X3::X3(const std::string& name, size_t N)
    : name_(name), bufSize_(N), pBuffer_(new int[N]) {
  }
  /*--- copy constructor ---*/
  X3::X3(const X3& x)
    : bufSize_(x.bufSize_), pBuffer_(new int[x.bufSize_]) {
    name_ = x.name_;
    memcpy(pBuffer_, x.pBuffer_, bufSize_ * sizeof(int));
  }
  /*--- destructor ---*/
  X3::~X3() {
    delete[] pBuffer_;
  }
  /*--- copy assignment operator ---*/
  X3& X3::operator=(const X3& x) {
    if (this != &x) {
      /* won't assign name */
      bufSize_ = x.bufSize_;
      delete pBuffer_;
      pBuffer_ = new int[bufSize_];
      memcpy(pBuffer_, x.pBuffer_, bufSize_ * sizeof(int));
    }
    return *this;
  }
  /*--- name accessor ---*/
  std::string& X3::name() {
    return name_;
  }
  /*--- indexer for non-const instances ---*/
  int& X3::operator[](size_t i) {
    if (i < 0 || bufSize_ <= i)
      throw std::exception("index out of range");
    return *(pBuffer_ + i);
  }
  /*--- indexer for const instances ---*/
  int X3::operator[](size_t i) const {
    if (i < 0 || bufSize_ <= i)
      throw std::exception("index out of range");
    return *(pBuffer_ + i);
  }
  /*--- buffer size accessor ---*/
  size_t X3::size() const {
    return bufSize_;
  }

  void demoBasicClasses() {

    displayDemo("=== Demo Basic Classes ===");

    displayDemo("--- class X1 ---");
    X1 xa("xa");
    show(xa);
    X1 xb = xa;
    xb.name() = "xb";
    show(xb);

    displayDemo("--- class X2 ---");
    X2 xc("xc",3);
    xc[0] = 1;
    xc[1] = 2;
    xc[2] = 3;
    show(xc);
    
    X2 xd("xd");
    xd = xc;
    show(xd);


    displayDemo("--- class X3 ---");
    X3 xe("xe", 3);
    xe[0] = 1;
    xe[1] = 2;
    xe[2] = 1;
    show(xe);

    X3 xf("xf");
    xf = xe;
    show(xf);
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

  Anatomy::Anatomy() : value(std::any()), name_("unknown") {
    myCount = ++count;
    showMsg(0, "obj #" + std::to_string(myCount));
  }

  Anatomy::Anatomy(const std::string& nameStr)
    : value(std::any()), name_(nameStr) {
    myCount = ++count;
    showMsg(0, "obj #" + std::to_string(myCount));
  }

  Anatomy::Anatomy(const Anatomy& a)
    : value(a.value), name_(a.name_) {
    myCount = ++count;
    showMsg(1, "obj #" + std::to_string(myCount));
  }

  Anatomy::Anatomy(Anatomy&& a) noexcept
    : value(std::move(a.value)), name_(std::move(a.name_)) {
    myCount = ++count;
    showMsg(2, "obj #" + std::to_string(myCount));
  }

  Anatomy& Anatomy::operator=(const Anatomy& a) {
    if (this != &a) {
      // don't want to rename, so no copy
      value = a.value;
    }
    showMsg(3, "obj #" + std::to_string(myCount));
    return *this;
  }

  Anatomy& Anatomy::operator=(Anatomy&& a) noexcept {
    if (this != &a) {
      // don't want to rename, so no copy
      value = std::move(a.value);
    }
    showMsg(4, "obj #" + std::to_string(myCount));
    return *this;
  }

  Anatomy::~Anatomy() {
    showMsg(5, "obj #" + std::to_string(myCount));
    // name_ and value are composed, so their dtors will be called here
  }

  void Anatomy::name(const std::string& nameStr) {
    name_ = nameStr;
  }

  std::string Anatomy::name() const {
    return name_;
  }

  size_t Anatomy::objNumber() const {
    return myCount;
  }

  template<typename T>
  void Anatomy::setValue(const T& t) {
    value = t;
  }

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

  template<typename T>
  Anatomy makeAnatomy(const T& t = T()) {
    Anatomy temp("created");
    temp.setValue(t);
    return temp;
  }

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
  showAnatomy<double>(a1, __LINE__);

  Anatomy a2{ a1 };
  a2.name("a2");
  showAnatomy<double>(a2, __LINE__);

  a1 = a2;
  showAnatomy<double>(a1, __LINE__);

  Anatomy a3 = makeAnatomy(std::string("some string"));
  showAnatomy<std::string>(a3, __LINE__);

  Anatomy a4;
  a4 = makeAnatomy(5);
  showAnatomy<int>(a4, __LINE__);
}

int main() {

  using namespace Chap4;

  demoBasicClasses();
  putline();
  demoClassAnatomy();
  putline(2);
}