/**
* @file ObjArrayItf.h
*
* This header file defines the interface of object array utility
*
*/

#ifndef __OBJARRAYITF_H__
#define __OBJARRAYITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define OBJ_ARRAY_ACT__KEEP                              0x0000
#define OBJ_ARRAY_ACT__CLEAR                             0x0001
#define OBJ_ARRAY_ACT__STOP                              0x0002

#define OBJ_ARRAY_IS_FLAG_SET(_RET_, _FALG_)             (_FALG_ == (_FALG_ & _RET_))
#define OBJ_ARRAY_IS_FLAG_NOT_SET(_RET_, _FALG_)         (_FALG_ != (_FALG_ & _RET_))

#define OBJ_ARRAY_NOT_FOUND 0XFFFF

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void (*ObjArray_CopyObject)(void *pDest, void *pSrc, u16 uObjSize);
typedef void (*ObjArray_ClearObject)(void *pObj, u16 uObjSize) ;
typedef bool (*ObjArray_IsObjEqual)(void *pvObj1, void *pvObj2) ;
typedef void* ObjArrayHdl_t;
typedef u16 (*ObjArray_DoAction)(u16 uIndex, void *pOwner, void *pCusData);

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ObjArrayHdl_t ObjArray_Init_Ex(u16 uMaxSize, u16 uObjSize, ObjArray_CopyObject CopyData, ObjArray_ClearObject ClearData, ObjArray_IsObjEqual CmpData) ;
ObjArrayHdl_t ObjArray_Init(u16 uMaxSize, u16 uObjSize, ObjArray_CopyObject CopyData);
void ObjArray_Uninit(ObjArrayHdl_t pObjArrayHdl);
void ObjArray_Get(ObjArrayHdl_t pObjArrayHdl, u16 uIdx, void *pObj);
void ObjArray_Clear(ObjArrayHdl_t pObjArrayHdl, u16 uIdx);
void ObjArray_Put(ObjArrayHdl_t pObjArrayHdl, u16 uIdx, void *pObj);
bool ObjArray_HasObject(ObjArrayHdl_t pObjArrayHdl, u16 uIdx);
__SLDPM_FREE__ u16 ObjArray_GetObjectNum(ObjArrayHdl_t pObjArrayHdl);
u16 ObjArray_GetMaxNum(ObjArrayHdl_t pObjArrayHdl);
void ObjArray_ClearAll(ObjArrayHdl_t pObjArrayHdl);
u16 ObjArray_Transverse(ObjArrayHdl_t pObjArrayHdl, ObjArray_DoAction DoAction, void *pCusData);

u16 ObjArray_FindObject(ObjArrayHdl_t pObjArrayHdl, void *pvObj) ;

#endif //__OBJARRAYITF_H__
