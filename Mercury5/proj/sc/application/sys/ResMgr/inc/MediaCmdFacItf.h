/**
* @file MediaCmdFacItf.h
*
* This header file defines the interfaces of audio commands
*
*/

#ifndef __MEDIACMDFACITF_H__
#define __MEDIACMDFACITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "MediaCmdItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_CmdHdl_t Media_CreateCmd
(
    ResMgr_AppId_e eAppId,
    MediaCmdSuspend_e eSuspendType,
    MediaCmdResume_e eResume,
    MediaCmdActType_e eActType,
    MediaCmdCusParm_t *pParms,
    bool bLoopPlay,
    void *pCusData
);

ResMgr_CmdHdl_t Media_CreateCmdExt
(
    ResMgr_AppId_e eAppId,
    MediaCmdSuspend_e eSuspendType,
    MediaCmdResume_e eResume,
    MediaCmdActType_e eActType,
    MediaCmdCusParm_t *pParms,
    bool bLoopPlay,
    void *pCusData
 );

void Media_DestroyCmd(ResMgr_CmdHdl_t pCmdHdl);
void* Media_GetCmdParms(ResMgr_CmdHdl_t pCmdHdl);

#endif //__MEDIACMDFACITF_H__

