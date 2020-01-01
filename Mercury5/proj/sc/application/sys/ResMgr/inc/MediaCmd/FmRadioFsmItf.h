/**
* @file FmRadioFsmItf.h
*
* This header file defines the interfaces of FmRadio States
*
*/

#ifndef __FMRADIOFSMITF_H__
#define __FMRADIOFSMITF_H__

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
typedef enum FmRadioStates_e_
{
    FM_RADIO_STATE__IDLE,
    FM_RADIO_STATE__INIT,
    FM_RADIO_STATE__PLAY,
    FM_RADIO_STATE__MUTE,
    FM_RADIO_STATE__REC,
    FM_RADIO_STATE__SEARCH,
    FM_RADIO_STATE__NUM
} FmRadioStates_e;

typedef struct FmRadioStateData_t_
{
    // TODO: need to handle seek/cancel in record state
    bool bIsFromPlayState;
} FmRadioStateData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t FmRadioFSM_Init(void *pCusData);
void FmRadioFSM_Uninit(StateMachineHandle_t pHandle);
bool FmRadio_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__FMRADIOFSMITF_H__

