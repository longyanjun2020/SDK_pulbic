/**
* @file ResMgr_CtrlFac.h
*
* This header file defines the data structure of resource manager
* controls
*/

#ifndef __RESMGR_CTRLFAC_H__
#define __RESMGR_CTRLFAC_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_CtrlHandlerItf.h"

/*=============================================================*/
// Structure Declarations
/*=============================================================*/
typedef struct DevMed_SetDeviceStatusReq_t_
{
    ResMgr_AppId_e eAppId;
    DevMedType_e eDevType;
    u16 uStatus;
} DevMed_SetDeviceStatusReq_t;

typedef struct DevMed_ReadStatusReq_t_
{
    ResMgr_AppId_e eAppId;
    DevMedType_e eDevType;
    u16 *pStatus;
} DevMed_ReadDeviceStatusReq_t;

typedef struct ResMgr_GetMmpCapabilityReq_t_
{
    ResMgr_AppId_e eAppId;
} ResMgr_GetMmpCapabilityReq_t;

typedef struct ResMgr_SetSpeakerTypeCtrl_t_
{
    ResMgr_AppId_e eAppId;
    u32 uSpeakerType;
} ResMgr_SetSpeakerTypeCtrl_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__RESMGR_CTRLFAC_H__

