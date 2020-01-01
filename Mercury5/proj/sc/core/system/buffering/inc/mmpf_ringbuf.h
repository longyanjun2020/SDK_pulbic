#ifndef _MMPF_RINGBUF_H_
#define _MMPF_RINGBUF_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_media_def.h"
#include "aitu_ringbuf.h"
#include "aitu_calendar.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define FORMAT_PER_FRAME            (0) //Set 1 to enable recording format for each frame

#define RING_MAX_FRAME_QUEUE_SIZE   (16) //note the size must be 2^n and less than 256
#define RING_MAX_FRAME_QUEUE_MASK   (RING_MAX_FRAME_QUEUE_SIZE - 1)

#define MMPF_RING_TRACE_ACCESS      (0)

#if (MMPF_RING_TRACE_ACCESS)
    void MMPF_Ring_DumpPtr(MMP_USHORT usEncID, char* szTag);
#else
    #define MMPF_Ring_DumpPtr(ID, tag)
#endif

#define RING2_MAX_FRAME_QUEUE_SIZE  (40)

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _MMPF_FRAME_3AINFO {
    MMP_ULONG               ulExpo[2];
    MMP_LONG                ulEvbias[2];
    MMP_USHORT              usIso;
} MMPF_FRAME_3AINFO;

typedef struct _MMPF_FRAME_INFO {
    MMP_ULONG               ulFrameAddr;
    MMP_ULONG               ulFrameSize;
    MMP_ULONG               ulFrameTick;
    MMP_UBYTE               ubFrameType;
    AUTL_DATETIME           sTimeInfo;
    MMPF_FRAME_3AINFO       s3AInfo;
} MMPF_FRAME_INFO;

typedef struct _MMPF_FRAME_STATIST {
    MMP_ULONG               ulWriteCnt;
    MMP_ULONG               ulDropCnt;
    MMP_ULONG               ulLostCnt;
    MMP_ULONG               ulReadCnt;
} MMPF_FRAME_STATIST;

typedef struct _MMPF_RING2_BUF {
    void*                   pCompHandle;
    MMP_ULONG               ulBufAddr;          // The ring buffer start address
    MMP_ULONG               ulBufSize;          // The ring buffer total size
    MMP_ULONG               ulBufReadPtr;       // The read-out pointer of compressed buffer
    MMP_ULONG               ulBufWritePtr;      // The write-in pointer of compressed buffer
    MMP_ULONG               ulBufReadWrap;      // The wrap times of read pointer
    MMP_ULONG               ulBufWriteWrap;     // The wrap times of write pointer
    MMP_ULONG               ulFrameRsvdSize;    // The reserved size for next frame.
    MMP_USHORT              usAlignment;        // The ring buffer address alignment
    MMP_UBYTE               ubStatus;           // The ring buffer status
        /*-DEFINE-----------------------------------------------------*/
        #define RINGBUF_STATE_UNDEF             (0x00)
        #define RINGBUF_STATE_EMPTY             (0x01)
        #define RINGBUF_STATE_UPDATE_WR_IDX     (0x02)
        #define RINGBUF_STATE_UPDATE_RD_IDX     (0x03)
        #define RINGBUF_STATE_REWIND_IDX        (0x04)
        #define RINGBUF_STATE_BUF_OVERFLOW      (0x05)
        #define RINGBUF_STATE_BUF_UNDERFLOW     (0x06)
        /*------------------------------------------------------------*/
    
    /* Frame Queue */
    MMP_USHORT              usQWrIdx;           // The write index.
    MMP_USHORT              usQRdIdx;           // The read index
    MMP_USHORT              usQWrWrap;          // The write wrap.
    MMP_USHORT              usQRdWrap;          // The read wrap.
    MMP_ULONG               ulInterval;
    MMPF_FRAME_STATIST      stStatInfo;         // The frame statistics
    MMPF_FRAME_INFO         stFrameInfoQ[RING2_MAX_FRAME_QUEUE_SIZE];
} MMPF_RING2_BUF;

typedef MMP_BOOL (*MMPF_Ring_MoveCallback) (MMP_M_STREAMCB_ACTION cbmode, MMP_ULONG framesize, MMP_M_STREAM_INFO* moveinfo);

typedef struct _MMPF_FRAME_RING_BUF             *MMPF_FRAME_RING_BUF_HANDLE;
typedef struct _AUTL_RINGBUF                    *AUTL_RINGBUF_HANDLE;

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

// For stream ID. It describes the purpose and usage of the stream.
typedef enum _MMPF_STREAM_RING_ID {
    VIDEO1_RING_STREAM = 0,
    VIDEO2_RING_STREAM,
    AUDIO_RING_STREAM,
    MAX_RING_STREAM
} MMPF_STREAM_RING_ID;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

// Initialization
void        MMPF_FrameRing_SetMoveCallback(MMPF_Ring_MoveCallback cb);
void        MMPF_FrameRing_SetThresholdCallback(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_ULONG (*pfCalThreshold)(MMP_ULONG frameSize));
void        MMPF_FrameRing_ConfigBuffer(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize,
                                        MMP_USHORT usAlignment, MMP_BOOL bUseDma);
MMP_ERR     MMPF_FrameRing_LinkMgrComponent(MMPF_FRAME_RING_BUF_HANDLE pRing, void* pCompHandle);

// Operation
void        MMPF_FrameRing_Flush(MMPF_FRAME_RING_BUF_HANDLE pRing);
MMP_BOOL    MMPF_FrameRing_SyncWrPtr(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_ULONG ptr, MMP_ULONG wrap);
MMP_BOOL    MMPF_FrameRing_AddFrame(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_ULONG CurSize, MMP_M_STREAMCB_CODEC format, MMP_ULONG time, void* pDbg);
MMP_BOOL    MMPF_FrameRing_MoveFrame(MMPF_FRAME_RING_BUF_HANDLE pRing);
void        MMPF_FrameRing_ResetReadPtr(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_ULONG ptr, MMP_ULONG wrap);
void        MMPF_FrameRing_GetReadPtr(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_ULONG *ptr, MMP_ULONG *wrap);
void        MMPF_FrameRing_GetWritePtr(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_ULONG *ptr, MMP_ULONG *wrap);
MMP_ULONG   MMPF_FrameRing_GetNextWriteAddr(MMPF_FRAME_RING_BUF_HANDLE pRing);
void        MMPF_FrameRing_CloneAUTL(MMPF_FRAME_RING_BUF_HANDLE pRing, AUTL_RINGBUF* ring, int elementsize);
void        MMPF_FrameRing_AttachBuf(MMPF_FRAME_RING_BUF_HANDLE pRing, char* databuf, int datasize);
void        MMPF_FrameRing_UpdateRing(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_ULONG wr, MMP_ULONG wr_wrap, MMP_ULONG rd, MMP_ULONG rd_wrap);

// Attributes
void        MMPF_FrameRing_SetFrc(MMPF_FRAME_RING_BUF_HANDLE pRing, MMP_LONG lInX1000, MMP_LONG lOutX1000);
void        MMPF_AudioRing_SetResetTrigger(MMPF_FRAME_RING_BUF_HANDLE pRing,MMP_BOOL bEnable);
MMP_BOOL    MMPF_AudioRing_IsResetTrigger(MMPF_FRAME_RING_BUF_HANDLE pRing);

// Initialization
#define MMPF_RING_KEEP_VALUE ((MMP_ULONG) -1)
void        MMPF_StreamRing_Init(void);
void        MMPF_StreamRing_ConfigBuffer(MMP_USHORT usEncID, MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize,
                                         MMP_USHORT usAlignment, MMP_BOOL bUseDma);
void        MMPF_StreamRing_SetFormat(MMP_USHORT usEncID, MMP_M_STREAMCB_CODEC codec);

// Operation
MMP_ERR     MMPF_StreamRing_AddFrame(MMP_USHORT usEncID, MMP_ULONG size, MMP_ULONG ulTime, void* pDbg);
void        MMPF_StreamRing_Reset(MMPF_STREAM_RING_ID usEncID);
MMP_BOOL    MMPF_StreamRing_Stop(MMPF_STREAM_RING_ID usEncID);
MMP_BOOL    MMPF_StreamRing_Start(MMPF_STREAM_RING_ID usEncID, MMP_BOOL bWaitForSync);
MMP_BOOL    MMPF_StreamRing_Sync(MMPF_STREAM_RING_ID usEncID, MMP_ULONG ptr, MMP_ULONG wrap);
MMP_BOOL    MMPF_StreamRing_Flush(MMP_USHORT usEncID);
MMP_BOOL    MMPF_StreamRing_FlushAll(void);

// Type-casting
MMPF_FRAME_RING_BUF_HANDLE MMPF_StreamRing_GetFrameRing(MMPF_STREAM_RING_ID usEncID);
AUTL_RINGBUF_HANDLE MMPF_StreamRing_GetAutlRing(MMPF_STREAM_RING_ID usEncID);

// Attributes
MMP_BOOL    MMPF_StreamRing_IsStreaming(MMPF_STREAM_RING_ID usEncID);
MMP_BOOL    MMPF_StreamRing_IsEnabled(MMPF_STREAM_RING_ID usEncID);
void        MMPF_StreamRing_SetEnable(MMPF_STREAM_RING_ID usEncID, MMP_BOOL bEnable);
MMP_ULONG   MMPF_StreamRing_GetTimeMs(MMP_USHORT usEncID);
MMP_ULONG   MMPF_StreamRing_SetTimeMs(MMP_USHORT usEncID, MMP_ULONG ulNewTime);

// Ring2 Function (Use Frame Index)
MMP_ERR MMPF_Ring2_InitBuf( MMP_UBYTE   ubRingSel,
                            MMP_ULONG   ulAddr,
                            MMP_ULONG   ulSize,
                            MMP_ULONG   ulRsvdSize,
                            MMP_USHORT  usAlignment,
                            MMP_ULONG   ulInterval);
MMP_ERR     MMPF_Ring2_LinkMgrComponent(MMP_UBYTE ubRingSel, void* pCompHandle);
MMP_ERR     MMPF_Ring2_ReadFrameInfo(MMP_UBYTE ubRingSel, MMPF_FRAME_INFO *pFrameInfo);
MMP_ERR     MMPF_Ring2_AddFrameInfo(MMP_UBYTE ubRingSel, MMPF_FRAME_INFO *pCurFrameInfo);
MMP_ULONG   MMPF_Ring2_GetWritedFrameCnt(MMP_UBYTE ubRingSel);
MMP_ULONG   MMPF_Ring2_GetReadFrameCnt(MMP_UBYTE ubRingSel);
MMP_BOOL    MMPF_Ring2_IsFrameQEmpty(MMP_UBYTE ubRingSel);

#endif //_MMPF_RINGBUF_H_
