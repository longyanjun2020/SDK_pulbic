/**
* @file    mmi_srv_audio.h
* @brief  The document describes the service wrapper interface of AudioSrv
*
*
* @author
* @version $Id: mmi_srv_audio.h 33169 2009-06-12 05:19:42Z johnson.yeh $
*/

#ifndef __MMI_SRV_AUDIO_H__
#define __MMI_SRV_AUDIO_H__
/*-------------------------------------------------------------------------*/
#include "mmi_audiosrv.h"
/*-------------------------------------------------------------------------*/
/**
SrvAudioQueryAudioMixingSupport
@brief  Query if Audio Mixing is supported (VOICE+STEREO audio mixing)
 */
MAE_Ret SrvAudioQueryAudioMixingSupport(bool *pAudioMixingSupported);

/**
SrvAudioSuspendBackgroundMusic
@brief  Suspend background playing music
 */
MAE_Ret SrvAudioSuspendBackgroundMusic(void);

/**
SrvAudioResumeBackgroundMusic
@brief  Resume background playing music
 */
MAE_Ret SrvAudioResumeBackgroundMusic(void);

/**
SrvAudioGetAudFileInfo
@brief  Get the information by an audio file

@param[in]      pURL			Audio file URL
@param[in]      nCusData
@param[in]      pfnCallBack		Get audio file information callback function pointer

@return MAE_RET_SUCCESS      If successful
@return MAE_RET_FAILED          Invalid/unknown path
 */
MAE_Ret SrvAudioGetAudFileInfo(MAE_WChar *pURL, u32 nCusData, AudioSrvFileInfoCb pfnCallBack);

/**
SrvAudioPlay
@brief  Play an audio file by URL

@param[in]      pURL			Audio file URL
@param[in]      nPosition		Start position
@param[in]      ePlayMode
@param[in]      pfnCallBack		Play audio file call back function pointer.

@return MAE_RET_SUCCESS      If successful
@return MAE_RET_FAILED          Invalid/unknown path
 */
MAE_Ret SrvAudioPlay(MAE_WChar *pURL, u32 nPosition, AudioSrvPlayMode_e ePlayMode, AudioSrvCb pfnCallBack);

/**
SrvAudioPlayStream
@brief  Play an audio file by streaming

@param[in]      pRawData		Audio data
@param[in]      nDataLength
@param[in]      eMimeType
@param[in]      eStreamMode
@param[in]      ePlayMode
@param[in]      pfnCallBack		Play stream call back function pointer.

@return MAE_RET_SUCCESS      If successful
@return MAE_RET_FAILED          Invalid/unknown path
 */
MAE_Ret SrvAudioPlayStream
(
    void *pRawData,
    u32 nDataLength,
    MediaSrvMimeType_e eMimeType,
    AudioSrvStreamMode_e eStreamMode,
    AudioSrvPlayMode_e ePlayMode,
    AudioSrvCb pfnCallBack
);

/**
SrvAudioPlayTone
@brief  Play a tone

@param[in]      eToneID
@param[in]      eVolRange
@param[in]      eVolume
 */
MAE_Ret SrvAudioPlayTone(AudioSrvToneID_e eToneID, AudioSrvToneVolLevel_e eVolRange, AudioSrvToneVolLevel_e eVolume);

/**
SrvAudioPlayKeypadTone
@brief  Play a keypad tone

@param[in]      eToneID
@param[in]      eVolRange
@param[in]      eVolume
 */
MAE_Ret SrvAudioPlayKeypadTone(AudioSrvToneID_e eToneID, AudioSrvToneVolLevel_e eVolRange, AudioSrvToneVolLevel_e eVolume);

/**
SrvAudioPlayForceResume
@brief  Force to resume a session
*/
void SrvAudioForceResume(void);

/**
SrvAudioEnableKeypadTone
@brief  Enable play tone
 */
MAE_Ret SrvAudioEnableKeypadTone(void);

/**
SrvAudioDisableKeypadTone
@brief  Disable play tone
 */
MAE_Ret SrvAudioDisableKeypadTone(void);

/**
SrvAudioPause
@brief  Pause current playing audio

@param[in]      pfnCallBack		Pause call back function pointer.
 */
MAE_Ret SrvAudioPause(AudioSrvCb pfnCallBack);

/**
SrvAudioResume
@brief  Resume the paused audio

@param[in]      pfnCallBack		Resume call back function pointer.
 */
MAE_Ret SrvAudioResume(AudioSrvCb pfnCallBack);

/**
SrvAudioStop
@brief  Stop playing audio

@param[in]      pfnCallBack		Stop call back function pointer.
 */
MAE_Ret SrvAudioStop(AudioSrvCb pfnCallBack);

/**
SrvAudioSetPlayStatusNotifyCb
@brief  Set a call back function to listen play status event

@param[in]      nCusData
@param[in]      pfnCallBack		Play status notify call back function pointer
 */
__SLDPM_FREE__ MAE_Ret SrvAudioSetPlayStatusNotifyCb(u32 nCusData, AudioSrvPlayStatusCb pfnCallBack);

/**
SrvAudioSetInterruptNotifyCb
@brief  Set a call back function to listen interrupt event

@param[in]      nCusData
@param[in]      pfnCallBack		Interrupt notify call back function pointer
 */
MAE_Ret SrvAudioSetInterruptNotifyCb(u32 nCusData, MediaSrvInterruptNotifyCb pfnCallBack);

/**
SrvAudioSetAccessoryNotifyCb
@brief  Set a call back function to listen accessory event

@param[in]      nCusData
@param[in]      pfnCallBack		Accessory notify call back function pointer
 */
MAE_Ret SrvAudioSetAccessoryNotifyCb(u32 nCusData, MediaSrvAccessoryNotifyCb pfnCallBack);

/**
SrvAudioSetSpectrumCb
@brief  To set audio spectrum cb.

@param[in]      nCusData
@param[in]      pfnCallBack		Spectrum notify call back function pointer
*/
MAE_Ret SrvAudioSetSpectrumCb(u32 nCusData, MediaSrvSpectrumCb pfnCallBack);

/**
SrvAudioSetSpectrumCbInterval
@brief  To set the interval of spectrum cb,
        the interval is between SPECTRUM_MIN_INTERVAL and SPECTRUM_MAX_INTERVAL.

@param[in]      nSpectrumInterval   Interval in mini seconds

@return MAE_RET_SUCCESS         If successful.
@return MAE_RET_BAD_PARAM       If input parameter error.
*/
MAE_Ret SrvAudioSetSpectrumCbInterval(u16 nSpectrumInterval);

/*-------------------------------------------------------------------------*/
#endif /* __MMI_SRV_AUDIO_H__ */
