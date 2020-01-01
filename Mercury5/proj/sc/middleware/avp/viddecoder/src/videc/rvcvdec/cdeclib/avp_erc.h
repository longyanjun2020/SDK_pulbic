/* ***** BEGIN LICENSE BLOCK *****
 *
 * REALNETWORKS CONFIDENTIAL--NOT FOR DISTRIBUTION IN SOURCE CODE FORM
 * Portions Copyright (c) 1995-2002 RealNetworks, Inc.
 * All Rights Reserved.
 *
 * The contents of this file, and the files included with this file,
 * are subject to the current version of the Real Format Source Code
 * Porting and Optimization License, available at
 * https://helixcommunity.org/2005/license/realformatsource (unless
 * RealNetworks otherwise expressly agrees in writing that you are
 * subject to a different license).  You may also obtain the license
 * terms directly from RealNetworks.  You may not use this file except
 * in compliance with the Real Format Source Code Porting and
 * Optimization License. There are no redistribution rights for the
 * source code of this file. Please see the Real Format Source Code
 * Porting and Optimization License for the rights, obligations and
 * limitations governing use of the contents of the file.
 *
 * RealNetworks is the developer of the Original Code and owns the
 * copyrights in the portions it created.
 *
 * This file, and the files included with this file, is distributed and
 * made available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS ALL
 * SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT
 * OR NON-INFRINGEMENT.
 *
 * Technology Compatibility Kit Test Suite(s) Location:
 * https://rarvcode-tck.helixcommunity.org
 *
 * Contributor(s):
 *
 * ***** END LICENSE BLOCK ***** */

/*/////////////////////////////////////////////////////////////////////////// */
/*    RealNetworks, Inc. Confidential and Proprietary Information. */
/* */
/*    Copyright (c) 1995-2002 RealNetworks, Inc. */
/*    All Rights Reserved. */
/* */
/*    Do not redistribute. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */
/*    Error concealment code. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */

/* *************************************************************************
**    INTEL Corporation Proprietary Information
**
**    This listing is supplied under the terms of a license
**    agreement with INTEL Corporation and may not be copied
**    nor disclosed except in accordance with the terms of
**    that agreement.
**
**    Copyright (c) 1998 - 1999 Intel Corporation.
**    All Rights Reserved.
**
** *************************************************************************
*/

#ifndef D3ERC_H__
#define D3ERC_H__

#include "avp_beginhdr.h"
#include "avp_cdrvdefs.h"
#include "avp_rvtypes.h"
#include "avp_rvfid.h"
#include "avp_basic.h"
#include "avp_rvstruct.h"


#ifdef __cplusplus
extern "C" {
#endif

/* yuv macroblock structure */
typedef struct
{
    uint8   y[16][16];
    uint8   v[8][8];
    uint8   u[8][8];
} T_YUVMB;

/* concealment types */
typedef enum {
    TYPE_TEMP_COPY,     /* temporally copy MB from the reference frame */
    TYPE_TEMP_EXTR,     /* motion compensated MB from the reference frame */
    TYPE_SPAT_EXTR,     /* spatially extrapolated from the neighboring MB */
    TYPE_SPAT_EDGX      /* spatially extrapolated from the adjacent edges */
} EnumConcealType;

typedef struct {
    int32     iMVx2;
    int32     iMVy2;
} T_MV;

/* motion vector type with direction */
typedef struct
{
    T_MV    mv;
    uint8   type;
} T_MVD;


/* maximum number of candidate motion vectors */
#define MAX_NUM_CANDID_MVs 18

/* --------------------------------------------------------------------------- */
/*  error concealment class */
/* --------------------------------------------------------------------------- */

struct  LossConcealment
{

        T_Copy4x4           *m_pLumaRecon;
            /* CPU-specific interpolation and reconstruction function pointers. */

        /* stream id */
        RV_Boolean          m_bIsRvFid;

        /* Frame level information variables.  Their values are passed */
        /* from the core decoder object. */

        struct DecodedFrame*        m_pCurrFrame;
        struct DecodedFrame*        m_pPrevFrame;
        struct DecodedFrame*        m_pFutrFrame;

        uint32                  m_width;
        uint32                  m_height;
        uint32                  m_pitch;

        struct DecoderMBInfo      *m_pMBInfo;
        struct DecoderPackedMotionVector
                           *m_pMotionVectors;

        uint32                  m_numBadMBs;
        uint32                  m_totalNumMBs;
        uint32                  m_numMBsPerRow;
        int8                    m_picType;

        /* Variables used in estimating concealed MB. */

        int32                   m_num_candidMVs;
        T_MVD                   m_candidMVs[MAX_NUM_CANDID_MVs];

        uint32                  m_mb;
        uint32                  m_row;
        uint32                  m_col;

        uint32                  m_edges;
        uint32                  m_numValidMBs;

        uint8              *m_pY;
        uint8              *m_pV;
        uint8              *m_pU;

#ifdef DEBUG
        /* These variables and methods are for debugging purposes only. */

        uint32                  m_count_temp_copy;
        uint32                  m_count_temp_extr;
        uint32                  m_count_spat_copy;
        uint32                  m_count_spat_edgx;
#endif

};




/* Default constructor. */
void LossConcealment_Init(struct LossConcealment *t, const RV_FID fid);

/* Destructor. */
void LossConcealment_Delete(struct LossConcealment *t);

/* Set the type of video as indicated by fid. */
void LossConcealment_SetFID(struct LossConcealment *t, const RV_FID fid);

/* Performs error concealment on a corrupted frame. */
int32 LossConcealment_Conceal(
            struct LossConcealment *t,
            struct DecodedFrame*    pCurrFrame,
            const RV_Boolean        bIsForcedKey,
            uint32                  numMissingMBs,
            int8                    PicType,
            struct DecoderMBInfo*,
            struct DecoderPackedMotionVector*,
            int                     width,
            int                     height);

/* Estimates the corruption caused by losses on a scale */
/* of [0, 100].  0 indicates no corruption. */
int32 LossConcealment_AssessDamage(struct LossConcealment *t);

/* Scans for missing MBs and attempts concealment. */
void LossConcealment_ScanAndConceal(struct LossConcealment *t);

/* Initializes variables to prepare for concealment. */
void LossConcealment_PreEstimate(
            struct LossConcealment *t,
            const int32             mb);

/* Finds the best replacement MB for a missing MB. */
void LossConcealment_EstimateMB(struct LossConcealment *t);

/* Finds temporal replacement for a missing MB. */
void LossConcealment_DoTemporalEstimate(
            struct LossConcealment *t,
            EnumConcealType*        type,
            int32*                  bestfit,
            T_YUVMB*                bestmb,
            T_MVD *                 bestmv);

/* Finds spatial replacement for a missing MB. */
void LossConcealment_DoSpatialEstimate(
            struct LossConcealment *t,
            EnumConcealType*        type,
            int32*                  bestfit,
            T_YUVMB*                bestmb);

/* Measures the fitness of the current candidate concealment */
/* MB based on side-match criterion. */
int32 LossConcealment_MeasureFitness(struct LossConcealment *t);

/* Saves the values of the current MB into a T_YUVMB structure. */
void LossConcealment_GetCurrYUVMB(
            struct LossConcealment *t,
            T_YUVMB*                mb);

/* Load current MB in the picture segment with values from the */
/* given T_YUVMB structure. */
void LossConcealment_LoadCurrYUVMB(
            struct LossConcealment *t,
            const T_YUVMB           *mb);

/* Selects motion vector candidates from any valid neighbor */
/* in the current frame. */
void LossConcealment_SelectCandidMVs(struct LossConcealment *t);

/* Adds a given motion vector into the candidate list. */
void LossConcealment_AddCandidMVs(
            struct LossConcealment *t,
            const int32             mvx,
            const int32             mvy,
            const uint8             type);

/* Removes any duplicate motion vectors from the list. */
void LossConcealment_RemoveDuplicateCandidMVs(struct LossConcealment *t);

/* Checks if the given motion vectors matched. */
RV_Boolean LossConcealment_MatchMVs(
            struct LossConcealment *t,
            const  T_MVD            mv1,
            const  T_MVD            mv2);

/* Finds the average of the motion vector candidates. */
T_MVD LossConcealment_FindAverageMV(struct LossConcealment *t);

/* Find the motion compensated candidate MB for a given MV. */
void LossConcealment_MvCompensate(
            struct LossConcealment *t,
            const  T_MVD            mvd);

/* Truncates a motion vector if necessary. */
T_MV LossConcealment_TruncateMV(
            struct LossConcealment *t,
            const  T_MV             mv);

/* Load current MB in the picture segment with values extrapolated */
/* from its neighboring MB. */
RV_Boolean LossConcealment_SpatialPeriodicExtrapol(
            struct LossConcealment *t,
            const uint32            side);

/* Checks if a MB is intra coded and significantly different */
/* from that in the reference frame. */
RV_Boolean LossConcealment_IsTrueIntraMB(
            struct LossConcealment *t,
            const uint32            mb);

/* Checks if given two MBs looked similar. */
RV_Boolean LossConcealment_ResemblingMBs(
            struct LossConcealment *t,
            const uint8            *pY1,
            const uint8            *pY2);

/* Load current MB in the picture segment with values extrapolated */
/* and averaged from the edges of its adjacent valid neighbors. */
void LossConcealment_EdgeExtrapolAndAverage(struct LossConcealment *t);

#ifdef DEBUG
/* Displays an ASCII map indicating the type of each MB. */
void LossConcealment_DisplayMBTypeMatrix(struct LossConcealment *t);

/* Updates concealment type counters. */
void LossConcealment_UpdateConcealmentTypeCounters(
            struct LossConcealment *t,
            const  EnumConcealType type);
#endif

#ifdef __cplusplus
}
#endif




#endif /* D3ERC_H__ */
