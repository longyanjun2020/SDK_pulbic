/**
* @file MediaCmn.h
*
* This header file defines the common interfaces of media.
*
*/

#ifndef __MEDIACMN_H__
#define __MEDIACMN_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
#define MEDIA_CHECK_FEATURE(_TABLE_, _FLAG_)    (0 != (_TABLE_ & _FLAG_))

#define MEDIA_VDO__ENABLE_VDO_CODEC_H263    0x0001
#define MEDIA_VDO__ENABLE_VDO_CODEC_MP4     0x0002
#define MEDIA_VDO__ENABLE_AUD_CODEC_AMR_NB  0x0001
#define MEDIA_VDO__ENABLE_AUD_CODEC_AMR_WB  0x0002
#define MEDIA_VDO__ENABLE_AUD_CODEC_AAC     0x0004
#define MEDIA_VDO__ENABLE_AUD_CODEC_WAV     0x0008
#define MEDIA_VDO__ENABLE_AUD_CODEC_MP3     0x0010
#define MEDIA_VDO__ENABLE_FPS_15            0x1000
#define MEDIA_VDO__ENABLE_FPS_30            0x2000
#define MEDIA_VDO__ENABLE_RES_SQCIF     0x00010000
#define MEDIA_VDO__ENABLE_RES_QCIF      0x00020000
#define MEDIA_VDO__ENABLE_RES_QVGA      0x00040000
#define MEDIA_VDO__ENABLE_RES_CIF       0x00080000
#define MEDIA_VDO__ENABLE_RES_VGA       0x00100000
#define MEDIA_VDO__ENABLE_RES_4CIF      0x00200000
#define MEDIA_VDO__ENABLE_RES_DVD_PAL   0x00400000
#define MEDIA_VDO__ENABLE_RES_DVD_NTSC  0x00800000

#define MEDIA_FMT__ENABLE_AUD_AMR_NB        0x00000020
#define MEDIA_FMT__ENABLE_AUD_AMR_WB        0x00000040
#define MEDIA_FMT__ENABLE_AUD_AAC           0x00000010
#define MEDIA_FMT__ENABLE_AUD_MP3           0x00000008
#define MEDIA_FMT__ENABLE_AUD_MIDI          0x00000002
#define MEDIA_FMT__ENABLE_AUD_WAV           0x00000001
#define MEDIA_FMT__ENABLE_AUD_WMA           0x00000100
#define MEDIA_FMT__ENABLE_AUD_RA            0x00000080
#define MEDIA_FMT__ENABLE_AUD_APE           0x00010000
#define MEDIA_FMT__ENABLE_AUD_M4A           0x00020000
#define MEDIA_FMT__ENABLE_AUD_ASF           0x00040000

#define MEDIA_FMT__ENABLE_AUD_ENCODER_AMR_NB               ((u32) 0x00000001)
#define MEDIA_FMT__ENABLE_AUD_ENCODER_AMR_WB               ((u32) 0x00000002)
#define MEDIA_FMT__ENABLE_AUD_ENCODER_WAV_IMAADPCM_4BIT    ((u32) 0x00000004)
#define MEDIA_FMT__ENABLE_AUD_ENCODER_WAV_IMAADPCM_3BIT    ((u32) 0x00000008)
#define MEDIA_FMT__ENABLE_AUD_ENCODER_WAV_MSADPCM4BIT      ((u32) 0x00000010)
#define MEDIA_FMT__ENABLE_AUD_ENCODER_MP3_LAYERII          ((u32) 0x00000020)
#define MEDIA_FMT__ENABLE_AUD_ENCODER_PCM                  ((u32) 0x00000040)
#define MEDIA_FMT__ENABLE_AUD_ENCODER_MP3_LAYERIII         ((u32) 0x00000080)

#define MEDIA_FMT__ENABLE_VDO_3GP           0x0001
#define MEDIA_FMT__ENABLE_VDO_MP4           0x0002
#define MEDIA_FMT__ENABLE_VDO_RM            0x0004
#define MEDIA_FMT__ENABLE_VDO_RMVB          0x0008
#define MEDIA_FMT__ENABLE_VDO_AVI           0x0010
#define MEDIA_FMT__ENABLE_VDO_FLV           0x0020
#define MEDIA_FMT__ENABLE_VDO_PS            0x0040
#define MEDIA_FMT__ENABLE_VDO_TS            0x0080
#define MEDIA_FMT__ENABLE_VDO_H324          0x0100
#define MEDIA_FMT__ENABLE_VDO_MPG           0x0200
#define MEDIA_FMT__ENABLE_VDO_VOB           0x0400
#define MEDIA_FMT__ENABLE_VDO_DAT           0x0800
#define MEDIA_FMT__ENABLE_VDO_DIVX          0x1000
#define MEDIA_FMT__ENABLE_VDO_MOV           0x2000
#define MEDIA_FMT__ENABLE_VDO_KMV           0x4000
#define MEDIA_FMT__ENABLE_VDO_MKV           0x8000

#define MEDIA_IMG__ENABLE_STEREO_EFFECT_RED_CYAN           ((u32) 0x00000001)

typedef enum Media_VdoCodec_e_
{
    MEDIA_VDO_CODEC__BEGIN,
    MEDIA_VDO_CODEC__H263 = MEDIA_VDO_CODEC__BEGIN,
    MEDIA_VDO_CODEC__MP4,
    MEDIA_VDO_CODEC__END = MEDIA_VDO_CODEC__MP4,
    MEDIA_VDO_CODEC__NUM
} Media_VdoCodec_e;    //Sync to MediaSrvVdoCodec_e

typedef enum Media_AudCodec_e_
{
    MEDIA_AUD_CODEC__BEGIN,
    MEDIA_AUD_CODEC__AMR_NB = MEDIA_AUD_CODEC__BEGIN,
    MEDIA_AUD_CODEC__AMR_WB,
    MEDIA_AUD_CODEC__AAC,
    MEDIA_AUD_CODEC__MP3,
    MEDIA_AUD_CODEC__WAV,
    MEDIA_AUD_CODEC__END = MEDIA_AUD_CODEC__WAV,
    MEDIA_AUD_CODEC__NUM
} Media_AudCodec_e;    //Sync to MediaSrvAudCodec_e

typedef enum Media_VdoEncodeFps_e_
{
    MEDIA_VDO_ENC_FPS__15,
    MEDIA_VDO_ENC_FPS__30,
    MEDIA_VDO_ENC_FPS__NUM
} Media_VdoEncodeFps_e;    //Sync to MediaSrvVdoEncodeFps_e

typedef enum Media_VdoEncodeRes_e_
{
    MEDIA_VDO_ENC_RES__4CIF,        /*704x576*/
    MEDIA_VDO_ENC_RES__CIF,         /*352x288*/
    MEDIA_VDO_ENC_RES__QCIF,        /*176x144*/
    MEDIA_VDO_ENC_RES__SUB_QCIF,    /*128x96*/
    MEDIA_VDO_ENC_RES__VGA,         /*640x480*/
    MEDIA_VDO_ENC_RES__QVGA,        /*320x240*/
    MEDIA_VDO_ENC_RES__WQVGA,       /*400x240*/
    MEDIA_VDO_ENC_RES__HVGA,        /*480x320*/
    MEDIA_VDO_ENC_RES__DVD_PAL,     /*720x480*/
    MEDIA_VDO_ENC_RES__DVD_NTSC,    /*720x480*/
    MEDIA_VDO_ENC_RES__NUM
} Media_VdoEncodeRes_e;    //Sync to MediaSrvVdoEncodeRes_e

typedef enum Media_Format_e_
{
    MEDIA_FMT__AUD_BEGIN,
    MEDIA_FMT__AUD_AMR_NB = MEDIA_FMT__AUD_BEGIN,
    MEDIA_FMT__AUD_AMR_WB,
    MEDIA_FMT__AUD_AAC,
    MEDIA_FMT__AUD_MP3,
    MEDIA_FMT__AUD_MIDI,
    MEDIA_FMT__AUD_WAV,
    MEDIA_FMT__AUD_ASF,
    MEDIA_FMT__AUD_WMA,
    MEDIA_FMT__AUD_RA,
    MEDIA_FMT__AUD_RAM,
    MEDIA_FMT__AUD_APE,
    MEDIA_FMT__AUD_M4A,
    MEDIA_FMT__AUD_END = MEDIA_FMT__AUD_M4A,
    MEDIA_FMT__VDO_BEGIN,
    MEDIA_FMT__VDO_3GP = MEDIA_FMT__VDO_BEGIN,
    MEDIA_FMT__VDO_MP4,
    MEDIA_FMT__VDO_RM,
    MEDIA_FMT__VDO_RMVB,
    MEDIA_FMT__VDO_AVI,
    MEDIA_FMT__VDO_FLV,
    MEDIA_FMT__VDO_PS,
    MEDIA_FMT__VDO_MFS,
    MEDIA_FMT__VDO_MPG,
    MEDIA_FMT__VDO_VOB,
    MEDIA_FMT__VDO_DAT,
    MEDIA_FMT__VDO_TS,
    MEDIA_FMT__VDO_DIVX,
    MEDIA_FMT__VDO_MOV,
    MEDIA_FMT__VDO_KMV,
    MEDIA_FMT__VDO_MKV,
    MEDIA_FMT__VDO_END = MEDIA_FMT__VDO_MKV,
    MEDIA_FMT__NUM
} Media_Format_e;

typedef enum Media_FormatGroup_e_
{
    MEDIA_FMT_GROUP__AUD_RECORD,
    MEDIA_FMT_GROUP__AUD_PLAYBACK,
    MEDIA_FMT_GROUP__VDO_RECORD,
    MEDIA_FMT_GROUP__VDO_PLAYBACK,
    MEDIA_FMT_GROUP__NUM
} Media_FormatGroup_e;

typedef enum
{
    MEDIA_CONCURRENT_SECTION_BLUETOOTH_POWERON = 0,           /* Bluetooth Power On */
    MEDIA_CONCURRENT_SECTION_BLUETOOTH_OBJECTPUSHPROFILE,     /* Bluetooth Object Push Profile (OPP) */
    MEDIA_CONCURRENT_SECTION_VIDEO_PLAYBACK,                  /* Video Playback */
    MEDIA_CONCURRENT_SECTION_VIDEO_RECORDING,                 /* Video Recording */
    MEDIA_CONCURRENT_SECTION_IMAGE_CAPTURE,                   /* Image Capture */
    MEDIA_CONCURRENT_SECTION_GAME_EMU,                        /* Game */
    MEDIA_CONCURRENT_SECTION_CAMERA_PREVIEW,                  /* Camera Preview */
    /* */
    MEDIA_CONCURRENT_SECTION_NUM
} MediaConcurrentSection_e;

typedef struct Media_CapabilityTab_t_
{
    u16 uVersion;       // major.minor 8.8
    u8 uReserved[2];
    u32 uAudRecordCap;
    u32 uAudPlaybackCap;
    u32 uVdoRecordCap;
    u32 uVdoPlaybackCap;
    u32 uEmuMaxRomSize;
    u32 uMemType;
    u32 uIsVideoA2DPSupport;
} Media_CapabilityTab_t;

typedef struct Media_AudCodecInfo_t_
{
    u32 u32SamplRate; //Sample rate, 8000, 44100, etc.
    u32 u32BitRate;
    u32 u32TotalTime;
    u32 u32filesize;
    s32 s32filesize;
    u8 *u8mem_sharebuf;
    u32 u32mem_sharebufsize;
    u8 u8input_path;
    u8 u8BitRateType;
    u8 u8Channel_info; // 1 : mono, 2 : stereo
    u8 u8datafmt;
    u8 *pu8DataAddress; //Retrieved data address (header removed)
    u32 u32Datasize;
} Media_AudCodecInfo_t;

typedef bool (*IsFormatSupport)(Media_CapabilityTab_t *pCapTab, Media_FormatGroup_e eGroup, Media_Format_e eFormat);
typedef bool (*IsPlaybackFormatSupport)(Media_CapabilityTab_t *pCapTab, Media_Format_e eFormat);
typedef bool (*IsVdoCodecSupport)(Media_CapabilityTab_t *pCapTab, Media_VdoCodec_e eVdoCodec);
typedef bool (*IsAudCodecSupport)(Media_CapabilityTab_t *pCapTab, Media_AudCodec_e eAudCodec);
typedef bool (*IsVdoEncFpsSuppport)(Media_CapabilityTab_t *pCapTab, Media_VdoEncodeFps_e eVdoEncFps);
typedef bool (*IsVdoEncResSupport)(Media_CapabilityTab_t *pCapTab, Media_VdoCodec_e eVdoCodec, Media_VdoEncodeRes_e eVdoEncRes);
typedef u32 (*EmuRomSize)(Media_CapabilityTab_t *pCapTab);

typedef struct Media_CapabilityItf_t_
{
    IsFormatSupport FormatSupport;
    IsPlaybackFormatSupport PlaybackFormatSupport;
    IsVdoCodecSupport VdoCodecSupport;
    IsAudCodecSupport AudCodecSupport;
    IsVdoEncFpsSuppport VdoEncFpsSupport;
    IsVdoEncResSupport VdoEncResSupport;
    EmuRomSize EmuMaxRomSize;
} Media_CapabilityItf_t;

typedef struct Media_Capability_t_
{
    Media_CapabilityTab_t tCapTab;
    Media_CapabilityItf_t tCapItf;
    bool bGetMmpCap;
} Media_Capability_t;

typedef void (*Media_GetMmpCapability)(Media_CapabilityTab_t *pMmpCap);

typedef struct Media_CmnItf_t_
{
    Media_GetMmpCapability GetMmpCapability;
} Media_CmnItf_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
#endif //__MEDIACMN_H__

