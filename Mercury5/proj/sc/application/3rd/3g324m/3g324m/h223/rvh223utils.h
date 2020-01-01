/******************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
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

#ifndef _RV_H223_UTILS_H
#define _RV_H223_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                               */
/*---------------------------------------------------------------------------*/

/******************************************************************************
 * RvH223CalculateCRC16
 * ----------------------------------------------------------------------------
 * General: Calculates CRC16.
 *
 * Return Value: CRC16.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  	reg     - Initial value of register.
 *          buffer  - Data buffer.
 *          size    - Size of buffer.
 *          xorout  - Flag indicating whether we need to XOR the output value.
 *****************************************************************************/
RvUint16 RvH223CalculateCRC16 (RvUint16 reg, RvUint8 *buffer, RvUint32 size, RvBool xorout);

/******************************************************************************
 * RvH223CalculateCRC8
 * ----------------------------------------------------------------------------
 * General: Calculates CRC8.
 *
 * Return Value: CRC.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:   reg     - Initial value of register.
 *          buffer  - Data buffer.
 *          size    - Size of buffer.
 *****************************************************************************/
RvUint8 RvH223CalculateCRC8 (RvUint8 reg, RvUint8 *buffer, RvUint32 size);

/******************************************************************************
 * RvH223CalculateCRC8AndReflect
 * ----------------------------------------------------------------------------
 * General: Calculates CRC8 and reflects the final value.
 *
 * Return Value: CRC.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  	reg     - Initial value of register.
 *          buffer  - Data buffer.
 *          size    - Size of buffer.
 *****************************************************************************/
RvUint8 RvH223CalculateCRC8AndReflect (RvUint8 reg, RvUint8 *buffer, RvUint32 size);

/******************************************************************************
 * RvH223EncodeGolay
 * ----------------------------------------------------------------------------
 * General: Calculates Golay 24-12-8 code.
 *
 * Return Value: Golay code in 12 low bits.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  	data  - 12 low bits.
 *****************************************************************************/
RvUint16 RvH223EncodeGolay (IN RvUint16 data);

/******************************************************************************
 * RvH223DecodeGolay
 * ----------------------------------------------------------------------------
 * General: Decodes Golay 24-12-8 codeword.
 *
 * Return Value: Decoded data in 12 low bits.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  	codeword  - 24 low bits.
 * Output:  errors    - pointer to be filled with the number of errors.
 *****************************************************************************/
RvUint16  RvH223DecodeGolay (RvUint32 codeword, RvUint8 *errors);


#ifdef __cplusplus
}
#endif

#endif /* _RV_H223_UTILS_H */
