#ifndef _SOCKMGR_RES_ITF_H_
#define _SOCKMGR_RES_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrResFactoryItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void (*TraverseOwnerCB)(void *pvCurOwner, void *pvCusData) ;
typedef void (*TraverseAllOwnerCB)(SockMgr_ResHdl_t hRes, TraverseOwnerCB cbTraverseOwner, void *pvCusData) ;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_Res_e SockMgr_Res_GetResType(SockMgr_ResHdl_t hRes) ;
bool SockMgr_Res_OccupyRes(SockMgr_ResHdl_t hRes, void *pvOwner) ;
bool SockMgr_Res_ReleaseRes(SockMgr_ResHdl_t hRes, void *pvOwner) ;
void SockMgr_Res_ReleaseAllRes(SockMgr_ResHdl_t hRes) ;
u16 SockMgr_Res_GetRemainResNum(SockMgr_ResHdl_t hRes) ;
u16  SockMgr_Res_GetOwnerNum(SockMgr_ResHdl_t hRes) ;
u16  SockMgr_Res_GetMaxOwnerNum(SockMgr_ResHdl_t hRes) ;
void SockMgr_Res_TraverseOwner(SockMgr_ResHdl_t hRes, TraverseOwnerCB cbTraverseOwner, void *pvCusData) ;
bool SockMgr_Res_IsSharable(SockMgr_ResHdl_t hRes, void *pvVerifyData) ;
bool SockMgr_Res_IsOccupiedBy(SockMgr_ResHdl_t hRes, void *pvOwner) ;

#endif/* _SOCKMGR_RES_ITF_H_ */
