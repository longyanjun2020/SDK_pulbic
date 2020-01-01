#ifndef _MMPF_WAVENCAPI_H_
#define _MMPF_WAVENCAPI_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define WAVENC_INBUF_SLOT   (8)
#define WAVENC_INBUF_UNIT   (2048)
#define WAVENC_INBUF_SIZE   (WAVENC_INBUF_UNIT*WAVENC_INBUF_SLOT)
#define WAVENC_BUFFER_SIZE  (WAVENC_INBUF_SIZE << 1)

#if (VPCM_R_EN)&&((VR_AUD_TIME_ALWAYS_LONGER)||(VR_MIX_FPS_WITH_AUD))
#define WAVENC_SILENCE_SIZE (WAVENC_INBUF_UNIT << 1)
#else
#define WAVENC_SILENCE_SIZE (0)
#endif

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

extern void MMPF_InitWAVEncoder(void);
extern void MMPF_EncodeWAVFrame(void);
extern void MMPF_SetWAVRecMode(MMP_USHORT mode);
extern void MMPF_PostsetWAVRecHeader(MMP_BYTE *glFileName);
extern MMP_ULONG MMPF_GetWAVRecSampleRate(void);
extern MMP_ULONG MMPF_GetWAVRecDataSize(void);

#if (VPCM_R_EN)
extern MMP_ULONG MMPF_GetWAVRecFrameCnt(void);
extern void MMPF_GetWAVRecParameter(MMP_ULONG *bitrate, MMP_ULONG *sampleRate);
#if (VR_AUD_TIME_ALWAYS_LONGER)||(VR_MIX_FPS_WITH_AUD)
extern void MMPF_GetWAVSilenceFrame(MMP_UBYTE **bs, MMP_ULONG *size);
#endif
#endif

#endif //_MMPF_WAVENCAPI_H_
