#ifndef _OUT_STREAM_H_
#define _OUT_STREAM_H_

#include "swvenc_MyLib.h"
#include "swvenc_deftypes.h"

typedef struct _OutStream_t {
	// 1st Level buffer (32-bit)
	int m_nBufferEmptyBits; 
	uint32 m_SmallBuffer;

	// 2nd level buffer 
	uint8* m_pbFrameBuffer;
    uint32 m_nFrameBufSize;
	uint32 m_nByteCount;
    uint32 m_nErrorCode;    // 0: No error.

	// Bitrate Control
	uint32 BC_nCumulativeBits;

	// indicate how many bytes written until now. Reset only when os_Create().
	uint32 m_ulWriteByte;

    // Small buffer bookmark
    int m_nLastEmptyBits;
    uint32 m_LastSmallBuffer;
} OutStream_t;

void os_Create(OutStream_t* ctx);
void os_Destroy(OutStream_t* ctx);

void os_SetWriteBuffer(OutStream_t* ctx, uint8 *pWBuf, uint32 nBufSize);

// put bits number of bits to output buffer , at almost 32 bits
void os_PutBits(OutStream_t* ctx, uint32 value, int bits);

void os_NextStartCode(OutStream_t* ctx);

// Flush write buffer
void os_FlushWBuf(OutStream_t* ctx);

// stuffing '0' to byte align about size byte...
// zero means align to the next byte...
// for byte aligned 
static ALWAYSINLINE void os_Stuffing(OutStream_t* ctx)
{
	if (ctx->m_nBufferEmptyBits & 7)
		os_PutBits(ctx, 0,ctx->m_nBufferEmptyBits&7);
}

// put start code 
static ALWAYSINLINE void os_PutStartCode(OutStream_t* ctx, uint32 code)
{
	os_Stuffing(ctx);
	os_PutBits(ctx, code,32);
}

static ALWAYSINLINE void os_Reset(OutStream_t* ctx)
{
	//m_nBufferEmptyBits = 32;
	ctx->BC_nCumulativeBits = 0;
}

// Restore the status of the 32-bit small buffer
static ALWAYSINLINE void os_RestoreBookmark32(OutStream_t* ctx)
{
    ctx->m_nBufferEmptyBits = ctx->m_nLastEmptyBits;
    ctx->m_SmallBuffer = ctx->m_LastSmallBuffer;
    ctx->BC_nCumulativeBits = 32 - ctx->m_nBufferEmptyBits;
}

// Bookmark the status of the 32-bit small buffer
static ALWAYSINLINE void os_Bookmark32(OutStream_t* ctx)
{
    ctx->m_nLastEmptyBits = ctx->m_nBufferEmptyBits;
    ctx->m_LastSmallBuffer = ctx->m_SmallBuffer;
}

//////////////////////////////////////////////////////////////////////////
// Query 
//////////////////////////////////////////////////////////////////////////

// Total bits including small and big buffer.
// static ALWAYSINLINE int32 os_GetBitsCount(OutStream_t* ctx)
// {
//     return ctx->BC_nCumulativeBits;
// }

// Total byte count in the big buffer.
// NOTE: Before os_FlushWBuf(), small buffer can also containing written bits.
static ALWAYSINLINE int32 os_GetByteCount(OutStream_t* ctx)
{
    return ctx->m_nByteCount;
}

// Total bytes since os_Create()
static ALWAYSINLINE uint32 os_GetStreamBytesCount(OutStream_t* ctx)
{
	return ctx->m_ulWriteByte;
}

static ALWAYSINLINE int32 os_IsBufferLevelHigh(OutStream_t* ctx)
{
    if (ctx->BC_nCumulativeBits >= ctx->m_nFrameBufSize*6)
        return 1;
    return 0;
}

#endif
