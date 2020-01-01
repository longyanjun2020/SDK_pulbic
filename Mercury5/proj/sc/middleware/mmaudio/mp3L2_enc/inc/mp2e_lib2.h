#ifndef _MP3L2_ENCODER_WRAPPER_INCLUDE_FILE_
#define _MP3L2_ENCODER_WRAPPER_INCLUDE_FILE_

extern S32 mp3L2_encoder_open(void *pInst,
                            S32 S32dtx_enable,
                            U32 *samplebuffer,
                            U32 *u32bits_per_sample,
                            U32 *u32sample_rate,
                            U32 *u32frame_length,
                            U32 *u32channels,
                            U32 *u32para);



extern S32 mp3L2_encoder_open_append(void *pInst,
                            S32 S32dtx_enable,
                            U32 *samplebuffer,
                            U32 *u32bits_per_sample,
                            U32 *u32sample_rate,
                            U32 *u32frame_length,
                            U32 *u32channels,
                            U32 *u32para);

extern S32 mp3L2_encoder_enc_data(void *pInst,
                          S32 *out_size,
                          U32 *u32rectotaltime,
                          U32 *u32rectotalsize,
                          S32 s32first_frame);

extern S32 mp3L2_encoder_get_timestamp(void *pInst, U32 *pu32Pos);

extern void mp3L2_encoder_engine_clock(void *pInst, U8 onoff);

extern S32 mp3L2_encoder_close(void *pInst);

extern S32 mp3L2_encoder_write_close(void *pinst ,S32 *seek_offt, S32 *wsize, U8** wsrcptr);

#endif
