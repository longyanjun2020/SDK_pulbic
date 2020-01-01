/*
   Psychoacoustic major function block
 */
#ifndef _PSYMAIN_H
#define _PSYMAIN_H

#include "psy_configuration.h"
#include "qc_data.h"
#include "aac_ram.h"
#include "tns_func.h"

/*
  psy kernel
*/
typedef struct  {
  PSY_CONFIGURATION_LONG  psyConfLong;           /* Word16 size: 515 */
  PSY_CONFIGURATION_SHORT psyConfShort;          /* Word16 size: 167 */
  PSY_DATA                psyData[MAX_CHANNELS]; /* Word16 size: MAX_CHANNELS*1669*/
#ifdef     USE_TNS    
  TNS_DATA                tnsData[MAX_CHANNELS]; /* Word16 size: MAX_CHANNELS*235 */
  Word32*                 pScratchTns;  
#endif  
}PSY_KERNEL; /* Word16 size: 2587 / 4491 */


Word16 PsyNew( PSY_KERNEL  *hPsy, Word32 nChan);
Word16 PsyDelete( PSY_KERNEL  *hPsy);

Word16 PsyOutNew( PSY_OUT *hPsyOut);
Word16 PsyOutDelete( PSY_OUT *hPsyOut);

Word16 psyMainInit( PSY_KERNEL *hPsy,
                    Word32 sampleRate,
                    Word32 bitRate,
                    Word16 channels,
                    Word16 tnsMask,
                    Word16 bandwidth);
#ifdef     USE_TNS 
Word16 psyMain(Word16                   nChannels,   /*!< total number of channels */              
               ELEMENT_INFO             *elemInfo,
               Word16                   *timeSignal, /*!< interleaved time signal */ 
               PSY_DATA                 psyData[MAX_CHANNELS],
               TNS_DATA                 tnsData[MAX_CHANNELS],
               PSY_CONFIGURATION_LONG*  psyConfLong,
               PSY_CONFIGURATION_SHORT* psyConfShort,                 
               PSY_OUT_CHANNEL          psyOutChannel[MAX_CHANNELS],            
               Word32                   *pScratchTns);
#else
Word16 psyMain(Word16                   nChannels,   /*!< total number of channels */              
               ELEMENT_INFO             *elemInfo,
               Word16                   *timeSignal, /*!< interleaved time signal */ 
               PSY_DATA                 psyData[MAX_CHANNELS],
               PSY_CONFIGURATION_LONG*  psyConfLong,
               PSY_CONFIGURATION_SHORT* psyConfShort,                 
               PSY_OUT_CHANNEL          psyOutChannel[MAX_CHANNELS]);

#endif



#ifdef     USE_TNS
extern  Word32 Calc_Sum32(Word32 *ptr32, 
                          Word32 Len,
                          Word32 Acc); 
#endif

extern  Word32 Threshold_Calc(Word32 *ptrI,
                              Word32 *ptrO, 
                              Word16 ratio,
                              Word32 clipEnergy,
                              Word32 Len);


#endif /* _PSYMAIN_H */
