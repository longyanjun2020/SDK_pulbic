/**
* @file CodecFsmItf.h
*
* This header file defines the interfaces of Codec States
*
*/

#ifndef __CODECFSMITF_H__
#define __CODECFSMITF_H__

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
typedef enum CodecStates_e_
{
    CODEC_STATE__IDLE,
    CODEC_STATE__INIT,
    CODEC_STATE__DECODE,
    CODEC_STATE__OPEN,
    CODEC_STATE__CONVERT,
    CODEC_STATE__NUM
} CodecStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t CodecFSM_Init(void *pCusData);
void CodecFSM_Uninit(StateMachineHandle_t pHandle);
bool Codec_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__CODECFSMITF_H__

