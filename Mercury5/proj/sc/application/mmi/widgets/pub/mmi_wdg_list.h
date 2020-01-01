/**
*  If AP wants to show more than one the same object on the screen, it can choose
*  List widget. Two types of List widget, one is Horizontal List orders each items
*  with the horizontal direction; the other is Vertical List orders each items in the
*  vertical direction. The list items can be Text widget, Bitmap, widget, Image
*  widget, etc. But not all of the widget can be the Item widget though. The Horizontal
*  List and Vertical List are illustrated below. There are several arrangement types to
*  present items and highlight focused items in the List widget, which depicted in
*  type and define section.
*
*         ex: Horizontal List widget
*       +---------------------------------+
*       |  Item  |  Item |  Item | Item   |
*       |   1    |    2  |    3  |   4    |
*       +---------------------------------+
*
*         ex: Vertical List widget
*             +------------+
*              |    Item 1 |
*              |-----------|
*              |    Item 2 |
*              |-----------|
*              |    Item 3 |
*              |-----------|
*              |    Item 4 |
*              +-----------+
*
*/

#ifndef __MMI_WDG_LIST_H__
#define __MMI_WDG_LIST_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_wdg_itf_menu_item.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

#define DEFAULT_FIXED_SIZE_GRID		3
#define DEFAULT_FIXED_SIZE_LIST		1

//the flags for list widget(PROP_FLAG)
#define	FLAG_NONE			0x0FFF
#define	FLAG_WRAP			0x1000	//wrap to first/last element (list mode or grid mode)
#define	FLAG_COL_WRAP		0x2000	//single column wrap (for grid only)
#define	FLAG_ROW_WRAP		0x4000	//single row warp (for grid only)
#define	FLAG_NO_SEL			0x8000	//set this flag if not want to handle select event
//Notice: The priority of FLAG_COL_WRAP/FLAG_ROW_WRAP is higher than FLAG_WRAP

// property value for PROP_FIRST_INDEX_ADJUST_RULE
typedef enum {
	FIRST_INDEX_ADJRULE_NONE = 0,      // Do not adjust when user set first index
	FIRST_INDEX_ADJRULE_FILL_PAGE,   // If the first index user set is larger than the first of last page, reset the first index to the first index of last page
	
	FIRST_INDEX_ADJRULE_END
}ListWdgFistIdxAdjRule_e;
typedef u8 ListWdgFistIdxAdjRule_t;

//property value for (PROP_FIXED_DIRECTION)
typedef enum {
	FIXED_COLUMN = 0,
	FIXED_ROW
} ListWdgFixedDir_e;

// property value for PROP_GRID_WDG_TOUCH_MODE
typedef enum {
	GRID_TOUCH_MODE_SELECTOR = 0,		/**< this grid widget is used for selecting a item 
										and any touch event will not pass into the item inside the grid widget */
	GRID_TOUCH_MODE_CONTAINER,			/**< this grid widget is used for layout items 
										and any touch event will pass into the item widget */
	GRID_TOUCH_MODE_END
}GridTouchMode_e;
typedef u8 GridTouchMode_t;

// property value for PROP_GRID_WDG_TOUCH_MOVE_STYLE
typedef enum {
	GRID_TOUCH_MOVE_STYLE_HOLD_SELECTION = 0,   /**< touch moving will not cause the selection change */
	GRID_TOUCH_MOVE_STYLE_CHANGE_SELECTION,     /**< if the touch moving leave the area of highlight item, 
	                                                 grid widget will try to hightlight the other item and send 
	                                                 the event to the new item */
	GRID_TOUCH_MOVE_STYLE_MOVE_LOCATION,  /**< highlight item will not change, but the location 
	                                                         of highlight will change by touch moving */
	GRID_TOUCH_MOVE_STYLE_END
}GridTouchMoveStyle_e;
typedef u8 GridTouchMoveStyle_t;

// property value for PROP_GRID_WDG_TOUCH_AS_STYLE
// notice that, so far the GRID_TOUCH_AS_STYLE_FINGERCMD is not ready for using
typedef enum {
	GRID_TOUCH_AS_STYLE_NONE = 0,
	GRID_TOUCH_AS_STYLE_PULL_AND_HOLD,   /**< when users move the list in certain direction and exceed the 
											  threshold that is set by propery GRID_TOUCH_AS_THRESHOLD,
											  the list will keep forward/backward utill users release the touch point
											  or it reach the bottom/top of the grid */

	GRID_TOUCH_AS_STYLE_FINGERCMD,     /**< the auto-scroll is activated by a finger command, and, the list scroll
											will be stopped when another touch event occur or the grid reaches its boundary */

	GRID_TOUCH_AS_STYLE_END
}GridTouchASStype_e;
typedef u8 GridTouchASStype_t;

// property value for PROP_GRID_WDG_TOUCH_AS_SPEEDUP
// it is workable when GRID_TOUCH_AS_STYLE_PULL_AND_HOLD
typedef enum {
	GRID_TOUCH_AS_SPEEDUP_NONE = 0,
	GRID_TOUCH_AS_SPEEDUP_DISTANCE,   /**< the scroll speed is up to the distance from touch position to threshold point */
	GRID_TOUCH_AS_SPEEDUP_TIME	/**< the scroll speed is up to the period that AS is activated */
}GridTouchASSpeedUp_e;
typedef u8 GridTouchASSpeedUp_t;

// property value for PROP_GRID_WDG_TOUCH_AS_THRESHOLD
// it define which point will the auto-scroll be activated (when GRID_TOUCH_AS_STYLE_PULL_AND_HOLD)
typedef enum {
	GRID_TOUCH_AS_THRESHOLD_LAST = 0,	/**< if touch position reach the last item of the screen */ 
	GRID_TOUCH_AS_THRESHOLD_SECOND_LAST   /**< if touch position reach the second last item of the screen */
}GridTouchASThreshold_e;
typedef u8 GridTouchASThreshold_t;

// property value for PROP_GRID_WDG_TOUCH_AS_MOVING
// it define the moving style each time the list will move
// and this property only be considered when the AS_Style is GRID_TOUCH_AS_STYLE_FINGERCMD
typedef enum {
	GRID_TOUCH_AS_MOVING_ONE_ITEM,	/**< each time it move up/down with distance as entire height (or width) of the item*/
	GRID_TOUCH_AS_MOVING_HALF_ITEM	/**< each time it move up/down with distance as half of item's height or width */
}GridTouchASMoving_e;
typedef u8 GridTouchASMoving_t;

typedef enum {
	GRID_TOUCH_SLIDING_DIRECTION_NONE,	/**< disable touch sliding */
	GRID_TOUCH_SLIDING_DIRECTION_VERTICAL,	/**< enable vertical sliding */
	GRID_TOUCH_SLIDING_DIRECTION_HORIZONTAL,	/**< enable horizontal sliding */
}GridTouchSlidingDirection_e;
typedef u8 GridTouchSlidingDirection_t;

// property value for PROP_GRID_WDG_ITEM_EFFECT
// it define the 3D moving style each time the list will move
typedef enum {
    GRID_ITEM_EFFECT_NONE,
    GRID_ITEM_EFFECT_HORZ_FLIP,
    GRID_ITEM_EFFECT_VERT_FLIP,
    GRID_ITEM_EFFECT_HORZ_ROLLING
}GridItemEffect_e;
typedef u8 GridItemEffect_t;


/** ItemInfo_st
*
* @brief    nIndex:     
*           bHighlight:          
*
*/
typedef struct {
	s32        nIndex;
	boolean    bHighlight;
} ItemInfo_st;


/** pfnItemDrawNotifier_t
* @brief      
*
* @param[in]  pUsrData        
* @param[in]  ItemInfo_st       
*
*/
typedef void (*pfnItemDrawNotifier_t) (void *pUsrData, ItemInfo_st *pstItemInfo);

/** ItemDrawNotifier_st
*
* @brief    pUsrData:     
*           pfnIDNfier:          
*
*/
typedef struct {
	void      *pUsrData;  ///<
	pfnItemDrawNotifier_t pfnIDNfier;
} ItemDrawNotifier_st;

/** ListStyle_e
*
* @brief        1, LIST_STYLE_GRID : Grid style list widget
*
*               (a), FIXED_COLUMN:
*               +--------------------------------+
*               |  Item 0  |  Item 1  |  Item 2  |
*               |----------+----------+----------|
*               |  Item 3  |  Item 4  |  Item 5  |
*               |----------+----------+----------|
*               |  Item 6  |  Item 7  |  Item 8  |
*               +--------------------------------+
*
*               FLAG_COL_WRAP turn on:
*                  0->3->6->0->...   1->4->7->1->...   2->5->8->2->...
*               FLAG_COL_WRAP turn off & FLAG_WRAP turn on:
*                  0->3->6->1->4->7->2->5->8->0->...
*               FLAG_COL_WRAP turn off & FLAG_WRAP turn off:
*                  0->3->6->1->4->7->2->5->8
*
*               (b), FIXED_ROW:
*               +--------------------------------+
*               |  Item 0  |  Item 3  |  Item 6  |
*               |----------+----------+----------|
*               |  Item 1  |  Item 4  |  Item 7  |
*               |----------+----------+----------|
*               |  Item 2  |  Item 5  |  Item 8  |
*               +--------------------------------+
*
*               2, LIST_STYLE_HORZ : horizontal style list widget
*
*               +-------------------------------------------+
*               |  Item 0  |  Item 1  |  Item 2  |  Item 3  |
*               +-------------------------------------------+
*
*               FLAG_WRAP turn on:
*                  0->1->2->3->0->...
*               FLAG_WRAP turn off:
*                  0->1->2->3
*
*               3, LIST_STYLE_VERT : vertical style list widget
*
*               +----------------+
*               |    Item 0      |
*               |----------------|
*               |    Item 1      |
*               |----------------|
*               |    Item 2      |
*               |----------------|
*               |    Item 3      |
*               +----------------+
*
*               FLAG_WRAP turn on:
*                  0->1->2->3->0->...
*               FLAG_WRAP turn off:
*                  0->1->2->3
*
*               4, LIST_STYLE_EXPAND : one kind of vertical style list widget,
*                                      Focused item is two line, unfocused item is one line.
*                                      Default FLAG_WRAP is on.
*
*               +--------------+
*               |    Item 0    |
*               |--------------|
*               |    Item 1    |
*               |   (Focus)    |
*               |--------------|
*               |    Item 2    |
*               |--------------|
*               |    Item 3    |
*               +--------------+
*
*               5, LIST_STYLE_ONELINE : one kind of vertical style list widget,
*                                      Focused/unfocused items are all one line, Default FLAG_WRAP is on.
*
*               +----------------+
*               |    Item 0      |
*               |----------------|
*               |    Item 1      |
*               |----------------|
*               |    Item 2      |
*               |----------------|
*               |    Item 3      |
*               +----------------+
*
*               6, LIST_STYLE_TWOLINE : one kind of vertical style list widget,
*                                      Focused/unfocused items are all two lines, Default FLAG_WRAP is on.
*
*               +-------------+
*               |    Item 0   |
*               |             |
*               |-------------|
*               |    Item 1   |
*               |             |
*               |-------------|
*               |    Item 2   |
*               |             |
*               +-------------+
*
*/

typedef enum
{
    WDG_LIST_TYPE_VERT = CLSID_VERT_LISTWIDGET,
    WDG_LIST_TYPE_HORZ = CLSID_HORZ_LISTWIDGET,
    WDG_LIST_TYPE_GRID = CLSID_GRIDWIDGET
} WdgListType_e;

typedef enum
{
    WDG_LIST_ROLL_NONE = FLAG_NONE,
    WDG_LIST_ROLL_WRAP = FLAG_WRAP,
    WDG_LIST_ROLL_GRID_COL_WRAP = FLAG_COL_WRAP,
    WDG_LIST_ROLL_GRID_ROW_WRAP = FLAG_ROW_WRAP,
    WDG_LIST_ROLL_GRID_BOTH_WRAP,
} WdgListRollType_e;

typedef enum
{
    WDG_LIST_MOVE_HOLD_SELECTION = GRID_TOUCH_MOVE_STYLE_HOLD_SELECTION,
    WDG_LIST_MOVE_CHANGE_SELECTION = GRID_TOUCH_MOVE_STYLE_CHANGE_SELECTION,
    WDG_LIST_MOVE_LOCATION = GRID_TOUCH_MOVE_STYLE_MOVE_LOCATION,
}WdgListTouchMoveStyle_e;

typedef enum
{
    WDG_LIST_TOUCH_ON_ITEM = GRID_TOUCH_MODE_SELECTOR,
    WDG_LIST_TOUCH_ON_LIST = GRID_TOUCH_MODE_CONTAINER,
} WdgListTouchModeType_e;

typedef enum
{
    WDG_LIST_GRID_ROW = FIXED_ROW,
    WDG_LIST_GRID_COL = FIXED_COLUMN
} WdgListGridDir_e;

typedef WdgMenuItemType_e WdgListItemType_e;
typedef WdgMenuItemPtr_t WdgListItem_t;


/** PfnWdgListFocusChange
* @brief      CB register by "WdgListRegisterFocusChangeCb"
*             and will be trigger when the Focus of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pFocusChangeData  The info of focus change, refer to FocusChangeData_t
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgListFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusChangeData,IWidget *pWidget);

/** PfnWdgListFocusSelect
* @brief      CB register by "WdgListRegisterFocusSelectCb"
*             
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nFocusIdx         The nth focus Index
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgListFocusSelect) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pWidget);

/** PfnWdgListFocusLongPress
* @brief      CB register by "WdgListRegisterFocusLongPressCb"
*
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nFocusIdx         The nth focus Index
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgListFocusLongPress) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pWidget);

/** PfnWdgListBoundTop
* @brief      CB register by "WdgListRegisterBoundTopNotifyCb"
*             
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgListBoundTop) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);

/** PfnWdgListBoundBottom
* @brief      CB register by "WdgListRegisterBoundBottomNotifyCb"
*             
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgListBoundBottom) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);

/** PfnWdgListScrollChange
* @brief      CB register by "WdgListRegisterScrollChangeCb"
*             
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  pType             the scroll type
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgListScrollChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, ScrollDataType_t *pType,IWidget *pWidget);

/** PfnWdgListWidgetItemChange
* @brief      CB register by "WdgListRegisterItemChangeCb"
*             
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  nReserve          Reserve for enhancement in the future
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgListWidgetItemChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve,IWidget *pWidget);

/** PfnWdgListItemDrawNotifier
* @brief      CB register by "WdgListRegisterItemDrawNotifierCb"
*             
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pstItemInfo       
*
*/
typedef void (*PfnWdgListItemDrawNotifier) (void *pApplet, ItemInfo_st *pstItemInfo);

/** PfnWdgListFreeData
* @brief      
*             
*
* @param[in]  pItemDataPtr           
* @param[in]  hWin    
* @param[in]  eItemType      
*
*/
typedef void (*PfnWdgListFreeData) (WdgListItem_t *pItemDataPtr, HWIN hWin, WdgListItemType_e eItemType);
/*=============================================================*/
// functions
/*=============================================================*/
/** WdgListCreateForWnd
* @brief        List widget create function for Window
*
* @param[in]    hWin         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    eListType      List initial style
*
* @retval       The pointer of List         Success.
* @retval       NULL                        Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgListCreateForWnd
(
    HWIN          hWin,
    Pos_t                *pPos,
    WidgetSize_t         *pSize,
    u16                  nWidgetID,
    WdgListType_e        eListType
);

/** WdgListCreate
* @brief        Create List widget
*
* @param[in]    eStyle                  List initial style
*
* @retval       The pointer of List  Success.
* @retval       NULL                 Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgListCreate
(
    WdgListType_e  eStyle
);

/** WdgListInit
* @brief        init List widget
*
* @param[in]    pWDGList         The pointer of IWidget interface object
* @param[in]    eItemType         The list item type
* @param[in]    pfnFreeItemData         The list item data free function pointer
*
* @retval       The pointer of List  Success.
* @retval       NULL                 Failed.
*
*/
MAE_Ret WdgListInit
(
	IWidget *pWDGList, 
	WdgListItemType_e eItemType, 
	PfnWdgListFreeData pfnFreeItemData
);

/**
* WdgListDeleteItem
* @brief   This function delete the specific item from list widget
*
* @param[in]   pWDGList         The pointer of IWidget interface object
* @param[in]   u32ItemIndex     A zero-base index of the position which will be removed.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgListDeleteItem
(   
    IWidget *pWDGList, 
    u32     u32ItemIndex
);

/**
* WdgListDeleteAllItem
* @brief   This function clear all items from list widget
*
* @param[in]   pWDGList         The pointer of IWidget interface object
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgListDeleteAllItem
(
    IWidget *pWDGList
);

/**
* WdgListInsertItem
* @brief   This function insert a new item into a list widget
*
* @param[in]   pWDGList         The pointer of IWidget interface object
* @param[in]   u32Index         A zero-base index of the position which will be inserted.
* @param[in]   sItemData        A pointer of item that will be inserted 
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgListInsertItem
(
    IWidget         *pWDGList, 
    u32             u32Index, 
    WdgListItem_t   sItemData
);

/**
* WdgListAddItem
* @brief   This function add a new item into a list widget
*
* @param[in]   pWDGList         The pointer of IWidget interface object
* @param[in]   sItemData        A pointer of item that will be added 
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgListAddItem
(
    IWidget         *pWDGList, 
    WdgListItem_t   sItemData
);

/**
* WdgListGetItem
* @brief   This function get the specific item from list widget
*
* @param[in]   pWDGList         The pointer of IWidget interface object
* @param[in]   u32Index         A zero-base index of the position which will be got.
* @param[in]   peItemType       
* @param[in]   psMenuItemData   A pointer of item that will be got 
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgListGetItem
(
    IWidget             *pWDGList, 
    u32                 u32Index, 
    WdgListItemType_e   *peItemType, 
    WdgListItem_t       *psMenuItemData
);

/**
* WdgListReplaceItem
* @brief   This function replace the item with users' new 
*
* @param[in]   pWDGList         The pointer of IWidget interface object
* @param[in]   u32Index         A zero-base index of the position which will be got.
* @param[in]   sItemData        A pointer of new item used to replace
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*/
MAE_Ret WdgListReplaceItem
(
    IWidget             *pWDGList, 
    u32                 u32Index, 
    WdgListItem_t       sItemData
);

/** WdgListMoveToNextItem
* @brief        To move the focus to next item of list.
*
* @param[in]    pWDGList          The pointer of IWidget interface object
*
*
* @retval       None
*
*/
__INLINE void WdgListMoveToNextItem
(
    IWidget                 *pWDGList
)
{
    WdgCommonHandleEvent(pWDGList, EVT_WIDGET_MOVETO_NEXT_ITEM, 0, 0);
}

/** WdgListMoveToPreviousItem
* @brief        To move the focus to previous item of list.
*
* @param[in]    pWDGList          The pointer of IWidget interface object
*
*
* @retval       None
*
*/
__INLINE void WdgListMoveToPreviousItem
(
    IWidget                 *pWDGList
)
{
    WdgCommonHandleEvent(pWDGList, EVT_WIDGET_MOVETO_PRIV_ITEM, 0, 0);
}

/** WdgListSetSelItemSize
* @brief        Set the selected item size(width and height), Can be changed in LIST_STYLE_GRID style only.
*
* @param[in]    pWDGList       The pointer of IWidget interface object
* @param[in]    u16ItemHeight      Item size in pixels to be set.
*
* @retval       void
*/
__INLINE void WdgListSetFocusItemHeight
(
    IWidget                 *pWDGList,
    u16                     u16ItemHeight
)
{
    WdgCommonSetProperty(pWDGList, PROP_SEL_ITEMSIZE, (u32)u16ItemHeight);
}

/** WdgListSetFCSItemBGColor
* @brief        Set the background color for focused item widget
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    nRBgColor         RGBColor_t value. the return value of MAKE_RGB()
*
* @retval       void
*
*/
__INLINE void WdgListSetFocusItemBGColor
(
    IWidget              *pWDGList,
    RGBColor_t           nRBgColor
)
{
    WdgCommonSetProperty(pWDGList, PROP_FCS_ITEM_BG_COLOR, nRBgColor);
}

/** WdgListSetFCSItemBGImage
* @brief        Set the background image for focused item widget
*
* @param[in]    pWDGList       The pointer of IWidget interface object
* @param[in]    pImage         An image object pointer.
*
* @retval       void
*
*/
__INLINE void WdgListSetFocusItemBGImage
(
    IWidget                *pWDGList,
    IImage                 *pImage
)
{
    WdgCommonSetProperty(pWDGList, PROP_FCS_ITEM_BG_IMAGE, (u32)pImage);
}

/** WdgListSetEnableHighlightBG
* @brief        Set the enable highlight item background
*
* @param[in]    pWDGList       The pointer of IWidget interface object
* @param[in]    bEnable         TRUE/FALSE
*
* @retval       void
*
*/
__INLINE void WdgListSetEnableHighlightBG
(
    IWidget                *pWDGList,
    boolean                 bEnable
)
{
    WdgCommonSetProperty(pWDGList, PROP_GRID_WDG_ENABLE_HIGHLIGHT_BG, (u32)bEnable);
}

/** WdgListSetFCSItemBGImageBitmap
* @brief        Set the background image for focused item widget
*
* @param[in]    pWDGList       The pointer of IWidget interface object
* @param[in]    pIBmp          An image object(IBitmap/IImage) pointer.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgListSetFCSItemBGImageBitmap
(
    IWidget                 *pWDGList,
    void                 *pIBmp
)
{
    return WdgCommonSetProperty(pWDGList, PROP_FCS_ITEM_BG_IMAGE, (u32)pIBmp);
}

/** WdgListSetFlag
* @brief        Set List widget flag for wrap and select event handle configuration to decide the behavior.
*
* @param[in]    pWDGList    The pointer of IWidget interface object
* @param[in]    eRoll       Flags refer to FLAG_NONE, FLAG_WRAP, FLAG_COL_WRAP, FLAG_ROW_WRAP, FLAG_NO_SEL
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
void WdgListSetRollStyle
(
    IWidget                *pWDGList,
    WdgListRollType_e      eRoll
);

/** WdgListSetHorScrollNoticeMode
* @brief        Set the horizontal scroll notice mode
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    bMode				TRUE : notice Focus ,  FALSE : notice scroll
*
* @retval       void
*
*/
__INLINE void WdgListSetHorScrollNoticeMode
(
    IWidget              *pWDGList,
    boolean                  bMode
)
{
    WdgCommonSetProperty(pWDGList, PROP_WDG_H_SCROLL_NOTICE_MODE, (u32)bMode);
}

/** WdgListSetVerScrollNoticeMode
* @brief        Set the vertical scroll notice mode
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    bMode				TRUE : notice Focus ,  FALSE : notice scroll
*
* @retval       void
*
*/
__INLINE void WdgListSetVerScrollNoticeMode
(
    IWidget              *pWDGList,
    boolean                  bMode
)
{
    WdgCommonSetProperty(pWDGList, PROP_WDG_V_SCROLL_NOTICE_MODE, (u32)bMode);
}

/** WdgListSetFirstItem
* @brief        Set the index of first element on the screen
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    nFirstDispIdx     The index of first display element, zero base(means the index start from 0).
*
* @retval       void
*
*/
__INLINE void WdgListSetFirstItem
(
    IWidget              *pWDGList,
    u32                  nFirstDispIdx
)
{
    WdgCommonSetProperty(pWDGList, PROP_FIRST_INDEX, nFirstDispIdx);
}

/** WdgListSetFirstItemAdjustRule
* @brief        Set the adjust rule when set first index
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    nRule				The adjust rule, FIRST_INDEX_ADJRULE_NONE / FIRST_INDEX_ADJRULE_FILL_PAGE
*
* @retval       void
*
*/
__INLINE void WdgListSetFirstItemAdjustRule
(
    IWidget              *pWDGList,
    ListWdgFistIdxAdjRule_e                  nRule
)
{
    WdgCommonSetProperty(pWDGList, PROP_FIRST_INDEX_ADJUST_RULE, nRule);
}

/** WdgListSetFocusIndex
* @brief        Set the index of focused element
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    nFocusIdx         The index of focused element, zero base(means the index start from 0).
*
* @retval       void
*
*/

__INLINE void WdgListSetFocusItemIndex
(
    IWidget              *pWDGList,
    u32                  nFocusIdx
)
{
    WdgCommonSetProperty(pWDGList, PROP_FOCUS_INDEX, nFocusIdx);
}

/** WdgListSetSelIndex
* @brief        Set the index of selected element
*
* @param[in]    pWDGList       The pointer of IWidget interface object
* @param[in]    nSelectIdx     The index of selected element, zero base(means the index start from 0).
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgListSetSelIndex
(
    IWidget              *pWDGList,
    s32                  nSelectIdx
)
{
    return WdgCommonSetProperty(pWDGList, PROP_SEL_INDEX, (u32)nSelectIdx);
}

/** WdgListSetItemWidth
* @brief        Set the width of item in pixels
*
* @param[in]    pWDGList         The pointer of IWidget interface object
* @param[in]    nItemWidth       The width of item in pixels
*
* @retval       void
*
*/
__INLINE void WdgListSetItemWidth
(
    IWidget              *pWDGList,
    u16                  nItemWidth
)
{
    WdgCommonSetProperty(pWDGList, PROP_ITEM_WIDTH, (u32)nItemWidth);
}

/** WdgListSetItemHeight
* @brief        Set the height of item in pixels
*
* @param[in]    pWDGList        The pointer of IWidget interface object
* @param[in]    nItemHeight     The height of item in pixels
*
* @retval       void
*
*/
__INLINE void WdgListSetItemHeight
(
    IWidget             *pWDGList,
    u16                 nItemHeight
)
{
    WdgCommonSetProperty(pWDGList, PROP_ITEM_HEIGHT, (u32)nItemHeight);
}

/** WdgListSetRowGap
* @brief        Set row gap in pixel between every item.
*
* @param[in]    pWDGList        The pointer of IWidget interface object
* @param[in]    nItemRowGap     The space in pixels between row items
*
* @retval       void
*
*/
__INLINE MAE_Ret WdgListSetRowGap
(
    IWidget              *pWDGList,
    u16                  nItemRowGap
)
{
    return WdgCommonSetProperty(pWDGList, PROP_WDG_ROW_GAP, (u32)nItemRowGap);
}

/** WdgListSetColGap
* @brief        Set column gap in pixel between every item.
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    nItemColGap       The space in pixels between column items
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgListSetColGap
(
    IWidget              *pWDGList,
    u16                  nItemColGap
)
{
    return WdgCommonSetProperty(pWDGList, PROP_WDG_COL_GAP, (u32)nItemColGap);
}

/** WdgListSetUNFCSItemBGColor
* @brief        Set the background color for unfocused item widget
*
* @param[in]    pWDGList         The pointer of IWidget interface object
* @param[in]    nRBgColor        RGBColor_t value. the return value of MAKE_RGB()
*
* @retval       void
*
*/
__INLINE void WdgListSetItemBGColor
(
    IWidget                 *pWDGList,
    RGBColor_t              nRBgColor
)
{
    WdgCommonSetProperty(pWDGList, PROP_UNFCS_ITEM_BG_COLOR, (u32)nRBgColor);
}

/** WdgListSetUNFCSItemBGImage
* @brief        Set the background image for unfocused item widget
*
* @param[in]    pWDGList      The pointer of IWidget interface object
* @param[in]    pImage        An image object pointer.
*
* @retval       void
*
*/
__INLINE void WdgListSetItemBGImage
(
    IWidget                 *pWDGList,
    IImage                  *pImage
)
{
    WdgCommonSetProperty(pWDGList, PROP_UNFCS_ITEM_BG_IMAGE, (u32)pImage);
}

#ifdef __TOUCH_SCREEN_MMI__
/** WdgListSetTouchMode
* @brief        Set the way deal with touch event
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    eTouchMode        the way deal with touch event
*
* @retval       void
*
*/
__INLINE void WdgListSetTouchMode
(
    IWidget                 *pWDGList,
    WdgListTouchModeType_e eTouchMode
)
{
    WdgCommonSetProperty(pWDGList, PROP_GRID_WDG_TOUCH_MODE, (u32)eTouchMode);
}

/** WdgListSetTouchMoveStyle
* @brief        Set the way deal with the touch moving ouside the hightlight item
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    eMoveType        The way deal with the touch moving ouside the hightlight item
*
* @retval        void
*
*/
__INLINE void WdgListSetTouchMoveStyle
(
    IWidget                 *pWDGList,
    WdgListTouchMoveStyle_e eMoveType
)
{
    WdgCommonSetProperty(pWDGList, PROP_GRID_WDG_TOUCH_MOVE_STYLE, (u32)eMoveType);
}

/** WdgListSetTouchASStyle
* @brief        Set the way deal with the touch Auto Slide Style
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    eASType        The way deal with the touch Auto Slide Style
*
* @retval        void
*
*/
__INLINE void WdgListSetTouchASStyle
(
    IWidget                 *pWDGList,
    GridTouchASStype_e eASType
)
{
    WdgCommonSetProperty(pWDGList, PROP_GRID_WDG_TOUCH_AS_STYLE, (u32)eASType);
}

/** WdgListSetTouchASSpeedUp
* @brief        Set the way deal with the touch Auto Slide Speed up type (distance or time)
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    eType        The way deal with the touch Auto Slide Speed up type (distance or time)
*
* @retval        void
*
*/
__INLINE void WdgListSetTouchASSpeedUp
(
    IWidget                 *pWDGList,
    GridTouchASSpeedUp_e eType
)
{
    WdgCommonSetProperty(pWDGList, PROP_GRID_WDG_TOUCH_AS_SPEEDUP, (u32)eType);
}

/** WdgListSetTouchSelected
* @brief        Enable/Disable Notify Select after released at highlight item
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    bTouchSelected    Set NotifySelect or not
*
* @retval        void
*
*/
__INLINE void WdgListSetTouchSelected
(
    IWidget                 *pWDGList,
    boolean                 bTouchSelected
)
{
    WdgCommonSetProperty(pWDGList, PROP_GRID_WDG_TOUCH_SELECTED, (u32)bTouchSelected);
}

/** WdgListSetDisableHandleTouchEvt
* @brief        Set TRUE to disable handle touch event.
*
* @param[in]    pWDGList                  The pointer of IWidget interface object
* @param[in]    bDisableHandleTouchEvt    Set TRUE or FALSE
*
* @retval        void
*
*/
__INLINE void WdgListSetDisableHandleTouchEvt
(
    IWidget                 *pWDGList,
    boolean                 bDisableHandleTouchEvt
)
{
    WdgCommonSetProperty(pWDGList, PROP_DISABLE_HANDLE_TOUCH_EVT, (u32)bDisableHandleTouchEvt);
}

/** WdgListSetChangefocusOnTouch
* @brief        Set the property to determine if a widget need to set focus automatically while touch press.
*
* @param[in]    pWDGList                  The pointer of IWidget interface object
* @param[in]    bChangefocusOnTouch        Set TRUE or FALSE
*
* @retval        void
*
*/
__INLINE void WdgListSetChangefocusOnTouch
(
    IWidget                 *pWDGList,
    boolean                 bChangefocusOnTouch
)
{
    WdgCommonSetProperty(pWDGList, PROP_WDG_CHANGEFOCUS_ON_TOUCH, (u32)bChangefocusOnTouch);
}

/** WdgListSetTouchSlidingDirection
* @brief        Set the touch sliding direction (vertical / horizontal / none)
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    eDirection			  The direction
*												 GRID_TOUCH_SLIDING_DIRECTION_NONE,	 disable touch sliding
*												 GRID_TOUCH_SLIDING_DIRECTION_VERTICAL,	 enable vertical sliding, only for vertical/grid menu
*												 GRID_TOUCH_SLIDING_DIRECTION_HORIZONTAL,	 enable horizontal sliding, only for horizontal/grid menu
* @retval        void
*
*/
__INLINE void WdgListSetTouchSlidingDirection
(
    IWidget                 *pWDGList,
    GridTouchSlidingDirection_e eDirection
)
{
	WdgCommonSetProperty(pWDGList, PROP_GRID_WDG_TOUCH_SLIDING_DIRECTION, (u32)eDirection);
}

#endif // __TOUCH_SCREEN_MMI__

/** WdgListSetFixedDirection
* @brief        Set the direction(row or column) to be fixed, Can be changed in LIST_STYLE_GRID style only.
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    nFixedDir         The direction(row or column) to be fixed
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgListSetFixedDirection
(
    IWidget                 *pWDGList,
    u8                      nFixedDir
)
{
    return WdgCommonSetProperty(pWDGList, PROP_FIXED_DIRECTION, (u32)nFixedDir);
}

/** WdgListSetFixedNum
* @brief        Set the fixed number, Can be changed in LIST_STYLE_GRID style only
*
* @param[in]    pWDGList          The pointer of IWidget interface object
* @param[in]    nFixedNum         The fixed row / column numbers, must bigger than zero
*
* @retval       void
*
*/
__INLINE MAE_Ret WdgListSetFixedNum
(
    IWidget                 *pWDGList,
    u16                     nFixedNum
)
{
    return WdgCommonSetProperty(pWDGList, PROP_FIXED_NUM, (u32)nFixedNum);
}

/** WdgListGetFlag
* @brief        Get widget flag (an u32 variable)
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    peRoll             A pointer of u32 with result of Flag,
*                                  Flags refer to FLAG_NONE, FLAG_WRAP, FLAG_COL_WRAP, FLAG_ROW_WRAP, FLAG_NO_SEL
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgListGetRollStyle
(
    IWidget                *pWDGList,
    WdgListRollType_e      *peRoll
);

/** WdgListGetFirstItem
* @brief        Get the index of first element on the screen
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    pFirstDispIdx     A pointer of s32 with result of the index of first display element.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgListGetFirstItem
(
    IWidget                 *pWDGList,
    u32                     *pFirstDispIdx
)
{
    return WdgCommonGetProperty(pWDGList, PROP_FIRST_INDEX, pFirstDispIdx);
}

/** WdgListGetFocusIndex
* @brief        Get the index of focused element
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    pFocusIdx         A pointer of s32 with result of the index of focused element, zero base(means the index start from 0).
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgListGetFocusItemIndex
(
    IWidget                 *pWDGList,
    u32                     *pFocusIdx
)
{
    return WdgCommonGetProperty(pWDGList, PROP_FOCUS_INDEX, pFocusIdx);
}

/** WdgListGetItemWidth
* @brief        Get the width of item in pixels
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    pItemWidth        A pointer of u16 with result of the width of item in pixels
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgListGetItemWidth
(
    IWidget                 *pWDGList,
    u16                     *pItemWidth
)
{
    return WdgCommonGetProperty(pWDGList, PROP_ITEM_WIDTH, (u32*)pItemWidth);
}

/** WdgListGetItemHeight
* @brief        Get the height of item in pixels
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    pItemHeight       A pointer of u16 with result of the height of item in pixels
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgListGetItemHeight
(
    IWidget                 *pWDGList,
    u16                     *pItemHeight
)
{
    return WdgCommonGetProperty(pWDGList, PROP_ITEM_HEIGHT, (u32*)pItemHeight);
}

/** WdgListGetRowGap
* @brief        Get row gap in pixel between every item.
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    pItemRowGap       A pointer of u16 with result of the space in pixels between row items
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgListGetRowGap
(
    IWidget                 *pWDGList,
    u16                     *pItemRowGap
)
{
    return WdgCommonGetProperty(pWDGList, PROP_WDG_ROW_GAP, (u32*)pItemRowGap);
}

/** WdgListGetColGap
* @brief        Get column gap in pixel between every item.
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    pItemColGap       A pointer of u16 with result of the space in pixels between column items
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgListGetColGap
(
    IWidget           *pWDGList,
    u16               *pItemColGap
)
{
    return WdgCommonGetProperty(pWDGList, PROP_WDG_COL_GAP, (u32*)pItemColGap);
}

/** WdgListGetFixedDirection
* @brief        Get the direction(row or column) to be fixed
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    pFixedDir         A pointer of u8 with result of the direction(row or column) to be fixed
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgListGetFixedDirection
(
    IWidget                 *pWDGList,
    u8                      *pFixedDir
)
{
    return WdgCommonGetProperty(pWDGList, PROP_FIXED_DIRECTION, (u32*)pFixedDir);
}

/** WdgListGetFixedNum
* @brief        Get the fixed number
*
* @param[in]     pWDGList          The pointer of IWidget interface object
* @param[out]    pnFixedNum         A pointer of u16 with result of the fixed row / column numbers, must bigger than zero
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
__INLINE MAE_Ret WdgListGetFixedNum
(
    IWidget                 *pWDGList,
    u16                     *pnFixedNum
)
{
    return WdgCommonGetProperty(pWDGList, PROP_FIXED_NUM, (u32*)pnFixedNum);
}

/** WdgListRegisterItemDrawNotifierCb
* @brief        To set a notifier callback while drawing an item
*
* @param[in]    pWDGList          The List widget which want to set callback
* @param[in]    pfn            callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListRegisterItemDrawNotifierCb
(
    IWidget                     *pWDGList,
    PfnWdgListItemDrawNotifier  pfn,
    void                        *pUserData
);

/** WdgListRegisterFocusChangeCb
* @brief        Register callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]    pWDGList          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgListRegisterFocusChangeCb
(
    IWidget                 *pWDGList,
    PfnWdgListFocusChange   pfn,
    void                    *pUserData
);

/** WdgListRegisterFocusSelectCb
* @brief        Register callback for selecting item; CB will be triggered if item selected
*
* @param[in]    pWDGList          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgListRegisterFocusSelectCb
(
    IWidget                 *pWDGList,
    PfnWdgListFocusSelect   pfn,
    void                    *pUserData
);

/** WdgListRegisterFocusLongPressCb
* @brief        Register callback for long pressed item; CB will be triggered if item is longpressed.
*
* @param[in]    pWDGList          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListRegisterFocusLongPressCb
(
    IWidget                 *pWDGList,
    PfnWdgListFocusSelect   pfn,
    void                    *pUserData
);

/** WdgListRegisterBoundTopNotifyCb
* @brief        Register callback : For list widget CB will be triggered when the focus move to the top item and can't wrap.
*
* @param[in]    pWDGList          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListRegisterBoundTopNotifyCb
(
    IWidget                 *pWDGList,
    PfnWdgListBoundTop      pfn,
    void                    *pUserData
);

/** WdgListRegisterBoundBottomNotifyCb
* @brief        Register callback : For list widget, CB will be triggered when the focus move to the end item and can't wrap.
*
* @param[in]    pWDGList          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListRegisterBoundBottomNotifyCb
(
    IWidget                 *pWDGList,
    PfnWdgListBoundBottom   pfn,
    void                    *pUserData
);

/** WdgListRegisterScrollChangeCb
* @brief        Register callback for handling scroll visible range change; CB will be triggered if scroll visible range changed
*
* @param[in]    pWDGList          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListRegisterScrollChangeCb
(
    IWidget                 *pWDGList,
    PfnWdgListScrollChange  pfn,
    void                    *pUserData
);

/** WdgListRegisterItemChangeCb
* @brief        Register item change callback; CB will be triggered while items has changed.
*
* @param[in]    pWDGList          The List widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListRegisterItemChangeCb
(
    IWidget                     *pWDGList,
    PfnWdgListWidgetItemChange  pfn,
    void                        *pUserData
);

/** WdgListDeregisterFocusChangeCb
* @brief        Deregister callback for changing focus item; CB will be triggered if focus item changed
*
* @param[in]    pWDGList          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgListDeregisterFocusChangeCb
(
    IWidget                 *pWDGList,
    PfnWdgListFocusChange   pfn,
    void                    *pUserData
);

/** WdgListDeregisterFocusSelectCb
* @brief        Deregister callback for selecting item; CB will be triggered if item selected
*
* @param[in]    pWDGList          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListDeregisterFocusSelectCb
(
    IWidget                 *pWDGList,
    PfnWdgListFocusSelect   pfn,
    void                    *pUserData
);

/** WdgListDeregisterFocusLongPressCb
* @brief        Deregister callback for long pressed item; CB will be triggered if item is long pressed.
*
* @param[in]    pWDGList          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListDeregisterFocusLongPressCb
(
    IWidget                 *pWDGList,
    PfnWdgListFocusSelect   pfn,
    void                    *pUserData
);

/** WdgListDeregisterBoundTopNotifyCb
* @brief        Deregister callback : For list widget CB will be triggered when the focus move to the top item and can't wrap.
*
* @param[in]    pWDGList          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListDeregisterBoundTopNotifyCb
(
    IWidget                 *pWDGList,
    PfnWdgListBoundTop      pfn,
    void                    *pUserData
);

/** WdgListDeregisterBoundBottomNotifyCb
* @brief        Deregister callback : For list widget, CB will be triggered when the focus move to the end item and can't wrap.
*
* @param[in]    pWDGList          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListDeregisterBoundBottomNotifyCb
(
    IWidget                 *pWDGList,
    PfnWdgListBoundBottom   pfn,
    void                    *pUserData
);

/** WdgListDeregisterScrollChangeCb
* @brief        Deregister callback for handling scroll visible range change; CB will be triggered if scroll visible range changed
*
* @param[in]    pWDGList          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListDeregisterScrollChangeCb
(
    IWidget                 *pWDGList,
    PfnWdgListScrollChange  pfn,
    void                    *pUserData
);

/** WdgListDeregisterItemChangeCb
* @brief        Deregister item change callback; CB will be triggered while item has changed.
*
* @param[in]    pWDGList          The List widget which want to deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgListDeregisterItemChangeCb
(
    IWidget                     *pWDGList,
    PfnWdgListWidgetItemChange  pfn,
    void                        *pUserData
);
#endif /* __MMI_WDG_LIST_H__ */
/*=============================================================*/
// end of file
