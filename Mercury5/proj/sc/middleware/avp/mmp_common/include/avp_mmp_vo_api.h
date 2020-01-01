////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
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


#ifndef MMP_VO_API_H
#define MMP_VO_API_H

#include <stdint.h>

enum {
    VO_FMT_I420,
    VO_FMT_MB_TILE,
    VO_FMT_YUYV,
    VO_FMT_NV12,
    VO_FMT_RGB565
};

enum {
    DISP_NORMAL,
    DISP_MENU_LOAD,
};

enum {
    VO_3D_NONE = 0,
    VO_3D_RED_CYAN,
    VO_3D_NAKE,
    VO_3D_LEFT_RIGHT,
    VO_3D_LEFT_ONLY
};

typedef struct mmp_vo_rect_s
{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
} mmp_vo_rect_st;

typedef struct MMP_VO_FRAME_SETTING_S
{
    int in_fmt;
    uint8_t *disp_buffer;
    int rotate_mode;
    uint8_t *src_y;
    uint8_t *src_u;
    uint8_t *src_v;
    int width;
    int height;
    int stride_y;
    int stride_uv;
    int active_x;
    int active_y;
    int x_offset;
    int y_offset;
    mmp_vo_rect_st disp_rect;
    int disp_pitch;
    void *disp_frame_info;
    int disp_mode;
    int maced;
    int row_num;
} MMP_VO_FRAME_SETTING;

typedef struct vo_driver_s
{
    int     (* init)                (struct vo_driver_s *handle, int width, int height, int frame_rate, int in_fmt, MMP_VO_FRAME_SETTING *frame_setting);
    void *  (* get_screen)          (struct vo_driver_s *handle);
    int     (* color_convert_row)   (struct vo_driver_s *handle, MMP_VO_FRAME_SETTING *frame_setting);
    int     (* color_convert)       (struct vo_driver_s *handle, MMP_VO_FRAME_SETTING *frame_setting);
    int     (* wait_convert_finish) (struct vo_driver_s *handle);
    int     (* flip)                (struct vo_driver_s *handle, MMP_VO_FRAME_SETTING *frame_setting, int *dec_frame_released, int *disp_frame_released);
    int     (* release_disp_buf)    (struct vo_driver_s *handle, int in_fmt, void *disp_frame_info);
    int     (* flip_thumbnail)      (struct vo_driver_s *handle, MMP_VO_FRAME_SETTING *frame_setting);
    int     (* get_disp_info_size)  (struct vo_driver_s *handle, int in_fmt);
    int     (* get_refresh_info)    (struct vo_driver_s *handle);
    int     (* refresh)             (struct vo_driver_s *handle);
    int     (* reset_setting)       (struct vo_driver_s *handle, MMP_VO_FRAME_SETTING *frame_setting);
    int     (* setting_changed)     (struct vo_driver_s *handle);
    int     (* close)               (struct vo_driver_s **handle, int in_fmt);
    int     row_mode;
    int     effect_3D;
    int     effect_3D_depth;
} vo_driver_st;

int init_default_video_out(struct vo_driver_s **handle);

#endif /* MMP_VO_API_H */
