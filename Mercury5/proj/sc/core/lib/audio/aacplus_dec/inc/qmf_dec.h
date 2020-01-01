/*
   QMF filtering
*/

#ifndef __QMF_DEC_H
#define __QMF_DEC_H


#include "sbr_scale.h"
#include "sbrdecsettings.h"
#include "aacplus_intrinsics.h"

#ifndef MONO_ONLY
#include "ps_dec.h"
#endif

typedef struct _SBR_QMF_FILTER_BANK
{
  Word32 dctTempBuffer[64];        /*!< dct temp buffer  (LP-SBR)*/


  Word16 no_channels;


#if 1//ndef ARM_OPT
  const Word16 *p_filter_ana;      /*!< Pointer to filter coefficients */

  const Word16 *p_filter;          /*!< Pointer to filter coefficients */
#else
		const Word32 *p_filter_ana;      /*!< Pointer to filter coefficients */
	  const Word32 *p_filter;          /*!< Pointer to filter coefficients */
#endif
  Word16 *ralt_sin_twiddle;        /*!< dct twiddle factors (LP-SBR) */ 

#ifndef LP_SBR_ONLY
#if 1//ndef ARM_OPT
  const Word16 *cos_twiddle;       /*!< Twiddle factors */
  const Word16 *sin_twiddle;       /*!< Twiddle factors */
	const Word16 *alt_sin_twiddle;   /*!< Twiddle factors */
#else
  const Word32 *cos_twiddle;       /*!< Twiddle factors */
  const Word32 *sin_twiddle;       /*!< Twiddle factors */
  const Word32 *alt_sin_twiddle;   /*!< Twiddle factors */
#endif  
  
  const Word16 *t_cos;             /*!< Twiddle factors */
  const Word16 *t_sin;             /*!< Twiddle factors */
#endif

  Word16 *FilterStatesAna;         /*!< Pointer to buffer of filter states */
  Word16 *FilterStates;            /*!< Pointer to buffer of filter states */
  
  Word16 no_col;                   /*!< Number of time slots */

  Word16 lsb;                      /*!< sbr start subband */
  Word16 usb;                      /*!< sbr stop subband  */

  Word16 qmf_filter_state_size;
}
SBR_QMF_FILTER_BANK, *HANDLE_SBR_QMF_FILTER_BANK;


void 
cplxAnalysisQmfFiltering(const Word16 *timeIn,
                         SBR_SCALE_FACTOR  *sbrScaleFactor,
                         Word32 **qmfReal,
#ifndef LP_SBR_ONLY
                         Word32 **qmfImag,
#endif
                         HANDLE_SBR_QMF_FILTER_BANK qmfBank,
                         Flag bUseLP);

void 
cplxSynthesisQmfFiltering(Word32 **qmfReal,
#ifndef LP_SBR_ONLY
                          Word32 **qmfImag,
#endif
                          Word32 splitSlot,
                          SBR_SCALE_FACTOR *sbrScaleFactor,
                          Word16 *timeOut,
                          HANDLE_SBR_QMF_FILTER_BANK qmfBank,
#ifndef MONO_ONLY
                          HANDLE_PS_DEC hPS,
                          Flag active,
#endif
                          Flag bUseLP);

Word32
createCplxAnalysisQmfBank(HANDLE_SBR_QMF_FILTER_BANK h_sbrQmf,
                          SBR_SCALE_FACTOR  *sbrScaleFactor,
                          Word16 noCols,
                          Word16 usb,
                          Word16 chan);

Word32
createCplxSynthesisQmfBank(HANDLE_SBR_QMF_FILTER_BANK h_sbrQmf,
                           SBR_SCALE_FACTOR *sbrScaleFactor,
                           Word16 noCols,
                           Word16 lsb,
                           Word16 usb,
                           Word16 chan,
                           Flag bDownSample);

/*                           
void 
SynthesisPolyphaseFiltering(Word16 *pFilterStates,             
                            const Word32 *pFilter,             
                            Word32 *pReal,                     
                            Word32 *pImag,                     
                            Word16 *pTimeOut,                  
                            Word16 outScalefactor,            
                            Word32 no_synthesis_channels,
                            Word16 qmf_filter_state_syn_size);                          
                            */ 
/*           
void           
inverseModulationLP(Word32 *qmfReal,                    
                     Word32 *qmfReal2,                    
                     const Word32 scaleFactorLowBand,    
                     const Word32 scaleFactorHighBand,  
                     HANDLE_SBR_QMF_FILTER_BANK synQmf  
                   );
                   */
                       
/*                   
void
inverseModulation (Word32 *qmfReal,                     
                   Word32 *qmfImag,                      
                   Word16 scaleFactorLowBand,            
                   Word16 scaleFactorHighBand,           
                   HANDLE_SBR_QMF_FILTER_BANK synQmf     
                   );                         
                   */ 
                           

extern void dct3_fun1(Word32 *data, Word32 *tmp, Word32 *pSinTwiddle);
extern void inverseModulation_sub1(Word32 *qmfReal,Word32 *qmfImag);
                            
extern void synthesis_fun(Word32 *ptr1, 
                    Word16 *ptrF,
                    Word16 *pFilterState,
                    Word32 scale,
                    Word32 *pReal,
                    Word16 *pTimeOut,
                    const Word32 *pFilter,
                    const Word32 *pFilterR);                            
                            
#endif
