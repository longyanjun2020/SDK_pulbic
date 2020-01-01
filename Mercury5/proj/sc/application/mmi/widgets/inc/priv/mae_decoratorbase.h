/**
* @file mae_decoratorbase.h
* @version $Id: mae_decoratorbase.h 38890 2009-08-29 16:22:38Z zinc.chen $
* @brief
*/
/*=============================================================
File name: mae_decoratorwidget_priv.h
Description:
=============================================================*/
#ifndef __MAE_DECORATORWIDGET_PRIV_H__
#define __MAE_DECORATORWIDGET_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_containerbase.h"
#include "mmi_mae_decorator.h"
#include "mae_widgetbase.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef void (*DECORATOR_DRAW_FUNC_PTR) (IDecorator*, IDispCanvas*, s32, s32);


/**
* @brief  Using Decorator_t as base structure if implement IDecorator WITHOUT border.
* @note   Now we use "Flags" in WidgetBase_t/WidgetBaseEx_t to keep the status of disable/enable invalidate flag.
*/
typedef struct Decorator_Tag{
	WidgetBase_t    WdgBase;     ///< Using WidgetBase_t as a base structure.
	IWidget         *pChildWdg;  ///< A IWidget pointer to keep child widget.
}Decorator_t;

/**
* @brief  Using DecoratorEx_t as base structure when implement IDecorator with border.
* @note   Now we use "Flags" in WidgetBase_t/WidgetBaseEx_t to keep the status of disable/enable invalidate flag.
*/
typedef struct DecoratorEx_Tag{
	WidgetBaseEx_t  WdgBase;     ///< Using WidgetBaseEx_t as a base structure.
	IWidget         *pChildWdg;  ///< A IWidget pointer to keep child widget.
}DecoratorEx_t;

//Please use the following macros to get/set the flag value.
enum
{
	DEC_BASE_FLAG_START = WDG_BASE_FLAG_END,
	DEC_BASE_FLAG_DISABLE_INVALIDATE = DEC_BASE_FLAG_START,
	DEC_BASE_FLAG_END
};//Note: DEC_BASE_FLAG_END is 10 now.
/**
* Flag Mask
*/
#define DEC_MASK_IS_DISABLE_INVALIDATE		(1<<DEC_BASE_FLAG_DISABLE_INVALIDATE)

/**
* Macro to Get flag value
* DEC_IS_FOCUSED, get "is focused" flag value
* DEC_CAN_BE_FOCUSED, get "can be focused" flag value
* DEC_IS_SUPPORT_BORDDR, get "support border" flag value
* DEC_IS_DISABLE_INVALIDATE, get "disable invalidate" flag value
*/
#define DEC_IS_FOCUSED(_pDecBase) \
	WDG_IS_FOCUSED(&((_pDecBase)->WdgBase))
//(boolean)(((_pDecBase)->WdgBase.Flags&WDG_MASK_IS_FOCUSED)>>WDG_BASE_FLAG_IS_FOCUSED)
#define DEC_CAN_BE_FOCUSED(_pDecBase) \
	WDG_CAN_BE_FOCUSED(&((_pDecBase)->WdgBase))
//(boolean)(((_pDecBase)->WdgBase.Flags&WDG_MASK_CAN_BE_FOCUSED)>>WDG_BASE_FLAG_CAN_BE_FOCUSED)
#define DEC_IS_SUPPORT_BORDER(_pDecBase) \
	WDG_IS_SUPPORT_BORDDR(&((_pDecBase)->WdgBase))
//(boolean)(((_pDecBase)->WdgBase.Flags&WDG_MASK_SUPPORT_BORDDR)>>WDG_BASE_FLAG_SUPPORT_BORDER)
#define DEC_IS_DISABLE_INVALIDATE(_pDecBase) \
	(boolean)(((_pDecBase)->WdgBase.Flags&DEC_MASK_IS_DISABLE_INVALIDATE)>>DEC_BASE_FLAG_DISABLE_INVALIDATE)
/*deprecated
#define DEC_CHILD_GET_SELECTED(_pDecBase) \
    (_pDecBase)->pChildWdg ? WDG_GET_SELECTED((WidgetBase_t *)(_pDecBase)->pChildWdg) : FALSE
*/

/**
* Macro to Set flag value
* DEC_SET_FOCUSED, to set "focused" flag value
* DEC_SET_CAN_BE_FOCUSED, to set "can be focused" flag value
* DEC_SET_DISABLE_INVALIDATE, to set "disable invalidate" flag value
*/
#define DEC_SET_FOCUSED(_pDecBase, _b) \
	WDG_SET_FOCUSED(&((_pDecBase)->WdgBase), _b)
//(_pDecBase)->WdgBase.Flags = ((_pDecBase)->WdgBase.Flags&(~WDG_MASK_IS_FOCUSED))|(((u32)_b)<<WDG_BASE_FLAG_IS_FOCUSED)
#define DEC_SET_CAN_BE_FOCUSED(_pDecBase, _b) \
	WDG_SET_CAN_BE_FOCUSED(&((_pDecBase)->WdgBase), _b)
//(_pDecBase)->WdgBase.Flags = ((_pDecBase)->WdgBase.Flags&(~WDG_MASK_CAN_BE_FOCUSED))|(((u32)_b)<<WDG_BASE_FLAG_CAN_BE_FOCUSED)
#define DEC_SET_DISABLE_INVALIDATE(_pDecBase, _b) \
	(_pDecBase)->WdgBase.Flags = ((_pDecBase)->WdgBase.Flags&(~DEC_MASK_IS_DISABLE_INVALIDATE))|(((u32)_b)<<DEC_BASE_FLAG_DISABLE_INVALIDATE)
/*deprecated
#define DEC_CHILD_SET_SELECTED(_pDecBase, _b) \
    (_pDecBase)->pChildWdg ? WDG_SET_CHILD_SELECTED((WidgetBase_t *)(_pDecBase)->pChildWdg, _b) : (_b = (u32)FALSE)
*/

/*=============================================================*/
// functions
/*=============================================================*/
/*------------------------------------------------------------------------------------------
* Constructor and Destructor for DecoratorBase
------------------------------------------------------------------------------------------*/

// for a new style decorator
MAE_Ret WdgDecoratorBaseConstructor(DecoratorEx_t *pDecorator);
void WdgDecoratorBaseDestructor(DecoratorEx_t *pDecorator);

// for a old style decorator
MAE_Ret DecoratorBaseExStructCtor(DecoratorEx_t *pThis, const FUNCTBL(IDecorator) *FtblPtr, WHANDLER_HDL_FUNC_PTR pfnHandler, DECORATOR_DRAW_FUNC_PTR pfnDraw);

/*------------------------------------------------------------------------------------------
* For IBase interface
------------------------------------------------------------------------------------------*/
u32 DecoratorBase_Release(IDecorator *pIDecorator);
MAE_Ret DecoratorBase_QueryInterface(IDecorator *pIDecorator, MAE_IId iId, void **ppObj, IBase *pOwner);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
void DecoratorBase_GetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
void DecoratorBase_SetSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
void DecoratorBase_GetPreferredSize(IDecorator *pIDecorator, WidgetSize_t *pSize);
boolean DecoratorBase_IntersectOpaque(IDecorator *pIDecorator, const Rect_t *pInRect, Rect_t *pOutRect);
void DecoratorBase_DefDraw(IDecorator *pIDecorator, IDispCanvas *pIDispCanvas, s32 x, s32 y);

/*------------------------------------------------------------------------------------------
* For IContainer interface
------------------------------------------------------------------------------------------*/
MAE_Ret DecoratorBase_Add(IDecorator *pIDecorator, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isBefore, const void *DescPtr);
MAE_Ret DecoratorBase_Delete(IDecorator *pIDecorator, IWidget *WidgetPtr);
MAE_Ret DecoratorBase_Move(IDecorator *pIDecorator, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isBefore);
IWidget *DecoratorBase_GetWidget(IDecorator *pIDecorator, IWidget *RefWidgetPtr, boolean isBefore, boolean isWrap, IBase *pOwner);
void    DecoratorBase_Invalidate(IDecorator *pIDecorator, IWidget *WidgetPtr, const Rect_t *WRectPtr, InvFlag_t Flags);
MAE_Ret DecoratorBase_Locate(IDecorator *pIDecorator, IWidget *WidgetPtr, IContainer **ppRoot, Rect_t *RelativeRectPtr, IBase *pOwner);
MAERet_t DecoratorBase_RequestUp(IDecorator *pIDecorator, MAEEvent_t evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IDecorator interface
------------------------------------------------------------------------------------------*/
void DecoratorBase_GetDecWidget(IDecorator *pIDecorator, IWidget **ppChild, IBase *pOwner);
void DecoratorBase_SetDecWidget(IDecorator *pIDecorator, IWidget *pChild, IBase *pOwner);

/*------------------------------------------------------------------------------------------
* Other function for decorator base
------------------------------------------------------------------------------------------*/
void DecoratorBase_HandleChildSetFocus(Decorator_t *pThis, boolean bFocus, IWidget *pIWidget);
boolean DecoratorBase_DefHandleEvent(IDecorator *pIDecorator, MAE_EventId evt, u32 P1, u32 P2);

/* Get/Set property function will NOT send unhalded property to child */
boolean DecoratorBase_SetProperty(Decorator_t *pThis, u32 P1, u32 P2);
boolean DecoratorBase_GetProperty(Decorator_t *pThis, u32 P1, u32 P2);

__INLINE IWidget* DecoratorBase_GetChildWidget(Decorator_t *pThis)
{
	if (!pThis)
	{
		return NULL;
	}
	if (DEC_IS_SUPPORT_BORDER(pThis))
	{
		DecoratorEx_t *pThisEx = (DecoratorEx_t*)pThis;
		return (pThisEx->pChildWdg);
	}
	else
	{
		return (pThis->pChildWdg);
	}
}

__INLINE void DecoratorBase_SetChildWidget(Decorator_t *pThis, IWidget *pChdWdg)
{
	if (!pThis)
	{
		return;
	}
	if(pChdWdg)
	{
        WdgCommonSetProperty(pChdWdg, PROP_WDG_3D_ENABLE, WDG_IS_3D_ENABLE((WidgetBase_t*)pThis));
	}
	if (DEC_IS_SUPPORT_BORDER(pThis))
	{
		DecoratorEx_t *pThisEx = (DecoratorEx_t*)pThis;
		pThisEx->pChildWdg = pChdWdg;
	}
	else
	{
		pThis->pChildWdg = pChdWdg;
	}
}



#endif //__MAE_DECORATORWIDGET_PRIV_H__
/*=============================================================*/
// end of file
