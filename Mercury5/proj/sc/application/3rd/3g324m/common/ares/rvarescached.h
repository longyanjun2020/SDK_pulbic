#ifndef _RV_ARES_CACHED_H
#define _RV_ARES_CACHED_H

#include "rvtypes.h"
#include "rvlog.h"

typedef struct {
	RvSize_t pageSize;
    RvSize_t minPages;
    RvSize_t maxPages;
    RvSize_t maxBigPagesSize;
    RvSize_t deltaPages;
	RvSize_t hashSize;
} RvAresCacheParams;


typedef struct _RvAresCacheD RvAresCacheD;

typedef struct _RvAresCacheClt RvAresCacheClt;

struct _RvAresCacheClt {
    RvAresCacheClt      *next;
    RvAresCacheD        *cached;
    RvLogMgr            *logMgr;
    RvLogSource          ilogSrc;
    RvLogSource         *logSrc;
};



#endif
