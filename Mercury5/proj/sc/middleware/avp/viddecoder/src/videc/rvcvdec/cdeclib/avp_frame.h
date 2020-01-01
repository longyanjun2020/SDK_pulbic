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
/* The DecodedFrame class represents a YUV work space which was obtained */
/* by decoding a bitstream picture. */
#ifndef DECTEMP_H__
#define DECTEMP_H__

#include "avp_rvtypes.h"
#include "avp_rvstatus.h"
#include "avp_rvstruct.h"

#ifdef __cplusplus
extern "C" {
#endif

/* */
/* Define classes that encapsulate pitched YUV image data. */
/* */




/* The PaddedYUVBuffer class represents a YUV image laid out in memory such */
/* that there are padding bytes surrounding the three planes.  This extra */
/* padding allows pixels at the edge of the planes to be replicated, as */
/* well as facilitating algorithms that need to read or write a few bytes */
/* beyond the end of a line of pixels.  The frame is laid out as shown below. */
/* */
/*          +---------------------+ */
/*          |                     | */
/*          |    +-----------+    |     The amount of padding around the */
/*          |    |           |    |     U and V planes is half the amount */
/*          |    |     Y     |    |     around the Y plane.  The dotted line */
/*          |    |           |    |     separating the planes is there just */
/*          |    +-----------+    |     to emphasize that the padding around */
/*          |                     |     each plane does not overlap the */
/*          | .  .  .  .  .  .  . |     padding around the other planes. */
/*          |          .          | */
/*          |  +----+  .  +----+  |     Note that all three planes have */
/*          |  | U  |  .  |  V |  |     the same pitch. */
/*          |  +----+  .  +----+  | */
/*          +---------------------+ */
/* */
/* Note that the class is designed to allow reusing existing buffer space */
/* for a smaller image size.  For example, if the frame buffer was originally */
/* allocated to hold a CIF image, and is then adjusted to hold a QCIF image, */
/* then the QCIF Y, U and V planes will reside in or about the upper left */
/* quadrant of the CIF-size frame buffer.  Such reuse can result in much */
/* wasted space.  If this is undesireable, then the existing large buffer */
/* should be explicitly deallocated prior to allocating the smaller size. */
/* */

/* To be fully general, this class should allow the amount of padding to be */
/* specified via a constructor parameter.  However, we don't need such */
/* generality currently.  To simplify the class, we will use the hard coded */
/* padding amounts defined below. */

#define YUV_Y_PADDING       16
    /* The Y plane has this many bytes (a.k.a. pels) of padding around each */
    /* of its 4 sides */

#define YUV_UV_PADDING      8
    /* The U and V planes have this many bytes (a.k.a. pels) of padding */
    /* around each of their 4 sides */

#define YUV_ALIGNMENT       64 //32
    /* The beginning of the padded buffer is aligned thusly. */
    /* (Hmm?  These numbers imply that the entire buffer is 32-byte aligned, */
    /* while the Y plane is only 16-byte aligned.  Is 16-byte alignment */
    /* sufficient for the overall buffer?) */


struct DecodedFrame;

void DecodedFrame_Init(struct DecodedFrame *t);

RV_Status
DecodedFrame_allocate(RVC_HANDLE *hp, struct DecodedFrame *t, const struct RV_Dimensions *lumaSize, struct RV_Image *dst);

void 
DecodedFrame_clearState(struct DecodedFrame *t);

void 
DecodedFrame_copyState(struct DecodedFrame *t, struct DecodedFrame *src);

void
DecodedFrame_expand(RVC_HANDLE *hp, struct DecodedFrame *t);

void
DecodedFrame_swap(struct DecodedFrame *t, struct DecodedFrame *pOther);

#ifdef INTERLACED_CODE
extern void RV_CDECL ExpandPlanei(
                uint8 *StartPtr,
                uint32 uFrameWidth,
                uint32 uFrameHeight,
                uint32 uPitch,
                uint32 uPels) GNUCDECL;             /* size of expansion (8 or 16) */
#endif

#ifdef __cplusplus
}
#endif

#endif
