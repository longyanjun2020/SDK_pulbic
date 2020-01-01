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
 * @file    fmrx_dev.h
 * @brief   This file defines FM radio driver function prototype and data structure
 */
#ifndef __FMRX_DEV_H__
#define __FMRX_DEV_H__

#include "vm_types.ht"
#if !defined(__SDK_SIMULATION__)
//#include "kernel.h"
#include "sys_traces.ho"
//#include "dev_acc_pub_types.h"
//#include "dev_acc_pub_api.h"

#include "vm_audio_api.h"
#endif // #if !defined(__SDK_SIMULATION__)

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

#ifndef __ONCHIP_FMRX_ENABLE__
#define SUP_SILAB4702
#define SUP_NXP5760
#define SUP_RDA5800
#define SUP_RDA5802

typedef enum
{
    CSL_FMR_SILAB4702,
    CSL_FMR_NXP5760,
    CSL_FMR_RDA5800,
#ifdef  __ATV_DRV__

  #ifdef  __ATV_DRV_RDA5888E__
    CSL_FMR_RDA5888E,
  #endif
	 
  #ifdef  __ATV_DRV_NMI600__
    CSL_FMR_NMI600,
  #endif

  #ifdef  __ATV_DRV_TLG1120__
    CSL_FMR_TLG1120,
  #endif

#endif
    CSL_FMR_RDA5802,
    CSL_FMR_NUM_MAX
} csl_FmrVendorId_e;
#else //#ifndef __ONCHIP_FMRX_ENABLE__
typedef enum
{
    CSL_FMR_ONCHIP,
    CSL_FMR_NUM_MAX
} csl_FmrVendorId_e;

bool HalFMrxSetPower(u8 on);
bool HalFMrxTune(u32 freq);
bool HalFMrxSeek(u8 on, u8 direction);
bool HalFMrxSetMute(u8 mute);
bool HalFMrxSetStereo(u8 mute);
bool HalFMrxReadChanInfo(u32 *pFreq, u16 *pRssi, u8 *pStereo);
bool HalFMrxReadChipInfo(u32 *pVersion, u16 *pManufactrId, u16 *pChipId);
bool HalFMrxSetArea(csl_FmrArea_e area);

#endif //#ifndef __ONCHIP_FMRX_ENABLE__


#ifdef SUP_NXP5760
bool NXP5760_SetPower(u8 on);
bool NXP5760_Tune(u32 tuneFreq);
bool NXP5760_Seek(u8 on, u8 direction);
bool NXP5760_SetBand(u8 bl);
bool NXP5760_Mute(u8 mute);
bool NXP5760_StereoOn(u8 on);
bool NXP5760_ReadChanInfo(u32 *pFreq, u16 *pRssi, u8 *pStereo);
bool NXP5760_ReadChipInfo(u32 *pVersion, u16 *pManufactrId, u16 *pChipId);
#endif //SUP_NXP5760

#ifdef SUP_SILAB4702
bool SiLab4702_SetPower(u8 on);
bool SiLab4702_Tune2(u32 freq);
bool SiLab4702_Seek2(u8 on, u8 direction);
bool SiLab4702_SetMute(u8 mute);
bool SiLab4702_SetStereo(u8 mute);
bool SiLab4702_ReadChanInfo(u32 *pFreq, u16 *pRssi, u8 *pStereo);
bool SiLab4702_ReadChipInfo(u32 *pVersion, u16 *pManufactrId, u16 *pChipId);
#endif //#ifdef SUP_SILAB4702

#ifdef SUP_RDA5800
bool RDA5800_SetPower(u8 on);
bool RDA5800_Tune(u32 freq);
bool RDA5800_Seek(u8 on, u8 direction);
bool RDA5800_Mute(u8 mute);
bool RDA5800_ReadChanInfo(u32 *pFreq, u16 *pRssi, u8 *pStereo);
bool RDA5800_ReadChipInfo(u32 *pVersion, u16 *pManufactrId, u16 *pChipId);
#endif //#ifdef SUP_RDA5800

#ifdef SUP_RDA5802
bool RDA5802_SetPower(u8 on);
bool RDA5802_Tune(u32 freq);
bool RDA5802_Seek(u8 on, u8 direction);
bool RDA5802_Mute(u8 mute);
bool RDA5802_ReadChanInfo(u32 *pFreq, u16 *pRssi, u8 *pStereo);
bool RDA5802_ReadChipInfo(u32 *pVersion, u16 *pManufactrId, u16 *pChipId);
#endif //#ifdef SUP_RDA5802

#endif//#ifndef __FMRX_DEV_H__
