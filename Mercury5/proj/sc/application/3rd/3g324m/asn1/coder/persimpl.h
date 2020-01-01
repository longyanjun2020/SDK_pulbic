#ifdef __cplusplus
extern "C" {
#endif



/*
***********************************************************************************

NOTICE:
This document contains information that is proprietary to RADVISION LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVISION LTD..

RADVISION LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

***********************************************************************************
*/

/*
  perSimple.h

  Simple type encoding/decoding
  ASN.1 PER basic-aligned variant.
  */

#ifndef _PERSIMPLE_
#define _PERSIMPLE_

#include "coderbitbuffer.h"

typedef enum {
  perLenTypeCONSTRAINED = 1,
  perLenTypeNORMALLY_SMALL,
  perLenTypeUNCONSTRAINED
} perLenType;


int perEncodeInt(IN  RvUint32 n,
         IN  RvUint32 lb,
         IN  RvUint32 ub,
                 IN  RvBool isFromAbsent,
                 IN  RvBool isToAbsent,
         IN  RvBool isExtension,
         OUT HBB bbH); /* Should be initialized with sufficient size.
                  It has to have at least 4 bytes size. */


/* RV_TRUE or negative value on failure */
RVINTAPI int RVCALLCONV
perDecodeInt(
         /* Decodes an integer from a bit buffer. */
         OUT RvUint32 *n, /* decoded number */
         IN  RvUint32 lb,
         IN  RvUint32 ub,
         IN  RvBool isFromAbsent,
         IN  RvBool isToAbsent,
         IN  RvBool isExtension,
         IN  HPER hPer,
         IN  RvUint32 from, /* position in buffer */
         OUT RvUint32 *decoded,
         IN  const char* desc /* short description (optional) */
         );

int perEncodeLen(IN  perLenType type,  /* CONSTRAINED, NORMALLY_SMALL, UNCONSTRAINED */
         IN  RvUint32 n,  /* the length */
         IN  RvUint32 lb,  /* only for constrained type */
         IN  RvUint32 ub,  /* only for constrained type */
         OUT HBB bbH); /* Should be initialized with sufficient size.
                  It has to have at least 4 bytes size. */

RVINTAPI int RVCALLCONV
perDecodeLen(IN  perLenType type, /* CONSTRAINED, NORMALLY_SMALL, UNCONSTRAINED */
         OUT RvUint32 *n, /* the length */
         IN  RvUint32 lb,
         IN  RvUint32 ub,
         OUT HPER hPer,
         IN  RvUint32 from, /* position in buffer */
         OUT RvUint32 *decoded);

int perEncodeBool(IN  RvBool n,
          OUT HBB bbH); /* Should be initialized with sufficient size.
                   It has to have at least 1 byte size. */

RVINTAPI int RVCALLCONV
perDecodeBool(OUT RvBool *n,
          IN  HPER hPer,
          IN  RvUint32 from,
          OUT RvUint32 *decoded);

RVINTAPI int RVCALLCONV
perEncodeNormallySmallInt(IN  RvUint32 n, /* the number */
                  OUT HBB bbH);


RVINTAPI int RVCALLCONV
perDecodeNormallySmallInt(OUT RvUint32 *n, /* the number */
                  IN  HPER hPer,
                  IN  RvUint32 from,
                  OUT RvUint32 *dec);

int perEncodeNumber(IN  RvUint32 n,
            IN  RvUint32 b,  /* number of bits to hold the encoding */
            OUT HBB bbH); /* Should be initialized with sufficient size. */

int perDecodeNumber(OUT RvUint32 *n, /* decoded number */
            IN  RvUint32 b,  /* number of bits to hold the encoding */
            IN  HPER hPer,
            IN  RvUint32 from, /* position in buffer */
            OUT RvUint32 *decoded);


#endif
#ifdef __cplusplus
}
#endif



