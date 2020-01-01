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


#ifndef VIDEO_OUT_H
#define VIDEO_OUT_H

#include <stdint.h>
#include "avp_thread_mapping.h"
#include "avp_rbuffer.h"
#include "avp_mmp_video.h"
#include "avp_mmp_vo_api.h"
#include "avp_buf_element.h"
#include "avp_master_clock.h"
#ifdef SUPPORT_KMV
#include "avp_kmv_api.h"
#endif

typedef struct _video_out_s_ video_out_t;
typedef struct _vo_frame_buffer_ vo_frame_buffer_t;
typedef struct _decoded_picture_ dec_picture;

struct _decoded_picture_
{
    uint8_t *src_y;
    uint8_t *src_u;
    uint8_t *src_v;
    int width;
    int height;
    int stride_y;
    int stride_uv;
    int active_x;
    int active_y;
    void *private;
};

struct _vo_frame_buffer_
{
    uint32_t buff_size;          /* VO frame attached buff size */
    uint32_t flag;               /* vo flag */
    void *buffer;                /* display buff */
    int32_t  pts;                /* raw pts time */
    dec_picture picture;
    uint8_t need_relase_disp_buf;
    uint8_t valid;
#ifdef SUPPORT_KMV
    kmv_meta_st kmv_buf;
#endif
};

typedef struct
{
    int64_t pts;
    int     late;
} vo_quality_st;

enum {
    OUTPUT_DST_UNKNOWN = 0,
    OUTPUT_DST_BUF,
    OUTPUT_DST_DISP,
};

enum {
    /* frame related events */
    VO_EVENT_FRAME_START,
    VO_EVENT_FRAME_WAIT,
    VO_EVENT_CHECK_DROP,
    VO_EVENT_FRAME_DISP,
    VO_EVENT_FRAME_DONE,
    VO_EVENT_QUALITY,           /* MSMERR_FALSE - don't do quality control for this frame */

    /* query frame status */
    VO_QUERY_REFERENCED,
    /* query for audio only */
    VO_QUERY_FAKE,

    /* state related events */
    VO_STATE_PAUSED,
    VO_STATE_RESUMED,
    VO_STATE_FLUSHED,
};


typedef int (* vo_event_cb)(int event, void *ctx, void *data);

struct _video_out_s_ {

    int (*open) (video_out_t *self, mmp_video_config_st *config);
    //
    //flush video_out fifo
    //
    void (*flush) (video_out_t *self);

    void (*reset) (video_out_t *self);

    void (*close) (video_out_t *self);

    void (*dispose) (video_out_t *self);

    void (*get_vo_pkt)(video_out_t *this, vo_frame_buffer_t *frame_buf);

    void (*flip)(video_out_t *this, vo_frame_buffer_t *frame_buf, MMP_VO_FRAME_SETTING *frame_setting);

    int inited;
    //
    //ring buffer for vo
    //
    struct ringbuffer vo_ringbuf;
    uint8_t *vo_queue_buf;

    int sync_with_clock;
    int flip_to_display;
    void *screen;

    int input_format;
    int output_dst;
    void *player;
    int need_refresh_screen;
    int kmv_type;
    int kmv_outbuf_fmt;
    int kmv_inbuf_fmt;

    int voStop;
    int voPause;
    int voFlush;

    master_clock_st *clock;

    mmp_video_config_st     config;
    mmp_display_setting_st  setting;
    mmp_display_setting_st  new_setting;        /* TODO: use only one instance */
    int                     setting_dirty;
    mmp_mutex_t             setting_lock;

    vo_event_cb             event_callback;

    int prev_num_no_pts_frame;
    int32_t last_video_pts;

    int frame_duration;
    int color_convert_duration;
    int flip_duration;

    uint8_t                 thumbnail_done;
    vo_driver_st            *vo_drv;
};


int init_video_out(void *pInst, uint32_t input_format);
int start_vo_thread(void *pInst);
void destroy_vo_thread(video_out_t *vo);
int portable_video_out_set_disp_setting(video_out_t *vo, const mmp_display_setting_st *setting);
void portable_video_out_set_event_cb(video_out_t *vo, vo_event_cb event_cb);
void portable_video_out_set_new_pts(video_out_t *vo, int32_t new_pts);

#endif // VIDEO_OUT_H
