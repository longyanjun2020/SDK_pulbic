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
* @file    mmi_keyguardapp.h
* @version
* @brief   KeyGuard header file
*
*/

#ifndef __MMI_KEYGUARDAPP_H__
#define __MMI_KEYGUARDAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_srv_header.h"
#include "mmi_launcher_keyguard.h"
#include "mmi_common_keyguard_type.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/



/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret KeyGuardAppNew(MAE_ClsId id, void **ppObj);
void KeyGuardAppPreNew(void);

#endif /* __MMI_KEYGUARDAPP_H__ */
