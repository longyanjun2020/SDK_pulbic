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
// Copyright (c) 2008-2011 MStar Semiconductor, Inc.
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
/// file    regNJPD.h
/// @brief  NJPD Register Table
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _REG_NJPD_H_
#define _REG_NJPD_H_

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

#define NJPD_MEM_SCWGIF_BASE        0x0000
#define NJPD_MEM_SYMIDX_BASE        0x0400
#define NJPD_MEM_QTBL_BASE          0x0800
#define NJPD_MEM_TBL_TOTAL_SIZE     0x1000

#define NJPD_CLKGEN2_BASE           0x03800
#define NJPD1_REG_BASE              0x63000
#define NJPD2_REG_BASE              0x63100 // NOT USED

// NJPD1 register=======================================================================

// Global Setting
#define BK_NJPD1_GLOBAL_SETTING00                    (NJPD1_REG_BASE+NJPD_OFFSET(0x00))
#define BK_NJPD1_GLOBAL_SETTING01                    (NJPD1_REG_BASE+NJPD_OFFSET(0x01))
#define BK_NJPD1_GLOBAL_SETTING02                    (NJPD1_REG_BASE+NJPD_OFFSET(0x02))

// Pitch Width
#define BK_NJPD1_PITCH_WIDTH                         (NJPD1_REG_BASE+NJPD_OFFSET(0x03))

// Restart Interval
#define BK_NJPD1_RESTART_INTERVAL                    (NJPD1_REG_BASE+NJPD_OFFSET(0x05))

// Image Size
#define BK_NJPD1_IMG_HSIZE                           (NJPD1_REG_BASE+NJPD_OFFSET(0x06))
#define BK_NJPD1_IMG_VSIZE                           (NJPD1_REG_BASE+NJPD_OFFSET(0x07))

// Write-one-clear
#define BK_NJPD1_WRITE_ONE_CLEAR                     (NJPD1_REG_BASE+NJPD_OFFSET(0x08))

// Region of Interest
#define BK_NJPD1_ROI_H_START                         (NJPD1_REG_BASE+NJPD_OFFSET(0x09))
#define BK_NJPD1_ROI_V_START                         (NJPD1_REG_BASE+NJPD_OFFSET(0x0a))
#define BK_NJPD1_ROI_H_SIZE                          (NJPD1_REG_BASE+NJPD_OFFSET(0x0b))
#define BK_NJPD1_ROI_V_SIZE                          (NJPD1_REG_BASE+NJPD_OFFSET(0x0c))

// Gated-Clock Control
#define BK_NJPD1_GATED_CLOCK_CTRL                    (NJPD1_REG_BASE+NJPD_OFFSET(0x0d))

// Miu Interface
#define BK_NJPD1_MIU_READ_STATUS                     (NJPD1_REG_BASE+NJPD_OFFSET(0x0e))
#define BK_NJPD1_MIU_IBUFFER_CNT                     (NJPD1_REG_BASE+NJPD_OFFSET(0x0f))
#define BK_NJPD1_MIU_READ_START_ADDR_L               (NJPD1_REG_BASE+NJPD_OFFSET(0x10))
#define BK_NJPD1_MIU_READ_START_ADDR_H               (NJPD1_REG_BASE+NJPD_OFFSET(0x11))
#define BK_NJPD1_MIU_READ_BUFFER0_START_ADDR_L       (NJPD1_REG_BASE+NJPD_OFFSET(0x12))
#define BK_NJPD1_MIU_READ_BUFFER0_START_ADDR_H       (NJPD1_REG_BASE+NJPD_OFFSET(0x13))
#define BK_NJPD1_MIU_READ_BUFFER0_END_ADDR_L         (NJPD1_REG_BASE+NJPD_OFFSET(0x14))
#define BK_NJPD1_MIU_READ_BUFFER0_END_ADDR_H         (NJPD1_REG_BASE+NJPD_OFFSET(0x15))
#define BK_NJPD1_MIU_READ_BUFFER1_START_ADDR_L       (NJPD1_REG_BASE+NJPD_OFFSET(0x16))
#define BK_NJPD1_MIU_READ_BUFFER1_START_ADDR_H       (NJPD1_REG_BASE+NJPD_OFFSET(0x17))
#define BK_NJPD1_MIU_READ_BUFFER1_END_ADDR_L         (NJPD1_REG_BASE+NJPD_OFFSET(0x18))
#define BK_NJPD1_MIU_READ_BUFFER1_END_ADDR_H         (NJPD1_REG_BASE+NJPD_OFFSET(0x19))
#define BK_NJPD1_MIU_WRITE_START_ADDR_L              (NJPD1_REG_BASE+NJPD_OFFSET(0x1a))
#define BK_NJPD1_MIU_WRITE_START_ADDR_H              (NJPD1_REG_BASE+NJPD_OFFSET(0x1b))
#define BK_NJPD1_MIU_WRITE_POINTER_ADDR_L            (NJPD1_REG_BASE+NJPD_OFFSET(0x1c))
#define BK_NJPD1_MIU_WRITE_POINTER_ADDR_H            (NJPD1_REG_BASE+NJPD_OFFSET(0x1d))
#define BK_NJPD1_MIU_READ_POINTER_ADDR_L             (NJPD1_REG_BASE+NJPD_OFFSET(0x1e))
#define BK_NJPD1_MIU_READ_POINTER_ADDR_H             (NJPD1_REG_BASE+NJPD_OFFSET(0x1f))
#define BK_NJPD1_MIU_HTABLE_START_ADDR_L             (NJPD1_REG_BASE+NJPD_OFFSET(0x20))
#define BK_NJPD1_MIU_HTABLE_START_ADDR_H             (NJPD1_REG_BASE+NJPD_OFFSET(0x21))
#define BK_NJPD1_MIU_GTABLE_START_ADDR_L             (NJPD1_REG_BASE+NJPD_OFFSET(0x22))
#define BK_NJPD1_MIU_GTABLE_START_ADDR_H             (NJPD1_REG_BASE+NJPD_OFFSET(0x23))
#define BK_NJPD1_MIU_QTABLE_START_ADDR_L             (NJPD1_REG_BASE+NJPD_OFFSET(0x24))
#define BK_NJPD1_MIU_QTABLE_START_ADDR_H             (NJPD1_REG_BASE+NJPD_OFFSET(0x25))
#define BK_NJPD1_MIU_HTABLE_SIZE                     (NJPD1_REG_BASE+NJPD_OFFSET(0x26))
#define BK_NJPD1_SET_CHROMA_VALUE                    (NJPD1_REG_BASE+NJPD_OFFSET(0x27))
#define BK_NJPD1_IBUF_READ_LENGTH                    (NJPD1_REG_BASE+NJPD_OFFSET(0x28))

// Interrupt
#define BK_NJPD1_IRQ_CLEAR                           (NJPD1_REG_BASE+NJPD_OFFSET(0x29))
#define BK_NJPD1_IRQ_FORCE                           (NJPD1_REG_BASE+NJPD_OFFSET(0x2a))
#define BK_NJPD1_IRQ_MASK                            (NJPD1_REG_BASE+NJPD_OFFSET(0x2b))
#define BK_NJPD1_IRQ_FINAL_S                         (NJPD1_REG_BASE+NJPD_OFFSET(0x2c))
#define BK_NJPD1_IRQ_RAW_S                           (NJPD1_REG_BASE+NJPD_OFFSET(0x2d))

// Sram Gated-Clock Control
#define BK_NJPD1_MIU_TLB                             (NJPD1_REG_BASE+NJPD_OFFSET(0x2f)+1)

// Debug
#define BK_NJPD1_ROW_IDEX                            (NJPD1_REG_BASE+NJPD_OFFSET(0x30))
#define BK_NJPD1_COLUMN_IDEX                         (NJPD1_REG_BASE+NJPD_OFFSET(0x31))
#define BK_NJPD1_DEBUG_BUS_SELECT                    (NJPD1_REG_BASE+NJPD_OFFSET(0x32))
#define BK_NJPD1_DEBUG_BUS_H                         (NJPD1_REG_BASE+NJPD_OFFSET(0x33))
#define BK_NJPD1_DEBUG_BUS_L                         (NJPD1_REG_BASE+NJPD_OFFSET(0x34))
#define BK_NJPD1_IBUF_BYTE_COUNT_L                   (NJPD1_REG_BASE+NJPD_OFFSET(0x35))
#define BK_NJPD1_IBUF_BYTE_COUNT_H                   (NJPD1_REG_BASE+NJPD_OFFSET(0x36))
#define BK_NJPD1_VLD_BYTE_COUNT_L                    (NJPD1_REG_BASE+NJPD_OFFSET(0x37))
#define BK_NJPD1_VLD_BYTE_COUNT_H                    (NJPD1_REG_BASE+NJPD_OFFSET(0x38))
#define BK_NJPD1_VLD_DECODING_DATA_L                 (NJPD1_REG_BASE+NJPD_OFFSET(0x39))
#define BK_NJPD1_VLD_DECODING_DATA_H                 (NJPD1_REG_BASE+NJPD_OFFSET(0x3a))
#define BK_NJPD1_DEBUG_TRIG_CYCLE                    (NJPD1_REG_BASE+NJPD_OFFSET(0x3b))
#define BK_NJPD1_DEBUG_TRIG_MBX                      (NJPD1_REG_BASE+NJPD_OFFSET(0x3c))
#define BK_NJPD1_DEBUG_TRIG_MBY                      (NJPD1_REG_BASE+NJPD_OFFSET(0x3d))
#define BK_NJPD1_DEBUG_TRIGGER                       (NJPD1_REG_BASE+NJPD_OFFSET(0x3e))

// BIST
#define BK_NJPD1_BIST_FAIL                           (NJPD1_REG_BASE+NJPD_OFFSET(0x3f))

// TBC RIU Interface
#define BK_NJPD1_TBC                                 (NJPD1_REG_BASE+NJPD_OFFSET(0x40))
#define BK_NJPD1_TBC_WDATA0                          (NJPD1_REG_BASE+NJPD_OFFSET(0x41))
#define BK_NJPD1_TBC_WDATA1                          (NJPD1_REG_BASE+NJPD_OFFSET(0x42))
#define BK_NJPD1_TBC_RDATA_L                         (NJPD1_REG_BASE+NJPD_OFFSET(0x43))
#define BK_NJPD1_TBC_RDATA_H                         (NJPD1_REG_BASE+NJPD_OFFSET(0x44))

// Max Huffman Table Address
#define BK_NJPD1_Y_MAX_HUFFTABLE_ADDRESS             (NJPD1_REG_BASE+NJPD_OFFSET(0x45))
#define BK_NJPD1_CB_MAX_HUFFTABLE_ADDRESS            (NJPD1_REG_BASE+NJPD_OFFSET(0x46))
#define BK_NJPD1_CR_MAX_HUFFTABLE_ADDRESS            (NJPD1_REG_BASE+NJPD_OFFSET(0x47))

// Spare
#define BK_NJPD1_SPARE00                             (NJPD1_REG_BASE+NJPD_OFFSET(0x48))
#define BK_NJPD1_SPARE01                             (NJPD1_REG_BASE+NJPD_OFFSET(0x49))
#define BK_NJPD1_SPARE02                             (NJPD1_REG_BASE+NJPD_OFFSET(0x4a))
#define BK_NJPD1_SPARE03                             (NJPD1_REG_BASE+NJPD_OFFSET(0x4b))
#define BK_NJPD1_SPARE04                             (NJPD1_REG_BASE+NJPD_OFFSET(0x4c))
#define BK_NJPD1_SPARE05                             (NJPD1_REG_BASE+NJPD_OFFSET(0x4d))
#define BK_NJPD1_SPARE06                             (NJPD1_REG_BASE+NJPD_OFFSET(0x4e))
#define BK_NJPD1_SPARE07                             (NJPD1_REG_BASE+NJPD_OFFSET(0x4f))

#define BK_NJPD1_MARB_SETTING_00                     (NJPD1_REG_BASE+NJPD_OFFSET(0x50))
#define BK_NJPD1_MARB_SETTING_01                     (NJPD1_REG_BASE+NJPD_OFFSET(0x51))
#define BK_NJPD1_MARB_SETTING_02                     (NJPD1_REG_BASE+NJPD_OFFSET(0x52))
#define BK_NJPD1_MARB_SETTING_03                     (NJPD1_REG_BASE+NJPD_OFFSET(0x53))
#define BK_NJPD1_MARB_SETTING_04                     (NJPD1_REG_BASE+NJPD_OFFSET(0x54))
#define BK_NJPD1_MARB_SETTING_05                     (NJPD1_REG_BASE+NJPD_OFFSET(0x55))
#define BK_NJPD1_MARB_SETTING_06                     (NJPD1_REG_BASE+NJPD_OFFSET(0x56))
#define BK_NJPD1_MARB_SETTING_07                     (NJPD1_REG_BASE+NJPD_OFFSET(0x57))

#define BK_NJPD1_MARB_UBOUND_0_L                     (NJPD1_REG_BASE+NJPD_OFFSET(0x58))
#define BK_NJPD1_MARB_UBOUND_0_H                     (NJPD1_REG_BASE+NJPD_OFFSET(0x59))
#define BK_NJPD1_MARB_LBOUND_0_L                     (NJPD1_REG_BASE+NJPD_OFFSET(0x5a))
#define BK_NJPD1_MARB_LBOUND_0_H                     (NJPD1_REG_BASE+NJPD_OFFSET(0x5b))

#define BK_NJPD1_CRC_MODE                            (NJPD1_REG_BASE+NJPD_OFFSET(0x6d))

// Miu Arbiter
#define BK_NJPD1_MARB_CRC_RESULT_0                   (NJPD1_REG_BASE+NJPD_OFFSET(0x70))
#define BK_NJPD1_MARB_CRC_RESULT_1                   (NJPD1_REG_BASE+NJPD_OFFSET(0x71))
#define BK_NJPD1_MARB_CRC_RESULT_2                   (NJPD1_REG_BASE+NJPD_OFFSET(0x72))
#define BK_NJPD1_MARB_CRC_RESULT_3                   (NJPD1_REG_BASE+NJPD_OFFSET(0x73))
#define BK_NJPD1_MARB_RESET                          (NJPD1_REG_BASE+NJPD_OFFSET(0x74))
#define BK_NJPD1_HANDSHAKE_CNT                       (NJPD1_REG_BASE+NJPD_OFFSET(0x74)+1)
#define BK_NJPD1_SW_MB_ROW_CNT                       (NJPD1_REG_BASE+NJPD_OFFSET(0x75))
#define BK_NJPD1_HANDSHAKE                           (NJPD1_REG_BASE+NJPD_OFFSET(0x75)+1)
#define BK_NJPD1_TOP_MARB_PORT_ENABLE                (NJPD1_REG_BASE+NJPD_OFFSET(0x76))

#define BK_NJPD1_GENERAL(x)                          (NJPD1_REG_BASE+NJPD_OFFSET(x))

// NJPD2 register=======================================================================

// Global Setting
#define BK_NJPD2_GLOBAL_SETTING00                    (NJPD2_REG_BASE+NJPD_OFFSET(0x00))
#define BK_NJPD2_GLOBAL_SETTING01                    (NJPD2_REG_BASE+NJPD_OFFSET(0x01))
#define BK_NJPD2_GLOBAL_SETTING02                    (NJPD2_REG_BASE+NJPD_OFFSET(0x02))

// Pitch Width
#define BK_NJPD2_PITCH_WIDTH                         (NJPD2_REG_BASE+NJPD_OFFSET(0x03))

// Restart Interval
#define BK_NJPD2_RESTART_INTERVAL                    (NJPD2_REG_BASE+NJPD_OFFSET(0x05))

// Image Size
#define BK_NJPD2_IMG_HSIZE                           (NJPD2_REG_BASE+NJPD_OFFSET(0x06))
#define BK_NJPD2_IMG_VSIZE                           (NJPD2_REG_BASE+NJPD_OFFSET(0x07))

// Write-one-clear
#define BK_NJPD2_WRITE_ONE_CLEAR                     (NJPD2_REG_BASE+NJPD_OFFSET(0x08))

// Region of Interest
#define BK_NJPD2_ROI_H_START                         (NJPD2_REG_BASE+NJPD_OFFSET(0x09))
#define BK_NJPD2_ROI_V_START                         (NJPD2_REG_BASE+NJPD_OFFSET(0x0a))
#define BK_NJPD2_ROI_H_SIZE                          (NJPD2_REG_BASE+NJPD_OFFSET(0x0b))
#define BK_NJPD2_ROI_V_SIZE                          (NJPD2_REG_BASE+NJPD_OFFSET(0x0c))

// Gated-Clock Control
#define BK_NJPD2_GATED_CLOCK_CTRL                    (NJPD2_REG_BASE+NJPD_OFFSET(0x0d))

// Miu Interface
#define BK_NJPD2_MIU_READ_STATUS                     (NJPD2_REG_BASE+NJPD_OFFSET(0x0e))
#define BK_NJPD2_MIU_IBUFFER_CNT                     (NJPD2_REG_BASE+NJPD_OFFSET(0x0f))
#define BK_NJPD2_MIU_READ_START_ADDR_L               (NJPD2_REG_BASE+NJPD_OFFSET(0x10))
#define BK_NJPD2_MIU_READ_START_ADDR_H               (NJPD2_REG_BASE+NJPD_OFFSET(0x11))
#define BK_NJPD2_MIU_READ_BUFFER0_START_ADDR_L       (NJPD2_REG_BASE+NJPD_OFFSET(0x12))
#define BK_NJPD2_MIU_READ_BUFFER0_START_ADDR_H       (NJPD2_REG_BASE+NJPD_OFFSET(0x13))
#define BK_NJPD2_MIU_READ_BUFFER0_END_ADDR_L         (NJPD2_REG_BASE+NJPD_OFFSET(0x14))
#define BK_NJPD2_MIU_READ_BUFFER0_END_ADDR_H         (NJPD2_REG_BASE+NJPD_OFFSET(0x15))
#define BK_NJPD2_MIU_READ_BUFFER1_START_ADDR_L       (NJPD2_REG_BASE+NJPD_OFFSET(0x16))
#define BK_NJPD2_MIU_READ_BUFFER1_START_ADDR_H       (NJPD2_REG_BASE+NJPD_OFFSET(0x17))
#define BK_NJPD2_MIU_READ_BUFFER1_END_ADDR_L         (NJPD2_REG_BASE+NJPD_OFFSET(0x18))
#define BK_NJPD2_MIU_READ_BUFFER1_END_ADDR_H         (NJPD2_REG_BASE+NJPD_OFFSET(0x19))
#define BK_NJPD2_MIU_WRITE_START_ADDR_L              (NJPD2_REG_BASE+NJPD_OFFSET(0x1a))
#define BK_NJPD2_MIU_WRITE_START_ADDR_H              (NJPD2_REG_BASE+NJPD_OFFSET(0x1b))
#define BK_NJPD2_MIU_WRITE_POINTER_ADDR_L            (NJPD2_REG_BASE+NJPD_OFFSET(0x1c))
#define BK_NJPD2_MIU_WRITE_POINTER_ADDR_H            (NJPD2_REG_BASE+NJPD_OFFSET(0x1d))
#define BK_NJPD2_MIU_READ_POINTER_ADDR_L             (NJPD2_REG_BASE+NJPD_OFFSET(0x1e))
#define BK_NJPD2_MIU_READ_POINTER_ADDR_H             (NJPD2_REG_BASE+NJPD_OFFSET(0x1f))
#define BK_NJPD2_MIU_HTABLE_START_ADDR_L             (NJPD2_REG_BASE+NJPD_OFFSET(0x20))
#define BK_NJPD2_MIU_HTABLE_START_ADDR_H             (NJPD2_REG_BASE+NJPD_OFFSET(0x21))
#define BK_NJPD2_MIU_GTABLE_START_ADDR_L             (NJPD2_REG_BASE+NJPD_OFFSET(0x22))
#define BK_NJPD2_MIU_GTABLE_START_ADDR_H             (NJPD2_REG_BASE+NJPD_OFFSET(0x23))
#define BK_NJPD2_MIU_QTABLE_START_ADDR_L             (NJPD2_REG_BASE+NJPD_OFFSET(0x24))
#define BK_NJPD2_MIU_QTABLE_START_ADDR_H             (NJPD2_REG_BASE+NJPD_OFFSET(0x25))
#define BK_NJPD2_MIU_HTABLE_SIZE                     (NJPD2_REG_BASE+NJPD_OFFSET(0x26))
#define BK_NJPD2_SET_CHROMA_VALUE                    (NJPD2_REG_BASE+NJPD_OFFSET(0x27))
#define BK_NJPD2_IBUF_READ_LENGTH                    (NJPD2_REG_BASE+NJPD_OFFSET(0x28))

// Interrupt
#define BK_NJPD2_IRQ_CLEAR                           (NJPD2_REG_BASE+NJPD_OFFSET(0x29))
#define BK_NJPD2_IRQ_FORCE                           (NJPD2_REG_BASE+NJPD_OFFSET(0x2a))
#define BK_NJPD2_IRQ_MASK                            (NJPD2_REG_BASE+NJPD_OFFSET(0x2b))
#define BK_NJPD2_IRQ_FINAL_S                         (NJPD2_REG_BASE+NJPD_OFFSET(0x2c))
#define BK_NJPD2_IRQ_RAW_S                           (NJPD2_REG_BASE+NJPD_OFFSET(0x2d))

// Sram Gated-Clock Control
#define BK_NJPD2_MIU_TLB                             (NJPD2_REG_BASE+NJPD_OFFSET(0x2f)+1)

// Debug
#define BK_NJPD2_ROW_IDEX                            (NJPD2_REG_BASE+NJPD_OFFSET(0x30))
#define BK_NJPD2_COLUMN_IDEX                         (NJPD2_REG_BASE+NJPD_OFFSET(0x31))
#define BK_NJPD2_DEBUG_BUS_SELECT                    (NJPD2_REG_BASE+NJPD_OFFSET(0x32))
#define BK_NJPD2_DEBUG_BUS_H                         (NJPD2_REG_BASE+NJPD_OFFSET(0x33))
#define BK_NJPD2_DEBUG_BUS_L                         (NJPD2_REG_BASE+NJPD_OFFSET(0x34))
#define BK_NJPD2_IBUF_BYTE_COUNT_L                   (NJPD2_REG_BASE+NJPD_OFFSET(0x35))
#define BK_NJPD2_IBUF_BYTE_COUNT_H                   (NJPD2_REG_BASE+NJPD_OFFSET(0x36))
#define BK_NJPD2_VLD_BYTE_COUNT_L                    (NJPD2_REG_BASE+NJPD_OFFSET(0x37))
#define BK_NJPD2_VLD_BYTE_COUNT_H                    (NJPD2_REG_BASE+NJPD_OFFSET(0x38))
#define BK_NJPD2_VLD_DECODING_DATA_L                 (NJPD2_REG_BASE+NJPD_OFFSET(0x39))
#define BK_NJPD2_VLD_DECODING_DATA_H                 (NJPD2_REG_BASE+NJPD_OFFSET(0x3a))
#define BK_NJPD2_DEBUG_TRIG_CYCLE                    (NJPD2_REG_BASE+NJPD_OFFSET(0x3b))
#define BK_NJPD2_DEBUG_TRIG_MBX                      (NJPD2_REG_BASE+NJPD_OFFSET(0x3c))
#define BK_NJPD2_DEBUG_TRIG_MBY                      (NJPD2_REG_BASE+NJPD_OFFSET(0x3d))
#define BK_NJPD2_DEBUG_TRIGGER                       (NJPD2_REG_BASE+NJPD_OFFSET(0x3e))

// BIST
#define BK_NJPD2_BIST_FAIL                           (NJPD2_REG_BASE+NJPD_OFFSET(0x3f))

// TBC RIU Interface
#define BK_NJPD2_TBC                                 (NJPD2_REG_BASE+NJPD_OFFSET(0x40))
#define BK_NJPD2_TBC_WDATA0                          (NJPD2_REG_BASE+NJPD_OFFSET(0x41))
#define BK_NJPD2_TBC_WDATA1                          (NJPD2_REG_BASE+NJPD_OFFSET(0x42))
#define BK_NJPD2_TBC_RDATA_L                         (NJPD2_REG_BASE+NJPD_OFFSET(0x43))
#define BK_NJPD2_TBC_RDATA_H                         (NJPD2_REG_BASE+NJPD_OFFSET(0x44))

// Max Huffman Table Address
#define BK_NJPD2_Y_MAX_HUFFTABLE_ADDRESS             (NJPD2_REG_BASE+NJPD_OFFSET(0x45))
#define BK_NJPD2_CB_MAX_HUFFTABLE_ADDRESS            (NJPD2_REG_BASE+NJPD_OFFSET(0x46))
#define BK_NJPD2_CR_MAX_HUFFTABLE_ADDRESS            (NJPD2_REG_BASE+NJPD_OFFSET(0x47))

// Spare
#define BK_NJPD2_SPARE00                             (NJPD2_REG_BASE+NJPD_OFFSET(0x48))
#define BK_NJPD2_SPARE01                             (NJPD2_REG_BASE+NJPD_OFFSET(0x49))
#define BK_NJPD2_SPARE02                             (NJPD2_REG_BASE+NJPD_OFFSET(0x4a))
#define BK_NJPD2_SPARE03                             (NJPD2_REG_BASE+NJPD_OFFSET(0x4b))
#define BK_NJPD2_SPARE04                             (NJPD2_REG_BASE+NJPD_OFFSET(0x4c))
#define BK_NJPD2_SPARE05                             (NJPD2_REG_BASE+NJPD_OFFSET(0x4d))
#define BK_NJPD2_SPARE06                             (NJPD2_REG_BASE+NJPD_OFFSET(0x4e))
#define BK_NJPD2_SPARE07                             (NJPD2_REG_BASE+NJPD_OFFSET(0x4f))

#define BK_NJPD2_SPARE07                             (NJPD2_REG_BASE+NJPD_OFFSET(0x4f))

#define BK_NJPD2_MARB_SETTING_00                     (NJPD2_REG_BASE+NJPD_OFFSET(0x50))
#define BK_NJPD2_MARB_SETTING_01                     (NJPD2_REG_BASE+NJPD_OFFSET(0x51))
#define BK_NJPD2_MARB_SETTING_02                     (NJPD2_REG_BASE+NJPD_OFFSET(0x52))
#define BK_NJPD2_MARB_SETTING_03                     (NJPD2_REG_BASE+NJPD_OFFSET(0x53))
#define BK_NJPD2_MARB_SETTING_04                     (NJPD2_REG_BASE+NJPD_OFFSET(0x54))
#define BK_NJPD2_MARB_SETTING_05                     (NJPD2_REG_BASE+NJPD_OFFSET(0x55))
#define BK_NJPD2_MARB_SETTING_06                     (NJPD2_REG_BASE+NJPD_OFFSET(0x56))
#define BK_NJPD2_MARB_SETTING_07                     (NJPD2_REG_BASE+NJPD_OFFSET(0x57))

#define BK_NJPD2_MARB_UBOUND_0_L                     (NJPD2_REG_BASE+NJPD_OFFSET(0x58))
#define BK_NJPD2_MARB_UBOUND_0_H                     (NJPD2_REG_BASE+NJPD_OFFSET(0x59))
#define BK_NJPD2_MARB_LBOUND_0_L                     (NJPD2_REG_BASE+NJPD_OFFSET(0x5a))
#define BK_NJPD2_MARB_LBOUND_0_H                     (NJPD2_REG_BASE+NJPD_OFFSET(0x5b))

#define BK_NJPD2_CRC_MODE                            (NJPD2_REG_BASE+NJPD_OFFSET(0x6d))

// Miu Arbiter
#define BK_NJPD2_MARB_CRC_RESULT_0                   (NJPD2_REG_BASE+NJPD_OFFSET(0x70))
#define BK_NJPD2_MARB_CRC_RESULT_1                   (NJPD2_REG_BASE+NJPD_OFFSET(0x71))
#define BK_NJPD2_MARB_CRC_RESULT_2                   (NJPD2_REG_BASE+NJPD_OFFSET(0x72))
#define BK_NJPD2_MARB_CRC_RESULT_3                   (NJPD2_REG_BASE+NJPD_OFFSET(0x73))
#define BK_NJPD2_MARB_RESET                          (NJPD2_REG_BASE+NJPD_OFFSET(0x74))
#define BK_NJPD2_HANDSHAKE_CNT                       (NJPD2_REG_BASE+NJPD_OFFSET(0x74)+1)
#define BK_NJPD2_SW_MB_ROW_CNT                       (NJPD2_REG_BASE+NJPD_OFFSET(0x75))
#define BK_NJPD2_HANDSHAKE                           (NJPD2_REG_BASE+NJPD_OFFSET(0x75)+1)
#define BK_NJPD2_TOP_MARB_PORT_ENABLE                (NJPD2_REG_BASE+NJPD_OFFSET(0x76))

#define BK_NJPD2_GENERAL(x)                          (NJPD2_REG_BASE+NJPD_OFFSET(x))

// Clock Gen register=======================================================================

#define NJPD_CLOCK                                  (NJPD_CLKGEN2_BASE+NJPD_OFFSET(0x50))

#endif // _REG_NJPD_H_


