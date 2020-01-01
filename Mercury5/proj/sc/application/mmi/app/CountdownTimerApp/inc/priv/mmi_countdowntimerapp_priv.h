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
* @file    mmi_countdowntimerapp_priv.h
* @version
* @brief   CountdownTimer applet private header file
*
*/

#ifndef __MMI_COUNTDOWNTIMERAPP_PRIV_H__
#define __MMI_COUNTDOWNTIMERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_srv_header.h"
#include "melody_data.h"

#include "mmi_countdowntimerapp_id.h"
#include "countdowntimerapp_resource.h"
#include "mmi_launcher_filemanager.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

// Widget list for set time
typedef struct
{
    IWidget *pSetTimeWdg;
#ifndef __COUNTDOWNTIMERAPP_SMALLROM__
    IWidget *pHourTextWdg;
    IWidget *pMinTextWdg;
    IWidget *pSecTextWdg;
#ifdef __IFONE_STYLE_MMI_COUNTDOWN_TIMER__
    IWidget *pStartRingTextWdg;
    IWidget *pRingNameTextWdg;
    IWidget *pStartButtonWdg;
    IWidget *pStartRingWdg;
#endif
#else
    IWidget *pTextWdg;
#endif
} CountdownTimerSetTimeWdgList_t;

// Widget list for count down
typedef struct
{
    IWidget *pTextWdg;
#ifdef __IFONE_STYLE_MMI_COUNTDOWN_TIMER__
    IWidget *pStartRingTextWdg;
    IWidget *pStopButtonWdg;
    IWidget *pStartRingWdg;
    IWidget *pRingNameTextWdg;
#endif
} CountdownTimerCountdownWdgList_t;

// Set time window data
typedef struct
{
    CountdownTimerSetTimeWdgList_t tWdgList;
} CountdownTimerSetTimeWndData_t;

// Conut down window data
typedef struct
{
    CountdownTimerCountdownWdgList_t tWdgList;
} CountdownTimerCountdownWndData_t;

#ifdef __IFONE_STYLE_MMI_COUNTDOWN_TIMER__
typedef struct
{
    IWidget *pIMenuWdg;
} CountdownTimerSetRingtoneWdgList_t;

typedef struct
{
    CountdownTimerSetRingtoneWdgList_t tWdgList;
    MAE_WChar *pURL;
} CountdownTimerSetRingtoneWndData_t;
#endif

/**
 * Application structure
 */
typedef struct
{
    APPLET_BASE_ELEMENTS;

    u32 nCountdownDuration;

    u8 nInputHour;
    u8 nInputMin;
    u8 nInputSec;

    CountDownTimerSrv_State_e eCountDownTimerSrvState;
    u32 nCountDownTimerSrvSeconds;

#ifdef __IFONE_STYLE_MMI_COUNTDOWN_TIMER__
    MAE_WChar *pCountdownRingToneUrl;
    WidgetHandler_t SetViewRingNameTextWidgetHandler;
    WidgetHandler_t CountViewRingNameTextWidgetHandler;
    WidgetHandler_t SetViewStartRingTextWidgetHandler;
    WidgetHandler_t CountViewStartRingTextWidgetHandler;
#endif
} CountdownTimerAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
boolean CountdownTimerStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CountdownTimerStopCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CountdownTimerKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

//Window manager related function
MAE_Ret CountdownTimerSetTimeWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CountdownTimerCountdownWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#ifdef __IFONE_STYLE_MMI_COUNTDOWN_TIMER__
MAE_Ret CountdownTimerSetRingtoneWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
#endif // __IFONE_STYLE_MMI_COUNTDOWN_TIMER__

//CountdownService related Function
void CountdownTimerTickCB(void *pThis, CountDownTimerSrv_State_e eState, u32 nCountDownSeconds);
void CountdownTimerStateChangeCB(void *pThis, CountDownTimerSrv_State_e eState);

#endif /* __MMI_COUNTDOWNTIMERAPP_PRIV_H__ */
