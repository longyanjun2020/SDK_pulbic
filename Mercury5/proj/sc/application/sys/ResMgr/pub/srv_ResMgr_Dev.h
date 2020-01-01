/**
* @file srv_ResMgr_Dev.h
*
* This header file defines the device declaration of DBL.
*
*/

#ifndef __SRV_RESMGR_DEV_H__
#define __SRV_RESMGR_DEV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "MediaCtrlItf.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum ABL_DeviceSpeakerType_e_
{
    ABL_DEVICE_SPEAKER_TYPE_MONO,
    ABL_DEVICE_SPEAKER_TYPE_STEREO,
    ABL_DEVICE_SPEAKER_TYPE_NUM
} ABL_DeviceSpeakerType_e;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
bool ABL_IsHeadsetIns(ResMgr_AppId_e eAppId);
ABL_CmnErrCode_e ABL_InsHeadset(ResMgr_AppId_e eAppId);
ABL_CmnErrCode_e ABL_PullHeadset(ResMgr_AppId_e eAppId);
ABL_DeviceSpeakerType_e ABL_GetSpeakerType(ResMgr_AppId_e eAppId);
__SLDPM_FREE__ bool ABL_IsBtHeadsetConnect(ResMgr_AppId_e eAppId);
ABL_CmnErrCode_e ABL_ConnectToBtHeadset(ResMgr_AppId_e eAppId);
ABL_CmnErrCode_e ABL_DisconnectToBtHeadset(ResMgr_AppId_e eAppId);
ABL_CmnErrCode_e ABL_SetPrefPath(ResMgr_AppId_e eAppId, MediaPrefPath_e ePath);
#endif //__SRV_RESMGR_DEV_H__

