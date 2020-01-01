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


#ifndef MMP_VIDEO_H
#define MMP_VIDEO_H

#include <stdint.h>

#define VIDEO_TYPE_4CC(a, b, c, d) \
            (((uint32_t) (a) << 24) | ((uint32_t) (b) << 16) | \
             ((uint32_t) (c) <<  8) | ((uint32_t) (d)))

enum VIDEC_TIMESTAMP_TYPE
{
    VDEC_TS_PTS,
    VDEC_TS_DTS,
};

enum VIDEO_CODEC_TYPE
{
    MMP_CODEC_I420 = VIDEO_TYPE_4CC('i','4','2','0')
};

typedef enum mmp_video_rotate_type_e
{
    MMP_VIDEO_ROTATE_0,
    MMP_VIDEO_ROTATE_90,
    MMP_VIDEO_ROTATE_180,
    MMP_VIDEO_ROTATE_270
} mmp_video_rotate_type_et;

typedef enum mmp_video_flip_type_e
{
    MMP_VIDEO_FLIP_ACTIVE,
    MMP_VIDEO_FLIP_PASSIVE,
    MMP_VIDEO_FLIP_THUMBNAIL
} mmp_video_flip_type_et;

typedef struct mmp_video_rect_s
{
    uint16_t                    x;
    uint16_t                    y;
    uint16_t                    w;
    uint16_t                    h;
} mmp_video_rect_st;

typedef struct mmp_video_config_s
{
    uint32_t                    codec_type; /* only I420 is available for now */
    uint16_t                    width;
    uint16_t                    height;
    uint32_t                    frame_rate_num;
    uint32_t                    frame_rate_den;
    uint8_t                     ts_type;
    uint8_t                     bit_depth;  /* optional unless codec_type is 'raw ' (RGB) */
    uint8_t                     init_only;
} mmp_video_config_st;

typedef struct mmp_display_setting_s
{
    mmp_video_rect_st           disp_rect;
    mmp_video_rotate_type_et    rotate_mode;
    mmp_video_flip_type_et      flip_mode;
    int                         maced;
    void                       *disp_buff;
    void                       *vo_drv;
} mmp_display_setting_st;

typedef struct mmp_video_frame_s
{
    uint8_t                    *data[4];
    int32_t                     stride[4];
    int32_t                     pts;        /* unit: ms */
    mmp_video_rect_st           disp_area;
    void                       *opaque;     /* callback context */
} mmp_video_frame_st;

int mmp_video_render_stream(void **handle, mmp_video_config_st *config, mmp_display_setting_st *setting);
int mmp_video_set_sync_source(void *handle, void *clock); /* default to audio clock */
int mmp_video_display_frame(void *handle, mmp_video_frame_st *frame);
int mmp_video_pause_playback(void *handle);
int mmp_video_resume_playback(void *handle);
int mmp_video_flush_stream(void *handle);
int mmp_video_close_stream(void *handle);
int mmp_video_set_callback(void *handle, ...); /* pre-render, post-convert, post-render, etc. */

#endif /* MMP_VIDEO_H */
