#ifndef _PUB_RA_DECODER_LIBRARY_INCLUDE_FILE_
#define _PUB_RA_DECODER_LIBRARY_INCLUDE_FILE_


int  Mstar_COOKD_init(unsigned char * RMlbr_buf_start, int *sample_rate, int *ch, int *total_time, int *bitrate, int *frame_size, int *MaxSamples, int *BitRateType);
int  Mstar_COOKD_decode(short **pcm_buf,  int *outbufsize, int mono2stereo_enable, int init_channels);
int  Mstar_COOKD_get_info(unsigned char * cook_buf_start, int *sample_rate, int *ch, int *total_time, int *bitrate, int *BitRateType);
void Mstar_COOKD_get_timestamp(unsigned int *play_time);
int Mstar_COOKD_seek_data(unsigned int *msSeekTo);
void Mstar_COOKD_Close(void);

int  Mstar_COOKD_avp_init(  unsigned char * buf_start,
                            int out_ch,
                            int sampRate,
                            int nFrameBits,
                            void* pCodecInitInfo);
int  Mstar_COOKD_avp_decode(int ulFramesizes, short **pcm_buf,  int *outbufsize, int *consuming_bytes);

int Mstar_COOK_aop_bitstream_callback(unsigned char *buf, unsigned int len);

#endif

