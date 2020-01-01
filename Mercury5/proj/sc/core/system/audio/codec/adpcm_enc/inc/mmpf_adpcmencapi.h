//==============================================================================
//
//  File        : mmpf_adpcmencapi.h
//  Description : INCLUDE File for the Audio ADPCM Encoder.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_ADPCMENCAPI_H_
#define _MMPF_ADPCMENCAPI_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define ADPCMENC_INBUF_FRAME_NUM    (40)//5
#define	ADPCMENC_BLOCK_SIZE         (1024)  // 1024 samples
#define ADPCMENC_OUTBUF_SIZE		(1024)
#define ADPCMENC_SIZEOF_WORKING_BUF	(32)

#define ADPCMENC_INBUF_SIZE			(ADPCMENC_BLOCK_SIZE*ADPCMENC_INBUF_FRAME_NUM)
#define ADPCMENC_TEMPBUF_SIZE       (ADPCMENC_BLOCK_SIZE << 1)

#if (VADPCM_R_EN)&&((VR_AUD_TIME_ALWAYS_LONGER)||(VR_MIX_FPS_WITH_AUD))
#define ADPCMENC_SILENCE_SIZE       ADPCMENC_OUTBUF_SIZE
#else
#define ADPCMENC_SILENCE_SIZE       (0)
#endif

#define ADPCMENC_BUFFER_SIZE        ((ADPCMENC_SIZEOF_WORKING_BUF << 1) + \
                                     (ADPCMENC_INBUF_SIZE << 1) + \
                                     (ADPCMENC_TEMPBUF_SIZE << 1) + \
                                     (ADPCMENC_OUTBUF_SIZE) + \
                                     (ADPCMENC_SILENCE_SIZE))

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void        MMPF_InitADPCMEncoder(void);
void        MMPF_EncodeADPCMFrame(void);
void        MMPF_SetADPCMEncMode(MMP_USHORT mode);
void        MMPF_GetADPCMParameter(MMP_ULONG *bitrate, MMP_ULONG *sampleRate);
MMP_ULONG   MMPF_GetADPCMRecFrameCntInSeconds(MMP_ULONG seconds);
MMP_ULONG   MMPF_GetADPCMRecFrameCnt(void);
void        MMPF_GetADPCMSilenceFrame(MMP_UBYTE **bs, MMP_ULONG *size);

#endif //_MMPF_ADPCMENCAPI_H_