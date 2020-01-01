//==============================================================================
//
//  File        : mmpf_aacencapi.h
//  Description : INCLUDE File for the Audio AAC Encoder.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#ifndef _MMPF_AACENCAPI_H_
#define _MMPF_AACENCAPI_H_

//==============================================================================
//
//                              INCLUDE FILES
//
//==============================================================================

#include "aacenc.h"
#include "mmpf_ringbuf.h"

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================

#ifndef NULL
#define NULL                0
#endif

#define MAX_PAYLOAD_SIZE    128

#define BYTE_NUMBIT         8   /* bits in byte (char) */

#ifndef min
#define min(a, b)   ((a < b) ? (a) : (b))
#endif

#define AACENC_SIZEOF_WORKING_BUF   0x8000	//32K bytes
#define AACENC_INBUF_FRAME_NUM      (45) //15
#define AACENC_INBUF_SIZE           (1024*2*AACENC_INBUF_FRAME_NUM)
#define AACENC_OUT_MAX_SIZE         ((6144 >> 3) * MAX_CHANNELS)
#if (VAAC_R_EN)&&((VR_AUD_TIME_ALWAYS_LONGER)||(VR_MIX_FPS_WITH_AUD))
#define AACENC_SILENCE_SIZE         AACENC_OUT_MAX_SIZE
#else
#define AACENC_SILENCE_SIZE         0
#endif

#define AACENC_BUFFER_SIZE          (AACENC_SIZEOF_WORKING_BUF + \
                                    (AACENC_INBUF_SIZE << 1) + \
                                    AACENC_OUT_MAX_SIZE +\
                                    AACENC_SILENCE_SIZE)

#if (LIVE_AAC_R_EN)
#define LIVE_AAC_OUTBUF_SIZE        (72000) // 3 seconds for 128Kbps
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct {
    long numBit;          /* number of bits in buffer */
    long size;            /* buffer size in bytes */
    long currentBit;      /* current bit position in bit stream */
    long numByte;         /* number of bytes read/written (only file) */
    unsigned char *data;  /* data bits */
} BitStream;

//==============================================================================
//
//                              PUBLIC FUNCTIONS
//
//==============================================================================
extern int GetSRIndex(unsigned int sampleRate);

extern void MMPF_EncodeAACFrame(void);
extern void MMPF_InitAACEncoder(void);
extern void MMPF_SetAACRecParameter(unsigned int bitrate,unsigned int sampleRate);
extern void MMPF_GetAACRecParameter(unsigned int *bitrate,unsigned int *sampleRate);
extern void MMPF_SetAACEncMode(unsigned short mode);
extern unsigned int MMPF_GetAACRecFrameCnt(void);
extern unsigned int MMPF_GetAACRecFrameCntInSeconds(MMP_ULONG seconds);
extern void MMPF_PostsetAACRecordData(MMP_BYTE *glFileName);
extern void MMPF_GetAACSilenceFrame(MMP_UBYTE **bs, MMP_ULONG *size);
extern void MMPF_Audio_InitAACOutStreamBuf(void);
extern AUTL_RINGBUF *MMPF_Audio_GetAACOutStreamBuf(void);
extern void MMPF_ReadAACOutRingBuf(AUTL_RINGBUF *ringbuf, MMP_BYTE *target, MMP_ULONG bytes);

#endif //_MMPF_AACENCAPI_H_

