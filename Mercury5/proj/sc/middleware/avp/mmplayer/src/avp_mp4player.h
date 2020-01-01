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


#ifndef MP4PLAYER_H
#define MP4PLAYER_H

#include <stdint.h>
#include "avp_buf_element.h"
#include "avp_audio_decoder.h"
#include "avp_video_decoder.h"
#include "avp_video_out.h"
#include "avp_master_clock.h"
#include "avp_ms-mem.h"
#include "avp_thread_mapping.h"
#include "avp_msmComm.h"
#include "avp_player_common_struct.h"
#include "avp_player_common_api.h"
#include "avp_buff_mapping.h"
#include "avp_mmp_api.h"
#ifdef SUPPORT_SUBTITLE
#include "avp_subparser.h"
#endif

struct cb_io_s;
#define DEMUX_DROPTOI

//-----------------------------------------------------------------------------
//Include Files
//-----------------------------------------------------------------------------
#include "avp_rbuffer.h"
#include "avp_demux.h"

//-----------------------------------------------------------------------------
//Global Variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//Global definition
//-----------------------------------------------------------------------------
#define V_TRACK_EXIST   player->videotrack_exist
#define A_TRACK_EXIST   player->audiotrack_exist

#define A_CALL_BACK     (player->aud_decoder->callback_flag && !player->audioSilenceMode && (player->a_decode_target == -1))

#define V_TRACK_CMD_FLAG   (V_TRACK_EXIST)
#define A_TRACK_CMD_FLAG   (A_TRACK_EXIST << 1)

#define SEEK_IN_PLAY     (1<<0)
#define SEEK_BEFORE_PLAY (1<<1)
#define SEEK_PRECISE_POS (1<<2)
#define SEEK_IN_PAUSE    (1<<3)

typedef enum _mmp_play_mode_ {
    MMP_MODE_NORMAL_PLAY,
    MMP_MODE_GET_THUMBNAIL,
    MMP_MODE_GET_FILE_INFO,
} MMP_PLAY_MODE;

enum _PLAYING_STATES_
{
    OPEN_STATE,
    PLAY_STATE,
    STOP_STATE,
    PAUSED_STATE,
};

#if 0
#if 0
static void DBG_VO(const char *fmt, ...)
{
    va_list ap;
    char msg[2048];
    va_start(ap, fmt);
    vsprintf(msg, fmt, ap);
    vm_dbgError(0xD, msg);
    va_end(ap);
}
#else
#define DBG_VO(fmt, args...)                             \
{                                                     \
    UartSendTrace(fmt, ##args);                         \
}
#endif
#else
#define DBG_VO(x, ...) ((void)0) //diag_printf(fmt, ##args)
#endif

//-----------------------------------------------------------------------------
//Structure Declaration
//-----------------------------------------------------------------------------

typedef struct _ao_param_s_
{
    //
    //audio related
    //
    uint32_t samplerate;
    uint32_t frame_duration;
    uint32_t bytes_per_msec;
    uint16_t channel_info;
    uint16_t frame_length;
    uint32_t bits_per_sample;
    int volume;
    int EQMode;
    int reset;
    int init_mode;
} ao_param_t;

typedef struct _mp4_render_context_
{
    uint8_t     mode;
    uint8_t enable_audio;
    uint8_t enable_video;
    uint8_t enable_subtitle;
    uint8_t password[16];

    uint16_t disp_width;         /* display width */
    uint16_t disp_height;        /* display height */
    void     *disp_buffer;       /* display buffer address for thumbnail */
    void     *vo_drv;            /* video output driver */
    int      maced;

    uint16_t disp_start_x;
    uint16_t disp_start_y;
    MMP_ROTATE_MODE rotate_mode;

    int audio_volume;
    void *ao_handle;
    cb_io_st *cbio;

    int program_id;
    int appmode;
    int file_type;
    int capability;
} mp4_render_context;

typedef void mmp_enter_state_cb(void* pInst);

typedef struct {
    mmp_mutex_t         br_lock;        /* guarding mutex */
    mmp_cond_t          br_cond;        /* condition variable */
    uint8_t             br_count;       /* num of tasks at the barrier */
    uint8_t             br_n_threads;   /* num of tasks participating in the barrier synchronization */
    mmp_enter_state_cb  *enter_state_cb;
    void                *cb_par;
} barrier_t;

typedef int mmp_thread_release_cb(void* pInst);

typedef struct player_thread_s
{
    mmp_thread_inst       handle;
    void                  *stack;
    int                   existed;
    mmp_thread_release_cb *release_cb;
    void                  *cb_par;
} player_thread_st;

typedef struct _mp4player_s_
{
    player_common_inst      comm_inst;

    uint8_t curr_state;         /* playing state */

    int8_t s8Stop;              /* stop or not? */
    int8_t s8Pause;             /* pause or not: used for SCMD to notify EXE cmd that will pause later */
    int8_t audioStop;           /* stop flag for audio */
    int8_t audioPause;          /* pause flag for audio */
    int8_t audioFlush;          /* flush flag for audio */
    int8_t audioSilenceMode;    /* only put silence into IIS */
    uint16_t play_speed;        /* Slow or fast forward play */
    uint16_t next_speed;        /* next_speed != play_speed means play speed is going to change  */
    int64_t change_speed_time;  /* computer time base for current play_speed */
    int64_t change_speed_clock; /* system clock base for current play_speed */
    track_header_info audio_track;      /* audio track information? */
    track_header_info video_track;      /* video track information? */
    uint8_t audiotrack_exist;   /* audio track exist cached */
    uint8_t videotrack_exist;   /* video track exist cached */
    uint8_t subtrack_exist;     /* subtitle track exist cached */
    uint8_t vdis, adis;        /* discard video & audio frames */
    uint8_t sdis;              /* discard subtitle frames */
    uint8_t vo_dis;            /* discard vo frames */
    uint8_t adecoding;         /* temp solution for racing issue when in A/V flushing */
    int a_paused;
    uint8_t AO_finished;        /* temp solution for AD indicate DX if AD is finished */
    uint8_t VO_finished;
    int32_t reftime;            /* reference playback time */
    int32_t a_decode_target;
    int32_t v_decode_target;

    video_info file_info;

    ao_param_t ao_param;
    struct ao_driver_s *ao_drv;
    uint8_t audioCmd;

    audio_decoder_t *aud_decoder;
    video_decoder_t *vid_decoder;

    video_out_t vo;
    int         vo_inited;

    demux_t *demuxer;
    master_clock_st *mst_clock;

    mp4_render_context render_ctx;

    int64_t play_start_time;
    int8_t audio_play_start;

    int32_t new_a_pts, new_v_pts;

    //
    //Sync primitivies START
    //

    //  command gate START: for coping with the synging between states changing
    mmp_sem_t flag_command_gate;
    mmp_mutex_t state_change_mutex;
    barrier_t state_barrier;
    //  command gate END

    // command notify semaphore
    mmp_sem_t *event_cb;

    int use_timeout_sem;

    player_thread_st audio_thread;
    player_thread_st video_thread;
    player_thread_st demux_thread;
    player_thread_st vout_thread;
    player_thread_st *open_thread;

    int priority_state;

    int64_t pre_clock_base;

    uint16_t status;
    uint32_t last_audio_volume;
    mmp_notify_cb *notify_cb;
    mmp_sem_t *notify_sem;
    int        notify_msg;
#ifdef DEMUX_DROPTOI
    int audio_duration_threshold;
#endif

#ifdef SUPPORT_KMV
    unsigned int m_KMV_type;
#endif // SUPPORT_KMV

#ifdef SUPPORT_SUBTITLE
    SubParser_st *subpar;
#endif
} mp4player;

int fnMP4Player_Open(void *pInst);
int fnMP4Player_Close(void *pInst);
int fnMP4Player_Play(void *pInst, int32_t play_flag);
int fnMP4Player_Pause_Continue(void *pInst, int pause_cmd);
int fnMP4Player_SetPos(void *pInst, int32_t pi32Pos, int8_t flag);
int fnMP4Player_Stop(void *pInst);
int fnMP4Player_GetPos(void *pInst, uint32_t *pu32Pos);
int fnMP4Player_CancelSeek(void *pInst);
int fnMP4Player_SetTrack(void *pInst, int track_type, int track_id);
int fnMP4Player_SetSpeed(void *pInst, uint16_t speed_percent);
int fnMP4Player_GetSpeed(void *pInst, uint16_t *speed_percent);
int fnMP4Player_SetDispInfo(void *pInst, MMP_VO_SETTING *setting);
int fnMP4Player_SetThreadNum(void *pInst);

int is_supported_clip(mp4player *player);
int is_seeking(mp4player *player);
int player_create_thread(void *player, player_thread_st *thread, int priority, void *entry, void *data, char *name, int stack_size, mmp_thread_release_cb *release_cb, void *cb_par);
int player_destroy_thread(void *player, player_thread_st *thread, int no_timeout);

void player_init_context(mp4player *player, MMP_PLAY_MODE mode, KMV_info *movie_king_info);
int player_open_demuxer(mp4player *player, struct cb_io_s *cbio, KMV_info *movie_king_info);
int player_open_audio(mp4player *player, int mode);
int player_open_video(mp4player *player);
void player_seek_complete(mp4player *player, int av_done);

#endif // MP4PLAYER_H
