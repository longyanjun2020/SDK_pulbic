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

#ifndef __MMI_FMSCHAPP_UTIL_H__
#define __MMI_FMSCHAPP_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_fmschapp.h"
#if defined(__ONBOARD_USER_STORAGE_MMI__)
#include "mmi_common_storage_mgr.h"
#endif
#
/*=============================================================*/
// Macro definition
/*=============================================================*/
#define FMR_TEMP_STRING_SIZE 20 // Used to store channel frequency number(100.7) to string.

/*=============================================================*/
// Global function definition
/*=============================================================*/
void FmSchHandleAccessoryEvtCb(void *pUserData, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
MAE_WChar *FmSchUtilGetFmSchTitle(u32 nAlarmId, u32 nChannelFreq);
MAE_WChar * FmSchUtilGetFrequencyString(u32 nChannelFreq);
u32 FmSchUtilCovertWStrToFreq(MAE_WChar *pwszStr);
void FmSchUtilGetTimeFormat(SetPhoneTimeFormat_e *pTimeFormat);
MAE_Ret FmSchUtilGetScheduleListFromConfig(FMSCH_ENTITY_t alarmList[]);
MAE_Ret FmSchUtilSetScheduleListToConfig(FMSCH_ENTITY_t alarmList[]);
MAE_Ret FmSchUtilGetRecScheduleListFromConfig(FMRECSCH_ENTITY_t alarmList[]);
MAE_Ret FmSchUtilSetRecScheduleListToConfig(FMRECSCH_ENTITY_t alarmList[]);
u32 FmSchUtilConvertSchRecEndTime(u32 nEndTime, u32 nCurrentTime);
MAE_Ret AlarmUtilGetAlarmAlertData(u32 nAlarmUID, AlertDisplayType_e eDisplayType, MAE_WChar **ppAlertText, u32 *pSnoozeCount, IBase *pOwner);
boolean FmSchIsRecFormatSupport(VOICE_RECORD_Type_e eRecordType);
u32 FmSchNumRecFormatSupport(void);
void _FmSchRecGetFilterCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
#if defined(__ONBOARD_USER_STORAGE_MMI__)
void _FmSchRecGetVirtualVolumeListCb(void *pUserData, u32 *pNumber, const FileMgrVirtualVolumeItem_t **pVirtualVolumeList);
#endif
#endif /* __MMI_FMSCHAPP_UTIL_H__ */
