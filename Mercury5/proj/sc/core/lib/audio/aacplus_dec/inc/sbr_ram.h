/*
   memory layout
 */

#ifndef __SBR_RAM_H
#define __SBR_RAM_H

#include "aacplus_ffr.h"
#include "sbrdecsettings.h" /* for MAXNRSBRCHANNELS */
#include "sbrdecoder.h"
#include "env_extr.h"
#include "lpp_tran.h"


//extern Word16  sbr_CodecQmfStatesAnalysis[];
extern Word16  *sbr_CodecQmfStatesAnalysis;
//extern Word16  sbr_QmfStatesSynthesis[];
extern Word16  *sbr_QmfStatesSynthesis;

//extern Word16  sbr_GainSmooth_m[MAXNRSBRCHANNELS][MAX_FREQ_COEFFS];
//extern Word16  sbr_NoiseSmooth_m[MAXNRSBRCHANNELS][MAX_FREQ_COEFFS];
//extern Word16  sbr_GainSmooth_e[MAXNRSBRCHANNELS][MAX_FREQ_COEFFS];
extern Word16  *sbr_GainSmooth_m[MAXNRSBRCHANNELS];
extern Word16  *sbr_NoiseSmooth_m[MAXNRSBRCHANNELS];
extern Word16  *sbr_GainSmooth_e[MAXNRSBRCHANNELS];

//extern Word32  sbr_LpcFilterStatesReal[MAXNRSBRCHANNELS][LPC_ORDER][NO_ANALYSIS_CHANNELS];
extern Word32 *sbr_LpcFilterStatesReal_LPC_ORDER_0[MAXNRSBRCHANNELS];
extern Word32 *sbr_LpcFilterStatesReal_LPC_ORDER_1[MAXNRSBRCHANNELS];


#ifndef LP_SBR_ONLY
//extern Word32  sbr_LpcFilterStatesImag[MAXNRSBRCHANNELS][LPC_ORDER][NO_ANALYSIS_CHANNELS];
extern Word32 *sbr_LpcFilterStatesImag_LPC_ORDER_0[MAXNRSBRCHANNELS];
extern Word32 *sbr_LpcFilterStatesImag_LPC_ORDER_1[MAXNRSBRCHANNELS];
#endif

extern TRANSPOSER_SETTINGS sbr_TransposerSettings;
extern FREQ_BAND_DATA FreqBandData;

#ifdef LP_SBR_ONLY
//extern Word32  sbr_OverlapBuffer[MAXNRSBRCHANNELS][MAX_OV_COLS * NO_SYNTHESIS_CHANNELS];
extern Word32  *sbr_OverlapBuffer[MAXNRSBRCHANNELS];
#else
//extern Word32 sbr_OverlapBuffer[MAXNRSBRCHANNELS][2 * MAX_OV_COLS * NO_SYNTHESIS_CHANNELS];
extern Word32  *sbr_OverlapBuffer[MAXNRSBRCHANNELS];
#endif

extern SBR_PREV_FRAME_DATA PrevFrameData[MAXNRSBRCHANNELS];


#ifdef LP_SBR_ONLY
extern Word32  *WorkBuffer1;
#else
extern Word32  *WorkBuffer2;
//extern Word32  WorkBuffer1[MAX_COLS*NO_SYNTHESIS_CHANNELS];
extern Word32  *WorkBuffer1;
#endif

void Copy_PrevFrameData(SBR_PREV_FRAME_DATA * pdst, 
	SBR_PREV_FRAME_DATA * psrc);
	
int * inAACPLUS_SetSBRWorkingBuffer(int * ptr);

int	inAACPLUS_SetPSDECWorkingBuffer(PS_DEC * h_psdec);

#endif

