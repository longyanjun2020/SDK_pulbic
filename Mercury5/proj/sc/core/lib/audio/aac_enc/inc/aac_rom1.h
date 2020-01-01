#ifndef ROM1_H
#define ROM1_H

#include "ffr.h"
#include "fft.h"
#include "psy_const.h"
/*
  mdct
*/
#if 0
extern const Word16 LongWindowSine [FRAME_LEN_LONG];
extern const Word16 ShortWindowSine [FRAME_LEN_SHORT];
extern const Word16 LongWindowKBD [FRAME_LEN_LONG];
#else
extern const Word32 LongWindowSine [FRAME_LEN_LONG/2];

extern const Word32 LongWindowKBD [FRAME_LEN_LONG/2];
#endif

#if 0
extern const Word16 fftTwiddleTable[LSI_FFT_TWIDDLE_TABLE_SIZE+1];
#else
extern const Word32 fftTwiddleTable[LSI_FFT_TWIDDLE_TABLE_SIZE/2+1];
#endif


#endif