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


#ifndef MMP_INFO_H
#define MMP_INFO_H

#include "avp_ms_io.h"

enum MMP_TIMESTAMP_TYPE
{
    MMP_PTS_TYPE = 0,
    MMP_DTS_TYPE,
};

enum MMP_PLAY_SPEED
{
    SPEED_50_PERCENT = 50,
    SPEED_100_PERCENT = 100,
    SPEED_200_PERCENT = 200,
    SPEED_400_PERCENT = 400,
};

typedef enum MMP_ROTATE_ANGLE_TYPE {
    MMP_ROTATE_0 = 0,
    MMP_ROTATE_90,
    MMP_ROTATE_180,
    MMP_ROTATE_270
} MMP_ROTATE_MODE;

#define INPUT_INFO_MAX_SUBTITLE_NUM         (5)
#define INPUT_INFO_MAX_SUB_NAME_LEN         (32)

#define MMP_MAX_AUDIO_TRACK_NUM             (10)

typedef struct mmp_esg_info_s {
    unsigned char *payload; // do not need to allocate memory to it.
    unsigned int  length;
    unsigned char valid;
} mmp_esg_info_st;

typedef struct mmp_sub_desc_s {
    int id;
    ms_fnchar language[INPUT_INFO_MAX_SUB_NAME_LEN];
} mmp_sub_desc_st;

typedef struct mmp_sub_info_s {
    int num;
    int selected_id;
    mmp_sub_desc_st sub[INPUT_INFO_MAX_SUBTITLE_NUM];
} mmp_sub_info_st;

typedef struct f_video_track_info_s {
    int num;
    int selected_id;
} f_video_track_info;

typedef struct mmp_audio_track_info_s
{
    int codec;
    int sample_rate;
    int bit_rate;
    int channel_num;
} mmp_audio_track_info;

typedef struct f_audio_track_info_s {
    int num;
    int selected_id;
    int curr_codec;
    int curr_sample_rate;
    mmp_audio_track_info aud_track[MMP_MAX_AUDIO_TRACK_NUM];
} f_audio_track_info;

#define KMV_NAME_LEN (120)
#define KMV_STARRING_LEN (200)
#define KMV_SYNOPSIS_LEN (800)
#define KMV_COVER_LEN (16 * 1024)

typedef struct KMV_info_s {
    unsigned char name[KMV_NAME_LEN];
    unsigned short duration;
    unsigned short year;
    unsigned char starring[KMV_STARRING_LEN];
    unsigned char synopsis[KMV_SYNOPSIS_LEN];
    unsigned int category;
    unsigned int byteLength;
    unsigned char cover[KMV_COVER_LEN];
} KMV_info;

typedef struct video_info_s {
    unsigned int u32duration;
    unsigned short stream_width;
    unsigned short stream_height;
    unsigned int samplerate;
    unsigned int channel_info;
    unsigned int u32V_AveBitrate;
    unsigned int u32A_AveBitrate;
    unsigned int framerate;
    unsigned int ave_sync_sample;
    unsigned int max_allowed_play_speed;
    int file_seekable;
    int multi_program;
    unsigned int max_video_biterate;
    unsigned int max_audio_biterate;
    unsigned int max_framerate;
    unsigned int avg_framerate;
    unsigned int disp_framerate;
    unsigned int avg_frame_duration;
    unsigned char ts_type; //0:pts 1:dts
    mmp_esg_info_st     esg_data;
    mmp_sub_info_st     sub_info;
    f_video_track_info  v_track_info;
    f_audio_track_info  a_track_info;
    int audec_status; // use MSMERR_OK
    int videc_status; // use MSMERR_OK
    unsigned int video_type_4cc;
    unsigned int audio_type_4cc;
    MMP_ROTATE_MODE rotate_mode;
    unsigned int maced;
    int file_type;

    // movie king
    KMV_info *movie_king_info;
    int       kmv_type;
} video_info;

typedef struct audio_info_s {
    unsigned int u32SamplRate;
    unsigned int u32BitRate;
    unsigned char u8BitRateType;
    unsigned char u8Channel_info;
    unsigned int u32TotalTime;
    unsigned int u32filesize;
} audio_info;

typedef struct mmp_file_info_s {
    int          audio_player;
    unsigned int duration;
    union {
        video_info vid;
        audio_info aud;
    } info;
} mmp_file_info;

typedef struct mmp_disp_info_s {
    unsigned short u16Width;
    unsigned short u16Height;
    unsigned short u16FrameRate;
    unsigned short  u16temp;

    unsigned char bInterlace;
    unsigned char   par_width;
    unsigned char   par_height;
    int             videc_type;
} mmp_disp_info_st;

#endif /* MMP_INFO_H */
