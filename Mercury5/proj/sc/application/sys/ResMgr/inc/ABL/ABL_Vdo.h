/**
* @file ABL_Vdo.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of video.
*
*/

#ifndef __ABL_VDO_H__
#define __ABL_VDO_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_vdo_itf.h"
#include "MediaRspItf.h"
#include "srv_ResMgr_Vdo.h"
//#include "MML_Manager.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_ExecRes_e ABL_MmlVdoParseExecRes(s16 sResult);
void ABL_MmlVdoFreeGetMemInfoCusData(void *pCusData);
void ABL_VdoInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_VdoFreeCusData(void *pCusData);
void ABL_VdoFreeOpenCusData(void *pCusData);
void ABL_VdoFreeGetFileInfoCusData(void *pCusData);
void ABL_VdoGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
ResMgr_CmdHdl_t ABL_VdoCusFunc(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CusCmdType_e eCusCmdType);
#endif //__ABL_VDO_H__
