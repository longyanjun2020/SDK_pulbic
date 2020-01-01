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

#ifndef MDL_IMAGE_CAPTURE_MSG_H
#define MDL_IMAGE_CAPTURE_MSG_H

#include "mdl_image_capture_handle.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/




/*=============================================================*/
// Macro definition
/*=============================================================*/




/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef union
{
  MmlImageUCParam_t   tImageUCParam;
  MdlImgCapNotify_t   tImgCapNotify;      /* use to notify massage in main task      */
  MdlImgCapResponse_t tImgCapResponse;    /* use to response massage in main task      */
  MdlImgCapWbErr_t    tImgCapErrSetting;  /* use to set the error case      */
  MdlImgCapShutSnd_t  tImgCapShutSnd;     /* use to set shutter sound task */
  vm_osTimerMsgBody_t tOsTimeoutMsg;      /* use to simulate image-capture  */
} vm_msgBody_t;


#include "vm_msgt.ht"




/*=============================================================*/
// Variable definition
/*=============================================================*/




/*=============================================================*/
// Global function definition
/*=============================================================*/




#endif //MDL_IMAGE_CAPTURE_MSG_H
