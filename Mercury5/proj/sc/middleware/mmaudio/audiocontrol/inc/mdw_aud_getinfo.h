#ifndef AUD_GETINFO_H
#define AUD_GETINFO_H

#include <stdint.h>
#include "vm_types.ht"

typedef struct read_file_from_NOR
{
    u8 *u8_Sharebuffer;
    s32 s32_Sharebufferlen;
}READ_FILE_FROM_NOR;

#ifndef PIONEER_PLAYER
typedef struct _audio_info{
    u32 u32SamplRate;
    u32 u32BitRate;
    u32 u32TotalTime;
    s32 s32filesize;
    u8 *u8mem_sharebuf;
    u32 u32mem_sharebufsize;
    u8 u8input_path;
    u8 u8BitRateType;
    u8 u8Channel_info;
    u8 u8datafmt;
    u8 u8datafmt_profile1;
    u8 u8datafmt_profile2;
    u8 u8AudioIsSeekable;
} audio_info;
#endif

typedef struct pcmrawformat_tag {
    u16 nChannels;         /* number of channels (i.e. mono, stereo...) */
    u32 nSamplesPerSec;    /* sample rate */
    u16 wBitsPerSample;
    u16 nBlockAlign;
} PCMRAWFORMAT;

#endif /* MS_MEM_H */
