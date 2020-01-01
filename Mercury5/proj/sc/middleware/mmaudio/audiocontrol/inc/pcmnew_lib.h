#ifndef _PCMNEWLIB_H
#define _PCMNEWLIB_H


extern void pcm_decoder_funcinit(void *pInst);

extern s32 pcm_decoder_open(void *player,
                            u32 *bits_per_sample,
                            u32 *sample_rate,
                            u16 *frame_length,
                            u8 *channels,
                            u32 *para);

extern s32 pcm_decoder_decode_data(void *player,
                         u8 **out_buf, u32 *out_size,u32 *iisthreshold, u32 *consume_size);
extern s32 pcm_decoder_seek_data(void *player, u32 *seektime);

extern s32 pcm_decoder_get_timestamp(void *player, u32 *pu32Pos);

extern void pcm_decoder_engine_clock(void *player, u8 onoff);

extern u32 pcm_decoder_close(void *pInst);

#endif
