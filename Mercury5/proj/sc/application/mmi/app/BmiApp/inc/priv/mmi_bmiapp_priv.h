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
* @file    mmi_bmiapp_priv.h
* @version
* @brief   BMI applet private header file
*
*/
#ifndef __MMI_BMIAPP_PRIV_H__
#define __MMI_BMIAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_srv_clock.h"
#include "mmi_common_vtm.h"
#include "mmi_common_dialog.h"
#include "mmi_common_rai_id.h"
#include "mmi_bmiapp_id.h"
#include "bmiapp_resource.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MAX_BMI_RECORD_STR_LEN (25)
#define MAX_BMI_FLOT_STR_LEN (20)
#define MIN_BMI_POSITION (12)
#define MAX_BMI_POSITION (30)
#define THIN_BMI_VALUE (18)
#define FAT_BMI_VALUE (24)
#define CENTER_BMI_POSITION ((MAX_BMI_POSITION + MIN_BMI_POSITION)/2)
#define BMI_POSTION(b) (((b) * 100 - CENTER_BMI_POSITION * 100) * RS_BMI_BAR_WIDTH / ((MAX_BMI_POSITION - MIN_BMI_POSITION) * 100))
#define MIN_BMI_HEIGHT (0)
#define MAX_BMI_HEIGHT (300)
#define VALID_BMI_HEIGHT(h) ((MIN_BMI_HEIGHT < h) && (MAX_BMI_HEIGHT > h))
#define MIN_BMI_WEIGHT (0)
#define MAX_BMI_WEIGHT (300)
#define VALID_BMI_WEIGHT(w) ((MIN_BMI_WEIGHT < w) && (MAX_BMI_WEIGHT > w))
#define BMI_DIALOG_TIMER (1000)
#define MAX_BMI_LOG_NUMBER (100)


/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    BMI_CAL_STATE_EMPTY,
    BMI_CAL_STATE_INPUT_ONE,
    BMI_CAL_STATE_INPUT_TWO,
    BMI_CAL_STATE_RESULT
} BmiCalculatorState_e;

enum
{
    BMI_OPTION_VIEW,
    BMI_OPTION_DELETE,
    BMI_OPTION_DELETE_ALL
}BmiOptionRecord_e;

typedef struct
{
    double          dbHeight;
    double          dbWeight;
    double          dbBmi;
    MAE_DateTime_t  tTime;
} BmiLog_t;

typedef struct
{
    u8              nCount;
    BmiLog_t        pData[MAX_BMI_LOG_NUMBER];
} BmiLogData_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
} BmiAppData_t;

typedef struct
{
    IWidget         *pITitleWdg;
    IWidget         *pIHeightTextWdg;
    IWidget         *pIHeightValueTextWdg;
    IWidget         *pIInputHeightWdg;
    IWidget         *pIWeightTextWdg;
    IWidget         *pIWeightValueTextWdg;
    IWidget         *pIInputWeightWdg;
    IWidget         *pIBmiLimitTextWdg;
    IWidget         *pIJudgementTextWdg;
    IWidget         *pIBmiValueTextWdg;
    IWidget         *pIValueBgImageWdg;
    IWidget         *pIValueImageWdg;
}BmiCalcWdgList_t;

typedef struct
{
    TextInfo                tHeightTextInfo;
    TextInfo                tWeightTextInfo;
    BmiCalculatorState_e    eCalState;
    BmiCalcWdgList_t        tCalcWdgList;
    double                  dbWeight;
    double                  dbHeight;
    double                  dbBmi;
    BmiLogData_t    *pLog;
}CalcWndData_t;

typedef struct
{
    MenuWdgList_t   tMenuWdgList;
    MenuData_t      tMenuData;
    MenuCB_t        tMenuCB;
    u32             nListHightLightIndex;
    u32             nListFirstIndex;
}HistoryWndData_t;

typedef struct
{
    OptionMenuWdgList_t tOptionMenuWdgList;
    OptionMenuData_t    tOptionMenuData;
    OptionMenuCB_t      tOptionMenuCB;
}OptionWndData_t;

typedef struct
{
    TextInfo                tHeightTextInfo;
    TextInfo                tWeightTextInfo;
    BmiCalculatorState_e    eCalState;
    BmiCalcWdgList_t        tCalcWdgList;
}ViewerWndData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** BmiStartCB
* @brief        Applet start function(when receive MAE_EVT_APP_START)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean BmiStartCB
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);

/** BmiStopCB
* @brief        Applet stop function(when receive MAE_EVT_APP_STOP)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean BmiStopCB
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);
boolean BmiSuspendCB
(
 IApplet *pApplet,
 u32     nEvt,
 u32     nParam1,
 u32     nParam2
 );

/** BmiKeyPressCB
* @brief        Handle key press function(when receive MAE_EVT_KEY_PRESS)
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE                Event is handled
* @retval       FALSE               Event needs to pass to other handle function
*
*/
boolean BmiKeyPressCB
(
    IApplet *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);

/** BmiCalcWndHdl
* @brief        Calculator window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret BmiCalcWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

/** BmiHistoryWndHdl
* @brief        History window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret BmiHistoryWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

/** BmiOptionWndHdl
* @brief        Optionmenu window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret BmiOptionWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

/** BmiViewerWndHdl
* @brief        Viewer window handle function
*
* @param[in]    pCusHandle
* @param[in]    pWndMsg             Window action and window id
* @param[in]    pWndData            Window data
* @param[in]    nWndInitParam       The init param will be transferred to pfnWndFunc():WND_CREATE
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret BmiViewerWndHdl
(
    void                *pCusHandle,
    const WindowMsg_t   *pWndMsg,
    void                *pWndData,
    u32                 nWndInitParam
);

/** ShowInfoDlgCB
* @brief        Information dialog callback function
*
* @param[in]    pData
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret ShowInfoDlgCB
(
    void *pData
);

/** BmiConfirmDialogDeleteCB
* @brief        Callback function when press yes on delete file dialog
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       MAE_Ret             Success.
* @retval       other               Failed.
*
*/
MAE_Ret BmiConfirmDialogDeleteCB
(
    void   *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);

/** BmiConfirmDialogDeleteAllCB
* @brief        Callback function when press yes on delete all file dialog
*
* @param[in]    pApplet             The pointer of Applet
* @param[in]    nEvt                Event
* @param[in]    nParam1             First parameter
* @param[in]    nParam2             Second parameter
*
* @retval       TRUE
* @retval       FALSE
*
*/
MAE_Ret BmiConfirmDialogDeleteAllCB
(
    void    *pApplet,
    u32     nEvt,
    u32     nParam1,
    u32     nParam2
);

/** BmiCalcHeightTextChangeCb
* @brief        Callback function when input height change
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pTextInfo       Text information in input widget
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void BmiCalcHeightTextChangeCb
(
    void            *pApplet,
	void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    TextInfo        *pTextInfo,
    IWidget         *pWidget
);

/** BmiCalcWeightTextChangeCb
* @brief        Callback function when input weight change
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pTextInfo       Text information in input widget
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void BmiCalcWeightTextChangeCb
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    TextInfo        *pTextInfo,
    IWidget         *pWidget
);


/** BmiCalcHeightTextFocusChangeCb
* @brief        Callback function when input Height focus change
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    bFocus            focus or not
* @param[in]    pWidget          The pointer of Input widget
*
* @retval       None
*
*/
void BmiCalcHeightTextFocusChangeCb
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    boolean         bFocus,
    IWidget         *pWidget
);


/** BmiCalcWeightTextFocusChangeCb
* @brief        Callback function when input weight focus change
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    bFocus            focus or not
* @param[in]    pWidget          The pointer of Input widget
*
* @retval       None
*
*/
void BmiCalcWeightTextFocusChangeCb
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    boolean         bFocus,
    IWidget         *pWidget
);

/** BmiHistoryMenuSelectCB
* @brief        Callback function select menu
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void BmiHistoryMenuSelectCB
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    HistoryInfo_t   *pHistoryInfo,
    IWidget         *pWidget
);

/** BmiHistoryMenuOnFocusCB
* @brief        Callback function for on focus event
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pFocusInfo      Focus information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void BmiHistoryMenuOnFocusCB
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    FocusInfo_t     *pFocusInfo,
    IWidget         *pWidget
);

/** BmiHistoryMenuSoftkeyCB
* @brief        Callback function for press softkey
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void BmiHistoryMenuSoftkeyCB
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    HistoryInfo_t   *pHistoryInfo,
    IWidget         *pWidget
);

/** BmiHistoryMenuBackCB
* @brief        Callback function for press back
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void BmiHistoryMenuBackCB
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    HistoryInfo_t   *pHistoryInfo,
    IWidget         *pWidget
);

/** BmiOptionMenuLayer1SoftkeySelectCB
* @brief        Callback function for layer 1 menu softkey select event
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void BmiOptionMenuLayer1SoftkeySelectCB
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    HistoryInfo_t   *pHistoryInfo,
    IWidget         *pWidget
);

/** BmiOptionMenuSoftkeyActCB
* @brief        Callback function for option menu softkey act event
*
* @param[in]    pUsrData        The pointer of Applet
* @param[in]    nEvtCode        Event
* @param[in]    pHistoryInfo    History information
* @param[in]    pWidget         The pointer of Input widget
*
* @retval       None
*
*/
void BmiOptionMenuSoftkeyActCB
(
    void            *pApplet,
    void            *pUsrData,
    WidgetEvtCode_t nEvtCode,
    HistoryInfo_t   *pHistoryInfo,
    IWidget         *pWidget
);

/** BmiHistoryMenuFreeItem
* @brief        Callback function to free log item
*
* @param[in]    pItemDataPtr        Pointer to Data
* @param[in]    pWndHandle          Window handle
* @param[in]    eItemType           Item type
*
* @retval       None
*
*/
void BmiHistoryMenuFreeItem
(
    WdgDynamicMenuItemPtr_t    *pItemDataPtr,
    HWIN hWin,
    WdgMenuItemType_e          eItemType
 );

/** BmiHistoryMenuGetItem
* @brief        Callback function to get log item
*
* @param[in]    pItemDataPtr        Pointer to Data
* @param[in]    pWndHandle          Window handle
* @param[in]    eItemType           Item type
*
* @retval       None
*
*/
void BmiHistoryMenuGetItem
(
    WdgDynamicMenuItemPtr_t    *pItemDataPtr,
    HWIN hWin,
    WdgMenuItemType_e          eItemType,
    IWidget                     *pMenu,
    u32                         u32Index
);

#endif /* __MMI_BMIAPP_PRIV_H__ */

