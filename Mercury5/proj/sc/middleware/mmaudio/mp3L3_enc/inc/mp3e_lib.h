#ifndef __MP3_L3_ENCODER_LIB_INCLUDE_FILE__
#define __MP3_L3_ENCODER_LIB_INCLUDE_FILE__


void Mstar_mp3e_l3_getmem(int *sram_len,int *heap_len);
void *Mstar_mp3e_l3_init(void *sram_ptr,int sram_len,void *heap_ptr,int heap_len,
                       int srate, int bitrate, int nch, int st_mode);
int Mstar_mp3e_l3_encode(void *global_struct,short *pcm_buf,unsigned char *out_buf,int *out_len,int nsamples,int buf_size);

int Mstar_mp3e_l3_flush(void *global_struct,unsigned char *out_buf,int *out_len,int buf_size);  


#endif

