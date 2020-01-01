/**
* @file Simu_Tv.h
*
* This header file defines the interface of lower layer device simulation for analog TV
*
*/
#ifndef __SIMU_TV_H__
#define __SIMU_TV_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"
#include "ABL_Tv.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct Simu_TvCbRemap_t_
{
    u16 uTimerId;
    PfnMmlTvResponseCallback TvCb;
} Simu_TvCbRemap_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_TvOpenCb(void *pUserData);
void Simu_TvCloseCb(void *pUserData);
void Simu_TvSetConfigCb(void *pUserData);
void Simu_TvGetInfoCb(void *pUserData);
void Simu_TvGetEmInfoCb(void *pUserData);
void Simu_TvSwitchChannelCb(void *pUserData);
void Simu_TvScanChannelCb(void *pUserData, u32 uChannelIndex);
void Simu_TvPreviewCb(void *pUserData);
void Simu_TvCaptureCb(void *pUserData);
void Simu_TvResetWindowCb(void *pUserData);
void Simu_TvSetShutterSoundCb(void *pUserData);
void Simu_TvGetFileNameCb(void *pUserData);
#endif //__SIMU_TV_H__
