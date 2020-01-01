#ifndef TS_H
#define TS_H

#include <stdint.h>
#include "avp_streaming.h"
#include "avp_mvc_info.h"
#include "avp_mvc_demuxer.h"

#define MAX_PROGRAM_NUM 100
#define MAX_PACKET_SIZE 208
#define MAX_STREAM_NUM  64

#define PES_STREAM_ID_PROGRAM_STREAM_MAP        (0xBC)
#define PES_STREAM_ID_PRIVATE_STREAM_1          (0xBD)
#define PES_STREAM_ID_PADDING_STREAM            (0xBE)
#define PES_STREAM_ID_PRIVATE_STREAM_2          (0xBF)
#define PES_STREAM_ID_ECM_STREAM                (0xF0)
#define PES_STREAM_ID_EMM_STREAM                (0xF1)
#define PES_STREAM_ID_PROGRAM_STREAM_DIRECTORY  (0xFF)
#define PES_STREAM_ID_DSMCC_STREAM              (0xF2)
#define PES_STREAM_ID_H222_1_TYPE_E_STREAM      (0xF8)

#define TS_PID_PAT                              (0)
#define TS_PID_CAT                              (0x1)
#define TS_PID_TSDT                             (0x2)
#define TS_PID_IPMP_CIT                         (0x3)
#define TS_PID_NULL_PACKET                      (0x1fff)
#define TS_PID_NIT                              (0x10)
#define TS_PID_SDT                              (0x11)
#define TS_PID_EIT                              (0x12)
#define TS_PID_TOT                              (0x14)
#define TS_PID_PMT                              (-1)
#define TS_PID_ONE_SEG_PMT                      (0x1fc8)
#define TS_PID_ONE_SEG_EIT                      (0x27)

#define TS_PROGRAM_ID_NIT                       (0)

#define TS_TABLE_ID_EIT_ACTUAL_PRESENT          (0x4e)
#define TS_TABLE_ID_EIT_ACTUAL_SCHEDULE_START   (0x50)
#define TS_TABLE_ID_EIT_ACTUAL_SCHEDULE_END     (0x5f)
#define TS_TABLE_ID_STUFFING                    (0xff)

#define TS_AUDIO_TYPE                           (0)
#define TS_VIDEO_TYPE                           (1)
#define TS_SUBTITLE_TYPE                        (2)

#define TS_MAX_FRAME_TYPE_NUM                   (2)
#define TS_MAX_QUEUE_NUM                        (2)
#define TS_MAX_SERVICE_NUM                      (5)
#define TS_MAX_NETWORK_NUM                      (2)
#define TS_MAX_EVENT_NUM_PER_SERVICE            (15)
#define TS_MAX_SERVICE_PROVIDER_NAME_LEN        (50)
#define TS_MAX_SERVICE_NAME_LEN                 (50)
#define TS_MAX_SERVICE_LIST_NUM                 (20)
#define TS_MAX_NETWORK_NAME_LEN                 (40)
#define TS_MAX_EVENT_NAME_LEN                   (30)
#define TS_MAX_TEXT_CHAR_LEN                    (30)
#define TS_MAX_STREAM_NUM_PER_PROGRAM           (8)
#define TS_MAX_SECTION_SIZE                     (4096)
#define TS_MAX_PSI_PID_NUM                      (3)
#define TS_MAX_EIT_SCHEDULE_NUM                 (16)
#define TS_MAX_AUDIO_STREAM_NUM                 (5)
#define TS_MAX_VIDEO_STREAM_NUM                 (2)

#define TS_DESCRIPTOR_TAG_AC3_REGISTRATION_DESCRIPTOR (0x5)
#define TS_DESCRIPTOR_TAG_NETWORK_NAME          (0x40)
#define TS_DESCRIPTOR_TAG_SERVICE_LIST          (0x41)
#define TS_DESCRIPTOR_TAG_SERVICE               (0x48)
#define TS_DESCRIPTOR_TAG_SHORT_EVENT           (0x4d)
#define TS_DESCRIPTOR_TAG_COMPONENT             (0x50)
#define TS_DESCRIPTOR_TAG_STREAM_IDENTIFIER     (0x52)
#define TS_DESCRIPTOR_TAG_PARENTAL_RATING       (0x55)
#define TS_DESCRIPTOR_TAG_STUFFING              (0xff)
#define TS_DESCRIPTOR_TAG_TS_INFORMATION        (0xcd)

#define TS_STREAM_TYPE_11172_2                  (0x1)
#define TS_STREAM_TYPE_13818_2                  (0x2)
#define TS_STREAM_TYPE_11172_3                  (0x3)
#define TS_STREAM_TYPE_13818_3                  (0x4)
#define TS_STREAM_TYPE_PRIVATE                  (0x6)
#define TS_STREAM_TYPE_14496_2                  (0x10)
#define TS_STREAM_TYPE_LATM                     (0x11)
#define TS_STREAM_TYPE_AVC1                     (0x1b)
#define TS_STREAM_TYPE_ADTS                     (0xf)
#define TS_STREAM_TYPE_AC3                      (0x81)

typedef struct ts_PSI_section_common_field_s
{
    int table_id;
    int section_len;
    int id;
    int version_num;
    int current_next_indicator;
    int section_num;
    int last_section_num;
} ts_PSI_section_common_field;

typedef struct ts_frame_info_s {
    mvc_stream_type_et type;
    uint8_t *buffer;
    int   bufsize;
    int64_t pts;
    int   sync_frame_info;
} ts_frame_info;

typedef struct ts_audio_info {
    int   codec_type;
    int   freq_index;
    int   sample_rate;
    int   channle_num;
    int   bit_rate;
    int   object_index;
    int   frame_len;
    int   frame_type;
} ts_audio_info;

typedef struct ts_Table_common_s
{
    int total_entry;

    //curr paring section information
    int pid;
    int table_id;
    int id; //sevice_id(EIT), program_num_id(PMT)
    int version_num;
    int last_section_num;
    int curr_parsing_section_len;
    int curr_parsing_section_num;
    uint8_t *curr_parsing_section_payload;
    int last_parsed_section_num;
} ts_Table_common;

typedef struct ts_PAT_s
{
    ts_Table_common table_common;
    int pid[MAX_PROGRAM_NUM];
    int program_num_id[MAX_PROGRAM_NUM];
    int last_section_remain_len;
    int NIT_pid;
} ts_PAT;

typedef struct ts_service_descriptor_s
{
    int  service_type;
    int  service_provider_name_len;
    char service_provider_name[TS_MAX_SERVICE_PROVIDER_NAME_LEN];
    int  service_name_len;
    char service_name[TS_MAX_SERVICE_NAME_LEN];
} ts_service_descriptor;

typedef struct ts_SDT_element_s
{
    int service_id;
    int virtual_channel_num_high; //remote_control_key_id
    int virtual_channel_num_low; //service_type/service_num
    ts_service_descriptor service_descriptor;
} ts_SDT_element;

typedef struct ts_SDT_s
{
    ts_Table_common table_common;
    ts_SDT_element service[TS_MAX_SERVICE_NUM];
} ts_SDT;

typedef struct ts_elementary_stream_s
{
    int stream_type;
    int elementary_pid;
} ts_elementary_stream;

//per program structure
typedef struct ts_program_element_s
{
    int stream_num;
    ts_elementary_stream stream[TS_MAX_STREAM_NUM_PER_PROGRAM];
} ts_program_element;

typedef struct ts_PMT_s
{
    ts_Table_common table_common;
    ts_program_element program;
    int completion;
} ts_PMT;

typedef struct ts_PMT_set_s
{
    int PMT_num;
    ts_PMT PMT[MAX_PROGRAM_NUM];
} ts_PMT_set;

typedef struct ts_short_evnet_s
{
    int      ISO_639_language_code;
    uint8_t  event_name_length;
    char     event_name[TS_MAX_EVENT_NAME_LEN];
    //uint8_t  text_length;
    //char     text_char[TS_MAX_TEXT_CHAR_LEN];
} ts_short_event;

typedef struct ts_event_information_s
{
    int     service_id;
    int     table_id;
    int     version_num;
    int     section_num;
    int     event_id;
    int64_t start_time;
    int     duration;
    uint8_t running_status;
    ts_short_event short_event;
} ts_event_information;

typedef struct ts_EIT_element_s
{
    int service_id;
    int event_num;
    int first_event_index;
} ts_EIT_element;

typedef struct ts_EIT_s
{
    ts_Table_common table_common; //total_entry means the total_event_num
    int             in_use;
    ts_EIT_element  service;
} ts_EIT;

typedef struct ts_service_list_s
{
    int service_id;
    int service_type;
    int remote_control_key_id;
} ts_service_list;

typedef struct ts_NIT_element_s
{
    int             network_id;
    int             network_name_len;
    char            network_name[TS_MAX_NETWORK_NAME_LEN];
    int             service_num;
    ts_service_list service[TS_MAX_SERVICE_LIST_NUM];
} ts_NIT_element;

typedef struct ts_NIT_s
{
    ts_Table_common table_common;
    ts_NIT_element  network[TS_MAX_NETWORK_NUM];
} ts_NIT;

typedef struct ts_parental_ctl_info_s
{
    int country_code;
    int min_age;
} ts_parental_ctl_info;

typedef struct ts_PSI_section_payload_s
{
    int pid;
    int using;
    int section_len;
    int payload_size;
    uint8_t section[TS_MAX_SECTION_SIZE];
} ts_PSI_section_payload;

typedef struct ts_EPG_info_s
{
    int service_num;
    mvc_service_info service_info[TS_MAX_SERVICE_NUM];
    int event_num;
    mvc_EIT_info *EIT_info;
} ts_EPG_info;

typedef struct ts_EIT_service_s
{
    int service_id;
    int in_use;
    int present_version_num;
    int following_version_num;
    int schedule_version_num;
    int event_num;
    mvc_EIT_info event[TS_MAX_EVENT_NUM_PER_SERVICE];
} ts_EIT_service;

typedef struct ts_demuxer_s {
    uint8_t *heap;
    int64_t duration; //unit: us

    int64_t base_pts[TS_MAX_FRAME_TYPE_NUM];
    int64_t pts_queue[TS_MAX_FRAME_TYPE_NUM][TS_MAX_QUEUE_NUM];
    int     pts_queue_count[TS_MAX_QUEUE_NUM];
    int     sync_frame_info[TS_MAX_FRAME_TYPE_NUM][TS_MAX_QUEUE_NUM];
    int64_t sync_frame_pos[TS_MAX_FRAME_TYPE_NUM];

    int     seekable;
    int     packet_size;
    int     discontinuity;
    uint8_t buffer[2048];

    int     sel_program_service_id;
    int     sel_program_PID;
    int     sel_audio_PID;
    int     sel_video_PID;
    int     sel_subtitle_PID;
    int     sel_audio_stream_type;
    int     sel_video_stream_type;
    int     sel_audio_stream_index;
    int     sel_video_stream_index;
    int     all_audio_stream_index[TS_MAX_AUDIO_STREAM_NUM];
    int     all_video_stream_index[TS_MAX_VIDEO_STREAM_NUM];

    uint8_t pes_data_buffer[MAX_PACKET_SIZE];
    uint8_t *remain_buf[TS_MAX_FRAME_TYPE_NUM];
    int     remain_buf_size[TS_MAX_FRAME_TYPE_NUM];
    uint8_t *last_start_code_ptr[TS_MAX_FRAME_TYPE_NUM];
    uint8_t *last_search_ptr[TS_MAX_FRAME_TYPE_NUM];
    int     start_code_count[TS_MAX_FRAME_TYPE_NUM];
    int     last_start_code_type[TS_MAX_FRAME_TYPE_NUM];
    int     got_first_start_code[TS_MAX_FRAME_TYPE_NUM];
    int     got_config[TS_MAX_FRAME_TYPE_NUM];
    int     got_VOP_after_VOL;
    int64_t last_parsed_pts[TS_MAX_FRAME_TYPE_NUM];
    int64_t first_frame_pts[TS_MAX_FRAME_TYPE_NUM]; //the pts of the first output frame
    ts_audio_info last_audio_start_code_info;
    cb_buffer_st  cbuffer;

    int     PAT_completion;
    int     SDT_completion;
    int     NIT_completion;
    int     PMT_change;
    int     ts_info_descritpor_completion;
    ts_PAT  PAT;
    ts_PMT_set  PMT_set;
    ts_NIT  NIT;
    ts_SDT  SDT;
    ts_EIT  EIT_present;
    ts_EIT  EIT_following;
    ts_EIT  EIT_schedule[TS_MAX_EIT_SCHEDULE_NUM];
    int     one_event_valid;
    ts_event_information one_event;
    char    resync_flag;
    ts_parental_ctl_info parental_ctl_info;
    ts_PSI_section_payload PSI_section_set[TS_MAX_PSI_PID_NUM];

    int64_t last_frame_dur[TS_MAX_FRAME_TYPE_NUM];
    int64_t last_frame_org_pts[TS_MAX_FRAME_TYPE_NUM];
    int64_t last_frame_output_pts[TS_MAX_FRAME_TYPE_NUM];
    int     no_pts_frame_count[TS_MAX_FRAME_TYPE_NUM];
    int64_t output_base_pts[TS_MAX_FRAME_TYPE_NUM];
    ts_EPG_info  ts_epg;
    mvc_EPG_info mvc_epg;
    ts_EIT_service all_EIT_service[TS_MAX_SERVICE_NUM];
    int     scan_EPG;

    int     ac3_registration_descriptor_exist;
    int     num_audio_streams;
    int     num_video_streams;

    uint32_t file_size;
    int     bytes_per_second;
    int     store_file_pos; //to keep the file position of each pes_packet
    int     output_video_first;
    int     parse_header_only;

    int                 new_pts;
    mvc_allocator_st    allocator;
    void               *alloc_ctx;
    void               *mem_ctx;

    int                 last_pes_packet_data_size;
    struct {
        int pid;
        int counter;
    } stream_info[MAX_STREAM_NUM];
} ts_demuxer_st;

typedef struct ts_packet_s
{
    char  sync_byte;
    char  transport_error_indicator;
    char  payload_unit_start_indicator;
    char  transport_priority;
    short PID;
    char  transport_scrambling_control;
    char  adaptation_field_control;
    char  continuity_counter;
} ts_packet_st;

typedef struct ts_adaptation_field_s
{
#if 0
    uint8_t  adaptation_field_length;
    char     discontinuity_indicator;
    char     random_access_indicator;
    char     elementary_stream_priority_indicator;
    char     PCR_flag;
    char     OPCR_flag;
    char     splicing_point_flag;
    char     transport_private_data_flag;
    char     adaptation_field_extension_flag;
#endif
    uint64_t program_clock_reference_base;
    uint16_t program_clock_reference_extension;

    uint64_t original_program_clock_reference_base;
    uint16_t original_program_clock_reference_extension;
#if 0
    char     splice_countdown;

    uint8_t  transport_private_data_length;

    uint8_t  adaptation_field_extension_length;
    char     ltw_flag;
    char     piecewise_rate_flag;
    char     seamless_splice_flag;
    char     ltw_valid_flag;
    uint16_t ltw_offset;

    uint32_t piecewise_rate;

    char     splice_type;
    int64_t  DTS_next_AU;
#endif
} ts_adaptation_field_st;

typedef struct ts_PES_packet_s
{
    int      pid;
    int      stream_id;
    int      unit_start;
    int64_t  pts; //unit: us
    int64_t  dts; //unit: us
#if 0
    uint16_t PES_packet_length;
    char     PES_scrambling_control;
    char     PES_priority;
    char     data_alignment_indicator;
    char     copyright;
    char     original_or_copy;
    char     PTS_DTS_flags;
    char     ESCR_flag;
    char     ES_rate_flag;
    char     DSM_trick_mode_flag;
    char     additional_copy_info_flag;
    char     PES_CRC_flag;
    char     PES_extension_flag;
    uint8_t  PES_header_data_length;
    int64_t  ESCR_base;
    uint16_t ESCR_ext;
    uint32_t ES_rate;
#endif
    const uint8_t *pes_packet_data;
    int            pes_packet_data_size;
    int64_t        file_pos;
} ts_PES_packet_st;

#define TS_MEMNCPY(d, s, n, l) \
    memcpy(d, s, n < l ? n : l)

#endif /* TS_H */
