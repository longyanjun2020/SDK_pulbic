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
* @file    mmi_callsettingapp.h
* @version
* @brief   CallSeting applet header file
*
*/

#ifndef __MMI_CALLSETTINGAPP_H__
#define __MMI_CALLSETTINGAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_callsetting.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
    MMI_CALLSETTING_APP_MODE_NORMAL=1,            //Normal created by setting
    MMI_CALLSETTING_APP_MODE_CALL_SETTING=2,      //UIE: call setting mode
    MMI_CALLSETTING_APP_MODE_DIVERT=3,            //UIE: call divert mode
    MMI_CALLSETTING_APP_MODE_BARRING=4,           //UIE: call barring mode
    MMI_CALLSETTING_APP_MODE_DISTORTED_VOICE=5,   //UIE: call distorted voice setting
    MMI_CALLSETTING_APP_MODE_VOICEBOX=6,		  //UIE: Answering machine voice box list
    MMI_CALLSETTING_APP_MODE_CALL_BACKGROUND_SOUND=7, //UIE: Call background sound setting in call
} MMI_CALLSETTING_APP_MODE_e;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret CallSettingAppNew(MAE_ClsId id, void **ppObj);
void CallSettingAppPreNew(void);

#endif /* __MMI_CALLSETTINGAPP_H__ */
