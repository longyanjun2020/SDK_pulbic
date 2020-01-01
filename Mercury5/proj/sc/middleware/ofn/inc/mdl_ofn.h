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
* @file    mdl_ofn.h
* @version
* @brief   ofn middleware interface.
*
*/

#ifndef __PRIVATE_MDL_OFN_H__
#define __PRIVATE_MDL_OFN_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "sys_rtk_vmoshi.h"
#include "vm_types.ht"
#include "vm_kbd.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef union{
    vm_osTimerMsgBody_t TimerMsgBody;
    VKEYCODE         vcode;
    vm_kbdInd_t      scancode;
} Body_t;



/*=============================================================*/
// Global function definition
/*=============================================================*/

MdlOfnErrCode_e MdlOfnEnable(void);
MdlOfnErrCode_e MdlOfnDisable(void);

#endif//__MDL_OFN_H__

