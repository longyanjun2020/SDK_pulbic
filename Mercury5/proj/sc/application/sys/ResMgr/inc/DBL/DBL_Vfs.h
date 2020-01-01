/**
* @file DBL_Vfs.h
*
* Driver Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of analog VFS.
*
*/

#ifndef __DBL_VFS_H__
#define __DBL_VFS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "DBL_Common.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
//#pragma message("TODO: Should be replaced by driver's error code when integrating VFS into ResMgr in future")
typedef enum DBL_VfsErrCode_e_
{
    DBL_VFS_OK,
    DBL_VFS_FAIL,
    DBL_VFS_PARAM_ERROR,
    DBL_VFS_MEM_ALLOC_ERROR,
    DBL_VFS_REJECT,
    DBL_VFS_ABORT,
    DBL_VFS_TIMEOUT
} DBL_VfsErrCode_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ABL_VfsErrCode_e DBL_VfsRemapErrCode(s16 sResult, ResMgr_ExecRes_e *pExecRes);
void DBL_VfsCmnCb(u16 uSenderId, u32 uUserValue, DBL_VfsErrCode_e eErrCode, void *pVfsInfo);
s16 DBL_VfsOpenSession(ResMgr_CmdHdl_t pCurCmdHdl);
s16 DBL_VfsCloseSession(ResMgr_CmdHdl_t pCurCmdHdl);
#endif //__DBL_TV_H__
