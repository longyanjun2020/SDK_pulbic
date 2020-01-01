/**
* @file ABL_Gss.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of GSS.
*
*/

#ifndef __ABL_GSS_H__
#define __ABL_GSS_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_gss_itf.h"
#include "srv_ResMgr_Gss.h"
#include "esl_vdo_itf.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_ExecRes_e ABL_MmlGssRenderParseExecRes(s16 sResult);
ResMgr_ExecRes_e ABL_MmlGssImageParseExecRes(s16 sResult);
void ABL_GssFreeDecodeSyncCusData(void *pCusData);
void ABL_GssFreeDecodeNextFrameCusData(void *pCusData);
void ABL_GssFreeGetImageInfoCusData(void *pCusData);
ResMgr_ExecRes_e ABL_MmlGssParseExecRes(s16 sResult);
ResMgr_ExecRes_e ABL_GssParseExecRes(s16 sResult);
void ABL_GssInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_GssFreeCusData(void *pCusData);
void ABL_GssFreeEncodeCusData(void *pCusData);
void ABL_GssFreeSetEXIFCusData(void *pCusData);
void ABL_GssFreeRenderStartCusData(void *pCusData);
void ABL_GssFreeRenderGetInfoCusData(void *pCusData);
void ABL_GssGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
void ABL_GssInformAppExt(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_GssFreeCusDataExt(void *pCusData);
void ABL_GssGetCusDataExt(void *pSrcCusData, void *pRspData, void **ppDestCusData);
esl_GssFormat_e ABL_GssRemapFormat(ABL_GssFormat_e eFormat);
Image_StereoMode ABL_GssRemapStereo(ABL_ImageStereoType_e eStereo);
esl_GssEmuBinType_e ABL_GssRemapEmuBinType(ABL_GssEmuBinType_e eEmuBinType);
esl_GssPath_e ABL_GssRemapStoragePath(ABL_GssStoragePath_e ePath);
void ABL_GssConvertInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_GssConvertFreeCusData(void *pCusData);
void ABL_GssConvertGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
#endif //__ABL_GSS_H__

