/***********************************************************************
Copyright (c) 2003 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..
RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _PER_
#define _PER_

#include "pvaltree.h"
#include "coderbitbuffer.h"


#ifdef __cplusplus
extern "C" {
#endif



RV_DECLARE_HANDLE(HPER);


RvInt32 bbGet2Right(HPER hPer,
        IN RvUint32 fromBitPosition, /* in buffer */
        IN RvUint32 numOfBitsToGet,
        OUT RvUint8 *dest); /* destination buffer */

RvInt32 bbGet2Left(HPER hPer,
           IN RvUint32 fromBitPosition, /* in buffer */
           IN RvUint32 numOfBitsToGet,
           OUT RvUint8 *dest); /* destination buffer */



int perGetMsa(void);

/************************************************************************
 * perConstruct
 * purpose: Construct PER information needed by the encode/decode manager.
 * input  : maxBufSize  - Maximum size of buffer supported (messages larger
 *                        than this size in bytes cannot be decoded/encoded).
 * output : none
 * return : none
 ************************************************************************/
void perConstruct(IN int maxBufSize);

/************************************************************************
 * perBufferEnd
 * purpose: close down the local storage
 * input  : none
 * output : none
 * return : void
 ************************************************************************/
void perBufferEnd(void);


RVINTAPI void RVCALLCONV
perDestruct(void);


#ifdef __cplusplus
}
#endif


#endif /* _PER_ */

