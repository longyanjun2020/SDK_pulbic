/***********************************************************************
Filename   : rvhost.h
Description: host related functions
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
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

#ifndef _RV_HOST_H
#define _RV_HOST_H

#include "rvccore.h"
#include "rvaddress.h"
#include "rvlog.h"


/* Error checks to make sure configuration has been done properly */
#if !defined(RV_HOST_TYPE) || ((RV_HOST_TYPE != RV_HOST_BSD) && \
    (RV_HOST_TYPE != RV_HOST_POSIX) && (RV_HOST_TYPE != RV_HOST_VXWORKS) && \
    (RV_HOST_TYPE != RV_HOST_PSOS) && (RV_HOST_TYPE != RV_HOST_OSE) && \
    (RV_HOST_TYPE != RV_HOST_NUCLEUS) && (RV_HOST_TYPE != RV_HOST_WIN32))
#error RV_HOST_TYPE not set properly
#endif

#if !defined(RV_HOST_MAX_NAMESIZE) || (RV_HOST_MAX_NAMESIZE < 1)
#error RV_HOST_MAX_NAMESIZE not set properly
#endif

#if !defined(RV_HOST_MAX_ADDRS) || (RV_HOST_MAX_ADDRS < 1)
#error RV_HOST_MAX_ADDRS not set properly
#endif

#if !defined(RV_HOST_HAS_STATIC_ADDR) || ((RV_HOST_HAS_STATIC_ADDR != RV_NO) && (RV_HOST_HAS_STATIC_ADDR != RV_YES))
#error RV_HOST_HAS_STATIC_ADDR not set properly
#endif

/* End of configuration error checks */


#if defined(__cplusplus)
extern "C" {
#endif


RvStatus RvHostInit(void);
RvStatus RvHostEnd(void);
RvStatus RvHostSourceConstruct(IN RvLogMgr* logMgr);


#if (RV_NET_TYPE != RV_NET_NONE)

/********************************************************************************************
 * RvHostGetIpList
 * Get the IP list of a host. This is done for IPv4 addresses only.
 * INPUT   : hostName   - Name of host to look for
 *           logMgr     - log manager instance
 *           numOfIps   - Maximum number of IPs to get
 * OUTPUT  : numOfIps   - Number of IPs we got
 *           ipList     - List of IPs we got
 * RETURN  : RV_OK on success
 *           Other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvHostGetIpList(
    IN      RvChar*     hostName,
	IN      RvLogMgr*   logMgr,
    INOUT   RvUint32*   numOfIps,
    OUT     RvAddress*  ipList);

/********************************************************************************************
 * RvHostLocalGetName
 * Get the name of the local host.
 * INPUT   : nameLength - Length of the name buffer in bytes
 *           logMgr     - log manager instance
 * OUTPUT  : name       - Null terminated name of the local host
 * RETURN  : RV_OK on success
 *           Other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvHostLocalGetName(
    IN  RvSize_t    nameLength,
	IN  RvLogMgr*   logMgr,
    OUT RvChar*     name);


/********************************************************************************************
 * RvHostLocalGetAddress
 * Get the addresses of the local host. This is done for IPv4 addresses only.
 * INPUT   : logMgr             - log manager instance
 *           numberOfAddresses  - Maximum number of addresses to get
 *           addresses          - Array of addresses to fill in
 * OUTPUT  : numberOfAddresses  - Number of addresses filled in
 *           addresses          - Constructed addresses. These addresses should be destructed
 *                                using RvAddressDestruct() when not needed anymore.
 * RETURN  : RV_OK on success
 *           Other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvHostLocalGetAddress(
	IN      RvLogMgr*   logMgr,
    INOUT   RvUint32*   numberOfAddresses,
    INOUT   RvAddress*  addresses);


#if (RV_OS_TYPE == RV_OS_TYPE_MOPI)
/********************************************************************************************
 * RvHostMopiSetIpAddress
 * Dynamically sets the IP address of RTP or SIP (they have the same IP address) client.
 * INPUT   : address - address in dot notation, null terminated.
 * OUTPUT  : None.
 * RETURN  : RV_OK on success
 */
RVCOREAPI
RvStatus RVCALLCONV RvHostMopiSetIpAddress(RvChar *address);
#endif

#if defined(__cplusplus)
}
#endif

#endif /* _RV_HOST_H */

#endif /* (RV_NET_TYPE != RV_NET_NONE) */
