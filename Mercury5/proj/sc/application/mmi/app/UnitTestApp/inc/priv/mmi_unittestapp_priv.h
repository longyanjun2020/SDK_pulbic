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
* @file    mmi_unittestapp_priv.h
* @version
* @brief   Unit test applet private header file
*
*/

#ifndef __MMI_UNITTESTAPP_PRIV_H__
#define __MMI_UNITTESTAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"

#include "mmi_wdg_headers.h"

#include "ut_def.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    UNITTESTAPP_WND_AUTO = 1,//WND_ID_APP_BASE,
	UNITTESTAPP_WND_MENU,
	UNITTESTAPP_WND_LIST,
	UNITTESTAPP_WND_SUBLIST,
	UNITTESTAPP_WND_INPUT,
	UNITTESTAPP_WND_RESULT
} UnitTestAppWndId_e;

typedef enum
{
    UNITTEST_OPT__SINGLE_CASE = 0,
    UNITTEST_OPT__SINGLE_SUITE,
	UNITTEST_OPT__ALL_SUITE,	
	UNITTEST_OPT__CUSTOM
} UnitTestOption_e;

typedef struct
{
    UnitTestOption_e eOption;
    u32 nSuiteIdx;
    u32 nSuiteNum;
    u32 nCaseIdx;
    u32 nCaseNum;
    u32 nRepeatTimes;
} UnitTestParams_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    IWidget *pIInputWdg;
    u32      nTestSuiteIdx;
    u32      nTestSuiteNum;
    UnitTestParams_t tTestParam;
} MMI_UNITTESTAPP;

typedef struct
{
    u32 nSuiteIdx;
    u32 nCaseNum;
} UnitTestSubListWndData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
boolean UnitTestAppStartCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean UnitTestAppPressCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean UnitTestAppStopCB(IApplet* pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret UnitTestAppWndAutoHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret UnitTestAppWndMenuHdl(void *pCusHandle,const WindowMsg_t *pWndMsg,void *pWndData,u32 nWndInitParam);
MAE_Ret UnitTestAppWndListHdl(void *pCusHandle,const WindowMsg_t *pWndMsg,void *pWndData,u32 nWndInitParam);
MAE_Ret UnitTestAppWndSubListHdl(void *pCusHandle,const WindowMsg_t *pWndMsg,void *pWndData,u32 nWndInitParam);
MAE_Ret UnitTestAppWndInputHdl(void *pCusHandle,const WindowMsg_t *pWndMsg,void *pWndData,u32 nWndInitParam);
MAE_Ret UnitTestAppWndResultHdl(void *pCusHandle,const WindowMsg_t *pWndMsg,void *pWndData,u32 nWndInitParam);
void    UnitTestAppDoNextTest(MMI_UNITTESTAPP *pThis);
void _UnitTestMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
void _UnitTestMenuGetItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
#endif /* __MMI_UNITTESTAPP_PRIV_H__ */
