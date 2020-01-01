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
* @file    mmi_consettingapp.h
* @version
* @brief   ConSetting header file
*
*/

#ifndef __MMI_CONSETTINGAPP_H__
#define __MMI_CONSETTINGAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_consetting.h"

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
    //CON_SETTING_START_E_START=0,
    CON_SETTING_START_E_CONNECT_SETTINGS_MENU=0,
    CON_SETTING_START_E_GPRS_CONNECTION,
    CON_SETTING_START_E_DATA_ACCOUNT,
#ifdef __WAP_MMI_CDWAP__
    CON_SETTING_START_E_WAP_PROFILE,
#endif //__WAP_MMI_CDWAP__
#ifdef __MMS_MMI_CDMMS__
    CON_SETTING_START_E_MMS_PROFILE,
#endif //__MMS_MMI_CDMMS__
#ifdef __JAVA_MMI__
    CON_SETTING_START_E_JAVA_PROFILE,
#endif //__JAVA_MMI__
    CON_SETTING_START_E_OTHER_PROFILE,
    CON_SETTING_START_E_LBS_PROFILE,
#ifdef __WAP_MMI_CDWAP__
    CON_SETTING_START_E_WAP_SETTINGS,   //If active both SIM, start at Dual SIM selection menu
#endif //__WAP_MMI_CDWAP__
#ifdef __MMS_MMI_CDMMS__
    CON_SETTING_START_E_MMS_SETTINGS,   //If active both SIM, start at Dual SIM selection menu
#endif //__MMS_MMI_CDMMS__
#ifdef __JAVA_MMI__
    CON_SETTING_START_E_JAVA_SETTINGS,  //If active both SIM, start at Dual SIM selection menu
#endif //__JAVA_MMI__
    CON_SETTING_START_E_OTHER_SETTINGS, //If active both SIM, start at Dual SIM selection menu    
	CON_SETTING_START_E_LBS_SETTINGS,  //If active both SIM, start at Dual SIM selection menu

#ifdef __EMAIL_MMI__
	CON_SETTING_START_E_EMAIL_SETTINGS,   //If active both SIM, start at Dual SIM selection menu
#endif  // #ifdef __EMAIL_MMI__
#ifdef __APP_MMI_NTP__
    CON_SETTING_START_E_NTP_SETTINGS, //If active both SIM, start at Dual SIM selection menu
#endif
#ifdef __NCCQQ_MMI__
	CON_SETTING_START_E_QQ_SETTINGS,   //If active both SIM, start at Dual SIM selection menu
#endif  // #ifdef __NCCQQ_MMI__
#ifdef __STREAMING_MODULE__
    CON_SETTING_START_E_STREAMING_SETTINGS, //If active both SIM, start at Dual SIM selection menu
#endif
    CON_SETTING_START_E_TOTAL

} ConSettingAP_Start_e;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret ConSettingAppNew(MAE_ClsId id, void **ppObj);
void ConSettingAppPreNew(void);

#endif /* __MMI_CONSETTINGAPP_H__ */
