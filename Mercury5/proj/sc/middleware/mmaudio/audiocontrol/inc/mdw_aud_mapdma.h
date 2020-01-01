/// @file   mdw_aud_mapdma.h
/// @author MStar Semiconductor Inc.
/// @brief  audio application header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _MDW_AUD_MAPDMA_H
#define _MDW_AUD_MAPDMA_H

#include "vm_types.ht"
#include "mdl_aud_pub_api.h"

#define DMADRV_GETBUFINFO_ERR 0x3000
#define DMADRV_FORCESTOP_ERR 0x3001
#define DMADRV_PLAYWRITE_ERR 0x3002
#define DMADRV_PLAYSTART_ERR 0x3003
#define DMADRV_AMPON_ERR 0x3004
#define DMADRV_PAUSE_ERR 0x3005
#define DMADRV_RESUME_ERR 0x3006
#define DMADRV_PLAYSTOP_ERR 0x3007
#define DMADRV_CHKFINISH_ERR 0x3008
#define DMADRV_AMPOFF_ERR 0x3009
#define DMADRV_PLAYCLOSE_ERR 0x300a
#define MAP_OPEN_ERR 0x300b
#define MAP_DECODE_ERR 0x300c
#define MAP_BUFINIT_ERR 0x300d
#define MAP_SEEK_ERR 0x300e
#define MAP_OFFSETPLAY_SEEK_ERR 0x300f
#define DMADRV_GETBUF_NOSPACE_ERR 0x3010
#define MAP_READTHREAD_CLOSE_ERR 0x3011
#define MAP_STREAMING_UNDERRUN_ERR 0x3012

s32 fnMpAudio_driver_init(void *pInst,u32 fraction, u32 denominator, u8 channel, u32 sample_rate, s32 BitsPerSample);
MdlAudSamplingRate_e MdlAudDMASmpRateRemap(u32 nSamplRate);
s32 MdlAudOutToDMA(void *sample_buffer, u32 u32samplesize, void *audplayer);
s32 MdlAudInputFromDMA(void *sample_buffer, u32 u32samplesize,  u32 *nActualSize);
s32 MdlAudCheckPlayStart(u32 u32IISBufSize, u32 u32samplesize, s8 *u8bplay, s8 *alarm_enable, u8 nA2DPMode);
s32 MdlAudPlayChkSampleFinish(u8 *pStopFlag);
void MdlAudCheckOutputIsReady(void);
s32 fnMpAudio_music_pause(void *pInst,u8 u8sbcenable);



#endif
