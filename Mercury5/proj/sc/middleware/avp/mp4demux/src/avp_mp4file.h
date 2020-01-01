////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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


#ifndef MP4FILE_H
#define MP4FILE_H

#include "avp_mp4def.h"
#include "avp_mp4atom.h"
#include "avp_mp4track.h"
#include "avp_ms_input.h"

#ifdef SUPPORT_KMV
#include "avp_kmvBuffer.h"
#endif

#include "avp_mvc_demuxer.h"

#ifdef USE_STREAM_LIB
#include "avp_streaming.h"
#endif

typedef struct tagMP4File
{
    FILE_POS        m_fileSize;

    MP4ATOM*        m_pRootAtom;
    MP4TRACKARRAY   m_pTracks;

    uint32_t        m_numVideoTracks;
    uint32_t        m_numAudioTracks;
    uint32_t        m_numSubtitleTracks;

    // cached properties
    uint32_t        *m_pTimeScaleProperty;

    // ringbuf api
    const mvc_allocator_st *allocator;
    void            *alloc_ctx;
    int             new_pts;

    cb_io_st        m_cbio;
    // the desired atom to be parsed in demux open stage
    char            m_targetType[5];
    FILE_POS        m_targetTypePos;
#ifdef USE_STREAM_LIB
    cb_buffer_st    cbuffer;
#endif
    void           *mem_ctx;

#ifdef SUPPORT_KMV
        uint32_t        m_metaoffset;
        uint32_t        m_tSTCO;
        uint32_t        m_nChunk;
        uint32_t        m_SampleInChunk;
        KMVCACHE        m_STCOKMV;
        KMVCACHE        m_STSZKMV;
        KMVCACHE        m_MAPBUF;
        uint32_t        m_MP4offset;
#endif
} MP4FILE, *PMP4FILE;

//-----------------------------------------------------------------------------
// for demuxer
//-----------------------------------------------------------------------------
uint8_t MP4FileOpen(MP4FILE *pfile, const cb_io_st *input, int ringbuf_size);
uint8_t MP4FileClose(void *ctx, MP4FILE *pfile);

// IO API
FILE_POS MP4FileGetPosition(MP4FILE *pfile);
FILE_POS MP4FileSetPosition(MP4FILE *pfile, FILE_POS pos);
FILE_POS MP4FileGetSize(MP4FILE *pfile);

//
// For Read
//
uint8_t MP4FileRead(void *ctx, MP4FILE *pfile);
uint32_t MP4FileReadBytes(MP4FILE *pmp4file, void *pBytes, uint32_t numBytes);
uint8_t MP4FileReadUInt8(MP4FILE *pfile);
uint16_t MP4FileReadUInt16(MP4FILE *pfile);
void MP4FileSkipBytes(MP4FILE *pfile, uint32_t numBytes);

#ifdef USE_ATOM_BUFFERRED_READ
uint32_t MP4FileCacheBufferredPage(MP4FILE *mp4_file, uint8_t *page, uint32_t *curr_page_index,
                                    FILE_POS atom_file_pos, FILE_POS table_size, uint32_t entry_size, uint32_t entry_index
                                    , uint32_t *buffer_offset);

uint32_t MP4FileReadBufferredBytes(uint8_t* pBufferredBytes, uint8_t* pBytes, uint32_t *read_start, uint32_t numBytes);
uint16_t MP4FileReadBufferredUInt16(uint8_t* pBufferredBytes, uint32_t *read_start);
uint32_t MP4FileReadBufferredUInt32(uint8_t* pBufferredBytes, uint32_t *read_start);
#endif

uint32_t KMVFileCacheBufferredPage(MP4FILE *mp4_file, uint8_t *page, uint32_t *curr_page_index,
                                   FILE_POS atom_file_pos, uint32_t entry_size, uint32_t entry_index
                                   , uint32_t *buffer_offset, uint32_t CacheSize);

uint32_t MP4FileReadUInt32(MP4FILE *pfile);
uint64_t MP4FileReadUInt64(MP4FILE *pfile);
uint16_t MP4FileReadFixed16(MP4FILE *pfile);
uint16_t MP4FileReadFixed32(MP4FILE *pfile);
uint32_t MP4FileReadSample(MP4FILE *pfile,
                    MP4TrackId trackId,
                    MP4SampleId sampleId,
                    uint8_t* pBytes,
                    uint32_t* pNumBytes,
                    MP4Timestamp* pStartTime,
                    MP4Duration* pDuration,
                    uint32_t* pIsSyncSample);
uint32_t MP4FileReadSampleInfo(MP4FILE *pfile,
                    MP4TrackId trackId,
                    MP4SampleId sampleId,
                    uint32_t* pOffset,
                    uint32_t* pNumBytes,
                    MP4Timestamp* pStartTime,
                    MP4Duration* pDuration,
                    uint32_t* pIsSyncSample);

//This function should be used when samples duration are constant
int MP4FileGetFrameIdxbyTime(MP4FileHandle hFile, MP4TrackId trackId, MP4Timestamp reftime, MP4SampleId *pframeidx);

void MP4TrackGetSampleTimes(MP4TRACK *pTrack, MP4SampleId sampleId, MP4Timestamp* pStartTime, MP4Duration* pDuration);
void MP4TrackGetSampleTimes_BufMode(MP4TRACK *pTrack, MP4SampleId sampleId, MP4Timestamp* pStartTime, MP4Duration* pDuration);

#endif /* MP4FILE_H */
