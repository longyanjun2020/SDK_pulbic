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
* @file    mmi_calibrationapp_priv.h
* @version
* @brief   Calibration applet private header file
*
*/

#ifndef __MMI_CALIBRATIONAPP_PRIV_H__
#define __MMI_CALIBRATIONAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_baseapplet.h"
#include "mmi_calibrationapp.h"
#include "mmi_common_dialog_id.h"
#include "mmi_common_rai_id.h"
#include "mmi_common_display.h"

#include "mmi_srv_header.h"

#include "mmi_calibrationapp_id.h"
#include "calibrationapp_resource.h"


/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MMI_ENABLE_CALIBRATION_SKEW_VERIFY        (FALSE)

#ifdef __PC_SIMULATOR__

// diff tolerance
//#define MMI_CALIBRATIONAPP_TOP_CENTER_X_DIFF_MAX ((s32)((MMI_CALIBRATIONAPP_CENTER_X-MMI_CALIBRATIONAPP_LEFT_TOP_X)*1.2))
//#define MMI_CALIBRATIONAPP_TOP_CENTER_X_DIFF_MIN ((s32)((MMI_CALIBRATIONAPP_CENTER_X-MMI_CALIBRATIONAPP_LEFT_TOP_X)*0.8))
//#define MMI_CALIBRATIONAPP_TOP_CENTER_Y_DIFF_MAX ((s32)((MMI_CALIBRATIONAPP_CENTER_Y-MMI_CALIBRATIONAPP_LEFT_TOP_Y)*1.2))
//#define MMI_CALIBRATIONAPP_TOP_CENTER_Y_DIFF_MIN ((s32)((MMI_CALIBRATIONAPP_CENTER_Y-MMI_CALIBRATIONAPP_LEFT_TOP_Y)*0.8))
//#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_X_DIFF_MAX ((s32)((MMI_CALIBRATIONAPP_RIGHT_BOTTOM_X-MMI_CALIBRATIONAPP_CENTER_X)*1.2))
//#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_X_DIFF_MIN ((s32)((MMI_CALIBRATIONAPP_RIGHT_BOTTOM_X-MMI_CALIBRATIONAPP_CENTER_X)*0.8))
//#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_Y_DIFF_MAX ((s32)((MMI_CALIBRATIONAPP_RIGHT_BOTTOM_Y-MMI_CALIBRATIONAPP_CENTER_Y)*1.2))
//#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_Y_DIFF_MIN ((s32)((MMI_CALIBRATIONAPP_RIGHT_BOTTOM_Y-MMI_CALIBRATIONAPP_CENTER_Y)*0.8))
#define MMI_CALIBRATIONAPP_TOP_CENTER_X_DIFF_MAX ((s32)((RS_MMI_CALIBRATIONAPP_CENTER_X-RS_MMI_CALIBRATIONAPP_LEFT_TOP_X)*1.2))
#define MMI_CALIBRATIONAPP_TOP_CENTER_X_DIFF_MIN ((s32)((RS_MMI_CALIBRATIONAPP_CENTER_X-RS_MMI_CALIBRATIONAPP_LEFT_TOP_X)*0.8))
#define MMI_CALIBRATIONAPP_TOP_CENTER_Y_DIFF_MAX ((s32)((RS_MMI_CALIBRATIONAPP_CENTER_Y-RS_MMI_CALIBRATIONAPP_LEFT_TOP_Y)*1.2))
#define MMI_CALIBRATIONAPP_TOP_CENTER_Y_DIFF_MIN ((s32)((RS_MMI_CALIBRATIONAPP_CENTER_Y-RS_MMI_CALIBRATIONAPP_LEFT_TOP_Y)*0.8))
#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_X_DIFF_MAX ((s32)((RS_MMI_CALIBRATIONAPP_RIGHT_BOTTOM_X-RS_MMI_CALIBRATIONAPP_CENTER_X)*1.2))
#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_X_DIFF_MIN ((s32)((RS_MMI_CALIBRATIONAPP_RIGHT_BOTTOM_X-RS_MMI_CALIBRATIONAPP_CENTER_X)*0.8))
#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_Y_DIFF_MAX ((s32)((RS_MMI_CALIBRATIONAPP_RIGHT_BOTTOM_Y-RS_MMI_CALIBRATIONAPP_CENTER_Y)*1.2))
#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_Y_DIFF_MIN ((s32)((RS_MMI_CALIBRATIONAPP_RIGHT_BOTTOM_Y-RS_MMI_CALIBRATIONAPP_CENTER_Y)*0.8))
#else

// points in touch touch panel
#define MMI_CALIBRATIONAPP_TP_LEFT_TOP_X ((s32)(TOUCH_CALIBRATION_MIN_X_LOC+((TOUCH_CALIBRATION_MAX_X_LOC-TOUCH_CALIBRATION_MIN_X_LOC)*RS_MMI_CALIBRATIONAPP_LEFT_TOP_X)/RS_MAIN_LCD_WIDTH))
#define MMI_CALIBRATIONAPP_TP_LEFT_TOP_Y ((s32)(TOUCH_CALIBRATION_MIN_Y_LOC+((TOUCH_CALIBRATION_MAX_Y_LOC-TOUCH_CALIBRATION_MIN_Y_LOC)*RS_MMI_CALIBRATIONAPP_LEFT_TOP_Y)/RS_MAIN_LCD_HEIGHT))
#define MMI_CALIBRATIONAPP_TP_CENTER_X ((s32)TOUCH_CALIBRATION_MID_X_LOC)
#define MMI_CALIBRATIONAPP_TP_CENTER_Y ((s32)TOUCH_CALIBRATION_MID_Y_LOC)
#define MMI_CALIBRATIONAPP_TP_RIGHT_BOTTOM_X ((s32)(TOUCH_CALIBRATION_MIN_X_LOC+((TOUCH_CALIBRATION_MAX_X_LOC-TOUCH_CALIBRATION_MIN_X_LOC)*RS_MMI_CALIBRATIONAPP_RIGHT_BOTTOM_X)/RS_MAIN_LCD_WIDTH))
#define MMI_CALIBRATIONAPP_TP_RIGHT_BOTTOM_Y ((s32)(TOUCH_CALIBRATION_MIN_Y_LOC+((TOUCH_CALIBRATION_MAX_Y_LOC-TOUCH_CALIBRATION_MIN_Y_LOC)*RS_MMI_CALIBRATIONAPP_RIGHT_BOTTOM_Y)/RS_MAIN_LCD_HEIGHT))

// diff tolerance
#define MMI_CALIBRATIONAPP_TOP_CENTER_X_DIFF_MAX ((s32)((MMI_CALIBRATIONAPP_TP_CENTER_X-MMI_CALIBRATIONAPP_TP_LEFT_TOP_X)*1.2))
#define MMI_CALIBRATIONAPP_TOP_CENTER_X_DIFF_MIN ((s32)((MMI_CALIBRATIONAPP_TP_CENTER_X-MMI_CALIBRATIONAPP_TP_LEFT_TOP_X)*0.6))
#define MMI_CALIBRATIONAPP_TOP_CENTER_Y_DIFF_MAX ((s32)((MMI_CALIBRATIONAPP_TP_CENTER_Y-MMI_CALIBRATIONAPP_TP_LEFT_TOP_Y)*1.2))
#define MMI_CALIBRATIONAPP_TOP_CENTER_Y_DIFF_MIN ((s32)((MMI_CALIBRATIONAPP_TP_CENTER_Y-MMI_CALIBRATIONAPP_TP_LEFT_TOP_Y)*0.6))
#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_X_DIFF_MAX ((s32)((MMI_CALIBRATIONAPP_TP_RIGHT_BOTTOM_X-MMI_CALIBRATIONAPP_TP_CENTER_X)*1.2))
#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_X_DIFF_MIN ((s32)((MMI_CALIBRATIONAPP_TP_RIGHT_BOTTOM_X-MMI_CALIBRATIONAPP_TP_CENTER_X)*0.6))
#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_Y_DIFF_MAX ((s32)((MMI_CALIBRATIONAPP_TP_RIGHT_BOTTOM_Y-MMI_CALIBRATIONAPP_TP_CENTER_Y)*1.2))
#define MMI_CALIBRATIONAPP_BOTTOM_CENTER_Y_DIFF_MIN ((s32)((MMI_CALIBRATIONAPP_TP_RIGHT_BOTTOM_Y-MMI_CALIBRATIONAPP_TP_CENTER_Y)*0.6))

#endif

#if (MMI_ENABLE_CALIBRATION_SKEW_VERIFY)
#define MMI_CALIBRATIONAPP_CENTER_VERIFY_X      (RS_MMI_CALIBRATIONAPP_LEFT_TOP_X+ (RS_MMI_CALIBRATIONAPP_RIGHT_BOTTOM_X-RS_MMI_CALIBRATIONAPP_LEFT_TOP_X)* 85/200)
#define MMI_CALIBRATIONAPP_CENTER_VERIFY_Y      (RS_MMI_CALIBRATIONAPP_LEFT_TOP_Y+ (RS_MMI_CALIBRATIONAPP_RIGHT_BOTTOM_Y-RS_MMI_CALIBRATIONAPP_LEFT_TOP_Y)*115/200)
#else
#define MMI_CALIBRATIONAPP_CENTER_VERIFY_X      RS_MMI_CALIBRATIONAPP_CENTER_X
#define MMI_CALIBRATIONAPP_CENTER_VERIFY_Y      RS_MMI_CALIBRATIONAPP_CENTER_Y
#endif

#define ABS(a)           ((a)<0?-(a):(a))

#ifdef __MULTI_TOUCH__
#define MMI_CALIBRATIONAPP_MULTITOUCH_BTN_NUM 9
#define MMI_CALIBRATIONAPP_DASHED_LINES_NUM 2
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
* Application structure
*/
typedef struct CalibrationAppData_t_
{
    APPLET_BASE_ELEMENTS;

    IBitmap *pBmp;

    boolean bIsAgain;
    u8 nInputDotsNum;

    Mmi_CalibrationApp_InputPoints_t tInputPoints;
    Mmi_CalibrationApp_InputPoints_t *ptOldCalibrationSetting;

    Mmi_CalibrationApp_StartData_t tStartData;
    CmnAppLaunchRspCbInfo_t tCallerInfo;
#ifdef __MULTI_TOUCH__
    bool bTouched[MMI_CALIBRATIONAPP_MULTITOUCH_BTN_NUM];
    bool bPressed[MMI_CALIBRATIONAPP_MULTITOUCH_BTN_NUM];
    s32 s32MultiTouchCount;
    u32 u32LastX;
    u32 u32LastY;
    IDisplay *pDisplay;
#endif
} CalibrationAppData_t;

typedef enum
{
    CALIBRATION_SPLASH_TEXT = APP_WDG_START,
} CalibrationSplashView_e;

typedef struct
{
	IWidget *pTitleWdg;
	IWidget *pTextWdg;
} SplashWndWdgList_t;

typedef struct
{
    SplashWndWdgList_t tWdgList;
} SplashWndData_t;

typedef enum
{
    CALIBRATION_INPUT_BITMAP = APP_WDG_START,
#ifdef __MULTI_TOUCH__
    CALIBRATION_MULTITOUCH_BTN_01,
    CALIBRATION_MULTITOUCH_BTN_02,
    CALIBRATION_MULTITOUCH_BTN_03,
    CALIBRATION_MULTITOUCH_BTN_04,
    CALIBRATION_MULTITOUCH_BTN_05,
    CALIBRATION_MULTITOUCH_BTN_06,
    CALIBRATION_MULTITOUCH_BTN_07,
    CALIBRATION_MULTITOUCH_BTN_08,
    CALIBRATION_MULTITOUCH_BTN_09,
    CALIBRATION_LOST_COUNT,
#endif
} CalibrationInputView_e;

typedef struct
{
    IWidget *pBitmapWdg;
#ifdef __MULTI_TOUCH__
    IWidget *pMultiTouchBtnWdg01;
    IWidget *pMultiTouchBtnWdg02;
    IWidget *pMultiTouchBtnWdg03;
    IWidget *pMultiTouchBtnWdg04;
    IWidget *pMultiTouchBtnWdg05;
    IWidget *pMultiTouchBtnWdg06;
    IWidget *pMultiTouchBtnWdg07;
    IWidget *pMultiTouchBtnWdg08;
    IWidget *pMultiTouchBtnWdg09;
    IWidget *pLostCountWdg;
#endif
} InputWndWdgList_t;

typedef struct
{
    InputWndWdgList_t tWdgList;
} InputWndData_t;


/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret CalibrationConstructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CalibrationDestructor(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CalibrationStartCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CalibrationSuspendCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CalibrationResumeCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CalibrationKeyPressCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CalibrationTsMoveCB(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CalibrationTsReleaseCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean CalibrationTsCalibrationCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret CalibrationTimeOutCb(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);

//Window manager related function
MAE_Ret CalibrationWndSplashHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret CalibrationWndInputHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

void CalibrationNotifyCallerApFreeFunc(void *pData);
void CalibrationCleanFunc(IBase *pIssuer, u32 nParam);

#endif /* __MMI_CALIBRATIONAPP_PRIV_H__ */
