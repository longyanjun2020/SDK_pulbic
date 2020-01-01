#ifndef __IC_PREDICT_H__
#define __IC_PREDICT_H__

#include "aacplus_channelinfo.h"

UWord32 MaxPredSfb(const UWord8 sr_index);
void PnsResetPredState(CIcsInfo *ics, CPredData *state);
void ResetAllPredictors(CPredData *state, UWord16 frame_len);
void IntraChannelPrediction(CIcsInfo *ics, Word32 *spec, CPredData *state,
                            UWord16 frame_len, Word16 sf_index);
#endif


