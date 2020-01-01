#ifndef _PUB_WMA_DECODER_LIBRARY_INCLUDE_FILE_
#define _PUB_WMA_DECODER_LIBRARY_INCLUDE_FILE_

#define WMA_DECODER_DRAM_BUF_SIZE  ((56+12)*1024)  //12K is output buffer = 3K sample * 2 ch * sizeof(short)

int Mstar_WMAD_memset(int *sram_ptr,int *heap_ptr);

int  Mstar_WMAD_init(int *sample_rate, int *ch, int *total_time, int *bitrate, int *version, int *frame_size, int *Video_Audio);
int  Mstar_WMAD_decode(short **pcm_buf, int *outbufsize);
int  Mstar_WMAD_seek_data(unsigned int *msSeekTo);
void Mstar_WMAD_get_timestamp(unsigned int *play_time);
int Mstar_WMAD_get_info(unsigned char * wma_buf_start, int *sample_rate, int *ch, int *total_time, int *bitrate, int *BitRateType, int *version, int *frame_size);
int Mstar_WMAD_aop_bitstream_callback(unsigned char *buf, int len );
int Mstar_WMAD_aop_bitstream_fseek(unsigned int offset );
void Mstar_WMAD_close(void);

int  Mstar_WMAD_AVinit(int *sample_rate, int *ch, int *bitrate, int *version, int *frame_size, unsigned char *config_data, int config_size);
int  Mstar_WMAD_AVinit_getinfo(int *sample_rate, int *ch, int *bitrate, int *version, int *frame_size, unsigned char *config_data, int config_size);


#endif

