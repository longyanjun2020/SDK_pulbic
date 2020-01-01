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
* @file    mmi_mainmenuapp_priv.h
* @version
* @brief   MainMenu applet private header file
*
*/
#ifndef __MMI_MAINMENUAPP_PRIV_H__
#define __MMI_MAINMENUAPP_PRIV_H__
/*-------------------------------------------------------------------------*/
#include "mmi_baseapplet.h"
#include "mmi_common_menu.h"
#include "mmi_common_wdgvar.h"
#include "mmi_srv_header.h"
#include "mmi_mainmenuapp.h"
#include "mmi_wdg_headers.h"
#include "mmi_mainmenuapp_id.h"
#include "mainmenuapp_resource.h"
#include "mmi_wdg_animated_menu.h"
#include "mae_animation.h"
#include "mmi_common_vtm.h"
#if defined (__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)
#include "mmi_wdg_ifone.h"
#endif

#ifdef __UI_STYLE_MMI_MAIN_MENU_3D_SPIN__
#include "mmi_wdg_glrotationmenuwidget.h"
#endif
/*-------------------------------------------------------------------------*/
enum
{
	MAINMENU_LEVEL_1,
	MAINMENU_LEVEL_2,
	MAINMENU_LEVEL_TOTAL
};

typedef struct {
	IWidget *pMenuWdg;
#ifdef __UI_STYLE_MMI_MAIN_MENU_ANIMATION__
	IWidget *pAnimatedWdg;
#endif
#ifdef __USER_DEFINE_MAINMENU_VIDEO__
    IWidget *pMainAbsContainer;
#endif
	HistoryInfo_t info;
}GridListWndData_t;

typedef struct {
	IWidget *pMenuWdg;
	HistoryInfo_t info;
    MainmenuWnd_e eWndID;
}SubWndData_t;

#ifdef __USER_DEFINE_MAINMENU_VIDEO__
#define MAINMENU_WARNING_STRING_TIMEOUT 3000
#endif

#ifdef __UI_STYLE_MMI_MAIN_MENU_SPIN__
#define SPINMENU_MENU_ITEM					9
#define SPINMENU_TITLE_PREFIX_LEN			2
#define SPINMENU_TRANS_TIMER				30
#define SPINMENU_LONGPRESS_TIMER			30
#define SPINMENU_TS_MOVE_UPDATE_DISTANCE	60

typedef enum
{
	SPINMENU_STATIC		= 0,
	SPINMENU_TRANSFER
}SpinMenuType_e;

typedef struct
{
	IWidget *pBGWdg;
	IWidget *pTextWdg;
	IWidget *pMImgWdg;
	IWidget *pMenuWdg;

	u32	nTSPosx;
	u32	nTSPosy;
	HistoryInfo_t info;

	// Spin transition frame
	u16 nSpinTransitIndex;
}SpinWndData_t;
#endif //__UI_STYLE_MMI_MAIN_MENU_SPIN__

#ifdef __USER_DEFINE_MAINMENU_VIDEO__
typedef enum
{
    MAINMENU_STOP_CAUSE_INIT = 0,
    MAINMENU_STOP_CAUSE_SUSPEND,
    MAINMENU_STOP_CAUSE_CLOSEAP,
    MAINMENU_STOP_CAUSE_FLUSH,
    MAINMENU_STOP_CAUSE_SUBMENU,
    MAINMENU_STOP_CAUSE_VIDEOERROR,
    MAINMENU_STOP_CAUSE_BACKLIGHT,
    MAINMENU_STOP_CAUSE_MAX
}MainMenuStopVideoCause_e;

#endif

#ifdef __UI_STYLE_MMI_MAIN_MENU_3D_SPIN__
typedef struct
{
	IWidget *pGLCntr;
	IWidget *pIMenuWdg;
}Spin3DWndWdgList_t;

typedef struct
{
	u32	nTSPosx;
	u32	nTSPosy;
	HistoryInfo_t info;
	ModelListener_t MenuMdlListener;

	Spin3DWndWdgList_t tWdgList;
}Spin3DWndData_t;
#endif

#if defined (__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)

#define IFONE_PAGE_NUM				11
#define IFONE_PAGE_SC_IDX			(IFONE_PAGE_NUM-1)
#define IFONE_FALLDOWN_PHASE		20
#define IFONE_FALLDOWN_TIME		3000// 3 seconds
#define IFONE_FALLDOWN_MAXWAIT_TIME 1000
#define IFONE_ITME_MAX_NUM			100
#define MAINMENUAPP_IFONE_UP_WDG_NUM		(RS_MAINMENUAPP_IFONE_COL_ITEM_NUM*RS_MAINMENUAPP_IFONE_ROW_ITEM_NUM)		//
#define IFONE_WDG_NUM		(IFONE_UP_WDG_NUM+IFONE_SC_WDG_NUM)

typedef struct
{
	u32 nTextID;
	u32 nImageID;
	IfonIconType_e eMenuItemType;
	u16	nClsId;		//class id
	u32 nParam;		//start param
	u8 nFolderID;       //System or userdefine
} MenuItemModelInfo2_t;

#define MAINMENUIFONE_FOLDER_SYSTEM 0
#define MAINMENUIFONE_FOLDER_USERDEFINE 1

typedef struct
{
	HistoryInfo_t stHistory;
	MenuItemInfo_t stMenuItemData;
} MenuHistoryInfo_t;

typedef struct
{
	IWidget *pIWdget;
	IWidget *pIAbsContainer;
	Pos_t tPos;
	u8 nAnimPhase;
}MoveWdgPosAnimData_t;

typedef struct
{
	s32	nStartTime;
	IWidget* pMoveWidget;
	IAbsContainer *pIContainer;
}FallDownData_t;

typedef struct
{
	IWidget* pIDarkBGWdg;
	IWidget* pIAnimImgWdg;
	IWidget* pIStatusTxtWdg;
	IWidget* pIStatusBarWdg;

	IfoneMenuItemData_p pMenuItemTable;
	u32 nMenuItemNum;
	u32 nCurrentMenuIndex;
	u32 nPageIndex;
	IWidget* pICurrentFolderWdg;
	u8 aMenuPageNmbInfo[IFONE_PAGE_NUM];
	u32 nCurrentPageItemNum;
}MainmenuIfoneInitWndData_t;

typedef struct
{
    InputVtmWdgList_t tInputVtmWdgLst;
}IfoneFolderNameWndDat_t;

#define GET_IFONE_FOCUS_BG_POS(IFocusWdgPos, pFocusBGpos)\
	(pFocusBGpos)->x = ((IFocusWdgPos).x + (RS_IFONEWIDGET_WIDTH- IFONE_FOCUS_BG_WIDTH-2)/2);\
	(pFocusBGpos)->y = ((IFocusWdgPos).y + (RS_IFONEWIDGET_HEIGHT - IFONE_FOCUS_BG_HEIGHT-2)/2);

#endif /*__UI_STYLE_MMI_IFONE__ */

/**
* Application structure
*/
typedef struct MMI_MAINMENUAPP_TAG {
	APPLET_BASE_ELEMENTS;

#ifdef __MINIMODE_LAYOUTCHANGE__
	boolean bMiniModeEnable;	// mini mode status
#endif
	SetDisplayMenuStyle_e eMenuStyle;
	u32		nEntryTransId[MAINMENU_LEVEL_TOTAL];
	u32		nExitTransId[MAINMENU_LEVEL_TOTAL];
	u16 	nMenuID;
#if defined(__GADGETS_MMI__) || defined(__3D_UI_MAINMENU__)
	MainMenuStartType_e MenuAppStart;
#endif

#ifdef __FEATURE_MGL__
	Menu_StartupAnimStyle_e	eAnimStyle;
#endif

#ifdef __UI_STYLE_MMI_MAIN_MENU_3D_SPIN__
	IVectorModel    *pIVM_Spin;
#endif

#ifdef __USER_DEFINE_MAINMENU_VIDEO__
    IWidget *pBgOsdWdg;
    IWidget *pImageWdg;
    IWidget *pUnspportImgFadeoutWdg;
    IWidget *pUnspportImgTxtWdg;
    boolean bVideoBg;
    boolean bOpenSession;
    boolean bVideoError;
    boolean bTrunAlphaMask;
	MainMenuStopVideoCause_e eStopCause;
    ORIENTATION_e eOrientation;
#endif

#if defined (__UI_STYLE_MMI_IFONE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)
	s8				nHotItemIdx;
	s8				nHotVecIdx;

	s8      nFolderIMenuItemIdx;
	s8      nFolderIMenuVecIdx;
	u8      nFlyInEffectPhase;

	boolean bIsLaunchAP:1;
	boolean	bSwitch	:1;
	boolean bMoveWdgPos:1;
	boolean bShakeAnimation:1;
	boolean	bTSPRESS:1;
	boolean	bFallingDown:1;
	boolean	bBreakGlass:1;
	boolean	bTranslation:1;
	boolean bFolderOpened:1;
	boolean bPressedFolderMenuItem:1;
	boolean bFolderItemMoveOut:1;
	boolean bDoingFolderOnOff:1;
	boolean bNeedRecreateWnd:1;
	boolean bTSEvnetHappend:1;
    boolean bNeedClosFolder:1;

	IWidget*    pIParentAbsCntr;
	IWidget*    pICurrentAbs;
	IWidget*    pIShortCutAbs;
	IWidget*    pIWallpaperImgWdg;
	IWidget*    pIPageInfoListWdg;
	IWidget*    pIShortCutBGImgWdg;
	IWidget*    pITransWdg;
	IWidget*    pITransLeftContainer;
	IWidget*    pITransRightContainer;
	IWidget*    pIFocusWidget;
#ifdef __IFONESTYLE_SUPPROT_NIVIGATIONKEY__
	IWidget*    pIHighlightBGWidget;	// to show the back ground image
#endif
	IWidget *pIBreakGlassBGWdg;
	IWidget *pIGlassImgWdg;
	IWidget*    pIConstructingFolder;
	IWidget*    pIAddInFolder;
	IWidget*    pIStatusBarWdg;
	//For mainmenu folder
	IWidget*    pIFolderContainer;
	IWidget*    pIUpImageWdg;
	IWidget*    pIDownImageWdg;
	IWidget*    pIFolderNameTextWdg;
	IWidget*    pIFolderMenuWdg;
	IImage*    pIWallpaperImage;
	IImage*    pIIndUpImage;
	IImage*    pIIndDownImage;
	IVectorModel*   pIFolderWdgVMdl;
	IVectorModel*   pIPageInfoVMdl;
	IVectorModel*   pIItemTextVMdl;
	IVectorModel*   pIMoveVector;
	IVectorModel*   pIMenuItemVector[IFONE_PAGE_NUM];
	IArrayModel*    pIAvailItem;
	IDataModel*     pIDataMdl;	//for get data from EvtCenterSrv;
	MAE_WChar*      pFolderNameStr;

	Pos_t*   pIfoneMenuItemPos;
	FallDownData_t *tFallDownData;
	s8				nCurPageIdx;
	u32				nTotalPage;
	u32				u32TSPRESSPos_X;
	u32				u32TSPRESSPos_Y;
	u32 nTSMoveX;
	u32 nTSMoveY;
	ModelListener_t TransitionMdlListener;
	ModelListener_t SCMenuMdlListener;
	ModelListener_t EvtCenterMdlListener;
	ModelListener_t CFGSrvMdlListener;

	WidgetHandler_t TransWdgHandler;
	WidgetHandler_t PageInfoListWdgHandler;
    WidgetHandler_t FolderNameWdgHandler;

	s32	nFocusIndex;
	u8	nFallDownPhase;
	SetOnOff_e bEnableFalldown;
	SetOnOff_e bEnableBreakglass;
	SetOnOff_e bEnableCircumgyrate;
    SetOnOff_e bEnableTransition;
#ifndef __UI_STYLE_MMI_IFONE_WITH_IDLE__
    boolean bAdjustingBGPlayVol;
    SetRingToneVolume_e eVolumeLevel;
    AudioEnvSrvVolLevel_e eMediaVolumeLevel;
    CFGItemID_e eVolumeId;//record volume dialog is created by which ap
#endif
#endif //__UI_STYLE_MMI_IFONE__

} MMI_MAINMENUAPP;

#endif /* __MMI_MAINMENUAPP_PRIV_H__ */
