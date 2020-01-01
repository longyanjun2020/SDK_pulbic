////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef MS_MEM_H
#define MS_MEM_H

#ifdef __ARMCC_VERSION
#pragma diag_suppress 167
#endif

enum memory_pool_e
{
    HEAP_MEMORY_POOL = 0,
    PHYS_MEMORY_POOL,
    SRAM_MEMORY_POOL,
};

typedef struct memory_slot_s
{
    void           *buffer;
    unsigned int    size;
    int8_t          handle;
    int8_t          used;
} memory_slot_st;

#define MAX_SLOT_COUNT  70

/**
 * Memory allocation of size byte with alignment suitable for all
 * memory accesses (including vectors if available on the
 * CPU). ms_malloc(0) must return a non NULL pointer.
 */
void *ms_malloc(void *ctx, int handle, unsigned int size);
void *ms_calloc(void *ctx, int handle, unsigned int size);

/**
 * Free memory which has been allocated with ms_malloc(z)()
 * NOTE: ptr = NULL is explicetly allowed
 */
void internal_ms_freep(void *ctx, int handle, void **ptr);

void ms_heap_cleanup(void *ctx);

#define ms_freep(c, a, b) internal_ms_freep(c, a, (void **)b)

#endif /* MS_MEM_H */
