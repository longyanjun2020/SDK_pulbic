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
* @file    : arp_exp_vol.h
* @version :
* @author  : Wendy.Lin
* @brief   : control volume gain exponentially
*/

#ifndef __ARP_EXP_VOL_H__
#define __ARP_EXP_VOL_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "arp_datatype.h"

/*============================================================================*/
// Extern definition
/*============================================================================*/
//...

/*============================================================================*/
// Macro definition
/*============================================================================*/
/*------------------ Process Data Type ------------------*/
//#define ARP_EXPVOL_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_ARP_EXPVOL_PARSER_PRINTF

/*-------------------- Channel size ---------------------*/
#define ARP_EXPVOL_MAX_CH_NUM 2

/*--------------------- Gain Table ----------------------*/
#define ARP_EXPVOL_RIGHT_SHIFT       (14)

#if ARP_EXPVOL_RIGHT_SHIFT == 13

#define ARP_EXPVOL_ZERO_DB_GAIN      ((tS16)8191)
// Gain table from 12~-74dB, 0.5dB apart
#define ARP_EXPVOL_MIN_GAIN_TABIDX   (-148)
#define ARP_EXPVOL_MAX_GAIN_TABIDX   (24)
#define ARP_EXPVOL_GAIN_TABSIZE      (ARP_EXPVOL_MAX_GAIN_TABIDX - ARP_EXPVOL_MIN_GAIN_TABIDX + 1)

#elif ARP_EXPVOL_RIGHT_SHIFT == 14

#define ARP_EXPVOL_ZERO_DB_GAIN      ((tS16)16383)
// Gain table from 6~-80dB, 0.5dB apart
#define ARP_EXPVOL_MIN_GAIN_TABIDX   (-160)
#define ARP_EXPVOL_MAX_GAIN_TABIDX   (12)
#define ARP_EXPVOL_GAIN_TABSIZE      (ARP_EXPVOL_MAX_GAIN_TABIDX - ARP_EXPVOL_MIN_GAIN_TABIDX + 1)

#else

#error  Invalid Gain Table!!!

#endif

/*--------------------- Time Const ----------------------*/
// Time Const table from 0~18ms, 2ms apart
#define ARP_EXPVOL_MIN_TIMECONST_TABIDX     (0)
#define ARP_EXPVOL_MAX_TIMECONST_TABIDX     (9)
#define ARP_EXPVOL_TIMECONST_TABSIZE        (ARP_EXPVOL_MAX_TIMECONST_TABIDX - ARP_EXPVOL_MIN_TIMECONST_TABIDX + 1)
#define ARP_EXPVOL_DEFAULT_TIMECONST_TABIDX (8)

// 0 : DPGA Mode , 1 : Boost Mode , 2 : DPGA + Boost Mode
#define ARP_EXPVOL_MIN_GAINMODE_IDX         (0)
#define ARP_EXPVOL_MAX_GAINMODE_IDX         (2)
#define ARP_EXPVOL_GAINMODE_SIZE            (ARP_EXPVOL_MAX_GAINMODE_IDX - ARP_EXPVOL_MIN_GAINMODE_IDX + 1)

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef ARP_EXPVOL_32BITS_Q8_DATA
typedef tS32 ARP_EXPVOL_PROC_DATA_TYPE;
#else
typedef tS16 ARP_EXPVOL_PROC_DATA_TYPE;
#endif

/*----------------------- Interface ---------------------*/
typedef struct
{
    tU8  bEn;
    tS16 s16InstDBIdx[ARP_EXPVOL_MAX_CH_NUM];
    tS16 s16TgtDBIdx[ARP_EXPVOL_MAX_CH_NUM];
    tS16 s16FadTimeIdx;
    tU8  bInstChange;
    tU8  u8GainMode;     // 0 : DPGA Mode , 1 : Boost Mode , 2 : DPGA + Boost Mode
}ARP_EXPVOL_PAR_s;
#define ARP_SIZEOF_EXPVOL_DATA (sizeof(tU8) + (sizeof(tS16) * ARP_EXPVOL_MAX_CH_NUM) + (sizeof(tS16) * ARP_EXPVOL_MAX_CH_NUM) + sizeof(tS16) + sizeof(tU8) + sizeof(tU8))

typedef struct
{
    // IP control interface
    ARP_EXPVOL_PAR_s sExpVol_Ctr;
    tU8  bUpdateFlag;

    // IP public variable
    tS32 s32SmpFreq;
    tS32 s32ChumN;

    tS16 s16InstGain[ARP_EXPVOL_MAX_CH_NUM];/* gain applied right now */
    tS16 s16TgtGain[ARP_EXPVOL_MAX_CH_NUM]; /* in a smooth gain change, the gain we are aiming for */

    // IP private variable
    tS16 s16Shift[ARP_EXPVOL_MAX_CH_NUM];
}ARP_EXPVOL_MAIN_s;

/*============================================================================*/
// Variable definition
/*============================================================================*/
//...

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

// Parser
tS32 ARP_ATTR_16BITS ARP_EXPVOLPar_CopyParFromCalbTable(tU8* ps8ModeData, const tU8* ps8CalibTab);
tS32 ARP_ATTR_16BITS ARP_EXPVOLPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 ARP_ATTR_16BITS ARP_EXPVOLPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL ARP_ATTR_16BITS ARP_EXPVOLPar_SetPower(void* void_pSet, tU8 bEn);
tBOOL ARP_ATTR_16BITS ARP_EXPVOLPar_GetPower(void* void_pSet, tU8 *pbEn);
tBOOL ARP_ATTR_16BITS ARP_EXPVOLPar_SetFadingTime(void* void_pSet, tS16 s16FadingTimeIdx);
tBOOL ARP_ATTR_16BITS ARP_EXPVOLPar_GetFadingTime(void* void_pSet, tS16* ps16FadingTimeIdx);
tBOOL ARP_ATTR_16BITS ARP_EXPVOLPar_SetInstGain(void* void_pSet, tS32 s32LDBIdx, tS32 s32RDBIdx, tU8 bInstChange);
tBOOL ARP_ATTR_16BITS ARP_EXPVOLPar_GetInstGain(void* void_pSet, tS32* ps32LDBIdx, tS32* ps32RDBIdx, tU8* pbInstChange);
tBOOL ARP_ATTR_16BITS ARP_EXPVOLPar_SetTargetGain(void* void_pSet, tS32 s32LDBIdx, tS32 s32RDBIdx);
tBOOL ARP_ATTR_16BITS ARP_EXPVOLPar_GetTargetGain(void* void_pSet, tS32* ps32LDBIdx, tS32* ps32RDBIdx);

// Main
tBOOL ARP_EXPVOLMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL ARP_EXPVOLMain_CheckUpdate(void* void_pIP, void* void_pSet);
tBOOL ARP_EXPVOLMain_GetCurrentVolume(void* void_pIP, tS32* ps32LGain, tS32* ps32RGain);
tBOOL ARP_EXPVOLMain_Proc(void* void_pIP , ARP_EXPVOL_PROC_DATA_TYPE* ptFrmBuf, tS32 s32ProcSizePerCh);
tBOOL ARP_EXPVOLMain_Close(void* void_pIP, void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __ARP_EXP_VOL_H__ */

