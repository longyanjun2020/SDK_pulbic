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


#ifndef AUDIO_DECODER_H
#define AUDIO_DECODER_H

#include <stdint.h>
#include "avp_buf_element.h"

#define AUDIO_OPEN_MODE_NORMAL          0
#define AUDIO_OPEN_MODE_READ_INFO_ONLY  1

#define CONSUME_AUDIO_PKT_THRESHOLD (10)

typedef enum adec_error_code_e
{
    AUD_DEC_SUCCESS,
    AUD_DEC_FAIL,
    AUD_DEC_MORE_BITSTREAM,
    AUD_DEC_MORE_PCM,
    AUD_DEC_PLAY_ONCE_AND_BREAK,
    AUD_DEC_SKIP,
} adec_error_code_et;

typedef struct _audio_decoder_s_ audio_decoder_t;

struct _audio_decoder_s_
{
    uint32_t (*open)(audio_decoder_t *self,
                uint32_t *bits_per_sample,
                uint32_t *sample_rate,
                uint16_t *frame_length,
                uint8_t *channels,
                uint8_t *config_data,
                int config_size,
                uint32_t mode);

    uint32_t (*decode_data) (audio_decoder_t *self,
                         buf_element_t *buf, int *u32remaining,
                         uint8_t **out_buf, int *out_size,
                         int32_t *pts);

    /*
    * reset decoder after engine flush (prepare for new
    * audio data not related to recently decoded data)
    */
    void (*reset) (audio_decoder_t *self);

    /*
    * inform decoder that a time reference discontinuity has happened.
    * that is, it must forget any currently held pts value
    */
    void (*discontinuity) (audio_decoder_t *self);

    uint32_t (*close)(audio_decoder_t **self);

    /* get continuing audio frame num */
    uint32_t (*getframe_counts)(audio_decoder_t *self,
                           buf_element_t *buf, uint32_t u32remaining, int *cuter);

    void *player;
    int callback_flag; /* flag to indicate decoder input mode */

    int frame_counts;
    uint32_t samplerate;
    uint32_t frame_duration;
    uint32_t bitrate;
    uint16_t channel_info;
    uint16_t frame_length;
    uint32_t bits_per_sample;

    uint8_t *pcm_buffer;
    int pcm_buffer_size;

    int resync_flag;
    int remain_data_size;

    int dec_count;
    int64_t total_dec_time;

    int consume_pkt_cnt;
};

extern int init_audio_decoder(void *player_inst, uint32_t codec_type);
#ifdef SLDLM_MMAUDIO
int audio_remap_sldlm_error(int sldlm_ret);
#endif
#endif // AUDIO_DECODER_H
