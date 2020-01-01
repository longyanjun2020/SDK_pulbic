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
/// @file   halNJPD.h
/// @brief  NJPD hal interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _HAL_NJPD_H_
#define _HAL_NJPD_H_

//-------------------------------------------------------------------------------------------------
//  Enumeration
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Structure
//-------------------------------------------------------------------------------------------------

typedef struct
{
    MS_U8* pu8HalVer;
    MS_U8* pu8FwVer;
} NJPD_HAL_Version;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

void HAL_NJPD_SetMIU(MS_U8 u8Idx);
void HAL_NJPD_JPDSelect(MS_BOOL bNJPD);

void HAL_NJPD_Set_GlobalSetting00(MS_U16 u16Value);
MS_U16 HAL_NJPD_Get_GlobalSetting00(void);
void HAL_NJPD_Set_GlobalSetting01(MS_U16 u16Value);
MS_U16 HAL_NJPD_Get_GlobalSetting01(void);
void HAL_NJPD_Set_GlobalSetting02(MS_U16 u16Value);
MS_U16 HAL_NJPD_Get_GlobalSetting02(void);

void HAL_NJPD_SetMRCBuf0_StartLow(MS_U16 u16Value);
void HAL_NJPD_SetMRCBuf0_StartHigh(MS_U16 u16Value);
void HAL_NJPD_SetMRCBuf0_EndLow(MS_U16 u16Value);
void HAL_NJPD_SetMRCBuf0_EndHigh(MS_U16 u16Value);
void HAL_NJPD_SetMRCBuf1_StartLow(MS_U16 u16Value);
void HAL_NJPD_SetMRCBuf1_StartHigh(MS_U16 u16Value);
void HAL_NJPD_SetMRCBuf1_EndLow(MS_U16 u16Value);
void HAL_NJPD_SetMRCBuf1_EndHigh(MS_U16 u16Value);
void HAL_NJPD_SetMRCStartOffset_Low(MS_U16 u16Value);
void HAL_NJPD_SetMRCStartOffset_High(MS_U16 u16Value);
MS_U32 HAL_NJPD_GetCurMRCAddr(void);

MS_U16 HAL_NJPD_GetMWCBuf_StartLow(void);
MS_U16 HAL_NJPD_GetMWCBuf_StartHigh(void);
MS_U16 HAL_NJPD_GetMWCBuf_WritePtrLow(void);
MS_U16 HAL_NJPD_GetMWCBuf_WritePtrHigh(void);
void HAL_NJPD_SetMWCBuf_StartLow(MS_U16 u16Value);
void HAL_NJPD_SetMWCBuf_StartHigh(MS_U16 u16Value);

void HAL_NJPD_ClearEventFlag(MS_U16 u16Value);
void HAL_NJPD_ForceEventFlag(MS_U16 u16Value);
void HAL_NJPD_MaskEventFlag(MS_U16 u16Value);
void HAL_NJPD_UnMaskEventFlag(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetEventFlag(void);

void HAL_NJPD_EnableISR(void);
void HAL_NJPD_DisableISR(void);
void HAL_NJPD_RegisterISRCallBackFunc(int ulEventId, void* pfCBFunc, int ulCBArg);

void HAL_NJPD_SetPic_H(MS_U16 u16Value);
void HAL_NJPD_SetPic_V(MS_U16 u16Value);
void HAL_NJPD_SetROI_H(MS_U16 u16Value);
void HAL_NJPD_SetROI_V(MS_U16 u16Value);
void HAL_NJPD_SetROIWidth(MS_U16 u16Value);
void HAL_NJPD_SetROIHeight(MS_U16 u16Value);

void HAL_NJPD_SetAutoProtect(MS_BOOL enable);
void HAL_NJPD_SetWPENUBound_0_L(MS_U16 u16Value);
void HAL_NJPD_SetWPENUBound_0_H(MS_U16 u16Value);
void HAL_NJPD_SetWPENLBound_0_L(MS_U16 u16Value);
void HAL_NJPD_SetWPENLBound_0_H(MS_U16 u16Value);

void HAL_NJPD_SetClock(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetClock(void);
void HAL_NJPD_SetClockGate(MS_U16 u16Value);
void HAL_NJPD_PowerOn(void);
void HAL_NJPD_PowerOff(void);

void HAL_NJPD_CreateMutex(void);
void HAL_NJPD_DeleteMutex(void);

void HAL_NJPD_SetMRBurstThd(MS_U16 u16Value);
void HAL_NJPD_Set_MARB06(MS_U16 u16Value);
MS_U16 HAL_NJPD_Get_MARB06(void);
void HAL_NJPD_Set_MARB07(MS_U16 u16Value);
MS_U16 HAL_NJPD_Get_MARB07(void);

void HAL_NJPD_SetSpare00(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetSpare00(void);
void HAL_NJPD_SetSpare01(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetSpare01(void);
void HAL_NJPD_SetSpare02(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetSpare02(void);
void HAL_NJPD_SetSpare03(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetSpare03(void);
void HAL_NJPD_SetSpare04(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetSpare04(void);
void HAL_NJPD_SetSpare05(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetSpare05(void);
void HAL_NJPD_SetSpare06(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetSpare06(void);
void HAL_NJPD_SetSpare07(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetSpare07(void);

void HAL_NJPD_SetWriteOneClearReg(MS_U16 u16Value);
void HAL_NJPD_SetWriteOneClearReg_2(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetWriteOneClearReg(void);

void HAL_NJPD_SetHTableStart_Low(MS_U16 u16Value);
void HAL_NJPD_SetHTableStart_High(MS_U16 u16Value);
void HAL_NJPD_SetQTableStart_Low(MS_U16 u16Value);
void HAL_NJPD_SetQTableStart_High(MS_U16 u16Value);
void HAL_NJPD_SetGTableStart_Low(MS_U16 u16Value);
void HAL_NJPD_SetGTableStart_High(MS_U16 u16Value);
void HAL_NJPD_SetHTableSize(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetHTableSize(void);

void HAL_NJPD_InitRegBase(void);
void HAL_NJPD_SetRSTIntv(MS_U16 u16Value);
void HAL_NJPD_GetLibVer(NJPD_HAL_Version *pHalVer);
void HAL_NJPD_Rst(void);
MS_U16 HAL_NJPD_GetCurRow(void);
MS_U16 HAL_NJPD_GetCurCol(void);
void HAL_NJPD_SetRIUInterface(MS_U16 u16Value);
MS_U16 HAL_NJPD_GetRIUInterface(void);
MS_U16 HAL_NJPD_TBCReadData_L(void);
MS_U16 HAL_NJPD_TBCReadData_H(void);
void HAL_NJPD_SetIBufReadLength(MS_U8 u8Min, MS_U8 u8Max);
void HAL_NJPD_SetCRCReadMode(void);
void HAL_NJPD_SetCRCWriteMode(void);
MS_U8 HAL_NJPD_GetHandshakeCnt(void);
void HAL_NJPD_Handshake_SWRowCountMode(MS_U8 u8Cnt);
void HAL_NJPD_Handshake_HWRowCountMode(void);
void HAL_NJPD_SetOutputFormat(MS_BOOL bRst, NJPD_OutputFormat eOutputFormat);
void HAL_NJPD_SetMTLBMode(MS_U8 u8MTLB);
void HAL_NJPD_SetNJPDInstance(NJPD_Number JPDNum);

void HAL_NJPD_SetVerificationMode(NJPD_VerificationMode VerificationMode);
NJPD_VerificationMode HAL_NJPD_GetVerificationMode(void);
void HAL_NJPD_DebugReg(void);
void HAL_NJPD_Debug(void);

#endif // _HAL_NJPD_H_

