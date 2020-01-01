#ifndef __MMI_WDG_RINGLIST_PRIV_H__
#define __MMI_WDG_RINGLIST_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_ringlist.h"
#include "mmi_mae_common_def.h"
#include "mae_decoratorbase.h"
#include "mmi_mae_model.h"
#include "mmi_mae_listmodel.h"
#include "mae_wdgbackground.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct {
	s32      nRollingPixels; //how many pixels to roll.
	s32      nTargetHLIdx;   //which index item we want to roll to. If value is -1, adjust the highlight to center after rolling all pixels in nRollingPixels.
	u8       nRollingSteps;  //total steps to roll, zero means no need to roll.
} _RollingData_t;

typedef struct {
	DecoratorEx_t    DecBase;         ///< A decorator base structure DecoratorEx_t to support border
	IListModel      *pListMdl;        ///< A list model pointer to keep data
	ModelListener_t  ListMdlLsn;      ///< model listener for list-model

	IModel          *pItemWdgMdl;    ///< Model from item widget(child widget)
	MAE_IId          nItemMdlId;     ///< the interface id of item widget's model
	IModel          *pItemWdgViewMdl;///< item widget's view model
	ModelListener_t  ItemWdgViewMdlLsn;///< model listener for item widget's view model

	WdgLayoutStyle_t nLayoutMode;    ///< only accept LAYOUT_STYLE_VERTICAL, LAYOUT_STYLE_HORIZONTAL(default)
	s32              nHighLightIdx;  ///< The index of highlighted element, zero base.
	s32              nOffset;        ///offset for display items, should not bigger than nItemWidth/nItemHeight
	_RollingData_t   stRollingData;

	u16              nItemWidth;     ///< normal item width
	u16              nItemHeight;    ///< normal item height
	u16              nHlItemSpace;   ///< highlighted item space(width or height)
	u16              nItemGap;       ///< The white space in pixels between every item

	WdgItemBG_t      stHlItemBg;     ///< the background color/image for highlighted item

#ifdef __TOUCH_SCREEN_MMI__
	RingListTSMoveStyle_t   TSMoveStyle;///RINGLIST_TOUCH_MOVE_STYLE_NONE: handle MAE_EVT_TS_RELEASE to decide which item to be highlight
	                                    ///RINGLIST_TOUCH_MOVE_STYLE_MOVE_LOCATION: handles MAE_EVT_TS_PRESS,MAE_EVT_TS_MOVE,MAE_EVT_TS_RELEASE to move location.
	ITouchSrv               *pITouchSrv;///< Pointer to the touch service object
	s32                     nTS_StartX; /// Used to keep pressed x position in RINGLIST_TOUCH_MOVE_STYLE_MOVE_LOCATION move style.
	s32                     nTS_StartY; /// Used to keep pressed y position in RINGLIST_TOUCH_MOVE_STYLE_MOVE_LOCATION move style.
#endif // __TOUCH_SCREEN_MMI__
} _RingListWidget_t;

/// Status flags
enum
{
	RL_WDG_FLAG_STAR = DEC_BASE_FLAG_END,
	RL_WDG_FLAG_NO_WRAP = RL_WDG_FLAG_STAR,
	RL_WDG_FLAG_ENABLE_ROLLING,
	RL_WDG_FLAG_ROLLING_TIMER_RUN,
#ifdef __TOUCH_SCREEN_MMI__
	RL_WDG_FLAG_TOUCH_PRESSED,
	RL_WDG_FLAG_HELD_BY_TOUCH,
#endif // __TOUCH_SCREEN_MMI__
	RL_WDG_FLAG_END
};

/// Masks
#define RL_WDG_MASK_NO_WRAP            (1<<RL_WDG_FLAG_NO_WRAP)
#define RL_WDG_MASK_ENABLE_ROLLING     (1<<RL_WDG_FLAG_ENABLE_ROLLING)
#define RL_WDG_MASK_ROLLING_TIMER_RUN  (1<<RL_WDG_FLAG_ROLLING_TIMER_RUN)
#ifdef __TOUCH_SCREEN_MMI__
#define RL_WDG_MASK_TOUCH_PRESSED      (1<<RL_WDG_FLAG_TOUCH_PRESSED)
#define RL_WDG_MASK_HELD_BY_TOUCH      (1<<RL_WDG_FLAG_HELD_BY_TOUCH)
#endif // __TOUCH_SCREEN_MMI__

/// macro to Get flag
#define RL_WDG_IS_NO_WRAP(_pRLWdg_) \
	(boolean)(((_pRLWdg_)->DecBase.WdgBase.Flags&RL_WDG_MASK_NO_WRAP)>>RL_WDG_FLAG_NO_WRAP)
#define RL_WDG_ENABLE_ROLLING(_pRLWdg_) \
	(boolean)(((_pRLWdg_)->DecBase.WdgBase.Flags&RL_WDG_MASK_ENABLE_ROLLING)>>RL_WDG_FLAG_ENABLE_ROLLING)
#define RL_WDG_IS_ROLLING_TIMER_RUNNING(_pRLWdg_) \
	(boolean)(((_pRLWdg_)->DecBase.WdgBase.Flags&RL_WDG_MASK_ROLLING_TIMER_RUN)>>RL_WDG_FLAG_ROLLING_TIMER_RUN)
#ifdef __TOUCH_SCREEN_MMI__
#define RL_WDG_IS_TOUCH_PRESSED(_pRLWdg_) \
	(boolean)(((_pRLWdg_)->DecBase.WdgBase.Flags&RL_WDG_MASK_TOUCH_PRESSED)>>RL_WDG_FLAG_TOUCH_PRESSED)
#define RL_WDG_IS_HELD_BY_TOUCH(_pRLWdg_) \
	(boolean)(((_pRLWdg_)->DecBase.WdgBase.Flags&RL_WDG_MASK_HELD_BY_TOUCH)>>RL_WDG_FLAG_HELD_BY_TOUCH)
#endif // __TOUCH_SCREEN_MMI__

/// macro to set flag
#define RL_WDG_SET_NO_WRAP(_pRLWdg_, _b) \
	(_pRLWdg_)->DecBase.WdgBase.Flags = ((_pRLWdg_)->DecBase.WdgBase.Flags&(~RL_WDG_MASK_NO_WRAP))|(((u32)_b)<<RL_WDG_FLAG_NO_WRAP)
#define RL_WDG_SET_ENABLE_ROLLING(_pRLWdg_, _b) \
	(_pRLWdg_)->DecBase.WdgBase.Flags = ((_pRLWdg_)->DecBase.WdgBase.Flags&(~RL_WDG_MASK_ENABLE_ROLLING))|(((u32)_b)<<RL_WDG_FLAG_ENABLE_ROLLING)
#define RL_WDG_SET_ROLLING_TIMER_RUNNING(_pRLWdg_, _b) \
	(_pRLWdg_)->DecBase.WdgBase.Flags = ((_pRLWdg_)->DecBase.WdgBase.Flags&(~RL_WDG_MASK_ROLLING_TIMER_RUN))|(((u32)_b)<<RL_WDG_FLAG_ROLLING_TIMER_RUN)
#ifdef __TOUCH_SCREEN_MMI__
#define RL_WDG_SET_TOUCH_PRESSED(_pRLWdg_, _b) \
	(_pRLWdg_)->DecBase.WdgBase.Flags = ((_pRLWdg_)->DecBase.WdgBase.Flags&(~RL_WDG_MASK_TOUCH_PRESSED))|(((u32)_b)<<RL_WDG_FLAG_TOUCH_PRESSED)
#define RL_WDG_SET_HELD_BY_TOUCH(_pRLWdg_, _b) \
	(_pRLWdg_)->DecBase.WdgBase.Flags = ((_pRLWdg_)->DecBase.WdgBase.Flags&(~RL_WDG_MASK_HELD_BY_TOUCH))|(((u32)_b)<<RL_WDG_FLAG_HELD_BY_TOUCH)
#endif // __TOUCH_SCREEN_MMI__


/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAERet_t RingListWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean  RingListWdg_DefHandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);


/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAERet_t RingListWdgStructCtor(_RingListWidget_t *pThis);
static void RingListWdgStructDtor(_RingListWidget_t *pThis);
static void RingListWidget_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
static void RingListWidget_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
static boolean RingListWidget_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
static MAERet_t RingListWidget_SetModel(IDecorator *pIDecorator, IModel *pIModel, IBase* pOwner);
static void RingListWidget_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
static MAERet_t RingListWidget_Locate(IDecorator *pIDecorator, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);
static void RingListWidget_SetDecWidget(IDecorator *pIDecorator, IWidget *pChild);
void _RingListWdg_DefDraw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);
static void _RingListWdg_ListMdlListener(void *pData, ModelEvent_t *pMdlEvt);
static void _RingListWdg_ItemWdgViewMdlListener(void *pData, ModelEvent_t *pMdlEvt);
static u32 _RingListWdg_GetListMdlSize(_RingListWidget_t *pThis);
static void _RingListWdg_FindOutIidOfItemModel(_RingListWidget_t *pThis);
static boolean _RingListWdg_GetProperty(_RingListWidget_t *pThis, u32 P1, u32 P2);
static boolean _RingListWdg_SetProperty(_RingListWidget_t *pThis, u32 P1, u32 P2);
static boolean _RingListWdg_HandleNaviKey(_RingListWidget_t *pThis, u32 nKey);
static MAERet_t _RingListWdg_CalcRectForItem(_RingListWidget_t *pThis, s32 nIndex, Rect_t *pRcOut);
static void _RingListWdg_CalcRectByIndexOffset(_RingListWidget_t *pThis, s32 nIdxOffset, Rect_t *pRcOut);
static s32 _RingListWdg_CalcItemOffsetToHighlightItem(_RingListWidget_t *pThis, s32 nIndex);
static s32 _RingListWdg_CalcItemIndexByOffset(_RingListWidget_t *pThis, s32 nOffset);
static void _RingListWdg_DrawItem(_RingListWidget_t *pThis, 
								  IDispCanvas *pIDispCanvas, 
								  const Rect_t *pItemRc, 
								  const Rect_t *pDispRc, 
								  s32 nIndex
								  );
__inline static void _RingListWdg_SetListDataToItemWdg(_RingListWidget_t *pThis, u32 index);
static void _RingListWdg_SetDataToItemDataMdl(_RingListWidget_t *pThis, void *pData);
static void _RingListWdg_NotifyFocusChange(_RingListWidget_t *pThis);
static void _RingListWdg_NotifyRollingStart(_RingListWidget_t *pThis);
static void _RingListWdg_NotifyRollingFinished(_RingListWidget_t *pThis);
static s32 _RingListWdg_DrawingOffsetUpperBound(u32 nSize, s32 nHighlightIdx, boolean bNoWrap);
static s32 _RingListWdg_DrawingOffsetLowerBound(u32 nSize, s32 nHighlightIdx, boolean bNoWrap);
static void _RingListWdg_StartRollingByNewIndex(_RingListWidget_t *pThis, s32 nNewHlIdx);
static void _RingListWdg_StartRollingByIdxOffset(_RingListWidget_t *pThis, s32 nIdxOffset, s32 nTargetIdx);
static void _RingListWdg_RollingTimerCB(_RingListWidget_t *pThis, void *pUser);

#ifdef __TOUCH_SCREEN_MMI__
static boolean _RingListWdg_HandleTouchEvents(_RingListWidget_t *pThis, MAEEvent_t evt, s32 x, s32 y);
static MAERet_t _RingListWdg_GetIdxOffsetByLocation(_RingListWidget_t *pThis, s32 x, s32 y, s32 *pOutIdxOffset);
static void _RingListWdg_ChangeHighlightIdxByLocation(_RingListWidget_t *pThis, s32 x, s32 y);
static void _RingListWdg_MoveLocationByNewXY(_RingListWidget_t *pThis, s32 NewX, s32 NewY);
static void _RingListWdg_MoveToNearestItem(_RingListWidget_t *pThis);

#endif //__TOUCH_SCREEN_MMI__

#endif //__MMI_WDG_RINGLIST_PRIV_H__
/*=============================================================*/
// end of file
