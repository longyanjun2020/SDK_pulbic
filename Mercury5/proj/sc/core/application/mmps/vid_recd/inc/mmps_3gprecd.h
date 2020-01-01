/**
 @file mmps_3gprecd.h
 @brief Header File for the Host 3GP RECORDER API.
 @author Will Tseng
 @version 1.0
*/

#ifndef _MMPS_3GPRECD_H_
#define _MMPS_3GPRECD_H_

//===============================================================================
//
//                               INCLUDE FILE
//
//===============================================================================

#include "lib_retina.h"
#include "mmp_dsc_inc.h"
#include "mmp_display_inc.h"
#include "mmp_icon_inc.h"
#include "mmp_scal_inc.h"
#include "mmp_snr_inc.h"
#include "mmp_ptz_inc.h"
#include "mmp_mjpeg_inc.h"
#include "mmp_vidrec_inc.h"
#include "aitu_calendar.h"
#include "ait_config.h"

//===============================================================================
//
//                               MACRO DEFINE
//
//===============================================================================

#define VR_MAX_PREVIEW_NUM              (VIF_SENSOR_MAX_NUM)
#define VR_MAX_ENCODE_NUM               (MMPS_VR_RECD_ID_NUM)
#define VR_MAX_H264_STREAM_NUM          (MMPS_H264_STRM_ID_NUM)

#define VR_MIN_TIME_TO_RECORD           (2)     ///< 2 seconds

#define VR_QUERY_STATES_TIMEOUT         (300)   ///< 3000 millisecond.

#define VR_CAM_SEL_TO_RECD_SEL(c)       (c == PRM_SENSOR  ? MMPS_VR_PRM_RECD : \
                                         c == SCD_SENSOR  ? MMPS_VR_SCD_RECD : \
                                         c == USBH_SENSOR ? MMPS_VR_SCD_RECD : \
                                         c == TRD_SENSOR  ? MMPS_VR_TRD_RECD : \
                                         MMPS_VR_RECD_ID_NUM)

//===============================================================================
//
//                               ENUMERATION
//
//===============================================================================

// Video Stream Index (Record File)
typedef enum _MMPS_VIDRECD_ID {
    MMPS_VR_PRM_RECD = 0x00,
    MMPS_VR_SCD_RECD,
    MMPS_VR_TRD_RECD,
    MMPS_VR_RECD_ID_NUM
} MMPS_VIDRECD_ID;

// Video Stream Index (Streaming)
typedef enum _MMPS_H264_STRM_ID {
    MMPS_H264_STRM_PRM = 0x00,
    MMPS_H264_STRM_SCD,
    MMPS_H264_STRM_TRD,
    MMPS_H264_STRM_ID_NUM
} MMPS_H264_STRM_ID;

// Video encode count
typedef enum _MMPS_ENC_COUNT {
    MMPS_ENC_COUNT_0 = 0x00,
    MMPS_ENC_COUNT_1,
    MMPS_ENC_COUNT_2,
    MMPS_ENC_COUNT_3
} MMPS_ENC_COUNT;

// Video Format (Must be sync with PCAM_USB_VIDEO_FORMAT)
typedef enum _MMPS_3GPRECD_VIDEO_FORMAT {
    MMPS_3GPRECD_VIDEO_FORMAT_OTHERS = 0x00,            ///< Video format, none
    MMPS_3GPRECD_VIDEO_FORMAT_H264,                     ///< Video format, H.264
    MMPS_3GPRECD_VIDEO_FORMAT_MJPEG,                    ///< Video format, MJPEG
    MMPS_3GPRECD_VIDEO_FORMAT_YUV422,                   ///< Video format, YUV422
    MMPS_3GPRECD_VIDEO_FORMAT_YUV420
} MMPS_3GPRECD_VIDEO_FORMAT;

// Audio Format, Sample rate, Bit rate
typedef enum _MMPS_3GPRECD_AUDIO_OPTION {
    MMPS_3GPRECD_AUDIO_AAC_BASE         = 0x00,         ///< Audio AAC format
    MMPS_3GPRECD_AUDIO_AAC_16K_32K      = 0x02,         ///< AAC    16KHz with 32kbps
    MMPS_3GPRECD_AUDIO_AAC_16K_64K,                     ///< AAC    16KHz with 64kbps
    MMPS_3GPRECD_AUDIO_AAC_22d05K_64K,                  ///< AAC 22.05KHz with 64kbps
    MMPS_3GPRECD_AUDIO_AAC_22d05K_128K,                 ///< AAC 22.05KHz with 128kbps
    MMPS_3GPRECD_AUDIO_AAC_32K_64K,                     ///< AAC 32KHz with 64kbps
    MMPS_3GPRECD_AUDIO_AAC_32K_128K,                    ///< AAC 32KHz with 128kbps
    MMPS_3GPRECD_AUDIO_AAC_48K_128K,                    ///< AAC 48KHz with 128kbps
    MMPS_3GPRECD_AUDIO_AAC_44d1K_64K,                   ///< AAC 44.1KHz with 64kbps
    MMPS_3GPRECD_AUDIO_AAC_44d1K_128K,                  ///< AAC 44.1KHz with 128kbps

    MMPS_3GPRECD_AUDIO_AMR_BASE         = 0x10,         ///< Audio AMR format
    MMPS_3GPRECD_AUDIO_AMR_4d75K,                       ///< AMR 4.75KHz with 8kbps
    MMPS_3GPRECD_AUDIO_AMR_5d15K,                       ///< AMR 5.15KHz with 8kbps
    MMPS_3GPRECD_AUDIO_AMR_12d2K,                       ///< AMR 12.2KHz with 8kbps

    //ADPCM section, need to sync with MMPF_SetADPCMEncMode
    MMPS_3GPRECD_AUDIO_ADPCM_16K_22K,                   ///< ADPCM 16KHz with 22kbps
    MMPS_3GPRECD_AUDIO_ADPCM_32K_22K,                   ///< ADPCM 32KHz with 22kbps
    MMPS_3GPRECD_AUDIO_ADPCM_44d1K_22K,                 ///< ADPCM 44.1KHz with 22kbps
    MMPS_3GPRECD_AUDIO_ADPCM_48K_22K,                   ///< ADPCM 48KHz with 22kbps

    MMPS_3GPRECD_AUDIO_MP3_32K_128K,                    ///< MP3 32KHz with 128kbps
    MMPS_3GPRECD_AUDIO_MP3_44d1K_128K,                  ///< MP3 44.1KHz with 128kbps

    MMPS_3GPRECD_AUDIO_PCM_16K,                         ///< Raw PCM 16KHz
    MMPS_3GPRECD_AUDIO_PCM_32K                          ///< Raw PCM 32KHz
} MMPS_3GPRECD_AUDIO_OPTION;

// Audio Format
typedef enum _MMPS_3GPRECD_AUDIO_FORMAT {
    MMPS_3GPRECD_AUDIO_FORMAT_AAC = 0x00,               ///< Video encode with AAC audio
    MMPS_3GPRECD_AUDIO_FORMAT_AMR,                      ///< Video encode with AMR audio
    MMPS_3GPRECD_AUDIO_FORMAT_ADPCM,                    ///< Video encode with ADPCM audio
    MMPS_3GPRECD_AUDIO_FORMAT_MP3,                      ///< video encode with MP3 audio
    MMPS_3GPRECD_AUDIO_FORMAT_PCM                       ///< video encode with raw PCM audio
} MMPS_3GPRECD_AUDIO_FORMAT;

// Audio Data Type
typedef enum _MMPS_3GPRECD_AUDIO_DATATYPE {
    MMPS_3GPRECD_NO_AUDIO_DATA = 0,
    MMPS_3GPRECD_REC_AUDIO_DATA,
    MMPS_3GPRECD_SILENCE_AUDIO_DATA
} MMPS_3GPRECD_AUDIO_DATATYPE;

// Encode Parameters
typedef enum _MMPS_3GPRECD_PARAMETER {
    MMPS_3GPRECD_PARAMETER_PREVIEWMODE = 0x0,           ///< Encode sensor mode
    MMPS_3GPRECD_PARAMETER_SRCMODE,                     ///< Card or memory mode
    MMPS_3GPRECD_PARAMETER_VIDEO_FORMAT,                ///< Video format
    MMPS_3GPRECD_PARAMETER_AUDIO_FORMAT,                ///< Audio format
    MMPS_3GPRECD_PARAMETER_RESOLUTION,                  ///< Video resolution
    MMPS_3GPRECD_PARAMETER_BITRATE,
    MMPS_3GPRECD_PARAMETER_FRAME_RATE,                  ///< Video frame rate
    MMPS_3GPRECD_PARAMETER_GOP,
    MMPS_3GPRECD_PARAMETER_PROFILE,                     ///< Video codec profile
    MMPS_3GPRECD_PARAMETER_DRAM_END                     ///< End of DRAM address for video encode
} MMPS_3GPRECD_PARAMETER;

// Stream Callback Type
typedef enum _MMPS_3GPRECD_STREAMCB_TYPE {
    MMPS_3GPRECD_STREAMCB_VIDMOVE = 0,                  ///< move video stream
    MMPS_3GPRECD_STREAMCB_VIDUPDATE,                    ///< update video stream
    MMPS_3GPRECD_STREAMCB_AUDMOVE,                      ///< move audio stream
    MMPS_3GPRECD_STREAMCB_AUDUPDATE                     ///< update audio stream
} MMPS_3GPRECD_STREAMCB_TYPE;

#if (SUPPORT_VUI_INFO)
// Shutter Type
typedef enum _MMPS_SEI_SHUTTER_TYPE {
    MMPS_SEI_SHUTTER_1920x1080_29d97 = 0,
    MMPS_SEI_SHUTTER_1280x720_59d94,
    MMPS_SEI_SHUTTER_1280x720_29d97,
    MMPS_SEI_SHUTTER_848x480_29d97,
    MMPS_SEI_SHUTTER_NONE
} MMPS_SEI_SHUTTER_TYPE;
#endif

// Y-Pipe Frame Type
typedef enum _MMPS_3GPRECD_Y_FRAME_TYPE {
    MMPS_3GPRECD_Y_FRAME_TYPE_NONE = 0,
    MMPS_3GPRECD_Y_FRAME_TYPE_VMD,
    MMPS_3GPRECD_Y_FRAME_TYPE_ADAS,
    MMPS_3GPRECD_Y_FRAME_TYPE_MAX
} MMPS_3GPRECD_Y_FRAME_TYPE;

// Zoom Path
typedef enum _MMPS_3GPRECD_ZOOM_PATH {
    MMPS_3GPRECD_ZOOM_PATH_NONE = 0,
    MMPS_3GPRECD_ZOOM_PATH_PREV,
    MMPS_3GPRECD_ZOOM_PATH_RECD,
    MMPS_3GPRECD_ZOOM_PATH_BOTH,
    MMPS_3GPRECD_ZOOM_PATH_MAX
} MMPS_3GPRECD_ZOOM_PATH;

// For Emergency recording action flow
typedef enum _MMP_3GPRECD_EMERG_ACTION {
    MMP_3GPRECD_EMERG_NO_ACT = 0,
    MMP_3GPRECD_EMERG_DUAL_FILE,
    MMP_3GPRECD_EMERG_SWITCH_FILE,
    MMP_3GPRECD_EMERG_MOVE_FILE,
    MMP_3GPRECD_EMERG_DEFAULT_ACT = MMP_3GPRECD_EMERG_SWITCH_FILE //MMP_3GPRECD_EMERG_MOVE_FILE //MMP_3GPRECD_EMERG_NO_ACT
} MMP_3GPRECD_EMERG_ACTION;

// H264 Streaming Usage
typedef enum _MMP_H264_STREAM_USAGE {
    MMP_H264_STREAM_USAGE_PCAM = 0,
    MMP_H264_STREAM_USAGE_WIFI,
    MMP_H264_STREAM_USAGE_NUM
} MMP_H264_STREAM_USAGE;

typedef enum _MMP_H264_STREAM_MODE {
    MMP_H264_STREAM_MODE_NONE = 0,
    MMP_H264_STREAM_MODE_VR,
    MMP_H264_STREAM_MODE_DSC,
    MMP_H264_STREAM_MODE_NUM
} MMP_H264_STREAM_MODE;

//===============================================================================
//
//                               STRUCTURES
//
//===============================================================================

// Frame rate
typedef struct _MMPS_3GPRECD_FRAMERATE {
    MMP_ULONG               ulTimeIncre;                                    ///< Video encode VOP time increment
    MMP_ULONG               ulTimeResol;                                    ///< Video encode VOP time resolution
} MMPS_3GPRECD_FRAMERATE;

// GOP
typedef struct _MMPS_3GPRECD_GOP {
    MMP_USHORT              usPFrameCount;                                  ///< P frame count in 1 GOP
    MMP_USHORT              usBFrameCount;                                  ///< Consecutive B frame count
} MMPS_3GPRECD_GOP;

// Record run-time change configuration
typedef struct _MMPS_3GPRECD_RUNTIME_CFG {
    MMP_USHORT              usVideoPreviewMode;                             ///< Index of video encode preview modes
    MMP_USHORT              usVideoEncResIdx[VR_MAX_ENCODE_NUM];            ///< Index of video encode resolutions
    MMPS_3GPRECD_FRAMERATE  SnrFrameRate[VR_MAX_ENCODE_NUM];                ///< Sensor input frame rate settings
    MMPS_3GPRECD_FRAMERATE  EncFrameRate[VR_MAX_ENCODE_NUM];                ///< Video encode frame rate settings
    MMPS_3GPRECD_FRAMERATE  MgrFrameRate[VR_MAX_ENCODE_NUM];                ///< Container frame rate settings
    MMP_USHORT              usPFrameCount[VR_MAX_ENCODE_NUM];               ///< P frame count in 1 GOP
    MMP_USHORT              usBFrameCount[VR_MAX_ENCODE_NUM];               ///< Consecutive B frame count
    MMP_ULONG               ulBitrate[VR_MAX_ENCODE_NUM];                   ///< Video bitrate
    MMP_ULONG               ulAudBitrate;                                   ///< Audio bitrate
    MMP_ULONG               ulSizeLimit;                                    ///< Video stream size limit
    MMP_ULONG               ulTimeLimitMs;                                  ///< Video stream time limit (unit:ms)
    MMP_ULONG               ulReservedSpace;                                ///< Reserved storage space which can't be used by recorder or other application
    VIDENC_OUT_MODE         eVideoOutMode[VR_MAX_ENCODE_NUM];               ///< Card mode or streaming mode
    VIDENC_PROFILE          eVisualProfile[VR_MAX_ENCODE_NUM];              ///< Visual profile
    MMP_BOOL                bSlowMotionEn;                                  ///< Slow motion enable
    MMP_ULONG               ulMaxCompBufDuration[VR_MAX_ENCODE_NUM];        ///< Max compress buffer data duration (unit:sec)
} MMPS_3GPRECD_RUNTIME_CFG;

// Record preset configuration
typedef struct _MMPS_3GPRECD_PRESET_CFG {
    //++ For Encode
    MMP_USHORT              usEncWidth[VIDRECD_RESOL_MAX_NUM];              ///< Video encode width by resolution
    MMP_USHORT              usEncHeight[VIDRECD_RESOL_MAX_NUM];             ///< Video encode height by resolution
    MMP_ULONG               ulFps30BitrateMap[VIDRECD_RESOL_MAX_NUM][VIDRECD_QLEVEL_MAX_NUM];   ///< Bitrate map for 30fps
    MMP_ULONG               ulFps60BitrateMap[VIDRECD_RESOL_MAX_NUM][VIDRECD_QLEVEL_MAX_NUM];   ///< Bitrate map for 60fps
    MMPS_3GPRECD_FRAMERATE  stFrameRate[VIDRECD_FPS_MAX_NUM];               ///< Video encode frame rate settings
    //-- For Encode

    //++ For Feature
    MMP_BOOL                bSeamlessMode;                                  ///< Support seamless recording or not
    //-- For Feature

    //++ For Buffer Reserved Size
    MMP_ULONG               ulTailBufSize;
    MMP_ULONG               ulUVCTailBufSize;
    MMP_ULONG               ulUVCEmergTailBufSize;
    MMP_ULONG               ulDualEmergTailBufSize;
    #if (SUPPORT_VR_REFIX_TAILINFO)
    MMP_ULONG               ulReFixTailBufSize;
    #endif

    MMP_ULONG               ulAudioCompBufSize;
    MMP_ULONG               ulPrmVidCompBufSize;
    MMP_ULONG               ulScdVidCompBufSize;
    MMP_ULONG               ulTrdVidCompBufSize;
    MMP_ULONG               ulUvcVidCompBufSize;
    MMP_ULONG               ulWifiVidCompBufSize;
    //-- For Buffer Reserved Size
} MMPS_3GPRECD_PRESET_CFG;

// H264 stream encode configuration
typedef struct _MMP_H264_STREAM_ENC_CFG {
    MMPS_3GPRECD_FRAMERATE  SnrFrameRate;                                   ///< Sensor input frame rate settings
    MMPS_3GPRECD_FRAMERATE  EncFrameRate;                                   ///< Video encode frame rate settings
    MMPS_3GPRECD_FRAMERATE  MgrFrameRate;                                   ///< Container frame rate settings
    MMP_USHORT              usPFrameCount;                                  ///< P frame count in 1 GOP
    MMP_USHORT              usBFrameCount;                                  ///< Consecutive B frame count
    MMP_ULONG               ulBitrate;                                      ///< Video bitrate
    VIDENC_PROFILE          VisualProfile;                                  ///< Visual profile
} MMP_H264_STREAM_ENC_CFG;

typedef struct _MMP_H264_STREAM_OBJ {
    MMP_ULONG               ulEncID;
    MMP_USHORT              usStreamType;
    MMP_BOOL                bEnableWifi;
    MMP_UBYTE               ubStrmSel;
    MMP_UBYTE               ubCamSel;
    MMP_UBYTE               ubUiMode;
    MMP_H264_STREAM_USAGE   eUsage;
    MMP_H264_STREAM_ENC_CFG stEncCfg;
} MMP_H264_STREAM_OBJ;

#if (SUPPORT_TIMELAPSE)

#define MKTAG(a,b,c,d) (a | (b << 8) | (c << 16) | (d << 24))

// For time lapse
typedef struct _MMPS_3GPRECD_AVI_LIST {
    MMP_ULONG               List;
    MMP_ULONG               ulSize;
    MMP_ULONG               FourCC;
} MMPS_3GPRECD_AVI_LIST;

typedef struct _MMPS_3GPRECD_AVI_MainHeader {
    MMP_ULONG               FourCC;
    MMP_ULONG               ulSize;   // always 0x38bytes
    MMP_ULONG               ulMSecPreFrame;
    MMP_ULONG               ulMaxByteRate;
    MMP_ULONG               ulReServed;
    MMP_ULONG               ulFlag;
    MMP_ULONG               ulFrameNum;
    MMP_ULONG               ulInitFrame;
    MMP_ULONG               ulStreamNum;
    MMP_ULONG               ulBufferSize;
    MMP_ULONG               ulWidth;
    MMP_ULONG               ulHeight;
    MMP_ULONG               ulScale;
    MMP_ULONG               ulRate;
    MMP_ULONG               ulStart;
    MMP_ULONG               ulLength;
} MMPS_3GPRECD_AVI_MainHeader;

typedef struct _MMPS_3GPRECD_AVI_StreamHeader {
    MMP_ULONG               FourCC;
    MMP_ULONG               ulSize;     // always 0x38bytes
    MMP_ULONG               Type;
    MMP_ULONG               Handler;
    MMP_ULONG               ulFlag;
    MMP_ULONG               ulReServed;
    MMP_ULONG               InitFrame;
    MMP_ULONG               ulScale;
    MMP_ULONG               ulRate;
    MMP_ULONG               ulStart;
    MMP_ULONG               ulLength;
    MMP_ULONG               ulBufferSize;
    MMP_ULONG               ulQuality;
    MMP_ULONG               ulSampleSize;
    MMP_ULONG               ulReServed2;
    MMP_ULONG               ulReServed3;
} MMPS_3GPRECD_AVI_StreamHeader;

typedef struct _MMPS_3GPRECD_AVI_StreamFormat {
    MMP_ULONG               FourCC;
    MMP_ULONG               ulSize;     // always 0x28bytes
    MMP_ULONG               ulSize2;    // always 0x28
    MMP_ULONG               ulWidth;
    MMP_ULONG               ulHeight;
    MMP_ULONG               ulPlaneAndBitCount;
    MMP_ULONG               ubCompression;
    MMP_ULONG               ulImageSize;
    MMP_ULONG               ulXPelPerMeter;
    MMP_ULONG               ulYPelPerMeter;
    MMP_ULONG               ulColorUse;
    MMP_ULONG               ulColorBit;
} MMPS_3GPRECD_AVI_StreamFormat;

typedef struct _MMPS_3GPRECD_AVI_Header {
    MMP_ULONG               ubFourCC;
    MMP_ULONG               ulSize;     // always 327680bytes
} MMPS_3GPRECD_AVI_Header;

typedef struct _MMPS_3GPRECD_AVI_IndexEntry {
    MMP_ULONG               ubFourCC;
    MMP_ULONG               ulFlag;
    MMP_ULONG               ulPos;
    MMP_ULONG               ulSize;
} MMPS_3GPRECD_AVI_IndexEntry;
#endif

// AHC Parameters
typedef struct _MMPS_3GPRECD_AHC_PREVIEW_INFO {
    MMP_BOOL                bPreviewMirror;
    MMP_SCAL_FIT_MODE       sFitMode;
    MMP_ULONG               ulPreviewBufW;  // Scale Out Buffer Width
    MMP_ULONG               ulPreviewBufH;  // Scale Out Buffer Height
    MMP_ULONG               ulDispStartX;
    MMP_ULONG               ulDispStartY;
    MMP_ULONG               ulDispWidth;    // Display Window Width
    MMP_ULONG               ulDispHeight;   // Display Window Height
} MMPS_3GPRECD_AHC_PREVIEW_INFO;

typedef struct _MMPS_3GPRECD_AHC_VIDEO_INFO {
    MMP_SCAL_FIT_MODE       sFitMode;
    MMP_ULONG               ulVidEncW;
    MMP_ULONG               ulVidEncH;
    MMP_ULONG               ulVidEncBufW;
    MMP_ULONG               ulVidEncBufH;
} MMPS_3GPRECD_AHC_VIDEO_INFO;

//===============================================================================
//
//                               FUNCTION PROTOTYPES
//
//===============================================================================

/** @addtogroup MMPS_3GPRECD
@{
*/

MMPS_3GPRECD_PRESET_CFG* MMPS_3GPRECD_GetPresetCfg(void);
MMPS_3GPRECD_RUNTIME_CFG* MMPS_3GPRECD_GetRuntimeCfg(void);

/* Common Preview Config Function */
MMP_ERR MMPS_3GPRECD_CustomedPreviewAttr(MMP_UBYTE  ubCamSel,
                                         MMP_BOOL   bUserConfig,
                                         MMP_BOOL   bMirror,
                                         MMP_UBYTE  sFitMode,
                                         MMP_USHORT usBufWidth, MMP_USHORT usBufHeight,
                                         MMP_USHORT usStartX,   MMP_USHORT usStartY,
                                         MMP_USHORT usWinWidth, MMP_USHORT usWinHeight);
MMP_ERR MMPS_3GPRECD_GetPreviewMirror(MMP_UBYTE ubCamSel, MMP_BOOL *pbMirror);
MMP_ERR MMPS_3GPRECD_GetPreviewPipeWH(MMP_UBYTE ubCamSel, MMP_ULONG *pulAlignPrevW, MMP_ULONG *pulAlignPrevH);
MMP_ERR MMPS_3GPRECD_GetDisplayRes(MMP_UBYTE ubCamSel, MMP_ULONG *pulWidth, MMP_ULONG *pulHeight);
MMP_ERR MMPS_3GPRECD_GetDisplayPosition(MMP_UBYTE ubCamSel, MMP_ULONG *pulPosStartX, MMP_ULONG *pulPosStartY);
MMP_ERR MMPS_3GPRECD_GetPreviewPipeStatus(MMP_UBYTE ubCamSel, MMP_BOOL *pbEnable);
MMP_ERR MMPS_3GPRECD_EnablePreviewPipe(MMP_UBYTE ubCamSel, MMP_BOOL bEnable, MMP_BOOL bCheckFrameEnd);

/* 1st Preview Function */
MMP_ERR MMPS_3GPRECD_AdjustPrmShareRecdPipe(void);
MMP_ERR MMPS_3GPRECD_EnablePrmCamPreview(MMP_USHORT usPreviewMode);
MMP_ERR MMPS_3GPRECD_PrmCamPreviewStop(MMP_UBYTE ubCamSel);
MMP_ERR MMPS_3GPRECD_PrmCamPreviewStart(MMP_UBYTE ubCamSel, MMP_BOOL bCheckFrameEnd);

/* 2nd Preview Function */
MMP_ERR MMPS_3GPRECD_AdjustScdRecdPipe(MMP_UBYTE ubCamSel);
MMP_ERR MMPS_3GPRECD_AdjustScdPrevwPipe(MMP_UBYTE ubCamSel);
MMP_ERR MMPS_3GPRECD_ScdCamPreviewStop(MMP_UBYTE ubCamSel);
MMP_ERR MMPS_3GPRECD_ScdCamPreviewStart(MMP_UBYTE ubCamSel, MMP_BOOL bCheckFrameEnd);

/* VR Thumbnail Function */
MMP_ERR MMPS_3GPRECD_SetVRThumbEn(MMP_UBYTE ubEnable, MMP_UBYTE ubIsCreateJpg);
MMP_UBYTE MMPS_3GPRECD_GetVRThumbEn(void);
MMP_ERR MMPS_3GPRECD_SetVRThumbRingBufNum(MMP_UBYTE ubRingBufNum);
MMP_ERR MMPS_3GPRECD_SetVRThumbResol(MMP_ULONG ulJpegW, MMP_ULONG ulJpegH);
MMP_ERR MMPS_3GPRECD_GetVRThumbResol(MMP_ULONG *pulJpegW, MMP_ULONG *pulJpegH);
MMP_ERR MMPS_3GPRECD_StoreVRThumbToFile(MMP_BYTE ubFilename[], MMP_USHORT usFileNameLen, MMP_USHORT ulStreamType);

/* Memory Manage Function */
MMP_ERR MMPS_3GPRECD_AllocUVCEncMemory(void* pvCompHandle, MMP_USHORT usStreamType);
MMP_ERR MMPS_3GPRECD_FreeUVCEncMemory(MMP_USHORT usStreamType);
MMP_ERR MMPS_3GPRECD_AllocUVCMGRMemory(MMP_USHORT usStreamType, MMP_BOOL bMultiTrack);
MMP_ERR MMPS_3GPRECD_FreeUVCMGRMemory(MMP_USHORT usStreamType);
MMP_ERR MMPS_3GPRECD_AllocMGRMemory(MMP_USHORT usStrmType, MMP_BOOL bMultiTrack);
MMP_ERR MMPS_3GPRECD_FreeMGRMemory(MMP_USHORT usStrmType);
MMP_ERR MMPS_3GPRECD_AllocH264Memory(MMP_ULONG *pulEncId, void* pvCompHandle, MMP_USHORT usStreamType);
MMP_ERR MMPS_3GPRECD_FreeH264Memory(MMP_ULONG ulEncId);

/* Common Record Function */
MMP_ERR MMPS_3GPRECD_CustomedEncResol(MMP_UBYTE ubCamSel, MMP_UBYTE stFitMode, MMP_USHORT usWidth, MMP_USHORT usHeight);
MMP_ERR MMPS_3GPRECD_SetBitrate(MMP_UBYTE ubCamSel, MMP_ULONG ulBitrate);
MMP_ERR MMPS_3GPRECD_SetFrameRatePara(MMP_UBYTE                 ubCamSel,
                                      MMPS_3GPRECD_FRAMERATE    *pSnr_fps,
                                      MMPS_3GPRECD_FRAMERATE    *pEnc_fps,
                                      MMPS_3GPRECD_FRAMERATE    *pMgr_fps);
MMP_ERR MMPS_3GPRECD_SetPFrameCount(MMP_UBYTE ubCamSel, MMP_USHORT usFrmCnt);
MMP_ERR MMPS_3GPRECD_SetBFrameCount(MMP_UBYTE ubCamSel, MMP_USHORT usFrmCnt);
MMP_ERR MMPS_3GPRECD_SetProfile(MMP_UBYTE ubCamSel, VIDENC_PROFILE eProfile);
MMP_ERR MMPS_3GPRECD_SetContainerType(VIDMGR_CONTAINER_TYPE eType);
MMP_ERR MMPS_3GPRECD_SetFileName(MMP_USHORT usStreamType, MMP_BYTE bFilename[], MMP_USHORT usLength);
MMP_ERR MMPS_3GPRECD_SetUserDataAtom(MMP_USHORT usStreamType, MMP_BYTE bAtomName[], MMP_BYTE bUserDataBuf[], MMP_USHORT usUserDataLength);
MMP_ERR MMPS_3GPRECD_SetStoragePath(VIDENC_OUT_MODE eOutMode);
MMP_ERR MMPS_3GPRECD_SetReservedStorageSpace(MMP_ULONG ulRsvdSize);
MMP_ERR MMPS_3GPRECD_SetFileSizeLimit(MMP_ULONG ulSizeLimit);
MMP_ERR MMPS_3GPRECD_SetFileTimeLimit(MMP_ULONG ulTimeLimitMs);
MMP_ERR MMPS_3GPRECD_ChangeCurFileTimeLimit(MMP_ULONG ulTimeLimitMs);
MMP_ERR MMPS_3GPRECD_Set3GPCreateModifyTimeInfo(MMP_USHORT usStreamType, AUTL_DATETIME stDateTimeNew);
MMP_ERR MMPS_3GPRECD_GetParameter(MMP_UBYTE ubRecdSel, MMPS_3GPRECD_PARAMETER eParamType, MMP_ULONG *pulValue);
MMP_ERR MMPS_3GPRECD_UpdateParameter(MMP_ULONG ulStreamType, MMPS_3GPRECD_PARAMETER eParamType, void *param);
MMP_ERR MMPS_3GPRECD_SetRecordSpeed(VIDENC_SPEED_MODE eSpeedMode, VIDENC_SPEED_RATIO eSpeedRatio);
MMP_ERR MMPS_3GPRECD_SetSeamlessEnable(MMP_BOOL bStart);
MMP_ERR MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT eEvent, void *pvCallBack);
MMP_ERR MMPS_3GPRECD_SetNormalSkipFrmParam(MMP_ULONG ulTotalCount, MMP_ULONG ulContiCount);
MMP_ERR MMPS_3GPRECD_SetSeamlessSkipFrmParam(MMP_ULONG ulTotalCount, MMP_ULONG ulContiCount);
MMP_ERR MMPS_3GPRECD_SetH264EncUseMode(MMP_USHORT usStreamType, MMP_ULONG ulEncUseMode);
MMP_ERR MMPS_3GPRECD_SetMuxerConstFps(MMP_BOOL bEnable);
MMP_ERR MMPS_3GPRECD_SetMgrMultiTrackEn(MMP_BOOL bEnable);
MMP_ERR MMPS_3GPRECD_SetAVSyncMethod(VIDMGR_AVSYNC_METHOD eAVSyncMethod);
MMP_ERR MMPS_3GPRECD_SetAudioFormat(MMPS_3GPRECD_AUDIO_FORMAT eAudFmt, MMPS_3GPRECD_AUDIO_OPTION eOption);
MMP_ERR MMPS_3GPRECD_SetAudioRecMode(MMPS_3GPRECD_AUDIO_DATATYPE eMode);
MMP_ERR MMPS_3GPRECD_GetRecordPipeStatus(MMP_UBYTE ubCamSel, MMP_BOOL *pbEnable);
MMP_ERR MMPS_3GPRECD_GetEncodeCompBuf(MMP_USHORT usStreamType, MMP_ULONG *pulBufAddr, MMP_ULONG *pulBufSize, MMP_ULONG *pulThreshold);
MMP_LONG MMPS_3GPRECD_GetExpectedRecordTime(MMP_ULONG64 u64Space, MMP_ULONG ulVidBitRate, MMP_ULONG ulAudBitRate);
MMP_ERR MMPS_3GPRECD_GetFrameRatePara(MMP_UBYTE                 ubCamSel,
                                      MMPS_3GPRECD_FRAMERATE    *pSnr_fps,
                                      MMPS_3GPRECD_FRAMERATE    *pEnc_fps,
                                      MMPS_3GPRECD_FRAMERATE    *pMgr_fps);
MMP_ERR MMPS_3GPRECD_GetAllEncPreRecordTime(MMP_ULONG ulPreCaptureMs, MMP_ULONG *pulRealPreCaptureMs);
MMP_ERR MMPS_3GPRECD_GetRemainFrmTimeOffset(MMP_USHORT usStreamType, MMP_ULONG *pulTimeMs);

/* 1st Record Function */
MMP_ERR MMPS_3GPRECD_GetCurRecordingTime(MMP_ULONG *pulTimeMs);
MMP_ERR MMPS_3GPRECD_GetPrmEncoderStatus(VIDENC_FW_STATUS *peEncFwStatus);
MMP_ERR MMPS_3GPRECD_StartPrmPreEnc(MMP_ULONG *pulInPreEncMs);
MMP_ERR MMPS_3GPRECD_StartPrmRecord(void);
MMP_ERR MMPS_3GPRECD_StopPrmRecord(void);

/* 2nd Record Function */
MMP_ERR MMPS_3GPRECD_EnableScdRecd(MMP_BOOL bEnable);
MMP_ERR MMPS_3GPRECD_GetScdEncoderStatus(VIDENC_FW_STATUS *peEncFwStatus);
MMP_ERR MMPS_3GPRECD_StartScdPreEnc(MMP_ULONG *pulInPreEncMs);
MMP_ERR MMPS_3GPRECD_StartScdRecd(void);
MMP_ERR MMPS_3GPRECD_StopScdRecord(void);

/* 3rd Record Function */
MMP_ERR MMPS_3GPRECD_EnableTrdRecd(MMP_BOOL bEnable);
MMP_ERR MMPS_3GPRECD_GetTrdEncoderStatus(VIDENC_FW_STATUS *peEncFwStatus);
MMP_ERR MMPS_3GPRECD_StartTrdPreEnc(MMP_ULONG *pulInPreEncMs);
MMP_ERR MMPS_3GPRECD_StartTrdRecd(void);
MMP_ERR MMPS_3GPRECD_StopTrdRecord(void);

/* Multi-Record Function */
MMP_ERR MMPS_3GPRECD_StartAllRecord(void);
MMP_ERR MMPS_3GPRECD_StopAllRecord(void);

/* Share Record Function */
void MMPS_3GPRECD_SetShareRecordEn(MMP_BOOL bEnable);
MMP_BOOL MMPS_3GPRECD_IsShareRecordEn(void);
MMP_ERR MMPS_3GPRECD_SetShareFileTimeLimit(MMP_ULONG ulTimeLimitMs);
MMP_ERR MMPS_3GPRECD_GetSharePreEncDuration(MMP_ULONG *pulDuration);
MMP_ERR MMPS_3GPRECD_GetShareRecordingTime(MMP_ULONG *pulTime);

/* Wifi Streaming (H264) Function */
MMP_ERR MMPS_H264_STREAM_CustomedResol(MMP_UBYTE ubStrmSel, MMP_UBYTE sFitMode, MMP_USHORT usWidth, MMP_USHORT usHeight);
MMP_ERR MMPS_H264_STREAM_OpenStream(MMP_UBYTE ubStrmSel, MMP_UBYTE ubCamSel, MMP_UBYTE ubUsage, void** ppvHandle, MMP_H264_STREAM_MODE mode);
MMP_ERR MMPS_H264_STREAM_StartWifiStream(void* WifiHandle);
MMP_ERR MMPS_H264_STREAM_StopStream(void** WifiHandle);
MMP_ERR MMPS_H264_STREAM_Return2Display(void* WifiHandle);
MMP_ERR MMPS_H264_STREAM_StartUVCStream(void* UVCHandle);

/* Zoom Function */
MMP_ERR     MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH sPath, MMP_PTZ_ZOOM_DIR sZoomDir, MMP_USHORT usCurZoomStep);
MMP_ERR     MMPS_3GPRECD_GetCurZoomStep(MMP_UBYTE ubPipe, MMP_USHORT *usZoomStepNum);
MMP_ERR     MMPS_3GPRECD_SetZoomConfig(MMP_USHORT usMaxSteps, MMP_USHORT usMaxRatio);
MMP_UBYTE   MMPS_3GPRECD_GetCurZoomStatus(void);

/* Sticker Function */
MMP_ERR MMPS_3GPRECD_SetStickerAttr(MMP_STICKER_ATTR *pstStickerAttr);
MMP_ERR MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID stickerID, MMP_BOOL bEnable);
MMP_BOOL MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID stickerID);

/* TimeLapse Function */
#if (SUPPORT_TIMELAPSE)
MMP_ERR MMPS_3GPRECD_InitAVIFile(MMP_BYTE *bAviName, MMP_ULONG ulNameSize, MMP_ULONG ulWidth, MMP_ULONG ulHeight,
                                 MMP_ULONG CoedcFourCC, MMP_ULONG FrameRate, MMP_ULONG ulBitRate, MMP_BOOL bInit, MMP_ULONG *FileID);
MMP_ERR MMPS_3GPRECD_AVIAppendFrame(MMP_ULONG ulFID, MMP_UBYTE *pData, MMP_ULONG ulSize, MMP_ULONG64 *ulFileSize, MMP_ULONG *ulFrameNum);
#endif

/* Emergency Record Function */
MMP_ERR MMPS_3GPRECD_SetEmergFileName(MMP_BYTE bFileName[], MMP_USHORT usLength);
MMP_ERR MMPS_3GPRECD_EnableEmergentRecd(MMP_BOOL bEnable);
MMP_ERR MMPS_3GPRECD_StartEmergentRecd(MMP_BOOL bStopNormRecd);
MMP_ERR MMPS_3GPRECD_StopEmergentRecd(MMP_BOOL bBlocking);
MMP_ERR MMPS_3GPRECD_SetEmergentFileTimeLimit(MMP_ULONG ulTimeLimitMs);
MMP_ERR MMPS_3GPRECD_SetEmergPreEncTimeLimit(MMP_ULONG ulTimeLimitMs);
MMP_ERR MMPS_3GPRECD_GetEmergentRecordingTime(MMP_ULONG *ulTime);
MMP_ERR MMPS_3GPRECD_GetEmergentRecordingOffset(MMP_ULONG *ulTime);
MMP_ERR MMPS_3GPRECD_EnableUVCEmergentRecd(MMP_BOOL bEnable);
MMP_ERR MMPS_3GPRECD_EnableDualEmergentRecd(MMP_BOOL bEnable);
MMP_ERR MMPS_3GPRECD_SetEmergActionType(MMP_3GPRECD_EMERG_ACTION emergact);
MMP_3GPRECD_EMERG_ACTION MMPS_3GPRECD_GetEmergActionType(void);

/* Wifi Streaming (MJPEG) Function */
#if defined(ALL_FW)
MMP_ERR MMPS_MJPEG_STREAM_ConfigPipe(MMP_MJPEG_OBJ_PTR pstStreamObj,
                                     MMP_USHORT usStreamW, MMP_USHORT usStreamH,
                                     MMP_USHORT *pusAlignStreamW, MMP_USHORT *pusAlignStreamH);
MMP_ERR MMPS_MJPEG_OpenStream(MMP_UBYTE ubCamSel, MMP_USHORT usEncID, MMP_USHORT usMode, MMP_MJPEG_OBJ_PTR *ppHandle);
MMP_ERR MMPS_MJPEG_StartStream(MMP_UBYTE           ubMode,
                               MMP_MJPEG_OBJ_PTR   pHandle,
                               MMP_MJPEG_ENC_INFO  *pMjpegInfo,
                               MMP_MJPEG_RATE_CTL  *pRateCtrl);
MMP_ERR MMPS_MJPEG_StopStream(MMP_MJPEG_OBJ_PTR pHandle);
MMP_ERR MMPS_MJPEG_CloseStream(MMP_MJPEG_OBJ_PTR* ppHandle);
#endif

/* Misc Function */
MMP_ERR MMPS_3GPRECD_SetYFrameType(MMPS_3GPRECD_Y_FRAME_TYPE enType);
MMPS_3GPRECD_Y_FRAME_TYPE MMPS_3GPRECD_GetYFrameType(void);

#if (MGR_SUPPORT_AVI == 1)
#if (AVI_IDIT_CHUNK_EN == 1)
unsigned int MMPS_3GPMUX_Build_IDIT(void **ptr);
unsigned int MMPS_AVIMUX_Build_IDIT(void **ptr);
#endif
#endif

/// @}

#endif //  _MMPS_3GPRECD_H_

