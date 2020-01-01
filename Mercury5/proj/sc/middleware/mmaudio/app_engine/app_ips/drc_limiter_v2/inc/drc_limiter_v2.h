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
* @file    : drc_limiter_v2.h
* @version :
* @author  : CA.Wang
* @brief   : DRC Limiter V2
*/

#ifndef __DRC_LIMITER_V2_H__
#define __DRC_LIMITER_V2_H__

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
#define POST_PROC_DRC_LIMITER_V2_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_DRC_LIMITER_V2_PARSER_PRINTF

/*--------------- Separate Level Det. --------------------*/
//#define DRC_LIMITER_V2_SEPARATE

/*------------------ Quality Define ----------------------*/
//#define DRC_LIMITER_V2_HQ_OPERATOR

/*--------------------- Channel size --------------------*/
#define DRC_LIMITER_V2_MAX_CH_NUM 2

/*----------------------- DRC gain ----------------------*/
// drc gain : 0.2 dB
#define DRC_LIMITER_V2_MAX_IDX    (0)
#define DRC_LIMITER_V2_MIN_IDX    (-180)
#define DRC_LIMITER_V2_IDX_NUM    (DRC_LIMITER_V2_MAX_IDX - DRC_LIMITER_V2_MIN_IDX + 1)
#define DRC_LIMITER_V2_IDX_OFFSET (DRC_LIMITER_V2_MAX_IDX - DRC_LIMITER_V2_MIN_IDX)

// read gain table : 0.1 dB
#define DRC_LIMITER_V2_GAIN_TABLE_MAX_IDX    DRC_LIMITER_V2_MAX_IDX
#define DRC_LIMITER_V2_GAIN_TABLE_MIN_IDX    (DRC_LIMITER_V2_MIN_IDX*2)
#define DRC_LIMITER_V2_GAIN_TABLE_IDX_NUM    (DRC_LIMITER_V2_GAIN_TABLE_MAX_IDX - DRC_LIMITER_V2_GAIN_TABLE_MIN_IDX + 1)
#define DRC_LIMITER_V2_GAIN_TABLE_IDX_OFFSET (DRC_LIMITER_V2_GAIN_TABLE_MAX_IDX - DRC_LIMITER_V2_GAIN_TABLE_MIN_IDX)

// vpp to dB gain table : 0.1V
#define DRC_LIMITER_V2_MAX_VPP_IDX    (200)
#define DRC_LIMITER_V2_MIN_VPP_IDX    (0)
#define DRC_LIMITER_V2_VPP_IDX_NUM    (DRC_LIMITER_V2_MAX_VPP_IDX - DRC_LIMITER_V2_MIN_VPP_IDX + 1)
#define DRC_LIMITER_V2_VPP_IDX_OFFSET (DRC_LIMITER_V2_MAX_VPP_IDX - DRC_LIMITER_V2_MIN_VPP_IDX)

/*--------------------- Attack Time ---------------------*/
// Attack Time (ms) limitation index
#define DRC_LIMITER_V2_MIN_AT_TIME_IDX (0)
#define DRC_LIMITER_V2_MAX_AT_TIME_IDX (9)
#define DRC_LIMITER_V2_AT_TIME_IDX_TABLE_SIZE (DRC_LIMITER_V2_MAX_AT_TIME_IDX - DRC_LIMITER_V2_MIN_AT_TIME_IDX + 1)

/*-------------------- Release Time ---------------------*/
// Release Time (ms) limitation index
#define DRC_LIMITER_V2_MIN_RT_TIME_IDX (0)
#define DRC_LIMITER_V2_MAX_RT_TIME_IDX (9)
#define DRC_LIMITER_V2_RT_TIME_IDX_TABLE_SIZE (DRC_LIMITER_V2_MAX_RT_TIME_IDX - DRC_LIMITER_V2_MIN_RT_TIME_IDX + 1)

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_DRC_LIMITER_V2_32BITS_Q8_DATA
typedef tS32 DRC_LIMITER_V2_PROC_DATA_TYPE;
#else
typedef tS16 DRC_LIMITER_V2_PROC_DATA_TYPE;
#endif

/*----------------------- Interface ---------------------*/
typedef struct
{
    tU8   bEn;
    tS16  s16LimitValue_Idx[DRC_LIMITER_V2_MAX_CH_NUM];   // 0.2 dB
    tU16  u16ATTimeMs_Idx[  DRC_LIMITER_V2_MAX_CH_NUM];
    tU16  u16RTTimeMs_Idx[  DRC_LIMITER_V2_MAX_CH_NUM];

    tU8   bExtGainInfoEn;
    tS32  s32Weight_dB_Idx[   DRC_LIMITER_V2_MAX_CH_NUM];   // Q16 dB
    tS32  s32DPGA_dB_Idx[     DRC_LIMITER_V2_MAX_CH_NUM];   // Q16 dB
    tS32  s32DPGA_ClipVpp_Idx[ DRC_LIMITER_V2_MAX_CH_NUM];  // Q16 dB
    tS32  s32DRV_dB_Idx[      DRC_LIMITER_V2_MAX_CH_NUM];   // Q16 dB
    tS32  s32DRV_ClipVpp_Idx[ DRC_LIMITER_V2_MAX_CH_NUM];   // Q16 dB
    tS32  s32AMP_dB_Idx[      DRC_LIMITER_V2_MAX_CH_NUM];   // Q16 dB
    tS32  s32AMP_ClipVpp_Idx[ DRC_LIMITER_V2_MAX_CH_NUM];   // Q16 dB
}M_DRC_LIMITER_V2_PAR_s;
#define SIZEOF_DRC_LIMITER_V2_DATA  (sizeof(tU8) + (sizeof(tS16)*DRC_LIMITER_V2_MAX_CH_NUM) + (sizeof(tU16)*DRC_LIMITER_V2_MAX_CH_NUM) + (sizeof(tU16)*DRC_LIMITER_V2_MAX_CH_NUM) + sizeof(tU8) + (sizeof(tS32)*DRC_LIMITER_V2_MAX_CH_NUM) + (sizeof(tS32)*DRC_LIMITER_V2_MAX_CH_NUM) + (sizeof(tS32)*DRC_LIMITER_V2_MAX_CH_NUM) + (sizeof(tS32)*DRC_LIMITER_V2_MAX_CH_NUM) + (sizeof(tS32)*DRC_LIMITER_V2_MAX_CH_NUM) + (sizeof(tS32)*DRC_LIMITER_V2_MAX_CH_NUM) + (sizeof(tS32)*DRC_LIMITER_V2_MAX_CH_NUM))

typedef struct
{
    // IP control interface
    M_DRC_LIMITER_V2_PAR_s sDRC_Limiter_V2_Ctr;
    tU8   bUpdateFlag;

    // IP public variable
    DRC_LIMITER_V2_PROC_DATA_TYPE* ptFrmBuf;
    tS32  s32FrmSz;
    tS32  s32SmpFreq;
    tS32  s32ChumN;

    // IP private variable
    tU32  u32ATCst[     DRC_LIMITER_V2_MAX_CH_NUM];
    tU32  u32RTCst[     DRC_LIMITER_V2_MAX_CH_NUM];
    tU32  u32LimitValue[DRC_LIMITER_V2_MAX_CH_NUM];
    tU32  u32LevelDet[  DRC_LIMITER_V2_MAX_CH_NUM];
    tU32  u32GainDet[   DRC_LIMITER_V2_MAX_CH_NUM];
    tU8   bFirstSample;
}M_DRC_LIMITER_V2_MAIN_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_CopyParFromCalbTable(tU8* ps8CalibTab, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_SetStrcExtPower(void* void_pSet, tU8 bEn );
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_SetStrcExtWeightGain(void* void_pSet, tS32 s32Ch1_WeightIdx, tS32 s32Ch2_WeightIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_SetStrcExtDPGAGain(void* void_pSet, tS32 s32Ch1_DPGA_dB_Idx, tS32 s32Ch2_DPGA_dB_Idx, tS32 s32Ch1_DPGA_ClipVpp_Idx, tS32 s32Ch2_DPGA_ClipVpp_Idx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_SetStrcExtDRVGain(void* void_pSet, tS32 s32Ch1_DRV_dB_Idx, tS32 s32Ch2_DRV_dB_Idx, tS32 s32Ch1_DRV_ClipVpp_Idx, tS32 s32Ch2_DRV_ClipVpp_Idx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_SetStrcExtAMPGain(void* void_pSet, tS32 s32Ch1_AMP_dB_Idx, tS32 s32Ch2_AMP_dB_Idx, tS32 s32Ch1_AMP_ClipVpp_Idx, tS32 s32Ch2_AMP_ClipVpp_Idx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_SetStrcPower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_SetStrcPar(void* void_pSet,
                                          tS16 s16LimitIdx_Ch1, tU16 u16ATIdx_Ch1, tU16 u16RTIdx_Ch1,
                                          tS16 s16LimitIdx_Ch2, tU16 u16ATIdx_Ch2, tU16 u16RTIdx_Ch2);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_GetStrcExtPower(void* void_pSet, tU8 *pbEn );
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_GetStrcExtWeightGain(void* void_pSet, tS32* ps32Ch1_WeightIdx, tS32* ps32Ch2_WeightIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_GetStrcExtDPGAGain(void* void_pSet, tS32* ps32Ch1_DPGA_dB_Idx, tS32* ps32Ch2_DPGA_dB_Idx, tS32* ps32Ch1_DPGA_ClipVpp_Idx, tS32* ps32Ch2_DPGA_ClipVpp_Idx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_GetStrcExtDRVGain(void* void_pSet, tS32* ps32Ch1_DRV_dB_Idx, tS32* ps32Ch2_DRV_dB_Idx, tS32* ps32Ch1_DRV_ClipVpp_Idx, tS32* ps32Ch2_DRV_ClipVpp_Idx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_GetStrcExtAMPGain(void* void_pSet, tS32* ps32Ch1_AMP_dB_Idx, tS32* ps32Ch2_AMP_dB_Idx, tS32* ps32Ch1_AMP_ClipVpp_Idx, tS32* ps32Ch2_AMP_ClipVpp_Idx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_GetStrcPower(void* void_pSet, tU8* pbEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_DRCLimiterV2Par_GetStrcPar(void* void_pSet,
                                            tS16* s16LimitIdx_Ch1, tU16* u16ATIdx_Ch1, tU16* u16RTIdx_Ch1,
                                            tS16* s16LimitIdx_Ch2, tU16* u16ATIdx_Ch2, tU16* u16RTIdx_Ch2);

// Main
tBOOL AUD_DRCLimiterV2Main_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_DRCLimiterV2Main_Check(void* void_pIP, void* void_pSet, tU8* pbUpdateFlag);
tBOOL AUD_DRCLimiterV2Main_Update(void* void_pIP, void* void_pSet);
tBOOL AUD_DRCLimiterV2Main_ChangeTargetLevel(void* void_pIP,
                                                               tBOOL bExtGainInfoEn,
                                                               tS32 s32Ch1_Weight_dB_Idx   , tS32 s32Ch2_Weight_dB_Idx,
                                                               tS32 s32Ch1_DPGA_dB_Idx     , tS32 s32Ch2_DPGA_dB_Idx,
                                                               tS32 s32Ch1_DPGA_ClipVpp_Idx, tS32 s32Ch2_DPGA_ClipVpp_Idx,
                                                               tS32 s32Ch1_DRV_dB_Idx      , tS32 s32Ch2_DRV_dB_Idx,
                                                               tS32 s32Ch1_DRV_ClipVpp_Idx , tS32 s32Ch2_DRV_ClipVpp_Idx,
                                                               tS32 s32Ch1_AMP_dB_Idx      , tS32 s32Ch2_AMP_dB_Idx,
                                                               tS32 s32Ch1_AMP_ClipVpp_Idx , tS32 s32Ch2_AMP_ClipVpp_Idx);

tBOOL AUD_DRCLimiterV2Main_Proc(void* void_pIP, DRC_LIMITER_V2_PROC_DATA_TYPE* ptProcBuf, tS32* ps32ProcSizePerCh);
tBOOL AUD_DRCLimiterV2Main_Close(void* void_pIP, void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __DRC_LIMITER_V2_H__ */

