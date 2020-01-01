#ifndef AACD_MAIN_API_H
#define AACD_MAIN_API_H

void  aac_decoder_funcinit(void *pInst);

S32 aac_decoder_open(void *player,
							U32 *bits_per_sample,
							U32 *sample_rate,
							U16 *frame_length,
							U8 *channels,
							U32 *para);

S32 aac_decoder_decode_data(void *player,
								   U8 **out_buf,
								   U32 *out_size,
								   U32 *iisthreshold,
								   U32 *consume_size);

S32 aac_decoder_seek_data(void *player, U32 *seektime);

S32 aac_decoder_get_timestamp(void *player, U32 *pu32Pos);

void aac_decoder_engine_clock(void *player, U8 onoff);

U32  aac_decoder_close(void *player);

#endif

