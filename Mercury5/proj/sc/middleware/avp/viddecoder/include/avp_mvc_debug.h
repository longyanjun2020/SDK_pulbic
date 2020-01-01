#ifndef MVC_DEBUG_H
#define MVC_DEBUG_H

/* define printf across platforms, note this should be put to os fix instead */

#if defined(__TCS__)

#define MVC_PRINTF                  DP

#elif defined(__RTK_OS__)

#include "avp_player_util.h"
#define MVC_PRINTF                  diag_printf

#elif defined(MIPSDEV)

#ifndef MIPS_U2
#include <cyg/infra/diag.h>
#endif
#define MVC_PRINTF(fmt, args...)    diag_printf(fmt, ##args)

#elif defined(ARM_B1_DEV)

#define MVC_PRINTF(msg)             ((void) 0)

#elif defined(AEONDEV)

#include "utl.h"
#define MVC_PRINTF                  UTL_printf

#elif defined(ARM9)
#define DEBUG_LEVEL 0
#include "avp_ms_dprintf.h"
#define MVC_PRINTF(fmt, args...)    ms_dprintf(0, fmt, ##args)

#else

#include <stdio.h>
#define MVC_PRINTF                  printf

#endif

/* define assert across platforms, note this should be put to os fix instead */
#if !defined(_DEBUG) || defined(NDEBUG)

#define MVC_ASSERT(expr)            ((void) 0)

#elif defined(__TCS__)

#define MVC_ASSERT(expr)            tmAssert(expr, 0)

#elif defined(AEONDEV)

#define MVC_ASSERT(expr)            //if (!(expr)) { UTL_printf("assertion failed ,%s, %s\n", __FUNCTION__, __LINE__); while(1){;} }

#else

#include <assert.h>

#define MVC_ASSERT(expr)            assert(expr)

#endif

/* define conformance assert macro */
#define CONFORM_ASSERT(expr)        MVC_ASSERT(expr)

/* define debug message macro */

#if !defined(_DEBUG) || defined(NDEBUG)
#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define MVC_DBGMSG(format, ...)     ((void) 0)
#else
#define MVC_DBGMSG                  1 ? 0 :
#endif
#else
#define MVC_DBGMSG                  MVC_PRINTF
#endif

/* define error message macro */
#define MVC_ERRMSG                  MVC_PRINTF

/* define help message macro */
#define MVC_INFOMSG                 MVC_PRINTF

#endif /* MVC_DEBUG_H */
