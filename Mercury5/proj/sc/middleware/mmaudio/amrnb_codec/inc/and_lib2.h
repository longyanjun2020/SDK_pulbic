#ifndef _AMRNB_DECODER_WRAPPER_INCLUDE_FILE_
#define _AMRNB_DECODER_WRAPPER_INCLUDE_FILE_

extern void  amrnb_decoder_aop_funcinit(void *pInst);

extern int amrnb_decoder_aop_open(void *player,
							unsigned int *bits_per_sample,
							unsigned int *sample_rate,
							unsigned short *frame_length,
							unsigned char *channels,
							unsigned int *para);

extern int amrnb_decoder_aop_decode_data(void *player,
								   unsigned char **out_buf,
								   unsigned int *out_size,
								   unsigned int *iisthreshold, unsigned int *consume_size);
extern int amrnb_decoder_aop_seek_data(void *player,
								 unsigned int *seektime);
extern int amrnb_decoder_aop_get_timestamp(void *player, unsigned int *pu32Pos);

extern void amrnb_decoder_aop_engine_clock(void *player, unsigned char onoff);

extern unsigned int amrnb_decoder_aop_close(void *player);


#endif


