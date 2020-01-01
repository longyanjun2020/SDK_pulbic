/**
* @file ResMgr_EvtFacItf.h
*
* This header file defines the interfaces of media control factory
*
*/

#ifndef __RESMGR_EVTFACITF_H__
#define __RESMGR_EVTFACITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_EvtItf.h"
#include "ResMgr_DevMediatorItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* DevMedEvtParmHdl;
typedef void* ProRspEvtParmHdl;
typedef void* GenRspEvtParmHdl;

typedef struct DevMedEvtParms_t_
{
    DevMedType_e eDevType;
    u16 uStatus;
} DevMedEvtParms_t;

typedef struct ProRspEvtParms_t_
{
    u32 uRspId;
    u32 uRspOwner;
    void *pRspData;
	ResMgr_FreeCusRspData FreeCusRspData;
} ProRspEvtParms_t;

typedef struct GenRspEvtParms_t_
{
    void *pInformApp;
    void *pCusData;
    void *pRspData;
	ResMgr_InformType_e eInformType;
} GenRspEvtParms_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_EvtHdl_t ResMgr_CreateEvt(ResMgr_ResCategory_e eResCategory, ResMgr_EvtType_e eEvt, u32 uParams);
void ResMgr_DestroyEvt(ResMgr_EvtHdl_t pResMgrEvtHdl);
DevMedEvtParmHdl ResMgr_PackDevMedChgEvtParms(DevMedType_e eDevType, u16 uStatus);
void ResMgr_DestroyDevMedChgEvtParms(DevMedEvtParmHdl pEvtParmsHdl);
ProRspEvtParmHdl ResMgr_PackProRspEvtParms(u32 uRspId, u32 uRspOwner, void *pRspData, ResMgr_FreeCusRspData FreeCusRspData);
void ResMgr_DestroyProRspEvtParms(ProRspEvtParmHdl pEvtParmsHdl);
GenRspEvtParmHdl ResMgr_PackGenRspEvtParms(void *pInformApp, void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ResMgr_DestroyGenRspEvtParms(GenRspEvtParmHdl pEvtParmsHdl);

#endif //__RESMGR_EVTFACITF_H__

