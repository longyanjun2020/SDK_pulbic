#ifndef _AUD_SPECTRUM_MAP_H
#define _AUD_SPECTRUM_MAP_H

#include "vm_types.ht"

s32 MAP_SpectrumInit(u32 sample_rate, u8 channels);
s32 MAP_SpectrumUpdate(void *pInst, u8* aud_outbuf, u32 aud_outbufsize);
s32 Midi_SpectrumUpdate(void);
void MAP_SpectrumClose(void);

#endif
