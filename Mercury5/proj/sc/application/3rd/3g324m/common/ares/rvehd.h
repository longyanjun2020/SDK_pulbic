#ifndef _RV_EHD_H
#define _RV_EHD_H

#include "rvlog.h"
#include "rvselect.h"

#ifdef __cplusplus
extern "C" {
#endif

#if RV_NET_TYPE != RV_NET_NONE

#define RV_EHD_SEARCH_HOSTS_PLATFORM -1
#define RV_EHD_SEARCH_HOSTS_FIRST 0
#define RV_EHD_SEARCH_HOSTS_LAST  1

typedef struct _RvEHD RvEHD;

typedef struct _RvAddressList {
    struct _RvAddressList *next;
    RvAddress addr;
} RvAddressList;


/* From RFC-1035 */
typedef enum {
    RV_A     = 1,
    RV_CNAME = 5
} RvEHRecordType;


typedef struct _RvEHBaseRecord RvEHBaseRecord;

/* Abstract base class for records that are kept in EHDMap DB 
* Instances of this class are never created, but only instances
* of subclasses 
*/
struct _RvEHBaseRecord {
    RvEHBaseRecord *next;   /* points to the next record in the hash chain */
    RvChar         *name;   /* serves as key in the map */
    RvEHRecordType  type;   /* type, currently RV_A (for A and AAAA records) or RV_CNAME (alias) */
};

typedef struct _REHCnameRecord RvEHCnameRecord;

/* A record */
typedef struct {
    RvEHBaseRecord   base;     
    RvInt            nIpv4;
    RvInt            nIpv6;
    RvAddressList    firstAddr;
    RvEHCnameRecord *firstAlias;
} RvEHARecord;

/* CName record */
struct _REHCnameRecord {
    RvEHBaseRecord   base;
    RvEHCnameRecord *nextAlias;
    RvEHARecord     *arec;
};

RvStatus RvEHDNew(RvEHD **self, RvLogMgr *logMgr);

RvStatus RvEHDDelete(RvEHD *self);

RvStatus RvEHDFind(RvEHD *self, RvChar *name, RvUint16 qtype, RvEHARecord **pArec);

void RvEHDRelease(RvEHD *self);
void RvEHDLock(RvEHD *self);


/* RvEHDGetSearchOrder() 
 *
 * Returns hosts file search order:
 * RV_EHD_SEARCH_HOSTS_FIRST - search hosts file before DNS servers
 * RV_EHD_SEARCH_HOSTS_LAST  - search hosts file after  DNS servers
 */
RvInt RvEHDGetSearchOrder(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

