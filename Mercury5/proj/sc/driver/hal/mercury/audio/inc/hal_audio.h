////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (??MStar Confidential Information??) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    hal_audio.h
* @version
* @brief   Hal audio header file
*
*/

#ifndef __HAL_AUDIO_H__
#define __HAL_AUDIO_H__


//=============================================================================
// Include files
//=============================================================================
#include "hal_bach.h"
#include "hal_bach_reg.h"

//=============================================================================
// Extern definition
//=============================================================================

//=============================================================================
// Macro definition
//=============================================================================
/* DMA Channel State defines */
#define DMA_UNINIT          0
#define DMA_INIT            1
#define DMA_STOPPED         2
#define DMA_RUNNING         3


#define HAL_AUDIO_DMA1_WR_FULL      (1 << 0)
#define HAL_AUDIO_DMA1_RD_EMPTY     (1 << 1)
#define HAL_AUDIO_DMA1_RD_OVERRUN   (1 << 2)
#define HAL_AUDIO_DMA1_RD_UNDERRUN  (1 << 3)
#define HAL_AUDIO_DMA1_WR_OVERRUN   (1 << 4)
#define HAL_AUDIO_DMA1_WR_UNDERRUN  (1 << 5)
#define HAL_AUDIO_DMA2_WR_FULL      (1 << 6)
#define HAL_AUDIO_DMA2_RD_EMPTY     (1 << 7)
#define HAL_AUDIO_DMA2_RD_OVERRUN   (1 << 8)
#define HAL_AUDIO_DMA2_RD_UNDERRUN  (1 << 9)
#define HAL_AUDIO_DMA2_WR_OVERRUN   (1 << 10)
#define HAL_AUDIO_DMA2_WR_UNDERRUN  (1 << 11)

//=============================================================================
// Data type definition
//=============================================================================

/**
 * \brief Audio open type
 */
typedef enum
{
    HAL_AUDIO_RET_OK = 0,
    HAL_AUDIO_RET_NOT_SUPPORT,
    HAL_AUDIO_RET_PARAM_ERROR,
    HAL_AUDIO_RET_FAIL
} HalAudioRet_e;

/**
 *  @brief The enumeration defines the sampling rate
 */
typedef enum
{
    AUDIO_8_KHZ = 0,   /**< 8 kHz */
    AUDIO_11_025_KHZ,  /**< 11.025 kHz */
    AUDIO_12_KHZ,      /**< 12 kHz */
    AUDIO_16_KHZ,      /**< 16 kHz */
    AUDIO_22_050_KHZ,  /**< 22.05 kHz */
    AUDIO_24_KHZ,      /**< 24 kHz */
    AUDIO_32_KHZ,      /**< 32 kHz */
    AUDIO_44_1_KHZ,    /**< 44.1 kHz */
    AUDIO_48_KHZ,      /**< 48 kHz */
    AUDIO_64_KHZ,      /**< 64 kHz */
    AUDIO_96_KHZ,      /**< 96 kHz */
    AUDIO_MAX_FREQ
} AudioSamplingRate_e;

/**
 *  @brief The enumeration defines the chennal state
 */
typedef enum
{
    AUDIO_CHANNEL_CLOSED= 0, /**< channel is physically closed */
    AUDIO_CHANNEL_OPEN,      /**< channel is open (but may not be configured) */
} AudioChannelState_e;

/**
 *  @brief The enumeration defines ADC HPF
 */
typedef enum
{
    AUDIO_ADC_HPF1 = 0,
    AUDIO_ADC_HPF2,
} AudioAdcHpf_e;

/**
 *  @brief The enumeration defines DPGA sample step
 */
typedef enum
{
    AUDIO_DPGA_1_SAMPLE = 0,
    AUDIO_DPGA_2_SAMPLE,
    AUDIO_DPGA_4_SAMPLE,
    AUDIO_DPGA_8_SAMPLE,
    AUDIO_DPGA_16_SAMPLE,
    AUDIO_DPGA_32_SAMPLE,
    AUDIO_DPGA_64_SAMPLE,
    AUDIO_DPGA_SAMPLE_MAX
}AudioDpgaStep_e;


typedef enum
{
    BACH_RATE_SLAVE,
    BACH_RATE_8K,
    BACH_RATE_11K,
    BACH_RATE_12K,
    BACH_RATE_16K,
    BACH_RATE_22K,
    BACH_RATE_24K,
    BACH_RATE_32K,
    BACH_RATE_44K,
    BACH_RATE_48K,
    BACH_RATE_NUM,
    BACH_RATE_NULL = 0xff,
} BachRate_e;

typedef enum
{
    BACH_DPGA_MMC1,
    BACH_DPGA_ADC,
    BACH_DPGA_AEC1,
    BACH_DPGA_DEC1,
    BACH_DPGA_MMC2,
    BACH_DPGA_NUM,
    BACH_DPGA_NULL = 0xff,
} BachDpga_e;

typedef enum
{
    BACH_PATH_PLAYBACK,
    BACH_PATH_CAPTURE,
    BACH_PATH_PLAYBACK2,
    BACH_PATH_NUM
} BachPath_e;

typedef enum
{
    BACH_ATOP_LINEIN,
    BACH_ATOP_MIC,
    BACH_ATOP_LINEOUT,
    BACH_ATOP_NUM
} BachAtopPath_e;

typedef enum
{
    BACH_MUX2_MMC1,
    BACH_MUX2_DMAWR1,
    BACH_MUX2_NULL = 0xff
} BachMux2_e;

typedef enum
{
    BACH_I2STX_DMARD1,
    BACH_I2STX_DMAWR1,
    BACH_I2STX_SRC,
    BACH_I2STX_DMARD2,
    BACH_I2STX_NUM
} BachI2sTxMux_e;


typedef enum
{
    BACH_SINERATE_250,
    BACH_SINERATE_500,
    BACH_SINERATE_1000,
    BACH_SINERATE_1500,
    BACH_SINERATE_2K,
    BACH_SINERATE_3K,
    BACH_SINERATE_4K,
    BACH_SINERATE_6K,
    BACH_SINERATE_8K,
    BACH_SINERATE_12K,
    BACH_SINERATE_16K,
    BACH_SINERATE_NUM
} BachSineRate_e;

typedef struct
{
    u32 nDmaChannelState;

    // system things
    u32 nPhysDmaAddr;         // physical RAM address of the buffer
    u32 nBufferSize;          // lenght of contiguous physical RAM

    // internal things
    u32 nChannels;            // number of channels (1 or 2)
    u32 nSampleSize;          // sample word size
    u32 nSampleRate;          // sample rate in samples/second
    u32 nBytesPerInt;       // number of samples to play before interrupting

} DmaChannel_t;

typedef void (*PfnHalAudioDmaIrqCbFn)(void);

//=============================================================================
// Variable definition
//=============================================================================


//=============================================================================
// Global function definition
//=============================================================================

// DMA
HalAudioRet_e HalAudioDmaReset(void);
u32  HalAudioDmaGetLevelCnt(BachDmaChannel_e eDmaChannel);
bool HalAudioDmaMaskInt(BachDmaChannel_e eDmaChannel, BachDmaInterrupt_e eDmaInt, bool bMask);
void HalAudioDmaClearInt(BachDmaChannel_e eDmaChannel);
void HalAudioDmaReInit(BachDmaChannel_e eDmaChannel);
void HalAudioDmaEnable(BachDmaChannel_e eDmaChannel, bool bEnable);
void HalAudioDmaStartChannel(BachDmaChannel_e eDmaChannel);
void HalAudioDmaStopChannel(BachDmaChannel_e eDmaChannel);
void HalAudioDmaSetThreshold(BachDmaChannel_e eDmaChannel, u32 nOverrunTh, u32 nUnderrunTh);
void HalAudioDmaSetPhyAddr(BachDmaChannel_e eDmaChannel, u32 nBufAddr, u32 nBufSize);
void HalAudioDmaSetChMode(BachDmaChannel_e eDmaChannel, bool bMono);
bool HalAudioDmaSetRate(BachDmaChannel_e eDmaChannel, BachRate_e eRate);
u32 HalAudioDmaGetRate(BachDmaChannel_e eDmaChannel);

bool HalAudioDmaIsFull(BachDmaChannel_e eDmaChannel);
bool HalAudioDmaIsEmpty(BachDmaChannel_e eDmaChannel);
bool HalAudioDmaIsLocalEmpty(BachDmaChannel_e eDmaChannel);
bool HalAudioDmaIsUnderrun(BachDmaChannel_e eDmaChannel);
bool HalAudioDmaIsOverrun(BachDmaChannel_e eDmaChannel);
u32  HalAudioDmaTrigLevelCnt(BachDmaChannel_e eDmaChannel, u32 nDataSize);
bool HalAudioDmaIsWork(BachDmaChannel_e eDmaChannel);

void HalAudioDmaIntStatus(BachDmaChannel_e eDmaChannel, u16 *pnStatus);

//DIGMIC
bool HalAudioDigMicSetRate(BachRate_e eRate);
bool HalAudioDigMicEnable(bool bEn);

 //DPGA
void HalAudioDpgaCtrl(BachDpga_e eDpga, bool bEnable, bool bMute, bool bFade);
//void HalAudioDpgaCalGain(S8 s8Gain, U8 *pu8GainIdx);
s8 HalAudioDpgaGetGain(BachDpga_e eDpga);
void HalAudioDpgaSetGain(BachDpga_e eDpga, s8 s8Gain);
void HalAudioSetPathOnOff(BachPath_e ePath, bool bOn);
void HalAudioSetPathGain(BachPath_e ePath, s8 s8Gain);

//ATOP
void HalAudioAtopInit(void);
void HalAudioAtopEnableRef(bool bEnable);
void HalAudioAtopDac(bool bEnable);
void HalAudioAtopAdc(bool bEnable);
void HalAudioAtopMic(bool bEnable);
void HalAudioAtopLineIn(bool bEnable);
bool HalAudioOpenAtop(BachAtopPath_e ePath);
bool HalAudioCloseAtop(BachAtopPath_e ePath);
bool HalAudioAtopMicPreGain(u16 nLevel);
bool HalAudioAtopAdcGain(u16 nLevel, BachAtopPath_e eAtop);


//sinegen
bool HalAudioSineGenGain(u16 nGain);
bool HalAudioSineGenRate(u16 nRate);
void HalAudioSineGenEnable(bool bEnable);

//
void HalAudioSysInit(void);
void HalAudioSetMux2(BachMux2_e eMux, u8 u8Choice);

// I2S-Tx control
bool HalAudioSrcSetRate(BachRate_e eRate);
bool HalAudioI2sTxSetRate(BachRate_e eRate);
bool HalAudioI2sTxCtrl(BachI2sTxMux_e eMux, BachRate_e eRate);

// maybe remove to hal_bach.c ?
BachRate_e HalAudioRateFromU32(u32 nRate);
u32 HalAudioRateToU32(BachRate_e eRate);

HalAudioRet_e HalAudioDmaSetBufAddr(BachDmaChannel_e eDmaChannel, u8 *pnBufAddr, u32 nBufSize);
HalAudioRet_e HalAudioDmaCtrlInt(BachDmaChannel_e eDmaChannel, bool bFull, bool bOverrun, bool bUnderrun);

void HalAudioDmaPauseChannel(BachDmaChannel_e eDmaChannel);
void HalAudioDmaResumeChannel(BachDmaChannel_e eDmaChannel);

u32 HalAudioDma1WriteRdData(u8 *pData, u32 nDataSize);
u32 HalAudioDma2WriteRdData(u8 *pData, u32 nDataSize);
u32 HalAudioDma1ReadWrData(u8 *pData, u32 nDataSize);
u32 HalAudioDma2ReadWrData(u8 *pData, u32 nDataSize);

void HalAudioDpgaSetFadingStatus(BachDpga_e eDpga, bool bEnable);
void HalAudioDpgaSetMmc1Fading(bool bEnable);
void HalAudioDpgaSetAdcFading(bool bEnable);
void HalAudioDpgaSetDec1Fading(bool bEnable);
void HalAudioDpgaSetMmc2Fading(bool bEnable);

//isr
void HalAudioRegDmaIrqCB(PfnHalAudioDmaIrqCbFn pfnDmaIrqCb);
void HalAudioDmaIrq(void);
void HalAudioEnableDmaIrq(void);
void HalAudioDmaEventHandler(u16 *pnEvent);

#endif  // __HAL_AUDIO_H__