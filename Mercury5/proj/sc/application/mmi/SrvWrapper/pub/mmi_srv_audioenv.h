/**
* @file    mmi_srv_audioenv.h
* @brief  The document describes the service wrapper interface of AudioEnv
*
*
* @author
* @version $Id:$
*/

#ifndef __MMI_SRV_AUDIOENV_H__
#define __MMI_SRV_AUDIOENV_H__
/*-------------------------------------------------------------------------*/
#include "mmi_audioenvsrv.h"
/*-------------------------------------------------------------------------*/

/**
SrvAudioEnvSetVolume
@brief  Set volume level and update

@param[in]      eVolume         The range is from AUDIOENVSRV_VOLLEVEL__0 to AUDIOENVSRV_VOLLEVEL__8.
 */
MAE_Ret SrvAudioEnvSetVolume(AudioEnvSrvVolLevel_e eVolume);

/**
SrvAudioEnvSetTempVolume
@brief  Set volume level

@param[in]      eVolume         The range is from AUDIOENVSRV_VOLLEVEL__0 to AUDIOENVSRV_VOLLEVEL__8.
 */
MAE_Ret SrvAudioEnvSetTempVolume(AudioEnvSrvVolLevel_e eVolume);

/**
SrvAudioEnvSetMute
@brief  Mute the volume
 */
MAE_Ret SrvAudioEnvSetMute(void);

/**
SrvAudioEnvGetVolume
@brief  Get volume level

@param[out]      pVolume		Point to the volume level variable
 */
MAE_Ret SrvAudioEnvGetVolume(AudioEnvSrvVolLevel_e *pVolume);

MAE_Ret SrvAudioEnvGetVolumeCfg(void *pItemBuffer);

MAE_Ret SrvAudioEnvSetVolumeCfg(void *pItemBuffer);

MAE_Ret SrvAudioEnvGetCfgID(MAE_ClsId nClsId, u32 *pCFGIDBuffer);

/**
SrvAudioEnvSetCurProfileVolume
@brief  Set current profile volume level

@param[in]      eVolume         The range is from AUDIOENVSRV_VOLLEVEL__0 to AUDIOENVSRV_VOLLEVEL__8.
 */
MAE_Ret SrvAudioEnvSetCurProfileVolume(AudioEnvSrvVolLevel_e eVolume);

#ifdef __FM_PEQ_ENABLE__
/**
SrvAudioEnvSetEQ
@brief  Set EQ

@param[in]      eEQValue		The EQ value to set
 */
void SrvAudioEnvSetEQ(MPlayer_EQ_e eEQValue);
#endif

/**
SrvAudioEnvSetPitchShift
@brief  Set pitch shift

@param[in]      ePitchShiftValue		The pitch shift value to set
 */
void SrvAudioEnvSetPitchShift(MPlayer_PitchShift_e ePitchShiftValue);

/**
SrvAudioEnvGetPitchShift
@brief  Get pitch shift

@param[in]      pPitchShiftValue		The pitch shift value to get
 */
void SrvAudioEnvGetPitchShift(MPlayer_PitchShift_e *pPitchShiftValue);

/**
SrvAudioEnvSetPreferAudPath
@brief  Set prefer audio path

@param[in]      ePrefAudPath    The prefer path is such as AUDIOENVSRV_PREF_AUD_PATH__HANDSET etc..
 */
MAE_Ret SrvAudioEnvSetPreferAudPath(AudioEnvSrvPrefAudPath_e ePrefAudPath);

/**
SrvAudioEnvGetCurAudPath
@brief  Get current audio path

@param[out]      pCurAudPath	Point to the audio path variable
 */
MAE_Ret SrvAudioEnvGetCurAudPath(AudioEnvSrvAudPath_e *pCurAudPath);

/**
SrvAudioEnvGetCurSpeakerType
@brief  Get current speaker type

@param[out]      pCurSpeakerType    Point to the speaker type variable

@retval MAE_RET_SUCCESS         Get Speaker type successfully.
@retval MAE_RET_FAILED          Get Speaker type unsuccessfully.
@retval MAE_RET_BAD_PARAM       Parameter error.
 */
MAE_Ret SrvAudioEnvGetCurSpeakerType(AudEnvSrvSpeakerType_e *pCurSpeakerType);

/**
SrvAudioEnvSetActiveProfile
@brief  Set active profile

@param[in]      nProfileID      The profile ID is such as MEDIA_PROFILE_TYPE__NORMAL etc..
 */
MAE_Ret SrvAudioEnvSetActiveProfile(u8 nProfileID);

/**
SrvAudioEnvGetActiveProfile
@brief  Get active profile

@param[out]      pProfileID		Point to the active profile variable
 */
MAE_Ret SrvAudioEnvGetActiveProfile(u32 *pProfileID);

/**
SrvAudioEnvIsHeadsetInsert
@brief  Check if the headset is inserted

@return TRUE            Headset is inserted
@return FALSE           Headset is not inserted
 */
boolean SrvAudioEnvIsHeadsetInsert(void);

/**
SrvAudioEnvInsertHeadset
@brief  Insert headset
 */
MAE_Ret SrvAudioEnvInsertHeadset(void);

/**
SrvAudioEnvPullHeadset
@brief  Pull headset
 */
MAE_Ret SrvAudioEnvPullHeadset(void);

/**
SrvAudioEnvIsBtHeadsetConnect
@brief  Check if the BT headset is connected

@retval TRUE           BT headset is connected
@retval FALSE          BT headset is not connected
 */
boolean SrvAudioEnvIsBtHeadsetConnect(void);

/**
SrvAudioEnvConnectToBtHeadset
@brief  Connect to BT headset
 */
MAE_Ret SrvAudioEnvConnectToBtHeadset(void);

/**
SrvAudioEnvDisconnectToBtHeadset
@brief  Disconnect to BT headset
 */
MAE_Ret SrvAudioEnvDisconnectToBtHeadset(void);

/**
SrvAudioEnvGetPEQTable
@brief  Get PEQ table addr and size

@param[out]      pTblAddr    Double Pointer to PEQ table addr
@param[out]      pTblSize    Pointer to table size

@retval MAE_RET_SUCCESS                 Get PEQ table addr and size successfully.
@retval MAE_RET_OUT_OF_MEMORY           PEQ table addr memory is not valid
 */
MAE_Ret SrvAudioEnvGetPEQTable(u8 **pTblAddr, u32 *pTblSize);

/**
SrvAudioEnvSetPEQTable
@brief  Set PEQ table addr and size

@param[out]      pTblAddr    Pointer to set PEQ table addr
@param[out]      nTblSize    Table size

@retval MAE_RET_SUCCESS                 Set PEQ table addr and size successfully.
@retval MAE_RET_OUT_OF_MEMORY           PEQ table addr memory is not valid
 */
MAE_Ret SrvAudioEnvSetPEQTable(u8 *pTblAddr, u32 nTblSize);

#endif /* __MMI_SRV_AUDIOENV_H__ */
