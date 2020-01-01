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

#ifndef STREAMING_INPUT_H
#define STREAMING_INPUT_H

#include <stdint.h>
#include "avp_ms_io.h"
#include "avp_ms_input.h"
#include "mdl_avp_streaming_interface.h"

typedef int  vfs_rebuffer_cb(void *stm_handle, int size);
typedef int  vfs_rebuffer_done_cb(void *stm_handle);
typedef int  vfs_rebuffer_stop_cb(void *stm_handle);
typedef int  vfs_seek_cb(void *stm_handle, int id, int seek_byte);

typedef struct streaming_cbio_s
{
    //public handle
    cb_io_st    read_handle;
    cb_io_st    write_handle;

    uint8_t     read_handle_in_use;
    uint8_t     write_handle_in_use;

    //private handle: the read/write handle of file1/file2
    cb_io_st    read_ctx[2];
    cb_io_st    write_ctx[2];

    //store the absolute file offset
    int         read_pos[2];
    int         write_pos[2];

    //the absolute file offset of the first byte in file1/file2 for read pointer
    int         first_byte_offset_read[2];

    //the absolute file offset of the first byte in file1/file2 for write pointer
    int         first_byte_offset_write[2];

    //store the max_size of mem1/mem2
    int         max_size[2];

    uint8_t     *mem[2];

    int         active_read_index;
    int         active_write_index;

    int         file_size;
    uint8_t     streaming_type;
    uint8_t     network_type;

    int         new_active_write_index;
    int         new_first_byte_offset_write;

    //the absolute file offset of the seek byte
    int         new_write_pos;

    int         new_active_read_index;
    int         new_first_byte_offset_read;
    int         new_read_pos;

    vfs_rebuffer_cb      *rebuffer_cb;
    vfs_rebuffer_done_cb *rebuffer_done_cb;
    vfs_rebuffer_stop_cb *rebuffer_stop_cb;
    vfs_seek_cb          *seek_cb;

    //rebuffer state related fields
    int         cur_rebuffer_size;
    int         req_rebuffer_size;
    int         cb_status;
    uint8_t     enter_rebuffer;
    uint8_t     enter_seek_cb;
    uint8_t     ring_wait_free_size;
    uint8_t     stop_lock_wait;
    uint8_t     storage_full;
    int         network_error;
    uint8_t     seek_type;
    int         seek_time;
    int         seek_notify_offset;
    uint8_t     seek_notify_type;
    uint8_t     need_invalidate_read_cache;
    uint8_t     sequential_download_only;

    //session ID related fields
    uint32_t    active_session_id;
    uint32_t    pre_active_session_id;
    uint32_t    active_session_count;

    int         metadata_size;
    int         file_bitrate; //file bitrate
    int         bitrate;      //real input bitrate
    uint32_t    duration;
    int         first_download_byte;

    uint8_t     write_memory_full;

    //RTSP usage
    int         audio_id;
    int         video_id;
    uint32_t    sdp_size;

    uint32_t    video_pts_freq;
    uint32_t    audio_pts_freq;

    uint64_t    video_base_pts;
    uint64_t    audio_base_pts;

    uint64_t    video_output_base_pts;
    uint64_t    audio_output_base_pts;

    uint64_t    video_internal_base_pts;
    uint64_t    audio_internal_base_pts;

    uint64_t    last_write_org_video_pts;
    uint64_t    last_write_org_audio_pts;

    uint64_t    last_write_video_pts;
    uint64_t    last_write_audio_pts;

    uint64_t    last_read_video_pts;
    uint64_t    last_read_audio_pts;

    uint64_t    write_video_pts_diff;
    uint64_t    write_audio_pts_diff;

    uint32_t    last_drop_pkt_pts;

    uint32_t    last_dwn_end_time; //unit: ms
    int         last_read_size;
    int         play_start_pos;    //RTSP: ms, HTTP: byte

    int         enable_audio;
    int         enable_video;

    void        *stm_handle; //streaming control thread handle
    void        *player;
    ms_fnchar   *file_name2;
} streaming_cbio_st;

int     vfs_streaming_close(cb_io_st **read_handle, cb_io_st **write_handle);
void    vfs_streaming_close_handle(cb_io_st **ctx);
void    vfs_streaming_close_player(cb_io_st *ctx);
int     vfs_streaming_file_open(void *stm_handle, const ms_fnchar *file_name, int file_size, int *first_download_byte, cb_io_st **read_handle, cb_io_st **write_handle);
int     vfs_streaming_get_download_timestamp(cb_io_st *ctx, int pos);
int     vfs_streaming_get_network_type(cb_io_st *ctx);
int     vfs_streaming_get_status(cb_io_st *ctx);
int     vfs_streaming_read_init(cb_io_st *ctx);
cb_fpos vfs_streaming_read_data(cb_io_st *ctx, void *buf, int size);
cb_fpos vfs_streaming_read_seek(cb_io_st *ctx, int offset, int whence);
int     vfs_streaming_read_seek_time(cb_io_st *ctx, int seek_time);
void    vfs_streaming_reg_cb(cb_io_st *ctx, vfs_rebuffer_cb *rb_cb, vfs_rebuffer_done_cb *rb_done_cb, vfs_rebuffer_stop_cb *rb_stop_cb, vfs_seek_cb *seek_cb);
void    vfs_streaming_set_player_info(cb_io_st *ctx, void *player);
int     vfs_streaming_stop_rebuffer(cb_io_st *ctx);
int     vfs_streaming_notify_network_error(cb_io_st *ctx);
cb_fpos vfs_streaming_tell(cb_io_st *ctx);
int     vfs_streaming_update_file_size(cb_io_st *ctx, int file_size);
cb_fpos vfs_streaming_write_data(cb_io_st *ctx, void *buf, int size);
void    vfs_streaming_write_data_eof(cb_io_st *ctx);
cb_fpos vfs_streaming_write_seek(cb_io_st *ctx, int offset, int whence);

void *start_streaming_control_thread(int network_streaming_type, int vfs_streaming_type, avp_send_msg_to_avp_cb *send_msg_to_player_handle_cb, avp_send_msg_to_dm_cb *send_msg_to_download_module_cb);
int close_streaming_control_thread(void **streaming_handle);

#ifdef _MSC_VER
void send_rtcp_msg_to_dm(void *data);
#endif

#endif

