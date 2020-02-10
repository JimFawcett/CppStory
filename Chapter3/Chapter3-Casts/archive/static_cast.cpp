/*--------------------------------------------------------------------------------------
   purpose of static_cast is to create a new instance of a foreign type, based on
   data stored in the source type.
  --------------------------------------------------------------------------------------*/

void demoReinterpretCast() {

  int i = 1.75;  // i = 1, with compiler warning of loss of significance
  int j = static_cast<int>(1.75);  // j = 1, no compiler warning

}