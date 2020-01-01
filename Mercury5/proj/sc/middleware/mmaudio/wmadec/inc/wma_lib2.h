#ifndef WMAD_MAIN_API_H
#define WMAD_MAIN_API_H

void  wma_decoder_funcinit(void *player);

int wma_decoder_open(void *player,
					   U32 *bits_per_sample,
					   U32 *sample_rate,
					   U16 *frame_length,
					   U8 *channels,
					   U32 *para);


int wma_decoder_decode_data(void *player,
                         U8 **out_buf, U32 *out_size, U32 *iisthreshold,U32 *consume_size);

int wma_decoder_seek_data(void *player, U32 *seektime);

int wma_decoder_get_timestamp(void *player, U32 *pu32Pos);

void wma_decoder_engine_clock(void *player, U8 onoff);

U32 wma_decoder_close(void *player);


#endif

