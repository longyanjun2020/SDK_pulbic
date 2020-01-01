/**
* @file ResMgr_CmdMgrStgrItf.h
*
* This header file defines the interface of command manager tStgr
*
*/

#ifndef __RESMGR_CMDMGRSTGRITF_H__
#define __RESMGR_CMDMGRSTGRITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_CommItf.h"
#include "ResMgr_CtrlItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/
#ifndef __SDK_SIMULATION__
#define RES_MGR__MAX_CMD_IN_QUEUE                   50
#else
#define RES_MGR__MAX_CMD_IN_QUEUE                   150
#endif
#define RES_MGR__MERGE_KEYPAD__TONE_THRESHOLD       8
#define RES_MGR__MERGE_EVTCENTER__TONE_THRESHOLD    8

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* CmdMgrStgrHdl_t;

typedef CmdMgrStgrHdl_t (*CmdMgrStgr_Init)(ResMgrCommItf_t *pCommItf);
typedef void (*CmdMgrStgr_Uinit)(CmdMgrStgrHdl_t pHandle);
typedef void (*CmdMgrStgr_HandleCmd)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCmdHdl);
typedef void (*CmdMgrStgr_HandleRsp)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_RspHdl_t pRspHdl);
typedef bool (*CmdMgrStgr_HandleCtrl)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);
typedef void (*CmdMgrStgr_HandleEvt)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_EvtHdl_t pEvtHdl);

typedef struct CmdMgrStgrExtItf_t_
{
    CmdMgrStgr_HandleCmd HandleCmd;
    CmdMgrStgr_HandleRsp HandleRsp;
    CmdMgrStgr_HandleCtrl HandleCtrl;
    CmdMgrStgr_HandleEvt HandleEvt;
} CmdMgrStgrExtItf_t;

typedef bool (*CmdMgrStgr_ExecCtrlReq)(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CtrlHdl_t pCtrlHdl);

/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__RESMGR_CMDMGRSTGRITF_H__

