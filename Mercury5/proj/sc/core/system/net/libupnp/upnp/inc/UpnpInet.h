#ifndef UPNPINET_H
#define UPNPINET_H

/*!
 * \addtogroup Sock
 * 
 * @{
 * 
 * \file
 *
 * \brief Provides a platform independent way to include TCP/IP types and functions.
 */

#include "UpnpUniStd.h" /* for close() */

#ifdef WIN32
	#include <stdarg.h>
	#ifndef UPNP_USE_MSVCPP
		/* Removed: not required (and cause compilation issues) */
		#include <winbase.h>
		#include <windef.h>
	#endif
	#include <winsock2.h>
	#include <iphlpapi.h>
	#include <ws2tcpip.h>

	#define UpnpCloseSocket closesocket

	#if(_WIN32_WINNT < 0x0600)
		typedef short sa_family_t;
	#else
		typedef ADDRESS_FAMILY sa_family_t;
	#endif

#else /* WIN32 */
#ifdef __AMN_OS_LINUX__
	#include <sys/param.h>
	#if defined(__sun)
		#include <fcntl.h>
		#include <sys/sockio.h>
	#elif (defined(BSD) && BSD >= 199306) || defined (__FreeBSD_kernel__)
		#include <ifaddrs.h>
		/* Do not move or remove the include below for "sys/socket"!
		 * Will break FreeBSD builds. */
		#include <sys/socket.h>
	#endif
	#include <arpa/inet.h>  /* for inet_pton() */
	#include <net/if.h>
	#include <netinet/in.h>

	/*! Alias to close() to make code more WIN32 tolerant. */
	#define UpnpCloseSocket close
#else
	#include "amn_osal.h"
	#include "netdb.h"

	#define MSG_DONTROUTE    4

	//--------------------------------------------------------------------
	/* POSIX.1g specifies this type name for the `sa_family' member.  */
	typedef unsigned short int sa_family_t;

	/* This macro is used to declare the initial common members
	   of the data types used for socket addresses, `struct sockaddr',
	   `struct sockaddr_in', `struct sockaddr_un', etc.  */

	#define __SOCKADDR_COMMON(sa_prefix) \
	  sa_family_t sa_prefix##family

	#define __SOCKADDR_COMMON_SIZE  (sizeof (unsigned short int))
	
	//--------------------------------------------------------------------
	/* Structure large enough to hold any socket address (with the historical
	   exception of AF_UNIX).  We reserve 128 bytes.  */
	#define __ss_aligntype  unsigned long int
	#define _SS_SIZE        128
	#define _SS_PADSIZE     (_SS_SIZE - (2 * sizeof (__ss_aligntype)))

	struct sockaddr_storage
	{
	  u8_t ss_len;
	  u8_t ss_family;
	  u16_t ss_port;
	//__SOCKADDR_COMMON (ss_);    /* Address family, etc.  */
	__ss_aligntype __ss_align;  /* Force desired alignment.  */
	char __ss_padding[_SS_PADSIZE];
	};

	struct in6_addr {
	        union {
	                u8_t            u6_addr8[16];
	                u16_t           u6_addr16[8];
	                u32_t           u6_addr32[4];
	        } in6_u;
	#define s6_addr                 in6_u.u6_addr8
	#define s6_addr16               in6_u.u6_addr16
	#define s6_addr32               in6_u.u6_addr32
	};

	struct sockaddr_in6 {
	        unsigned short int      sin6_family;    /* AF_INET6 */
	        u16_t                   sin6_port;      /* Transport layer port # */
	        u32_t                   sin6_flowinfo;  /* IPv6 flow information */
	        struct in6_addr         sin6_addr;      /* IPv6 address */
	        u32_t                   sin6_scope_id;  /* scope id (new in RFC2553) */
	};

	#define INET_ADDRSTRLEN 16
	#define INET6_ADDRSTRLEN 46

	#ifndef PF_INET
	#define PF_INET         2       /* IP protocol family.  */
	#define AF_INET         PF_INET
	#endif
	#ifndef PF_INET6
	#define PF_INET6        10      /* IP version 6.  */
	#define AF_INET6        PF_INET6
	#endif

	#define UpnpCloseSocket net_close
	//--------------------------------------------------------------------
#endif

	/*! This typedef makes the code slightly more WIN32 tolerant.
	 * On WIN32 systems, SOCKET is unsigned and is not a file
	 * descriptor. */
	typedef int SOCKET;

	/*! INVALID_SOCKET is unsigned on win32. */
	#define INVALID_SOCKET (-1)

	/*! select() returns SOCKET_ERROR on win32. */
	#define SOCKET_ERROR (-1)
#endif /* WIN32 */

/* @} Sock */

#endif /* UPNPINET_H */
