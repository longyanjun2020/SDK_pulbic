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
* @file    mmi_autotestapp_priv.h
* @version
* @brief   Autotest applet private header file
*
*/

#ifndef __MMI_AUTOTESTAPP_PRIV_H__
#define __MMI_AUTOTESTAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#ifdef __FT_AUTO_TEST__

#include "mmi_baseapplet.h"
#include "mmi_calibrationapp.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_rai_id.h"
#include "mmi_common_display.h"

#include "mmi_srv_header.h"

#include "mmi_autotestapp_id.h"
#include "autotestapp_resource.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/
#define MMI_AUTOTEST_CHECK_SETBAND_TIME 60000
#define MMI_AUTOTEST_CHECK_SETBAND_COUNT 6

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
* Application structure
*/
typedef struct AutotestAppData_t_
{
    APPLET_BASE_ELEMENTS;
	u8	u8SplashMode;
	IWidget *pTextWdg1;
	IWidget *pTextWdg2;
	IWidget *pTextInputWdg1;
	IWidget *pTextInputWdg2;
	IWidget *pMenuWdg;
	u32		eBand;
	u8		u8StartMode;
	boolean	bIsCamping;
	boolean	bStartFTTest;
} AutotestAppData_t;

// splach view widget
typedef enum
{
    AUTOTEST_SPLASH_TEXT1 = APP_WDG_START,
	AUTOTEST_SPLASH_TEXT2
} AutotestSplashView_e;

typedef struct
{
	IWidget *pTextWdg1;
	IWidget *pTextWdg2;
} SplashWndWdgList_t;

typedef struct
{
    SplashWndWdgList_t tWdgList;
} SplashWndData_t;

// select band view widget
typedef enum
{
    AUTOTEST_BAND_MENU = APP_WDG_START
} AutotestBandView_e;

typedef struct
{
	IWidget *pMenuWdg;
} BandWndWdgList_t;

typedef struct
{
    BandWndWdgList_t tWdgList;
} BandWndData_t;

// setting view widget
typedef enum
{
    AUTOTEST_SETTING_TEXT1 = APP_WDG_START,
	AUTOTEST_SETTING_TEXT2,
	AUTOTEST_SETTING_TEXT_INPUT1,
	AUTOTEST_SETTING_TEXT_INPUT2
} AutotestSettingView_e;

typedef struct
{
	IWidget *pTextWdg1;
	IWidget *pTextWdg2;
	IWidget *pTextInputWdg1;
	IWidget *pTextInputWdg2;
} SettingWndWdgList_t;

typedef struct
{
    SettingWndWdgList_t tWdgList;
} SettingWndData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret AutotestConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret AutotestDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AutotestStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AutotestStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AutotestSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AutotestResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AutotestKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean AutotestKeyLongPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

//MAE_Ret AutotestTimeOutCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);

//Window manager related function
MAE_Ret AutotestWndSplashHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AutotestWndBandHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AutotestWndSettingHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret AutotestWndFinishHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

#endif // #ifdef __FT_AUTO_TEST__
#endif /* __MMI_AUTOTESTAPP_PRIV_H__ */
