/**
* @file    mmi_mae_widget.h
* @version $Id: mmi_mae_widget.h 38890 2009-08-29 16:22:38Z zinc.chen $
*
* @brief   This file defines IWidget interface.
*
* <Interface Description>
*     IWidget is the basic interface designed for all UI components, such as widgets, containers 
*     and decorators. The IWidget interface is derived from IHandler interface and provides 
*     many common methods for displaying logic control and  data control. The methods are provided 
*     to draw content, manage widget's size, set/get widget's model, set/get widget's parent widget, 
*     and hook event handler. Also, IWidget provides a mechanism to notify while the view of widget 
*     object changed. All widgets should implement IWidget interface.
*
*     Although IWidget is derived from IHandler, it is not directly handled by Shell as IApplet or
*     IService and is not considered as an individual execution unit. The HandleEvent method is
*     controlled by View, which passes the events of an applet to the specific widget's handler.
*
* <Interface ID>
*     IID_WIDGET
*/
#ifndef __MMI_MAE_WIDGET_H__
#define __MMI_MAE_WIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_handler.h"
#include "mmi_mae_widgethandler.h"
#include "mmi_mae_dispcanvas.h"
#include "mmi_mae_model.h"
#include "mmi_mae_widget_events.h"
#include "mmi_mae_widget_properties.h"
#include "mmi_mae_image.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/**
* The data type of Widget property ID.
*/
typedef u32 WdgPropId_t;
/**
* The data type of Widget flag.
*/
typedef u32 WdgFlag_t;
/**
* The data type of Widget size.
*/
typedef struct WidgetSize_TAG WidgetSize_t;

///< incomplete types to avoid mutual include headers
typedef struct IContainer_tag IContainer_it;

typedef struct IWidget_tag IWIDGET;   ///< the same with IWidget
typedef void (*PFN_WIDGET_EVT_LISTENER)(void *pUsrData1, void *pUsrData2, WidgetEvtCode_t nEvtCode, u32 dwParam, IWIDGET *pWdg);

typedef struct
{
    const Rect_t *pInRect;      ///< Pointer of Rect_t structure which keeps constant value as input rectangle.
    Rect_t       *pOutRect;     ///< Pointer of Rect_t as result rectangle.
    boolean      Rst;           ///< TRUE if there is opaque intersection. FALSE if No opaque intersection
}Wdg_IntersectOpaque_Check_t;

typedef struct
{
    IDispCanvas *pIDispCanvas;  ///< A display canvas which this widget can draw on.
    s32 x;                      ///< The x position of coordinate on the canvas.
    s32 y;                      ///< The y position of coordinate on the canvas.
}Wdg_Draw_Req_t;

typedef struct
{
	IModel *pIModel;			///< A model pointer to be set
	IBase *pOwner;			///< The owner of the data
	MAE_Ret ret;				///< The return code
}Wdg_SetModel_Req_t;

typedef struct
{
	MAE_IId iId;				///< The model interface id
	IModel **ppIModel;			///< A model pointer to be get
	IBase *pOwner;			///< The owner of the data
	MAE_Ret ret;				///< The return code
}Wdg_GetModel_Req_t;

typedef struct
{
	IModel **ppIModel;			///< A pointer of a model pointer that will be returned the widget's view model.
	IBase *pOwner;			///< A pointer to a IBase object which will keep the returned view model.
	MAE_Ret ret;				///< The return code
}Wdg_GetViewModel_Req_t;

typedef struct
{
    WidgetEvtCode_t nEvtCode;                   ///< Event code to listen.
    PFN_WIDGET_EVT_LISTENER pfnEvtListener;     ///< Callback function pointer to the event
    void *pUsrData1;                            ///< User data pointer. This pointer will be passed into callback function 
    void *pUsrData2;                            ///< User data pointer. This pointer will be passed into callback function 
    MAE_Ret ret;   
}Wdg_SetNotifyCB_Req_t;

typedef struct
{
    void *pDataPtr;			///< A data pointer to be set
    void *pfFree;				///< The data free function pointer
    IBase *pOwner;			///< The owner of the data
}Wdg_SetData_Req_t;

/*=============================================================*/
// interface
/*=============================================================*/
///
/// IWidget interface
///
/**
* INHERIT_IWidget
* @brief   INHERIT_IWidget is IWidget interface inheritance definition. 
*          Defines the methods of IWidget interface.
*/
#define INHERIT_IWidget(IName) \
	INHERIT_IHandler(IName); \
	void (*SetHandler) (IName *, WidgetHandler_t *)

DEFINE_INTERFACE(IWidget);


/**
* @brief   structure for EVT_WIDGET_GET_COMPONENT_WDG event, as parameter 2.
*/
typedef struct
{
	IWidget **ppWidget;   ///< A pointer of IWidget pointer to return the component widget pointer.
	IBase *pOwner;        ///< A IBase pointer to keep the returned compoinet widget pointer.
} GetCompWgt_t;

/**
* @brief   The width and height of widget.
*/
struct WidgetSize_TAG {
	u16 width;      ///< the width of widget.
	u16 height;     ///< the height of widget.
};


/*=============================================================*/
// Interface methods
/*=============================================================*/

/** IWIDGET_QueryInterface
* @brief	This function queries another interface from IWidget object. 
*          It will return an interface object which you want to query if successful.
*
* @param[in]   IWidgetPtr(IWidget*)    A pointer of IWidget interface object.
* @param[in]   iid(MAE_IId)            An interface id to be queried.
* @param[out]  ppObj(void**)           A pointer of void pointer to retrieve an interface object which you want to query.
* @param[in]   pOwner(IBase*)          Shall be an IBase interface object to keep the return object.
*
* @retval	MAE_RET_SUCCESS         Success.
* @retval	MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IWIDGET_QueryInterface(IWidgetPtr,iid,ppObj,pOwner) \
	GET_FUNCTBL((IWidgetPtr),IWidget)->QueryInterface(IWidgetPtr,iid,ppObj,pOwner)
#else
__INLINE MAERet_t IWIDGET_QueryInterface (IWidget *IWidgetPtr, MAEIId_t iid , void** ppObj, IBase* pOwner)
{
	return GET_FUNCTBL((IWidgetPtr),IWidget)->QueryInterface(IWidgetPtr,iid,ppObj,pOwner);
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/** IWIDGET_HandleEvent
* @brief	This function handles events which passed to this IWidget object.
*
* @param[in]	IWidgetPtr(IWidget*)	A pointer of IWidget interface object.
* @param[in]	eid(MAE_EventId)		Event Id sent to the IHandler object.
* @param[in]	p1(u32)					Parameter 1 of 32-bits specific data.
* @param[in]	p2(u32)					Parameter 2 of 32-bits specific data.
*
* @retval	TRUE		The object handled this event.
* @retval	FALSE		The object did NOT handle this event.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IWIDGET_HandleEvent(IWidgetPtr,eid,p1,p2) \
	GET_FUNCTBL((IWidgetPtr),IWidget)->HandleEvent(IWidgetPtr,eid,p1,p2)
#else
__INLINE boolean IWIDGET_HandleEvent (IWidget *IWidgetPtr, MAEEvent_t eid, u32 p1, u32 p2)
{
	return GET_FUNCTBL((IWidgetPtr),IWidget)->HandleEvent(IWidgetPtr,eid,p1,p2);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** IWIDGET_SetHandler
* @brief	This function is used for an application which want to hook this IWidget object's handle event function.
*
* @param[in]        IWidgetPtr(IWidget*)     A pointer of IWidget interface object.
* @param[in][out]   pWHD(WidgetHandler_t*)   A pointer of WidgetHandler_t sturcture which want to hook events.
*
* @retval	None.
*
* @note	pWHD will retrieve the old handler after calling IWIDGET_SetHandler(). If application wants
*			to pass event to old handler, call WHANDLER_CALL() with old handler sturcture.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define IWIDGET_SetHandler(IWidgetPtr,pWHD) \
	GET_FUNCTBL((IWidgetPtr),IWidget)->SetHandler(IWidgetPtr,pWHD)
#else
__INLINE void IWIDGET_SetHandler (IWidget *IWidgetPtr, WidgetHandler_t *pWHD)
{
	GET_FUNCTBL((IWidgetPtr),IWidget)->SetHandler(IWidgetPtr,pWHD);
}

#endif /* __MAE_VENEERED_INTERFACE__ */

/** MAKE_BORDER_SIZE
* @brief   A macro to make border size(including top/bottom/left/right).
*
* @note    Please refer to IWIDGET_SetBorder().
*/
#define MAKE_BORDER_SIZE(_l,_r,_t,_b) \
	((((u32)((_l)&0xFF))<<24)|(((u32)((_r)&0xFF))<<16)|(((u32)((_t)&0xFF))<<8)|((u32)((_b)&0xFF)))

/** MAKE_PADDING_SIZE
* @brief   A macro to make padding size(including top/bottom/left/right).
*
* @note    Please refer to IWIDGET_SetPadding().
*/
#define MAKE_PADDING_SIZE(_l,_r,_t,_b) \
	MAKE_BORDER_SIZE(_l,_r,_t,_b)
//	((((u32)(l&0xFF))<<24)|(((u32)(r&0xFF))<<16)|(((u32)(t&0xFF))<<8)|((u32)(b&0xFF)))

#endif	//__MAE_WIDGET_H__
/*=============================================================*/
// end of file
