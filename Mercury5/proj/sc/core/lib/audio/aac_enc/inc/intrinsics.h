/*  
   additional intrinsics
 */
#ifndef INTRINSIC_LIB_H
#define INTRINSIC_LIB_H


#include "basic_op.h"
#include "oper_32b.h"

#define SHORT_BITS 16
#define INT_BITS   32
#define OVL_BITS    8

/*
  min max macros
*/

#ifndef min
#define min(a,b) ( a < b ? a : b)
#endif

#ifndef max
#define max(a,b) ( a > b ? a : b)
#endif

Word32 fixmul(const Word32 a, const Word32 b);
Word32 fixmul_32x16b(const Word32 a, const Word16 b);


#endif
