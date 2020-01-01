#ifndef MI_STDLIB_H
#define MI_STDLIB_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef AEONDEV // it has its own utility
#include <string.h>
#endif
#include "avp_bitsbuf.h"
#include "avp_common.h"

#if defined(MIPSDEV) && !defined(MIPS_U2)
#include <cyg/infra/diag.h>
#endif


#define MY_PRINTF       (printf)
#define MY_MALLOC       (malloc)
#define MY_CALLOC       (calloc)
#define MY_FREE         (free)
#define MY_EXIT         (exit)

#define MY_COS          (cos)
#define MY_SIN          (sin)
#define MY_EXP          (exp)
#define MY_POW          (pow)
#define MY_CEIL         (ceil)
#define MY_FLOOR        (floor)
#define MY_SQRT         (sqrt)
#define MY_LOG          (log)

#define MY_BSINITBITS   bsInitBits
#define MY_BSFINIBITS   bsFiniBits
#define MY_BSSHOWBITS   bsShowBits_inline
#define MY_BSFLUSHBITS  bsFlushBits
#define MY_BSGETBITS    bsGetBits
#define MY_BSGETBITS_SHORT      bsGetBits_short
#define MY_BSFLUSHBITS_SHORT    bsFlushBits_short

#ifdef ARM_B1_DEV
#include "avp_vm_stdio.ho"
#define MY_MEMCPY       (vm_memcpy)
#define MY_MEMSET       (vm_memset)
#else
#define MY_MEMCPY       (memcpy)
#define MY_MEMSET       (memset)
#endif

#define MY_MEMMOVE      (memmove)
#define MY_STRNCMP      (strncmp)

#define MY_CLOCK        (clock)

#ifdef __TCS__
#define MY_DBGMSG(x)    DP(x)
#define MY_DP(x)        DP(x)
                        //(_dp)
#elif defined(__RTK_OS__)
#include "avp_player_util.h"
#define MY_REPORTMSG               diag_printf
#define MY_ERRMSG                  diag_printf
#define MY_DBGMSG                  diag_printf
#define MY_DP                      diag_printf
#undef  MY_PRINTF
#define MY_PRINTF                  diag_printf
#elif defined(MIPSDEV)
#define MY_REPORTMSG(fmt, args...)	diag_printf(fmt, ##args)
#define MY_ERRMSG(fmt, args...)		diag_printf(fmt, ##args)
#define MY_DBGMSG(fmt, args...)		diag_printf(fmt, ##args)
#define MY_DP(fmt, args...)			diag_printf(fmt, ##args)
#undef  MY_PRINTF
#define MY_PRINTF(fmt, args...)		diag_printf(fmt, ##args)
#elif defined(ARM_B1_DEV)
#define MY_REPORTMSG
#define MY_ERRMSG
#define MY_DBGMSG
#define MY_DP(x)
#undef  MY_PRINTF
#define MY_PRINTF
#elif defined(AEONDEV)
#include "utl.h"
#define printf          UTL_printf
#define MY_DBGMSG(x)    UTL_printf x
#define MY_ERRMSG       UTL_printf
#define MY_DP(x)        UTL_printf x
#define MY_REPORTMSG UTL_printf
#elif defined(ARM9)
#define DEBUG_LEVEL 0
#include "avp_ms_dprintf.h"
#define MY_REPORTMSG(fmt, args...) ms_dprintf(0, fmt, ##args)
#define MY_ERRMSG(fmt, args...)    ms_dprintf(0, fmt, ##args)
#define MY_DBGMSG(fmt, args...)    ms_dprintf(0, fmt, ##args)
#define MY_DP(fmt, args...)        ms_dprintf(0, fmt, ##args)
#else
#define MY_REPORTMSG    printf
#define MY_ERRMSG	    printf
#define MY_DBGMSG(x)    printf x
#define MY_DP(x)        printf x
#endif

#ifdef __TCS__
#define MY_ASSERT(cond, err)    tmAssert(cond, err)
#else
#define MY_ASSERT(cond, err)    assert(cond)
#endif //__TCS__


#ifdef NDEBUG

#undef MY_PRINTF
#undef MY_DP
#undef MY_DBGMSG
#undef MY_REPORTMSG
#undef MY_ASSERT
#define MY_DP(x)        ((void) 0)
#define MY_DBGMSG(x)    ((void) 0)
#if !defined(_MSC_VER)
#define MY_REPORTMSG(args...)
#define MY_PRINTF(args...)
#else
#define MY_REPORTMSG 1 ? 0 :
#define MY_PRINTF    1 ? 0 :
#endif
#define MY_ASSERT(cond, err) ((void) 0)

#endif // NDEBUG

#endif // MI_STDLIB_H
