/*
   IMDCT transform
*/

#ifndef _IMDCT_H
#define _IMDCT_H


#include "typedef.h"

void CLongBlock_InverseTransform(Word32 data[],
                                 Word16 *imdctScale);

void CShortBlock_InverseTransform(Word32 data[],
                                  Word16 *imdctScale);
/*
extern void scaledFFT_stage1to2(Word32 x[], Word32 count);
extern void scaledFFT_stage3(Word32 x[],  Word32 ldn, const Word16 SineTable[]);    
*/
#endif /* #ifndef IMDCT_H */
