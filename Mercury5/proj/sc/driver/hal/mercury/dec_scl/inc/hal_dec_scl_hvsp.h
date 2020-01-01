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
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
#ifndef __HAL_SCL_HVSP_H__
#define __HAL_SCL_HVSP_H__


//-------------------------------------------------------------------------------------------------
//  Defines & ENUM
//-------------------------------------------------------------------------------------------------

typedef enum
{
    E_DEC_HVSP_SRAM_SEL_0,
    E_DEC_HVSP_SRAM_SEL_1,
}EN_DEC_HVSP_SRAM_SEL_TYPE;

typedef enum
{
    E_DEC_HVSP_FILTER_SRAM_SEL_1,
    E_DEC_HVSP_FILTER_SRAM_SEL_2,
    E_DEC_HVSP_FILTER_SRAM_SEL_3,
    E_DEC_HVSP_FILTER_SRAM_SEL_4,
}EN_DEC_HVSP_FILTER_SRAM_SEL_TYPE;

typedef enum
{
    EN_DEC_HVSP_CLKATTR_ISP=0x10,
    EN_DEC_HVSP_CLKATTR_BT656=0x20,
    EN_DEC_HVSP_CLKATTR_FORCEMODE=0x40,
}EN_DEC_HVSP_CLKATTR_TYPE;


typedef enum
{
    EN_DEC_VIP_SRAM_DUMP_ICC = 0,
    EN_DEC_VIP_SRAM_DUMP_IHC,
    EN_DEC_VIP_SRAM_DUMP_HVSP,
    EN_DEC_VIP_SRAM_DUMP_HVSP_1,
    EN_DEC_VIP_SRAM_DUMP_HVSP_2,
    EN_DEC_VIP_SRAM_DUMP_WDR,
    EN_DEC_VIP_SRAM_DUMP_GAMMA_Y,
    EN_DEC_VIP_SRAM_DUMP_GAMMA_U,
    EN_DEC_VIP_SRAM_DUMP_GAMMA_V,
    EN_DEC_VIP_SRAM_DUMP_GM10to12_R,
    EN_DEC_VIP_SRAM_DUMP_GM10to12_G,
    EN_DEC_VIP_SRAM_DUMP_GM10to12_B,
    EN_DEC_VIP_SRAM_DUMP_GM12to10_R,
    EN_DEC_VIP_SRAM_DUMP_GM12to10_G,
    EN_DEC_VIP_SRAM_DUMP_GM12to10_B,
    EN_DEC_VIP_SRAM_DUMP_HVSP_V,
    EN_DEC_VIP_SRAM_DUMP_HVSP_H
}EN_DEC_VIP_SRAM_DUMP_TYPE;
//-------------------------------------------------------------------------------------------------
//  Structure
//-------------------------------------------------------------------------------------------------

typedef struct
{
    bool bEn;
    u16  u16In_hsize;
    u16  u16In_vsize;
    u16  u16Hst;
    u16  u16Hsize;
    u16  u16Vst;
    u16  u16Vsize;
}ST_HVSP_CROP_INFO;


//-------------------------------------------------------------------------------------------------
//  Prototype
//-------------------------------------------------------------------------------------------------

#ifndef HAL_HVSP_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

INTERFACE void Hal_DEC_HVSP_SetRiuBase(u32 u32RiuBase);

INTERFACE void Hal_DEC_HVSP_Set_Reset(void);
INTERFACE void Hal_DEC_HVSP_Set_CLKOFF(void);
INTERFACE void Hal_DEC_HVSP_Set_SW_Reset(bool bEn);

// NLM
INTERFACE void Hal_DEC_HVSP_SetVIPSize(u16 u16Width, u16 u16Height);


// Scaling
INTERFACE void Hal_DEC_HVSP_SetScalingVeEn(EN_DEC_HVSP_ID_TYPE enID, bool ben);
INTERFACE void Hal_DEC_HVSP_SetScalingVeFactor(EN_DEC_HVSP_ID_TYPE enID, u32 u32Ratio);
INTERFACE void Hal_DEC_HVSP_SetScalingHoEn(EN_DEC_HVSP_ID_TYPE enID, bool ben);
INTERFACE void Hal_DEC_HVSP_SetScalingHoFacotr(EN_DEC_HVSP_ID_TYPE enID, u32 u32Ratio);
INTERFACE void Hal_DEC_HVSP_SetModeYHo(EN_DEC_HVSP_ID_TYPE enID, EN_DEC_HVSP_FILTER_MODE enFilterMode);
INTERFACE void Hal_DEC_HVSP_SetModeYVe(EN_DEC_HVSP_ID_TYPE enID, EN_DEC_HVSP_FILTER_MODE enFilterMode);
INTERFACE void Hal_DEC_HVSP_SetModeCHo(EN_DEC_HVSP_ID_TYPE enID, EN_DEC_HVSP_FILTER_MODE enFilterMode, EN_DEC_HVSP_SRAM_SEL_TYPE enSramSel);
INTERFACE void Hal_DEC_HVSP_SetModeCVe(EN_DEC_HVSP_ID_TYPE enID, EN_DEC_HVSP_FILTER_MODE enFilterMode, EN_DEC_HVSP_SRAM_SEL_TYPE enSramSel);
INTERFACE void Hal_DEC_HVSP_SetHspDithEn(EN_DEC_HVSP_ID_TYPE enID, bool bEn);
INTERFACE void Hal_DEC_HVSP_SetVspDithEn(EN_DEC_HVSP_ID_TYPE enID, bool bEn);
INTERFACE void Hal_DEC_HVSP_SetHspCoringEnC(EN_DEC_HVSP_ID_TYPE enID, bool bEn);
INTERFACE void Hal_DEC_HVSP_SetHspCoringEnY(EN_DEC_HVSP_ID_TYPE enID, bool bEn);
INTERFACE void Hal_DEC_HVSP_SetVspCoringEnC(EN_DEC_HVSP_ID_TYPE enID, bool bEn);
INTERFACE void Hal_DEC_HVSP_SetVspCoringEnY(EN_DEC_HVSP_ID_TYPE enID, bool bEn);
INTERFACE void Hal_DEC_HVSP_SetHspCoringThrdC(EN_DEC_HVSP_ID_TYPE enID, u16 u16Thread);
INTERFACE void Hal_DEC_HVSP_SetHspCoringThrdY(EN_DEC_HVSP_ID_TYPE enID, u16 u16Thread);
INTERFACE void Hal_DEC_HVSP_SetVspCoringThrdC(EN_DEC_HVSP_ID_TYPE enID, u16 u16Thread);
INTERFACE void Hal_DEC_HVSP_SetVspCoringThrdY(EN_DEC_HVSP_ID_TYPE enID, u16 u16Thread);
INTERFACE void Hal_DEC_HVSP_Set_Sram_Coeff(EN_DEC_HVSP_ID_TYPE enID, EN_DEC_HVSP_FILTER_SRAM_SEL_TYPE enSramSel, bool bC_SRAM, u8 *pData);
INTERFACE void Hal_DEC_HVSP_SetHVSPInputSize(EN_DEC_HVSP_ID_TYPE enID, u16 u16Width, u16 u16Height);
INTERFACE void Hal_DEC_HVSP_SetHVSPOutputSize(EN_DEC_HVSP_ID_TYPE enID, u16 u16Width, u16 u16Height);

// REG W
INTERFACE void Hal_DEC_HVSP_Set_Reg(u32 u32Reg, u8 u8Val, u8 u8Mask);

// CMD buffer
INTERFACE void Hal_DEC_HVSP_SetResetFclk(bool bEn);



#if 0
INTERFACE void Hal_DEC_HVSP_SetIdclkOnOff(bool bEn,ST_DEC_HVSP_CLK_CONFIG* stclk);
INTERFACE void Hal_DEC_HVSP_FCLK1(ST_DEC_HVSP_CLK_CONFIG *stclk);
INTERFACE void Hal_DEC_HVSP_FCLK2(ST_DEC_HVSP_CLK_CONFIG *stclk);
#endif

INTERFACE u16 Hal_DEC_HVSP_GetHVSPOutputHeight(EN_DEC_HVSP_ID_TYPE enID);
INTERFACE u16 Hal_DEC_HVSP_GetHVSPOutputHeightCount(EN_DEC_HVSP_ID_TYPE enID);
INTERFACE u16 Hal_DEC_HVSP_GetScalingFunctionStatus(EN_DEC_HVSP_ID_TYPE enID);
INTERFACE u16 Hal_DEC_HVSP_GetHVSPInputHeight(EN_DEC_HVSP_ID_TYPE enID);
INTERFACE u16 Hal_DEC_HVSP_GetHVSPInputWidth(EN_DEC_HVSP_ID_TYPE enID);

INTERFACE u16 Hal_DEC_HVSP_GetHVSPOutputWidth(EN_DEC_HVSP_ID_TYPE enID);
INTERFACE void Hal_DEC_HVSP_SetCLKRate(unsigned char u8Idx);


INTERFACE void Hal_DEC_VIP_SRAM_Dump(EN_DEC_VIP_SRAM_DUMP_TYPE endump,u32 u32Sram);
INTERFACE u16 Hal_DEC_HVSP_Get_2ByteReg(u32 u32Reg);
INTERFACE void Hal_DEC_HVSP_Set_2ByteReg(u32 u32Reg, u16 u16Val, u16 u16Mask);

#undef INTERFACE


#endif
