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


#ifndef VIDEO_DECODER_H
#define VIDEO_DECODER_H

#include <stdint.h>
#include "avp_mmp_video.h"
#include "avp_buf_element.h"
#include "avp_video_out.h"
#include "avp_mmp_info.h"

#define DISP_FRAME_INFO_COUNT (4)

enum VIDEO_DECODER_TYPE
{
    MMP_SW_VIDEC,
    MMP_HW_MVD,
    MMP_HW_MJPD,
    MMP_HW_M4VD,
    MMP_RAW,
    MMP_RTK_MJPD,
    MMP_AVCODEC,
    MMP_FAKE,
};

enum VIDEO_DECODER_DEC_MODE
{
    NORMAL_DEC,
    THUMBNAIL_DEC,
};

typedef struct disp_frame_info_s
{
    void *buffer;
    int in_use;
} disp_frame_info_st;

enum VIDEO_DECODER_SPEED
{
    VD_SPEED_NORMAL,
    VD_SPEED_NON_REF_FILTER_OFF,
    VD_SPEED_FILTER_OFF,
    VD_SPEED_DROP_B,
};

typedef struct video_decoder_s video_decoder_t;

struct video_decoder_s
{
    uint32_t (*open) (video_decoder_t      *self,
                      mmp_video_config_st  *config,
                      void                 *opaque);

    int (*decode_data) (video_decoder_t    *self,
                        buf_element_t      *input,
                        vo_frame_buffer_t  *output);

    int (*flush) (video_decoder_t          *self,
                  vo_frame_buffer_t        *output);

    void (*reset) (video_decoder_t *self);

    uint32_t (*close)(video_decoder_t *self);

    // callback function for free decoding picture
    void (*picture_free_cb)(video_decoder_t *self, void *opaque);

    int (*ready_to_decode)(video_decoder_t *self);

    int (*get_capability)(video_decoder_t      *self,
                          video_info           *file_info,
                          uint32_t             *support_frame_rate);

    int (*is_in_use) (video_decoder_t *self, void *opaque);

    void *player;

    int videc_type;
    int dec_mode;
    void *output_buffer;
    int resync_flag;
    int dec_err_count;

    int drop_B;
    int vd_speed_level;
    int loopfilter_level;
    int seek_I;

    uint32_t output_format;

    disp_frame_info_st *disp_info_table;
    int disp_info_count;
    void *free_disp_packet;
    int row_mode;
};

int init_video_decoder(void *player_inst, uint32_t data_fmt);
void close_video_decoder_plugin(video_decoder_t **decoder);
int vd_send_vo_pkt(video_decoder_t *this, vo_frame_buffer_t *frame);
int prepare_row_video_out_data(void *ctx, MMP_VO_FRAME_SETTING *frame_setting);
int copy_data_to_ibuf(void *buffer, int buffer_size, int in_ibuf_size, uint8_t **out_ibuf, int *out_ibuf_size);
void mmp_d_cache_flush(uint8_t *buf, int size);
void mmp_d_cache_invalidate(uint8_t *buf, int size);
int notify_video_decode_delay(void *pInst, int64_t pts, int late);
int notify_decode_more(void *pInst);
int allocate_disp_info_table(video_decoder_t *this, void *disp_info_buf, int one_disp_info_size, int disp_info_count);
void free_disp_info_table(video_decoder_t *this);
void *get_free_disp_info_packet(video_decoder_t *this);
int set_disp_info_packet(video_decoder_t *this, void *packet, int in_use);
#endif // VIDEO_DECODER_H

