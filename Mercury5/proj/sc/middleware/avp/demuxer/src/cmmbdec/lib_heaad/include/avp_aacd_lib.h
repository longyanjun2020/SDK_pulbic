
#ifndef _AAC_DECODER_LIB_INCLUDE_FILE_
#define _AAC_DECODER_LIB_INCLUDE_FILE_

#define AACD_PARSER_FAIL    0x40000
#define AACD_FORMAT_FAIL    0x10000
#define AACD_PLAY_END       0x20000
#define AACD_RESYNC_END     0x30000
#define AACD_OK             0


//for AO API
int Mstar_AACD_aop_decode(int EQ_enable,int **pcm_buf,int *play_time,unsigned char **EQ_band,int *ch,
                          int *frame_size,int *fending);
int Mstar_AACD_aop_resync(int play_time);
int Mstar_AACD_aop_bitstream_callback(unsigned char *buf, int len,int *fending);
void Mstar_AACD_aop_fileseek_callback(int file_ptr);
int Mstar_AACD_aop_getposition_callback(void);
int Mstar_AACD_aop_init(unsigned int filelen, int *srate, int *ch,int *bitrate,int *total_time,int *total_frame,
                        int *header_type,int *sdram_buf,int sdram_size,
                        int fbrowser,int *sbr_flag);

//for AV API
int Mstar_AACD_eng_init(int samplerate,int sbr_present_flag,int downSampledSBR,int forceUpSampling);
int Mstar_AACD_eng_bitstream_callback(unsigned char *buf, int len);
int Mstar_AACD_eng_decode(int EQ_enable,int **pcm_buf,unsigned char **EQ_band,int *ch,int *frame_size);
void Mstar_AACD_eng_fill_frame(int frame_size);
int Mstar_AACD_eng_audio_config(unsigned char *buf,int size,int *sample_rate,int *ch_num,
                                int *sbr_present_flag,int *downSampledSBR,int *forceUpSampling);
//for AO and AV
void Mstar_AACD_eng_post_process(int mono_stereo,int stereo_reverse,int samples,int ch,int **pcm_buf,short *out_buf,int sbr_flag);

void Mstar_AACD_set_sram_addr(int *sram_ptr,int *heap_ptr);

#endif
