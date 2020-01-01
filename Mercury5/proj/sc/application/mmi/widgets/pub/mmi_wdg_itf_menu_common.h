#ifndef __MMI_WDG_ITF_MENU_COMMON_H__
#define __MMI_WDG_ITF_MENU_COMMON_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*     Menu widget, as its name implies, it shows the menu. The methodology of menu
*      is that on the menu for each item is a grid or to itemize on the two kinds
*     of display style to show. According to the menu widget to show on screen,
*     we can see the menu is composed of Item widget, List widget and Scroll-bar
*     widget. According to the size of the item style to display, when the putted items
*      number are more than the menu widget size, scroll bar will automatically
*     appear. Because there is only one entity item widget in Menu widget, so
*     in the menu widget every item must be of the same form.
*
*     In addition, the menu widget can set the softkeys. After the use of the AP
*     registers Model listener to menu widget, users touch/press key will be in the
*     model listener received by the call back function from the menu widget transponder
*     softkey event. In other words, if the AP through the menu settings no softkey
*     (directly to set softkey in view), the AP can not be in the model listener received
*     a call back of the menu transmitted softkey event.
*
*     Menu widgets can be categorized into several types: vertical, horizontal, numeric, image
*     grid, and text grid. The detail is described in the type and define section.
*
*          ex: image-grid menu widget
*           +---------------------------------+
*            | +------+  +------+  +------+   |
*            | | img  |  | img  |  | img  |   |
*            | +------+  +------+  +------+   |
*            | +------+  +------+  +------+   |
*            | | img  |  | img  |  | img  |   |
*            | +------+  +------+  +------+   |
*            | +------+  +------+  +------+   |
*            | | img  |  | img  |  | img  |   |
*            | +------+  +------+  +------+   |
*           +---------------------------------+
*
*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_itf_menu_cb.h"
#include "mmi_wdg_menu.h"
#include "mae_menulabel.h"
#include "mmi_wdg_optionmenu.h"
#include "mmi_wdg_list.h"

/*=============================================================*/
// type and define
/*=============================================================*/

#define WDG_MENU_SOFTKEY_NO_CHANGE  (SK_SOFTKEY_NUM + 1)

/*
*  CLSID_MENUWIDGET: This can also be called the vertical menu, because the
*  menu is based on the item with vertical manner. The switch is by up/down to switch item.
*
*  CLSID_HORZ_MENUWIDGET: This menu is based on the item with horizontal manner,
*  so as to look like a horizontal to switch previous or next item. For example: Idle style of the
*  event center or the first layer settings of camera.
*
*  CLSID_NUMERIC_MENUWIDGET: Such as a particular form of vertical menu widget,
*  by the name of view we can see that the menu is in digital form, that is, according to the
*  model into the order to increase the number corresponding to the front of each item.
*  Because the previous number (in fact, graphics) is a menu widget to help AP automatically
*  generated, so only the AP have to do is to fill pure text to model item.
*
*  CLSID_IMGGRID_MENUWIDGET: Such as the grid style of menu, from the name of the
*  menu we can see that this item is limited to image in the grid menu. For example: The 12 Palace
*  of the main menu or the thumbnail inside file manager.
*
*  CLSID_TXTGRID_MENUWIDGET: Such as the grid style of menu, from the name of the
*  menu we can see that this item is limited to text of grid menu. For example: Symbol table.
*/
typedef enum
{
    WDG_MENU_TYPE_NORMAL = CLSID_MENUWIDGET,
    WDG_MENU_TYPE_NUMERIC = CLSID_NUMERIC_MENUWIDGET,
    WDG_MENU_TYPE_GRID = CLSID_GRID_MENUWIDGET,
    WDG_MENU_TYPE_IMG_GRID = CLSID_IMGGRID_MENUWIDGET, //will removed
    WDG_MENU_TYPE_TXT_GRID = CLSID_TXTGRID_MENUWIDGET, //will removed
    WDG_MENU_TYPE_HORZ = CLSID_HORZ_MENUWIDGET,
    WDG_MENU_TYPE_OPTION_MENU = CLSID_OPTIONMENUWIDGET,
    WDG_MENU_TYPE_POPUPSELECT_MENU = CLSID_POPUPSELECTWIDGET,
    WDG_MENU_TYPE_NUMERIC_POPUPSELECT_MENU = CLSID_NUMERIC_POPUPSELECTWIDGET,
    WDG_MENU_TYPE_GLBOXLIST_MENU = CLSID_GLBOXLIST_WIDGET,    
} WdgMenuType_e;
typedef u32 WdgMenuType_t;
/*
*  WDG_MENU_SCROLL_STYLE_BAR: Set the menu to show scrollbar on necessary,
*  and scrollbar type is vertical bar.
*
*  WDG_MENU_SCROLL_STYLE_INDICATOR: Set the menu to show scrollbar on necessary,
*  and scrollbar type is horizontal indicator.
*
*  WDG_MENU_SCROLL_STYLE_VER_INDICATOR: Set the menu to show scrollbar on necessary,
*  and scrollbar type is vertical indicator.
*
*  WDG_MENU_SCROLL_STYLE_BAR_HORIZONTAL: Set the menu to show scrollbar on necessary,
*  and scrollbar type is horizontal bar.
*
*  WDG_MENU_SCROLL_STYLE_BAR_BOTH: Set the menu to show both vertical and horizontal scrollbars on necessary
*
*  WDG_MENU_SCROLL_STYLE_NONE: Set the menu do not show scrollbar, no matter total height of items is larger than
*  menu widget height or not.
*
*/
typedef enum
{
    WDG_MENU_SCROLL_STYLE_BAR = MENU_SCROLL_STYLE_BAR,
    WDG_MENU_SCROLL_STYLE_INDICATOR = MENU_SCROLL_STYLE_INDICATOR,
    WDG_MENU_SCROLL_STYLE_VER_INDICATOR = MENU_SCROLL_STYLE_VER_INDICATOR,
    WDG_MENU_SCROLL_STYLE_BAR_HORIZONTAL,
    WDG_MENU_SCROLL_STYLE_BAR_BOTH,
    WDG_MENU_SCROLL_STYLE_NONE
} WdgMenuScrollStyle_e;

/*
*  WDG_MENU_SCROLL_STYLE_BAR: Set the menu to show scrollbar on necessary,
*  and scrollbar type is vertical bar.
*
*  WDG_MENU_SCROLL_STYLE_INDICATOR: Set the menu to show scrollbar on necessary,
*  and scrollbar type is horizontal indicator.
*
*  WDG_MENU_SCROLL_STYLE_VER_INDICATOR: Set the menu to show scrollbar on necessary,
*  and scrollbar type is vertical indicator.
*
*  WDG_MENU_SCROLL_STYLE_BAR_HORIZONTAL: Set the menu to show scrollbar on necessary,
*  and scrollbar type is horizontal bar.
*
*  WDG_MENU_SCROLL_STYLE_BAR_BOTH: Set the menu to show both vertical and horizontal scrollbars on necessary
*
*  WDG_MENU_SCROLL_STYLE_NONE: Set the menu do not show scrollbar, no matter total height of items is larger than
*  menu widget height or not.
*
*/
typedef enum
{
    WDG_MENU_CHECK_STYLE_NONE = CHECK_RADIO_STYLE_NONE,
    WDG_MENU_CHECK_STYLE_CHECK = CHECK_RADIO_STYLE_CHECK,
    WDG_MENU_CHECK_STYLE_MARK = CHECK_RADIO_STYLE_MARK,
    WDG_MENU_CHECK_STYLE_ACTIVATE = CHECK_RADIO_STYLE_ACTIVATE,
    WDG_MENU_CHECK_STYLE_RADIO = CHECK_RADIO_STYLE_RADIO,
    WDG_MENU_CHECK_STYLE_CAMERA_MARK = CHECK_RADIO_STYLE_CAMERA_MARK,
    WDG_MENU_CHECK_STYLE_HIDE_RADIO = CHECK_RADIO_STYLE_HIDE_RADIO
} WdgMenuCheckStyle_e;
typedef u8 WdgMenuCheckStyle_t;

typedef enum
{
    WDG_MENU_GRID_STYLE_FIX_SINGLE_PAGE = GRID_FIX_LAYOUT_IN_SINGLE_PAGE,
    WDG_MENU_GRID_STYLE_FIX_MULTI_PAGE = GRID_FIX_LAYOUT_IN_MULTI_PAGE,
    WDG_MENU_GRID_STYLE_UNFIX = GRID_UNFIX_LAYOUT
} WdgMenuGridLayout_e;

typedef enum
{
    WDG_MENU_TITLE_DISPLAY_MARKED_NUM,
    WDG_MENU_TITLE_DISPLAY_TOTOAL_NUM,
    WDG_MENU_TITLE_AUTO_UPDATE,
    WDG_MENU_TITLE2_AUTO_UPDATE
} WdgMenuTitleStyle_e;

typedef enum
{
    WDG_MENU_TITLE2_OFF = TITLE2_STATUS_OFF,
    WDG_MENU_TITLE2_ON_WITH_TITLE1_BG = TITLE2_STATUS_ON_WITH_TITLE1_BG,
    WDG_MENU_TITLE2_ON_WITH_INFO_BG = TITLE2_STATUS_ON_WITH_INFO_BG,
    WDG_MENU_TITLE2_ON_WITH_CAMERA_SETTING_BG = TITLE2_STATUS_ON_WITH_CAMERA_SETTING_BG,
    WDG_MENU_TITLE2_ON_WITH_CAMERA_LANDSCAPE_SETTING_BG = TITLE2_STATUS_ON_WITH_CAMERA_LANDSCAPE_SETTING_BG,
    WDG_MENU_TITLE2_ON_WITH_NONE_BG = TITLE2_STATUS_ON_WITH_NONE_BG,
} WdgMenuTitle2State_e;

typedef enum
{
    WDG_MENU_MARK_UNMARK,
    WDG_MENU_MARK_MARK,
    WDG_MENU_MARK_TOGGLE
} WdgMenuMark_e;

typedef enum
{
    WDG_MENU_ROLL_NONE = FLAG_NONE,
    WDG_MENU_ROLL_WRAP = FLAG_WRAP,
    WDG_MENU_ROLL_GRID_COL_WRAP = FLAG_COL_WRAP,
    WDG_MENU_ROLL_GRID_ROW_WRAP = FLAG_ROW_WRAP,
    WDG_MENU_ROLL_GRID_BOTH_WRAP,
} WdgMenuRollType_e;
typedef u16 WdgMenuRollType_t;

typedef enum
{
    WDG_MENU_MOVE_HOLD_SELECTION = GRID_TOUCH_MOVE_STYLE_HOLD_SELECTION,
    WDG_MENU_MOVE_CHANGE_SELECTION = GRID_TOUCH_MOVE_STYLE_CHANGE_SELECTION,
    WDG_MENU_MOVE_LOCATION = GRID_TOUCH_MOVE_STYLE_MOVE_LOCATION,
}WdgMenuTouchMoveStyle_e;

typedef enum
{
    WDG_MENU_TOUCH_ON_ITEM = GRID_TOUCH_MODE_SELECTOR,
    WDG_MENU_TOUCH_ON_LIST = GRID_TOUCH_MODE_CONTAINER,
} WdgMenuTouchModeType_e;

typedef enum {
	WDG_MENU_TOUCH_SLIDING_DIRECTION_NONE,	/**< disable touch sliding */
	WDG_MENU_TOUCH_SLIDING_DIRECTION_VERTICAL,	/**< enable vertical sliding */
	WDG_MENU_TOUCH_SLIDING_DIRECTION_HORIZONTAL,	/**< enable horizontal sliding */
}WdgMenuTouchSlidingDirection_e;
typedef u8 WdgMenuTouchSlidingDirection_t;

typedef enum
{
    WDG_MENU_FIXED_ROW = FIXED_ROW,
    WDG_MENU_FIXED_COL = FIXED_COLUMN
} WdgMenuFixedDir_e;

typedef enum {
	MENU_FIRST_INDEX_ADJRULE_NONE = FIRST_INDEX_ADJRULE_NONE,      // Do not adjust when user set first index
	MENU_FIRST_INDEX_ADJRULE_FILL_PAGE = FIRST_INDEX_ADJRULE_FILL_PAGE,   // If the first index user set is larger than the first of last page, reset the first index to the first index of last page

}WdgMenuFistIdxAdjRule_e;

typedef struct
{
    u8 u8HorzNum;
    u8 u8VertNum;
    GridLayoutType_t eLayoutType;
} WdgGridStyleInfo_t;

typedef struct
{
    u32 u32ArrowUnPressId;
    u32 u32ArrowPressId;
} WdgMenuScrollImage_t;

typedef struct
{
    WdgMenuScrollImage_t sPreArrow;
    WdgMenuScrollImage_t sNextArrow;
} WdgMenuScrollArrowImages_t;

typedef struct
{
    u32 u32Width;
    u32 u32Height;
} WdgMenuItemSize_t;

typedef WdgItemPos_t WdgMenuItemPos_t;


typedef void (*PfnWdgMenuItemDrawNotifier) (void *pApplet, ItemInfo_st *pstItemInfo);

/** WdgMenuCreateForWnd
* @brief        Create Menu widget with size and position on window
*
* @param[in]    hWin          The window handle
* @param[in]    pPos             A pointer of widget position; can't be NULL.
* @param[in]    pSize            A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID        The widget unique ID of window
* @param[in]    eMenuType        The menu type
*
* @retval       The pointer of Menu      Success.
* @retval       NULL                     Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgMenuCreateForWnd
(
    HWIN             hWin,
    Pos_t                   *pPos,
    WidgetSize_t            *pSize,
    u16                     nWidgetID,
    WdgMenuType_e          eMenuType
);

/** WdgMenuCreate
* @brief        Create Menu widget
*
* @param[in]    eMenuType        The menu type
*
* @retval       The pointer of Menu      Success.
* @retval       NULL                     Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgMenuCreate
(
    WdgMenuType_e          eMenuType
);

/* common menu property */

/** WdgMenuSetCheckStyle
* @brief Set menu widget with check icon and assign the check style.
*
* @param[in]    pMenu: The menu widget pointer
* @param[in]    eCheckStyle: The check style. ref. WdgMenuCheckStyle_e
*
* @retval       NONE.
*
*/
__SLDPM_FREE__ void WdgMenuSetCheckStyle(IWidget *pMenu, WdgMenuCheckStyle_e eCheckStyle);

/** WdgMenuSetToOneLineStyle
* @brief Set menu widget to display each items in a line
*
* @param[in]    pMenu: The menu widget pointer
*
* @retval       NONE.
*
*/
__SLDPM_FREE__ void WdgMenuSetToOneLineStyle(IWidget *pMenu);

/** WdgMenuSetToTwoLineStyle
* @brief Set menu widget to display each items with two lines.
*
* @param[in]    pMenu: The menu widget pointer
* @param[in]    bTwoLineWhenFocus: FALSE - alwayse display each items with two lines
*                                                     TRUE - only the highlight itme displayed in two line,
*                                                                 and the others item displayed in one line.
*
* @retval       NONE.
*
*/
void WdgMenuSetToTwoLineStyle(IWidget *pMenu, boolean bTwoLineWhenFocus);

/** WdgMenuSetToGridStyle
* @brief Set menu widget to display item in a grid.
*
* @param[in]    pMenu: The menu widget pointer
* @param[in]    sStyleInfo: Set the row and colum items num in a grid, and grid layout style.
*                      ref. WdgGridStyleInfo_t
*
* @retval       NONE.
*
*/
void WdgMenuSetToGridStyle(IWidget *pMenu, WdgGridStyleInfo_t sStyleInfo);

/** WdgMenuSetScrollStyle
* @brief Set menu widget scroll style and scroll arrow images.
*
* @param[in]    pMenu: The menu widget pointer
* @param[in]    eStyle: The scrollbar style. ref. WdgMenuScrollStyle_e
* @param[in]    psScrollImages: The scrollbar arrow images, if won't to change default arrow images, assign NULL pointer
*
* @retval       NONE.
*
*/
void WdgMenuSetScrollStyle(IWidget *pMenu, WdgMenuScrollStyle_e eStyle, WdgMenuScrollArrowImages_t *psScrollImages);

/** WdgMenuSetOptionMenuStyle
* @brief Set menu widget's option menu style
*
* @param[in]    pMenu: The menu widget pointer
* @param[in]    eStyle: The check style. ref. OptionMenuStyle_t
*
* @retval       NONE.
*
*/
__INLINE void WdgMenuSetOptionMenuStyle(IWidget *pMenu, OptionMenuStyle_t eStyle)
{
	WdgCommonSetProperty(pMenu, PROP_MENU_WDG_OPTIONMENU_STYLE, (u32)eStyle);
}

/** WdgMenuSetSoftkeys
* @brief Set menu widget default softkeys id. If a item softkeys id are "DEFAULT_SK",
*           menu widget will set default softkey id to softkey on view.
*
* @param[in]    pMenu: The menu widget pointer.
* @param[in]    u32LeftId: The left softkey id. if won't change current setting, use WDG_MENU_SOFTKEY_NO_CHANGE
* @param[in]    u32MiddleId: The middle softkey id. if won't change current setting, use WDG_MENU_SOFTKEY_NO_CHANGE
* @param[in]    u32RightId: The middle softkey id. if won't change current setting, use WDG_MENU_SOFTKEY_NO_CHANGE
*
* @retval       NONE.
*
*/
__SLDPM_FREE__ void WdgMenuSetSoftkeys(IWidget *pMenu, u32 u32LeftId, u32 u32MiddleId, u32 u32RightId);

/** WdgMenuSetAllowModifySoftkeys
* @brief Set menu widget allow to modify softkey or not
*
* @param[in]    pMenu: The menu widget pointer.
* @param[in]    bAllow: TRUE/FALSE (Allow or not)
*
* @retval       NONE.
*
*/
__INLINE void WdgMenuSetAllowModifySoftkeys(IWidget *pMenu, boolean bAllow)
{
	WdgCommonSetProperty(pMenu, PROP_MENU_WDG_ALLOW_TO_MODIFY_SOFTKEY, bAllow);
}

/** WdgMenuSetUnavailSoftkeys
* @brief Set menu widget unavailable softkey ids. If the menu is unavailable,
*           menu will set unavailable softkey ids to softkey on view. for example, if the marked item number are reached
*           max marked items number, the menu will set softkey with unavailable softkey ids
*
* @param[in]    pMenu: The menu widget pointer.
* @param[in]    u32LeftId: The left softkey id. if won't change current setting, use WDG_MENU_SOFTKEY_NO_CHANGE
* @param[in]    u32MiddleId: The middle softkey id. if won't change current setting, use WDG_MENU_SOFTKEY_NO_CHANGE
* @param[in]    u32RightId: The middle softkey id. if won't change current setting, use WDG_MENU_SOFTKEY_NO_CHANGE
*
* @retval       NONE.
*
*/
void WdgMenuSetUnavailSoftkeys(IWidget *pMenu, u32 u32LeftId, u32 u32MiddleId, u32 u32RightId);

/** WdgMenuSetNumericControlOn
* @brief Set menu widget can be control by pressing numeric keypads. 1 is mapping to select first item on menu, ect.
*
* @param[in]    pMenu: The menu widget pointer.
* @param[in]    bOn: FALSE - Control off
*                              TRUE - Control on
*
* @retval       NONE.
*
*/
__SLDPM_FREE__ void WdgMenuSetNumericControlOn(IWidget *pMenu, boolean bOn);

/** WdgMenuSetMenuBGImage
* @brief Set menu widget background image by image id.
*
* @param[in]    pMenu: The menu widget pointer.
* @param[in]    u32ImageId: Background image id
*
* @retval       NONE.
*
*/
void WdgMenuSetMenuBGImage(IWidget *pMenu, u32 u32ImageId);

void WdgMenuSetItemID(IWidget *pMenu, u32 u32Index, u32 u32ItemId);
void WdgMenuSetItemSoftkeys(IWidget *pMenu, u32 u32ItemIndex, u32 u32LeftId, u32 u32MiddleId, u32 u32RightId);
void WdgMenuSetItemHasChild(IWidget *pMenu, u32 u32ItemIndex, boolean bHasChild);
__SLDPM_FREE__ void WdgMenuSetFirstItem(IWidget *pMenu, u32 u32ItemIndex);
__SLDPM_FREE__ void WdgMenuSetHighlightedItem(IWidget *pMenu, u32 u32ItemIndex);
void WdgMenuSetMaxMarkedItemNum(IWidget *pMenu, u32 u32MaxNum);
void WdgMenuSetMinMarkedItemNum(IWidget *pMenu, u32 u32MinNum);
__SLDPM_FREE__ void WdgMenuSetItemMarked(IWidget *pMenu, u32 u32Index, WdgMenuMark_e eMark);

void WdgMenuSetItemDispBGOnly(IWidget *pMenu, u32 u32Index, boolean bDispBG);
void WdgMenuSetAllItemMarked(IWidget *pMenu, boolean bMark);
__SLDPM_FREE__ void WdgMenuSetItemFocusImage(IWidget *pMenu, u32 u32ImageId);
void WdgMenuSetItemUnFocusImage(IWidget *pMenu, u32 u32ImageId);
__SLDPM_FREE__ void WdgMenuSetItemUnderLine(IWidget *pMenu, boolean bUnderLine);
void WdgMenuSetTitleById(IWidget *pMenu, u32 u32TextId);
void WdgMenuSetTitleByStr(IWidget *pMenu, MAE_WChar *pwText);
__SLDPM_FREE__ void WdgMenuSetTitleDisplayStyle(IWidget *pMenu, WdgMenuTitleStyle_e u32Style, boolean bOn);
__SLDPM_FREE__ void WdgMenuSetTitle2ById(IWidget *pMenu, u32 u32TextId);
MAE_Ret WdgMenuSetTitle2ByStr(IWidget *pMenu, MAE_WChar *pwText);
MAE_Ret WdgMenuSetTitle2State(IWidget *pMenu, WdgMenuTitle2State_e eState);
__SLDPM_FREE__ void WdgMenuSetEmptyTextId(IWidget *pMenu, u32 u32TextId);
void WdgMenuSetEmptyTextColor(IWidget *pMenu, u32 u32RGBColor);
void WdgMenuShowEmptyText(IWidget *pMenu, boolean bShow);
void WdgMenuSetAutoToggle(IWidget *pMenu, boolean bAutoToggle);
void WdgMenuSetHighlightBGEnable(IWidget *pMenu, boolean bEnable);
void WdgMenuSetUserActionSoftkeyId(IWidget *pMenu, u32 u32SoftkeyId);
void WdgMenuSetUserBackSoftkeyId(IWidget *pMenu, u32 u32SoftkeyId);


/** WdgMenuSetItemBGColor
* @brief        Set the background color for unfocused item widget
*
* @param[in]    pWDGMenu         The pointer of IWidget interface object
* @param[in]    nRBgColor         RGBColor_t value. the return value of MAKE_RGB()
*
* @retval       void
*
*/
__INLINE void WdgMenuSetItemBGColor(IWidget *pWDGMenu, RGBColor_t nRBgColor)
{
    WdgCommonSetProperty(pWDGMenu, PROP_UNFCS_ITEM_BG_COLOR, (u32)nRBgColor);
}

/** WdgMenuSetItemBGImageId
* @brief        Set the background image for unfocused item widget
*
* @param[in]    pWDGMenu       The pointer of IWidget interface object
* @param[in]    u32ImageId     Image ID.
*
* @retval       MAE_Ret
*
*/
__INLINE void WdgMenuSetItemBGImageId(IWidget *pWDGMenu, u32 u32ImageId)
{
    WdgCommonSetProperty(pWDGMenu, PROP_MENU_WDG_UNFCS_ITEM_BG_IMAGE_ID, u32ImageId);
}

/** WdgMenuSetFCSItemBGColor
* @brief        Set the background color for focused item widget
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    nRBgColor         RGBColor_t value. the return value of MAKE_RGB()
*
* @retval        void
*
*/
__INLINE void WdgMenuSetFocusItemBGColor(IWidget *pWDGMenu, RGBColor_t nRBgColor)
{
    WdgCommonSetProperty(pWDGMenu, PROP_FCS_ITEM_BG_COLOR, nRBgColor);
}

/** WdgMenuSetFocusItemBGImageId
* @brief        Set the background image for focused item widget
*
* @param[in]    pWDGMenu       The pointer of IWidget interface object
* @param[in]    u32ImageId     Image ID.
*
* @retval       MAE_Ret
*
*/
__INLINE void WdgMenuSetFocusItemBGImageId(IWidget *pWDGMenu, u32 u32ImageId)
{
    WdgCommonSetProperty(pWDGMenu, PROP_MENU_WDG_FCS_ITEM_BG_IMAGE_ID, u32ImageId);
}

/** WdgMenuSetSelItemSize
* @brief        Set the selected item size(width or height), Can be changed in LIST_STYLE_GRID style only.
*
* @param[in]    pWDGMenu       The pointer of IWidget interface object
* @param[in]    u16ItemSize         Item size in pixels to be set.
*
* @retval        void
*/
__INLINE void WdgMenuSetFocusItemSize(IWidget *pWDGMenu, u16 u16ItemSize)
{
    WdgCommonSetProperty(pWDGMenu, PROP_SEL_ITEMSIZE, (u32)u16ItemSize);
}

/** WdgMenuSetFlag
* @brief        Set List widget flag for wrap and select event handle configuration to decide the behavior.
*
* @param[in]    pWDGMenu    The pointer of IWidget interface object
* @param[in]    eRollType   Flags refer to FLAG_NONE, FLAG_WRAP, FLAG_COL_WRAP, FLAG_ROW_WRAP, FLAG_NO_SEL
*
*                                 Example:
*                                 COLUMN mode:
*                                 | 0 1 2 |
*                                 | 3 4 5 |
*                                 | 6 7 8 |
*                                 1,
*                                    FLAG_WRAP turn on and press key down: 0->3->6->1->4->7->2->5->8->0->...
*                                    FLAG_WRAP turn off and press key down:0->3->6->1->4->7->2->5->8
*                                 2,
*                                    FLAG_COL_WRAP turn on and press key down: 0->3->6->0->3->6->0->...
*
* @retval       void
*
*/
void WdgMenuSetRollType(IWidget *pWDGMenu, WdgMenuRollType_e eRollType);

/** WdgMenuSetItemDrawNotifier
* @brief        To set a notifier callback while drawing an item
*
* @param[in]    pWDGMenu         The pointer of IWidget interface object
* @param[in]    pfn              Callback function
* @param[in]    pUserData            User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
void WdgMenuSetItemDrawNotifier(IWidget *pWDGMenu, PfnWdgMenuItemDrawNotifier pfn, void *pUserData);


/** WdgMenuSetAnimOnFocused
* @brief        Only play item widget animation(e.g. text sliding) when menu widget was on focused
*
* @param[in]    bAnimOnFocused: FALSE - Animation played no matter on focused or not
*                              TRUE - Only play item widget animation when widget is focused
* @retval       void
*
*/
void WdgMenuSetAnimOnFocused(IWidget *pMenu, boolean bAnimOnFocused);

/** WdgListSetItemWidth
* @brief        Set the width of item in pixels
*
* @param[in]    pWDGMenu        The pointer of IWidget interface object
* @param[in]    nItemWidth        The width of item in pixels
*
* @retval        void
*
*/
__INLINE void WdgMenuSetItemWidth(IWidget *pWDGMenu, u16 nItemWidth)
{
    WdgCommonSetProperty(pWDGMenu, PROP_ITEM_WIDTH, (u32)nItemWidth);
}

/** WdgListSetItemHeight
* @brief        Set the height of item in pixels
*
* @param[in]    pWDGMenu        The pointer of IWidget interface object
* @param[in]    nItemHeight       The height of item in pixels
*
* @retval       void
*
*/
__INLINE void WdgMenuSetItemHeight(IWidget *pWDGMenu, u16 nItemHeight)
{
    WdgCommonSetProperty(pWDGMenu, PROP_ITEM_HEIGHT, (u32)nItemHeight);
}

/** WdgListSetRowGap
* @brief        Set row gap in pixel between every item.
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    nItemRowGap     The space in pixels between row items
*
* @retval      void
*
*/
__INLINE void WdgMenuSetRowGap(IWidget *pWDGMenu, u16 nItemRowGap)
{
    WdgCommonSetProperty(pWDGMenu, PROP_WDG_ROW_GAP, (u32)nItemRowGap);
}

/** WdgListSetColGap
* @brief        Set column gap in pixel between every item.
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    nItemColGap       The space in pixels between column items
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE void WdgMenuSetColGap(IWidget *pWDGMenu, u16 nItemColGap)
{
    WdgCommonSetProperty(pWDGMenu, PROP_WDG_COL_GAP, (u32)nItemColGap);
}

/** WdgMenuSetFixedDirection
* @brief        Set the direction(row or column) to be fixed, Can be changed in LIST_STYLE_GRID style only.
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    eFixedDir         The direction(row or column) to be fixed
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE void WdgMenuSetFixedDirection(IWidget *pWDGMenu, WdgMenuFixedDir_e eFixedDir)
{
    WdgCommonSetProperty(pWDGMenu, PROP_FIXED_DIRECTION, (u32)eFixedDir);
}

/** WdgMenuSetFixedNum
* @brief        Set the fixed number, Can be changed in LIST_STYLE_GRID style only
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    u16FixedNum         The fixed row / column numbers, must bigger than zero
*
* @retval        void
*
*/
__INLINE void WdgMenuSetFixedNum(IWidget *pWDGMenu, u16 u16FixedNum)
{
    WdgCommonSetProperty(pWDGMenu, PROP_FIXED_NUM, (u32)u16FixedNum);
}

/** WdgMenuSetFirstItemAdjustRule
* @brief        Set the adjust rule when set first index
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    nRule             The adjust rule, MENU_FIRST_INDEX_ADJRULE_NONE / MENU_FIRST_INDEX_ADJRULE_FILL_PAGE
*
* @retval       void
*
*/
__INLINE void WdgMenuSetFirstItemAdjustRule(IWidget *pWDGMenu, WdgMenuFistIdxAdjRule_e nRule)
{
    WdgCommonSetProperty(pWDGMenu, PROP_FIRST_INDEX_ADJUST_RULE, nRule);
}

void WdgMenu_GetCacheInfo(IWidget *pWDGMenu, MenuModelEntityData_t *ptEntityIdx);

void WdgMenu_SetCacheInfo(IWidget *pWDGMenu, u16 u16DiffSize, u16 u16MaxSize);

#ifdef __TOUCH_SCREEN_MMI__
/** WdgMenuSetTouchMode
* @brief        Set the way deal with touch event
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    eTouchMode        the way deal with touch event
*
* @retval       void
*
*/
__INLINE void WdgMenuSetTouchMode(IWidget *pWDGMenu, WdgMenuTouchModeType_e eTouchMode)
{
    WdgCommonSetProperty(pWDGMenu, PROP_GRID_WDG_TOUCH_MODE, (u32)eTouchMode);
}

/** WdgMenuSetTouchMoveStyle
* @brief        Set the way deal with the touch moving ouside the hightlight item
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    eMoveType        The way deal with the touch moving ouside the hightlight item
*
* @retval        void
*
*/
__INLINE void WdgMenuSetTouchMoveStyle(IWidget *pWDGMenu, WdgMenuTouchMoveStyle_e eMoveType)
{
    WdgCommonSetProperty(pWDGMenu, PROP_GRID_WDG_TOUCH_MOVE_STYLE, (u32)eMoveType);
}

/** WdgMenuSetTouchSelected
* @brief        Enable/Disable Notify Select after released at highlight item
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    bTouchSelected    Set NotifySelect or not
*
* @retval        void
*
*/
__INLINE void WdgMenuSetTouchSelected(IWidget *pWDGMenu, boolean bTouchSelected)
{
    WdgCommonSetProperty(pWDGMenu, PROP_GRID_WDG_TOUCH_SELECTED, (u32)bTouchSelected);
}

/** WdgMenuSetDisableHandleTouchEvt
* @brief        Set TRUE to disable handle touch event.
*
* @param[in]    pWDGMenu                  The pointer of IWidget interface object
* @param[in]    bDisableHandleTouchEvt    Set TRUE or FALSE
*
* @retval        void
*
*/
__INLINE void WdgMenuSetDisableHandleTouchEvt(IWidget *pWDGMenu, boolean bDisableHandleTouchEvt)
{
    WdgCommonSetProperty(pWDGMenu, PROP_DISABLE_HANDLE_TOUCH_EVT, (u32)bDisableHandleTouchEvt);
}

/** WdgMenuSetChangefocusOnTouch
* @brief        Set the property to determine if a widget need to set focus automatically while touch press.
*
* @param[in]    pWDGMenu                  The pointer of IWidget interface object
* @param[in]    bChangefocusOnTouch        Set TRUE or FALSE
*
* @retval        void
*
*/
__INLINE void WdgMenuSetChangeFocusOnTouch(IWidget *pWDGMenu, boolean bChangefocusOnTouch)
{
    WdgCommonSetProperty(pWDGMenu, PROP_WDG_CHANGEFOCUS_ON_TOUCH, (u32)bChangefocusOnTouch);
}

/** WdgMenuSetTouchSlidingDirection
* @brief        Set the touch sliding direction (vertical / horizontal / none)
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    eDirection			  The direction
*												 WDG_MENU_TOUCH_SLIDING_DIRECTION_NONE,	 disable touch sliding 
*												 WDG_MENU_TOUCH_SLIDING_DIRECTION_VERTICAL,	 enable vertical sliding, only for vertical/grid menu
*												 WDG_MENU_TOUCH_SLIDING_DIRECTION_HORIZONTAL,	 enable horizontal sliding, only for horizontal/grid menu
* @retval        void
*
*/
__INLINE void WdgMenuSetTouchSlidingDirection
(
    IWidget                 *pWDGMenu,
    WdgMenuTouchSlidingDirection_e eDirection
)
{
	WdgCommonSetProperty(pWDGMenu, PROP_MENU_WDG_TOUCH_SLIDING_DIRECTION, (u32)eDirection);
}
#endif // __TOUCH_SCREEN_MMI__

__SLDPM_FREE__ MAE_Ret WdgMenuGetMenuType(IWidget *pMenu, WdgMenuType_e *peMenuType);
IWidget* WdgMenuGetLayer2Menu(IWidget *pMenu);
MAE_Ret WdgMenuGetSoftkeys(IWidget *pMenu, u32 *pu32LeftId, u32 *pu32MiddleId, u32 *pu32RightId);
MAE_Ret WdgMenuGetCheckStyle(IWidget *pMenu, WdgMenuCheckStyle_e *peCheckStyle);
MAE_Ret WdgMenuGetMarkedNum(IWidget *pMenu, u32 *pMarkedNum);
__SLDPM_FREE__ MAE_Ret WdgMenuGetMaxItemOnScreen(IWidget *pMenu, u32 *pMaxItemNum);
MAE_Ret WdgMenuGetItemID(IWidget *pMenu, u32 u32Index, u32 *pu32ItemId);
__SLDPM_FREE__ MAE_Ret WdgMenuGetItemIndexByID(IWidget *pMenu, u32 u32ItemID, u32 *pu32ItemIndex);
MAE_Ret WdgMenuGetItemSoftkeys(IWidget *pMenu, u32 u32ItemIndex, u32 *pu32LeftId, u32 *pu32MiddleId, u32 *pu32RightId);
MAE_Ret WdgMenuGetFirstItemIndex(IWidget *pMenu, u32 *pu32Index);
__SLDPM_FREE__ MAE_Ret WdgMenuGetHighlightItemIndex(IWidget *pMenu, u32 *pu32Index);
MAE_Ret WdgMenuGetItemSize(IWidget *pMenu, WdgMenuItemSize_t *psItemSize);
MAE_Ret WdgMenuItemIsHided(IWidget *pMenu, u32 u32Index, boolean *pbIsHided);
MAE_Ret WdgMenuItemIsMarked(IWidget *pMenu, u32 u32Index, boolean *pbIsMarked);
__SLDPM_FREE__ MAE_Ret WdgMenuGetMenuSize(IWidget *pMenu, u32 *pu32MenuSize);
MAE_Ret WdgMenuGetVisableMenuSize(IWidget *pMenu, u32 *pu32MenuSize);
__SLDPM_FREE__ MAE_Ret WdgMenuGetItemDataType(IWidget *pMenu, WdgMenuItemType_e *peItemType);
IWidget* WdgMenuGetItemWidget(IWidget *pMenu);
IWidget* WdgMenuGetItemComponetWidget(IWidget *pMenu, WdgMenuItemComponetId_e eComponet);
MAE_Ret WdgMenuGetItemPos(IWidget *pMenu, WdgMenuItemPos_t *psPos);

MAE_Ret WdgMenuGetCheckStatus(IWidget *pMenu, boolean* bCheckStatusArray, u32 u32CheckStatusArrayLen);
MAE_Ret WdgMenuSetCheckStatus(IWidget *pMenu, boolean* bCheckStatusArray, u32 u32CheckStatusArrayLen);

/** WdgMenuGetHistoryInfo
* @brief        get the menu widget's history info
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
* @param[in]    ppHisInfo				The pointer to a HistoryInfo_t structure, recorded the returned info
*
*
* @retval        None
*
*/
MAE_Ret WdgMenuGetHistoryInfo(IWidget *pWDGMenu, HistoryInfo_t **ppHisInfo);

/** WdgListMoveToNextItem
* @brief        To move the focus to next item of list.
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
*
*
* @retval        None
*
*/
void WdgMenuMoveToNextItem(IWidget *pWDGMenu);

/** WdgMenuMoveToPreviousItem
* @brief        To move the focus to previous item of list.
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
*
*
* @retval        None
*
*/
void WdgMenuMoveToPreviousItem(IWidget *pWDGMenu);

boolean WdgMenuCheckItemInCachedData(IWidget *pWDGMenu, u32 u32Index);


/** 
* for auto testing
*/
#ifdef __NEW_AUTO_TESTING__
#define AUTO_TEST_MAX_SEARCH_ITEM		40
#define MAX_TEST_LEN                    255
#endif


#endif //__MMI_WDG_ITF_MENU_COMMON_H__


