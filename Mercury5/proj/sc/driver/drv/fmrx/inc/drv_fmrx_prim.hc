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


/**
 * @file    drv_fmrx_prim.hc
 * @brief   This module definies the message/primitive index of FM radio task
 */

#ifndef __DRV_FMRX_PRIM_HC__
#define __DRV_FMRX_PRIM_HC__
#if 0
#ifdef __ONCHIP_FMRX_ENABLE__
//#include "ema_prim.hc"
#else
#include "cus_msg.hc"
#endif


#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "fmr_message_define__.hi"
};
#endif
#endif /* __DRV_FMRX_PRIM_HC__ */

