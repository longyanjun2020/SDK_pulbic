/**
* @file mmi_audioplayersrv_priv.h
*
* Class Id: CLSID_AUDIOPLAYERSRV
* @version $Id: mmi_audioplayersrv_priv.h 41495 2009-09-25 13:30:21Z young.huang $
*/
#ifndef __MMI_AUDIOPLAYERSRV_PRIV_H__
#define __MMI_AUDIOPLAYERSRV_PRIV_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_audioplayersrv.h"
/*-------------------------------------------------------------------------*/
#include "ABL_Aud.h"
#include "mmi_mae_notifier.h"
#include "mmi_accessorysrv.h"
#include "mmi_playlistsrv.h"
#include "mmi_cfgsrv.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_filemgr.h"
#ifdef __BLUETOOTH_AVRCP_MMI__
#include "mmi_btsrv.h"
#endif

/*-------------------------------------------------------------------------*/
typedef enum AudioPlayerSrvPlayDirection_e_
{
    AUDIOPLAYERSRV_PLAYDIRECTION__NORMAL
   ,AUDIOPLAYERSRV_PLAYDIRECTION__NEXT
   ,AUDIOPLAYERSRV_PLAYDIRECTION__PREV
} AudioPlayerSrvPlayDirection_e;

typedef enum AudioPlayerSrvPrePlayStage_e_
{
    AUDIOPLAYERSRV_PREPLAYSTAGE__NONE
   ,AUDIOPLAYERSRV_PREPLAYSTAGE__GETFILEINFO
   ,AUDIOPLAYERSRV_PREPLAYSTAGE__GETLYRIC
   ,AUDIOPLAYERSRV_PREPLAYSTAGE__STARTPLAY
} AudioPlayerSrvPrePlayStage_e;

typedef enum AudioPlayerSrvAbortPlayType_e_
{
    AUDIOPLAYERSRV_ABORTPLAY_TYPE__NONE
   ,AUDIOPLAYERSRV_ABORTPLAY_TYPE__USERSTOP
   ,AUDIOPLAYERSRV_ABORTPLAY_TYPE__USERPAUSE
} AudioPlayerSrvAbortPlayType_e;

typedef enum AudioPlayerSrvPowerConsumptionStatus_e_
{
    AUDIOPLAYERSRV_POWER_CONSUMPTION__OFF
   ,AUDIOPLAYERSRV_POWER_CONSUMPTION__ON
} AudioPlayerSrvPowerConsumptionStatus_e;

typedef struct AudioPlayerSrvRawLyricsInfo_t_
{
    u32 nInfoDataLen;     //Total size of the Advanced data buffer
    u8 *pInfoData;      //Advanced data buffer
} AudioPlayerSrvRawLyricsInfo_t;

typedef struct AudioPlayerSrvLyricsElement_t_
{
    s32 sTimePosition;  // The time to display this lyrics
    u32 nDataLength;    // The length of the pData
    u8 *pData;  // The data (lyrics) to be displayed. (It points to the memory held by pThis->pRawLyricsInfo)
} AudioPlayerSrvLyricsElement_t;

typedef struct AudioPlayerSrvLyricsInfo_t_
{
    u32 nNextIndex; // The next lyrics element to be displayed
    s32 sTimerOffset; // It is used to correct the timer
    u32 nNumberOfElement;   // Number of the lyrics element
    AudioPlayerSrvLyricsElement_t *pLyricsElement;   // the array of lyrics element
} AudioPlayerSrvLyricsInfo_t;

typedef struct AudioPlayerSrvSpectrumClient_t_
{
    void *pAppInstance;
    u32 nCusData;
    MediaSrvSpectrumCb pfnSpectrumCb;
} AudioPlayerSrvSpectrumClient_t;

typedef struct AudioPlayerSrvID3CbData_t_
{
    u32 nSrvInstId;
    u32 nAppInstId;
    void *pfnCallBack;
    u32 nCusData;
    FileMgr_WChar *pFilename;
    ABL_AudGetMode_e eGetMode;
    AudioPlayerID3DataType_e eID3Type;
} AudioPlayerSrvID3CbData_t;

typedef struct AudioPlayerSrvLyricsCbData_t_
{
    u32 nSrvInstId;
    u16 *pFileName;
    ABL_AudGetMode_e eGetMode;
} AudioPlayerSrvLyricsCbData_t;

typedef struct AudioPlayerSrvMediaConfigData_t_
{
    MPlayer_EQ_e eEQMode;
    MPlayer_3DSurround_e e3DSurroundMode;
    MPlayer_Dolby_e eDolbyMode;
#if defined(ENABLE_TIMEPITCH_STRETCH)
    MPlayer_PitchShift_e ePitchShiftValue;
#endif
#if defined(ENABLE_TIME_STRETCH)
    MPlayer_TimeStretch_e eTSMode;
#endif
#if defined(ENABLE_REVERB)
    MPlayer_Reverb_e eReverbMode;
#endif
#if defined(ENABLE_SRSWOWHD)
    MPlayer_SRS_e eSRSMode;
    MPlayer_SRS_Type_e eSRSType;
    MPlayer_SRS_Param_t tSRSParam;
#endif
#if defined(ENABLE_BASS)
    MPlayer_VirtualBass_e eVirtualBassMode;
#endif
} AudioPlayerSrvMediaConfigData_t;

typedef struct AudioPlayerSrv_t_
{
    DECLARE_FUNCTBL(IAUDIOPLAYERSRV); // function table pointer
    u32 nRefCnt;     // reference count
    ICFGSrv *pICFGSrv;
    ModelListener_t tCFGSrvListener;
    IACCESSORYSRV *pIAccessorySrv;  // interface for querying the external card.
    ModelListener_t tAccessoryListener;
    MAE_Notifier_t *pNotifier;  // For the time being, it is used to notify Idle APP if MPLAYER is playing background.
    IPLAYLISTSRV *pIPlayListSrv;
    IDataModel *pPlayListDataModel; // The DataModel of the playing items
    MAE_WChar *pszPlayListName;     // The URL of the playing list
    MAE_WChar *pPlayListTitle;      // The title of the playing playlist
    MAE_WChar *pPlayingURL;     // Playing URL
    FileMgrHandleID_t tFileLockHdl;	//Playing URL lock handle
    FileMgrHandleID_t tDirLockHdl;	//Playing Dir lock handle
    FileMgrHandleID_t tPlayListLockHdl;	//Playing playlist lock handle
    MAE_WChar *pPlayingTitle;   // Playing song title
    AudioPlayerSrvFileInfo_t tAudFileInfo;                // The file info about the media
    AudioPlayerSrvLyricsInfo_t *pLyricsInfo; // Lyrics parsed result
    AudioPlayerSrvRawLyricsInfo_t *pRawLyricsInfo; // Lyrics data from ResMgr
    u32 *pU32PlayList;                          // It is a pointer (array) to keep the order of playing.
    u32 nPlayPosition;                           // Play Position
    boolean bIsLyricsExist;                 // It indicates if the lyrics information exists
    boolean bIsPredefinedList;  // It indicates if the playlist is predefined.
    boolean bShowPlayFailed;                     // Check if we have to show "play failed" when failed to play.
    boolean bLoadingLastPlaylist; // Check if loading last playlist

    u32 nPlayListSize;                        // The size of the play list
    u32 nPlayingIndex;                        // The index of the current playing media
    u32 nErrorCounter;                        // Keep how many the consecutive errors happen
    u32 nFocusIndex;                          // The focus(playing) media for UI menu
    AudioPlayerSrvPlayerStatus_e ePlayerStatus;              // Keep the status of player; it is used by "suspend".
    MPlayer_Shuffle_e eShuffleMode; // Keep the status of the shuffle mode
    MPlayer_Repeat_e eRepeatMode;   // Keep the status of the repeat mode
    MPlayer_EQ_e eEQMode;               // Keep the status of Equalizer
    MPlayer_3DSurround_e e3DSurroundMode;   // Keep the status of the 3D surround
    MPlayer_TimeStretch_e eTSMode;           // Keep the status of the Time Stretch
    MPlayer_Reverb_e eReverbMode;           // Keep the status of the Reverb
    MPlayer_PitchShift_e ePitchShiftValue;                    // keep the patch shift value
    MPlayer_Dolby_e eDolbyMode;   // Keep the status of the Dolby
#if defined(ENABLE_SRSWOWHD)
    MPlayer_SRS_e eSRSMode;         // Keep the status of the SRS effect
    MPlayer_SRS_Type_e eSRSType;    // Keep the type of the SRS effect
    MPlayer_SRS_Param_t tSRSParam;  // Keep the parameters of the SRS effect
#endif
#ifdef ENABLE_BASS
    MPlayer_VirtualBass_e eVirtualBassMode;   // Keep the status of the Virtual bass mode
#endif
    MPlayer_Lyric_e eLyricMode; // Keep the status of the Lyric setting
    MPlayer_VolLevel_e eVolumeLevel;    // Keep the volume level
    PLAYLISTSRV_Playback_Info_t tPlaybackInfo;
#ifdef __BLUETOOTH_AVRCP_MMI__
    IBTSRV *pIBTSrv;
    BTSRV_AvrcpActionType_e eBTAvrcpReq;
    IHandler *pIExtDevReqListener;
    AudioPlayerSrvBtAvrcpCb pIExtDevReqCB;
    boolean bIsAvrcpEnable;
#endif
    u16 nAppId;
    void *pAppInstance;             // The pointer to hold MPLAYERAPP instance
    AudioPlayerSrvPlayDirection_e ePlayDirection;    // The direction of reading the play list
    AudioPlayerSrvPrePlayStage_e ePrePlayStage;      //To describe the stages of preplay procedure: Get file info->Get lyric->Start play
    AudioPlayerSrvAbortPlayType_e eAbortPlayType;   //App invoke stop or pause during preplay procedure
    boolean bCancelLyricTimer;
    boolean bNeedResetLyricsTimer;					 //Set lyrics timer while receiving first timetick update
    boolean bIsSessionOpened;
    boolean bPendedPause;                       //User pause in play finish to play next music
    boolean bPendingPlay;                       //If service is suspended, pending start play until resume
    boolean bIsPlaying;                               // Check if the media\player is playing.
    boolean bIsPaused;
    boolean bIsSuspended;
    boolean bIsResumedPause;                    //RM resume in user pause
    boolean bPCLinkActivated;
    boolean bTerminated;
    boolean bIsReset;               //If player is reset, skip executing all cb functions
    boolean bIsSeeking;           // if True, ignore position updating
    boolean bIsNeedToUpdate;
    boolean bWaitPlayRsp;
    boolean bWaitStopRsp;
    boolean bWaitPauseRsp;
    boolean bWaitResumeRsp;
    boolean bWaitChangeRsp;
    boolean bWaitPairStopRsp;
    boolean bPlayCmdSuspended;
    boolean bStopCmdSuspended;
    boolean bPauseCmdSuspended;
    boolean bResumeCmdSuspended;
    boolean bChangeCmdSuspended;
#ifdef __LANTERN_BY_AUDIO__
    AudioPlayerSrvSpectrumClient_t *pSpectrumClient;
    u16 nSpecTimerInterval;
#endif
} AudioPlayerSrv_t;

/*-------------------------------------------------------------------------*/
#endif /* __MMI_AUDIOPLAYERSRV_PRIV_H__ */
