/*
   Optimization for ARM platform
 */
#ifndef _OPTIMIZE_H_
#define _OPTIMIZE_H_

#include "typedef.h"
#include "block_switch.h"
#include "interface.h"
#include "line_pe.h"
#include "adj_thr.h"

#define MANT_DIGITS 9
#define MANT_SIZE   (1<<MANT_DIGITS)
#define ENERGY_SHIFT 8

#define FF_SQRT_BITS                    7
#define FF_SQRT_TABLE_SIZE              (1<<FF_SQRT_BITS - 1<<(FF_SQRT_BITS-2))

#define  minSnrLimit    0x6666 /* 1 dB */
                   
Word32 CalcWindowEnergy(BLOCK_SWITCHING_CONTROL *blockSwitchingControl,
                        Word16 *timeSignal,
                        Word16 chIncrement,
                        Word16 windowLen);
                                      
void CalcFormFactorChannel(Word16 *logSfbFormFactor,
                           Word16 *sfbNRelevantLines,
                           Word16 *logSfbEnergy,
                           PSY_OUT_CHANNEL *psyOutChan);                   
                   
void assimilateMultipleScf(PSY_OUT_CHANNEL *psyOutChan,
                           Word16 *scf, 
                           Word16 *minScf,
                           Word32 *sfbDist, 
                           Word16 *sfbConstPePart,
                           Word16 *logSfbEnergy,
                           Word16 *logSfbFormFactor,
                           Word16 *sfbNRelevantLines);                   
                   
void assimilateSingleScf(PSY_OUT_CHANNEL *psyOutChan,
                         Word16 *scf, 
                         Word16 *minScf,
                         Word32 *sfbDist, 
                         Word16 *sfbConstPePart,
                         Word16 *logSfbEnergy,
                         Word16 *logSfbFormFactor,
                         Word16 *sfbNRelevantLines,
                         Word16 *minScfCalculated,
                         Flag    restartOnSuccess);     
                         
void calcSfbPe(PE_DATA *peData,
               PSY_OUT_CHANNEL psyOutChannel[MAX_CHANNELS],
               const Word16 nChannels);                                       
              
void adaptMinSnr(PSY_OUT_CHANNEL     psyOutChannel[MAX_CHANNELS],
                 Word16              logSfbEnergy[MAX_CHANNELS][MAX_GROUPED_SFB],
                 MINSNR_ADAPT_PARAM *msaParam,
                 const Word16        nChannels);              
              
void reduceThresholds(PSY_OUT_CHANNEL  psyOutChannel[MAX_CHANNELS],
                      Word16           ahFlag[MAX_CHANNELS][MAX_GROUPED_SFB],
                      Word32           thrExp[MAX_CHANNELS][MAX_GROUPED_SFB],
                      const Word16     nChannels,
                      const Word32     redVal);
                      
void calcPeNoAH(Word16          *pe,
                Word16          *constPart,
                Word16          *nActiveLines,
                PE_DATA         *peData,
                Word16           ahFlag[MAX_CHANNELS][MAX_GROUPED_SFB],
                PSY_OUT_CHANNEL  psyOutChannel[MAX_CHANNELS],
                const Word16     nChannels);
                
void reduceMinSnr(PSY_OUT_CHANNEL  psyOutChannel[MAX_CHANNELS], 
                  PE_DATA         *peData, 
                  Word16           ahFlag[MAX_CHANNELS][MAX_GROUPED_SFB],
                  const Word16     nChannels,
                  const Word16     desiredPe);                                        
  
void count1_2_3_4_5_6_7_8_9_10_11(const Word16 *values,
                                  const Word16  width,
                                  Word16       *bitCount);
                                  
void EstimateScaleFactorsChannel(PSY_OUT_CHANNEL *psyOutChan,
                                 Word16          *scf,
                                 Word16          *globalGain,
                                 Word16          *logSfbEnergy,
                                 Word16          *logSfbFormFactor,
                                 Word16          *sfbNRelevantLines);                                    
                   
#endif                   