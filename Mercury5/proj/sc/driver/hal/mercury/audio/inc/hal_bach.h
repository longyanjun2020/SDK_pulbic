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
* @file    hal_bach.h
* @version
* @brief   Hal audio bach header file
*
*/

#ifndef __HAL_BACH_H__
#define __HAL_BACH_H__


//=============================================================================
// Include files
//=============================================================================
#include "hal_bach_reg.h"

//=============================================================================
// Extern definition
//=============================================================================

//=============================================================================
// Macro definition
//=============================================================================
#define BACH_RIU_BASE_ADDR        0x1f000000
#define BACH_REG_BANK_1           0x150200
#define BACH_REG_BANK_2           0x150300
#define BACH_REG_BANK_3           0x150400
#define BACH_REG_BANK_4           0x103400

#define MIU_WORD_BYTE_SIZE          (8)
#define BACH_ARM_CACHE_LINE_ALIGN   (32)

#define WRITE_BYTE(_reg, _val)      (*((volatile u8*)(_reg)))  = (u8)(_val)
#define WRITE_WORD(_reg, _val)      (*((volatile u16*)(_reg))) = (u16)(_val)
#define WRITE_LONG(_reg, _val)      (*((volatile u32*)(_reg))) = (u32)(_val)
#define READ_BYTE(_reg)             (*(volatile u8*)(_reg))
#define READ_WORD(_reg)             (*(volatile u16*)(_reg))
#define READ_LONG(_reg)             (*(volatile u32*)(_reg))


#define BACH_DPGA_GAIN_MAX_DB 30
#define BACH_DPGA_GAIN_MIN_DB -64   //actually -63.5 dB
#define BACH_DPGA_GAIN_MIN_IDX 0x7F

#define BACH_TRACE_AUDIO LEVEL_23

#define ERRMSG(fmt, args...) UartSendTrace("[HalAudio]: " fmt, ## args)
//=============================================================================
// Data type definition
//=============================================================================
/**
 *  @brief Audio DMA
 */
typedef enum
{
    BACH_DMA_WRITER1 = 0, /**< DMA writer 1 */
    BACH_DMA_READER1,     /**< DMA reader 1 */
    BACH_DMA_WRITER2,     /**< DMA writer 2 */
    BACH_DMA_READER2,     /**< DMA reader 2 */
    BACH_DMA_NUM,
    BACH_DMA_NULL = 0xff,

} BachDmaChannel_e;

typedef enum
{//
    BACH_DMA_INT_UNDERRUN = 0,
    BACH_DMA_INT_OVERRUN,
    BACH_DMA_INT_EMPTY,
    BACH_DMA_INT_FULL,
    BACH_DMA_INT_NUM

} BachDmaInterrupt_e;


typedef enum
{
    BACH_REG_BANK1,
    BACH_REG_BANK2,
    BACH_REG_BANK3,
    BACH_REG_BANK4
} BachRegBank_e;


//=============================================================================
// Variable definition
//=============================================================================


//=============================================================================
// Global function definition
//=============================================================================
void HalBachSetBank1BaseAddr(u32 addr);
void HalBachSetBank2BaseAddr(u32 addr);
void HalBachSetBank3BaseAddr(u32 addr);
void HalBachSetBank4BaseAddr(u32 addr);
void HalBachSetBankBaseAddr(u32 addr);

void HalBachWriteReg2Byte(u32 nAddr, u16 nValue);
void HalBachWriteRegByte(u32 nAddr, u8 nValue);
u16 HalBachReadReg2Byte(u32 nAddr);
u8 HalBachReadRegByte(u32 nAddr);

void HalBachWriteReg(BachRegBank_e nBank, u8 nAddr, u16 regMsk, u16 nValue);
u16 HalBachReadReg(BachRegBank_e nBank, u8 nAddr);

//
u16 HalBachGetMaskReg(BachRegBank_e nBank, u8 nAddr);

void HalBachDma1WriterCtrlInt(bool bFull, bool bOverrun, bool bUnderrun);
void HalBachDma1ReaderCtrlInt(bool bEmpty, bool bOverrun, bool bUnderrun);
void HalBachDma2WriterCtrlInt(bool bFull, bool bOverrun, bool bUnderrun);
void HalBachDma2ReaderCtrlInt(bool bEmpty, bool bOverrun, bool bUnderrun);

void HalBachDpgaCalGain(s8 s8Gain, u8 *pu8GainIdx);
void HalBachGetMmc1Gain(s8 *pnGainL, s8 *pnGainR);
void HalBachSetMmc1Gain(s8 nGainL, s8 nGainR);
void HalBachGetAdcGain(s8 *pnGainL, s8 *pnGainR);
void HalBachSetAdcGain(s8 nGainL, s8 nGainR);
void HalBachGetDec1Gain(s8 *pnGainL, s8 *pnGainR);
void HalBachSetDec1Gain(s8 nGainL, s8 nGainR);
void HalBachGetMmc2Gain(s8 *pnGainL, s8 *pnGainR);
void HalBachSetMmc2Gain(s8 nGainL, s8 nGainR);

#endif  // __HAL_BACH_H__