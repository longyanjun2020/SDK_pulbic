/******************************************************************************
        Copyright (c) 2005 RADVISION Inc. and RADVISION Ltd.
*******************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
******************************************************************************/

#ifndef _RV_H223_EGOLAY_H_
#define _RV_H223_EGOLAY_H_

/* GOLAY (23, 12, 7) and Extended GOLAY (24, 12, 8) code implementations

 References: *	http://mathworld.wolfram.com/GolayCode.html
 *	http://planetmath.org/encyclopedia/ExtendedBinaryGolayCode.html
 *    http://www.maths.ex.ac.uk/~rjc/etc/golay11.pdf 
 *    John Wiley - The Art of Error Correcting Coding

 GOLAY (X,Y,Z): There are 2^Y codewords, each X bits long, which are different from
                each other by at least Z bits.
 The EGOLAY(X,Y,Z) code is a GOLAY(X-1,Y,Z-1) code with an added parity bit.
 Parity is defined at (mod 2) sum of the bits in the code (even 1s --> zero parity)

 Requirements for the implementation:
 Memory:
		EGOLAY_LOOKUP table:	8K byte
		EGOLAY_DATA_CORRECTION: 8K byte
 CPU:
      Minimal (table lookup)

 Note: Code for computing content of lookup tables is supplied, but commented out
*/

#include "rvtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EGOLAY_OK			 0x00
#define EGOLAY_FIXED	 	 0x01
#define EGOLAY_UNFIXABLE	 0xff


RvUint16 RvH223EGolayEncode (IN  RvUint16  data);
RvUint8  RvH223EGolayDecode (IN  RvUint16  received_data,
                             IN  RvUint16  received_egolay,
                             OUT RvUint16 *corrected_data);



#ifdef __cplusplus
}
#endif


#endif /* _RV_H223_EGOLAY_H_ */
