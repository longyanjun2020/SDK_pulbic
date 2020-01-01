/* $Id: ares.h,v 1.3 2000/09/21 19:15:48 ghudson Exp $ */

/* Copyright 1998 by the Massachusetts Institute of Technology.
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in
 * advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 */

#ifndef ARES__H
#define ARES__H

#include "rvccore.h"

/* If we're compiling without network support - disable DNS support */
#if RV_NET_TYPE == RV_NET_NONE
#undef RV_DNS_TYPE
#define RV_DNS_TYPE RV_DNS_NONE
#endif

#if (RV_DNS_TYPE == RV_DNS_ARES)

#include "rvselect.h"
#include "rvnet2host.h"
#include "rvtimestamp.h"
#include "rvarescached.h"
#include "rvehd.h"
#include "rvcondvar.h"
#include "rvrandomgenerator.h"


#if (RV_OS_TYPE == RV_OS_TYPE_SOLARIS)  || (RV_OS_TYPE == RV_OS_TYPE_LINUX) || \
    (RV_OS_TYPE == RV_OS_TYPE_UNIXWARE) || (RV_OS_TYPE == RV_OS_TYPE_TRU64) || \
    (RV_OS_TYPE == RV_OS_TYPE_HPUX)     || (RV_OS_TYPE == RV_OS_TYPE_INTEGRITY) || \
    (RV_OS_TYPE == RV_OS_TYPE_FREEBSD)	|| (RV_OS_TYPE == RV_OS_TYPE_MAC) ||\
    (RV_OS_TYPE == RV_OS_TYPE_NETBSD)

#include <netinet/in.h>
#include <arpa/nameser.h>


#elif (RV_OS_TYPE == RV_OS_TYPE_VXWORKS)

#include <resolvLib.h>

#define	HFIXEDSZ    12
#ifndef T_AAAA
#define T_AAAA		0x1c
#endif
#ifndef T_SRV
#define T_SRV		0x21
#endif
#ifndef T_NAPTR
#define T_NAPTR		0x23
#endif


#elif (RV_OS_TYPE == RV_OS_TYPE_SYMBIAN)

#if (RV_OS_VERSION  < RV_OS_SYMBIAN_9) || (RV_TLS_TYPE != RV_TLS_OPENSSL)
/* we needthis only if Symbian's standard libc is used,
   if OpenC is installed & used (must for OpenSSL) these lines are not needed */
typedef	unsigned short u_int16_t;
typedef	unsigned long u_int32_t;
#include <sys/types.h>
#endif

#include <netinet/in.h>
#include <arpa/nameser.h>

#define NS_MAXDNAME	    1025    /* maximum domain name */ 

#endif


#if (RV_OS_TYPE == RV_OS_TYPE_WIN32) || (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS) || \
    (RV_OS_TYPE == RV_OS_TYPE_MOPI)  || (RV_OS_TYPE == RV_OS_TYPE_PSOS)    || \
    (RV_OS_TYPE == RV_OS_TYPE_OSE)   || (RV_OS_TYPE == RV_OS_TYPE_WINCE)   || \
    (RV_OS_TYPE == RV_OS_TYPE_MAC)

#if (RV_OS_TYPE != RV_OS_TYPE_MAC)
/*
 * Currently defined opcodes.
 */
typedef enum __ns_opcode {
	ns_o_query = 0,		/* Standard query. */
	ns_o_iquery = 1,	/* Inverse query (deprecated/unsupported). */
	ns_o_status = 2,	/* Name server status query (unsupported). */
				/* Opcode 3 is undefined/reserved. */
	ns_o_notify = 4,	/* Zone change notification. */
	ns_o_update = 5,	/* Zone update message. */
	ns_o_max = 6
} ns_opcode;

/*
 * Currently defined response codes.
 */
typedef	enum __ns_rcode {
	ns_r_noerror = 0,	/* No error occurred. */
	ns_r_formerr = 1,	/* Format error. */
	ns_r_servfail = 2,	/* Server failure. */
	ns_r_nxdomain = 3,	/* Name error. */
	ns_r_notimpl = 4,	/* Unimplemented. */
	ns_r_refused = 5,	/* Operation refused. */
	/* these are for BIND_UPDATE */
	ns_r_yxdomain = 6,	/* Name exists */
	ns_r_yxrrset = 7,	/* RRset exists */
	ns_r_nxrrset = 8,	/* RRset does not exist */
	ns_r_notauth = 9,	/* Not authoritative for zone */
	ns_r_notzone = 10,	/* Zone of record different from zone section */
	ns_r_max = 11,
	/* The following are TSIG extended errors */
	ns_r_badsig = 16,
	ns_r_badkey = 17,
	ns_r_badtime = 18
} ns_rcode;
#endif

/*
 * Define constants based on RFC 883, RFC 1034, RFC 1035
 */
#define NS_PACKETSZ	    512	    /* maximum packet size */
#define NS_MAXDNAME	    1025    /* maximum domain name */
#define NS_MAXCDNAME	255	    /* maximum compressed domain name */
#define NS_MAXLABEL	    63	    /* maximum length of domain label */
#define NS_HFIXEDSZ	    12	    /* #/bytes of fixed data in header */
#define NS_QFIXEDSZ	    4	    /* #/bytes of fixed data in query */
#define NS_RRFIXEDSZ	10	    /* #/bytes of fixed data in r record */
#define NS_INT32SZ	    4	    /* #/bytes of data in a u_int32_t */
#define NS_INT16SZ	    2	    /* #/bytes of data in a u_int16_t */
#define NS_INT8SZ	    1	    /* #/bytes of data in a u_int8_t */
#define NS_INADDRSZ	    4	    /* IPv4 T_A */
#define NS_IN6ADDRSZ	16	    /* IPv6 T_AAAA */
#define NS_CMPRSFLGS	0xc0	/* Flag bits indicating name compression. */
#define NS_DEFAULTPORT	53	    /* For both TCP and UDP. */

#define PACKETSZ		NS_PACKETSZ
#define MAXDNAME		NS_MAXDNAME
#define MAXCDNAME		NS_MAXCDNAME
#define MAXLABEL		NS_MAXLABEL
#define	HFIXEDSZ		NS_HFIXEDSZ
#define QFIXEDSZ		NS_QFIXEDSZ
#define RRFIXEDSZ		NS_RRFIXEDSZ
#define	INT32SZ			NS_INT32SZ
#define	INT16SZ			NS_INT16SZ
#define	INADDRSZ		NS_INADDRSZ
#define	IN6ADDRSZ		NS_IN6ADDRSZ
#define	INDIR_MASK		NS_CMPRSFLGS
#define NAMESERVER_PORT	NS_DEFAULTPORT

#define QUERY			ns_o_query

#undef  NOERROR
#define NOERROR			ns_r_noerror
#define FORMERR			ns_r_formerr
#define SERVFAIL		ns_r_servfail
#define NXDOMAIN		ns_r_nxdomain
#define NOTIMP			ns_r_notimpl
#define REFUSED			ns_r_refused
#define YXDOMAIN		ns_r_yxdomain
#define YXRRSET			ns_r_yxrrset
#define NXRRSET			ns_r_nxrrset
#define NOTAUTH			ns_r_notauth
#define NOTZONE			ns_r_notzone

#if (RV_OS_TYPE != RV_OS_TYPE_MAC)
#define MAXHOSTNAMELEN	64
#endif

#endif  /* RV_OS_TYPE_WIN32, RV_OS_TYPE_NUCLEUS, RV_OS_TYPE_MOPI,
           RV_OS_TYPE_PSOS, RV_OS_TYPE_OSE, RV_OS_TYPE_WINCE */


#ifndef C_IN
#define C_IN			1
#endif

#ifndef T_A
#define T_A				1
#endif

#ifndef T_CNAME
#define T_CNAME         5
#endif

#ifndef T_AAAA
#define T_AAAA	        28
#endif

#ifndef T_SRV
#define T_SRV			33
#endif

#ifndef T_NAPTR
#define T_NAPTR			35
#endif

#ifndef T_SOA
#define T_SOA           6
#endif

#ifndef T_NS
#define T_NS            2
#endif

/* Support for negative caching. It will work only for RR types < 64 
 * 
 */
#define T_NXDOMAIN      127
#define T_NODATA(x)     (0x40 | (x))
#define T_NODATA_START  (0x40)


/* Default system values */
#define	DEFAULT_TIMEOUT		RvInt64Mul(RvInt64Const(1,0,5), RV_TIME64_NSECPERSEC)
#define DEFAULT_TRIES		4
#define DEFAULT_IOVEC_LEN   20

/* Maximum DNS name length (RFC1035 2.3.4) */
#define RV_DNS_MAX_NAME_LEN 255
#define RV_DNS_MAX_CHARSTRING_LENGTH 255
#define RV_NAPTR_FLAGS_LEN  RV_DNS_MAX_CHARSTRING_LENGTH
#define RV_NAPTR_SERV_LEN   RV_DNS_MAX_CHARSTRING_LENGTH
#define RV_NAPTR_REGEXP_LEN RV_DNS_MAX_CHARSTRING_LENGTH

#define ARES_SUCCESS		0

/* Server error codes (ARES_ENODATA indicates no relevant answer) */
#define ARES_ENODATA		1
#define ARES_EFORMERR		2
#define ARES_ESERVFAIL		3
#define ARES_ENOTFOUND		4
#define ARES_ENOTIMP		5
#define ARES_EREFUSED		6

/* Locally generated error codes */
#define ARES_EBADQUERY		7
#define ARES_EBADNAME		8
#define ARES_EBADFAMILY		9
#define ARES_EBADRESP		10
#define ARES_ECONNREFUSED	11
#define ARES_ETIMEOUT		12
#define ARES_EOF		    13
#define ARES_EFILE		    14
#define ARES_ENOMEM		    15
#define ARES_EDESTRUCTION	16
#define ARES_ESERVICE   	17
#define ARES_ENOSERVERS   	18
#define ARES_ENDOFSERVERS   19  /* all servers in the list were searched */

/* Converts error codes to meaningful string */
const char* ares_get_error_string(int error);

/* Flag values */
#define ARES_FLAG_USEVC		    (1 << 0)
#define ARES_FLAG_PRIMARY	    (1 << 1)
#define ARES_FLAG_IGNTC		    (1 << 2)
#define ARES_FLAG_NORECURSE	    (1 << 3)
#define ARES_FLAG_STAYOPEN	    (1 << 4)
#define ARES_FLAG_NOSEARCH	    (1 << 5)
#define ARES_FLAG_NOALIASES	    (1 << 6)
#define ARES_FLAG_NOCHECKRESP	(1 << 7)

/* Option mask values */
#define ARES_OPT_FLAGS		    (1 << 0)
#define ARES_OPT_TIMEOUT	    (1 << 1)
#define ARES_OPT_TRIES		    (1 << 2)
#define ARES_OPT_NDOTS		    (1 << 3)
#define ARES_OPT_UDP_PORT	    (1 << 4)
#define ARES_OPT_TCP_PORT	    (1 << 5)
#define ARES_OPT_SERVERS	    (1 << 6)
#define ARES_OPT_DOMAINS	    (1 << 7)
#define ARES_OPT_LOOKUPS	    (1 << 8)


typedef struct RvDnsEngineStruct RvDnsEngine;
typedef struct server_state rvServerState;
typedef struct query_struct rvQuery;

typedef enum {
    RV_DNS_UNDEFINED = -1,
    /* these are symmetric codes: application <---> resolver */
	RV_DNS_HOST_IPV4_TYPE = T_A,
	RV_DNS_CNAME_TYPE     = T_CNAME, 
	RV_DNS_HOST_IPV6_TYPE = T_AAAA,
	RV_DNS_SRV_TYPE       = T_SRV,
	RV_DNS_NAPTR_TYPE     = T_NAPTR,

    /* one-way codes: status reports from DNS resolver to application */
    RV_DNS_STATUS_TYPE,
    RV_DNS_ENDOFLIST_TYPE,
    RV_DNS_NO_DATA_TYPE
} RvDnsQueryType;

typedef RvInt RvDnsConfigType;

#define RV_DNS_SERVERS  (0x01)
#define RV_DNS_SUFFIXES (0x02)


/* the following 2 structures are delivered to the user callback
   for each SRV / NAPTR record */
typedef struct {
	RvChar              targetName[RV_DNS_MAX_NAME_LEN+1];
	RvUint16            port;
	RvUint16            priority;
	RvUint16            weight;
} RvDnsSrvData;

typedef struct {
	RvUint16            order;
	RvUint16            preference;
    RvChar              flags[RV_NAPTR_FLAGS_LEN];
    RvChar              service[RV_NAPTR_SERV_LEN];
    RvChar              regexp[RV_NAPTR_REGEXP_LEN];
    RvChar              replacement[RV_DNS_MAX_NAME_LEN+1];
} RvDnsNaptrData;

typedef struct {
	RvChar alias[RV_DNS_MAX_NAME_LEN + 1];
} RvDnsCNAMEData;

/* RvDnsData
 * 
 * Used for returning DNS replies to the user and for some internal purposes
 * 
 * Interpretation of 'dataType' field:
 *
 * RV_DNS_HOST_IPV4_TYPE or RV_DNS_HOST_IPV6_TYPE - appropriate record is in data.hostAddress field
 * RV_DNS_CNAME_TYPE - appropriate record is in data.dnsCnameData field
 * RV_DNS_SRV_TYPE - appropriate record is in data.dnsSrvData
 * RV_DNS_NAPTR_TYPE - appropriate record is in data.dnsNaptrData
 *
 * RV_DNS_STATUS_TYPE - designates some exceptional condition. In this case error code is placed in
 *                      data.status field. After this record no more records will be sent to user's callback
 * 
 * RV_DNS_ENDOFLIST_TYPE - designates the end of DNS reply. No other data is included in this record
 */
typedef struct {
    RvInt               recordNumber; /* Sequential number of this record in DNS reply */
    RvChar              ownerName[RV_DNS_MAX_NAME_LEN+1]; 
    RvUint32            ttl;
	RvDnsQueryType      dataType;    /* selector field for 'data' union. according to the value of this field
                                      * 'data' union will be interpreted
                                      */ 
    RvInt               queryType;   /* query type as it appears in DNS specification, e.g. T_A, T_AAA, etc */
	union {
		RvAddress       hostAddress;
		RvDnsSrvData    dnsSrvData;
		RvDnsNaptrData  dnsNaptrData;
		RvDnsCNAMEData  dnsCnameData;
        RvStatus        status;
	} data;
} RvDnsData;



/*****************************************************************************
 *                           callbacks
 *****************************************************************************/




 /********************************************************************************************
 * RvDnsNewRecordCB
 *
 * Inserts a new DNS record data to the appropriate list.
 *
 * INPUT:
 *  context    - the user private data provided by the caller of the DNS function,
 *               which calls this callback
 *  queryId    - serial number of the query that originated this reply
 *  dnsData    - structure of type RvDnsData with a new record data to add.
 *               the dataType member indicates the type of data (IPv4/6, SRV or NAPTR)
 *               in the structure
 * RETURNS:
 *  RV_OK on success, other values on failure
 */
typedef RvStatus (*RvDnsNewRecordCB) (
	IN  void*               context,
    IN  RvUint32            queryId,
	IN  RvDnsData*          dnsData);

typedef void (*rvAresCallback) (
	IN  RvDnsEngine*        dnsEngine,
    IN  RvDnsNewRecordCB    newRecordCB,
	IN  void*               context,
    IN  RvStatus            status,
    IN  RvUint32            queryId,
    IN  RvUint8*            queryResults,
    IN  RvInt               alen);


/* DNS engine */
struct RvDnsEngineStruct {
    /* guarding lock for channel structure */
    RvLock lock;
    RvBool destroyed;
    RvRandomGenerator rnd;
    /* Configuration data */
    int flags;
    RvInt64 timeout;
    int tries;
    int ndots;
    RvUint16 udp_port;
    RvUint16 tcp_port;
    
    /* Server addresses and communications state */
    int  serversGeneration; /* Running counter, that increased every time we reconfigure servers */
    int skipServerWords;    /* size of skip_server array in 'int' */
    int max_servers;
    rvServerState *servers;
    int nservers;
    int tcp_bufflen;

    /* Domain names array */
    int domainsGeneration;
    int max_domains;
    char **domains;
    int ndomains;
    int longest_domain_i;
    
    /* ID to use for next query */
    unsigned short next_id;
    
    /* Active queries */
    rvQuery *queries;
    rvQuery *lastQuery;

    RvInt64 nSearches;
    RvInt64 nCompares;
    RvInt32 nMaxCompares;
    RvInt32 nAvgCompares;
    
    /* delivery callback for new data elements */
	RvDnsNewRecordCB newRecordCB;

    /* select engine, timer queue and log manager */
    RvUint32 userQueryId;
    RvSelectEngine *selectEngine;
    RvTimerQueue *timerQueue;
	RvLogMgr *logMgr;
	RvLogSource *dnsSource;


    /* Support for RvCancelQuery suspending while callback is in progress */
    RvCondvar  inCallbackCond;
    /* inCallbackQid - qid of the query currently in callback. 
     * Has 2 special values:
     * 0 - no queries currently in callback
     * 1 - wildcard, match all
     * Pay attention that valid qid's are always even positive numbers, so
     *  no ambiguity here.
     */
    RvUint32   inCallbackQid; 

    /* Thread id of the thread currently in callback */
    RvThreadId inCallbackTid;

    RvInt   ehdOrder;      /* order of hosts search (first or last) - should be out of conditional compilation */
    RvAresCacheClt cache;
};


struct ares_options {
    int flags;
    RvInt64 timeout;
    int tries;
    int ndots;
    RvUint16 udp_port;
    RvUint16 tcp_port;
    RvAddress *servers;
    int nservers;
    char **domains;
    int ndomains;
#if 0
    char *lookups;
#endif
};

int ares_init(void);
void ares_end(void);
int ares_construct(RvDnsEngine *channel, int max_servers, int max_domains,
                   int tcp_bufflen, struct ares_options *options, int optmask);
void ares_destruct(RvDnsEngine *channel, RvBool waitForCallbacks);
int ares_configure(RvDnsEngine *channel, int config_type);
int ares_set_options(RvDnsEngine *channel, struct ares_options *options, int optmask);
void ares_get_options(RvDnsEngine *channel, RvInt64 *timeout, int *tries, RvAddress *servers,
                 int *nservers, char **domains, int *ndomains);

int ares_query(RvDnsEngine *channel, const char *name, int dnsclass, int type, void *query_buf,
               RvSize_t *qbuf_len, RvDnsNewRecordCB newRecordCB, rvAresCallback callback, void *usr_arg, unsigned int qid);

int ares_search(RvDnsEngine *channel, const char *name, int dnsclass,
                 int type, rvAresCallback callback, void *arg, unsigned int qid);

/* Cancels query given by qid */
int ares_cancel_query(RvDnsEngine *channel, unsigned int qid, RvBool waitForCallbacks);

int ares_name_length(const unsigned char *encoded, const unsigned char *abuf, RvSize_t alen);

int ares_enc_length(const unsigned char *inencoded, const unsigned char *abuf, size_t msgLen);


int ares_expand_name(const unsigned char *encoded, const unsigned char *abuf,
                     RvSize_t alen, char *s, int strLen);

int ares_expand_string(const unsigned char *encoded, char *s, int strLen);

void rvDnsTreatNxdomain(RvDnsEngine *dnsEngine, RvUint8 *abuf, RvSize_t alen);

#endif /* RV_DNS_ARES */

#endif /* ARES__H */
