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
* @file    : hw_agc.h
* @version :
* @author  : CA.Wang
* @brief   : Hardware DRC
*/

#ifndef __ARP_HW_AGC_H__
#define __ARP_HW_AGC_H__

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
#define ARP_HWAGC_32BITS_Q8_DATA

/*----------------- Print Message Switch ----------------*/
#define ENABLE_ARP_HWAGC_PARSER_PRINTF

/*--------------------- DRC Info. -----------------------*/
#define ARP_HWAGC_MIN_GAINLIMT   ((tU16)0)
#define ARP_HWAGC_MAX_GAINLIMT   ((tU16)511)

#define ARP_HWAGC_MIN_TARGET     ((tU16)0)
#define ARP_HWAGC_MAX_TARGET     ((tU16)1023)

#define ARP_HWAGC_MIN_COMPRESSRATIO ((tU16)0)
#define ARP_HWAGC_MAX_COMPRESSRATIO ((tU16)3)

#define ARP_HWAGC_MIN_ATCOEFF    ((tU16)0)
#define ARP_HWAGC_MAX_ATCOEFF    ((tU16)31)

#define ARP_HWAGC_MIN_RTCOEFF    ((tU16)0)
#define ARP_HWAGC_MAX_RTCOEFF    ((tU16)31)

#define ARP_HWAGC_MIN_HPFCOEFF   ((tU16)0)
#define ARP_HWAGC_MAX_HPFCOEFF   ((tU16)7)

#define ARP_HWAGC_MIN_LPFCOEFF   ((tU16)0)
#define ARP_HWAGC_MAX_LPFCOEFF   ((tU16)7)

#define ARP_HWAGC_MIN_NOISELEVEL ((tU16)0)
#define ARP_HWAGC_MAX_NOISELEVEL ((tU16)7)

#define ARP_HWAGC_MIN_NOISECOEFF ((tU16)0)
#define ARP_HWAGC_MAX_NOISECOEFF ((tU16)31)

#define ARP_HWAGC_MIN_NOISEPERIOD ((tU16)0)
#define ARP_HWAGC_MAX_NOISEPERIOD ((tU16)65535)

#define ARP_HWAGC_MIN_TAPDELAY ((tU16)0) 
#define ARP_HWAGC_MAX_TAPDELAY ((tU16)1023) 
/*============================================================================*/
// Data type definition
/*============================================================================*/
/*------------------- Source Data Type ------------------*/
#ifdef ARP_HWAGC_32BITS_Q8_DATA
typedef tS32 ARP_HWAGC_PROC_DATA_TYPE;
#else
typedef tS16 ARP_HWAGC_PROC_DATA_TYPE;
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
    tU16 u16NoisePeriod_VoiceBand;
    tU8 u8TapDelay_VoiceBand;
    tU8 u8TapDelay;
}ARP_HWAGC_PAR_s;

#define ARP_SIZEOF_HWAGC_DATA_POWER      (sizeof(tU8))
#define ARP_SIZEOF_HWAGC_DATA_SIGNALINFO (sizeof(tU8) + sizeof(tU16) + sizeof(tU16) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8))
#define ARP_SIZEOF_HWAGC_DATA_FILTER     (sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8))
#define ARP_SIZEOF_HWAGC_DATA_NOISEINFO  (sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU8) + sizeof(tU16) + sizeof(tU16))
#define ARP_SIZEOF_HWAGC_DATA_TAPDELAYINFO (sizeof(tU8)+ sizeof(tU8))
#define ARP_SIZEOF_HWAGC_DATA (ARP_SIZEOF_HWAGC_DATA_POWER + ARP_SIZEOF_HWAGC_DATA_SIGNALINFO + ARP_SIZEOF_HWAGC_DATA_FILTER + ARP_SIZEOF_HWAGC_DATA_NOISEINFO+ARP_SIZEOF_HWAGC_DATA_TAPDELAYINFO)

typedef struct
{
    // IP control interface
    ARP_HWAGC_PAR_s sHWAGC_Ctr;
    tU8   bUpdateFlag;

    // IP public variable
    tS32  s32FrmSz;
    tS32  s32SmpFreq;
    tS32  s32ChumN;
}ARP_HWAGC_MAIN_s;

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
tS32 ARP_ATTR_16BITS ARP_HWAGCPar_CopyParFromCalbTable(tU8* ps8ModeData,const tU8* ps8CalibTab);
tS32 ARP_ATTR_16BITS ARP_HWAGCPar_Table2ParStrc(void* void_pSet, tU8* pu8InBuf);
tS32 ARP_ATTR_16BITS ARP_HWAGCPar_ParStrc2Table(void* void_pSet, tU8* pu8InBuf);

// Par
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetPower(void* void_pSet, tU8 bEn);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetGainLimitMode(void* void_pSet, tU8 u8Mode);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetGainLimit(void* void_pSet, tU16 u16GainLimit);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetTargetLevel(void* void_pSet, tU16 u16Level);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetCompressRatio(void* void_pSet, tU8 u8Ratio);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetATCoeff(void* void_pSet, tU8 u8AttCoeff, tU8 u8AttCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetRTCoeff(void* void_pSet, tU8 u8RelCoeff, tU8 u8RelCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetHPF(void* void_pSet, tU8 u8HPFCoeff, tU8 u8HPFCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetLPF(void* void_pSet, tU8 u8LPFCoeff, tU8 u8LPFCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetNoiseGatePower(void* void_pSet, tU8 bEn);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetNoiseGateMode(void* void_pSet, tU8 u8Mode);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetNoiseGateLevel(void* void_pSet, tU8 u8Level);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetNoiseGateATCoeff(void* void_pSet, tU8 u8NoiseCoeff, tU8 u8NoiseCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetNoiseGatePeriod(void* void_pSet, tU16 u16Period, tU16 u16Period_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_SetTapDelay(void* void_pSet, tU8 u8TapDelay, tU8 u8TapDelay_VoiceBand);

tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetPower(void* void_pSet, tU8* pbEn);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetGainLimitMode(void* void_pSet, tU8* pu8Mode);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetGainLimit(void* void_pSet, tU16* pu16GainLimit);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetTargetLevel(void* void_pSet, tU16* pu16Level);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetCompressRatio(void* void_pSet, tU8* pu8Ratio);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetATCoeff(void* void_pSet, tU8* pu8AttCoeff, tU8* pu8AttCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetRTCoeff(void* void_pSet, tU8* pu8RelCoeff, tU8* pu8RelCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetHPF(void* void_pSet, tU8* pu8HPFCoeff, tU8* pu8HPFCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetLPF(void* void_pSet, tU8* pu8LPFCoeff, tU8* pu8LPFCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetNoiseGatePower(void* void_pSet, tU8* pbEn);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetNoiseGateMode(void* void_pSet, tU8* pu8Mode);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetNoiseGateLevel(void* void_pSet, tU8* pu8Level);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetNoiseGateATCoeff(void* void_pSet, tU8* pu8NoiseCoeff, tU8* pu8NoiseCoeff_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetNoiseGatePeriod(void* void_pSet, tU16* pu16Period, tU16* pu16Period_VoiceBand);
tBOOL ARP_ATTR_16BITS ARP_HWAGCPar_GetTapdelay(void* void_pSet, tU8* pu8TapDelay, tU8* pu8TapDelay_Voiceband);

// Main
tBOOL ARP_HWAGCMain_Init(void* void_pIP, void* void_pSet, tS32 s32ChNum, tS32 s32SampleRate);
tBOOL ARP_HWAGCMain_Check(void* void_pIP, void* void_pSet, tU8 bRtChangeGain, tU8* pbUpdateFlag);
tBOOL ARP_HWAGCMain_Update(void* void_pIP, void* void_pSet, tU8 bRtChangeGain);
tBOOL ARP_HWAGCMain_Proc(void* void_pIP, tS32* ptProcBuf, tS32 s32ProcSizePerCh);
tBOOL ARP_HWAGCMain_Close(void* void_pIP , void* void_pSet);

#ifdef __cplusplus
}
#endif

#endif // __ARP_HW_AGC_H__

