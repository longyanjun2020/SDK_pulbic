/**
* @file ResMgr_CmdMgr.h
*
* This header file defines the APIs of resource command manager.
*
*/

#ifndef __RESMGR_CMDMGR_H__
#define __RESMGR_CMDMGR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_CmdMgrItf.h"
#include "ResMgr_CmdMgrFacItf.h"
#include "ResMgr_CmdMgrStgrItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ResMgr_CmdMgr_t_
{
    ResMgr_StgrType_e eStrategier;
    CmdMgrStgrHdl_t pStgrHdl[RES_MGR_RES_CATEGORY__NUM];
} ResMgr_CmdMgr_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__RESMGR_CMDMGR_H__

