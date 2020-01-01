////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    drv_audio_pub_api.h
* @version
* @brief   Driver audio header file
*
*/

#ifndef __DRV_AUDIO_PUB_API_H__
#define __DRV_AUDIO_PUB_API_H__


//=============================================================================
// Include files
//=============================================================================
#include "drv_audio_pub_types.h"

//=============================================================================
// Extern definition
//=============================================================================

//=============================================================================
// Macro definition
//=============================================================================

//=============================================================================
// Data type definition
//=============================================================================
/**
 * \brief Audio DMA callback
 */
 typedef void (*PfnDrvAudioDmaIrqCbFn)(void);


//=============================================================================
// Variable definition
//=============================================================================

//=============================================================================
// Global function definition
//=============================================================================
DrvAudioRet_e DrvAudioDmaReset(void);
DrvAudioRet_e DrvAudioDmaSetBufAddr(BachDmaChannel_e eDmaChannel, u8 *pnBufAddr, u32 nBufSize);
DrvAudioRet_e DrvAudioDmaSetThreshold(BachDmaChannel_e eDmaChannel, u32 nOverrun, u32 nUnderrun);
DrvAudioRet_e DrvAudioDmaSetSamplingRate(BachDmaChannel_e eDmaChannel, u32 nSamplingRate);
DrvAudioRet_e DrvAudioDmaGetBufInfo(BachDmaChannel_e eDmaChannel, u32 *pnDataSize, bool *pbOverrun, bool *pbUnderrun);
DrvAudioRet_e DrvAudioDmaClrEmptyFlag(BachDmaChannel_e eDmaChannel);
DrvAudioRet_e DrvAudioDmaCtrlInt(BachDmaChannel_e eDmaChannel, bool bFullEmpty, bool bOverrun, bool bUnderrun);
DrvAudioRet_e DrvAudioDmaRecReadData(BachDmaChannel_e eDmaChannel, u8 *pnDestAddr, u32 nDataSize, u32 *pnActualSize);
DrvAudioRet_e DrvAudioDmaStart(BachDmaChannel_e eDmaChannel);
DrvAudioRet_e DrvAudioDmaStop(BachDmaChannel_e eDmaChannel);
DrvAudioRet_e DrvAudioDmaPause(BachDmaChannel_e eDmaChannel);
DrvAudioRet_e DrvAudioDmaResume(BachDmaChannel_e eDmaChannel);
DrvAudioRet_e DrvAudioDmaPlayWriteData(BachDmaChannel_e eDmaChannel, u8 *pnSrcAddr, u32 nDataSize, u32 *pnActualSize);
//DrvAudioRet_e DrvAudioDmaPlayPowerSavingPause(void);
//DrvAudioRet_e DrvAudioDmaPlayPowerSavingResume(void);
//bool DrvAudioDmaIsActive(void);
//bool DrvAudioDmaIsPlaying(void);

DrvAudioRet_e DrvAudioDpgaSetFadeOut(BachDpga_e eDpga);
DrvAudioRet_e DrvAudioDpgaSetFadeIn(BachDpga_e eDpga);
DrvAudioRet_e DrvAudioDpgaCtrl(BachDpga_e eDpga, bool bEnable, bool bMute, bool bFade);

//DIGMIC
DrvAudioRet_e DrvAudioDigMicSetRate(u32 nSamplingRate);
DrvAudioRet_e DrvAudioDigMicEnable(bool bEn);

//Related of ATOP
DrvAudioRet_e DrvAudioOpenAtop(BachAtopPath_e ePath);
DrvAudioRet_e DrvAudioCloseAtop(BachAtopPath_e ePath);

DrvAudioRet_e DrvAudioAtopMicPreGain(u16 nLevel);
DrvAudioRet_e DrvAudioAtopAdcGain(u16 nLevel, BachAtopPath_e eAtop);


DrvAudioRet_e DrvAudioSysInit(void);

//
DrvAudioRet_e DrvAudioSetPathOnOff(BachPath_e ePath, bool bOn);
DrvAudioRet_e DrvAudioSetPathGain(BachPath_e ePath, s8 s8Gain);

// I2S-Tx
DrvAudioRet_e DrvAudioI2sTxCtrl(BachI2sTxMux_e eMux, u32 nSamplingRate);

//ISR
void DrvAudioDmaIrqCB(void);
DrvAudioRet_e DrvAudioRegDmaIrqCB(PfnDrvAudioDmaIrqCbFn pfnDmaIrqCb);
DrvAudioRet_e DrvAudioDmaEventHandler(u16 *pnEvent);
DrvAudioRet_e DrvAudioEnableDmaIrq(void);

#endif //__DRV_AUDIO_PUB_API_H__

