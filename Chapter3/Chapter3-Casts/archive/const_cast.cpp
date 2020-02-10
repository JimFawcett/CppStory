/*--------------------------------------------------------------------------------------
   purpose of const_cast is to allow passing const data to functions that won't change
   value even though not declared const functions, OS API calls for example.
  --------------------------------------------------------------------------------------*/

#include <string>
#include <iostream>
#include "../../Chapter8/Chapter8-Display/Chap8Display.h"

void mockAPIfunction(std::string* pStr) {
  std::cout << "\n  inside mock API function: " << *pStr;
}

void demoConstCast(const std::string& str) {

  displaySubtitle("const_cast");

  std::cout << "\n  " << str;
  //mockAPIfunction(&str);  fails to compile since str is const

  /*--- useful operation using sRef ---*/

  std::string& sRef = const_cast<std::string&>(str);
  // created non-const reference to const str

  mockAPIfunction(&sRef);  // succeeds since sRef is not const

  /*--- evil operation on sRef, violates contract of function interface ---*/
  /* don't do this */
  sRef = "changed";
  std::cout << "\n  " << str;  // now has changed value
  std::cout << "\n";
}
