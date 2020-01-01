#ifndef TM_TCS_H
#define TM_TCS_H

// *****common part
#include <ops/custom_defs.h>
#define RESTRICT    restrict

#if !defined(_TM3260_) && (__TCS_VERSION__ < 400)  //shiu : we have tcs4.41
// *****for tm1300, tcs2.2
#include <tmLibappErr.h>  //TMLIBAPP_OK
#include <tm1/tmAssert.h>

#define DUALASL(a,i)    ((((int32)a)<<(i)) & PACK16LSB(((int32)-1)<<(i), ((int32)-1)<<(i)))

#undef assert
#ifdef NDEBUG
#define assert(c)
#else
//shiu030220 : tmAssert() will cause messy video output in debug mode
//  problematic files : m4vHeader.c, m4vPicture.c, m4vMBlock.c
//  problematic clips : lopetz.m4v, bali-b-352x288.m4v, SM03A01031.m4v
/*
#include <tm1/tmAssert.h>
#define assert(c)   tmAssert(c, 0)
*/
#include <stdio.h>
#include <stdlib.h>
#include <tm1/mmio.h>
#include <ops/custom_ops.h>
#include <tm1/tmInterrupts.h>

extern Int _dp(const char* format, ...);
extern void _default_interrupt_handler( void );

#define assert(cond) {                                        \
  if (!(cond)) {                                                         \
    _dp ("*** Assertion failed : file %s, line %d\n", __FILE__, __LINE__);                    \
    if ((readpcsw () & intIEN) != 0) {                                  \
      fprintf (stderr, "*** Assertion failed : file %s, line %d\n", __FILE__, __LINE__);     \
      exit (-1);                                                 \
    } else {   \
      if (MMIO (INTVEC18) == (UInt32) _default_interrupt_handler &&     \
          MMIO (INTVEC30) == (UInt32) _default_interrupt_handler) { \
         MMIO (BIU_CTL) |= 1 << 11;                         \
      } else {                                                             \
         exit (-1);                                                 \
      }                                                             \
    }                                                               \
  }   \
}

#endif // NDEBUG

//define for debug message
#include <tmlib/dprintf.h>

#define CHECK_OK(a) rval = a; tmAssert(rval == TM_OK, rval)
#define CHECK_SUCCESS(a) Status = a; tmAssert(Status == statusSuccess, tmmanGetErrorString (Status))
#define PREFD prefd

#else //__TCS_VERSION__

// *****for tm1500, tcs4.41, tcs4.5f,
//shiu: what is equivalent for TCS4.41 should be filled here
#include <ops/undoc_custom_op.h>

#include <tmDbg.h>
#define PREFD prefd

#ifdef _DEBUG
#define DBGMSG(x)    DP(x)
//#define DBGMSG(x)    printf x
#else
#define DBGMSG(x)
#endif // _DEBUG
#define tmAssert(x,y)   DBG_ASSERT2 (x, ("%x\n", y))

#define CHECK_OK(x) rval = x; DBG_ASSERT2 (rval == TM_OK, ("%x\n", rval))
#define CHECK_SUCCESS(x) status = x; DBG_ASSERT2 (status == statusSuccess, ("%x\n", status))
#undef assert
#define assert(x) DBG_ASSERT(x)

#endif  //__TCS_VERSION__

#ifndef _TM5250_
#define DUALIADD(a, b) DSPIDUALADD(a, b)
#define DUALISUB(a, b) DSPIDUALSUB(a, b)
#endif

#define LSR8(a)  FUNSHIFT3(0, a)
#define LSR16(a) FUNSHIFT2(0, a)
#define LSR24(a) FUNSHIFT1(0, a)
#define LSL8(a)  FUNSHIFT1(a, 0)
#define LSL16(a) FUNSHIFT2(a, 0)
#define LSL24(a) FUNSHIFT3(a, 0)

#define _B1(x) ((x)&1)

// bug: only 24 bit in precision
#define idiv(a, b) ((int)(IFLOATRZ(a)/IFLOATRZ(b)))

#endif
