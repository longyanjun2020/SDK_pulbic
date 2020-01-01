#ifndef TS_H
#define TS_H

//#include <stdint.h>
//#include "streaming.h"

#define MVC_MAX_SERVICE_NAME_LEN        (50)
#define MVC_MAX_EVENT_NAME_LEN          (30)

typedef enum mvc_ts_type_e
{
    MVC_TS_PTS,
    MVC_TS_DTS,
} mvc_ts_type_et;

typedef struct mvc_data_info_s
{
    int length;
    unsigned char *payload;
} mvc_data_info_st;

typedef struct mvc_clip_info_s
{
    int seekable;
    int num_program;
    int active_program;
    mvc_ts_type_et ts_type;
} mvc_clip_info_st;

typedef struct mvc_program_info_s
{
    s64 duration;
    int num_video_streams;
    int num_audio_streams;
    int num_subtitle_streams;
    int active_video;
    int active_audio;
    int active_subtitle;
    mvc_data_info_st private_data;
} mvc_program_info_st;

typedef struct mvc_audio_info_s
{
    int codec;
    int sample_rate;
    int bit_rate;
    int channel_num;
    int config_len;
    unsigned char *config;
} mvc_audio_info_st;

typedef struct mvc_video_info_s
{
    int codec;
    int width;
    int height;
    int frame_rate_num;
    int frame_rate_den;
    int bit_rate;
    int config_len;
    unsigned char *config;
} mvc_video_info_st;

typedef struct mvc_service_info_s
{
    int service_id;
    int virtual_channel_num_high;
    int virtual_channel_num_low;
    int service_name_len;
    char service_name[MVC_MAX_SERVICE_NAME_LEN];
} mvc_service_info;

typedef struct mvc_EIT_info_s
{
    int     event_id;
    int     running_status;
    s64 start_time;
    int     duration;
    int     event_name_len;
    char    event_name[MVC_MAX_EVENT_NAME_LEN];
} mvc_EIT_info;

typedef struct mvc_EPG_info_s
{
    int service_num;
    mvc_service_info *service_info;
    int event_num;
    mvc_EIT_info *EIT_info;
} mvc_EPG_info;


#endif /* TS_H */
