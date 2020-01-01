#ifndef TINYDMX_H
#define TINYDMX_H

#include <stdint.h>
#include "avp_streaming.h"
#include "avp_mvc_demuxer.h"

/**************************************************************************
    Beginning of TINY file format spec

    1. Any new field should be added in the last one of each structure.
***************************************************************************/

#define TINY_MAX_CONFIG_LEN   256

typedef enum TINY_FRAME_TYPE_e
{
    TINY_EOF_FRAME = 0,
    TINY_AUDIO_FRAME,
    TINY_VIDEO_FRAME,
    TINY_A_CONFIG_FRAME,
    TINY_V_CONFIG_FRAME,
} TINY_FRAME_TYPE;

typedef enum TINY_VIDEO_CODEC_TYPE_e
{
    TINY_VIDEO_TYPE_ERROR = -1,
    TINY_VIDEO_TYPE_UNKNOWN,
    TINY_VIDEO_TYPE_MP2V,
    TINY_VIDEO_TYPE_DIV3,
    TINY_VIDEO_TYPE_DIVX,
    TINY_VIDEO_TYPE_H263,
    TINY_VIDEO_TYPE_M4V,
    TINY_VIDEO_TYPE_MP4S,
    TINY_VIDEO_TYPE_MP41,
    TINY_VIDEO_TYPE_MP42,
    TINY_VIDEO_TYPE_MP43,
    TINY_VIDEO_TYPE_WMV1,
    TINY_VIDEO_TYPE_WMV2,
    TINY_VIDEO_TYPE_WMV3,
    TINY_VIDEO_TYPE_WMVA,
    TINY_VIDEO_TYPE_AVC1,
    TINY_VIDEO_TYPE_RVCH,
    TINY_VIDEO_TYPE_FLV1,
    TINY_VIDEO_TYPE_RV10,
    TINY_VIDEO_TYPE_RV20,
    TINY_VIDEO_TYPE_RV30,
    TINY_VIDEO_TYPE_RV40,
    TINY_VIDEO_TYPE_AVS1,
    TINY_VIDEO_TYPE_MJPG,
    TINY_VIDEO_TYPE_MSVC,
    TINY_VIDEO_TYPE_VP60,
    TINY_VIDEO_TYPE_VP70,
    TINY_VIDEO_TYPE_VP80,
    TINY_VIDEO_TYPE_I420,
} TINY_VIDEO_CODEC_TYPE;

typedef enum TINY_AUDIO_CODEC_TYPE_e
{
    TINY_AUDIO_TYPE_ERROR = -1,
    TINY_AUDIO_TYPE_UNKNOWN,
    TINY_AUDIO_TYPE_AAC,
    TINY_AUDIO_TYPE_AC3,
    TINY_AUDIO_TYPE_AMRNB,
    TINY_AUDIO_TYPE_AMRNBIF2,
    TINY_AUDIO_TYPE_AMRWB,
    TINY_AUDIO_TYPE_ATRC,
    TINY_AUDIO_TYPE_COOK,
    TINY_AUDIO_TYPE_DRA,
    TINY_AUDIO_TYPE_DTS,
    TINY_AUDIO_TYPE_MP3,
    TINY_AUDIO_TYPE_PCM,
    TINY_AUDIO_TYPE_SIPR,
    TINY_AUDIO_TYPE_WMA1,
    TINY_AUDIO_TYPE_WMA2,
    TINY_AUDIO_TYPE_WMA3,
} TINY_AUDIO_CODEC_TYPE;

typedef enum TINY_SUBTITLE_TYPE_e
{
    TINY_SUBTITLE_TYPE_ERROR = -1,
    TINY_SUBTITLE_TYPE_UNKNOWN,
    TINY_SUBTITLE_TYPE_DXSB,
    TINY_SUBTITLE_TYPE_MP4S,
} TINY_SUBTITLE_TYPE;

typedef struct tiny_video_config_s {
    int codec_type;
    int width;
    int height;
    int config_len;

    uint8_t config[TINY_MAX_CONFIG_LEN];
    /*
    config contains following fields
    1. int stride_y
    2. int stride_uv
    */

} tiny_video_config;

typedef struct tiny_audio_config_s {
    int codec_type;
    int sample_rate;
    int channel_num;
    int bits_per_sample;
    int frame_length;
    int config_len;
    uint8_t config[TINY_MAX_CONFIG_LEN];
} tiny_audio_config;

/**************************************************************************
    End of TINY file format spec
***************************************************************************/

typedef struct tiny_frame_info_s {
    mvc_stream_type_et type;
    uint8_t *buffer;
    int   bufsize;
    int64_t pts;
} tiny_frame_info;

typedef struct tiny_demuxer_s {
    cb_buffer_st        cbuffer;
    mvc_allocator_st    allocator;
    void               *alloc_ctx;
    void               *mem_ctx;
    tiny_audio_config   a_config;
    tiny_video_config   v_config;
    int                 queued_frame_size[2];
    int                 queued_frame_count[2];
    int                 start_code_count[2];
    int64_t             pts_queue[2];

} tiny_demuxer_st;

#endif /* TINYDMX_H */
