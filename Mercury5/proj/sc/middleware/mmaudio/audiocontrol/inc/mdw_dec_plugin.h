#ifndef _MDW_DEC_PLUGIN_H_
#define _MDW_DEC_PLUGIN_H_

#include "vm_types.ht"

s32 init_audio_codec(void *player, s32 data_fmt);
s32 fnAudioPlayer_setAddr(void *player, s32 data_fmt);
s32 fnAudioPlayerReleaseMem(void *pInst, s32 data_fmt);
s32 fnMidiSldlmLoad(void);

#endif
