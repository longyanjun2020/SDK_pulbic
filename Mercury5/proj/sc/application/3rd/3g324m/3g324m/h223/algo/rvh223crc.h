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
#ifndef _CRC_H_
#define _CRC_H_

#include "rvtypes.h"

/* Notes on usage:
    1. For all CRCs, except the CRC16, initialize the first CRC to 0.

    2. The routines are restricted to BYTE-sized chunks to allow the usage of lookup tables
    to accelerate computation. (It is possible to do otherwise, but we loose ~10x speed factor).

    3. In H223 CRC16 is unique in that it requires an initial value of 0xffff and the final CRC
    is the result of the last crc retured XOR-red with 0xffff:
                        true_crc = final_crc ^ 0xffff


#ifdef __cplusplus
extern "C" {
#endif

Note: In polynomial specification the left-most bit (normally the MSB) is considered
        bit 0 of the polynomial. Also, for CRC-n, having bit n set is always implicit. */

#define CRC_8_POLY  0xe0        /* 1110 0000    (H223 7.3.3.2.3, bits (8),2,1,0) */
#define CRC_8_INIT_ONES   0
#define CRC_8_FLIP_RESULT 0

#define CRC_16_POLY 0x4408      /* 0100 0100 0000 1000  (H223 7.4.3.2.3, bits (16),12,5,1) */
#define CRC_16_INIT_ONES   1    /* Pre-conditioning */
#define CRC_16_FLIP_RESULT 1    /* Post-conditioning */

#define CRC_4_POLY  0x07        /* 0111 (H223 C.1.4.7.2, bits (4),3,2,1) */
#define CRC_4_INIT_ONES    0
#define CRC_4_FLIP_RESULT  0

#define CRC_12_POLY 0x0f01      /* 1111 0000 0001 */
#define CRC_12_INIT_ONES   0    /* (H223 C.1.4.7.2, bits (12),11,3,2,1,0) */
#define CRC_12_FLIP_RESULT 0

#define CRC_20_POLY 0x056001    /* 0101 0110 0000 0000 0001  */
#define CRC_20_INIT_ONES   0    /* (H223 C.1.4.7.2, bits (20),19,6,5,3,1) */
#define CRC_20_FLIP_RESULT 0

#define CRC_28_POLY 0x05600001  /* 0101 0110    0000 0000   0000 0000   0001  */
#define CRC_28_INIT_ONES   0    /* (H223 C.1.4.7.2, bits (28),27,6,5,3,1) */
#define CRC_28_FLIP_RESULT 0

#define CRC_32_POLY 0xEDB88320L /* 1110 1101    1011 1000   1000 0011   0010 0000    */
#define CRC_32_INIT_ONES   0    /* (H223 D.4.1.7.2, bits (32),26,23,22,16,12,11,10,8,7,5,4,2,1,0) */
#define CRC_32_FLIP_RESULT 0

/******************************************************************************
 * RvH223CalculateAlxMCRCx
 * ----------------------------------------------------------------------------
 * General: Calculates x-bit CRC for AL1M/AL3M.
 *
 * Return Value: CRC.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   buffer  - Data buffer.
 *          size    - Size of buffer.
 *          pos     - offset in the data buffer
 *          reg     - Initial value of register.
 *****************************************************************************/
RvUint8  RvH223CalculateAlxMCRC4  (IN RvUint8* buffer,
                                   IN RvUint32 size,
                                   IN RvUint16 pos,
                                   IN RvUint8 reg);
RvUint8  RvH223CalculateAlxMCRC8  (IN RvUint8* buffer,
                                   IN RvUint32 size,
                                   IN RvUint16 pos,
                                   IN RvUint8 reg);
RvUint16 RvH223CalculateAlxMCRC12 (IN RvUint8* buffer,
                                   IN RvUint32 size,
                                   IN RvUint16 pos,
                                   IN RvUint16 reg);
RvUint16 RvH223CalculateAlxMCRC16 (IN RvUint8* buffer,
                                   IN RvUint32 size,
                                   IN RvUint16 pos,
                                   IN RvUint16 reg);
RvUint32 RvH223CalculateAlxMCRC20 (IN RvUint8* buffer,
                                   IN RvUint32 size,
                                   IN RvUint16 pos,
                                   IN RvUint32 reg);
RvUint32 RvH223CalculateAlxMCRC28 (IN RvUint8* buffer,
                                   IN RvUint32 size,
                                   IN RvUint16 pos,
                                   IN RvUint32 reg);
RvUint32 RvH223CalculateAlxMCRC32 (IN RvUint8* buffer,
                                   IN RvUint32 size,
                                   IN RvUint16 pos,
                                   IN RvUint32 reg);


#ifdef __cplusplus
}
#endif

#endif
