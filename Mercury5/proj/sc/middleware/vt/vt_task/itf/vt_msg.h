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
* @file    vt_msg.h
* @version
* @brief   video telephony message format definitions
*
*/
#ifndef __VT_MSG_H__
#define __VT_MSG_H__

#include "vm_msgof.hc"
#include "osdefs.hc"
#include "sys_MsWrapper_cus_os_msg.h"


#include "api_cm_itf.h"
#include "cmvt_sig.h"
#include "vtmux_sig.h"
#include "fcm.hi"
#include "wmh_fcm.ho"

#include "vt_types.h"

typedef union
{
    vm_osTimerMsgBody_t     msgTimer;
    
    VtCallStateInd_t        msgCallStateInd;
    VtCallDropReq_t         msgCallDropReq;    
    VtUserInputDtmfReq_t    msgUserInputDTMFReq;
    VtUserInputDtmfCnf_t    msgUserInputDTMFCnf;    
    VtLoopbackReq_t         msgLoopbackReq;
    VtLoopbackCnf_t         msgLoopbackCnf;
    VtChannelOnOffInd_t         msgChannelOnOffInd;	
    VtChannelOnOffReq_t         msgChannelOnOffReq;	
    VtTimerSend_t           msgTimerSend;

    CmVtGetChannelNumberReq msgGetChannelNumberReq;   
    CmVtGetChannelNumberCnf msgGetChannelNumberCnf;  
    CmVtOpenConnectionReq   msgOpenConnectionReq;
    CmVtOpenConnectionCnf   msgOpenConnectionCnf;
    CmVtCloseConnectionInd  msgCloseConnectionInd;

    VtMuxOpenReq            msgMuxOpenReq;
        
    fcm_DataBlock_t         fcmDataBlock;
    fcm_OpenFlowInd_t       fcmOpenFlowInd;
    fcm_CloseFlowInd_t      fcmCloseFlowInd;
    fcm_ResumeDataFlowInd_t fcmResumeFlowInd;   
} vm_msgBody_t;


#include "vm_msgt.ht"

#endif

