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

#ifndef _HAL_HVD_H_
#define _HAL_HVD_H_

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
// Feature
#define HAL_HVD_ENABLE_MUTEX_PROTECT    HVD_ENABLE_MUTEX_PROTECT
#define HAL_HVD_ENABLE_MIU_PROTECT      HVD_ENABLE_MIU_RST_PROTECT
#define HAL_HVD_ENABLE_VPU_CMD    1

// MBox type of FW cmd
#if (HAL_HVD_ENABLE_VPU_CMD)
    #define HAL_HVD_CMD_MBOX            E_HVD_VPU_HI_0
    #define HAL_HVD_CMD_ARG_MBOX        E_HVD_VPU_HI_1
#else
    #define HAL_HVD_CMD_MBOX            E_HVD_HI_0
    #define HAL_HVD_CMD_ARG_MBOX        E_HVD_HI_1
#endif
// MBox other usages
#define HAL_HVD_REG_ISR_VPU     E_HVD_VPU_RISC_1
#define HAL_HVD_REG_FW_STATE    E_HVD_RISC_0
#define HAL_HVD_REG_ISR_HVD     E_HVD_RISC_1
#define HAL_HVD_REG_DISP_INFO_COPYED    E_HVD_RISC_1
#define HAL_HVD_REG_DISP_INFO_CHANGE    E_HVD_RISC_1
#define HAL_HVD_REG_DISP_CTL    E_HVD_HI_0

#if defined(CHIP_T3)
// patch for HW bug
#define HVD_MIU1_BASE_ADDRESS   0x08000000UL//0x10000000UL
#else // CHIP_U3
#define HVD_MIU1_BASE_ADDRESS   0x08000000UL
#endif

#define HVD_RV_BROKENBYUS_BIT    29

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

typedef enum
{
    E_HVD_HI_0,
    E_HVD_HI_1,
    E_HVD_RISC_0,
    E_HVD_RISC_1,
    E_HVD_VPU_HI_0,
    E_HVD_VPU_HI_1,
    E_HVD_VPU_RISC_0,
    E_HVD_VPU_RISC_1,
} HVD_MBOX_TYPE;

typedef enum
{
    E_HAL_HVD_CLOCK_SPEED_NONE = 0,
    E_HAL_HVD_CLOCK_SPEED_HIGHEST,
    E_HAL_HVD_CLOCK_SPEED_HIGH,
    E_HAL_HVD_CLOCK_SPEED_MEDIUM,
    E_HAL_HVD_CLOCK_SPEED_LOW,
    E_HAL_HVD_CLOCK_SPEED_LOWEST,
    E_HAL_HVD_CLOCK_SPEED_DEFAULT,
} HAL_HVD_ClockSpeed;

typedef struct
{
    MS_U32 u32WritePtr;
    MS_U32 u32OffsetCnt;
} HVD_PTS_Table_Ctrl;

typedef struct
{
    MS_U32 u32PTS;
    MS_U32 u32OffsetCnt;
    MS_U32 u32ID_L;
    MS_U32 u32ID_H;
} HVD_PTS_Table_Entry;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
void        HAL_HVD_FlushMemory(void);
void        HAL_HVD_ReadMemory(void);
void        HAL_HVD_CheckMIUSel(MS_BOOL bChange);
MS_U32      HAL_HVD_Get_HWVersionID(void);
void        HAL_HVD_PowerCtrl(MS_BOOL bEnable);
void        HAL_HVD_InitRegBase(MS_U32 u32RegBase);
void        HAL_HVD_SetPreCtrlVariables(MS_U32 drvprectrl);
HVD_Return  HAL_HVD_InitVariables(MS_U32 drvctrl);
HVD_Return  HAL_HVD_InitShareMem(void);
HVD_Return  HAL_HVD_InitRegCPU(void);
HVD_Return  HAL_HVD_SetData(HVD_SetData u32type, MS_U32 u32Data);
MS_U32      HAL_HVD_GetData(HVD_GetData eType);
MS_S64 		HAL_HVD_GetData_EX(HVD_GetData eType);
HVD_Return  HAL_HVD_SetCmd(HVD_User_Cmd eUsrCmd, MS_U32 u32CmdArg);
HVD_Return  HAL_HVD_DeInit(void);
HVD_Return  HAL_HVD_PushPacket(HVD_BBU_Info *pInfo);
void        HAL_HVD_EnableISR(MS_BOOL bEnable);
void        HAL_HVD_SetForceISR(MS_BOOL bEnable);
void        HAL_HVD_SetClearISR(void);
MS_BOOL     HAL_HVD_IsISROccured(void);
MS_BOOL     HAL_HVD_IsEnableISR(void);
MS_BOOL     HAL_HVD_IsAlive(void);
MS_BOOL     HAL_HVD_RstPTSCtrlVariable(void);
MS_BOOL     HAL_HVD_FlushRstShareMem(void);
void        HAL_HVD_UartSwitch2FW(MS_BOOL bEnable);
MS_U32      HAL_HVD_GetData_Dbg(MS_U32 u32Addr);
void        HAL_HVD_SetData_Dbg(MS_U32 u32Addr, MS_U32 u32Data);
MS_U16      HAL_HVD_GetCorretClock(MS_U16 u16Clock);
HVD_Return  HAL_HVD_SetClockSpeed(HAL_HVD_ClockSpeed eClockSpeed);
void        HAL_HVD_UpdateESWptr_Fire(void);
void        HAL_HVD_MVD_PowerCtrl(MS_BOOL bEnable);
void        HAL_HVD_Dump_FW_Status(void);
void        HAL_HVD_Dump_HW_Status(MS_U32 numb);
void        HAL_HVD_SetMiuBurstLevel(HVD_MIU_Burst_Cnt_Ctrl eMiuBurstCntCtrl);
MS_BOOL     HAL_HVD_GetFrmRateIsSupported(MS_U16 u16HSize, MS_U16 u16VSize, MS_U32 u32FrmRate);
MS_U32      HAL_HVD_GetEVDHWBuffer(void);
void        HAL_HVD_SetHwRegBase(MS_U32 u32ModeFlag);

#endif // _HAL_HVD_H_

