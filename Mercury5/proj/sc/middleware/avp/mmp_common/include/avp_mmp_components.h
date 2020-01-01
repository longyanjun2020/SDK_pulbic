////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011-2012 MStar Semiconductor, Inc.
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


#ifndef MMP_COMPONENTS_H
#define MMP_COMPONENTS_H

#include <stdint.h>
#include "avp_mvc_demuxer.h"
#include "mdl_avp_demuxer.h"

// audio decoder
struct _audio_decoder_s_;

int init_AC3A_decoder    (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_AMRNB_decoder_AV(struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_AMRWB_decoder   (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_COOK_decoder    (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_DRAA_decoder    (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_DSPA_decoder    (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_HEAAC_decoder   (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_MP3A_decoder    (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_PCMA_decoder    (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);
int init_WMA_decoder     (struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);

extern int (* const audio_decoder_factory[])(struct _audio_decoder_s_ **decoder, uint32_t codec_type, void *player);

// demuxer
struct demux_s;

int init_avi_demux_plugin  (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_ts_demux_plugin   (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_cmmb_demux_plugin (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_flv_demux_plugin  (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_mp2ps_demux_plugin(void *player, struct demux_s **demuxer, uint32_t file_type);
int init_rmvb_demux_plugin (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_tiny_demux_plugin (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_mkv_demux_plugin  (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_asf_demux_plugin  (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_mp3_demux_plugin  (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_amrn_demux_plugin (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_rtp_demux_plugin (void *player, struct demux_s **demuxer, uint32_t file_type);
int init_plugin_demux_plugin(void *player, struct demux_s **demuxer, uint32_t file_type);

extern int (* const demuxer_factory[])(void *player, struct demux_s **demuxer, uint32_t file_type);

typedef struct demuxer_probe_s
{
    char ext[5], len, fmt;
    const mvc_dmx_func_st *demuxer;
    int (* probe)(const uint8_t *header, int len, cb_io_st *cbio, int noio);
} demuxer_probe_st;

extern demuxer_probe_st demuxer_probe[];
extern int demuxer_probe_num;

typedef struct demuxer_plugin_s
{
    int                     file_type;
    const MDLAvpDemuxer_st *demuxer;
} demuxer_plugin_st;

extern demuxer_plugin_st demuxer_plugin[MDL_AVP_MAX_DMX_PLUGIN + 1];

void mmp_init_plugin(int speed_page_mode);

extern const int mmp_video_ringbuf_size;
extern const int mmp_audio_ringbuf_size;
extern const int max_ringbuf_size;
extern const int max_framebuf_size;

#endif /* MMP_COMPONENTS_H */
