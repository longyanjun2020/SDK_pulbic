/*
** heap.h: the heap header file.
**
** Copyright (C) 2007-2008 SKY-MOBI AS.  All rights reserved.
**
** This file is part of the simple gui library.
** It may not be redistributed under any circumstances.
*/

#ifndef _SGL_HEAP_H
#define _SGL_HEAP_H

#include "sgl_types.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * \brief A type definition for handle to block heap.
 */
typedef DWORD HBLOCKHEAP;

/**
 * \brief Initialize the block heap.
 *
 * \attention the buffersize and blocksize must can be divided exactly by 4, 
 * And the buffersize must can be divided exactly by blocksize.
 *
 * \param buffer the pointer to data buffer
 * \param buffersize the data buffer size
 * \param blocksize the block size
 * \return 
 *	- the heap handle on success
 *	- NULL otherwise
 */
HBLOCKHEAP GUIAPI BlockHeap_Initialize(VOID* buffer, int buffersize, int blocksize);

/**
 * \brief Allocate a block from a the block heap.
 *
 * \param pHeap the pointer to block heap handle
 * \return the allocated block address, NUL when no empty block.
 */
VOID* GUIAPI BlockHeap_Alloc(HBLOCKHEAP* pHeap);

/**
 * \brief Free a block to the block heap.
 *
 * \param pHeap the pointer to block heap handle
 * \param pBlock the block address
 */
VOID GUIAPI BlockHeap_Free(HBLOCKHEAP* pHeap, VOID* pBlock);


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _SGL_HEAP_H */

