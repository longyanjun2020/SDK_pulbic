/**
* @file ResMgr_DevMediatorItf.h
*
* This header file defines the APIs of device mediator.
*
*/

#ifndef __RESMGR_DEVMEDIATORITF_H__
#define __RESMGR_DEVMEDIATORITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_CmdMgrStgrItf.h"
#include "ResMgr_CtrlItf.h"
#include "MediatorItf.h"

/*=============================================================*/
// Macro Definition
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef void* DevMediatorHdl;

typedef enum DevMedType_e_
{
    DEV_MED_TYPE__HEADSET,
    DEV_MED_TYPE__BT_HEADSET,
    DEV_MED_TYPE__FM_SPEAKER,
    DEV_MED_TYPE__CC_SPEAKER,
    DEV_MED_TYPE__NUM,
    DEV_MED_TYPE__INVALID
} DevMedType_e;

typedef enum DevMed_HeadsetConfig_e_
{
    DEV_MED_HEADSET__OFF,
    DEV_MED_HEADSET__ON,
    DEV_MED_HEADSET__NUM
} DevMed_HeadsetSta_e;

typedef enum DevMed_BtHeadsetConfig_e_
{
    DEV_MED_BT_HEADSET__OFF,
    DEV_MED_BT_HEADSET__ON,
    DEV_MED_BT_HEADSET__NUM
} DevMed_BtHeadsetConfig_e;

typedef enum DevMed_SpeakerConfig_e_
{
    DEV_MED_SPEAKER__OFF,
    DEV_MED_SPEAKER__ON,
    DEV_MED_SPEAKER__NUM
} DevMed_SpeakerConfig_e;

typedef enum DevMed_SpeakerType_e_
{
    DEV_MED_SPEAKER_TYPE__MONO,
    DEV_MED_SPEAKER_TYPE__STEREO,
    DEV_MED_SPEAKER_TYPE__NUM
} DevMed_SpeakerType_e;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
DevMediatorHdl DevMed_Init(void *pCusData);
void DevMed_Uninit(DevMediatorHdl pDevMedHdl);
void DevMed_RegClient(DevMediatorHdl pDevMedHdl, MediatorClient_t *pMedClientItf);
void DevMed_DeregClient(DevMediatorHdl pDevMedHdl, MediatorClient_t *pMedClientItf);
void DevMed_ChangeStatus(DevMediatorHdl pDevMedHdl, DevMedType_e eDevType, u16 uStatus);
u16 DevMed_GetStatus(DevMediatorHdl pDevMedHdl, DevMedType_e eDevType);
void DevMed_OnChanged(DevMediatorHdl pDevMedHdl, DevMedType_e eDevType, u16 uStatus);

#endif //__RESMGR_DEVMEDIATORITF_H__

