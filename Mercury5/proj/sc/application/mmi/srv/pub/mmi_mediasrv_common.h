/**
* @file mmi_mediasrv_common.h
*
*/
#ifndef __MMI_MEDIASRV_COMMON_H__
#define __MMI_MEDIASRV_COMMON_H__

#include "mmi_log.h"
#include "mmi_mae_mime_type.h"

#define SPECTRUM_MIN_INTERVAL 40
#define SPECTRUM_MAX_INTERVAL 1000
#define SPECTRUM_DATA_NUMBER 16

typedef enum
{
    MEDIASRV_VDO_CODEC__BEGIN,
    MEDIASRV_VDO_CODEC__H263 = MEDIASRV_VDO_CODEC__BEGIN,
    MEDIASRV_VDO_CODEC__MP4,
    MEDIASRV_VDO_CODEC__MP2,
    MEDIASRV_VDO_CODEC__AVC,                                      // MPEG4 Part 10 Advanced Video Coding, also known as H.264 video format
    MEDIASRV_VDO_CODEC__VC1,                                      // Windows Media Codec video format
    MEDIASRV_VDO_CODEC__RVC,                                      // Real Video Codec format
    MEDIASRV_VDO_CODEC__MJPEG,                                    // Motion JPEG
    MEDIASRV_VDO_CODEC__KMV,                                      // King Movie format
    MEDIASRV_VDO_CODEC__END = MEDIASRV_VDO_CODEC__KMV,
    MEDIASRV_VDO_CODEC__NUM,
    MEDIASRV_VDO_CODEC__UNSUPPORTED
} MediaSrvVdoCodec_e;   //Sync to Media_VdoCodec_e

typedef enum
{
    MEDIASRV_AUD_CODEC__BEGIN,
    MEDIASRV_AUD_CODEC__AMR_NB = MEDIASRV_AUD_CODEC__BEGIN,
    MEDIASRV_AUD_CODEC__AMR_WB,
    MEDIASRV_AUD_CODEC__AAC,
    MEDIASRV_AUD_CODEC__MP3,
    MEDIASRV_AUD_CODEC__MP3_8K,
    MEDIASRV_AUD_CODEC__WAV,
    MEDIASRV_AUD_CODEC__PCM,
    MEDIASRV_AUD_CODEC__END = MEDIASRV_AUD_CODEC__PCM,
    MEDIASRV_AUD_CODEC__NUM,
    MEDIASRV_AUD_CODEC__UNSUPPORT
} MediaSrvAudCodec_e;   //Sync to Media_AudCodec_e

typedef enum
{
    MEDIASRV_VDO_ENC_FPS__15,
    MEDIASRV_VDO_ENC_FPS__30,
    MEDIASRV_VDO_ENC_FPS__NUM
} MediaSrvVdoEncodeFps_e;   //Sync to Media_VdoEncodeFps_e

typedef enum
{
    MEDIASRV_VDO_ENC_RES__4CIF,        /*704x576*/
    MEDIASRV_VDO_ENC_RES__CIF,         /*352x288*/
    MEDIASRV_VDO_ENC_RES__QCIF,        /*176x144*/
    MEDIASRV_VDO_ENC_RES__SUB_QCIF,    /*128x96*/
    MEDIASRV_VDO_ENC_RES__VGA,         /*640x480*/
    MEDIASRV_VDO_ENC_RES__QVGA,        /*320x240*/
    MEDIASRV_VDO_ENC_RES__WQVGA,       /*400x240*/
    MEDIASRV_VDO_ENC_RES__HVGA,        /*480x320*/
    MEDIASRV_VDO_ENC_RES__DVD_PAL,     /*720x480*/
    MEDIASRV_VDO_ENC_RES__DVD_NTSC,    /*720x480*/
    MEDIASRV_VDO_ENC_RES__NUM
} MediaSrvVdoEncodeRes_e;   //Sync to Media_VdoEncodeRes_e


typedef enum
{
    MEDIASRV_ERR__OK
   ,MEDIASRV_ERR__FAIL
   ,MEDIASRV_ERR__DENY
   ,MEDIASRV_ERR__FORMAT_NOT_SUPPORT
   ,MEDIASRV_ERR__NO_MEMORY
   ,MEDIASRV_ERR__FILE_DATA_FAIL
   ,MEDIASRV_ERR__SDCARD_NOT_DETECTED
   ,MEDIASRV_ERR__FORMAT_NOT_MATCH
   ,MEDIASRV_ERR__ABORT
   ,MEDIASRV_ERR__WAIT_APPSTOP_DROP
   ,MEDIASRV_ERR__VERSION_NOT_MATCH
   ,MEDIASRV_ERR__NO_FILE
   ,MEDIASRV_ERR__UNKNOWN
} MediaSrvErrCode_e;

typedef enum
{
    MEDIASRV_MIME__START = 0
   ,MEDIASRV_MIME__UNKNOWN = MEDIASRV_MIME__START
   ,MEDIASRV_MIME__BMP
   ,MEDIASRV_MIME__GIF
   ,MEDIASRV_MIME__PNG
   ,MEDIASRV_MIME__JPG
   ,MEDIASRV_MIME__MP1
   ,MEDIASRV_MIME__MP2
   ,MEDIASRV_MIME__MP3
   ,MEDIASRV_MIME__AAC
   ,MEDIASRV_MIME__AMR
   ,MEDIASRV_MIME__WAV
   ,MEDIASRV_MIME__MID
   ,MEDIASRV_MIME__IMY
   ,MEDIASRV_MIME__ASF
   ,MEDIASRV_MIME__WMA
   ,MEDIASRV_MIME__WMV
   ,MEDIASRV_MIME__MP4
   ,MEDIASRV_MIME__3GP
   ,MEDIASRV_MIME__MIDI_EVENT
   ,MEDIASRV_MIME__AWB
   ,MEDIASRV_MIME__RAM
   ,MEDIASRV_MIME__PCM
   ,MEDIASRV_MIME__M4A
   ,MEDIASRV_MIME__RM
   ,MEDIASRV_MIME__RMVB
   ,MEDIASRV_MIME__AVI
   ,MEDIASRV_MIME__MFS
   ,MEDIASRV_MIME__TS
   ,MEDIASRV_MIME__FLV
   ,MEDIASRV_MIME__MPG
   ,MEDIASRV_MIME__MPEG
   ,MEDIASRV_MIME__DIVX
   ,MEDIASRV_MIME__KMV
   ,MEDIASRV_MIME__NUM
} MediaSrvMimeType_e;

typedef enum
{
    MEDIASRV_FILE_FMT__WAVE
   ,MEDIASRV_FILE_FMT__MIDI
   ,MEDIASRV_FILE_FMT__IMY
   ,MEDIASRV_FILE_FMT__MP3
   ,MEDIASRV_FILE_FMT__MP2
   ,MEDIASRV_FILE_FMT__MP1
   ,MEDIASRV_FILE_FMT__AAC
   ,MEDIASRV_FILE_FMT__AMR
   ,MEDIASRV_FILE_FMT__AWB
   ,MEDIASRV_FILE_FMT__RAM
   ,MEDIASRV_FILE_FMT__ASF
   ,MEDIASRV_FILE_FMT__WMA
   ,MEDIASRV_FILE_FMT__WMV
   ,MEDIASRV_FILE_FMT__MP4
   ,MEDIASRV_FILE_FMT__3GP
   ,MEDIASRV_FILE_FMT__WAVE_EXT
   ,MEDIASRV_FILE_FMT__MIDI_EVENT
   ,MEDIASRV_FILE_FMT__PCM
   ,MEDIASRV_FILE_FMT__RM
   ,MEDIASRV_FILE_FMT__AVI
   ,MEDIASRV_FILE_FMT__MFS
   ,MEDIASRV_FILE_FMT__TS
   //below formats are adding for capability dection
   ,MEDIASRV_FILE_FMT__DIVX
   ,MEDIASRV_FILE_FMT__RA
   ,MEDIASRV_FILE_FMT__APE
   ,MEDIASRV_FILE_FMT__M4A
   ,MEDIASRV_FILE_FMT__FLV
   ,MEDIASRV_FILE_FMT__PS
   ,MEDIASRV_FILE_FMT__MPG
   ,MEDIASRV_FILE_FMT__VOB
   ,MEDIASRV_FILE_FMT__DAT
   ,MEDIASRV_FILE_FMT__RMVB
   ,MEDIASRV_FILE_FMT__MOV
   ,MEDIASRV_FILE_FMT__KMV
   ,MEDIASRV_FILE_FMT__QKMV
   ,MEDIASRV_FILE_FMT__HKMV
 #if defined(__MMI_KING_MOVIE_3D__)
   ,MEDIASRV_FILE_FMT__3DKMV
 #endif
   ,MEDIASRV_FILE_FMT__MKV
   ,MEDIASRV_FILE_FMT__UNKNOWN_FORMAT
} MediaSrvFileFormat_e;

typedef enum MediaSrvRecPath_e_
{
	MEDIASRV_REC_PATH__DIR		  /**< Directory */
   ,MEDIASRV_REC_PATH__PREFIX	  /**< Prefix */
   ,MEDIASRV_REC_PATH__ABSOLUTE	  /**< Absolute filename */
   ,MEDIASRV_REC_PATH__NUM
} MediaSrvRecPath_e;

typedef enum MediaSrvInterruptStatus_e_
{
   MEDIASRV_INTERRUPT_STATUS__SUSPEND
   ,MEDIASRV_INTERRUPT_STATUS__RESUME
} MediaSrvInterruptStatus_e;

typedef enum MediaSrvAccessoryStatus_e_
{
    MEDIASRV_ACS_STATUS__PCLINK_ACTIVATED
} MediaSrvAccessoryStatus_e;

typedef enum MediaSrvMediaType_e_
{
    MEDIASRV_TYPE__AUDIO
   ,MEDIASRV_TYPE__VIDEO
   ,MEDIASRV_TYPE__VIDEO_REC
   ,MEDIASRV_TYPE__AUDIO_RAW
   ,MEDIASRV_TYPE__AUDIO_REC
   ,MEDIASRV_TYPE__AUDIO_PCMREC
   ,MEDIASRV_TYPE__UNKNOWN
} MediaSrvMediaType_e;

typedef enum
{
    MEDIASRV_AREA__TAIWAN
   ,MEDIASRV_AREA__CHINA
   ,MEDIASRV_AREA__THAILAND
   ,MEDIASRV_AREA__UNKNOWN
} MediaSrvArea_e;

typedef enum MediaSrvSeekMode_e_
{
    MEDIASRV_SEEK__FAST
   ,MEDIASRV_SEEK__PRECISE
} MediaSrvSeekMode_e;

typedef enum MediaSrvAngle_e_
{
    MEDIASRV_ANGLE__0 = 0
   ,MEDIASRV_ANGLE__90
   ,MEDIASRV_ANGLE__180
   ,MEDIASRV_ANGLE__270
   ,MEDIASRV_ANGLE__NUM
} MediaSrvAngle_e;

typedef enum MediaSrvEmuEngineType_e_
{
    MEDIASRV_EMU_ENGINE_TYPE__EMU_8BIT,
    MEDIASRV_EMU_ENGINE_TYPE__EMU_16BIT,
    MEDIASRV_EMU_ENGINE_TYPE__EMU_16BIT_MINI,
    MEDIASRV_EMU_ENGINE_TYPE__NUM,
    MEDIASRV_EMU_ENGINE_TYPE__UNKNOWN
} MediaSrvEmuEngineType_e;

typedef enum MediaSrvEmuRomType_e_
{
    MEDIASRV_EMU_ROM_TYPE__EMU_8BIT,
    MEDIASRV_EMU_ROM_TYPE__EMU_16BIT,
    MEDIASRV_EMU_ROM_TYPE__NUM,
    MEDIASRV_EMU_ROM_TYPE__UNKNOWN
} MediaSrvEmuRomType_e;

/*Every 40 bytes spectrum info from M3 contains:
  8 bytes PTS data and 32 bytes spectrum data*/
typedef struct MediaSrvSpectrumInfo_t_
{
    s64 nPlayingTime;
    s16 aSpectrumData[SPECTRUM_DATA_NUMBER];
} MediaSrvSpectrumInfo_t;

typedef void (*MediaSrvCb)(void *pThis, MediaSrvErrCode_e nErrorCode, void *pInfoData);
typedef void (*MediaSrvInterruptNotifyCb)(void *pThis, u32 nCusData, MediaSrvInterruptStatus_e nStatus);
typedef void (*MediaSrvAccessoryNotifyCb)(void *pThis, u32 nCusData, MediaSrvAccessoryStatus_e nStatus);
typedef void (*MediaSrvSpectrumCb)(void *pThis, u32 nCusData, MediaSrvSpectrumInfo_t *pSpectrumInfo);

bool MediaSrvIsFormatSupport(MediaSrvMediaType_e eType, MediaSrvFileFormat_e eFormat, bool *pSupport);
bool MediaSrvIsPlaybackFormatSupport(MediaSrvFileFormat_e eFormat, bool *pSupport);
bool MediaSrvEmuMaxRomSize(u32 *pSize);
bool MediaSrvIsVdoCodecSupport(MediaSrvVdoCodec_e eVdoCodec, bool *pSupport);
bool MediaSrvIsAudCodecSupport(MediaSrvAudCodec_e eAudCodec, bool *pSupport);
bool MediaSrvIsVdoEncFpsSupport(MediaSrvVdoEncodeFps_e eVdoEncFps, bool *pSupport);
bool MediaSrvIsVdoEncResSupport(MediaSrvVdoCodec_e eVdoCodec, MediaSrvVdoEncodeRes_e eVdoEncRes, bool *pSupport);
bool MediaSrvGetCamRecordMemorySize(u32 *pVdoMemoryInfo);

#ifdef __MMI_STEREO_VIDEO__
bool MediaSrvVdoIsStereoEffectSupport(bool *pSupport);
#endif
#ifdef __MMI_STEREO_IMAGE__
bool MediaSrvImgIsStereoEffectSupport(bool *pSupport);
#endif

u32 MediaSrvGetFreeSpaceInSecond(MediaSrvAudCodec_e eAudCodec, const MAE_WChar *pUrl);
MediaSrvMimeType_e MediaSrvGetSrvMimeByMMIMimeType(MAE_MIME_et eMimeType);
bool MediaSrvGetEmuMaxRomSize(MediaSrvEmuEngineType_e eEngineType, u32 *pMaxRomSize);
bool MediaSrvIsEmuEngineSupport(MediaSrvEmuEngineType_e eEngineType, bool *pSupport);
bool MediaSrvGetEmuEngineName(MediaSrvEmuEngineType_e eEngineType, const MAE_WChar **ppEmuEngineName, u32 *pEmuEngineNameLen);

#endif /* __MMI_MEDIASRV_COMMON_H__ */

