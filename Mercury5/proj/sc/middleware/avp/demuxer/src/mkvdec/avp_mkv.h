////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2010 MStar Semiconductor, Inc.
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


#ifndef MKV_H
#define MKV_H

#include <stdint.h>
#include "avp_sys_common.h"
#include "avp_streaming.h"

enum MKV_ELEMENT_ID_e
{
    ELEMENT_EMBL            =   0x1A45DFA3,
    ELEMENT_SEGMENT         =   0x18538067,
/* level 1 element*/
    ELEMENT_SeekHead        =   0x114D9B74,
    ELEMENT_SegmentInfo     =   0x1549A966,
    ELEMENT_Track           =   0x1654AE6B,
    ELEMENT_Cluster         =   0x1F43B675,
    ELEMENT_Cues            =   0x1C53BB6B,
/* not level 1 */
/* element related to cues */
    ELEMENT_CueTime         =   0xB3,
    ELEMENT_CuePoint        =   0xBB,
    ELEMENT_CueTrackPositions = 0xB7,
    ELENEBT_CueTrack        =   0xF7,
    ELENEBT_CueClusterPosition =0xF1,
    ELENEBT_CueBlockNumber  =   0x5378,
/* element inside seek head */
    ELEMENT_Seek            =   0x4DBB,
    ELEMENT_SeekID          =   0x53AB,
    ELEMENT_SeekPosition    =   0x53AC,
/* element inside segment info */
    ELEMENT_TimeCodeScale   =   0x2AD7B1,
    ElEMENT_Duration        =   0x4489,
/* element related to track */
    ELEMENT_TrackEntry      =   0xAE,
    ELEMENT_TrackNumber     =   0xD7,
    ELEMENT_TrackUID        =   0x73C5,
    ELEMENT_TrackType       =   0x83,
    ELEMENT_FlagEnabled     =   0xB9,
    ELEMENT_FlagDefault     =   0x88,
    ELEMENT_FlagForced      =   0x55AA,
    ELEMENT_FlagLacing      =   0x9C,
    ELEMENT_MinCache        =   0x6DE7,
    ELEMENT_MaxCache        =   0x6DF8,
    ELEMENT_DefaultDuration =   0x23E383,
    ELEMENT_TrackTimeCodeScale =0x23314F,
    ELEMENT_CodecID         =   0x86,
    ELEMENT_CodecPrivate    =   0x63A2,
    ELEMENT_ContentEncodings=   0x6D80,
    ELEMENT_ContentEncoding =   0x6240,
    ELEMENT_ContentCompression =0x5034,
    ELEMENT_ContentCompAlgo =   0x4254,
    ELEMENT_ContentCompSettings = 0x4255,
    ELEMENT_Video           =   0xE0,
    ELEMENT_Audio           =   0xE1,
/* element inside video track */
    ELEMENT_PixelWidth      =   0xB0,
    ELEMENT_PixelHeight     =   0xBA,
    ELEMENT_PixelCropBottom =   0x54AA,
    ELEMENT_PixelCropTop    =   0x54BB,
    ELEMENT_PixelCropLeft   =   0x54CC,
    ELEMENT_PixelCropRight  =   0x54DD,
    ELEMENT_DisplayWidth    =   0x54B0,
    ELEMENT_DisplayHeight   =   0x54BA,
    ELEMENT_DisplayUnit     =   0x54B2,
/* element inside audio track */
    ELEMENT_SamplingFreq    =   0xB5,
    ELEMENT_OutSamplingFreq =   0x78B5,
    ELEMENT_Channels        =   0x9F,
    ELEMENT_BitDepth        =   0x6264,
/* element inside cluster */
    ELEMENT_TimeCode        =   0xE7,
    ELEMENT_BlockGroup      =   0xA0,
    ELEMENT_SimpleBlock     =   0xA3,
    ELEMENT_Blocks          =   0xA1,
/* global element */
    ELEMENT_CRC32           =   0xBF,
};

enum mkv_track_type_e {
    MKV_VIDEO_TRACK     = 0x01,
    MKV_AUDIO_TRACK     = 0x02,
    MKV_COMPLEX_TRACK   = 0x03, /* combined audio and video track */
    MKV_LOGO_TRACK      = 0x10,
    MKV_SUBSTITLE_TRACK = 0x11,
    MKV_BUTTON_TRACK    = 0x10,
    MKV_CONTROL_TRACK   = 0x20,
};

typedef enum mkv_block_mode_e {
    MKV_BlockGroup,
    MKV_SimpleBlock,
} mkv_block_mode_et;

typedef enum mkv_lacing_type_e {
    NO_Lacing           = 0,
    Xiph_Lacing         = 2,
    Fixed_Size_Lacing   = 4,
    EBML_Lacing         = 6,
} mkv_lacing_type_et;

enum mkv_content_comp_algo_e {
    COMP_ALGO_ZLIB = 0,
    COMP_ALGO_BZLIB,
    COMP_ALGO_LZO1X,
    COMP_ALGO_HEADER_STRIPING,
    COMP_ALGO_NONE,
};

enum mkv_flag_e
{
    MKV_keyframe    = 0x80,
    MKV_invisible   = 0x08,
    MKV_lacing      = 0x06,
    MKV_discardable = 0x01,
};

/* MKV demuxer context */
typedef struct mkv_stream_s
{
    mvc_stream_type_et  stream_type;
    int                 codec_type;
    int                 priority;
    uint32_t            frame_rate_num;
    uint32_t            frame_rate_den;
    int                 pts_base;
    int                 pts_curr;    /* in frame rate unit */
    int64_t             last_pts;
    uint32_t            last_fpos;
    uint32_t            length;
    uint32_t            sample_size;
    uint8_t             config[MAX_CONFIG_LEN];
    int                 config_len;
    int                 drop_index;
} mkv_stream_st;

#define AFQ_SIZE    3
#define VFQ_SIZE    500

#define MAX_CODEC_ID_LEN 16
#define MAX_COMP_SETTING_LEN 16

typedef struct mkv_avframe_s
{
    uint32_t            fpos;
    uint32_t            len;
    int64_t             pts;
    uint32_t            frame_count;
    int8_t              flag;
} mkv_avframe_st;

typedef struct mkv_video_track_s
{
    uint32_t    pixelWidth;
    uint32_t    pixelHeight;
    uint32_t    displayWidth;
    uint32_t    displayHeight;
    uint32_t    displayUnit;
} mkv_video_track_st;

typedef struct mkv_audio_track_s
{
    uint32_t    samplingFrequency;
    uint32_t    outputSamplingFrequency;
    uint32_t    channels;
    uint32_t    bitDepth;
} mkv_audio_track_st;

typedef struct mkv_track_entry_s
{
    uint32_t            trackNumber;
    uint64_t            trackUID;
    uint32_t            trackType;
    uint8_t             flagEnbale;
    uint8_t             flagDefault;
    uint8_t             flagForced;
    uint8_t             flagLacing;
    uint64_t            defaultDuration;
    uint64_t            trackTimeCodeScale;
    uint8_t             codecID[MAX_CODEC_ID_LEN];
    uint8_t             config[MAX_CONFIG_LEN]; // codecPrivate in MKV spec
    int                 config_len;
    uint32_t            compAlgo;
    uint8_t             compSetting[MAX_COMP_SETTING_LEN];
    uint32_t            compSetting_len;
    mvc_stream_type_et  mvc_track_type;
    union {
        mkv_video_track_st videoTrack;
        mkv_audio_track_st audioTrack;
    } avtrack;
    int                 codec_type;
} mkv_track_entry_st;

typedef struct mkv_seekhead_s
{
    uint32_t tracks_addr;
    uint32_t segmentInfo_addr;
    uint32_t cues_addr;
    uint32_t additional_seekhead_addr;
} mkv_seekhead_st;

typedef struct mkv_cuepoint_s
{
    int64_t     cue_time;
    uint32_t    cluster_position;
    uint32_t    track_number;
    uint32_t    block_number;
} mkv_cuepoint_st;

typedef struct mkv_block_s
{
    int8_t              flag;
    int8_t              remaining_frame_count;
    uint32_t            remaining_size;
} mkv_block_st;

// could be a block_group or a simple_block
typedef struct mkv_block_group_s
{
    uint32_t            remaining_size;
    uint32_t            time_code;
    mkv_block_st        block; // this one means payload
} mkv_block_group_st;

typedef struct mkv_cluster_s
{
    uint32_t            remaining_size;
    uint32_t            time_code;
    uint32_t            cur_block_group_number;
    mkv_block_mode_et   cur_block_group_mode;
    mkv_block_group_st  cur_block_group;
} mkv_cluster_st;

typedef struct mkv_next_block_prop_s
{
    mvc_stream_type_et  type;           /* MVC_STREAM_NONE means no constraint */
    uint32_t            block_number;
    int64_t             time_code;
} mkv_next_block_prop_st;

typedef struct mkv_demuxer_s
{
    int                 seekable;
    uint32_t            frame_duration; /* in microsecond unit */
    uint64_t            time_code_scale;
    int64_t             duration;
    uint32_t            max_byte_rate;
    uint32_t            segment_addr;   /* the start address of segment */
    uint32_t            segment_size;
    uint32_t            cue_addr;       /* the start address of cue */
    uint32_t            additional_seekhead_addr;
    uint32_t            first_cluster_addr;
    uint32_t            next_cluster_addr;
    mkv_cluster_st      cur_cluster;
    int                 max_tracks;
    int                 num_tracks;
    int                 num_video_tracks;
    int                 num_audio_tracks;
    int                 num_complex_tracks;
    int                 num_subtitle_tracks;
    int                 num_other_tracks;
    int                 width, height;
    int                 active_video, active_audio, active_subtitle;
    int64_t             last_video_pts;
    int64_t             last_audio_pts;
    uint32_t            nalu_length;
    cb_buffer_st        cbuffer;
    mkv_next_block_prop_st target_block_prop;  /* indicate the property of next desired block, used after seeking */
    mvc_allocator_st    allocator;
    void               *alloc_ctx;
    void               *mem_ctx;
    mvc_drop_level_et   drop_level;
    int                 drop_ratio_num;
    int                 drop_ratio_den;
    mkv_avframe_st      vf_queue[VFQ_SIZE];
    uint16_t            vf_rptr;
    uint16_t            vf_size;
    mkv_avframe_st      af_queue[AFQ_SIZE];
    uint16_t            af_rptr;
    uint16_t            af_size;
    mkv_track_entry_st  mkv_track_entry[];
} mkv_demuxer_st;

/* these structures map to actual data structures in the file */
#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

typedef struct mkv_ms_vfw_header_s
{
    uint32_t size;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t  pel_per_meter_x;
    int32_t  pel_per_meter_y;
    uint32_t color_used;
    uint32_t color_required;
} ATTR_PACK mkv_ms_vfw_st;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif /* MKV_H */
