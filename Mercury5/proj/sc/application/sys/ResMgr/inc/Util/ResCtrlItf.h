/**
* @file ResCtrlItf.h
*
* This header file defines the interface of resouce controller
*
*/

#ifndef __RESCTRLITF_H__
#define __RESCTRLITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"
#include "ObjArrayItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define RES_CTRL_ACT__KEEP                              OBJ_ARRAY_ACT__KEEP
#define RES_CTRL_ACT__CLEAR                             OBJ_ARRAY_ACT__CLEAR
#define RES_CTRL_ACT__STOP                              OBJ_ARRAY_ACT__STOP
#define RES_CTRL_ACT__CUS_STOP                          0x0100
#define RES_CTRL_ACT__STOP_AND_CLEAR                    (OBJ_ARRAY_ACT__CLEAR | RES_CTRL_ACT__STOP | RES_CTRL_ACT__CUS_STOP)

#define RES_CTRL_IS_FLAG_SET(_RET_, _FALG_)             (_FALG_ == (_FALG_ & _RET_))
#define RES_CTRL_IS_FLAG_NOT_SET(_RET_, _FALG_)         (_FALG_ != (_FALG_ & _RET_))

#define RES_CTRL_NO_RES_REQUIRED                        0xFFFF

#define RES_CTRL_ID(_APP_ID_,_RES_INFO_)                (((_APP_ID_ & 0x00000000FF) << 16) | (_RES_INFO_ & 0x0000FFFF))
#define RES_CTRL_GET_APP_ID(_RES_ID_)                   ((_RES_ID_ & 0x00FF0000) >> 16)
#define RES_CTRL_GET_RES_INFO(_RES_ID_)                 (_RES_ID_ & 0x0000FFFF)

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* ResCtrlHandle_t;
typedef u16 (*ResCtrl_GetResID)(u32 uCtrlId);
typedef u16 (*ResCtrl_DoAction)(u16 uIndex, void *pOwner, void *pCusData);
typedef bool (*ResCtrl_CheckConflictCB)(ResCtrlHandle_t pResCtrlHdl, u32 uCtrlId, ResCtrlHandle_t pConflictResHdl);
typedef void (*ResCtrl_OccupyResCB)(ResCtrlHandle_t pResCtrlHdl, u32 uCtrlId, void *pOwner);
typedef void* (*ResCtrl_ReleaseResCB)(ResCtrlHandle_t pResCtrlHdl, u32 uCtrlId);
typedef void (*ResCtrl_ReleaseResByOwnerCB)(ResCtrlHandle_t pResCtrlHdl, void *pOwner);
typedef void* (*ResCtrl_GetResOwnerCB)(ResCtrlHandle_t pResCtrlHdl, u32 uCtrlId);
typedef u16 (*ResCtrl_GetUsedResNumCB)(ResCtrlHandle_t pResCtrlHdl);
typedef u16 (*ResCtrl_TransverseCB)(ResCtrlHandle_t pResCtrlHdl, ResCtrl_DoAction DoAction, void *pCusData);

typedef struct ResCtrlItf_t_
{
    ResCtrl_CheckConflictCB CheckConflict;
    ResCtrl_OccupyResCB OccupyRes;
    ResCtrl_ReleaseResCB ReleaseRes;
    ResCtrl_ReleaseResByOwnerCB ReleaseResByOwner;
    ResCtrl_GetResOwnerCB GetResOwner;
    ResCtrl_GetUsedResNumCB GetUsedNum;
    ResCtrl_TransverseCB Transverse;
} ResCtrlItf_t;

typedef struct ResCtrl_t_
{
    const ResCtrlItf_t *pInterface;
} ResCtrl_t;

typedef enum ResCtrlType_e_
{
    RES_CTRL_TYPE__SINGLE_OWNER,
    RES_CTRL_TYPE__MULTIPLE_OWNER,
    RES_CTRL_TYPE__NUM
} ResCtrlType_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__RESCTRLITF_H__
