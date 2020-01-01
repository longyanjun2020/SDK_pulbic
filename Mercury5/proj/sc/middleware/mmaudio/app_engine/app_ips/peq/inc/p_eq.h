////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    : p_eq.h
* @version :
* @author  : CA.Wang
* @brief   : parameter EQ
*/

#ifndef __P_EQ_H__
#define __P_EQ_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "app_datatype.h"
#include "app_mac.h"
/*============================================================================*/
// Extern definition
/*============================================================================*/
//...

/*============================================================================*/
// Macro definition
/*============================================================================*/
/*------------------ Process Data Type ------------------*/
#define POST_PROC_PEQ_32BITS_Q8_DATA

/*---------------- Print Message Switch -----------------*/
#define ENABLE_PEQ_PARSER_PRINTF

/*------------------- PEQ Band Fading -------------------*/
//#define USING_PI_FOR_BAND_FADING

#ifdef USING_PI_FOR_BAND_FADING
#define PEQ_FADING_STEPS 1024
#define PEQ_FADING_SHIFT 10
#endif

/*-------------------- Channel size ---------------------*/
#define PEQ_MAX_CH_NUM 2

/*-------------------- EQ band size ---------------------*/
#define PEQ_BAND_NUM   5

/*-------------------- Filter define --------------------*/
#define PEQ_BIQUAD_A_COEFF_SIZE 3
#define PEQ_BIQUAD_B_COEFF_SIZE 2
#define PEQ_BIQUAD_FILTER_COEFF_SIZE (PEQ_BIQUAD_A_COEFF_SIZE + PEQ_BIQUAD_B_COEFF_SIZE)

#define PEQ_BIQUAD_X_MEM_SIZE 2
#define PEQ_BIQUAD_Y_MEM_SIZE 2
#define PEQ_BIQUAD_FILTER_MEM_SIZE (PEQ_BIQUAD_X_MEM_SIZE + PEQ_BIQUAD_Y_MEM_SIZE)

/*----------------------- Q Bound -----------------------*/
//   Q  = 0.2 ~ 20
#define PEQ_MIN_Q_IDX (-2)
#define PEQ_MAX_Q_IDX (20)

/*----------------------- G Bound -----------------------*/
//   G  = -18 : 0.5 : 18 dB
#define PEQ_NOTCH_GAIN_IDX (-37)
#define PEQ_MIN_GAIN_IDX   (-36)
#define PEQ_MAX_GAIN_IDX   (36)

/*---------------------- GG Bound -----------------------*/
//   GG = -32 : 0.5 : 32 dB
#define PEQ_MIN_GLBGAIN_IDX (-64)
#define PEQ_MAX_GLBGAIN_IDX (64)

/*---------------------- Fc Bound -----------------------*/
#define PEQ_MAX_FC_48K 23046 // Hz
#define PEQ_MAX_FC_44K 21170 // Hz
#define PEQ_MAX_FC_32K 15350 // Hz
#define PEQ_MAX_FC_24K 11520 // Hz
#define PEQ_MAX_FC_22K 10584 // Hz
#define PEQ_MAX_FC_16K 7680  // Hz
#define PEQ_MAX_FC_12K 5760  // Hz
#define PEQ_MAX_FC_11K 5292  // Hz
#define PEQ_MAX_FC_8K  3840  // Hz

#define PEQ_MIN_FC 20
#define PEQ_MAX_FC 23000

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_PEQ_32BITS_Q8_DATA
typedef tS32 PEQ_PROC_DATA_TYPE;
#else
typedef tS16 PEQ_PROC_DATA_TYPE;
#endif

/*------------------- PEQ Filter Type -------------------*/
typedef enum {
    PEQ_LOW_SHELVING_FILTER  = 0,
    PEQ_HIGH_SHELVING_FILTER = 1,
    PEQ_PEAKING_FILTER       = 2,
    PEQ_NOTCH_FILTER         = 3,
}PEQ_FILTER_TYPE_e;

/*---------------------- Interface ----------------------*/
typedef struct
{
    // IP specific controls
    tU8    bEn;
    tS32   s32GlbGainIdx;
    tS32   s32GIdx[PEQ_BAND_NUM];
    tS32   s32FC[  PEQ_BAND_NUM];
    tS32   s32QIdx[PEQ_BAND_NUM];
    tU8    bPass[  PEQ_BAND_NUM];
}M_PEQ_PAR_s;
#define SIZEOF_PEQ_DATA (sizeof(tU8) + sizeof(tS32) + (sizeof(tS32) * PEQ_BAND_NUM) + (sizeof(tS32) * PEQ_BAND_NUM) + (sizeof(tS32) * PEQ_BAND_NUM) + (sizeof(tU8) * PEQ_BAND_NUM) )

typedef struct
{
    // IP control interface
    M_PEQ_PAR_s sPEQ_Ctr;
    tU8	   bUpdateFlag;

    // IP public variable
    PEQ_PROC_DATA_TYPE* ptFrmBuf;
    tS32    s32ChumN;
    tS32    s32FrmSz;
    tS32    s32SmpFreq;

    // IP specific variables
    PEQ_FILTER_TYPE_e  eFilterType[PEQ_BAND_NUM];
    tS32   s32BiquadCoef[PEQ_BAND_NUM][PEQ_BIQUAD_FILTER_COEFF_SIZE];
    tS32   s32BiquadZn[  PEQ_BAND_NUM][PEQ_MAX_CH_NUM][PEQ_BIQUAD_FILTER_MEM_SIZE];

#ifdef USING_PI_FOR_BAND_FADING
    tS32   s32OldBiquadCoef[PEQ_BAND_NUM][PEQ_MAX_CH_NUM][PEQ_BIQUAD_FILTER_COEFF_SIZE];
    tS32   s32CoefDelta[    PEQ_BAND_NUM][PEQ_BIQUAD_FILTER_COEFF_SIZE];
    tS32   s32CoefCount[    PEQ_BAND_NUM][PEQ_MAX_CH_NUM];
#endif
}M_PEQ_MAIN_s;

typedef struct
{
    tU32 u32InvQ;
    tU32 u32V0;
    tU32 u32Sqrt2V0;

    tS32 s32K;
    tS32 s32KxK;

    tU32 u32Fc;
    tU32 u32Fs;
}M_PEQ_COEFFPAR_s;

/*============================================================================*/
// Variable definition
/*============================================================================*/
//...

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif

// Parser
tS32 POSTPROCMGR_ATTR_16BITS AUD_PEQPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_PEQPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_PEQPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_PEQPar_SetStrcPower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_PEQPar_SetStrcGlbGain(void* void_pSet, tS32 s32GGIDx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_PEQPar_SetStrcBandPar(void* void_pSet, tS32 s32BandIdx, tS32 s32GainIdx, tS32 s32Fc, tS32 s32QIdx, tU8 bBandPass);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_PEQPar_GetStrcPower(void* void_pSet, tU8* bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_PEQPar_GetStrcGlbGain(void* void_pSet, tS32* s32GGIDx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_PEQPar_GetStrcBandPar(void* void_pSet, tS32 s32BandIdx, tS32* ps32GainIdx, tS32* ps32Fc, tS32* ps32QIdx, tU8* pbBandPass);

// Main
tBOOL AUD_PEQMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_PEQMain_Check(void* void_pIP, void* void_pSet, tU8 bRtChangeGain, tU8* pbUpdateFlag);
tBOOL AUD_PEQMain_Update(void* void_pIP, void* void_pSet, tU8 bRtChangeGain);
tBOOL AUD_PEQMain_ChangeGain(void* void_pIP, tS32 s32BandIdx, tS32 s32GainIdx );
tBOOL AUD_PEQMain_GetGain(void* void_pIP, tS32 s32BandIdx, tU8* pbBandPass, tS32* ps32GainIdx);
tBOOL AUD_PEQMain_Proc(void* void_pIP, PEQ_PROC_DATA_TYPE* ptProcBuf, tS32 s32ProcSizePerCh);
tBOOL AUD_PEQMain_Close(void* void_pIP , void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __P_EQ_H__ */

