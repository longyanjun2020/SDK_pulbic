//==============================================================================
//
//  File        : ahc_mediaplayback.h
//  Description : INCLUDE File for the AHC Media Playback function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_MEDIAPLAYBACK_H_
#define _AHC_MEDIAPLAYBACK_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_audio_inc.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

// Recference mmpf_player.c VIDEO_EVENT_XXX
#define AHC_VIDEO_PLAY         				(0x00000000)
#define AHC_VIDEO_PLAY_EOF     				(0x00000001)
#define AHC_VIDEO_PLAY_FF_EOS  				(0x00000002)
#define AHC_VIDEO_PLAY_BW_BOS  				(0x00000004)
#define AHC_VIDEO_PLAY_ERROR_STOP  			(0x00000008)
#define AHC_VIDEO_PLAY_UNSUPPORTED_AUDIO  	(0x00000010)

//For Audio Callback Event [Ref:mmpf_audio_ctl.h]
#define AHC_AUDIO_EVENT_EOF     			(0x00000001)
#define AHC_AUDIO_EVENT_PLAY				(0x00000002)

#define MAX_ALLOWED_WORD_LENGTH (57)

/*===========================================================================
 * Enum define
 *===========================================================================*/ 

// Note that these enumerates must be group in video, audio and movie order.
// leave the naming such as AHC_CLIP for better comparison with CarDV code base.
typedef enum _AHC_VIDEO_CODEC_FORMAT
{
    AHC_VIDEO_CODEC_NONE        = 0,
    AHC_VIDEO_CODEC_H263        = 0x1,
    AHC_VIDEO_CODEC_MP4V_SP     = 0x2,
    AHC_VIDEO_CODEC_MP4V        = 0x2,
    AHC_VIDEO_CODEC_MP4V_ASP    = 0x4,
    AHC_VIDEO_CODEC_H264        = 0x8,
    AHC_VIDEO_CODEC_RV          = 0x10,
    AHC_VIDEO_CODEC_WMV         = 0x20,
    AHC_VIDEO_CODEC_UNSUPPORTED = 0x80,
    AHC_VIDEO_CODEC_MAX
} AHC_VIDEO_CODEC_FORMAT;

typedef enum _AHC_PLAYBACK_CMDS {
    AHC_PB_MOVIE_PAUSE = 0,
    AHC_PB_MOVIE_RESUME,
    AHC_PB_MOVIE_FAST_FORWARD,
    AHC_PB_MOVIE_FAST_FORWARD_RATE,
    AHC_PB_MOVIE_BACKWARD,
    AHC_PB_MOVIE_BACKWARD_RATE,
    AHC_PB_MOVIE_AUDIO_MUTE,
    AHC_PB_MOVIE_SEEK_BY_TIME,
    AHC_PB_MOVIE_ROTATE,
    AHC_PB_MOVIE_NORMAL_PLAY_SPEED,
    AHC_PB_MOVIE_SEEK_TO_SOS
} AHC_PLAYBACK_CMDS;

typedef enum _AHC_PLAYBACKSEL {
    AHC_PLAYBACK_PREVIOUS = 0,
    AHC_PLAYBACK_CURRENT  ,
    AHC_PLAYBACK_NEXT     ,
    AHC_PLAYFILESEL_MAX
} AHC_PLAYBACKSEL;

typedef enum _AHC_FILETYPE {
    AHC_FILETYPE_IMAGE = 0,
    AHC_FILETYPE_VIDEO ,
    AHC_FILETYPE_AUDIO ,
    AHC_FILETYPE_UNSUPPORTED
} AHC_FILETYPE;

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef struct _AHC_IMG_ATTR {
    UINT16                  ImageHSize;
    UINT16                  ImageVSize;
    UINT16                  ThumbHSize;
    UINT16                  ThumbVSize;
} AHC_IMG_ATTR;

typedef struct _AHC_VIDEO_ATTR
{
    AHC_VIDEO_CODEC_FORMAT  VideoFormat[2];
    AHC_AUDIO_CODEC_FORMAT  AudioFormat;
    UINT32                  VideoAvailable[2];
    UINT32                  AudioAvailable;
    UINT32                  Seekable[2];
    UINT32                  Width[2];
    UINT32                  Height[2];
    UINT32                  SampleRate;
    UINT32                  Channels;
    UINT32                  TotalTime;
} AHC_VIDEO_ATTR;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

// Video/Audio Playback Function
void 		AHC_SetVideoPlayStartTime(UINT32 ulStartTime);
AHC_BOOL 	AHC_GetVideoPlayStopStatus(UINT32 *pwValue);
AHC_BOOL 	AHC_SetVideoPlayStopStatus(UINT32 Value);
AHC_BOOL 	AHC_GetAudioPlayStopStatus(UINT32 *pwValue);
AHC_BOOL 	AHC_SetAudioPlayStopStatus(UINT32 Value);
AHC_BOOL 	AIHC_GetCurrentPBFileType(UINT32 *pFileType);
AHC_BOOL 	AIHC_GetCurrentPBHeight(UINT16 *pHeight);
AHC_BOOL 	AIHC_StopPlaybackMode(void);
AHC_BOOL 	AIHC_SetPlaybackMode(void);
void        AHC_SetPlayBackRearCam(AHC_BOOL bIsRear);
AHC_BOOL    AHC_GetPlayBackRearCam(void);

#endif //_AHC_MEDIAPLAYBACK_H_
