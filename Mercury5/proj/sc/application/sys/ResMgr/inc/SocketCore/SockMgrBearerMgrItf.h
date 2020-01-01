#ifndef _SOCKMGR_BEARERMGR_ITF_H_
#define _SOCKMGR_BEARERMGR_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrDSPortItf.h"
#include "SockMgrResItf.h"
#include "SockMgrResCtrlItf.h"
#include "SockMgrBearerItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* SockMgr_BearerMgrHdl_t ;
typedef SockMgr_ResCtrl_TraverseResCB SockMgr_BearerMgr_TraverseAllBearerCB ;
typedef struct
{
	SockMgr_ResCtrl_InitData_t sResCtrl_InitData ;
}SockMgr_BearerMgr_InitData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_BearerMgrHdl_t SockMgr_BearerMgr_Init(SockMgr_BearerMgr_InitData_t *psBearerMgrInitData) ;
void SockMgr_BearerMgr_UnInit(SockMgr_BearerMgrHdl_t hBearerMgr) ;
bool SockMgr_BearerMgr_IsConflict(SockMgr_BearerMgrHdl_t hBearerMgr, SockMgr_Bearer_e eBearer1, SockMgr_Bearer_e eBearer2) ;
SockMgr_BearerHdl_t SockMgr_BearerMgr_GetBearer(SockMgr_BearerMgrHdl_t hBearerMgr, SockMgr_Bearer_e eBearer) ;
void SockMgr_BearerMgr_TraverseAllBearer(SockMgr_BearerMgrHdl_t hBearerMgr, SockMgr_BearerMgr_TraverseAllBearerCB cbTraverseAllBearer, void *pvCusData) ;


#endif/* _SOCKMGR_BEARERMGR_ITF_H_ */
