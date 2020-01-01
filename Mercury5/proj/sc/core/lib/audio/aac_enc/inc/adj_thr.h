/*
   Threshold compensation
 */
#ifndef __ADJ_THR_H
#define __ADJ_THR_H

#include "adj_thr_data.h"
#include "qc_data.h"
#include "interface.h"

/* values for avoid hole flag */
enum _avoid_hole_state {
  NO_AH              =0,
  AH_INACTIVE        =1,
  AH_ACTIVE          =2
};


Word16 bits2pe(const Word16 bits);

Word32 AdjThrNew(ADJ_THR_STATE** phAdjThr,
                 Word32 nElements);

void AdjThrDelete(ADJ_THR_STATE *hAdjThr);

void AdjThrInit(ADJ_THR_STATE *hAdjThr,
                const Word32 peMean,
                Word32 chBitrate);

void AdjustThresholds(ADJ_THR_STATE *adjThrState,
                      ATS_ELEMENT* AdjThrStateElement,
                      PSY_OUT_CHANNEL psyOutChannel[MAX_CHANNELS],
                      Word16 *chBitDistribution,
                      Word16 logSfbEnergy[MAX_CHANNELS][MAX_GROUPED_SFB],
                      Word16 sfbNRelevantLines[MAX_CHANNELS][MAX_GROUPED_SFB],
                      const Word16 nChannels,
                      QC_OUT_ELEMENT* qcOE,
                      const Word16 avgBits,
                      const Word16 bitresBits,
                      const Word16 maxBitresBits,
                      const Word16 maxBitFac,
                      const Word16 sideInfoBits);

void AdjThrUpdate(ATS_ELEMENT *AdjThrStateElement,
                  const Word16 dynBitsUsed);


#endif
