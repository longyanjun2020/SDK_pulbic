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
* @file    UrlSrvCommonMsgBodyDef.h
* @brief   define the message body for vm_msg_t 
*          
*/

#ifndef __MMI_URL_SRV_COMMON_MSG_BODY_DEF_H__
#define __MMI_URL_SRV_COMMON_MSG_BODY_DEF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/// define the msg body for vm_msg_t
/*
 * vm_msgBody_t has been typedef in platform .h
 * When performing ABI check using gcc, 
 * gcc reports error because vm_msgBody_t is defined twice.
 * So here use #define macro to get over this problem.
 * */
typedef void* UrlSrvMsgBody_t;
typedef union
{
	UrlSrvMsgBody_t pSrvMsgBody;
} vm_msgBody_Url_t;

#ifdef vm_msgBody_t
/* Allow double define of vm_msgBody_t only 
 * when performing ABI check (__X86LINUXGCC__) 
 */
#ifdef __X86LINUXGCC__
#undef vm_msgBody_t
#else
#error "error: No double typedef of vm_msgBody_t"
#endif //__X86LINUXGCC__
#endif //vm_msgBody_t

#define vm_msgBody_t vm_msgBody_Url_t

/// if you want to include it, 
/// you must define the msg body first
#include "vm_msgt.ht"


/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* __MMI_URL_SRV_COMMON_MSG_BODY_DEF_H__ */
