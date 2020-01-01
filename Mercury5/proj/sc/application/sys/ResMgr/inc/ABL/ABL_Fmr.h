/**
* @file ABL_Fmr.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*   drivers and Resource Manager
*  This header file defines the declaration of operations of FM Radio.
*
*/

#ifndef __ABL_FMR_H__
#define __ABL_FMR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_fmr_itf.h"
#include "MediaRspItf.h"
#include "srv_resmgr_mmlradio_types.h"
//#include "MML_Manager.h"
#include "ABL_Aud.h"
#include "srv_ResMgr_Fmr.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_ExecRes_e ABL_FmrParseExecRes(s16 sResult);
void ABL_FmrInformApp(void *pCusData, void *pRsp, ResMgr_InformType_e eInformType);
void ABL_FmrFreeCusData(void *pCusData);
void ABL_FmrGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
void ABL_FmrFreeRecStartInfoCusData(void *pCusData);
MmlRadioRangeBandMinFrequency_e ABL_MmlFmrRemapRangeBandMinFrequency(esl_FmrBeginRange_e eRangeBandMinFrequency);
MmlRadioRangeBandMaxFrequency_e ABL_MmlFmrRemapRangeBandMaxFrequency(esl_FmrEndRange_e eRangeBandMaxFrequency);
ResMgr_ExecRes_e ABL_MmlFmrRecParseExecRes(s16 sResult);

#endif //__ABL_FMR_H__

