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
* @file    : hw_p_eq.h
* @version :
* @author  : CA.Wang
* @brief   : Hardware Parameter EQ
*/

#ifndef __HW_P_EQ_H__
#define __HW_P_EQ_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "app_datatype.h"

/*============================================================================*/
// Extern definition
/*============================================================================*/
//...

/*============================================================================*/
// Macro definition
/*============================================================================*/
/*------------------ Process Data Type ------------------*/
#define POST_PROC_HWPEQ_32BITS_Q8_DATA

/*---------------- Print Message Switch -----------------*/
#define ENABLE_HWPEQ_PARSER_PRINTF

/*-------------------- Channel size ---------------------*/
#define HWPEQ_MAX_CH_NUM 2

/*-------------------- EQ band size ---------------------*/
#define HWPEQ_BAND_NUM   8

/*-------------------- Filter define --------------------*/
#define HWPEQ_BIQUAD_A_COEFF_SIZE 3
#define HWPEQ_BIQUAD_B_COEFF_SIZE 2
#define HWPEQ_BIQUAD_FILTER_COEFF_SIZE (HWPEQ_BIQUAD_A_COEFF_SIZE + HWPEQ_BIQUAD_B_COEFF_SIZE)

#define HWPEQ_BIQUAD_X_MEM_SIZE 2
#define HWPEQ_BIQUAD_Y_MEM_SIZE 2
#define HWPEQ_BIQUAD_FILTER_MEM_SIZE (HWPEQ_BIQUAD_X_MEM_SIZE + HWPEQ_BIQUAD_Y_MEM_SIZE)

/*----------------------- Q Bound -----------------------*/
//   Q  = 0.2 ~ 20
#define HWPEQ_MIN_Q_IDX (-2)
#define HWPEQ_MAX_Q_IDX (20)

/*----------------------- G Bound -----------------------*/
//   G  = -18 : 0.5 : 18 dB
#define HWPEQ_NOTCH_GAIN_IDX (-37)
#define HWPEQ_MIN_GAIN_IDX   (-36)
#define HWPEQ_MAX_GAIN_IDX   (36)

/*-------------------- PreScale Bound -------------------*/
//   GG = -12 : 0.5 : 12 dB
#define HWPEQ_MIN_PRESCALEGAIN_IDX (-24)
#define HWPEQ_MAX_PRESCALEGAIN_IDX (24)

/*---------------------- Fc Bound -----------------------*/
#define HWPEQ_MAX_FC_48K 23046 // Hz
#define HWPEQ_MAX_FC_44K 21170 // Hz
#define HWPEQ_MAX_FC_32K 15350 // Hz
#define HWPEQ_MAX_FC_24K 11520 // Hz
#define HWPEQ_MAX_FC_22K 10584 // Hz
#define HWPEQ_MAX_FC_16K 7680  // Hz
#define HWPEQ_MAX_FC_12K 5760  // Hz
#define HWPEQ_MAX_FC_11K 5292  // Hz
#define HWPEQ_MAX_FC_8K  3840  // Hz

#define HWPEQ_MIN_FC 20
#define HWPEQ_MAX_FC 23000

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_HWPEQ_32BITS_Q8_DATA
typedef tS32 HWPEQ_PROC_DATA_TYPE;
#else
typedef tS16 HWPEQ_PROC_DATA_TYPE;
#endif

/*------------------- PEQ Filter Type -------------------*/
typedef enum {
    HWPEQ_LOW_SHELVING_FILTER  = 0,
    HWPEQ_HIGH_SHELVING_FILTER = 1,
    HWPEQ_PEAKING_FILTER       = 2,
    HWPEQ_NOTCH_FILTER         = 3,
} HWPEQ_FILTER_TYPE_e;

/*---------------------- Interface ----------------------*/
typedef struct
{
    // IP specific controls
    tU8    bEn;
    tS32   s32GlbGainIdx;
    tS32   s32GIdx[HWPEQ_BAND_NUM];
    tS32   s32FC[  HWPEQ_BAND_NUM];
    tS32   s32QIdx[HWPEQ_BAND_NUM];
    tU8    bPass[  HWPEQ_BAND_NUM];
}M_HWPEQ_PAR_s;
#define SIZEOF_HWPEQ_DATA (sizeof(tU8) + sizeof(tS32) + (sizeof(tS32) * HWPEQ_BAND_NUM) + (sizeof(tS32) * HWPEQ_BAND_NUM) + (sizeof(tS32) * HWPEQ_BAND_NUM) + (sizeof(tU8) * HWPEQ_BAND_NUM) )

typedef struct
{
    // IP control interface
    M_HWPEQ_PAR_s sHWPEQ_Ctr;
    tU8   bUpdateFlag;

    // IP public variable
    tS32  s32ChumN;
    tS32  s32FrmSz;
    tS32  s32SmpFreq;

    // IP specific variables
    HWPEQ_FILTER_TYPE_e  eFilterType[HWPEQ_BAND_NUM];
    tS32   s32BiquadCoef[HWPEQ_BAND_NUM][HWPEQ_BIQUAD_FILTER_COEFF_SIZE];
}M_HWPEQ_MAIN_s;

typedef struct
{
    tU32 u32InvQ;
    tU32 u32V0;
    tU32 u32Sqrt2V0;

    tS32 s32K;
    tS32 s32KxK;

    tU32 u32Fc;
    tU32 u32Fs;
}M_HWPEQ_COEFFPAR_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_SetStrcPower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_SetStrcGlbGain(void* void_pSet, tS32 s32GGIDx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_SetStrcBandPar(void* void_pSet, tS32 s32BandIdx, tS32 s32GainIdx, tS32 s32Fc, tS32 s32QIdx, tU8 bBandPass);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_GetStrcPower(void* void_pSet, tU8* pbEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_GetStrcGlbGain(void* void_pSet, tS32* ps32GGIDx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWPEQPar_GetStrcBandPar(void* void_pSet, tS32 s32BandIdx, tS32* ps32GainIdx, tS32* ps32Fc, tS32* ps32QIdx, tU8* pbBandPass);

// Main
tBOOL AUD_HWPEQMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_HWPEQMain_Check(void* void_pIP, void* void_pSet, tU8 bRtChangeGain, tU8* pbUpdateFlag);
tBOOL AUD_HWPEQMain_Update(void* void_pIP, void* void_pSet, tU8 bRtChangeGain);
tBOOL AUD_HWPEQMain_Proc(void* void_pIP, tS32* ptProcBuf, tS32 s32ProcSizePerCh);
tBOOL AUD_HWPEQMain_Close(void* void_pIP , void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __HW_P_EQ_H__ */

