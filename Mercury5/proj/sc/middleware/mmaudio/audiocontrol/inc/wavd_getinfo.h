#ifndef _WAVD_GETINFO_H_
#define _WAVD_GETINFO_H_

#include "vm_types.ht"

extern s32 retrieve_WAV_info2(void *aud_player, void *pInfo);


typedef struct pcmwaveformat_tag2 {
    u16 wFormatTag;        /* format type */
    u16 nChannels;         /* number of channels (i.e. mono, stereo...) */
    u32 nSamplesPerSec;    /* sample rate */
    u32 nAvgBytesPerSec;   /* for buffer estimation */
    u16 nBlockAlign;       /* block size of data */
    u16 wBitsPerSample;
} PCMWAVEFORMAT2;

typedef struct imaadpcmformat_tag {
    u16 nSamplesPerBlock;
    s16 sample0_ch0;
    s16 sample0_ch1;
    u8 index_ch0;
    u8 index_ch1;
} IMAADPCMFORMAT;

typedef struct msadpcmcoef_tag {
	s16 iCoef1;
	s16 iCoef2;
} MSADPCMCOEFSET;

typedef struct msadpcmformat_tag {
    u16 nSamplesPerBlock;
    u16 wNumCoef;
    MSADPCMCOEFSET aCoeff[7];
    u8 bPredictor[2];
    s16 iDelta[2];
    s16 iSamp1[2];
    s16 iSamp2[2];
} MSADPCMFORMAT;

extern u16 nSamplesPerBlock_GInfo;
extern PCMWAVEFORMAT2 PCMWaveHeader_Ginfo;
extern IMAADPCMFORMAT IMAADPCMHeader_Ginfo;
extern MSADPCMFORMAT MSADPCMHeader_Ginfo;

#endif
