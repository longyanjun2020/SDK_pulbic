//==============================================================================
//
//  File        : statevideofunc.h
//  Description : INCLUDE File for the StateCameraFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEVIDEOFUNC_H_
#define _STATEVIDEOFUNC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "MenuCommon.h"
#include "MenuSetting.h"
#include "ahc_motor.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE)
#define UVC_XU_RECORDTIME_CONTROL   (0x01)
#define UVC_XU_RECORDRES_CONTROL    (0x02)
#define UVC_XU_FILE_CONTROL         (0x03)
#define UVC_XU_PICTURE_CONTROL      (0x04)
#define UVC_XU_GSENSOR_CONTROL      (0x05)
#define UVC_XU_AUDIO_CONTROL        (0x06)
#define UVC_XU_REC_STATUS_CONTROL   (0x07)
#define UVC_XU_REC_MODE_CONTROL     (0x08)
#define UVC_XU_FIRMWARE_CONTROL     (0x09)
#define UVC_XU_MMC_CONTROL          (0x0A)
#define UVC_XU_SWITCH_MSDC_MODE     (0x0B)
#endif

/*===========================================================================
 * Enumeration
 *===========================================================================*/

typedef enum {
    F_LARGE_R_SMALL = 0,
    F_SMALL_R_LARGE,
    ONLY_FRONT,
    ONLY_REAR,
    F_HALF_R_HALF,
    PIP_SWAP_TYPE_NUM
} PIP_SWAP_TYPE;

typedef enum {
    VIDEO_REC_START,
    VIDEO_REC_PAUSE,
    VIDEO_REC_STOP,
    VIDEO_REC_CAPTURE,
    VIDEO_REC_PRERECD,
    VIDEO_REC_CARD_FULL,
    VIDEO_REC_NO_SD_CARD,
    VIDEO_REC_WRONG_MEDIA,
    VIDEO_REC_SEAMLESS_ERROR,
    VIDEO_REC_SD_CARD_ERROR
} VIDEO_RECORD_STATUS;

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

UINT32      VideoFunc_GetRecordTimeOffset(void);
void        VideoRecMode_PreviewUpdate(void);
AHC_BOOL    VideoRecMode_Start(void);
AHC_BOOL    VideoFunc_RecordStatus(void);
AHC_BOOL    VideoFunc_ExitVMDMode(void);
AHC_BOOL    VideoFunc_ZoomOperation(AHC_ZOOM_DIRECTION bZoomDir);
void        VideoFunc_PresetPrmSnrMode(MOVIESIZE_SETTING ubResolution);
void        VideoFunc_PresetFrameRate(MOVIESIZE_SETTING ubResolution);
AHC_BOOL    VideoFunc_RecordStatus(void);
AHC_BOOL    VideoFunc_RecordRestart(void);
AHC_BOOL    VideoFunc_RecordStop(void);
void        VideoTimer_Event_Busy(AHC_BOOL bBusy);
AHC_BOOL    VideoTimer_Event_IsBusy(void);
AHC_BOOL    VideoTimer_Start(UINT32 ulTime);
AHC_BOOL    VideoTimer_Stop(void);
AHC_BOOL    VideoFunc_Preview(void);
AHC_BOOL    VideoFunc_PreRecordStatus(void);
AHC_BOOL    VideoFunc_SetFileLock(void);
AHC_BOOL    VideoFunc_Shutter(void);
AHC_BOOL    VideoFunc_ShutterFail(void);
AHC_BOOL    VideoFunc_LockFileEnabled(void);
AHC_BOOL    VideoRec_TriggeredByVMD(void);
AHC_BOOL    VideoFunc_IsShareRecordStarted(void);

AHC_BOOL    StateSelectFuncVideoRecordMode(void);
AHC_BOOL    StateVideoRecMode_StartRecordingProc(UINT32 ulJobEvent);
AHC_BOOL    StateVideoRecMode_StopRecordingProc(UINT32 ulJobEvent);

#if (ENABLE_ADAS_LDWS || ENABLE_ADAS_FCWS || ENABLE_ADAS_SAG)
AHC_BOOL    AHC_VIDEO_SetRecordModeInitADASMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeUnInitADASMode(void);
#endif
AHC_BOOL    VideoFunc_ParkingModeStart(void);
AHC_BOOL    VideoFunc_ParkingModeStop(void);
void        VRMotionDetectCB(void);

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE == 1)
AHC_BOOL    VideoFunc_UVCXUCmdRegisterHandler(void);
#endif

#endif //_STATEVIDEOFUNC_H_

