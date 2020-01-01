/**
* @file srv_ResMgr_Vfs.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of analog TV.
*
*/

#ifndef __SRV_RESMGR_VFS_H__
#define __SRV_RESMGR_VFS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "MediaRspItf.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum ABL_VfsErrCode_e_
{
    ABL_VFS_OK,               //DBL_VFS_OK
    ABL_VFS_FAIL,             //DBL_VFS_FAIL
    ABL_VFS_PARAM_ERROR,      //DBL_VFS_PARAM_ERROR
    ABL_VFS_MEM_ALLOC_ERROR,  //DBL_VFS_MEM_ALLOC_ERROR
    ABL_VFS_REJECT,           //DBL_VFS_REJECT
    ABL_VFS_ABORT,            //DBL_VFS_ABORT
    ABL_VFS_TIMEOUT,          //DBL_VFS_TIMEOUT
    ABL_VFS_DENY,
    ABL_VFS_MERGE
} ABL_VfsErrCode_e;

typedef struct DBLVfsRemapErrCode_t_
{
    ABL_VfsErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLVfsRemapErrCode_t;

typedef struct ABL_VfsRspInfo_t_
{
    ABL_VfsErrCode_e eErrCode;
    void *tVfsInfo;
} ABL_VfsRspInfo_t;

typedef void (*ABL_VfsCb)(u16 uSenderId, u32 uUserValue, ABL_VfsErrCode_e eErrCode, void *pVfsInfo);

typedef struct ABL_VfsCb_t_
{
    u16 uSenderId;
    u32 uUserValue;
    ABL_VfsCb pfnCb;
} ABL_VfsCb_t;

typedef struct VfsCmd_t_
{
    ABL_VfsCb_t *pCbParams;
} VfsCmd_t;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
void ABL_VfsOpenSessionReq(ResMgr_AppId_e eAppId, ABL_VfsCb_t *pVfsCb);
void ABL_VfsCloseSessionReq(ResMgr_AppId_e eAppId, ABL_VfsCb_t *pVfsCb);
#endif //__ABL_VFS_H__

