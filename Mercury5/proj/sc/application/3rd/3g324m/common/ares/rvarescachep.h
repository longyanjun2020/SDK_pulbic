#ifndef _rvarescachep_h
#define _rvarescachep_h

#include "rvtypes.h"
#include "rvobjpool.h"
#include "rvlog.h"

typedef RvUint32 RvAresTime;
#define PQILLEGALIDX (~(RvSize_t)(0))


/* casts some field 'f' in the object of type T to type T, given fields address faddr */
#define RvObjectFromField(T, f, faddr) ((T *)(void *)((RvChar *)(faddr) - RV_OFFSETOF(T, f)))

typedef struct _RvAresPage RvAresPage;
typedef struct _RvRdata    RvRdata;
typedef struct _RvDLink    RvDLink;

typedef RvDLink RvAresHashLink;

struct _RvDLink {
    RvDLink *next;
    RvDLink *prev;
};

/* RvRdata is actually variable-length. Last field may be up to 256 chars length */
struct _RvRdata {
    RvRdata        *nextPageEntry;
    RvAresPage     *page;           /* points to the owning page */
    RvAresTime      expirationTime;
    RvUint16        type;

    /* RvRdata fields (derived class) */
    RvAresHashLink  hashLink;  /* links records in the same bucket */
    RvUint16        size;      /* total size */
    RvBool          negative;  /* RV_TRUE - negative caching */
    RvUint8         nRecords;  /* number of records in this data set */
#if RV_DNS_CACHE_DEBUG
    RvBool          hmark;
    RvBool          pmark;
#endif

    RvUint8         nameSize;  /* owner name size */
    RvChar          name[1];   /* owner name, variable length - should be last field */
    /*
    No new fields after this point!
    */
};

#define RvRdataIsValid(self) ((self)->hashLink.next != 0)

struct _RvAresPage {
    RvObjPoolElement poolElem;
    RvAresPage      *next;        /* points to the next page in the cell */
    RvInt16          lockCnt;     /* if lockCnt == 0 - page is orphan and may be returned to allocator
                                   * if lockCnt == 1 and page is located on one of the cell lists or expired PQs,
                                   *   then page can be reused (no active queries referencing this page
                                   * if lockCnt > 1 - there are active queries referencing data on this page
                                   */
    RvInt16          nRecords;      /* Number of accessible records on this page */
    RvAresTime       maxExpirationTime; /* maximal expiration time of records on this page */
    RvRdata         *firstRecord; /* points to the first record on the page */
    RvSize_t         spaceLeft;   /* left space in bytes */
    RvSize_t         pageSize;    /* pageSize == 0 means page is allocated from the pool, else - using RvMemoryAlloc */
    RvUint8         *freeSpace;   /* pointer to the first free byte */
};

typedef struct {
    RvObjPool pagePool;
    RvLogSource *logSrc;
    RvSize_t  pageSize;
    RvSize_t  realPageSize;
    RvSize_t  bigPagesMax;
    RvSize_t  bigPagesCurrent;
} RvAresPageAllocator;

RvStatus RvAresPageAllocatorConstruct(RvAresPageAllocator *self,
                                      RvSize_t pageSize,
                                      RvSize_t minPages,
                                      RvSize_t maxPages,
                                      RvSize_t deltaPages,
                                      RvSize_t bigPagesMax,
                                      RvLogSource *logSrc);

void RvAresPageAllocatorDestruct(RvAresPageAllocator *self);

RvAresPage* RvAresPageAllocatorAlloc(RvAresPageAllocator *self, RvSize_t pageSize);

void RvAresPageAllocatorFree(RvAresPageAllocator *self, RvAresPage *page);

void RvAresPageAllocatorReset(RvAresPageAllocator *self);

typedef struct {
    RvAresHashLink  *buckets;
    RvSize_t         size;
    RvLogSource     *logSrc;
} RvAresHash;

typedef RvSize_t RvAresHashInsertPoint;

RvStatus RvAresHashConstruct(RvAresHash *self, RvLogSource *logSrc, RvSize_t hashSize);
void RvAresHashDestruct(RvAresHash *self);
void RvAresHashRemove(RvAresHash *self, RvRdata *data);
void RvAresHashAdd(RvAresHash *self, RvAresHashInsertPoint insertionPoint, RvRdata *data);
void RvAresHashRemovePage(RvAresHash *self, const RvAresPage *page);
void RvAresHashClear(RvAresHash *self);
RvRdata* RvAresHashFind(RvAresHash *self, 
                        RvAresTime curTime,
                        RvSize_t t, 
                        RvChar *name, 
                        RvSize_t nameSize, 
                        RvAresHashInsertPoint *insertPoint);


void *pageAlloc(RvSize_t size, void *data);
void pageFree(void *p, void *data);

/* Logging support */
#if RV_LOGMASK == RV_LOGLEVEL_NONE
#define LogMgrFromLogSrc(logSrc) (0)
#else
#define LogMgrFromLogSrc(logSrc) ((logSrc) ? (*logSrc)->logMgr : 0)
#endif

#define LOGSRCDFLT (self->logSrc)
#define LOGMGRDFLT  LogMgrFromLogSrc(LOGSRC)
#define LOGSRC LOGSRCDFLT
#define LOGMGR LOGMGRDFLT

#endif

