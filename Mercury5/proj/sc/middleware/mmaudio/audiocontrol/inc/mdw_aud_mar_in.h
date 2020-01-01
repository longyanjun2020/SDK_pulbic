#ifndef __MDW_AUD_SETUP__
#define __MDW_AUD_SETUP__

#include "vm_types.ht"



#ifdef __FM_PEQ_ENABLE__
static void MAROverrunRingBufferNCallback(u32 nContactID, u32 nUserValue);
#if 0
static void MARUnderrunRingBufferNCallback(u32 nContactID, u32 nUserValue);
#endif
static s32 _MdlMarAudRBSetup(void *pInst);
static s32 fnMARRecRBPop(u32 u32PopSize, u8* pDstAddr);
static s32 fnMARRec_GetRBufInfo(void *pInst, void *sample_buffer, u32 u32samplesize, u32 u32channel);
#endif
static void _MdlMarAudFullCb(void);
static void _MdlMarAudOverrunCb(void);
static void _MdlMarAudUnderrunCb(void);
static s32 _MdlMarAudDMASetup(void *pInst);

#if defined(BIG3) && defined(__B3_AUDIO_DRV_API__)
static u32 MdlMARErrorTranslate(MdlAudRet_e eError);
static void _MdlMARStereoToMono(u8* dest, u8 *src, u32 len);
#ifdef __FM_STEREO_AUTO
static void _MdlMARStereoMixToMono(u8* dest, u8 *src, u32 len);
#endif
static s32 fnMARRec_GetDMABufInfo(void *pInst, void *sample_buffer, u32 u32samplesize, u32 u32channel);
#endif


s32 _MdlMarAudSetup(void *pInst);
s32 fnMARRec_GetBufInfo(void *pInst,void *sample_buffer, u32 u32samplesize, u32 u32channel);
s32 fnMAR_Stop(void);
s32 MdlAudRecGetBufInfoReq(void *pInst, u32 *pnDataSize);

#endif
