/**
* @file ABL_Tv.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of analog TV.
*
*/

#ifndef __ABL_TV_H__
#define __ABL_TV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_tv_itf.h"
#include "MediaRspItf.h"
#include "srv_ResMgr_Tv.h"
//#include "MML_Tv.h"
#include "ABL_Cam.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
ResMgr_ExecRes_e ABL_TvParseExecRes(s16 sResult);
void ABL_TvInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_TvFreeCusData(void *pCusData);
void ABL_TvGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
ResMgr_ExecRes_e ABL_MmlTvParseExecRes(s16 sResult);
ResMgr_ExecRes_e ABL_MmlTvImageParseExecRes(s16 sResult);
void ABL_MmlTvCaptureFreeCusData(void *pCusData);
#endif //__ABL_TV_H__
