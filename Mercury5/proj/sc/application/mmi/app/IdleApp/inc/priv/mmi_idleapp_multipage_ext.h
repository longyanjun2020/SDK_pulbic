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
* @file mmi_idleapp_multipage_ext.h
* @brief
* @version
*/
#ifndef __MMI_IDLEAPP_MULTIPAGE_EXT_H__
#define __MMI_IDLEAPP_MULTIPAGE_EXT_H__

#if defined(__3D_UI_IDLE_MULTIPAGE__)
#include "mmi_idleapp_priv.h"
#include "mmi_launcher_worldclock.h"

#define __PAGE_ANIMATION_EXT__

#define DESKTOP_OBJECT_RESUME_DELAY 5
#define PAGECHANGE_BORDER_WIDTH     30
#define PAGE_CHANGE_TIMER           500
#define NEXT_PAGE_CHANGE_TIMER      1000
#define CALC_HANDOFF_FOCUS_TIMER    300
#define DRAG_DESKTOPWIDGET_VIBRATE_TIME 150

typedef struct
{
    u16 nClsID;
    u16 nStyleID;
    u32 nWidgetImageID;
    u32 nWidgetDescriptionTextID;
    u32 nWidgetStyleTextID;
}DesktopWidgetStyleInfo_t;

typedef struct
{
    IWidget *pMenuWdg;

} IdleConfigMenuWndWdgList_t;

typedef struct
{
    IdleConfigMenuWndWdgList_t tWdgList;
} IdleConfigMenuWndData_t;

typedef struct
{
    IWidget *pAbsContainer;
    IWidget *pTitleTextWdg;
    IWidget *pLeftIndicatorButtonWdg;
    IWidget *pRightIndicatorButtonWdg;
    IWidget *pInfoContainer;
    IWidget *pThumbnailImgWdg;
    IWidget *pSelectButtonWdg;
    IWidget *pStyle1TextWdg;
    IWidget *pStyle2TextWdg;
    IWidget *pExistShadowWdg;
    IWidget *pExistImgWdg;
    IWidget *pExistTextWdg;

    IWidget *pSlideWdg;

} IdleConfigPreviewWndWdgList_t;

typedef struct
{
    IdleConfigPreviewWndWdgList_t tWdgList;
    const DesktopWidgetStyleInfo_t *pWdgStylePtr;
    u32 nCurrentStyle;
    u32 nAvailableStyle;
    DesktopWidget_e nDesktopIdBase;
    u8  nWidgetStatus[DESKTOP_WIDGET_NUM];
    boolean bSlideAnimating;

} IdleConfigPreviewWndData_t;

static const DesktopWidgetStyleInfo_t tClockStyle[] = {
    {CLSID_ACLOCKDESKTOPWIDGET, ACLOCK_WDG_STYLE_TRANSSLIVER_LARGE, IDLE_IMG_SET_WIDGET_BIG_ANALOG_CLOCK, TXT_LIL_N_ANALOGUE_CLOCK, TXT_LIL_N_LARGE},
    {CLSID_ACLOCKDESKTOPWIDGET, ACLOCK_WDG_STYLE_TRANSSLIVER_SMALL, IDLE_IMG_SET_WIDGET_SMALL_ANALOG_CLOCK, TXT_LIL_N_ANALOGUE_CLOCK, TXT_LIL_N_SMALL},
    {CLSID_DCLOCKDESKTOPWIDGET, DCLOCK_WDG_STYLE_CIRCLE_LARGE, IDLE_IMG_SET_WIDGET_BIG_DIGITAL_CLOCK, TXT_LIL_N_DIGITAL_CLOCK, TXT_LIL_N_LARGE},
    {CLSID_DCLOCKDESKTOPWIDGET, DCLOCK_WDG_STYLE_CIRCLE_SMALL, IDLE_IMG_SET_WIDGET_SMALL_DIGITAL_CLOCK, TXT_LIL_N_DIGITAL_CLOCK, TXT_LIL_N_SMALL},
    {CLSID_DCLOCKDESKTOPWIDGET, DCLOCK_WDG_STYLE_PAGE, IDLE_IMG_SET_WIDGET_BIG_PAGE_CLOCK, TXT_LIL_N_DIGITAL_CLOCK, TXT_LIL_N_NORMAL}
};

static const DesktopWidgetStyleInfo_t tCalendarStyle[] = {
    {CLSID_CALENDARDESKTOPWIDGET, CALENDAR_WDG_STYLE_LARGE, IDLE_IMG_SET_WIDGET_BIG_CALENDAR, TXT_LIL_N_CALENDAR, TXT_LIL_N_LARGE},
    {CLSID_CALENDARDESKTOPWIDGET, CALENDAR_WDG_STYLE_SMALL, IDLE_IMG_SET_WIDGET_SMALL_CALENDAR, TXT_LIL_N_CALENDAR, TXT_LIL_N_SMALL}
};

static const DesktopWidgetStyleInfo_t tMplayerStyle[] = {
    {CLSID_MPDESKTOPWIDGET, MPLAYER_WDG_STYLE_LARGE, IDLE_IMG_SET_WIDGET_BIG_MUSIC_PLAYER, TXT_LIL_N_MUSIC, TXT_LIL_N_LARGE},
    {CLSID_MPDESKTOPWIDGET, MPLAYER_WDG_STYLE_SMALL, IDLE_IMG_SET_WIDGET_SMALL_MUSIC_PLAYER, TXT_LIL_N_MUSIC, TXT_LIL_N_SMALL}
};

static const DesktopWidgetStyleInfo_t tFMRadioStyle[] = {
    {CLSID_FMDESKTOPWIDGET, FM_WDG_STYLE_LARGE, IDLE_IMG_SET_WIDGET_BIG_FM_RADIO, TXT_LIL_N_FM_RADIO, TXT_LIL_N_LARGE},
    {CLSID_FMDESKTOPWIDGET, FM_WDG_STYLE_SMALL, IDLE_IMG_SET_WIDGET_SMALL_FM_RADIO, TXT_LIL_N_FM_RADIO, TXT_LIL_N_SMALL}
};

static const DesktopWidgetStyleInfo_t tPhotoStyle[] = {
    {CLSID_PHOTODESKTOP_WIDGET, 0, IDLE_IMG_SET_WIDGET_PHOTOVIEW, TXT_LIL_N_PHOTOS, TXT_LIL_N_NORMAL}
};

static const DesktopWidgetStyleInfo_t tMessageStyle[] = {
    {CLSID_MESSAGEDESKTOP_WIDGET, 0, IDLE_IMG_SET_WIDGET_MESSAGE, TXT_LIL_N_MESSAGE, TXT_LIL_N_NORMAL}
};

static const DesktopWidgetStyleInfo_t tPhonebookStyle[] = {
    {CLSID_PHONEBOOKDESKTOP_WIDGET, 0, IDLE_IMG_SET_WIDGET_PHONE_BOOK, TXT_LIL_N_DESKTOPWIDGET_PHB_TITLE, TXT_LIL_N_NORMAL}
};

static const DesktopWidgetStyleInfo_t tOperatorStyle[] = {
    {CLSID_OPDESKTOPWIDGET, 0, IDLE_IMG_SET_WIDGET_OPERATOR, TXT_LIL_N_CONFIGMENU_WIDGET_OPERATOR, TXT_LIL_N_NORMAL}
};

static const DesktopWidgetStyleInfo_t tNotePadStyle[] = {
    {CLSID_NOTEPADDESKTOPWIDGET, 0, IDLE_IMG_SET_WIDGET_NOTEPAD, TXT_LIL_N_NOTEPAD, TXT_LIL_N_NORMAL}
};

static const DesktopWidgetStyleInfo_t tWorldClockStyle[] = {
    {CLSID_ACLOCKDESKTOPWIDGET, ACLOCK_WDG_STYLE_WANALOGBLACK_LARGE, IDLE_IMG_SET_WIDGET_BIG_WOLDER_ANALOG_CLOCK, TXT_LIL_N_ANALOGUE_CLOCK, TXT_LIL_N_LARGE},
    {CLSID_ACLOCKDESKTOPWIDGET, ACLOCK_WDG_STYLE_WANALOGBLACK_SMALL, IDLE_IMG_SET_WIDGET_SAMLL_WOLDER_ANALOG_CLOCK, TXT_LIL_N_ANALOGUE_CLOCK, TXT_LIL_N_SMALL},
    {CLSID_DCLOCKDESKTOPWIDGET, DCLOCK_WDG_STYLE_WBLACK_LARGE, IDLE_IMG_SET_WIDGET_BIG_WOLDER_DIGITAL_CLOCK, TXT_LIL_N_DIGITAL_CLOCK, TXT_LIL_N_LARGE},
    {CLSID_DCLOCKDESKTOPWIDGET, DCLOCK_WDG_STYLE_WBLACK_SMALL, IDLE_IMG_SET_WIDGET_SAMLL_WOLDER_DIGITAL_CLOCK, TXT_LIL_N_DIGITAL_CLOCK, TXT_LIL_N_SMALL}
};

static const DesktopWidgetStyleInfo_t tSearchStyle[] = {
    {CLSID_SEARCHDESKTOPWIDGET, 0, IDLE_IMG_SET_WIDGET_SEARCH, TXT_LIL_N_SEARCH, TXT_LIL_N_NORMAL}
};

boolean IdleMultipageHandleKeyPress(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleMultipageHandleKeyRelease(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleMultipageHandleFingerCommand(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean IdleMultipageHandleTouchEvent(IApplet *pApplet, u32 evt, u32 param1, u32 param2);

void IdleMultipageHandleDesktopWidgetTouchReleaseIn(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pMoveData, IWidget *pWidget);
void IdleMultipageHandleDesktopWidgetTouchMoveToTop(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, DesktopWdg_t *pDesktopWdg, IWidget *pWidget);
void IdleMultipageHandleDesktopWidgetTouchRelease(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, ShortMoveData_t *pMoveData, IWidget *pWidget);

void IdleAddMultipageItems(MMI_IDLEAPP* pThis);
void IdleDeleteMultipageItems(MMI_IDLEAPP* pThis);
void IdleLaunchThumbnailApp(MMI_IDLEAPP* pThis);
void IdleCloseConfigEntry(MMI_IDLEAPP* pThis);
void IdleStartConfigEntry(MMI_IDLEAPP* pThis);
#if defined (__PAGE_ANIMATION_EXT__)
void IdleShiftBgImageToCenter(MMI_IDLEAPP *pThis);
#endif

void IdleDesktopWidgetAlignPosToCenterCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, DesktopWdg_t *pDesktopWdg, IWidget *pWidget);
void IdleNotifyPhbSrvReadyToDesktopPhbCB(void* pUserdata);
void IdlePhonebookDesktopWdgEventCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void IdleConfigEntryEventCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void IdleConfigMenuForWidgetEventCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void IdleConfigMenuForShortcutEventCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void IdleConfigPreviewLeftIndicatorButtonClickCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void IdleConfigPreviewRightIndicatorButtonClickCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void IdleConfigPreviewSelectButtonClickCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void IdleConfigCancelButtonClickCB(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void IdlePageShiftAnimationDoneCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);

void IdleSlideEffectDelayDeleteWdgCB(void* pUserData);
void IdleCreateDesktopObjectBottomHalfTimerCB(void *pUserData);
void IdleMultipagePageChangeTimerCB(void *pUserData);
void IdleMultipageCalcFocusOnHandoffCB(void *pUserData);
#ifdef __PAGE_ANIMATION_EXT__
void IdlePageShiftAnimationExtTimerCB(void *pUser);
#endif
void IdleDragDesktopWidgetVibrateTimerCB(void* pData);

void IdlePreserveWidgetDataAfterConfigPreview(MMI_IDLEAPP * pThis, DesktopWidgetStyleInfo_t **ppCurrentStyle, u32 *pCurrentWdgID);
void IdleDestroyDesktopObjectForAppSuspend(MMI_IDLEAPP *pThis);
void IdleCreateDesktopObjectTopHalfForAppResume(MMI_IDLEAPP *pThis);

#endif /* __GADGETS_MMI__ && __3D_UI_IDLE_MULTIPAGE__*/

#endif /* __MMI_IDLEAPP_MULTIPAGE_EXT_H__ */
