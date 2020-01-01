#ifndef _PUB_AUDCTL_H
#define _PUB_AUDCTL_H

extern s32 init_mar_codec(void *pInst, s32 data_fmt);
extern s32 Uninit_mar_codec(void);

extern u32 MDLShutterSoundWAVParser(u8 *audmem_sharebuf, u32 audmem_sharebufsize, u32 *pDataPos, u32 *pSamplerate, u8 *pChNum, u16 *wbitpersample, u32 *shutter_availsize, u8 *pPCMFormat, u32 *pBlockAlign);

extern S32 AUD_GetSpectrumData(void *pData, u32 nDataSize);
extern void AUD_SET_SPECTRUM_ONOFF(bool setonoff);

extern s32 MdlAudCheckAMRCabability(void);

#endif

