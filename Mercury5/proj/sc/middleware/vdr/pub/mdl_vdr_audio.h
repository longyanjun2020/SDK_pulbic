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
///@file       mdl_vdr_audio.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_AUDIO_H__
#define __MDL_VDR_AUDIO_H__


//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

#include "mdl_vdr_common.h"


//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------

/* define the audio plug-in */
//#define MP4_REC_PLUGIN_AMRNB  1  // get audio bitstream from AMR-NB engine
#define MP4_REC_PLUGIN_MAR  1  // get audio bitstream MAR interface
//#define MP4_REC_PLUGIN_ADO_FILE  1  // get audio bitstream from file

/* define the type to inquiry information of time */
#define AUDIO_TIME_CURRENT      (1)            /* current time */
#define AUDIO_TIME_TOTAL            (2)              /* total time of recording data */

#define AUDIOUNDEFINED                              (0)
/* constant to AMR profiles and modes */
/* constant to profileSetting */
#define AUDIOPROFILE_AMR                            (1)

#define FLUSH_MODE  1
#define NORMAL_MODE 0

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

/* general usage structures */
/* structure used to set the audio encoder parameters */
typedef struct a_info_s
{
    U32 sampleRate;
    U32 bitsPerSample;          /* to describe source */
    U32 db;
    U32 avgBitrate;
    U32 maxBitrate;
    U32 rateControl;                /* constant or variable bit rate. */
    U32 profileSetting;         /* Profile to use for encoding */
    U32 levelSetting;           /* Level to use for encoding */
    U32 channelMode;        /* channel mode for encoding */
    U32 streamFormat;       /* format of bitstream */
    U32 frameSamples;       /* how many samples in one frame, codec will fill it */
    U32 bytesPerFrame;     /* bytes of compressed data, codec will fill it. ignore it if rateControl is RATECONTROL_VARIABLEBITRATE */
    U32 timeScale;              /* ticks for one second */
    U8  extradata_size;
    U8 *extradata;              /* some codecs generate extradata */
    void *pusrdata;                /* encode structure, will different with various codec */
} a_info_st, *pa_info_st;

/* encoder structures */
typedef struct aenc_s
{
    U32 state;
    //const char *name;
    CodecType_et codec_type;
    CodecID_et codec_id;

    //interface function
    S32 (*enc_open)(struct aenc_s *inst, encdata_st *pin, encdata_st *pout, a_info_st *psetting);
    S32 (*enc_start)(struct aenc_s *inst);
    S32 (*enc_pause)(struct aenc_s *inst);
    S32 (*enc_encode)(struct aenc_s *inst, av_packet_st *pencoded, int mode);
    S32 (*enc_resume)(struct aenc_s *inst);
    S32 (*enc_stop)(struct aenc_s *inst);
    S32 (*enc_close)(struct aenc_s *inst);

#if 0 // Modify
    //thread variables
    cyg_handle_t enc_thread_hdl; /* encoder thread handle */
    cyg_thread enc_thread_obj; /* encoder thread object */

    //state control flag
    cyg_sem_t start_sem; /* start semaphore */
    cyg_sem_t stop_sem; /* stop semaphore */
#endif

    U32 enc_frms;        /* encoded video/audio frames number */
    U32 totaltime;          /* summarize time of all frames */
    U32 totaltime_pause_duration;  /* summarize time of all frames, for pause duration */
    U32 totalsize;          /* summarize size of all frames */

    /*  this points to the data source */
    encdata_st enc_source;

    /*  this points to the destination */
    encdata_st enc_dest;

    a_info_st  enc_info; /* audio encode structure, will different with various codec */
    void (*raw_data_cb)(void* buf, int size);       /* inform someone there are raw data ready in VDR, used for VT recording now */
} aenc_st, *paenc_st;


//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------

S32 init_audio_plugin(aenc_st *pInst, av_info_st *pav_info);

#endif // __MDL_VDR_AUDIO_H__


