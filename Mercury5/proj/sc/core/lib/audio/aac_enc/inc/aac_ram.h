/*
   memory requirement in dynamic and static RAM
 */

#ifndef RAM_H
#define RAM_H

#include "ffr.h"
#include "psy_const.h"
#include "line_pe.h"

extern Word32 *mdctSpectrum;
#ifdef     USE_TNS
extern Word32 *scratchTNS;
#else
//extern Word32 TmpSpecBuf[1024];
extern Word32 *TmpSpecBuf;
#endif

//extern Word16 mdctDelayBuffer[MAX_CHANNELS * BLOCK_SWITCHING_OFFSET];
//extern Word16 quantSpec[MAX_CHANNELS * FRAME_LEN_LONG];
//extern Word16 scf[MAX_CHANNELS * MAX_GROUPED_SFB];
//extern UWord16 maxValueInSfb[MAX_CHANNELS * MAX_GROUPED_SFB];
//extern Word16 sideInfoTabLong[MAX_SFB_LONG + 1];
//extern Word16 sideInfoTabShort[MAX_SFB_SHORT + 1];

extern Word16 *mdctDelayBuffer;
extern Word16 *quantSpec;
extern Word16 *scf;
extern UWord16 *maxValueInSfb;
extern Word16 *sideInfoTabLong;
extern Word16 *sideInfoTabShort;
#endif
