#ifndef __MDL_AUD_WAV_TYPES_H__
#define __MDL_AUD_WAV_TYPES_H__

#include "mdl_aud_forward.h"

// mdl_aud_wav_api.h
// \brief WAVE file starts from the RIFF signature
struct _st_wave_header__
{
    u8	    riffID[4];    //RIFF
    u32	    riffSIZE;
    u8	    riffFORMAT[4];//WAVE
};

//===============================================
// \brief characters of the WAVE
struct _st_wave_form__
{
    u16	    wFormatTag;     // 1 : PCM, others, compressed data
    u16	    nChannels;      // 1 : mono, 2 : stereo
    u32	    nSamplesPerSec; //Sample rate, 8000, 44100, etc.
    u32	    nAvgBytesPerSec;//SampleRate * NumChannels * BitsPerSample/8
    u16     nBlockAlign;    //NumChannels * BitsPerSample/8
    u16     wBitsPerSample; //8 bits = 8, 16 bits = 16, etc.
};

//===============================================
// \brief subchunk 1
struct _st_wave_fmt__
{
    u8          fmtID[4];        //"fmt "
    u32         fmtSIZE;
    MSWAVEFORM  fmtFORMAT;
};

//===============================================
// \brief data chunk
struct _st_wave_data_chunk__
{
    u8          dataID[4];   // "data"
    u32         dataSIZE;
};

//===============================================
// \brief WAVE file header
struct _st_pcm_wave_header__
{
    MSWAVEHEADER    RIFF;
    MSWAVEFMT       FMT;
    MSDATACHUNK     DATA;
    //u32          Buffer;	//Address of Data
};

struct WAVEFORM_
{
	u16 wFormatTag;
	u16 nChannels;
	u32 nSamplesPerSec;
	u32 nAvgBytesPerSec;
	u16 nBlockAlign;
	u16 wBitsPerSample;
};

struct RIFF_
{
	u8 riffID[4];
	u32 riffSIZE;
	u8 riffFORMAT[4];
};

struct FMT_
{
	u8 fmtID[4];
	u32 fmtSIZE;
	WAVEFORM fmtFORMAT;
};

struct DATA_
{
	u8 dataID[4];
	u32 dataSIZE;
};

struct CWAVEFILE {
	u32 baseAddress;
	u32 length;
	u32 dataAddress;
	RIFF* pRIFF;
	FMT* pFMT;
	DATA wavDATA;
};
// end mdl_aud_wav_api.h
#endif // __MDL_AUD_WAV_TYPES_H__

