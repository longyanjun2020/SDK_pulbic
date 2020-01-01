/**
* @file mmi_audioplayersrv.h
*
*
* Class Id: CLSID_AUDIOPLAYERSRV
*
*
* @version $Id$
*/
#ifndef __MMI_AUDIOPLAYERSRV_H__
#define __MMI_AUDIOPLAYERSRV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"
/*-------------------------------------------------------------------------*/
#include "mmi_common_cfg.h"
#include "mmi_mediasrv_common.h"

typedef enum AudioPlayerSrvPropertyId_e_
{
    AUDIOPLAYERSRV_PROP__IS_BACKGROUND_PLAYING = 0
   ,/* Check if the service is playing in background */
    AUDIOPLAYERSRV_PROP__IS_PREDEFINED_LIST
   ,/* Check if the playing playlist is predefined list or not */
    AUDIOPLAYERSRV_PROP__PLAYLIST_NAME
   ,/* Get \ Set the play list name; NULL is to release it */
    AUDIOPLAYERSRV_PROP__APP_INSTANCE
   ,/* Set the APP instance */
    AUDIOPLAYERSRV_PROP__PLAYING_TICK
   ,/* Get the tick info of the playing media */
    AUDIOPLAYERSRV_PROP__PLAYING_DURATION
   ,/* Get the duration of the playing media */
    AUDIOPLAYERSRV_PROP__PLAYLIST_TITLE
   ,/* Get \ Set the play list title; NULL is to release it*/
    AUDIOPLAYERSRV_PROP__PLAYLIST_DATAMODEL
   ,/* Get \ Set the play list DataModel; if set a NULL DataModel, it means to release it. */
   	AUDIOPLAYERSRV_PROP__NUM
} AudioPlayerSrvPropertyId_e;

typedef enum AudioPlayerSrvNotifyMask_e_
{
    AUDIOPLAYERSRV_MASK_PLAYSTATUS = 1 << 0
   ,// MPLAYERSRV  play status indication (background play)
    AUDIOPLAYERSRV_MASK_PLAYING_TICK = 1 << 1
   ,// Playing tick
    AUDIOPLAYERSRV_MASK_PLAYING_MEDIA_NAME = 1 << 2
   ,// MPLAYERSRV playing media name indication
    AUDIOPLAYERSRV_MASK_LYRICINFO = 1 << 3
   ,// LyricInfo string update
    AUDIOPLAYERSRV_MASK_INSERT_CONTENT_TO_PLAYLIST = 1 << 4
   ,// Insert content with parar1 is index to playlist .
    AUDIOPLAYERSRV_MASK_COMMON = 1 << 5
   ,// Common notify without parameter
    AUDIOPLAYERSRV_MASK_PLAYING_INDEX = 1 << 6
   ,// Playing index notify due to play next or Play previous.
    AUDIOPLAYERSRV_MASK_PLAYMUSIC_INFO = 1 << 7
   ,// Get music information after play music.
    AUDIOPLAYERSRV_MASK_SEEK_CANCEL = 1 << 8
   ,// MPLAYERSRV seek cancel indication
    AUDIOPLAYERSRV_MASK_TOTAL_TIME_UPDATE = 1 << 9
   ,// Total time update
    AUDIOPLAYERSRV_MASK_ALL = (signed int) 0xFFFFFFFF
} AudioPlayerSrvNotifyMask_e;

typedef enum AudioPlayerSrvPlayerStatus_e_
{
    AUDIOPLAYERSRV_IDLE
   ,AUDIOPLAYERSRV_PLAY
   ,AUDIOPLAYERSRV_STOP
   ,AUDIOPLAYERSRV_PAUSE
   ,AUDIOPLAYERSRV_PLAY_SUSPEND
} AudioPlayerSrvPlayerStatus_e;

typedef enum AudioPlayerSrvActionType_e_
{
    AUDIOPLAYERSRV_NO_ACT
   ,AUDIOPLAYERSRV_PLAY_ACT
   ,AUDIOPLAYERSRV_STOP_ACT
   ,AUDIOPLAYERSRV_PAUSE_ACT
   ,AUDIOPLAYERSRV_RESUME_ACT
   ,AUDIOPLAYERSRV_VOLUME_UP_ACT
   ,AUDIOPLAYERSRV_VOLUME_DOWN_ACT
   ,AUDIOPLAYERSRV_FORWARD_ACT
   ,AUDIOPLAYERSRV_BACKWARD_ACT
   ,AUDIOPLAYERSRV_MUTE_ACT
} AudioPlayerSrvActionType_e;

typedef enum AudioPlayerSrvActionResult_e_
{
    AUDIOPLAYERSRV_ACT_REJECT
   ,AUDIOPLAYERSRV_ACT_WAITING
   ,AUDIOPLAYERSRV_ACT_FAILED
   ,AUDIOPLAYERSRV_ACT_DONE
} AudioPlayerSrvActionResult_e;

typedef struct AudioPlayerSrvFileInfo_t_
{
    u32 nFocusIndex;
    boolean bIsSet;
    u32 nFormat;
    u32 nFreq;
    u32 nBitrate;
    boolean bStereo;
    u32 nTotalTime;
    u16 bAudioIsSeekable;
} AudioPlayerSrvFileInfo_t;

typedef enum AudioPlayerID3DataType_e_
{
    AUDIOPLAYERSRV_ID3_V1
   ,AUDIOPLAYERSRV_ID3_V2
} AudioPlayerID3DataType_e;

#define AUDIOPLAYERSRV_SONGNAME_WLEN 62  //Wide Character size of music ID3V1 'song name'
#define AUDIOPLAYERSRV_ARTIST_WLEN   62  //Wide Character size of music ID3V1 'artist name'
#define AUDIOPLAYERSRV_ALBUM_WLEN    62  //Wide Character size of music ID3V1 'album name'
#define AUDIOPLAYERSRV_YEAR_WLEN     62  //Wide Character size of music ID3V1 'year'
#define AUDIOPLAYERSRV_COMMENT_WLEN  62  //Wide Character size of music ID3V1 'comment'
#define AUDIOPLAYERSRV_TRACK_WLEN    62  //Wide  Character size of music ID3V1 'song track'

typedef struct AudioPlayerSrvID3Info_t_
{
    MAE_WChar nSongName[AUDIOPLAYERSRV_SONGNAME_WLEN];
    MAE_WChar nArtist[AUDIOPLAYERSRV_ARTIST_WLEN];
    MAE_WChar nAlbum[AUDIOPLAYERSRV_ALBUM_WLEN];
    MAE_WChar nYear[AUDIOPLAYERSRV_YEAR_WLEN];
    MAE_WChar nComment[AUDIOPLAYERSRV_COMMENT_WLEN];
    MAE_WChar nTrack[AUDIOPLAYERSRV_TRACK_WLEN];
    u8 nSongNameValid;
    u8 nArtistValid;
    u8 nAlbumValid;
    u8 nYearValid;
    u8 nCommentValid;
    u8 nTrackValid;
} AudioPlayerSrvID3Info_t;

typedef struct AudioPlayerSrvID3TextInfo_t_
{
    u32         nLength;
    MAE_WChar   *pContent;
} AudioPlayerSrvID3TextInfo_t;

typedef struct AudioPlayerSrvID3PictureInfo_t_
{
    u32         nLength;
    u8          *pContent;
} AudioPlayerSrvID3PictureInfo_t;

typedef struct AudioPlayerSrvID3InfoEx_t_
{
    AudioPlayerSrvID3TextInfo_t tSongName;
    AudioPlayerSrvID3TextInfo_t tArtist;
    AudioPlayerSrvID3TextInfo_t tAlbum;
    AudioPlayerSrvID3TextInfo_t tYear;
    AudioPlayerSrvID3TextInfo_t tComment;
    AudioPlayerSrvID3TextInfo_t tTrack;
    AudioPlayerSrvID3PictureInfo_t tPicture;
} AudioPlayerSrvID3InfoEx_t;

typedef void (*AudioPlayerSrvID3InfoCb)(void *pThis, MediaSrvErrCode_e eErrorCode, AudioPlayerSrvID3Info_t *pID3Info);
#ifdef __MMI_ID3_SUPPORT__
typedef void (*AudioPlayerSrvID3InfoExCb)(void *pThis, u32 nCusData, MediaSrvErrCode_e eErrorCode, AudioPlayerSrvID3InfoEx_t *pID3Info);
#endif
typedef void (*AudioPlayerSrvBtAvrcpCb)(AudioPlayerSrvActionType_e eAction, AudioPlayerSrvActionResult_e *eAcceptRes, IBase *pListener);

/*-------------------------------------------------------------------------*/
/**
 * External Events
 */
 //AUDIOPLAYERSRV_MASK_PLAYSTATUS
#define MPLAYERSRV_EVT_PlaySuccess              (CLSID_AUDIOPLAYERSRV << 16 | 1)   	//confirm
#define MPLAYERSRV_EVT_PlayFailed               (CLSID_AUDIOPLAYERSRV << 16 | 2)   	//confirm
#define MPLAYERSRV_EVT_PauseSuccess             (CLSID_AUDIOPLAYERSRV << 16 | 3)   	//confirm
#define MPLAYERSRV_EVT_PauseFailed              (CLSID_AUDIOPLAYERSRV << 16 | 4)   	//confirm
#define MPLAYERSRV_EVT_StopSuccess              (CLSID_AUDIOPLAYERSRV << 16 | 5)   	//confirm
#define MPLAYERSRV_EVT_StopFailed               (CLSID_AUDIOPLAYERSRV << 16 | 6)   	//confirm
#define MPLAYERSRV_EVT_SuspendInd               (CLSID_AUDIOPLAYERSRV << 16 | 7)    //notify
#define MPLAYERSRV_EVT_ResumeInd                (CLSID_AUDIOPLAYERSRV << 16 | 8)    //notify
#define MPLAYERSRV_EVT_PlayBackgroundInd        (CLSID_AUDIOPLAYERSRV << 16 | 9)   	//notify
//AUDIOPLAYERSRV_MASK_PLAYING_TICK
#define MPLAYERSRV_EVT_PlayTick             	(CLSID_AUDIOPLAYERSRV << 16 | 10)   //notify
//AUDIOPLAYERSRV_MASK_PLAYING_MEDIA_NAME
#define MPLAYERSRV_EVT_PlayingMediaName         (CLSID_AUDIOPLAYERSRV << 16 | 11)   //notify
//AUDIOPLAYERSRV_MASK_LYRICINFO
#define MPLAYERSRV_EVT_LyricsInfo               (CLSID_AUDIOPLAYERSRV << 16 | 12)   //notify
//AUDIOPLAYERSRV_MASK_INSERT_CONTENT_TO_PLAYLIST
#define MPLAYERSRV_EVT_InsertContentToPlaylist  (CLSID_AUDIOPLAYERSRV << 16 | 13)   //notify
//AUDIOPLAYERSRV_MASK_COMMON
#define MPLAYERSRV_EVT_SuspendDone              (CLSID_AUDIOPLAYERSRV << 16 | 14)   //??
#define MPLAYERSRV_EVT_EndPlaying               (CLSID_AUDIOPLAYERSRV << 16 | 15)   //notify
#define MPLAYERSRV_EVT_LyricsSuccess            (CLSID_AUDIOPLAYERSRV << 16 | 16)   //confirm
#define MPLAYERSRV_EVT_LyricsFailed             (CLSID_AUDIOPLAYERSRV << 16 | 17)   //confirm
#define MPLAYERSRV_EVT_PCLinkActivated          (CLSID_AUDIOPLAYERSRV << 16 | 18)   //notify
#define MPLAYERSRV_EVT_SDDB_DISABLED            (CLSID_AUDIOPLAYERSRV << 16 | 19)   //notify
#define MPLAYERSRV_EVT_CommandSkip              (CLSID_AUDIOPLAYERSRV << 16 | 20)   //notify
#define MPLAYERSRV_EVT_CommandReject            (CLSID_AUDIOPLAYERSRV << 16 | 21)   //notify
#define MPLAYERSRV_EVT_FileFormatNotSupport     (CLSID_AUDIOPLAYERSRV << 16 | 22)   //confirm
#define MPLAYERSRV_EVT_FileNotExist             (CLSID_AUDIOPLAYERSRV << 16 | 23)   //confirm
#define MPLAYERSRV_EVT_LoadLastPlayInfoDone     (CLSID_AUDIOPLAYERSRV << 16 | 24)   //??
//AUDIOPLAYERSRV_MASK_PLAYING_INDEX
#define MPLAYERSRV_EVT_PlayNext             	(CLSID_AUDIOPLAYERSRV << 16 | 25)   //confirm
#define MPLAYERSRV_EVT_PlayPrevious             (CLSID_AUDIOPLAYERSRV << 16 | 26)   //confirm
//AUDIOPLAYERSRV_MASK_PLAYMUSIC_INFO
#define MPLAYERSRV_EVT_PlayMusic                (CLSID_AUDIOPLAYERSRV << 16 | 27)   //confirm (GetFileInfo)
#define MPLAYERSRV_EVT_SeekSuccess              (CLSID_AUDIOPLAYERSRV << 16 | 28)   //confirm
#define MPLAYERSRV_EVT_SeekFailed               (CLSID_AUDIOPLAYERSRV << 16 | 29)   //confirm
#define MPLAYERSRV_EVT_SeekCancel               (CLSID_AUDIOPLAYERSRV << 16 | 30)   //confirm
#define MPLAYERSRV_EVT_SeekComplete             (CLSID_AUDIOPLAYERSRV << 16 | 31)   //confirm
//AUDIOPLAYERSRV_MASK_TOTAL_TIME_UPDATE
#define MPLAYERSRV_EVT_TotalTimeUpdate          (CLSID_AUDIOPLAYERSRV << 16 | 32)   //notify

/**
 * IAUDIOPLAYERSRV Interfaces
 */
#define INHERIT_IAUDIOPLAYERSRV(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(IAUDIOPLAYERSRV);

#define IMPLAYERSRV_QueryInterface(pICntlr, id, pp, po)         GET_FUNCTBL((pICntlr), IAUDIOPLAYERSRV)->QueryInterface(pICntlr, id, pp, po)
#define IMPLAYERSRV_HandleEvent(pICntlr, e, p1, p2)             GET_FUNCTBL((pICntlr), IAUDIOPLAYERSRV)->HandleEvent(pICntlr, e, p1, p2)

void AudioPlayerSrvInit(void);
__SLDPM_FREE__ MAE_Ret AudioPlayerSrvNew(MAE_ClsId nId, void **ppObj);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  AudioPlayer Service interface
/////////////////////////////////////////////////////////////////////////////////////////////////////////
MAE_Ret AudioPlayerSrvSuspendBackgroundMusic(IAUDIOPLAYERSRV *pAudioPlayerSrv);
MAE_Ret AudioPlayerSrvResumeBackgroundMusic(IAUDIOPLAYERSRV *pAudioPlayerSrv);
MAE_Ret AudioPlayerSrvGetID3Info(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID, MAE_WChar *pURL, AudioPlayerSrvID3InfoCb pfnCallBack);
#ifdef __MMI_ID3_SUPPORT__
MAE_Ret AudioPlayerSrvGetID3InfoEx(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID, MAE_WChar *pURL, u32 nCusData, AudioPlayerSrvID3InfoExCb pfnCallBack);
#endif
MAE_Ret AudioPlayerSrvPlay(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID, u32 nFocusIndex, u32 nPosition);
MAE_Ret AudioPlayerSrvPause(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID);
MAE_Ret AudioPlayerSrvResume(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID);
MAE_Ret AudioPlayerSrvStop(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID);
MAE_Ret AudioPlayerSrvPlayNext(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID);
MAE_Ret AudioPlayerSrvPlayPrevious(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID);
boolean AudioPlayerSrvQueryEQSupport(bool *pUserEQSupported);
#if defined(ENABLE_TIME_STRETCH)
boolean AudioPlayerSrvQueryTSSupport(bool *pUserTSSupported);
#endif
#if defined(ENABLE_REVERB)
boolean AudioPlayerSrvQueryReverbSupport(bool *pUserReverbSupported);
#endif
boolean AudioPlayerSrvQuery3DSurroundSupport(bool *p3DSurroundSupported);
#if defined(ENABLE_SRSWOWHD)
boolean AudioPlayerSrvQuerySRSSupport(bool *pSRSSupported);
#endif
boolean AudioPlayerSrvQueryVirtualBassSupport(bool *pVirtualBassSupported);
MAE_Ret AudioPlayerSrvSetEQ(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_EQ_e eEQMode);
MAE_Ret AudioPlayerSrvGetEQ(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_EQ_e *pEQMode);
#if defined(ENABLE_TIME_STRETCH)
MAE_Ret AudioPlayerSrvSetTS(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_TimeStretch_e eTSMode);
MAE_Ret AudioPlayerSrvGetTS(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_TimeStretch_e *pTSMode);
#endif
#if defined(ENABLE_REVERB)
MAE_Ret AudioPlayerSrvSetReverb(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Reverb_e eReverbMode);
MAE_Ret AudioPlayerSrvGetReverb(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Reverb_e *pReverbMode);
#endif
MAE_Ret AudioPlayerSrvSetShuffle(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Shuffle_e eShuffleMode);
MAE_Ret AudioPlayerSrvGetShuffle(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Shuffle_e *pShuffleMode);
MAE_Ret AudioPlayerSrvSetRepeat(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Repeat_e eRepeatMode);
MAE_Ret AudioPlayerSrvGetRepeat(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Repeat_e *pRepeatMode);
MAE_Ret AudioPlayerSrvSetVolume(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_VolLevel_e eVolumeLevel);
MAE_Ret AudioPlayerSrvGetVolume(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_VolLevel_e *pVolumeLevel);
MAE_Ret AudioPlayerSrvSet3DSurround(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_3DSurround_e e3DSurroundMode);
MAE_Ret AudioPlayerSrvGet3DSurround(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_3DSurround_e *p3DSurroundMode);
MAE_Ret AudioPlayerSrvSetPitchShift(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_PitchShift_e ePitchShiftValue);
MAE_Ret AudioPlayerSrvGetPitchShift(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_PitchShift_e *pPitchShiftValue);
MAE_Ret AudioPlayerSrvSetDolby(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Dolby_e eDolbyMode);
void AudioPlayerSrvGetDolby(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Dolby_e *pDolbyMode);
#if defined(ENABLE_SRSWOWHD)
MAE_Ret AudioPlayerSrvSetSRS(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_e eSRSMode);
MAE_Ret AudioPlayerSrvGetSRS(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_e *pSRSMode);
MAE_Ret AudioPlayerSrvSetSRSType(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_Type_e eSRSType);
MAE_Ret AudioPlayerSrvGetSRSType(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_Type_e *pSRSType);
MAE_Ret AudioPlayerSrvSetSRSParam(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_Param_t tSRSParam);
MAE_Ret AudioPlayerSrvGetSRSParam(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_Param_t *pSRSParam);
MAE_Ret AudioPlayerSrvRestoreSRSParam(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_Type_e eSRSType);
MAE_Ret AudioPlayerSrvSetSRSParamCfg(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_Type_e eSRSType, MPlayer_SRS_Param_t tSRSParam);
MAE_Ret AudioPlayerSrvGetSRSParamCfg(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_Type_e eSRSType, MPlayer_SRS_Param_t *pSRSParam);
MAE_Ret AudioPlayerSrvRestoreSRSParamCfg(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_SRS_Type_e eSRSType);
#endif // defined(ENABLE_SRSWOWHD)
MAE_Ret AudioPlayerSrvSetVirtualBassMode(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_VirtualBass_e eVirtualBassMode);
MAE_Ret AudioPlayerSrvGetVirtualBassMode(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_VirtualBass_e *pVirtualBassMode);
MAE_Ret AudioPlayerSrvSetLyricMode(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Lyric_e eLyricMode);
MAE_Ret AudioPlayerSrvGetLyricMode(IAUDIOPLAYERSRV *pAudioPlayerSrv, MPlayer_Lyric_e *pLyricMode);
boolean AudioPlayerSrvIsSeekable(IAUDIOPLAYERSRV *pAudioPlayerSrv);
MAE_Ret AudioPlayerSrvSeekTo(IAUDIOPLAYERSRV *pThis, u32 nPosition);
MAE_Ret AudioPlayerSrvSeekCancel(IAUDIOPLAYERSRV *pAudioPlayerSrv);
boolean AudioPlayerSrvIsLyricsInfoExist(IAUDIOPLAYERSRV *pAudioPlayerSrv);
MAE_Ret AudioPlayerSrvGetCurrentLyrics(IAUDIOPLAYERSRV *pAudioPlayerSrv, MAE_WChar **ppLyrics);
AudioPlayerSrvPlayerStatus_e AudioPlayerSrvGetPlayerStatus(IAUDIOPLAYERSRV *pAudioPlayerSrv);
boolean AudioPlayerSrvIsPlaylistExist(IAUDIOPLAYERSRV *pAudioPlayerSrv);
boolean AudioPlayerSrvIsLoadingPlaylist(IAUDIOPLAYERSRV *pAudioPlayerSrv);
boolean AudioPlayerSrvIsPlaying(IAUDIOPLAYERSRV *pAudioPlayerSrv);
MAE_Ret AudioPlayerSrvGetPlayingTitle(IAUDIOPLAYERSRV *pAudioPlayerSrv, MAE_WChar **ppTitle);
MAE_Ret AudioPlayerSrvGetPlayingIndex(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 *pPlayingIndex);
MAE_Ret AudioPlayerSrvGetNextPlayIndex(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 *pNextIndex);
MAE_Ret AudioPlayerSrvGetPreviousPlayIndex(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 *pPrevIndex);
MAE_Ret AudioPlayerSrvGetPlayingURL(IAUDIOPLAYERSRV *pAudioPlayerSrv, MAE_WChar **ppURL);
MAE_Ret AudioPlayerSrvSetBtAvrcpCb(IAUDIOPLAYERSRV *pAudioPlayerSrv, AudioPlayerSrvBtAvrcpCb pIReqCB, IHandler *pIListener);
MAE_Ret AudioPlayerSrvUnsetBtAvrcpCb(IAUDIOPLAYERSRV *pAudioPlayerSrv, IHandler *pIListener);
__SLDPM_FREE__ MAE_Ret AudioPlayerSrvSetBtAvrcpStatus(IAUDIOPLAYERSRV *pAudioPlayerSrv, boolean bEnable);
#ifdef __LANTERN_BY_AUDIO__
MAE_Ret AudioPlayerSrvSetSpectrumCb(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID, u32 nCusData, MediaSrvSpectrumCb pfnSpectrumCb);
MAE_Ret AudioPlayerSrvSetSpectrumCbInterval(IAUDIOPLAYERSRV *pAudioPlayerSrv, u32 nInstanceID, u16 nSpectrumInterval);
#endif
__SLDPM_FREE__ MAE_Ret AudioPlayerSrvRegisterNotification(IAUDIOPLAYERSRV *pAudioPlayerSrv, void *pInstanceID, AudioPlayerSrvNotifyMask_e eMask);
MAE_Ret AudioPlayerSrvDeregisterNotification(IAUDIOPLAYERSRV *pAudioPlayerSrv, void *pInstanceID, AudioPlayerSrvNotifyMask_e eMask);
MAE_Ret AudioPlayerSrvGetProperty(IAUDIOPLAYERSRV *pAudioPlayerSrv, AudioPlayerSrvPropertyId_e ePropId, u32 nOutVal);
MAE_Ret AudioPlayerSrvSetProperty(IAUDIOPLAYERSRV *pAudioPlayerSrv, AudioPlayerSrvPropertyId_e ePropId, u32 nVal);
boolean AudioPlayerSrvIsServiceSuspended(IAUDIOPLAYERSRV *pAudioPlayerSrv);
boolean AudioPlayerSrvIsExtStorageChanged(IAUDIOPLAYERSRV *pAudioPlayerSrv);
MAE_Ret AudioPlayerSrvSetIsNeedToUpdatePlaylist(IAUDIOPLAYERSRV *pAudioPlayerSrv, boolean bIsNeedToUpdate);

/*-------------------------------------------------------------------------*/
#endif /* __MMI_AUDIOPLAYERSRV_H__ */
