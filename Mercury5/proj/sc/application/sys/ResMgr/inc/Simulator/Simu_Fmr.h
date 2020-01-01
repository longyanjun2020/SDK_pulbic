/**
* @file Simu_Fmr.h
*
* This header file defines the interface of lower layer device simulation for radio
*
*/
#ifndef __SIMU_FMR_H__
#define __SIMU_FMR_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"
#include "esl_fmr_itf.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_FmrPowerOnCb(void *pUserData);
void Simu_FmrPowerOffCb(void *pUserData);
void Simu_FmrSetBandCb(void *pUserData);
void Simu_FmrSetFrequencyCb(void *pUserData);
void Simu_FmrSetAreaCb(void *pUserData);
void Simu_FmrSetCarrierThreshold(void *pUserData);
void Simu_FmrSetMuteCb(void *pUserData);
void Simu_FmrSetUnMuteCb(void *pUserData);
void Simu_FmrSetStereoCb(void *pUserData);
void Simu_FmrSearchChannelCb(void *pUserData);
void Simu_FmrCancelSearchCb(void *pUserData);
void Simu_FmrGetChanInfoCb(void *pUserData);
void Simu_FmrGetChipInfoCb(void *pUserData);
void Simu_FmrGetCapabilityCb(void *pUserData);



void Simu_FmrRecStart(void *pUserData, esl_FmrRecParam_t tRecParam);
void Simu_FmrRecStop(void *pUserData);
void Simu_FmrGetRecFileName(void *pUserData);

#endif //__SIMU_FMR_H__