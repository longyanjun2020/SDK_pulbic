//==============================================================================
//
//  File        : aitu_ringbuf.h
//  Description : Header File of Generic Ring buffer Utility
//  Author      : Alterman
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AITU_RINGBUF_H_
#define _AITU_RINGBUF_H_

/** @addtogroup AIT_UTILITY
 *  @{
 */

//==============================================================================
//
//                              INCLUDE FILES
//
//==============================================================================

#include "mmpf_typedef.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

/*
 * Ring buffer error codes
 */
#define RINGBUF_SUCCESS         (0)
#define RINGBUF_ERR_NULL_HANDLE (-1)
#define RINGBUF_ERR_OVERFLOW    (-2)
#define RINGBUF_ERR_UNDERFLOW   (-3)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

/*
 * Ring buffer pointer
 */
typedef struct {
    MMP_ULONG   rd;         ///< read pointer
    MMP_ULONG   wr;         ///< write pointer
    MMP_ULONG   rd_wrap;    ///< read pointer wrap count
    MMP_ULONG   wr_wrap;    ///< write pointer wrap count
} AUTL_RINGBUF_PTR;

/*
 * Ring buffer handler
 */
typedef struct _AUTL_RINGBUF{
    void            *buf;   ///< ring buffer address
    MMP_ULONG        size;  ///< ring buffer size   unit:byte
    AUTL_RINGBUF_PTR ptr;   ///< ring buffer pointers
} AUTL_RINGBUF;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

int AUTL_RingBuf_Init(AUTL_RINGBUF *ring, void *buf, MMP_ULONG size);
int AUTL_RingBuf_Fork(AUTL_RINGBUF *src, AUTL_RINGBUF *dst);
int AUTL_RingBuf_StrictCommitRead(AUTL_RINGBUF *ring, MMP_ULONG size);
int AUTL_RingBuf_StrictCommitWrite(AUTL_RINGBUF *ring, MMP_ULONG size);
int AUTL_RingBuf_CommitRead(AUTL_RINGBUF *ring, MMP_ULONG size);
int AUTL_RingBuf_CommitWrite(AUTL_RINGBUF *ring, MMP_ULONG size);
int AUTL_RingBuf_SpaceAvailable(AUTL_RINGBUF *ring, MMP_ULONG *space);
int AUTL_RingBuf_DataAvailable(AUTL_RINGBUF *ring, MMP_ULONG *data_size);
MMP_BOOL AUTL_RingBuf_Empty(AUTL_RINGBUF *ring);
MMP_BOOL AUTL_RingBuf_Full(AUTL_RINGBUF *ring);

/// @}

#endif //_AITU_RINGBUF_H_
