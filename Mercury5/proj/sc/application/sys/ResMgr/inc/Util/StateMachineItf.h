/**
* @file StateMachineItf.h
*
* This header file defines the generic APIs of finite state machine.
*
*/

#ifndef __STATEMACHINEITF_H__
#define __STATEMACHINEITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define STATE_ACT__NONE                             0x00000000
#define STATE_ACT__TRANSIT                          0x00000001
#define STATE_ACT__MASK                             0x0000000F
#define STATE_PARAM__MASK                           0xFFFFFFF0

#define STATE_RET__SET_CUS_FLAG(_RET_, _FLAG_)          (((_RET_)->uCusFlags) |= _FLAG_)
#define STATE_RET__GET_CUS_FLAG(_RET_)                  ((_RET_)->uCusFlags)

#define STATE_RET__SET_CUS_PARAM(_RET_, _PARAM_)        (((_RET_)->uCusParams) |= _PARAM_)
#define STATE_RET__GET_CUS_PARAM(_RET_)                 ((_RET_)->uCusParams)

#define STATE_PARAM__IS_FLAG_SET(_PARAM_, _FLAG_)       ((_FLAG_) == ((_FLAG_) & (_PARAM_)))
#define STATE_PARAM__IS_FLAG_NOT_SET(_PARAM_, _FLAG_)   ((_FLAG_) != ((_FLAG_) & (_PARAM_)))
#define STATE_PARAM__GET_STATE(_PARAM_)                 ((STATE_PARAM__MASK & (_PARAM_)) >> 4)
#define STATE_PARAM__SET_STATE(_PARAM_, _STATE_ID_)     ((_PARAM_) |= ((_STATE_ID_) << 4))
#define STATE_PARAM__IS_STATE_SET(_PARAM_, _STATE_ID_)  ((_STATE_ID_) == ((_STATE_ID_) & STATE_PARAM__GET_STATE(_PARAM_)))

#define TRANSIT_STATE(_PARAM_, _STATE_ID_)              ((_PARAM_) |= (STATE_ACT__TRANSIT | ((_STATE_ID_) << 4)))
#define STATE_RET__SET_TRANSIT_STATE(_RET_, _STATE_ID_) (((_RET_)->uStateParams) = TRANSIT_STATE((_RET_)->uStateParams, _STATE_ID_))

#if defined(FSM_ENABLE_DEBUG_INFO)
    #define FSM_INIT_PATTERN    0x201AE32C
    #define FSM_UNINIT_PATTERN  0x32AECD21
#endif

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef void* StateMachineHandle_t;

typedef u32 (*GenericState_EntryFunc)(StateMachineHandle_t pHandle, u16 uStateId, void *pCusData);
typedef u32 (*GenericState_ExitFunc)(StateMachineHandle_t pHandle, u16 uStateId, void *pCusData);
typedef u32 (*GenericState_HandleEvt)(StateMachineHandle_t pHandle, u16 uStateId, void *pCusData, void *pEvt, void *pRetParam);
typedef bool (*GenericState_AcceptAct)(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

typedef struct GenericState_t_
{
    GenericState_EntryFunc EntryFunc;
    GenericState_ExitFunc ExitFunc;
    GenericState_HandleEvt HandleEvt;
    GenericState_AcceptAct AcceptAct;
} GenericState_t;

typedef struct StateMachine_t_
{
    u16 uCurState;
    u16 uPrevState;
    u16 uStateNum;
    void *pCusData;
    const GenericState_t *pStates;
#if defined(FSM_ENABLE_DEBUG_INFO)
    u32 uDebugInfo;
#endif
    u16 uInitState;
} StateMachine_t;

typedef struct StateMachineRetParam_t_
{
    u32 uStateParams;
    u32 uCusFlags;
    u32 uCusParams;
} StateMachineRetParam_t;

typedef StateMachineHandle_t (*InitStateMachine)(void *pCusData);
typedef void (*UninitStateMachine)(StateMachineHandle_t pHandle);

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void StateMachine_Init(StateMachineHandle_t pHandle, void *pCusData, u16 uStateNum, const GenericState_t *pStates, u16 uDefaultState);
void StateMachine_HandleEvt(StateMachineHandle_t pHandle, void *pEvt, void *pRetParam);
void StateMachine_Uninit(StateMachineHandle_t pHandle);
bool StateMachine_AcceptAct(StateMachineHandle_t pHandle, u16 uAction);

void StateMachine_Reset(StateMachineHandle_t pHandle);

#endif //__STATEMACHINEITF_H__
