/**
* @file    mmi_srv_audioplayer.h
* @brief
*
*
*/
#ifndef __MMI_SRV_AUDIOPLAYER_H__
#define __MMI_SRV_AUDIOPLAYER_H__
/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_audioplayersrv.h"

typedef enum SrvAudioPlayerPlayStatus_e_
{
    SRV_MPLAYER_PLAYSTATUS_NONE,
    SRV_MPLAYER_PLAYSTATUS_PLAY_SUCCESS,
    SRV_MPLAYER_PLAYSTATUS_PLAY_FAILED,
    SRV_MPLAYER_PLAYSTATUS_PAUSE_SUCCESS,
    SRV_MPLAYER_PLAYSTATUS_PAUSE_FAILED,
    SRV_MPLAYER_PLAYSTATUS_STOP_SUCCESS,
    SRV_MPLAYER_PLAYSTATUS_STOP_FAILED,
    SRV_MPLAYER_PLAYSTATUS_SUSPEND_IND,
    SRV_MPLAYER_PLAYSTATUS_RESUME_IND,
    SRV_MPLAYER_PLAYSTATUS_PLAYBACKGROUND_IND
} SrvAudioPlayerPlayStatus_e;

typedef enum SrvAudioPlayerCommonNotify_e_
{
    SRV_MPLAYER_COMMON_NOTIFY_NONE,
    SRV_MPLAYER_COMMON_NOTIFY_SUSPEND_DONE,
    SRV_MPLAYER_COMMON_NOTIFY_END_PLAYING,
    SRV_MPLAYER_COMMON_NOTIFY_LYRICS_SUCCESS,
    SRV_MPLAYER_COMMON_NOTIFY_LYRICS_FAILED,
    SRV_MPLAYER_COMMON_NOTIFY_PCLINK_ACTIVATED,
    SRV_MPLAYER_COMMON_NOTIFY_SDDB_DISABLE,
    SRV_MPLAYER_COMMON_NOTIFY_COMMAND_SKIP,
    SRV_MPLAYER_COMMON_NOTIFY_COMMAND_REJECT,
    SRV_MPLAYER_COMMON_NOTIFY_FILE_FORMAT_NOT_SUPPORT,
    SRV_MPLAYER_COMMON_NOTIFY_FILE_NOT_EXIST,
    SRV_MPLAYER_COMMON_NOTIFY_LOAD_LAST_PLAYINFO_DONE,
    SRV_MPLAYER_COMMON_NOTIFY_SEEK_SUCCESS,
    SRV_MPLAYER_COMMON_NOTIFY_SEEK_FAILED,
    SRV_MPLAYER_COMMON_NOTIFY_SEEK_CANCEL,
    SRV_MPLAYER_COMMON_NOTIFY_SEEK_COMPLETE
} SrvAudioPlayerCommonNotify_e;

////////////////////
//Wrapper CALLBACK//
////////////////////

/**
SrvAudioPlayer EV and Callback Function descript
@brief  The interface of Service Client is use to set the indicator-callback to CB module

Group1: SrvMplayerSetPlayStausCB/SrvAudioPlayerPlayStatusCb/SrvMplayerExePlayStatusEvToCB
MASK = MPLAYERSRV_MASK_PLAYSTATUS
MPLAYERSRV_EVT_PlaySuccess
MPLAYERSRV_EVT_PlayFailed
MPLAYERSRV_EVT_PauseSuccess
MPLAYERSRV_EVT_PauseFailed
MPLAYERSRV_EVT_StopSuccess
MPLAYERSRV_EVT_StopFailed
MPLAYERSRV_EVT_SuspendInd
MPLAYERSRV_EVT_ResumeInd
MPLAYERSRV_EVT_PlayBackgroundInd

Group2:SrvAudioPlayerSetPlayTickCb/SrvAudioPlayerPlayTickCb/SrvMplayerExePlayTickEvToCB
MASK = AUDIOPLAYERSRV_MASK_PLAYING_TICK
MPLAYERSRV_EVT_PlayTick

Group3:SrvAudioPlayerSetPlayingMediaNameCb/SrvAudioPlayerPlayingMediaNameCb/SrvMplayerExePlayingMediaNameEvToCB
MASK = AUDIOPLAYERSRV_MASK_PLAYING_MEDIA_NAME
MPLAYERSRV_EVT_PlayingMediaName

Group4:SrvMplayerSetLyricInfoCB/SrvMplayerLyricInfoCB/SrvMplayerExeLyricInfoEvToCB
MASK = AUDIOPLAYERSRV_MASK_LYRICINFO
MPLAYERSRV_EVT_LyricsInfo

Group5:SrvAudioPlayerSetInsertContentToPlaylistCb/SrvAudioPlayerInsertContentToPlaylistCb/SrvMplayerExeInsertContentToPlaylistEvToCB
MASK = AUDIOPLAYERSRV_MASK_INSERT_CONTENT_TO_PLAYLIST
MPLAYERSRV_EVT_InsertContentToPlaylist

Group6:SrvAudioPlayerSetCommonCb/SrvAudioPlayerCommonCb/SrvMplayerExeCommonEvToCB
MASK = MPLAYERSRV_MASK_COMMON
MPLAYERSRV_EVT_PlayMusic
MPLAYERSRV_EVT_SuspendDone
MPLAYERSRV_EVT_EndPlaying
MPLAYERSRV_EVT_LyricsSuccess
MPLAYERSRV_EVT_LyricsFailed
MPLAYERSRV_EVT_PCLinkActivated
MPLAYERSRV_EVT_SDDB_DISABLED
MPLAYERSRV_EVT_CommandSkip
MPLAYERSRV_EVT_CommandReject
MPLAYERSRV_EVT_FileFormatNotSupport
MPLAYERSRV_EVT_FileNotExist
MPLAYERSRV_EVT_LoadLastPlayInfoDone

Group7:SrvAudioPlayerSetPlayingIndexCb/SrvAudioPlayerPlayingIndexCb/SrvMplayerExeCommonEvToCB
MASK = AUDIOPLAYERSRV_MASK_PLAYING_INDEX
MPLAYERSRV_EVT_PlayNext
MPLAYERSRV_EVT_PlayPrevious
*/

typedef void (* SrvAudioPlayerPlayStatusCb)(void *pThis, SrvAudioPlayerPlayStatus_e ePlayStatus);
/**
SrvAudioPlayerSetPlayStatusCb
@brief  The interface of Service Client is use to set CB to listen the play status.

@param[in]      pfnCallBack             Play status Call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetPlayStatusCb(SrvAudioPlayerPlayStatusCb  pfnCallBack);

typedef void (* SrvAudioPlayerPlayTickCb)(void *pThis, u32 nTimeElapsed);
/**
SrvAudioPlayerSetPlayTickCb
@brief  The interface of Service Client is use to set CB to listen the play tick.

@param[in]      pfnCallBack             MPLAYERSRV_EVT_PlayTick Call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetPlayTickCb(SrvAudioPlayerPlayTickCb  pfnCallBack);

typedef void (* SrvAudioPlayerTotalTimeUpdateCb)(void *pThis, u32 nTotalTime);
/**
SrvAudioPlayerSetTotalTimeUpdateCb
@brief  The interface of Service Client is use to set CB to listen the total time update notify.

@param[in]      pfnCallBack             MPLAYERSRV_EVT_TotalTimeUpdate Call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetTotalTimeUpdateCb(SrvAudioPlayerTotalTimeUpdateCb pfnCallBack);

typedef void (* SrvAudioPlayerPlayingMediaNameCb)(void *pThis, MAE_WChar *pMediaName);
/**
SrvAudioPlayerSetPlayingMediaNameCb
@brief  The interface of Service Client is use to set CB to listen the playing meida name.

@param[in]      pfnCallBack             MPLAYERSRV_EVT_PlayingMediaName Call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetPlayingMediaNameCb(SrvAudioPlayerPlayingMediaNameCb  pfnCallBack);

typedef void (* SrvAudioPlayerLyricsInfoCb)(void *pThis, MAE_WChar *pLyricsInfo);
/**
SrvAudioPlayerSetLyricsInfoCb
@brief  The interface of Service Client is use to set CB to listen the lyric info.

@param[in]      pfnCallBack             MPLAYERSRV_EVT_LyricsInfo Call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetLyricsInfoCb(SrvAudioPlayerLyricsInfoCb pfnCallBack);

typedef void (* SrvAudioPlayerInsertContentToPlaylistCb)(void *pThis, u32 nInsertIdx);
/**
SrvAudioPlayerSetInsertContentToPlaylistCb
@brief  The interface of Service Client is use to set CB to listen the index of insert content.

@param[in]      pfnCallBack             MPLAYERSRV_EVT_InsertContentToPlaylist Call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetInsertContentToPlaylistCb(SrvAudioPlayerInsertContentToPlaylistCb pfnCallBack);

typedef void (* SrvAudioPlayerSeekCancelCb)(void *pThis, u32 nParam1);
/**
SrvAudioPlayerSetCommonCb
@brief  The interface of Service Client is use to set CB to listen common event.

@param[in]      pfnCallBack             Player common event call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetSeekCancelCb(SrvAudioPlayerSeekCancelCb pfnCallBack);

typedef void (* SrvAudioPlayerCommonCb)(void *pThis, SrvAudioPlayerCommonNotify_e eCommonNotify);
/**
SrvAudioPlayerSetCommonCb
@brief  The interface of Service Client is use to set CB to listen common event.

@param[in]      pfnCallBack             Player common event call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetCommonCb(SrvAudioPlayerCommonCb  pfnCallBack);

typedef void (* SrvAudioPlayerPlayingIndexCb)(void *pThis, u32 nPlayingIndex);
/**
SrvAudioPlayerSetPlayingIndexCb
@brief  The interface of Service Client is use to set CB to listen the playing index due to play next or play previous.

@param[in]      pfnCallBack             Playing index call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetPlayingIndexCb(SrvAudioPlayerPlayingIndexCb  pfnCallBack);

typedef void (* SrvAudioPlayerPlayMusicInfoCb)(void *pThis, AudioPlayerSrvFileInfo_t *pAudFileInfo);
/**
SrvAudioPlayerSetPlayMusicInfoCb
@brief  The interface of Service Client is use to set CB to listen music file information after play music.

@param[in]      pfnCallBack             Play music information call back function pointer.

@return SRVCLIENT_RET_SUCCESS           If successful.
@return SRVCLIENT_RET_FAILED            If an error happen.
@return SRVCLIENT_RET_BAD_PARAM         If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetPlayMusicInfoCb(SrvAudioPlayerPlayMusicInfoCb  pfnCallBack);

///////////////
//Wrapper API//
///////////////

/**
SrvAudioPlayerSuspendBackgroundMusic
@brief	Suspend background playing music
*/
MAE_Ret SrvAudioPlayerSuspendBackgroundMusic(void);

/**
SrvAudioPlayerResumeBackgroundMusic
@brief	Resume background playing music
*/
MAE_Ret SrvAudioPlayerResumeBackgroundMusic(void);

/**
SrvAudioPlayerGetID3Info
@brief	Get the ID3 information of an audio file

@param[in]      pURL             	Audio file URL.
@param[in]      pfnCallBack		Get ID3 information call back function pointer.
*/
MAE_Ret SrvAudioPlayerGetID3Info(MAE_WChar *pURL, AudioPlayerSrvID3InfoCb pfnCallBack);

/**
SrvAudioPlayerGetID3InfoEx
@brief	Get the ID3 extension information of an audio file

@param[in]      pURL             	Audio file URL.
@param[in]      pfnCallBack		Get ID3 extension information call back function pointer.
@param[in]      nCusData            User data
@param[in]      nCusDataSize      User data size
*/
#ifdef __MMI_ID3_SUPPORT__
MAE_Ret SrvAudioPlayerGetID3InfoEx(MAE_WChar *pURL, AudioPlayerSrvID3InfoExCb pfnCallBack, u32 nCusData);
#endif

/**
SrvAudioPlayerPlay
@brief	Start to play an audio file by the focus index in playlist

@param[in]		nFocusIndex	Focus index of file in playlist
@param[in]		nPosition 	Start position
*/
MAE_Ret SrvAudioPlayerPlay(u32 nFocusIndex, u32 nPosition);

/**
SrvAudioPlayerPause
@brief	Pause current playing audio file
*/
MAE_Ret SrvAudioPlayerPause(void);

/**
SrvAudioPlayerStop
@brief	Stop playing audio file
*/
MAE_Ret SrvAudioPlayerStop(void);

/**
SrvAudioPlayerResume
@brief	Resume the paused audio file
*/
MAE_Ret SrvAudioPlayerResume(void);

/**
SrvAudioPlayerPlayNext
@brief	Stop playing current file and start to play the next one in playlist
*/
MAE_Ret SrvAudioPlayerPlayNext(void);

/**
SrvAudioPlayerPlayPrevious
@brief	Stop playing current file and start to play the previous one in playlist
*/
MAE_Ret SrvAudioPlayerPlayPrevious(void);

/**
* SrvAudioPlayerQueryEQSupport
* @brief        Users can query whether platform support EQ setting.
*
* @param[in]    pUserEQSupported         TRUE:support, False:Not support
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the query.
* @retval       MAE_RET_BAD_PARAM        If *pUserEQSupported is NULL pointer.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
* @retval       MAE_RET_FAILED           If it fail to accept the query.
*/
#if defined(ENABLE_TIME_STRETCH)
MAE_Ret SrvAudioPlayerQueryTSSupport(bool *pUserTSSupported);
#endif
/**
* SrvAudioPlayerQueryTSSupport
* @brief        Users can query whether platform support TS setting.
*
* @param[in]    pUserTSSupported         TRUE:support, False:Not support
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the query.
* @retval       MAE_RET_BAD_PARAM        If *pUserEQSupported is NULL pointer.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
* @retval       MAE_RET_FAILED           If it fail to accept the query.
*/
#if defined(ENABLE_REVERB)
MAE_Ret SrvAudioPlayerQueryReverbSupport(bool *pUserReverbSupported);
#endif
/**
* SrvAudioPlayerQueryReverbSupport
* @brief        Users can query whether platform support Reverb setting.
*
* @param[in]    pUserReverbSupported         TRUE:support, False:Not support
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the query.
* @retval       MAE_RET_BAD_PARAM        If *pUserEQSupported is NULL pointer.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
* @retval       MAE_RET_FAILED           If it fail to accept the query.
*/
MAE_Ret SrvAudioPlayerQueryEQSupport(bool *pUserEQSupported);

/**
SrvAudioPlayerQuery3DSurroundSupport
@brief	Users can query whether platform support 3D surrounding.

@param[in]      p3DSurroundSupported        TRUE:support, False:Not support

* @retval       MAE_RET_SUCCESS             If it succeeds to accept the query.
* @retval       MAE_RET_BAD_PARAM           If *pUserEQSupported is NULL pointer.
* @retavl       MAE_RET_OUT_OF_MEMORY       If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED       If this function is not supported.
* @retval       MAE_RET_FAILED              If it fail to accept the query.
*/
MAE_Ret SrvAudioPlayerQuery3DSurroundSupport(bool *p3DSurroundSupported);

/**
SrvAudioPlayerQuerySRSSupport
@brief	Users can query whether platform support SRS setting.

@param[out]      pSRSSupported        TRUE:support, False:Not support

* @retval       MAE_RET_SUCCESS             If it succeeds to accept the query.
* @retval       MAE_RET_BAD_PARAM           If *pUserEQSupported is NULL pointer.
* @retavl       MAE_RET_OUT_OF_MEMORY       If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED       If this function is not supported.
* @retval       MAE_RET_FAILED              If it fail to accept the query.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerQuerySRSSupport(bool *pSRSSupported);
#endif

/**
SrvAudioPlayerQueryVirtualBassSupport
@brief	Users can query whether platform support Virtual Bass function.

@param[in]      pVirtualBassSupported        TRUE:support, False:Not support

* @retval       MAE_RET_SUCCESS             If it succeeds to accept the query.
* @retval       MAE_RET_BAD_PARAM           If *pUserEQSupported is NULL pointer.
* @retavl       MAE_RET_OUT_OF_MEMORY       If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED       If this function is not supported.
* @retval       MAE_RET_FAILED              If it fail to accept the query.
*/
MAE_Ret SrvAudioPlayerQueryVirtualBassSupport(bool *pVirtualBassSupported);

/**
SrvAudioPlayerSetEQ
@brief	Change the EQ setting

@param[in]      eEQMode                 Indicate an EQ mode.
*/
MAE_Ret SrvAudioPlayerSetEQ(MPlayer_EQ_e eEQMode);

/**
SrvAudioPlayerGetEQ
@brief	Get the EQ setting

@param[out]      pEQMode                 Pointer to an EQ Mode variable.
*/
MAE_Ret SrvAudioPlayerGetEQ(MPlayer_EQ_e *pEQMode);

/**
SrvAudioPlayerSetTS
@brief	Change the TS setting

@param[in]      eETSMode                 Indicate an TS mode.
*/
#if defined(ENABLE_TIME_STRETCH)
MAE_Ret SrvAudioPlayerSetTS(MPlayer_TimeStretch_e eTSMode);
#endif
/**
SrvAudioPlayerGetTS
@brief	Get the EQ setting

@param[out]      pTSMode                 Pointer to an TS Mode variable.
*/
#if defined(ENABLE_TIME_STRETCH)
MAE_Ret SrvAudioPlayerGetTS(MPlayer_TimeStretch_e *pTSMode);
#endif
/**
SrvAudioPlayerSetReverb
@brief	Change the Reverb setting

@param[in]      eEReverbMode                 Indicate an Reverb mode.
*/
#if defined(ENABLE_REVERB)
MAE_Ret SrvAudioPlayerSetReverb(MPlayer_Reverb_e eReverbMode);

/**
SrvAudioPlayerGetReverb
@brief	Get the Reverb setting

@param[out]      pReverbMode                 Pointer to an Reverb Mode variable.
*/
MAE_Ret SrvAudioPlayerGetReverb(MPlayer_Reverb_e *pReverbMode);
#endif

/**
SrvAudioPlayerSetShuffle
@brief	Set the shuffle mode

@param[in]      eShuffleMode                 Indicate the shuffle mode.
*/
MAE_Ret SrvAudioPlayerSetShuffle(MPlayer_Shuffle_e eShuffleMode);

/**
SrvAudioPlayerGetShuffle
@brief  Get the shuffle mode.

@param[out]     pShuffleMode            Pointer to the shuffle mode variable.
*/
MAE_Ret SrvAudioPlayerGetShuffle(MPlayer_Shuffle_e *pShuffleMode);

/**
SrvAudioPlayerSetRepeat
@brief	Set the repeat mode.

@param[in] 	eRepeatMode			Indicate the repeat mode.
*/
MAE_Ret SrvAudioPlayerSetRepeat(MPlayer_Repeat_e eRepeatMode);

/**
SrvAudioPlayerGetRepeat
@brief	Get the repeat mode.

@param[out] 	pRepeatMode			Pointer to the repeat mode variable.
*/
MAE_Ret SrvAudioPlayerGetRepeat(MPlayer_Repeat_e *pRepeatMode);

/**
SrvAudioPlayerSetVolume
@brief	Set the volume level.

@param[in] 	eVolumeLevel			Indicate the volume level.
*/
MAE_Ret SrvAudioPlayerSetVolume(MPlayer_VolLevel_e eVolumeLevel);

/**
SrvAudioPlayerGetVolume
@brief	Get the volume level.

@param[out] 	pVolumeLevel			Pointer to the volume level variable
*/
MAE_Ret SrvAudioPlayerGetVolume(MPlayer_VolLevel_e *pVolumeLevel);

/**
SrvAudioPlayerSet3DSurround
@brief	Set the 3D surround mode.

@param[in]	e3DSurroundMode			Indicate a 3DSurround mode.
*/
MAE_Ret SrvAudioPlayerSet3DSurround(MPlayer_3DSurround_e e3DSurroundMode);

/**
SrvAudioPlayerGet3DSurround
@brief	Get the 3D surround mode.

@param[out] 	p3DSurroundMode			Pointer to the 3DSurround mode variable.
*/
MAE_Ret SrvAudioPlayerGet3DSurround(MPlayer_3DSurround_e *p3DSurroundMode);

/**
SrvAudioPlayerSetPitchShift
@brief	Set the pitch shift value.

@param[in]	ePitchShiftValue			Indicate the pitch shift value.
*/
MAE_Ret SrvAudioPlayerSetPitchShift(MPlayer_PitchShift_e ePitchShiftValue);

/**
SrvAudioPlayerGetPitchShift
@brief	Get the pitch shift value.

@param[in]	pPitchShiftValue			Pointer to the pitch shift variable.
*/
MAE_Ret SrvAudioPlayerGetPitchShift(MPlayer_PitchShift_e *pPitchShiftValue);


/**
SrvAudioPlayerSetDolby
@brief	Set the Dolby mode.

@param[in]	eDolbyMode			Indicate a Dolby mode.
*/
MAE_Ret SrvAudioPlayerSetDolby(MPlayer_Dolby_e eDolbyMode);

/**
SrvAudioPlayerGetDolby
@brief	Get the Dolby mode.

@param[out] 	pDolbyMode			Pointer to the Dolby mode variable.
*/
void SrvAudioPlayerGetDolby(MPlayer_Dolby_e *pDolbyMode);

/**
SrvAudioPlayerSetSRSMode
@brief  Set the SRS mode.

@param[in]      eSRSMode            Indicate a SRS mode.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerSetSRS(MPlayer_SRS_e eSRSMode);
#endif

/**
SrvAudioPlayerGetSRS
@brief  Get the SRS mode

@param[out]     pSRSMode            Pointer to the SRS mode variable.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerGetSRS(MPlayer_SRS_e *pSRSMode);
#endif

/**
SrvAudioPlayerSetSRSType
@brief  Set the SRS type.

@param[in]      eSRSType            Indicate a SRS type.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerSetSRSType(MPlayer_SRS_Type_e eSRSType);
#endif

/**
SrvAudioPlayerGetSRSType
@brief  Get the SRS type.

@param[out]     pSRSType            Pointer to the SRS type variable.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerGetSRSType(MPlayer_SRS_Type_e *pSRSType);
#endif

/**
SrvAudioPlayerSetSRSParam
@brief  Set the SRS parameters' value.

@param[in]      tSRSParam           Indicate a SRS parameter structure.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerSetSRSParam(MPlayer_SRS_Param_t tSRSParam);
#endif

/**
SrvAudioPlayerGetSRSParam
@brief  Get the SRS parameters' value.

@param[out]      pSRSParam           Indicate a SRS parameter structure.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerGetSRSParam(MPlayer_SRS_Param_t *pSRSParam);
#endif

/**
SrvAudioPlayerRestoreSRSParam
@brief  Restore the SRS parameters' value to default. And set the SRS type.

@param[in]      eSRSType            Indicate a SRS type.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerRestoreSRSParam(MPlayer_SRS_Type_e eSRSType);
#endif

/**
SrvAudioPlayerSetSRSParamCfg
@brief  Set the SRS parameters' configure value.

@param[in]      eSRSType            Indicate a SRS type.
@param[in]      pSRSParam           Indicate a SRS parameter structure.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerSetSRSParamCfg(MPlayer_SRS_Type_e eSRSType, MPlayer_SRS_Param_t tSRSParam);
#endif

/**
SrvAudioPlayerGetSRSParamCfg
@brief  Get the SRS parameters' configure value.

@param[in]      eSRSType            Indicate a SRS type.
@param[out]     pSRSParam           Pointer to the SRS parameter structure.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerGetSRSParamCfg(MPlayer_SRS_Type_e eSRSType, MPlayer_SRS_Param_t *pSRSParam);
#endif

/**
SrvAudioPlayerRestoreSRSParamCfg
@brief  Restore the SRS parameters' configure value to default.

@param[in]      eSRSType            Indicate a SRS type.
*/
#if defined(ENABLE_SRSWOWHD)
MAE_Ret SrvAudioPlayerRestoreSRSParamCfg(MPlayer_SRS_Type_e eSRSType);
#endif

/**
SrvAudioPlayerSetVirtualBass
@brief  Set the virtual bass value.

@param[in]      eVirtualBassMode           VirtualBass value to on/off virtual bass
*/
MAE_Ret SrvAudioPlayerSetVirtualBass(MPlayer_VirtualBass_e eVirtualBassMode);

/**
SrvAudioPlayerGetVirtualBass
@brief  Get the virtual bass value.

@param[in]      pVirtualBassMode           VirtualBass value pointer to get virtual bass is on or off.
*/
MAE_Ret SrvAudioPlayerGetVirtualBass(MPlayer_VirtualBass_e *pVirtualBassMode);

/**
SrvAudioPlayerSetLyricMode
@brief	Set the lyric mode.

@param[in]	eLyricMode			Indicate a lyric mode.
*/
MAE_Ret SrvAudioPlayerSetLyricMode(MPlayer_Lyric_e eLyricMode);

/**
SrvAudioPlayerIsSeekable

@brief	get the seek capability.

*/
boolean SrvAudioPlayerIsSeekable(void);

/**
SrvAudioPlayerSeekTo
@brief	Seek to target position.

@param[in]	nPosition			Target position.
*/
MAE_Ret SrvAudioPlayerSeekTo(u32 nPosition);

/**
SrvAudioPlayerSeekCancel
@brief	Cancel the Seek operation
*/
MAE_Ret SrvAudioPlayerSeekCancel(void);

/**
SrvAudioPlayerGetLyricMode
@brief	Get the lyric mode.

@param[out] 	pLyricMode			Pointer to the lyric mode variable.
*/
MAE_Ret SrvAudioPlayerGetLyricMode(MPlayer_Lyric_e *pLyricMode);

/**
SrvAudioPlayerIsLyricsInfoExist
@brief  To check if there is any lyrics info in the service.

@return TRUE            If there is any lyrics info.
@return FALSE           If there is no lyrics info.
*/
boolean SrvAudioPlayerIsLyricsInfoExist(void);

/**
SrvAudioPlayerGetCurrentLyrics
@brief  Get the current showing lyrics.
@       [Note]The Lyrics string will alloc and copy to ppLyrics; Remember to Free ppLyrics by AP self

@param[out]      ppLyrics                	Pointer to the pLyrics variable.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED            	If there is no lyrics.
@return MAE_RET_NOT_READY         	If service is terminated.
*/
MAE_Ret SrvAudioPlayerGetCurrentLyrics(MAE_WChar **ppLyrics);

/**
SrvAudioPlayerGetPlayerStatus
@brief  Get current player status of audio player.

@param[out]      pPlayerStatus        Pointer to the player status variable.
*/
MAE_Ret SrvAudioPlayerGetPlayerStatus(AudioPlayerSrvPlayerStatus_e *pPlayerStatus);

/**
SrvAudioPlayerIsPlaylistExist
@brief  Check if playlist is exist.

@return TRUE            If the playlist is exist.
@return FALSE           If the playlist is not exist.
*/
boolean SrvAudioPlayerIsPlaylistExist(void);

/**
SrvAudioPlayerIsLoadingPlaylist
@brief  Check if service is loading last playback info or not.

@return TRUE            If service is loading last playback info.
@return FALSE           If service is not loading last playback info.
*/
boolean SrvAudioPlayerIsLoadingPlaylist(void);

/**
SrvMplayerGetPlayingTitle
@brief  Get an content title pointer.
@       [Note] This title is taken directly from AudioPlayerSrv, User shall not free this pointer ppTitle.

@param[out]     ppTitle            	Pointer to a pTitle variable.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED       		If there is no playing title.
@return MAE_RET_BAD_PARAM      	    If input parameter error.
*/
MAE_Ret SrvAudioPlayerGetPlayingTitle(MAE_WChar **ppTitle);

/**
SrvAudioPlayerGetPlayingIndex
@brief  Get the focus index in the current play list.

@param[out]      pPlayingIndex           Pointer to a playing index variable.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED          		If an error happen.
@return MAE_RET_BAD_PARAM         	If input parameter error.
*/
MAE_Ret SrvAudioPlayerGetPlayingIndex(u32 *pPlayingIndex);

/**
SrvAudioPlayerGetNextPlayIndex
@brief  Get the next index in the current play list.

@param[out]      pNextIndex           Pointer to a next index variable.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED          		If an error happen.
@return MAE_RET_BAD_PARAM         	If input parameter error.
*/
MAE_Ret SrvAudioPlayerGetNextPlayIndex(u32 *pNextIndex);

/**
SrvAudioPlayerGetPreviousPlayIndex
@brief  Get the previous index in the current play list.

@param[out]      pPrevIndex           Pointer to a previous index variable.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED          		If an error happen.
@return MAE_RET_BAD_PARAM         	If input parameter error.
*/
MAE_Ret SrvAudioPlayerGetPreviousPlayIndex(u32 *pPrevIndex);

/**
SrvAudioPlayerGetPlayingURL
@brief  Get current playing URL pointer.
@       [Note] This URL is taken directly from AudioPlayerSrv, User shall not free this pointer ppURL.

@param[out]      ppURL                   	Pointer to an pURL variable, which is taken directly from AudioPlayerSrv, Client shall not free this pointer.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED            	If there is no playing url.
@return MAE_RET_BAD_PARAM        	If input parameter error.
*/
MAE_Ret SrvAudioPlayerGetPlayingURL(MAE_WChar **ppURL);

/**
SrvAudioPlayerSetBtAvrcpCb
@brief  Register a playback by extend device.

@param[in]      pIReqCB                 Pointer to a Request callback function.
@param[in]      pIListener              Pointer to a listener.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
@return MAE_RET_BAD_PARAM 		If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetBtAvrcpCb(AudioPlayerSrvBtAvrcpCb pIReqCB, IHandler *pIListener);

/**
SrvAudioPlayerUnsetBtAvrcpCb
@brief  Deregister a playback by extend device.

@param[in]      pIListener              Pointer to a listener.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
@return MAE_RET_BAD_PARAM 		If input parameter error.
*/
MAE_Ret SrvAudioPlayerUnsetBtAvrcpCb(IHandler *pIListener);

/**
SrvAudioPlayerEnableBtAvrcp
@brief  To enable bt avrcp.
*/
MAE_Ret SrvAudioPlayerEnableBtAvrcp(void);

/**
SrvAudioPlayerDisableBtAvrcp
@brief  To disable bt avrcp.
*/
__SLDPM_FREE__ MAE_Ret SrvAudioPlayerDisableBtAvrcp(void);

/**
SrvAudioPlayerSetSpectrumCb
@brief  To set spectrum cb.
*/
MAE_Ret SrvAudioPlayerSetSpectrumCb(u32 nCusData, MediaSrvSpectrumCb pfnSpectrumCb);

/**
SrvAudioPlayerSetSpectrumCb
@brief  To set the interval of spectrum cb,
        the interval is between SPECTRUM_MIN_INTERVAL and SPECTRUM_MAX_INTERVAL.

@param[in]      nSpectrumInterval   Interval in mini seconds

@return MAE_RET_SUCCESS         If successful.
@return MAE_RET_BAD_PARAM       If input parameter error.
*/
MAE_Ret SrvAudioPlayerSetSpectrumCbInterval(u16 nSpectrumInterval);

/**
SrvAudioPlayerIsServiceSuspended
@brief  Check if service is suspended by other

@return TRUE           	If service is suspended.
@return FALSE           	If service isn't suspended.
*/
boolean SrvAudioPlayerIsServiceSuspended(void);

/**
SrvAudioPlayerSetBackgroundPlaying
@brief  Set the background playing music on/off.

@param[in]      	bIsBgPlay         	Background on/off.

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerSetBackgroundPlaying(boolean bIsBgPlay);

/**
SrvAudioPlayerIsPredefinedPlaylist
@brief  Check if current playing playlist is pre-defined.

@return TRUE           	If the playlist is pre-defined.
@return FALSE           	If the playlist is user-defined or an error happen.
*/
boolean SrvAudioPlayerIsPredefinedPlaylist(void);

/**
SrvAudioPlayerSetIsPredefinedPlaylist
@brief  Set the playlist as pre-defined or user-defined.

@param[in]      	bIsPredefined         Pre-defined/user-defined

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerSetIsPredefinedPlaylist(boolean bIsPredefined);

/**
SrvAudioPlayerGetPlaylistName
@brief  Get the name of current playlist
@       [Note]The name string will alloc and copy to ppPlaylistName; Remember to Free ppPlaylistName by AP self

@param[out]     	ppPlaylistName       A pointer to the playlist name

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerGetPlaylistName(MAE_WChar **ppPlaylistName);

/**
SrvAudioPlayerSetPlaylistName
@brief  Set the name of current playlist

@param[in]      	pPlaylistName       	Playlist name

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerSetPlaylistName(MAE_WChar *pPlaylistName);

/**
SrvAudioPlayerSetAppInstance
@brief  Set the instance of app to service

@param[in]      	nInstanceId       	App instance

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerSetAppInstance(u32 nInstanceId);

/**
SrvAudioPlayerGetPlayTick
@brief  Get the playtick of current playing music

@param[out]      	pPlayingTick       	Playing tick of an audio file
*/
MAE_Ret SrvAudioPlayerGetPlayTick(u32 *pPlayingTick);

/**
SrvAudioPlayerGetPlayDuration
@brief  Get the total time of current playing music

@param[out]      	pPlayDuration       	Total play time of an audio file
*/
MAE_Ret SrvAudioPlayerGetPlayDuration(u32 *pPlayDuration);

/**
SrvAudioPlayerGetPlaylistTitle
@brief  Get the title of current playlist
@       [Note]The title string will alloc and copy to ppPlaylistTitle; Remember to Free ppPlaylistTitle by AP self

@param[out]      	ppPlaylistTitle       	Playlist title

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerGetPlaylistTitle(MAE_WChar **ppPlaylistTitle);

/**
SrvAudioPlayerSetPlaylistTitle
@brief  Set the title of current playlist

@param[in]      	pPlaylistTitle       	Playlist title

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerSetPlaylistTitle(MAE_WChar *pPlaylistTitle);

/**
SrvAudioPlayerGetPlaylistDataModel
@brief  Get the playlist data model of current playlist
@       [Note] This datamodel will release in Srv, User shall not release this pointer ppPlaylistDataModel.

@param[out]      	ppPlaylistDataModel       Playlist data model

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerGetPlaylistDataModel(IDataModel **ppPlaylistDataModel);

/**
SrvAudioPlayerSetPlaylistDataModel
@brief  Set the playlist data model of current playlist

@param[in]      	pPlaylistDataModel       Playlist data model

@return MAE_RET_SUCCESS           	If successful.
@return MAE_RET_FAILED           	If an error happen.
*/
MAE_Ret SrvAudioPlayerSetPlaylistDataModel(IDataModel *pPlaylistDataModel);

/**
SrvAudioPlayerIsExtStorageChanged
@brief  To check if need update pre-defined playlist.

@return TRUE            If need to update pre-defined playlist.
@return FALSE           If no need to update pre-defined playlist.
*/
boolean SrvAudioPlayerIsExtStorageChanged(void);

/**
SrvAudioPlayerSetIsNeedToUpdatePlaylist
@brief	Change Update pre-defined playlist.

@param[in]      bIsNeedToUpdate               Indicate to update pre-defined playlist.
*/
MAE_Ret SrvAudioPlayerSetIsNeedToUpdatePlaylist(boolean bIsNeedToUpdate);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_AUDIOPLAYER_H__
