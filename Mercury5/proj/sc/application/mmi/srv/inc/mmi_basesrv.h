/**
* @file mmi_BaseSrv.h
*
* This header file defines the data structure of base service.
*
*/

#ifndef __MMI_BASESRV_H__
#define __MMI_BASESRV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_handler.h"
#include "mmi_mae_event.h"
#include "GenEvtHdlrItf.h"
/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define SRV_STATE_INVALID GEN_STATE_INVALID
#define SRV_EVT_INVALID   GEN_EVT_INVALID

#define SRV_RET_MASK GEN_RET_MASK
#define SRV_ACT_MASK GEN_ACT_MASK
#define SRV_ACT_DESTORY_EVT GEN_ACT_DESTORY_EVT
#define SRV_ACT_SM_WAIT GEN_ACT_SM_WAIT
#define SRV_ACT_SM_CLEAR_WAIT GEN_ACT_SM_CLEAR_WAIT
#define SRV_ACT_QUEUE_STOP_PARSE GEN_ACT_QUEUE_STOP_PARSE

#define SRV_IS_FLAG_SET  GEN_IS_FLAG_SET
#define SRV_SET_FLAG GEN_SET_FLAG
#define SRV_CLEAR_FLAG GEN_CLEAR_FLAG

#define SRV_COMBINE_RET GEN_COMBINE_RET
#define SRV_GET_RET GEN_GET_RET
#define SRV_GET_ACT GEN_GET_ACT

#define INHERIT_IBaseSrv(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(IBaseSrv);

#define SERVICE_BASE_ELEMENTS \
    DECLARE_FUNCTBL(IBaseSrv);\
    u32 nRefCnt;\
    const BaseSrvHandler_t *pBaseSrvTbl

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef MAE_Ret (*SrvConstructor)(IBaseSrv *pBaseSrv);
typedef MAE_Ret (*SrvDestructor)(IBaseSrv *pBaseSrv);
typedef MAE_Ret (*SrvHandleEvt)(IBaseSrv *pBaseSrv, MAE_EventId nEventId, u32 nParam1, u32 nParam2);

enum
{
    SRV_SM_HANDLE__ENTRY = GEN_SM_HANDLE__ENTRY,
    SRV_SM_HANDLE__EXIT,
    SRV_SM_HANDLE__EVT,
};
typedef GenSMHandle_e SrvSMHandle_e;

enum
{
    BASESRV_RET__OK = GENEVTHDLR_RET__OK,
    BASESRV_RET__FAIL,
    BASESRV_RET__BAD_PARAM,    
    BASESRV_RET__OUT_OF_MEMORY,
    BASESRV_RET__BUSY,
    BASESRV_RET__QUEUE_FULL,  
    
    BASESRV_RET__SM_DESTROY_EVT = GENEVTHDLR_RET__SM_DESTROY_EVT,
    BASESRV_RET__SM_WAIT = GENEVTHDLR_RET__SM_WAIT,
    BASESRV_RET__SM_CLEAR_WAIT = GENEVTHDLR_RET__SM_CLEAR_WAIT,
    BASESRV_RET__SM_WAIT_AND_DESTROY = GENEVTHDLR_RET__SM_WAIT_AND_DESTROY,
    BASESRV_RET__SM_CLEAR_WAIT_AND_DESTROY = GENEVTHDLR_RET__SM_CLEAR_WAIT_AND_DESTROY,
    BASESRV_RET__QUEUE_DESTROY_EVT = GENEVTHDLR_RET__QUEUE_DESTROY_EVT,    
    BASESRV_RET__QUEUE_STOP_PARSE = GENEVTHDLR_RET__QUEUE_STOP_PARSE,
    BASESRV_RET__QUEUE_STOP_AND_DESTROY = GENEVTHDLR_RET__QUEUE_STOP_AND_DESTROY,
};
typedef GenEvtHdlrRet_e BaseSrvRet_e;

typedef GenEvtHdlrHdl_t BaseSrvHdl_t;
typedef GenEvtHdl_t SrvEvtHdl_t;

typedef void (*BaseSrvInformCb)(BaseSrvHdl_t pBaseSrvHdl, SrvEvtHdl_t pCurEvtHdl);
typedef GenEvtHdlrHistoryFilter BaseSrvHistoryFilter;
typedef GenEvtHdlrSMEvtFilter BaseSrvSMEvtFilter;
typedef GenEvtFreeCb SrvEvtFreeCb;

typedef struct
{    
    SrvConstructor pfnConstructor;
    SrvDestructor pfnDestructor;
    SrvHandleEvt pfnHandleEvt;
}BaseSrvHandler_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/
/*Base service APIs*/
MAE_Ret BaseSrvInit(MAE_ClsId nClsId, void **ppObj, u32 nSize, const BaseSrvHandler_t *pBaseSrvTbl);

BaseSrvHdl_t BaseSrvCreate(IBaseSrv *pBaseSrv, const StateToFuncCB_t *pStateHandler, const QueueHandler_t *pQueueHandler, u16 nQueueSize);
void BaseSrvSetAttribute(BaseSrvHdl_t pBaseSrvHdl, u32 nAttribute);
void BaseSrvSetHistoryFilter(BaseSrvHdl_t pBaseSrvHdl, BaseSrvHistoryFilter pfnHistoryFilter);
MAE_Ret BaseSrvDestroy(BaseSrvHdl_t pBaseSrvHdl);
IBaseSrv * BaseSrvGetCurrService(BaseSrvHdl_t pBaseSrvHdl);
void BaseSrvSetGuidingEvt(BaseSrvHdl_t pBaseSrvHdl, SrvEvtHdl_t pGuidingEvt);
SrvEvtHdl_t BaseSrvGetGuidingEvt(BaseSrvHdl_t pBaseSrvHdl);
void BaseSrvDestroyGuidingEvt(BaseSrvHdl_t pBaseSrvHdl);

u16 BaseSrvSMGetCurrState(BaseSrvHdl_t pBaseSrvHdl);
u16 BaseSrvSMGetPrevState(BaseSrvHdl_t pBaseSrvHdl);
boolean BaseSrvSMIsWaiting(BaseSrvHdl_t pBaseSrvHdl);
MAE_Ret BaseSrvSMHandleEvt(BaseSrvHdl_t pBaseSrvHdl, SrvEvtHdl_t pEvtHdl);
MAE_Ret BaseSrvSMTransTo(BaseSrvHdl_t pBaseSrvHdl, u16 nTargetState);
void BaseSrvSMSetEvtFilter(BaseSrvHdl_t pBaseSrvHdl, BaseSrvSMEvtFilter pfnSMEvtFilter);

MAE_Ret BaseSrvQueueHandleEvt(BaseSrvHdl_t pBaseSrvHdl, SrvEvtHdl_t pEvtHdl);
boolean BaseSrvQueueCheckAbortEvt(BaseSrvHdl_t pBaseSrvHdl, SrvEvtHdl_t pEvtHdl);
u16 BaseSrvQueueGetEvtNum(BaseSrvHdl_t pBaseSrvHdl);

MAE_Ret BaseSrvInformEvt(BaseSrvHdl_t pBaseSrvHdl, void *pDestInstance, BaseSrvInformCb pfnInformCb, SrvEvtHdl_t pEvtHdl);

void BaseSrvSetUTMode(boolean bUTMode);

/*Basic event component*/
void SrvEvtCmnFreeCb(u32 nEventData);
SrvEvtHdl_t SrvEvtCreate(u32 nEventId, u32 nEventData, SrvEvtFreeCb pFreeCb);
void SrvEvtDestroy(SrvEvtHdl_t pEvtHdl);
u32 SrvEvtGetId(SrvEvtHdl_t pEvtHdl);
u32 SrvEvtGetData(SrvEvtHdl_t pEvtHdl);
void SrvEvtSetId(SrvEvtHdl_t pEvtHdl, u32 nEventId);

#endif //__MMI_BASESRV_H__

