/**
* @file mmi_idlepedometer_util.h
* @brief   xxxx
* @version $Id:
*/
#ifndef __MMI_IDLEPEDOMETER_UTIL_H__
#define __MMI_IDLEPEDOMETER_UTIL_H__

#ifdef __NATIVE_GAME_MMI_PEDOMETER__
#include "mmi_idleapp_priv.h"
#include "mmi_pedometerapp.h"


MAE_Ret IdlePedometerCreateButtonWidget(MMI_IDLEAPP *pThis, IWidget **ppIButtonWidget, u32 nUnPressedImgID, u32 nPressedImgID, IDataModel **ppButtonDataMdl);
void IdlePedometerFreeButtonModel(void *pUserData, IBase *pOwner);
void IdlePedometerButtonClickCB(void *pUserData, WidgetEvtCode_t nEvtCode, IModel *pModelPtr, IWidget *pWidget);
MAE_Ret IdleCreatePedometerNoticeDialog(MMI_IDLEAPP *pThis);
void IdlePedometerNoticeDialogTimerCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
void IdleGoalReachCB(void *pUserData);
void IdleSensorStatusChangeCB(void *pUserData);

MAE_Ret IdleCreatePedometerWdg(MMI_IDLEAPP *pThis);
#endif /* __NATIVE_GAME_MMI_PEDOMETER__ */

#endif /* __MMI_IDLEPEDOMETER_UTIL_H__ */

