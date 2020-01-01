/**
* @file HAL_MmpResCtrlItf.h
*
* This header file defines the interfaces of multimedia resources
* in HW adaptor layer
*/

#ifndef __HAL_MMPRESCTRLITF_H__
#define __HAL_MMPRESCTRLITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResCtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResCtrlHandle_t MmpResCtrl_Init(void);
void MmpResCtrl_Uninit(ResCtrlHandle_t pResCtrlHdl);
bool MmpResCtrl_IsConflict(u32 uCtrlID1, u32 uCtrlID2);
#endif //__HAL_MMPRESCTRLITF_H__

