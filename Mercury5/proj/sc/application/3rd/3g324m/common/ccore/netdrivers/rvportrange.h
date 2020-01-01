/***********************************************************************
Filename   : rvportrange.h
Description: port range implementation.
************************************************************************
                Copyright (c) 2001 RADVISION Inc.
************************************************************************
NOTICE:
This document contains information that is proprietary to RADVISION LTD.
No part of this publication may be reproduced in any form whatsoever
without written prior approval by RADVISION LTD..

RADVISION LTD. reserves the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
************************************************************************/

#ifndef _RV_PORT_RANGE_H
#define _RV_PORT_RANGE_H

#include "rvccore.h"

/*
   The port-range allows allocation of ports from within a given range.
   The port-range object holds a linked-list of free ports. Whenever someone
   wants a port, he can allocate one from the range, when it is no more
   needed, he can return it to the port range, making sure it will be the
   last one to be reallocated.

   This code is used by rvsocket for some of the operating systems and
   for the port-range feature. */


/* Error checks to make sure configuration has been done properly */
#if !defined(RV_PORTRANGE_TYPE) || ((RV_PORTRANGE_TYPE != RV_PORTRANGE_SLIM) && \
    (RV_PORTRANGE_TYPE != RV_PORTRANGE_FAST))
#error RV_PORTRANGE_TYPE not set properly
#endif
/* End of configuration error checks */



#if defined(__cplusplus)
extern "C" {
#endif


/********************************************************************************************
 * RvPortRange object
 * A port range holds a range of ports in a linked list of "free" ports, allowing the user
 * to get ports from this list and release ports back into the list.
 * The port range itself isn't thread-safe and the user of this object should provide the
 * locking for it.
 * When using a "slim" port range, the implementation is only an index of the last port
 * tried.
 ********************************************************************************************/
typedef struct
{
    RvUint16        fromPort; /* Port the range starts from */
    RvUint16        toPort; /* Port the range ends in */
    RvUint          numberOfFreePorts; /* The number of free ports in the port range */

#if (RV_PORTRANGE_TYPE == RV_PORTRANGE_FAST)
    RvUint16        nextToAllocate; /* Next port index to allocate */
    RvUint16        lastToAllocate; /* Last port index to allocate */
    RvUint16*       range; /* Range of ports we can allocate */

#elif (RV_PORTRANGE_TYPE == RV_PORTRANGE_SLIM)
    RvUint16        next; /* Next port to allocate */
#endif

    RvLock          lock; /* Lock to use for thread-safety */
	RvLogMgr*       logMgr;        /* port range log manager */
	RvLogSource*    prangeSource;  /* log source, to be used for the port range module instance */
} RvPortRange;



/********************************************************************************************
 * RvPortRangeSourceConstruct - Constructs PortRange module log source.
 *
 * Constructs log source to be used by common core when printing log from the 
 * PortRange module. This function is applied per instance of log manager.
 * 
 * INPUT   : logMgr - log manager instance
 * OUTPUT  : none
 * RETURN  : RV_OK if successful otherwise an error code. 
 */
RvStatus RvPortRangeSourceConstruct(
	IN RvLogMgr	*logMgr);


#if (RV_NET_TYPE != RV_NET_NONE)

/********************************************************************************************
 * RvPortRangeConstruct
 *
 * purpose : Create a port-range object.
 * input   : fromPort   - Port to start from in the range
 *           toPort     - Last port in the range
 * output  : portRange  - Object to construct
 * return  : RV_OK on success, other on failure
 ********************************************************************************************/
RVCOREAPI
RvStatus RVCALLCONV RvPortRangeConstruct(
    IN  RvUint       fromPort,
    IN  RvUint       toPort,
	IN  RvLogMgr*    logMgr,
    OUT RvPortRange* portRange);


/********************************************************************************************
 * RvPortRangeDestruct
 *
 * purpose : Kill a port-range object.
 * input   : portRange  - Object to destruct
 * output  : None
 * return  : RV_OK on success, other on failure
 ********************************************************************************************/
RVCOREAPI
RvStatus RVCALLCONV  RvPortRangeDestruct(
    IN RvPortRange* portRange);


/********************************************************************************************
 * RvPortRangeGetRange
 *
 * purpose : Returns a range of ports the port-range object deals with
 * input   : portRange  - Port range object to use
 * output  : fromPort   - Port we're starting from
 *           toPort     - Last port in range
 * return  : RV_OK on success, other on failure
 ********************************************************************************************/
RvStatus RvPortRangeGetRange(
    IN  RvPortRange*    portRange,
    OUT RvUint*         fromPort,
    OUT RvUint*         toPort);


/********************************************************************************************
 * RvPortRangeGetNumberOfFreePorts
 *
 * purpose : Returns the number of free ports in port range
 * input   : portRange  - Port range object to use
 * output  : freePorts  - The number of free ports
 * return  : RV_OK on success, other on failure
 ********************************************************************************************/
RVCOREAPI
RvStatus RVCALLCONV RvPortRangeGetNumberOfFreePorts(
    IN  RvPortRange*    portRange,
    OUT RvUint*         freePorts);


/********************************************************************************************
 * RvPortRangeGetPort
 *
 * purpose : Returns a port from the port range
 * input   : portRange  - Port range object to use
 * output  : port       - Free port for the application's use
 * return  : RV_OK on success, other on failure
 ********************************************************************************************/
RVCOREAPI
RvStatus RVCALLCONV RvPortRangeGetPort(
    IN  RvPortRange*    portRange,
    OUT RvUint*         port);


/********************************************************************************************
 * RvPortRangeReleasePort
 *
 * purpose : Returns the port into the port range
 * input   : portRange      - Port range object to use
 *           portToRelease  - Port to return to the port range
 * output  : None
 * return  : RV_OK on success, other on failure
 ********************************************************************************************/
RVCOREAPI
RvStatus RVCALLCONV RvPortRangeReleasePort(
    IN  RvPortRange*    portRange,
    IN  RvUint          portToRelease);


#endif /* (RV_NET_TYPE != RV_NET_NONE) */

#if defined(__cplusplus)
}
#endif

#endif /* _RV_PORT_RANGE_H */
