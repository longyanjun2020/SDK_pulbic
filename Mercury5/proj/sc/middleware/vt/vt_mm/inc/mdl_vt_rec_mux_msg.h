////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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


/**
* @file    mdl_vt_rec_mux_msg.h
* @version
* @brief   3g324mTask
*
*/

#ifdef __VT_3G324M__
#ifndef _MDL_VTMUX_MSG_H_
#define _MDL_VTMUX_MSG_H_

typedef struct
{
    MmlVideoUCParam_t           tVideoUCParam;  ///< Video use case parameters
    u32                         Msg;            ///< Internal message
    u32                         Userdata;
    //MdlVdrFakeErrorParam_t      tFakeErrParam;  ///< Fake Error paramaters
} vm_msgBody_t;

#include "vm_msgt.ht"

//u16 _MdlSendMsgToVtMux(u32 MsgType, void *Msg, u32 MsgSize, u32 UserData);

#endif //_MDL_VTMUX_MSG_H_
#endif //__VT_3G324M__

