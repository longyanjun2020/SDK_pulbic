////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 MStar Semiconductor, Inc.
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

#ifndef MDL_AVP_STREAMING_INTERFACE_H
#define MDL_AVP_STREAMING_INTERFACE_H

#ifdef __RTK_OS__
typedef u16Char ms_fnchar;
#else
#include "avp_ms_io.h"
#endif

#include <stdint.h>

#define STREAM_MAX_PATH 250

enum
{
    //cmd: MDL streaming control -> download module
    MDL_AVP_STREAMING_CMD_NONE = 0x1000,                                                    //0x1000
    MDL_AVP_STREAMING_CMD_OPEN,    //open data link                                         //0x1001
    MDL_AVP_STREAMING_CMD_CLOSE,   //close data link                                        //0x1002
    MDL_AVP_STREAMING_CMD_INIT,    //init download module handle                            //0x1003
    MDL_AVP_STREAMING_CMD_UNINIT,  //uninit download module handle                          //0x1004
    MDL_AVP_STREAMING_CMD_PLAY,    //play one url                                           //0x1005
    MDL_AVP_STREAMING_CMD_STOP,    //stop play one url                                      //0x1006
    MDL_AVP_STREAMING_CMD_PAUSE,                                                            //0x1007
    MDL_AVP_STREAMING_CMD_RESUME,                                                           //0x1008
    MDL_AVP_STREAMING_CMD_SEEK,                                                             //0x1009
    MDL_AVP_STREAMING_CMD_DATA_CONSUMED,                                                    //0x100a
    MDL_AVP_STREAMING_CMD_GET_DATA,                                                         //0x100b
    MDL_AVP_STREAMING_CMD_SEND_RTCP,                                                        //0x100c

    //internal DM cmd: MDL streaming control -> MDL streaming control
    MDL_AVP_STREAMING_INT_CMD_PLAY = 0X2000,                                                //0x2000
    MDL_AVP_STREAMING_INT_CMD_PAUSE,                                                        //0x2001
    MDL_AVP_STREAMING_INT_CMD_RESUME,                                                       //0x2002
    MDL_AVP_STREAMING_INT_CMD_UNINIT,                                                       //0x2003
    MDL_AVP_STREAMING_INT_CMD_UPDATE_DWN_POS,                                               //0x2004
    MDL_AVP_STREAMING_INT_CMD_STOP,                                                         //0x2005
    MDL_AVP_STREAMING_INT_CMD_NETWORK_CONNECTION_FAIL,                                      //0x2006
    MDL_AVP_STREAMING_INT_CMD_DATA_IN,                                                      //0x2007

    //cmd: avp_handle-> MDL streaming control
    MDL_AVP_STREAMING_AVP_CMD_PLAY = 0x3000,                                                //0x3000
    MDL_AVP_STREAMING_AVP_CMD_PAUSE,                                                        //0x3001
    MDL_AVP_STREAMING_AVP_CMD_RESUME,                                                       //0x3002
    MDL_AVP_STREAMING_AVP_CMD_SEEK,                                                         //0x3003
    MDL_AVP_STREAMING_AVP_CMD_STOP,                                                         //0x3004

    //response: download module -> MDL streaming control
    MDL_AVP_STREAMING_RSP_OPEN = 0x4000,                                                    //0x4000
    MDL_AVP_STREAMING_RSP_CLOSE,                                                            //0x4001
    MDL_AVP_STREAMING_RSP_INIT,                                                             //0x4002
    MDL_AVP_STREAMING_RSP_UNINIT,                                                           //0x4003
    MDL_AVP_STREAMING_RSP_PLAY,                                                             //0x4004
    MDL_AVP_STREAMING_RSP_STOP,                                                             //0x4005
    MDL_AVP_STREAMING_RSP_PAUSE,                                                            //0x4006
    MDL_AVP_STREAMING_RSP_RESUME,                                                           //0x4007
    MDL_AVP_STREAMING_RSP_SEEK,                                                             //0x4008
    MDL_AVP_STREAMING_RSP_GET_DATA,                                                         //0x4009

    //event: download module -> MDL streaming control
    //       MDL streaming control -> avp_handle
    //       MDL streaming control -> MDL streaming control
    MDL_AVP_STREAMING_EVENT_OPEN_FAIL = 0x5000,                                             //0x5000
    MDL_AVP_STREAMING_EVENT_OPEN_COMPLETE,                                                  //0x5001
    MDL_AVP_STREAMING_EVENT_CLOSE_FAIL,                                                     //0x5002
    MDL_AVP_STREAMING_EVENT_CLOSE_COMPLETE,                                                 //0x5003
    MDL_AVP_STREAMING_EVENT_INIT_FAIL,                                                      //0x5004
    MDL_AVP_STREAMING_EVENT_INIT_COMPLETE,                                                  //0x5005
    MDL_AVP_STREAMING_EVENT_UNINIT_FAIL,                                                    //0x5006
    MDL_AVP_STREAMING_EVENT_UNINIT_COMPLETE,                                                //0x5007
    MDL_AVP_STREAMING_EVENT_PLAY_FAIL,                                                      //0x5008
    MDL_AVP_STREAMING_EVENT_PLAY_COMPLETE,                                                  //0x5009
    MDL_AVP_STREAMING_EVENT_STOP_FAIL,                                                      //0x500a
    MDL_AVP_STREAMING_EVENT_STOP_COMPLETE,                                                  //0x500b
    MDL_AVP_STREAMING_EVENT_PAUSE_FAIL,                                                     //0x500c
    MDL_AVP_STREAMING_EVENT_PAUSE_COMPLETE,                                                 //0x500d
    MDL_AVP_STREAMING_EVENT_RESUME_FAIL,                                                    //0x500e
    MDL_AVP_STREAMING_EVENT_RESUME_COMPLETE,                                                //0x500f
    MDL_AVP_STREAMING_EVENT_SEEK_FAIL,                                                      //0x5010
    MDL_AVP_STREAMING_EVENT_SEEK_COMPLETE,                                                  //0x5011
    MDL_AVP_STREAMING_EVENT_GET_DATA_FAIL,                                                  //0x5012
    MDL_AVP_STREAMING_EVENT_GET_DATA_COMPLETE,                                              //0x5013
    MDL_AVP_STREAMING_EVENT_DATA_IN,                                                        //0x5014
    MDL_AVP_STREAMING_EVENT_DATA_EOS,                                                       //0x5015
    MDL_AVP_STREAMING_EVENT_STORAGE_FULL,                                                   //0x5016
    MDL_AVP_STREAMING_EVENT_NETWORK_DISCONNECTED,                                           //0x5017
    MDL_AVP_STREAMING_EVENT_NETWORK_CONNECTION_FAIL,                                        //0x5018: 1. Not receiving network data for a while
    MDL_AVP_STREAMING_EVENT_NETWORK_OPERATION_FAIL,                                         //0x5019: 1. TCP disconneced from server 2. Only receiving audio or video payload in 10s after MDL_AVP_STREAMING_EVENT_PLAY_COMPLETE.
    MDL_AVP_STREAMING_EVENT_UPDATE_DOWNLOAD_POS,                                            //0x501a
};

enum
{
    MDL_AVP_STREAMING_SEEK_BY_BYTE,
    MDL_AVP_STREAMING_SEEK_BY_TIME,
};

enum
{
    MDL_AVP_STREAMING_POS_END_OF_STREAM = -1,
    MDL_AVP_STREAMING_POS_START_OF_STREAM,
};

enum
{
    MDL_AVP_STREAMING_NETWORK_HTTP,
    MDL_AVP_STREAMING_NETWORK_RTSP,
};

enum
{
    MDL_AVP_STREAMING_FILE_MODE,
    MDL_AVP_STREAMING_MEMORY_MODE,
};

enum
{
    MDL_AVP_STREAMING_DATALINK_WIFI,
    MDL_AVP_STREAMING_DATALINK_SIM1,
    MDL_AVP_STREAMING_DATALINK_SIM2,
};

typedef int avp_vfs_rebuffer_cb(void *stm_handle, int size);
typedef int avp_vfs_rebuffer_done_cb(void *stm_handle);
typedef int avp_vfs_rebuffer_stop_cb(void *stm_handle);
typedef int avp_vfs_seek_cb(void *stm_handle, int id, int seek_pos);

typedef int avp_send_msg_to_avp_cb(int message_type, int data_size, void *data);
typedef int avp_send_msg_to_dm_cb(int message_type, int data_size, void *data);
typedef int avp_send_msg_to_stm_cb(void *stm_ctx, int message_type, int data_size, void *data);

//data: avp -> download module
typedef struct avp_streaming_avp_to_dm_open_data_s
{
    avp_send_msg_to_avp_cb *send_msg_to_avp;
    int data_link_type;
} avp_streaming_avp_to_dm_open_data_st;

//data: MDL streaming control -> download module
typedef struct avp_streaming_stm_to_dm_init_data_s
{
    void *streaming_handle;
    int min_queue_size;
    avp_send_msg_to_stm_cb *send_msg_to_stm;
} avp_streaming_stm_to_dm_init_data_st;

typedef struct avp_streaming_stm_to_dm_uninit_data_s
{
    void *download_module_handle;
} avp_streaming_stm_to_dm_uninit_data_st;

typedef struct avp_streaming_stm_to_dm_play_data_s
{
    void *download_module_handle;
    ms_fnchar play_url[STREAM_MAX_PATH];
    int seek_type;
    int start_pos;
    int end_pos;
    int enable_audio;
    int enable_video;
} avp_streaming_stm_to_dm_play_data_st;

typedef struct avp_streaming_stm_to_dm_stop_data_s
{
    void *download_module_handle;
} avp_streaming_stm_to_dm_stop_data_st;

typedef struct avp_streaming_stm_to_dm_pause_data_s
{
    void *download_module_handle;
} avp_streaming_stm_to_dm_pause_data_st;

typedef struct avp_streaming_stm_to_dm_resume_data_s
{
    void *download_module_handle;
} avp_streaming_stm_to_dm_resume_data_st;

typedef struct avp_streaming_stm_to_dm_seek_data_s
{
    void *download_module_handle;
    int seek_type;
    int seek_pos;
} avp_streaming_stm_to_dm_seek_data_st;

typedef struct avp_streaming_stm_to_dm_data_consumed_data_s
{
    void *download_module_handle;
    void *data_ptr;
    int  data_size;
} avp_streaming_stm_to_dm_data_consumed_data_st;

//data: download module -> MDL streaming control
typedef struct avp_streaming_dm_to_stm_init_complete_data_s
{
    void *download_module_handle;
} avp_streaming_dm_to_stm_init_complete_data_st;

typedef struct avp_streaming_http_pos_info_s
{
    int start_pos;
} avp_streaming_http_pos_info_st;

typedef struct avp_streaming_rtsp_pos_info_s
{
    uint32_t start_pos;
    uint32_t audio_start_seq_num;
    uint32_t audio_start_timestamp;
    uint32_t video_start_seq_num;
    uint32_t video_start_timestamp;
} avp_streaming_rtsp_pos_info_st;

typedef struct avp_streaming_dm_to_stm_play_complete_data_s
{
    int file_size;
    int enable_audio;
    int enable_video;
    union
    {
        avp_streaming_http_pos_info_st http_pos_info;
        avp_streaming_rtsp_pos_info_st rtsp_pos_info;
    } pos_info;
} avp_streaming_dm_to_stm_play_complete_data_st;

typedef struct avp_streaming_dm_to_stm_seek_complete_data_s
{
    union
    {
        avp_streaming_http_pos_info_st http_pos_info;
        avp_streaming_rtsp_pos_info_st rtsp_pos_info;
    } pos_info;
} avp_streaming_dm_to_stm_seek_complete_data_st;

typedef struct avp_streaming_dm_to_stm_resume_complete_data_s
{
    union
    {
        avp_streaming_http_pos_info_st http_pos_info;
        avp_streaming_rtsp_pos_info_st rtsp_pos_info;
    } pos_info;
} avp_streaming_dm_to_stm_resume_complete_data_st;

typedef struct avp_streaming_dm_to_stm_data_in_data_s
{
    int data_size;
    void *data;
    int start_pos;
} avp_streaming_dm_to_stm_data_in_data_st;


//data: avp_handle -> MDL streaming control
typedef struct avp_streaming_avp_to_stm_play_data_s
{
    void *streaming_handle;
    ms_fnchar play_url[STREAM_MAX_PATH];
    ms_fnchar store_url[STREAM_MAX_PATH];
    avp_vfs_rebuffer_cb      *rb_cb;
    avp_vfs_rebuffer_done_cb *rb_done_cb;
    avp_vfs_rebuffer_stop_cb *rb_stop_cb;
    avp_vfs_seek_cb          *seek_cb;
} avp_streaming_avp_to_stm_play_data_st;

typedef struct avp_streaming_avp_to_stm_seek_data_s
{
    int session_id;
    int seek_pos;
} avp_streaming_avp_to_stm_seek_data_st;

//data: MDL streaming control -> avp_handle
typedef struct avp_streaming_stm_to_avp_play_complete_data_s
{
    void *stm_handle;
    int file_size;
    uint32_t read_handle;
    int enable_audio;
    int enable_video;
} avp_streaming_stm_to_avp_play_complete_data_st;

typedef struct avp_streaming_stm_to_avp_stop_complete_data_s
{
    void *stm_handle;
} avp_streaming_stm_to_avp_stop_complete_data_st;

typedef struct avp_streaming_stm_to_avp_download_pos_data_s
{
    //unit: ms
    int start_time;
    int end_time;
} avp_streaming_stm_to_avp_download_pos_data_st;

int MDLAvpStreamingSendMsgToStm(void *stm_ctx, int message_type, int data_size, void *data);

#ifdef _MSC_VER
typedef int   avp_download_module_open(avp_send_msg_to_avp_cb *send_msg_to_avp);
typedef int   avp_download_module_close(void);
typedef int   avp_download_module_init(void *stm_ctx, int min_queue_size, avp_send_msg_to_stm_cb *send_msg_to_stm, avp_streaming_dm_to_stm_init_complete_data_st *dm_init_complete_data);
typedef int   avp_download_module_uninit(void **ctx);
typedef int   avp_download_module_play(void *ctx, const ms_fnchar *play_url, int seek_type, int start_pos, int end_pos, int enable_audio, int enable_video, avp_streaming_dm_to_stm_play_complete_data_st *dm_play_complete_data);
typedef int   avp_download_module_stop(void *ctx);
typedef int   avp_download_module_pause(void *ctx);
typedef int   avp_download_module_resume(void *ctx);
typedef int   avp_download_module_seek(void *ctx, int seek_type, int seek_pos, avp_streaming_dm_to_stm_seek_complete_data_st *dm_seek_complete_data);

int write_one_dm_msg(int message_type, int data_size, void* data);
int close_download_module_thread(void **dm_handle_p);
void* start_download_module_thread(int network_streaming_type, avp_send_msg_to_avp_cb *send_msg_to_avp, avp_send_msg_to_stm_cb *send_msg_to_stm);
#endif

#endif

