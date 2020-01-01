#ifndef _SOCKMGR_BEARER_ITF_H_
#define _SOCKMGR_BEARER_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrBearerMgrItf.h"
#include "SockMgrResItf.h"
#include "SockMgrDataLinkItf.h"
#include "SockMgrBearerFsmItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void (*SockMgr_Bearer_TraverseDataLinkCB)(void *pvCurOwner, void *pvCusData);

typedef struct
{
	SockMgr_Res_e  eResType  ;
	u16 uOwnerNum;
	SockMgr_Bearer_e eBearer;
	u16 uMaxSocketPerDataLink;
}SockMgr_BearerCreateData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_BearerHdl_t SockMgr_BearerFactory_CreateBearer(SockMgr_BearerCreateData_t *psCreateBearerData) ;
void SockMgr_BearerFactory_DestroyBearer(SockMgr_BearerHdl_t hBearer);
SockMgr_Bearer_e SockMgr_Bearer_GetBearerID(SockMgr_BearerHdl_t hBearer) ;
u16 SockMgr_Bearer_GetRemainDataLink(SockMgr_BearerHdl_t hBearer) ;
u16 SockMgr_Bearer_GetMaxDataLink(SockMgr_BearerHdl_t hBearer) ;
u16 SockMgr_Bearer_GetUsedDataLink(SockMgr_BearerHdl_t hBearer) ;
u16 SockMgr_Bearer_GetMaxSocketPerDataLink(SockMgr_BearerHdl_t hBearer) ;
void SockMgr_Bearer_TraverseUsedDataLink(SockMgr_BearerHdl_t hBearer, SockMgr_Bearer_TraverseDataLinkCB cbTraverseDataLink, void *pvCusData) ;               
bool SockMgr_Bearer_HasSharableDataLink(SockMgr_BearerHdl_t hBearer, SockMgr_ResCheckInfo_t *psResInfo, SockMgr_DataLinkHdl_t *phDataLink) ;
SockMgr_DataLinkHdl_t SockMgr_Bearer_CreateDataLink(SockMgr_BearerHdl_t hBearer, SockMgr_ResCheckInfo_t *psResInfo, SockMgr_ComMediaHdl_t hComMedia) ;
bool SockMgr_Bearer_DestroyDataLink(SockMgr_BearerHdl_t hBearer, SockMgr_DataLinkHdl_t hDataLink, ResMgr_AppId_e eAp) ;
void SockMgr_Bearer_DataLinkCloseAbnormally(SockMgr_BearerHdl_t hBearer, SockMgr_DataLinkHdl_t hDataLink) ;
bool SockMgr_Bearer_IsUsed(SockMgr_BearerHdl_t hBearer) ;
SockMgr_FSMHdl_t SockMgr_Bearer_GeBearertFSM(SockMgr_BearerHdl_t hBearer);
bool SockMgr_Bearer_BindComMedia(SockMgr_BearerHdl_t hBearer, SockMgr_ComMediaHdl_t hBindComMedia);
bool SockMgr_Bearer_UnBindComMedia(SockMgr_BearerHdl_t hBearer, SockMgr_ComMediaHdl_t hUnBindComMedia);
bool SockMgr_Bearer_GetBindComMedia(SockMgr_BearerHdl_t hBearer, SockMgr_ComMediaHdl_t *phBindComMedia);

#endif /* _SOCKMGR_BEARER_ITF_H_ */
