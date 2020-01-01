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


#ifndef DMXINST_H
#define DMXINST_H

#include "avp_mp4def.h"

typedef struct tagMP4DMXInst
{
        mp4_heap_st     m_heap_ctx;
        MP4FileHandle   m_mp4File;
        uint32_t        m_numTracks;
        uint32_t        m_numVideoTracks;
        uint32_t        m_numAudioTracks;
        uint32_t        m_numSubtitleTracks;
        MP4TrackId      m_VTrackId;
        MP4TrackId      m_ATrackId;
        MP4TrackId      m_SubTrackId;
        uint64_t        m_numVSamples;
        uint64_t        m_numASamples;
        uint64_t        m_numSubSamples;
        uint32_t        m_VTimeScale;
        uint32_t        m_ATimeScale;
        uint32_t        m_SubTimeScale;
        uint8_t         m_seekable;
#ifdef SUPPORT_KMV
        uint32_t        m_KMV_type;
#endif
} MP4DMXInst;

#endif /* DMXINST_H */
