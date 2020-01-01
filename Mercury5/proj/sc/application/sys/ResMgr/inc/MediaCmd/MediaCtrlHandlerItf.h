/**
* @file MediaCtrlHandlerItf.h
*
* This header file defines the interfaces of Video States
*
*/

#ifndef __MEDIACTRLHANDLERITF_H__
#define __MEDIACTRLHANDLERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_CtrlHandlerItf.h"
#include "HAL_AudResCtrlItf.h"
#include "MediaTaskClientMgrItf.h"
#include "mediacmn.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void (*MediaCtrl_DevChgHdlFunc)(CmdMgrStgrHdl_t pStgrHdl);

typedef struct MediaDtmfCtrl_t_
{
    ResMgr_AppId_e eAppId;
} MediaDtmfCtrl_t;

typedef struct MediaIsDtmfDiabledCtrl_t_
{
    ResMgr_AppId_e eAppId;
    bool *pDisabled;
} MediaIsDtmfDisabledCtrl_t;

typedef struct MediaSetVolCtrl_t_
{
    u8 uVolUserId;
    u8 uDefVol;
    u8 uVolRange;
} MediaSetVolCtrl_t;

typedef struct MediaRegVolCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u8 uVolUserId;
} MediaRegVolCtrl_t;

typedef struct MediaDeregVolCtrl_t_
{
    ResMgr_AppId_e eAppId;
} MediaDeregVolCtrl_t;

typedef struct MediaVolCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u8 uVolUserId;
    AudChannel_e eChannel;
    u8 uVolume;
} MediaVolCtrl_t;

typedef struct MediaBalanceCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u8 uVolUserId;
    AudChannel_e eChannel;
    s8 sBalance;
} MediaBalanceCtrl_t;

typedef struct MediaProfileVolCtrl_t_
{
    u8 uVolUserId;
    MediaProfileType_e eProfile;
    u8 uVolume;
} MediaProfileVolCtrl_t;

typedef struct MediaGetVolCtrl_t_
{
    ResMgr_AppId_e eAppId;
    AudChannel_e eChannel;
    u8 *pVolume;
    u8 *pVolRange;
} MediaGetVolCtrl_t;

typedef struct MediaGetPathCtrl_t_
{
    ResMgr_AppId_e eAppId;
    AudPath_e *pPath;
    AudChannel_e *pChannel;
} MediaGetPathCtrl_t;

typedef struct MediaGetApPathSettingCtrl_t_
{
    ResMgr_AppId_e eAppId;
    MediaResInfo_e eResInfo;
    AudPath_e *pPath;
} MediaGetApPathSettingCtrl_t;

typedef struct MediaSetPrefPathCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u8 uPath;
    u16 uResInfo;
} MediaSetPrefPathCtrl_t;

typedef struct MediaGetResumeRestartCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u8 *pGetResumeRestart;
} MediaGetResumeRestartCtrl_t;

typedef struct MediaResumeRestartCtrl_t_
{
    ResMgr_AppId_e eAppId;
    void* pAudCb;
    u16 nAudCbSize;
} MediaResumeRestartCtrl_t;

typedef struct MediaGetSpeakerTypeCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u32 *pSpeakerType;
} MediaGetSpeakerTypeCtrl_t;

typedef struct MediaRelResourceCtrl_t_
{
	ResMgr_AppId_e eAppId;
} MediaRelResourceCtrl_t;

typedef struct MediaInitProfileVolCtrl_t_
{
    u8 uVolUserId;
    MediaProfileVol_t tProfileVol;
} MediaInitProfileVolCtrl_t;

typedef struct MediaSetActiveProfileCtrl_t_
{
    MediaProfileType_e eProfileType;
} MediaSetActiveProfileCtrl_t;

typedef struct MediaGetActiveProfileCtrl_t_
{
    MediaProfileType_e *pProfileType;
} MediaGetActiveProfileCtrl_t;

typedef struct MediaRegDeviceChangedCbCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u32 uCusData;
    MediaCtrl_DeviceChanged pDeviceChangedCb;
} MediaRegDeviceChangedCbCtrl_t;

typedef struct MediaRegBtStatusChangedCnfCbCtrl_t_
{
    ResMgr_AppId_e eAppId;
    BtStatusChangedCb pBtStatusChangedCb;
} MediaRegBtStatusChangedCnfCbCtrl_t;

typedef struct MediaFinalizeCmdCtrl_t_
{
    ResMgr_AppId_e eAppId;
} MediaFinalizeCmdCtrl_t;

typedef struct MediaForceResumeCmdCtrl_t_
{
    ResMgr_AppId_e eAppId;
} MediaForceResumeCmdCtrl_t;

typedef struct MediaSetTmpVolCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u8 uVolume;
    u8 uVolRange;
} MediaSetTmpVolCtrl_t;

typedef struct MediaSetConfigCtrl_t_
{
    ResMgr_AppId_e eAppId;
    MediaSetConfigParm_t tMediaConfig;
} MediaSetConfigCtrl_t;

typedef struct MediaUpdateConfigCtrl_t_
{
    ResMgr_AppId_e eAppId;
} MediaUpdateConfigCtrl_t;

typedef struct MediaDynamicIdRegCtrl_t_
{
    ResMgr_AppId_e *pAppId;
	ResMgr_ConfigSet_e eConfigSet;
	ResMgr_TaskId_e eTaskId;
} MediaDynamicIdRegCtrl_t;

typedef struct MediaDynamicIdDeregCtrl_t_
{
    ResMgr_AppId_e eAppId;
} MediaDynamicIdDeregCtrl_t;

typedef struct MediaCheckFormatCtrl_t_
{
    ResMgr_AppId_e eAppId;
    Media_FormatGroup_e eGroup;
    Media_Format_e eFormat;
    bool *pSuccess;
    bool *pSupport;
} MediaCheckFormatCtrl_t;

typedef struct MediaCheckPlaybackFormatCtrl_t_
{
    ResMgr_AppId_e eAppId;
    Media_Format_e eFormat;
    bool *pSuccess;
    bool *pSupport;
} MediaCheckPlaybackFormatCtrl_t;

typedef struct MediaEmuMaxRomSizeCtrl_t_
{
    ResMgr_AppId_e eAppId;
    bool *pSuccess;
    u32 *pMaxSize;
} MediaEmuMaxRomSizeCtrl_t;

typedef struct MediaCheckVdoCodecCtrl_t_
{
    ResMgr_AppId_e eAppId;
    Media_VdoCodec_e eVdoCodec;
    bool *pSuccess;
    bool *pSupport;
} MediaCheckVdoCodecCtrl_t;

typedef struct MediaCheckAudCodecCtrl_t_
{
    ResMgr_AppId_e eAppId;
    Media_AudCodec_e eAudCodec;
    bool *pSuccess;
    bool *pSupport;
} MediaCheckAudCodecCtrl_t;

typedef struct MediaCheckVdoFpsCtrl_t_
{
    ResMgr_AppId_e eAppId;
    Media_VdoEncodeFps_e eVdoEncFps;
    bool *pSuccess;
    bool *pSupport;
} MediaCheckVdoFpsCtrl_t;

typedef struct MediaCheckVdoResCtrl_t_
{
    ResMgr_AppId_e eAppId;
    Media_VdoCodec_e eVdoCodec;
    Media_VdoEncodeRes_e eVdoEncRes;
    bool *pSuccess;
    bool *pSupport;
} MediaCheckVdoResCtrl_t;

typedef struct MediaGetPlatformCapabilityCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u32 *pPlatCapability;
    bool *pSuccess;
} MediaGetPlatformCapabilityCtrl_t;

typedef struct MediaGetPlatformChipTypeCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u32 *pChipType;
    bool *pSuccess;
} MediaGetPlatformChipTypeCtrl_t;

typedef struct MediaCheckHWScalarOccupiedCtrl_t_
{
    bool *pIsHWScalarOccupied;
} MediaCheckHWScalarOccupiedCtrl_t;

typedef struct MediaIsTaskIdleCtrl_t_
{
    bool *pIsIdle;
} MediaIsTaskIdleCtrl_t;

typedef struct MediaLocalToneCtrl_t_
{
    bool bEnable;
} MediaLocalToneCtrl_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void MediaTaskStgr_InitCtrlHdlr(CmdMgrStgrHdl_t pHandle);
void MediaTaskStgr_UninitCtrlHdlr(CmdMgrStgrHdl_t pHandle);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateDtmfCtrlReq(ResMgr_AppId_e eAppId);
bool MediaTaskStgr_HandleEnableDtmf(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
bool MediaTaskStgr_HandleDisableDtmf(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

__SLDPM_FREE__ ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateIsDtmfDisabledCtrlReq(ResMgr_AppId_e eAppId, bool *pDisabled);
bool MediaTaskStgr_HandleIsDtmfDisabled(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateInitDefVolReq(u8 uVolUserId, u8 uDefVol, u8 uVolRange);
bool MediaTaskStgr_HandleInitDefVol(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateInitDefProfileVolReq(u8 uVolUserId, MediaProfileVol_t *pProfileVol);
bool MediaTaskStgr_HandleInitDefProfileVol(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateSetActiveProfileReq(u8 uVolUserId, MediaProfileType_e eProfileType);
bool MediaTaskStgr_HandleSetActiveProfile(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateGetActiveProfileReq(u8 uVolUserId, MediaProfileType_e *pProfileType);
bool MediaTaskStgr_HandleGetActiveProfile(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateRegVolCtrlReq(ResMgr_AppId_e eAppId, u8 uVolUserId);
bool MediaTaskStgr_HandleRegVolCtrl(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateDeregVolCtrlReq(ResMgr_AppId_e eAppId);
bool MediaTaskStgr_HandleDeregVolCtrl(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateSetVolReq(ResMgr_AppId_e eAppId, u8 uVolUserId, u8 uVolume);
ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateSetChannelVolReq(ResMgr_AppId_e eAppId, u8 uVolUserId, AudChannel_e eChannel,u8 uVolume);
bool MediaTaskStgr_HandleSetVol(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateSetBalanceReq(ResMgr_AppId_e eAppId, u8 uVolUserId, AudChannel_e eChannel,s8 sBalance);
bool MediaTaskStgr_HandleSetBalance(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateGetVolReq(ResMgr_AppId_e eAppId, u8 *pVolume, u8 *pVolRange);
bool MediaTaskStgr_HandleGetVol(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateRegDeviceChangedCbReq(ResMgr_AppId_e eAppId, u32 uCusData, MediaCtrl_DeviceChanged pFn);
bool MediaTaskStgr_HandleRegDeviceChangedCb(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateRegBtStatusChangedCnfCbReq(ResMgr_AppId_e eAppId, BtStatusChangedCb pFn);
bool MediaTaskStgr_HandleRegBtStatusChangedCnfCb(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

bool MediaTaskStgr_HandleSetDeviceStatus(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

bool MediaTaskStgr_HandleSetSpeakerType(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
bool MediaTaskStgr_HandleGetResumeRestart(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
bool MediaTaskStgr_HandleExecResumeRestart(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t ResMgr_CreateGetSpeakerTypeReq(ResMgr_AppId_e eAppId, u32 *pSpeakerType);
bool MediaTaskStgr_HandleGetSpeakerType(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateSetPrefPathReq(ResMgr_AppId_e eAppId, u8 uPath, u16 uResInfo);
bool MediaTaskStgr_HandleSetPrefPath(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateGetPathReq(ResMgr_AppId_e eAppId, AudPath_e *pPath, AudChannel_e *pChannel);
bool MediaTaskStgr_HandleGetPath(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateSetTmpVolReq(ResMgr_AppId_e eAppId, u8 uVolume, u8 uRange);
bool MediaTaskStgr_HandleSetTmpVol(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

/*
    Set media configurations
*/
ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateSetMediaConfigReq(ResMgr_AppId_e eAppId, MediaSetConfigParm_t *pMediaConfig);
bool MediaTaskStgr_HandleSetMediaConfigReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateUpdateMediaConfigReq(ResMgr_AppId_e eAppId);
bool MediaTaskStgr_HandleUpdateMediaConfigReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateFinalizeCmdReq(ResMgr_AppId_e eAppId);
bool MediaTaskStgr_HandleFinalizeCmd(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateForceResumeCmdReq(ResMgr_AppId_e eAppId);
bool MediaTaskStgr_HandleForceResumeCmd(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateGetCapabilityReq(ResMgr_AppId_e eAppId);
bool MediaTaskStgr_HandleGetMmpCapabilityReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateCheckFormatReq(ResMgr_AppId_e eAppId, Media_FormatGroup_e eGroup, Media_Format_e eFormat, bool *pSuccess, bool *pSupport);
bool MediaTaskStgr_HandleCheckFormatReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateCheckPlaybackFormatReq(ResMgr_AppId_e eAppId, Media_Format_e eFormat, bool *pSuccess, bool *pSupport);
bool MediaTaskStgr_HandleCheckPlaybackFormatReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateEmuMaxRomSizeReq(ResMgr_AppId_e eAppId, bool *pSuccess, u32 *pMaxSize);
bool MediaTaskStgr_HandleEmuMaxRomSizeReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateCheckVdoCodecReq(ResMgr_AppId_e eAppId, Media_VdoCodec_e eVdoCodec, bool *pSuccess, bool *pSupport);
bool MediaTaskStgr_HandleCheckVdoCodecReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateCheckAudCodecReq(ResMgr_AppId_e eAppId, Media_AudCodec_e eAudCodec, bool *pSuccess, bool *pSupport);
bool MediaTaskStgr_HandleCheckAudCodecReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateCheckVdoFpsReq(ResMgr_AppId_e eAppId, Media_VdoEncodeFps_e eVdoEncFps, bool *pSuccess, bool *pSupport);
bool MediaTaskStgr_HandleCheckVdoEncFpsReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateCheckVdoResReq(ResMgr_AppId_e eAppId, Media_VdoCodec_e eVdoCodec, Media_VdoEncodeRes_e eVdoEncRes, bool *pSuccess, bool *pSupport);
bool MediaTaskStgr_HandleCheckVdoEncResReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateGetPlatformCapabilityReq(ResMgr_AppId_e eAppId, u32 *pPlatCapability, bool* pIsSuccess);
bool MediaTaskStgr_HandleGetPlatformCapabilityReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateGetPlatformChipTypeReq(ResMgr_AppId_e eAppId, u32 *pChipType, bool* pIsSuccess);
bool MediaTaskStgr_HandleGetPlatformChipTypeReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateCheckHWScalarOccupiedReq(bool *pIsHWScalarOccupied);
bool MediaTaskStgr_HandleCheckHWScalarOccupiedReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateGetApPathSettingReq(ResMgr_AppId_e eAppId, MediaResInfo_e eResInfo, AudPath_e *pPath);
bool MediaTaskStgr_HandleGetApPathSetting(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

__SLDPM_FREE__ ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateIsTaskIdleCtrlReq(bool *pIsIdle);
__SLDPM_FREE__ bool MediaTaskStgr_HandleIsTaskIdle(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateGetResumeRestartReq(ResMgr_AppId_e eAppId, u8 *pGetResumeRestart);
ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateResumeRestartCtrlReq(ResMgr_AppId_e eAppId, void* pAudCb, u16 nAudCbSize);

ResMgr_CtrlReqHandle_t MediaTaskStgr_CreateLocalToneReq(bool bEnable);
bool MediaTaskStgr_HandleLocalToneReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

#endif //__MEDIACTRLHANDLERITF_H__

