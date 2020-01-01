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
* @file    : dm2.h
* @version :
* @author  : CA.Wang
* @brief   : Control Third Party Dolby Mobile 2 Solution
*/

#ifndef __DM2_H__
#define __DM2_H__

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
/*---------------- Print Message Switch -----------------*/
#define ENABLE_DM2_PARSER_PRINTF

/*-------------------- EQ band size ---------------------*/
#define DM2_GEQ_BANDS_MAX   (7)
#define DM2_CHANNEL_MAX     (2)
#define DM2_SAMPLECOUNT_MAX (512*2)

/*---------------------- Interface ----------------------*/
typedef struct
{
    // Boundle
    tS32 s32DM2_Bypass;

    // Mono to Stereo
    tS32 s32DM2_M2S_enable;

    // High-Frequency Enhancer
    tS32 s32DM2_HFE_enable;
    tS32 s32DM2_HFE_depth;

    // Sound Space Expander
    tS32 s32DM2_SSE_enable;
    tS32 s32DM2_SSE_width;
    tS32 s32DM2_SSE_spkmode;

    // Sound Space for headphones
    tS32 s32DM2_SSH_enable;
    tS32 s32DM2_SSH_mode;

    // Mobile Surround UpMixer
    tS32 s32DM2_MUP_enable;

    // Mobile Surround
    tS32 s32DM2_MSR_enable;

    // Sound Level Controller
    tS32 s32DM2_SLC_enable;
    tS32 s32DM2_SLC_level;
    tS32 s32DM2_SLC_depth;

    // GEQ
    tS32 s32DM2_GEQ_enable;
    tS32 s32DM2_GEQ_nbands;
    tS32 s32DM2_GEQ_preamp;
    tS32 s32DM2_GEQ_maxboost;
    tS32 s32DM2_GEQ_gain[DM2_GEQ_BANDS_MAX];

    // Volume
    tS32 s32DM2_VOL_enable;
    tS32 s32DM2_VOL_gain_type;
    tS32 s32DM2_VOL_internal_gain;
    tS32 s32DM2_VOL_external_gain;
    tS32 s32DM2_VOL_balance;
    tS32 s32DM2_VOL_mute;

    // Natural Bass
    tS32 s32DM2_NB_enable;
    tS32 s32DM2_NB_cutoff;
    tS32 s32DM2_NB_boost;
    tS32 s32DM2_NB_level;

    // Fade
    tS32 s32DM2_FADE_enable;
    tS32 s32DM2_FADE_target;
    tS32 s32DM2_FADE_time;

}M_DM2_PAR_s;
#define SIZEOF_DM2_DATA (sizeof(tS32)*38)

typedef struct
{
    // IP control interface
    M_DM2_PAR_s sDM2_Ctr;
    tU8	   bUpdateFlag;

    // IP public variable
    tS32  s32ChumN;
    tS32  s32FrmSz;
    tS32  s32SmpFreq;

    // memory control
    tS16  ptFrmBuf[DM2_SAMPLECOUNT_MAX * DM2_CHANNEL_MAX];
    tS32  s32RemnCount;

}M_DM2_MAIN_s;

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
tS32 AUD_DM2Par_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 AUD_DM2Par_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 AUD_DM2Par_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL AUD_DM2Par_SetBypass(void* void_pSet, tU8 u8Enable);
tBOOL AUD_DM2Par_GetBypass(void* void_pSet, tU8* pu8Enable);
tBOOL AUD_DM2Par_SetM2S(void* void_pSet, tU8 u8Enable);
tBOOL AUD_DM2Par_GetM2S(void* void_pSet, tU8* pu8Enable);
tBOOL AUD_DM2Par_SetHFE(void* void_pSet, tS32 s32Enable, tS32 s32Depth);
tBOOL AUD_DM2Par_GetHFE(void* void_pSet, tS32* ps32Enable, tS32* ps32Depth);
tBOOL AUD_DM2Par_SetSSE(void* void_pSet, tS32 s32Enable, tS32 s32Width, tS32 s32Mode);
tBOOL AUD_DM2Par_GetSSE(void* void_pSet, tS32* ps32Enable, tS32* ps32Width, tS32* s32Mode);
tBOOL AUD_DM2Par_SetSSH(void* void_pSet, tS32 s32Enable, tS32 s32Mode);
tBOOL AUD_DM2Par_GetSSH(void* void_pSet, tS32* ps32Enable, tS32* ps32Mode);
tBOOL AUD_DM2Par_SetMUP(void* void_pSet,tS32 s32Enable);
tBOOL AUD_DM2Par_GetMUP(void* void_pSet, tU8* pu8Enable);
tBOOL AUD_DM2Par_SetMSR(void* void_pSet, tU8 u8Enable);
tBOOL AUD_DM2Par_GetMSR(void* void_pSet, tU8* pu8Enable);
tBOOL AUD_DM2Par_SetSLC(void* void_pSet, tS32 s32Enable, tS32 s32Level, tS32 s32Depth);
tBOOL AUD_DM2Par_GetSLC(void* void_pSet, tS32* ps32Enable, tS32* ps32Level, tS32* s32Depth);
tBOOL AUD_DM2Par_SetGEQ(void* void_pSet, tS32 s32Enable, tS32 s32Bands);
tBOOL AUD_DM2Par_GetGEQ(void* void_pSet, tS32* ps32Enable, tS32* ps32Bands);
tBOOL AUD_DM2Par_SetGEQGlbGain(void* void_pSet, tS32 s32PreAmp, tS32 s32MaxBoost);
tBOOL AUD_DM2Par_GetGEQGlbGain(void* void_pSet, tS32* ps32PreAmp, tS32* ps32MaxBoost);
tBOOL AUD_DM2Par_SetGEQBandGain(void* void_pSet, tS32 s32bandIdx, tS32 s32Gain);
tBOOL AUD_DM2Par_GetGEQBandGain(void* void_pSet, tS32 s32bandIdx, tS32* ps32Gain);
tBOOL AUD_DM2Par_SetVOLPower(void* void_pSet, tS32 s32Enable, tS32 s32GainType);
tBOOL AUD_DM2Par_GetVOLPower(void* void_pSet, tS32* ps32Enable, tS32* ps32GainType);
tBOOL AUD_DM2Par_SetVOLGain(void* void_pSet, tS32 s32IntGain, tS32 s32ExtGain, tS32 s32Balance, tS32 s32Mute);
tBOOL AUD_DM2Par_GetVOLGain(void* void_pSet, tS32* ps32IntGain, tS32* ps32ExtGain, tS32* ps32Balance, tS32* ps32Mute);
tBOOL AUD_DM2Par_SetNB(void* void_pSet, tS32 s32Enable, tS32 s32CutOff, tS32 s32Boost, tS32 s32Level);
tBOOL AUD_DM2Par_GetNB(void* void_pSet, tS32* ps32Enable, tS32* ps32CutOff, tS32* ps32Boost, tS32* ps32Level);
tBOOL AUD_DM2Par_SetFADE(void* void_pSet, tS32 s32Enable, tS32 s32Target, tS32 s32FadeTime);
tBOOL AUD_DM2Par_GetFADE(void* void_pSet, tS32* ps32Enable, tS32* ps32Target, tS32* ps32FadeTime);

// Main
tBOOL AUD_DM2Main_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_DM2Main_Check(void* void_pIP, void* void_pSet, tU8* pbUpdateFlag);
tBOOL AUD_DM2Main_Update(void* void_pIP, void* void_pSet);
tBOOL AUD_DM2Main_Proc(void* void_pIP, tS16* ptProcBuf, tS32* ps32ProcSizePerCh);
tBOOL AUD_DM2Main_Close(void* void_pIP , void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __DM2_H__ */

