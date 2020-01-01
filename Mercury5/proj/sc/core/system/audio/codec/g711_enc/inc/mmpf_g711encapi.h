#ifndef _MMPF_G711ENCAPI_H_
#define _MMPF_G711ENCAPI_H_

#include "mmpf_srcapi.h"

#define G711_INBUF_SIZE     (SRC_READ_SAMPLE * 2 * 2 * 36)// ( 2 BPP, 2 channels, 36 slots))
#define G711_OUTBUF_SIZE    8000 //1sec

void MMPF_InitG711Enc(MMP_ULONG ADCsamplerate);
MMP_ULONG MMPF_g711BlockEnc(void);
void MMPF_StopG711Enc(void);
AUTL_RINGBUF *MMPF_G711_GetRing(void);
#endif
