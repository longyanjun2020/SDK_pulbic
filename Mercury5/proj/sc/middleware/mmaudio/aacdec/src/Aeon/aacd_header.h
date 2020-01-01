#ifndef _AAC_DECODER_HEADER_INCLUDE_FILE
#define _AAC_DECODER_HEADER_INCLUDE_FILE


#include <string.h>
/*lint --e{414} */
/*lint --e{504} */
/*lint --e{514} */
/*lint --e{529} */
/*lint --e{530} */
/*lint --e{545} */
/*lint --e{550} */
/*lint --e{569} */
/*lint --e{570} */
/*lint --e{573} */
/*lint --e{578} */
/*lint --e{644} */
/*lint --e{648} */
/*lint --e{661} */
/*lint --e{662} */
/*lint --e{666} */
/*lint --e{676} */
/*lint --e{681} */

#ifdef HEAAC_V2_DEC
#define SBR_DEC
#define PS_DEC  
#endif

#ifdef HEAAC_V1_DEC
#define SBR_DEC
#endif

#if defined(CERAMAL_3) || defined(CERAMAL_5)
#define USE_AMAC_32x32
#undef SBR_DEC
#undef PS_DEC
#endif


#define ENABLE_DOWN_SAMPLING

typedef signed char schar;

#ifdef SBR_DEC
#include "sbr_constant.h"
#endif

#ifdef SBR_DEC
#include "sbr_struct.h"
#endif
#include "aacd_struct.h"


#include "aacd_function.h"
#ifdef SBR_DEC
#include "sbr_function.h"
#endif

#include "aacd_mac.h"
#ifdef SBR_DEC
#include "sbr_mac.h"
#endif

#include "aacd_lib.h"





#endif


