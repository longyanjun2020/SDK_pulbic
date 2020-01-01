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
* @file    vt_api.h
* @version
* @brief   APIs
*
*/
#ifndef __VT_API_H__
#define __VT_API_H__

#include "vt_types.h"
#include "sys_MsWrapper_cus_os_mem.h"

void vt_init(void);
void vt_3g324mTask(vm_msg_t *pMessage);
bool VtCallDropReq(void);
bool VtUserInputDTMFReq(char digit);
bool VtLoopbackReq(VtLoopbackState_e state);
u32 VtGetChannelNum(void);
bool VtChannelOnOffInd(VtChannelOnOffState_e channelonoffstate, VtChannelType_e channeltype );
bool VtChannelOnOffReq(VtChannelOnOffState_e channelonoffstate, VtChannelType_e channeltype, VtChannelNotifyRemote_e notify );
bool VtCallFCMCloseFlowINDReq(void);

void Video_Fast_Update_CallbackAttach(VT_VIDEO_FAST_UPDATE_CALLBACK nCallbackAdr);
void Video_Fast_Update_CallbackDisable(void);

void Video_SendVideoFastUpdate_CallbackAttach(VT_REQ_VIDEO_FAST_UPDATE_CALLBACK nCallbackAdr);
void Video_SendVideoFastUpdate_CallbackDisable(void);

void Video_TSTO_CMD_CallbackAttach(VT_TSTO_CMD_CALLBACK nCallbackAdr);
void Video_TSTO_CMD_CallbackDisable(void);

RvBool VT_Request_LocalCMD(char *VtReqMsg, int VtSendIdx, void *usrData);
RvBool VT_Request_RemoteCMD(char *VtReqMsg, int VtSendIdx, void *usrData);

short VT_RvVTGets(u8 *buffer, u32 size, void *file_ptr);
void VT_DUMP1(u8 *puData, u32 uLen, VtStackDumpType_e type);
void VT_DUMP2(u8 *puData, u32 uLen, VtStackDumpType_e type);

long long mdl_vt_stack_get_current_time(void);
void mdl_vt_stack_reset_timer(void);

void MdlVt_SetTestStackMode (int mode);
unsigned char MdlVt_GetTestStackMode (void);
void MdlVt_SetTestStackDumpBitStream (int mode);
unsigned char MdlVt_GetTestStackDumpBitStream (void);

void mdl_vt_stack_resetlogfile(void);
int mdl_vt_stack_initlog_bitstream(void);
int mdl_vt_stack_finalizelogfiles(void);

int mdl_vt_stack_init_logging(void);
int mdl_vt_stack_finalize_logging(void);
int mdl_vt_stack_printf(int level, int level2, const char *pFmt, ...);
#endif

