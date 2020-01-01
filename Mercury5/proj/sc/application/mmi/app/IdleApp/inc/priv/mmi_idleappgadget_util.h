////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_idleappgadget_util.h
* @version
* @brief   Idle applet file for gadget
*
*/

#ifndef __MMI_IDLEAPPGADGET_UTIL_H__
#define __MMI_IDLEAPPGADGET_UTIL_H__

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)

#include "mmi_idleapp_priv.h"

MAE_Ret IdleCreateFmNoticeDialog(MMI_IDLEAPP *pThis, u32 nTextId);
void IdleMediaNameLayoutChange(MMI_IDLEAPP *pThis);
void IdleShortcutBarIconEventCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);
void IdleShortcutBarIconMoveOutCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pShortcutMoveData, IWidget *pWidget);
void IdleShortcutButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void IdleCreateDesktopWdgByOrder(MMI_IDLEAPP *pThis);
void IdleUpdateOperatorName(MMI_IDLEAPP *pThis, u8 nDualID, MAE_WChar *pName);
void IdleUpdateShortcutButtonStatus(MMI_IDLEAPP *pThis,boolean bIsPlayAnimation);
void IdleUpdateShortcutBarDogIcon(MMI_IDLEAPP *pThis);
void IDLEAPP_AnimationEndCB(void * param1);

MAE_Ret IdleRegisterAliveWidgetCb(IWidget *pIWidget);
MAE_Ret IdleDeregisterAliveWidgetCb(IWidget *pIWidget);
MAE_Ret IdleRegisterDesktopWidgetCb(IWidget *pIWidget, u32 nItemId);
MAE_Ret IdleDeregisterDesktopWidgetCb(IWidget *pIWidget, u32 nItemId);
void IdleAliveWidgetTouchReleaseInCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pShortMoveData, IWidget *pIWidget);
void IdleAliveWidgetTouchReleaseOutCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pShortMoveData, IWidget *pIWidget);
void IdleAliveWidgetTouchMoveToTopCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pShortMoveData, IWidget *pIWidget);
void IdleAliveWidgetLaunchSMSInboxCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
void IdleAliveWidgetLaunchCallLogCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
void IdleAliveWidgetLaunchMediaPlayerCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
void IdleAliveWidgetLaunchFMRadioCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
void IdleAliveWidgetLaunchTimeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
void IdleDesktopWidgetTouchReleaseInCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pMoveData, IWidget *pWidget);
void IdleDesktopWidgetTouchReleaseOutCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pMoveData, IWidget *pWidget);
void IdleDesktopWidgetTouchReleaseCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pMoveData, IWidget *pWidget);
void IdleDesktopWidgetTouchMoveToTopCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, DesktopWdg_t *pDesktopWdg, IWidget *pWidget);
void IdleDesktopWidgetLaunchAppCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, DesktopWdg_LaunchApp_Info_t *pLaunchApInfo, IWidget *pWidget);
void IdleMediaPlayerDesktopWidgetLaunchAdjustVolumeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
void IdleFMRadioDesktopWidgetLaunchAdjustVolumeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
void IdleFMRadioDesktopWidgetLaunchAirplaneModeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
void IdleFMRadioDesktopWidgetLaunchPlugHeadsetCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
void IdleDesktopWidgetFlipEventCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

#if defined(__3D_UI_IDLE_GADGETBAR__)
void IdleDesktopWidgetLaunchAnimationDoneCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);
void IdleResumeAnimationDoneCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);
#endif

#endif /* __GADGETS_MMI__ */

#endif /* __MMI_IDLEAPPGADGET_UTIL_H__ */
