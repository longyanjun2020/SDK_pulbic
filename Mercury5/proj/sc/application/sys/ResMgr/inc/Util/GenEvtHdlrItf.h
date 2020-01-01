/**
* @file GenEvtHdlrItf.h
*
* This header file defines the data structure of generic event handler.
*
*/

#ifndef __GENEVTHDLRITF_H__
#define __GENEVTHDLRITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h" 
/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define GEN_STATE_INVALID 0xFFFF
#define GEN_EVT_INVALID   0xFFFFFFFF

#define GEN_RET_MASK 0x0000FFFF
#define GEN_ACT_MASK 0xFFFF0000
#define GEN_ACT_DESTORY_EVT 0x0001
#define GEN_ACT_SM_WAIT 0x0002
#define GEN_ACT_SM_CLEAR_WAIT 0x0004
#define GEN_ACT_QUEUE_STOP_PARSE 0x0008

#define GEN_IS_FLAG_SET(_PARAM_, _FLAG_)  ((_FLAG_) == ((_FLAG_) & (_PARAM_)))
#define GEN_SET_FLAG(_PARAM_, _FLAG_)     ((_PARAM_) = ((_FLAG_) | (_PARAM_)))
#define GEN_CLEAR_FLAG(_PARAM_, _FLAG_)   ((_PARAM_) = (~(_FLAG_) & (_PARAM_)))

#define GEN_COMBINE_RET(_RET_, _ACT_)     (((_ACT_) << 16) | (_RET_))
#define GEN_GET_RET(_PARAM_)              ((_PARAM_) & (GEN_RET_MASK))
#define GEN_GET_ACT(_PARAM_)              (((_PARAM_) & GEN_ACT_MASK) >> 16)

#define BEGIN_STATECB_TABLE(g_tStateToFuncCBTbl) \
    static const StateToFuncCB_t g_tStateToFuncCBTbl[] = {

#define END_STATECB_TABLE   \
    {GEN_STATE_INVALID,  NULL}}

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum GenSMHandle_e_
{
    GEN_SM_HANDLE__ENTRY,
    GEN_SM_HANDLE__EXIT,
    GEN_SM_HANDLE__EVT,
} GenSMHandle_e;

enum
{
    GENEVTHDLR_RET__OK = 0,
    GENEVTHDLR_RET__FAIL,
    GENEVTHDLR_RET__BAD_PARAM,    
    GENEVTHDLR_RET__OUT_OF_MEMORY,
    GENEVTHDLR_RET__BUSY,
    GENEVTHDLR_RET__QUEUE_FULL,  
    
    GENEVTHDLR_RET__SM_DESTROY_EVT = GEN_COMBINE_RET(GENEVTHDLR_RET__OK, GEN_ACT_DESTORY_EVT),
    GENEVTHDLR_RET__SM_WAIT = GEN_COMBINE_RET(GENEVTHDLR_RET__OK, GEN_ACT_SM_WAIT),
    GENEVTHDLR_RET__SM_CLEAR_WAIT = GEN_COMBINE_RET(GENEVTHDLR_RET__OK, GEN_ACT_SM_CLEAR_WAIT),
    GENEVTHDLR_RET__SM_WAIT_AND_DESTROY = GEN_COMBINE_RET(GENEVTHDLR_RET__OK, GEN_ACT_SM_WAIT | GEN_ACT_DESTORY_EVT),
    GENEVTHDLR_RET__SM_CLEAR_WAIT_AND_DESTROY = GEN_COMBINE_RET(GENEVTHDLR_RET__OK, GEN_ACT_SM_CLEAR_WAIT | GEN_ACT_DESTORY_EVT),
    GENEVTHDLR_RET__QUEUE_DESTROY_EVT = GEN_COMBINE_RET(GENEVTHDLR_RET__OK, GEN_ACT_DESTORY_EVT),    
    GENEVTHDLR_RET__QUEUE_STOP_PARSE = GEN_COMBINE_RET(GENEVTHDLR_RET__OK, GEN_ACT_QUEUE_STOP_PARSE),
    GENEVTHDLR_RET__QUEUE_STOP_AND_DESTROY = GEN_COMBINE_RET(GENEVTHDLR_RET__OK, GEN_ACT_QUEUE_STOP_PARSE | GEN_ACT_DESTORY_EVT),
};
typedef u32 GenEvtHdlrRet_e;

typedef void *GenEvtHdlrHdl_t;
typedef void *GenSMHdl_t;
typedef void *GenQueueHdl_t;
typedef void *GenEvtHdl_t;

typedef GenEvtHdlrRet_e (*GenEvtHdlrStateHandler)(GenEvtHdlrHdl_t pEvtHdlrHdl, GenSMHandle_e eSMHandleType, GenEvtHdl_t pEvtHdl, u32 nCusData);
typedef GenEvtHdlrRet_e (*GenEvtHdlrQueueFetchEvt)(GenEvtHdlrHdl_t pEvtHdlrHdl, GenEvtHdl_t pCurEvtHdl);
typedef bool (*GenEvtHdlrQueueCheckAbort)(GenEvtHdlrHdl_t pEvtHdlrHdl, GenEvtHdl_t pCurEvtHdl, GenEvtHdl_t pWaitEvtHdl);
typedef bool (*GenEvtHdlrHistoryFilter)(u32 nEventId);
typedef bool (*GenEvtHdlrSMEvtFilter)(GenEvtHdlrHdl_t pEvtHdlrHdl, u32 nWaitingEvtId, u32 nComingEvtId);

typedef GenEvtHdlrRet_e (*GenSMHandler)(GenSMHdl_t pSMHdl, GenSMHandle_e eSMHandleType, GenEvtHdl_t pEvtHdl, u32 nCusData);
typedef GenEvtHdlrRet_e (*GenQueueParser)(GenQueueHdl_t pQueueHdl, GenEvtHdl_t pEvtHdl, u32 nCusData);
typedef void (*GenEvtFreeCb)(u32 nEventData);

typedef struct
{    
    u16 nStateId;
    GenEvtHdlrStateHandler pfnHandler;
}StateToFuncCB_t;

typedef struct
{    
    GenEvtHdlrQueueFetchEvt pfnFetchEvtCb;
    GenEvtHdlrQueueCheckAbort pfnCheckAbortCb;
}QueueHandler_t;

typedef struct
{    
    u16 nStateId;
    GenSMHandler pfnHandler;
}SMStateHandler_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/
/*Generic event handler APIs*/
GenEvtHdlrHdl_t GenEvtHdlr_Create(u32 nCusData, const StateToFuncCB_t *pStateHandler, const QueueHandler_t *pQueueHandler, u16 nQueueSize);
void GenEvtHdlr_SetHistoryFilter(GenEvtHdlrHdl_t pEvtHdlrHdl, GenEvtHdlrHistoryFilter pfnHistoryFilter);
GenEvtHdlrRet_e GenEvtHdlr_Destroy(GenEvtHdlrHdl_t pEvtHdlrHdl);
u32 GenEvtHdlr_GetCusData(GenEvtHdlrHdl_t pEvtHdlrHdl);
void GenEvtHdlr_SetGuidingEvt(GenEvtHdlrHdl_t pEvtHdlrHdl, GenEvtHdl_t pGuidingEvt);
GenEvtHdl_t GenEvtHdlr_GetGuidingEvt(GenEvtHdlrHdl_t pEvtHdlrHdl);
void GenEvtHdlr_DestroyGuidingEvt(GenEvtHdlrHdl_t pEvtHdlrHdl);

u16 GenEvtHdlr_SMGetCurrState(GenEvtHdlrHdl_t pEvtHdlrHdl);
u16 GenEvtHdlr_SMGetPrevState(GenEvtHdlrHdl_t pEvtHdlrHdl);
bool GenEvtHdlr_SMIsWaiting(GenEvtHdlrHdl_t pEvtHdlrHdl);
GenEvtHdlrRet_e GenEvtHdlr_SMHandleEvt(GenEvtHdlrHdl_t pEvtHdlrHdl, GenEvtHdl_t pEvtHdl);
GenEvtHdlrRet_e GenEvtHdlr_SMTransTo(GenEvtHdlrHdl_t pEvtHdlrHdl, u16 nTargetState);
void GenEvtHdlr_SMSetEvtFilter(GenEvtHdlrHdl_t pEvtHdlrHdl, GenEvtHdlrSMEvtFilter pfnSMEvtFilter);

GenEvtHdlrRet_e GenEvtHdlr_QueueHandleEvt(GenEvtHdlrHdl_t pEvtHdlrHdl, GenEvtHdl_t pEvtHdl);
bool GenEvtHdlr_QueueCheckAbortEvt(GenEvtHdlrHdl_t pEvtHdlrHdl, GenEvtHdl_t pEvtHdl);
u16 GenEvtHdlr_QueueGetEvtNum(GenEvtHdlrHdl_t pEvtHdlrHdl);

/*Generic state machine component*/
GenSMHdl_t GenSM_Create(const SMStateHandler_t *pStateHandler, u32 nCusData);
void GenSM_Destroy(GenSMHdl_t pSMHdl);
u16 GenSM_GetCurrState(GenSMHdl_t pSMHdl);
u16 GenSM_GetPrevState(GenSMHdl_t pSMHdl);
GenEvtHdlrRet_e GenSM_HandleEvt(GenSMHdl_t pSMHdl, GenEvtHdl_t pEvtHdl);
GenEvtHdlrRet_e GenSM_TransTo(GenSMHdl_t pSMHdl, u16 nTargetState);
void GenSM_SetWaiting(GenSMHdl_t pSMHdl, bool bWaiting);
bool GenSM_IsWaiting(GenSMHdl_t pSMHdl);

/*Generic queue component*/
GenQueueHdl_t GenQueue_Create(u16 nQueueSize);
void GenQueue_Destroy(GenQueueHdl_t pQueueHdl);
GenEvtHdlrRet_e GenQueue_AddEvt(GenQueueHdl_t pQueueHdl, GenEvtHdl_t pEvtHdl);
GenEvtHdlrRet_e GenQueue_RemoveEvt(GenQueueHdl_t pQueueHdl, GenEvtHdl_t pEvtHdl);
GenEvtHdlrRet_e GenQueue_Parse(GenQueueHdl_t pQueueHdl, GenQueueParser pfnParser, u32 nCusData);
u16 GenQueue_GetEvtNum(GenQueueHdl_t pQueueHdl);
u16 GenQueue_GetSize(GenQueueHdl_t pQueueHdl);

/*Generic event component*/
GenEvtHdl_t GenEvt_Create(u32 nEventId, u32 nEventData, GenEvtFreeCb pFreeCb);
void GenEvt_Destroy(GenEvtHdl_t pEvtHdl);
u32 GenEvt_GetId(GenEvtHdl_t pEvtHdl);
u32 GenEvt_GetData(GenEvtHdl_t pEvtHdl);
void GenEvt_SetId(GenEvtHdl_t pEvtHdl, u32 nEventId);

#endif //__GENEVTHDLRITF_H__

