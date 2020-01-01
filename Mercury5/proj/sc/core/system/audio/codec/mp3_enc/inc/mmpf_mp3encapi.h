#ifndef MMPF_MP3ENCAPI_API
#define MMPF_MP3ENCAPI_API

#include "mmp_lib.h"

#define	MP3ENC_SIZEOF_WORKING_BUF	0x9C00	//39K
#define MP3ENC_INBUF_FRAME_NUM      20
#define MP3ENC_INBUF_SIZE           (1152*2*MP3ENC_INBUF_FRAME_NUM)
#define MP3ENC_OUTBUF_SIZE          2048
#define MP3ENC_BUFFER_SIZE          (MP3ENC_SIZEOF_WORKING_BUF + \
                                    (MP3ENC_INBUF_SIZE << 1) + \
                                    MP3ENC_OUTBUF_SIZE)

extern void MMPF_EncodeMP3Frame(void);
extern void MMPF_InitMP3Encoder(void);
extern void MMPF_SetMP3RecParameter(unsigned int bitrate,unsigned int sampleRate);
extern void MMPF_GetMP3RecParameter(unsigned int *bitrate, unsigned int *sampleRate);
extern void MMPF_SetMP3EncMode(unsigned short mode);
extern void MMPF_ExitMP3Encoder(void);
extern void MMPF_PostsetMP3RecordData(char *glFileName);
MMP_ULONG   MMPF_GetMP3FrameSize(void);
MMP_ULONG   MMPF_GetMP3RecFrameCnt(void);
MMP_ULONG   MMPF_GetMP3RecFrameCntInSeconds(MMP_ULONG seconds);
#endif
