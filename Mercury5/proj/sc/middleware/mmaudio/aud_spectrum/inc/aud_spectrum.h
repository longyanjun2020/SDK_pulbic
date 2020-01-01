#ifndef AUDIOSPECTRUM_H
#define AUDIOSPECTRUM_H

#include "audspecsharedmem.h"
#include "vm_types.ht"

// ------- compile option -----
//#define USE_PRECAL_BITREVERSE_PATN
//#define NFFT64 // 64-point
//#define NFFT128 // 128-point
#define NFFT256// 256-point
//#define NFFT512 // 512-point
//#define NFFT1024 // 1024-point
#define SPEC_RING_BUF

// ------- parameters ---------
#if defined(NFFT1024)
#define AUDIO_SPECTRUM_NFFT 1024
#elif defined(NFFT512)
#define AUDIO_SPECTRUM_NFFT 512
#elif defined(NFFT256)
#define AUDIO_SPECTRUM_NFFT 256
#elif defined(NFFT128)
#define AUDIO_SPECTRUM_NFFT 128
#elif defined(NFFT64)
#define AUDIO_SPECTRUM_NFFT 64
#endif
#define OUT_MAG_SIZE        16

#if defined(USE_PRECAL_BITREVERSE_PATN)
#define AUD_SPEC_MEMORY     (AUDIO_SPECTRUM_NFFT*4 /*queue input data*/+\
                             AUDIO_SPECTRUM_NFFT*8 /*complex FFT result*/ +\
                             AUDIO_SPECTRUM_NFFT*4 /*bit reverse pattern*/)
#else
#define AUD_SPEC_MEMORY     (AUDIO_SPECTRUM_NFFT*4 /*queue input data*/+\
                             AUDIO_SPECTRUM_NFFT*8 /*complex FFT result*/ )
#endif



typedef struct
{
    int EnableDisp;
    int NFFT;
    int Channel;
    int SmpRate;
}STRUC_AUDSPEC_USER_CONFIG;

typedef struct
{
    STRUC_AUDSPEC_USER_CONFIG UserConfig;
    STRUC_AUDSPEC_RBUF_HEADER AudSpecRbuf;
    int SmpCount;
    int SmpNumThreshold;
    int RealDataBufOffset;
    int FFT_RESOLUTION;
    short* p16FFTReCoeff;
    short* p16FFTImCoeff;
    unsigned short* pWin;
    int (*PreProc_AudSpectrum)(void*, short*, int, s64);
    short* p16RealData;        // for downmix input data
    int* p32ComplexFFT;        // for result complex FFT
    short* p16BitReversePatn;  // for Radix-2 FFT bit reverse pattern
    s64 pts;
	bool cmdset;
	#ifdef SPEC_RING_BUF
	u32 u32wHandle;
	#endif
   bool configSuccess;
}STRUC_AUDSPEC_SELF_CONFIG;

#ifdef __cplusplus
extern "C"{
#endif

#if defined(PIONEER_PLAYER)
extern STRUC_AUDSPEC_USER_CONFIG gAudSpecUserConfig;
extern STRUC_AUDSPEC_SELF_CONFIG gAudSpecSelfConfig;
#endif

int Config_AudSpectrum(void* pUserConfig,
                       void* pSelfConfig,
                       int FFTSize,
                       int SmpRate,
                       short Channel,
                       char* pGlobalBuf);
int Proc_AudSpectrum(void* pSelfConfig,
                     short* p16data,
                     int SzInByte,
                     unsigned int pts);
int Close_AudSpectrum(void* pSelfConfig);
int GetnFFT_AudSpectrum(void* pSelfConfig);
int GetnFFT_AudSpectrum(void* pSelfConfig);
int Update_Settings_AudSpectrum(void* pSelfConfig, void* pUserConfig);
int Alloc_Shared_Memory_AudSpectrum(void*, char* pbuf, int size);
void Set_Enable_AudSpectrum(void* pUserConfig, int EnableDisp);
#ifdef SPEC_RING_BUF
s32 AUD_SpecWriteBuf(U32 wHandle, s32 nConsumeSize, u8 *pSrcAddr);
S32 AUD_GetSpectrumData(void *pData, u32 nDataSize);

#endif


#ifdef __cplusplus
    }
#endif

#endif
