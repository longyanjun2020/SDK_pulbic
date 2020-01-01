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
/// @file   drvHVD_sub.h
/// @brief  SubHVD Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_HVD_SUB_H_
#define _DRV_HVD_SUB_H_

#ifdef __cplusplus
extern "C"
{
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
void MDrv_HVD_Sub_PowerCtrl( MS_BOOL bEnable );
void MDrv_HVD_Sub_SetOSRegBase( MS_U32 u32RegBaseAddr );
HVD_Result MDrv_HVD_Sub_Init(HVD_MemCfg *pStMemCfg, HVD_Init_Settings *pStInitSettings);
HVD_Result MDrv_HVD_Sub_Rst(MS_BOOL bErrHandle);
HVD_Result MDrv_HVD_Sub_Play(void);
HVD_Result MDrv_HVD_Sub_Exit(void);
HVD_Result MDrv_HVD_Sub_Pause(void);
HVD_Result MDrv_HVD_Sub_Flush( MS_BOOL bShowLast);
HVD_Result MDrv_HVD_Sub_StepDisp( void);
HVD_Result MDrv_HVD_Sub_StepDecode(void);
HVD_Result MDrv_HVD_Sub_PushQueue(HVD_Packet_Info* pInfo);
HVD_Result MDrv_HVD_Sub_PushQueue_Fire(void);
HVD_Result MDrv_HVD_Sub_DecodeIFrame(MS_PHYADDR u32SrcSt , MS_U32 u32SrcSize);

HVD_Result MDrv_HVD_Sub_SetDataEnd( MS_BOOL bEnd );
HVD_Result MDrv_HVD_Sub_SetDispErrFrm(MS_BOOL bEnable);
HVD_Result MDrv_HVD_Sub_SetDispRepeatField(MS_BOOL bEnable);
HVD_Result MDrv_HVD_Sub_SetSkipDecMode(HVD_Skip_Decode eDecType);
HVD_Result MDrv_HVD_Sub_SetDispSpeed(HVD_Drv_Disp_Speed eSpeed);
HVD_Result MDrv_HVD_Sub_SetSyncActive( MS_BOOL bEnable);
HVD_Result MDrv_HVD_Sub_SetDropMode( HVD_Drop_Disp eMode , MS_U32 u32Arg);
HVD_Result MDrv_HVD_Sub_RstPTS(MS_U32 u32PTS);
HVD_Result MDrv_HVD_Sub_SetFrcMode(HVD_FrmRateConv_Mode eMode );
HVD_Result MDrv_HVD_Sub_SetSyncTolerance(MS_U32 u32Arg );
HVD_Result MDrv_HVD_Sub_SetSyncVideoDelay( MS_U32 u32Arg);
HVD_Result MDrv_HVD_Sub_SetSyncFreeRunTH(MS_U32 u32Arg );
HVD_Result MDrv_HVD_Sub_SetSyncRepeatTH( MS_U32 u32Arg);
HVD_Result MDrv_HVD_Sub_SetErrConceal(MS_BOOL u32Arg );
void MDrv_HVD_Sub_SetDbgLevel( HVD_Uart_Level elevel );
HVD_Result MDrv_HVD_Sub_SeekToPTS(MS_U32 u32PTS );
HVD_Result MDrv_HVD_Sub_SkipToPTS(MS_U32 u32PTS );
HVD_Result MDrv_HVD_Sub_SetFreezeImg(MS_BOOL bEnable );
HVD_Result MDrv_HVD_Sub_SetBlueScreen(MS_BOOL bEnable );
HVD_Result MDrv_HVD_Sub_SetDispOneField(MS_BOOL bEnable );
HVD_Result MDrv_HVD_Sub_SetISREvent(MS_U32 u32Event, HVD_InterruptCb fnISRHandler );
MS_BOOL MDrv_HVD_Sub_SetEnableISR(MS_BOOL bEnable);
MS_BOOL MDrv_HVD_Sub_SetForceISR(MS_BOOL bEnable);
MS_BOOL MDrv_HVD_Sub_SetMVOPDone(void);
HVD_Result MDrv_HVD_Sub_SetVirtualBox(MS_U16 u16Width, MS_U16 u16Height);
HVD_Result MDrv_HVD_Sub_SetDynScalingParam(  void *pStAddr , MS_U32 u32Size );
HVD_Result MDrv_HVD_Sub_SetAutoRmLstZeroByte(MS_BOOL bOn);
HVD_Result MDrv_HVD_Sub_SetDispInfoTH(HVD_Disp_Info_Threshold* DispInfoTH );

MS_BOOL MDrv_HVD_Sub_IsISROccured(void);
MS_BOOL MDrv_HVD_Sub_IsDispFinish(void);
MS_BOOL MDrv_HVD_Sub_IsFrameShowed(void);
MS_BOOL MDrv_HVD_Sub_IsStepDecodeDone(void);
HVD_Result MDrv_HVD_Sub_CheckDispInfoRdy(void);
MS_BOOL MDrv_HVD_Sub_IsDispInfoChg(void);
MS_BOOL MDrv_HVD_Sub_IsIdle(void);
MS_BOOL MDrv_HVD_Sub_IsSyncStart(void);
MS_BOOL MDrv_HVD_Sub_IsSyncReach(void);
MS_BOOL MDrv_HVD_Sub_IsLowDelay(void);
MS_BOOL MDrv_HVD_Sub_IsIFrmFound(void);
MS_BOOL MDrv_HVD_Sub_Is1stFrmRdy(void);
MS_BOOL MDrv_HVD_Sub_IsAllBufferEmpty(void);
HVD_Result MDrv_HVD_Sub_IsAlive(void);

MS_U32 MDrv_HVD_Sub_GetBBUVacancy(void);
HVD_Result MDrv_HVD_Sub_GetDispInfo( HVD_Disp_Info *pinfo );
MS_U32 MDrv_HVD_Sub_GetPTS(void);
MS_U32 MDrv_HVD_Sub_GetNextPTS(void);
MS_U32 MDrv_HVD_Sub_GetDataErrCnt(void);
MS_U32 MDrv_HVD_Sub_GetDecErrCnt(void);
MS_U32 MDrv_HVD_Sub_GetESWritePtr(void);
MS_U32 MDrv_HVD_Sub_GetESReadPtr(void);
MS_BOOL MDrv_HVD_Sub_GetCaps( HVD_Codec u32Type);
MS_U32 MDrv_HVD_Sub_GetErrCode(void);
MS_U32 MDrv_HVD_Sub_GetPlayMode(HVD_Get_Mode_Status eMode);
HVD_Get_Play_State MDrv_HVD_Sub_GetPlayState(void);
MS_U32 MDrv_HVD_Sub_GetDecodeCnt(void);
MS_U8 MDrv_HVD_Sub_GetActiveFormat(void);
const HVD_DrvInfo* MDrv_HVD_Sub_GetInfo( void );
MS_BOOL MDrv_HVD_Sub_GetStatus( HVD_DrvStatus *pstatus);
HVD_Result MDrv_HVD_Sub_GetFrmInfo( HVD_Get_Frm_Info_Type eType  ,  HVD_Frame_Info *pInfo);
MS_BOOL MDrv_HVD_Sub_GetISRInfo( MS_U32* eType );
MS_U32 MDrv_HVD_Sub_CalLumaSum(  HVD_Get_Frm_Info_Type eType  );
MS_U32 MDrv_HVD_Sub_GetUserData_Wptr( void );
MS_U32 MDrv_HVD_Sub_GetUserData_Packet( MS_U32 u32Idx , MS_U32* u32Size );
HVD_Result MDrv_HVD_Sub_GenPattern( HVD_PatternType eType ,  MS_U32 u32VAddr  ,  MS_U32* u32Size  );
MS_U32 MDrv_HVD_Sub_GetPatternInfo(   HVD_Pattern_Info eType );
MS_U32 MDrv_HVD_Sub_GetDynamicScalingInfo(   HVD_DynamicScaling_Info eType );

MS_U32 MDrv_HVD_Sub_GetData(HVD_GData_Type eType);
MS_U32 MDrv_HVD_Sub_GetMem_Dbg(MS_U32 u32Addr);
void MDrv_HVD_Sub_DbgDumpStatus(HVD_DumpStatus eFlag);
void MDrv_HVD_Sub_SetMem_Dbg(MS_U32 u32Addr , MS_U32 u32Arg);
HVD_Result MDrv_HVD_Sub_SetCmd_Dbg( MS_U32 u32Cmd , MS_U32 u32Arg);
HVD_Result MDrv_HVD_Sub_SetSettings_Pro( HVD_SSettings_Type eType , MS_U32 u32Arg);
HVD_Result MDrv_HVD_Sub_SetBalanceBW(MS_U8 qp_cnt, MS_U8 db_cnt, MS_U8 upper);

#ifdef __cplusplus
}
#endif

#endif // _DRV_HVD_SUB_H_

