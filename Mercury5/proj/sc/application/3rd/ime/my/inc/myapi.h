#if defined(__AEONGCC__) && !defined(__SDK_SIMULATION__)
  // The MY library for R2 is newer version, so we have to include different header file
  #include "myapi_6_65.h"
#else //defined(__AEONGCC__) && !defined()
  #include "myapi_6_51.h"
#endif //defined(__AEONGCC__) && !defined()
