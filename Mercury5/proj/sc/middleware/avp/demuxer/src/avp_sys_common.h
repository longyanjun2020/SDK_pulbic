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


#ifndef SYS_COMMON_H
#define SYS_COMMON_H

#include "avp_mvc_demuxer.h"
#include "avp_streaming.h"

/* demuxer common internal definitions */

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define ATTR_PACK __attribute__ ((packed))
#define UNUSED __attribute__((unused))
#else
#define ATTR_PACK
#define UNUSED
#endif

/* maximum length for decoder specific configuration data */
#define MAX_CONFIG_LEN   1024

/* maximum length for trying to resync header */
#define MAX_RESYNC_SIZE  (1024 * 1024)

/* maximum PTS difference between consecutive frames (unit: us) */
#define MAX_PTS_DIFF     INT64_C(10000000)

/* macro for pointer alignment, n must be power of 2 */
#define ALIGN_PTR(p, n)  ((void *) (((intptr_t) (p) + ((n) - 1)) & -(n)))

/* min/max macros */
#define SYS_MIN(a, b)    ((a) < (b) ?  (a) : (b))
#define SYS_MAX(a, b)    ((a) > (b) ?  (a) : (b))
#define SYS_ABS(a)       ((a) <  0  ? -(a) : (a))

#define READ_BE16(a)     ((((uint8_t *) (a))[0] <<  8) | ((uint8_t *) (a))[1])
#define READ_BE32(a)     ((((uint8_t *) (a))[0] << 24) | (((uint8_t *) (a))[1] << 16) | \
                          (((uint8_t *) (a))[2] <<  8) | (((uint8_t *) (a))[3]))
#define READ_LE32(a)     ((((uint8_t *) (a))[3] << 24) | (((uint8_t *) (a))[2] << 16) | \
                          (((uint8_t *) (a))[1] <<  8) | (((uint8_t *) (a))[0]))
#define BE32_TO_NE32(a)  READ_BE32(a)
#define LE32_TO_NE32(a)  (a)

/* demuxer common internal structures */

enum sys_stream_type_e
{
    AUD,
    VID,
    SUB,
    OTH,
};

typedef struct sys_aud_inf_s
{
    uint32_t            sample_rate;
    uint32_t            sample_size;
} sys_aud_inf_st;

typedef struct sys_vid_inf_s
{
    uint16_t            width;
    uint16_t            height;
} sys_vid_inf_st;

typedef struct sys_stream_s
{
    mvc_stream_type_et  stream_type;
    int                 codec_type;
    uint8_t             config[MAX_CONFIG_LEN];
    int                 config_len;
    union
    {
        sys_aud_inf_st  aud;
        sys_vid_inf_st  vid;
    } info;
} sys_stream_st;

typedef struct sys_demuxer_s
{
    int64_t             duration;
    int                 seekable;
    int                 total_streams;
    int                 num_streams[OTH + 1];
    int                 active_stream[SUB + 1];
    cb_buffer_st        cbuffer;
    mvc_allocator_st    allocator;
    void               *alloc_ctx;
    mvc_drop_level_et   drop_level;
    int                 drop_ratio_num;
    int                 drop_ratio_den;
    int                 drop_index;
} sys_demuxer_st;

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

/* BITMAPINFOHEADER structure */
typedef struct msft_video_header_s
{
    uint32_t            size;
    int32_t             width;
    int32_t             height;
    uint16_t            planes;
    uint16_t            bit_count;
    uint32_t            compression;
    uint32_t            size_image;
    int32_t             pel_per_meter_x;
    int32_t             pel_per_meter_y;
    uint32_t            color_used;
    uint32_t            color_required;
} ATTR_PACK msft_video_header_st;

enum msft_audio_format_e
{
    MSFT_AUDIO_PCM       = 1,
    MSFT_AUDIO_MS_ADPCM  = 2,
    MSFT_AUDIO_ALAW      = 6,
    MSFT_AUDIO_MULAW     = 7,
    MSFT_AUDIO_IMA_ADPCM = 0x11,
    MSFT_AUDIO_MPG       = 0x50,
    MSFT_AUDIO_MP3       = 0x55,
    MSFT_AUDIO_AC3_SPDIF = 0x92,
    MSFT_AUDIO_AAC       = 0xFF,
    MSFT_AUDIO_WMA1      = 0x160,
    MSFT_AUDIO_WMA2      = 0x161,
    MSFT_AUDIO_WMA3      = 0x162,
    MSFT_AUDIO_AC3       = 0x2000,
    MSFT_AUDIO_FAAC      = 0x706D,
};

/* WAVEFORMATEX structure (without cbSize) */
typedef struct msft_audio_header_s
{
    uint16_t            format_tag;
    uint16_t            channels;
    uint32_t            sample_rate;
    uint32_t            bit_rate;
    uint16_t            block_align;
    uint16_t            sample_depth;
} ATTR_PACK msft_audio_header_st;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

MVCVideoType msft_fourcc_to_vcodec(uint32_t fourcc);
int msft_parse_audio_header(sys_demuxer_st *d, sys_stream_st *s, uint32_t *size);
int msft_parse_video_header(sys_demuxer_st *d, sys_stream_st *s, uint32_t *size, uint32_t *fourcc);

#endif /* SYS_COMMON_H */
