#if !defined(SWVENC_UDMA_SHARE_H)
#define SWVENC_UDMA_SHARE_H

/* Linear memory area descriptor */
typedef struct MEMMAP
{
    unsigned char *miuPointer;  // Logical address  (CPU side)
    unsigned int  miuAddress;   // Physical address (IP side)
    unsigned int  size;         // Allocated size
} MEMMAP_t;

void SWVENC_MMAPInit(unsigned char *buf, unsigned int buf_pa, unsigned int buf_size);

// nAlignBytes: The required alignment (in bytes) for the physical address
//    0 means "no matter".
int SWVENC_MMAPMalloc(unsigned int size, MEMMAP_t * memmap, unsigned int nAlignBytes);

#endif // SWVENC_UDMA_SHARE_H
