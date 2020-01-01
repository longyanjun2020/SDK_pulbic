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
* @file    mmi_beautyclksettingapp_priv.h
* @version
* @brief   Beauty clock setting applet private header file
*
*/

#ifndef __MMI_BEAUTYCLKSETTINGAPP_PRIV_H__
#define __MMI_BEAUTYCLKSETTINGAPP_PRIV_H__

#if defined(__MMI_BEAUTY_CLK_APP__)

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_beautyclksettingapp.h"

#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"
#include "mmi_common_cfg.h"
#include "mmi_wdg_headers.h"
#include "mmi_wdg_glmagnifywidget.h"
#include "mae_animation.h"

#include "mmi_beautyclksettingapp_id.h"
#include "BeautyClkSettingApp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

#define BCS_FILE_STR_LENGTH     32

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef enum
{
	MNU_BCS_SELECT_MENU_BEGIN = 0,
	MNU_BCS_SELECT_MENU_KEYGUARD = MNU_BCS_SELECT_MENU_BEGIN,
	MNU_BCS_SELECT_MENU_EXIT,
	MNU_BCS_SELECT_MENU_END,
}BeautyClkSettingSelectMenuId_e;

typedef enum
{
	BCS_EFFECT_TYPE_NONE = 0,
	BCS_EFFECT_TYPE_SWITCH_ANIMATION,
	BCS_EFFECT_TYPE_OPTION_ANIMATION,
} BCSEffectType_e;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    IImage *pImage;
#ifdef __3D_UI_KEYGUARD_BEAUTY_CLK__
    boolean bKeyguardEnabled;
    boolean bOptionMenuEnabled;
#endif

    IWidget *pMagnifyWdg;
	MAE_DateTime_t sTime;
	MAE_DateTime_t sShowTime;
    BeautyClkSettingSelectMenuId_e eSelectMenuId;
    IAnimation *pAnimation;
    BCSEffectType_e eEffectType;
    Pos_t tCurrentSwitchPos;
    Pos_t tCurrentOptionPos;
    boolean bIsSuspend;
    boolean bDecodeFail;
    boolean bIsReceiveKeypadFromCoreSrv;
	SetPhoneTimeFormat_e ePhoneTimeFormat;    
} BeautyClkSettingAppData_t;

typedef struct
{
    IWidget *pBGWdg;
    IWidget *pClothEffectWdg;

    IWidget *pInfoBGWdg;
    IWidget *pTimeWdg;
    IWidget *pI12HWdg;

    IWidget *pIdleInfoCntr;
    IWidget *pBtnWdg;
    IWidget *pSwitchCntr;
    IWidget *pSwitchWdg;
    IWidget *pSwitchBGWdg;
    IWidget *pSwitchTitleWdg;
    IWidget *pSwitchIconWdg;
    IWidget *pSwitchOnWdg;
    IWidget *pSwitchOffWdg;
    IWidget *pExitBGWdg;
    IWidget *pExitTitleWdg;
}BeautyClkSettingMainWndWdgList_t;

typedef struct
{
    BeautyClkSettingMainWndWdgList_t tWdgList;
}BeautyClkSettingMainWndData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret BCSAppDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean BCSAppStartCb(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean BCSAppSuspendCb(IApplet* pApplet,MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean BCSAppResumeCb(IApplet* pApplet,MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean BCSAppKeyPressCb(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean BCSAppTSCb(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret BCSAppWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret BCSAppWndSelectMenuHdl(void* pCusHandle, const WindowMsg_t *pWndMsg, void* pWndData, u32 nWndInitParam);

#endif //__MMI_BEAUTY_CLK_APP__
#endif /* __MMI_BEAUTYCLKSETTINGAPP_PRIV_H__ */
