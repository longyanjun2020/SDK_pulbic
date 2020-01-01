/**
 * @file    mmi_wdg_drag.h
 * @version $Id: mmi_wdg_drag.h  2009-09-01 ken.zhou $
 * @brief   This file defines the interface of DRAGWIDGET
 *
 * @CLS ID : CLSID_DRAGWIDGET
 */
#ifndef MMI_WDG_DRAG_H
#define MMI_WDG_DRAG_H


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_propcontainer.h"
#include "mmi_mae_image.h"
#include "mmi_wdg_common_interface.h"


/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum
{
	DRAG_WIDGET_DISPLAY_NORMAL,
	DRAG_WIDGET_DISPLAY_FOCUS,
	DRAG_WIDGET_DISPLAY_DRAG,
	DRAG_WIDGET_DISPLAY_ANIM,
    DRAG_WIDGET_DISPLAY_FOCUS_BY_MASK,
    DRAG_WIDGET_DISPLAY_DRAG_BY_RESIZE,
	DRAG_WIDGET_DISPLAY_TATOL,
}DRAGWDG_DISPLAY_STYLE_e;

// for indicate Ifone widget animation style
typedef enum
{
	DRAGWDG_ANIMSTYLE_NONE,
	DRAGWDG_ANIMSTYLE_CHANGEANGLE,	// change image angle
	DRAGWDG_ANIMSTYLE_MOVE,	// move image position
}DRAGWDG_ANIMSTYLE_e;

typedef enum
{
	DRAG_Direction_Left,
	DRAG_Direction_Right,
	DRAG_Direction_Up,
	DRAG_Direction_Down,
	DRAG_Direction_Center,
}DRAGWDG_ANIM_DIRECTION_e;

typedef enum
{
	DRAGWDG_DOWNTEXT_STYLE_SHOWTEXT,
	DRAGWDG_DOWNTEXT_STYLE_SHOWIMAGE,
}DRAGWDG_DOWNTEXT_STYLE_e;


/*=============================================================*/
// interface function
/*=============================================================*/
IWidget* WdgDragCreate(void);

__INLINE void WdgDragSetDisplayStyle(IWidget *pIWidget, DRAGWDG_DISPLAY_STYLE_e eMode)
{
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
	WdgCommonSetProperty((IWidget *)(pIWidget), PROP_DRAG_WDG_DISPLAY_STYLE, eMode);
#endif //__UI_STYLE_MMI_ANDROID_IDLE__
}

void WdgDrag_SetAnimation(IWidget *pIWidget, boolean bEnableAnim);

__INLINE void WdgDragSetMainImageID(IWidget *pIWidget, u32 nImageID)
{
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
	WdgCommonSetProperty((IWidget *)(pIWidget), PROP_DRAG_WDG_MAINIMAGEID, nImageID);
#endif //__UI_STYLE_MMI_ANDROID_IDLE__
}

__INLINE void WdgDragSetFocusImageID(IWidget *pIWidget, u32 nImageID)
{
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
	WdgCommonSetProperty((IWidget *)(pIWidget), PROP_DRAG_WDG_FOCUSIMAGEID, nImageID);
#endif //__UI_STYLE_MMI_ANDROID_IDLE__
}

__INLINE void WdgDragSetDragImageID(IWidget *pIWidget, u32 nImageID)
{
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
	WdgCommonSetProperty((IWidget *)(pIWidget), PROP_DRAG_WDG_DRAGIMAGEID, nImageID);
#endif //__UI_STYLE_MMI_ANDROID_IDLE__
}

__INLINE void WdgDragSetDownImageID(IWidget *pIWidget, u32 nImageID)
{
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
	WdgCommonSetProperty((IWidget *)(pIWidget), PROP_DRAG_WDG_DOWNIMAGEID, nImageID);
#endif //__UI_STYLE_MMI_ANDROID_IDLE__
}

__INLINE void WdgDragSetDownTextStyle(IWidget *pIWidget, DRAGWDG_DOWNTEXT_STYLE_e eMode)
{
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
	WdgCommonSetProperty((IWidget *)(pIWidget), PORP_DRAG_WDG_DOWNTEXT_STYLE, eMode);
#endif //__UI_STYLE_MMI_ANDROID_IDLE__
}

MAE_Ret WdgDragSetMaskImageID(IWidget *pIWidget, u32 nMaskImageID);

MAE_Ret WdgDragSetAlpha(IWidget *pIWidget, u8 nAlpha);

MAE_Ret WdgDragSetDragSize(IWidget *pIWidget, WidgetSize_t *pSize);

#endif	//MMI_WDG_DRAG_H
/*=============================================================*/
// end of file
