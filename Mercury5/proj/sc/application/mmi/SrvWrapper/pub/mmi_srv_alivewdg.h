/**
* @file    mmi_srv_alivewdg.h
* @brief
*
*
* @author
* @version $Id: mmi_srv_alivewdg.h
*/

#ifndef __MMI_SRV_ALIVEWDG_H__
#define __MMI_SRV_ALIVEWDG_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_alivewdgsrv.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)

//Specific Service ListenerCallBack API
typedef void (*    SrvAlivewdgSingletonDogCB)(void *pThis, AliveWidget_InputEvent_e eEvtType); //AliveWidgetID_Singleton_Dog
typedef void (*    SrvAlivewdgSingletonClockCB)(void *pThis, AliveWidget_InputEvent_e eEvtType); //AliveWidgetID_SingletonClock
typedef void (*    SrvAlivewdgNonSingletonCountDownCB)(void *pThis, AliveWidget_InputEvent_e eEvtType); //AliveWidgetID_NonSingletonDogHouse

/** SrvAlivewdgSetSingletonDogCB
@brief  The interface is use to Set CB which will trigger when Battery level change(MAEBatteryLevel).

@param[out]     pfnLevelChangeCB        SrvAlivewdgSingletonDogCB CB to info owner Battery level change data
*/
void SrvAlivewdgSetSingletonDogCB(SrvAlivewdgSingletonDogCB pfnLevelChangeCB);

/** SrvAlivewdgSetSingletonClock
@brief  The interface is use to Set CB which will trigger when Battery level change(MAEBatteryLevel).

@param[out]     pfnLevelChangeCB        SrvAlivewdgSingletonClockCB CB to info owner Battery level change data
*/
void SrvAlivewdgSetSingletonClock(SrvAlivewdgSingletonClockCB pfnLevelChangeCB);

/** SrvAlivewdgSetNonSingletonCountDown
@brief  The interface is use to Set CB which will trigger when Battery level change(MAEBatteryLevel).

@param[out]     pfnLevelChangeCB        SrvAlivewdgNonSingletonCountDownCB CB to info owner Battery level change data
*/
void SrvAlivewdgSetNonSingletonCountDown(SrvAlivewdgNonSingletonCountDownCB pfnLevelChangeCB);

/** SrvAlivewdgIsBackgroundMusicPlay
@brief   The interface is provided to query FM radio or MPlayer is played

@param[out] pIsMediaPlayer      FM radio or MPlayer i played in background, True is in background.
@param[out] pbIsBackgroundPlay  TRUE if FM radio or Mpalyer is played in background

@retval MAE_RET_SUCCESS         If successful
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvAlivewdgIsBackgroundMusicPlay(boolean *pIsMediaPlayer, boolean *pbIsBackgroundPlay);

/** SrvAlivewdgGetNextState
@brief   The interface is provided AliveWdg to get next state

@param[in]  eId                 ID of AliveWidget (Dog or Clock)
@param[in]  eCurrentState       The state of current widget (EX: Sleep of Dog)
@param[in]  eInputEvent         Input event to change current state
@param[out] pNextState          Return the next state of current widget

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_BAD_PARAM       If input paramter error.
@retval MAE_RET_NOT_READY       If alivewdg Srv is terminated.
@retval MAE_RET_NOT_FOUND       If the state or table is not found.
*/
MAE_Ret SrvAlivewdgGetNextState(AliveWidgetID_e eId,
                                AliveWidget_State_e eCurrentState,
                                AliveWidget_InputEvent_e eInputEvent,
                                AliveWidget_State_e *pNextState);

/** SrvAlivewdgGetBehavior
@brief   The interface is provided AliveWdg to get state behavior

@param[in]  eId                 ID of AliveWidget (Dog or Clock)
@param[in]  eCurrState          The state of current widget (EX: Sleep of Dog)
@param[out] pBehavior           Return the behavior description of given state

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY       If alivewdg Srv is terminated.
*/
MAE_Ret SrvAlivewdgGetBehavior(AliveWidgetID_e eId, AliveWidget_State_e eCurrState, AliveWidget_Behavior_t *pBehavior);

/** SrvAlivewdgUpdateStatus
@brief   The interface is provided AliveWdg to keep information

@param[in]  eId                     ID of AliveWidget (Dog or Clock)
@param[in]  pInfo                   Data to be stored

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           If alivewdg Srv is terminated.
*/
MAE_Ret SrvAlivewdgUpdateStatus(AliveWidgetID_e eId, AliveWidgetSrvInfo_t *pInfo);

/** SrvAlivewdgRestoreStatus
@brief   The interface is provided AliveWdg to retrieve previous information

@param[in]  eId                     ID of AliveWidget (Dog or Clock)
@param[out] pInfo                   Data pointer to return

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_BAD_PARAM           If input parameter error.
*/
MAE_Ret SrvAlivewdgRestoreStatus(AliveWidgetID_e eId, AliveWidgetSrvInfo_t *pInfo);

/** SrvAlivewdgGetInitState
@brief   The interface is provided AliveWdg to get init state and position information

@param[in]  eId                     ID of AliveWidget (Dog or Clock)
@param[out] pInitStateInfo          State Info data pointer to return

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_FOUND           If not found.
*/
MAE_Ret SrvAlivewdgGetInitState(AliveWidgetID_e eId, AliveWidget_Init_State_Info_t *pInitStateInfo);

/** SrvAlivewdgCompareStatePriority
@brief   The interface is provided AliveWdg to compare the priority between two states

@param[in]  eNewState           New state
@param[in]  eCurrentState       Current state

@retval AliveWidget_Priority_Compare_Result_CanNotCompare   can not compare these two states
@retval AliveWidget_Priority_Compare_Result_Lower           eNewState's priority is lower than eCurrentState's
@retval AliveWidget_Priority_Compare_Result_Equal           eNewState's priority is the same as eCurrentState's
@retval AliveWidget_Priority_Compare_Result_Higher          eNewState's priority is higher than eCurrentState's
*/
AliveWidget_Priority_Compare_Result_e SrvAlivewdgCompareStatePriority(AliveWidget_State_e eNewState,
                                                                      AliveWidget_State_e eCurrentState);

/** SrvAlivewdgIsCountDownTimerExist
@brief   The interface is provided to query count down timer exist

@retval TRUE          Count down timer exist.
@retval FALSE         There is no count down timer.
*/
boolean SrvAlivewdgIsCountDownTimerExist(void);

/** SrvAlivewdgSetNotify
@brief   The interface is provided to other AP or service to set notify like missed SMS or low battery to AliveWdgSrv

@param[in]  pInputEvent     Input event type
*/
void SrvAlivewdgSetNotify(AliveWidget_InputEvent_e eInputEvent);

/** SrvAlivewdgIsIdleApActive
@brief   The interface is provided to query if Idle ap is active or not

@retval TRUE    Idle Ap is active
@retval FALSE   Idle Ap is inactive
*/
boolean SrvAlivewdgIsIdleApActive(void);

/** SrvAlivewdgIsPetExist
@brief   The interface is provided to query if Pet exist or not

@retval TRUE    Idle pet exist
@retval FALSE   Idle pet not exist
*/
boolean SrvAlivewdgIsPetExist(void);

/** SrvAlivewdgSetPetExist
@brief   The interface is provided to set Pet exist status

@param[in]  bExist          TRUE for exist; FALSE for inexist
*/
void SrvAlivewdgSetPetExist(boolean bExist);

/** SrvAlivewdgSetIdleApActive
@brief   The interface is provided to Idle AP to set its status.

@param[in]  bActive    TRUE for active; FALSE for inactive
*/
void SrvAlivewdgSetIdleApActive(boolean bActive);

/** SrvAlivewdgIsAliveWidgetCanBeFocused
@brief   The interface is provided to query count down timer exist

@param[in]  eId     ID of AliveWidget (Dog or Clock)

@retval TRUE        Can be focused
@retval FALSE       Can not be focused
*/
boolean SrvAlivewdgIsAliveWidgetCanBeFocused(AliveWidgetID_e eId);

/** SrvAlivewdgGetNextSamePriorityState
@brief   The interface is provided to get next same priority state

@param[in]  eId             ID of AliveWidget (Dog or Clock)
@param[in]  eCurrState      current state

@retval     state for next priority
*/
AliveWidget_State_e SrvAlivewdgGetNextSamePriorityState(AliveWidgetID_e eId,
                                                        AliveWidget_State_e eCurrState);
/** SrvAlivewdgIsIncomingCallExisted
@brief   The interface is provided to query Incoming call existed or not

@retval TRUE          If Incoming call existed
@retval FALSE         If Incoming call is not existed
*/
boolean SrvAlivewdgIsIncomingCallExisted(void);

/** SrvAlivewdgGetLastBGPlayAP
@brief   Get last BG play AP

@retval media player or fm radio
*/
AliveWidget_BG_Play_e SrvAlivewdgGetLastBGPlayAP(void);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__

#endif //__MMI_SRV_ALIVEWDG_H__
/*-----------------------------------------------------*/
