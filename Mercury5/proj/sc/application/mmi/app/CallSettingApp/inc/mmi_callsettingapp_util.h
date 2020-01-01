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
* @file    mmi_callsettingapp_util.h
* @version
* @brief   CallSeting applet utility header file
*
*/

#ifndef __MMI_UTIL_CALLSETTINGAPP_H__
#define __MMI_UTIL_CALLSETTINGAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_callsettingapp_priv.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define CALLSETTING_MINUTE_REMINDER_OFF      0
#define CALLSETTING_MINUTE_REMINDER_1_MINUTE 60
#define CALLSETTING_MINUTE_REMINDER_3_MINUTE 180
#define CALLSETTING_MINUTE_REMINDER_5_MINUTE 300

#define CALLSETTING_EDIT_HEIGHT                  (MAIN_LCD_ONELINE_HEIGHT*7)
#define CALLSETTING_TEXT_COLOR                   MAKE_RGB(2, 187, 240)
#define CALLSETTING_MAX_TEMP_STRING_LEN          50
#define CALLSETTING_MAX_SMALL_TEMP_STRING_LEN    10

#define CALLSETTING_DONE_TIMER  2000    //Lih:TBD, Shall we use the uniform setting?

#define CALLSETTINGAPP_UTIL_TEXTTYPE_LOADRES                    0
#define CALLSETTINGAPP_UTIL_TEXTTYPE_GETERRORCAUSE              1
#define CALLSETTINGAPP_UTIL_TEXTTYPE_GETMAEERRORCAUSE           2

#define CALLSETTINGAPP_UTIL_SCREENTYPE_DONE                     0
#define CALLSETTINGAPP_UTIL_SCREENTYPE_PROCESSING               1
#define CALLSETTINGAPP_UTIL_SCREENTYPE_NEWRESULT                2
#define CALLSETTINGAPP_UTIL_SCREENTYPE_CONFIRM                  3

#define MAX_FILEPATH_WCHAR_BUFFER_SIZE (sizeof(MAE_WChar)*FILEMGR_MAX_FILEPATH_SIZE)

#ifdef __APP_MMI_ANSWERING_MACHINE__
#define CALLSETTING_AM_AUTO_ANSWER_AFTER_RING_IMMEDIATE 0
#define CALLSETTING_AM_AUTO_ANSWER_AFTER_RING_5_SECONDS 5
#define CALLSETTING_AM_AUTO_ANSWER_AFTER_RING_15_SECONDS 15
#define CALLSETTING_AM_AUTO_ANSWER_AFTER_RING_30_SECONDS 30
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef u32 MenuItemID_e;
#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
typedef struct CBS_EFFECT_ITEM_tag
{
	CFGItemID_e eCFGItemID;
	u32 u32TextID;
	u32 u32MelodyID;
} CBS_EFFECT_ITEM_t;
#define CBS_MAX_PREDEFINED 9
#endif

/*=============================================================*/
// Global function definition
/*=============================================================*/

///MAE_Ret CallSettingGetViewData(CallSettingApp_t* pThis, IView **ppIView, u16 nViewID, MAE_WChar	*pPWTitleTextBuffer);
///void CallSettingReleaseViewData(CallSettingApp_t* pThis);
u32 CallSettingGetMenuIDByReminderSecond(u16 nSecond);
u32 CallSettingGetMenuIDByCallerIdentityEnum(MMI_CALLSETTING_CALLER_IDENTITY_e eValue);
u32 CallSettingGetMenuIDByAnswerModeEnum(MMI_CALLSETTING_ANSWER_MODE_e eValue);
u32 CallSettingGetMenuIDByAutoRedialEnum(MMI_CALLSETTING_AUTO_REDIAL_e eValue);

#ifdef __ANSWER_INDICATOR_MMI__
u32 CallSettingGetMenuIDByAnswerIndicatorEnum(MMI_CALLSETTING_ANSWER_INDICATOR_e eValue);
#endif

#ifdef __APP_VIDEO_TELEPHONY__
u32 CallSettingGetMenuIDByVideoCallEnum(VideoCall_Setting_MODE_e eValue);
#endif

#ifdef __AUTO_RECORDING_MMI__
u32 CallSettingGetMenuIDByAutoRecordingStatus(boolean bStatus);
#endif

MAE_Ret CallSettingSetMenuItemLine2Data(CallSettingAppData_t* pThis, IWidget *pMenuWdg, u32 nMenuItemID, u32 nTextID);
MAE_Ret CallSettingReplaceMenuItemLine2DataByText(CallSettingAppData_t* pThis, IWidget *pMenuWdg, u32 nMenuItemID, MAE_WChar *pWStr);

void CallSettingLoadTitleStrByTextStr(CallSettingAppData_t *pThis, MAE_WChar *pTypeTextStr);
u32 CallSettingGetTextIDByMenuID(u32 nMenuItemID);
MAE_WChar* CallSettingGetErrorCause(u16 nErrorCode);
u32 CallSettingGetNetworkErrorCause(u16 nErrorCode);
u32 CallSettingGetMAEErrorCause(u16 nErrorCode);
boolean CallSettingIsDnSequence(const u8 * ptr);
MAE_WChar*  CallSettingGetDivertReasonText(MMI_SSSRV_CFX_Reason_e eReason);
MAE_WChar*  CallSettingGetBarringText(MMI_SSSRV_CBX_Type_e eReqType);
boolean CallSettingIsInAirplaneMode(CallSettingAppData_t* pThis);
void CallSettingRemoveDoubleNewLine(MAE_WChar *pWCharData);

#ifdef __APP_MMI_ANSWERING_MACHINE__
u32 CALLSETTINGAPP_GetMenuIDByAutoAnswerAfterRing(const u8 u8Second);
//u32 CALLSETTINGAPP_GetMenuIDByAMStorage(const MMI_CALLSETTING_AM_STORAGE_e eStorage);
u32 CALLSETTINGAPP_GetTextIDByMenuID(u32 u32MenuItemID);
#endif
#ifdef __APP_MMI_CALL_BACKGROUND_SOUND__
void CallSettingCBSInit(void);
u32 CALLSETTINGAPP_GetMenuIDByCBSPlayType(const CallBgSound_Play_Type_e ePlayType);
MAE_WChar* CallSettingCBSGetEffectCfgString(const u16 nIndex);
void CallSettingCBSGetSettingsFromSrv(CallSettingAppData_t* pThis);
void CallSettingCBSGetSettingsFromCfg(CallSettingAppData_t* pThis);
#endif
#endif//__MMI_UTIL_CALLSETTINGAPP_H__
