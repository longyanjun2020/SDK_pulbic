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
/// file    regHVD.h
/// @brief  HVD Module Register Definition
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _REG_HVD_H_
#define _REG_HVD_H_


//-------------------------------------------------------------------------------------------------
//  Hardware Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

//*****************************************************************************
// RIU macro
#define HVD_MACRO_START     do {
#define HVD_MACRO_END       } while (0)
#define HVD_RIU_BASE        u32HVDRegOSBase

#define HVD_HIGHBYTE(u16)               ((MS_U8)((u16) >> 8))
#define HVD_LOWBYTE(u16)                ((MS_U8)(u16))
#define HVD_RIU_READ_BYTE(addr)   ( READ_BYTE( HVD_RIU_BASE + (addr) ) )
#define HVD_RIU_READ_WORD(addr)   ( READ_WORD( HVD_RIU_BASE + (addr) ) )
#define HVD_RIU_WRITE_BYTE(addr, val)      { WRITE_BYTE( HVD_RIU_BASE+(addr), val); }
#define HVD_RIU_WRITE_WORD(addr, val)      { WRITE_WORD( HVD_RIU_BASE+(addr), val); }


#define _HVD_ReadByte( u32Reg )   HVD_RIU_READ_BYTE(((u32Reg) << 1) - ((u32Reg) & 1))

#define _HVD_Read2Byte( u32Reg )    (HVD_RIU_READ_WORD((u32Reg)<<1))

#define _HVD_Read4Byte( u32Reg )   ( (MS_U32)HVD_RIU_READ_WORD((u32Reg)<<1) | ((MS_U32)HVD_RIU_READ_WORD(((u32Reg)+2)<<1)<<16 )  )

#define _HVD_ReadRegBit( u32Reg, u8Mask )   (HVD_RIU_READ_BYTE(((u32Reg)<<1) - ((u32Reg) & 1)) & (u8Mask))

#define _HVD_ReadWordBit( u32Reg, u16Mask )   (_HVD_Read2Byte( u32Reg ) & (u16Mask))

#define _HVD_WriteRegBit( u32Reg, bEnable, u8Mask )                                     \
    HVD_MACRO_START                                                                     \
    HVD_RIU_WRITE_BYTE( (((u32Reg) <<1) - ((u32Reg) & 1)) , (bEnable) ? (HVD_RIU_READ_BYTE(  (((u32Reg) <<1) - ((u32Reg) & 1))  ) |  (u8Mask)) :                           \
                                (HVD_RIU_READ_BYTE( (((u32Reg) <<1) - ((u32Reg) & 1)) ) & ~(u8Mask)));                            \
    HVD_MACRO_END

#define _HVD_WriteByte( u32Reg, u8Val )                                                 \
    HVD_MACRO_START                                                                     \
    HVD_RIU_WRITE_BYTE(((u32Reg) << 1) - ((u32Reg) & 1), u8Val);   \
    HVD_MACRO_END

#define _HVD_Write2Byte( u32Reg, u16Val )                                               \
    HVD_MACRO_START                                                                     \
    if ( ((u32Reg) & 0x01) )                                                        \
    {                                                                               \
        HVD_RIU_WRITE_BYTE(((u32Reg) << 1) - 1, (MS_U8)((u16Val)));                                  \
        HVD_RIU_WRITE_BYTE(((u32Reg) + 1) << 1, (MS_U8)((u16Val) >> 8));                             \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        HVD_RIU_WRITE_WORD( ((u32Reg)<<1) ,  u16Val);                                                       \
    }                                                                               \
    HVD_MACRO_END

#define _HVD_Write3Byte( u32Reg, u32Val )   \
    if ((u32Reg) & 0x01)                                                                \
    {                                                                                               \
        HVD_RIU_WRITE_BYTE((u32Reg << 1) - 1, u32Val);                                    \
        HVD_RIU_WRITE_WORD( (u32Reg + 1)<<1 , ((u32Val) >> 8));                                      \
    }                                                                                           \
    else                                                                                        \
    {                                                                                               \
        HVD_RIU_WRITE_WORD( (u32Reg) << 1,  u32Val);                                                         \
        HVD_RIU_WRITE_BYTE( (u32Reg + 2) << 1 ,  ((u32Val) >> 16));                             \
    }

#define _HVD_Write4Byte( u32Reg, u32Val )                                               \
    HVD_MACRO_START                                                                     \
    if ((u32Reg) & 0x01)                                                      \
    {                                                                                               \
        HVD_RIU_WRITE_BYTE( ((u32Reg) << 1) - 1 ,  u32Val);                                         \
        HVD_RIU_WRITE_WORD( ((u32Reg) + 1)<<1 , ( (u32Val) >> 8));                                      \
        HVD_RIU_WRITE_BYTE( (((u32Reg) + 3) << 1) ,  ((u32Val) >> 24));                           \
    }                                                                                               \
    else                                                                                                \
    {                                                                                                   \
        HVD_RIU_WRITE_WORD( (u32Reg) <<1 ,  u32Val);                                                             \
        HVD_RIU_WRITE_WORD(  ((u32Reg) + 2)<<1 ,  ((u32Val) >> 16));                                             \
    }                                                                     \
    HVD_MACRO_END

#define _HVD_WriteByteMask( u32Reg, u8Val, u8Msk )                                      \
    HVD_MACRO_START                                                                     \
    HVD_RIU_WRITE_BYTE( (((u32Reg) <<1) - ((u32Reg) & 1)), (HVD_RIU_READ_BYTE((((u32Reg) <<1) - ((u32Reg) & 1))) & ~(u8Msk)) | ((u8Val) & (u8Msk)));                   \
    HVD_MACRO_END

#define _HVD_WriteWordMask( u32Reg, u16Val , u16Msk)                                               \
    HVD_MACRO_START                                                                     \
    if ( ((u32Reg) & 0x01) )                                                        \
    {                                                                                           \
        _HVD_WriteByteMask( ((u32Reg)+1) , (((u16Val) & 0xff00)>>8) , (((u16Msk)&0xff00)>>8) );                                                                          \
        _HVD_WriteByteMask( (u32Reg) , ((u16Val) & 0x00ff) , ((u16Msk)&0x00ff) );                                                                          \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        HVD_RIU_WRITE_WORD( ((u32Reg)<<1) ,  (((u16Val) & (u16Msk))  | (_HVD_Read2Byte( u32Reg  ) & (~( u16Msk ))))  );                                                       \
    }                                                                               \
    HVD_MACRO_END

//------------------------------------------------------------------------------
// MVD Reg
//------------------------------------------------------------------------------
#define REG_MVD_BASE                    (0x1100)

#define MVD_REG_STAT_CTRL               (REG_MVD_BASE)
    #define MVD_REG_CTRL_RST            BIT(0)
    #define MVD_REG_CTRL_INIT           BIT(2)
    #define MVD_REG_DISCONNECT_MIU      BIT(6)

//------------------------------------------------------------------------------
// HVD Reg
//------------------------------------------------------------------------------
#define REG_HVD_BASE                            (0x62100) //M5_Bank:1621h
#define REG_EVD_BASE                            (0x60B00)

#define HVD_REG_REV_ID                          (REG_HVD_BASE+(( 0x0000)<<1))
#define HVD_REG_RESET                           (REG_HVD_BASE+(( 0x0001)<<1))
    #define HVD_REG_RESET_SWRST                 BIT(0)
    #define HVD_REG_RESET_SWRST_FIN             BIT(2)
    #define HVD_REG_RESET_STOP_BBU              BIT(3)
    #define HVD_REG_RESET_MIU_RDY               BIT(4)
    #define HVD_REG_RESET_HK_AVS_MODE           BIT(8)
    #define HVD_REG_RESET_HK_RM_MODE            BIT(9)
    #define HVD_REG_RESET_HK_RV9_DEC_MODE       BIT(10)
    #define HVD_REG_RESET_MIU_128               BIT(11)
#define HVD_REG_ESB_ST_ADDR_L(reg_base)                   (reg_base+(( 0x0002)<<1))
#define HVD_REG_ESB_ST_ADDR_H(reg_base)                   (reg_base+(( 0x0003)<<1))

#define HVD_REG_ESB_LENGTH_L(reg_base)                    (reg_base+(( 0x0004)<<1))
#define HVD_REG_ESB_LENGTH_H(reg_base)                    (reg_base+(( 0x0005)<<1))

#define HVD_REG_ESB_RPTR(reg_base)                        (reg_base+(( 0x0006)<<1))
    #define HVD_REG_ESB_RPTR_POLL               BIT(0)
#define HVD_REG_ESB_RPTR_H(reg_base)                      (reg_base+(( 0x0007)<<1))
#define HVD_REG_MIF_BBU(reg_base)                         (reg_base+(( 0x0008)<<1))
    #define HVD_REG_MIF_OFFSET_L_BITS           7
    #define HVD_REG_MIF_OFFSET_H                BIT(12)
    #define HVD_REG_BBU_TSP_INPUT               BIT(8)
    #define HVD_REG_BBU_PASER_MASK              (BIT(10) | BIT(9))
    #define HVD_REG_BBU_PASER_DISABLE           0
    #define HVD_REG_BBU_PASER_ENABLE_ALL        BIT(9)
    #define HVD_REG_BBU_PASER_ENABLE_03         (BIT(9)|BIT(10))
    #define HVD_REG_BBU_AUTO_NAL_TAB            BIT(11)
#define HVD_REG_NAL_TBL_ST_ADDR_L(reg_base)               (reg_base+(( 0x0009)<<1))
#define HVD_REG_NAL_TBL_ST_ADDR_H(reg_base)               (reg_base+(( 0x000A)<<1))
#define HVD_REG_HI_MBOX0_L(reg_base)                      (reg_base+(( 0x000B)<<1))
#define HVD_REG_HI_MBOX0_H(reg_base)                      (reg_base+(( 0x000C)<<1))
#define HVD_REG_HI_MBOX1_L(reg_base)                      (reg_base+(( 0x000D)<<1))
#define HVD_REG_HI_MBOX1_H(reg_base)                      (reg_base+(( 0x000E)<<1))
#define HVD_REG_HI_MBOX_SET(reg_base)                     (reg_base+(( 0x000F)<<1))
    #define HVD_REG_HI_MBOX0_SET                BIT(0)
    #define HVD_REG_HI_MBOX1_SET                BIT(8)
#define HVD_REG_RISC_MBOX_CLR(reg_base)                   (reg_base+(( 0x0010)<<1))
    #define HVD_REG_RISC_MBOX0_CLR              BIT(0)
    #define HVD_REG_RISC_MBOX1_CLR              BIT(1)
    #define HVD_REG_RISC_ISR_CLR                BIT(2)
    #define HVD_REG_NAL_WPTR_SYNC               BIT(3)
    #define HVD_REG_RISC_ISR_MSK                BIT(6)
    #define HVD_REG_RISC_ISR_FORCE              BIT(10)
#define HVD_REG_RISC_MBOX_RDY(reg_base)                   (reg_base+(( 0x0011)<<1))
    #define HVD_REG_RISC_MBOX0_RDY              BIT(0)
    #define HVD_REG_RISC_MBOX1_RDY              BIT(4)
    #define HVD_REG_RISC_ISR_VALID              BIT(8)
#define HVD_REG_HI_MBOX_RDY(reg_base)                     (reg_base+(( 0x0012)<<1))
    #define HVD_REG_HI_MBOX0_RDY                BIT(0)
    #define HVD_REG_HI_MBOX1_RDY                BIT(8)
#define HVD_REG_RISC_MBOX0_L(reg_base)                    (reg_base+(( 0x0013)<<1))
#define HVD_REG_RISC_MBOX0_H(reg_base)                    (reg_base+(( 0x0014)<<1))
#define HVD_REG_RISC_MBOX1_L(reg_base)                    (reg_base+(( 0x0015)<<1))
#define HVD_REG_RISC_MBOX1_H(reg_base)                    (reg_base+(( 0x0016)<<1))
#define HVD_REG_POLL_NAL_RPTR(reg_base)                   (reg_base+(( 0x0017)<<1))
    #define HVD_REG_POLL_NAL_RPTR_BIT           BIT(0)
#define HVD_REG_NAL_RPTR_HI(reg_base)                     (reg_base+(( 0x0018)<<1))
#define HVD_REG_NAL_WPTR_HI(reg_base)                     (reg_base+(( 0x0019)<<1))
#define HVD_REG_NAL_TAB_LEN(reg_base)                     (reg_base+(( 0x0020)<<1))

#define HVD_REG_DEBUG_DAT_L                     (REG_HVD_BASE+(( 0x0023)<<1))
#define HVD_REG_DEBUG_DAT_H                     (REG_HVD_BASE+(( 0x0024)<<1))
#define HVD_REG_DEBUG_SEL                       (REG_HVD_BASE+(( 0x0025)<<1))

//------------------------------------------------------------------------------
// EVD Reg
//------------------------------------------------------------------------------
#define EVD_REG_RESET                           (REG_EVD_BASE + ((0x0001) << 1))
    #define EVD_REG_RESET_SWRST                 BIT(0)
    #define EVD_REG_RESET_SWRST_FIN             BIT(2)
    #define EVD_REG_RESET_STOP_BBU              BIT(3)
    #define EVD_REG_RESET_MIU_RDY               BIT(4)
    #define EVD_REG_RESET_MIU1_128              BIT(5)
    #define EVD_REG_RESET_MIU1_256              BIT(6)
    #define EVD_REG_RESET_HK_HEVC_MODE          BIT(8)
    #define EVD_REG_RESET_HK_TSP2EVD_EN         BIT(9)
    #define EVD_REG_RESET_MIU_256               BIT(10)
    #define EVD_REG_RESET_MIU_128               BIT(11)
    #define EVD_REG_RESET_CPUIF_SEL             BIT(12)
    #define EVD_REG_RESET_ALL_SRAM_SD_EN        BIT(13)
    #define EVD_REG_RESET_BOND_UHD              BIT(14)
    #define EVD_REG_RESET_BOND_HD               BIT(15)

//------------------------------------------------------------------------------
// ChipTop Reg
//------------------------------------------------------------------------------

#define CHIPTOP_REG_BASE               (0x1E00 ) //M5_bank:101Eh
#define CLKGEN0_REG_BASE               (0x3800 ) //M5_bank:1038h

#define REG_TOP_PSRAM0_1_MIUMUX            (CHIPTOP_REG_BASE+(0x002D<<1))   //TODO
    #define TOP_CKG_PSRAM0_MASK                 BMASK(1:0)
    #define TOP_CKG_PSRAM0_DIS                  BIT(0)
    #define TOP_CKG_PSRAM0_INV                  BIT(1)
    #define TOP_CKG_PSRAM1_MASK                 BMASK(3:2)
    #define TOP_CKG_PSRAM1_DIS                  BIT(0)
    #define TOP_CKG_PSRAM1_INV                  BIT(1)
    #define TOP_MIU_MUX_G07_MASK                BMASK(7:6)
	#define TOP_MIU_MUX_G07_OD_LSB_R            BITS(7:6,0)
	#define TOP_MIU_MUX_G07_GOP2_R              BITS(7:6,1)
    #define TOP_MIU_MUX_G08_MASK                BMASK(9:8)
	#define TOP_MIU_MUX_G08_OD_LSB_W            BITS(9:8,0)
	#define TOP_MIU_MUX_G08_VE_W                BITS(9:8,1)
    #define TOP_MIU_MUX_G15_MASK                BMASK(11:10)
	#define TOP_MIU_MUX_G15_GOP2_R              BITS(11:10,0)
	#define TOP_MIU_MUX_G15_OD_LSB_R            BITS(11:10,1)
    #define TOP_MIU_MUX_G1A_MASK                BMASK(13:12)
	#define TOP_MIU_MUX_G1A_VE_W                BITS(13:12,0)
	#define TOP_MIU_MUX_G1A_OD_LSB_W            BITS(13:12,1)
    #define TOP_MIU_MUX_G26_MASK                BMASK(15:14)
	#define TOP_MIU_MUX_G26_RVD_RW              BITS(15:14,0)
	#define TOP_MIU_MUX_G26_SVD_INTP_R          BITS(15:14,1)
	#define TOP_MIU_MUX_G26_MVD_R               BITS(15:14,2)

#define REG_TOP_VPU             (CLKGEN0_REG_BASE+(0x0052<<1))
    #define TOP_CKG_VPU_MASK                  BMASK(11:8)
    #define TOP_CKG_VPU_DIS                   BIT(8)
    #define TOP_CKG_VPU_INV                   BIT(9)
    #define TOP_CKG_VPU_CLK_MASK              BMASK(11:10)
    #define TOP_CKG_VPU_240MHZ                BITS(11:10,0)
    #define TOP_CKG_VPU_216MHZ                BITS(11:10,1)
    #define TOP_CKG_VPU_160MHZ                BITS(11:10,2)
    #define TOP_CKG_VPU_144MHZ                BITS(11:10,3)

#define REG_TOP_HVD_IDB         (CLKGEN0_REG_BASE+(0x0051<<1))
    #define TOP_CKG_HVD_IDB_MASK              BMASK(3:0)
    #define TOP_CKG_HVD_IDB_DIS               BIT(0)
    #define TOP_CKG_HVD_IDB_INV               BIT(1)
    #define TOP_CKG_HVD_IDB_CLK_MASK          BMASK(3:2)
    #define TOP_CKG_HVD_IDB_320MHZ            BITS(3:2, 0)
    #define TOP_CKG_HVD_IDB_288MHZ            BITS(3:2, 1)
    #define TOP_CKG_HVD_IDB_172MHZ            BITS(3:2, 2)
    #define TOP_CKG_HVD_IDB_240MHZ            BITS(3:2, 3)

#define REG_TOP_HVD             (CLKGEN0_REG_BASE+(0x0050<<1))
    #define TOP_CKG_HVD_MASK                  BMASK(11:8)
    #define TOP_CKG_HVD_DIS                   BIT(8)
    #define TOP_CKG_HVD_INV                   BIT(9)
    #define TOP_CKG_HVD_CLK_MASK              BMASK(11:10)
    #define TOP_CKG_HVD_240MHZ                BITS(11:10,0)
    #define TOP_CKG_HVD_172MHZ                BITS(11:10,1)
    #define TOP_CKG_HVD_160MHZ                BITS(11:10,2)
    #define TOP_CKG_HVD_144MHZ                BITS(11:10,3)

#define REG_TOP_MVD             (CLKGEN0_REG_BASE+(0x0039<<1))
    #define TOP_CKG_MVD_MASK                  BMASK(4:0)
    #define TOP_CKG_MHVD_DIS                  BIT(0)
    #define TOP_CKG_MVD_INV                   BIT(1)
    #define TOP_CKG_MVD_CLK_MASK              BMASK(4:2)
    #define TOP_CKG_MVD_160MHZ                BITS(4:2,0)
    #define TOP_CKG_MVD_144MHZ                BITS(4:2,1)
    #define TOP_CKG_MVD_123MHZ                BITS(4:2,2)
    #define TOP_CKG_MVD_108MHZ                BITS(4:2,3)
    #define TOP_CKG_MVD_86MHZ                 BITS(4:2,4)
    #define TOP_CKG_MVD_72MHZ                 BITS(4:2,5)
    #define TOP_CKG_MVD_62MHZ                 BITS(4:2,6)
    #define TOP_CKG_MVD_XTALI                 BITS(4:2,7)


#define REG_TOP_MVD2             (CLKGEN0_REG_BASE+(0x0039<<1))
    #define TOP_CKG_MVD2_MASK                  BMASK(12:8)
    #define TOP_CKG_MHVD2_DIS                   BIT(8)
    #define TOP_CKG_MVD2_INV                   BIT(9)
    #define TOP_CKG_MVD2_CLK_MASK              BMASK(12:10)
    #define TOP_CKG_MVD2_170MHZ                BITS(12:10,0)
    #define TOP_CKG_MVD2_144MHZ                BITS(12:10,1)
    #define TOP_CKG_MVD2_160MHZ                BITS(12:10,2)
    #define TOP_CKG_MVD2_123MHZ                BITS(12:10,3)
    #define TOP_CKG_MVD2_XTALI                 BITS(12:10,4)
    #define TOP_CKG_MVD2_CLK_MIU_P             BITS(12:10,7)

#define REG_TOP_CKG_EVD_PPU             (CLKGEN0_REG_BASE+(0x0033<<1))
    #define TOP_CKG_EVD_PPU_MASK                    BMASK(13:10)
    #define TOP_CKG_EVD_PPU_DIS                  BIT(8)
    #define TOP_CKG_EVD_PPU_INV                   BIT(9)
    #define TOP_CKG_EVD_PPU_240MHZ                   BITS(13:10, 0)
    #define TOP_CKG_EVD_PPU_216MHZ                   BITS(13:10, 1)
    #define TOP_CKG_EVD_PPU_192MHZ                   BITS(13:10, 2)
    #define TOP_CKG_EVD_PPU_160MHZ                   BITS(13:10, 3)

#define REG_TOP_CKG_EVD             (CLKGEN0_REG_BASE+(0x0034<<1))
    #define TOP_CKG_EVD_MASK                    BMASK(13:10)
    #define TOP_CKG_EVD_DIS                  BIT(8)
    #define TOP_CKG_EVD_INV                   BIT(9)
    #define TOP_CKG_EVD_240MHZ                   BITS(13:10, 0)
    #define TOP_CKG_EVD_216MHZ                   BITS(13:10, 1)
    #define TOP_CKG_EVD_192MHZ                   BITS(13:10, 2)
    #define TOP_CKG_EVD_160MHZ                   BITS(13:10, 3)

#define REG_TOP_UART_SEL0             (CHIPTOP_REG_BASE+(0x0053<<1))
    #define REG_TOP_UART_SEL_0_MASK                  BMASK(3:0)    
    #define REG_TOP_UART_SEL_VD_MHEG5                BITS(3:0 , 0)
    #define REG_TOP_UART_SEL_FUART                   BITS(3:0 , 1)    
    #define REG_TOP_UART_SEL_UART0                   BITS(3:0 , 2)
    #define REG_TOP_UART_SEL_UART1                   BITS(3:0 , 3)
//------------------------------------------------------------------------------
// MIU Reg
//------------------------------------------------------------------------------
#define MIU0_REG_HVD_BASE             	(0x1600)  //M5_bank:1016h Mercury5_reg_arb_e_dig.xls
#define MIU0_REG_HVD_SEL_BASE_0         (0x1200)  //M5_bank:1012h Mercury5_reg_miu_dig.xls
#define MIU0_REG_HVD_SEL_BASE_1         (0x1400)  //M5_bank:1014h Mercury5_reg_arbb_dig.xls

#define MIU0_REG_RQ0_MASK                 (MIU0_REG_HVD_BASE+(( 0x0003)<<1))
#define MIU0_REG_RQ1_MASK                 (MIU0_REG_HVD_BASE+(( 0x0023)<<1))
#define MIU0_REG_RQ2_MASK                 (MIU0_REG_HVD_BASE+(( 0x0043)<<1))
#define MIU0_REG_RQ3_MASK                 (MIU0_REG_HVD_BASE+(( 0x0063)<<1))

#define MIU0_REG_SEL0                 (MIU0_REG_HVD_SEL_BASE_0+(( 0x0078)<<1))
#define MIU0_REG_SEL1                 (MIU0_REG_HVD_SEL_BASE_0+(( 0x0079)<<1))
#define MIU0_REG_SEL2                 (MIU0_REG_HVD_SEL_BASE_0+(( 0x007A)<<1))
#define MIU0_REG_SEL3                 (MIU0_REG_HVD_SEL_BASE_0+(( 0x007B)<<1))
#define MIU0_REG_SEL4                 (MIU0_REG_HVD_SEL_BASE_0+(( 0x007C)<<1))
#define MIU0_REG_SEL5                 (MIU0_REG_HVD_SEL_BASE_0+(( 0x007D)<<1))
#define MIU0_REG_SEL6                 (MIU0_REG_HVD_SEL_BASE_1+(( 0x0078)<<1))

#define MIU_HVD_RW      (BIT(10)|BIT(11))
#define MIU_MVD_RW      (BIT(5)|BIT(6))

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------


#endif // _REG_HVD_H_

