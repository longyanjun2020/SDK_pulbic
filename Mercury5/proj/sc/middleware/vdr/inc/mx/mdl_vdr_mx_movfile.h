////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_mx_movfile.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_MOVFILE_H__
#define __MDL_VDR_MX_MOVFILE_H__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

#include "mdl_vdr_mx_def.h"
#include "mdl_vdr_mx_mov.h"
#include "mdl_vdr_mx_movtrack.h"

//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------
typedef struct tagMOVFile
{
    FILE_HANDLE     m_pFile;
    uint8_t *pcached_buf;
    uint32_t cached_size;
    uint32_t cached_offset;

    char            m_mode;
    char            m_append;

    MOVATOM*        m_pRootAtom;
    MP4TrackId      m_currentusedtrackid;
    MOVTRACKARRAY   m_pTracks;

    // cached properties
    uint32_t        *m_pModificationProperty;
    uint32_t        *m_pTimeScaleProperty;  // glocal time scale
    uint32_t        *m_pDurationProperty;

    void              *m_pMuxInst;
} MOVFILE, *PMOVFILE;
//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------
U8 mxMP4FileCreate(MOVFILE *pfile,
                    int add_ftyp, int add_iods,
                    char* majorBrand, uint32_t minorVersion,
                    char** supportedBrands, uint32_t supportedBrandsCount);
U8 mxMP4FileClose(MOVFILE *pfile);
U8 mxMP4FileSetTimeScale(MOVFILE *pfile, uint32_t value);
void mxMP4FileWritePacket(MOVFILE *pfile, MP4AVPacket *av_packet);
BOOL mxMP4FileWriteSample(MOVFILE *pfile, MP4TrackId trackId);
void mxMP4FileFlushSample(MOVFILE *pfile);
MP4TrackId mxMP4FileAddMp3AudioTrack(MOVFILE *pfile,
							uint32_t type,
							uint32_t timeScale,
							uint32_t duration,
							uint32_t sampleSize);
MP4TrackId mxMP4FileAddAmrAudioTrack(MOVFILE *pfile,
							uint32_t type,
							uint32_t timeScale,
							uint32_t duration,
							uint32_t sampleSize);
MP4TrackId mxMP4FileAddPCMAudioTrack(MOVFILE *pfile,
							uint32_t type,
							uint32_t timeScale,
							uint32_t duration,
							uint32_t sampleSize);
MP4TrackId mxMP4FileAddAacAudioTrack(MOVFILE *pfile,
							uint32_t timeScale,
							uint32_t duration,
							uint32_t sampleSize,
							uint32_t profile,
							uint32_t level);
MP4TrackId mxMP4FileAddH263VideoTrack(MOVFILE *pfile,
                                    uint16_t syncStrategy,
									uint32_t timeScale,
                                    MP4Duration sampleDuration,
									uint16_t width,
                                    uint16_t height,
									uint8_t h263Profile,
                                    uint8_t h263Level,
									uint32_t avgBitrate,
									uint32_t maxBitrate,
                                    uint8_t maceTag);
MP4TrackId mxMP4FileAddMPEG4VideoTrack(MOVFILE *pfile,
									uint16_t syncStrategy,
									uint32_t timeScale,
                                    MP4Duration sampleDuration,
									uint16_t width,
                                    uint16_t height,
									uint8_t profile,
                                    uint8_t level,
									uint32_t avgBitrate,
                                    uint32_t maxBitrate,
                                    uint8_t maceTag);
void mxMP4FileSetTrackProperty(MOVFILE *pfile, MP4TrackId trackId, const char* name, void *value);
void mxMP4FileCacheProperties(MOVFILE *pfile);
// IO API
FILE_POS mxMuxMP4FileGetPosition(MOVFILE *pfile);
void mxMuxMP4FileSetPosition(MOVFILE *pfile, FILE_POS pos);
void mxMP4FileWriteUInt16(MOVFILE *pfile, uint16_t value);
void mxMP4FileWriteUInt32(MOVFILE *pfile, uint32_t value);
void mxMP4FileWriteBytes(MOVFILE *pfile, const uint8_t* pBytes, uint32_t numBytes);
void mxMP4FileWriteBytesRemainInCache(MOVFILE *pfile);
void mxMP4FileFinishWrite(MOVFILE *pfile);
void mxMP4FileWriteUInt8(MOVFILE *pfile, uint8_t value);
void mxMP4FileWriteFixed32(MOVFILE *pfile, int32_t value);
void mxMP4FileWriteFixed16(MOVFILE *pfile, int16_t value);
void mxMP4FileCachedBufferRealloc(void *pMuxInst, uint32_t track_id, uint32_t atom_id,
                                    void **page, uint8_t **cluster_base, uint32_t *curr_page_index,
									uint32_t entry_size, uint32_t entry_index);
extern uint32_t _14496_12_mx_fill_cached_buffer(void *pMuxObj, uint32_t track_index, uint32_t atom_id, uint32_t offset, uint32_t size, uint8_t *buffer);
#define MP4FillCachedBuffer(muxobj, track_index, atom_id, offset, size, buffer) \
    _14496_12_mx_fill_cached_buffer(muxobj, track_index, atom_id, offset, size, buffer)
extern int _14496_12_mx_flush_cached_buffer(void *pMuxObj, uint32_t track_id, uint32_t atom_id, uint8_t *buffer, uint32_t size, BOOL prealloc);
#define mxMP4FileCachedBufferFlush(muxobj, track_id, atom_id, buffer, size, prealloc) \
	_14496_12_mx_flush_cached_buffer(muxobj, track_id, atom_id, buffer, size, prealloc)
#endif // __MDL_VDR_MX_MOVFILE_H__

