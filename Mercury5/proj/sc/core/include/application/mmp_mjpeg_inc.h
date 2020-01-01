/// @ait_only
//==============================================================================
//
//  File        : mmp_mjpeg_inc.h
//  Description : INCLUDE File for the Common MJPEG Driver.
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_MJPEG_INC_H_
#define _MMP_MJPEG_INC_H_

/** @addtogroup MMPF_DSC
 *  @{
 */

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_MJPEG_STREAM_NUM (2)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

// Map to MMPF_STREAM_RING_ID
typedef enum _MMP_MJPEG_STREAM_ID {
    MMP_MJPEG_STREAM_FCAM_VIDEO = 0,
    MMP_MJPEG_STREAM_RCAM_VIDEO,
    MMP_MJPEG_STREAM_FCAM_AUDIO,
    MMP_MJPEG_STREAM_ID_NUM
} MMP_MJPEG_STREAM_ID;

typedef enum _MMP_STREAM_UI_MODE_ID {
    MMP_STREAM_UI_MODE_WIFI_VR = 0,
    MMP_STREAM_UI_MODE_WIFI_DSC,
    MMP_STREAM_UI_MODE_UVC_VR,
    MMP_STREAM_UI_MODE_UVC_DSC,
    MMP_STREAM_UI_MODE_ID_NUM
} MMP_STREAM_UI_MODE_ID;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMP_MJPEG_RATE_CTL
{
    MMP_ULONG               ulBitrate;
    MMP_USHORT              FPSx10;     // 300 = 30FPS, 75 = 7.5 FPS
} MMP_MJPEG_RATE_CTL;

typedef struct _MMP_MJPEG_OBJ
{
    MMP_USHORT              usEncID;    // JPEG structure index
    MMP_UBYTE               ubCamSel;
    MMP_STREAM_UI_MODE_ID   eUiModeID;
} MMP_MJPEG_OBJ, *MMP_MJPEG_OBJ_PTR;

typedef struct _MMP_MJPEG_ENC_INFO
{
    MMP_USHORT              usEncWidth;
    MMP_USHORT              usEncHeight;
    MMP_BOOL                bTargetCtl;
    MMP_BOOL                bLimitCtl;
    MMP_ULONG               bTargetSize;
    MMP_ULONG               bLimitSize;
    MMP_USHORT              bMaxTrialCnt;
    MMP_UBYTE               Quality;
} MMP_MJPEG_ENC_INFO;

/// @}

#endif // _MMP_MJPEG_INC_H_

/// @end_ait_only
