/**
* @file ABL_Tv.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of analog TV.
*
*/

#ifndef __ABL_VFS_H__
#define __ABL_VFS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "MediaRspItf.h"
#include "srv_ResMgr_Vfs.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
void ABL_VfsInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_VfsFreeCusData(void *pCusData);
void ABL_VfsGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
ResMgr_ExecRes_e ABL_VfsParseExecRes(s16 sResult);
#endif //__ABL_VFS_H__

