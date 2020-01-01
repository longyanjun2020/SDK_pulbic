////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
* @file    mmi_android_keyguardapp.h
* @version
* @brief   KeyGuard header file
*
*/
#ifdef __UI_STYLE_MMI_ANDROID_KEYGUARD__

#ifndef __MMI_ANDROID_KEYGUARDAPP_H__
#define __MMI_ANDROID_KEYGUARDAPP_H__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_srv_header.h"
#include "mmi_launcher_keyguard.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define KEYGUARDAPP_START_TYPE_BY_HOTKEY	0
#define KEYGUARDAPP_START_TYPE_AUTOMATIC	1
#define KEYGUARDAPP_START_TYPE_INIT_FAIL_RESUME	2

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret AndroidKeyGuardAppNew(MAE_ClsId id, void **ppObj);
void AndroidKeyGuardAppPreNew(void);
#endif /*__MMI_KEYGUARDAPP_H__*/
#endif /*__UI_STYLE_MMI_ANDROID_KEYGUARD__ */
