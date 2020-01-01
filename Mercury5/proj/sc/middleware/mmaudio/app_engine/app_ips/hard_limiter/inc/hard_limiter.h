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
* @file    : hard_limiter.h
* @version :
* @author  : CA.Wang
* @brief   : The Limiter is limit the peak value
*/

#ifndef __HARD_LIMITER_H__
#define __HARD_LIMITER_H__

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
#define POST_PROC_HARDLIMITER_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_HARDLIMITER_PARSER_PRINTF

/*--------------- Separate Level Det. --------------------*/
//#define HARD_LIMITER_SEPARATE

/*-------------------------------------------------------*/
//#define HARD_LIMITER_HQ_OPERATOR

/*------------------ Look ahead size --------------------*/
#define HARD_LIMITRER_MIN_LOOKAHEAD_MS   (1)   // ms
#define HARD_LIMITRER_MAX_LOOKAHEAD_MS   (10)  // ms

#define HARD_LIMITRER_MAX_LOOKAHEAD_SIZE ((APP_FS_48K * HARD_LIMITRER_MAX_LOOKAHEAD_MS)/1000) //  MAX : 48000*10ms = 480 sample

/*-------------------- channel size ---------------------*/
#define HARD_LIMITER_MAX_CH_NUM (2)

/*--------- Histogram Quantization Table Define ---------*/
#define HARD_LIMITER_HIST_MAX_ABS_VALUE    (32768)  // max(abs(-32768~32767)) = 32768
#define HARD_LIMITER_HIST_MIN_ABS_VALUE    (0)

#define HARD_LIMITER_HIST_QUANT_BIT        (2)
#define HARD_LIMITER_HIST_QUANT_STEP       ((tS32)1 << HARD_LIMITER_HIST_QUANT_BIT)
#define HARD_LIMITER_HIST_QUANT_INVCOMP    ((tS32)1)
#define HARD_LIMITER_HIST_QUANT_COMP       ((tS32)HARD_LIMITER_HIST_QUANT_STEP - HARD_LIMITER_HIST_QUANT_INVCOMP)
#define HARD_LIMITER_HIST_QUANT_TABLE_SIZE ((tS32)((HARD_LIMITER_HIST_MAX_ABS_VALUE - HARD_LIMITER_HIST_MIN_ABS_VALUE) >> HARD_LIMITER_HIST_QUANT_BIT) + 1)

/*--------------------- Gain Table ----------------------*/
//gain : 0.2 dB
#define HARD_LIMITER_MAX_IDX    (0)
#define HARD_LIMITER_MIN_IDX    (-60)
#define HARD_LIMITER_IDX_NUM    (HARD_LIMITER_MAX_IDX - HARD_LIMITER_MIN_IDX +1)
#define HARD_LIMITER_IDX_OFFSET (HARD_LIMITER_MAX_IDX - HARD_LIMITER_MIN_IDX)

// 0.1dB
#define HARD_LIMITER_GAIN_TABLE_MAX_IDX    (HARD_LIMITER_MAX_IDX)
#define HARD_LIMITER_GAIN_TABLE_MIN_IDX    (HARD_LIMITER_MIN_IDX*2)
#define HARD_LIMITER_GAIN_TABLE_IDX_NUM    (HARD_LIMITER_GAIN_TABLE_MAX_IDX - HARD_LIMITER_GAIN_TABLE_MIN_IDX +1)
#define HARD_LIMITER_GAIN_TABLE_IDX_OFFSET (HARD_LIMITER_GAIN_TABLE_MAX_IDX - HARD_LIMITER_GAIN_TABLE_MIN_IDX)

/*-------------------- Release Time----------------------*/
// Release Time (ms) limitation
#define HARD_LIMITER_MIN_RT_TIME_MS (50)
#define HARD_LIMITER_MAX_RT_TIME_MS (1000)

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_HARDLIMITER_32BITS_Q8_DATA
typedef tS32 HARDLIMITER_PROC_DATA_TYPE;
#else
typedef tS16 HARDLIMITER_PROC_DATA_TYPE;
#endif

/*----------------------- Interface ---------------------*/
typedef struct
{
    tU8   bEn;
    tS16  s16LimitValue_Idx[ HARD_LIMITER_MAX_CH_NUM];
    tU16  u16RTTimeMs_Idx[   HARD_LIMITER_MAX_CH_NUM];
    tS32  s32DPGAdB_Idx[     HARD_LIMITER_MAX_CH_NUM];      // 0.5 dB
    tU16  u16LookAHeadTimeMs[HARD_LIMITER_MAX_CH_NUM];
}M_HARD_LIMITER_PAR_s;
#define SIZEOF_HARDLIMITER_DATA (sizeof(tU8) + (sizeof(tS16) * HARD_LIMITER_MAX_CH_NUM) + (sizeof(tU16) * HARD_LIMITER_MAX_CH_NUM) + (sizeof(tS32) * HARD_LIMITER_MAX_CH_NUM) + (sizeof(tU16) * HARD_LIMITER_MAX_CH_NUM))

typedef struct
{
    // IP control interface
    M_HARD_LIMITER_PAR_s sHardLimiter_Ctr;
    tU8   bUpdateFlag;

    // IP public variable
    HARDLIMITER_PROC_DATA_TYPE*  ptFrmBuf;
    tS32   s32FrmSz;
    tS32   s32SmpFreq;
    tS32   s32ChumN;

    // IP private variable
    tU32  u32RTCst[     HARD_LIMITER_MAX_CH_NUM];           // [2]
    tU32  u32LimitValue[HARD_LIMITER_MAX_CH_NUM];           // [2]
    tU32  u32AtMaxValue[HARD_LIMITER_MAX_CH_NUM];           // [2]
    tU32  u32LevelDet[  HARD_LIMITER_MAX_CH_NUM];           // [2]
    tU8   bFirstSample;

    tU16  u16OffsetSamplesPerCh;
    tU16  u16LookaheadSamplesPerCh;
    HARDLIMITER_PROC_DATA_TYPE  tmp_buf[ HARD_LIMITRER_MAX_LOOKAHEAD_SIZE * HARD_LIMITER_MAX_CH_NUM];
    HARDLIMITER_PROC_DATA_TYPE  tmp_buf2[HARD_LIMITRER_MAX_LOOKAHEAD_SIZE * HARD_LIMITER_MAX_CH_NUM];

    tU16  u16QuantTable[       HARD_LIMITER_MAX_CH_NUM][HARD_LIMITER_HIST_QUANT_TABLE_SIZE]; // [2][8192]
    tU16  u16QuantTable_MaxIdx[HARD_LIMITER_MAX_CH_NUM];   // [2]
    tU16  u16QuantTable_PreIdx[HARD_LIMITER_MAX_CH_NUM];   // [2]
}M_HARD_LIMITER_MAIN_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_SetStrcPower(void* void_pSet, tU8 bEn );
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_SetStrcPar(void* void_pSet,
                                                           tS16 s16LimitIdx_Ch1, tU16 u16RTIdx_Ch1,
                                                           tS16 s16LimitIdx_Ch2, tU16 u16RTIdx_Ch2);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_SetStrcLookaheadTime(void* void_pSet, tU16 u16LookMs_Ch1, tU16 u16LookMs_Ch2);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_SetStrcDPGA(void* void_pSet, tS32 s32Ch1_DPGAIdx, tS32 s32Ch2_DPGAIdx);

tBOOL POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_GetStrcPower(void* void_pSet, tU8 *pbEn );
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_GetStrcPar(void* void_pSet,
                                                           tS16* ps16Ch1_LimitIdx, tU16* pu16Ch1_RTIdx,
                                                           tS16* ps16Ch2_LimitIdx, tU16* pu16Ch2_RTIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_GetStrcLookaheadTime(void* void_pSet, tU16* pu16LookMs_Ch1, tU16* pu16LookMs_Ch2);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HardLimiterPar_GetStrcDPGA(void* void_pSet, tS32* ps32Ch1_DPGAIdx, tS32* ps32Ch2_DPGAIdx);

// Main
tBOOL AUD_HardLimiterMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum , tS32 s32SampleRate);
tBOOL AUD_HardLimiterMain_Check(void* void_pIP, void* void_pSet, tU8* pbUpdateFlag);
tBOOL AUD_HardLimiterMain_Update(void *void_pIP, void* void_pSet);
tBOOL AUD_HardLimiterMain_ChangeDPGA(void* void_pIP, tS32 s32Ch1_DPGAIdx, tS32 s32Ch2_DPGAIdx);
tBOOL AUD_HardLimiterMain_Proc(void* void_pIP, HARDLIMITER_PROC_DATA_TYPE* ptProcBuf, tS32 *ps32ProcSizePerCh);
tBOOL AUD_HardLimiterMain_Close(void* void_pIP, void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif // __HARD_LIMITER_H__



