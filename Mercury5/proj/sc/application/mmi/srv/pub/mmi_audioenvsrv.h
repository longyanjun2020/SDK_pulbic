/**
* @file mmi_audioenvsrv.h
*
* Class Id: CLSID_AUDIOENVSRV
*
* @version $Id$
*/
#ifndef __MMI_AUDIOENVSRV_H__
#define __MMI_AUDIOENVSRV_H__
/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_accessorysrv.h"
#include "mmi_common_cfg.h"
/*-------------------------------------------------------------------------*/
typedef enum AudioEnvSrvAudPath_e_
{
    AUDIOENVSRV_AUD_PATH__HANDSET_IN_HANDSET_OUT = 1
   ,/*Sync. with ESL*/
    AUDIOENVSRV_AUD_PATH__HEADSET_IN_HEADSET_OUT
   ,AUDIOENVSRV_AUD_PATH__HANDSET_IN_SPEAKER_OUT
   ,AUDIOENVSRV_AUD_PATH__SPEAKER_OUT
   ,AUDIOENVSRV_AUD_PATH__SPEAKER_LEFT_OUT
   ,AUDIOENVSRV_AUD_PATH__SPEAKER_RIGHT_OUT
   ,AUDIOENVSRV_AUD_PATH__HEADSET_OUT
   ,AUDIOENVSRV_AUD_PATH__BT_HEADSET_IN_HEADSET_OUT
 ,  //Voice Call
    AUDIOENVSRV_AUD_PATH__BT_HEADSET_OUT
 ,  //Video Call
    AUDIOENVSRV_AUD_PATH__VT_BT_HEADSET_OUT
   ,AUDIOENVSRV_AUD_PATH__HEADSET_SPEAKER_OUT
,             //Stereo voice
    AUDIOENVSRV_AUD_PATH__HANDSET_HEADSET_SPEAKER_OUT
   ,AUDIOENVSRV_AUD_PATH__NUM
   ,AUDIOENVSRV_AUD_PATH__INVALID
} AudioEnvSrvAudPath_e;

typedef enum AudioEnvSrvPrefAudPath_e_
{
    AUDIOENVSRV_PREF_AUD_PATH__HANDSET
   ,AUDIOENVSRV_PREF_AUD_PATH__HEADSET
   ,AUDIOENVSRV_PREF_AUD_PATH__SPEAKER
   ,AUDIOENVSRV_PREF_AUD_PATH__BT_HEADSET
   ,AUDIOENVSRV_PREF_AUD_PATH__RIGHT_SPEAKER
   ,AUDIOENVSRV_PREF_AUD_PATH__LEFT_SPEAKER
   ,AUDIOENVSRV_PREF_AUD_PATH__NUM
} AudioEnvSrvPrefAudPath_e;

typedef enum AudioEnvSrvVolLevel_e_
{
    AUDIOENVSRV_VOLLEVEL__DEFAULT = 4
   ,AUDIOENVSRV_VOLLEVEL__OFF = 0
   ,AUDIOENVSRV_VOLLEVEL__MIN = 0
   ,AUDIOENVSRV_VOLLEVEL__0 = AUDIOENVSRV_VOLLEVEL__MIN
   ,AUDIOENVSRV_VOLLEVEL__1 = 1
   ,AUDIOENVSRV_VOLLEVEL__2 = 2
   ,AUDIOENVSRV_VOLLEVEL__3 = 3
   ,AUDIOENVSRV_VOLLEVEL__4 = 4
   ,AUDIOENVSRV_VOLLEVEL__5 = 5
   ,AUDIOENVSRV_VOLLEVEL__6 = 6
   ,AUDIOENVSRV_VOLLEVEL__7 = 7
   ,AUDIOENVSRV_VOLLEVEL__8 = 8
   ,AUDIOENVSRV_VOLLEVEL__MAX = AUDIOENVSRV_VOLLEVEL__8
} AudioEnvSrvVolLevel_e;

typedef enum AudioEnvSrvChannel_e_
{                                                       /*Sync. with ABL */
    AUDIOENVSRV_CHAN__VOICE = 0,                        //AUD_CHAN__VOICE = 0,
    AUDIOENVSRV_CHAN__STEREO,                           //AUD_CHAN__STEREO,
    AUDIOENVSRV_CHAN__AUX,                              //AUD_CHAN__AUX,
    AUDIOENVSRV_CHAN__VOICE_SLAVE,                      //AUD_CHAN__VOICE_SLAVE,
    AUDIOENVSRV_CHAN__NUM,                              //AUD_CHAN__NUM,
    AUDIOENVSRV_CHAN__INVALID                           //AUD_CHAN__INVALID
}
AudioEnvSrvChannel_e;

typedef enum AudioEnvSrvProfileType_e_
{
    AUDIOENVSRV_PROFILE_TYPE__NORMAL
   ,AUDIOENVSRV_PROFILE_TYPE__MEETING
   ,AUDIOENVSRV_PROFILE_TYPE__OUTDOOR
   ,AUDIOENVSRV_PROFILE_TYPE__SILENT
   ,AUDIOENVSRV_PROFILE_TYPE__USER_DEFINE
   ,AUDIOENVSRV_PROFILE_TYPE__HEADSET
   ,AUDIOENVSRV_PROFILE_TYPE__BLUETOOTH
   ,AUDIOENVSRV_PROFILE_TYPE__POWER_SAVING
   ,AUDIOENVSRV_PROFILE_TYPE__NUM
   ,AUDIOENVSRV_PROFILE_TYPE__INVALID = 0xFF,
} AudioEnvSrvProfileType_e;

typedef enum AudEnvSrvSpeakerType_e_
{
    AUDIOENVSRV_SPEAKER_TYPE_MONO
   ,AUDIOENVSRV_SPEAKER_TYPE_STEREO
   ,AUDIOENVSRV_SPEAKER_TYPE_NUM
} AudEnvSrvSpeakerType_e;

typedef struct AudioEnvSrvProfileVol_t_
{
    u8 nDefVol[AUDIOENVSRV_PROFILE_TYPE__NUM];
    u8 aDefChannelVol[AUDIOENVSRV_PROFILE_TYPE__NUM][AUDIOENVSRV_CHAN__NUM];
    u8 nDefVolRange[AUDIOENVSRV_PROFILE_TYPE__NUM];
    s8 aDefBalanceVol[AUDIOENVSRV_PROFILE_TYPE__NUM][AUDIOENVSRV_CHAN__NUM];
} AudioEnvSrvProfileVol_t;

typedef struct AudioEnvSrvConfigCmd_t_
{
    u32 nPortID;
    u8 nModuleID;
    u8 nCmdID;	//refer to Item Index in doc.
    u8 nFunID;
    u8 nStatus;
    u8 *pu8Data;
    u32	u32MemorySize;
} AudioEnvSrvConfigCmd_t;//AudPEQ_CMD_s

/**
 * IAUDIOENVSRV Interfaces
 */
#define INHERIT_IAUDIOENVSRV(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(IAUDIOENVSRV);

#define IAUDIOENVSRV_QueryInterface(pICntlr, id, pp, po)         GET_FUNCTBL((pICntlr), IAUDIOENVSRV)->QueryInterface(pICntlr, id, pp, po)
#define IAUDIOENVSRV_HandleEvent(pICntlr, e, p1, p2)             GET_FUNCTBL((pICntlr), IAUDIOENVSRV)->HandleEvent(pICntlr, e, p1, p2)

typedef struct AudioEnvSrv_t_
{
    DECLARE_FUNCTBL(IAUDIOENVSRV); // function table pointer
    u32 nRefCnt;     // reference count
    IACCESSORYSRV *pIAccessorySrv;
    ModelListener_t tAccessoryListener;
    AudioEnvSrvConfigCmd_t tPEQData;
    AudioEnvSrvConfigCmd_t tARPData;
    MPlayer_PitchShift_e ePitchShiftValue;
	MPlayer_EQ_e eEQValue;
} AudioEnvSrv_t;

MAE_Ret AudioEnvSrvNew(MAE_ClsId nId, void **ppObj);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Audio Env Service interface
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
AudioEnvSrvSetVolume
@brief  Set the volume

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
@param[in]  eVolume             AUDIOENVSRV_VOLLEVEL__0 etc..
*/
MAE_Ret AudioEnvSrvSetVolume(u16 nAppId, AudioEnvSrvVolLevel_e eVolume);

/**
AudioEnvSrvSetVolume
@brief  Set specific channel volume (Current support CLSID_CCAPP only, other application please use AudioEnvSrvSetVolume)

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
@param[in]  eChannel            AUDIOENVSRV_CHAN__VOICE etc...
@param[in]  eVolume             AUDIOENVSRV_VOLLEVEL__0 etc..
*/
MAE_Ret AudioEnvSrvSetChannelVolume(u16 nAppId, AudioEnvSrvChannel_e eChannel, AudioEnvSrvVolLevel_e eVolume);

/**
AudioEnvSrvSetTempVolume
@brief  Set the temporary volume

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
@param[in]  eVolume             AUDIOENVSRV_VOLLEVEL__0 etc..
*/
MAE_Ret AudioEnvSrvSetTempVolume(u16 nAppId, AudioEnvSrvVolLevel_e eVolume);

/**
AudioEnvSrvGetVolume
@brief  Get the volume

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
@param[out] pVolume             AUDIOENVSRV_VOLLEVEL__0 etc..
*/
MAE_Ret AudioEnvSrvGetVolume(u16 nAppId, AudioEnvSrvVolLevel_e *pVolume);

/**
AudioEnvSrvInitProfileVolume
@brief  Initialize the volume setting to the one of profile

@param[in]  pProfileVol         profile volume settings
*/
void AudioEnvSrvInitProfileVolume(AudioEnvSrvProfileVol_t *pProfileVol);

/**
AudioEnvSrvSetCurProfileVolume
@brief  Set the volume setting from the current profile

@param[in]  eVolume             AUDIOENVSRV_VOLLEVEL__0
*/
MAE_Ret AudioEnvSrvSetCurProfileVolume(AudioEnvSrvVolLevel_e eVolume);

/**
AudioEnvSrvSetPitchShift
@brief  Set the pitch shift setting

@param[in]  ePitchShiftValue             pitch shift value to set
*/
void AudioEnvSrvSetPitchShift(u16 nAppId, IAUDIOENVSRV *pAudioEnvSrv, MPlayer_PitchShift_e ePitchShiftValue);

/**
AudioEnvSrvSetEQ
@brief  Set the EQ setting

@param[in]  eEQValue             EQ value to set
*/
void AudioEnvSrvSetEQ(u16 nAppId, IAUDIOENVSRV *pAudioEnvSrv, MPlayer_EQ_e eEQValue);

/**
AudioEnvSrvGetPitchShift
@brief  Get the pitch shift setting

@param[in]  pPitchShiftValue             pitch shift value to get
*/
void AudioEnvSrvGetPitchShift(u16 nAppId, IAUDIOENVSRV *pAudioEnvSrv, MPlayer_PitchShift_e *pPitchShiftValue);

/**
AudioEnvSrvSetPreferAudPath
@brief  Set the prefer path

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
@param[in]  ePrefAudPath        AUDIOENVSRV_PREF_AUD_PATH__HANDSET etc..
*/
MAE_Ret AudioEnvSrvSetPreferAudPath(u16 nAppId, AudioEnvSrvPrefAudPath_e ePrefAudPath);

/**
AudioEnvSrvGetCurAudPath
@brief  Get Current audio path

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
@param[out] pCurAudPath         AUDIOENVSRV_AUD_PATH__HANDSET_IN_HANDSET_OUT etc..
*/
MAE_Ret AudioEnvSrvGetCurAudPath(u16 nAppId, AudioEnvSrvAudPath_e *pCurAudPath);

/**
AudioEnvSrvGetCurSpeakerType
@brief  Get current speaker type.

@param[in]  nAppId              RES_MGR_APP_ID__EM etc..
@param[out] pCurSpeakerType     AUDIOENVSRV_SPEAKER_TYPE_MONO etc..

@retval MAE_RET_SUCCESS         Get Speaker type successfully.
@retval MAE_RET_FAILED          Get Speaker type unsuccessfully.
@retval MAE_RET_BAD_PARAM       Parameter error.
*/
MAE_Ret AudioEnvSrvGetCurSpeakerType(u16 nAppId, AudEnvSrvSpeakerType_e *pCurSpeakerType);


/**
AudioEnvSrvSetActiveProfile
@brief  Set the active profile ID

@param[in]  nProfileID          AUDIOENVSRV_PROFILE_TYPE__NORMAL etc..
*/
MAE_Ret AudioEnvSrvSetActiveProfile(u8 nProfileID);

/**
AudioEnvSrvGetActiveProfile
@brief  Get the active profile ID

@param[out] nProfileID          AUDIOENVSRV_PROFILE_TYPE__NORMAL etc..
*/
MAE_Ret AudioEnvSrvGetActiveProfile(u32 *pProfileID);

/**
AudioEnvSrvIsHeadsetInsert
@brief  Check the status of headset plug-in or not.

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..

@retval TURE        Headset is inserted.
@retval FALSE       Headset is not inserted.
*/
boolean AudioEnvSrvIsHeadsetInsert(u16 nAppId);

/**
AudioEnvSrvInsertHeadset
@brief  Insert Headset

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
*/
MAE_Ret AudioEnvSrvInsertHeadset(u16 nAppId);

/**
AudioEnvSrvPullHeadset
@brief  Pull out headset

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
*/
MAE_Ret AudioEnvSrvPullHeadset(u16 nAppId);

/**
AudioEnvSrvIsBtHeadsetConnect
@brief  Check BT headset is inserted or not.

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..

@retval TRUE        BT headset is inserted.
@retval FALSE       BT headset is not inserted.
*/
boolean AudioEnvSrvIsBtHeadsetConnect(u16 nAppId);

/**
AudioEnvSrvConnectToBtHeadset
@brief  Connect to BT headset

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
*/
MAE_Ret AudioEnvSrvConnectToBtHeadset(u16 nAppId);

/**
AudioEnvSrvDisconnectToBtHeadset
@brief  Disconnect to BT headset

@param[in]  nAppId              RES_MGR_APP_ID__CCMTA etc..
*/
MAE_Ret AudioEnvSrvDisconnectToBtHeadset(u16 nAppId);

/**
AudioEnvSrvInitPEQTable
@brief  Init PEQ table for Audio calibration tool

@param[in]  pIAUDIOENVSRV  service data
@param[in]  pConfigData            PEQ data about tool
*/
void AudioEnvSrvInitPEQTable(IBase *pIAUDIOENVSRV, AudioEnvSrvConfigCmd_t *pConfigData);

/**
AudioEnvSrvWritePEQTable
@brief  Write PEQ table for Audio calibration tool

@param[in]  pIAUDIOENVSRV  service data
@param[in]  pConfigData            PEQ data about tool
*/
void AudioEnvSrvWritePEQTable(IBase *pIAUDIOENVSRV, AudioEnvSrvConfigCmd_t *pConfigData);

/**
AudioEnvSrvReadPEQTable
@brief  Read PEQ table for Audio calibration tool

@param[in]  pIAUDIOENVSRV  service data
@param[in]  pConfigData            PEQ data about tool
*/
void AudioEnvSrvReadPEQTable(IBase *pIAUDIOENVSRV, AudioEnvSrvConfigCmd_t *pConfigData);

/**
AudioEnvSrvGetPEQTable
@brief  Read the PEQ table address for app to reference

@param[in]  pIAUDIOENVSRV  service data
@param[in]  pTblAddr            PEQ table return addr
@param[in]  pTblSize            PEQ table return size
*/
MAE_Ret AudioEnvSrvGetPEQTable(IAUDIOENVSRV *pAudioEnvSrv, u8 **pTblAddr, u32 *pTblSize);

/**
AudioEnvSrvSetPEQTable
@brief  Set the PEQ table address to audioenv srv and mdl

@param[in]  pIAUDIOENVSRV  service data
@param[in]  pTblAddr            PEQ table to be set to mdl.
@param[in]  nTblSize            PEQ table size
*/
MAE_Ret AudioEnvSrvSetPEQTable(IAUDIOENVSRV *pAudioEnvSrv, u8 *pTblAddr, u32 nTblSize);

/**
AudioEnvSrvInitPreProcessTable
@brief  Init PreProcess table for Audio calibration tool

@param[in]  pIAUDIOENVSRV  service data
@param[in]  pConfigData            PreProcess data about tool
*/
void AudioEnvSrvInitPreProcessTable(IBase *pIAUDIOENVSRV, AudioEnvSrvConfigCmd_t *pConfigData);

/**
AudioEnvSrvWritePreProcessTable
@brief  Write PreProcess table for Audio calibration tool

@param[in]  pIAUDIOENVSRV  service data
@param[in]  pConfigData            PreProcess data about tool
*/
void AudioEnvSrvWritePreProcessTable(IBase *pIAUDIOENVSRV, AudioEnvSrvConfigCmd_t *pConfigData);

/**
AudioEnvSrvReadPreProcessTable
@brief  Read PreProcess table for Audio calibration tool

@param[in]  pIAUDIOENVSRV  service data
@param[in]  pConfigData            PreProcessdata about tool
*/
void AudioEnvSrvReadPreProcessTable(IBase *pIAUDIOENVSRV, AudioEnvSrvConfigCmd_t *pConfigData);

MAE_Ret AudioEnvSrvSetVolumeCfg(u16 nAppId, void *pVolume);

MAE_Ret AudioEnvSrvGetVolumeCfg(u16 nAppId, void *pVolume);

__SLDPM_FREE__ MAE_Ret AudioEnvSrvGetCfgID(u16 nAppId, u32 *pCFGID);

/*-------------------------------------------------------------------------*/
#endif /* __MMI_AUDIOENVSRV_H__ */
