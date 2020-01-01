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
#ifndef _SEBCH_H_
#define _SEBCH_H_

#include "rvtypes.h"

#define SEBCH_DECODE_FAILED 0xff
#ifdef __cplusplus
extern "C" {
#endif

/* SEBCH (16,7,6) : H.223 C.4.1.5.4 p34 - for AL1M / AL3M
      7 data bits    (0.. 6)
      9 parity bits  (7..15)

   Capabilities: Fixes 2-bit errors anywhere. Chance of fixing 3-bit errors */

RvUint16 sebch_16_7_6_Encode(IN RvUint16 data);
RvUint8  sebch_16_7_6_Decode(IN RvUint16 data);

/* SEBCH (16,5,8): H.223 C.4.2.3.1.2 p51 - for AL2M
      5 data bits    (0.. 4)
     11 parity bits  (5..15)

   Capabilities: Fixes 3-bit errors anywhere. Chance of fixing 4-bit errors */

RvUint16 sebch_16_5_8_Encode(IN RvUint16 data);
RvUint8  sebch_16_5_8_Decode(IN RvUint16 data);

#ifdef __cplusplus
}
#endif

#endif /* _SEBCH_H_ */

