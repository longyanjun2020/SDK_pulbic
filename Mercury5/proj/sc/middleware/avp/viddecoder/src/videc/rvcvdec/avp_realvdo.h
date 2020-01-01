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
/*////////////////////////////////////////////////////////// */
/* */
/*    INTEL Corporation Proprietary Information */
/* */
/*    This listing is supplied under the terms of a license */
/*    agreement with INTEL Corporation and may not be copied */
/*    nor disclosed except in accordance with the terms of */
/*    that agreement. */
/* */
/*    Copyright (c) 1997-1998 Intel Corporation. */
/*    All Rights Reserved. */
/* */
/*////////////////////////////////////////////////////////// */
/*////////////////////////////////////////////////////////// */

#ifndef REALVDO_H__
#define REALVDO_H__

/* The file defines the base RealVideo class. */

#include "avp_rvtypes.h"
#include "avp_rvstruct.h"
#include "avp_rvstatus.h"
#include "avp_rvfid.h"
#include "avp_rvmsg.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RVCH_MEDIA_AUDIO    0x4155444F /* 'AUDO' */
#define RVCH_MEDIA_VIDEO    0x5649444F /* 'VIDO' */

#define RVCH_RVTRVIDEO_ID   0x52565452  /* 'RVTR' (for rv20 codec) */
#define RVCH_RVTR_RV30_ID   0x52565432  /* 'RVT2' (for rv30 codec) */
#define RVCH_RV20VIDEO_ID   0x52563230  /* 'RV20' */
#define RVCH_RV30VIDEO_ID   0x52563330  /* 'RV30' */
#define RVCH_RV40VIDEO_ID   0x52563430  /* 'RV40' */
#define RVCH_RVG2VIDEO_ID   0x52564732  /* 'RVG2' (raw TCK format) */
#define RVCH_RV89COMBO_ID   0x54524F4D  /* 'TROM' (raw TCK format) */


#ifdef DEBUG
extern FILE* g_debug_fp;
extern char* g_debug_module_name;
#endif


/* The RealVideo class represents an arbitrary host-independent video */
/* environment.  This is the view of the world from the underlying codec */
/* looking up.  Its implementation mediates communication between a */
/* specific video environment and the codec's RV interface. */
/* Typically only one RealVideo object is allocated, and is used by all */
/* codec instances. */

/* */
/* Define the information that gets passed into, and returned from, */
/* each call to decompress a frame. */
/* */

typedef uint32     RV_Decoder_Decompression_Flags;
    /* This set of flags gets passed into each Decode() invocation. */

#define     RV_DDF_DONT_DRAW         0x1
    /* This flag indicates that the input image should be decoded but */
    /* not displayed.  It is enabled when the video environment sees */
    /* various indications such as preroll requests or hurry up requests. */

#define     RV_DDF_KEY_FRAME         0x2
    /* This flag is set if the video environment has signalled that */
    /* the frame is a key frame. */

#define     RV_DDF_MORE_FRAMES       0x4
    /* This flag indicates that the RV_Decoder's Decode method is being */
    /* called to retrieve the second (or subsequent) output image */
    /* corresponding to a single input image. */

#define     RV_DDF_LAST_FRAME        0x200

typedef uint32     RV_Decoder_Decompression_Notes;
    /* This set of notes gets returned from each Decode() invocation. */

#define     RV_DDN_MORE_FRAMES       0x1
    /* Indicates that the decoder has more frames to emit.  This note is */
    /* used by a decoder to inform the RealVideo layer that multiple output */
    /* frames are to be emitted for a given input frame.  The RealVideo layer */
    /* will loop, repeatedly calling Decode() with the same input image and */
    /* with the RV_DDF_MORE_FRAMES flag set, until this note is no longer set. */
    /* This note should only be returned when operating in video environments */
    /* that support multiple output frames per input frame. */

#define     RV_DDN_DONT_DRAW         0x2
    /* This note is returned by a decoder to indicate that the output */
    /* image should not be passed back to the environment.  It should */
    /* be set by a decoder when the RV_DDF_DONT_DRAW flag is set, or */
    /* in situations where the decoder has nothing to display. */

#define     RV_DDN_DEBLOCKING_FILTER    0x10
    /* Indicates that the returned frame has gone through the */
    /* deblocking filter. */

#define     RV_DDN_FRU_FRAME            0x20
    /* Indicates that the decompressed image is a B frame. */
    /* At most one of RV_DDN_KEY_FRAME and RV_DDN_B_FRAME will be set. */

// copied from rv30dec.h
/* Defines match ilvcmsg.h so that spo_extra == rv10init.invariants */
#define RV40_SPO_FLAG_UNRESTRICTEDMV        0x00000001  /* ANNEX D */
#define RV40_SPO_FLAG_EXTENDMVRANGE         0x00000002  /* IMPLIES NEW VLC TABLES */
#define RV40_SPO_FLAG_ADVMOTIONPRED         0x00000004  /* ANNEX F */
#define RV40_SPO_FLAG_ADVINTRA              0x00000008  /* ANNEX I */
#define RV40_SPO_FLAG_INLOOPDEBLOCK         0x00000010  /* ANNEX J */
#define RV40_SPO_FLAG_SLICEMODE             0x00000020  /* ANNEX K */
#define RV40_SPO_FLAG_SLICESHAPE            0x00000040  /* 0: free running; 1: rect */
#define RV40_SPO_FLAG_SLICEORDER            0x00000080  /* 0: sequential; 1: arbitrary */
#define RV40_SPO_FLAG_REFPICTSELECTION      0x00000100  /* ANNEX N */
#define RV40_SPO_FLAG_INDEPENDSEGMENT       0x00000200  /* ANNEX R */
#define RV40_SPO_FLAG_ALTVLCTAB             0x00000400  /* ANNEX S */
#define RV40_SPO_FLAG_MODCHROMAQUANT        0x00000800  /* ANNEX T */
#define RV40_SPO_FLAG_BFRAMES               0x00001000  /* SETS DECODE PHASE */
#define RV40_SPO_BITS_DEBLOCK_STRENGTH      0x0000e000  /* deblocking strength */
#define RV40_SPO_BITS_NUMRESAMPLE_IMAGES    0x00070000  /* max of 8 RPR images sizes */
#define RV40_SPO_FLAG_FRUFLAG               0x00080000  /* FRU HXBOOL: if 1 then OFF; */
#define RV40_SPO_FLAG_FLIP_FLIP_INTL        0x00100000  /* FLIP-FLOP interlacing; */
#define RV40_SPO_FLAG_INTERLACE             0x00200000  /* de-interlacing prefilter has been applied; */
#define RV40_SPO_FLAG_MULTIPASS             0x00400000  /* encoded with multipass; */
#define RV40_SPO_FLAG_INV_TELECINE          0x00800000  /* inverse-telecine prefilter has been applied; */
#define RV40_SPO_FLAG_VBR_ENCODE            0x01000000  /* encoded using VBR; */
#define RV40_SPO_BITS_DEBLOCK_SHIFT     13
#define RV40_SPO_BITS_NUMRESAMPLE_IMAGES_SHIFT 16

void            Decoder_Delete(VID_HANDLE *hp, void *coredecoder);



RV_Status      Decoder_Custom_Message(void *t, RV_Custom_Message_ID*);

RV_Status      Decoder_Start_Sequence(RVC_HANDLE *hp,
                                      const struct RV_Image_Format *,
                                      const struct RV_Image_Format *,
                                      uint8 *decbuf, int32 *used_size
                                      );

int     rvc_parse_sequence_header(VID_HANDLE *hp, int is_rvch);
int     rvc_parse_picture_header(VID_HANDLE *hp);
int     rvc_init_decoder(VID_HANDLE *hp, uint8 **decbuf, int *used_size);

#ifdef __cplusplus
}
#endif


#endif /* REALVDO_H__ */
