#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

#ifndef _IMGCODEC_MEMMGR_H_
#define _IMGCODEC_MEMMGR_H_
#include "imgcodec_common.h"

typedef enum
{
    IMAGE_MEMTYPE_SYS_DRAM_PHYSICAL,
    IMAGE_MEMTYPE_SYS_DRAM_VIRTUAL,
    IMAGE_MEMTYPE_SYS_IRAM_PHYSICAL
} Image_MemType;

void *imageCodec_allocateMem(u32 size, Image_MemType memType);
void imageCodec_releaseMem(void *ptr);
u32 imageCodec_getFreeHeapSize(void);
#endif
#endif

