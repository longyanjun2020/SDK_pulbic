#ifndef CFLV_H
#define CFLV_H

#include <stdint.h>
#include "avp_streaming.h"

#define FLV_MAX_CONFIG_LEN (256)
#define FLV_CACHE_PAGE_SIZE (1024) // must bigger than 11
#define FLV_MAX_RECORD_PTS_COUNT (5)

#define AFQ_SIZE    3
#define VFQ_SIZE    600

typedef struct flv_avframe_s
{
    uint32_t            fpos;
    uint32_t            len;
    int64_t             pts;
} flv_avframe_st;

typedef struct FLV_cache_page_s
{
    uint8_t cache_page[FLV_CACHE_PAGE_SIZE];
    int     cache_capacity;
    int     cache_base; // file position mapped to cache_page[0]
}FLV_cache_page;

typedef struct CFLV_s
{
    cb_buffer_st cbuffer;
    int     width, height;
    int     bitrate;
    int64_t duration; //unit: ms
    int     video_type, audio_type;
    int     bufsize;
    int     lensize;
    int64_t last_video_pts;
    int64_t last_audio_pts;
    int64_t last_video_dur;
    int64_t last_audio_dur;
    int64_t seek_time;
    int     vol_size;
    int     aol_size;
    uint8_t vol_buf[FLV_MAX_CONFIG_LEN];
    uint8_t aol_buf[FLV_MAX_CONFIG_LEN];
    flv_avframe_st      vf_queue[VFQ_SIZE];
    uint16_t            vf_rptr;
    uint16_t            vf_size;
    flv_avframe_st      af_queue[AFQ_SIZE];
    uint16_t            af_rptr;
    uint16_t            af_size;

    int                 file_size;
    FLV_cache_page      flv_cache_page;
    uint8_t             record_pts_flag;
    int                 record_pts_count;
    int64_t             record_pts[FLV_MAX_RECORD_PTS_COUNT]; //unit: ms

    // for allocator use
    const mvc_allocator_st    *allocator;
    void               *alloc_ctx;
    void               *mem_ctx;
} CFLV;

#endif
