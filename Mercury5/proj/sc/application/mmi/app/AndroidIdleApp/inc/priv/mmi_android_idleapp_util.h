/*
 *	file: "mmi_android_idleapp_util.h"
 *	author: Hf.lin
*/
#ifndef __MMI_ANDROID_IDLEAPP_UTIL__
#define __MMI_ANDROID_IDLEAPP_UTIL__
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
#include "mmi_mae_interfacemodel.h"
#include "mmi_wdg_image_text_image.h"
#include "mmi_mae_helper.h"
#include "mmi_wdg_transition.h"
#include "mmi_wdg_list.h"
#include "mmi_offapp.h"
#include "mmi_mae_vectormodel.h"
#include "mae_decoratorbase.h"
#include "mae_widget_common.h"
#include "mmi_common_menu.h"
#include "mmi_wdg_drag.h"
#include "mmi_android_idleapp_priv.h"
#include "mmi_wdg_image.h"
#include "AndroidIdleApp_resource.h"
#include "mmi_android_mainmenuapp.h"
#include "mmi_common_cfg.h"
#include "mmi_launcher_filemanager.h"
#include "mmi_launcher_off.h"
#include "mmi_launcher_dialer.h"
#include "mmi_launcher_calllog.h"
#include "mmi_launcher_keyguard.h"
#include "mmi_launcher_shortcut.h"
#include "mmi_srv_header.h"
#include "mmi_common_wdgvar.h"
#include "mmi_wdg_desktop.h"
#include "mmi_wdg_calendardesktop.h"
#include "mmi_wdg_dclockdesktop.h"
#include "mmi_wdg_fmdesktop.h"
#include "mmi_wdg_mpdesktop.h"
#include "mmi_wdg_notedesktop.h"
#include "mmi_wdg_opdesktop.h"
#include "mmi_wdg_searchdesktop.h"
#include "mmi_wdg_profile.h"
#include "mae_animation.h"
#include "Widgets_img_data.h"

typedef enum
{
	MNU_DESKTOP_STAR = MNU_MAIN_ANDROID_TOTAL,
    MNU_DESKTOP_CALENDAR,
    MNU_DESKTOP_ANACLOCK,
    MNU_DESKTOP_DIGCLOCK,
    MNU_DESKTOP_MPLAYER,
#ifdef __APP_MMI_FM_RADIO__
    MNU_DESKTOP_FMRADIO,
#endif
#ifdef __MAP_MMI__
    MNU_DESKTOP_MAP,
#endif
    MNU_DESKTOP_GAME,
    MNU_DESKTOP_NOTE,
    MNU_DESKTOP_OPERATOR,
    MNU_DESKTOP_SEARCH,
    MNU_DESKTOP_PROFILE,
    MNU_DESKTOP_end
}DeskTopWidget_e;
typedef struct
{
    DeskTopWidget_e eWdgID;
    MAE_ClsId nClsId;
    boolean bAdded;
}DeskTopWidgeInfo_t;

#ifdef __UI_STYLE_MMI_ANDROID_4_0__
enum
{
	LEFT2BUTTON = 0,
	LEFT1BUTTON,
	MIDDLEBUTTON,
	RIGHT1BUTTON,
	RIGHT2BUTTON,
};
#else
enum
{
	LEFTBUTTON = 0,
	MIDDLEBUTTON ,
	RIGHTBUTTON,
};
#endif // __UI_STYLE_MMI_ANDROID_4_0__

enum
{
    HomePage = 0,
    SubPage_1 ,
    SubPage_2 ,
    SubPage_3 ,
    SubPage_4 ,
};


typedef u32 SoftkeyButton_Selection_e;
#ifdef __UI_STYLE_MMI_ANDROID_IDLE_DRAG_WITH_MASK__
typedef struct
{
    u32 nMenuID;
    u32 nTextID;
    u32 nImageID0;
    u32 nStartType;
	u32 nStartID;
    u32 nParamID;
} MenuItemModelInfo2_t;
#else
typedef struct
{
    u32 nMenuID;
    u32 nTextID;
    u32 nImageID0;
    u32 nImageID3;
    u32 nImageID4;
    u32 nStartType;
	u32 nStartID;
    u32 nParamID;
} MenuItemModelInfo2_t;
#endif

typedef struct
{
	HistoryInfo_t stHistory;
	MenuItemInfo_t stMenuItemData;
} MenuHistoryInfo_t;

typedef struct
{
    u16  nMenuItemID;
    u32 nImageID;
    u32 nTextID;
}WdgSelStaticData;

typedef struct
{
    void *pDskWdgOwner;
    IWidget *pIDskWdg;
    WidgetHandler_t DeskTopWdgHandle;
}DskWdgHdlData_t;

#define ANDROID_MENU_TRANS_DURATION		300
#define ANDROID_MENU_SWITCHPAGE_TRANS_DURATION		300
#define ANDROID_FOCUS_IDX_NULL		(-1)
#define ANDROID_FOCUS_TIME_INTERVAL 	400
#define ANDROID_WALLPAPER_RIGHT_POS_THRESHOLD	0
#define ANDROID_WALLPAPER_MOVE_TIME	16
#define ANDROID_WALLPAPER_MOVE_NUM	4

const static u32 nPagePreviewImgPos_X[ANDROID_PAGE_NUM] = {\
IDLE_ANDROID_PAGE_PREVIEW_TOP_IMAGE_X,\
IDLE_ANDROID_PAGE_PREVIEW_MIDDLE_1_IMAGE_X,\
IDLE_ANDROID_PAGE_PREVIEW_MIDDLE_2_IMAGE_X,\
IDLE_ANDROID_PAGE_PREVIEW_MIDDLE_3_IMAGE_X,\
IDLE_ANDROID_PAGE_PREVIEW_BOTTOM_IMAGE_X};

const static u32 nPagePreviewImgPos_Y[ANDROID_PAGE_NUM] = {\
IDLE_ANDROID_PAGE_PREVIEW_TOP_IMAGE_Y,\
IDLE_ANDROID_PAGE_PREVIEW_MIDDLE_1_IMAGE_Y,\
IDLE_ANDROID_PAGE_PREVIEW_MIDDLE_2_IMAGE_Y,\
IDLE_ANDROID_PAGE_PREVIEW_MIDDLE_3_IMAGE_Y,\
IDLE_ANDROID_PAGE_PREVIEW_BOTTOM_IMAGE_Y};

const  static WdgSelStaticData WdgSelData[] =
{
    {MNU_DESKTOP_ANACLOCK,    ANDROID_IDLE_DESKTOP_ANACLOCK_ICON,          TXT_LIL_N_ANALOGUE_CLOCK},
    {MNU_DESKTOP_DIGCLOCK,    ANDROID_IDLE_DESKTOP_DIGCLOCK_ICON,  TXT_LIL_N_DIGITAL_CLOCK},
    {MNU_DESKTOP_OPERATOR,    ANDROID_IDLE_DESKTOP_OPERATOR_ICON,  TXT_LIL_N_OPERATE},
    {MNU_DESKTOP_CALENDAR, ANDROID_IDLE_DESKTOP_CALENDAR_ICON,       TXT_DSL_N_CALENDAR},
    {MNU_DESKTOP_PROFILE,  ANDROID_IDLE_DESKTOP_PROFILES_ICON,       TXT_LIL_N_PROFILES},
#ifdef __APP_MMI_FM_RADIO__
    {MNU_DESKTOP_FMRADIO,    ANDROID_IDLE_DESKTOP_FM_RADIO_ICON,       TXT_LIL_N_FM_RADIO},
#endif
    {MNU_DESKTOP_NOTE,      ANDROID_IDLE_DESKTOP_NOTE_ICON,            TXT_LIL_N_NOTE},
    {MNU_DESKTOP_MPLAYER,    ANDROID_IDLE_DESKTOP_MUSIC_PLAYER_ICON,   TXT_LIL_N_MUSIC},
};

void AndroidIdleCreateAndroidView(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleLoadMenuItem(MMI_ANDROID_IDLEAPP *pThis);
#ifndef __UI_STYLE_MMI_ANDROID_IDLE_MUTEX__
void AndroidIdleLoadDeskTopWdgItem(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleLoadDeskTopWdgItem(MMI_ANDROID_IDLEAPP *pThis);
boolean AndroidIdleDskTopWdgHandleEvent(void* pUserData, MAE_EventId evt, u32 param1, u32 param2);
void AndroidIdleDskTopWdgHandleFree(void *pData);
const MenuItemModelInfo2_t* AndroidIdleGetMenuItemPtr(u8 nMenuID);

AndroidItemInfo_t* AndroidIdleFindItemDataByDskTopWdgObj(MMI_ANDROID_IDLEAPP *pThis,IWidget *pDskTopWdg);
s16 AndroidIdleArrayIndexByDskTopWdgObj(MMI_ANDROID_IDLEAPP *pThis,IWidget *pDskTopWdg);
void AndroidIdleSaveDesktopInfoWithoutMutex(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleMoveIconPositionWithoutMutex(MMI_ANDROID_IDLEAPP* pThis,s8 sDestPageIndex,s8 DestPosIndex);
s8 AndroidIdleGetBestPosToFillWdgWithoutMutex(MMI_ANDROID_IDLEAPP* pThis,s8 sPageIndex);
void AndroidIdleAddIconToContainerWithoutMutex(MMI_ANDROID_IDLEAPP *pThis, s8 sPageIndex);
void AndroidIdleAddDeskTopWidgetWithoutMutex(MMI_ANDROID_IDLEAPP *pThis,u8 u8MenuID);
s8 AndroidIdleFindArrayItemIdxByDskTopWdgObj(MMI_ANDROID_IDLEAPP *pThis,IWidget *pDskTopWdg);
void AndroidIdlePrepareNewPageWithoutMutex(MMI_ANDROID_IDLEAPP *pThis, s8 sPageIndex , IWidget** pITargetContainer);
void AndroidIdleDestroyDeskTopWdgWithoutMutex(MMI_ANDROID_IDLEAPP *pThis, s8 sPageIndex);
#endif
s32 AndroidIdleFindIndexbyMenuID(u8 nMenuID);
void AndroidIdleLaunchFunc(MMI_ANDROID_IDLEAPP *pThis, AndroidItemInfo_t *pItem);

void AndroidIdleInit(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleTSMoveEvtHdl(MMI_ANDROID_IDLEAPP *pThis, s32 param1, s32 param2);
void AndroidIdleTSReleaseEvtHdl(MMI_ANDROID_IDLEAPP *pThis, s32 param1, s32 param2);
void AndroidIdleTSPressEvtHdl(MMI_ANDROID_IDLEAPP *pThis, s32 param1, s32 param2);
void AndroidIdleTSMoveTimerCB(void *pUser);
s8 AndroidIdleGetBestPosToFillWdg(MMI_ANDROID_IDLEAPP* pThis,s8 sPageIndex);
boolean AndroidIdleCheckPosIsEmpty(MMI_ANDROID_IDLEAPP* pThis,s8 sPageIndex,u8 u8AssignPos,WidgetSize_t tSize);
boolean AndroidIdleCheckAreaCanBeFill(MMI_ANDROID_IDLEAPP* pThis,u8 u8PosIndex, Rect_t tIconRect);
Rect_t AndroidIdleGetIconAreaByPosIndex(MMI_ANDROID_IDLEAPP* pThis,u8 u8PosIndex,u32 nIconWith,u32 nIconHight);
Rect_t AndroidIdleGetIconAreaByCoordination(MMI_ANDROID_IDLEAPP* pThis,s32 sPos_x,s32 sPos_y,u32 nIconWith,u32 nIconHight);
void AndroidIdleCheckDelActive(MMI_ANDROID_IDLEAPP* pThis,s32 nIconPos_X,s32 nIconPos_Y);
void AndroidIdleAdjustDeskTopWdgCoordinate(MMI_ANDROID_IDLEAPP* pThis,AndroidItemInfo_t *pItem);
void AndroidIdleEnterDeleteMode(MMI_ANDROID_IDLEAPP* pThis);
void AndroidIdleExitDeleteMode(MMI_ANDROID_IDLEAPP* pThis);
void AndroidIdleDeleteIcon(MMI_ANDROID_IDLEAPP* pThis);
void AndroidIdleMoveIconPosition(MMI_ANDROID_IDLEAPP* pThis,s8 sPageIndex,s8 DestItemIdx);
void AndroidIdleFocusTimerCB(void* pData);
void AndroidIdleAddNewIconFromMainmenu(MMI_ANDROID_IDLEAPP* pThis,s8 sDestPageIndex,s8 DestPosIndex);
s8 _AndroidIdleGetPosIdxByCoordinate(MMI_ANDROID_IDLEAPP* pThis,s32 nPos_X,s32 nPos_y);
void AndroidIdleArrayModleFree(void *pData, IBase *pOwner);
void AndroidIdleTransitionModelListener(void *pUserData, ModelEvent_t *pMdlEvent);
void AndroidIdleAddIconToContainer(MMI_ANDROID_IDLEAPP *pThis, s8 sPageIndex);
void AndroidIdlePrepareNewPage(MMI_ANDROID_IDLEAPP *pThis, s8 sPageIndex , IWidget** pITargetContainer);
void AndroidIdleRelease(IApplet *pApplet);
void AndroidIdleMoveWidgetToContainer(MMI_ANDROID_IDLEAPP *pThis,IWidget* pWidget, IWidget* pIDestContainer, WPos_t * tPos,boolean bIsTop);
void AndroidIdleDestroyWdg(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleSaveIconInfo(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleShowPagebyIndex(MMI_ANDROID_IDLEAPP *pThis,s8 sPageIndex);
s8 AndroidIdleGetEmptyPosToFillDeskTop(MMI_ANDROID_IDLEAPP* pThis,s8 sPageIndex,WidgetSize_t tSize);
void AndroidIdleUpdateOperatorName(MMI_ANDROID_IDLEAPP *pThis, u8 nDualID, MAE_WChar *pName);
void AndroidIdleShowDragIconFromMainmenu(MMI_ANDROID_IDLEAPP *pThis,CellLongPS_t *pCellLongPS);
#ifdef __UI_STYLE_MMI_ANDROID_IDLE_MUTEX__
void AndroidIdleAddDeskTopWidget(MMI_ANDROID_IDLEAPP *pThis,u8 nMenuID);
#endif
MAE_Ret AndroidIdleRegisterDesktopWidgetCb(IWidget *pIWidget, u32 nItemId);
MAE_Ret AndroidIdleDeregisterDesktopWidgetCb(IWidget *pIWidget, u32 nItemId);
void AndroidIdleMediaPlayerDesktopWidgetLaunchAdjustVolumeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
#if defined(__APP_MMI_FM_RADIO__)
void AndroidIdleFMRadioDesktopWidgetLaunchAdjustVolumeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
#endif
#if defined(__APP_MMI_FM_RADIO__)
void AndroidIdleFMRadioDesktopWidgetLaunchAirplaneModeCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
#endif
#if defined(__APP_MMI_FM_RADIO__) && !defined(__FM_SHARE_ANTENNA__)
void AndroidIdleFMRadioDesktopWidgetLaunchPlugHeadsetCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pWidget);
#endif
void AndroidIdleDesktopWidgetLaunchAppCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, DesktopWdg_LaunchApp_Info_t *pLaunchApInfo, IWidget *pWidget);
MAE_Ret AndroidIdleCreateVolumeDialog(MMI_ANDROID_IDLEAPP *pThis, boolean bSilent, boolean bBGPlaying, CFGItemID_e eVolumeId);
MAE_Ret AndroidIdleCreateFmNoticeDialog(MMI_ANDROID_IDLEAPP *pThis, u32 nTextId);
void AndroidIdlePagePreviewFreeHandler(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleMoveWallpaperByPageIndex(void *pUserData, s8 nPageIdx);
boolean AndroidIdleTouchReleaseCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
boolean AndroidIdleTouchMoveCB(IApplet *pApplet, u32 evt, u32 param1, u32 param2);
void AndroidIdleTouchMoveDelayCB(void *pUser);

#ifdef __UI_STYLE_MMI_ANDROID_IDLE_ENABLE_PREVIEW__
void AndroidIdleActionKeyLongPressHandle(IApplet *pApplet);
boolean AndroidIdlePagePreviewHandleEvent(MMI_ANDROID_IDLEAPP *pThis, MAE_EventId eventID, u32 param1, u32 param2);
#endif // __UI_STYLE_MMI_ANDROID_IDLE_ENABLE_PREVIEW__

void AndroidIdleMoveBigWallpaperByFinger(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleInitBigWallpaper(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleCreatSofykey(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleCreateSwitchPageTag(MMI_ANDROID_IDLEAPP *pThis);
void AndroidIdleUpdateSwitchPageTag(MMI_ANDROID_IDLEAPP *pThis,u32 nOldIdx,u32 nNewIdx);
boolean AndroidIdleCheckMenuIDExistInEveryPage(MMI_ANDROID_IDLEAPP *pThis,u8 u8MenuID);
MAE_Ret AndroidIdleRemoveDragWdgByMenuID(MMI_ANDROID_IDLEAPP *pThis, u32 nMenuID);

#endif /*__UI_STYLE_MMI_ANDROID_IDLE__*/
#endif /*__MMI_ANDROID_IDLEAPP_ANDROIDSTYLE__*/
