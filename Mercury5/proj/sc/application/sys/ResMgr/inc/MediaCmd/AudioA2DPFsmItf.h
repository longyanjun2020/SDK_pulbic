/**
* @file AudioA2DPFsmItf.h
*
* This header file defines the interfaces of audio states
*
*/

#ifndef __AUDIOA2DPFSMITF_H__
#define __AUDIOA2DPFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "MediaFsm.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum A2dpSubStates_e_
{
    A2DP_STATE__M2_IDLE_BT_IDLE,
    A2DP_STATE__M2_IDLE_BT_STARTING,
    A2DP_STATE__M2_IDLE_BT_PLAY,
    A2DP_STATE__M2_IDLE_BT_STOPPING,
   
    A2DP_STATE__M2_PLAY_BT_IDLE,
    A2DP_STATE__M2_PLAY_BT_STARTING,
    A2DP_STATE__M2_PLAY_BT_PLAY,
    A2DP_STATE__M2_PLAY_BT_STOPPING,

    A2DP_STATE__M2_STOPPING_BT_IDLE, 

    A2DP_STATE__NUM
} A2dpSubStates_e;



typedef bool (*Audio_A2dpState)(StateMachineHandle_t pHandle, u16 uStateId, void *pCusData, void *pEvt, void *pRetParam);

typedef struct A2dpStateData_t_
{
    bool bStarted;
    u32 uState;
} A2dpStateData_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

__SLDPM_FREE__ bool Audio_A2dpHandleEvt(StateMachineHandle_t pHandle, u16 uStateId, void *pCusData, void *pEvt, void *pRetParam);

#endif //__AUDIOFSMITF_H__

