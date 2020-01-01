#ifndef __MDL_AUD_WAV_FORWARD_H__
#define __MDL_AUD_WAV_FORWARD_H__

#include "vm_types.ht"
/// mdl_aud_wav_api.h
typedef short	AudioWord;
typedef unsigned char	AudioByte;
typedef struct _st_wave_header__ MSWAVEHEADER;
typedef struct _st_wave_header__ *PMSWAVEHEADER;
typedef struct _st_wave_form__ MSWAVEFORM;
typedef struct _st_wave_form__ *PMSWAVEFORM;
typedef struct _st_wave_fmt__ MSWAVEFMT;
typedef struct _st_wave_fmt__ *PMSWAVEFMT;
typedef struct _st_wave_data_chunk__ MSDATACHUNK;
typedef struct _st_wave_data_chunk__ *PMSDATACHUNK;
typedef struct _st_pcm_wave_header__ MSWAVEFILE;
typedef struct _st_pcm_wave_header__ *PMSWAVEFILE;
typedef struct WAVEFORM_ WAVEFORM;
typedef struct RIFF_ RIFF;
typedef struct FMT_ FMT;
typedef struct DATA_ DATA;
typedef struct CWAVEFILE CWaveFile;

#endif // __MDL_AUD_WAV_FORWARD_H__
