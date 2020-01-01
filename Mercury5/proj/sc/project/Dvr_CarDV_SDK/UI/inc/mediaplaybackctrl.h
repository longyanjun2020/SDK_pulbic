
//==============================================================================
//
//  File        : mediaplaybackctrl.h
//  Description : INCLUDE File for the MediaPlaybackCtrl function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MEDIAPLAYBACKCTRL_H_
#define _MEDIAPLAYBACKCTRL_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

#include "MenuCommon.h"
#include "ahc_common.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define STATE_MOV_INVALID       ((AHC_MODE_PLAYBACK<<16)|AHC_SYS_VIDPLAY_INVALID)
#define STATE_MOV_LOADED        ((AHC_MODE_PLAYBACK<<16)|AHC_SYS_VIDPLAY_LOADED)
#define STATE_MOV_IDLE          ((AHC_MODE_PLAYBACK<<16)|AHC_SYS_VIDPLAY_IDLE)
#define STATE_MOV_EXECUTE       ((AHC_MODE_PLAYBACK<<16)|AHC_SYS_VIDPLAY_EXECUTING)
#define STATE_MOV_PAUSE         ((AHC_MODE_PLAYBACK<<16)|AHC_SYS_VIDPLAY_PAUSE)

#define STATE_AUD_PLAY        	((AHC_MODE_PLAYBACK<<16)|AHC_SYS_AUDPLAY_START)
#define STATE_AUD_PAUSE         ((AHC_MODE_PLAYBACK<<16)|AHC_SYS_AUDPLAY_PAUSE)
#define STATE_AUD_STOP       	((AHC_MODE_PLAYBACK<<16)|AHC_SYS_AUDPLAY_STOP)
#define STATE_AUD_INVALID       ((AHC_MODE_PLAYBACK<<16)|AHC_SYS_AUDPLAY_INVALID)

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum _JPGPB_ZOOM_CTRL 
{
	JPGPB_ZOOM_IN    = 0 ,
	JPGPB_ZOOM_OUT       ,
    JPGPB_ZOOM_NONE  = 2
} JPGPB_ZOOM_CTRL;

typedef enum _JPGPB_PAN_CTRL 
{
    JPGPB_PAN_UP   = 0 ,
    JPGPB_PAN_DOWN     ,
    JPGPB_PAN_LEFT     ,
    JPGPB_PAN_RIGHT    ,
    JPGPB_PAN_NUM = 4
} JPGPB_PAN_CTRL;

typedef enum _MEDIAPB_ROTATE_CTRL 
{
    MEDIAPB_ROTATE_CW  = 0 ,
    MEDIAPB_ROTATE_CCW     ,
    MEDIAPB_ROTATE_MAX     
} MEDIAPB_ROTATE_CTRL;

typedef enum _PLAYBACK_FILESEL
{
    PLAYBACK_PREVIOUS = 0,
    PLAYBACK_CURRENT  ,
    PLAYBACK_NEXT     ,     
    PLAYBACK_MAX   
} PLAYBACK_FILESEL;

typedef enum _PLAYBACK_FILETYPE
{
    PLAYBACK_IMAGE_TYPE = 0,
    PLAYBACK_VIDEO_TYPE ,
    PLAYBACK_AUDIO_TYPE ,
    PLAYBACK_TYPE_UNSUPPORTED
}PLAYBACK_FILETYPE;

typedef enum _MOV_PLAYBACK_STATUS
{
    MOV_STATE_STOP ,
    MOV_STATE_PLAY ,
    MOV_STATE_PAUSE,
    MOV_STATE_FF   
}MOV_PLAYBACK_STATUS;

typedef enum _AUD_PLAYBACK_STATUS
{
    AUD_STATE_STOP ,
    AUD_STATE_PLAY ,
    AUD_STATE_PAUSE,
    AUD_STATE_FF   
}AUD_PLAYBACK_STATUS;

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _JPG_PLAYBACK_CONFIG
{
    UINT8  iRotate;
    UINT32 iStartX;
    UINT32 iStartY;
    UINT32 iCurZoomLevel;
    UINT32 iDecodeWidth;
    UINT32 iDecodeHeight;
    UINT32 iJpegWidth;
    UINT32 iJpegHeight;
    UINT32 iJpegDispWidth;
    UINT32 iJpegDispHeight;
}JPG_PLAYBACK_CONFIG;

typedef struct _MOV_PLAYBACK_CONFIG
{
    MOV_PLAYBACK_STATUS iState;
    UINT8     iRotate;

}MOV_PLAYBACK_CONFIG;

typedef struct _AUD_PLAYBACK_CONFIG
{
    AUD_PLAYBACK_STATUS iState;
}AUD_PLAYBACK_CONFIG;

/*===========================================================================
 * Function prototype 
 *===========================================================================*/
 
PLAYBACK_FILETYPE GetPlayBackFileType(void);
JPG_PLAYBACK_CONFIG *GetJpgConfig(void);
void JpgPlaybackParamReset(void);
AHC_BOOL JpgPlayback_Play(void);
AHC_BOOL JpgPlayback_Zoom( JPGPB_ZOOM_CTRL uJpgZoomSel );
AHC_BOOL JpgPlayback_IsZoomNone(void); 
AHC_BOOL JpgPlayback_Pan( JPGPB_PAN_CTRL ulDir );
AHC_BOOL JpgPlayback_Rotate( MEDIAPB_ROTATE_CTRL ulDir );
MOV_PLAYBACK_CONFIG *GetMovConfig(void);
AHC_BOOL GetMovTotalTime(UINT32 *ultime);
AHC_BOOL GetMovCurrPlayTime(UINT32 *ultime);
void MovPlaybackParamReset(void);
AHC_BOOL MovPlayback_Play(void);
AHC_BOOL MovPlayback_Forward(void);
AHC_BOOL MovPlayback_Backward(void);
AHC_BOOL MovPlayback_NormalSpeed(void);
AHC_BOOL MovPlayback_Pause(void);
AHC_BOOL MovPlayback_Resume(void);
AHC_BOOL MovPlayback_VolumnUp(void);
AHC_BOOL MovPlayback_VolumnDown(void);
AHC_BOOL MovPlayback_Rotate(MEDIAPB_ROTATE_CTRL ulDir);
AHC_BOOL MediaPlaybackConfig(UINT8 iSelect);

AUD_PLAYBACK_CONFIG *GetAudConfig(void);
AHC_BOOL GetAudCurrPlayTime(UINT32 *ultime);
void AudPlaybackParamReset(void);
AHC_BOOL AudPlayback_Play(void);
AHC_BOOL AudPlayback_Forward(void);
AHC_BOOL AudPlayback_Backward(void);
AHC_BOOL AudPlayback_NormalSpeed(void);
AHC_BOOL AudPlayback_Pause(void);
AHC_BOOL AudPlayback_Resume(void);

#endif //_MEDIAPLAYBACKCTRL_H_
