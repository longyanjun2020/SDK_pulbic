
#ifndef __PUB_AMR_WB_DECODER_LIBRARY_API_INCLUDE_FILE__
#define __PUB_AAMR_WB_DECODER_LIBRARY_API_INCLUDE_FILE__

int Mstar_amrwbd_memsize(void);
void *Mstar_amrwbd_init(char *memaddr,int *srate,int *ch,int *frame_size);
int Mstar_amrwbd_decode(void *ass,unsigned char *inbuf,int len, int mono_stereo,short *pcm_buf);

#endif
