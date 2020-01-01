/***********************************************************************
Filename   : rvusrconfig.h
Description: let the user to put his own choices
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
#ifndef RV_USRCONFIG_H
#define RV_USRCONFIG_H

/***********************************************************************

    3G-324M Specific definitions

***********************************************************************/

/* H.223 Split add-on module support */
#ifndef RV_H223_USE_SPLIT
#define RV_H223_USE_SPLIT RV_NO
#endif

/* Real-time statistics support */
#undef RV_H223_USE_STATISTICS
#define RV_H223_USE_STATISTICS RV_YES

/* Multiplexing levels support */
#undef RV_H223_USE_MUX_LEVEL_0
#define RV_H223_USE_MUX_LEVEL_0 RV_YES

#undef RV_H223_USE_MUX_LEVEL_1
#define RV_H223_USE_MUX_LEVEL_1 RV_YES

#undef RV_H223_USE_MUX_LEVEL_2
#define RV_H223_USE_MUX_LEVEL_2 RV_YES

#undef RV_H223_USE_MUX_LEVEL_3
#define RV_H223_USE_MUX_LEVEL_3 RV_YES


/* The maximum size of an audio frame size we can easily mux along with segmentable channels */
#undef RV_H223_MAX_AUDIO_FRAME_SIZE
#define RV_H223_MAX_AUDIO_FRAME_SIZE    (33)

/* The maximum number of different audio frame sizes we can have in the mux-table */
#undef RV_H223_MAX_AUDIO_SIZES
#define RV_H223_MAX_AUDIO_SIZES         (8)

/* The maximum size of an H.245 message that is supported. Should be 255-2048 */
#undef RV_H223_MAX_H245_MESSAGE_SIZE
#define RV_H223_MAX_H245_MESSAGE_SIZE   (2048)

/* Do we want H.223 memory management to be contiguous per call? */
#undef RV_H223_USE_MEMORY_LOCALITY
#define RV_H223_USE_MEMORY_LOCALITY RV_NO


/* Lean compilation, reducing features that might not be needed for most applications */
#undef RV_3G324M_LEAN
#define RV_3G324M_LEAN RV_NO

#if (RV_3G324M_LEAN == RV_YES)
#undef RV_H223_MAX_AUDIO_SIZES
#undef RV_H223_MAX_H245_MESSAGE_SIZE
#undef RV_H223_USE_MUX_LEVEL_3

#define RV_3G324M_USE_HIGH_AVAILABILITY RV_NO
#define RV_H245_USE_HIGH_AVAILABILITY   RV_NO
#define RV_H245_LEAN_H223               RV_YES
#define RV_ASN1_LEAN_3G324M             RV_YES
#define RV_H223_MAX_AUDIO_SIZES         (3)
#define RV_H223_MAX_H245_MESSAGE_SIZE   (256)
#define RV_H223_USE_MUX_LEVEL_3         RV_NO
#define RV_H223_USE_AL3_RETRANSMISSIONS RV_NO

#else
#define RV_3G324M_USE_HIGH_AVAILABILITY RV_YES
#define RV_H245_USE_HIGH_AVAILABILITY   RV_YES
#define RV_H245_LEAN_H223               RV_NO
#define RV_ASN1_LEAN_3G324M             RV_NO
#if (RV_OS_TYPE == RV_OS_TYPE_RTK) //temp configuration

#else

#endif

#define RV_H223_USE_AL3_RETRANSMISSIONS RV_NO
#endif

#if 1//(RV_OS_TYPE == RV_OS_TYPE_RTK) 
/* Support of MONA */
#undef  RV_3G324M_USE_MONA
#define RV_3G324M_USE_MONA              RV_NO


/* definitions for supporting H.225 or H.223 */
#define RV_H245_SUPPORT_H225_PARAMS RV_NO
#define RV_H245_SUPPORT_H223_PARAMS RV_YES

/* H.245 definitions for capability set and for capability descriptors arrays */
#define RV_H245_CAP_SET_SIZE 100
#define RV_H245_CAP_DESC_SIZE 100

/* GEF add-on module codecs support */

#undef RV_GEF_USE_AMR
#define RV_GEF_USE_AMR RV_YES

#undef RV_GEF_USE_G7221
#define RV_GEF_USE_G7221 RV_YES

#undef RV_GEF_USE_G7222
#define RV_GEF_USE_G7222 RV_YES

#undef RV_GEF_USE_G726
#define RV_GEF_USE_G726 RV_YES

#undef RV_GEF_USE_H239
#define RV_GEF_USE_H239 RV_YES

#undef RV_GEF_USE_H264
#define RV_GEF_USE_H264 RV_YES

#undef RV_GEF_USE_H324ANNEXI
#define RV_GEF_USE_H324ANNEXI RV_YES

#undef RV_GEF_USE_MPEG4
#define RV_GEF_USE_MPEG4 RV_YES

#undef RV_GEF_USE_H249
#define RV_GEF_USE_H249 RV_YES

#undef  RV_GEF_USE_MONA
#define RV_GEF_USE_MONA RV_YES

/* H.245 AutoCaps add-on module codecs support */
#undef RV_H245_AUTO_CAPS_CHECK_CAP
#define RV_H245_AUTO_CAPS_CHECK_CAP RV_YES

#undef RV_H245_AUTO_CAPS_AMR
#define RV_H245_AUTO_CAPS_AMR RV_YES

/* AMR WIDEBAND */
#undef RV_H245_AUTO_CAPS_G7222
#define RV_H245_AUTO_CAPS_G7222 RV_YES

#undef RV_H245_AUTO_CAPS_G723
#define RV_H245_AUTO_CAPS_G723 RV_YES

#undef RV_H245_AUTO_CAPS_G711
#define RV_H245_AUTO_CAPS_G711 RV_YES

#undef RV_H245_AUTO_CAPS_G722
#define RV_H245_AUTO_CAPS_G722 RV_YES

#undef RV_H245_AUTO_CAPS_G726
#define RV_H245_AUTO_CAPS_G726 RV_YES

#undef RV_H245_AUTO_CAPS_G729
#define RV_H245_AUTO_CAPS_G729 RV_YES

#undef RV_H245_AUTO_CAPS_H263
#define RV_H245_AUTO_CAPS_H263 RV_YES

#undef RV_H245_AUTO_CAPS_H264
#define RV_H245_AUTO_CAPS_H264 RV_YES

#undef RV_H245_AUTO_CAPS_MPEG4
#define RV_H245_AUTO_CAPS_MPEG4 RV_YES

#else

/* Support of MONA */
#undef  RV_3G324M_USE_MONA
#define RV_3G324M_USE_MONA              RV_NO


/* definitions for supporting H.225 or H.223 */
#define RV_H245_SUPPORT_H225_PARAMS RV_NO
#define RV_H245_SUPPORT_H223_PARAMS RV_YES

/* H.245 definitions for capability set and for capability descriptors arrays */
#define RV_H245_CAP_SET_SIZE 100
#define RV_H245_CAP_DESC_SIZE 100

/* GEF add-on module codecs support */

#undef RV_GEF_USE_AMR
#define RV_GEF_USE_AMR RV_YES

#undef RV_GEF_USE_G7221
#define RV_GEF_USE_G7221 RV_NO

#undef RV_GEF_USE_G7222
#define RV_GEF_USE_G7222 RV_NO

#undef RV_GEF_USE_G726
#define RV_GEF_USE_G726 RV_NO

#undef RV_GEF_USE_H239
#define RV_GEF_USE_H239 RV_NO

#undef RV_GEF_USE_H264
#define RV_GEF_USE_H264 RV_NO

#undef RV_GEF_USE_H324ANNEXI
#define RV_GEF_USE_H324ANNEXI RV_YES

#undef RV_GEF_USE_MPEG4
#define RV_GEF_USE_MPEG4 RV_NO

#undef RV_GEF_USE_H249
#define RV_GEF_USE_H249 RV_NO

#undef  RV_GEF_USE_MONA
#define RV_GEF_USE_MONA RV_NO

/* H.245 AutoCaps add-on module codecs support */
#undef RV_H245_AUTO_CAPS_CHECK_CAP
#define RV_H245_AUTO_CAPS_CHECK_CAP RV_YES

#undef RV_H245_AUTO_CAPS_AMR
#define RV_H245_AUTO_CAPS_AMR RV_YES

/* AMR WIDEBAND */
#undef RV_H245_AUTO_CAPS_G7222
#define RV_H245_AUTO_CAPS_G7222 RV_NO

#undef RV_H245_AUTO_CAPS_G723
#define RV_H245_AUTO_CAPS_G723 RV_NO

#undef RV_H245_AUTO_CAPS_G711
#define RV_H245_AUTO_CAPS_G711 RV_NO

#undef RV_H245_AUTO_CAPS_G722
#define RV_H245_AUTO_CAPS_G722 RV_NO

#undef RV_H245_AUTO_CAPS_G726
#define RV_H245_AUTO_CAPS_G726 RV_NO

#undef RV_H245_AUTO_CAPS_G729
#define RV_H245_AUTO_CAPS_G729 RV_NO

#undef RV_H245_AUTO_CAPS_H263
#define RV_H245_AUTO_CAPS_H263 RV_YES

#undef RV_H245_AUTO_CAPS_H264
#define RV_H245_AUTO_CAPS_H264 RV_NO

#undef RV_H245_AUTO_CAPS_MPEG4
#define RV_H245_AUTO_CAPS_MPEG4 RV_NO
#endif

/* ASN.1 related parameters */
#undef RV_ASN1_CODER_USE_Q931
#define RV_ASN1_CODER_USE_Q931 RV_NO

#undef RV_ASN1_CODER_USE_H450
#define RV_ASN1_CODER_USE_H450 RV_NO


/***********************************************************************

    General compilation and interfaces flags

***********************************************************************/
#ifndef RV_ANSI_FOURCE_OUR
#define RV_ANSI_FORCE_OUR RV_NO
#endif

#ifndef RV_TEST_ALL
#define RV_TEST_ALL RV_NO
#endif

/* Validation checking options */
#undef  RV_CHECK_MASK
#define RV_CHECK_MASK RV_CHECK_ALL

/* Logging options */
#undef  RV_LOGMASK
#define RV_LOGMASK RV_LOGLEVEL_ALL

/* Log listener */
#undef  RV_LOGLISTENER_TYPE

#if (RV_OS_TYPE == RV_OS_TYPE_PSOS)
#define RV_LOGLISTENER_TYPE  RV_LOGLISTENER_TERMINAL/*RV_LOGLISTENER_FILE_AND_TERMINAL RV_LOGLISTENER_UDP*/
#elif (RV_OS_TYPE == RV_OS_TYPE_RTK)
#define RV_LOGLISTENER_TYPE  RV_LOGLISTENER_FILE_AND_TERMINAL
#else
#define RV_LOGLISTENER_TYPE  RV_LOGLISTENER_FILE_AND_TERMINAL
#endif

/* Threadness mode: Single / Multi */
#undef  RV_THREADNESS_TYPE
#define RV_THREADNESS_TYPE RV_THREADNESS_MULTI

/* Networking support: None, IPv4, IPv6 */
#undef  RV_NET_TYPE
#define RV_NET_TYPE RV_NET_IPV4  /* + RV_NET_IPV6 */

/* Select method: Select, Poll, Devpoll, Win32 WSA */
#undef  RV_SELECT_TYPE
#define RV_SELECT_TYPE RV_SELECT_DEFAULT

/* DNS support: None, Ares */
#undef  RV_DNS_TYPE
#define RV_DNS_TYPE RV_DNS_NONE

/* IPsec support for IMS: RV_NO, RV_YES */
#undef  RV_IMS_IPSEC_ENABLED
#define RV_IMS_IPSEC_ENABLED RV_NO

/* TLS support: None, OpenSSL */
#undef  RV_TLS_TYPE
#define RV_TLS_TYPE RV_TLS_NONE

/* Set the priority of the blocked network commands for Nucleus (connect, close)
   RV_THREAD_SOCKET_PRIORITY_DEFAULT by default is 3 */
/* #undef RV_THREAD_SOCKET_PRIORITY_DEFAULT
#define RV_THREAD_SOCKET_PRIORITY_DEFAULT  (2) */

/* Select if socket priority should be implemented with kqueue*/
#undef  RV_SELECT_KQUEUE_GROUPS
#define RV_SELECT_KQUEUE_GROUPS RV_NO
/* Set the range of Nucleus default portRange (otherwise, default range is 5000-65535) */
/*#undef RV_PORTRANGE_DEFAULT_START
#define RV_PORTRANGE_DEFAULT_START 10000
#undef RV_PORTRANGE_DEFAULT_FINISH
#define RV_PORTRANGE_DEFAULT_FINISH 65534*/

/* Select engine preemption is usually used in multithreading scenarios
 *  to interrupt RvSelectWaitAndBlock call. As a side effect user defined
 *  callback is called. In single-threaded scenarios the main effect (interrupt
 *  of RvSelectWaitAndBlock) is meaningless, so this mechanism is disabled by default.
 *  On the other hand, some application may find usefull the above mentioned 
 *  side effect. To enable preemption in single-threaded scenarios also - set
 *  uncomment the following lines
 */
#undef RV_SINGLE_THREADED_PREEMPTION
#define RV_SINGLE_THREADED_PREEMPTION RV_YES



/* 'Hosts' file resolution settings */

/* If defined as 1 - enables 'hosts' file based name resolution */
#undef  RV_DNS_USES_HOSTS
#define RV_DNS_USES_HOSTS RV_NO

/* Defines 'hosts' file search order 
 * If set as 
 *  RV_EHD_SEARCH_HOSTS_PLATFORM - platform specific algorithm will be used
 *  RV_EHD_SEARCH_HOSTS_FIRST    - hosts file will be searched before DNS servers
 *  RV_EHD_SEARCH_HOSTS_LAST     - hosts file will be searched after DNS servers
 */
#undef  RV_EHD_SEARCH_ORDER 
#define RV_EHD_SEARCH_ORDER RV_EHD_SEARCH_HOSTS_PLATFORM

#define RV_QUEUE_TYPE RV_QUEUE_STANDARD

#define RV_THREAD_TLS_TYPE 0/* RV_THREAD_TLS_MANUAL */

#define RV_LOCK_WIN32_DEBUG

/* Square root support mode: None, Fast, */
#define RV_SQRT_TYPE RV_SQRT_ALGR

#define RV_THREAD_USE_AUTOMATIC_INTERNING 0

#undef	RV_MEMORY_DEBUGINFO
#define RV_MEMORY_DEBUGINFO RV_YES

/* Support for resource counting */
#define RV_USE_RESOURCE_COUNTING RV_YES

/*============== DNS caching related constants ==============*/

/* Set RV_DNS_USES_CACHING to enable caching */
#define RV_DNS_USES_CACHING RV_NO

/* Size of page used to hold cache data. Should be >= 512 */
#define RV_DNS_CACHE_PAGE_SIZE 2048

/* Number of preallocated pages */
#define RV_DNS_CACHE_PAGES_NUMBER 512

/* Lower limit on the number of buckets in hash table 
 * Actual number will be calculated by cache module itself as some prime
 * greater or equal RV_DNS_CACHE_HASH_SIZE 
 */
#define RV_DNS_CACHE_HASH_SIZE 1024

/* Maximal number of active queries to cache module */
#define RV_DNS_CACHE_MAX_ACTIVE_QUERIES 512

/* Compiles in support for sanity checks in DNS caching */
#define RV_DNS_CACHE_SANITY RV_NO

/* For debugging purposes only! Uses faked notion of time */
/*#define RV_DNS_CACHE_DEBUG 1*/


#endif /* RV_USRCONFIG_H */
