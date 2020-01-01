#ifndef _AAC_DECODER_WRAPPER_INCLUDE_FILE_
#define _AAC_DECODER_WRAPPER_INCLUDE_FILE_

extern void  aac_decoder_aop_funcinit(void *pInst);

extern int aac_decoder_aop_open(void *player,
							unsigned int *bits_per_sample,
							unsigned int *sample_rate,
							unsigned short *frame_length,
							unsigned char *channels,
							unsigned int *para);

extern int aac_decoder_aop_decode_data(void *player,
								   unsigned char **out_buf,
								   unsigned int *out_size,
								   unsigned int *iisthreshold , unsigned int *consume_size);
extern int aac_decoder_aop_seek_data(void *player,
								 unsigned int *seektime);
extern int aac_decoder_aop_get_timestamp(void *player, unsigned int *pu32Pos);

extern void aac_decoder_aop_engine_clock(void *player, unsigned char onoff);

extern unsigned int aac_decoder_aop_close(void *player);


#endif


