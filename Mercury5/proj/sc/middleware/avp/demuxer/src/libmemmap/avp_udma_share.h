#ifndef UDMA_SHARE_H
#define UDMA_SHARE_H

#include "avp_memmap.h"
/* Linear memory area descriptor */

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct MEMMAP
{
    u32 *miuPointer;
    u32 miuAddress;
    u32 size;
} MEMMAP_t;


void MMAPInit(u8 *buf);
i32  MMAPMalloc(u32 size, MEMMAP_t * info);

#if defined(__cplusplus)
}
#endif

#endif // UDMA_SHARE_H