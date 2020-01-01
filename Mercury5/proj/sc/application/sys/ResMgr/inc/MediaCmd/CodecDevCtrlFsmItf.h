/**
* @file CodecDevCtrlFsmItf.h
*
* This header file defines the interfaces of Codec Device Ctrl States
*
*/

#ifndef __CODECDEVCTRLFSMITF_H__
#define __CODECDEVCTRLFSMITF_H__

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
typedef enum CodecDevStates_e_
{
    CODEC_DEV_STATE__IDLE,
    CODEC_DEV_STATE__NUM
} CodecDevStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t CodecDevFSM_Init(void *pCusData);
void CodecDevFSM_Uninit(StateMachineHandle_t pHandle);
bool CodecDev_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__CODECDEVCTRLFSMITF_H__

