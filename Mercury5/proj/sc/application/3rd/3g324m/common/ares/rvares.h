/***********************************************************************
Filename   : rvares.h
Description: Interface functions for DNS resolving services
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
#ifndef RV_ARES_H
#define RV_ARES_H

#include "rvaddress.h"
#include "rvlog.h"
#include "ares.h"


/* Error checks to make sure configuration has been done properly */
#if !defined(RV_DNS_TYPE) || \
    ((RV_DNS_TYPE != RV_DNS_NONE) && (RV_DNS_TYPE != RV_DNS_ARES))
#error RV_DNS_TYPE not set properly
#endif


#if defined(__cplusplus)
extern "C" {
#endif

/* DNS error codes calculation */
#define RvDnsErrorCode(_e) RvErrorCode(RV_ERROR_LIBCODE_CCORE, RV_CCORE_MODULE_DNS, (_e))

/* Record type not supported - DNS reply accepted with record type not supported by this resolver */
#define RV_DNS_ERROR_RTNOTSUPP RvDnsErrorCode(-513)
#define RV_DNS_QUERY_CANCELED  RvDnsErrorCode(-514)

/* Caching error - page size too small - shoulrn't happen */
#define RV_DNS_ERROR_SMALLPAGE      RvDnsErrorCode(-515) 

/* Requested record wasn't found (result of NXDOMAIN/NODATA code in DNS response */
#define RV_DNS_ERROR_NOTFOUND       RvDnsErrorCode(-516)
#define RV_DNS_ERROR_CACHE_NOTFOUND RvDnsErrorCode(-517)    
#define RV_DNS_ERROR_INCALLBACK     RvDnsErrorCode(-518) /* query currently in it's callback - cannot be canceled */

/* Resource type in response is different from resource type in question */
#define RV_DNS_ERROR_RTUNEXPECTED   RvDnsErrorCode(-519)

/* Malformed record */  
#define RV_DNS_ERROR_RMALFORMED     RvDnsErrorCode(-520)
    
#define RV_DNS_MAX_DOMAINS (31)




/********************************************************************************************
 * RvAresInit
 *
 * Initializes the DNS module.
 *
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RvStatus RvAresInit(void);


/********************************************************************************************
 * RvAresEnd
 *
 * Shutdown the DNS module.
 *
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RvStatus RvAresEnd(void);


/********************************************************************************************
 * RvAresSourceConstruct
 *
 * Constructs a Log Source object for the DNS module.
 *
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RvStatus RvAresSourceConstruct(RvLogMgr* logMgr);



#if (RV_DNS_TYPE == RV_DNS_ARES)

/********************************************************************************************
 * RvAresConstruct
 *
 * Constructs a DNS engine, allocates memory for the DNS server state structures,
 * allocates memory for TCP input data and sets the user callback routine which will
 * be called upon answers arrival.
 *
 * INPUT:
 *  selectEngine - select engine constructed by the user previously and will be
 *                 used to receive transport events from DNS servers
 *  newItemCB    - a user callback routine to handle DNS replies
 *  maxServers   - the maximum number of DNS servers that will be configured
 *                 will be set to the actual number of servers found in the system repository
 *  maxDomains   - the maximum number of domain strings that will be configured
 *                 will be set to the actual number of domains found in the system repository
 *  tcpBuffLen   - length of the TCP buffer that will be used to receive DNS replies
 *  logMgr       - handle of the log manager for this instance
 * OUTPUT:
 *  dnsEngine    - a structure of type RvDnsEngine allocated by the user
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvAresConstructN(
	IN  RvSelectEngine*     selectEngine,
	IN  RvDnsNewRecordCB    newRecordCB,
    IN  RvInt               maxServers,
    IN  RvInt               maxDomains,
    IN  RvInt               tcpBuffLen,
	IN  RvLogMgr*           logMgr,
	OUT RvDnsEngine*        dnsEngine);


/********************************************************************************************
 * RvAresConstruct
 *
 * Constructs a DNS engine, allocates memory for the DNS server state structures,
 * allocates memory for TCP input data and sets the user callback routine which will
 * be called upon answers arrival.
 *
 * INPUT:
 *  selectEngine - select engine constructed by the user previously and will be
 *                 used to receive transport events from DNS servers
 *  newItemCB    - a user callback routine to handle DNS replies
 *  maxServers   - the maximum number of DNS servers that will be configured
 *                 will be set to the actual number of servers found in the system repository
 *  maxDomains   - the maximum number of domain strings that will be configured
 *                 will be set to the actual number of domains found in the system repository
 *  tcpBuffLen   - length of the TCP buffer that will be used to receive DNS replies
 *  logMgr       - handle of the log manager for this instance
 * OUTPUT:
 *  dnsEngine    - a structure of type RvDnsEngine allocated by the user
 * RETURNS:
 *  RV_OK on success, other values on failure
 */

RVCOREAPI RvStatus RVCALLCONV RvAresConstructO(
	IN    RvSelectEngine*    selectEngine,
	IN    RvDnsNewRecordCB   newRecordCB,
    INOUT RvInt*             maxServers,
    INOUT RvInt*             maxDomains,
    IN    RvInt              tcpBuffLen,
    IN    RvBool             retrieveDnsServers,
    IN    RvBool             retrieveDnsSuffix,
	IN    RvLogMgr*          logMgr,
	OUT   RvDnsEngine*       dnsEngine);

#if defined(RV_CCORE_COMP_MODE) && (RV_CCORE_COMP_MODE < 0x1100)
#define RvAresConstruct RvAresConstruct0
#else
#define RvAresConstruct RvAresConstructN
#endif

/********************************************************************************************
 * RvAresDestruct
 *
 * Destructs a DNS engine.
 *
 * INPUT:
 *  dnsEngine  - a DNS engine structure
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvAresDestruct(
	IN RvDnsEngine*         dnsEngine);


/********************************************************************************************
 * RvAresConfigure
 *
 * Read the system configuration (DNS servers and suffix list) and set the values
 * in the DNS engine.
 * This function completes the construction of a DNS engine.
 *
 * INPUT:
 *  dnsEngine    - a DNS engine structure
 *  configType   - a bit-mask indicating what part of the system configuration should be set.
 *                 allowable values are RV_DNS_SERVERS and RV_DNS_SUFFIXES
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvAresConfigure(
    IN  RvDnsEngine*        dnsEngine,
    IN  RvDnsConfigType     configType);


/********************************************************************************************
 * RvAresSetParams
 *
 * Change the default parameters for a DNS engine.
 *
 * INPUT:
 *  dnsEngine    - a DNS engine structure
 *  timeoutInSec - timeout in seconds for un-answered query
 *  nTries       - number of tries before canceling a query
 *  dnsServList  - array of DNS server addresses
 *  nServers     - number of DNS server addresses
 *  dnsDomains   - array of DNS domain suffixes
 *  nDomains     - number of DNS domain suffixes
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvAresSetParams(
	IN  RvDnsEngine*        dnsEngine,
    IN  RvInt               timeoutInSec,
    IN  RvInt               nTries,
    IN  RvAddress*          dnsServList,
    IN  RvInt               nServers,
    IN  RvChar**            dnsDomains,
    IN  RvInt               nDomains);


/********************************************************************************************
 * RvAresGetParams
 *
 * Retrieve the configuration parameters for a DNS engine.
 *
 * INPUT:
 *  dnsEngine    - a DNS engine structure
 * OUTPUT:
 *  timeoutInSec - timeout in seconds for un-answered query
 *  nTries       - number of tries before canceling a query
 *  dnsServList  - array of DNS server addresses
 *  nServers     - number of DNS server addresses
 *  dnsDomains   - array of DNS domain suffixes
 *  nDomains     - number of DNS domain suffixes
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvAresGetParams(
    IN     RvDnsEngine*     dnsEngine,
    OUT    RvInt*           timeoutInSec,
    OUT    RvInt*           nTries,
    OUT    RvAddress*       dnsServList,
    INOUT  RvInt*           nServers,
    OUT    char**           dnsDomains,
    INOUT  RvInt*           nDomains);


/********************************************************************************************
 * RvAresSendQueryEx
 *
 * Sends a DNS query to one of the pre-configured DNS servers and returns immediately
 * before replies are received.
 *
 * INPUT:
 *  dnsEngine   - a DNS engine structure constructed previously
 *  dnsQuery    - type of query (enum value: IPv4/6, SRV or NAPTR)
 *  dnsName     - the name of the domain to search for its DNS records
 *  as_is       - indicates whether ARES will use the "suffix algorithm" or send a query
 *                with the provided name as-is
 *  queryBuffer - a buffer of qbufLen bytes long to be used by ARES as a work area
 *                to generate the query.
 *                the buffer must not be corrupted by the user until a reply is received
 *  qbufLen     - specifies the length in bytes of queryBuffer.
 *                if length is too small an error is returned and the required value is
 *                set into this parameter.
 *                Note: this notification may occurred iteratively more than once
 *  newRecordCB - user callback. If newRecordCB == 0, dnsEngine newRecordCB will be used
 *  context     - a user private data. will be delivered to the user callback
 * OUTPUT:
 *  queryId     - the query id; generated by ARES; enables the user to cancel transactions
 *                and also delivered to the user callback together with the context param.
 * RETURNS:
 *  RV_OK on success, other values on failure
 *  RV_ERROR_INSUFFICIENT_BUFFER - queryBuffer is too small. Required size of query buffer is 
 *                given by *qbufLen
 *  RV_DNS_ERROR_NOTFOUND - record wasn't found.
 */
RVCOREAPI RvStatus RVCALLCONV RvAresSendQueryEx(
	IN    RvDnsEngine*      dnsEngine,
	IN    RvDnsQueryType    dnsQuery,
    IN    const RvChar*     dnsName,
    IN    RvBool            as_is,
    IN    void*             queryBuffer,
    INOUT RvInt*            qbufLen,
    IN    RvDnsNewRecordCB  newRecordCB,
	IN    void*             context,
    OUT   RvUint32*         queryId);

#define RvAresSendQuery(dnsEngine, queryType, dnsName, asis, queryBuffer, qbufLen, ctx, queryId) \
    RvAresSendQueryEx(dnsEngine, queryType, dnsName, asis, queryBuffer, qbufLen, 0, ctx, queryId)


/********************************************************************************************
 * RvAresCancelQuery
 *
 * Asks ARES to ignore replies for a query which has been already sent.
 * The query buffer provided by the user is no longer valid to ARES.
 *
 * INPUT:
 *  dnsEngine   - a DNS engine structure constructed previously
 *  queryId     - the query id supplied by ARES when the query was sent
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RVCOREAPI RvStatus RVCALLCONV RvAresCancelQuery(
	IN  RvDnsEngine*        dnsEngine,
    IN  RvUint32            queryId);



RVCOREAPI RvStatus RVCALLCONV RvAresCancelQueryEx(RvDnsEngine *dnsEngine, RvUint32 queryId, RvBool waitForCallbacks);

/********************************************************************************************
 * RvAresClearCache
 *
 * Clears internal DNS cache
 * Pay attention, all instances of RvDnsEngine in the process shares the same cache by default.
 * So, clearing the cache will affect all instances of RvDnsEngine
 *
 *
 * INPUT:
 *  dnsEngine   - a DNS engine structure constructed previously
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
RVCOREAPI 
RvStatus RVCALLCONV RvAresClearCache(RvDnsEngine *dnsEngine);


#endif /* RV_DNS_NONE */


#if defined(__cplusplus)
}
#endif


#endif /* RV_ARES_H */
