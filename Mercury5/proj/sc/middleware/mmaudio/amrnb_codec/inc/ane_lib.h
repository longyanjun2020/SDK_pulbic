#ifndef __AMRNB_ENCODER_LIB_INCLUDE_FILE__
#define __AMRNB_ENCODER_LIB_INCLUDE_FILE__


int Mstar_amrnbe_memsize(void);

void *Mstar_amrnbe_init(void *memaddr);          
                        
int Mstar_amrnbe_coder(void *void_st,           //i/o   :  State structure 
                       int mode,              //input :  used mode 
                       int allow_dtx,         //input :  DTX ON/OFF 
                       int bitstream_format,
                       short *pcm_in,           //input :  160 new speech samples (at 8 kHz) 
                       void *parm_out,            //output:  output parameters
                       int *outlen);            //output:  output buffer valid len

int Mstar_amrnbe_coder_mb(void *void_st,int *mode,int allow_dtx,short *pcm_in,
             void *parm_out,int *outlen, short *status_p, int dtxSyncFlag,int *frameType);
#endif

