/**
* @file ResMgr_DevMediator.h
*
* This header file defines the APIs of device mediator.
*
*/

#ifndef __RESMGR_DEVMEDIATOR_H__
#define __RESMGR_DEVMEDIATOR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_DevMediatorItf.h"
#include "ResMgr_CmdMgrItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ResMgr_DevMed_t_
{
    MediatorHandle_t aDevMediatorHdl[DEV_MED_TYPE__NUM];
} ResMgr_DevMed_t;

typedef struct DevMed_Params_t_
{
    u16 uMedId;
    u16 uDataSize;
    MedChangeStaus ChangeStatus;
    u16 uDefVal;
} DevMed_Params_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__RESMGR_RESMEDIATOR_H__

