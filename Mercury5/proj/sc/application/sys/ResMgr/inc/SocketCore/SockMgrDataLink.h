#if !defined(_SOCKMGR_DATALINK_H_)
#    define  _SOCKMGR_DATALINK_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrRes.h"
#include "SockMgrDataLinkItf.h"
#include "SockMgrDSPortItf.h"
#include "SockMgrDataLinkFsmItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef SockMgr_BearerHdl_t (*SockMgr_DataLink_GetBearerCB)(SockMgr_DataLinkHdl_t hDataLink) ;
typedef void (*SockMgr_DataLink_SetBearerCB)(SockMgr_DataLinkHdl_t hDataLink, SockMgr_BearerHdl_t hBearer) ;
typedef bool(*SockMgr_DataLink_OccupySocketCB)(SockMgr_DataLinkHdl_t hDataLink, SockMgr_SocketHdl_t hSocket) ;
typedef bool(*SockMgr_DataLink_ReleaseSocketCB)(SockMgr_DataLinkHdl_t hDataLink, SockMgr_SocketHdl_t hSocket) ;
typedef void(*SockMgr_DataLink_ReleaseAllSocketCB)(SockMgr_DataLinkHdl_t hDataLink) ;
typedef u16 (*SockMgr_DataLink_GetMaxSocketNumCB)(SockMgr_DataLinkHdl_t hDataLink) ;
typedef u16 (*SockMgr_DataLink_GetRemainSocketNumCB)(SockMgr_DataLinkHdl_t hDataLink) ;
typedef u16 (*SockMgr_DataLink_GetUsedSocketNumCB)(SockMgr_DataLinkHdl_t hDataLink) ;
typedef bool(*SockMgr_DataLink_IsExpiredCB)(SockMgr_DataLinkHdl_t hDataLink) ;


typedef struct _SockMgr_DataLinkItf_t_
{
	/// Derived from ResItf
	GetResTypeCB cbGetResType;
	OccupyResCB cbOccupyRes ;
	ReleaseResCB cbReleaseRes;
	ReleaseAllResCB cbReleaseAllRes ;
	GetRemainResNumCB cbGetRemainResNum ;
	GetOwnerNumCB cbGetOwnerNum ;
	GetMaxOwnerNumCB cbGetMaxOwnerNum ;
	TraverseAllOwnerCB cbTraverseAllOwner  ;
	IsSharableCB cbIsSharable        ;
	IsUsedCB cbIsUsed ;
	IsOccupiedByCB cbIsOccupiedBy ;
	///
	SockMgr_DataLink_GetBearerCB cbGetBearer ;
	SockMgr_DataLink_SetBearerCB cbSetBearer ;
	SockMgr_DataLink_OccupySocketCB cbOccupySocket ;
	SockMgr_DataLink_ReleaseSocketCB cbReleaseSocket ;
	SockMgr_DataLink_ReleaseAllSocketCB cbReleaseAllSocket ;
	SockMgr_DataLink_GetMaxSocketNumCB cbGetMaxSocketNum ;
	SockMgr_DataLink_GetRemainSocketNumCB cbGetRemainSocketNum ;
	SockMgr_DataLink_GetUsedSocketNumCB cbGetUsedSocketNum ;
	SockMgr_DataLink_IsExpiredCB cbIsDataLinkExpired ;
}SockMgr_DataLinkItf_t;

typedef struct
{
	// Derived from ResItf
	SockMgr_DataLinkItf_t *fptrDataLinkItf ;
	ObjArrayHdl_t hObjArray ;
	u16 *puFreeIndex ;
	u16 uResNum   ;
	u16 uResSize  ;
	SockMgr_Res_e eResType ;   
	//////////////////////////////////////////////////////////////////////////
	//	SockMgr_DataLink_e eDataLinkType ;
	SockMgr_Bearer_e eParentBearer;
	SockMgr_BearerHdl_t hParentBearer ;
	SockMgr_ResCheckInfo_t sResShareInfo ;
	SockMgr_SharableDataLinkRspData_t sShareRspData;
	SockMgr_FSMHdl_t hDataLinkFsm;
	u16 uMaxSocketPerDataLink ;
	u16 uSocketRemainNum ;
}SockMgr_DataLink_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_BearerHdl_t SockMgr_DataLink_BaseGetBearer(SockMgr_DataLinkHdl_t hDataLink) ;
void SockMgr_DataLink_BaseSetBearer(SockMgr_DataLinkHdl_t hDataLink, SockMgr_BearerHdl_t hBearer) ;
bool SockMgr_DataLink_BaseOccupySocket (SockMgr_DataLinkHdl_t hDataLink, SockMgr_SocketHdl_t hSocket) ;
bool SockMgr_DataLink_BaseReleaseSocket(SockMgr_DataLinkHdl_t hDataLink, SockMgr_SocketHdl_t hSocket) ;
void SockMgr_DataLink_BaseReleaseAllSocket(SockMgr_DataLinkHdl_t hDataLink) ;
u16 SockMgr_DataLink_BaseGetMaxSocketNum(SockMgr_DataLinkHdl_t hDataLink) ;
u16 SockMgr_DataLink_BaseGetRemainSocketNum(SockMgr_DataLinkHdl_t hDataLink) ;
u16 SockMgr_DataLink_BaseGetUsedSocketNum(SockMgr_DataLinkHdl_t hDataLink) ;
bool SockMgr_DataLink_BaseIsDataLinkExpired(SockMgr_DataLinkHdl_t hDataLink) ;
bool SockMgr_DataLink_OverrideIsSharable(SockMgr_ResHdl_t hRes, void *pvVerifyData) ;

#endif/* _SOCKMGR_DATALINK_H_ */
