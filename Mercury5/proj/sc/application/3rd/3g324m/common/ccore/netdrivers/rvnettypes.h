/* rvnettypes.h - Common Core public types networking types and APIs*/

/************************************************************************
                Copyright (c) 2006 RADVISION Inc.
************************************************************************
NOTICE:
This document contains information that is proprietary to RADVISION LTD.
No part of this publication may be reproduced in any form whatsoever
without written prior approval by RADVISION LTD..

RADVISION LTD. reserves the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
************************************************************************/


#ifndef _RV_NETTYPES_H
#define _RV_NETTYPES_H

/*
 * RvTLSMethod - defines supported SSL versions:
 *----------------------------------------------------------------------
 * SSL_V1	- SSL version 1
 * SSL_V2	- SSL version 2
 * TLS_V1	- SSL version 3
 */
typedef enum {
	RV_TLS_SSL_V2 = 1,
	RV_TLS_SSL_V3,
	RV_TLS_TLS_V1
} RvTLSMethod;



#define RV_TLS_DEFAULT_CERT_DEPTH	(-1) /* Used to specify that default
										  certificate chain lenght should
										  be used */


/*
 * RvPrivKeyType - defines supported private keys types:
 *----------------------------------------------------------------------
 * RSA	- RSA key type
 */
typedef enum {
	RV_TLS_RSA_KEY = 1
} RvPrivKeyType;


#include "rvtypes.h"

#if (RV_NET_TYPE != RV_NET_NONE)

/* Support address types. */
#define RV_ADDRESS_TYPE_NONE RvIntConst(0)
#define RV_ADDRESS_TYPE_IPV4 RvIntConst(1)
#define RV_ADDRESS_TYPE_IPV6 RvIntConst(2)

/* IPV4 definitions */
#define RV_ADDRESS_IPV4_STRINGSIZE 16               /* Max size of IPV4 address string */
#define RV_ADDRESS_IPV4_ADDRSIZE 4                  /* Size of IPV4 address */
#define RV_ADDRESS_IPV4_ANYADDRESS RvUint32Const(0) /* for dynamic addresss binding */
#define RV_ADDRESS_IPV4_BROADCAST RvUint32Const(0xFFFFFFFF)
#define RV_ADDRESS_IPV4_ANYPORT RvUint16Const(0)    /* for dynamic port binding */

/* abstract IPv4 address structure used internally inside the core */
typedef struct {
    RvUint32 ip;    /* 4 byte IP address, network format */
    RvUint16 port;  /* 2 byte port number, host format */
} RvAddressIpv4;


#if (RV_NET_TYPE & RV_NET_IPV6)
/* IPV6 definitions */
#define RV_ADDRESS_IPV6_STRINGSIZE 46               /* Max size of IPV6 address string */
#define RV_ADDRESS_IPV6_ADDRSIZE 16                 /* Size of IPV6 address */
#define RV_ADDRESS_IPV6_ANYPORT RvUint16Const(0)    /* for dynamic port binding */

/* abstract IPv6 address structure used internally inside the core */
typedef struct {
    RvUint8 ip[16];     /* 16 byte IP address, network format */
    RvUint16 port;      /* 2 byte port number, host format */
    RvUint32 scopeId;   /* 4 bytes of interface for a scope. todo: also could
                           be implemented as a list of interfaces */
} RvAddressIpv6;

#endif


/* abstract IP address structure used internally inside the core */
typedef struct
{
    RvInt   addrtype; /* Address type */
    union
    {
        /* One for each address type supported. */
        RvAddressIpv4 ipv4;
#if (RV_NET_TYPE & RV_NET_IPV6)
        RvAddressIpv6 ipv6;
#endif
    } data;
} RvAddress;

/* For comparisons */
#define RV_ADDRESS_FULLADDRESS RvIntConst(0) /* Compare entire address. */
#define RV_ADDRESS_BASEADDRESS RvIntConst(1) /* Compare only the base address */

/* Combined Constants */
#if (RV_NET_TYPE & RV_NET_IPV6)
#define RV_ADDRESS_MAXSTRINGSIZE RV_ADDRESS_IPV6_STRINGSIZE /* Max size of any address string */
#define RV_ADDRESS_MAXADDRSIZE RV_ADDRESS_IPV6_ADDRSIZE /* Max address size of any address. */
#else
#define RV_ADDRESS_MAXSTRINGSIZE RV_ADDRESS_IPV4_STRINGSIZE /* Max size of any address string */
#define RV_ADDRESS_MAXADDRSIZE RV_ADDRESS_IPV4_ADDRSIZE /* Max address size of any address. */
#endif

#if defined(__cplusplus)
extern "C" {
#endif


/**********************************************************************************
 * RvAddressConstruct - creates default address structure.
 *
 * INPUT:
 *  addr        - pointer to a pre-located address structure.
 *  addrtype    - type of address.
 * RETURN:
 *  RvStatus    - pointer to the given address struct, or NULL on failure.
 */
RVCOREAPI RvAddress * RVCALLCONV RvAddressConstruct(
    IN    RvInt addrtype,
	INOUT RvAddress *addr);


/**********************************************************************************
 * RvAddressGetType - return the address type.
 *
 * INPUT:
 *  addr        - pointer to a pre-located address structure.
 * RETURN:
 *  RvInt       - address type.
 */
RVCOREAPI RvInt RVCALLCONV RvAddressGetType(
    IN const RvAddress *addr);

/**********************************************************************************
 * RvAddressCopy
 * copy an address structure.
 * INPUT:
 *  source - pointer to the source address
 *  result - pointer to a pre-located target address structure.
 * RETURN:
 *  RvStatus    - pointer to a pre-located target address structure
 */
RVCOREAPI RvAddress * RVCALLCONV RvAddressCopy(
    IN const RvAddress *source,
    INOUT RvAddress *result);

/**********************************************************************************
 * RvAddressCompare
 * compare 2 address-structures.
 * INPUT:
 *  addr1 - pointer to address 1.
 *  addr2 - pointer to address 2.
 *  comparetype - RV_ADDRESS_FULLADDRESS - checks also the port,
 *                RV_ADDRESS_BASEADDRESS - checks only ip
 * RETURN:
 *  RvStatus    - RV_TRUE/RV_FALSE
 */
RVCOREAPI RvBool RVCALLCONV RvAddressCompare(
    IN const RvAddress *addr1,
    IN const RvAddress *addr2,
    IN RvInt comparetype);

/**********************************************************************************
 * RvAddressGetString
 * converts the IP address to string.
 * INPUT:
 *  addr - pointer to address to get the ip from.
 *  bufsize - size of string buffer.
 *  buf - the buffer in which to put the converted ip in.
 * RETURN:
 *  RvStatus    - the converted ip string.
 */
RVCOREAPI RvChar * RVCALLCONV RvAddressGetString(
    IN const RvAddress *addr,
    IN RvSize_t bufsize,
    INOUT RvChar *buf);

/**********************************************************************************
 * RvAddressSetString
 * sets an IP in string format to core-format structure.
 * INPUT:
 *  buf - the source string format ip
 *  addr - the address structure to set the ip into.
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddress * RVCALLCONV RvAddressSetString(
    IN const RvChar *buf,
    INOUT RvAddress *addr);

#define RvAddressDestruct(_a)
#define RvAddressChangeType(_a, _t) RvAddressConstruct((_a), (_t))

/* IPV4 Utility functions. */

/**********************************************************************************
 * RvAddressGetIpPort
 * extract the port from an rvAddress structure.
 * INPUT:
 *  addr - the address structure to get the port from.
 * RETURN:
 *   result - the port.
 */
RVCOREAPI RvUint16 RVCALLCONV RvAddressGetIpPort(
    IN const RvAddress *addr);

/**********************************************************************************
 * RvAddressIsNull
 * check if an all the bits of an address are 0
 * INPUT:
 *  addr - the address structure
 * RETURN:
 *  RvBool - RV_TRUE if address is null, RV_FALSE o/w
 */
RVCOREAPI RvBool RVCALLCONV RvAddressIsNull(
    IN const RvAddress *addr);

/**********************************************************************************
 * RvAddressSetIpPort
 * sets the port in an rvAddress structure.
 * INPUT:
 *  addr - the address structure to ser the port into.
 *  port - the port.
 * RETURN:
 *  RvStatus - the port.
 */
RVCOREAPI RvAddress * RVCALLCONV RvAddressSetIpPort(
    INOUT RvAddress *addr,
    IN RvUint16 port);

/**********************************************************************************
 * RvAddressIsMulticastIp
 * Return RV_TRUE if addr is a multicast address.
 * INPUT:
 *  addr - the address structure to check.
 * RETURN:
 *  RvStatus - RV_TRUE if addr is a multicast address.
 */
RVCOREAPI RvBool RVCALLCONV RvAddressIsMulticastIp(
    IN const RvAddress *addr);

/**********************************************************************************
 * RvAddressConstructIpv4
 * creates a core-format address structure.
 * INPUT:
 *  addr - the address structure to check.
 *  ip - ip value to set in the new address structure
 *  port - port value to set in the new address structure
 * RETURN:
 *  RvStatus - the new address.
 */
RVCOREAPI RvAddress * RVCALLCONV RvAddressConstructIpv4(
    INOUT RvAddress *addr,
    IN RvUint32 ip,
    IN RvUint16 port);

/**********************************************************************************
 * RvAddressIpv4ToString
 * converts an hexa-format ip to a string format ip.
 * INPUT:
 *  buf - pointer to a buffer in which to place the string.
 *  bufsize - buffer size.
 *  ip - the ip value in hexa format
 * RETURN:
 *  RvStatus - the ip in string format.
 */
RVCOREAPI RvChar * RVCALLCONV RvAddressIpv4ToString(
    INOUT RvChar *buf,
    IN RvSize_t bufsize,
    IN RvUint32 ip);

/**********************************************************************************
 * RvAddressIpv4ToString
 * converts a string format ip address to an integer format ip.
 * INPUT:
 *  ipbuf - pointer to a place in which to store the IP value.
 *  buf - pointer to the pi string to convert.
 * RETURN:
 *  RvStatus - RV_TRUE on success.
 */
RVCOREAPI RvBool RVCALLCONV RvAddressStringToIpv4(
    INOUT  RvUint32 *ip,
    IN const RvChar *buf);

#define RvAddressChangeTypeIpv4(_a, _i, _p) RvAddressConstructIpv4((_a), (_i), (_p))

/**********************************************************************************
 * RvAddressGetIpv4
 * extracts the ip value from an address-structure.
 * INPUT:
 *  addr - pointer to the structure from which to get the ip from.
 * RETURN:
 *  RvStatus - the ip value.
 */
RVCOREAPI const RvAddressIpv4 * RVCALLCONV RvAddressGetIpv4(
    IN const RvAddress *addr);

/* IPV4 specific functions. Only use if absolutely necessary. */

/**********************************************************************************
 * RvAddressIpv4Construct
 * creates an ipv4 core format address structure.
 * INPUT:
 *  addr - pointer to the structure to "fill in".
 *  ip - ip address in integer format.
 *  port - port to use in the new address structure
 * RETURN:
 *  RvStatus - the new address structure
 */
RVCOREAPI RvAddressIpv4 * RVCALLCONV RvAddressIpv4Construct(
    INOUT RvAddressIpv4 *addr,
    IN RvUint32 ip,
    IN RvUint16 port);

/**********************************************************************************
 * RvAddressIpv4Compare
 * compare 2 ipv4 address-structures.
 * INPUT:
 *  addr1 - pointer to address 1.
 *  addr2 - pointer to address 2.
 *  comparetype - RV_ADDRESS_FULLADDRESS - checks also the port,
 *                RV_ADDRESS_BASEADDRESS - checks only ip
 * RETURN:
 *  RvStatus    - RV_TRUE/RV_FALSE
 */
RVCOREAPI RvBool RVCALLCONV RvAddressIpv4Compare(
    IN const RvAddressIpv4 *addr1,
    IN const RvAddressIpv4 *addr2,
    IN RvInt comparetype);

/**********************************************************************************
 * RvAddressIpv4GetString
 * converts the IPv4 address to string.
 * INPUT:
 *  addr - pointer to address to get the ip from.
 *  bufsize - size of string buffer.
 *  buf - the buffer in which to put the converted ip in.
 * RETURN:
 *  RvStatus    - the converted ip string.
 */
RVCOREAPI RvChar * RVCALLCONV RvAddressIpv4GetString(
    IN const RvAddressIpv4 *addr,
    IN RvSize_t bufsize,
    INOUT RvChar *buf);

/**********************************************************************************
 * RvAddressIpv4SetString
 * sets an IPv4 in string format to core-format structure.
 * INPUT:
 *  buf - the source string format ip
 *  addr - the address structure to set the ip into.
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddressIpv4 * RVCALLCONV RvAddressIpv4SetString(
    IN const RvChar *buf,
    INOUT RvAddressIpv4 *addr);

/**********************************************************************************
 * RvAddressIpv4GetIp
 * extract the ip value from an ipv4 rvAddress structure.
 * INPUT:
 *  addr - the address structure to get the ip from.
 * RETURN:
 *  RvStatus - the ip value.
 */
RVCOREAPI RvUint32 RVCALLCONV RvAddressIpv4GetIp(
    IN const RvAddressIpv4 *addr);

/**********************************************************************************
 * RvAddressIpv4SetIp
 * sets the ip value in an ipv4 rvAddress structure.
 * INPUT:
 *  addr - the address structure to set the ip in.
 *  ip   - the ip value
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddressIpv4 * RVCALLCONV RvAddressIpv4SetIp(
    INOUT RvAddressIpv4 *addr,
    IN RvUint32 ip);

/**********************************************************************************
 * RvAddressIpv4GetPort
 * extract the port from an ipv4 rvAddress structure.
 * INPUT:
 *  addr - the address structure to get the port from.
 * RETURN:
 *  RvStatus - the port.
 */
RVCOREAPI RvUint16 RVCALLCONV RvAddressIpv4GetPort(
    IN const RvAddressIpv4 *addr);

/**********************************************************************************
 * RvAddressIpv4IsNull
 * check if an all the bits of an address are 0
 * INPUT:
 *  addr - the address structure
 * RETURN:
 *  RvBool - RV_TRUE if address is null, RV_FALSE o/w
 */
RVCOREAPI RvBool RVCALLCONV RvAddressIpv4IsNull(
    IN const RvAddressIpv4 *addr);

/**********************************************************************************
 * RvAddressIpv4SetPort
 * sets the port from in ipv4 rvAddress structure.
 * INPUT:
 *  addr - the address structure to set the port in.
 *  port - the port value.
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddressIpv4 * RVCALLCONV RvAddressIpv4SetPort(
    INOUT RvAddressIpv4 *addr,
    IN RvUint16 port);

/**********************************************************************************
 * RvAddressIpv4IsMulticast
 * Return RV_TRUE if ipv4 address is a multicast address.
 * INPUT:
 *  addr - the address structure to check.
 * RETURN:
 *  RvStatus - RV_TRUE if addr is a multicast address.
 */
RVCOREAPI RvBool RVCALLCONV RvAddressIpv4IsMulticast(
    IN const RvAddressIpv4 *addr);

#if (RV_NET_TYPE & RV_NET_IPV6)
/* IPV6 specific functions */

/**********************************************************************************
 * RvAddressGetIpv6Scope
 * extract the scope number from an ipv6 rvAddress structure.
 * INPUT:
 *  addr - the address structure to get the scope from.
 * RETURN:
 *  RvStatus - the scope value.
 */
RVCOREAPI RvUint32 RVCALLCONV RvAddressGetIpv6Scope(
    IN const RvAddress *addr);

#else
#define RvAddressGetIpv6Scope(a) (-1)
#endif



#if (RV_NET_TYPE & RV_NET_IPV6)
/* IPV6 Utility functions. */


/**********************************************************************************
 * RvAddressSetIpv6Scope
 * sets the scope number in an ipv6 rvAddress structure.
 * INPUT:
 *  addr - the address structure to set the scope in.
 *  scopeId - scope dumber to set.
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddress * RVCALLCONV RvAddressSetIpv6Scope(
    INOUT RvAddress *addr,
    IN RvUint32 scopeId);

/**********************************************************************************
 * RvAddressConstructIpv6
 * creates a new core-format IPv6 address structure.
 * INPUT:
 *  addr - the address structure to "fill in".
 *  ip - pointer to a 16byte ipv6 string.
 *  port - port number to set.
 *  scopeId - scope number to set.
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddress * RVCALLCONV RvAddressConstructIpv6(
    INOUT RvAddress *addr,
    IN const RvUint8 *ip,
    IN RvUint16 port,
    IN RvUint32 scopeId);

RVCOREAPI RvAddress * RVCALLCONV RvAddressConstructIpv6FromIpv4(
    INOUT RvAddress *addr,
    IN    RvAddress *ipv4addr);

/**********************************************************************************
 * RvAddressIpv6ToString
 * converts a hexa-format string ipv6 to a string format ip.
 * INPUT:
 *  buf - pointer to a buffer in which to place the string.
 *  bufsize - buffer size.
 *  ip - the ip value in hexa format
 * RETURN:
 *  RvStatus - the ip in string format.
 */
RVCOREAPI RvChar * RVCALLCONV RvAddressIpv6ToString(
    INOUT RvChar *buf,
    IN RvSize_t bufsize,
    IN const RvUint8 *ip);

/**********************************************************************************
 * RvAddressStringToIpv6
 * converts a string format ipv6 address to an hexa-format string ip.
 * INPUT:
 *  ip - pointer to a place in which to store the IP value.
 *  buf - pointer to the ip string to convert.
 * RETURN:
 *  RvStatus - RV_TRUE on success.
 */
RVCOREAPI RvBool RVCALLCONV RvAddressStringToIpv6(
    INOUT RvUint8 *ip,
    IN const RvChar *buf);

#define RvAddressChangeTypeIpv6(_a, _i, _p, _s) RvAddressConstructIpv6((_a), (_i), (_p), (_s))

/* IPV6 specific functions. Only use if absolutely necessary. */

/**********************************************************************************
 * RvAddressGetIpv6
 * extracts the ip value from an ipv6 address-structure.
 * INPUT:
 *  addr - pointer to the structure from which to get the ip from.
 * RETURN:
 *  RvStatus - the ipv6 structure.
 */
RVCOREAPI const RvAddressIpv6 * RVCALLCONV RvAddressGetIpv6(
    IN const RvAddress *addr);

/**********************************************************************************
 * RvAddressIpv6Construct
 * creates an ipv6 core format address structure.
 * INPUT:
 *  ip - ip address in string format.
 *  port - port to use in the new address structure
 *  scopeId - scope number to set.
 *  addr - pointer to the structure to "fill in".
 * RETURN:
 *  RvStatus - the new address structure
 */
RVCOREAPI RvAddressIpv6 * RVCALLCONV RvAddressIpv6Construct(
    IN const RvUint8 *ip,
    IN RvUint16 port,
    IN RvUint32 scopeId,
	INOUT RvAddressIpv6 *addr);

/**********************************************************************************
 * RvAddressIpv6Compare
 * compare 2 ipv4 address-structures.
 * INPUT:
 *  addr1 - pointer to address 1.
 *  addr2 - pointer to address 2.
 *  comparetype - RV_ADDRESS_FULLADDRESS - checks also the port and scopeId
 *                RV_ADDRESS_BASEADDRESS - checks only ip
 * RETURN:
 *  RvStatus    - RV_TRUE/RV_FALSE
 */
RVCOREAPI RvBool RVCALLCONV RvAddressIpv6Compare(
    IN const RvAddressIpv6 *addr1,
    IN const RvAddressIpv6 *addr2,
    IN RvInt comparetype);

/**********************************************************************************
 * RvAddressIpv6GetString
 * converts the IPv6 address to string.
 * INPUT:
 *  addr - pointer to address to get the ip from.
 *  bufsize - size of string buffer.
 *  buf - the buffer in which to put the converted ip in.
 * RETURN:
 *  RvStatus    - the converted ip string.
 */
RVCOREAPI RvChar * RVCALLCONV RvAddressIpv6GetString(
    IN const RvAddressIpv6 *addr,
    IN RvSize_t bufsize,
    INOUT RvChar *buf);

/**********************************************************************************
 * RvAddressIpv6SetString
 * sets an IPv6 in string format to core-format structure.
 * INPUT:
 *  addr - the address structure to set the ip into.
 *  buf - the source string format ip
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddressIpv6 * RVCALLCONV RvAddressIpv6SetString(
    IN const RvChar *buf,
    INOUT RvAddressIpv6 *addr);

/**********************************************************************************
 * RvAddressIpv6GetIp
 * extract the ip value from an ipv6 rvAddress structure.
 * INPUT:
 *  addr - the address structure to get the ip from.
 * RETURN:
 *  RvStatus - the ip value.
 */
RVCOREAPI const RvUint8 * RVCALLCONV RvAddressIpv6GetIp(
    IN const RvAddressIpv6 *addr);

/**********************************************************************************
 * RvAddressIpv6SetIp
 * sets the ip value in an ipv6 rvAddress structure.
 * INPUT:
 *  addr - the address structure to set the ip in.
 *  ip   - the ip value
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddressIpv6 * RVCALLCONV RvAddressIpv6SetIp(
    INOUT RvAddressIpv6 *addr,
    IN const RvUint8 *ip);

/**********************************************************************************
 * RvAddressIpv6GetPort
 * extract the port from an ipv6 rvAddress structure.
 * INPUT:
 *  addr - the address structure to get the port from.
 * RETURN:
 *  RvStatus - the port.
 */
RVCOREAPI RvUint16 RVCALLCONV RvAddressIpv6GetPort(
    IN const RvAddressIpv6 *addr);

/**********************************************************************************
 * RvAddressIpv6IsNull
 * check if an all the bits of an address are 0
 * INPUT:
 *  addr - the address structure
 * RETURN:
 *  RvBool - RV_TRUE if address is null, RV_FALSE o/w
 */
RVCOREAPI RvBool RVCALLCONV RvAddressIpv6IsNull(
    IN const RvAddressIpv6 *addr);

/**********************************************************************************
 * RvAddressIpv6SetPort
 * sets the port from in ipv6 rvAddress structure.
 * INPUT:
 *  addr - the address structure to set the port in.
 *  port - the port value.
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddressIpv6 * RVCALLCONV RvAddressIpv6SetPort(
    INOUT RvAddressIpv6 *addr,
    IN RvUint16 port);

/**********************************************************************************
 * RvAddressIpv6GetScope
 * extract the scope number from an ipv6 rvAddress structure.
 * INPUT:
 *  addr - the address structure to get the scope from.
 * RETURN:
 *  RvStatus - the scope value.
 */
RVCOREAPI RvUint32 RVCALLCONV RvAddressIpv6GetScope(
    IN const RvAddressIpv6 *addr);

/**********************************************************************************
 * RvAddressIpv6SetScope
 * sets the scope number in an ipv6 rvAddress structure.
 * INPUT:
 *  addr - the address structure to set the scope in.
 *  scopeId - scope number to set.
 * RETURN:
 *  RvStatus - the new address structure.
 */
RVCOREAPI RvAddressIpv6 * RVCALLCONV RvAddressIpv6SetScope(
    INOUT RvAddressIpv6 *addr,
    IN RvUint32 scopeId);

/**********************************************************************************
 * RvAddressIpv6IsMulticast
 * Return RV_TRUE if ipv6 address is a multicast address.
 * INPUT:
 *  addr - the address structure to check.
 * RETURN:
 *  RvStatus - RV_TRUE if addr is a multicast address.
 */
RVCOREAPI RvBool RVCALLCONV RvAddressIpv6IsMulticast(
    IN const RvAddressIpv6 *addr);

#else /* (RV_NET_TYPE & RV_NET_IPV6) */

#define RvAddressConstructIpv6(addr, ip, port, scopeId) NULL
#define RvAddressSetIpv6Scope(addr,scopeId) (0)

#endif /* (RV_NET_TYPE & RV_NET_IPV6) */


#ifdef __cplusplus
}
#endif

#endif /* (RV_NET_TYPE != RV_NET_NONE) */


#endif /*#ifndef _RV_NETTYPES_H*/
