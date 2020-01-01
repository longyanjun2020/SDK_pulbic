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
* @file    : hw_drc.h
* @version :
* @author  : CA.Wang
* @brief   : Hardware DRC
*/

#ifndef __HW_DRC_H__
#define __HW_DRC_H__

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
#define POST_PROC_HWDRC_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_HWDRC_PARSER_PRINTF

/*--------------------- DRC Info. -----------------------*/
#define HWDRC_MIN_GAINLIMT   ((tU16)0)
#define HWDRC_MAX_GAINLIMT   ((tU16)511)

#define HWDRC_MIN_TARGET     ((tU16)0)
#define HWDRC_MAX_TARGET     ((tU16)1023)

#define HWDRC_MIN_COMPRESSRATIO ((tU16)0)
#define HWDRC_MAX_COMPRESSRATIO ((tU16)3)

#define HWDRC_MIN_ATCOEFF    ((tU16)0)
#define HWDRC_MAX_ATCOEFF    ((tU16)31)

#define HWDRC_MIN_RTCOEFF    ((tU16)0)
#define HWDRC_MAX_RTCOEFF    ((tU16)31)

#define HWDRC_MIN_HPFCOEFF   ((tU16)0)
#define HWDRC_MAX_HPFCOEFF   ((tU16)7)

#define HWDRC_MIN_LPFCOEFF   ((tU16)0)
#define HWDRC_MAX_LPFCOEFF   ((tU16)7)

#define HWDRC_MIN_NOISELEVEL ((tU16)0)
#define HWDRC_MAX_NOISELEVEL ((tU16)7)

#define HWDRC_MIN_NOISECOEFF ((tU16)0)
#define HWDRC_MAX_NOISECOEFF ((tU16)31)

#define HWDRC_MIN_NOISEPERIOD ((tU16)0)
#define HWDRC_MAX_NOISEPERIOD ((tU16)65535)

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef POST_PROC_HWDRC_32BITS_Q8_DATA
typedef tS32 HWDRC_PROC_DATA_TYPE;
#else
typedef tS16 HWDRC_PROC_DATA_TYPE;
#endif

/*----------------------- Interface ---------------------*/
typedef struct
{
    // Power
    tU8  bEn;             // Function Enable                 : 0: Disable  1: Enable

    // Signal Info
    tU8  u8GainLimitMode; // Gain-Limit Mode                 : 0: programable region  1: by Ratio
    tU16 u16GainLimit;    // Gain Limit                      : (unsigned) 7.2 (dB)

    tU16 u16Target;       // Threshold                       : (unsigned) 8.2 (-dB)
    tU8  u8CompressRatio; // Ratio                           : 0: (inf:1)  1: (2:1)  2: (4:1)  3: (8:1)
    tU8  u8AttCoeff;      // Attack slope                    : 0 ~ 31 (-1.06m dB/FS)
    tU8  u8AttCoeff_VoiceBand;
    tU8  u8RelCoeff;      // Release slope                   : 0 ~ 31 (33.13u dB/FS)
    tU8  u8RelCoeff_VoiceBand;

    // Filter
    tU8  u8HPFCoeff;      // High-Pass freq. corner          : 0 ~ 7 ==> 1-2^-3 ~ 1-2^-10
    tU8  u8HPFCoeff_VoiceBand;

    tU8  u8LPFCoeff;      // Low-Pass freq. corner           : 0 ~ 7 ==> 2^-2 ~ 2^-9
    tU8  u8LPFCoeff_VoiceBand;

    // Noise Info
    tU8  bNoiseGateEn;    // Noise Gating Function Enable    : 0: Disable  1: Enable
    tU8  u8NoiseGateMode; // Noise Gating Mode               : 0: Holding  1: Fading out to 0dB
    tU8  u8NoiseLevel;    // Reset threshold for Level CNT   : 0 ~ 7 ==> -78 ~ -36 (6dB/step)

    tU8  u8NoiseCoeff;    // Attack slope(for noise gating)  : 0 ~ 31 (-33.13u dB/FS)
    tU8  u8NoiseCoeff_VoiceBand;
    tU16 u16NoisePeriod;  // Trigger threshold for Level CNT : 0 ~ 65535 (FS)
    tU16  u16NoisePeriod_VoiceBand;
}M_HWDRC_PAR_s;
#define SIZEOF_HWDRC_DATA_POWER      (sizeof(tU8))
#define SIZEOF_HWDRC_DATA_SIGNALINFO (sizeof(tU8) + sizeof(tU16) + sizeof(tU16) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8))
#define SIZEOF_HWDRC_DATA_FILTER     (sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8))
#define SIZEOF_HWDRC_DATA_NOISEINFO  (sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU16) + sizeof(tU16))
#define SIZEOF_HWDRC_DATA (SIZEOF_HWDRC_DATA_POWER + SIZEOF_HWDRC_DATA_SIGNALINFO + SIZEOF_HWDRC_DATA_FILTER + SIZEOF_HWDRC_DATA_NOISEINFO)

typedef struct
{
    // IP control interface
    M_HWDRC_PAR_s sHWDRC_Ctr;
    tU8   bUpdateFlag;

    // IP public variable
    tS32  s32FrmSz;
    tS32  s32SmpFreq;
    tS32  s32ChumN;
}M_HWDRC_MAIN_s;

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
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_CopyParFromCalbTable(tU8* ps8ModeData, tU8* ps8CalibTab);
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetPower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetGainLimitMode(void* void_pSet, tU8 u8Mode);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetGainLimit(void* void_pSet, tU16 u16GainLimit);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetTargetLevel(void* void_pSet, tU16 u16Level);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetCompressRatio(void* void_pSet, tU8 u8Ratio);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetATCoeff(void* void_pSet, tU8 u8AttCoeff, tU8 u8AttCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetRTCoeff(void* void_pSet, tU8 u8RelCoeff, tU8 u8RelCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetHPF(void* void_pSet, tU8 u8HPFCoeff, tU8 u8HPFCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetLPF(void* void_pSet, tU8 u8LPFCoeff, tU8 u8LPFCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetNoiseGatePower(void* void_pSet, tU8 bEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetNoiseGateMode(void* void_pSet, tU8 u8Mode);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetNoiseGateLevel(void* void_pSet, tU8 u8Level);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetNoiseGateATCoeff(void* void_pSet, tU8 u8NoiseCoeff, tU8 u8NoiseCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_SetNoiseGatePeriod(void* void_pSet, tU16 u16Period, tU16 u16Period_VoiceBand);

tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetPower(void* void_pSet, tU8* pbEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetGainLimitMode(void* void_pSet, tU8* pu8Mode);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetGainLimit(void* void_pSet, tU16* pu16GainLimit);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetTargetLevel(void* void_pSet, tU16* pu16Level);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetCompressRatio(void* void_pSet, tU8* pu8Ratio);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetATCoeff(void* void_pSet, tU8* pu8AttCoeff, tU8* pu8AttCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetRTCoeff(void* void_pSet, tU8* pu8RelCoeff, tU8* pu8RelCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetHPF(void* void_pSet, tU8* pu8HPFCoeff, tU8* pu8HPFCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetLPF(void* void_pSet, tU8* pu8LPFCoeff, tU8* pu8LPFCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetNoiseGatePower(void* void_pSet, tU8* pbEn);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetNoiseGateMode(void* void_pSet, tU8* pu8Mode);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetNoiseGateLevel(void* void_pSet, tU8* pu8Level);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetNoiseGateATCoeff(void* void_pSet, tU8* pu8NoiseCoeff, tU8* pu8NoiseCoeff_VoiceBand);
tBOOL POSTPROCMGR_ATTR_16BITS AUD_HWDRCPar_GetNoiseGatePeriod(void* void_pSet, tU16* pu16Period, tU16* pu16Period_VoiceBand);

// Main
tBOOL AUD_HWDRCMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL AUD_HWDRCMain_Check(void* void_pIP, void* void_pSet, tU8 bRtChangeGain, tU8* pbUpdateFlag);
tBOOL AUD_HWDRCMain_Update(void* void_pIP, void* void_pSet, tU8 bRtChangeGain);
tBOOL AUD_HWDRCMain_Proc(void* void_pIP, tS32* ptProcBuf, tS32 s32ProcSizePerCh);
tBOOL AUD_HWDRCMain_Close(void* void_pIP , void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif /* __HW_DRC_H__ */

