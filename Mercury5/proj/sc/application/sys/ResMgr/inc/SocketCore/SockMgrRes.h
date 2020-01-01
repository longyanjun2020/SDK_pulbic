#ifndef _SOCKMGR_RES_H_
#define _SOCKMGR_RES_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrResItf.h"
#include "ObjArrayItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef SockMgr_Res_e (*GetResTypeCB)(SockMgr_ResHdl_t hRes) ;
typedef bool(*OccupyResCB)(SockMgr_ResHdl_t hRes, void *pvOwner) ;
typedef bool(*ReleaseResCB)(SockMgr_ResHdl_t hRes, void *pvOwner) ;
typedef u16 (*GetRemainResNumCB)(SockMgr_ResHdl_t hRes) ;
typedef u16 (*GetOwnerNumCB)(SockMgr_ResHdl_t hRes) ;
typedef u16 (*GetMaxOwnerNumCB)(SockMgr_ResHdl_t hRes) ;
typedef bool (*IsSharableCB)(SockMgr_ResHdl_t hRes, void *pvVerifyData) ;
typedef bool (*IsUsedCB)(SockMgr_ResHdl_t hRes) ;
typedef bool (*IsOccupiedByCB)(SockMgr_ResHdl_t hRes, void *pvOwner) ;
typedef void (*ReleaseAllResCB)(SockMgr_ResHdl_t hRes) ;

typedef struct
{
	GetResTypeCB cbGetResType;
	OccupyResCB cbOccupyRes ;
	ReleaseResCB cbReleaseRes;
	ReleaseAllResCB cbReleaseAllRes ;
	GetRemainResNumCB cbRemainResNum ;
	GetOwnerNumCB cbGetOwnerNum ;
	GetMaxOwnerNumCB cbGetMaxOwnerNum ;
	TraverseAllOwnerCB cbTraverseAllOwner  ;
	IsSharableCB cbIsSharable        ;
	IsUsedCB cbIsUsed ;
	IsOccupiedByCB cbIsOccupiedBy ;
}SockMgr_ResItf_t;

typedef struct _SockMgr_Res_t_
{
	SockMgr_ResItf_t *fptrResItf ;
	ObjArrayHdl_t    hObjArray ;
	u16              *puFreeIndex ;
	u16              uResNum   ;
	u16              uResSize  ;
	SockMgr_Res_e    eResType ;
}SockMgr_Res_t;

typedef struct
{
	SockMgr_Res_e  eResType  ;
	u16            uResSize;
	u16            uResNum ;
	OwnerCopyCB    cbOwnerCopy    ;
	OwnerClearCB   cbOwnerClear   ;
	OwnerCmpCB     cbIsOwnerEqual ;
}SockMgr_ResInitData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_ResHdl_t SockMgr_Res_Init(SockMgr_ResHdl_t hRes, SockMgr_ResInitData_t *psResInitData) ;
void SockMgr_Res_UnInit(SockMgr_ResHdl_t hRes) ;
SockMgr_Res_e SockMgr_Res_DefaultGetResType(SockMgr_ResHdl_t hRes) ;
bool SockMgr_Res_DefaultOccupyRes(SockMgr_ResHdl_t hRes, void *pvOwner) ;
bool SockMgr_Res_DefaultReleaseRes(SockMgr_ResHdl_t hRes, void *pvOwner) ;
void SockMgr_Res_DefaultReleaseAllRes(SockMgr_ResHdl_t hRes) ;
u16 SockMgr_Res_DefaultGetRemainResNum(SockMgr_ResHdl_t hRes) ;
u16 SockMgr_Res_DefaultGetOwnerNum(SockMgr_ResHdl_t hRes) ;
u16 SockMgr_Res_DefaultGetMaxOwnerNum(SockMgr_ResHdl_t hRes) ;
void SockMgr_Res_DefaultTraverseOwner(SockMgr_ResHdl_t hRes, TraverseOwnerCB cbTraverseOwner, void *pvCusData) ;
__SLDPM_FREE__ bool SockMgr_Res_DefaultIsUsed(SockMgr_ResHdl_t hRes) ;
bool SockMgr_Res_DefaultIsSharable(SockMgr_ResHdl_t hRes, void *pvVerifyData) ;
bool SockMgr_Res_DefaultIsOccupiedBy(SockMgr_ResHdl_t hRes, void *pvOwner) ;

#endif/* _SOCKMGR_RES_H_ */
