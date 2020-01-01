/* config.h: hardware details of host system for CLIB */
/* Copyright (C) Codemist Ltd, 1988                */
/* Copyright (C) Advanced RISC Machines Ltd., 1991 */

#ifndef __PRINTF_H__
#define __PRINTF_H__

#define HOSTSEX_l

#ifdef HOSTSEX_b /* ig__ENDIAN */
#  define BYTESEX_ODD 1
#else
#  ifdef HOSTSEX_l /* itle_ENDIAN */
#  else
#error byte sex not specified - assume little endian
#  endif
#  define BYTESEX_EVEN 1
#endif

#define MACHINE "ARM"

#define HOST_HAS_BCD_FLT 1
#ifndef SOFTWARE_FLOATING_POINT
#  define HOST_HAS_TRIG 1         /* and ieee trig functions     */
#  define IEEE 1
#  undef OTHER_WORD_ORDER_FOR_FP_NUMBERS
#  define DO_NOT_SUPPORT_UNNORMALIZED_NUMBERS 1
#endif


#ifdef __FLOATING_POINT__
#ifndef OTHER_WORD_ORDER_FOR_FP_NUMBERS

#  ifdef BYTESEX_EVEN
typedef union {struct {int mhi:20, x:11, s:1; unsigned mlo; } i;
               double d; } fp_number;
#  else
typedef union {struct {int s:1, x:11, mhi:20; unsigned mlo; } i;
               double d; } fp_number;
#  endif

#else   /* OTHER_WORD_ORDER_FOR_FP_NUMBERS */

#  ifdef BYTESEX_EVEN
typedef union {struct {unsigned mlo; int mhi:20, x:11, s:1; } i;
               double d; } fp_number;
#  else
typedef union {struct {unsigned mlo; int s:1, x:11, mhi:20; } i;
           double d; } fp_number;
#  endif
#endif  /* OTHER_WORD_ORDER_FOR_FP_NUMBERS */


#define _fp_normalize(high, low)                                          \
    {   fp_number temp;        /* access to representation     */         \
    double temp1;                                                     \
    temp.d = high;         /* take original number         */         \
    temp.i.mlo = 0;        /* make low part of mantissa 0  */         \
    temp1 = high - temp.d; /* the bit that was thrown away */         \
    low += temp1;          /* add into low-order result    */         \
    high = temp.d;                                                    \
    }

#endif /* __FLOATING_POINT__ */
#endif

/* end of printf.h */
