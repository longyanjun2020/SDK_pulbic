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
* @file    : hw_g_eq.h
* @version :
* @author  : CA.Wang
* @brief   : Hardware Graphic EQ
*/

#ifndef __HW_G_EQ_H__
#define __HW_G_EQ_H__

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
#define POST_PROC_HWGEQ_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_HWGEQ_PARSER_PRINTF

/*-------------------- Channel size ---------------------*/
#define HWGEQ_MAX_CH_NUM 2

/*-------------------- EQ band size ---------------------*/
#define HWGEQ_BAND_NUM   7 // 5 and 7

/*-------------------- Filter define --------------------*/
#define HWGEQ_7BAND_FILTER_NUM 6
#define HWGEQ_5BAND_FILTER_NUM 4

#define HWGEQ_AP_A_COEFF_SIZE 1
#define HWGEQ_AP_B_COEFF_SIZE 2
#define HWGEQ_AP_FILTER_COEFF_SIZE (HWGEQ_AP_A_COEFF_SIZE + HWGEQ_AP_B_COEFF_SIZE)

/*----------------------- G Bound -----------------------*/
//   G  = -12 : 0.5 : 12 dB
#define HWGEQ_MIN_GAIN_IDX    (-24)
#define HWGEQ_MAX_GAIN_IDX    (24)


/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_HWGEQ_32BITS_Q8_DATA
typedef tS32 HWGEQ_PROC_DATA_TYPE;
#else
typedef tS16 HWGEQ_PROC_DATA_TYPE;
#endif

/*----------------------- Interface ---------------------*/
typedef struct
{
    // Power
    tU8   bEn;
    tS32  s32GIdx[HWGEQ_BAND_NUM];
    tU8   b7BandMode;
}M_HWGEQ_PAR_s;
#define SIZEOF_HWGEQ_DATA (sizeof(tU8) + (sizeof(tS32) * HWGEQ_BAND_NUM) + sizeof(tU8))

typedef struct
{
    // IP control interface
    M_HWGEQ_PAR_s sHWGEQ_Ctr;
    tU8   bUpdateFlag;

    // IP public variable
    tS32  s32FrmSz;
    tS32  s32SmpFreq;
    tS32  s32ChumN;
}M_HWGEQ_MAIN_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWGEQPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWGEQPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWGEQPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWGEQPar_SetStrcPower(void* void_pSet, tU8 bEn );
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWGEQPar_SetStrcBandGain(void* void_pSet, tS32 s32BandIdx, tS32 s32GainIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWGEQPar_GetStrcPower(void* void_pSet, tU8* pbEn );
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWGEQPar_GetStrcBandGain(void* void_pSet, tS32 s32BandIdx, tS32* s32GainIdx);

// Main
tBOOL AUD_HWGEQMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_HWGEQMain_Check(void* void_pIP, void* void_pSet, tU8 bRtChangeGain, tU8* pbUpdateFlag);
tBOOL AUD_HWGEQMain_Update(void* void_pIP, void* void_pSet, tU8 bRtChangeGain);
tBOOL AUD_HWGEQMain_Proc(void* void_pIP, tS32* ptProcBuf, tS32 s32ProcSizePerCh);
tBOOL AUD_HWGEQMain_Close(void* void_pIP , void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __HW_G_EQ_H__ */

