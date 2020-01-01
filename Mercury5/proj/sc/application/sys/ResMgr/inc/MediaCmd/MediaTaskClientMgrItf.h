/**
* @file MediaTaskClientMgrItf.h
*
* This header file defines the interfaces of media client manager
*
*/

#ifndef __MEDIATASKCLIENTMGRITF_H__
#define __MEDIATASKCLIENTMGRITF_H__

/*==================================================================================*/
// Include Files
/*==================================================================================*/
#include "ResMgr_Common.h"
#include "MediaCtrlItf.h"
/*==================================================================================*/
// Macro Definitions
/*==================================================================================*/
#define MEDIA_TASK_CLIENT_MGR__ENABLE_DTMF      0
#define MEDIA_TASK_CLIENT_MGR__DISABLE_DTMF     1

#define MEDIA_TASK_CLIENT_MGR__UNINIT_USER_ID   0xFF

/*==================================================================================*/
// Type Declarations
/*==================================================================================*/
typedef enum MediaCtrl_DeviceChangedAct_e_
{
    MEDIA_DEV_CHG_ACT__NONE,
    MEDIA_DEV_CHG_ACT__STOP_PLAY,
    MEDIA_DEV_CHG_ACT__CHANGE_PROFILE,
    MEDIA_DEV_CHG_ACT__NUM,
    MEDIA_DEV_CHG_ACT__INVALID = 0xFF,
} MediaCtrl_DeviceChangedAct_e;

typedef MediaCtrl_DeviceChangedAct_e (*MediaCtrl_DeviceChanged)(u16 uDevStatus, u32 uCusData, u16 uAppId, u32 *pRetInfo);

typedef struct MediaDeviceChangedCb_t_
{
    u32 uCusData;
    MediaCtrl_DeviceChanged CbFunc;
} MediaDeviceChangedCb_t;

typedef enum BtStatus_e_
{
    BT_STATUS__CONNECT,
    BT_STATUS__DISCONNECT,
    BT_STATUS__START,
    BT_STATUS__STOP
} BtStatus_e;

typedef void (*BtStatusChangedCb)(BtStatus_e eStatus, u32 uNotifyInfo);

typedef struct BtStatusChangedCb_t_
{
    ResMgr_AppId_e eAppId;
    BtStatusChangedCb CbFunc;
} BtStatusChangedCb_t;

typedef struct MediaVol_t_
{
    u8 uVolume;
    u8 aChannelVolume[MEDIA_AUD_CHAN__NUM];
    u8 uVolRange;
    s8 aChannelBalance[MEDIA_AUD_CHAN__NUM];
} MediaVol_t;

typedef struct MediaVolParm_t_
{
    bool bProfileVol;
    union
    {
        MediaVol_t tVol;
        MediaProfileVol_t tProfileVol;
    } Parms;
} MediaVolParm_t;

typedef struct MediaTaskClientMgr_t_
{
    u8 uDisableDtmfNum;
    bool aDtmfStatus[RES_MGR_APP_ID__NUM];
    u8 uVolUserNum;
    u8 aAppRegVolUsers[RES_MGR_APP_ID__NUM];
    MediaDeviceChangedCb_t tDeviceChangedCb;
    BtStatusChangedCb_t tBtStatusChanged;
    MediaProfileType_e eActiveProfile;
    u32 uSpeakerType;
    MediaVolParm_t aVolParms[MEDIA_VOL_USER_ID__NUM];
    MediaConfigId_e eActMediaConfigId;
    MediaConfig_t *pMediaConfig;
    MediaARPConfig_t *pMediaARPConfig;
    bool MediaPathAPPSupport[MEDIA_CONFIG_ID__NUM];
    bool *pMediaPathMemTypeAffectAPP;
    MediaVol_t tTmpVol;
} MediaTaskClientMgr_t;

/*==================================================================================*/
// Function Declarations
/*==================================================================================*/
MediaTaskClientMgr_t* MediaTaskClientMgr_Init(void);
void MediaTaskClientMgr_Uninit(MediaTaskClientMgr_t* pMediaClientMgr);

/************************************************************************************/
/*                                                                                  */
/*                    Media volume handling APIs                                    */
/*                                                                                  */
/************************************************************************************/
void MediaTaskClientMgr_SetVolCtrl(MediaTaskClientMgr_t* pMediaClientMgr, u8 uVolCtrlId, u8 uDefVol, u8 uVolRange);
void MediaTaskClientMgr_ClearVolCtrl(MediaTaskClientMgr_t* pMediaClientMgr, u8 uVolCtrlId);

void MediaTaskClientMgr_RegVolCtrl(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, u8 uVolCtrlId);
void MediaTaskClientMgr_DeregVolCtrl(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId);
void MediaTaskClientMgr_DeregRelatedVolCtrl(MediaTaskClientMgr_t* pMediaClientMgr, u8 uVolCtrlId);

void MediaTaskClientMgr_GetVolume(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, MediaAudChannel_e eChannel, u8 *pVolume, u8 *pVolRange);
void MediaTaskClientMgr_SetVolume(MediaTaskClientMgr_t* pMediaClientMgr, u8 uVolCtrlId, MediaAudChannel_e eChannel, u8 uVolume);

void MediaTaskClientMgr_GetTmpVolume(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, u8 *pVolume, u8 *pVolRange);
void MediaTaskClientMgr_SetTmpVolume(MediaTaskClientMgr_t* pMediaClientMgr, u8 uVolume, u8 uVolRange);

void MediaTaskClientMgr_SetBalance(MediaTaskClientMgr_t* pMediaClientMgr, u8 uVolUserId, MediaAudChannel_e eChannel, s8 sBalance);
void MediaTaskClientMgr_GetBalance(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, MediaAudChannel_e eChannel, s8 *pBalance);
/************************************************************************************/
/*                                                                                  */
/*                    Media DTMF handling APIs                                      */
/*                                                                                  */
/************************************************************************************/
void MediaTaskClientMgr_EnableDTMF(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId);
void MediaTaskClientMgr_DisableDTMF(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId);
__SLDPM_FREE__ bool MediaTaskClientMgr_IsDTMFDisabled(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, bool *pDisabled);

/************************************************************************************/
/*                                                                                  */
/*                    Media profile handling APIs                                   */
/*                                                                                  */
/************************************************************************************/
void MediaTaskClientMgr_SetProfileVolCtrl(MediaTaskClientMgr_t* pMediaClientMgr, u8 uVolUserId, MediaProfileVol_t *pProfileVol);
void MediaTaskClientMgr_SetActiveProfileCtrl(MediaTaskClientMgr_t* pMediaClientMgr, MediaProfileType_e eProfileType);
void MediaTaskClientMgr_GetActiveProfileCtrl(MediaTaskClientMgr_t* pMediaClientMgr, MediaProfileType_e *pProfileType);

void MediaTaskClientMgr_RegDeviceChangedCb(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, u32 uCusData, MediaCtrl_DeviceChanged pFn);
void MediaTaskClientMgr_RegBtStatusChangedCnfCb(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, BtStatusChangedCb pFn);

/************************************************************************************/
/*                                                                                  */
/*                    Media configuration handling APIs                             */
/*                                                                                  */
/************************************************************************************/
void MediaTaskClientMgr_GetActiveMediaConfig(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, MediaConfigParm_t* pMediaConfigParm);
void MediaTaskClientMgr_GetActiveMediaARPConfig(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, MediaARPConfigParm_t* pMediaConfigParm);
void MediaTaskClientMgr_SetActiveMediaConfigCtrl(MediaTaskClientMgr_t* pMediaClientMgr, MediaConfigId_e eMediaConfigId);
void MediaTaskClientMgr_SetMediaConfig(MediaTaskClientMgr_t* pMediaClientMgr, ResMgr_AppId_e eAppId, MediaSetConfigParm_t *pMediaSetConfigParm);

#endif //__MEDIATASKCLIENTMGRITF_H__

