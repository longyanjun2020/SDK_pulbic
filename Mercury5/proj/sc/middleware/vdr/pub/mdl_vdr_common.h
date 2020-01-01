////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_common.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_COMMON_H__
#define __MDL_VDR_COMMON_H__


//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

//#include "mm_types.h"
#include "vm_types.ht"
#if 0 // Put back
#include "Rbuffer.h"
#include "mmp_Capability.h"
#endif


//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------

/* use M4VE IP always */
#if defined(MONTAGE_APP_M4VE_DRIVER)
#define FIRE_THE_M4VE_IP
#define M4VE_PERFORM_LVL_MAX PERFORM_LVL_12
#endif


/* PCM releated macro defines */
/* The PCM size of one channel in IIS bufeer */
#define DATAINPUTCHANNELMONO             1
#define DATAINPUTCHANNELSTEREO         2

/* constants to bitsPerSample */
#define PCMSAMPLEFORMAT_8          0x0008       /* 8 bits sample */
#define PCMSAMPLEFORMAT_16        0x0010        /* 16 bits sample */
/* constants to containerMode */
#define PCMJUSTIFIEDLEFT                (1)     /* data is left-justified in the container */
/* constants to endianness */
#define PCM_BIGENDIAN                       (1)
#define PCM_LITTLEENDIAN                (2)

/* encdata related macro defines */
/* define data locator */
#define DATALOCATORNULL                         (1)
#define DATALOCATORSERIAL                       (2) /* serial memory */
#define DATALOCATORRING                         (3) /* ring buffer */

/* define data format */
#define DATAFORMATIIS                             (0)
#define DATAFORMATFM                            (1)
#define DATAFORMATSPDIF                         (2)
#define DATAFORMATSENSOR                    (4)

/* define Sampling rate */
#define SAMPLINGRATE8000                    (8000)
#define SAMPLINGRATE11025                   (11025)
#define SAMPLINGRATE12000                   (12000)
#define SAMPLINGRATE16000                   (16000)
#define SAMPLINGRATE22025                   (22025)
#define SAMPLINGRATE24000                   (24000)
#define SAMPLINGRATE32000                   (32000)
#define SAMPLINGRATE44100                   (44100)
#define SAMPLINGRATE48000                   (48000)

/* constant to rateControl */
#define RATECONTROL_CONSTANTBITRATE     (1)
#define RATECONTROL_VARIABLEBITRATE     (2)

/* constant to frame type */
#define FRAME_TYPE_UNKNOWN  0
#define FRAME_TYPE_I    1   // Intra
#define FRAME_TYPE_P    2   // Predicted
#define FRAME_TYPE_B    3   // Bi-dir Predicted

/* constant to packet status */
#define PACKET_START    0
#define PACKET_CONTINUE     1
#define PACKET_END          2
#define PACKET_ERROR    3
#define PACKET_GETBITS      4


//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

typedef enum
{
    COND_TYPE_UNKNOWN = -1,
    COND_TYPE_START,
    COND_TYPE_PAUSE,
    COND_TYPE_STOP
}CondType_e;

typedef enum
{
    CLOCK_MASTER_MODE_RESET  =   0,
    CLOCK_MASTER_MODE_STOP,
    CLOCK_MASTER_MODE_UPDATE,
    CLOCK_MASTER_MODE_GET,
    CLOCK_MASTER_MODE_STAMP_START,     // start time stamp
    CLOCK_MASTER_MODE_RESUME,
    CLOCK_MASTER_MODE_AV_SYNC
}ClockMasterMode_e;


typedef enum CodecID_e
{
    /* video */
    CODEC_NONE = 0x0000,
    CODEC_H263 = 0x0001,
    CODEC_MPEG4 = 0x0002,

    /* audio */
    CODEC_AMR_NB = 0x1000,
    CODEC_AMR_WB = 0x1001,
    CODEC_WAVIMAADPCM4BIT = 0x1002,
    CODEC_WAVIMAADPCM3BIT = 0x1003,
    CODEC_WAVIMSADPCM4BIT = 0x1004,
    CODEC_AAC = 0x1005,
    CODEC_MP3 = 0x1006
} CodecID_et ;

typedef enum CodecType_e
{
    CODEC_TYPE_NONE = -1,
    CODEC_TYPE_VDO,
    CODEC_TYPE_ADO,
    CODEC_TYPE_VT    
}CodecType_et;

typedef enum MediaFormat_e
{
    FORMAT_NONE  =  -1,
    FORMAT_3GP,
    FORMAT_MP4,
    FORMAT_VT    
}MediaFormat_et;


/* profile and level definition */
typedef enum AVProfile_e {
    /* based on ITU-T Recommendation H.263 */
    ProfileH263Baseline = 0x0,

    /* based on ISO-IEC 14496-2 FLC table for profile_and_level_indication */
    ProfileMP4Simple = 0x0,
    ProfileMP4SimpleScalable = 0x01,
    ProfileMP4Core  = 0x02,
    ProfileMP4Main  = 0x03,

    /* based on ISO-IEC 14496-3 Audio Profiles definition */
    ProfileAACMain = 0x0,
    ProfileAACScalable    = 0x01,
    ProfileAACSpeech   = 0x02,
    ProfileAACSynthesis = 0x03,

    ProfileUnknown = 0xFF
} AVProfile_et;

typedef enum AVLevel_e {
    /* based on ITU-T Recommendation H.263 */
    LevelH263_10 = 10,
    LevelH263_20 = 20,

    /* based on ISO-IEC 14496-2 FLC table for profile_and_level_indication */
    LevelMP4_1      = 0x1,
    LevelMP4_2      = 0x2,
    LevelMP4_3      = 0x3,
    LevelMP4_4      = 0x4,

    /* based on ISO-IEC 14496-3 Levels within the profiles */
    LevelAAC_1      = 0x1,
    LevelAAC_2      = 0x2,
    LevelAAC_3      = 0x3,
    LevelAAC_4      = 0x4,

    LevelUnknown = 0xFF
} AVLevel_et;

typedef enum RecordState
{
    RECORDSTATE_OPEN,
    RECORDSTATE_STOPPED,
    RECORDSTATE_PAUSED,
    RECORDSTATE_RECORDING,
    RECORDSTATE_CLOSE,
}RecordState_et;

typedef enum CodecIP
{
    CODEC_IP_JPE,
    CODEC_IP_M4VE
}CodecIP_et;

// define how to get source data for encoder
typedef enum VideoSrcStyle
{
    VIDEO_SRC_ROWSCL,
    VIDEO_SRC_DISPLAY,
    VIDEO_SRC_FRAMESCL,
}VideoSrcStyle_et;

typedef struct
{
    U32 V_totaltime;          /* summarize time of all frames */
    U32 A_totaltime;          /* summarize time of all frames */
    U32* pduration_V_A;       /* before resume, V-totaltime - A-totaltime */
} av_sync_totaltime, *pav_sync_totaltime;

typedef struct
{
    U32* pframeduration;          /* frame duration */
    U32 frametime_after;          /* frame(n+1) time */
    U32 frametime_before;         /* frame(n)   time */
    U32* pduration_V_A;           /* before resume, V-totaltime - A-totaltime */
} av_sync_frametime, *pav_sync_frametime;

typedef struct av_info_s
{
    U16 *prec_name;
    U32 video_codec;
    U32 audio_codec;
    U32 media_fmt;
    U32 width;
    U32 height;
    U32 frame_rate;
    U16 quant;
    U8 video_ip;
    U8 reserved[1];
} av_info_st, *pav_info_st;

#if 0 // put back
/* operation ring buffer */
typedef     void fnRecMemCreate(struct ringbuffer *rbuf, void *data, uint32_t len);
typedef     void fnRecMemClose(struct ringbuffer *rbuf);
typedef     void fnRecMemDetroy(struct ringbuffer *rbuf);
typedef     uint8_t *fnRecMemRead(struct ringbuffer *rbuf, uint8_t *buf, uint32_t len, uint32_t *actuallen);
typedef     uint8_t *fnRecMemWrite(struct ringbuffer *rbuf, const uint8_t *buf, uint32_t len, uint32_t *actuallen);
typedef     int32_t fnRecMemInfoQuiry(struct ringbuffer *rbuf);

typedef struct ringbufop_s
{
    void *pdata;

    fnRecMemCreate      *fp_RecMemCreate;
    fnRecMemClose       *fp_RecMemClose;
    fnRecMemDetroy      *fp_RecMemDestroy;
    fnRecMemRead        *fp_RecMemRead;         /* get the start address to read the data with requested size */
    fnRecMemWrite       *fp_RecMemWrite;        /* get the start address to write data with requested size */
    fnRecMemInfoQuiry   *fp_RecMemFree;     /* the maximal free space to be written */
    fnRecMemInfoQuiry   *fp_RecMemAvail;    /* the maximal available data to be read */
    fnRecMemInfoQuiry   *fp_RecMemSize;     /* the total size of the ring buffer */
}ringbufop_st, *pringbufop_st;
#endif

/* output device structures */
typedef struct stbasic
{
    U32     u32Type;            /* format type or data type */
    void    *pdata;
}stbasic_st, *pdtbasic_st;

/* the data structure defines the specified data locator structure. */
/* This points to direct memory address */
typedef struct directbuf_s
{
    U32     u32Base;
    U32     u32Size;
}directbuf_st, *pdirectbuf_st;

typedef struct dtlocatorbuf
{
    U32 locatorType;            /* format type and always DATALOCATORRING */
    directbuf_st  *directbuf;
}dtlocatorbuf_st, *pdtlocatorbuf_st;

#if 0 // put back
typedef struct dtlocatorrrb
{
    U32 locatorType;            /* format type and always DATALOCATORRING */
    ringbufop_st *ringbuf;
}dtlocatorrbop_st, *pdtlocatorrbop_st;
#endif

typedef struct dtformatpcm {
    U32 formatType;             /* format type and always DATAFORMATPCM*/
    U32 numberChannels;     /* number of channel of the data */
    U32 samplesPerSec;      /* audio sample rate of data */
    U32 bitsPerSample;      /* actual data bit in a sample */
    U32 containerSize;      /* container data size for PCM in bits, for example, 20 bit data in 24 bit container */
    U32 containerMode;      /* data alignment in container */
    U32 endianness;         /* endianness of audio data */
} dtformatpcm_st, *pdtformatpcm_st;

typedef struct dtformatsensor {
    U32 formatType;             /* format type and always DATAFORMATSENSOR*/
    U32 framesPerSec;       /* number of fps 16.16*/
    VideoSrcStyle_et eSrcStyle;                  /* where is data from */
} dtformatsensor_st, *pdtformatsensor_st;


typedef struct encdata
{
    void *pLocator;     /* the first U32 is reserved to define style. See DATALOCATOR */
    void *pFormat;     /* the first U32 is reserved to define type. See DATAFORMAT */
}encdata_st, *pencdata_st;

/* packet functions */
typedef struct av_packet{
    U32 pts;                        /* presentation timestamp in system time_base units */
    U32 dts;                        /* decompression timestamp in system time_base units. */
    U8  *data;                      /* the address to the audio/video data */
    U32 size;                       /* the size of the data */
    U32 stream_index;       /* index to the stream */
    U32 duration;               /* duration od this packet in system time_base units */
    U32 type;                      /* information about the packet */
    U32 status;                   /* the last packet ?*/
}av_packet_st, *pav_packet_st;



//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------


#endif //_MDL_VDR_COMMON_H_

