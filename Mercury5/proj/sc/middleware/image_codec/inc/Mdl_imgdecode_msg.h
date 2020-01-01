#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

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

#ifndef IMGCODEC_MSG_H
#define IMGCODEC_MSG_H
#include "sys_rtk_vmoshi.h"
#include "srv_resmgr_mmlimage_types.h"
#include "vm_types.ht"

typedef union
{
  MmlImageUCParam_t          tImageUCParam;     ///< Image use case parameters
  Mdl_ImgDecode_Response_t   tImageResponse;
  vm_osTimerMsgBody_t        tTimerMsgBody;
} vm_msgBody_t;

#include "vm_msgt.ht"
#endif //MDW_IMGDEC_HANDLE_H
#endif

