#ifndef _PCAM_API_H_
#define _PCAM_API_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "os_wrap.h"
#include "mmp_lib.h"
#include "mmps_3gprecd.h"
#include "mmpf_audio_ctl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define PCAM_SLOT_BUF_CNT (3) // 2~3
#define PCAM_SLOT_BUF_CNT_MULTI_STREAM (6) 

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum {
    PCAM_ERROR_NONE = 0,
    /* System Error */
    PCAM_SYS_ERR,
    PCAM_SYS_TIMEOUT,
    /* Pcam Error */
    PCAM_USB_INIT_ERR,
    PCAM_USB_PREVIEW_ERR,
    PCAM_USB_CAPTURE_ERR,
    /* Misc */
    PCAM_USB_FIRMWARE_ERR,
    PCAM_ERROR_MAX
} PCAM_USB_ERR;

// Must be sync with MMPS_3GPRECD_VIDEO_FORMAT
typedef enum _PCAM_USB_VIDEO_FORMAT {
    PCAM_USB_VIDEO_FORMAT_OTHERS = 0x00,
    PCAM_USB_VIDEO_FORMAT_H264,
    PCAM_USB_VIDEO_FORMAT_MJPEG, 
    PCAM_USB_VIDEO_FORMAT_YUV422,
    PCAM_USB_VIDEO_FORMAT_YUV420, 
    PCAM_USB_VIDEO_FORMAT_NUM
} PCAM_USB_VIDEO_FORMAT;

typedef enum _PCAM_USB_VIDEO_QUALITY {
    PCAM_USB_HIGH_Q = 0,
    PCAM_USB_NORMAL_Q,
    PCAM_USB_LOW_Q,
    PCAM_USB_QUALITY_NUM
} PCAM_USB_VIDEO_QUALITY;

// Must be sync with PCAM_RESOL_ID
typedef enum _PCAM_USB_VIDEO_RES { 
    PCAM_USB_RESOL_640x360 = 0, 
    PCAM_USB_RESOL_640x480,
    PCAM_USB_RESOL_720x480,
    PCAM_USB_RESOL_800x600,
    PCAM_USB_RESOL_848x480,
    PCAM_USB_RESOL_960x720,
    PCAM_USB_RESOL_1024x576,
    PCAM_USB_RESOL_1024x600,
    PCAM_USB_RESOL_1024x768,
    PCAM_USB_RESOL_1280x720,
    PCAM_USB_RESOL_1280x960,
    PCAM_USB_RESOL_1600x1200,
    PCAM_USB_RESOL_1920x1080,
    PCAM_USB_RESOL_2048x1536,
    PCAM_USB_RESOL_2176x1224,
    PCAM_USB_RESOL_2560x1440,
    PCAM_USB_RESOL_2560x1920,
    PCAM_USB_RESOL_NUM
} PCAM_USB_VIDEO_RES;

typedef enum _PCAM_USB_AUDIO_FORMAT {
    PCAM_USB_AUDIO_FORMAT_AAC,
    PCAM_USB_AUDIO_FORMAT_AMR,
    PCAM_USB_AUDIO_FORMAT_NUM 
} PCAM_USB_AUDIO_FORMAT;

typedef enum _PCAM_USB_DEBAND {
    PCAM_USB_DEBAND_60HZ,
    PCAM_USB_DEBAND_50HZ
} PCAM_USB_DEBAND;

typedef enum _PCAM_USB_SETTING_CONTEXT {
    PCAM_USB_SETTING_H264_RES = 0,
    PCAM_USB_SETTING_VIDEO_RES,
    PCAM_USB_SETTING_VIDEO_FORMAT,
    PCAM_USB_SETTING_VIDEO_QUALITY,
    PCAM_USB_SETTING_DEBAND,
    PCAM_USB_SETTING_AUDIO_FORMAT,
    PCAM_USB_SETTING_SATURATION,
    PCAM_USB_SETTING_CONTRAST,
    PCAM_USB_SETTING_BRIGHTNESS,
    PCAM_USB_SETTING_HUE,
    PCAM_USB_SETTING_GAMMA,
    PCAM_USB_SETTING_BACKLIGHT,
    PCAM_USB_SETTING_SHARPNESS,
    PCAM_USB_SETTING_GAIN,
    PCAM_USB_SETTING_WB,
    PCAM_USB_SETTING_LENS,
    PCAM_USB_SETTING_AF,
    PCAM_USB_SETTING_AE,
    PCAM_USB_SETTING_WB_TEMP,
    PCAM_USB_SETTING_DIGZOOM,
    PCAM_USB_SETTING_DIGPAN,
    PCAM_USB_SETTING_OUTPUT_SENSOR, // Dual sensor output case.
    PCAM_USB_SETTING_ALL
} PCAM_USB_SETTING_CONTEXT;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _PCAM_USB_CTX {
    MMPS_3GPRECD_VIDEO_FORMAT   videoFormat;
    MMP_USHORT                  videoQuality;
    MMP_USHORT                  videoRes;
    MMP_USHORT                  debandMode;
    MMPS_3GPRECD_AUDIO_FORMAT   audioFormat;
    MMP_USHORT                  audioInPath;
    MMP_AUD_LINEIN_CH           lineInChannel;
} PCAM_USB_CTX;

typedef struct _PCAM_USB_ZOOM {
    MMP_UBYTE                   Dir;            // 0 : zoom in, 1 : zoom out, 2 : zoom stop
    MMP_UBYTE                   RangeStep;      // How many step, defined at UVC.
    MMP_UBYTE                   RangeMin;       // The zoom range for each step, floating
    MMP_UBYTE                   RangeMax;       // The zoom range for each step, floating
} PCAM_USB_ZOOM;

typedef struct _PAN_USB_PANTILT {
    MMP_LONG                    PanMin;
    MMP_LONG                    PanMax;
    MMP_LONG                    TiltMin;
    MMP_LONG                    TiltMax;
    MMP_USHORT                  Steps;
} PCAM_USB_PANTILT;

typedef struct _PCAM_USB_INFO {
    PCAM_USB_VIDEO_FORMAT       pCamVideoFormat;
    PCAM_USB_VIDEO_QUALITY      pCamVideoQuality;
    PCAM_USB_VIDEO_RES          pCamVideoRes;
    PCAM_USB_DEBAND             pCamDebandMode;
    PCAM_USB_AUDIO_FORMAT       pCamAudioFormat;
    MMP_USHORT                  pCamVideoFrameRate;
    MMP_ULONG                   pCamVideoBitrate;
    MMP_USHORT                  pCamVideoPFrameCount;
    MMP_BOOL                    pCamVideoEnableTimeStamp;
    
    MMP_USHORT                  pCamSaturation;
    MMP_USHORT                  pCamContrast;
    MMP_USHORT                  pCamSharpness;
    MMP_USHORT                  pCamGain;
    MMP_SHORT                   pCamBrightness;
    MMP_SHORT                   pCamHue;
    MMP_SHORT                   pCamGamma;
    MMP_USHORT                  pCamBacklight;
    MMP_UBYTE                   pCamWB;
    MMP_USHORT                  pCamWBTemp;
    MMP_USHORT                  pCamLensPos;
    MMP_BOOL                    pCamEnableAF;
    MMP_BOOL                    pCamEnableAE;
    
    PCAM_USB_ZOOM               pCamDigZoom;
    PCAM_USB_PANTILT            pCamDigPan;
    PCAM_USB_VIDEO_FORMAT       pCam2ndVideoFormat;
    MMP_USHORT                  pCam2ndVideoWidth;
    MMP_USHORT                  pCam2ndVideoHeight;
    MMP_USHORT                  pCam2ndVideoFrameRate;
    MMP_ULONG                   pCam2ndVideoBitrate;
    MMP_BOOL                    pCam2ndVideoMirrorEn;
    MMP_BOOL                    pCamEnableMDTC;
    MMP_UBYTE                   pCamMdtcSensitivity;
} PCAM_USB_INFO;

// VC async. control block
typedef struct _PCAM_ASYNC_VC_CFG
{
    MMP_BOOL                    pCamEnableAsyncMode; // Enable Async mode or not
    MMP_UBYTE                   pCamOriginator;
    MMP_UBYTE                   pCamSelector;
    MMP_UBYTE                   pCamAttribute;
    MMP_UBYTE                   pCamValUnit;
} PCAM_ASYNC_VC_CFG;

typedef struct _PCAM_AHC_PREVIEW_INFO 
{
    MMP_BOOL                    bUserDefine;
    MMP_UBYTE                   ubPreviewMode;
    MMP_BOOL                    bUseCustBitrate;
    MMP_ULONG                   ulStreamBitrate;
} PCAM_AHC_PREVIEW_INFO;

#define MAX_MULTI_STREAM_ID  (6)

//#define MAX_H264_STREAM_ID  (6)
//#define MAX_H264_STREAMS    (4) //(MAX_NUM_ENC_SET)
//#define H264_STREAM_GROUP   (3)

typedef enum
{
    MS_LOCAL_VIEW = 0,
    MS_H264_VIEW,
    MS_MOTION_DETECT

} PCAM_MULTISTREAM_MODE ;

typedef enum 
{
    MS_H264     = 1,
    MS_MJPEG    = 2 ,
    MS_YUY2     = 3 ,
    MS_NV12     = 4,
    MS_NV21     = 5,
    MS_GRAY     = 6
} PCAM_MULTISTREAM_TYPE ;

typedef struct _PCAM_MULTISTREAM_SETTING 
{
    MMP_BOOL   bStreamActive; // active means the stream is inited and working.
    PCAM_MULTISTREAM_TYPE StreamType;
    MMP_USHORT usWidth;
    MMP_USHORT usHeight;
    
    MMP_USHORT usBitrate10Kbps;
    MMP_UBYTE  byFrameRate;
} PCAM_MULTISTREAM_SETTING;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

#if (SUPPORT_UVC_FUNC)
MMP_USHORT pcam_usb_preview_start(void);
MMP_USHORT pcam_usb_exit(void);
MMP_USHORT pcam_usb_set_attributes(MMP_UBYTE ubPcamAttrIdx, void *pcamValue );
PCAM_USB_INFO *pcam_usb_get_info(void);
MMP_USHORT pcam_usb_CustomedPreviewAttr(MMP_BOOL bUserConfig, MMP_UBYTE ubPrevSnrMode);
MMP_USHORT pcam_usb_CustomedStreamAttr(MMP_BOOL bUserConfig, MMP_ULONG ulBitrate);
void pcam_usb_setGain_UAC2ADC(MMP_SHORT sVoldb);
void pcam_usb_set_mix_mode(MMP_BOOL bUVCMixEn);
MMP_BOOL pcam_usb_get_mix_mode(void);
void pcam_usb_free_buffer(void);
MMP_USHORT pcam_usb_get_2nd_vid_fmt(void);
MMP_BOOL pcam_usb_get_timeStamp_status(void);
PCAM_MULTISTREAM_SETTING *pcam_usb_get_multistream(MMP_UBYTE byStreamId);
#endif

#endif //_PCAM_API_H_
