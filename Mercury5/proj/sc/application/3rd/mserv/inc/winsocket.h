/*
* This file includes parts which are Copyright (c) 1982-1986 Regents
* of the University of California.  All rights reserved.  The
* Berkeley Software License Agreement specifies the terms and
* conditions for redistribution.
*/

/****************************************************************************/
/*  File    : winsocket.h                                                   */
/*--------------------------------------------------------------------------*/
/*  Scope   : Constants,Structure, Macro and Prototypes definition          */
/*            of MIC XML parser                                             */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
* --------------------------------------------------------------------------
*  Date     | Author | Revision       | Description
* ----------+--------+----------------+-------------------------------------
*/

#ifndef _WINSOCK_API_H_
#define _WINSOCK_API_H_

#ifndef _WINSOCKAPI_
/*
* Basic system type definitions, taken from the BSD file sys/types.h.
*/
#if defined(__GNUC__)&&defined(__i686__)
#include <sys/types.h>
#else //__GNUC__&&__i686__
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;
#endif //__GNUC__&&__i686__
/*
* The new type to be used in all
* instances which refer to sockets.
*/
typedef u_int           SOCKET;

/*
* Select uses arrays of SOCKETs.  These macros manipulate such
* arrays.  FD_SETSIZE may be defined by the user before including
* this file, but the default here should be >= 64.
*
* CAVEAT IMPLEMENTOR and USER: THESE MACROS AND TYPES MUST BE
* INCLUDED IN WINSOCK.H EXACTLY AS SHOWN HERE.
*/
#ifndef FD_SETSIZE
#define FD_SETSIZE      64
#endif /* FD_SETSIZE */

#if defined(__GNUC__)&&defined(__i686__)
#include <sys/select.h>
#else //__GNUC__&&__i686__

#undef fd_set

typedef struct fd_set
{
	u_int   fd_count;               /* how many are SET? */
	SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs */
} fd_set;

/*
* Structure used in select() call, taken from the BSD file sys/time.h.
*/
struct timeval
{
	long    tv_sec;         /* seconds */
	long    tv_usec;        /* and microseconds */
};

#endif //__GNUC__&&__i686__

/*
* Operations on timevals.
*
* NB: timercmp does not work for >= or <=.
*/
#define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp) \
	((tvp)->tv_sec cmp (uvp)->tv_sec || \
	(tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0

/*
* Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
*
*
* Ioctl's have the command encoded in the lower word,
* and the size of any in or out parameters in the upper
* word.  The high 2 bits of the upper word are used
* to encode the in/out status of the parameter; for now
* we restrict parameters to at most 128 bytes.
*/
#define IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define IOC_VOID        0x20000000      /* no parameters */
#define IOC_OUT         0x40000000      /* copy out parameters */
#define IOC_IN          0x80000000      /* copy in parameters */
#define IOC_INOUT       (IOC_IN|IOC_OUT)
/* 0x20000000 distinguishes new &
old ioctl's */
#define _IO(x,y)        (IOC_VOID|((x)<<8)|(y))

#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define FIONREAD    _IOR('f', 127, u_long) /* get # bytes to read */
#define FIONBIO     _IOW('f', 126, u_long) /* set/clear non-blocking i/o */
#define FIOASYNC    _IOW('f', 125, u_long) /* set/clear async i/o */

/* Socket I/O Controls */
#define SIOCSHIWAT  _IOW('s',  0, u_long)  /* set high watermark */
#define SIOCGHIWAT  _IOR('s',  1, u_long)  /* get high watermark */
#define SIOCSLOWAT  _IOW('s',  2, u_long)  /* set low watermark */
#define SIOCGLOWAT  _IOR('s',  3, u_long)  /* get low watermark */
#define SIOCATMARK  _IOR('s',  7, u_long)  /* at oob mark? */

/*
* Structures returned by network data base library, taken from the
* BSD file netdb.h.  All addresses are supplied in host order, and
* returned in network order (suitable for use in system calls).
*/

struct  hostent
{
	char     *h_name;           /* official name of host */
	char     **h_aliases;  /* alias list */
	short   h_addrtype;             /* host address type */
	short   h_length;               /* length of address */
	char     **h_addr_list; /* list of addresses */
    short   s_free_by_vendor;    /* for debugging purpose, increase while the memory space is freed by vendor */
    short   s_free_by_sdk;       /* for debugging purpose, increase while the memory space is freed by sdk */
    short   s_usage_count;       /* for debugging purpose, increase while the memory space is used for querying */
#define h_addr  h_addr_list[0]          /* address, for backward compat */
};

/*
* It is assumed here that a network number
* fits in 32 bits.
*/
struct  netent
{
	char     *n_name;           /* official name of net */
	char     **n_aliases;  /* alias list */
	short   n_addrtype;             /* net address type */
	u_long  n_net;                  /* network # */
};

struct  servent
{
	char     *s_name;           /* official service name */
	char     **s_aliases;  /* alias list */
	short   s_port;                 /* port # */
	char     *s_proto;          /* protocol to use */
};

struct  protoent
{
	char     *p_name;           /* official protocol name */
	char     **p_aliases;  /* alias list */
	short   p_proto;                /* protocol # */
};

/*
* Constants and structures defined by the internet system,
* Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
*/

/*
* Protocols
*/
#define IPPROTO_IP              0               /* dummy for IP */
#define IPPROTO_ICMP            1               /* control message protocol */
#define IPPROTO_IGMP            2               /* group management protocol */
#define IPPROTO_GGP             3               /* gateway^2 (deprecated) */
#define IPPROTO_TCP             6               /* tcp */
#define IPPROTO_PUP             12              /* pup */
#define IPPROTO_UDP             17              /* user datagram protocol */
#define IPPROTO_IDP             22              /* xns idp */
#define IPPROTO_ND              77              /* UNOFFICIAL net disk proto */

#define IPPROTO_RAW             255             /* raw IP packet */
#define IPPROTO_MAX             256

/*
* Port/socket numbers: network standard functions
*/
#define IPPORT_ECHO             7
#define IPPORT_DISCARD          9
#define IPPORT_SYSTAT           11
#define IPPORT_DAYTIME          13
#define IPPORT_NETSTAT          15
#define IPPORT_FTP              21
#define IPPORT_TELNET           23
#define IPPORT_SMTP             25
#define IPPORT_TIMESERVER       37
#define IPPORT_NAMESERVER       42
#define IPPORT_WHOIS            43
#define IPPORT_MTP              57

/*
* Port/socket numbers: host specific functions
*/
#define IPPORT_TFTP             69
#define IPPORT_RJE              77
#define IPPORT_FINGER           79
#define IPPORT_TTYLINK          87
#define IPPORT_SUPDUP           95

/*
* UNIX TCP sockets
*/
#define IPPORT_EXECSERVER       512
#define IPPORT_LOGINSERVER      513
#define IPPORT_CMDSERVER        514
#define IPPORT_EFSSERVER        520

/*
* UNIX UDP sockets
*/
#define IPPORT_BIFFUDP          512
#define IPPORT_WHOSERVER        513
#define IPPORT_ROUTESERVER      520
/* 520+1 also used */

/*
* Ports < IPPORT_RESERVED are reserved for
* privileged processes (e.g. root).
*/
#define IPPORT_RESERVED         1024

/*
* Link numbers
*/
#define IMPLINK_IP              155
#define IMPLINK_LOWEXPER        156
#define IMPLINK_HIGHEXPER       158

/*
* Internet address (old style... should be updated)
*/
struct in_addr
{
	union
	{
		struct
		{
			u_char s_b1,s_b2,s_b3,s_b4;
		} S_un_b;
		struct
		{
			u_short s_w1,s_w2;
		} S_un_w;
		u_long S_addr;
	} S_un;
#define s_addr  S_un.S_addr
	/* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2
	/* host on imp */
#define s_net   S_un.S_un_b.s_b1
	/* network */
#define s_imp   S_un.S_un_w.s_w2
	/* imp */
#define s_impno S_un.S_un_b.s_b4
	/* imp # */
#define s_lh    S_un.S_un_b.s_b3
	/* logical host */
};

/*
* Definitions of bits in internet address integers.
* On subnets, the decomposition of addresses to host and net parts
* is done according to subnet mask, not the masks here.
*/
#define IN_CLASSA(i)            (((long)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET           0xff000000
#define IN_CLASSA_NSHIFT        24
#define IN_CLASSA_HOST          0x00ffffff
#define IN_CLASSA_MAX           128

#define IN_CLASSB(i)            (((long)(i) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET           0xffff0000
#define IN_CLASSB_NSHIFT        16
#define IN_CLASSB_HOST          0x0000ffff
#define IN_CLASSB_MAX           65536

#define IN_CLASSC(i)            (((long)(i) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET           0xffffff00
#define IN_CLASSC_NSHIFT        8
#define IN_CLASSC_HOST          0x000000ff

#define INADDR_ANY              (u_long)0x00000000
#define INADDR_LOOPBACK         0x7f000001
#define INADDR_BROADCAST        (u_long)0xffffffff
#define INADDR_NONE             0xffffffff

#define MAX_IP_LENGTH (15+1) ///< Maximum length for IPv4 format, xxx.xxx.xxx.xxx

/*
* Socket address, internet style.
*/
struct sockaddr_in
{
	short   sin_family;
	u_short sin_port;
	struct  in_addr sin_addr;
	char    sin_zero[8];
};

/*
* Options for use with [gs]etsockopt at the IP level.
*/
#define IP_OPTIONS          1           /* set/get IP per-packet options    */
#define IP_MULTICAST_IF     2           /* set/get IP multicast interface   */
#define IP_MULTICAST_TTL    3           /* set/get IP multicast timetolive  */
#define IP_MULTICAST_LOOP   4           /* set/get IP multicast loopback    */
#define IP_ADD_MEMBERSHIP   5           /* add  an IP group membership      */
#define IP_DROP_MEMBERSHIP  6           /* drop an IP group membership      */
#define IP_TTL              7           /* set/get IP Time To Live          */
#define IP_TOS              8           /* set/get IP Type Of Service       */
#define IP_DONTFRAGMENT     9           /* set/get IP Don't Fragment flag   */


#define IP_DEFAULT_MULTICAST_TTL   1    /* normally limit m'casts to 1 hop  */
#define IP_DEFAULT_MULTICAST_LOOP  1    /* normally hear sends if a member  */
#define IP_MAX_MEMBERSHIPS         20   /* per socket; must fit in one mbuf */

/*
* Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
*/
struct ip_mreq
{
	struct in_addr  imr_multiaddr;  /* IP multicast address of group */
	struct in_addr  imr_interface;  /* local IP address of interface */
};

/*
* Definitions related to sockets: types, address families, options,
* taken from the BSD file sys/socket.h.
*/

/*
* This is used instead of -1, since the
* SOCKET type is unsigned.
*/
#define INVALID_SOCKET  (SOCKET)(~0)

/*
* Types
*/
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */

/*
* Option flags per-socket.
*/
#define SO_DEBUG        0x0001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define SO_REUSEADDR    0x0004          /* allow local address reuse */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define SO_LINGER       0x0080          /* linger on close if data present */
#define SO_OOBINLINE    0x0100          /* leave received OOB data in line */

#define SO_DONTLINGER   (u_int)(~SO_LINGER)

/*
* Additional options.
*/
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */

/*
* Options for connect and disconnect data and options.  Used only by
* non-TCP/IP transports such as DECNet, OSI TP4, etc.
*/
#define SO_CONNDATA     0x7000
#define SO_CONNOPT      0x7001
#define SO_DISCDATA     0x7002
#define SO_DISCOPT      0x7003
#define SO_CONNDATALEN  0x7004
#define SO_CONNOPTLEN   0x7005
#define SO_DISCDATALEN  0x7006
#define SO_DISCOPTLEN   0x7007

/*
* Option for opening sockets for synchronous access.
*/
#define SO_OPENTYPE     0x7008

#define SO_SYNCHRONOUS_ALERT    0x10
#define SO_SYNCHRONOUS_NONALERT 0x20

/*
* Other NT-specific options.
*/
#define SO_MAXDG        0x7009
#define SO_MAXPATHDG    0x700A
#define SO_UPDATE_ACCEPT_CONTEXT 0x700B
#define SO_CONNECT_TIME 0x700C

/*
* TCP options.
*/
#define TCP_NODELAY     0x0001
#define TCP_BSDURGENT   0x7000

/*
* Address families.
*/
#define AF_UNSPEC       0               /* unspecified */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_IPX          6               /* IPX and SPX */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_ISO          7               /* ISO protocols */
#define AF_OSI          AF_ISO          /* OSI is ISO */
#define AF_ECMA         8               /* european computer manufacturers */
#define AF_DATAKIT      9               /* datakit protocols */
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define AF_SNA          11              /* IBM SNA */
#define AF_DECnet       12              /* DECnet */
#define AF_DLI          13              /* Direct data link interface */
#define AF_LAT          14              /* LAT */
#define AF_HYLINK       15              /* NSC Hyperchannel */
#define AF_APPLETALK    16              /* AppleTalk */
#define AF_NETBIOS      17              /* NetBios-style addresses */
#define AF_VOICEVIEW    18              /* VoiceView */
#define AF_FIREFOX      19              /* FireFox */
#define AF_UNKNOWN1     20              /* Somebody is using this! */
#define AF_BAN          21              /* Banyan */

#define AF_MAX          22

/*
* Structure used by kernel to store most
* addresses.
*/
struct sockaddr
{
	u_short sa_family;              /* address family */
	char    sa_data[14];            /* up to 14 bytes of direct address */
};

/*
* Structure used by kernel to pass protocol
* information in raw sockets.
*/
struct sockproto
{
	u_short sp_family;              /* address family */
	u_short sp_protocol;            /* protocol */
};

/*
* Protocol families, same as address families for now.
*/
#define PF_UNSPEC       AF_UNSPEC
#define PF_UNIX         AF_UNIX
#define PF_INET         AF_INET
#define PF_IMPLINK      AF_IMPLINK
#define PF_PUP          AF_PUP
#define PF_CHAOS        AF_CHAOS
#define PF_NS           AF_NS
#define PF_IPX          AF_IPX
#define PF_ISO          AF_ISO
#define PF_OSI          AF_OSI
#define PF_ECMA         AF_ECMA
#define PF_DATAKIT      AF_DATAKIT
#define PF_CCITT        AF_CCITT
#define PF_SNA          AF_SNA
#define PF_DECnet       AF_DECnet
#define PF_DLI          AF_DLI
#define PF_LAT          AF_LAT
#define PF_HYLINK       AF_HYLINK
#define PF_APPLETALK    AF_APPLETALK
#define PF_VOICEVIEW    AF_VOICEVIEW
#define PF_FIREFOX      AF_FIREFOX
#define PF_UNKNOWN1     AF_UNKNOWN1
#define PF_BAN          AF_BAN

#define PF_MAX          AF_MAX

/*
* Structure used for manipulating linger option.
*/
struct  linger
{
	u_short l_onoff;                /* option on/off */
	u_short l_linger;               /* linger time */
};

/*
* Level number for (get/set)sockopt() to apply to socket itself.
*/
#define SOL_SOCKET      0xffff          /* options for socket level */

/*
* Maximum queue length specifiable by listen.
*/
#define SOMAXCONN       5

#define MSG_OOB         0x1             /* process out-of-band data */
#define MSG_PEEK        0x2             /* peek at incoming message */
#define MSG_DONTROUTE   0x4             /* send without using routing tables */

#define MSG_MAXIOVLEN   16

#define MSG_PARTIAL     0x8000          /* partial send or recv for message xport */

/*
* Define constant based on rfc883, used by gethostbyxxxx() calls.
*/
#define MAXGETHOSTSTRUCT        1024

/*
* All Windows Sockets error constants are biased by NET_E_BASEERR from
* the "normal"
*/
#define NET_E_NOERROR           0
#define NET_E_BASEERR              10000
/*
* Windows Sockets definitions of regular Microsoft C error constants
*/
#define NET_E_INTR                (NET_E_BASEERR+4)
#define NET_E_BADF                (NET_E_BASEERR+9)
#define NET_E_ACCES               (NET_E_BASEERR+13)
#define NET_E_FAULT               (NET_E_BASEERR+14)
#define NET_E_INVAL               (NET_E_BASEERR+22)
#define NET_E_MFILE               (NET_E_BASEERR+24)

/*
* Windows Sockets definitions of regular Berkeley error constants
*/
#define NET_E_WOULDBLOCK          (NET_E_BASEERR+35)
#define NET_E_INPROGRESS          (NET_E_BASEERR+36)
#define NET_E_ALREADY             (NET_E_BASEERR+37)
#define NET_E_NOTSOCK             (NET_E_BASEERR+38)
#define NET_E_DESTADDRREQ         (NET_E_BASEERR+39)
#define NET_E_MSGSIZE             (NET_E_BASEERR+40)
#define NET_E_PROTOTYPE           (NET_E_BASEERR+41)
#define NET_E_NOPROTOOPT          (NET_E_BASEERR+42)
#define NET_E_PROTONOSUPPORT      (NET_E_BASEERR+43)
#define NET_E_SOCKTNOSUPPORT      (NET_E_BASEERR+44)
#define NET_E_OPNOTSUPP           (NET_E_BASEERR+45)
#define NET_E_PFNOSUPPORT         (NET_E_BASEERR+46)
#define NET_E_AFNOSUPPORT         (NET_E_BASEERR+47)
#define NET_E_ADDRINUSE           (NET_E_BASEERR+48)
#define NET_E_ADDRNOTAVAIL        (NET_E_BASEERR+49)
#define NET_E_NETDOWN             (NET_E_BASEERR+50)
#define NET_E_NETUNREACH          (NET_E_BASEERR+51)
#define NET_E_NETRESET            (NET_E_BASEERR+52)
#define NET_E_CONNABORTED         (NET_E_BASEERR+53)
#define NET_E_CONNRESET           (NET_E_BASEERR+54)
#define NET_E_NOBUFS              (NET_E_BASEERR+55)
#define NET_E_ISCONN              (NET_E_BASEERR+56)
#define NET_E_NOTCONN             (NET_E_BASEERR+57)
#define NET_E_SHUTDOWN            (NET_E_BASEERR+58)
#define NET_E_TOOMANYREFS         (NET_E_BASEERR+59)
#define NET_E_TIMEDOUT            (NET_E_BASEERR+60)
#define NET_E_CONNREFUSED         (NET_E_BASEERR+61)
#define NET_E_LOOP                (NET_E_BASEERR+62)
#define NET_E_NAMETOOLONG         (NET_E_BASEERR+63)
#define NET_E_HOSTDOWN            (NET_E_BASEERR+64)
#define NET_E_HOSTUNREACH         (NET_E_BASEERR+65)
#define NET_E_NOTEMPTY            (NET_E_BASEERR+66)
#define NET_E_PROCLIM             (NET_E_BASEERR+67)
#define NET_E_USERS               (NET_E_BASEERR+68)
#define NET_E_DQUOT               (NET_E_BASEERR+69)
#define NET_E_STALE               (NET_E_BASEERR+70)
#define NET_E_REMOTE              (NET_E_BASEERR+71)

#define NET_E_DISCON              (NET_E_BASEERR+101)

/*
* Extended Windows Sockets error constant definitions
*/
#define NET_E_SYSNOTREADY          (NET_E_BASEERR+91)
#define NET_E_VERNOTSUPPORTED      (NET_E_BASEERR+92)
#define NET_E_NOTINITIALISED       (NET_E_BASEERR+93)
#define NET_E_NOMEMORY             (NET_E_BASEERR+94)
/*
* Error return codes from gethostbyname() and gethostbyaddr()
* (when using the resolver). Note that these errors are
* retrieved via WSAGetLastError() and must therefore follow
* the rules for avoiding clashes with error numbers from
* specific implementations or language run-time systems.
* For this reason the codes are based at NET_E_BASEERR+1001.
* Note also that [WSA]NO_ADDRESS is defined only for
* compatibility purposes.
*/

#define h_errno         NET_GetLastError()

/* Authoritative Answer: Host not found */
#define NET_E_HOST_NOT_FOUND       (NET_E_BASEERR+1001)
#define HOST_NOT_FOUND          NET_E_HOST_NOT_FOUND

/* Non-Authoritative: Host not found, or SERVERFAIL */
#define NET_E_TRY_AGAIN            (NET_E_BASEERR+1002)
#define TRY_AGAIN               NET_E_TRY_AGAIN

/* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define NET_E_NO_RECOVERY          (NET_E_BASEERR+1003)
#define NO_RECOVERY             NET_E_NO_RECOVERY

/* Valid name, no data record of requested type */
#define NET_E_NO_DATA              (NET_E_BASEERR+1004)
#define NO_DATA                 NET_E_NO_DATA

/* no address, look for MX record */
#define NET_E_NO_ADDRESS           NET_E_NO_DATA
#define NO_ADDRESS              NET_E_NO_ADDRESS

/* Microsoft Windows Extended data types */
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr *PSOCKADDR;
typedef struct sockaddr  *LPSOCKADDR;

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in *PSOCKADDR_IN;
typedef struct sockaddr_in  *LPSOCKADDR_IN;

typedef struct linger LINGER;
typedef struct linger *PLINGER;
typedef struct linger  *LPLINGER;

typedef struct in_addr IN_ADDR;
typedef struct in_addr *PIN_ADDR;
typedef struct in_addr  *LPIN_ADDR;

#if 0
/* seems no one uses FD_SET etc, 
 * disable the following typedef to get ABI check passed
*/
typedef struct fd_set FD_SET;
typedef struct fd_set *PFD_SET;
typedef struct fd_set  *LPFD_SET;
#endif //#ifndef __X86LINUXGCC__ 

typedef struct hostent HOSTENT;
typedef struct hostent *PHOSTENT;
typedef struct hostent  *LPHOSTENT;

typedef struct servent SERVENT;
typedef struct servent *PSERVENT;
typedef struct servent  *LPSERVENT;

typedef struct protoent PROTOENT;
typedef struct protoent *PPROTOENT;
typedef struct protoent  *LPPROTOENT;

typedef struct timeval TIMEVAL;
typedef struct timeval *PTIMEVAL;
typedef struct timeval  *LPTIMEVAL;

extern int NET_errno;
extern int NET_Last_errno;


/* Socket function prototypes */
#ifdef __cplusplus
extern "C" {
#endif


	typedef enum {
		NET_SDK_VER_1 = 0,
		NET_SDK_VER_2 = 1,
	} NET_SDKVer_t ;

	extern u_long   NET_htonl (u_long hostlong);
	extern u_short   NET_htons (u_short hostshort);
	extern unsigned long   NET_inet_addr (const char  *cp);
	extern void  NET_inet_ntoa (struct in_addr in, s8 *pIPStr);
	extern u_long   NET_ntohl (u_long netlong);
	extern u_short   NET_ntohs (u_short netshort);

	/* Database function prototypes */
	extern struct hostent  *NET_gethostbyaddr(const char  *addr, int len, int type);
	extern int   NET_gethostname (char  *name, int namelen);
	extern struct servent  *NET_getservbyport(int port, const char  *proto);
	extern struct servent  *NET_getservbyname(const char  *name, const char  *proto);
	extern struct protoent  *NET_getprotobynumber(int proto);
	extern struct protoent  *NET_getprotobyname(const char  *name);
	//=============================
	//extension by Delta
	//=============================
#define NET_bzero(addr,len)   vm_memset((addr),0,(len))
#define NET_bcopy(s_addr,d_addr,len)   vm_memcpy((d_addr),(s_addr),(len))

	typedef u32 (*NET_ReqAppId2SockIdCB)(u32 uReqAppId);
	extern void NET_Initialize(void);
	extern void NET_CleanUp(void);
	extern int  NET_GetLastError(void);
	extern int NET_inet_aton(const char *cp, struct in_addr *addr);

	typedef void (*NET_recv_callback) (SOCKET s, u8 *buf, u_int len);
	extern int _NetRecvGeneric (SOCKET s, void* cbfunc, int flags, NET_SDKVer_t ver, void *pUserData);
	typedef void (*NET_recvfrom_callback) (SOCKET s, u8 *buf, u_int len, struct sockaddr *from, int fromlen);
	extern int _NetRecvfromGeneric (SOCKET s, void* cbfunc, int flags, NET_SDKVer_t ver, void *pUserData);
	typedef void (*NET_connect_callback) (SOCKET s, s8 result);
	extern int _NetConnectGeneric (SOCKET s, const struct sockaddr  *name, int namelen, void* cbfunc, NET_SDKVer_t ver, void *pUserData);
	extern int _NetConnectGenericEx (SOCKET s, const struct sockaddr  *name, int namelen, void* cbfunc, NET_SDKVer_t ver, void *pUserData, bool bBind);
	typedef void (*NET_gethostbyname_callback) (u8 ti, struct hostent *phost);
	extern int _NetGetHostByNameGeneric (u32 uVenId, const char  *name, void* cbfunc, NET_SDKVer_t ver, void *pUserData, NET_ReqAppId2SockIdCB pfnIdCb);
	typedef void (*NET_send_callback) (SOCKET s, s8 result);
	extern int _NetSendGeneric (SOCKET s, const char  *buf, int len, void* cbfunc, int flags, NET_SDKVer_t ver, void *pUserData);
	typedef void (*NET_sendto_callback) (SOCKET s, s8 result);
	extern int _NetSendtoGeneric (SOCKET s, const char  *buf, int len, void* cbfunc, int flags, const struct sockaddr *to, int tolen, NET_SDKVer_t ver, void *pUserData);
	typedef void (*NET_closesocket_callback) (SOCKET s, s8 result);
	extern int _NetCloseGeneric (SOCKET s, void* cbfunc, NET_SDKVer_t ver, void *pUserData);

	typedef void (*NET_ping_callback)(u8 ti, s8 result);
	extern int _NetPingGeneric(u8 ti, void* cbfunc,void *pUserData, NET_ReqAppId2SockIdCB pfnIdC);

	/// the callback type is the same with
	extern int _NetBindGeneric(SOCKET s, void* cbfunc, void *pUserData, bool bUDP);

#define NET_SETTING_MAX_LEN_GPRSAPN    31     /* max len(GPRS APN) in ASCII */
#define NET_SETTING_MAX_LEN_USERNAME   31     /* max len(username) in ASCII */
#define NET_SETTING_MAX_LEN_PASSWORD   31     /* max len(password) in ASCII */
#define NET_SETTING_IP_BYTESIZE        4      /* xxx.xxx.xxx.xxx */

#define NET_TCP_MSS 1460
#define NET_MAX_SOCKET 7
#define NET_MAX_DNS_QUERY NET_MAX_SOCKET
#define TCP_PACKET_LIMIT 64512 // (63<<10)
#define UDP_PACKET_LIMIT 1472

	enum {
		NET_SOCKET_IDX = 0,
		NET_CONNECT_IDX,
		NET_SEND_IDX,
		NET_SENDTO_IDX,
		NET_RECV_IDX,
		NET_RECVFROM_IDX,
		NET_CLOSE_IDX,
		NET_SETSOCKOPT_IDX,
		NET_GETSOCKOPT_IDX,
		NET_SHUTDOWN_IDX,
		NET_LAST_IDX,
	} ;

	enum
	{
		NET_SocketState_Idle = 0,
		NET_SocketState_Created,
		NET_SocketState_Connecting,
		NET_SocketState_Connected,
		NET_SocketState_Closing
	};
	typedef u8 NET_SocketState_enum;

	typedef struct
	{
		u8 socket ;
		u8 sdk_ver ;
		u16 data_idx ;
		u16 data_len ;
		// simple flow control
		void *pReceiveInd;
		void *pData[NET_LAST_IDX];
		void *pCBFunc[NET_LAST_IDX];
		NET_SocketState_enum eState;
	} NET_SocketUserDataCBFunc_t ;

	typedef struct
	{
		u8 GprsApn[NET_SETTING_MAX_LEN_GPRSAPN + 1];
		u8 Username[NET_SETTING_MAX_LEN_USERNAME + 1];
		u8 Password[NET_SETTING_MAX_LEN_PASSWORD + 1];
		u8 DnsIp[NET_SETTING_IP_BYTESIZE];
		u8 LocalIp[NET_SETTING_IP_BYTESIZE];
	} NET_data_link_data_t ;

	enum {
		NET_CREATE_DATA_LINK_IDX = 0,
		NET_CLOSE_DATA_LINK_IDX,
	} ;

	typedef enum {
		NET_SOCKET_RESULT_OK,                          /**< Operation OK */
		NET_SOCKET_RESULT_DEFAULT,                     /**< Cause not defined */
		NET_SOCKET_RESULT_NB_MAX_CTXT_REACHED,         /**< Nb max MSL context reached */
		NET_SOCKET_RESULT_DATA_LINK_ALREADY_ACTIVATED, /**< CSD/GPRS DATA com already active */
		NET_SOCKET_RESULT_COM_CLOSE_BY_PEER,           /**< Communication closed by peer */
		NET_SOCKET_RESULT_DATA_LINK_KO,                /**< Data link can't be activated */
		NET_SOCKET_RESULT_IP_ERROR,                    /**< IP setup or sock opening failure */
		NET_SOCKET_RESULT_NO_MORE_SOCKET,              /**< No more socket available */
		NET_SOCKET_RESULT_BAD_SOCKET_ID,               /**< Bad socket identifier */
		NET_SOCKET_RESULT_CONTCP_CLOSE,                /**< TCP connection to distant closed */
		NET_SOCKET_RESULT_DNS_ERROR,                   /**< DNS error */
		NET_SOCKET_RESULT_GPRS_NOT_PRESENT,            /**< GPRS feature not present */
		NET_SOCKET_RESULT_KO_WRONG_STATE,               /**< Wrong MSL state */
		NET_SOCKET_RESULT_KO_NO_MSL_CONTEXT_FOUND,     /**< Cannot find corresponding msl context */
		NET_SOCKET_RESULT_SET_SOCKET_OPTION_ERROR,    /**< Set socket option failure */
		NET_SOCKET_RESULT_GET_SOCKET_OPTION_ERROR,    /**< Get socket option failure */
		NET_SOCKET_RESULT_SHUTDOWN_SOCKET_ERROR,      /**< Shutdown socket failure */
		NET_SOCKET_RESULT_CONTCP_SYN_TIMEOUT,
		NET_SOCKET_RESULT_CONTCP_AGAIN,
		NET_SOCKET_RESULT_CONTCP_NO_BUFFER_ERROR
	} NET_SocketResult_e ;

	typedef struct
	{
		void *pData;
		void *pCBFunc;
	} NET_UserDataCBFunc_t ;

	typedef struct
	{
        void *pConn;
		void *pData;
		void *pCBFunc;
		u8 sdk_ver;
		u8 ti;
	}NET_GetHostByNameUserDataCBFunc_t ;

	typedef struct
	{
        void *pConn;
		void *pData;
		void *pCBFunc;
		u8 ti;
	}NET_PingCBFunc_t;

    typedef struct
    {
        void *pData;
        void *pCBFunc;
    }NET_StatisticFunc_t;

	typedef struct NET_StatIndiUserDataCBFunc_tag NET_StatIndiUserDataCBFunc_t;
	struct NET_StatIndiUserDataCBFunc_tag
	{
		u32 uSockId;
		void *pData;
		void *pCBFunc;
		NET_StatIndiUserDataCBFunc_t *pPrev;
		NET_StatIndiUserDataCBFunc_t *pNext;
	} ;

	typedef struct NET_DomainNameQuery_tag NET_DomainNameQuery_t;
	struct NET_DomainNameQuery_tag
	{
		NET_GetHostByNameUserDataCBFunc_t *pData;
		NET_DomainNameQuery_t *pPrev;
		NET_DomainNameQuery_t *pNext;
	} ;

	// for V2 create/close datalink
	///extern NET_UserDataCBFunc_t NET_UserDataCBFunc[2];
	// for V2 socket operations
	extern NET_SocketUserDataCBFunc_t NET_SocketUserDataCBFunc[NET_MAX_SOCKET];
	// for V2 status indication
	extern NET_StatIndiUserDataCBFunc_t *pNET_StatIndiDataCBFuncList;
	// for domain query to release memory if data link is broken
	extern NET_DomainNameQuery_t *pNET_DomainNameQueryList;


	typedef void (*NET_data_link_CBFunc_t) (s8 nRetCode, void* pUserData);
	extern bool NET_data_link_exist(void);
	extern void NET_create_data_link (u8 nModId, NET_data_link_data_t *pDataLinkData, void *pUserData, NET_data_link_CBFunc_t pCBFunc);
	extern void NET_close_data_link (void *pUserData, NET_data_link_CBFunc_t pCBFunc);

	extern void NET_create_data_link_ex(void *pUserData, NET_data_link_CBFunc_t pCBFunc, NET_ReqAppId2SockIdCB pfnIdCb);
    extern void NET_close_data_link_ex(void *pUserData, NET_data_link_CBFunc_t pCBFunc, NET_ReqAppId2SockIdCB pfnIdCb);
    extern void NET_close_all_data_links_ex(void *pUserData, NET_data_link_CBFunc_t pCBFunc, NET_ReqAppId2SockIdCB pfnIdCb);

	typedef void (*NET_ping_CBFunc_t)(u8 ti, s8 result, void* pUserData);
	void NET_ReportPingFailCb(void *pvPingData, void *pvUserData);
	extern void NET_MSLpingQueryRsp(s32 result, u32 userdata);

    typedef void (*NET_gethostbyname_CBFunc_t) (u8 ti, struct hostent *phost, void* pUserData);
	typedef void (*NET_connect_CBFunc_t) (SOCKET s, s8 result, void* pUserData);
	typedef void (*NET_send_CBFunc_t) (SOCKET s, s8 result, void* pUserData);
	typedef void (*NET_sendto_CBFunc_t) (SOCKET s, s8 result, void* pUserData);
	typedef void (*NET_recv_CBFunc_t) (SOCKET s, u8 *buf, u_int len, void* pUserData, void* pLinkMsg);
	typedef void (*NET_recvfrom_CBFunc_t) (SOCKET s, u8 *buf, u_int len, struct sockaddr *from, s32 fromlen, void* pUserData, void* pLinkMsg);
	typedef void (*NET_close_CBFunc_t) (SOCKET s, s8 result, void* pUserData);
	typedef void (*NET_setsockopt_CBFunc_t) (SOCKET s, s8 status, void* pUserData);
	typedef void (*NET_getsockopt_CBFunc_t) (SOCKET s, s32 level, s32 optname, s8* optval, s32 optlen, s8 status, void* pUserData);
	typedef void (*NET_shutdown_CBFunc_t) (SOCKET s, s8 status, void* pUserData);
	typedef void (*NET_StatIndi_CBFunc_t) (s8 nRetCode, void* pUserData);
    typedef void (*NET_bind_CBFunc_t)(SOCKET s, s8 result, void* pUserData);
    typedef void (*NET_StatisticQuery_CBFunc_t)(s8 result, u32 nBytes, void *pvReqMsg);
    typedef void (*NET_StatisticResetAll_CBFunc_t)(s8 result, void *pvReqMsg);

	extern void NET_CreateDataLinkRsp(void* pvDataLink, u8 result);
	extern void NET_DestroyDataLinkRsp(void* pvDataLink, u8 result);
	extern void NET_MSLrecv (SOCKET s, void *buf, u_int len, u_int src_addr, u_short src_port, void* msg) ;
	extern void NET_MSLsendReady (SOCKET s, u8 result) ;
	extern void NET_MSLcreateSocketRsp (SOCKET s, u8 result) ;
	extern u8 NET_GetEvent (s16 typmsg, u32 timeout) ;
	extern u32 NET_GetLocalIP (void) ;
	extern u32 NET_GetDNSIP (void) ;
	extern u8 NET_DNameToQName (u8 *dname, u8 *qname) ;
	extern u8 NET_QNameToDName (u8 *qname, u8 *dname) ;
	extern void NET_MSLdnsQueryRsp (u8 ti, u8 *addr, u8 len, u32 userdata);
	extern void NET_MSLcloseSocketRsp (SOCKET s, u8 result) ;
	extern void _NetReceiveReady (SOCKET s);
	extern s32 _NetSetSockOpt(SOCKET s, s32 level, s32 optname, s8* optval, s32 optlen, void *pCBFunc, void *pUserData);
	extern s32 _NetGetSockOpt(SOCKET s, s32 level, s32 optname, void *pCBFunc, void *pUserData);
	extern s32 _NetShutdown(SOCKET s, s32 how, void *pCBFunc, void *pUserData);
	u8 MMS_CreateDataLink (u8 simid, NET_data_link_data_t *mmsSetting);
	u8 MMS_CloseDataLink (void);
	extern u8 _NetStatIndi (void *pUserData, NET_StatIndi_CBFunc_t pCBFunc, u32 uSockId);
    extern u8 _NetStatIndi_De(void* pCBFunc, u32 uSockId);
    void NET_ReportDnsFailCb(void *pvDnsData, void *pvUserData);

    extern s8 NET_StatisticQueryReq(void *pvReqMsg, NET_StatisticQuery_CBFunc_t pCBFunc);
    extern void NET_StatisticQueryRsp(s8 nResult, u32 nBytes,void *pvWrapperData);
    extern s8 NET_StatisticResetAllReq(void *pvReqMsg, NET_StatisticResetAll_CBFunc_t pCBFunc);
    extern void NET_StatisticResetAllRsp(s8 nResult, void *pvWrapperData);

	extern bool NET_FindStatIndiUserCb(void* pCBFunc, u32 uSocketId, NET_StatIndiUserDataCBFunc_t **ppsUserCb);

#ifdef __cplusplus
}
#endif

#endif  /*#ifndef _WINSOCKAPI_*/
#endif  /* _WINSOCK_API_H_ */


