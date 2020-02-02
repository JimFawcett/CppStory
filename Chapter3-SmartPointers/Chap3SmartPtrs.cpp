// Chap3SmartPtrs.cpp

#include <memory>
#include <string>
#include <iostream>
#include "../Chapter8-Display/Chap8Display.h"

std::string displayHelper(
  const std::string& str
) 
{
  std::string insert = 
    (str.size() > 0 ? " " + str + " " : " ");
  return insert;
}
/*-- interface for Widget class --*/

struct IWidget {
  virtual ~IWidget() {}
  virtual void say() = 0;
  virtual std::string name() = 0;
  virtual void name(const std::string& nm) = 0;
};
/*-- Widget class --*/

class Widget : public IWidget {
public:
  Widget() = default;
  Widget(const std::string& nm) {
    name_ = nm;
  }
  ~Widget() {
    std::cout << "\n  destroying "
              << displayHelper(name_);
  }
  virtual void say() override {
    std::cout << "\n  Widget instance" 
              << displayHelper(name_) 
              << "here";
    std::cout << "\n  my address is " 
              << reinterpret_cast<long long>(this);
  }
  virtual std::string name() override {
    return name_;
  }
  virtual void name(const std::string& nm) {
    name_ = nm;
  }
private:
  std::string name_;
};
/*-------------------------------------------
  first factory function uses unique_ptr
*/

std::unique_ptr<IWidget> createWidget1() {
  return std::unique_ptr<Widget>(new Widget);
}
/*--------------------------------------------
  second factory function uses make_unique
*/

std::unique_ptr<IWidget> createWidget2() {
  return std::make_unique<Widget>();
}
/*-------------------------------------------
  third factory function uses initialized
  make_unique
*/
std::unique_ptr<IWidget>
createWidget3(const std::string& name) {
  return std::make_unique<Widget>(
    Widget(name)
    );
}

/*-------------------------------------------
  fourth factory function uses static Widget
  for make_unique avoiding repeated constr.
*/
std::unique_ptr<IWidget>
createWidget4(const std::string& name) {
  static Widget widget;
  widget.name(name);
  return std::make_unique<Widget>(
    widget
  );
}

int main() {

  displayTitle("Demonstrating Smart Pointers");

  displayDemo(
    "--- createWidget1 with std::unique_ptr ---"
  );
  std::unique_ptr<IWidget> pWidget = 
    createWidget1();
  pWidget->say();
  pWidget->name("Joe");
  pWidget->say();
  putline();

  displayDemo(
    "--- createWidget2 with std::make_unique ---"
  );
  pWidget = createWidget2();
  pWidget->name("Zhang");
  pWidget->say();
  putline();

  displayDemo(
    "--- createWidget3 with initialized "
    "std::make_unique ---"
  );
  pWidget = createWidget3("Ashok");
  pWidget->say();
  putline();

  displayDemo(
    "--- createWidget4 with "
    "static initialized "
    "std::make_unique ---"
  );
  pWidget = createWidget4("Priyaa");
  pWidget->say();
  putline();

  displayDemo(
    "--- std::shared_ptr ---"
  );
  std::shared_ptr<IWidget> pS1Widget = 
    std::make_shared<Widget>(Widget("Mike"));
  pS1Widget->say();
  std::shared_ptr<IWidget> 
  pS2Widget = pS1Widget;
  pS2Widget->say();
  putline();

  displayDemo(
    "--- std::shared_ptr via factory---"
  );
  std::shared_ptr<IWidget>
  pS3Widget = createWidget4("Sally");
  pS3Widget->say();
  std::shared_ptr<IWidget>
  pS4Widget = pS3Widget;
  pS4Widget->say();
  putline();
}