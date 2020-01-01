//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file   drvNJPD.h
/// @brief  NJPD Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_NJPD_H_
#define _DRV_NJPD_H_

#include "njpeg_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define NJPD_BIT(_bit_)                 (1 << (_bit_))
#define NJPD_BITMASK(_bits_)            (NJPD_BIT(((1)?_bits_)+1)-NJPD_BIT(((0)?_bits_)))
#define NJPD_OFFSET(x)                  ((x) << 1)

/*****************Config Flag*********************/

// Reg: BK_NJPD_GLOBAL_SETTING00 (0x00)
#define NJPD_Y_HSF1                     NJPD_BIT(0)
#define NJPD_Y_HSF2                     NJPD_BIT(1)
#define NJPD_Y_VSF2                     NJPD_BIT(2)
#define NJPD_UV                         NJPD_BIT(3)
#define NJPD_SWRST                      NJPD_BIT(4)
#define NJPD_RST_EN                     NJPD_BIT(5)
#define NJPD_ROI_EN                     NJPD_BIT(6)
#define NJPD_SUVQ                       NJPD_BIT(7)
#define NJPD_SUVH                       NJPD_BIT(8)
#define NJPD_YC_SWAP                    NJPD_BIT(10)
#define NJPD_UV_SWAP                    NJPD_BIT(11)

// Reg: BK_NJPD_GLOBAL_SETTING01 (0x01)
#define NJPD_DOWN_SCALE                 (NJPD_BIT(0) | NJPD_BIT(1))
#define NJPD_SVLD                       NJPD_BIT(6)
#define NJPD_UV_7BIT                    NJPD_BIT(8)
#define NJPD_UV_MSB                     NJPD_BIT(9)
#define NJPD_GTABLE_RST                 NJPD_BIT(10)
#define NJPD_HTABLE_RELOAD_EN           NJPD_BIT(11)
#define NJPD_GTABLE_RELOAD_EN           NJPD_BIT(12)
#define NJPD_QTABLE_RELOAD_EN           NJPD_BIT(13)

// Reg: BK_NJPD_GLOBAL_SETTING02 (0x02)
#define NJPD_PITCH_EN                   NJPD_BIT(0)
#define NJPD_TBC_MODE                   NJPD_BIT(1)
#define NJPD_VLD_DONE_BY_FFD9_EN        NJPD_BIT(2)
#define NJPD_STOP_BY_MINI_CODE_ERR      NJPD_BIT(3)
#define NJPD_STOP_BY_INVT_SCAN_ERR      NJPD_BIT(4)
#define NJPD_STOP_BY_RST_MARKER_ERR     NJPD_BIT(5)
#define NJPD_STOP_BY_RST_MARKER_IDX_ERR NJPD_BIT(6)
#define NJPD_STOP_BY_END_IMG_ERR        NJPD_BIT(7)
#define NJPD_STOP_ANY_ERR               (NJPD_STOP_BY_MINI_CODE_ERR | NJPD_STOP_BY_INVT_SCAN_ERR | NJPD_STOP_BY_RST_MARKER_ERR |\
                                        NJPD_STOP_BY_RST_MARKER_IDX_ERR | NJPD_STOP_BY_END_IMG_ERR)
#define NJPD_LITTLE_ENDIAN_WR           NJPD_BIT(8)
#define NJPD_REMOVE_0xFF00              NJPD_BIT(9)
#define NJPD_REMOVE_0xFFFF              NJPD_BIT(10)
#define NJPD_STOP_BY_HUFF_TABLE_ERR     NJPD_BIT(11)
#define NJPD_STOP_BY_HUFF_DATA_LOSS_ERR NJPD_BIT(12)
#define NJPD_BITSTREAM_LE               NJPD_BIT(13)
#define NJPD_TURN_OFF_ALL_SRAM          NJPD_BIT(15)

// Reg: BK_NJPD_WRITE_ONE_CLEAR (0x08)
#define NJPD_DECODE_ENABLE              NJPD_BIT(0)
#define NJPD_TABLE_LOADING_START        NJPD_BIT(1)
#define NJPD_MIU_PARK                   NJPD_BIT(2)
#define NJPD_MRC0_VALID                 NJPD_BIT(3)
#define NJPD_MRC1_VALID                 NJPD_BIT(4)
#define NJPD_MRC_LAST                   NJPD_BIT(5)
#define NJPD_TBC_EN                     NJPD_BIT(6)
#define NJPD_TBC_DONE_CLR               NJPD_BIT(7)
#define NJPD_CLEAR_CRC                  NJPD_BIT(8)
#define NJPD_HANDSHAKE_SW_WOC           NJPD_BIT(9)

// Reg: BK_NJPD_MIU_READ_STATUS (0x0e)
#define NJPD_MIU_MRC0_STATUS            NJPD_BIT(0)
#define NJPD_MIU_MRC1_STATUS            NJPD_BIT(1)
#define NJPD_MIU_HTABLE_RDY             NJPD_BIT(2)
#define NJPD_MIU_GTABLE_RDY             NJPD_BIT(3)
#define NJPD_MIU_QTABLE_RDY             NJPD_BIT(4)

// Reg: BK_NJPD_MIU_HTABLE_SIZE (0x26)
#define NJPD_HTABLE_SIZE_MASK           (0x00FF)

// Reg: BK_NJPD1_IBUF_READ_LENGTH (0x28)
#define NJPD_MIU_SEL_SHIFT              10
#define NJPD_MIU_SEL_1_SHIFT            11
#define NJPD_MIU_SEL                    NJPD_BIT(NJPD_MIU_SEL_SHIFT)        // this reg only supported in edison/einstein/eiffel
#define NJPD_MIU_SEL_1                  NJPD_BIT(NJPD_MIU_SEL_1_SHIFT)      // this reg only supported in einstein3

// Reg: BK_NJPD_IRQ_CLEAR (0x29)
//[0] Decode done event flag
//[1] Mini-code error event flag
//[2] Inverse scan error event flag
//[3] Restart marker error event flag
//[4] Restart marker index disorder error event flag
//[5] End image error event flag
//[6] Read buffer0 empty event flag
//[7] Read buffer1 empty event flag
//[8] MIU write protect event flag
//[9] Data lose error event flag
//[10] iBuf table load done flag
//[11] Huffman table error

#define NJPD_EVENT_DECODE_DONE          NJPD_BIT(0)
#define NJPD_EVENT_MINICODE_ERR         NJPD_BIT(1)
#define NJPD_EVENT_INV_SCAN_ERR         NJPD_BIT(2)
#define NJPD_EVENT_RES_MARKER_ERR       NJPD_BIT(3)
#define NJPD_EVENT_RMID_ERR             NJPD_BIT(4)
#define NJPD_EVENT_END_IMAGE_ERR        NJPD_BIT(5)
#define NJPD_EVENT_MRC0_EMPTY           NJPD_BIT(6)
#define NJPD_EVENT_MRC1_EMPTY           NJPD_BIT(7)
#define NJPD_EVENT_WRITE_PROTECT        NJPD_BIT(8)
#define NJPD_EVENT_DATA_LOSS_ERR        NJPD_BIT(9)
#define NJPD_EVENT_IBUF_LOAD_DONE       NJPD_BIT(10)
#define NJPD_EVENT_HUFF_TABLE_ERR       NJPD_BIT(11)
#define NJPD_EVENT_ALL                  (NJPD_EVENT_DECODE_DONE | NJPD_EVENT_MINICODE_ERR | \
                                        NJPD_EVENT_INV_SCAN_ERR | NJPD_EVENT_RES_MARKER_ERR | NJPD_EVENT_RMID_ERR |     \
                                        NJPD_EVENT_END_IMAGE_ERR | NJPD_EVENT_MRC0_EMPTY | NJPD_EVENT_MRC1_EMPTY |      \
                                        NJPD_EVENT_WRITE_PROTECT | NJPD_EVENT_DATA_LOSS_ERR |                           \
                                        NJPD_EVENT_IBUF_LOAD_DONE | NJPD_EVENT_HUFF_TABLE_ERR)

#define NJPD_EVENT_ERROR                (NJPD_EVENT_MINICODE_ERR | NJPD_EVENT_INV_SCAN_ERR | \
                                        NJPD_EVENT_RES_MARKER_ERR | NJPD_EVENT_RMID_ERR |     \
                                        NJPD_EVENT_DATA_LOSS_ERR | NJPD_EVENT_HUFF_TABLE_ERR)

// Reg: BK_NJPD_TBC (0x40)
#define NJPD_JPD_TBC_RW                 NJPD_BIT(0)
#define NJPD_JPD_TBC_SEL                (NJPD_BIT(1) | NJPD_BIT(2))
#define NJPD_JPD_TBC_TABLE_READ         NJPD_BIT(4)
#define NJPD_JPD_TBC_ADR                (NJPD_BIT(8) | NJPD_BIT(9) | NJPD_BIT(10) | NJPD_BIT(11) | NJPD_BIT(12) | NJPD_BIT(13) | NJPD_BIT(14) | NJPD_BIT(15))

// Reg: BK_NJPD2_MARB_SETTING_06 (0x56)
#define NJPD_JPD_MARB_MRPRIORITY_SW     (NJPD_BIT(0) | NJPD_BIT(1))

// Reg: BK_NJPD2_MARB_SETTING_07 (0x57)
#define NJPD_JPD_MARB_BURST_SPLIT       (NJPD_BIT(12) | NJPD_BIT(13))

// Reg: BK_NJPD_MARB_LBOUND_0_H (0x5b)
#define NJPD_MARB_MIU_BOUND_EN_0        NJPD_BIT(13)

// Reg: BK_NJPD_TOP_MARB_PORT_ENABLE (0x76)
#define NJPD_TOP_MARB_P0_ENABLE             NJPD_BIT(0)
#define NJPD_TOP_MARB_P1_ENABLE             NJPD_BIT(1)
#define NJPD_TOP_MARB_P2_ENABLE             NJPD_BIT(2)
#define NJPD_TOP_MARB_P0_W_BYPASS_ENABLE    NJPD_BIT(4)
#define NJPD_TOP_MARB_P1_W_BYPASS_ENABLE    NJPD_BIT(5)
#define NJPD_TOP_MARB_P2_W_BYPASS_ENABLE    NJPD_BIT(6)
#define NJPD_TOP_MARB_P0_R_BYPASS_ENABLE    NJPD_BIT(7)
#define NJPD_TOP_MARB_P1_R_BYPASS_ENABLE    NJPD_BIT(0)     // second byte
#define NJPD_TOP_MARB_P2_R_BYPASS_ENABLE    NJPD_BIT(1)     // second byte

//-------------------------------------------------------------------------------------------------
// Enumeration
//-------------------------------------------------------------------------------------------------

// Map to the interrupt register
typedef enum
{
    E_NJPD_EVENT_DEC_NONE       = 0x0000,
    E_NJPD_EVENT_DEC_DONE       = 0x0001,
    E_NJPD_EVENT_MINICODE_ERR   = 0x0002,
    E_NJPD_EVENT_INV_SCAN_ERR   = 0x0004,
    E_NJPD_EVENT_RES_MARKER_ERR = 0x0008,
    E_NJPD_EVENT_RMID_ERR       = 0x0010,
    E_NJPD_EVENT_END_IMAGE_ERR  = 0x0020,
    E_NJPD_EVENT_MRC0_EMPTY     = 0x0040,
    E_NJPD_EVENT_MRC1_EMPTY     = 0x0080,
    E_NJPD_EVENT_WRITE_PROTECT  = 0x0100,
    E_NJPD_EVENT_DATA_LOSS_ERR  = 0x0200,
    E_NJPD_EVENT_IBUF_LOAD_DONE = 0x0400,
    E_NJPD_EVENT_HUFF_TABLE_ERR = 0x0800,
    E_NJPD_EVENT_MASK           = 0x0FFF
} NJPD_Event;

typedef enum
{
    E_NJPD_ISR_ID_DEC_DONE       = 0,
    E_NJPD_ISR_ID_DEC_ERR,
    E_NJPD_ISR_ID_DEC_MRC0_EMPTY,
    E_NJPD_ISR_ID_DEC_MRC1_EMPTY,
    E_NJPD_ISR_ID_DEC_WRITE_PROTECT,
    E_NJPD_ISR_ID_NUM
} NJPD_ISR_Handle_Id;

typedef enum
{
    E_NJPD_OUTPUT_ORIGINAL  = 0x00,
    E_NJPD_OUTPUT_YC_SWAP   = 0x01,
    E_NJPD_OUTPUT_UV_SWAP   = 0x02,
    E_NJPD_OUTPUT_UV_7BIT   = 0x03,
    E_NJPD_OUTPUT_UV_MSB    = 0x04
} NJPD_OutputFormat;

typedef enum
{
    E_NJPD_DOWNSCALE_ORG     = 0x00,
    E_NJPD_DOWNSCALE_HALF    = 0x01,
    E_NJPD_DOWNSCALE_FOURTH  = 0x02,
    E_NJPD_DOWNSCALE_EIGHTH  = 0x03
} NJPD_DownScale;

typedef enum
{
    E_NJPD_NJPD1 = 0,
    E_NJPD_NJPD2,
    E_NJPD_NJPD_TOTAL
} NJPD_Number;

//-------------------------------------------------------------------------------------------------
// Structure
//-------------------------------------------------------------------------------------------------

// NJPD Interrupt Register Function
typedef void (NJPD_IsrFuncCb)(int);

// Structure for buffer
typedef struct
{
    MS_PHY  u32ThumbnailBufAddr;     // Thumbnail buffer address (PA)
    MS_U32  u32ThumbnailBufSize;     // Thumbnail buffer size
    MS_U32  u32ThumbnailBufOffset;   // Access byte address offset in Thumbnail buffer relative to Thumbnail start address
    MS_PHY  u32MRCBufAddr;           // MRC buffer address (PA)
    MS_U32  u32MRCBufSize;           // MRC buffer size
    MS_U32  u32MRCBufOffset;         // MRC access byte address offset in MRC buffer relative to MRC start address
    MS_PHY  u32MWCBufAddr;           // MWC buffer address (PA)
    MS_U16  u16MWCBufLineNum;        // MWC Line number
    MS_BOOL bProgressive;
    MS_BOOL bThumbnailAccessMode;
} NJPD_BufCfg;

// Structure for Grpinf of Table
typedef struct
{
    MS_U8   *u8DcLumaValid;
    MS_U8   *u8DcLumaSymbol;
    MS_U16  *u16DcLumaCode;
    MS_U8   *u8DcChromaValid;
    MS_U8   *u8DcChromaSymbol;
    MS_U16  *u16DcChromaCode;
    MS_U8   *u8DcChroma2Valid;
    MS_U8   *u8DcChroma2Symbol;
    MS_U16  *u16DcChroma2Code;

    MS_U8   *u8AcLumaValid;
    MS_U8   *u8AcLumaSymbol;
    MS_U16  *u16AcLumaCode;
    MS_U8   *u8AcChromaValid;
    MS_U8   *u8AcChromaSymbol;
    MS_U16  *u16AcChromaCode;
    MS_U8   *u8AcChroma2Valid;
    MS_U8   *u8AcChroma2Symbol;
    MS_U16  *u16AcChroma2Code;

    MS_BOOL DHT;
    MS_BOOL bUVHuffman;
    MS_U8   u8DcLumaCnt;
    MS_U8   u8DcChromaCnt;
    MS_U8   u8DcChroma2Cnt;
    MS_U8   u8AcLumaCnt;
    MS_U8   u8AcChromaCnt;
    MS_U8   u8AcChroma2Cnt;
} NJPD_Grpinf;

// Structure for Symidx of Table
typedef struct
{
    MS_U8   *u8DcLumaHuffVal;
    MS_U8   *u8DcChromaHuffVal;
    MS_U8   *u8DcChroma2HuffVal;
    MS_U8   *u8AcLumaHuffVal;
    MS_U8   *u8AcChromaHuffVal;
    MS_U8   *u8AcChroma2HuffVal;
    MS_BOOL DHT;
    MS_BOOL bUVHuffman;
} NJPD_Symidx;

// Structure for Quantization Table
typedef struct
{
    MS_U16  s16Value[64];
    MS_BOOL bValid;
} NJPD_QuanTbl;

// Structure for IQtbl of Table
typedef struct
{
    MS_U8   *u8CompQuant;
    NJPD_QuanTbl *QuantTables;
    MS_U8   u8CompNum;
    MS_BOOL DQT;
} NJPD_IQTbl;

// Structure for NJPD capability
typedef struct
{
    MS_BOOL bBaseline;
    MS_BOOL bProgressive;
    MS_BOOL bMJPEG;
} NJPD_Cap;

// Structure for NJPD Information
typedef struct
{
    MS_U8*  pu8HalVer;
    MS_U8*  pu8FwVer;
    NJPD_Cap stCap;
} NJPD_Info;

// Structure for NJPD Status
typedef struct
{
    MS_U32  u32CurMRCAddr;
    MS_U16  u16CurRow;
    MS_U16  u16CurCol;
    MS_BOOL bIsBusy;
    MS_BOOL bIsrEnable;
} NJPD_Status;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

void MDrv_NJPD_Set_GlobalSetting00(MS_U16 u16Value);
MS_U16 MDrv_NJPD_Get_GlobalSetting00(void);

MS_BOOL MDrv_NJPD_InitBuf(NJPD_BufCfg in, MS_BOOL bMJPEG);
MS_U32 MDrv_NJPD_GetMWCStartAddr(void);
MS_U32 MDrv_NJPD_GetWritePtrAddr(void);
MS_U32 MDrv_NJPD_GetCurMRCAddr(void);
void MDrv_NJPD_SetMRC_Valid(MS_U16 u16Value);
void MDrv_NJPD_ReadLastBuffer(void);

MS_U16 MDrv_NJPD_GetEventFlag(void);
void MDrv_NJPD_SetEventFlag(MS_U16 u16Value);
void MDrv_NJPD_MaskEventFlag(MS_U16 u16Value);
void MDrv_NJPD_UnMaskEventFlag(MS_U16 u16Value);

MS_BOOL MDrv_NJPD_EnableISR(void);
MS_BOOL MDrv_NJPD_DisableISR(void);
void MDrv_NJPD_RegisterISRCallBackFunc(int ulEventId, void* pfCBFunc, int ulCBArg);

void MDrv_NJPD_PowerOn(void);
void MDrv_NJPD_PowerOff(void);
void MDrv_NJPD_EnablePowerSaving(void);

void MDrv_NJPD_SetAutoProtect(MS_BOOL enable);
void MDrv_NJPD_SetWPENEndAddr(MS_PHY u32ByteOffset);
void MDrv_NJPD_SetWPENStartAddr(MS_PHY u32ByteOffset);

void MDrv_NJPD_SetSpare(MS_U16 u16Value);
MS_U16 MDrv_NJPD_GetSpare(void);

void MDrv_NJPD_GTable_Rst(MS_BOOL bEnable);
void MDrv_NJPD_HTable_Reload_Enable(void);
void MDrv_NJPD_GTable_Reload_Enable(void);
void MDrv_NJPD_QTable_Reload_Enable(void);
void MDrv_NJPD_SetHTableStartAddr(MS_PHY u32ByteOffset);
void MDrv_NJPD_SetQTableStartAddr(MS_PHY u32ByteOffset);
void MDrv_NJPD_SetGTableStartAddr(MS_PHY u32ByteOffset);
void MDrv_NJPD_SetDifferentQTable(MS_BOOL bEnable);
void MDrv_NJPD_SetDifferentHTable(MS_BOOL bEnable);
void MDrv_NJPD_WriteGrpinf(NJPD_Grpinf in);
void MDrv_NJPD_WriteSymidx(NJPD_Symidx in);
void MDrv_NJPD_WriteIQTbl(NJPD_IQTbl in);
void MDrv_NJPD_TableLoadingStart(void);

void MDrv_NJPD_SetPicDimension(MS_U16 u16Width, MS_U16 u16Height);
void MDrv_NJPD_SetROI(MS_U16 start_x, MS_U16 start_y, MS_U16 width, MS_U16 height);
void MDrv_NJPD_SetRSTIntv(MS_U16 u16Value);
void MDrv_NJPD_GetInfo(NJPD_Info *pNJPD_Info);
NJPD_Status* MDrv_NJPD_GetStatus(void);
MS_U16 MDrv_NJPD_GetCurRow(void);
MS_U16 MDrv_NJPD_GetCurCol(void);
void MDrv_NJPD_Rst(void);
void MDrv_NJPD_DecodeEnable(void);
void MDrv_NJPD_SetScalingDownFactor(NJPD_DownScale eScalingFactor);
void MDrv_NJPD_SetSoftwareVLD(MS_BOOL bEnable);
void MDrv_NJPD_SetNJPDInstance(NJPD_Number JPDNum);

void MDrv_NJPD_SetVerificationMode(NJPD_VerificationMode VerificationMode);
NJPD_VerificationMode MDrv_NJPD_GetVerificationMode(void);
void MDrv_NJPD_DebugReg(void);
void MDrv_NJPD_Debug(void);

#ifdef __cplusplus
}
#endif

#endif // _DRV_NJPD_H_

