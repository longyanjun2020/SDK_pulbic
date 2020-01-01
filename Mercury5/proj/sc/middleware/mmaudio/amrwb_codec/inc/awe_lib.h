#ifndef __AMR_WB_ENCODER_LIB_INCLUDE_FILE__
#define __AMR_WB_ENCODER_LIB_INCLUDE_FILE__

int Mstar_amrwbe_memsize(void);
void *Mstar_amrwbe_init(char *memaddr);

int Mstar_amrwbe_coder(
     void *void_st,                 //i/o   :  State structure 
     short mode,                    //input :  used mode 
     short allow_dtx,               //input :  DTX ON/OFF  
     short bitstreamformat,
     short *signal,                 //input :  320 new speech samples (at 16 kHz) 
     unsigned char *outbuf,         //output:  output parameters
     int *outlen                    //output:  output buffer valid len
);





#endif

