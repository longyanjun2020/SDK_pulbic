////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2012 MStar Semiconductor, Inc.
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


#ifndef AVI_H
#define AVI_H

#include "avp_sys_common.h"
#include "avp_streaming.h"

typedef enum parse_mode_e
{
    PARSE_SEQ,
    PARSE_IDX,
    PARSE_SEP,
} parse_mode_et;

typedef struct rect_s
{
    int16_t left;
    int16_t top;
    int16_t right;
    int16_t bottom;
} rect_st;

/* AVI demuxer context */
typedef struct avi_stream_s
{
    sys_stream_st       s;
    int                 priority;
    uint32_t            frame_rate_num;
    uint32_t            frame_rate_den;
    int                 pts_base;
    int                 pts_curr;    /* in frame rate unit */
    int64_t             last_pts;
    uint32_t            last_fpos;
    uint32_t            length;
    uint32_t            indx_addr;
} avi_stream_st;

#define AFQ_SIZE    5
#define VFQ_SIZE    600 /* this is for 720P temporary solution */

typedef struct avi_avframe_s
{
    uint32_t            fpos;
    uint32_t            len;
    int64_t             pts;
} avi_avframe_st;

typedef struct avi_demuxer_s
{
    sys_demuxer_st      s;
    int                 is_odml;
    int                 has_index;
    uint32_t            frame_duration; /* in microsecond unit */
    uint32_t            max_byte_rate;
    int                 max_streams;
    int                 width, height;
    uint32_t            movi_addr;
    uint32_t            movi_size;
    uint32_t            idx1_addr;
    uint32_t            idx1_size;
    parse_mode_et       parse_mode;
    void               *mem_ctx;
    avi_avframe_st      vf_queue[VFQ_SIZE];
    uint16_t            vf_rptr;
    uint16_t            vf_size;
    avi_avframe_st      af_queue[AFQ_SIZE];
    uint16_t            af_rptr;
    uint16_t            af_size;
    avi_stream_st       stream_info[];
} avi_demuxer_st;

/* these structures map to actual data structures in the file */
#ifdef _MSC_VER
#pragma pack(push, 1)
#endif
typedef struct avi_main_header_s
{
    uint32_t frame_duration;
    uint32_t max_byte_rate;
    uint32_t alignment;
    uint32_t flags;
    uint32_t num_frames;
    uint32_t initial_frame;
    uint32_t num_streams;
    uint32_t buffer_size;
    uint32_t width;
    uint32_t height;
    uint32_t reserved[4];
} avi_main_header_st;

#define AVI_FLAG_DISABLE 0x00000001
#define AVI_FLAG_PALCHG  0x00010000

typedef struct avi_stream_header_s
{
    uint32_t fcc_type;
    uint32_t fcc_handler;
    uint32_t flags;
    int16_t  priority;
    int16_t  language;
    uint32_t initial_frame;
    uint32_t scale;
    uint32_t rate;
    uint32_t start;
    uint32_t length;
    uint32_t buffer_size;
    uint32_t quality;
    uint32_t sample_size;
    rect_st rect;
} ATTR_PACK avi_stream_header_st;

#define AVI_IDX_IS_LIST     0x00000001
#define AVI_IDX_IS_KEYFRAME 0x00000010

typedef struct avi_old_index_s
{
    uint32_t id;
    uint32_t flags;
    uint32_t offset;
    uint32_t size;
} ATTR_PACK avi_old_index_st;

typedef struct avi_meta_index_s
{
    uint16_t size_per_entry;
    uint8_t  index_sub_type;
    uint8_t  index_type;
    uint32_t valid_entries;
    uint32_t chunk_type;
    union {
        struct {
            uint32_t reserved[3];
        } ATTR_PACK sup;
        struct {
            uint64_t offset;
            uint32_t reserved;
        } ATTR_PACK std;
        struct {
            uint64_t offset;
            uint32_t reserved;
        } ATTR_PACK fld;
    } u;
} ATTR_PACK avi_meta_index_st;

typedef struct avi_super_index_entry_s
{
    uint64_t offset;
    uint32_t size;
    uint32_t duration;
} ATTR_PACK avi_super_index_entry_st;

typedef struct avi_standard_index_entry_s
{
    uint32_t offset;
    int32_t  size;
} ATTR_PACK avi_standard_index_entry_st;

// index_type
#define AVI_INDEX_OF_INDEXES    0x00
#define AVI_INDEX_OF_CHUNKS     0x01
#define AVI_INDEX_IS_DATA       0x80

// index_sub_type
#define AVI_INDEX_2FIELD        0x01

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif /* AVI_H */
