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
/* */
/*    Various structure definitions. */
/* */
/*/////////////////////////////////////////////////////////////////////////// */

/*/////////////////////////////////////////////////////////////////////////// */
/*    INTEL Corporation Proprietary Information */
/* */
/*    This listing is supplied under the terms of a license */
/*    agreement with INTEL Corporation and may not be copied */
/*    nor disclosed except in accordance with the terms of */
/*    that agreement. */
/* */
/*    Copyright (c) 1995 - 2000 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*////////////////////////////////////////////////////////////////////////// */

#ifndef RVSTRUCT_H__
#define RVSTRUCT_H__


#include <stdint.h>
#include "avp_rvtypes.h"
#include "avp_rvfid.h"
#include "avp_videc_s.h"
#include "avp_rvmsg.h"
#include "avp_decdefs.h"
#include "avp_dec4x4t.h"
#include "avp_spinterp.h"

#ifdef __cplusplus
extern "C" {
#endif


struct RV_Dimensions
{
    uint32     width;
    uint32     height;
};

typedef enum 
{
    INTRAPIC    = I_PICTURE,
    INTERPIC    = P_PICTURE,
    TRUEBPIC    = B_PICTURE,
    FRUPIC      = 3
} EnumPicCodType;

#define FID_I420  100
#define FID_YUV12 120
#define FID_IYUV  140
#define FID_NOTSUPPORTED 999

/* Macroblock type definitions */
/* Keep these ordered such that intra types are first, followed by */
/* inter types.  Otherwise you'll need to change the definitions */
/* of IS_INTRA_MBTYPE and IS_INTER_MBTYPE. */
/* */
/* WARNING:  Because the decoder exposes macroblock types to the application, */
/* these values cannot be changed without affecting users of the decoder. */
/* If new macro block types need to be inserted in the middle of the list, */
/* then perhaps existing types should retain their numeric value, the new */
/* type should be given a new value, and for coding efficiency we should */
/* perhaps decouple these values from the ones that are encoded in the */
/* bitstream. */
/* */
/* */

typedef enum {
    MBTYPE_INTRA,           /* 0 */
    MBTYPE_INTRA_16x16,     /* 1 */
    MBTYPE_INTER,           /* 2 */
    MBTYPE_INTER_4V,        /* 3 */
    MBTYPE_FORWARD,         /* 4 */
    MBTYPE_BACKWARD,        /* 5 */
    MBTYPE_SKIPPED,         /* 6 */
    MBTYPE_DIRECT,          /* 7 */
    MBTYPE_INTER_16x8V,     /* 8 */
    MBTYPE_INTER_8x16V,     /* 9  */
    MBTYPE_BIDIR,           /* 10 */
    MBTYPE_INTER_16x16,     /* 11 */
#ifdef INTERLACED_CODE
    MBTYPE_INTER_16x16i,    // 12
    MBTYPE_INTER_16x8i,     // 13
    MBTYPE_INTER_8x8i,      // 14
    MBTYPE_FORWARD_16x16i,  //15
    MBTYPE_BACKWARD_16x16i, //16
    MBTYPE_FORWARD_16x8i,   //17
    MBTYPE_BACKWARD_16x8i,  //18
#endif
    NUMBER_OF_MBTYPES       /* 19 */
} MB_Type;


/* macro - yields TRUE if a given MB type is INTRA */
#define IS_INTRA_MBTYPE(mbtype) ((mbtype) < MBTYPE_INTER)

/* macro - yields TRUE if a given MB type is INTER */
#define IS_INTER_MBTYPE(mbtype) ((mbtype) >= MBTYPE_INTER)

/* macro - yields TRUE if a given MB type is INTERLACED */
#define IS_INTERLACE_MBTYPE(mbtype) ((mbtype) >= MBTYPE_INTER_16x16i)

/* macro - yields TRUE if a given MB type is INTERLACED & B Frame type*/
#define IS_INTERLACE_B_MBTYPE(mbtype) ((mbtype) >= MBTYPE_FORWARD_16x16i)

#define IS_FORWARD_OR_BIDIR(mbtype)(((mbtype) == MBTYPE_FORWARD) || \
                                    ((mbtype) == MBTYPE_FORWARD_16x16i) || \
                                    ((mbtype) == MBTYPE_FORWARD_16x8i) || \
                                    ((mbtype) == MBTYPE_BIDIR))

#define IS_BACKWARD_OR_BIDIR(mbtype)(((mbtype) == MBTYPE_BACKWARD) || \
                                     ((mbtype) == MBTYPE_BACKWARD_16x16i) || \
                                     ((mbtype) == MBTYPE_BACKWARD_16x8i) || \
                                     ((mbtype) == MBTYPE_BIDIR))


typedef struct YUVFrame
{
    /* Pointers to Y, V, and U planes */
    uint8 *pYPlane;
    uint8 *pVPlane;
    uint8 *pUPlane;
} T_YUVFrame;

/* The PictureHeader structure represents the information that */
/* goes into the picture header of a single bitstream picture. */

struct PictureHeader
{
    int8                            PicCodType;
    struct RV_Dimensions            dimensions;
    uint32                          TR;

    RV_Boolean                      Deblocking_Filter_Passthrough;
        /* This is a non-standard option used in RealVideo */
        /* that indicates that the deblocking filter in annex J */
        /* should not be called. The option will be ignored if */
        /* Annex J is off or if the bitstream is standards-based. */

    uint8                           PQUANT;
    uint8                           OSVQUANT;

#ifdef INTERLACED_CODE
        RV_Boolean                  x10;
        RV_Boolean                  Interlaced;
        RV_Boolean                  InterlacedTopFieldFirst;
        RV_Boolean                  RepeatField;
        uint32                      DeblockingQpAdjust;
#endif
};


/* A DecoderMBInfo structure describes one decoded macroblock. */
/* */
/* We should keep this structure reasonably small and well aligned, */
/* since we need to allocate one per luma macroblock, twice (one set */
/* for B frames and one set for non-B frames). */
/* Technically, we don't need two sets of the 'missing' and 'edge_type' */
/* members.  But they are relatively small, and keeping them along with */
/* QP and mbtype will help localize data cache accesses. */

struct DecoderMBInfo
{
#if 0
    //uint8   edge_type; // 4-bit
#define         D_LEFT_EDGE     0x1
#define         D_RIGHT_EDGE    0x2
#define         D_TOP_EDGE      0x4
#define         D_BOTTOM_EDGE   0x8
#define         D_MISSING       0x10
#else
#define edge_type cbpcoef
#define         D_CBP_MASK      (0xffffff)
#define         D_LEFT_EDGE     (0x1 << 24)
#define         D_RIGHT_EDGE    (0x2 << 24)
#define         D_TOP_EDGE      (0x4 << 24)
#define         D_BOTTOM_EDGE   (0x8 << 24)
#define         D_MISSING       (0x10 << 24)
#endif
        //it is similar to block_avail. if (edge_type&x)==1, it means not available
            /* Indicates whether the MB falls on a picture or slice boundary. */
            /* */
            /* WARNING: Do not change the following EDGE value definitions */
            /* without making corresponding changes to dscalup.cpp, */
            /* specifically the jump table in ExtendBlockEdges(). */
            /* These bit masks are also used by error concealment. */
        //uint8   missing; // 1-bit
        /* Indicates whether the MB was absent from the bitstream. */
        /* Error concealment is performed on such MBs. */

        uint8                       QP; // 5-bit

        uint8                       mbtype; // 4~5 bit

        uint16                      mvdelta; // 16-bit
        uint32                      cbpcoef; // cbp:24-bit + edge_type:4 bit + missing:1 bit
            /* Indicates coded blocks with coefficients. */
};

/* A RV_Image_Format object describes the *type* of an image.  The intent */
/* is that it contains enough descriptive information so that a codec can */
/* perform capability negotiations (i.e., advertise and agree on input and */
/* output format types) and also allocate any dimension-dependent memory. */

struct RV_Image_Format
{
        RV_FID                      fid;
        struct RV_Dimensions        dimensions;
};



/* A RV_Image object represents an actual instance of an image.  Thus it */
/* includes a RV_Image_Format that describes the image, as well as pointers */
/* to the image's data, among other information. */

struct RV_Image {
        struct RV_Image_Format      format;
        uint32                      size;
            /* "size" gives the total length, in bytes, of the image's data. */

        uint32                      sequence_number;
            /* This number indicates the temporal position of this image */
            /* with respect to previous and future images.  Its value is */
            /* specific to each video environment. */

        frameobj                    frame;
            /* The frameobj struct points to the Y, U and V planes' data. */
            /* It is used for YUV formats, e.g. YUV12, YVU9, et. al. */
};

struct DecodedFrame
{
        frameobj                    frame;

        /* DecoderYUVWorkspace */
        RV_Boolean                  m_isSmoothed;
            /* These indicate whether a deblocking or smoothing filter */
            /* have been applied. */

        RV_Boolean                  m_isExpanded;
            /* This indicates whether pixels around the edges of the planes */
            /* have been replicated into the surrounding padding area. */
            /* The expand() method performs this operation. */

        struct PictureHeader        m_pictureHeader;

        uint64                      m_cumulativeTR;
            /* This is the TR of the picture, relative to the very first */
            /* frame decoded after a call to Start_Sequence.  The double type */
            /* is used to avoid wrap around problems. */

        uint32                      m_timeStamp;
            /* m_timeStamp provides an alternate time stamping mechanism, */
            /* used by RealVideo bitstreams. */
            /* For reference frames (i.e., non-B frames) m_timeStamp */
            /* is the sequence_number of the RV_Image with which this */
            /* image came into Decode().  For B frames, it is calculated */
            /* using the previous reference frame's frameTimestamp() plus */
            /* the TR difference between that frame and the B frame. */
            /* It assumes that the TR has millisecond granularity. */
};


typedef enum
{
    RV_INTRAPIC,        /* 0 (00) */
    RV_FORCED_INTRAPIC, /* 1 (01) */
    RV_INTERPIC,        /* 2 (10) */
    RV_TRUEBPIC         /* 3 (11) */
} EnumRVPicCodType;



typedef struct
{
        uint32      is_valid;
        uint32      offset;
} Bitstream_Segment_Info;
/* The Bitstream_Segment_Info structure *MUST* be structurally equivalent */
/* to the PNCODEC_SEGMENTINFO structure defined in the RealVideo */
/* front-end. */

/* real-video picture header format */
typedef struct
{
        EnumRVPicCodType    ptype;
        RV_Boolean          deblocking_filter_passthrough;
        int32               mba;
        uint32              tr;
        uint8               pquant;
        uint8               pctsz; /* RV8 */
        uint32              pwidth;
        uint32              pheight;
        uint32              pwidth_prev;
        uint32              pheight_prev;
#ifdef INTERLACED_CODE
        RV_Boolean          x10;
        RV_Boolean          interlaced;
        RV_Boolean          interlacedTopFieldFirst;
        RV_Boolean          RepeatField;
        uint32              DeblockingQpAdjust;
#endif

} RV_BS_Info;

struct CRealVideoBs 
{
        RV_FID              m_fid;          /* stream type */

        RV_Boolean          m_isForcedKey;  /* forced keyframe */

        uint8               m_mbaSize;      /* size of MBA field */

        RV_BS_Info          m_rv;           /* RV2 bitstream picture header info */

        /* slice information for packetization w/o rtp extension */
        uint32              m_nSlices;
        Bitstream_Segment_Info  *m_sliceInfo;

        /* size of PCTSZ (RealVideo RPR size index) */
        uint8_t             m_pctszSize;

        /* location of RealVideo RPR size array */
        uint16_t            *m_pSizes;
};


struct Global_Decoder_Options
{
        RV_Boolean          SmoothingPostFilter;
            /* The decoder should use the smoothing post-filter. */

        uint32              CPU_Scalability_Setting;
            /* Decoder's CPU scalability setting, interface defined in */
            /* RV_I_CPU_Scalability */

        RV_Boolean          lossConcealment;
            /* Decoder's error concealment switch. */

        RV_Boolean          FrameRateUpsampling;

#ifdef INTERLACED_CODE
        RV_Boolean          Interlaced;
#endif

        /* The following reserved members are place holders that allow us */
        /* to add new options, without changing the size of this structure. */
        /* They are intended to be used after a release, so that adding */
        /* new options does not affect the size of our persistent data. */

        uint32              m_Reserved1;
};

struct SmoothingFilter
{
        /* legacy filter */
        RV_Boolean                  m_bIsRV8;

        /* Filter strength level */
        uint32                      m_uStrength;

        /* Pointers to strengths map */
        uint8                       *m_pStrengthMapPreAligned;
        uint8                       *m_pStrengthMap;

        /* Strength map size (minimum) */
        uint32                      m_uStrengthMapSize;

        /* Strength map pitch */
        uint32                      m_uStrengthMapPitch;

        /* TRUE if all strengths in map are 0's */
        RV_Boolean                  m_bEmptyStrengthMap;
};

struct RVDecoder
{
        RV_Boolean                  m_bIsRV8; /* is this RV8 or RV9 */

        uint32                      m_initialSequenceNumber;
        uint32                      m_initialTR;
            /* m_initialSequenceNumber and m_initialTR are the RV_Image */
            /* sequence_number and bitstream TR of the very first image */
            /* we decode after a Start_Sequence.  Typically these will */
            /* be zero, but not necessarily.  For example, when Start_Sequence */
            /* is called after "seeking" to an I frame in the middle of a */
            /* video stream, then these will be non-zero.  These values */
            /* are used, along with each bitstream's TR, to calculate */
            /* each picture's presentation time stamp. */

        uint32                      m_uTRWrap;
            /* This is the value at which the TR Wraps around for this  */
            /* particular sequence. */

        struct CRealVideoBs         m_BitStream;

        /* DecodedFrame */
        struct DecodedFrame         m_PrevFrame;
        struct DecodedFrame         m_FutuFrame;
            /* These point to the previous and future reference frames */
            /* used to decode this frame. */
            /* m_PrevFrame will always be valid when */
            /* decoding a P or B frame, and m_FutuFrame will always */
            /* be valid when decoding a B frame. */

        /* Declare space for our YUV reference frames and B frames. */
        /* Currently the list contains at most two decoded */
        /* reference frames.  An additional single buffer is maintained for */
        /* decoding B frames, and this buffer is not linked into the reference */
        /* frame list (although its previous() and future() pointers will */
        /* point into the reference frame list). */

        struct DecodedFrame         m_BFrame;
            /* This is the buffer that we decode B frames into. */
            /* in non-hw video memory mode */

        struct DecodedFrame         m_postBuffer;
            /* If post processing is required on a reference frame, or if */
            /* post-processing entails a copy, then this buffer is used */
            /* for the additional copy. */

        struct DecodedFrame         *m_pCurrentFrame;
            /* This points to either m_BFrame, or one of the frames in our */
            /* reference frame list.  It is the frame that we are currently */
            /* parsing in Decode().  It's previous() and future() methods */
            /* can be used to access the frames it is predicted from. */
            /* After a successful call to Decode(), this remains a valid */
            /* pointer, so that the application can use custom messages to */
            /* extract bitstream information for the just-decoded picture. */

#ifdef SUPPORT_RV8
        struct SmoothingFilter      m_smoothingPostFilter;
            /* Provide smoothing post filtering. */
#endif

        uint8                       *m_pParsedData;
            /* This points to a huge, monolithic buffer that contains data */
            /* derived from parsing the current frame.  It contains motion */
            /* vectors for a single frame, and MB info for one reference */
            /* frame and one B frame, among other things. */
            /* Logically this information belongs in the DecodedFrame class. */
            /* However, algorithmically, we only need to keep around this */
            /* information for the most recent reference frame and B frame */
            /* that we decoded.  Thus, as a space saving optimization, we */
            /* allocate this information in the RVDecoder class rather than */
            /* in the DecodedFrame class. */

        uint32                      m_parsedDataLength;
        struct RV_Dimensions        m_paddedParsedDataSize;
            /* m_pParsedData's allocated size is remembered so that a */
            /* re-allocation is done only if size requirements exceed the */
            /* existing allocation. */
            /* m_paddedParsedDataSize contains the image dimensions, rounded */
            /* up to a multiple of 16, that were used to calculate */
            /* m_parsedDataLength.  If the image dimensions change, while */
            /* the allocated buffer is already large enough, then we don't */
            /* reallocate the buffer, but we still need to adjust the various */
            /* pointers that point into the buffer. */

        COEF_TYPE                   *m_pQuantBuf;
            /* Buffer (within m_pParsedData) to store coefficients for */
            /* one macroblock, and perform inverse quantization and inverse */
            /* transform.  Even though the size of this buffer is independent */
            /* of image dimensions, we allocate it in m_pParsedData so that */
            /* we can control its alignment.  It must be 8-byte aligned */
            /* for optimal inverse transform performance. */

#define NUM_QUANT_BUFFER_ELEMENTS 32 //intra16x16DC + one 4x4block 
            /* Number of quant buffer elements in one MB for which space is allocated. */
            /* Add four additional entries, in case channel bit errors cause */
            /* too many coefficients to be present. */

        DecoderIntraType           *m_pAboveSubBlockIntraTypes;
        DecoderIntraType           *m_pMBIntraTypes;
            /* The differential coding of intra-coding types uses the intra */
            /* type of the above and left subblocks as predictors. */
            /* We don't need to store the intra type for all subblocks in */
            /* the whole frame, but rather just for those in the current */
            /* macroblock being decoded (m_pMBIntraTypes) and for the bottom */
            /* row of subblocks in the previously decoded row of macroblocks */
            /* (m_pAboveSubblockIntratypes).  Both of these small buffers */
            /* reside in m_pParsedData. */
#define NUM_INTRA_TYPE_ELEMENTS 24
            /* Number of intra type elements in one MB for which space is allocated. */

        DecoderPackedMotionVector  *m_pReferenceMotionVectors;
            /* Buffer (within m_pParsedData) used to store motion vectors */
            /* for each 4x4 subblock of a reference frame. */
            /* Note that we may leave the motion vectors unassigned */
            /* when decoding a key frame, so beware. */

        DecoderPackedMotionVector  *m_pBMotionVectors;
            /* Buffer (within m_pParsedData) used to store motion vectors */
            /* for each 4x4 subblock of a B frame. */
            /* Note that we may leave the motion vectors unassigned */
            /* when decoding a key frame, so beware. */

        DecoderPackedMotionVector  *m_pBidirMotionVectors;
            /* Buffer (within m_pParsedData) used to store backward  */
            /* motion vectors for each 16x16 macroblock of a B frame. */
            /* Note that we may leave the motion vectors unassigned */
            /* when decoding a key frame, so beware. */

        DecoderPackedMotionVector  *m_pMotionVectors;
            /* Pointer that is initialized during prepareDecodeBuffers. */
            /* This points to either m_pBmotionVectors or m_pReferenceMotionVectors, */
            /* depending on what type of frame is being decoded. */

        struct DecoderMBInfo        *m_pReferenceMBInfo;
            /* Buffer (within m_pParsedData) used to store information about */
            /* each MB in the bitstream.  This buffer is only used when */
            /* decoding reference frames (i.e., non-B frames). */

        struct DecoderMBInfo        *m_pBFrameMBInfo;
            /* Buffer (within m_pParsedData) used to store information about */
            /* each MB in the bitstream.  This buffer is only used when */
            /* decoding B frames. */

        struct DecoderMBInfo        *m_pMBInfo;
            /* Initialized during prepareDecodeBuffers, this points to */
            /* either m_pReferenceMBInfo or m_pBFrameMBInfo, depending */
            /* on what type of frame is being decoded. */

        uint32                      m_uNumMissingMBs;

#if defined(DEC_TIMING_DETAIL)

#define NUM_PERF_COUNTERS 11
        uint32 m_uTimeCount_DecodeMB;       /* MB decode timing counter */
        uint32 m_uTimeCount_Deblock;        /* deblocking filter timing counter */
        uint32 m_uTimeCount_Postfilter;     /* smoothing post filter timing counter */
        uint32 m_uTimeCount_Smooth_PrePost; /* before and after actual smoothing filter */
        uint32 m_uTimeCount_decMBheader;    /* MB header parse in MB loop */
        uint32 m_uTimeCount_decCoeffs;      /* vld, dequant, inv transform in MB loop */
        uint32 m_uTimeCount_recMB;          /* motion comp in MB loop */
        uint32 m_uTimeCount_Utility[3];     /* for temporary development use */
#endif

        uint32                              m_picture_clock_num;
        uint32                              m_picture_clock_den;

        struct Global_Decoder_Options       m_options;

#ifdef ERROR_CONCEALMENT
        struct LossConcealment              m_lossConcealment;
#endif

#if defined(RV_D1_FAST_MC) || defined(RV_CONST_STRIDE) || defined(RV_CONST_STRIDE_D1)
        const T_InterpFnxTable              *m_pfnInterpY;
        const T_InterpChromaFnxTable_UV     *m_pfnInterpC;
#endif
#ifdef USE_DECOMP_TABLE
        const INTRA_DECODE_TABLES           *intra_decode_tables;
        const INTER_DECODE_TABLES           *inter_decode_tables;
#else
        INTRA_DECODE_TABLES                 *intra_decode_tables;
        INTER_DECODE_TABLES                 *inter_decode_tables;
#endif
};

typedef struct
{
    VID_HANDLE                      h;

    struct RVDecoder                *rvdecoder;
    RV_FID                          rv_format_fid;
    RV_Boolean                      smoothing_postfilter;
    RV_Boolean                      is_rvch;
    uint8_t                         Num_RPR_Sizes;
    uint16_t                        RPR_Sizes[2 * 8]; /* Table of encoded dimensions, including RPR sizes. */
    struct RV_Image                 compressed_image;
    struct RV_Image                 decompressed_image;
    struct RV_Image                 resample_image;
#define RV_MAX_SEGMENTS 128
    RV_Segment_Info                 segment_info[RV_MAX_SEGMENTS];
    uint32                          number_of_segments;
    int                             drop_b_frame;
    int                             mvpitch;

    struct PictureHeader            header;
} RVC_HANDLE;


#ifdef __cplusplus
}
#endif

#endif /* RVSTRUCT_H__ */
