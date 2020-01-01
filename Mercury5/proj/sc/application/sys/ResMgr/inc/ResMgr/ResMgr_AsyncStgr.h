/**
* @file ResMgr_AsyncStgr.h
*
* This header file defines the interfaces of common utility of resource
* manager asynchronous strategier
*/

#ifndef __RESMGR_ASYNCSTGR_H__
#define __RESMGR_ASYNCSTGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_CmdMgrStgr.h"
#include "ResMgr_CommItf.h"
#include "ResMgr_CmdItf.h"
#include "DListItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#define TRANSVERSE_CMD_ACT__NONE            0x0000
#define TRANSVERSE_CMD_ACT__DELETE          0x0001
#define RES_MGR_APP_BIT_STREAM_SIZE         ((RES_MGR_APP_ID__NUM + 7) >> 3)
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* ResMgr_BitStreamHdl_t;

typedef void (*AsyncStgr_InitBit)(CmdMgrStgrHdl_t pStgrHdl);
typedef void (*AsyncStgr_UninitBit)(CmdMgrStgrHdl_t pStgrHdl);
typedef void (*AsyncStgr_SetBit)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCmdHdl, bool bBusyReasonLowPriority);
typedef bool (*AsyncStgr_GetBit)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCmdHdl, bool *pBusyReasonLowPriority);
typedef void (*AsyncStgr_ResetBit)(CmdMgrStgrHdl_t pStgrHdl);

typedef struct AsyncStgrBitItf_t_
{
    AsyncStgr_InitBit InitBit;
    AsyncStgr_UninitBit UninitBit;
    AsyncStgr_SetBit SetBit;
    AsyncStgr_GetBit GetBit;
    AsyncStgr_ResetBit ResetBit;
} AsyncStgrBitItf_t;

typedef struct AsyncStgr_BusyBitInfo_t_
{
    AsyncStgrBitItf_t tBusyBitItf;
    u8 *pBusyAppBitStream;
    u8 *pBusyReasonLowPriBitStream;
} AsyncStgr_BusyBitInfo_t;

typedef struct ResMgr_AsyncStgr_t_
{
    ResMgr_CmdMgrStgr_t tCmdMgrStgr;
    ResMgrCommItf_t tCommItf;
    DataStruct_t *pCmdQueue;
    DList_t *pWaitingCmdList;
    ResMgr_CmdHdl_t pCurCmd;
    ResMgr_CmdHdl_t pWaitCmd;
    AsyncStgr_BusyBitInfo_t tBusyAppInfo;    
} ResMgr_AsyncStgr_t;

typedef struct ResMgrAsyncItf_t_
{
    AsyncStgrBitItf_t *pBusyBitItf;
} ResMgrAsyncItf_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void AsyncStgr_Init(ResMgr_AsyncStgr_t *pStgr, CmdMgrStgrExtItf_t const *pExtInterface, ResMgrCommItf_t *pCommItf, ResMgrAsyncItf_t const *pAsyncItf);
void AsyncStgr_Uninit(ResMgr_AsyncStgr_t *pStgr);
bool AsyncStgr_OptimizeCmd(const DataStructItf_t *pDataStructItf, ResMgr_AsyncStgr_t *pStgr);
void AsyncStgr_SetRelatedCmdBusy(ResMgr_AsyncStgr_t *pStgr, ResMgr_CmdHdl_t pCmdHdl, bool bBusyReasonLowPriority);
bool AsyncStgr_IsRelatedCmdBusy(ResMgr_AsyncStgr_t *pStgr, ResMgr_CmdHdl_t pCmdHdl, bool *pBusyReasonLowPriority);
void AsyncStgr_ResetRelatedCmdBusyTable(ResMgr_AsyncStgr_t *pStgr);

#endif //__RESMGR_ASYNCSTGR_H__

