/**
* @file HAL_AudioPathCtrlItf.h
*
* This header file defines the interface of audio path controller
* in HW adaptor layer
*/

#ifndef __HAL_AUDPATHCTRLITF_H__
#define __HAL_AUDPATHCTRLITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResCtrlItf.h"
#include "MediaCmdItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*
    Input Path: Handset, Headset
    Output Path: Handset, Headset, Speaker
*/
typedef enum AudPath_e_
{                                               /*Sync. with MDL*/
    AUD_PATH__HANDSET_IN_HANDSET_OUT = 1,       //MDL_AUD_PATH_HANDSET
    AUD_PATH__HEADSET_IN_HEADSET_OUT,           //MDL_AUD_PATH_HEADSET
    AUD_PATH__HANDSET_IN_SPEAKER_OUT,           //MDL_AUD_PATH_HANDSFREE
    AUD_PATH__SPEAKER_OUT,		                //MDL_AUD_PATH_LINE_OUT
    AUD_PATH__SPEAKER_LEFT_OUT,                 //MDL_AUD_PATH_LINE_LEFT_OUT
    AUD_PATH__SPEAKER_RIGHT_OUT,                //MDL_AUD_PATH_LINE_RIGHT_OUT
    AUD_PATH__HEADSET_OUT,                      //MDL_AUD_PATH_HEADPHONE_OUT
    AUD_PATH__BT_HEADSET_IN_HEADSET_OUT,        //MDL_AUD_PATH_BT_MONO
    AUD_PATH__BT_HEADSET_OUT,                   //MDL_AUD_PATH_BT_STEREO
    AUD_PATH__VT_BT_HEADSET_OUT,                //MDL_AUD_PATH_BT_VT
    AUD_PATH__HEADSET_SPEAKER_OUT,              //MDL_AUD_PATH_HEADSET_AND_LINE_OUT
    AUD_PATH__HANDSET_HEADSET_SPEAKER_OUT,      //MDL_AUD_PATH_ALL_OUT
    AUD_PATH__NUM,
    AUD_PATH__LAST_CONNECTED,                   //Can be set only in the case of Wire headset ON and BT headset ON */
    AUD_PATH__INVALID
} AudPath_e;

typedef enum AudChannel_e_
{                                               /*Sync. with ESL*/
    AUD_CHAN__VOICE = 0,                        //ESL_AUD_VOICE_CHANNEL
    AUD_CHAN__STEREO,                           //ESL_AUD_MUSIC_CHANNEL
    AUD_CHAN__AUX,                              //ESL_AUD_LINEIN_CHANNEL
    AUD_CHAN__VOICE_SLAVE,                      //ESL_AUD_VOICE_SLAVE_CHANNEL
    AUD_CHAN__NUM,
    AUD_CHAN__ALL = AUD_CHAN__NUM,
    AUD_CHAN__INVALID
} AudChannel_e;

typedef enum AudResConfig_e_
{
    AUD_RES_CFG__DEFAULT,
    AUD_RES_CFG__VIDEOCHAT,
    AUD_RES_CFG__NUM,
} AudResConfig_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResCtrlHandle_t AudResCtrl_Init(void);
void AudResCtrl_Uninit(ResCtrlHandle_t pResCtrlHdl);
u16 AudResCtrl_QueryChan(MediaResInfo_e eMediaFormat);

/*
    This API is designed for media command set correct audio path before executing command.
    It's Resource Manager internal API and should not be published to Resource Manager clients
*/
void AudResCtrl_SetCurCmdPath(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);

/*
    This API is designed to update audio path when device status changed. We need
    to re-select audio path because the current audio path may be invalid
*/
void AudResCtrl_ReSelectPath(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);


void AudResCtrl_SetPrefPath(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, AudPath_e ePath, MediaResInfo_e eMediaFormat);
void AudResCtrl_AddPrefPath(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, AudPath_e ePath, MediaResInfo_e eMediaFormat);
__SLDPM_FREE__ void AudResCtrl_ClearPrefPath(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);

/*
    This API is designed to apply current audio volume to driver layer. It only call driver API
    when audio volume changed and current media required channel is enabled
*/
void AudResCtrl_UpdateAudioVolumeToDriver(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);

/*
    This API is designed to apply current audio path to driver layer. It only call driver API
    when audio channel changed and current media required channel is enabled
*/
void AudResCtrl_UpdateAudioChannelToDriver(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);

/*
    This API is designed to apply current audio balance to driver layer. It only call driver API
    when audio balance changed and current media required channel is enabled
*/
void AudResCtrl_UpdateAudioBalanceToDriver(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);

/*
    Check if there is any conflicts in audio resources
*/
bool AudResCtrl_IsConflict(u32 uCtrlID1, u32 uCtrlID2);
void AudResCtrl_SetTmpVol(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);

/*
    Re-select active media configuration id
*/
void AudResCtrl_ReSelectMediaConfig(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat, bool bChangeByUser, MediaUpdateAudEnv_e eAudEnv);
void AudResCtrl_SetMediaConfig(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, bool bChangeByUser, MediaUpdateAudEnv_e eAudEnv);
void AudResCtrl_GetCurVolume(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat, u8 *pVolume, u8 *pRange);
/*
	Switch Path from handset_in_speaker_out to handset_in_handset_out, if audio voice channel is not required.
*/
void AudResCtrl_SwitchPathForVoiceChan(CmdMgrStgrHdl_t pStgrHdl);
/*
	Update the audio environment when the path is changed
*/
    void AudResCtrl_UpdateAudEnv(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat, MediaUpdateAudEnv_e eAudEnv);
/*
	Update the audio environment when the path is changed if temp volume is set
*/
void AudResCtrl_UpdateTmpAudEnv(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat, MediaUpdateAudEnv_e eAudEnv);

bool AudResCtrl_IsAllowMultiChan(u16 uAppId, u16 uReqAppId, AudChannel_e eChannel, AudChannel_e eReqChannel);

void AudResCtrl_SetResConfig(ResMgr_AppId_e eAppId, ResMgr_ConfigId_e eConfigId, AudResConfig_e eResConfig);
bool AudResCtrl_IsSupportA2DP(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);
AudPath_e AudResCtrl_GetApPathSetting(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);
AudPath_e AudResCtrl_DecidePath(CmdMgrStgrHdl_t pStgrHdl, ResMgr_AppId_e eAppId, MediaResInfo_e eMediaFormat);
void AudResCtrl_SyncDefaultPath(CmdMgrStgrHdl_t pStgrHdl);

#endif //__HAL_AUDPATHCTRLITF_H__

