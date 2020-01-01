/**
* @file RingBufferItf.h
*
* This header file defines the interface of ring buffer
*
*/

#ifndef __RINGBUFFERITF_H__
#define __RINGBUFFERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum RingBuffErrCode_e_
{
    RING_BUFFER__OK,
    RING_BUFFER__FAIL,
    RING_BUFFER__FULL,
    RING_BUFFER__EMPTY,
} RingBuffErrCode_e;

typedef struct stream_ring_buffer_
{
    s32 s32widx;
    u32 u32wcycle;
    u32 padding1[6]; // 32bytes aligned

    s32 s32ridx;
    u32 u32rcycle;
    u32 padding2[6]; // 32bytes aligned

    u8 *u32RingBaseMMIAddr;
	u8 *u32RingBaseM3Addr;
    s32 s32ringbufsize;
    u32 u32ringinit;
    u32 u32ring_off_t;
	s32 s32m3bufflag;
    u32 padding3[2]; // 32bytes aligned
} RingBuffer_t;

typedef void* RingBufferHandle_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
void RingBuffer_Init(RingBufferHandle_t pRingBuffHdl, u8 *pBaseaddr, u32 uBuflen);
RingBuffErrCode_e RingBuffer_Push(RingBufferHandle_t pRingBuffHdl, u8* pBuffer, s32 s32Len);
RingBuffErrCode_e RingBuffer_Pop(RingBufferHandle_t pRingBuffHdl, u8* pBuffer, s32 s32Len);
//gets available size, for pop
s32 RingBuffer_GetFilledDataSize(RingBufferHandle_t pRingBuffHdl);
//gets free size , for push
s32 RingBuffer_GetFreeSpaceSize(RingBufferHandle_t pRingBuffHdl);
//get m3 play status
u32 RingBuffer_GetM3PlayStatus(RingBufferHandle_t pRingBuffHdl);

#endif //__RESCTRLITF_H__
