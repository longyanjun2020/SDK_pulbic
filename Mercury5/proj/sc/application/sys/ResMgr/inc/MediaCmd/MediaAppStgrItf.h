/**
* @file MediaAppStgrItf.h
*
* This header file defines the APIs of media application strategier
*
*/

#ifndef __MEDIAAPPSTGRITF_H__
#define __MEDIAAPPSTGRITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_TaskStgr.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
CmdMgrStgrHdl_t MediaAppStgr_Init(ResMgrCommItf_t *pCommItf);
void MediaAppStgr_Uninit(CmdMgrStgrHdl_t pHandle);

#endif //__MEDIAAPPSTGRITF_H__

