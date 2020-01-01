#ifndef _AMRWB_DECODER_WRAPPER_INCLUDE_FILE_
#define _AMRWB_DECODER_WRAPPER_INCLUDE_FILE_

extern void  amrwb_decoder_funcinit(void *pInst);

extern int amrwb_decoder_open(void *player,
							unsigned int *bits_per_sample,
							unsigned int *sample_rate,
							unsigned short *frame_length,
							unsigned char *channels,
							unsigned int *para);

extern int amrwb_decoder_decode_data(void *player,
								   unsigned char **out_buf,
								   unsigned int *out_size,
								   unsigned int *iisthreshold,
								   unsigned int  *consume_size);
extern int amrwb_decoder_seek_data(void *player,
								 unsigned int *seektime);
extern int amrwb_decoder_get_timestamp(void *player, unsigned int *pu32Pos);

extern void amrwb_decoder_engine_clock(void *player, unsigned char onoff);

extern unsigned int amrwb_decoder_close(void *player);


#endif


