#ifndef _SOCKMGR_COMMEDIA_H_
#define _SOCKMGR_COMMEDIA_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrRes.h"
#include "SockMgrComMediaItf.h"
#include "SockMgrBearerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef SockMgr_ComMedia_e (*GetComMediaIDCB)   (SockMgr_ComMediaHdl_t hComMedia) ;
typedef bool (*IsSupportBearerCB)(SockMgr_ComMediaHdl_t hComMedia, SockMgr_Bearer_e eBearer) ;
typedef s32 (*PostMessageCB)(SockMgr_ComMediaHdl_t hComMedia, void *pvMsg) ;
typedef bool (*SockMgr_ComMedia_IsUsedCB)(SockMgr_ComMediaHdl_t hComMedia) ;
typedef bool (*SockMgr_ComMedia_GetOwnerBearerCB)(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t *phOwnerBearer) ;
typedef bool (*SockMgr_ComMedia_SetOwnerBearerCB)(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t hOwnerBearer) ;
typedef bool (*SockMgr_ComMedia_BaseClearOwnerBearerCB)(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t hOwnerBearer) ;

typedef struct
{
	/// Derived From ResItf
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
	//////////////////////////////////////////////////////////////////////////
	GetComMediaIDCB cbGetComMediaID ;
	PostMessageCB cbPostMessage;
	IsSupportBearerCB cbIsSupportBearer ;
	SockMgr_ComMedia_GetOwnerBearerCB cbGetOwnerBearer ;
	SockMgr_ComMedia_SetOwnerBearerCB cbSetOwnerBearer ;
	SockMgr_ComMedia_BaseClearOwnerBearerCB cbClearOwnerBearer ;
}SockMgr_ComMeidaItf_t;

typedef struct
{
	//////////////////////////////////////////////////////////////////////////
	SockMgr_ComMeidaItf_t *fptrComMediaItf ;
	ObjArrayHdl_t hObjArray ;
	u16 *puFreeIndex ;
	u16 uResNum   ;
	u16 uResSize  ;
	SockMgr_Res_e eResType ;
	//////////////////////////////////////////////////////////////////////////
	SockMgr_ComMedia_e eComMediaID ;
	u32 uSrcMailBox;
	u32 uDestMailBox;
	u32 uWaitFlag[RES_MGR_APP_ID__NUM];
	u32 (*puChannels)[RES_MGR_APP_ID__NUM];
	u32 *puOwners;
	u8  uMaxChannelNum;
	u8  uUsedChannelNum;
}SockMgr_ComMedia_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_ComMedia_e SockMgr_ComMedia_BaseGetComMediaID(SockMgr_ComMediaHdl_t hComMedia) ;
s32 SockMgr_ComMedia_BasePostMessage(SockMgr_ComMediaHdl_t hComMedia, void *pvMsg) ;
bool SockMgr_ComMedia_BaseIsSupportBearer(SockMgr_ComMediaHdl_t hComMedia, SockMgr_Bearer_e eBearer) ;
bool SockMgr_ComMedia_BaseGetOwnerBearer(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t *phOwnerBearer) ;
bool SockMgr_ComMedia_BaseSetOwnerBearer(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t hOwnerBearer) ;
bool SockMgr_ComMedia_BaseClearOwnerBearer(SockMgr_ComMediaHdl_t hComMedia, SockMgr_BearerHdl_t hOwnerBearer) ;

#endif/* _SOCKMGR_COMMEDIA_H_ */
