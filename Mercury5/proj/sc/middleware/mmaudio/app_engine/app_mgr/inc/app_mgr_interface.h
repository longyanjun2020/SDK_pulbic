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
* @file    : app_mgr_interface.h
* @version :
* @author  : CA.Wang
* @brief   : dinterface define
*/

#ifndef __APP_MGR_INTERFACE_H__
#define __APP_MGR_INTERFACE_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "app_confg.h"

#if !defined(_MSC_VER)
#include <stdint.h>
#endif

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif
typedef void *(* tPMem_alloc)(unsigned int size);
typedef void (* tPMem_free)(void *p);

// Parser
int AUDPostProcParser_IniIntParTab(unsigned char* u8Addr, unsigned int u32BufSz);
int AUDPostProcParser_PshClbEngID2IntParTab(unsigned char * ps8CalibTab);
int AUDPostProcParser_PshClbPar2IntParTab(unsigned short u16TargetIPID, unsigned int u32TargetModeIdx, unsigned char * ps8CalibTab);
int AUDPostProcParser_PshExtParTab2IntParTab(unsigned char* u8Buffer, unsigned int u32SubLen, unsigned int u32InTotalDatalen);
int AUDPostProcParser_CvtIntParTable2IntParStrc(void);
int AUDPostProcParser_CloseIntParTab(void);

// Paramater
int AUDPostProcPar_Reverb_SetPow(unsigned char bEn);
int AUDPostProcPar_Reverb_GetPow(unsigned char * pbEn);
int AUDPostProcPar_Surround_SetPow(unsigned char bEn);
int AUDPostProcPar_Surround_GetPow(unsigned char* pbEn);
int AUDPostProcPar_UserPEQ_SetPow(unsigned char bEn);
int AUDPostProcPar_UserPEQ_GetPow(unsigned char* pbEn);
int AUDPostProcPar_UserPEQ_SetGlbGain(int s32GGIDx);
int AUDPostProcPar_UserPEQ_SetBandPar(int s32BandIdx, int s32GainIdx, int s32Fc, int s32QIdx, unsigned char bBandPass);
int AUDPostProcPar_BIG3HWGEQ_SetPow(unsigned char bEn);
int AUDPostProcPar_BIG3HWGEQ_GetPow(unsigned char* pbEn);
int AUDPostProcPar_BIG3HWGEQ_Set7BandsMode(unsigned char bEn);
int AUDPostProcPar_BIG3HWGEQ_SetBandGain(int s32BandIdx, int s32GainIdx);
int AUDPostProcPar_G1HWGEQ_SetPow(unsigned char bEn);
int AUDPostProcPar_G1HWGEQ_GetPow(unsigned char* pbEn);
int AUDPostProcPar_G1HWGEQ_Set7BandsMode(unsigned char bEn);
int AUDPostProcPar_G1HWGEQ_SetBandGain(int s32BandIdx, int s32GainIdx);
int AUDPostProcPar_SpeakerPEQ_SetPow(unsigned char bEn);
int AUDPostProcPar_SpeakerPEQ_GetPow(unsigned char* pbEn);
int AUDPostProcPar_SpeakerPEQ_SetGlbGain(int s32GGIDx);
int AUDPostProcPar_SpeakerPEQ_SetBandPar(int s32BandIdx, int s32GainIdx, int s32Fc, int s32QIdx, unsigned char bBandPass);
int AUDPostProcPar_BIG3HWPEQ_SetPow(unsigned char bEn);
int AUDPostProcPar_BIG3HWPEQ_GetPow(unsigned char* pbEn);
int AUDPostProcPar_BIG3HWPEQ_SetGlbGain(int s32GGIDx);
int AUDPostProcPar_BIG3HWPEQ_SetBandPar(int s32BandIdx, int s32GainIdx, int s32Fc, int s32QIdx, unsigned char bBandPass);
int AUDPostProcPar_G1HWPEQ_SetPow(unsigned char bEn);
int AUDPostProcPar_G1HWPEQ_GetPow(unsigned char* pbEn);
int AUDPostProcPar_G1HWPEQ_SetGlbGain(int s32GGIDx);
int AUDPostProcPar_G1HWPEQ_SetBandPar(int s32BandIdx, int s32GainIdx, int s32Fc, int s32QIdx, unsigned char bBandPass);
int AUDPostProcPar_DRCLimiter_SetPow(unsigned char bEn);
int AUDPostProcPar_DRCLimiter_GetPow(unsigned char* pbEn);
int AUDPostProcPar_DRCLimiter_SetPar(short s16LimitIdx_Ch1, unsigned short u16ATIdx_Ch1, unsigned short u16RTIdx_Ch1, short s16LimitIdx_Ch2, unsigned short u16ATIdx_Ch2, unsigned short u16RTIdx_Ch2);
int AUDPostProcPar_DRCLimiter_SetDPGA(int s32DPGAIdx);
int AUDPostProcPar_DRCLimiterV2_SetPow(unsigned char bEn);
int AUDPostProcPar_DRCLimiterV2_GetPow(unsigned char* pbEn);
int AUDPostProcPar_DRCLimiterV2_SetExtPower(unsigned char bEn);
int AUDPostProcPar_DRCLimiterV2_SetExtWeightGain(int s32Ch1_WeightIdx, int s32Ch2_WeightIdx);
int AUDPostProcPar_DRCLimiterV2_SetExtDPGAGain(int s32DPGA_dB_Idx, int s32DPGA_ClipVpp_Idx);
int AUDPostProcPar_DRCLimiterV2_SetExtDRVGain(int s32DRV_dB_Idx, int s32DRV_ClipVpp_Idx);
int AUDPostProcPar_DRCLimiterV2_SetExtAMPGain(int s32AMP_dB_Idx, int s32AMP_ClipVpp_Idx);
int AUDPostProcPar_LookaheadDRCLimiter_SetPow(unsigned char bEn);
int AUDPostProcPar_LookaheadDRCLimiter_GetPow(unsigned char* pbEn);
int AUDPostProcPar_LookaheadDRCLimiter_SetDPGA(int s32DPGAIdx);
int AUDPostProcPar_LookaheadDRCLimiter_SetLookaheadTime(unsigned short u16LookMs_Ch1, unsigned short u16LookMs_Ch2);
int AUDPostProcPar_LookaheadDRCLimiter_SetPar(short s16LimitIdx_Ch1, unsigned short u16ATIdx_Ch1, unsigned short u16RTIdx_Ch1, short s16LimitIdx_Ch2, unsigned short u16ATIdx_Ch2, unsigned short u16RTIdx_Ch2);
int AUDPostProcPar_HardLimiter_SetPow(unsigned char bEn);
int AUDPostProcPar_HardLimiter_GetPow(unsigned char* pbEn);
int AUDPostProcPar_HardLimiter_SetLookaheadTime(unsigned short u16LookMs_Ch1, unsigned short u16LookMs_Ch2);
int AUDPostProcPar_HardLimiter_SetPar(short s16LimitIdx_Ch1, unsigned short u16RTIdx_Ch1, short s16LimitIdx_Ch2, unsigned short u16RTIdx_Ch2);
int AUDPostProcPar_HardLimiter_SetDPGA(int s32DPGAIdx);
int AUDPostProcPar_BIG3HWDRC_SetPow(unsigned char bEn);
int AUDPostProcPar_BIG3HWDRC_GetPow(unsigned char* pbEn);
int AUDPostProcPar_BIG3HWDRC_SetGainLimitMode(unsigned char u8Mode);
int AUDPostProcPar_BIG3HWDRC_SetGainLimit(unsigned short u16GainLimit);
int AUDPostProcPar_BIG3HWDRC_SetTargetLevel(unsigned short u16Level);
int AUDPostProcPar_BIG3HWDRC_SetCompressRatio(unsigned char u8Ratio);
int AUDPostProcPar_BIG3HWDRC_SetATCoeff(unsigned char u8AttCoeff, unsigned char u8AttCoeff_VoiceBand);
int AUDPostProcPar_BIG3HWDRC_SetRTCoeff(unsigned char u8RelCoeff, unsigned char u8RelCoeff_VoiceBand);
int AUDPostProcPar_BIG3HWDRC_SetHPF(unsigned char u8HPFCoeff, unsigned char u8HPFCoeff_VoiceBand);
int AUDPostProcPar_BIG3HWDRC_SetLPF(unsigned char u8LPFCoeff, unsigned char u8LPFCoeff_VoiceBand);
int AUDPostProcPar_BIG3HWDRC_SetNoiseGatePower(unsigned char bEn);
int AUDPostProcPar_BIG3HWDRC_SetNoiseGateMode(unsigned char u8Mode);
int AUDPostProcPar_BIG3HWDRC_SetNoiseGateLevel(unsigned char u8Level);
int AUDPostProcPar_BIG3HWDRC_SetNoiseGateATCoeff(unsigned char u8NoiseCoeff, unsigned char u8NoiseCoeff_VoiceBand);
int AUDPostProcPar_BIG3HWDRC_SetNoiseGatePeriod(unsigned short u16Period, unsigned short u16Period_VoiceBand);
int AUDPostProcPar_G1HWDRC_SetPow(unsigned char bEn);
int AUDPostProcPar_G1HWDRC_GetPow(unsigned char* pbEn);
int AUDPostProcPar_G1HWDRC_SetGainLimitMode(unsigned char u8Mode);
int AUDPostProcPar_G1HWDRC_SetGainLimit(unsigned short u16GainLimit);
int AUDPostProcPar_G1HWDRC_SetTargetLevel(unsigned short u16Level);
int AUDPostProcPar_G1HWDRC_SetCompressRatio(unsigned char u8Ratio);
int AUDPostProcPar_G1HWDRC_SetATCoeff(unsigned char u8AttCoeff, unsigned char u8AttCoeff_VoiceBand);
int AUDPostProcPar_G1HWDRC_SetRTCoeff(unsigned char u8RelCoeff, unsigned char u8RelCoeff_VoiceBand);
int AUDPostProcPar_G1HWDRC_SetHPF(unsigned char u8HPFCoeff, unsigned char u8HPFCoeff_VoiceBand);
int AUDPostProcPar_G1HWDRC_SetLPF(unsigned char u8LPFCoeff, unsigned char u8LPFCoeff_VoiceBand);
int AUDPostProcPar_G1HWDRC_SetNoiseGatePower(unsigned char bEn);
int AUDPostProcPar_G1HWDRC_SetNoiseGateMode(unsigned char u8Mode);
int AUDPostProcPar_G1HWDRC_SetNoiseGateLevel(unsigned char u8Level);
int AUDPostProcPar_G1HWDRC_SetNoiseGateATCoeff(unsigned char u8NoiseCoeff, unsigned char u8NoiseCoeff_VoiceBand);
int AUDPostProcPar_G1HWDRC_SetNoiseGatePeriod(unsigned short u16Period, unsigned short u16Period_VoiceBand);
int AUDPostProcPar_Volume_SetPow(unsigned char bEn);
int AUDPostProcPar_Volume_GetPow(unsigned char * pbEn);
int AUDPostProcPar_Volume_SetFadingTime(short s16FadingTimeIdx);
int AUDPostProcPar_Volume_SetInstGain(int s32LDBIdx, int s32RDBIdx, unsigned char bInstChange);
int AUDPostProcPar_Volume_ChangeVolume(int s32Vol);
int AUDPostProcPar_Fader_SetPow(unsigned char bEn);
int AUDPostProcPar_Fader_GetPow(unsigned char* pbEn);
int AUDPostProcPar_Fader_SetFadeTimeMs(int s32FadeTimeMs);
int AUDPostProcPar_Fader_SetInitFade(unsigned char bInitFade);
int AUDPostProcPar_TimeStretch_SetPow(unsigned char bEn);
int AUDPostProcPar_TimeStretch_GetPow(unsigned char* pbEn);
int AUDPostProcPar_TimeStretch_SetRate(unsigned char u8Rate);
int AUDPostProcPar_TimePitchStretch_SetPow(unsigned char bEn);
int AUDPostProcPar_TimePitchStretch_GetPow(unsigned char* pbEn);
int AUDPostProcPar_TimePitchStretch_SetType(unsigned char u8TypeIdx);
int AUDPostProcPar_TimePitchStretch_SetRate(unsigned char u8Rate);
int AUDPostProcPar_DM2_SetPow(unsigned char  bEn);
int AUDPostProcPar_DM2_GetPow(unsigned char*  pbEn);
int AUDPostProcPar_DM2_SetM2S(unsigned char u8Enable);
int AUDPostProcPar_DM2_SetHFE(int s32Enable, int s32Depth);
int AUDPostProcPar_DM2_SetSSE(int s32Enable, int s32Width, int s32Mode);
int AUDPostProcPar_DM2_SetSSH(int s32Enable, int s32Mode);
int AUDPostProcPar_DM2_SetMUP(int s32Enable);
int AUDPostProcPar_DM2_SetMSR(unsigned char u8Enable);
int AUDPostProcPar_DM2_SetSLC(int s32Enable, int s32Level, int s32Depth);
int AUDPostProcPar_DM2_SetGEQ(int s32Enable, int s32Bands);
int AUDPostProcPar_DM2_SetGEQGlbGain(int s32PreAmp, int s32MaxBoost);
int AUDPostProcPar_DM2_SetGEQBandGain(int s32bandIdx, int s32Gain);
int AUDPostProcPar_DM2_SetVOLPower(int s32Enable, int s32GainType);
int AUDPostProcPar_DM2_SetVOLGain(int s32IntGain, int s32ExtGain, int s32Balance, int s32Mute);
int AUDPostProcPar_DM2_SetNB(int s32Enable, int s32CutOff, int s32Boost, int s32Level);
int AUDPostProcPar_DM2_SetFADE(int s32Enable, int s32Target, int s32FadeTime);
int AUDPostProcPar_Reverb_SetPow(unsigned char bEn);
int AUDPostProcPar_Reverb_GetPow(unsigned char* pbEn);
int AUDPostProcPar_Reverb_SetMode(unsigned char u8mode);

int AUDPostProcPar_Main_SetPow(unsigned char bEn);
int AUDPostProcPar_Main_GetPow(unsigned char* pbEn);
int AUDPostProcPar_Bass_GetPow(unsigned char* pbEn);
int AUDPostProcPar_Bass_SetPow(unsigned char bEn);
int AUDPostProcPar_SRSWOWHD_SetPow(unsigned char  bEn);
int AUDPostProcPar_SRSWOWHD_GetPow(unsigned char*  pbEn);
int AUDPostProcPar_WOWHD_SetPath(int s32Deviceidx);


int AUDPostProcPar_Main_SetSLDLM_Flag(unsigned char bEn);
unsigned char AUDPostProcPar_Main_GetSLDLM_Flag(void);
int AUDPostProcPar_WOWHD_Set3DSpaceCtrl(short s163DSpaceCtrl);
int AUDPostProcPar_WOWHD_Set3DCenterCtrl(short s163DCenterCtrl);
int AUDPostProcPar_WOWHD_SetFocusFactor(short s16FocusFactor);
int AUDPostProcPar_WOWHD_SetDefFactor(short s16defFactor);
int AUDPostProcPar_WOWHD_SetTBCtrl(short s16TrueBassCtrl);
int AUDPostProcPar_Main_Set_SRS_SLDLM_Flag(unsigned char bEn);
unsigned char AUDPostProcPar_Main_Get_SRS_SLDLM_Flag(void);

//memory size
int AUDPostProcMem_init(tPMem_alloc alloc_func, tPMem_free freefunc );

// Main IP
int AUDPostProcTime_PitchMain_Proc(int s32ChannelNum, int* s32SamplePerCh,  unsigned char** pIOBuffer);
int AUDPostProcMain_Init(int s32ChannelNum, int s32SampleRate);
int AUDPostProcMain_Proc(int s32ChannelNum, int* s32SamplePerCh, unsigned char* pIOBuffer);
int AUDPostProcMain_Close(void);

#ifdef __cplusplus
}
#endif

#endif // __APP_MGR_INTERFACE_H__

