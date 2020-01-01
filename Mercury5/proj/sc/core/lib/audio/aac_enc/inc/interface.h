/*
   Interface psychoaccoustic/quantizer
 */
#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "psy_const.h"
#include "psy_data.h"
#include "ffr.h"


enum
{
  MS_NONE = 0,
  MS_SOME = 1,
  MS_ALL  = 2
};



typedef struct {
  Word16  sfbCnt;
  Word16  sfbPerGroup;
  Word16  maxSfbPerGroup;
  Word16  windowSequence;
  Word16  windowShape;
  Word16  groupingMask;
//  Word16  sfbOffsets[MAX_GROUPED_SFB+1];
  Word16  *sfbOffsets;
  Word32 *sfbEnergy; 
  Word32 *sfbSpreadedEnergy;
  Word32 *sfbThreshold;       
  Word32 *mdctSpectrum;        
  Word16  mdctScale; 
  Word32  sfbEnSumLR;
//  Word16  sfbMinSnr[MAX_GROUPED_SFB];
  Word16  *sfbMinSnr;
  TNS_INFO tnsInfo;
} PSY_OUT_CHANNEL; /* Word16 size: 14 + 60(MAX_GROUPED_SFB) + 112(TNS_INFO) = 186 */


typedef struct {
  /* information specific to each channel */
  PSY_OUT_CHANNEL  psyOutChannel[MAX_CHANNELS];
}PSY_OUT;

void BuildInterface(Word32                 *mdctSpectrum,
                    const Word16            mdctScale,
                    SFB_THRESHOLD          *sfbThreshold,
                    SFB_ENERGY             *sfbEnergy,
                    SFB_ENERGY             *sfbSpreadedEnergy,
                    const SFB_ENERGY_SUM    sfbEnergySumLR,
                    const Word16            windowSequence,
                    const Word16            windowShape,
                    const Word16            sfbCnt,
                    const Word16           *sfbOffset,
                    const Word16            maxSfbPerGroup,
                    const Word16           *groupedSfbMinSnr,
                    const Word16            noOfGroups,
                    const Word16           *groupLen,
                    PSY_OUT_CHANNEL        *psyOutCh);

#endif /* _INTERFACE_H */
