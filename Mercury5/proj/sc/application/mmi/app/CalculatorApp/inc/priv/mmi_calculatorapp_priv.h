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
 * @file    mmi_calculatorapp_priv.h
 * @version
 * @brief   calculator app
 */

#ifndef __MMI_CALCULATORAPP_PRIV_H__
#define __MMI_CALCULATORAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_calculatorapp.h"
#include "mmi_wdg_headers.h"

#include "mmi_calculatorapp_id.h"
#include "calculatorapp_resource.h"


/*=============================================================*/
// Macro definition
/*=============================================================*/

#define CALCULATORAPP_MAX_DISPLAY_DIGITS 18
#define CALCULATORAPP_MAX_INPUT_DIGITS 10
#define CALCULATORAPP_MAX_LARGET_DIGITS 8
#define CALCULATORAPP_PRECISION_STRING L"%s%.10g"  //although max input digits is 10, so there are 8 digits at most after dot.( ex:0.99999999)  Temporary add a %s in front of the double due to 8byte alignement problem

//#define __CALCULATORAPP_ROLEX_STYLE__
/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct
{
    // Widgets for common usage
    IWidget *pResultTextWidget;
    IWidget *pOperand1TextWidget;
    IWidget *pOperatorTextWidget;
    IWidget *pResultBgBitmapWidget;

    // Widgets for touch UI
    IWidget *pOperandListWidget;
    IWidget *pOperandButtonWidget;
    IWidget *pOperatorListWidget;
    IWidget *pOperatorButtonWidget;

    // Widgets for No-touch UI
    IWidget *pOperatorAdditionButtonWidget;         // Button for Addition
    IWidget *pOperatorSubstractionButtonWidget;     // Button for Substraction
    IWidget *pOperatorMultiplicationButtonWidget;   // Button for Multiplication
    IWidget *pOperatorDivisionButtonWidget;         // Button for Division
    IWidget *pOperatorEqualButtonWidget;            // Button for Equal
    IWidget *pOperatorDotTextWidget;                // Text for Dot
    IWidget *pOperatorPercentTextWidget;            // Text for Percent
}CalculatorViewWdgList_t;

typedef struct
{
    CalculatorViewWdgList_t tWdgList;
    double nOperand1;
    double nOperand2;
    double nResult;
    boolean bInvalid;
    boolean bLastIsPercent;
    u32 nOperatorID;
    u32 nCurrentState;
    MAE_WChar strCurrentInput[CALCULATORAPP_MAX_DISPLAY_DIGITS+1];
#ifdef __MMI_SOFTKEY_AS_CLEAR__
    boolean bRSKAsClear;
#endif
}CalculatorWndData_t;

typedef enum
{
    CALCULATOR_STATE_ACTIVE = 0,
    CALCULATOR_STATE_CALCULATE,
    CALCULATOR_STATE_SETOPERAND1,
    CALCULATOR_STATE_SETOPERAND2,
    CALCULATOR_STATE_SETOPERATOR
}CalculatorState_e;


typedef struct
{
    APPLET_BASE_ELEMENTS;
} CalculatorAppData_t;

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret CalculatorWndMainHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalculatorWndCreateMain(void *pCusHandle, void *pWndData, u32 nWndInitParam);
boolean CalculatorStartCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CalculatorKeyPressCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CalculatorKeyLongPressCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
boolean CalculatorKeyReleaseCb(IApplet *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);

#ifdef __TOUCH_SCREEN_MMI__
void CalculatorOperandMenuSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pFocusInfo, IWidget *pWidget);
void CalculatorOperatorMenuSelectCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pFocusInfo, IWidget *pWidget);
#endif
#ifdef __CALCULATORAPP_ROLEX_STYLE__
void CalculatorTextWidgetDataChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nParam, IWidget *pWidget);
#endif

#endif /* __MMI_CALCULATORAPP_PRIV_H__ */
