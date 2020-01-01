#if defined(__AEONGCC__) && !defined(__SDK_SIMULATION__)
  // G1 must using sinovoice library V5 version
  #include "sv_hzrecog_v5.h"
#else
  #if defined(__SINOVOICE_HW_V5__)
    #include "sv_hzrecog_v5.h"
  #else //defined(__SINOVOICE_HW_V5__)
    #include "sv_hzrecog_v4.h"
  #endif //defined(__SINOVOICE_HW_V5__)
#endif
