/**
* @file GenResCtrl.h
*
* This header file defines the interface of resouce controller
*
*/

#ifndef __GENRESCTRL_H__
#define __GENRESCTRL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResCtrlItf.h"
#include "ObjArrayItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct GenResCtrl_t_
{
    ResCtrl_t tResCtrl;
    ResCtrlType_e eResCtrlType;
    ResCtrl_GetResID GetResId;
    ObjArrayHdl_t pObjArrayHdl;
} GenResCtrl_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
bool GenResCtrl_CheckConflict(ResCtrlHandle_t pResCtrlHdl, u32 uCtrlId, ResCtrlHandle_t pConflictResHdl);
void GenResCtrl_OccupyRes(ResCtrlHandle_t pResCtrlHdl, u32 uCtrlId, void *pOwner);
void* GenResCtrl_ReleaseRes(ResCtrlHandle_t pResCtrlHdl, u32 uCtrlId);
void GenResCtrl_ReleaseResByOwner(ResCtrlHandle_t pResCtrlHdl, void *pOwner);
void* GenResCtrl_GetResOwner(ResCtrlHandle_t pResCtrlHdl, u32 uCtrlId);
__SLDPM_FREE__ u16 GenResCtrl_GetUsedResNum(ResCtrlHandle_t pResCtrlHdl);
__SLDPM_FREE__ u16 GenResCtrl_Transverse(ResCtrlHandle_t pResCtrlHdl, ResCtrl_DoAction DoAction, void *pCusData);
ResCtrlHandle_t GenResCtrl_Init(u16 uResNum, ResCtrl_GetResID GetResId, const ResCtrlItf_t *pInterface);
__SLDPM_FREE__ void GenResCtrl_Uninit(ResCtrlHandle_t pResCtrlHdl);

#endif //__GENRESCTRL_H__
