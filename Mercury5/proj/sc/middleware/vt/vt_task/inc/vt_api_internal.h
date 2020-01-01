////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
* @file    vt_api_internal.h
* @version
* @brief   APIs used internally in 3g324mTask.
*
*/
#ifndef __VT_API_INTERNAL_H__
#define __VT_API_INTERNAL_H__

#include "vt_types.h"

#define VT_MUX_OFFSET 5

//324M-MMI
bool VtCallStateInd(VtCallState_e CallState);
bool VtUserInputDTMFCnf(VtResultCode_e result);
RvStatus VtLoopbackMsgIdentHandle(void);
RvStatus VtLoopbackTimerHandle(void);
RvStatus VtLoopbackMsgTypeHandle(VtLoopbackState_e VtloopbackState);
bool VtLoopbackCnf(VtResultCode_e result);
u32 VtLoopSetChannelOnOff(VtChannelOnOffState_e channelonoffstate, VtChannelType_e channeltype );

//324M-CM
void VtSetChannelNum(u32 ChannelNum);
void VtSetMuxFcmChNum(u32 ChannelNum);
u32 VtGetMuxFcmChNum(void);
bool VtCmGetChNumReq(void);
bool VtCmOpenConnectionCnf(RESULT_e result);
bool VtCmCloseConnectionInd(void);

//324M-MUX
bool VtOpenMuxReq(void);
bool VtMuxSendOpenFlowInd(void);
bool VtMuxSendCloseFlowInd(void);
void VtSendMuxPdu(u8 *pBuff, u16 Length);
bool VtFcmRelease(void);
void VtSetFcmState(VtFcmState_e state);
bool VtFcmStateIsOpened(void);

//Others
char* VtGetFilename(const char* name);
bool VtTimerSendWithPrio(VtMsgType_e type);
bool VtTestDialReq(ascii* num);
void VtSetMediaGate(u32 on);
u32 VtCheckMediaGate(void);
void VtPrint2String(u32 dbg_level, char *str1, char *str2);

#if VT_LOOPBACK_CHECK_VT_INFO

int VtUpdateMediaTimeInfo( void *pVtMediaInfo, u16 size, u16 type, VT_Call_Statement_e tpath );
int VtUpdateInfoPeriodical( void *pVtMediaInfo, VT_Call_Statement_e tpath );
int VtCheckLostFrame(void *pVtMediaInfo, u16 sequenceNumber, u16 type, VT_Call_Statement_e tpath );

#endif //VT_LOOPBACK_CHECK_VT_INFO
    
#endif

