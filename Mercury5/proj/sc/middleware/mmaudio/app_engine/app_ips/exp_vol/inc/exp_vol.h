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
* @file    : exp_vol.h
* @version :
* @author  : Wendy.Lin
* @brief   : control volume gain exponentially
*/

#ifndef __EXP_VOL_H__
#define __EXP_VOL_H__

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
//#define POST_PROC_EXPVOL_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_EXPVOL_PARSER_PRINTF

/*-------------------- Channel size ---------------------*/
#define EXPVOL_MAX_CH_NUM 2

/*--------------------- Gain Table ----------------------*/
#define RIGHT_SHIFT       (14)

#if RIGHT_SHIFT == 13

#define ZERO_DB_GAIN      ((tS16)8191)
// Gain table from 12~-74dB, 0.5dB apart
#define MIN_GAIN_TABIDX   (-148)
#define MAX_GAIN_TABIDX   (24)
#define GAIN_TABSIZE      (MAX_GAIN_TABIDX - MIN_GAIN_TABIDX + 1)

#elif RIGHT_SHIFT == 14

#define ZERO_DB_GAIN      ((tS16)16383)
// Gain table from 6~-80dB, 0.5dB apart
#define MIN_GAIN_TABIDX   (-160)
#define MAX_GAIN_TABIDX   (12)
#define GAIN_TABSIZE      (MAX_GAIN_TABIDX - MIN_GAIN_TABIDX + 1)

#else

#error  Invalid Gain Table!!!

#endif

/*--------------------- Time Const ----------------------*/
// Time Const table from 0~18ms, 2ms apart
#define MIN_TIMECONST_TABIDX     (0)
#define MAX_TIMECONST_TABIDX     (9)
#define TIMECONST_TABSIZE        (MAX_TIMECONST_TABIDX - MIN_TIMECONST_TABIDX + 1)
#define DEFAULT_TIMECONST_TABIDX (8)

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_EXPVOL_32BITS_Q8_DATA
typedef tS32 EXPVOL_PROC_DATA_TYPE;
#else
typedef tS16 EXPVOL_PROC_DATA_TYPE;
#endif

/*----------------------- Interface ---------------------*/
typedef struct
{
    tU8  bEn;
    tS16 s16InstDBIdx[EXPVOL_MAX_CH_NUM];
    tS16 s16TgtDBIdx[EXPVOL_MAX_CH_NUM];
    tS16 s16FadTimeIdx;
    tU8  bInstChange;
}M_VOL_EXP_PAR_s;
#define SIZEOF_EXP_VOL_DATA (sizeof(tU8) + (sizeof(tS16) * EXPVOL_MAX_CH_NUM) + (sizeof(tS16) * EXPVOL_MAX_CH_NUM) + sizeof(tS16) + sizeof(tU8))

typedef struct
{
    // IP control interface
    M_VOL_EXP_PAR_s sExpVol_Ctr;
    tU8   bUpdateFlag;

    // IP public variable
    tS32 s32SmpFreq;
    tS32 s32ChumN;

    tS16 s16InstGain[EXPVOL_MAX_CH_NUM];/* gain applied right now */
    tS16 s16TgtGain[EXPVOL_MAX_CH_NUM]; /* in a smooth gain change, the gain we are aiming for */

    // IP private variable
    tS16 s16Shift[EXPVOL_MAX_CH_NUM];
}M_VOL_EXP_MAIN_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_SetPower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_GetPower(void* void_pSet, tU8 *pbEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_SetFadingTime(void* void_pSet, tS16 s16FadingTimeIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_GetFadingTime(void* void_pSet, tS16* ps16FadingTimeIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_SetInstGain(void* void_pSet, tS32 s32LDBIdx, tS32 s32RDBIdx, tU8 bInstChange);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_GetInstGain(void* void_pSet, tS32* ps32LDBIdx, tS32* ps32RDBIdx, tU8* pbInstChange);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_SetTargetGain(void* void_pSet, tS32 s32LDBIdx, tS32 s32RDBIdx);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_EXPVOLPar_GetTargetGain(void* void_pSet, tS32* ps32LDBIdx, tS32* ps32RDBIdx);

// Main
tBOOL AUD_EXPVOLMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_EXPVOLMain_CheckUpdate(void* void_pIP, void* void_pSet);
tBOOL AUD_EXPVOLMain_GetCurrentVolume(void* void_pIP, tS32* ps32LGain, tS32* ps32RGain);
tBOOL AUD_EXPVOLMain_Proc(void* void_pIP , EXPVOL_PROC_DATA_TYPE* ptFrmBuf, tS32 s32ProcSizePerCh);
tBOOL AUD_EXPVOLMain_Close(void* void_pIP, void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __EXP_VOL_H__ */

