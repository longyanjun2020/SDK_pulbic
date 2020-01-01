/*
   transposer
*/

#ifndef _LPP_TRANS_H
#define _LPP_TRANS_H



#include "aacplus_ffr.h"
#include "sbr_scale.h"
#include "sbrdecsettings.h"


#define MAX_NUM_PATCHES 6
#define GUARDBANDS      0              /*!< number of guardbands between every patch */
#define SHIFT_START_SB  1              /*!< lowest subband of source range */

typedef enum
{
  INVF_OFF = 0,
  INVF_LOW_LEVEL,
  INVF_MID_LEVEL,
  INVF_HIGH_LEVEL,
  INVF_SWITCHED /* not a real choice but used here to control behaviour */
}
INVF_MODE;

typedef struct _ACORR_COEFS{
  Word32  r11r;
  Word32  r22r;
  Word32  r01r;
  Word32  r02r;
  Word32  r12r;
#ifndef LP_SBR_ONLY
  Word32  r01i;
  Word32  r02i;
  Word32  r12i;
#endif
  Word32  det;
}ACORR_COEFS;


/** parameter set for one single patch */
typedef struct {
  Word16  sourceStartBand;   /*!< first band in lowbands where to take the samples from */ 
  Word16  sourceStopBand;    /*!< first band in lowbands which is not included in the patch anymore */
  Word16  guardStartBand;    /*!< first band in highbands to be filled with zeros in order to
			          reduce interferences between patches */
  Word16  targetStartBand;   /*!< first band in highbands to be filled with whitened lowband signal */
  Word16  targetBandOffs;    /*!< difference between 'startTargetBand' and 'startSourceBand' */
  Word16  numBandsInPatch;   /*!< number of consecutive bands in this one patch */
} PATCH_PARAM;

/** whitening factors for different levels of whitening 
    need to be initialized corresponding to crossover frequency */
typedef struct {
  Word32    off;                       /*!< bw factor for signal OFF */
  Word32    transitionLevel;
  Word32    lowLevel;                  /*!< bw factor for signal LOW_LEVEL */
  Word32    midLevel;                  /*!< bw factor for signal MID_LEVEL */
  Word32    highLevel;                 /*!< bw factor for signal HIGH_LEVEL */
} WHITENING_FACTORS;

/*! The transposer settings are calculated on a header reset and are shared by both channels. */
typedef struct {
  Word16  nCols;                       /*!< number subsamples of a codec frame */
  Word16  noOfPatches;                 /*!< number of patches */
  Word16  lbStartPatching;             /*!< first band of lowbands that will be patched */
  Word16  lbStopPatching;              /*!< first band that won't be patched anymore*/
  Word16  bwBorders[MAX_NUM_NOISE_VALUES];
  PATCH_PARAM    patchParam[MAX_NUM_PATCHES]; /*!< new parameter set for patching */
  WHITENING_FACTORS whFactors;                /*!< the pole moving factors for certain whitening levels as indicated
                                                   in the bitstream depending on the crossover frequency */
} TRANSPOSER_SETTINGS;


typedef struct
{
  TRANSPOSER_SETTINGS *pSettings;
  Word32    bwVectorOld[MAX_NUM_PATCHES];    /*!< pole moving factors of past frame */
  Word32   *lpcFilterStatesReal[LPC_ORDER];  /*!< pointer array to save filter states */
#ifndef LP_SBR_ONLY
  Word32   *lpcFilterStatesImag[LPC_ORDER];  /*!< pointer array to save filter states */
#endif
} 
SBR_LPP_TRANS;

typedef SBR_LPP_TRANS *HANDLE_SBR_LPP_TRANS;


void lppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans,
                    SBR_SCALE_FACTOR  *sbrScaleFactor,
                    Word32 **qmfBufferReal,
					#ifndef LP_SBR_ONLY
                    Word32 **qmfBufferImag,
					#endif
                    Word16 *degreeAlias,
                    Word16 timeStep,            
                    Word16 firstSlotOffset,     
                    Word16 lastSlotOffset,     
                    Word16 nInvfBands,
                    Word16 maxQmfSubbandAac,
                    INVF_MODE *sbr_invf_mode,    
                    INVF_MODE *sbr_invf_mode_prev,
                    Flag bUseLP

                    );


Word16
createLppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans,
                     Word16 highBandStartSb,
                     Word16 *v_k_master,
                     Word16 numMaster,
                     Word16 usb,
                     Word16 nCols,
                     Word16* noiseBandTable,
                     Word16 noNoiseBands,
                     Word32 fs,
                     Word16  chan);
  

Word16
resetLppTransposer (HANDLE_SBR_LPP_TRANS hLppTrans,
                    Word16 highBandStartSb,
                    Word16 *v_k_master,
                    Word16 numMaster,
                    Word16* noiseBandTable,
                    Word16 noNoiseBands,
                    Word16 usb,
                    Word32 fs);
                    
void lppTransposer_sub1(Word32 *ptemp1,Word32 *ptemp2,
										Word32 startSample,Word32 stopSample,
										Word32 **qmfBufferReal,Word32 hiBand,
										Word16 a0r,Word16 a0i,Word16 a1r,Word16 a1i,Word32 **qmfBufferImag); 
/*
void 
autoCorrelation2ndLP(ACORR_COEFS *ac, 
                     Word32 *realBuf,    
                     Word16 len          
                     );
                     */
/*
void
autoCorrelation2nd (ACORR_COEFS *ac,
                    Word32 *realBuf,   
                    Word32 *imagBuf,    
                    Word16 len);                                 
                    */

/*
Word16 findClosestEntry(Word16 goalSb, Word16 * v_k_master, 
	Word16 numMaster, Word16 direction);                    
*/

#endif /* _LPP_TRANS_H */

