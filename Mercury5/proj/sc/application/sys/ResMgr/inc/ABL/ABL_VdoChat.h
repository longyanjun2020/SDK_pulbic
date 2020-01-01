/**
* @file ABL_VdoChat.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of VideoChat.
*
*/
#ifndef __VENDOR_SMALLROM__
#ifndef __ABL_VDOCHAT_H__
#define __ABL_VDOCHAT_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_vc_itf.h"
#include "MediaRspItf.h"
#include "srv_ResMgr_VdoChat.h"
#include "srv_ResMgr_MmlManager.h"
#include "ABL_Cam.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
ResMgr_ExecRes_e ABL_VdoChatParseExecRes(s16 sResult);
ResMgr_ExecRes_e ABL_MmlVdoChatParseExecRes(s16 sResult);
void ABL_VdoChatInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_VdoChatFreeCusData(void *pCusData);
void ABL_VdoChatGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
#endif
#endif
