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

#ifndef STREAMING_STRUCT_H
#define STREAMING_STRUCT_H

#include <stdint.h>
#include "avp_vfs_api.h"
#include "mdl_avp_streaming_interface.h"

#define STREAMING_THREAD_STACK_SIZE      (10*1024)
#define STREAM_MAX_MSG_NUM               (100)
#define STREAM_DM_DATA_BUF_SIZE          (10*1024)
#define STREAM_MAX_QUEUE_DATA_IN_SIZE    (30*1024)

typedef struct stm_msg_record_st
{
    uint16_t idx;
    uint16_t msg;
} stm_msg_record;

typedef struct streaming_inst_st
{
    uint32_t write_handle;
    uint32_t read_handle;
    mmp_thread_inst thread_handle;
    uint8_t stack[STREAMING_THREAD_STACK_SIZE];

    int record_idx;
    stm_msg_record msg_table[STREAM_MAX_MSG_NUM];

    int total_write_size;
    int session_write_size;
    int seek_pos;
    int data_eos;
    void *download_module_handle;
    int session_id;
    int data_dirty;
    int play_retry_count;
    int connect_fail_retry_count;
    int need_retry_play;
    uint8_t memory_full;

    avp_vfs_rebuffer_cb      *rb_cb;
    avp_vfs_rebuffer_done_cb *rb_done_cb;
    avp_vfs_rebuffer_stop_cb *rb_stop_cb;
    avp_vfs_seek_cb          *seek_cb;

    int network_streaming_type;
    int vfs_streaming_type;
    int seek_type;
    int total_memory_size;

    avp_send_msg_to_avp_cb *send_msg_to_avp;   //send message to avp_handle
    avp_send_msg_to_dm_cb *send_msg_to_dm; //send message to download module
    avp_send_msg_to_stm_cb *send_msg_to_stm; //send message to stm (streaming control thread)

    //for RTSP usage
    int have_rtp_info;
    uint32_t play_start_pos;
    int audio_id;
    int video_id;
    uint32_t audio_pts_freq;
    uint32_t video_pts_freq;
    uint32_t audio_start_timestamp;
    uint32_t video_start_timestamp;
    uint32_t audio_start_seq_num;
    uint32_t video_start_seq_num;
    int rtsp_check_old_audio_data;
    int rtsp_check_old_video_data;
    uint32_t last_drop_pkt_org_timestamp;
    uint32_t last_drop_pkt_output_pts;
    int write_SDP_done;
    int need_write_rtp_info;
    int64_t init_start_time;

    //used for store new DM data
    uint8_t dm_data_buf[STREAM_DM_DATA_BUF_SIZE];
    int dm_data_size;

    //data to download module
    ms_fnchar store_url[STREAM_MAX_PATH];
    avp_streaming_stm_to_dm_init_data_st          init_data;
    avp_streaming_stm_to_dm_uninit_data_st        uninit_data;
    avp_streaming_stm_to_dm_play_data_st          play_data;
    avp_streaming_stm_to_dm_pause_data_st         pause_data;
    avp_streaming_stm_to_dm_resume_data_st        resume_data;
    avp_streaming_stm_to_dm_stop_data_st          stop_data;
    avp_streaming_stm_to_dm_seek_data_st          seek_data;
    avp_streaming_stm_to_dm_data_consumed_data_st consume_data;

    //data to avp_handle
    avp_streaming_stm_to_avp_play_complete_data_st play_complete_data;
    avp_streaming_stm_to_avp_download_pos_data_st  download_pos_data;

    //data to stm
    avp_streaming_avp_to_stm_seek_data_st         queue_avp_seek_data;

    avp_streaming_dm_to_stm_data_in_data_st       queue_dm_data_in;

    int (*fp_write_data)(void *s_handle, int start_offset, int data_size, uint8_t *data);

#ifdef ENABLE_DOWNLOAD_MODULE_THREAD
    struct ringbuffer mbx_ringbuf;
    uint8_t mbx_buffer[2*1024];
#endif

} streaming_inst;


#endif

