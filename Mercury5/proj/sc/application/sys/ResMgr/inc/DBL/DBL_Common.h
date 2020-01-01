/**
* @file DBL_Common.h
*
* This header file defines the common declaration of DBL.
*
*/

#ifndef __DBL_COMMON_H__
#define __DBL_COMMON_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ABL_Aud.h"
#include "ABL_Vdo.h"
#include "ABL_Cam.h"
#include "ABL_Device.h"
#include "ABL_Usb.h"
#include "ABL_Fmr.h"
#include "ABL_Gss.h"
#include "ABL_Tv.h"
#include "ABL_Vfs.h"
#include "ABL_Gps.h"
#include "esl_aud_itf.h"
#include "esl_vdo_itf.h"
#include "esl_cam_itf.h"
#include "esl_usb_itf.h"
#include "esl_tv_itf.h"
#include "esl_gps_itf.h"
#include "mdl_aud_pub_api.h"
#include "MML_Manager.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef esl_AudNotifyCb DBL_AudNotifyCb;
typedef esl_VdoNotifyCb DBL_VdoNotifyCb;
typedef esl_CamNotifyCb DBL_CamNotifyCb;
typedef esl_UsbNotifyCb DBL_UsbNotifyCb;
typedef esl_TvNotifyCb DBL_TvNotifyCb;
typedef esl_FmrNotifyCb DBL_FmrNotifyCb;
typedef esl_GpsNotifyCb DBL_GpsNotifyCb;
typedef esl_AudNotifyCb_t DBL_AudNotify;
typedef esl_VdoNotifyCb_t DBL_VdoNotify;
typedef esl_CamNotifyCb_t DBL_CamNotify;
typedef esl_UsbNotifyCb_t DBL_UsbNotify;
typedef esl_TvNotifyCb_t DBL_TvNotify;
typedef esl_FmrNotifyCb_t DBL_FmrNotify;
typedef esl_GpsNotifyCb_t DBL_GpsNotify;
typedef esl_AudNotifyInfo_t DBL_AudNotifyInfo;
typedef esl_VdoNotifyInfo_t DBL_VdoNotifyInfo;
typedef esl_CamNotifyInfo_t DBL_CamNotifyInfo;
typedef esl_UsbNotifyInfo_t DBL_UsbNotifyInfo;
typedef esl_TvNotifyInfo_t DBL_TvNotifyInfo;
typedef esl_FmrNotifyInfo_t DBL_FmrNotifyInfo;

typedef struct NotifyMsgBody_t_
{
    u32 uCusData;
    void *pEvtInfo;
} NotifyMsgBody_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void DBL_Init(void);
__SLDPM_FREE__ u16 DBL_GetHeadsetStatus(void);
__SLDPM_FREE__ ABL_DeviceSpeakerType_e DBL_GetSpeakerType(void);
__SLDPM_FREE__ u16 DBL_GetMmpCapability(u8 *pStrucAddr, u32 uStrucLen);
__SLDPM_FREE__ ResMgr_ErrorCode_e DBL_GetMmlPlatformCapability(u32 *pAddr);
__SLDPM_FREE__ ResMgr_ErrorCode_e DBL_GetMmlPlatformChipType(u32 *pAddr);
__SLDPM_FREE__ void DBL_RequestHighCpuSpeed(void);
__SLDPM_FREE__ void DBL_RequestLowCpuSpeed(void);
__SLDPM_FREE__ bool DBL_IsAllowCpuSleepInFM(void);
__SLDPM_FREE__ void DBL_WakeUpDevice(void);
__SLDPM_FREE__ bool DBL_IsResMgrTaskIdle(void);
__SLDPM_FREE__ bool DBL_IsRspNeedFlowCtrl(u32 uEvent);
#endif

