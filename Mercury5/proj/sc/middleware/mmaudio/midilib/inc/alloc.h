#if ! defined( common_alloc_h )
#define common_alloc_h
/*****************************************************************************/
/* common_alloc_h                                                            */
/* alloc.h                                                                   */
/* 2007/08                                                                   */
/* Copyright 2007 FAITH,INC.                                                 */
/* H.M.                                                                      */
/*****************************************************************************/

#define NO_MALLOC //ccc
#include "vm_types.ht"

extern U8 *gU8MIDIStackBufPtr;

#if 0
extern U8 MIDIBufSUZAKUCONTEXT[16];
extern     U8 MIDIBufCTX505[8];
extern     U8 MIDIBufDEVICECONTEXT[32];
extern    U8 MIDIBufDRIVERCONTEXT[24];
extern    U8 MIDIBufSYNTHCONTEXT[8];
extern    U8 MIDIBufSYNTHDRVCONTEXT[20];
extern     U8 MIDIBufSYNTHAPICONTEXT[428];
extern     U8 MIDIBufAPORT[48];
extern     U8 MIDIBufSAMPLEFRAME[1024];
//extern     U8 MIDIBufAVIF[768]; // 32 polyphony
extern     U8 MIDIBufAVIF[1536]; // 64 polyphony
//extern     U8 MIDIBufVREG[7168]; //224*32, 32 polyphony
extern     U8 MIDIBufVREG[14336]; //224*64, 64 polyphony
#endif

extern
void *
ALLOC(
    unsigned long   bytes
);

extern
void
FREE(
    void *  p
);

/*****************************************************************************/
#endif  /* ! defined( common_alloc_h ) */
