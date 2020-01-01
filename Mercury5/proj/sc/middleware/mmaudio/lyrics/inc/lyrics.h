#ifndef _WAVDEC_H
#define _WAVDEC_H
#ifdef __cplusplus
extern "C"{
#endif

#ifdef PIONEER_PLAYER
#include "mmp_common_types.h"
#else
//#include "shellmgr.h"
#endif
#include "ms_io.h"
#include "vm_types.ht"


#if 0
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
#endif



//extern u16 nSamplesPerBlock_GInfo;
#if 0
extern PCMWAVEFORMAT2 PCMWaveHeader_Ginfo;
extern IMAADPCMFORMAT IMAADPCMHeader_Ginfo;
extern MSADPCMFORMAT MSADPCMHeader_Ginfo;

//u32 WAVSearchChunk(S8 *filename, u32 chunkID);
//u32 WAVSearchChunk(S8 *filename, u32 chunkID, void *pInst);
//u32 WAVHeaderParser(S8 *filename, u32 *data_pos, u8 only_getinfo);
s32 PlayWAV(S8 *filename);
s32 WAVPlayer_PauseOn(void);
s32 WAVPlayer_PauseOff(void);
s32 WAVPlayer_Stop(void);
u32 WAVPlayer_GetTime(void);
#endif
extern u32 WAVHeaderParser(void *pInst, u32 *data_pos, void *aPCMWaveHeader, void *aIMAADPCMHeader, void *aMSADPCMHeader);

extern void  wav_decoder_funcinit(void *pInst);

extern s32 wav_decoder_open(void *player,
                            u32 *bits_per_sample,
                            u32 *sample_rate,
                            u16 *frame_length,
                            u8 *channels,
                            u32 *para);
extern u32 wav_decoder_close(void *pInst);
extern s32 wav_decoder_decode_data(void *player,
                         u8 **out_buf, u32 *out_size, u32 *iisthreshold,u32 *consume_size);
extern s32 wav_decoder_seek_data(void *player, u32 *seektime);
extern s32 wav_decoder_get_timestamp(void *player, u32 *pu32Pos);
extern void wav_decoder_engine_clock(void *pinst, u8 onoff);

#if 0
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

#if 0
extern u32 WAVPCMFormat_Init_MMP( void* WavPCMHeader);
extern s32 WAVPCMFormat_Proc_MMP(u8 *out_buf, u32 *out_size, u8 *wavstreambuf, u32 *consumed_size, u32 residual_size);


extern u32 WAVIMAADPCMFormat_Init_MMP(void* IMAADPCMAudBlkHeader);
extern s32 WAVIMAADPCMFormat_Proc_MMP(u8 *out_buf, u32 *out_size, u8 *wavstreambuf, u32 *consumed_size, u32 residual_size);


extern u32 WAVMSADPCMFormat_Init_MMP(void* WavPCMHeader);
extern s32 WAVMSADPCMFormat_Proc_MMP(u8 *out_buf, u32 *out_size, u8 *wavstreambuf, u32 *consumed_size, u32 residual_size);
#endif



#ifdef __cplusplus
}
#endif
#endif

