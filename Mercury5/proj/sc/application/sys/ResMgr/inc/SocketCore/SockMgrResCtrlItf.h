#ifndef _SOCKMGR_RESCTRL_ITF_H_
#define _SOCKMGR_RESCTRL_ITF_H_

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrPlatformCommon.h"
#include "SockMgrResItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* SockMgr_ResCtrlHdl_t ;
typedef void (*SockMgr_ResCtrl_CopyResCB)    (void *pvSrc, void *pvDest, u16 uSize) ;
typedef void (*SockMgr_ResCtrl_ClearResCB)   (void *pDest, u16 uSize) ;
typedef SockMgr_ResHdl_t (*SockMgr_ResFactory_CreateCB)(SockMgr_ResCreateData_t *psResCreateData) ;
typedef void (*SockMgr_ResFactory_DestroyCB)(SockMgr_ResHdl_t hRes, void *pvDestroyData) ;
typedef void (*SockMgr_ResCtrl_TraverseResCB)(u16 uRemapId, void *pvCurData , void *pvCusData) ;

typedef struct
{
	u16  uResNum;
	u16  uResSize;
	u16  *puRemapTable;
	SockMgr_ResCtrl_CopyResCB    cbCopy      ;
	SockMgr_ResCtrl_ClearResCB   cbClear     ;
	SockMgr_ResFactory_CreateCB  cbCreateRes ;
	SockMgr_ResFactory_DestroyCB cbDestroyRes;
	SockMgr_ResCreateData_t **ppsResDescriptorTable ;
}SockMgr_ResCtrl_InitData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

SockMgr_ResCtrlHdl_t SockMgr_ResCtrl_Init(SockMgr_ResCtrl_InitData_t *psInitData) ;
void SockMgr_ResCtrl_UnInit(SockMgr_ResCtrlHdl_t hResCtrl, void *pvDestroyData) ;
void SockMgr_ResCtrl_TraverseAllRes(SockMgr_ResCtrlHdl_t hResCtrl, SockMgr_ResCtrl_TraverseResCB cbTraverseRes, void *pvCusData) ;
__SLDPM_FREE__ void SockMgr_ResCtrl_GetRes(SockMgr_ResCtrlHdl_t hResCtrl, u16 uRemapId, SockMgr_ResHdl_t *phRes) ;

#endif/* _SOCKMGR_RESCTRL_ITF_H_ */
