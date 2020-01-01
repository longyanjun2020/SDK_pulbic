///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file  MMP_capability.h
/// @author MStar Semiconductor Inc.
/// @brief  MMP Capabilityvariable definition header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MEDIAMMPCAPABILITY_H
#define _MEDIAMMPCAPABILITY_H

#include "PlatformDefines.h"

//-------------------------------------------------------------------------------------------------
// Multimedia capability
//-------------------------------------------------------------------------------------------------
typedef enum _AUDIO_RECORD_SUPPORTTYPE
{
    MAR_CODEC_AUDREC_AMR_NB = 0x0001, //.amr
    MAR_CODEC_AUDREC_AMR_WB = 0x0002, //.awb
    MAR_CODEC_AUDREC_IMAADPCM3BIT = 0x0004, //.wave IMAADPCM3BIT
    MAR_CODEC_AUDREC_IMAADPCM4BIT = 0x0008, //.wave IMAADPCM4BIT
    MAR_CODEC_AUDREC_MSADPCM4BIT = 0x0010, //.wave MSADPCM4BI
} AUDIO_RECORD_SUPPORTTYPE;

typedef enum _AUDIO_PLAYBACK_SUPPORTTYPE
{
    MAP_CODEC_AUDIO_AMR_NB = 0x0001, //.amr
    MAP_CODEC_AUDIO_AMR_WB = 0x0002, //.awb
    MAP_CODEC_AUDIO_AAC = 0x0004, //.aac
    MAP_CODEC_AUDIO_MP3 = 0x0008, //.mp3
    MAP_CODEC_AUDIO_MIDI = 0x0010, //.mid
    MAP_CODEC_AUDIO_WAV = 0x0020, //.wav
    MAP_CODEC_AUDIO_WMA = 0x0040, //.wma
    MAP_CODEC_AUDIO_RA = 0x0080, //.ra .ram
    MAP_CODEC_AUDIO_APE = 0x0100, //.ape
} AUDIO_PLAYBACK_SUPPORTTYPE;

typedef enum _VIDEO_RECORD_SUPPORTTYPE
{
    /* bits 0~3: available file format */
    GVR_FILE_FORMAT_3GP = 0x0001,
    GVR_FILE_FORMAT_MP4 = 0x0002,
    /* bits 4~7: available visual format */
    GVR_CODEC_VIDEO_H263 = 0x0010,
    GVR_CODEC_VIDEO_MPEG4 = 0x0020,
    /* bits 8~11: available audio format */
    GVR_CODEC_AUDIO_AMR_NB = 0x0100,
    GVR_CODEC_AUDIO_AMR_WB = 0x0200,
    GVR_CODEC_AUDIO_AAC = 0x0400,
    GVR_CODEC_AUDIO_WAV = 0x0800,
    /* bits 12~13: maximal frame rate */
    GVR_FPS_MAX_15 = 0x1000,
    GVR_FPS_MAX_30 = 0x2000,
     /* bits 14~15: available ratio */
    GVR_IAR_4_3 = 0x4000,
    GVR_IAR_16_9 = 0x8000,
    /* bits 16~23: available resolution */
    GVR_RESOLUTION_128_96 = 0x00010000, // 128x96, SQCIF
    GVR_RESOLUTION_176_144 = 0x00020000, // 176x144, QCIF
    GVR_RESOLUTION_320_240 = 0x00040000, // 320x240, QVGA
    GVR_RESOLUTION_352_288 = 0x00080000, // 352x288, CIF
    GVR_RESOLUTION_640_480 = 0x00100000, // 640x480, VGA
    GVR_RESOLUTION_704_576 = 0x00200000, // 704x576, 4CIF
    GVR_RESOLUTION_720_480 = 0x00400000, // 720x480, NTSC
    GVR_RESOLUTION_720_576 = 0x00800000, // 720x576, PAL
    /* bits 24~31: reserved */
} VIDEO_RECORDER_SUPPORTTYPE;

typedef enum _VIDEO_PLAYBACK_SUPPORTTYPE
{
    MMP_VIDEO_FILE_FORMAT_3GP = 0x0001, //.3GP
    MMP_VIDEO_FILE_FORMAT_MP4 = 0x0002, //.MP4
    MMP_VIDEO_FILE_FORMAT_RM = 0x0004,  //.RM
    MMP_VIDEO_FILE_FORMAT_RMVB = 0x0008, //.RMVB

    MMP_VIDEO_FILE_FORMAT_AVI = 0x0010, //.AVI
    MMP_VIDEO_FILE_FORMAT_FLV = 0x0020, //.FLV
    MMP_VIDEO_FILE_FORMAT_PS = 0x0040, //.PS
    MMP_VIDEO_FILE_FORMAT_MPG = 0x0080, //.MPG .MPEG

    MMP_VIDEO_FILE_FORMAT_VOB = 0x0100, //.VOB
    MMP_VIDEO_FILE_FORMAT_DAT = 0x0200, //.DAT
    MMP_VIDEO_FILE_FORMAT_TS = 0x0400, //.TS
    MMP_VIDEO_FILE_FORMAT_DIVX  = 0x0800, //.DIVX
    MMP_VIDEO_FILE_FORMAT_MOV  = 0x1000, //.MOV
} VIDEO_PLAYBACK_SUPPORTTYPE;

typedef struct _MultimediaCapability
{
    u16 uVersion; // major.minor 8.8
    u8 uReserved[2];
    u32 uAudioRecordCapability;
    u32 uAudioPlaybackCapability;
    u32 uVideoRecordCapability;
    u32 uVideoPlaybackCapability;
    u32 uEmuMaxRomSize;
    u32 uMemType;
    u32 uIsVideoA2DPSupport;
} MultimediaCapability;

u8 Media_MmpCapabilityFun(u8 *pStrucAddr, u32 uStrucLen);

#endif // _MEDIAMMPCAPABILITY_H
