/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _RV_CODER_BIT_BUFFER_H
#define _RV_CODER_BIT_BUFFER_H

#include "rvtypes.h"
#include "rverror.h"

#ifdef __cplusplus
extern "C" {
#endif


RV_DECLARE_HANDLE(HBB); /* handler */

typedef struct
{
    unsigned int    maxOctets;
    RvUint32        bitsInUse;
    RvUint8*        octets; /* buffer */
    RvBool          isOverflowOfBuffer; /*RV_TRUE if we reached a buffer overflow */
} bbStruct;




/* returns number of bytes needed to contain the bitLength */
unsigned int bbSetByte(IN RvUint32 bitLength);

RVINTAPI int RVCALLCONV
bbGetAllocationSize(int maxOctets);

RVINTAPI HBB RVCALLCONV
bbConstructFrom(IN int maxOctets, /* size of buffer in octetes */
            IN char *buffer,
            IN int bufferSize);

RVINTAPI int RVCALLCONV
bbSetOctets(IN  HBB bbH,
        IN  int maxOctets, /* size of buffer in octets */
        IN  RvInt32 bitsInUse, /* number of bits already in use */
        IN  RvUint8 *octetBuffer); /* octet memory */

#define bbDestruct(_bbH)

/* returns pointer to the octet array */
RvUint8 *bbOctets(HBB bbH);

/* return number of alignment bits (modulu 8) */
int bbAlignBits(HBB bbH,
        IN RvInt32 location);

/* return number of bits in use */
int bbAlignTail(HBB bbH);

RvInt32 bbFreeBits      (HBB bbH);
int bbFreeBytes     (HBB bbH);
RvUint32 bbBitsInUse     (HBB bbH);
unsigned bbBytesInUse    (HBB bbH);



/* concatenate src to buffer */
int bbAddTail(HBB bbH,
          IN RvUint8 *src,
          IN RvUint32 srcBitsLength,
          IN RvBool isAligned); /* true if src is aligned */

int bbAddTailFrom(HBB bbH,
          IN  RvUint8 *src,
          IN  RvUint32 srcFrom, /* offset for beginning of data in src, in bits */
          IN  RvUint32 srcBitsLength,
          IN  RvBool isAligned); /* true if src is aligned */


/* move bits within buffer
   bitLength bits starting at fromOffset shall be moved to position starting at toOffset */
int bbMove(HBB bbH,
       IN  RvUint32 fromOffset,
       IN  RvUint32 bitLength,
       IN  RvUint32 toOffset);

/* Desc: Set bits within buffer. */
int bbSet(HBB bbH,
      IN  RvUint32 fromOffset,
      IN  RvUint32 bitLength,
      IN  RvUint8 *src);

void bbSetOverflow(HBB bbH);





#ifdef __cplusplus
}
#endif


#endif  /* _RV_CODER_BIT_BUFFER_H */

