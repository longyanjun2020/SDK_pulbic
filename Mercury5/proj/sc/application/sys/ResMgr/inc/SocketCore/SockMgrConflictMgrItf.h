#ifndef _SOCKMGR_CONFLICTMGR_ITF_H_
#define _SOCKMGR_CONFLICTMGR_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrBearerMgrItf.h"
#include "SockMgrComMediaMgrItf.h"
#include "SockMgrDSPortItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* SockMgr_ConflictMgrHdlt_t ;

typedef enum
{
	SOCKMGR_AP_PRIORITY__HIGH_E = 0X00,
	SOCKMGR_AP_PRIORITY__SAME_E = 0X01,
	SOCKMGR_AP_PRIORITY__LOW_E  = 0X02,
}SockMgr_ApPriority_e;

typedef enum
{
	SOCKMGR_CONFLICT_RESOLVE__OK = 0,
	SOCKMGR_CONFLICT_RESOLVE__OK_BUSY,
	SOCKMGR_CONFLICT_RESOLVE__FAIL,
}SockMgr_ResolveConflict_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_ConflictMgrHdlt_t SockMgr_ConflictMgr_Init
(
  void
);

void SockMgr_ConflictMgr_UnInit
( 
  SockMgr_ConflictMgrHdlt_t hConflictMgr
);

bool SockMgr_ConflictMgr_HasBearerConflict
( 
  SockMgr_ConflictMgrHdlt_t hConflictMgr, 
  SockMgr_BearerMgrHdl_t hBearerMgr, 
  SockMgr_ResCheckInfo_t *psResInfo, 
  SockMgr_CtnrHdl_t *phCtnrConflictBearerCandidates
 );

bool SockMgr_ConflictMgr_HasComMediaConflict
( 
  SockMgr_ConflictMgrHdlt_t hConflictMgr, 
  SockMgr_ComMediaMgrHdl_t hComMediaMgr, 
  SockMgr_ResCheckInfo_t *psResInfo, 
  SockMgr_CtnrHdl_t *phCtnrConflictComMediaCandidates, 
  SockMgr_CtnrHdl_t *phCtnrComMediaCandidates
);

bool SockMgr_ConflictMgr_HasDataLinkConflict
(
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 SockMgr_BearerMgrHdl_t hBearerMgr, 
 SockMgr_ResCheckInfo_t *psResInfo,
 SockMgr_CtnrHdl_t *phCtnrDataLinkConflictCandidates
);

bool SockMgr_ConflictMgr_HasSocketConflict
(
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 SockMgr_BearerMgrHdl_t hBearerMgr, 
 SockMgr_DataLinkHdl_t hDataLink, 
 SockMgr_CtnrHdl_t *phSocketConflictCandidates,
 ResMgr_AppId_e eReqAp
);

bool SockMgr_ConflictMgr_HasConnectionConflict
( 
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 SockMgr_BearerMgrHdl_t hBearerMgr, 
 SockMgr_ComMediaMgrHdl_t hComMediaMgr, 
 SockMgr_ResCheckInfo_t *psResInfo,
 SockMgr_CtnrHdl_t *phCtnrConflictBearerCandidates,
 SockMgr_CtnrHdl_t *phCtnrConflictComMediaCandidates, 
 SockMgr_CtnrHdl_t *phCtnrComMediaCandidates,
 SockMgr_CtnrHdl_t *phCtnrDataLinkConflictCandidates
);

SockMgr_ResolveConflict_e SockMgr_ConflictMgr_CanResolveBearerConflict
(
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 SockMgr_BearerMgrHdl_t hBearerMgr, 
 SockMgr_ResCheckInfo_t *psResInfo, 
 SockMgr_CtnrHdl_t *phCtnrConflictBearerCandidates
);

SockMgr_ResolveConflict_e SockMgr_ConflictMgr_CanResolveComMediaConflict
(
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 SockMgr_ComMediaMgrHdl_t hComMediaMgr, 
 SockMgr_ResCheckInfo_t *psResInfo, 
 SockMgr_CtnrHdl_t *phCtnrConflictComMediaCandidates, 
 SockMgr_CtnrHdl_t *phCtnrComMediaCandidates
);

SockMgr_ResolveConflict_e SockMgr_ConflictMgr_CanResolveDataLinkConflict
(
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 SockMgr_BearerMgrHdl_t hBearerMgr, 
 SockMgr_ResCheckInfo_t *psResInfo,
 SockMgr_CtnrHdl_t *phConflictDataLinkCandidates
 );

SockMgr_ResolveConflict_e SockMgr_ConflictMgr_CanResolveConnectionConflict
(
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 SockMgr_BearerMgrHdl_t hBearerMgr, 
 SockMgr_ComMediaMgrHdl_t hComMediaMgr, 
 SockMgr_ResCheckInfo_t *psResInfo, 
 SockMgr_CtnrHdl_t *phBearerConflictCandidates, 
 SockMgr_CtnrHdl_t *phComMediaConflictCandidates,
 SockMgr_CtnrHdl_t *phCtnrComMediaCandidates,
 SockMgr_CtnrHdl_t *phDataLinkConflictCandidates
 );

SockMgr_ResolveConflict_e SockMgr_ConflictMgr_CanResolveSocketConflict
(
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 SockMgr_BearerMgrHdl_t hBearerMgr, 
 SockMgr_DataLinkHdl_t hDataLink, 
 ResMgr_AppId_e eNewAp, 
 SockMgr_CtnrHdl_t *phSocketConflictCandidates
 );

SockMgr_ApPriority_e SockMgr_ConflictMgr_CompareApPriority
(
 SockMgr_ConflictMgrHdlt_t hConflictMgr, 
 ResMgr_AppId_e eAp1, 
 ResMgr_AppId_e eAp2
);

ResMgr_AppId_e SockMgr_ConflictMgr_FindMaxPriorityApIdInBearer
(
  SockMgr_ConflictMgrHdlt_t hConflictMgr, 
  SockMgr_BearerHdl_t hBearer
);

ResMgr_AppId_e SockMgr_ConflictMgr_FindMaxPriorityIdInDataLink
(
  SockMgr_ConflictMgrHdlt_t hConflictMgr, 
  SockMgr_DataLinkHdl_t hDataLink
);

void SockMgr_ConflictMgr_FindDataLinksInBearerByPriority
(
  SockMgr_ConflictMgrHdlt_t hConflictMgr, 
  SockMgr_BearerHdl_t hBearer,
  ResMgr_AppId_e eAp,
  SockMgr_ApPriority_e eCompare,
  SockMgr_CtnrHdl_t *phCtnrCandidates
);


#endif/* _SOCKMGR_CONFLICTMGR_ITF_H_ */
