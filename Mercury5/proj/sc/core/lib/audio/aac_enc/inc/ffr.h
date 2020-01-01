/*
   fractional arithmetric
 */
#ifndef __FFR_H
#define __FFR_H


#include <stdarg.h>
#include "intrinsics.h"
#include "typedef.h"

#define INV_TABLE_SIZE         256   /*!< Number of entries for 0.5/x lookup table. */
#define SQRT_TABLE_SIZE        256   /*!< Number of entries for sqrt(x) lookup table. */

#define POW2_TABLE_BITS 8
#define POW2_TABLE_SIZE (1<<POW2_TABLE_BITS)

Word16 ffr_iLog4(Word32 value);
Word32 ffr_pow2_xy(Word32 x, Word32 y);
Word32 ffr_div32_32(Word32 x, Word32 y);
Word16 ffr_Short_Div(Word16 x, Word16 y);
Word32 ffr_Integer_Div(Word32 x, Word32 y);
Word32 ffr_divideWord32(Word32 a, Word32 b);
Word32 ffr_sqrt(Word32 op, Word32 accuracy);
Word16 ffr_getScalefactorOfShortVector(const Word16 *vector, Word16 len);
Word16 ffr_getScalefactorOfShortVectorStride(const Word16 *vector, Word16 len, Word16 stride);

Word16 ffr_norm32(Word32 x);
#endif
