#ifndef __PUB_AMRNB_DECODER_LIB_INCLUDE_FILE__
#define __PUB_AMRNB_DECODER_LIB_INCLUDE_FILE__

int Mstar_amrnbd_memsize(void);

void *Mstar_amrnbd_init(void *memaddr,int *srate,int *ch,int *frame_size);

int Mstar_amrnbd_decode(void *void_st,void *parm_in,int len, int mono_stereo, short *pcm_out, int efr_flag,int bitstream_format);

int Mstar_amrnbd_decode_mb(void *void_st,void *parm_in,int len,short *pcm_out, int mode, int txType,int *flags_p);

void Mstar_amrnbd_resync(void *void_st); 

#endif
