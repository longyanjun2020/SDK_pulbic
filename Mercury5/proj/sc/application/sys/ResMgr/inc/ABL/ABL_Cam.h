/**
* @file ABL_Cam.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of Camera.
*
*/

#ifndef __ABL_CAM_H__
#define __ABL_CAM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_cam_itf.h"
#include "MediaRspItf.h"
#include "srv_ResMgr_Cam.h"
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
void *ABL_CamCusFunc(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CusCmdType_e eCusCmdType);
ResMgr_ExecRes_e ABL_CamParseExecRes(s16 sResult);
ResMgr_ExecRes_e ABL_MmlCamParseExecRes(s16 sResult);
ResMgr_ExecRes_e ABL_MmlVDRParseExecRes(s16 sResult);
ResMgr_ExecRes_e ABL_MmlImageParseExecRes(s16 sResult);
void ABL_CamInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_CamFreeCusData(void *pCusData);
void ABL_CamFreeStartRecData(void *pCusData);
void ABL_CamFreeImgCaptureData(void *pCusData);
void ABL_CamGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
#endif //__ABL_CAM_H__


