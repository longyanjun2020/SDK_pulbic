#ifdef __TTS__
#ifndef __MMI_TTSSRV_PLAY_SM__H__
#define __MMI_TTSSRV_PLAY_SM__H__

#include "StateMachineItf.h"

StateMachineHandle_t TtsSrvTextStateMachine_Create(void *pCusData);
void TtsSrvTextStateMachine_Destroy(StateMachineHandle_t hFSM);
bool TtsSrvTextStateMachine_IsInStableState(StateMachineHandle_t hFSM);
bool TtsSrvTextStateMachine_IsInIdleState(StateMachineHandle_t hFSM);
bool TtsSrvTextStateMachine_IsInPlayState(StateMachineHandle_t hFSM);
#endif/* __MMI_TTSSRV_PLAY_SM__H__ */
#endif/* __TTS__ */
