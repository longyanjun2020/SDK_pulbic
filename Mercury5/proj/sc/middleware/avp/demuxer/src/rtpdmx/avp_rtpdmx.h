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


#ifndef RTPDMX_H
#define RTPDMX_H

#include <stdint.h>
#include "avp_streaming.h"
#include "avp_mvc_demuxer.h"

#define REORDER_QUEUED_MAX_NUMBER   (3)
#define REORDER_BUF_SIZE            (2*1024)
#define AOL_SIZE                    (20)
#define VOL_SIZE                    (200)
#define SDP_SIZE                    (2048)
#define PLAY_CONFIG_NUM             (5)

typedef enum rtp_codec_type_e {
    // video
    RTP_CODEC_MP4VES        = 1,
    RTP_CODEC_H264          = 2,
    RTP_CODEC_H2631998      = 3,
    // audio
    RTP_CODEC_AMR           = 4,
    RTP_CODEC_MP4ALATM      = 5,
    RTP_CODEC_MPEG4GENERIC  = 6,
} rtp_codec_type_et;

typedef struct rtp_video_config_s {
    int codec_type;
    int width;
    int height;
    int frame_rate_num;
    int frame_rate_den;
    uint32_t vol_size;
    uint8_t vol_data[VOL_SIZE];
    int payload_type;
    int bitrate;
} rtp_video_config_st;

typedef struct rtp_audio_config_s {
    int codec_type;
    int sample_rate;
    int channel_num;
    uint32_t aol_size;
    uint8_t aol_data[AOL_SIZE];
    int payload_type;
    int bitrate;
} rtp_audio_config_st;


typedef struct payload_param_s {
    uint8_t  version;
    uint8_t  padding;
    uint8_t  extension;
    uint8_t  csrc_count;
    uint8_t  marker;
    uint16_t payload_type;
    uint32_t seqNo;
    uint32_t timestamp;
    uint32_t ssrc;

    uint8_t  dmx_type;
    uint8_t  buffer[REORDER_BUF_SIZE];
    uint32_t buf_size;
    uint8_t used;

    int64_t pts;
} payload_param_st;

typedef struct reorder_packet_s {
    int32_t  queued_num;
    payload_param_st  queued_pkt[REORDER_QUEUED_MAX_NUMBER];
} reorder_packet_st;

typedef struct rtp_amr_attr_s {
    uint8_t isWideband;
    uint8_t numChannels;
    uint8_t isOctetAligned;
    uint8_t interleaving;
    // relevant only if "isOctetAligned"
    // The maximum # of frame-blocks in a group
    // 0 means: no interleaving
    uint8_t robustSortingOrder;
    // relevant only if "isOctetAligned"
    uint8_t CRCsArePresent;
    // relevant only if "isOctetAligned"
} rtp_amr_attr_st;

typedef struct rtp_mp4alatm_attr_s {
    int cpresent;
} rtp_mp4alatm_attr_st;

typedef struct rtp_mpeg4generic_attr_s {
    int8_t mode[10];
    int sizeLength;
    int indexLength;
    int indexDeltaLength;
} rtp_mpeg4generic_attr_st;


typedef struct rtp_h264_attr_s {
    int packetization_mode;
} rtp_h264_attr_st;

typedef struct rtp_h263_attr_s {
    uint8_t tmp;
} rtp_h263_attr_st;

typedef struct rtp_mp4ves_attr_s {
    uint8_t tmp;
} rtp_mp4ves_attr_st;


typedef struct rtp_video_attr_s {
    union {
        rtp_h264_attr_st            rtp_h264_attr;
        rtp_h263_attr_st            rtp_h263_attr;
        rtp_mp4ves_attr_st          rtp_mp4ves_attr;
    } attr;
} rtp_video_attr_st;

typedef struct rtp_audio_attr_s {
    union {
        rtp_amr_attr_st             rtp_amr_attr;
        rtp_mp4alatm_attr_st        rtp_mp4alatm_attr;
        rtp_mpeg4generic_attr_st    rtp_mpeg4generic_attr;
    } attr;
} rtp_audio_attr_st;

// queue 2 frames.
typedef struct rtp_h264_slice_s {
    int8_t  get_start_code; // for H.264, to indicate how many start code we get so far
    int8_t  first_mb;
    int64_t prv_pts;
} rtp_h264_slice_st;

typedef struct rtp_m4v_slice_s {
    int64_t prv_pts;
} rtp_m4v_slice_st;

typedef struct rtp_slice_s {
    union {
        rtp_h264_slice_st   h264_slice;
        rtp_m4v_slice_st    m4v_slice;
    } slice;
} rtp_slice_st;

typedef struct rtsp_rtpinfo_t {
    int32_t  have_info;
    uint32_t start_pos; // millisecond
    uint32_t video_rtptime;
    uint32_t audio_rtptime;
    uint16_t video_seqNo;
    uint16_t audio_seqNo;
} rtsp_rtpinfo_st;

typedef struct rtsp_play_config_t {
    rtsp_rtpinfo_st cfg_data[PLAY_CONFIG_NUM];
    int             ready;
    int             v_ridx;
    int             v_widx;
    int             a_ridx;
    int             a_widx;
} rtsp_play_config_st;

typedef struct rtsp_sdp_t {
    rtp_video_config_st video_cfg;
    rtp_audio_config_st audio_cfg;
    rtp_video_attr_st   video_attr;
    rtp_audio_attr_st   audio_attr;
    int64_t             duration;
    rtp_codec_type_et   codec_type[2];
    uint32_t            timestamp_freq[2];
} rtsp_sdp_st;

typedef struct rtp_demuxer_s {
    cb_buffer_st        cbuffer;
    mvc_allocator_st    allocator;
    void                *alloc_ctx;
    void                *mem_ctx;

    uint32_t            payload_type[2];
    uint32_t            payload_length[2];
    uint32_t            expected_seqNo[2];
    uint16_t            max_seq[2];
    uint32_t            seq_cycle[2];
    uint32_t            prv_timestamp[2];
    int64_t             timestamp_base[2];
    uint64_t            play_start_time[2];
    int32_t             (*fp_video_payload_rfc)(void *ctx, uint8_t *p_payload, int buf_len, uint8_t *p_avpayload,
                                                int *bufsize, int64_t pts, int *is_intra);
    int32_t             (*fp_audio_payload_rfc)(void *ctx, uint8_t *p_payload, int buf_len, uint8_t *p_avpayload,
                                                int *bufsize, int64_t pts);
    uint8_t             resync;

    uint8_t             *avpayload;
    uint8_t             *out_avpacket;
    uint8_t             buf_allocated[2];

    reorder_packet_st   reorder_pkt[2];
    uint8_t             base64decTab[123];
    rtp_slice_st        rtp_slice;
    uint8_t             last_fragment;
    uint8_t             sdpdata[SDP_SIZE];
    uint32_t            sdpsize;
    uint8_t             sdpdata2[SDP_SIZE]; // in case receiving another sdp
    rtsp_sdp_st         sdpcfg;
    int                 last_video_seq_num;
    rtsp_play_config_st play_cfg;
    int                 seekable;
    int                 is_eos;
    int                 is_intra;
    int64_t             start_drop_time;
    int                 enable_fakeI;
} rtp_demuxer_st;

#endif /* RTPDMX_H */
