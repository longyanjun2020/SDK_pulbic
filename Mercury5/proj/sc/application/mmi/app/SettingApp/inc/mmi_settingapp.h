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
* @file mmi_settingapp.h
*
* Class Id: CLSID_SETTINGAPP
*
* @version $Id: mmi_settingapp.h 33199 2009-06-12 09:01:32Z jason.su $
*/
#ifndef __MMI_SETTINGAPP_H__
#define __MMI_SETTINGAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_launcher_setting.h"
#include "mmi_common_setting_type.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
void SettingPreNew(void);
MAE_Ret SettingAppNew(MAE_ClsId id, void **ppObj);
#endif /* __MMI_SETTINGAPP_H__ */
