#ifndef _AMRNB_ENCODER_WRAPPER_INCLUDE_FILE_
#define _AMRNB_ENCODER_WRAPPER_INCLUDE_FILE_

extern int amrnb_encoder_open(void *pInst,
                            int s32dtx_enable,
                            unsigned int *samplebuffer,
                            unsigned int *u32bits_per_sample,
                            unsigned int *u32sample_rate,
                            unsigned int *u32frame_length,
                            unsigned int *u32channels,
                            unsigned int *u32para);

extern int amrnb_encoder_open_append(void *pInst,
                            int s32dtx_enable,
                            unsigned int *samplebuffer,
                            unsigned int *u32bits_per_sample,
                            unsigned int *u32sample_rate,
                            unsigned int *u32frame_length,
                            unsigned int *u32channels,
                            unsigned int *u32para);

extern int amrnb_encoder_enc_data(void *pInst,
                          int *out_size,
                          unsigned int *u32rectotaltime,
                          unsigned int *u32rectotalsize,
                          int s32first_frame);

extern int amrnb_encoder_enc_data_videochat(void *pInst,
                          int *out_size,
                          unsigned int *u32rectotaltime,
                          unsigned int *u32rectotalsize,
                          int s32first_frame);

extern int amrnb_encoder_enc_data_append(void *pInst,
                          int *out_size,
                          unsigned int *u32rectotaltime,
                          unsigned int *u32rectotalsize,
                          int s32first_frame);

extern int amrnb_encoder_get_timestamp(void *pInst, unsigned int *pu32Pos);

extern void amrnb_encoder_engine_clock(void *pInst, unsigned char onoff);

extern int amrnb_encoder_close(void *pInst);

extern int amrnb_encoder_write_close(void *pinst ,int *seek_offt, int *wsize, unsigned char** wsrcptr);


#endif


