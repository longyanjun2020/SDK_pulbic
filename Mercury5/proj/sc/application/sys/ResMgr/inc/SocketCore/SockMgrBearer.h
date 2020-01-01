#ifndef _SOCKMGR_BEARER_H_
#define _SOCKMGR_BEARER_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrRes.h"
#include "SockMgrDataLinkItf.h"
#include "SockMgrBearerItf.h"
#include "SockMgrDSPortItf.h"
#include "SockMgrBearerFsmItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef bool (*SockMgr_IsUsedCB)(SockMgr_BearerHdl_t hBearer);
typedef u16 (*SockMgr_GetMaxDataLinkCB)(SockMgr_BearerHdl_t hBearer);
typedef u16 (*SockMgr_GetUsedDataLinkCB)(SockMgr_BearerHdl_t hBearer);
typedef u16 (*SockMgr_GetRemainDataLinkCB)(SockMgr_BearerHdl_t hBearer);
typedef u16 (*SockMgr_GetMaxSocketPerDataLinkCB)(SockMgr_BearerHdl_t hBearer);
typedef SockMgr_Bearer_e (*SockMgr_GetBearerIDCB)(SockMgr_BearerHdl_t hBearer) ;
typedef SockMgr_DataLinkHdl_t (*SockMgr_CreateDataLinkCB)(SockMgr_BearerHdl_t hBearer, SockMgr_ResCheckInfo_t *psResInfo, SockMgr_ComMediaHdl_t hComMedia);
typedef bool (*SockMgr_DestroyDataLinkCB)(SockMgr_BearerHdl_t hBearer, SockMgr_DataLinkHdl_t hDataLink, ResMgr_AppId_e eAp);
typedef bool (*SockMgr_HasSharableDataLinkCB)(SockMgr_BearerHdl_t hBearer,SockMgr_ResCheckInfo_t *psResInfo, SockMgr_DataLinkHdl_t *phDataLink);
typedef void (*SockMgr_TraverseAllDataLinkCB)(SockMgr_BearerHdl_t hBearer, SockMgr_Bearer_TraverseDataLinkCB cbTraverseDataLink, void *pvCusData);

typedef struct 
{
	/// Derived From ResItf
	GetResTypeCB     cbGetResType;
	OccupyResCB      cbOccupyRes;
	ReleaseResCB     cbReleaseRes;
	ReleaseAllResCB cbReleaseAllRes;
	GetRemainResNumCB cbGetRemainResNum;
	GetOwnerNumCB    cbGetOwnerNum;
	GetMaxOwnerNumCB cbGetMaxOwnerNum;
	TraverseAllOwnerCB  cbTraverseAllOwner;
	IsSharableCB     cbIsSharable;
	IsOccupiedByCB cbIsOccupiedBy;
	/// End Derived Fro ResItf
	SockMgr_GetBearerIDCB           cbGetBearerID;
	SockMgr_GetMaxDataLinkCB        cbGetMaxDataLinkNum;
	SockMgr_GetUsedDataLinkCB       cbGetUsedDataLinkNum;
	SockMgr_GetRemainDataLinkCB cbGetRemainDataLin;
	SockMgr_GetMaxSocketPerDataLinkCB cbGetMaxSocketNumPerDataLink;
	SockMgr_CreateDataLinkCB        cbCreateDataLink;
	SockMgr_DestroyDataLinkCB       cbDestroyDataLink;
	SockMgr_HasSharableDataLinkCB   cbHasSharableDataLink;
	SockMgr_TraverseAllDataLinkCB cbTraverseAllDataLink;
	SockMgr_IsUsedCB cbIsUsed ;
}SockMgr_BearerItf_t;

typedef struct
{
	/// Derived From ResItf
	SockMgr_BearerItf_t *pfpBearerItf ;
	ObjArrayHdl_t hObjArray ;
	u16 *puFreeIndex ;
	u16 uResNum   ;
	u16 uResSize  ;
	SockMgr_Res_e eResType ;
	/// End Derived Fro ResItf
	SockMgr_Bearer_e eBearerID;
	SockMgr_ComMediaHdl_t hBindComMedia;
	u16 uMaxSocketPerDataLink;
	SockMgr_FSMHdl_t hBearerFsm;
}SockMgr_Bearer_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_Bearer_e SockMgr_Bearer_BaseGetBearerID(SockMgr_BearerHdl_t hBearer);
u16 SockMgr_Bearer_BaseGetMaxDataLink(SockMgr_BearerHdl_t hBearer);
u16 SockMgr_Bearer_BaseGetUsedDataLink(SockMgr_BearerHdl_t hBearer);
u16 SockMgr_Bearer_BaseGetRemainDataLink(SockMgr_BearerHdl_t hBearer);
u16 SockMgr_Bearer_BaseGetMaxSocketPerDataLink(SockMgr_BearerHdl_t hBearer);
void SockMgr_Bearer_BaseTraverseUsedDataLink(SockMgr_BearerHdl_t hBearer, SockMgr_Bearer_TraverseDataLinkCB cbTraverseDataLink, void *pvCusData);
SockMgr_DataLinkHdl_t SockMgr_Bearer_BaseCreateDataLink(SockMgr_BearerHdl_t hBearer, SockMgr_ResCheckInfo_t *psResInfo, SockMgr_ComMediaHdl_t hComMedia);
bool SockMgr_Bearer_BaseDestroyDataLink(SockMgr_BearerHdl_t hBearer, SockMgr_DataLinkHdl_t hDataLink, ResMgr_AppId_e eAp);
bool SockMgr_Bearer_BaseHasSharableDataLink(SockMgr_BearerHdl_t hBearer, SockMgr_ResCheckInfo_t *psResInfo, SockMgr_DataLinkHdl_t *phDataLink);
bool SockMgr_Bearer_BaseIsUsed(SockMgr_BearerHdl_t hBearer);

#endif/* _SOCKMGR_BEARER_H_ */
