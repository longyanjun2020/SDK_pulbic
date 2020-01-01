/**
* @file 	mae_gridwidgetbase.h
* @brief   
*
* @version $Id: mae_gridwidgetbase.h 37684 2009-08-12 12:08:18Z steve.lee $
*/
#ifndef __MAE_GRIDWIDGETBASE_H__
#define __MAE_GRIDWIDGETBASE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_decorator.h"
#include "mae_decoratorbase.h"
#include "mmi_mae_listmodel.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_textmodel.h"
#include "mmi_mae_interfacemodel.h"
#include "mmi_wdg_list.h"
#include "mae_wdgbackground.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define ITEM_FLIP_ROTATION_COUNT		20
#define ITEM_FLIP_ROTATION_INTERVAL		5	//ms

#define ITEM_ROLLING_ROTATION_COUNT		10
#define ITEM_ROLLING_ROTATION_INTERVAL	5	//ms

typedef enum {
    MOVING_DIRECTION_UP = -1,
    MOVING_DIRECTION_STATIC = 0,
    MOVING_DIRECTION_DOWN = 1
} GridWdgMoveDirection_e;

/// Here define the types for grid/list widget.
typedef enum {
	LW_GRID = 0,	///> grid
	LW_HORZ,		///> Horizontal
	LW_VERT			///> Vertical
} GridWdgMode_e;

#ifdef __TOUCH_SCREEN_MMI__
enum {
	GRID_SLIDE_TO_NONE = 0,
	GRID_SLIDE_TO_LEFT, ///< minus x offset
	GRID_SLIDE_TO_RIGHT,    ///< plus x offset
	GRID_SLIDE_TO_TOP,      ///< minus y offset
	GRID_SLIDE_TO_BOTTOM,   ///< plus y offset
	GRID_SLIDE_ROLLBACK_X,
	GRID_SLIDE_ROLLBACK_Y,
	GRID_SLIDE_END
};
typedef u8 GridWdgSildeMode_t;
#endif // __TOUCH_SCREEN_MMI__

//#define		FIXED_COLUMN	0
//#define		FIXED_ROW		1

typedef struct
{
    u32 u32Index;
    boolean bHighlight;
    Rect_t sRect;
} MAE_ItemInfo_s;

typedef void (*pfnItemDraw_t) (void *pUsrData, IDispCanvas *pICanvas, MAE_ItemInfo_s sItemInf);
typedef u32 (*pfnGetItemSize_t) (void *pUsrData, s32 nIndex);

typedef struct 
{
    void *pUsrData;
    pfnItemDraw_t pfnItemDraw;
} MAE_ItemDraw_s;

typedef struct 
{
	void *pUsrData;
	pfnGetItemSize_t pfnGetItemSize;
} GridWdgGetItemSize_t;

typedef struct _GridWdgBase GridWdgBase_t;

typedef boolean (*KEY_MOVE_FUNCPTR) (GridWdgBase_t *pThis, u32 nKey);

struct _GridWdgBase {
	DecoratorEx_t	DecBase;            ///< A decorator base structure DecoratorEx_t to support border
	IListModel		*pListMdl;          ///< A list model pointer to keep data
	ModelListener_t	MdlListener;        ///< model listener for list model
	KEY_MOVE_FUNCPTR	KeyMoveFnPtr;          ///< A function pointer to keep move function which decide how to handle up/down/left/right key event

	IModel			*pItemWdgDataMdl;   ///< Model from item widget(child widget)
	MAE_IId			nItemMdlId;         ///< the interface id of item widget's model
	IModel			*pItemWdgViewMdl;	///< item widget's view model
	ModelListener_t	ItemWdgViewMdlLsn;	///< model listener for item widget's view model

	ItemDrawNotifier_st stDrawNotifier;
    MAE_ItemDraw_s sItemDraw;

	u32				nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
	u32				nFlag;              ///< Flags
	u32             nStatusFlags;       ///< status flags such as being a item widget, highlighted,...
	s32				nFocusIdx;			///< The index of focused element, zero base.
	s32				nFirstDispIdx;		///< The index of first display element, zero base.
	s32             nBigOffsetX;        ///< the offset x from the very first(index:zero) element to the gridbase
	s32             nBigOffsetY;        ///< the offset y from the very first(index:zero) element to the gridbase

	u16				nItemWidth;			///< The width of item in pixels
	u16				nItemHeight;		///< The height of item in pixels
	u16				nItemRowGap;		///< The space in pixels between row items
	u16				nItemColGap;		///< The space in pixels between col items
	u16				nSelItemSize;		/*!< The width/height of highlighted item in pixels, 
	                                    only useful in LW_HORZ and LW_VERT mode. 
	                                    In LW_GRID mode highlighted item size should be the same with unhighlight item.
	                                    Notice: If it is zero in LW_HORZ and LW_VERT mode, we use nItemWith/nItemHeight 
	                                            to be the highlight item size */
	WdgItemBG_t		stFocusItemBg;		///< the background color/image for focused item
	WdgItemBG_t		stUnfocusItemBg;	///< background color/image for unfocused item

	u8				nMode;              ///< Horizontal(LW_HORZ), Vertical(LW_VERT) and Grid(LW_GRID)
	u8				nFixedNum;			///< Fixed row / column numbers, must bigger than zero, 1,2,3.....
	u8				nFixedDir;			///< Fixed direction, to indicate row or column is fixed.
	PfnWdgListFreeData pfnListFreeItemData;///< Only for list wdg free data 
	WdgListItemType_e eListItemType;	///< Only for list wdg free data 
	GridTouchMode_t	eFirstIdxAdjRule;         ///< First index adjust rule when user set first index
	Rect_t			rcFocusItem;		///< The rectangle of focused item coordinate to this list widget
    GridWdgGetItemSize_t tGetItemSize;		// for variable item length
	u16				*aVariableItemSize;	// Array that includes item size of each item

#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv 				*pITouchSrv;	///< Pointer to the touch service object

	GridTouchMode_t			touchMode;		///< The way dear with touch event. (Default=GRID_TOUCH_MODE_SELECTOR)
	GridTouchMoveStyle_t	moveStyle;		/*!< The way dear with the touch moving ouside the hightlight item. 
	                                             (Default is GRID_TOUCH_MOVE_STYLE_HOLD_SELECTION)*/
	s32                     nPressIdx;      /// < The focus index when touch is pressed>
	GridWdgSildeMode_t      SlideMode;
	
	s32						nTS_StartX;			/*!< Used to keep pressed x position in GRID_TOUCH_MOVE_STYLE_MOVE_LOCATION 
	                                                 move style. It is coordinate to content rectangle! */
	s32						nTS_StartY;			/*!< Used to keep pressed y position in GRID_TOUCH_MOVE_STYLE_MOVE_LOCATION 
	                                                 move style. It is coordinate to content rectangle! */
	u32						nTS_StartOffsetX;	/*!< Used to keep offset x while receive touch press event in 
	                                                 GRID_TOUCH_MOVE_STYLE_MOVE_LOCATION move style.*/
	u32						nTS_StartOffsetY;	/*!< Used to keep offset y while receive touch press event in 
	                                                 GRID_TOUCH_MOVE_STYLE_MOVE_LOCATION move style.*/
	u32						nSlideOffset;
	boolean				bSlideChecking;
		
	/* Auto-scroll */
	u32                     nTotalPixelsToMove;
	u32						nAutoscrollStatus;	/*!< the auto-scroll status of the grid, and if the style flag is GRID_TOUCH_AS_STYLE_NONE,
			                                         the auto-scroll feature is disable and all the other AS status are ignored.
			                                         please refer to GRIDBASE_AS_STATUS_START */
	s32						nAS_LastX;			/*!< Used to keep last x position of the screen for auto-scroll */
	s32						nAS_LastY;			/*!< Used to keep last Y position of the screen for auto-scroll */
	s32						nAS_ThresholdTop;	/*! < Used to denote the threshold area to activate the auto-scroll */
	s32						nAS_ThresholdBottom;	/*! < Used to denote the threshold area to activate the auto-scroll */
	s32						nAS_ThresholdLeft;	/*! < Used to denote the threshold area to activate the auto-scroll */
	s32						nAS_ThresholdRight;	/*! < Used to denote the threshold area to activate the auto-scroll */
	GridWdgSildeMode_t		nASSlideDir;		/*! used to keep the current slide direction */
	u16						nAS_TimerInterval;
	u16						nAS_CBTimes;
#endif // __TOUCH_SCREEN_MMI__

    s16						moveDirection;
    s16						animationTick;
    GridItemEffect_t		itemEffect;			/*!< The way dear with the 3D item moving effect with the hightlight item. 
                                                (Default is GRID_ITEM_EFFECT_NONE)*/
    WdgEasingType_t			easingFunc;
};

/**
* Status flags
*/
enum
{
	GRIDBASE_FLAG_START = 0,
	GRIDBASE_FLAG_BEING_ITEMWDG = GRIDBASE_FLAG_START,   ///< 0: not an item widget, 1: being an item widget
	GRIDBASE_FLAG_HIGHLIGHTED,                           ///< 0: not highlighted, 1: highlighted now
	GRIDBASE_FLAG_NOTICE_SCROLL_MODE,                    ///< 0: notice scroll by scroll change; 1: notice scroll by focus change.
#ifdef __TOUCH_SCREEN_MMI__
	GRIDBASE_FLAG_DISABLE_TOUCH_EVT,                     ///< 0(default): enbale handle touch events, 1: disable.
	GRIDBASE_FLAG_SELECT_AFTER_TOUCH,                    ///< 1(default): If NotifySelect after released at highlight item.
	GRIDBASE_FLAG_IS_TOUCH_PRESSED,                      ///< 0: Touch pressed now; 1: Touch not pressed
	GRIDBASE_FLAG_SLIDE_TIMER_RUNNING,                      ///< 0: not running; 1: running
	GRIDBASE_FLAG_CHANGE_FOCUS_ON_TOUCH,                    ///< 0: not change; 1: change
#endif // __TOUCH_SCREEN_MMI__
	GRIDBASE_FLAG_HIGHLIGHT_ON_TOUCH,        ///1:highlight bg draw while touch pressed,
	GRIDBASE_FLAG_RESET_ANI_STATUS, ///< Use to notice item widget to reset animation status
	GRIDBASE_FLAG_ENABLE_HIGHLIGHT_BG,        ///1:use FCS BG, 0: use UNFCS BG,
#ifdef __TOUCH_SCREEN_MMI__
	GRIDBASE_FLAG_AS_TIMER_RUNNING,                      ///< 0: not running; 1: running
	GRIDBASE_FLAG_FOCUS_CHANGED_BY_TOUCH,				///< 1: focus index changed due to touch	
	GRIDBASE_FLAG_ENABLE_HORZ_SLIDE,					///< 0: disabled; 1: enabled
	GRIDBASE_FLAG_ENABLE_VERT_SLIDE,					///< 0: disabled; 1: enabled
#endif // __TOUCH_SCREEN_MMI__
	GRIDBASE_FLAG_ITEM_ANIM_ON_FOCUS,					///< 0: enable animation no matter on focused or not; 1: only enable when focused (default)
	GRIDBASE_FLAG_END
};


/**
* Status Flag Mask
*/
#define GRIDBASE_MASK_BEING_ITEMWDG         (1<<GRIDBASE_FLAG_BEING_ITEMWDG)
#define GRIDBASE_MASK_HIGHLIGHTED           (1<<GRIDBASE_FLAG_HIGHLIGHTED)
#define GRIDBASE_MASK_NOTICE_SCL_MODE       (1<<GRIDBASE_FLAG_NOTICE_SCROLL_MODE)
#ifdef __TOUCH_SCREEN_MMI__
#define GRIDBASE_MASK_DISABLE_TOUCH_EVT     (1<<GRIDBASE_FLAG_DISABLE_TOUCH_EVT)
#define GRIDBASE_MASK_SELECT_AFTER_TOUCH    (1<<GRIDBASE_FLAG_SELECT_AFTER_TOUCH)
#define GRIDBASE_MASK_IS_TOUCH_PRESSED      (1<<GRIDBASE_FLAG_IS_TOUCH_PRESSED)
#define GRIDBASE_MASK_SLIDE_TIMER_RUNNING   (1<<GRIDBASE_FLAG_SLIDE_TIMER_RUNNING)
#define GRIDBASE_MASK_CHANGE_FOCUS_ON_TOUCH (1<<GRIDBASE_FLAG_CHANGE_FOCUS_ON_TOUCH)
#endif // __TOUCH_SCREEN_MMI__
#define GRIDBASE_MASK_HIGHLIGHT_ON_TOUCH    (1<<GRIDBASE_FLAG_HIGHLIGHT_ON_TOUCH)
#define GRIDBASE_MASK_RESET_ANI_STATUS      (1<<GRIDBASE_FLAG_RESET_ANI_STATUS)
#define GRIDBASE_MASK_ENABLE_HIGHLIGHT_BG      (1<<GRIDBASE_FLAG_ENABLE_HIGHLIGHT_BG)
#ifdef __TOUCH_SCREEN_MMI__
#define GRIDBASE_MASK_AS_TIMER_RUNNING		(1<<GRIDBASE_FLAG_AS_TIMER_RUNNING)
#define GRIDBASE_MASK_FOCUS_CHANGED_BY_TOUCH	(1<<GRIDBASE_FLAG_FOCUS_CHANGED_BY_TOUCH)
#define GRIDBASE_MASK_ENABLE_HORZ_SLIDE			(1<<GRIDBASE_FLAG_ENABLE_HORZ_SLIDE)
#define GRIDBASE_MASK_ENABLE_VERT_SLIDE			(1<<GRIDBASE_FLAG_ENABLE_VERT_SLIDE)
#endif // __TOUCH_SCREEN_MMI__
#define GRIDBASE_MASK_ITEM_ANIM_ON_FOCUS	(1<<GRIDBASE_FLAG_ITEM_ANIM_ON_FOCUS)

/**
* Macro to get flag value
*/
#define GRIDBASE_IS_BEING_ITEMWDG(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_BEING_ITEMWDG)>>GRIDBASE_FLAG_BEING_ITEMWDG)
#define GRIDBASE_IS_HIGHLIGHTED(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_HIGHLIGHTED)>>GRIDBASE_FLAG_HIGHLIGHTED)
#define GRIDBASE_GET_NOTICE_SCROLL_MODE(_pGridBase) \
	(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_NOTICE_SCL_MODE)>>GRIDBASE_FLAG_NOTICE_SCROLL_MODE)
#ifdef __TOUCH_SCREEN_MMI__
#define GRIDBASE_IS_DISABLE_TOUCH_EVT(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_DISABLE_TOUCH_EVT)>>GRIDBASE_FLAG_DISABLE_TOUCH_EVT)
#define GRIDBASE_IS_SELECT_AFTER_TOUCH(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_SELECT_AFTER_TOUCH)>>GRIDBASE_FLAG_SELECT_AFTER_TOUCH)
#define GRIDBASE_IS_TOUCH_PRESSED(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_IS_TOUCH_PRESSED)>>GRIDBASE_FLAG_IS_TOUCH_PRESSED)
#define GRIDBASE_IS_SLIDE_TIMER_RUNNING(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_SLIDE_TIMER_RUNNING)>>GRIDBASE_FLAG_SLIDE_TIMER_RUNNING)
#define GRIDBASE_DOES_CHANGE_FOCUS_ON_TOUCH(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_CHANGE_FOCUS_ON_TOUCH)>>GRIDBASE_FLAG_CHANGE_FOCUS_ON_TOUCH)
#endif // __TOUCH_SCREEN_MMI__
#define GRIDBASE_IS_HIGHLIGHT_ON_TOUCH(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_HIGHLIGHT_ON_TOUCH)>>GRIDBASE_FLAG_HIGHLIGHT_ON_TOUCH)
#define GRIDBASE_SHOULD_RESET_ANI_STATUS(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_RESET_ANI_STATUS)>>GRIDBASE_FLAG_RESET_ANI_STATUS)
#define GRIDBASE_IS_ENABLE_HIGHLIGHT_BG(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_ENABLE_HIGHLIGHT_BG)>>GRIDBASE_FLAG_ENABLE_HIGHLIGHT_BG)
#ifdef __TOUCH_SCREEN_MMI__
#define GRIDBASE_IS_AS_TIMER_RUNNING(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_AS_TIMER_RUNNING)>>GRIDBASE_FLAG_AS_TIMER_RUNNING)
#define GRIDBASE_IS_FOCUS_CHANGED_BY_TOUCH(_pGridBase) \
    (boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_FOCUS_CHANGED_BY_TOUCH)>>GRIDBASE_FLAG_FOCUS_CHANGED_BY_TOUCH)
#define GRIDBASE_IS_ENABLE_HORZ_SLIDE(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_ENABLE_HORZ_SLIDE)>>GRIDBASE_FLAG_ENABLE_HORZ_SLIDE)
#define GRIDBASE_IS_ENABLE_VERT_SLIDE(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_ENABLE_VERT_SLIDE)>>GRIDBASE_FLAG_ENABLE_VERT_SLIDE)
#endif // __TOUCH_SCREEN_MMI__
#define GRIDBASE_IS_ITEM_ANIM_ON_FOCUS(_pGridBase) \
	(boolean)(((_pGridBase)->nStatusFlags&GRIDBASE_MASK_ITEM_ANIM_ON_FOCUS)>>GRIDBASE_FLAG_ITEM_ANIM_ON_FOCUS)


/**
* Macro to Set flag value
*/
#define GRIDBASE_SET_BEING_ITEMWDG(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_BEING_ITEMWDG))|(((u32)_b)<<GRIDBASE_FLAG_BEING_ITEMWDG)
#define GRIDBASE_SET_HIGHLIGHTED(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_HIGHLIGHTED))|(((u32)_b)<<GRIDBASE_FLAG_HIGHLIGHTED)
#define GRIDBASE_SET_NOTICE_SCROLL_MODE(_pGridBase, _SclMode) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_NOTICE_SCL_MODE))|(((u32)_SclMode)<<GRIDBASE_FLAG_NOTICE_SCROLL_MODE)
#ifdef __TOUCH_SCREEN_MMI__
#define GRIDBASE_DISABLE_TOUCH_EVT(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_DISABLE_TOUCH_EVT))|(((u32)_b)<<GRIDBASE_FLAG_DISABLE_TOUCH_EVT)
#define GRIDBASE_SET_SELECT_AFTER_TOUCH(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_SELECT_AFTER_TOUCH))|(((u32)_b)<<GRIDBASE_FLAG_SELECT_AFTER_TOUCH)
#define GRIDBASE_SET_TOUCH_PRESSED(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_IS_TOUCH_PRESSED))|(((u32)_b)<<GRIDBASE_FLAG_IS_TOUCH_PRESSED)
#define GRIDBASE_SET_SLIDE_TIMER_RUNNING(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_SLIDE_TIMER_RUNNING))|(((u32)_b)<<GRIDBASE_FLAG_SLIDE_TIMER_RUNNING)
#define GRIDBASE_SET_CHANGE_FOCUS_ON_TOUCH(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_CHANGE_FOCUS_ON_TOUCH))|(((u32)_b)<<GRIDBASE_FLAG_CHANGE_FOCUS_ON_TOUCH)
#endif // __TOUCH_SCREEN_MMI__
#define GRIDBASE_SET_HIGHLIGHT_ON_TOUCH(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_HIGHLIGHT_ON_TOUCH))|(((u32)_b)<<GRIDBASE_FLAG_HIGHLIGHT_ON_TOUCH)
#define GRIDBASE_SET_TO_RESET_ANI_STATUS(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_RESET_ANI_STATUS))|(((u32)_b)<<GRIDBASE_FLAG_RESET_ANI_STATUS)
#define GRIDBASE_SET_ENABLE_HIGHLIGHT_BG(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_ENABLE_HIGHLIGHT_BG))|(((u32)_b)<<GRIDBASE_FLAG_ENABLE_HIGHLIGHT_BG)
#ifdef __TOUCH_SCREEN_MMI__
#define GRIDBASE_SET_AS_TIMER_RUNNING(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_AS_TIMER_RUNNING))|(((u32)_b)<<GRIDBASE_FLAG_AS_TIMER_RUNNING)
#define GRIDBASE_SET_FOCUS_CHANGED_BY_TOUCH(_pGridBase, _b) \
    (_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_FOCUS_CHANGED_BY_TOUCH))|(((u32)_b)<<GRIDBASE_FLAG_FOCUS_CHANGED_BY_TOUCH)
#define GRIDBASE_SET_ENABLE_HORZ_SLIDE(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_ENABLE_HORZ_SLIDE))|(((u32)_b)<<GRIDBASE_FLAG_ENABLE_HORZ_SLIDE)
#define GRIDBASE_SET_ENABLE_VERT_SLIDE(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_ENABLE_VERT_SLIDE))|(((u32)_b)<<GRIDBASE_FLAG_ENABLE_VERT_SLIDE)
#endif // __TOUCH_SCREEN_MMI__
#define GRIDBASE_SET_ITEM_ANIM_ON_FOCUS(_pGridBase, _b) \
	(_pGridBase)->nStatusFlags = ((_pGridBase)->nStatusFlags&(~GRIDBASE_MASK_ITEM_ANIM_ON_FOCUS))|(((u32)_b)<<GRIDBASE_FLAG_ITEM_ANIM_ON_FOCUS)



#ifdef __TOUCH_SCREEN_MMI__
/**
* Auto-scroll status
*/
enum
{
	GRIDBASE_AS_STATUS_START = 0,
	GRIDBASE_AS_STATUS_STYLE = GRIDBASE_AS_STATUS_START,   /// refer to GridTouchMoveStyle_t
	GRIDBASE_AS_STATUS_SPEEDUP,	// refer to GridTouchASSpeedUp_t
	GRIDBASE_AS_STATUS_THRESHOLD,	// refer to GridTouchASThreshold_t
	GRIDBASE_AS_STATUS_MOVING,	// refer to GridTouchASMoving_t
	GRIDBASE_AS_STATUS_END = 7
};

/**
* Auto-scroll status bit value
*/
#define GRIDBASE_AS_STATUS_BIT_INTERVAL	4	// 4 bits to represent one kind of status
#define GRIDBASE_AS_STATUS_SHIFT_STYLE		(GRIDBASE_AS_STATUS_STYLE*GRIDBASE_AS_STATUS_BIT_INTERVAL)
#define GRIDBASE_AS_STATUS_SHIFT_SPEEDUP	(GRIDBASE_AS_STATUS_SPEEDUP*GRIDBASE_AS_STATUS_BIT_INTERVAL)
#define GRIDBASE_AS_STATUS_SHIFT_THRESHOLD	(GRIDBASE_AS_STATUS_THRESHOLD*GRIDBASE_AS_STATUS_BIT_INTERVAL)
#define GRIDBASE_AS_STATUS_SHIFT_MOVING		(GRIDBASE_AS_STATUS_MOVING*GRIDBASE_AS_STATUS_BIT_INTERVAL)

/**
* Auto-scroll status Mask
*/
#define GRIDBASE_AS_MASK_STYLE		(0xF<<GRIDBASE_AS_STATUS_SHIFT_STYLE)
#define GRIDBASE_AS_MASK_SPEEDUP	(0xF<<GRIDBASE_AS_STATUS_SHIFT_SPEEDUP)
#define GRIDBASE_AS_MASK_THRESHOLD	(0xF<<GRIDBASE_AS_STATUS_SHIFT_THRESHOLD)
#define GRIDBASE_AS_MASK_MOVING		(0xF<<GRIDBASE_AS_STATUS_SHIFT_MOVING)


/**
* Macro to Get auto-scroll status value
*/
#define GRIDBASE_GET_AS_STYLE(_pGridBase) \
	(GridTouchASStype_t)(((_pGridBase)->nAutoscrollStatus&GRIDBASE_AS_MASK_STYLE)>>GRIDBASE_AS_STATUS_SHIFT_STYLE)
#define GRIDBASE_GET_AS_SPEEDUP(_pGridBase) \
	(GridTouchASSpeedUp_t)(((_pGridBase)->nAutoscrollStatus&GRIDBASE_AS_MASK_SPEEDUP)>>GRIDBASE_AS_STATUS_SHIFT_SPEEDUP)
#define GRIDBASE_GET_AS_THRESHOLD(_pGridBase) \
	(GridTouchASThreshold_t)(((_pGridBase)->nAutoscrollStatus&GRIDBASE_AS_MASK_THRESHOLD)>>GRIDBASE_AS_STATUS_SHIFT_THRESHOLD)
#define GRIDBASE_GET_AS_MOVING(_pGridBase) \
	(GridTouchASMoving_t)(((_pGridBase)->nAutoscrollStatus&GRIDBASE_AS_MASK_MOVING)>>GRIDBASE_AS_STATUS_SHIFT_MOVING)

/**
* Macro to Set auto-scroll status value
*/
#define GRIDBASE_SET_AS_STYLE(_pGridBase, _ScrStyle) \
	(_pGridBase)->nAutoscrollStatus = ((_pGridBase)->nAutoscrollStatus&(~GRIDBASE_AS_MASK_STYLE))|(((u32)_ScrStyle)<<GRIDBASE_AS_STATUS_SHIFT_STYLE)
#define GRIDBASE_SET_AS_SPEEDUP(_pGridBase, _SpeedUp) \
	(_pGridBase)->nAutoscrollStatus = ((_pGridBase)->nAutoscrollStatus&(~GRIDBASE_AS_MASK_SPEEDUP))|(((u32)_SpeedUp)<<GRIDBASE_AS_STATUS_SHIFT_SPEEDUP)
#define GRIDBASE_SET_AS_THRESHOLD(_pGridBase, _Threshold) \
	(_pGridBase)->nAutoscrollStatus = ((_pGridBase)->nAutoscrollStatus&(~GRIDBASE_AS_MASK_THRESHOLD))|(((u32)_Threshold)<<GRIDBASE_AS_STATUS_SHIFT_THRESHOLD)
#define GRIDBASE_SET_AS_MOVING(_pGridBase, _Moving) \
	(_pGridBase)->nAutoscrollStatus = ((_pGridBase)->nAutoscrollStatus&(~GRIDBASE_AS_MASK_MOVING))|(((u32)_Moving)<<GRIDBASE_AS_STATUS_SHIFT_MOVING)

#endif /* __TOUCH_SCREEN_MMI__ */

typedef enum {
	GRIDBASE_SCRL_MODE_SCROLL = 0,
	GRIDBASE_SCRL_MODE_FOCUS
} GridbaseScrollMode_t;


// RELOAD flag
enum
{
	GRIDBASE_WDG_RELOAD_FLAG_START = 0,
	GRIDBASE_WDG_RELOAD_FLAG_ITEMHEIGHT = GRIDBASE_WDG_RELOAD_FLAG_START,   ///< nItemHeight
	GRIDBASE_WDG_RELOAD_FLAG_ITEMWIDTH,	///< nItemWidth
	GRIDBASE_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define GRIDBASE_WDG_RELOAD_MASK_ITEMHEIGHT         (1<<GRIDBASE_WDG_RELOAD_FLAG_ITEMHEIGHT)
#define GRIDBASE_WDG_RELOAD_MASK_ITEMWIDTH        (1<<GRIDBASE_WDG_RELOAD_FLAG_ITEMWIDTH)
/**
* Macro to get flag value
*/
#define GRIDBASE_WDG_ITEMHEIGHT_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&GRIDBASE_WDG_RELOAD_MASK_ITEMHEIGHT)>>GRIDBASE_WDG_RELOAD_FLAG_ITEMHEIGHT)
#define GRIDBASE_WDG_ITEMWIDTH_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&GRIDBASE_WDG_RELOAD_MASK_ITEMWIDTH)>>GRIDBASE_WDG_RELOAD_FLAG_ITEMWIDTH)
/**
* Macro to Set flag value
*/
#define GRIDBASE_WDG_ITEMHEIGHT_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~GRIDBASE_WDG_RELOAD_MASK_ITEMHEIGHT))|(((u32)_b)<<GRIDBASE_WDG_RELOAD_FLAG_ITEMHEIGHT)
#define GRIDBASE_WDG_ITEMWIDTH_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~GRIDBASE_WDG_RELOAD_MASK_ITEMWIDTH))|(((u32)_b)<<GRIDBASE_WDG_RELOAD_FLAG_ITEMWIDTH)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ boolean GridWdgBase_HandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
//constructor
__SLDPM_FREE__ MAE_Ret GridWdgBaseStructCtor(GridWdgBase_t *pThis, KEY_MOVE_FUNCPTR pfMove);

//destructor
__SLDPM_FREE__ void GridWdgBaseStructDtor(GridWdgBase_t *pThis);

//free obj function
void GridWdgBaseStructFreeObj(GridWdgBase_t *pThis);

//set size
__SLDPM_FREE__ void GridWdgBase_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);

//get preferred size
__SLDPM_FREE__ void GridWdgBase_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);

//intersect opaque
__SLDPM_FREE__ boolean GridWdgBase_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);

//draw
__SLDPM_FREE__ void GridWdgBase_DefDraw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);

//set model
__SLDPM_FREE__ MAE_Ret GridWdgBase_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);

//set widget
__SLDPM_FREE__ void GridWdgBase_SetWidget(IDecorator *pIDecorator, IWidget *pChild);

//invalidate
__SLDPM_FREE__ void GridWdgBase_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);

//locate
__SLDPM_FREE__ MAE_Ret GridWdgBase_Locate(IDecorator *pIDecorator, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);

boolean GridWdgBase_NotifySelect(GridWdgBase_t *pThis);
__SLDPM_FREE__ boolean GridWdgBase_NotifyFocus(GridWdgBase_t *pThis);
__SLDPM_FREE__ void GridWdgBase_NotifyScroll(GridWdgBase_t *pThis, boolean bVert);
__SLDPM_FREE__ void GridWdgBase_NotifyBoundary(GridWdgBase_t *pThis, boolean bTop);
__SLDPM_FREE__ boolean ListMode_KeyMove(GridWdgBase_t *pThis, u32 nKey);
__SLDPM_FREE__ boolean GirdMode_KeyMove(GridWdgBase_t *pThis, u32 nKey);
__SLDPM_FREE__ boolean GridWdgBase_GetProperty(GridWdgBase_t *pThis, u32 P1, u32 P2);
__SLDPM_FREE__ boolean GridWdgBase_SetProperty(GridWdgBase_t *pThis, u32 P1, u32 P2);

#if defined(__AUTO_ROTATE_DISPLAY__) || defined(__MULTI_THEMES_ENABLED__)
static void _GridWdgBase_ReloadRC(GridWdgBase_t *pThis, DisplayMode_e nDispMode);
#endif


#endif //__MAE_GRIDWIDGETBASE_H__
/*=============================================================*/
// end of file
