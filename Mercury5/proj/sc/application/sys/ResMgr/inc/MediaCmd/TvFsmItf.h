/**
* @file TvFsmItf.h
*
* This header file defines the interfaces of analog TV States
*
*/

#ifndef __TVFSMITF_H__
#define __TVFSMITF_H__

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
typedef enum TvStates_e_
{
    TV_STATE__IDLE,
    TV_STATE__INIT,
    TV_STATE__OPEN,
    TV_STATE__PREVIEW,
    TV_STATE__CAPTURE,
    TV_STATE__NUM
} TvStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t TvFSM_Init(void *pCusData);
void TvFSM_Uninit(StateMachineHandle_t pHandle);
bool Tv_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__VIDEOFSMITF_H__

