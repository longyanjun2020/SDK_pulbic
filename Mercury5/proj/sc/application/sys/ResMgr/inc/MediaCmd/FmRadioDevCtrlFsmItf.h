/**
* @file FmRadioDevCtrlFsmItf.h
*
* This header file defines the interfaces of Fm Radio Device Ctrl States
*
*/

#ifndef __FMRADIOEVCTRLFSMITF_H__
#define __FMRADIOEVCTRLFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "StateMachineItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum FmRadioDevStates_e_
{
    FMRADIO_DEV_STATE__IDLE,
    FMRADIO_DEV_STATE__NUM
} FmRadioDevStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t FmRadioDevFSM_Init(void *pCusData);
void FmRadioDevFSM_Uninit(StateMachineHandle_t pHandle);
bool FmRadioDev_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__FMRADIOEVCTRLFSMITF_H__

