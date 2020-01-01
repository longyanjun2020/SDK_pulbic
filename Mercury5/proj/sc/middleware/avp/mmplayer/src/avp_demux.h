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


#ifndef DEMUX_H
#define DEMUX_H

#include <stdint.h>
#include "avp_rbuffer.h"
#include "avp_mmp_info.h"
#include "avp_player_common_api.h"
#include "avp_mvc_demuxer.h"

struct cb_io_s;

//====================================================================
// demux status
//
#define DEMUXER_OK                  (0)
#define DEMUXER_FINISHED            (1<<1)
#define DEMUXER_SEEK_FAIL           (1<<2)

//
// demux status
//====================================================================


#define DMX_SEEK_MODE_PREV_I    0
#define DMX_SEEK_MODE_NEXT_I    1
#define DMX_SEEK_A_ONLY         (1 << 1)
#define DMX_SEEK_V_ONLY         (1 << 2)

#define DMX_AUDIO_TRACK         0
#define DMX_VIDEO_TRACK         1
#define DMX_SUBTITLE_TRACK      2

enum
{
    DMX_INIT_STATE=0,
    DMX_PLAY_STATE,
};

enum FORCE_DMX_EOF_ERR_CAUSE
{
    VD_ERR_FORCE_DMX_EOF=1,
    DMX_ERR_FORCE_DMX_EOF,
};

#define START_DROP_VIDEO_THRESHOLD  400
#define DROP_FRAME_MAX_PTS          0x7FFFFFFF
#define DEMUX_DROPTOI
//#define PROFILE_DEMUX_READ_DATA
typedef enum MY_DROP_STATE
{
    NORMAL_PLAY=0,
    NONSYNC_PLAY,
    DROP2NEXTI,     //drop_video=1, but demuxer hasn't parsed targetPTS, so we drop all packets unitl parsing targetPTS packet
    WAIT_DROP_VIDEO,//demuxer parsing PTS is larger than targetPTS+30 frames, set to this state, and won't parsing any packets
    VOPBUF2VRING,   //demuxer copy VOPbuf to V_ring until VOPbuf is empty, then set state to NORMAL_PLAY.
} DROP_STATE;

typedef enum CLEARVRING_STATE
{
    INIT_STATE=0, //if clear Vring to PTS and we don't get target_PTS, we will set to init_state
    WAIT_VIDEO_CLEAR,
    VD_GET_TARGET_PTS,
    VO_GET_TARGET_PTS,
    NO_TARGET_PTS,
} CLEAR_VRING_STATE;

typedef enum SKIPB_MODE
{
    SKIPB_INIT=0,   //Set to MVC_DROP_1_2
    SKIPB_ALL,      //skip all B frame
    SKIPB_2_3,      //decode 1 B with continuous 3 B frames
} SKIP_B_MODE;

typedef struct _TRACK_HEADER_INFO_
{
    uint8_t track_exist;
    unsigned int data_fmt;
    unsigned char *m_decoderConfigDesc;
    unsigned int m_decoderConfigDesc_len;
} track_header_info;

typedef struct demux_s demux_t;


struct demux_s {
    int (*open) (demux_t *this, struct cb_io_s *cbio, video_info *file_info, track_header_info *atrack, track_header_info *vtrack, uint8_t password[16], int enable_audio, int enable_video);

    void (*close) (demux_t *this);

    void (*reset) (demux_t *this);

    int (*seek) (demux_t *this, int *seek_pos, int mode, int query_only);

    int (*read_data) (demux_t *this);

    int (*get_optional_data) (demux_t *this, void *data, mvc_stream_type_et data_type);

    int (*set_channel) (demux_t *this, int ch1, int ch2);

    int (*set_track) (demux_t *this, int track_type, int track_id);

    int (*flush_queue_frame)(demux_t *this);

    int (*set_playback_speed)(demux_t *this, video_info *file_info, int play_speed);

    int (*set_drop)(demux_t *this, mvc_drop_level_et level);

    int (*get_metadata)(demux_t *this, void *pBuffer, int bufsize);

    mmp_mutex_t ui_cmd_mutex;
    mmp_sem_t ui_cmd_complete_sem;
    mmp_sem_t enter_seek_I_sem;
    uint8_t   seek_I_complete;

    int select_track_flag;
    int select_track_type;
    int select_track_id;

    //
    // ring buffer for demuxer
    //
    struct ringbuffer v_ringbuf;
    struct ringbuffer a_ringbuf;
#ifdef SUPPORT_SUBTITLE
    struct ringbuffer s_ringbuf;
#endif
    int v_rbuf_mem_pool; // temp solution for video ringbuffer memory type

    int audio_inited, video_inited;
    int video_end, audio_end, status;
    int32_t last_video_pts;
    int32_t last_audio_pts;

    int32_t seek_time;
    int32_t seek_I_time;

    uint8_t audio_enabled, video_enabled, subtitle_enabled;
    uint8_t subtrack_exist;

    uint8_t av_seek;
    uint8_t switch_channel;
    int force_eof;
    uint8_t dx_wait_rbuf_done;

    void *player;
    void *context; // format dependent context
    void *baseptr; // the allocated buffer pointer for demuxer context

    int seek_flag;
    int seek_result;
    int dmx_count;
    int64_t total_dmx_time;

    int enable_adaptive_ringbuf_size;
    int org_dmx_mode;
    int64_t pause_dmx_time;
    int32_t v_last_dec_pts;
    int32_t a_last_dec_pts;
    int dmx_state;

    uint32_t vdrop_target;      /* the target time to speed demux to */
    int support_avframe_video;  /* the same value as sys_demux_t support_avframe_video */
    int support_avframe_audio;  /* the same value as sys_demux_t support_avframe_audio */
    int64_t nextI_PTS;          /* VO pass PTS to demuxer for NextIFrame. Demuxer store this PTS for updating target_PTS when non-seekable file */
    int64_t target_PTS;
    int target_PTS_updated;     /* 1: NextIFrame() updated, 2: demuxer nextI_PTS update */
    SKIP_B_MODE skip_b;
    int skip_b_set;
    int I_frame_only;
    int drop_video;
    int split_audio;
    int more_audio;             /* to prevent audio break, generally by tolerating larger A/V latency */
    CLEAR_VRING_STATE clearVringtoPTS;  //0: initial, 1: demuxer wait video clear Vring to PTS, 2: get targetI from Vring
    DROP_STATE drop_state;

    struct cb_io_s *cbio;

    buf_element_t video_packet;
    buf_element_t audio_packet;
    buf_element_t subtitle_packet;

#if defined(DROP_FRAME_STATISTIC) && defined(DEMUX_DROPTOI)
    int drop_count;
    int total_drop_time;
#endif
};

int  init_demuxer_plugin(void *player, demux_t **dmx, uint32_t demux_fmt);
void close_demuxer_plugin(demux_t **dmx);
int  start_demux_thread(void *pInst);
void destroy_demux_thread(demux_t *dmx);

int  notify_demux_more(void *pInst);
int  notify_video_delay(void *pInst, int64_t pts, int late);
int  notify_audio_delay(void *pInst, int64_t pts, int late);

int  dmx_common_init(demux_t *dmx, int vsize, int asize, uint32_t v_codec, uint32_t a_codec);
void dmx_common_reset(demux_t *dmx);
void dmx_common_close(demux_t *dmx);
int  dmx_change_drop_state(demux_t *this, int to_state);

int  demux_init_seek(void *pInst);
void demux_send_a_end_buffer(demux_t *dmx);
void demux_send_v_end_buffer(demux_t *dmx);
int  demux_init_set_channel(void *pInst, int ch1, int ch2);
int  demux_init_select_track(void *pInst, int track_type, int track_id);
int  demux_check_ringbuf_empty(struct ringbuffer *rbuf);
int  demux_get_first_packet(struct ringbuffer *rbuf, buf_element_t *cfg);
int  demux_set_fast_forward_drop(void *pInst, int play_speed);
void demux_enter_drop_state(void *pInst, int32_t target_pts, int allow_run_time_update);

int  clear_v_ring_buf_to_pts(void *pInst, buf_element_t *read_buf);
void decide_ringbuffer_size(uint32_t v_codec, uint32_t a_codec, int width, int height, int enable_video, int enable_audio, int *video_rbuf_size, int *audio_rbuf_size);

int rbuf_alloc(void *ctx, mvc_stream_type_et type, void **buffer, int size);
int rbuf_commit(void *ctx, mvc_stream_type_et type, int size, int64_t pts);
int rbuf_discard(void *ctx, mvc_stream_type_et type);
int rbuf_end_stream(void *ctx, mvc_stream_type_et type);
int rbuf_realloc(void *ctx, mvc_stream_type_et type, void **buffer, int size);

#endif // DEMUX_H
