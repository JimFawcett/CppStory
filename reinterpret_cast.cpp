/*--------------------------------------------------------------------------------------
  purpose of reinterpret_cast is to apply new type rules to an existing instance.
  - packing double's bytes into byte array
  - unpacking byte array into another double
  - illustrates how data might be marshalled over a socket channel, where the
    byte array pretends to be the socket channel
  --------------------------------------------------------------------------------------*/

void demoReinterpretCast() {

  displaySubtitle("reinterpret_cast");

  double d1{ 3.5 };
  double d2;
  size_t Max = sizeof(d1);

  /* create byte array on heap referenced by std::unique_ptr<std::byte> */

  std::unique_ptr<std::byte> pBuffer(new std::byte[Max]);  // owning pointer
  std::byte* pBuffIndex = pBuffer.get();                   // non-owning pointer

  /* pack double d1 into byte array */

  std::byte* pByteSrc = reinterpret_cast<std::byte*>(&d1);
  std::byte* pSrcIndex = pByteSrc;  			   // non-owning pointers

  for (size_t i = 0; i < Max; ++i) {
    *pBuffIndex++ = *pSrcIndex++;
  }

  /* unpack byte array into double d2 */

  if (sizeof(d2) == sizeof(d1)) {
    std::byte* pByteDst = reinterpret_cast<std::byte*>(&d2);
    std::byte* pDstIndex = pByteDst;  			   // non-owning pointers
    pBuffIndex = pBuffer.get();
    for (size_t i = 0; i < Max; ++i) {
      *pDstIndex++ = *pBuffIndex++;
    }
  }

  /* show that src and dst have the same values */

  std::cout << "\n  src double = " << d1;
  std::cout << "\n  dst double = " << d2;

  // byte array on heap will be deallocated here
  // as std::unique_ptr goes out of scope
}
