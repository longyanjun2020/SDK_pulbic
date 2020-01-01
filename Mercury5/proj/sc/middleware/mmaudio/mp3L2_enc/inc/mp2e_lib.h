#ifndef __MP3_ENC_LIB_INCLUDE_FILE__
#define __MP3_ENC_LIB_INCLUDE_FILE__

void Mstar_mp3e_getmem(int *sram_len,int *heap_len);
int Mstar_mp3e_setmem(void *sram_ptr,int sram_len,void *heap_ptr,int heap_len);
int Mstar_mp3e_init(int srate, int bitrate, int nch, int st_mode);

int Mstar_mp3e_encode(short *pcm_buf,unsigned char *out_buf,int *out_len);

#endif


