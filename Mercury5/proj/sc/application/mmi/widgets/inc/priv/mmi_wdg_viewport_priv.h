#ifndef __MMI_WDG_VIEWPORT_PRIV_H__
#define __MMI_WDG_VIEWPORT_PRIV_H__

#include "mae_decoratorbase.h"
#include "mae_animation.h"
#ifdef __TOUCH_SCREEN_MMI__
#include "mmi_mae_touchsrv.h"
#endif /* __TOUCH_SCREEN_MMI__ */


/*************************************************************************/
/*   Type/Structure/Enum definitions                                     */
/*************************************************************************/
#define VIEWPORT_WDG_DEFAULT_TS_START	0x80000000
#define VIEWPORT_WDG_DEFAULT_STEP	    10
// the variable deprecated, keep it for the purpose of compatibility
#define VIEWPORT_WDG_MENU_GRID_Y_SIZE 1

typedef struct{
	DecoratorEx_t   DecBase;
	WidgetSize_t  ChildSize;
	s32           xOffset;          ///< when child w > viewport w, xOffset can be > 0, else xOffset is always 0
	s32           yOffset;          ///< when child h > viewport h, yOffset can be > 0, else yOffset is always 0
	s32           xOffMax;
	s32           yOffMax;
	u16           step;
	u8            Alignment;
	u32           nStatusFlags;      /*!< keeps many flags, such as
	                                      "keep in center",
	                                      "lock horz movement",
	                                      "lock vert movement"
	                                 */
    ViewportAnimCb_t tAnimCb;
    ViewportAnimStyleData_t *pAnimStyleData;
    boolean bPlayAnim;
    boolean       bVertOverBound;
    boolean       bHorzOverBound;
#ifdef __TOUCH_SCREEN_MMI__
    s32           TS_StartX;
	s32           TS_StartY;
	s32           TS_EndX;
	s32           TS_EndY;
	u32           TS_StartXoff;
	u32           TS_StartYoff;
	boolean       bRegTouchSrv;
	ITouchSrv    *pTouchSrv;
// the following variables are deprecated, keep it for the purpose of compatibility
// use MMI_Common_SetViewportAnim to call View port Android animation
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__
    boolean       bIsCellMainMAni; // boolean ,set cell mainmenu animation flag
    boolean       bTouchSnapToGrid;
    u32           nGridYSize;
#endif
//end of deprecated
#endif
}ViewportWdg_t;

/**
* Flags in viewport widget
*/
typedef enum
{
    VP_WDG_ANIMATION_DIR_HORZ = 0,
    VP_WDG_ANIMATION_DIR_VERT,
    VP_WDG_ANIMATION_DIR_FLAG_END
}ENUM_VP_WDG_ANIMATION_DIR_FLAG;

enum
{
	VP_WDG_FLAG_START = 0,
	VP_WDG_FLAG_KEEP_CENTER = VP_WDG_FLAG_START, ///< (1 bit) a flag to indicate whether keep in center.
	VP_WDG_FLAG_LOCK_HORZ_KEYPRESS_MOVE,         ///< (1 bit) a flag to lock horizontal key press movement.
	VP_WDG_FLAG_LOCK_VERT_KEYPRESS_MOVE,         ///< (1 bit) a flag to lock vertical key press movement.
    VP_WDG_FLAG_LOCK_HORZ_TOUCH_MOVE,            ///< (1 bit) a flag to lock horizontal touch movement.
    VP_WDG_FLAG_LOCK_VERT_TOUCH_MOVE,            ///< (1 bit) a flag to lock vertical touch movement.
	VP_WDG_FLAG_LAYOUT_STYLE,                    ///< (2 bits) layout style.
	VP_WDG_FLAG_LAYOUT_STYLE1,                   ///<  2nd bit of layout style
	VP_WDG_FLAG_DISABLE_HORZ_SCROLL, 			 ///< (1 bit) a flag to disable horizontal scroll
	VP_WDG_FLAG_DISABLE_VERT_SCROLL,			 ///< (1 bit) a flag to disable vertical scroll
	VP_WDG_FLAG_ENABLE_TOUCH_CHILD,              ///< (1 bit) a flag to enable send touch event to child
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__
	VP_WDG_FLAG_DISABLE_TOUCH_EVENT,			 ///< (1 bit) a flag to disable touch event  lin.wang modify in 2010-11-19
#endif
#ifdef __TOUCH_SCREEN_MMI__
    VP_WDG_FLAG_ENABLE_HOOK_POINT,
#endif
	VP_WDG_FLAG_END
};

/**
 * Flag Mask
 */
#define VP_WDG_MASK_KEEP_CENTER			(1<<VP_WDG_FLAG_KEEP_CENTER)
#define VP_WDG_MASK_LOCK_HORZ_KEYPRESS_MOVE		(1<<VP_WDG_FLAG_LOCK_HORZ_KEYPRESS_MOVE)
#define VP_WDG_MASK_LOCK_VERT_KEYPRESS_MOVE		(1<<VP_WDG_FLAG_LOCK_VERT_KEYPRESS_MOVE)
#define VP_WDG_MASK_LOCK_HORZ_TOUCH_MOVE		(1<<VP_WDG_FLAG_LOCK_HORZ_TOUCH_MOVE)
#define VP_WDG_MASK_LOCK_VERT_TOUCH_MOVE	    (1<<VP_WDG_FLAG_LOCK_VERT_TOUCH_MOVE)
#define VP_WDG_MASK_LAYOUT_STYLE		((1<<VP_WDG_FLAG_LAYOUT_STYLE)|(1<<VP_WDG_FLAG_LAYOUT_STYLE1))
#define VP_WDG_MASK_DISALBE_HORZ_SCROLL	(1<<VP_WDG_FLAG_DISABLE_HORZ_SCROLL)
#define VP_WDG_MASK_DISABLE_VERT_SCROLL	(1<<VP_WDG_FLAG_DISABLE_VERT_SCROLL)
#define VP_WDG_MASK_ENABLE_TOUCH_CHILD	(1<<VP_WDG_FLAG_ENABLE_TOUCH_CHILD)
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__
#define VP_WDG_MASK_DISABLE_TOUCH_EVENT	(1<<VP_WDG_FLAG_DISABLE_TOUCH_EVENT) // lin.wang modify in 2010-11-19
#endif
#ifdef __TOUCH_SCREEN_MMI__
#define VP_WDG_MASK_ENABLE_HOOK_POINT	(1<<VP_WDG_FLAG_ENABLE_HOOK_POINT)
#endif

/**
 * Notify Scroll Type Mask
 */
#define VP_WDG_NTY_SCROLL_VERT  0x00000001
#define VP_WDG_NTY_SCROLL_HORZ  0x00000002

/**
 * Macro to get flag value
 */
#define VP_WDG_GET_KEEP_CENTER(_pstViewPortWdg) \
	(boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_KEEP_CENTER)>>VP_WDG_FLAG_KEEP_CENTER)
#define VP_WDG_GET_LOCK_HORZ_KEYPRESS_MOVE(_pstViewPortWdg) \
	(boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_LOCK_HORZ_KEYPRESS_MOVE)>>VP_WDG_FLAG_LOCK_HORZ_KEYPRESS_MOVE)
#define VP_WDG_GET_LOCK_VERT_KEYPRESS_MOVE(_pstViewPortWdg) \
	(boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_LOCK_VERT_KEYPRESS_MOVE)>>VP_WDG_FLAG_LOCK_VERT_KEYPRESS_MOVE)
#define VP_WDG_GET_LOCK_HORZ_TOUCH_MOVE(_pstViewPortWdg) \
    (boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_LOCK_HORZ_TOUCH_MOVE)>>VP_WDG_FLAG_LOCK_HORZ_TOUCH_MOVE)
#define VP_WDG_GET_LOCK_VERT_TOUCH_MOVE(_pstViewPortWdg) \
    (boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_LOCK_VERT_TOUCH_MOVE)>>VP_WDG_FLAG_LOCK_VERT_TOUCH_MOVE)
#define VP_WDG_GET_LAYOUT_STYLE(_pstViewPortWdg) \
	(boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_LAYOUT_STYLE)>>VP_WDG_FLAG_LAYOUT_STYLE)
#define VP_WDG_GET_DISABLE_HORZ_SCROLL(_pstViewPortWdg) \
		(boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_DISALBE_HORZ_SCROLL)>>VP_WDG_FLAG_DISABLE_HORZ_SCROLL)
#define VP_WDG_GET_DISABLE_VERT_SCROLL(_pstViewPortWdg) \
		(boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_DISABLE_VERT_SCROLL)>>VP_WDG_FLAG_DISABLE_VERT_SCROLL)
#define VP_WDG_GET_ENABLE_TOUCH_CHILD(_pstViewPortWdg) \
		(boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_ENABLE_TOUCH_CHILD)>>VP_WDG_FLAG_ENABLE_TOUCH_CHILD)
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__
#define VP_WDG_GET_ABLE_TOUCH_EVENT(_pstViewPortWdg) \
		(boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_DISABLE_TOUCH_EVENT)>>VP_WDG_FLAG_DISABLE_TOUCH_EVENT)
#endif
#ifdef __TOUCH_SCREEN_MMI__
#define VP_WDG_GET_ENABLE_HOOK_POINT(_pstViewPortWdg) \
    (boolean)(((_pstViewPortWdg)->nStatusFlags&VP_WDG_MASK_ENABLE_HOOK_POINT)>>VP_WDG_FLAG_ENABLE_HOOK_POINT)
#endif

/**
 * Macro to set flag value
 */
#define VP_WDG_SET_KEEP_CENTER(_pstViewPortWdg, _b) \
	(_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_KEEP_CENTER))|(((u32)_b)<<VP_WDG_FLAG_KEEP_CENTER)
#define VP_WDG_SET_LOCK_HORZ_KEYPRESS_MOVE(_pstViewPortWdg, _b) \
	(_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_LOCK_HORZ_KEYPRESS_MOVE))|(((u32)_b)<<VP_WDG_FLAG_LOCK_HORZ_KEYPRESS_MOVE)
#define VP_WDG_SET_LOCK_VERT_KEYPRESS_MOVE(_pstViewPortWdg, _b) \
	(_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_LOCK_VERT_KEYPRESS_MOVE))|(((u32)_b)<<VP_WDG_FLAG_LOCK_VERT_KEYPRESS_MOVE)
#define VP_WDG_SET_LOCK_HORZ_TOUCH_MOVE(_pstViewPortWdg, _b) \
    (_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_LOCK_HORZ_TOUCH_MOVE))|(((u32)_b)<<VP_WDG_FLAG_LOCK_HORZ_TOUCH_MOVE)
#define VP_WDG_SET_LOCK_VERT_TOUCH_MOVE(_pstViewPortWdg, _b) \
    (_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_LOCK_VERT_TOUCH_MOVE))|(((u32)_b)<<VP_WDG_FLAG_LOCK_VERT_TOUCH_MOVE)
#define VP_WDG_SET_LAYOUT_STYLE(_pstViewPortWdg, _b) \
	(_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_LAYOUT_STYLE))|(((u32)_b)<<VP_WDG_FLAG_LAYOUT_STYLE)
#define VP_WDG_SET_DISABLE_HORZ_SCROLL(_pstViewPortWdg, _b) \
		(_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_DISALBE_HORZ_SCROLL))|(((u32)_b)<<VP_WDG_FLAG_DISABLE_HORZ_SCROLL)
#define VP_WDG_SET_DISABLE_VERT_SCROLL(_pstViewPortWdg, _b) \
		(_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_DISABLE_VERT_SCROLL))|(((u32)_b)<<VP_WDG_FLAG_DISABLE_VERT_SCROLL)
#define VP_WDG_SET_ENABLE_TOUCH_CHILD(_pstViewPortWdg, _b) \
		(_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_ENABLE_TOUCH_CHILD))|(((u32)_b)<<VP_WDG_FLAG_ENABLE_TOUCH_CHILD)
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__
#define VP_WDG_SET_ABLE_TOUCH_EVENT(_pstViewPortWdg, _b) \
		(_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_DISABLE_TOUCH_EVENT))|(((u32)_b)<<VP_WDG_FLAG_DISABLE_TOUCH_EVENT)
#endif
#ifdef __TOUCH_SCREEN_MMI__
#define VP_WDG_SET_ENABLE_HOOK_POINT(_pstViewPortWdg, _b) \
    (_pstViewPortWdg)->nStatusFlags = ((_pstViewPortWdg)->nStatusFlags&(~VP_WDG_MASK_ENABLE_HOOK_POINT))|(((u32)_b)<<VP_WDG_FLAG_ENABLE_HOOK_POINT)
#endif
/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAERet_t ViewportWidget_New(MAE_ClsId ClsID, void **ppObj);
boolean  ViewportWidget_HandleEvent(IDecorator*, MAE_EventId, u32, u32);
/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAERet_t _WdgViewportConstructor(ViewportWdg_t *pThis);
void     _WdgViewportDestructor(ViewportWdg_t *pThis);
void     _ViewportWidget_Draw(IDecorator*, IDispCanvas*, s32, s32);

#endif /* __MMI_WDG_VIEWPORT_PRIV_H__ */
