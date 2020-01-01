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
* @file    mmi_fmradioapp_3d.h
* @version
* @brief   Fm radio applet 3d view header file
*
*/

#ifndef __MMI_FMRADIOAPP_3D_H__
#define __MMI_FMRADIOAPP_3D_H__

#if defined(__APP_MMI_FM_RADIO__) && defined(__3D_UI_FMRADIO__)

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_common_cfg.h"
#include "mmi_baseapplet.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/
#define FMRADIO_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_FRAME (3)
#define FMRADIO_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_MIN_POS (200)
#define FMRADIO_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_MAX_POS (500)
/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/
MAE_Ret FmRadioCreateMainPanelView3D(HWIN hWin, FmRadioMainPanelViewWdgList_t *pWdgList);
MAE_Ret FmRadioSetMainPanelView3D(HWIN hWin, FmRadioMainPanelViewWdgList_t *pWdgList);
MAE_Ret FmRadioMainPanelUpdateChannelMenu(FmRadioAppData_t *pThis);
void FmRadioMainPaneChannelMenuSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void FmRadioMainPaneChannelMenuFocusCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pReserve);
void FmRadioMainPanelChannelMenuButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void FmRadioMainPanelAnimationDoneCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);
void _FmRadioMainPanelFreeItem(void *pCusHandle, void *pWndData);

#endif /* defined(__APP_MMI_FM_RADIO__) && defined(__3D_UI_FMRADIO__) */

#endif /* __MMI_FMRADIOAPP_3D_H__ */
