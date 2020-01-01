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
* @file    : drclookahead_limiter.h
* @version :
* @author  : CA.Wang
* @brief   : DRC Limiter
*/

#ifndef __DRCLOOKAHEAD_LIMITER_H__
#define __DRCLOOKAHEAD_LIMITER_H__

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
#define POST_PROC_DRCLOOKAHEAD_LIMITER_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_DRCLOOKAHEAD_LIMITER_PARSER_PRINTF

/*--------------- Separate Level Det. --------------------*/
//#define DRCLOOKAHEAD_LIMITER_SEPARATE

/*------------------ Quality Define ----------------------*/
//#define DRCLOOKAHEAD_LIMITER_HQ_OPERATOR

/*----------------------- Lookahead ---------------------*/
#if 1//def ENABLE_LOOKAHEAD_DRC_LIMITER
#define USE_DRCLOOKAHEAD_LIMITER
#else
#undef  USE_DRCLOOKAHEAD_LIMITER
#endif

#ifdef USE_DRCLOOKAHEAD_LIMITER
#define DRCLOOKAHEAD_LIMITER_MIN_LOOKAHEAD_MS   (1)   // ms
#define DRCLOOKAHEAD_LIMITER_MAX_LOOKAHEAD_MS   (10)   // ms

#define DRCLOOKAHEAD_LIMITER_MAX_LOOKAHEAD_SIZE ((APP_FS_48K * DRCLOOKAHEAD_LIMITER_MAX_LOOKAHEAD_MS)/1000) //  MAX : 48000*10ms = 480 sample
#endif

/*--------------------- Channel size --------------------*/
#define DRCLOOKAHEAD_LIMITER_MAX_CH_NUM 2

/*----------------------- DRC gain ----------------------*/
// drc gain : 0.2 dB
#define DRCLOOKAHEAD_LIMITER_MAX_IDX    (0)
#define DRCLOOKAHEAD_LIMITER_MIN_IDX    (-180)
#define DRCLOOKAHEAD_LIMITER_IDX_NUM    (DRCLOOKAHEAD_LIMITER_MAX_IDX - DRCLOOKAHEAD_LIMITER_MIN_IDX +1)
#define DRCLOOKAHEAD_LIMITER_IDX_OFFSET (DRCLOOKAHEAD_LIMITER_MAX_IDX - DRCLOOKAHEAD_LIMITER_MIN_IDX)

// read gain table : 0.1 dB
#define DRCLOOKAHEAD_LIMITER_GAIN_TABLE_MAX_IDX    DRCLOOKAHEAD_LIMITER_MAX_IDX
#define DRCLOOKAHEAD_LIMITER_GAIN_TABLE_MIN_IDX    (DRCLOOKAHEAD_LIMITER_MIN_IDX*2)
#define DRCLOOKAHEAD_LIMITER_GAIN_TABLE_IDX_NUM    (DRCLOOKAHEAD_LIMITER_GAIN_TABLE_MAX_IDX - DRCLOOKAHEAD_LIMITER_GAIN_TABLE_MIN_IDX +1)
#define DRCLOOKAHEAD_LIMITER_GAIN_TABLE_IDX_OFFSET (DRCLOOKAHEAD_LIMITER_GAIN_TABLE_MAX_IDX - DRCLOOKAHEAD_LIMITER_GAIN_TABLE_MIN_IDX)

/*--------------------- Attack Time ---------------------*/
// Attack Time (ms) limitation index
#define DRCLOOKAHEAD_LIMITER_MIN_AT_TIME_IDX (0)
#define DRCLOOKAHEAD_LIMITER_MAX_AT_TIME_IDX (9)
#define DRCLOOKAHEAD_LIMITER_AT_TIME_IDX_TABLE_SIZE (DRCLOOKAHEAD_LIMITER_MAX_AT_TIME_IDX - DRCLOOKAHEAD_LIMITER_MIN_AT_TIME_IDX + 1)

/*-------------------- Release Time ---------------------*/
// Release Time (ms) limitation index
#define DRCLOOKAHEAD_LIMITER_MIN_RT_TIME_IDX (0)
#define DRCLOOKAHEAD_LIMITER_MAX_RT_TIME_IDX (9)
#define DRCLOOKAHEAD_LIMITER_RT_TIME_IDX_TABLE_SIZE (DRCLOOKAHEAD_LIMITER_MAX_RT_TIME_IDX - DRCLOOKAHEAD_LIMITER_MIN_RT_TIME_IDX + 1)

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_DRCLOOKAHEAD_LIMITER_32BITS_Q8_DATA
typedef tS32 DRCLOOKAHEAD_LIMITER_PROC_DATA_TYPE;
#else
typedef tS16 DRCLOOKAHEAD_LIMITER_PROC_DATA_TYPE;
#endif

#ifdef POST_PROC_DRCLOOKAHEAD_LIMITER_32BITS_Q8_DATA
#define DRC_LOOKAHEAD_BUFSIZE (2*4*(DRC_LIMITER_MAX_CH_NUM * DRCLOOKAHEAD_LIMITER_MAX_LOOKAHEAD_SIZE))
#else
#define DRC_LOOKAHEAD_BUFSIZE (2*2*(DRC_LIMITER_MAX_CH_NUM * DRCLOOKAHEAD_LIMITER_MAX_LOOKAHEAD_SIZE))
#endif

/*----------------------- Interface ---------------------*/
typedef struct
{
    tU8   bEn;
    tS16  s16LimitValue_Idx[DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];   // 0.2 dB
    tU16  u16ATTimeMs_Idx[ DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];
    tU16  u16RTTimeMs_Idx[ DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];
#ifdef USE_DRCLOOKAHEAD_LIMITER
    tU16  u16LookAHeadTimeMs[DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];
#endif
    tS32  s32DPGAdB_Idx[   DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];      // 0.5 dB
}M_DRCLOOKAHEAD_LIMITER_PAR_s;
#ifdef USE_DRCLOOKAHEAD_LIMITER
#define SIZEOF_DRCLOOKAHEAD_LIMITER_DATA (sizeof(tU8) + (sizeof(tS16)*DRCLOOKAHEAD_LIMITER_MAX_CH_NUM) + (sizeof(tU16)*DRCLOOKAHEAD_LIMITER_MAX_CH_NUM) + (sizeof(tU16)*DRCLOOKAHEAD_LIMITER_MAX_CH_NUM) + (sizeof(tU16)*DRCLOOKAHEAD_LIMITER_MAX_CH_NUM) + (sizeof(tS32)*DRCLOOKAHEAD_LIMITER_MAX_CH_NUM))
#endif

typedef struct
{
    // IP control interface
    M_DRCLOOKAHEAD_LIMITER_PAR_s sDRCLookahead_Limiter_Ctr;
    tU8   bUpdateFlag;

    // IP public variable
    DRCLOOKAHEAD_LIMITER_PROC_DATA_TYPE* ptFrmBuf;
    tS32  s32FrmSz;
    tS32  s32SmpFreq;
    tS32  s32ChumN;

    // IP private variable
    tU32  u32ATCst[     DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];
    tU32  u32RTCst[     DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];
    tU32  u32LimitValue[DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];
    tU32  u32LevelDet[  DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];
    tU32  u32GainDet[   DRCLOOKAHEAD_LIMITER_MAX_CH_NUM];
    tU8   bFirstSample;

#ifdef USE_DRCLOOKAHEAD_LIMITER
    tU8   bLastFrm;
    tU16  u16OffsetSamplesPerCh;
    tU16  u16LookaheadSamplesPerCh;
   // DRCLOOKAHEAD_LIMITER_PROC_DATA_TYPE tmp_buf[ DRCLOOKAHEAD_LIMITER_MAX_CH_NUM * DRCLOOKAHEAD_LIMITER_MAX_LOOKAHEAD_SIZE];
   // DRCLOOKAHEAD_LIMITER_PROC_DATA_TYPE tmp_buf2[DRCLOOKAHEAD_LIMITER_MAX_CH_NUM * DRCLOOKAHEAD_LIMITER_MAX_LOOKAHEAD_SIZE];
    DRCLOOKAHEAD_LIMITER_PROC_DATA_TYPE* tmp_buf;
    DRCLOOKAHEAD_LIMITER_PROC_DATA_TYPE* tmp_buf2;
#endif
}M_DRCLOOKAHEAD_LIMITER_MAIN_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_CopyParFromCalbTable(tU8* ps8CalibTab, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_SetStrcDPGA(void* void_pSet, tS32 s32Ch1_DPGAIdx, tS32 s32Ch2_DPGAIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_SetStrcPower(void* void_pSet, tU8 bEn);
#ifdef USE_DRCLOOKAHEAD_LIMITER
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_SetStrcLookaheadTime(void* void_pSet, tU16 u16LookMs_Ch1, tU16 u16LookMs_Ch2);
#endif
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_SetStrcPar(void* void_pSet,
                                          tS16 s16LimitIdx_Ch1, tU16 u16ATIdx_Ch1, tU16 u16RTIdx_Ch1,
                                          tS16 s16LimitIdx_Ch2, tU16 u16ATIdx_Ch2, tU16 u16RTIdx_Ch2);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_GetStrcDPGA(void* void_pSet, tS32* ps32Ch1_DPGAIdx, tS32* ps32Ch2_DPGAIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_GetStrcPower(void* void_pSet, tU8* pbEn);
#ifdef USE_DRCLOOKAHEAD_LIMITER
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_GetStrcLookaheadTime(void* void_pSet, tU16* pu16LookMs_Ch1, tU16* pu16LookMs_Ch2);
#endif
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterPar_GetStrcPar(void* void_pSet,
                                            tS16* s16LimitIdx_Ch1, tU16* u16ATIdx_Ch1, tU16* u16RTIdx_Ch1,
                                            tS16* s16LimitIdx_Ch2, tU16* u16ATIdx_Ch2, tU16* u16RTIdx_Ch2);

// Main
tBOOL AUD_DRCLookaheadLimiterMain_AllocateTempBuf(void* void_pIP, tU8* u8addr, tS32 s32bufsz);
tBOOL AUD_DRCLookaheadLimiterMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_DRCLookaheadLimiterMain_Check(void* void_pIP, void* void_pSet, tU8* pbUpdateFlag);
tBOOL AUD_DRCLookaheadLimiterMain_Update(void* void_pIP, void* void_pSet);
tBOOL AUD_DRCLookaheadLimiterMain_ChangeDPGA(void* void_pIP, tS32 s32Ch1_DPGAIdx, tS32 s32Ch2_DPGAIdx);
tBOOL AUD_DRCLookaheadLimiterMain_Proc(void* void_pIP, DRCLOOKAHEAD_LIMITER_PROC_DATA_TYPE* ptProcBuf, tS32* ps32ProcSizePerCh);
tBOOL AUD_DRCLookaheadLimiterMain_Close(void* void_pIP, void* void_pSet);

#ifdef USE_DRCLOOKAHEAD_LIMITER
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLookaheadLimiterMain_Set_LastFrm(void* void_pIP, tU8 bLastFrm);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DRCLOOKAHEAD_LIMITER_H__ */

