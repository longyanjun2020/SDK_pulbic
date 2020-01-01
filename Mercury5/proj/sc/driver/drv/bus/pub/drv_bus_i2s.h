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
 * @file drv_bus_i2s.h
 * @brief CPU I2s low-level driver
 */

#ifndef __DRV_BUS_I2S_H__
#define __DRV_BUS_I2S_H__

#include "vm_types.ht"
#include "msgofs.hc"
#include "mdl_aud_forward.h"

typedef struct
{
    u32 nMaxSize; ///< max block size
    u8 nMailbox; ///< mailbox in which Fifo messages will be sent
    bool bStereoData; ///< if TRUE, data will be read as 32 bits, otherwise as 16 bits
    bool bLeftChannel; ///< if mono data, the 16 bits data can be set in Left or rigth channel
    bool bDmaMode; ///< flag to enable or disable DMA mode
} I2sParam_t;

/* Error codes */
#define I2S_OK                  1
#define I2S_DTMF_START_FAIL     -6
#define I2S_NOT_ENOUGH_MEMORY   -5
#define I2S_BAD_PARAM           -4
#define I2S_BAD_SESSION         -3
#define I2S_FIFO_FULL           -1

/**
 * @brief Maximum number of I2s buffers
 */
#define I2S_NB_MAX_BUFFERS  10

/**
 * @brief Maximum level for DTMF tones
 */
#define I2S_DTMF_MAX_LEVEL  0x7FF

/**
 * @brief Maximum frequency for DTMF tones
 */
#define I2S_DTMF_MAX_FREQ   7999

/**
 * @brief Maximum duration for DTMF tones
 */
#define I2S_DTMF_MAX_DURATION   (0x3FF/8)

void DrvI2sPcmDmaStartCpuListen(void);
void DrvI2sPcmDmaStop(void);
void DrvI2sPcmDmaStart(void);
void DrvI2sVoiceInit(vm_AudioIF_e itf, bool cpu);
void DrvI2sVoiceClose(void);
void DrvI2sVoiceSetMux(bool cpu);
void DrvI2sHandler(void);
s32 DrvI2sOpen(I2sParam_t *param);
s32 DrvI2sStart(s32 session);
s32 DrvI2sPause(s32 session);
s32 DrvI2sResume(s32 session);
s32 DrvI2sStop(s32 session);
s32 DrvI2sAddData(s32 session, u32* new_data, u32 nb_data, bool last_data);
bool DrvI2sIsFifoFull(s32 session);
s32 DrvI2sClose(s32 session);

s32 DrvI2sStartDtmf(u16 Freq1, u16 Level1, u16 Freq2, u16 Level2, u16 duration_ms);
s32 DrvI2sStopDtmf(void);

#endif //__DRV_BUS_I2S_H__
