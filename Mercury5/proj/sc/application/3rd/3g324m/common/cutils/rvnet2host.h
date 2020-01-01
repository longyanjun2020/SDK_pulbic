/* rvnet2host.h - converst network/host organized header bytes */

/************************************************************************
        Copyright (c) 2002 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/

#if !defined(RV_NET2HOST_H)
#define RV_NET2HOST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rvtypes.h"


/* Macros for conversion of byte ordering */
#if (RV_ARCH_ENDIAN == RV_ARCH_LITTLE_ENDIAN)

/* Always use these macros with a variable - never pass an argument or a function call as a
   parameter of these macros! */
/************************************************************************************************************************
 * RvConvertHostToNetwork64
 *
 * Converts a 64bit integer in host order to an integer in a network format.
 *
 * INPUT   :  host       : value to convert.
 * OUTPUT  :  None.
 * RETURN  :  The converted value.
 */
RVCOREAPI
RvUint64 RVCALLCONV RvConvertHostToNetwork64(RvUint64 host);

/************************************************************************************************************************
 * RvConvertHostToNetwork32
 *
 * Converts an integer in host order to an integer in a network format.
 *
 * INPUT   :  host       : value to convert.
 * OUTPUT  :  None.
 * RETURN  :  The converted value.
 */
RVCOREAPI
RvUint32 RVCALLCONV RvConvertHostToNetwork32(RvUint32 host);

/************************************************************************************************************************
 * RvConvertHostToNetwork16
 *
 * Converts a short integer in host order to a short integer in a network format.
 *
 * INPUT   :  host       : value to convert.
 * OUTPUT  :  None.
 * RETURN  :  The converted value.
 */
RVCOREAPI
RvUint16 RVCALLCONV RvConvertHostToNetwork16(RvUint16 host);

#define RvConvertNetworkToHost64(_network) RvConvertHostToNetwork64(_network)
#define RvConvertNetworkToHost32(_network) RvConvertHostToNetwork32(_network)
#define RvConvertNetworkToHost16(_network) RvConvertHostToNetwork16(_network)

#elif (RV_ARCH_ENDIAN == RV_ARCH_BIG_ENDIAN)

#define RvConvertHostToNetwork64(_host) (_host)
#define RvConvertNetworkToHost64(_network) (_network)
#define RvConvertHostToNetwork32(_host) (_host)
#define RvConvertNetworkToHost32(_network) (_network)
#define RvConvertHostToNetwork16(_host) (_host)
#define RvConvertNetworkToHost16(_network) (_network)

#endif

	
/************************************************************************************************************************
 * RvNet2Host2Network
 *
 * Converts an array of 4-byte integers from host format to network format.  The integers can
 * then be sent over the network.
 *
 * INPUT   :  buff       : A pointer to the buffer location where the array of 4-byte integers in host format are located.
 *            startIndex : The exact byte location in the buffer where the integers in host format begin.
 *            size       : The number of integers to convert.
 * OUTPUT  :  None.
 * RETURN  :  None
 */
RVCOREAPI
void RVCALLCONV RvNet2Host2Network(
	IN RvUint8	*buff,
	IN RvInt	startIndex,
	IN RvInt	size);


/***********************************************************************************************************************
 * RvNet2Host2Host
 * Converts an array of 4-byte integers from network format to host format.
 * INPUT   : buff       : A pointer to the buffer location where the array of 4-byte integers in network format are located,
 *                        and where the conversion occurs.
 *           startIndex : The exact byte location in the buffer where the integers in network format begin.
 *           size       : The number of integers to convert.
 * OUTPUT  : None.
 * RETURN  : None.
 */
RVCOREAPI
void RVCALLCONV RvNet2Host2Host(
	IN RvUint8	*buff,
	IN RvInt	startIndex,
	IN RvInt	size);

#ifdef __cplusplus
}
#endif

#endif

