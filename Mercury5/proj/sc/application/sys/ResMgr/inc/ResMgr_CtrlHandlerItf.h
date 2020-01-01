/**
* @file ResMgr_CtrlHandlerItf.h
*
* This header file defines the interfaces of resource manager control
* handler
*/

#ifndef __RESMGR_CTRLHANDLERITF_H__
#define __RESMGR_CTRLHANDLERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_CtrlItf.h"
#include "ResMgr_DevMediatorItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_CtrlHdl_t ResMgr_CreateCtrl(ResMgr_ResCategory_e eResCategory, ResMgr_CtrlType_e eCtrlType, ResMgr_CtrlReqHandle_t pParm);
void ResMgr_DestroyCtrl(ResMgr_CtrlHdl_t pResMgrCtrl);
ResMgr_CtrlReqHandle_t ResMgr_CreateSetDeviceStatusReq(ResMgr_AppId_e eAppId, DevMedType_e eDevType, u16 uStatus);
bool ResMgr_HandleSetDeviceStatus(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t ResMgr_CreateReadDeviceStatusReq(ResMgr_AppId_e eAppId, DevMedType_e eDevType, u16 *pStatus);
bool ResMgr_HandleReadDeviceStatus(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t ResMgr_CreateGetCapabilityReq(ResMgr_AppId_e eAppId);
bool ResMgr_HandleGetMmpCapabilityReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);
ResMgr_CtrlReqHandle_t ResMgr_CreateSetSpeakerTypeReq(ResMgr_AppId_e eAppId, u32 uSpeakerType);
bool ResMgr_HandleSetSpeakerTypeReq(CmdMgrStgrHdl_t pHandle, ResMgr_CtrlHdl_t pCtrlHdl);

#endif //__RESMGR_CTRLHANDLERITF_H__

