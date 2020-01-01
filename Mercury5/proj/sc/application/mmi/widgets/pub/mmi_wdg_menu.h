#ifndef __MMI_WDG_MENU_H__
#define __MMI_WDG_MENU_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_mae_menumodel.h"
/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct
{
    IWidget *pIWidget;
    void *pOwner;
} MAE_MenuGetItemWidget_t;

typedef struct
{
    IWidget *pIWidget;
    MAE_ClsId eClsId;
} MAE_MenuSetItemWidget_t;

typedef u8 GridLayoutType_t;
enum {
	GRID_FIX_LAYOUT_IN_SINGLE_PAGE,	/* the grid layout is fixed with no scroll bar no matter how many items */
	GRID_FIX_LAYOUT_IN_MULTI_PAGE,	/* the grid layout is fixed with scroll bar no matter how many items */
	GRID_UNFIX_LAYOUT				/* the grid layout is NOT fixed no matter how many items */
};

typedef struct {
	u8 nHorzNum;					/* the total item number of horizontal dimension -> for grid menu usage */
	u8 nVertNum;					/* the total item number of vertical dimension -> for grid menu usage */
	GridLayoutType_t eLayoutType;	/* the layout type of this assigned grid view */
} GridItemNumInfo_t;

typedef u8 AutoUpdate_t;
enum {
	AUTO_UPDATE_NONE,
	AUTO_UPDATE_ON_TITLE_1,
	AUTO_UPDATE_ON_TITLE_2
};

typedef u8 Title2Status_t;
enum {
	TITLE2_STATUS_OFF,
	TITLE2_STATUS_ON_WITH_TITLE1_BG,
	TITLE2_STATUS_ON_WITH_INFO_BG,
	TITLE2_STATUS_ON_WITH_CAMERA_SETTING_BG,
    TITLE2_STATUS_ON_WITH_CAMERA_LANDSCAPE_SETTING_BG,
    TITLE2_STATUS_ON_WITH_NONE_BG
};

typedef u8 ScrollStyle_t;
enum {
    MENU_SCROLL_STYLE_BAR,
    MENU_SCROLL_STYLE_INDICATOR,
    MENU_SCROLL_STYLE_VER_INDICATOR,
    MENU_SCROLL_STYLE_BAR_HORIZONTAL,
    MENU_SCROLL_STYLE_BAR_BOTH,
    MENU_SCROLL_STYLE_NONE
};

typedef u8 OptionMenuStyle_t;
enum {
	OPTIONMENU_STYLE_NONE,
	OPTIONMENU_STYLE_LEVEL_1,
	OPTIONMENU_STYLE_LEVEL_2,
	OPTIONMENU_STYLE_POPUP_SELECT
};

typedef u8 ItemDisplayStyle_t;
enum
{
	ITEM_DISP_STYLE_START = 0x00,
	ITEM_DISP_STYLE_ALWAYS_ONELINE = 0x00,
	ITEM_DISP_STYLE_ALWAYS_TWOLINE = 0x10,
	ITEM_DISP_STYLE_TWOLINE_WHENFOCUS = 0x20,
	ITEM_DISP_STYLE_GRID = 0x30,
	ITEM_DISP_STYLE_TOTAL = 0x40,
	ITEM_DISP_STYLE_MASK = 0xF0
};

#if defined(__FEATURE_MGL__)
enum
{
	MENU_ANIMATION_FLIP_1ST_ITEM = 0,
	MENU_ANIMATION_FLIP_2ND_ITEM,
	MENU_ANIMATION_FLIP_3RD_ITEM,
	MENU_ANIMATION_FLIP_4TH_ITEM,
	MENU_ANIMATION_FLIP_5TH_ITEM,
	MENU_ANIMATION_FLIP_6TH_ITEM,
	MENU_ANIMATION_FLIP_7TH_ITEM,
	MENU_ANIMATION_FLIP_8TH_ITEM,
	MENU_ANIMATION_FLIP_9TH_ITEM,
	MENU_ANIMATION_FLIP_10TH_ITEM,
	MENU_ANIMATION_FLIP_11TH_ITEM,
	MENU_ANIMATION_FLIP_12TH_ITEM,
	MENU_ANIMATION_FLIP_13TH_ITEM,
	MENU_ANIMATION_FLIP_14TH_ITEM,
	MENU_ANIMATION_FLIP_15TH_ITEM,
    MENU_ANIMATION_FLIP_ITEM_MAX,
};
typedef u8 FlipItemOrder_e;

enum
{
	MENU_ANIMATION_STATE_1ST_ITEM_START = 0,
	MENU_ANIMATION_STATE_2ND_ITEM_START,
	MENU_ANIMATION_STATE_3RD_ITEM_START,
	MENU_ANIMATION_STATE_4TH_ITEM_START,
	MENU_ANIMATION_STATE_5TH_ITEM_START,
	MENU_ANIMATION_STATE_6TH_ITEM_START,
	MENU_ANIMATION_STATE_7TH_ITEM_START,
	MENU_ANIMATION_STATE_8TH_ITEM_START,
	MENU_ANIMATION_STATE_9TH_ITEM_START,
	MENU_ANIMATION_STATE_10TH_ITEM_START,
	MENU_ANIMATION_STATE_11TH_ITEM_START,
	MENU_ANIMATION_STATE_12TH_ITEM_START,
	MENU_ANIMATION_STATE_13TH_ITEM_START,
	MENU_ANIMATION_STATE_14TH_ITEM_START,
	MENU_ANIMATION_STATE_15TH_ITEM_START,
	MENU_ANIMATION_STATE_ALL_ITEM_END,
	MENU_ANIMATION_STATE_EMPTY
};
typedef u8 FlipItemAnimationState_e;

//item action for menu flip complete
typedef boolean ( *PfnMenuWidgetFlipComplete ) ( IWidget *pMenu, void *pUserData );
#endif

//item action for menu tree
typedef boolean ( *PfnMenuWidgetTreeAction ) ( IWidget *pMenu, u32 u32ItemId, void *pUserData );

//item back for menu tree
typedef boolean ( *PfnMenuWidgetTreeBack ) ( IWidget *pMenu, void *pUserData );

//menu tree free function
typedef void ( *PfnMenuWidgetTreeFree ) ( IWidget *pMenu, void *pUserData );

//menu animation complete cb
typedef void (*PfnMenuWidgetAniEnd) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

typedef struct
{
    PfnMenuWidgetTreeAction pfAction;
    PfnMenuWidgetTreeBack pfBack;
    PfnMenuWidgetTreeFree pfFree;
    void *pUserData;
} MaeMenuWidgetTree_t;

#define MAX_CHECKED_NUM_ALL		0xFFFF
#define MIN_CHECKED_NUM_NONE	0x0000

#define MENUWIDGET_UNDEFINE_IMAGE_ID		0xFFFFFFFF

/*=============================================================*/
// macro property interface
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/
MAE_Ret MenuWidgetRegisterAniStatusCb(IWidget *pMenuWdg, PfnMenuWidgetAniEnd pfn,void *pUserData);
MAE_Ret MenuWidgetDeregisterAniStatusCb(IWidget *pMenuWdg, PfnMenuWidgetAniEnd pfn,void *pUserData);

// Please check mmi_wdg_itf_menu_common.h and mmi_wdg_itf_menu.h

#endif //__MMI_WDG_MENU_H__
/*=============================================================*/
// end of file
