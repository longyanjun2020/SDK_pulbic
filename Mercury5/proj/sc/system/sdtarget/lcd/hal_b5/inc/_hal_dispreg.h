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
* @file    hal_disp.h
* @version
* @brief   This module defines the Display driver hal layer
*
*/

#ifndef __HAL_DISPREG_H__
#define __HAL_DISPREG_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* CONSTANT DEFINITION                                                      */
/*--------------------------------------------------------------------------*/

/*******************  Reg ***********/
#define DISP_REG_BASE                       (0x74003000)

#define DISP_REG_ENABLE                     (DISP_REG_BASE + 0x0000) ///
#define DISP_REG_PATTERN                    (DISP_REG_BASE + 0x0004)
#define DISP_REG_LCM_BUS                    (DISP_REG_BASE + 0x0008) ///

#define DISP_REG_WIDTH_MASK                 (DISP_REG_BASE + 0x003C) ///

//Video buffer configuration....
#define DISP_REG_V0_ADDR_L                  (DISP_REG_BASE + 0x0040) ///
#define DISP_REG_V0_ADDR_H                  (DISP_REG_BASE + 0x0044) ///
#define DISP_REG_V0_WIDTH                   (DISP_REG_BASE + 0x0048) ///
#define DISP_REG_V0_HEIGHT                  (DISP_REG_BASE + 0x004C) ///
#define DISP_REG_V0_PIT                     (DISP_REG_BASE + 0x0050) ///

//G0 buffer configuration....
#define DISP_REG_G0_ADDR_L                  (DISP_REG_BASE + 0x0054) ///
#define DISP_REG_G0_ADDR_H                  (DISP_REG_BASE + 0x0058) ///
#define DISP_REG_G0_WIDTH                   (DISP_REG_BASE + 0x005C) ///
#define DISP_REG_G0_HEIGHT                  (DISP_REG_BASE + 0x0060) ///
#define DISP_REG_G0_PIT                     (DISP_REG_BASE + 0x0064) ///

#define DISP_REG_BUF_FMT                    (DISP_REG_BASE + 0x0094) ///

#define DISP_REG_LAYER_SEL                  (DISP_REG_BASE + 0x009C) ///


//PIP parameters...
#define DISP_REG_PIPL1_Xst                  (DISP_REG_BASE + 0x00A0) ///
#define DISP_REG_PIPL1_Yst                  (DISP_REG_BASE + 0x00A4) ///
#define DISP_REG_PIPL1_Xend                 (DISP_REG_BASE + 0x00A8) ///
#define DISP_REG_PIPL1_Yend                 (DISP_REG_BASE + 0x00AC) ///


//Alpha blending parameters...
#define DISP_REG_L1_ALPHA                   (DISP_REG_BASE + 0x00D0)


//Source color key parameters...
#define DISP_REG_L1_SCK_R                   (DISP_REG_BASE + 0x00DC) ///
#define DISP_REG_L1_SCK_G                   (DISP_REG_BASE + 0x00E0) ///
#define DISP_REG_L1_SCK_B                   (DISP_REG_BASE + 0x00E4) ///

#define DISP_REG_SCK_OP                     (DISP_REG_BASE + 0x0100) ///

//back ground configuration paramters....
#define DISP_REG_L0_BgC_BG                  (DISP_REG_BASE + 0x0104) ///
#define DISP_REG_L1_BgC_BG                  (DISP_REG_BASE + 0x0108) ///
#define DISP_REG_L01_BgC_R                  (DISP_REG_BASE + 0x0114) ///
#define DISP_REG_EN_BGC                     (DISP_REG_BASE + 0x011C) ///

#define DISP_REG_COMP_ORD                   (DISP_REG_BASE + 0x0120) ///


//LCM program parameters...
#define DISP_REG_LCM_REG_L                  (DISP_REG_BASE + 0x0124) ///
#define DISP_REG_LCM_REG_H                  (DISP_REG_BASE + 0x0128) ///

#define DISP_REG_LCM_READCMD                (DISP_REG_BASE + 0x012C) ///
#define DISP_REG_LCM_READDATA_L             (DISP_REG_BASE + 0x0130) ///
#define DISP_REG_LCM_READDATA_H             (DISP_REG_BASE + 0x0134) ///
#define DISP_REG_LCM_CSRS                   (DISP_REG_BASE + 0x0138) ///


#define DISP_REG_FORCE_UPDATE               (DISP_REG_BASE + 0x013C) ///


#define DISP_REG_SW_RESET                   (DISP_REG_BASE + 0x0140) ///
#define DISP_REG_DEBUG_MD                   (DISP_REG_BASE + 0x0144) ///
#define DISP_REG_IRQ                        (DISP_REG_BASE + 0x0148) ///
#define DISP_REG_IRQ_FINAL                  (DISP_REG_BASE + 0x014C) ///


#define DISP_REG_LCMSYNC_MODE               (DISP_REG_BASE + 0x0150)
#define DISP_REG_FMARK_DELAY_CNT_L          (DISP_REG_BASE + 0x0154)
#define DISP_REG_FMARK_DELAY_CNT_H          (DISP_REG_BASE + 0x0158)


#define DISP_REG_DITHER_CTRL                (DISP_REG_BASE + 0x015C)
#define DISP_REG_RPRI_CTRL                  (DISP_REG_BASE + 0x0160)
#define DISP_REG_RPRI_TH                    (DISP_REG_BASE + 0x0164)


#define DISP_REG_BURST_MODE                 (DISP_REG_BASE + 0x016C)

#define DISP_REG_EOM_DELAY                  (DISP_REG_BASE + 0x0170) ///

#define DISP_REG_DGCLK_EN                   (DISP_REG_BASE + 0x0174) ///


//Gamma paramters....
#define DISP_REG_EN_GAMMA                   (DISP_REG_BASE + 0x0180)
#define DISP_REG_GAMMA_ADDR                 (DISP_REG_BASE + 0x0184)
#define DISP_REG_GAMMA_WRDATA               (DISP_REG_BASE + 0x0188)
#define DISP_REG_READ_PULSE                 (DISP_REG_BASE + 0x018C)
#define DISP_REG_R_GAMMA_R                  (DISP_REG_BASE + 0x0190)
#define DISP_REG_R_GAMMA_G                  (DISP_REG_BASE + 0x0194)
#define DISP_REG_R_GAMMA_B                  (DISP_REG_BASE + 0x0198)


#define DISP_REG_YUV_ORDER                  (DISP_REG_BASE + 0x019C) ///

#define DISP_REG_PAD_SWITCH                 (DISP_REG_BASE + 0x01A0) ///
#define DISP_REG_DEBUG_DATAL                (DISP_REG_BASE + 0x01A4)
#define DISP_REG_DEBUG_DATAH                (DISP_REG_BASE + 0x01A8) ///

#define DISP_REG_SW_DOEN                    (DISP_REG_BASE + 0x01AC)
#define DISP_REG_DISP_FAST                  (DISP_REG_BASE + 0x01B0)
#define DISP_REG_SW_FMARK                   (DISP_REG_BASE + 0x01B4)

//#define DISP_REG_FORCE_NANDSTOP         (DISP_REG_BASE + 0x01B8)


#define DISP_REG_V0_LINEWIDTH               (DISP_REG_BASE + 0x01C0) ///
#define DISP_REG_G0_LINEWIDTH               (DISP_REG_BASE + 0x01C4) ///


// new in B5 : TEAR EFFECT SETTING : avoid tearing effect relative parameter
#define DISP_REG_EN_TE                      (DISP_REG_BASE + 0x01C8)

#define DISP_REG_TE_CHK_PT_NO               (DISP_REG_BASE + 0x01CC)

#define DISP_REG_TE_CHK_PT_INTVL_L          (DISP_REG_BASE + 0x01D0)
#define DISP_REG_TE_CHK_PT_INTVL_H          (DISP_REG_BASE + 0x01D4)

#define DISP_REG_TE_R_CHK_PT_SIZE_L         (DISP_REG_BASE + 0x01D8)
#define DISP_REG_TE_R_CHK_PT_SIZE_H         (DISP_REG_BASE + 0x01DC)

#define DISP_REG_TE_W_CHK_PT_SIZE_L         (DISP_REG_BASE + 0x01E0)
#define DISP_REG_TE_W_CHK_PT_SIZE_H         (DISP_REG_BASE + 0x01E4)

#define DISP_TE_HI_LOAD_CHK_PT_SIZE_L       (DISP_REG_BASE + 0x01E8)
#define DISP_TE_HI_LOAD_CHK_PT_SIZE_H       (DISP_REG_BASE + 0x01EC)

#define DISP_TE_HI_LOAD_CHK_PT_NO_ST        (DISP_REG_BASE + 0x01F0)
#define DISP_TE_HI_LOAD_CHK_PT_NO_END       (DISP_REG_BASE + 0x01F4)


// SPARE_REG_DISP0
#define DISP_REG_DISP0_SPARE0               (DISP_REG_BASE + 0x01F8)
#define DISP_REG_DISP0_SPARE_BIT            (DISP_REG_BASE + 0x01FC)

//#define DISP_REG_BASE_MAX               DISP_REG_SPARE_BIT


#define DISP_REG_BASE2                      (0x74003200)


#define DISP_EN_SCLDMA_DIRECT               (DISP_REG_BASE2 + 0x0000)


// Misc
#define DISP_REG_LCM_WCMD_COND              (DISP_REG_BASE2 + 0x0004)
#define DISP_REG_MX_DISP_ACT                (DISP_REG_BASE2 + 0x0008)
#define DISP_REG_VBUF_ARGB_CH_SEL           (DISP_REG_BASE2 + 0x000C)
#define DISP_REG_G0BUF_ARGB_CH_SEL          (DISP_REG_BASE2 + 0x0010)

#define DISP_REG_CONT_FM_BLANK              (DISP_REG_BASE2 + 0x0014)
#define DISP_REG_CPU_VS_BLANK               (DISP_REG_BASE2 + 0x0018)


// IO Test Mode Registers
#define DISP_REG_LCM_IO_TEST_MODE           (DISP_REG_BASE2 + 0x0040)

#define DISP_REG_LCM_IO_TEST_DOEN_L         (DISP_REG_BASE2 + 0x0044)
#define DISP_REG_LCM_IO_TEST_DOEN_H         (DISP_REG_BASE2 + 0x0048)

#define DISP_REG_LCM_IO_TEST_DATA_L         (DISP_REG_BASE2 + 0x004C)
#define DISP_REG_LCM_IO_TEST_DATA_H         (DISP_REG_BASE2 + 0x0050)

#define DISP_REG_LCM_IO_TEST_SIGS           (DISP_REG_BASE2 + 0x0054)


// Multi window setting
#define DISP_REG_G0_LINE_WID_1              (DISP_REG_BASE2 + 0x005C)
#define DISP_REG_G0_LINE_WID_2              (DISP_REG_BASE2 + 0x0060)
#define DISP_REG_G0_LINE_WID_3              (DISP_REG_BASE2 + 0x0064)

#define DISP_REG_GPIX0_INI_1_L              (DISP_REG_BASE2 + 0x0080)
#define DISP_REG_GPIX0_INI_1_H              (DISP_REG_BASE2 + 0x0084)
#define DISP_REG_GBUF0_WIDTH_1              (DISP_REG_BASE2 + 0x0088)
#define DISP_REG_GBUF0_HEIGHT_1             (DISP_REG_BASE2 + 0x008C)
#define DISP_REG_GBUF0_PIT_1                (DISP_REG_BASE2 + 0x0090)

#define DISP_REG_GPIX0_INI_2_L              (DISP_REG_BASE2 + 0x0094)
#define DISP_REG_GPIX0_INI_2_H              (DISP_REG_BASE2 + 0x0098)
#define DISP_REG_GBUF0_WIDTH_2              (DISP_REG_BASE2 + 0x009C)
#define DISP_REG_GBUF0_HEIGHT_2             (DISP_REG_BASE2 + 0x00A0)
#define DISP_REG_GBUF0_PIT_2                (DISP_REG_BASE2 + 0x00A4)

#define DISP_REG_GPIX0_INI_3_L              (DISP_REG_BASE2 + 0x00A8)
#define DISP_REG_GPIX0_INI_3_H              (DISP_REG_BASE2 + 0x00AC)
#define DISP_REG_GBUF0_WIDTH_3              (DISP_REG_BASE2 + 0x00B0)
#define DISP_REG_GBUF0_HEIGHT_3             (DISP_REG_BASE2 + 0x00B4)
#define DISP_REG_GBUF0_PIT_3                (DISP_REG_BASE2 + 0x00B8)

#define DISP_REG_G0_MASK_WIDTH_1            (DISP_REG_BASE2 + 0x00BC)
#define DISP_REG_G0_MASK_WIDTH_2            (DISP_REG_BASE2 + 0x00C0)
#define DISP_REG_G0_MASK_WIDTH_3            (DISP_REG_BASE2 + 0x00C4)

#define DISP_REG_MULTI_WIN_CNT              (DISP_REG_BASE2 + 0x00C8)

#define DISP_REG_PIP_L1_XST_1               (DISP_REG_BASE2 + 0x00CC)
#define DISP_REG_PIP_L1_YST_1               (DISP_REG_BASE2 + 0x00D0)
#define DISP_REG_PIP_L1_XEND_1              (DISP_REG_BASE2 + 0x00D4)
#define DISP_REG_PIP_L1_YEND_1              (DISP_REG_BASE2 + 0x00D8)

#define DISP_REG_PIP_L1_XST_2               (DISP_REG_BASE2 + 0x00DC)
#define DISP_REG_PIP_L1_YST_2               (DISP_REG_BASE2 + 0x00E0)
#define DISP_REG_PIP_L1_XEND_2              (DISP_REG_BASE2 + 0x00E4)
#define DISP_REG_PIP_L1_YEND_2              (DISP_REG_BASE2 + 0x0100)

#define DISP_REG_PIP_L1_XST_3               (DISP_REG_BASE2 + 0x0104)
#define DISP_REG_PIP_L1_YST_3               (DISP_REG_BASE2 + 0x0108)
#define DISP_REG_PIP_L1_XEND_3              (DISP_REG_BASE2 + 0x010C)
#define DISP_REG_PIP_L1_YEND_3              (DISP_REG_BASE2 + 0x0110)


// More Gamma Setting
#define DISP_REG_VIDEO_GM_MUX               (DISP_REG_BASE2 + 0x011C)

// SPI Setting
#define DISP_REG_SPI_IF_EN                  (DISP_REG_BASE2 + 0x0140)
#define DISP_REG_SPI_SETTING_0              (DISP_REG_BASE2 + 0x0144)
#define DISP_REG_SPI_SETTING_1              (DISP_REG_BASE2 + 0x0148)
#define DISP_REG_SPI_SETTING_2              (DISP_REG_BASE2 + 0x014C)

#define DISP_REG_SPI_WAIT_NXT_DATA          (DISP_REG_BASE2 + 0x0150)
#define DISP_REG_BIT_PER_TXB                (DISP_REG_BASE2 + 0x0154)


// EMI Write Setting
#define DISP_REG_EMI_DATA_REMAP             (DISP_REG_BASE2 + 0x0158)
#define DISP_REG_8B_BUS_RE_ORD              (DISP_REG_BASE2 + 0x015C)

#define DISP_REG_MEM_PIN_SHARE              (DISP_REG_BASE2 + 0x0180)
#define DISP_REG_DIS_WCMD_FLUSH             (DISP_REG_BASE2 + 0x0184)
#define DISP_REG_CMD_QU_MARK                (DISP_REG_BASE2 + 0x0188)


// TEAR EFFECT SETTING for multi window : avoid tearing effect relative parameter
#define DISP_REG_TE_RECT_0_CHK_PT_SIZE_H    (DISP_REG_BASE2 + 0x0160)
#define DISP_REG_TE_RECT_0_CHK_PT_SIZE_L    (DISP_REG_BASE2 + 0x0164)
#define DISP_REG_TE_RECT_0_CHK_PT_NO_ST     (DISP_REG_BASE2 + 0x0168)
#define DISP_REG_TE_RECT_0_CHK_PT_NO_END    (DISP_REG_BASE2 + 0x016C)

#define DISP_REG_TE_RECT_1_CHK_PT_SIZE_H    (DISP_REG_BASE2 + 0x0190)
#define DISP_REG_TE_RECT_1_CHK_PT_SIZE_L    (DISP_REG_BASE2 + 0x0194)
#define DISP_REG_TE_RECT_1_CHK_PT_NO_ST     (DISP_REG_BASE2 + 0x0198)
#define DISP_REG_TE_RECT_1_CHK_PT_NO_END    (DISP_REG_BASE2 + 0x019C)

#define DISP_REG_TE_RECT_2_CHK_PT_SIZE_H    (DISP_REG_BASE2 + 0x01A0)
#define DISP_REG_TE_RECT_2_CHK_PT_SIZE_L    (DISP_REG_BASE2 + 0x01A4)
#define DISP_REG_TE_RECT_2_CHK_PT_NO_ST     (DISP_REG_BASE2 + 0x01A8)
#define DISP_REG_TE_RECT_2_CHK_PT_NO_END    (DISP_REG_BASE2 + 0x01AC)

#define DISP_REG_TE_RECT_3_CHK_PT_SIZE_H    (DISP_REG_BASE2 + 0x01B0)
#define DISP_REG_TE_RECT_3_CHK_PT_SIZE_L    (DISP_REG_BASE2 + 0x01B4)
#define DISP_REG_TE_RECT_3_CHK_PT_NO_ST     (DISP_REG_BASE2 + 0x01B8)
#define DISP_REG_TE_RECT_3_CHK_PT_NO_END    (DISP_REG_BASE2 + 0x01BC)


// TO_PAD_INTRA_SKEW_MUX: skew enable and path selection
#define DISP_REG_SKEW_EN_L                  (DISP_REG_BASE2 + 0x01C0)
#define DISP_REG_SKEW_EN_H                  (DISP_REG_BASE2 + 0x01C4)
#define DISP_REG_SKEWWR_EN                  (DISP_REG_BASE2 + 0x01C8) ///
#define DISP_REG_SKEW_D0_D7_SEL             (DISP_REG_BASE2 + 0x01CC)
#define DISP_REG_SKEW_D8_D15_SEL            (DISP_REG_BASE2 + 0x01D0)
#define DISP_REG_SKEW_D16_D17_SEL           (DISP_REG_BASE2 + 0x01D4)
#define DISP_REG_SKEWWR_SEL                 (DISP_REG_BASE2 + 0x01D8) ///


// Misc
#define DISP_REG_NO_NAND_SHARE              (DISP_REG_BASE2 + 0x01E4)


// Debug Register
#define DISP_REG_TOTAL_PIX_CNT              (DISP_REG_BASE2 + 0x01E8)
#define DISP_REG_FRAME_CRC                  (DISP_REG_BASE2 + 0x01EC)
#define DISP_REG_FMARK_CNT                  (DISP_REG_BASE2 + 0x01F0)


// SPARE_REG_DISP1
#define DISP_REG_DISP1_SPARE0               (DISP_REG_BASE + 0x01F8)
#define DISP_REG_DISP1_SPARE_BIT            (DISP_REG_BASE + 0x01FC)


/*--------------------------------------------------------------------------*/
/* MACRO DEFINITION                                                         */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* DATA TYPE DEFINITION                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* VARIABLE DEFINITION                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTION PROTOTYPE DECLARATION AND DEFINITION                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif //__HAL_DISPREG_H__
