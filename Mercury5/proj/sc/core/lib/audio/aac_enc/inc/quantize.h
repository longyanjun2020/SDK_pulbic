/*
   Quantization
 */
#ifndef _QUANTIZE_H_
#define _QUANTIZE_H_
#include "ffr.h"
#include "intrinsics.h"

/* quantizing */

#define MAX_QUANT 8191

void QuantizeSpectrum(Word16 sfbCnt, 
                      Word16 maxSfbPerGroup,
                      Word16 sfbPerGroup,
                      Word16 *sfbOffset, Word32 *mdctSpectrum,
                      Word16 globalGain, Word16 *scalefactors,
                      Word16 *quantizedSpectrum);

#endif /* _QUANTIZE_H_ */
