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
#ifndef __DRV_DEC_SCL_HVSP_ST_H__
#define __DRV_DEC_SCL_HVSP_ST_H__


#define BYTESIZE 8
//-------------------------------------------------------------------------------------------------
//  Defines & enum
//-------------------------------------------------------------------------------------------------

typedef enum
{
    E_DEC_HVSP_FILTER_MODE_BYPASS,
    E_DEC_HVSP_FILTER_MODE_BILINEAR,
    E_DEC_HVSP_FILTER_MODE_SRAM_0,
    E_DEC_HVSP_FILTER_MODE_SRAM_1,
}EN_DEC_HVSP_FILTER_MODE;


typedef enum
{
    EN_DRV_DEC_VIP_OSD_LOC_AFTER  = 0,    ///< after hvsp
    EN_DRV_DEC_VIP_OSD_LOC_BEFORE = 1,    ///< before hvsp
}EN_DRV_DEC_VIP_OSD_LOC_TYPE;


typedef enum
{
    E_DEC_HVSP_ID_1,
    E_DEC_HVSP_ID_MAX,      //
}EN_DEC_HVSP_ID_TYPE;

typedef enum
{
    E_DEC_HVSP_CMD_TRIG_NONE,           //RIU
    E_DEC_HVSP_CMD_TRIG_POLL_LDC_SYNC,  //polling blanking region RIU
    E_DEC_HVSP_CMD_TRIG_CMDQ_FRMCNT,    //wait framecnt CMDQ
    E_DEC_HVSP_CMD_TRIG_CMDQ_LDC_SYNC,  //used CMDQ in blanking region
    E_DEC_HVSP_CMD_TRIG_MAX,            //HVSP has 4 type to set register,2 RIU,2 CMDQ
}EN_DEC_HVSP_CMD_TRIG_TYPE;
typedef enum
{
    E_HVSP_EVENT_RUN = 0x00000001,
    E_HVSP_EVENT_IRQ = 0x00000002,
} MDrvHVSPTXEvent;

typedef enum
{
    EN_DRV_DEC_HVSP_IQ_H_Tbl0,
    EN_DRV_DEC_HVSP_IQ_H_Tbl1,
    EN_DRV_DEC_HVSP_IQ_H_Tbl2,
    EN_DRV_DEC_HVSP_IQ_H_Tbl3,
    EN_DRV_DEC_HVSP_IQ_H_BYPASS,
    EN_DRV_DEC_HVSP_IQ_H_BILINEAR,
    EN_DRV_DEC_HVSP_IQ_V_Tbl0,
    EN_DRV_DEC_HVSP_IQ_V_Tbl1,
    EN_DRV_DEC_HVSP_IQ_V_Tbl2,
    EN_DRV_DEC_HVSP_IQ_V_Tbl3,
    EN_DRV_DEC_HVSP_IQ_V_BYPASS,
    EN_DRV_DEC_HVSP_IQ_V_BILINEAR,
    EN_DRV_DEC_HVSP_IQ_NUM,
}EN_DRV_DEC_HVSP_IQ_TYPE;


typedef enum
{
    EN_DRV_DEC_VIP_SRAM_DUMP_ICC = 0,
    EN_DRV_DEC_VIP_SRAM_DUMP_IHC,
    EN_DRV_DEC_VIP_SRAM_DUMP_HVSP,
    EN_DRV_DEC_VIP_SRAM_DUMP_HVSP_1,
    EN_DRV_DEC_VIP_SRAM_DUMP_HVSP_2,
    EN_DRV_DEC_VIP_SRAM_DUMP_WDR,
    EN_DRV_DEC_VIP_SRAM_DUMP_GAMMA_Y,
    EN_DRV_DEC_VIP_SRAM_DUMP_GAMMA_U,
    EN_DRV_DEC_VIP_SRAM_DUMP_GAMMA_V,
    EN_DRV_DEC_VIP_SRAM_DUMP_GM10to12_R,
    EN_DRV_DEC_VIP_SRAM_DUMP_GM10to12_G,
    EN_DRV_DEC_VIP_SRAM_DUMP_GM10to12_B,
    EN_DRV_DEC_VIP_SRAM_DUMP_GM12to10_R,
    EN_DRV_DEC_VIP_SRAM_DUMP_GM12to10_G,
    EN_DRV_DEC_VIP_SRAM_DUMP_GM12to10_B,
    EN_DRV_DEC_VIP_SRAM_DUMP_HVSP_V,
    EN_DRV_DEC_VIP_SRAM_DUMP_HVSP_H
}EN_DRV_DEC_VIP_SRAM_DUMP_TYPE;
//-------------------------------------------------------------------------------------------------
//  Structure
//-------------------------------------------------------------------------------------------------

typedef struct
{
    EN_DEC_HVSP_CMD_TRIG_TYPE enType;
    u8             u8Fmcnt;
}ST_DEC_HVSP_CMD_TRIG_CONFIG;

typedef struct
{
    u32 u32RiuBase;
    u32 u32IRQNUM;
    u32 u32CMDQIRQNUM;
}ST_DEC_SCLIRQ_INIT_CONFIG;


typedef struct
{
    u32 u32RIUBase;      // I1 :0x1F000000
    u32 u32IRQNUM;       // scl irq num by device tree
    u32 u32CMDQIRQNUM;   // cmdq irq
}ST_DEC_HVSP_INIT_CONFIG;

typedef struct
{
    u32 u32IRQNUM;
    u32 u32CMDQIRQNUM;   // cmdq irq
}ST_DEC_HVSP_SUSPEND_RESUME_CONFIG;

#if 1

typedef struct clk MsOS_scl_ST_CLK;
typedef struct
{
    MsOS_scl_ST_CLK* idclk; // I1 scl clk 1.idclk(for before crop)
    MsOS_scl_ST_CLK* fclk1; // 2. fclk1(scl main clk)
    MsOS_scl_ST_CLK* fclk2; // 3.fclk2(scl hvsp3 only)
    MsOS_scl_ST_CLK* odclk; // 4.odclk(ttl only )
}ST_DEC_HVSP_CLK_CONFIG;
#endif

typedef struct
{
    u32 u32AffCount;
    u32 u32ISPInCount;
    u32 u32ISPDoneCount;
 
    u32 u32SC3ActiveTime;
    u32 u32SCLMainActiveTime;
    u32 u32ISPTime;
    u32 u32ErrorCount;
    u8 u8CountReset;
}ST_HVSP_SCINTS_TYPE;


#if 0
typedef struct
{
    EN_HVSP_CMD_TRIG_TYPE enType;
    u8             u8Fmcnt;
}ST_HVSP_CMD_TRIG_CONFIG;
#endif

typedef struct
{
    #if 0
    ST_HVSP_CMD_TRIG_CONFIG stCmdTrigCfg;
    #endif
    u16 u16Src_Width;                      // Input source width
    u16 u16Src_Height;                     // Input source height
   
    u16 u16Dsp_Width;                      // After scl display width
    u16 u16Dsp_Height;                     // After scl display height

    bool bScl_H_Bypass;
    bool bScl_V_Bypass;
}ST_DEC_HVSP_SCALING_CONFIG;

typedef struct
{
    bool bSet;
    u16 u16Width;
    u16 u16Height;
}ST_DEC_HVSP_SIZE_CONFIG;

typedef struct
{
    ST_DEC_HVSP_SIZE_CONFIG stSizeBeforeScaling;
    ST_DEC_HVSP_SIZE_CONFIG stSizeAfterScaling;
    u32              u32ScalingRatio_H;
    u32              u32ScalingRatio_V;
}ST_DEC_HVSP_SCALING_INFO;

typedef struct
{
    unsigned short u16X;            //isp crop x
    unsigned short u16Y;            // isp crop y
    unsigned short u16Width;        // display width
    unsigned short u16Height;       // display height
    unsigned char  bEn;             //crop En
}ST_DRV_DEC_HVSP_SCINFORM_CONFIG;
typedef struct
{
    unsigned short u16Width;        // display width
    unsigned short u16Height;       // display height
    unsigned short u16inWidth; // after hvsp width
    unsigned short u16inHeight;// after hvsp height
    unsigned char  bEn;             //function En
}ST_DRV_DEC_HVSP_HVSPINFORM_CONFIG;




//-------------------------------------------------------------------------------------------------
//  Prototype
//-------------------------------------------------------------------------------------------------

#endif
