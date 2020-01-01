/**
* @file    mmi_srv_countdowntimer.h
* @brief   
*          
*/

#ifndef __MMI_SRV_COUNTDOWNTIMER_H__
#define __MMI_SRV_COUNTDOWNTIMER_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_countdowntimersrv.h"

typedef void (*SrvCountDownTimerTickCB)(void *pThis, CountDownTimerSrv_State_e eState, u32 nCountDownSeconds);
typedef void (*SrvCountDownTimerStateChangeCB)(void *pThis, CountDownTimerSrv_State_e eState);

MAE_Ret SrvCountDownTimerSetTickCB(SrvCountDownTimerTickCB pfnCallBack);
MAE_Ret SrvCountDownTimerSetStateChangeCB(SrvCountDownTimerStateChangeCB pfnCallBack);

MAE_Ret SrvCountDownTimerStart(u32 nDuration);

MAE_Ret SrvCountDownTimerStop(void);

MAE_Ret SrvCountDownTimerPause(void);

MAE_Ret SrvCountDownTimerResume(void);

__SLDPM_FREE__ MAE_Ret SrvCountDownTimerGetState(CountDownTimerSrv_State_e *pState, u32 *pCountdownSeconds);

MAE_Ret SrvCountDownTimerGetDuration(u32 *pDuration);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_COUNTDOWNTIMER_H__


