/***********************************************************************
Filename   : rvarescache.h
Description: Internal module that provides caching support for
             DNS resolution.

This module includes defines internal API for caching support,
  so most of the functions (except some functions for debugging support)
  aren't exported
************************************************************************
        Copyright (c) 2006 RADVISION Inc. and RADVISION Ltd.
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

#ifndef _RV_ARES_CACHE_H
#define _RV_ARES_CACHE_H

#include "rvtypes.h"
#include "rvselect.h"
#include "rvarescached.h"

/* If we're compiling with no DNS - disable caching too */
#if RV_DNS_TYPE == RV_DNS_NONE
#undef RV_DNS_USES_CACHING
#define RV_DNS_USES_CACHING RV_NO
#endif

/* If we're compiling with no support for caching, debugging 
 *   caching or sanity check doesn't make a sence, so disable it
 */
#if RV_DNS_USES_CACHING == RV_NO

#undef RV_DNS_CACHE_DEBUG
#define RV_DNS_CACHE_DEBUG RV_NO

#undef RV_DNS_CACHE_SANITY
#define RV_DNS_CACHE_SANITY RV_NO

#endif


#ifdef __cplusplus
extern "C" {
#endif
/* Setting default page size
 */
#define RV_DNS_CACHE_MIN_PAGE_SIZE 512

#ifndef RV_DNS_CACHE_PAGE_SIZE
#define RV_DNS_CACHE_PAGE_SIZE 0
#endif

#ifndef RV_DNS_CACHE_MINPAGES
#define RV_DNS_CACHE_MINPAGES 0
#endif

#ifndef RV_DNS_CACHE_MAXPAGES
#define RV_DNS_CACHE_MAXPAGES 0
#endif

#ifndef RV_DNS_CACHE_DELTAPAGES
#define RV_DNS_CACHE_DELTAPAGES 0
#endif

#ifndef RV_DNS_CACHE_HASH_SIZE
#define RV_DNS_CACHE_HASH_SIZE 0
#endif

#ifndef RV_DNS_CACHE_PAGES_NUMBER
#  define RV_DNS_CACHE_PAGES_NUMBER 64
#endif

#if RV_DNS_CACHE_PAGE_SIZE == 0
#  undef RV_DNS_CACHE_PAGE_SIZE
#  define RV_DNS_CACHE_PAGE_SIZE 2048
#endif

#if RV_DNS_CACHE_PAGE_SIZE < RV_DNS_CACHE_MIN_PAGE_SIZE
#  undef RV_DNS_CACHE_PAGE_SIZE
#  define RV_DNS_CACHE_PAGE_SIZE RV_DNS_CACHE_MIN_PAGE_SIZE
#endif

#if RV_DNS_CACHE_MAXPAGES == 0
#  undef RV_DNS_CACHE_MAXPAGES
#  define RV_DNS_CACHE_MAXPAGES RV_DNS_CACHE_PAGES_NUMBER
#endif

#if RV_DNS_CACHE_MINPAGES == 0
#  undef RV_DNS_CACHE_MINPAGES
#  define RV_DNS_CACHE_MINPAGES RV_DNS_CACHE_MAXPAGES
#endif


#if RV_DNS_CACHE_DELTAPAGES == 0
#  undef RV_DNS_CACHE_DELTAPAGES
#  define RV_DNS_CACHE_DELTAPAGES RV_DNS_CACHE_MINPAGES
#endif


#if RV_DNS_CACHE_HASH_SIZE == 0
#  undef RV_DNS_CACHE_HASH_SIZE
#  define RV_DNS_CACHE_HASH_SIZE 1024
#endif

#if RV_DNS_CACHE_MAXBIGPAGES_SIZE == 0
#  undef RV_DNS_CACHE_MAXBIGPAGES_SIZE
#  define RV_DNS_CACHE_MAXBIGPAGES_SIZE 4096
#endif

#define RV_DNS_FIND_CACHE 1
#define RV_DNS_FIND_EHD   2


    
typedef struct _RvAresCacheCtx {
    struct _RvRdata    *rdata;
    RvLogSource *logSrc;
    RvUint32     minTTL;
    RvUint16     type;
    RvUint8     *start;
    RvUint8     *cur;
    RvUint8     *end;
    union {
        double   d1;
        void    *d2; 
        RvUint8  buf[RV_DNS_CACHE_PAGE_SIZE];
    } u;
} RvAresCacheCtx;
    
/* For debugging purposes you can set RV_DNS_CACHE_FAKETIME to 1 and 
 * control time from outside
 */
#ifndef RV_DNS_CACHE_FAKETIME
#define RV_DNS_CACHE_FAKETIME 0
#endif

#if RV_DNS_CACHE_FAKETIME

/* This functions and macros should be enabled only in debug mode */

/* Sets caching time to 't' seconds */
RVCOREAPI
void RvAresCacheDSetTime(RvUint32 t);

RVCOREAPI
RvUint32 RvAresCacheDGetTime();

RVCOREAPI
void RvAresCacheDAdvanceTime(RvUint32 time);



#else 

#define RvAresCacheDSetTime(t)
#define RvAresCacheDGetTime() (0)
#define RvAresCacheDAdvanceTime(time)

#endif

#if RV_DNS_CACHE_DEBUG

RVCOREAPI
void RvAresCacheDumpGlobal(RvChar *filename);

#else

#define RvAresCacheDumpGlobal(filename)  (void)filename

#endif

#if RV_DNS_USES_CACHING

RvStatus RvAresCacheCltConstruct(RvAresCacheClt *self, RvSelectEngine *seli, const RvAresCacheParams *params, RvLogMgr *logMgr);
RvStatus RvAresCacheCltDestruct(RvAresCacheClt *self);

#define RvAresCacheLetter(env) ((env)->cached)

RVCOREAPI
void RvAresCacheParamsInit(RvAresCacheParams *params);

RVCOREAPI
void RvAresCacheSetDefaultParams(RvAresCacheParams *params);


RvStatus RvAresCacheDInit(void);

RvStatus RvAresCacheDEnd(void);

RvStatus RvAresCacheDRecord(RvAresCacheD *self, RvAresCacheCtx *ctx, RvDnsData *record);

RvStatus RvAresCacheDFind(RvAresCacheD *self,
                          RvUint32 queryType,
                          const RvChar *name,
                          RvSize_t nameSize,
                          RvChar  **domainSuffixes,
                          RvSize_t  nDomains,
                          RvUint32 *domainSuffixesMask,
                          RvDnsNewRecordCB cb,
                          void *cbCtx,
                          RvUint32 *pQid);

RvStatus RvAresCacheDCancelQuery(RvAresCacheD *self, RvUint32 qid, RvBool waitForCallbacks);


RvStatus RvAresCacheDStartCaching(RvAresCacheD *self, RvAresCacheCtx *ctx); 


RvStatus RvAresCacheDFinishCaching(RvAresCacheD *self, RvAresCacheCtx *ctx); 

void RvAresCacheDClear(RvAresCacheD *self);


#if RV_DNS_CACHE_SANITY

RVCOREAPI
RvBool RvAresCacheDPerformSanityChecks(RvAresCacheD *self);

#else

#define RvAresCacheDPerformSanityChecks(self) (RV_TRUE)

#endif

#else /* !RV_DNS_USES_CACHING */

#define RvAresCacheParamsInit(p)

#define RvAresCacheDInit() (RV_OK)
#define RvAresCacheDEnd()  (RV_OK)

#define RvAresCacheDRecord(cached, ctx, record) ((void)(cached), (void)ctx, (void)(record), (RV_OK))

#define RvAresCacheDFind(cached, qtype, name, nameSize, domainSuffixes, nDomains, domainMask, cb, cbCtx, qid) \
    ((void)(cached), (void)qtype, (void)(name), (void)(nameSize), (void)(domainSuffixes), (void)nDomains, (void)domainMask, \
    (void)(cb), (void)(cbCtx), (void)(qid), (RV_DNS_ERROR_CACHE_NOTFOUND))

#define RvAresCacheDCancelQuery(cached, qid, wait) ((void)(cached), (void)(qid), (void)(wait), (RV_DNS_ERROR_CACHE_NOTFOUND))

#define RvAresCacheDStartCaching(cached, ctx)  ((void)(cached), (void)(ctx), (RV_OK))
#define RvAresCacheDFinishCaching(cached, ctx) ((void)(cached), (void)(ctx), (RV_OK))

#define RvAresCacheDPerformSanityChecks(self) (RV_TRUE)

#define RvAresCacheDClear(self) ((void)(self))

#define RvAresCacheCltConstruct(self, seli, params, logMgr)  ((void)(self), (void)(seli), (void)(params), (void)(logMgr), (RV_OK))
#define RvAresCacheCltDestruct(self) ((void)(self), (RV_OK))


#endif

/* Clt delegators */

#define RvAresCacheCltFind(env, qtype, name, nameSize, domainSuffixes, nDomains, domainMask,  cb, cbCtx, qid) \
    RvAresCacheDFind((env)->cached, qtype, name, nameSize, domainSuffixes, nDomains, domainMask, cb, cbCtx, qid)
#define RvAresCacheCltRecord(env, ctx, record) RvAresCacheDRecord((env)->cached, ctx, record)
#define RvAresCacheCltCancelQuery(env, qid, waitForCallbacks) RvAresCacheDCancelQuery((env)->cached, qid, waitForCallbacks)

#define RvAresCacheCltStartCaching(env, ctx) RvAresCacheDStartCaching((env)->cached, ctx)
#define RvAresCacheCltFinishCaching(env, ctx) RvAresCacheDFinishCaching((env)->cached, ctx)
#define RvAresCacheCltClear(env) RvAresCacheDClear((env)->cached)


#ifdef __cplusplus
}
#endif

#endif

