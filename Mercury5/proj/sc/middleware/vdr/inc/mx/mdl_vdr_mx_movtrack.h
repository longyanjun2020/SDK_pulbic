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
///@file       mdl_vdr_mx_movatom.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_MOVTRACK_H__
#define __MDL_VDR_MX_MOVTRACK_H__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

#include "mdl_vdr_mx_def.h"
#include "mdl_vdr_mx_property.h"
#include "mdl_vdr_mx_mov.h"

//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------
#define MOV_I_QUANT_OFFSET_NONE  0 // no i-vop
#define MOV_I_QUANT_OFFSET_ALL      1 // all i-vop
#define MOV_I_QUANT_OFFSET_RATION  2 // offset between P and I-frames is dynamic

#define VIDEO_TRACK 1
#define AUDIO_TRACK 2

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------
struct tagMOVFile;
struct tagMOVATOM;

typedef struct tagMOVTrack {
    struct tagMOVFile       *m_pFile;
    struct tagMOVATOM    *m_pTrakAtom;       // moov.trak[]
    MP4TrackId      m_trackId;          // moov.trak[].tkhd.trackId
    char                m_pTypeProperty[4];        // moov.trak[].mdia.hdlr.handlerType, string type
    uint32_t        m_tag;                                          //stsd fourcc
    void            *infoBuf;   // store information of frame buffer
    void            *payloadBuf;    // store payload

    /* track information */
    uint16_t        m_profile;
    uint16_t        m_level;

    int16_t         m_mode;
    uint32_t        m_entry;                                      // chunk count
    uint32_t       m_TimeScale;
    uint32_t       m_time;
    uint32_t       m_sampleCount;
    uint32_t       m_sampleSize;                             // 0 for variable frame size
    uint32_t       m_sampleDuration;                             // 0 for variable frame size
    uint32_t       m_trackDuration;
    uint16_t         m_keyFrameStrategy;                 // MOV_I_QUANT_OFFSET_xxx
    uint32_t        m_mdatoffset;
    uint32_t        m_mdatSize;

    /* encoder information */
    uint32_t        m_db;
    uint32_t        m_avgBitrate;
    uint32_t        m_maxBitrate;
    uint8_t          m_vosLen;
    uint8_t         m_vosData[256];
    uint32_t       	m_prevSampleSize;

    // cached properties
    TKHDPROP_V0*    m_pTkhdProp;
    STSCPROP*       m_pStscProp;
    STSZPROP*       m_pStszProp;
    STTSPROP*       m_pSttsProp;
    STCOPROP*       m_pStcoProp;
    STSDPROP*       m_pStsdProp;
    D263PROP*       m_pD263Prop;
    DAMRPROP*       m_pDamrProp;
    MP4AV_ESDS*     m_pESDSProp;
    STSSPROP*       m_pStssProp;
    AVCConfig*      m_pavcCProp;

    struct tagMOVTrack     *m_pNextItem;
}MOVTRACK, *PMOVTRACK;

typedef struct tagMOVTrackArray {
	uint32_t   	m_totalnum;
    MOVTRACK    *m_pBegin;
    MOVTRACK    *m_pTail;
} MOVTRACKARRAY, *PMOVTRACKARRAY;

//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------
// Tracks Array API
MOVTRACK *mxCreateMuxTrack(struct tagMOVFile *pfile, struct tagMOVATOM *pTrack);
#define mxMP4TracksGetSize(pArray) ((pArray)->m_totalnum)
MOVTRACK  *mxMP4TracksGet(MOVTRACKARRAY *pArray, uint32_t index);
MOVTRACK  *mxMP4TracksGetById(MOVTRACKARRAY *pArray, MP4TrackId trackId);
U8 mxMP4TracksAdd(MOVTRACKARRAY *pArray, MOVTRACK *pTrack);
U8 mxMP4TracksFree(MOVTRACKARRAY *pArray);
// write out any remaining samples in chunk buffer
#define mxMP4TrackFinishWrite(pTrack) mxMP4TrackWriteChunkBuffer(pTrack)
void mxMP4TrackWriteChunkBuffer(MOVTRACK *pTrack);
void mxMP4TrackUpdateModificationTimes(MOVTRACK *pTrack);
void mxMP4TrackWritePacket(MOVTRACK *pTrack,
						MP4AVPacket *av_packet);
void mxMP4TrackAddSampleInfo(MOVTRACK *pTrack,
                        uint32_t    offset,
                        uint32_t numBytes,
                        MP4Duration duration,
                        MP4Duration renderingOffset,
                        U8 isSyncSample);
void mxMP4TrackFlushSample(MOVTRACK *pTrack);
#endif  // __MDL_VDR_MX_MOVTRACK_H__

