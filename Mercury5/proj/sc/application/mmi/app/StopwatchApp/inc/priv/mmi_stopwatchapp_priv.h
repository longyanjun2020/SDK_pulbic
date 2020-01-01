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
* @file    mmi_stopwatchapp_priv.h
* @version
* @brief   Stopwatch applet private header file
*
*/

#ifndef __MMI_STOPWATCHAPP_PRIV_H__
#define __MMI_STOPWATCHAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_stopwatchapp.h"
#include "mmi_wdg_itf_dynamicmenu.h"

#ifdef __MMI_BIDI_UI__
#include "mmi_mae_text_util.h"
#endif //__MMI_BIDI_UI__

#include "mmi_stopwatchapp_id.h"

#include "stopwatchapp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

//#define __STOPWATCH_APP_ROLEX_STYLE__
#define STOPWATCH_MAX_SECONDS 86399
#define STOPWATCH_MAX_TICK 99

/*=============================================================*/
// Data type definition
/*=============================================================*/


typedef enum
{
    STOPWATCH_STATE_READY = 0,
    STOPWATCH_STATE_PAUSE,
    STOPWATCH_STATE_RUN

} StopwatchState_e;

typedef struct
{
    IWidget *pListInfoCntr;
    IWidget *pCountWdg;
    IWidget *pTimerWdg;
    IWidget *pMenuWdg;
    IWidget *pMenuItemTextWdg;
    IWidget *pMenuItemTimerWdg;
#ifdef __STOPWATCH_APP_ROLEX_STYLE__
    IWidget *pFuncBtnWdg;
    IWidget *pActBtnWdg;
#endif
}StopwatchWndWdgList_t;

typedef struct
{
    StopwatchWndWdgList_t tWdgList;
    RGBColor_t rgbListItemTextClr;
    RGBColor_t rgbTimeInfoCrl;
    u32 nRowsPerPage;
    u32 nStartTimeInSec;
    u16 nStartTick;
    u32 nPauseTimeInSec;
    u16 nPauseTick;
    u32 nCurrTimeInSec;
    u16 nCurrTick;
    u32 nAccTimeInSec;
    u8  nRecords;
    boolean bPaused;
    boolean bReachedMax;
    boolean bStopped;
    StopwatchState_e eState;
} StopwatchWndData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
    TimerFomatData_t pRecordItems[MAX_STOPWATCH_ITEM_NUM]; // Save the Record Items
    WidgetHandler_t tSoftkeyHdlData;
} StopwatchAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret StopwatchDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean StopwatchStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean StopwatchSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean StopwatchResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean StopwatchKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean StopwatchStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret StopwatchWndListMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret StopwatchWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret StopwatchWndConvert(void *pCusHandle, void *pWndData);
void StopwatchTickCb(void *pUser);
void StopwatchFreeTimerData(void *pData, IBase *pOwner);
void StopwatchMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
boolean StopwatchMenuWidgetHandler(StopwatchAppData_t* pThis, MAE_EventId nEvt, u32 nParm1, u32 nParm2);
void StopwatchListWdgHdlFree(void *pData);
#ifdef __STOPWATCH_APP_ROLEX_STYLE__
void StopwatchFunctionButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nParam, IWidget *pWidget);
void StopwatchActionButtonClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nParam, IWidget *pWidget);
#endif

#endif /* __MMI_STOPWATCHAPP_PRIV_H__ */
