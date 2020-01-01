
#ifndef _MDW_MIDI_COMPRESS_H_
#define _MDW_MIDI_COMPRESS_H_
#include "vm_types.ht"


bool LoadMidiTable(u8  **tablebuf , const u8* ComressTable, u32 CompressLen);
void UnloadMidiTable(u8  **tablebuf);
u8* GetMidiTableAdr(void);
u32 GetMidiTableSize(void);

#endif


