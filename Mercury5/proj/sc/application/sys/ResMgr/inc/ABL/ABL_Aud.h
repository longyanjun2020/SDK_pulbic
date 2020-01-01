/**
* @file ABL_Aud.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of audio.
*
*/

#ifndef __ABL_AUD_H__
#define __ABL_AUD_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_aud_itf.h"
#include "Esl_vdo_itf.h"
#include "MediaCtrlItf.h"
#include "HAL_AudResCtrlItf.h"
#include "MediaRspItf.h"
#include "srv_ResMgr_Aud.h"
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
__SLDPM_FREE__ ResMgr_ExecRes_e ABL_AudParseExecRes(s16 sResult);
__SLDPM_FREE__ ResMgr_ExecRes_e ABL_MmlAudParseExecRes(s16 sResult);
__SLDPM_FREE__ void ABL_AudInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
__SLDPM_FREE__ void ABL_AudFreeCusData(void *pCusData);
__SLDPM_FREE__ void ABL_AudFreePlayFileCusData(void *pCusData);
__SLDPM_FREE__ void ABL_AudFreeGetID3V1InfoCusData(void *pCusData);
__SLDPM_FREE__ void ABL_AudFreeGetAdvInfoCusData(void *pCusData);
__SLDPM_FREE__ void ABL_AudFreeGetFileInfoCusData(void *pCusData);
__SLDPM_FREE__ void ABL_AudFreeRecStartInfoCusData(void *pCusData);
__SLDPM_FREE__ void ABL_AudGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
__SLDPM_FREE__ ResMgr_CmdHdl_t ABL_AudCusFunc(CmdMgrStgrHdl_t pStgrHdl, ResMgr_CmdHdl_t pCurCmdHdl, ResMgr_CusCmdType_e eCusCmdType);

#endif //__ABL_AUD_H__

