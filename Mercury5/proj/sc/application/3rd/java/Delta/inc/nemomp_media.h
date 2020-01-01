#ifndef __NEMOMP_MEDIA_H__
#define __NEMOMP_MEDIA_H__

#include "nemomp_media_ctrl.h"

enum
{
    NM_MEDIA_TYPE_MIDI = 1,
    NM_MEDIA_TYPE_WAVE = 2,
    NM_MEDIA_TYPE_MP3 = 4,
    NM_MEDIA_TYPE_TONE = 8,
    NM_MEDIA_TYPE_AAC = 16,
    NM_MEDIA_TYPE_AWB = 32,
    NM_MEDIA_TYPE_AMR = 64,
    NM_MEDIA_TYPE_AU = 128,
    NM_MEDIA_TYPE_IMY = 256,
    NM_MEDIA_TYPE_WMA = 512,
    NM_MEDIA_TYPE_M4A = 1024,
    NM_MEDIA_TYPE_MMF = 2048,
    NM_MEDIA_TYPE_CAMERA = 16384,
    NM_MEDIA_TYPE_3GP = 131072,
    NM_MEDIA_TYPE_MP4 = 262144,
    NM_MEDIA_TYPE_AVI = 524288,
    NM_MEDIA_TYPE_WMV = 1048576,
    NM_MEDIA_TYPE_MOV = 2097152,
    NM_MEDIA_NO_OF_AUDIO_TYPE
};

extern void nemomp_media_initialize(void);
extern void nemomp_media_finalize(void);

extern nm_bool nemomp_media_audio_open(int mma_type, int java_player, nm_char* data, nm_wchar* filename, int count);
extern int nemomp_media_audio_play_tone(int note, int duration, int volumne);
extern nm_bool nemomp_media_audio_play(int mma_type, int java_player);
extern nm_bool nemomp_media_audio_pause(int mma_type, int java_player);
extern void nemomp_media_audio_close(int mma_type, int java_player);
extern nm_bool nemomp_media_audio_get_duration_info(int mma_type, nm_wchar* file_path, nm_uint8* data, nm_uint32 data_len, nm_metadata_ctrl* meta, nm_uint32* pDuration);
extern int nemomp_media_audio_set_media_time(int mma_type, int java_player, int now);
extern int nemomp_media_audio_get_media_time(int mma_type, int java_player);
extern int nemomp_media_audio_set_volume(int mma_type, int java_player, int volumne);


#endif /* __NEMOMP_MEDIA_H__ */
