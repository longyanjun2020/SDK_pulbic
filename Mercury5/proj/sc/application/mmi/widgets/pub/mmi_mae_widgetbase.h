#ifndef __MMI_MAE_WIDGETBASE_H__
#define __MMI_MAE_WIDGETBASE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_container.h"
#ifdef __TOUCH_SCREEN_MMI__
#include "mmi_mae_touchsrv.h"
#endif //__TOUCH_SCREEN_MMI__
#include "mmi_mae_event.h"
#include "mmi_class.h"
#include "mmi_layout.h"
#include "mmi_mae_widgetbase_type.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/**
* Flags in WidgetBase_t
*/
enum
{
    WDG_BASE_FLAG_START = 0,
    WDG_BASE_FLAG_IS_FOCUSED = WDG_BASE_FLAG_START,   ///< To keep whether this widget is focused or not
    WDG_BASE_FLAG_CAN_BE_FOCUSED,                     ///< To decide whether this widget could be focused or not
    WDG_BASE_FLAG_SUPPORT_BORDER,                     ///< Support border(including padding and background) or not
    WDG_BASE_FLAG_BORDER_ENABLE,              ///< Enable or disable border
    WDG_BASE_FLAG_PADDING_ENABLE,             ///< Enable or disable padding
    WDG_BASE_FLAG_BG_ENABLE,                  ///< Enable or disalbe to draw background
    //WDG_BASE_FLAG_BG_TYPE,                    ///< Background type, 0:color, 1:Image
    WDG_BASE_FLAG_BG_POS,                     /*!< Background position,
                                              0:background draw inside padding,
                                              1:background cover whole widget */
    WDG_BASE_FLAG_BGIMG_TYPE,                 ///< background image type, WDG_BGIMG_TYPE_IMAGE:IImage, WDG_BGIMG_TYPE_BITMAP:IBitmap
    WDG_BASE_FLAG_LOOKCTRL_TYPE,              ///< look control type,
	WDG_BASE_FLAG_3D_ENABLE,
	WDG_BASE_FLAG_REFCOUNT_PROTECTED,		///< flag to indicate if the reference count is protected
/*deprecated
    WDG_BASE_FLAG_SELECTED,
    WDG_BASE_FLAG_CAN_BE_SELECTED,
    WDG_BASE_FLAG_CHILD_SELECTED,
*/
#ifdef __AP_USE_ML__
	WDG_BASE_FLAG_TRANSP_BG_ENABLE,	// enable draw full transparent background
#endif
    WDG_BASE_FLAG_IS_INVISIBLE,
	WDG_BASE_FLAG_REGISTER_PRE_DRAW,		///< indicate if someone register predraw cb for this widget
    WDG_BASE_FLAG_BG_INVALIDATE,
    WDG_BASE_FLAG_MULTI_TOUCH,              ///<support multi touch or not
    WDG_BASE_FLAG_END
};//Note: WDG_BASE_FLAG_END is 9 now.



enum
{
    BORDER_OPAQUE_NONE,          //does not opaque by border and content
    BORDER_OPAQUE_FULL,          //fullly opaque by border
    BORDER_OPAQUE_CONTENT_DEP    //depends on content
};

typedef u32 BorderOpaqueType;

#define GET_LEFT_BORDER(s)        ((s>>24)&0xFF)
#define GET_RIGHT_BORDER(s)       ((s>>16)&0xFF)
#define GET_TOP_BORDER(s)         ((s>>8)&0xFF)
#define GET_BOTTOM_BORDER(s)      (s&0xFF)

#define GET_LEFT_PADDING(_p)      GET_LEFT_BORDER(_p)
#define GET_RIGHT_PADDING(_p)     GET_RIGHT_BORDER(_p)
#define GET_TOP_PADDING(_p)       GET_TOP_BORDER(_p)
#define GET_BOTTOM_PADDING(_p)    GET_BOTTOM_BORDER(_p)


/**
* Flag Mask
*/
#define WDG_MASK_IS_FOCUSED         (1<<WDG_BASE_FLAG_IS_FOCUSED)
#define WDG_MASK_CAN_BE_FOCUSED     (1<<WDG_BASE_FLAG_CAN_BE_FOCUSED)
#define WDG_MASK_SUPPORT_BORDDR     (1<<WDG_BASE_FLAG_SUPPORT_BORDER)
#define WDG_MASK_BORDER_ENABLE      (1<<WDG_BASE_FLAG_BORDER_ENABLE)
#define WDG_MASK_PADDING_ENABLE     (1<<WDG_BASE_FLAG_PADDING_ENABLE)
#define WDG_MASK_BG_ENABLE          (1<<WDG_BASE_FLAG_BG_ENABLE)
//#define WDG_MASK_BG_TYPE            (1<<WDG_BASE_FLAG_BG_TYPE)
#define WDG_MASK_BGIMG_TYPE         (1<<WDG_BASE_FLAG_BGIMG_TYPE)
#define WDG_MASK_BG_POS             (1<<WDG_BASE_FLAG_BG_POS)
#define WDG_MASK_CTRL_TYPE          (1<<WDG_BASE_FLAG_LOOKCTRL_TYPE)
#define WDG_MASK_3D_ENABLE          (1<<WDG_BASE_FLAG_3D_ENABLE)
#define WDG_MASK_REFCOUNT_PROTECTED          (1<<WDG_BASE_FLAG_REFCOUNT_PROTECTED)
/*deprecated
#define WDG_MASK_SELECTED           (1<<WDG_BASE_FLAG_SELECTED)
#define WDG_MASK_CAN_BE_SELECTED    (1<<WDG_BASE_FLAG_CAN_BE_SELECTED)
#define WDG_MASK_CHILD_SELECTED     (1<<WDG_BASE_FLAG_CHILD_SELECTED)
*/
#ifdef __AP_USE_ML__
#define WDG_MASK_TRANSP_BG_ENABLE          (1<<WDG_BASE_FLAG_TRANSP_BG_ENABLE)
#endif
#define WDG_MASK_IS_INVISIBLE       (1<<WDG_BASE_FLAG_IS_INVISIBLE)
#define WDG_MASK_REGISTER_PRE_DRAW          (1<<WDG_BASE_FLAG_REGISTER_PRE_DRAW)
#define WDG_MASK_BG_INVALIDATE      (1<<WDG_BASE_FLAG_BG_INVALIDATE)
#define WDG_MASK_MULTI_TOUCH      (1<<WDG_BASE_FLAG_MULTI_TOUCH)
/**
* Background image types
*/
typedef enum
{
    WDG_BGIMG_TYPE_IMAGE = 0,
    WDG_BGIMG_TYPE_BITMAP
} WdgBackgroundImageType_t;

/**
* Macro to get flag value
*/
#define WDG_IS_FOCUSED(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_IS_FOCUSED)>>WDG_BASE_FLAG_IS_FOCUSED)
#define WDG_CAN_BE_FOCUSED(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_CAN_BE_FOCUSED)>>WDG_BASE_FLAG_CAN_BE_FOCUSED)
#define WDG_IS_SUPPORT_BORDDR(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_SUPPORT_BORDDR)>>WDG_BASE_FLAG_SUPPORT_BORDER)
#define WDG_IS_BORDER_ENABLE(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_BORDER_ENABLE)>>WDG_BASE_FLAG_BORDER_ENABLE)
#define WDG_IS_PADDING_ENABLE(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_PADDING_ENABLE)>>WDG_BASE_FLAG_PADDING_ENABLE)
#define WDG_IS_BG_ENABLE(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_BG_ENABLE)>>WDG_BASE_FLAG_BG_ENABLE)
/*
#define WDG_GET_BG_TYPE(_pWdgBase) \
    (((_pWdgBase)->Flags&WDG_MASK_BG_TYPE)>>WDG_BASE_FLAG_BG_TYPE)
*/
#define WDG_GET_BGIMG_TYPE(_pWdgBase) \
    (((_pWdgBase)->Flags&WDG_MASK_BGIMG_TYPE)>>WDG_BASE_FLAG_BGIMG_TYPE)
#define WDG_GET_BG_POS(_pWdgBase) \
    (((_pWdgBase)->Flags&WDG_MASK_BG_POS)>>WDG_BASE_FLAG_BG_POS)
#define WDG_GET_CTRL_TYPE(_pWdgBase) \
    (((_pWdgBase)->Flags&WDG_MASK_CTRL_TYPE)>>WDG_BASE_FLAG_LOOKCTRL_TYPE)
#define WDG_IS_3D_ENABLE(_pWdgBase) \
    (((_pWdgBase)->Flags&WDG_MASK_3D_ENABLE)>>WDG_BASE_FLAG_3D_ENABLE)
#define WDG_IS_REFCOUNT_PROTECTED(_pWdgBase) \
	(((_pWdgBase)->Flags&WDG_MASK_REFCOUNT_PROTECTED)>>WDG_BASE_FLAG_REFCOUNT_PROTECTED)
/*deprecated
#define WDG_GET_SELECTED(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_SELECTED)>>WDG_BASE_FLAG_SELECTED)
#define WDG_CAN_BE_SELECTED(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_CAN_BE_SELECTED)>>WDG_BASE_FLAG_CAN_BE_SELECTED)
#define WDG_GET_CHILD_SELECTED(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_CHILD_SELECTED)>>WDG_BASE_FLAG_CHILD_SELECTED)
*/
#ifdef __AP_USE_ML__
#define WDG_IS_TRANSP_BG_ENABLE(_pWdgBase) \
	(boolean)(((_pWdgBase)->Flags&WDG_MASK_TRANSP_BG_ENABLE)>>WDG_BASE_FLAG_TRANSP_BG_ENABLE)
#endif
#define WDG_IS_INVISIBLE(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_IS_INVISIBLE)>>WDG_BASE_FLAG_IS_INVISIBLE)
#define WDG_IS_REGISTER_PRE_DRAW(_pWdgBase) \
	(boolean)(((_pWdgBase)->Flags&WDG_MASK_REGISTER_PRE_DRAW)>>WDG_BASE_FLAG_REGISTER_PRE_DRAW)
#define WDG_BG_INVALIDATE(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_BG_INVALIDATE)>>WDG_BASE_FLAG_BG_INVALIDATE)
#define WDG_IS_MULTI_TOUCH(_pWdgBase) \
    (boolean)(((_pWdgBase)->Flags&WDG_MASK_MULTI_TOUCH)>>WDG_BASE_FLAG_MULTI_TOUCH)
/**
* Macro to Set flag value
*/
#define WDG_SET_FOCUSED(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_IS_FOCUSED))|(((u32)_b)<<WDG_BASE_FLAG_IS_FOCUSED)
#define WDG_SET_CAN_BE_FOCUSED(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_CAN_BE_FOCUSED))|(((u32)_b)<<WDG_BASE_FLAG_CAN_BE_FOCUSED)
/*
#define WDG_SET_SUPPORT_BORDER(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_SUPPORT_BORDDR))|(((u32)_b)<<WDG_BASE_FLAG_SUPPORT_BORDER)
*/
#define WDG_SET_BORDER_ENABLE(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_BORDER_ENABLE))|(((u32)_b)<<WDG_BASE_FLAG_BORDER_ENABLE)
#define WDG_SET_PADDING_ENABLE(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_PADDING_ENABLE))|(((u32)_b)<<WDG_BASE_FLAG_PADDING_ENABLE)
#define WDG_SET_BG_ENABLE(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_BG_ENABLE))|(((u32)_b)<<WDG_BASE_FLAG_BG_ENABLE)
/*
#define WDG_SET_BG_TYPE(_pWdgBase, _type) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_BG_TYPE))|(((u32)_type)<<WDG_BASE_FLAG_BG_TYPE)
*/
#define WDG_SET_BGIMG_TYPE(_pWdgBase, _type) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_BGIMG_TYPE))|(((u32)_type)<<WDG_BASE_FLAG_BGIMG_TYPE)
#define WDG_SET_BG_POS(_pWdgBase, _pos) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_BG_POS))|(((u32)_pos)<<WDG_BASE_FLAG_BG_POS)
#define WDG_SET_CTRL_TYPE(_pWdgBase, __type) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_CTRL_TYPE))|(((u32)__type)<<WDG_BASE_FLAG_LOOKCTRL_TYPE)
#define WDG_SET_3D_ENABLE(_pWdgBase, __type) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_3D_ENABLE))|(((u32)__type)<<WDG_BASE_FLAG_3D_ENABLE)

/*
 * This macro is used to set/cancel reference count protection,
 * If the flag is TRUE, the widget's reference count cannot be less than the __ProtectedRefCnt
 * Here we usually set __ProtectedRefCnt as 2 and 1,
 * 2 is used in the case that widget is owned by a container based widget and be add into the container, e.g., statusbar widget
 * 1 is used in the case that widget is owned by another widget and be set as child of a decorator, e.g., tab widget's item widget
*/
#define WDG_SET_REFCOUNT_PROTECTED(_pWdgBase, __type, __ProtectedRefCnt) \
	do \
	{ \
		(_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_REFCOUNT_PROTECTED))|(((u32)__type)<<WDG_BASE_FLAG_REFCOUNT_PROTECTED); \
		(_pWdgBase)->nProtectedRefCnt = (__ProtectedRefCnt); \
	}while(0)
/*deprecated
#define WDG_SET_SELECTED(_pWdgBase,_b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_SELECTED)&(~WDG_MASK_CHILD_SELECTED))|(((u32)_b)<<WDG_BASE_FLAG_SELECTED)|(((u32)_b)<<WDG_BASE_FLAG_CHILD_SELECTED)
#define WDG_SET_CAN_BE_SELECTED(_pWdgBase,_b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_CAN_BE_SELECTED))|(((u32)_b)<<WDG_BASE_FLAG_CAN_BE_SELECTED)
#define WDG_SET_CHILD_SELECTED(_pWdgBase,_b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_CHILD_SELECTED))|(((u32)_b)<<WDG_BASE_FLAG_CHILD_SELECTED)
*/
#ifdef __AP_USE_ML__
#define WDG_SET_TRANSP_BG_ENABLE(_pWdgBase, _b) \
	(_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_TRANSP_BG_ENABLE))|(((u32)_b)<<WDG_BASE_FLAG_TRANSP_BG_ENABLE)
#endif
#define WDG_SET_INVISIBLE(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_IS_INVISIBLE))|(((u32)_b)<<WDG_BASE_FLAG_IS_INVISIBLE)
#define WDG_SET_REGISTER_PRE_DRAW(_pWdgBase, _b) \
	(_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_REGISTER_PRE_DRAW))|(((u32)_b)<<WDG_BASE_FLAG_REGISTER_PRE_DRAW)
#define WDG_SET_BG_INVALIDATE(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_BG_INVALIDATE))|(((u32)_b)<<WDG_BASE_FLAG_BG_INVALIDATE)
#define WDG_SET_MULTI_TOUCH(_pWdgBase, _b) \
    (_pWdgBase)->Flags = ((_pWdgBase)->Flags&(~WDG_MASK_MULTI_TOUCH))|(((u32)_b)<<WDG_BASE_FLAG_MULTI_TOUCH)
/**
* Macro to get the size on bits (not byte)
*/
#define WDG_BASE_FLAG_SIZE(_pWdgBase) \
    (sizeof((_pWdgBase)->Flags)*8)

/*=============================================================*/
// functions
/*=============================================================*/
/*------------------------------------------------------------------------------------------
* Widget Init function
------------------------------------------------------------------------------------------*/
MAE_Ret WdgInit(MAE_ClsId nClsId, void **ppObj, u32 nSize, WHANDLER_HDL_FUNC_PTR pfnHandler);

/*------------------------------------------------------------------------------------------
* constructor and destructor for widget base
------------------------------------------------------------------------------------------*/

// for a new style widget
MAE_Ret WdgBaseConstructor(WidgetBaseEx_t *pWidget);
void WdgBaseDestructor(WidgetBaseEx_t *pWidget);
// for New Style Widget, draw border and BG, and calculate padding
void WidgetBaseEx_DrawBorderAndBG(IWidget *pIWidget, Wdg_Draw_Req_t *pReq);

// for a old style widget
MAE_Ret WidgetBaseExStrucCtor(WidgetBaseEx_t *pThis, const FUNCTBL(IWidget) *FtblPtr, WHANDLER_HDL_FUNC_PTR pfnHandler, WDG_DRAW_FUNC_PTR pfnDraw);

/*------------------------------------------------------------------------------------------
* For IBase Interface
------------------------------------------------------------------------------------------*/
u32 WidgetBase_AddRef(IWidget *pIWidget);
u32 WidgetBase_Release(IWidget *pIWidget);
MAE_Ret WidgetBase_QueryInterface(IWidget *pIWidget, MAE_IId iId, void **ppObj, IBase *pOwner);


/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
boolean WidgetBase_HandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);
/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
void WidgetBase_SetHandler(IWidget *pIWidget, WidgetHandler_t *pHdlData);
void WidgetBase_GetSize(IWidget *pIWidget, WidgetSize_t *pSize);
void WidgetBase_SetSize(IWidget *pIWidget, WidgetSize_t *pSize);
void WidgetBase_GetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);
void WidgetBase_GetParent(IWidget *pIWidget, IContainer **ppParentContainer, IBase *pOwner);
void WidgetBase_SetParent(IWidget *pIWidget, IContainer *pParentContainer);
boolean WidgetBase_IntersectOpaque_T(IWidget *pIWidget, const Rect_t *pInRect, Rect_t *pOutRect);
boolean WidgetBase_IntersectOpaque_NotTransp(IWidget *pIWidget, const Rect_t *pInRect, Rect_t *pOutRect);
boolean WidgetBase_IntersectOpaque_CheckBGColor(IWidget *pIWidget, const Rect_t *pInRect, Rect_t *pOutRect);
void WidgetBase_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);
MAE_Ret WidgetBase_SetModel(IWidget *pIWidget, IModel *pIModel, IBase *pOwner);
MAE_Ret WidgetBase_GetModel(IWidget *pIWidget, MAE_IId iId, IModel **ppObj, IBase *pOwner);
//MAE_Ret WidgetBase_AddEvtListener(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData);
//MAE_Ret WidgetBase_CancelEvtListener(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData);
MAE_Ret WidgetBase_AddEvtListener(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData1, void *pUsrData2);
MAE_Ret WidgetBase_CancelEvtListener(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData1, void *pUsrData2);

//Check parent's link
void _WidgetBase_CheckParentLink(IWidget* pWidget);

/*deprecated
void WidgetBase_DrawSelected(WidgetBase_t *pWdgBase, IDisplay *pDisp, s32 x, s32 y);
*/

/**
** Draw function for widget which support border(using WidgetBaseEx_t structure).
**/
void WidgetBaseEx_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

//Get widget's view model function for widget base.
//pIWidget:
//ppObj:
//pOwner:
//return:
MAE_Ret WidgetBase_GetViewModel(IWidget *pIWidget, IModel **ppObj, IBase *pOwner);

/*------------------------------------------------------------------------------------------
* For Widget Border
------------------------------------------------------------------------------------------*/

/**
** @brief  coordinate conversion:
**         given pCntRect in CONTENT's coordinate, output the same rect in WIDGET's coordinate
** @note   just convert x and y position, not including width and height.
*/
__SLDPM_FREE__ void WdgBorder_CoordCvrtCntRectToWdgRect(WidgetBaseEx_t *pWdgBase, Rect_t *pCntRect, Rect_t *pWdgRect);

/**
** @brief  coordinate conversion:
**         given pWdgRect in WIDGET's coordinate, output the same rect in CONTENT's coordinate
** @note   just convert x and y position, not including width and height.
*/
__SLDPM_FREE__ void WdgBorder_CoordCvrtWdgRectToCntRect(WidgetBaseEx_t *pWdgBase, Rect_t *pWdgRect, Rect_t *pCntRect);

/**
** @brief   calculate content rect according to the given WIDGET'S rectangle
**/
__SLDPM_FREE__ void WdgBorder_CalcContentRect(WidgetBaseEx_t *pWdgBase, Rect_t *pWdgRect, Rect_t *pCntRect);

/**
** @brief   calculate the inner rectangle inside border according to the given WIDGET'S rectangle
**/
void WdgBorder_CalcBorderInnerRect(WidgetBaseEx_t *pWdgBase, Rect_t *pWdgRect, Rect_t *pInnerRect);

/**
** @brief   Give input rect(in widget's coordinate) and
**          output the intersect rect of input rect and content rect in CONTENT's coordinate
**/
__SLDPM_FREE__ void WdgBorder_ContentRectIntersect(WidgetBaseEx_t *pWdgBase, const Rect_t *pInRect, Rect_t *pOutRect);

/* Draw background and border
*  The priority: border > background image > background color
*  So we draw background color first, and background image and border last.
*  x, y: abs coordinate of the widget
*/
__SLDPM_FREE__ void WdgBorder_DrawBorder(WidgetBaseEx_t *pWdgBase, IDisplay *pDisp, s32 x, s32 y, boolean b3D);

/**
** Set border size to array
**/
__SLDPM_FREE__ void WdgBorder_SetBorderSize(WidgetBaseEx_t *pWdgBase, u8 top, u8 bot, u8 left, u8 right);

/**
** Get border size from array
**/
void WdgBorder_GetBorderSize(WidgetBaseEx_t *pWdgBase, u8 *pTop, u8 *pBot, u8 *pLeft, u8 *pRight);

/**
** Set padding size to array
** the function will also re-calculate content size which keep in WidgetBaseEx_t
**/
__SLDPM_FREE__ void WdgBorder_SetPaddingSize(WidgetBaseEx_t *pWdgBase, u8 top, u8 bot, u8 left, u8 right);

/**
** Get padding size from array
**/
void WdgBorder_GetPaddingSize(WidgetBaseEx_t *pWdgBase, u8 *pTop, u8 *pBot, u8 *pLeft, u8 *pRight);

/*
pInRect:   input rectangle
pOutRect:  intersction rectangle of pInRect and widget Rect_t

*/
/*
BorderOpaqueType WdgBorder_CalcOpaque(WidgetBaseEx_t *pWdgBase, const Rect_t *pInRect, Rect_t *pOutRect);
*/
__SLDPM_FREE__ boolean WdgBorder_CalcOpaque(WidgetBaseEx_t *pWdgBase, const Rect_t *pInRect, Rect_t *pOutRect);

/**
** @brief   This function will calculate content size according the giving widget size.
** @param[in]   pWdgBase   A pointer of WidgetBaseEx_t structure.
** @param[in]   pWdgSize   Giving widget size.
** @param[out]  pCntSize   A pointer of WidgetSize_t to return content size.
**/
__INLINE void WdgBorder_GetContentSize(WidgetBaseEx_t *pWdgBase, WidgetSize_t *pWdgSize, WidgetSize_t *pCntSize)
{
    if(WDG_IS_PADDING_ENABLE(pWdgBase))
    {
        pCntSize->width = MAX(0, (pWdgSize->width - pWdgBase->Padding[PADDING_LEFT] - pWdgBase->Padding[PADDING_RIGHT]));
        pCntSize->height = MAX(0, (pWdgSize->height - pWdgBase->Padding[PADDING_TOP] - pWdgBase->Padding[PADDING_BOTTOM]));
    }
    else
    {
        *pCntSize = *pWdgSize;
    }
}

/**
** @brief   This function will calculate widget size according the giving content size.
** @param[in]   pWdgBase   A pointer of WidgetBaseEx_t structure.
** @param[in]   pCntSize   Giving content size.
** @param[out]  pWdgSize   A pointer of WidgetSize_t to return widget size.
**/
__INLINE void WdgBorder_GetWidgetSize(WidgetBaseEx_t *pWdgBase, WidgetSize_t *pCntSize, WidgetSize_t *pWdgSize)
{
    if(WDG_IS_PADDING_ENABLE(pWdgBase))
    {
        pWdgSize->width = pCntSize->width + pWdgBase->Padding[PADDING_LEFT] + pWdgBase->Padding[PADDING_RIGHT];
        pWdgSize->height = pCntSize->height + pWdgBase->Padding[PADDING_TOP] + pWdgBase->Padding[PADDING_BOTTOM];
    }
    else
    {
        *pWdgSize = *pCntSize;
    }
}

/** WdgBorder_GetContentXY
** @brief   This function will calculate the x and y coordinate of the content rectangle.
** @par Prototype:
**          void WdgBorder_GetContentXY(WidgetBaseEx_t *pWdgBase, s32 x, s32 y, s32 *pCntX, s32 *pCntY)
**
** @param[in]   pWdgBase   A pointer of WidgetBaseEx_t structure.
** @param[in]   x          The x coordinate of this widget.
** @param[in]   y          The y coordinate of this widget.
** @param[out]  pCntX      A pointer of s32 to return the x coordinate of content rectangle.
** @param[out]  pCntY      A pointer of s32 to return the y coordinate of content rectangle.
**
** @retval   None.
**/
__INLINE void WdgBorder_GetContentXY(WidgetBaseEx_t *pWdgBase, s32 x, s32 y, s32 *pCntX, s32 *pCntY)
{
    *pCntX = x + pWdgBase->Padding[PADDING_LEFT];
    *pCntY = y + pWdgBase->Padding[PADDING_TOP];
}

/**
** Set border color.
**/
__INLINE void WdgBorder_SetBorderColor(WidgetBaseEx_t *pWdgBase, RGBColor_t color)
{
    pWdgBase->BorderColor = color;
}

/**
** Set background color.
**/
__INLINE void WdgBorder_SetBGColor(WidgetBaseEx_t *pWdgBase, RGBColor_t color)
{
    pWdgBase->BGColor = color;
}

/**
** Set background image.
**/
__INLINE void WdgBorder_SetBGImage(WidgetBaseEx_t *pWdgBase, IBase *pBGObj)
{
    RELEASEIF(pWdgBase->pBGObj, pWdgBase);
    pWdgBase->pBGObj = pBGObj;
    ADDREFIF(pBGObj, (IBase*)pWdgBase);
}

/**
** @brief   This function will calculate the preferred size for widget supporting border
** @param[in]   pWdgBase       A pointer of WidgetBaseEx_t structure.
** @param[in]   pCntPrefSize   A pointer of WidgetSize_t for keeping content preferred size.
** @param[out]  pWdgPrefSize   A pointer of WidgetSize_t to return widget preferred size.
**/
__INLINE void WdgBorder_CalcPreferredSize(WidgetBaseEx_t *pWdgBase, WidgetSize_t *pCntPrefSize, WidgetSize_t *pWdgPrefSize)
{
    if(WDG_IS_PADDING_ENABLE(pWdgBase))
    {
        pWdgPrefSize->width = pCntPrefSize->width + pWdgBase->Padding[PADDING_LEFT] + pWdgBase->Padding[PADDING_RIGHT];
        pWdgPrefSize->height= pCntPrefSize->height+ pWdgBase->Padding[PADDING_TOP] + pWdgBase->Padding[PADDING_BOTTOM];
    }
    else
    {
        *pWdgPrefSize = *pCntPrefSize;
    }
}

/*------------------------------------------------------------------------------------------
* For other function
------------------------------------------------------------------------------------------*/
//default handle event function for widget-base
boolean WidgetBase_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);
//
void WidgetBase_Invalidate(IWidget *pIWidget, InvFlag_t flag);
void WidgetBase_InvalidateContentSize(IWidget *pIWidget, InvFlag_t flag);
void WidgetBase_InvalidateRect(IWidget *pIWidget, Rect_t *WRectPtr, InvFlag_t flag);

void WidgetBase_NoticeParentSetFocus(WidgetBase_t *pThis, boolean bFocus);

boolean WidgetBase_SetProperty(WidgetBase_t *pThis, u32 P1, u32 P2);

boolean WidgetBase_GetProperty(WidgetBase_t *pThis, u32 P1, u32 P2);

void WidgetBase_SendNotify(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, u32 dwParam);
boolean WidgetBase_CallRegisterCB(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, u32 dwParam);

#ifdef __TOUCH_SCREEN_MMI__
MAERet_t WidgetBase_RegisterToTouchSrv(WidgetBase_t *pThis, ITouchSrv *pITouchSrv);
MAERet_t WidgetBase_DeRegisterToTouchSrv(WidgetBase_t *pThis, ITouchSrv *pITouchSrv);
#ifdef __MULTI_TOUCH__
MAERet_t WidgetBase_MultiRegisterToTouchSrv(WidgetBase_t *pThis, ITouchSrv *pITouchSrv, u32 nUniqueID);
MAERet_t WidgetBase_MultiDeRegisterToTouchSrv(WidgetBase_t *pThis, ITouchSrv *pITouchSrv, u32 nUniqueID);
boolean WidgetBase_QueryIsHook(WidgetBase_t *pThis, ITouchSrv *pITouchSrv, s32 x, s32 y);
u32 WidgetBase_QueryPointID(WidgetBase_t *pThis, ITouchSrv *pITouchSrv, s32 x, s32 y);
MAERet_t WidgetBase_UpdateHookWidgtPosistion(WidgetBase_t *pThis, ITouchSrv *pITouchSrv);
#endif
#endif // __TOUCH_SCREEN_MMI__

u32 WidgetBase_GetRef(IWidget *pIWidget);

#if defined(__G3D_MMI__)
u32 WidgetBase_CreateNode(WidgetBase_t *pThis);
#endif



#endif // __MMI_MAE_WIDGETBASE_H__
