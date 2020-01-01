////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef MVC_DEMUXER_H
#define MVC_DEMUXER_H

#include <stdint.h>
#include "avp_ms_input.h"
#include "avp_mvc_info.h"

typedef enum mvc_errno_e {
    MVC_OK,
    MVC_NoInputSignal,
    MVC_TryAgain,
    MVC_InvalidParam,
    MVC_NotEnoughMemory,
    MVC_OpenFailed,
    MVC_SeekFailed,
    MVC_ProgramChanged,
    MVC_EndOfStream,
    MVC_AVFrameEmpty
} mvc_errno_et;

typedef enum mvc_drop_level_e {
    MVC_DROP_NONE,
    MVC_DROP_1_3,
    MVC_DROP_1_2,
    MVC_DROP_2_3, //drop all B
    MVC_DROP_3_4,
    MVC_DROP_FULL,
} mvc_drop_level_et;

typedef enum MVCDemuxType_e {
    CLIP_DEMUX_TYPE_UNKNOWN,
    CLIP_DEMUX_TYPE_AMRNB,
    CLIP_DEMUX_TYPE_ASF,
    CLIP_DEMUX_TYPE_AVI,
    CLIP_DEMUX_TYPE_CMMB,
    CLIP_DEMUX_TYPE_FLV,
    CLIP_DEMUX_TYPE_M2PS,
    CLIP_DEMUX_TYPE_M2TS,
    CLIP_DEMUX_TYPE_MKV,
    CLIP_DEMUX_TYPE_MP3,
    CLIP_DEMUX_TYPE_RMFF,
    CLIP_DEMUX_TYPE_TINY,
    CLIP_DEMUX_TYPE_RTP,
} MVCDemuxType_et;

typedef enum MVCVideoType_e {
    CLIP_VIDEO_TYPE_ERROR = -1,
    CLIP_VIDEO_TYPE_UNKNOWN,
    CLIP_VIDEO_TYPE_MP2V,
    CLIP_VIDEO_TYPE_DIV3,
    CLIP_VIDEO_TYPE_DIVX,
    CLIP_VIDEO_TYPE_H263,
    CLIP_VIDEO_TYPE_M4V,
    CLIP_VIDEO_TYPE_MP4S,
    CLIP_VIDEO_TYPE_M4S2,
    CLIP_VIDEO_TYPE_MP41,
    CLIP_VIDEO_TYPE_MP42,
    CLIP_VIDEO_TYPE_MP43,
    CLIP_VIDEO_TYPE_WMV1,
    CLIP_VIDEO_TYPE_WMV2,
    CLIP_VIDEO_TYPE_WMV3,
    CLIP_VIDEO_TYPE_WMVA,
    CLIP_VIDEO_TYPE_AVC1,
    CLIP_VIDEO_TYPE_RVCH,
    CLIP_VIDEO_TYPE_FLV1,
    CLIP_VIDEO_TYPE_RV10,
    CLIP_VIDEO_TYPE_RV20,
    CLIP_VIDEO_TYPE_RV30,
    CLIP_VIDEO_TYPE_RV40,
    CLIP_VIDEO_TYPE_AVS1,
    CLIP_VIDEO_TYPE_MJPG,
    CLIP_VIDEO_TYPE_MSVC,
    CLIP_VIDEO_TYPE_VP60,
    CLIP_VIDEO_TYPE_VP70,
    CLIP_VIDEO_TYPE_VP80,
    CLIP_VIDEO_TYPE_I420,
} MVCVideoType;

typedef enum MVCAudioType_e {
    CLIP_AUDIO_TYPE_ERROR = -1,
    CLIP_AUDIO_TYPE_UNKNOWN,
    CLIP_AUDIO_TYPE_AAC,
    CLIP_AUDIO_TYPE_AC3,
    CLIP_AUDIO_TYPE_AMRNB,
    CLIP_AUDIO_TYPE_AMRNBIF2,
    CLIP_AUDIO_TYPE_AMRWB,
    CLIP_AUDIO_TYPE_ATRC,
    CLIP_AUDIO_TYPE_COOK,
    CLIP_AUDIO_TYPE_DRA,
    CLIP_AUDIO_TYPE_DTS,
    CLIP_AUDIO_TYPE_MP3,
    CLIP_AUDIO_TYPE_PCM,
    CLIP_AUDIO_TYPE_SIPR,
    CLIP_AUDIO_TYPE_WMA1,
    CLIP_AUDIO_TYPE_WMA2,
    CLIP_AUDIO_TYPE_WMA3,
} MVCAudioType;

typedef enum MVCSubtitleType_e {
    CLIP_SUBTITLE_TYPE_ERROR = -1,
    CLIP_SUBTITLE_TYPE_UNKNOWN,
    CLIP_SUBTITLE_TYPE_DXSB,
    CLIP_SUBTITLE_TYPE_MP4S,
} MVCSubtitleType;

typedef enum mvc_stream_type_e {
    MVC_STREAM_NONE,
    MVC_STREAM_PROG,
    MVC_STREAM_AUDIO,
    MVC_STREAM_VIDEO,
    MVC_STREAM_SUBTITLE,
    MVC_STREAM_ESG,
    MVC_STREAM_EMG,
    MVC_STREAM_CA,
    MVC_STREAM_PROG2 // hack
} mvc_stream_type_et;

typedef struct mvc_allocator_s
{
    int (* alloc)(void *ctx, mvc_stream_type_et type, void **buffer, int size);
    int (* discard)(void *ctx, mvc_stream_type_et type);
    int (* commit)(void *ctx, mvc_stream_type_et type, int size, int64_t pts);
    int (* realloc)(void *ctx, mvc_stream_type_et type, void **buffer, int size);
    int (* end_stream)(void *ctx, mvc_stream_type_et type);
} mvc_allocator_st;

typedef enum mvc_seek_direction_e {
    MVC_SEEK_FORWARD,
    MVC_SEEK_BACKWARD,
} mvc_seek_direction_et;

typedef struct mvc_dmx_func_s
{
    /* normal interface */
    int (* open_file  )(void **ctx, cb_io_st *cbio, void *buffer, int bufsize, int ringbuf_size, void *mem_ctx);
    int (* close_file )(void *ctx);
    int (* set_alloc  )(void *ctx, const mvc_allocator_st *allocator, void *cbctx);
    int (* get_info   )(void *ctx, mvc_stream_type_et type, int index, void *info);
    int (* get_data   )(void *ctx, mvc_stream_type_et *type, int *bufsize, int64_t *pts);
    int (* seek_time  )(void *ctx, int dir, int64_t *pts, int query_only);
    int (* set_track  )(void *ctx, mvc_stream_type_et type, int index);
    int (* set_drop   )(void *ctx, mvc_drop_level_et level);

    /* avframe interface */
    int  (* get_frame_info )(void *ctx, mvc_stream_type_et *type, int *bufsize, int64_t *pts, int *is_intra);
    void (* reset_avframe  )(void *ctx, mvc_stream_type_et type);
    void (* discard_avframe)(void *ctx, mvc_stream_type_et type);
    int  (* queue_avframe  )(void *ctx, int size, mvc_stream_type_et type, int64_t target_PTS);
    int  (* deliver_avframe)(void *ctx, int *len, int64_t *pts, mvc_stream_type_et type);
    int  (* peek_avframe   )(void *ctx, int *frame_size, int64_t *pts, mvc_stream_type_et type);

    /* capability */
    int min_context_size;
    int support_avframe_video;
    int support_avframe_audio;
} mvc_dmx_func_st;

typedef struct sub_packet_s
{
    uint32_t chunk_size;
    int      chunk_pos;
    int      codec_type;
    uint32_t palette[16];
} sub_packet_st;

/* factory method for demuxer construction */
const mvc_dmx_func_st *mvc_demuxer_create(MVCDemuxType_et type);

extern const mvc_dmx_func_st mvc_amrn_demuxer;
extern const mvc_dmx_func_st mvc_avif_demuxer;
extern const mvc_dmx_func_st mvc_cmmb_demuxer;
extern const mvc_dmx_func_st mvc_flvf_demuxer;
extern const mvc_dmx_func_st mvc_m2ps_demuxer;
extern const mvc_dmx_func_st mvc_m2ts_demuxer;
extern const mvc_dmx_func_st mvc_mkvf_demuxer;
extern const mvc_dmx_func_st mvc_mp3a_demuxer;
extern const mvc_dmx_func_st mvc_rmvb_demuxer;
extern const mvc_dmx_func_st mvc_tiny_demuxer;
extern const mvc_dmx_func_st mvc_asff_demuxer;
extern const mvc_dmx_func_st mvc_rtpp_demuxer;
extern const mvc_dmx_func_st mvc_plugin_demuxer;

#endif /* MVC_DEMUXER_H */
