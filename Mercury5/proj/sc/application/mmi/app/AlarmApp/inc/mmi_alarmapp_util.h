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

#ifndef __MMI_ALARMAPP_UTIL_H__
#define __MMI_ALARMAPP_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_alarmapp.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_WChar *AlarmUtilGetAlarmTitle(u32 nIndex, MAE_WChar *pTitle);
boolean AlarmUtilIsDefaultAlarmTitle(u32 nAlarmUID, MAE_WChar *pTitle);
u32 AlarmUtilGetAlarmTitleTextID(u32 nAlarmUID);
MAE_Ret _AlarmUtilGetAlarmToneURLFromConfig(MAE_WChar** ppAlarmToneURL);
void AlarmUtilGetTimeFormat(SetPhoneTimeFormat_e *pTimeFormat);
MAE_Ret AlarmUtilGetAlarmListFromConfig(ALARM_RECORD_t alarmList[]);
MAE_Ret AlarmUtilSetAlarmListToConfig(ALARM_RECORD_t alarmList[]);
MAE_Ret AlarmUtilGetAlarmAlertData(u32 nAlarmUID, AlertDisplayType_e eDisplayType, MAE_WChar **ppAlertText, u32 *pSnoozeCount, IBase *pOwner);
u32 AlarmUtilGetWeekDay(MAE_DateTime_t *pDate);
u8 AlarmUtilGetWeekDayByFrequency(ALARM_FREQUENCY_e eFrequency);
ALARM_FREQUENCY_e AlarmUtilGetFrequencyByWeekDay(u8 nWeekDay);
ALARM_FREQUENCY_e AlarmUtilGetNextFrequency(ALARM_FREQUENCY_e eCurrentFrequency);

#endif /* __MMI_ALARMAPP_UTIL_H__ */
