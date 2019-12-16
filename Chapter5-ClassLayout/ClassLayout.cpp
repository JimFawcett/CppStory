///////////////////////////////////////////////////////////////////////
// Layout.cpp - Demonstrates how objects are laid out in memory      //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Sp 2009             //
///////////////////////////////////////////////////////////////////////
// See rules for using pointers:                                     //
// http://msdn.microsoft.com/en-us/library/aa384242.aspx             //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <conio.h>
//#include <winnt.h>

class Composed;
class Base;
class Derived;

//----< takes any pointer type and displays as a decimal string >----

std::string ToDecAddressString(unsigned int address)
{
  std::ostringstream oss;
  oss << std::uppercase << std::dec << address;
  return oss.str();
}
//----< takes any pointer type and displays as a hex string >--------

std::string ToHexAddressString(unsigned int address)
{
  std::ostringstream oss;
  oss << std::uppercase << " (0x" << std::hex << address << ")";
  return oss.str();
}
//----< explore process information structures >---------------------

HMODULE showProcessInfo()
{
  const int BuffSize = 255;
  char buffer[BuffSize];
  ::GetModuleFileNameA(NULL, buffer, BuffSize);
  std::cout << "  This executable is:\n  " << buffer;

  HMODULE hMod = ::GetModuleHandleA(buffer);
  //std::cout << "\n  Its base address is:   " << ToDecAddressString(hMod);
  //std::cout << ToHexAddressString(hMod);

  IMAGE_DOS_HEADER* dosheader = (IMAGE_DOS_HEADER*)hMod;
  IMAGE_OPTIONAL_HEADER* opthdr =
    (IMAGE_OPTIONAL_HEADER*)((BYTE*)hMod + dosheader->e_lfanew + 24);
  UINT_PTR pImageBase = opthdr->ImageBase;
  std::cout << "\n  Image base:   " << pImageBase;
  UINT_PTR pBaseOfCode = opthdr->BaseOfCode;
  std::cout << "\n  Code Section: " << pBaseOfCode << " bytes relative to image base";

  ///////////////////////////////////////////////////////////////////
  // two lines below don't compile for x64 platform
  UINT_PTR pBaseOfData = opthdr->BaseOfData;
  std::cout << "\n  Data Section: " << pBaseOfData << " bytes relative to image base";

  DWORD CodeSize = opthdr->SizeOfCode;
  std::cout << "\n  Code size:    " << CodeSize << " bytes";
  DWORD ImageSize = opthdr->SizeOfImage;
  std::cout << "\n  Image size:   " << ImageSize;
  std::cout << "\n";
  return hMod;
}
//----< show type and address layout >-------------------------------

template <typename T>
void showStatistics(T* thisPtr)
{
  int size = sizeof(*thisPtr);
  unsigned int startAddress = reinterpret_cast<unsigned int>(thisPtr);
  unsigned int endAddress = startAddress + size;

  std::cout << "\n  " << typeid(*thisPtr).name();
  std::cout << "\n  my size is: " << size << " bytes";
  if (typeid(thisPtr) == typeid(Base*))
    std::cout << " -- holds string and pointer to vtbl";
  if (typeid(thisPtr) == typeid(Composed*))
    std::cout << " -- holds string";
  if (typeid(thisPtr) == typeid(Derived*))
    std::cout << " -- holds Base and Composed";

  std::cout << "\n  my starting address is "
    << ToDecAddressString(startAddress) << ToHexAddressString(startAddress);
  std::cout << "\n  my ending address is   "
    << ToDecAddressString(endAddress) << ToHexAddressString(endAddress);
}
//----< format string display >--------------------------------------

void showString(const std::string& name, const std::string& msg)
{
  std::string temp = "\"This " + name + " " + msg + "\"";
  std::cout << "\n  " << temp;
  std::cout << " has " << temp.size() << " characters";
}
/////////////////////////////////////////////////////////////////////
// Display startup and shutdown messages

class Global_IO
{
public:
  Global_IO()
  {
    // display opening message before all of main's text

    std::cout << "\n  Demonstrating class layout and other things too!";
    std::cout << "\n ==================================================\n";
  }
  ~Global_IO()
  {
    // display parting message after all of main's text

    std::cout << "\n\n  That's all folks\n\n";
  }
} inStatic;  // note global definition

/////////////////////////////////////////////////////////////////////
// Used class is used by Derived, shows its statistics

class Used
{
public:
  Used(const std::string& msg) : msg_(msg)
  {
    std::cout << "\n  Used(const std::string&) called";
  }
  ~Used() { std::cout << "\n  ~Used() called"; }
  void say()
  {
    std::cout << "\n\n  Used::say()";
    showStatistics(this);
    showString("Used", msg_);
  }
private:
  std::string msg_;
};
/////////////////////////////////////////////////////////////////////
// Composed class is a data member of Base, shows its statistics

class Composed
{
public:
  Composed(const std::string& msg) : msg_(msg)
  {
    std::cout << "\n  Composed(const std::string&) called";
  }
  ~Composed() { std::cout << "\n  ~Composed() called"; }
  void say()
  {
    std::cout << "\n\n  Composed::say()";
    showStatistics(dynamic_cast<Composed*>(this));
    showString("Composed", msg_);
  }
private:
  std::string msg_;
};
/////////////////////////////////////////////////////////////////////
// Base class holds Composed and displays its layout statistics

class Base
{
public:
  Base(const std::string& msg) : composed_(msg)
  {
    std::cout << "\n  Base(const std::string&) called";
  }

  // If you remove virtual qualifier on ~Base() only 
  // Base destructor is called in main when created
  // on heap.  Both called if created on stack.

  virtual ~Base()
  {
    std::cout << "\n  ~Base() called";
  }
  virtual void say()
  {
    std::cout << "\n\n  Base::say()";
    showStatistics(dynamic_cast<Base*>(this));
    std::cout << "\n\n  Base invoking my Composed::say(): ";
    composed_.say();
  }
protected:
  Composed composed_;
};
/////////////////////////////////////////////////////////////////////
// Derived inherits from Base and displays its layout statistics.

class Derived : public Base
{
public:
  Derived(const std::string& msg) : Base(msg)
  {
    std::cout << "\n  Derived(const std::string&) called";
  }
  ~Derived() { std::cout << "\n  ~Derived() called"; }
  virtual void say(Used& used)
  {
    std::cout << "\n\n  Derived::say()";
    showStatistics(dynamic_cast<Derived*>(this));

    std::cout << "\n\n  Derived calling Base::say(): ";
    Base::say();
    std::cout << std::endl;

    std::cout << "\n\n  Derived calling Used::say(): ";
    used.say();
    std::cout << std::endl;
  }
private:
};

/////////////////////////////////////////////////////////////////////
// class inStack is created on stack, used to show stack addresses

class inStack
{
};
//----< demonstraton >-----------------------------------------------
int main()
{
  ///////////////////////////////////////////////////////////////////
  // uncomment to show process information
  HMODULE hMod = showProcessInfo();

  showStatistics(&inStatic);
  std::cout << std::endl;

  inStack instk;
  showStatistics(&instk);
  std::cout << std::endl;

  std::string arg = "string entered as constructor argument";
  std::cout << "\n  String, below, will be used in this demonstration:";
  std::cout << "\n    \"" << arg << "\"";
  std::cout << "\n  It's object size is " << sizeof(arg) << " bytes";
  std::cout << "\n  It contains " << arg.size() << " characters\n";

  std::cout << "\n  creating used object on stack";
  std::cout << "\n -------------------------------";
  Used u(arg);
  u.say();

  std::cout << std::endl;

  std::cout << "\n  creating base object on stack";
  std::cout << "\n -------------------------------";
  Base b(arg);
  b.say();

  std::cout << std::endl;

  /////////////////////////////////////////////////////////////////////
  // Works the same whether Derived created on stack or on heap, but
  // you will notice differences in the region of memory occupied
  //
  std::cout << "\n  creating derived object on stack";
  std::cout << "\n ----------------------------------";
  Derived d(arg);
  d.say(u);

  std::cout << "\n  creating derived object on heap";
  std::cout << "\n ---------------------------------";
  Base* pB = new Derived(arg);
  pB->say();
  delete pB;

  /////////////////////////////////////////////////////////////////////
  // uncomment to hold process in memory (to examine its properties)
  // getche() uses conio.h
  //std::cout << "\n  press key to exit: ";
  //std::cout.flush();
  //getche();
}