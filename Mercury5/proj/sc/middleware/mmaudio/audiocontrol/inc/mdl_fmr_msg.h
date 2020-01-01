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

#ifndef MDL_FMR_MSG_H
#define MDL_FMR_MSG_H

#include "mdl_fmr_handle.h"
#include "srv_ResMgr_MmlManager.h"
#include "srv_resmgr_mmlradio_types.h"

typedef struct
{
    MdlFmrCtlMsgId_e       eMsgId;
    MmlRadioResult_e        eErrCode;
    union
    {
        MmlRadioResponse_t   tResponse;
        MmlRadioNotify_t     tRadioNotify;
    } uParam;
} MdlRadioCtlMsg_t;

typedef union
{
    vm_osTimerMsgBody_t             timerMsg;
    u32                     nUseCaseID;
    MmlRadioUCParam_t       tRadioUCParam;
    MdlRadioCtlMsg_t        tRadioCtlMsg;
} vm_msgBody_t;

#include "vm_msgt.ht"

#define MDL_GET_RADIO_UCID(pMsg)           (MML_GET_RADIO_UCID(&pMsg->Body.tRadioUCParam))
#define MDL_GET_RADIO_CTL_MSGID(pMsg)      ((MdlFmrCtlMsgId_e)(pMsg->Body.tRadioCtlMsg.eMsgId))

#endif

