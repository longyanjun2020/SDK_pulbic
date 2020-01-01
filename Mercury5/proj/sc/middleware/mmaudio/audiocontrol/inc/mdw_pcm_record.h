#ifndef _PCMENC_H
#define _PCMENC_H
                            
extern s32 pcm_encoder_open(void *pInst,
                            s32 S32dtx_enable,
                            u32 *u32samplebuffer_addr,
                            u32 *u32bits_per_sample,
                            u32 *u32sample_rate,
                            u32 *u32frame_length,
                            u32 *u32channels,
                            u32 *u32para);

extern s32 pcm_encoder_open_append(void *pInst,
                            s32 S32dtx_enable,
                            u32 *u32samplebuffer_addr,
                            u32 *u32bits_per_sample,
                            u32 *u32sample_rate,
                            u32 *u32frame_length,
                            u32 *u32channels,
                            u32 *u32para);

extern s32 pcm_encoder_enc_data(void *pInst,
                           s32 *out_size,
                           u32 *u32rectotaltime,
                           u32 *u32rectotalsize,
                           s32 s32first_frame);

extern s32 pcm_encoder_get_timestamp(void *pInst, u32 *pu32Pos);

extern void pcm_encoder_engine_clock(void *pInst, u8 onoff);

extern s32  pcm_encoder_close(void *pInst);

extern s32 pcm_encoder_write_close(void *pinst , s32 *seek_offt, s32 *wsize, u8** wsrcptr);

#endif

