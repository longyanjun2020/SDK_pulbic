#ifndef __MMI_WDG_COMMON_INTERFACE_H__
#define __MMI_WDG_COMMON_INTERFACE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_container.h"
#include "mmi_mae_textmodel.h"
#include "mmi_mae_interfacemodel.h"
#include "mmi_mae_interface_def.h"
#include "mmi_wdg_abscontainer.h"
#include "mmi_mae_window.h"
#include "mmi_wdg_scrollbar.h"
#include "mmi_mae_widgetbase_type.h" //WdgCommonDestroy needs the definition of WidgetBaseEx_t
#include "mmi_mae_containerbase_type.h" 

///MAE Pub Header
#include "mmi_mae_font_base.h"
#include "mmi_mae_font_types.h"
/*=============================================================*/
// type and define
/*=============================================================*/

typedef void (*PfnDataFree) (void *pData, IBase *pOwner);
typedef void (*PfnWdgPreDraw) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, Wdg_Draw_Req_t *pDrawReq, IWidget *pWidget);

/** WdgPaddingData_t
*
* @brief      Padding Struct for Set and Get Widget Padding Information.
* @brief      Used via WDG_Xxx_SetPaddingData and WDG_Xxx_GetPaddingData.
*
*/
typedef struct
{
    u8  nPaddingLeft;
    u8  nPaddingRight;
    u8  nPaddingTop;
    u8  nPaddingBottom;
}WdgPaddingData_t;

/** WdgBorderData_t
*
* @brief      Border Struct for Set and Get Widget Border Information.
* @brief      Often used via WDG_Xxx_SetBorderData and WDG_Xxx_GetBorderData.
* @brief      tBorderColor ==> Border Background Color can be set by MAKE_RGB or MAKE_RGBA.
*
*/
typedef struct
{
    u8  nBorderLeft;
    u8  nBorderRight;
    u8  nBorderTop;
    u8  nBorderBottom;
    RGBColor_t tBorderColor;
}WdgBorderData_t;

/*=============================================================*/
// functions
/*=============================================================*/

/** WdgCommonCreate
* @brief        This function is used for create a Widget object
*
* @param[in]    nClsId            Class id of the Widget
*
* @retval       The created widget
*
*/
IWidget* WdgCommonCreate
(
    MAEClsId_t nClsId
);

/** WdgCommonDestroy
* @brief        This function is used for destroy a Widget object
*
* @param[in]    pWDGObject            The pointer of IWidget object
*
* @retval       None.
*
*/
#define WdgCommonDestroy(pWDGObject) \
	do{\
		if ((pWDGObject))\
		{\
            IBase *pWdgOwner = ((WidgetBaseEx_t *)(pWDGObject))->pOwner;\
            RELEASEIF((pWDGObject),pWdgOwner);\
		}\
	}while(0)

/** WdgCommonHandleEvent
* @brief        This function handles events which passed to this Widget
*
* @param[in]    pWDGObject    The pointer of Widget
* @param[in]    evt           Event Id.
* @param[in]    Param1        Parameter 1 of 32-bits specific data
* @param[in]    Param2        Parameter 2 of 32-bits specific data
*
* @retval       TRUE          The object handled this event.
* @retval       FALSE         The object did NOT handle this event.
*
*/
boolean WdgCommonHandleEvent
(
    IWidget             *pWDGObject,
    MAEEvent_t          evt,
    u32                 Param1,
    u32                 Param2
);

/** WdgCommonCheckType
* @brief   This function is used for check if the widget is belong to the type
*
* @param[in]   pIWidget(IWidget*)         A pointer of IWidget interface object.
* @param[in]   nClsID (MAEClsId_t)		  The type to be ckecked.
*
* @retval	TRUE		The widget is belong to the type.
* @retval	FALSE	The widget is not belong to the type
*/
boolean WdgCommonCheckType(IWidget *pIWidget, MAEClsId_t nClsID);

/** WdgCommonQueryInterface
* @brief	This function queries another interface from IWidget object.
*          It will return an interface object which you want to query if successful.
*
* @param[in]   pIWidget(IWidget*)    A pointer of IWidget interface object.
* @param[in]   iid(MAE_IId)            An interface id to be queried.
* @param[out]  ppObj(void**)           A pointer of void pointer to retrieve an interface object which you want to query.
* @param[in]   pOwner(IBase*)          Shall be an IBase interface object to keep the return object.
*
* @retval	MAE_RET_SUCCESS         Success.
* @retval	MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
*/
MAE_Ret WdgCommonQueryInterface
(
	IWidget *pIWidget,
	MAE_IId iid ,
	void** ppObj,
	IBase* pOwner
);

/** WdgCommonGetSize
* @brief        Get size of this Widget
*
* @param[in]    pWDGObject           The pointer of Widget
* @param[out]   pSize                A pointer of WidgetSize_t structure
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*
*/
MAE_Ret WdgCommonGetSize
(
    IWidget             *pWDGObject,
    WidgetSize_t        *pSize
);

/** WdgCommonSetSize
* @brief        Set size of this Widget
*
* @param[in]    pWDGObject           The pointer of Widget
* @param[in]    pSize                A pointer of WidgetSize_t structure
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*
*/
MAE_Ret WdgCommonSetSize
(
    IWidget             *pWDGObject,
    WidgetSize_t        *pSize
);

/** WdgCommonGetPreferredSize
* @brief        Get preferred size of this Widget; "preferred size" means the suitable size of the widget in different situation.
*
* @param[in]     pWDGObject           The pointer of Widget
* @param[out]    pSize                A pointer of WidgetSize_t structure
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*
*/
MAE_Ret WdgCommonGetPreferredSize
(
    IWidget             *pWDGObject,
    WidgetSize_t        *pSize
);

/** WdgCommonSetParent
* @brief   A function to set widget's property.
*
* @param[in]   IWidgetPtr    The pointer of IWidget interface object
* @param[in]   pParentContainer     Parent container
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*/
MAE_Ret WdgCommonSetParent(IWidget *IWidgetPtr, IContainer *pParentContainer);

/** WdgCommonGetParent
* @brief        Get this Widget's parent container
*
* @param[in]    pWDGObject          The pointer of Widget
* @param[out]   ppParentContainer   A pointer of IContainer pointer
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*
*/
MAE_Ret WdgCommonGetParent
(
    IWidget               *pWDGObject,
    IContainer            **ppParentContainer
);

/** WdgCommonSetViewable
* @brief        Move a widget's position inside/outside of its parent.
*
* @param[in]    IWidgetPtr      The pointer of Widget
* @param[in]    bViewable       TRUE: if the widget is outside its parent, move to the mirrored position inside its parent.
*                               FALSE: if the widget is inside its parent, move to the mirrored position outside its parent.
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*
*/
MAE_Ret WdgCommonSetViewable
(
    IWidget             *IWidgetPtr,
    boolean             bViewable
);

/** WdgCommonIntersectOpaque
* @brief   This function will calculate the opaque intersection of this widget and input rectangle.
*
* @param[in]   pIWidget(IWidget*)         A pointer of IWidget interface object.
* @param[in]   pInRect(const Rect_t*)     A pointer of Rect_t structure which keeps constant value as input rectangle.
* @param[out]  pOutRect(Rect_t*)          A pointer of Rect_t as result rectangle.
*
* @retval	TRUE		There is opaque intersection.
* @retval	FALSE		No opaque intersection.
*/
boolean WdgCommonIntersectOpaque(IWidget *pIWidget, const Rect_t *pInRect, Rect_t *pOutRect);

/** WdgCommonDraw
* @brief   To draw this container to the specific canvas.
*
* @param[in]   IWidgetPtr(IWidget*)    A pointer of IWidget interface object.
* @param[in]   iDC(IDispCanvas*)       A display canvas which this widget can draw on.
* @param[in]   x(s32)                  The x position of coordinate on the canvas.
* @param[in]   y(s32)                  The y position of coordinate on the canvas.
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*/
MAE_Ret WdgCommonDraw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

/** WdgCommonGetViewModel
* @brief   Get widget's view model
*
* @param[in]   IWidgetPtr(IWidget*)    The pointer of IWidget interface object.
* @param[out]  ppModel(IModel**)       A pointer of a model pointer that will be returned the widget's view model.
* @param[in]   pOwner(IBase*)          A pointer to a IBase object which will keep the returned view model.
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*/
MAE_Ret WdgCommonGetViewModel(IWidget *pIWidget, IModel **ppObj, IBase *pOwner);


/** WdgCommonGetModel
* @brief   This function can retrieve the model from a specific widget.
*
* @param[in]   IWidgetPtr(IWidget*)    A pointer of IWidget interface object.
* @param[in]   iid(MAE_IId)            An interface Id to indicate which kind of model to get.
* @param[out]  ppModel(IModel**)       A pointer of IModel pointer to retrieve widget's model.
* @param[in]   pOwner(IBase*)          A pointer of IBase object which will keep the returned model.
*
* @retval  MAE_RET_SUCCESS         Success.
* @retval  MAE_RET_FAILED		    Failed. This widget does not have a model.
* @retval  MAE_RET_NOT_SUPPORTED	Failed. The queried interface id is not supported.
*/
MAE_Ret WdgCommonGetModel(IWidget *pIWidget, MAE_IId iId, IModel **ppObj, IBase* pOwner);

/** WdgCommonSetModel
* @brief   This function can set a model to a specific widget.
*
* @param[in]   IWidgetPtr(IWidget*)    A pointer of IWidget interface object.
* @param[in]   pModel(IModel*)         A pointer of IModel object to be set.
* @param[in]   pOwner(IBase*)          No used.
*
* @retval  MAE_RET_SUCCESS         Success.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. The specific widget does not support this kind of model.
* @retval  MAE_RET_FAILED          Failed. Other reasons.
*/
MAE_Ret WdgCommonSetModel(IWidget *pIWidget, IModel *pIModel, IBase* pOwner);

/** WdgCommonGetProperty
* @brief   A function to get the property of a specific widget.
*
* @param[in]   IWidgetPtr(IWidget*)    The pointer of IWidget interface object
* @param[in]   PropId(WdgPropId_t)     Property ID. An enum defined in mmi_mmi_mae_widget_properties.h
* @param[out]  ValuePtr(u32*)          A pointer of u32 which will return a value associated with the requested property Id.
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*/
MAE_Ret WdgCommonGetProperty
(
    IWidget         *IWidgetPtr,
    WdgPropId_t     PropId,
    u32             *ValuePtr
);

/** WdgCommonSetProperty
* @brief   A function to set widget's property.
*
* @param[in]   IWidgetPtr(IWidget*)    The pointer of IWidget interface object
* @param[in]   PropId(WdgPropId_t)     Property ID. An enum defined in mmi_mmi_mae_widget_properties.h
* @param[in]   Value(u32)              A value want to be set which is related to the requested property Id.
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*/
MAE_Ret WdgCommonSetProperty
(
    IWidget         *IWidgetPtr,
    WdgPropId_t     PropId,
    u32             Value
);


/** WdgContainerAdd
* @brief   The function can insert a widget to the container.
*
* @param[in]   pContainer(IWidget*)         The pointer of container object.
* @param[in]   pIWidget(IWidget*)           A pointer of IWidget interface object to add.
* @param[in]   pRefWidget(IWidget*)         The reference widget. A pointer of IWidget interface object to be reference.
*                                           If the parameter is NULL, it means that widget will be added to top-most or
*                                           bottom-most depending on isUpper parameter.
* @param[in]   isUpper(boolean)             A boolean value.
*                                           TRUE: add the widget to the above of the reference widget,
*                                           FALSE: add the widget to the below of the reference widget.
* @param[in]   pDscp(const void*)           This is a description structure. Different type by different container.
*
* @retval  MAE_RET_SUCCESS         Success. Successfully to add.
* @retval  MAE_RET_BAD_PARAM       Failed. pIWidget is NULL or pRefWidget not found.
* @retval  MAE_RET_OUT_OF_MEMORY   Failed. Memory is not enough.
*/
MAE_Ret WdgContainerAdd
(
    IWidget         *pContainer,
    IWidget         *WidgetPtr,
    IWidget         *RefWidgetPtr,
    boolean         isUpper,
    const void      *DescPtr
);

/** WdgContainerDelete
* @brief	The function can remove a widget from the specific container.
*
* @param[in]   pContainer(IWidget*)         The pointer of container object.
* @param[in]   pIWidget(IWidget*)           A pointer of IWidget interface object to remove.
*
* @retval  MAE_RET_SUCCESS         Success. Successfully to remove.
* @retval  MAE_RET_FAILED          Failed. pIWidget is NULL or not found.
*/
MAE_Ret WdgContainerDelete
(
    IWidget     *pContainer,
    IWidget     *WidgetPtr
);

/** WdgContainerMove
* @brief	The function move the widget in container's widget stack.
*
* @param[in]   pContainer(IWidget*)         The pointer of container object.
* @param[in]   pIWidget(IWidget*)           A pointer of IWidget interface object to be moved.
* @param[in]   pRefWidget(IWidget*)         A pointer of IWidget interface object to be reference.
* @param[in]   isUpper(boolean)             A boolean, TRUE is moving the widget to the above of referred widget,
*                                           FALSE is moving the widget to the below of referred widget.
*
* @retval  MAE_RET_SUCCESS         Success. Moving is successful.
* @retval  MAE_RET_BAD_PARAM       Failed. pIWidget is NULL, or pIWidget not found in widget stack, or pRefWidget not found in widget stack.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. Some kind of container does not support.
*/
MAE_Ret WdgContainerMove
(
    IWidget     *pContainer,
    IWidget     *WidgetPtr,
    IWidget     *RefWidgetPtr,
    boolean     isUpper
);

/** WdgContainerGetWidget
* @brief	Obtain the instance of the widget from this container.
*
* @param[in]   pContainer(IWidget*)         The pointer of container object.
* @param[in]   pRW(IWidget*)                A pointer of IWidget interface object to be reference.
* @param[in]   isUpper(boolean)             A boolean flag, TRUE to search to top(of the stack), FALSE to search to bottom(of the stack).
* @param[in]   isWrap(boolean)              A boolean flag, TRUE means to search to top/bottom when at bottom/top.
* @param[in]   pOwner(IBase*)               A pointer to a IBase object which will keep the returned widget.
*
* @retval  NULL.       If reference widget not found or stack empty.
* @retval  IWidget*    Get a widget according to the parameters condition.
*/
IWidget *WdgContainerGetWidget
(
    IWidget         *pContainer,
    IWidget         *RefWidgetPtr,
    boolean         isUpper,
    boolean         isWrap,
    IBase           *pOwner
);

/** WdgContainerInvalidate
* @brief        Send a Invalid request to a Container
*
* @param[in]   pContainer(IContainer*)   The pointer of IContainer interface object.
* @param[in]   WidgetPtr(IWidget*)            A pointer of widget instance object in this container.
* @param[in]   WRectPtr(const Rect_t*)           A pointer of constant rectangle coordinated to the widget of pWidget.
* @param[in]   Flags(InvFlag_t)               A flag for invalidating.
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*
*/
MAE_Ret WdgContainerInvalidate
(
    IWidget         *pContainer,
    IWidget         *WidgetPtr,
    const Rect_t    *pRc,
    InvFlag_t       nFlags
);

/** WdgContainerLocate
* @brief	Obtain the location of the widget on root-container.
*          Note, the implementation should add the location value to the parameter passed in, NOT fill the result directly
*          because the child widget may be a conatiner and use this interface try to obtain the location for it's child widget.
*          At that time the input pRc will put the relative location of it and it's child widget. You only need to add the relative position and call
*          our container to calculate the rest for us.
*          Thus, You only need to add the relative location value of child pWidget and then ask your parent
*          container to calc your position in your parent container.
*
* @param[in]   pContainer(IWidget*)   The pointer of IContainer interface object.
* @param[in]   WidgetPtr(IWidget*)            A pointer of widget instance object in this container.
* @param[out]  ppRoot(IContainer**)         A pointer of IContainer object pointer to retrieve the root-container.
* @param[out]  RelativeRectPtr(Rect_t*)                 A pointer of Rect_t to retrieve the position of pWidget coordinate to root-container.
* @param[in]   pOwner(IBase*)               A pointer to a IBase object which will keep the returned root-container.
*
* @retval  MAE_RET_SUCCESS         Success.
* @retval  MAE_RET_FAILED          Failed. Widget not found.
*/
MAE_Ret WdgContainerLocate
(
    IWidget *pContainer,
    IWidget *WidgetPtr,
    IContainer **ppRoot,
    Rect_t *RelativeRectPtr,
    IBase *pOwner
);

/** WdgContainerGetTopMostWidget
* @brief	The function retrieves the widget which is stored on the top of container's widget stack.
*
* @param[in]   IContainerPtr(IContainer*)   The pointer of IContainer interface object.
* @param[in]   pOwner(IBase*)               A pointer to a IBase object which will keep the returned widget.
*
* @retval  A pointer of IWidget object or NULL.
*/
__INLINE IWidget* WdgContainerGetTopMostWidget
(
 IContainer        *IContainerPtr,
 IBase               *pOwner
 )
{
	return WdgContainerGetWidget((IWidget*)IContainerPtr, NULL, FALSE, FALSE, pOwner);
}

/** WdgContainerGetBottomMostWidget
* @brief	The function retrieves the widget which is stored on the bottom of container's widget stack.
*
* @param[in]   IContainerPtr(IContainer*)   The pointer of IContainer interface object.
* @param[in]   pOwner(IBase*)               A pointer to a IBase object which will keep the returned widget.
*
* @retval  A pointer of IWidget object or NULL.
*/
__INLINE IWidget* WdgContainerGetBottomMostWidget
(
 IContainer       *IContainerPtr,
 IBase              *pOwner
 )
{
	return WdgContainerGetWidget((IWidget*)IContainerPtr, NULL, TRUE, FALSE, pOwner);
}

/** WdgContainerAddToTopMost
* @brief	The function add a widget to the top most of container's widget stack.
*
* @param[in]   IContainerPtr(IContainer*)   The pointer of IContainer interface object.
* @param[in]   pIWidget(IWidget*)           A pointer of IWidget interface object to add.
* @param[in]   pDscp(const void*)           This is a description structure. Different type by different container.
*
* @retval  MAE_RET_SUCCESS         Success. Successfully to add.
* @retval  MAE_RET_BAD_PARAM       Failed. pIWidget is NULL or not found.
* @retval  MAE_RET_OUT_OF_MEMORY   Failed. Memory is not enough.
* @retval	MAE_RET_FAILED          Failed. Other reason.
*/
__INLINE MAE_Ret WdgContainerAddToTopMost
(
 IContainer             *IContainerPtr,
 IWidget				   *pIWidget,
 const void			   *pDscp
 )
{
	return WdgContainerAdd((IWidget*)IContainerPtr, pIWidget, NULL, FALSE, pDscp);
}

/** WdgContainerAddToBottomMost
* @brief	The function add a widget to the bottom most of container's widget stack.
*
* @param[in]   IContainerPtr(IContainer*)   The pointer of IContainer interface object.
* @param[in]   pIWidget(IWidget*)           A pointer of IWidget interface object to add.
* @param[in]   pDscp(const void*)           This is a description structure. Different type by different container.
*
* @retval  MAE_RET_SUCCESS         Success. Successfully to add.
* @retval  MAE_RET_BAD_PARAM       Failed. pIWidget is NULL or not found.
* @retval  MAE_RET_OUT_OF_MEMORY   Failed. Memory is not enough.
* @retval	MAE_RET_FAILED          Failed. Other reason.
*/
__INLINE MAE_Ret WdgContainerAddToBottomMost
(
 IContainer             *IContainerPtr,
 IWidget				   *pIWidget,
 const void			   *pDscp
 )
{
	return WdgContainerAdd((IWidget*)IContainerPtr, pIWidget, NULL, TRUE, pDscp);
}

/** WdgContainerMoveToTop
* @brief	The function move the widget to the top of container's widget stack.
*
* @param[in]   IContainerPtr(IContainer*)   The pointer of IContainer interface object.
* @param[in]   pIWidget(IWidget*)           A pointer of IWidget interface object to be moved.
*
* @retval  MAE_RET_SUCCESS         Success. Moving is successful.
* @retval  MAE_RET_BAD_PARAM       Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. Some kind of container does not support.
*/
__INLINE MAE_Ret WdgContainerMoveToTop
(
 IContainer             *IContainerPtr,
 IWidget				   *pIWidget
 )
{
	return WdgContainerMove((IWidget*)IContainerPtr, pIWidget, NULL, FALSE);
}

/** WdgContainerMoveToBottom
* @brief	The function move the widget to the bottom of container's widget stack.
*
* @param[in]   IContainerPtr(IContainer*)   The pointer of IContainer interface object.
* @param[in]   pIWidget(IWidget*)           A pointer of IWidget interface object to be moved.
*
* @retval  MAE_RET_SUCCESS         Success. Moving is successful.
* @retval  MAE_RET_BAD_PARAM       Failed. pIWidget is NULL, or pIWidget not found in widget stack.
* @retval  MAE_RET_NOT_SUPPORTED   Failed. Some kind of container does not support.
*/
__INLINE MAE_Ret WdgContainerMoveToBottom
(
 IContainer             *IContainerPtr,
 IWidget				   *pIWidget
 )
{
	return WdgContainerMove((IWidget*)IContainerPtr, pIWidget, NULL, TRUE);
}

/** WdgDecoratorGetDecWidget
* @brief        Send a EVT_WIDGET_DECORATOR_GET_DECWDG event to a Decorator Widget
*
* @param[in]    pDecorator  The pointer of Container
* @param[out]   ppChild     A pointer of returned child widget pointer
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*
*/
MAE_Ret WdgDecoratorGetDecWidget
(
    IWidget     *pDecorator,
    IWidget     **ppChild
);

/** WdgDecoratorSetDecWidget
* @brief        Send a EVT_WIDGET_DECORATOR_SET_DECWDG event to a Decorator Widget
*
* @param[in]    pDecorator  The pointer of Container
* @param[out]   pChild      A pointer of child widget
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_FAILED		Failed. The widget can not handle this request.
*
*/
MAE_Ret WdgDecoratorSetDecWidget
(
    IWidget     *pDecorator,
    IWidget     *pChild
);

/** WdgCommonSetHandlerHookFunc
* @brief        This function is used for an application which want to hook this Widget object's handle event function.
*
* @param[in]    pWDGObject            The pointer of Widget
* @param[in]    pHD                   A pointer of WidgetHandler_t structure. The input is the hook event handler function of application. The output is  the original event handler.
*
* @retval       None.
*
*/
void WdgCommonSetHandlerHookFunc
(
    IWidget             *pWDGObject,
    WidgetHandler_t     *pHD
);

/** WdgCommonSetLookCtrlType
* @brief        Set widget look control type to WDG_LOOKCTRL_TYPE_THEME or WDG_LOOKCTRL_TYPE_MANUAL.
*
* @param[in]    pWDGObject        The widget which want to be set
* @param[in]    eLookCtrlType     Look control type.
*                                 Ex,When set WDG_LOOKCTRL_TYPE_THEME; the color of text widget is decided by theme.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgCommonSetLookCtrlType
(
    IWidget                 *pWDGObject,
    WdgLookCtrlType_e       eLookCtrlType
)
{
    return WdgCommonSetProperty(pWDGObject, PROP_WDG_LOOKCTRL_TYPE, (u32)eLookCtrlType);
}

/** WdgCommonSetIconStyle
* @brief    Set SwitchIcon/SwitchIconItem widget's icon style
*
* @param[in]    pWDGObject        The pointer of IWidget interface object
* @param[in]    nStyle            A kind of icon style enum value, refer to Icon_Style_e.
*
*
*/
__INLINE void WdgCommonSetIconStyle
(
    IWidget                 *pWDGObject,
    Icon_Style_e            nStyle
)
{
    WdgCommonSetProperty(pWDGObject, PROP_SWITCH_WDG_ICON_STYLE, (u32)nStyle);
}

/** WdgCommonSetTextColor
* @brief    Set text color of widget.
*
* @param[in]    pWDGObject       The pointer of IWidget interface object
* @param[in]    TextColor        RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
*
*/
__INLINE void WdgCommonSetTextColor
(
    IWidget                 *pWDGObject,
    RGBColor_t              TextColor
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_TEXT_COLOR, (u32)TextColor);
}

/** WdgCommonSetHighlightTextColor
* @brief    Set text color of widget.
*
* @param[in]    pWDGObject       The pointer of IWidget interface object
* @param[in]    TextColor        RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
*
*/
__INLINE void WdgCommonSetHighlightTextColor
(
    IWidget                 *pWDGObject,
    RGBColor_t              TextColor
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_HIGHLIGHT_TEXT_COLOR, (u32)TextColor);
}

/** WdgCommonSetFontType
* @brief    Set font type on widget.
*
* @param[in]    pWDGObject      The pointer of IWidget interface object
* @param[in]    FT              A kind of font type value, refer to mae_font.h
*
*
*/
__INLINE void WdgCommonSetFontType
(
    IWidget                 *pWDGObject,
    FontType_t              FT
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_FONT_TYPE, (u32)FT);
}

/** WdgCommonSetFontCategory
* @brief    Set font category of widget.
*
* @param[in]    pIWidget(IWidget*)    The pointer of IWidget interface object
* @param[in]    FC                    A kind of font category enum value, refer to mae_font.h
*
*
*/
__INLINE void WdgCommonSetFontCategory
(
    IWidget                 *pWDGObject,
    FontCategory_t          FC
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_FONT_CATE, (u32)FC);
}

/** WdgCommonSetVectorFontSize
* @brief    Set font size of widget. only work when font Category is FONT_CAT_VECTOR
*
* @param[in]    pIWidget(IWidget*)    The pointer of IWidget interface object
* @param[in]    nSize                 font size
*
*
*/
__INLINE void WdgCommonSetVectorFontSize
(
    IWidget                 *pWDGObject,
    u32						nSize
)
{
#ifdef __FEATURE_VECTOR_FONT__
	if(FONTBASE_IsVectorFontExist())
	{
		WdgCommonSetProperty(pWDGObject, PROP_WDG_FONT_CATE, (u32)FONT_CAT_VECTOR);
		WdgCommonSetProperty(pWDGObject, PROP_WDG_FONT_SIZE, (u32)nSize);
	}
#endif
}

/** WdgCommonSetLangDirection
* @brief  Set language direction to IWidget object.
*
* @param[in]    pWDGObject      The pointer of IDecorator interface object
* @param[in]    LD              A u8 value which indicates the text display style:
*                               LANG_DIR_L_TO_R if want the text display style of the widget is left-to-right, or
*                               LANG_DIR_R_TO_L if want the text display style of the widget is right-to-left.
*
*
*/
__INLINE void WdgCommonSetLangDirection
(
    IWidget                 *pWDGObject,
    WdgLangDirection_e      LD
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_LANG_DIRECTION, (u32)LD);
}

/** WdgCommonSetFocus
* @brief        Set the widget to be focused of unfocused
*
* @param[in]    pWDGObject        The pointer of IWidget interface object
* @param[in]    bisFocus          A boolean value. TRUE is to set the widget to be focused. FALSE is to set the widget to be unfocused.
*
* @retval       None
*
*
*/
void WdgCommonSetFocus
(
    IWidget                 *pWDGObject,
    boolean                 bisFocus
);

/** WdgCommonSetVisible
* @brief        Set the widget to visible or invisible
*
* @param[in]    pWDGObject        The pointer of IWidget interface object
* @param[in]    bisVisible        A boolean value to set. TRUE is to set this widget to be visible; FALSE is to set this widget to be invisible.
*
*
*/
void WdgCommonSetVisible
(
    IWidget                 *pWDGObject,
    boolean                 bisVisible
);

/** WdgCommonSetAlignment
* @brief        Set widget alignment
*
* @param[in]    pWDGObject        Pointer to the widget
* @param[in]    nAlignment        Widget Alignment flag
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgCommonSetAlignment
(
    IWidget                 *pWDGObject,
    WdgAlignment_e          nAlignment
)
{
    return WdgCommonSetProperty(pWDGObject, PROP_WDG_ALIGNMENT, (u32)nAlignment);
}

/** WdgCommonSetPaddingData
* @brief        Set widget padding size, include left, right, top and bottom size.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    pPaddingData        The widget padding size which will be set to the widget.
*
*
*/
void WdgCommonSetPaddingData
(
    IWidget                 *pWDGObject,
    WdgPaddingData_t        *pPaddingData
);

/** WdgCommonSetPaddingTop
* @brief        Set widget padding top size
*
* @param[in]    pWDGObject        Pointer to the widget
* @param[in]    nPadding        The padding top size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgCommonSetPaddingTop
(
    IWidget                 *pWDGObject,
    u8						 nPadding
)
{
    return WdgCommonSetProperty(pWDGObject, PROP_PADDING_TOP, (u32)nPadding);
}

/** WdgCommonSetPaddingRight
* @brief        Set widget padding right size
*
* @param[in]    pWDGObject        Pointer to the widget
* @param[in]    nPadding        The padding right size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgCommonSetPaddingRight
(
    IWidget                 *pWDGObject,
    u8						 nPadding
)
{
    return WdgCommonSetProperty(pWDGObject, PROP_PADDING_RIGHT, (u32)nPadding);
}

/** WdgCommonSetPaddingLeft
* @brief        Set widget padding left size
*
* @param[in]    pWDGObject        Pointer to the widget
* @param[in]    nPadding        The padding left size
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgCommonSetPaddingLeft
(
    IWidget                 *pWDGObject,
    u8						 nPadding
)
{
    return WdgCommonSetProperty(pWDGObject, PROP_PADDING_LEFT, (u32)nPadding);
}

/** WdgCommonSetBorderData
* @brief        Set widget border relative data, include left, right, top and bottom border size and Border color.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    pBorderData         The widget border size and Border color which will be set to the widget.
*
*
*/
void WdgCommonSetBorderData
(
    IWidget                 *pWDGObject,
    WdgBorderData_t         *pBorderData
);

/** WdgCommonSetBorderSize
* @brief        Set widget border size
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    nBorderSize            The widget border color which will be set to the widget
*
*
*/
__INLINE void WdgCommonSetBorderSize
(
    IWidget                 *pWDGObject,
    u32              nBorderSize
)
{
    WdgCommonSetProperty(pWDGObject, PROP_BORDER_SIZE, nBorderSize);
}

/** WdgCommonSetBorderColor
* @brief        Set widget border color
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    nBoderColor            The widget border color which will be set to the widget
*
*
*/
__INLINE void WdgCommonSetBorderColor
(
    IWidget                 *pWDGObject,
    RGBColor_t              nBorderColor
)
{
    WdgCommonSetProperty(pWDGObject, PROP_BORDER_COLOR, (u32)nBorderColor);
}

/** WdgCommonSetBGColor
* @brief        Set widget background color
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    nBGColor            The widget background color which will be set to the widget
*
*
*/
__INLINE void WdgCommonSetBGColor
(
    IWidget                 *pWDGObject,
    RGBColor_t              nBGColor
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_BG_COLOR, (u32)nBGColor);
}

/** WdgCommonSetBGImage
* @brief        Set widget background image
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    pBGImage            The widget background image which will be set to the widget
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgCommonSetBGImage
(
    IWidget                 *pWDGObject,
    IBase                   *pBGImage
)
{
    return WdgCommonSetProperty(pWDGObject, PROP_WDG_BG_IMAGE, (u32)pBGImage);
}

/** WdgCommonSetBGImage
* @brief        Set widget background image
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    pBGImage            The widget background image which will be set to the widget
*
*
*/
void WdgCommonSetBGImageId
(
    IWidget *pWDGObject,
    u32 u32ImageId
);


/** WdgCommonSetBGPosition
* @brief        Set widget background position
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    tBGPosition         The widget background position which will be set to the widget
*
*
*/
__INLINE void WdgCommonSetBGPosition
(
    IWidget                 *pWDGObject,
    WdgBackgroundPos_t      tBGPosition
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_BG_POSITION, (u32)tBGPosition);
}

/** WdgCommonSetBGEnable
* @brief        Set widget background enable/disable
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    bEnable             The widget background enable/disable which will be set to the widget
*
*
*/
__INLINE void WdgCommonSetBGEnable
(
    IWidget                 *pWDGObject,
    boolean                 bEnable
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_BG_ENABLE, (u32)bEnable);
}

/** WdgCommonSetBGAlignment
* @brief        Set widget background image alignment
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    eWdgAlignment       The widget background image alignment which will be set to the widget
*
*
*/
__INLINE void WdgCommonSetBGAlignment
(
    IWidget                 *pWDGObject,
    WdgAlignment_e          eWdgAlignment
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_BG_ALIGN, (u32)eWdgAlignment);
}


/** WdgCommonSetBeAutoAnimate
* @brief        Set widget can be auto animated, for image and text widget
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    bAutoAnimate        TRUE/FALSE
*
*
*/
__INLINE void WdgCommonSetBeAutoAnimate
(
    IWidget                 *pWDGObject,
    boolean				 bAutoAnimate
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_BE_AUTO_ANIMATE, (u32)bAutoAnimate);
}

/** WdgCommonSetEnableAnimate
* @brief        Set widget can enable animated, for image and text widget
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    bAnimate        TRUE/FALSE
*
*
*/
__INLINE void WdgCommonSetEnableAnimate
(
    IWidget                 *pWDGObject,
    boolean				 bAnimate
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_ENABLE_ANIMATE, (u32)bAnimate);
}

/** WdgCommonResetAnimate
* @brief        Set widget reset animate, for image and text widget
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    bReset        TRUE/FALSE
*
*
*/
__INLINE void WdgCommonResetAnimate
(
    IWidget                 *pWDGObject,
    boolean				 bReset
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_RESET_ANIMATE, (u32)bReset);
}

/** WdgCommonSetBeItemWidget
* @brief        Set widget is item widget or not
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    bItemWidget        TRUE/FALSE
*
*
*/
__INLINE void WdgCommonSetBeItemWidget
(
    IWidget                 *pWDGObject,
    boolean				 bItemWidget
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_BE_ITEM_WDG, (u32)bItemWidget);
}

/** WdgCommonSetBeItemInGrid
* @brief        Set widget is item widget in grid or not
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    bInGrid        TRUE/FALSE
*
*
*/
__INLINE void WdgCommonSetBeItemInGrid
(
    IWidget                 *pWDGObject,
    boolean				 bInGrid
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_BE_ITEM_IN_GRID, (u32)bInGrid);
}

/** WdgCommonSetHighlighted
* @brief        Set widget to be highlighted or not
*
* @param[in]    pWDGObject           The pointer of IWidget interface object
* @param[in]    bHighlighted      Flag of highlighted or not
*
* @retval       void
*
*/
__INLINE void WdgCommonSetHighlighted
(
    IWidget             *pWDGObject,
    boolean             bHighlighted
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_HIGHLIGHTED, (u32)bHighlighted);
}

/** WdgCommonSetPressed
* @brief        Set widget to be pressed or not
*
* @param[in]    pWDGObject           The pointer of IWidget interface object
* @param[in]    bPressed      Flag of pressed or not
*
* @retval       void
*
*/
__INLINE void WdgCommonSetPressed
(
    IWidget             *pWDGObject,
    boolean             bPressed
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_ITEM_PRESSED, (u32)bPressed);
}

/** WdgCommonGetLookCtrlType
* @brief        Get widget look control type
*
* @param[in]    pWDGObject          The widget which want to be get
*
* @retval       WdgLookCtrlType_e   Look control type. WDG_LOOKCTRL_TYPE_THEME or WDG_LOOKCTRL_TYPE_MANUAL
*
*/
WdgLookCtrlType_e WdgCommonGetLookCtrlType
(
    IWidget                 *pWDGObject
);

/** WdgCommonGetTextColor
* @brief        Get text color of widget.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pTextColor          RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter.
*
*/
__INLINE MAE_Ret WdgCommonGetTextColor
(
    IWidget                 *pWDGObject,
    RGBColor_t              *pTextColor
)
{
    return WdgCommonGetProperty(pWDGObject, PROP_WDG_TEXT_COLOR, (RGBColor_t*)pTextColor);
}

/** WdgCommonGetHighlightTextColor
* @brief        Get Highlight text color of widget.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    pTextColor          RGBColor_t value. User can make the value via MAKE_RGB(), MAKE_RGBA().
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter.
*
*/
__INLINE MAE_Ret WdgCommonGetHighlightTextColor
(
    IWidget                 *pWDGObject,
    RGBColor_t              *pTextColor
)
{
    return WdgCommonGetProperty(pWDGObject, PROP_WDG_HIGHLIGHT_TEXT_COLOR, (RGBColor_t*)pTextColor);
}

/** WdgCommonGetFontType
* @brief    Get font type on widget.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pFT                 A kind of font type value, refer to mae_font.h
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter.
*
*/
__INLINE MAE_Ret WdgCommonGetFontType
(
    IWidget                 *pWDGObject,
    FontType_t              *pFT
)
{
    return WdgCommonGetProperty(pWDGObject, PROP_WDG_FONT_TYPE, (u32*)pFT);
}

/** WdgCommonGetFontCategory
* @brief    Get font category of widget.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pFC                 A kind of font category enum value, refer to mae_font.h
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter.
*
*/
__INLINE MAE_Ret WdgCommonGetFontCategory
(
    IWidget                 *pWDGObject,
    FontCategory_t          *pFC
)
{
    return WdgCommonGetProperty(pWDGObject, PROP_WDG_FONT_CATE, (u32*)pFC);
}

/** WdgCommonGetVectorFontSize
* @brief    Get font size of widget
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pSize               font size
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter.
*
*/
__INLINE MAE_Ret WdgCommonGetVectorFontSize
(
    IWidget                 *pWDGObject,
    FontCategory_t          *pSize
)
{
#ifdef __FEATURE_VECTOR_FONT__
	if(FONTBASE_IsVectorFontExist())
	{
		return WdgCommonGetProperty(pWDGObject, PROP_WDG_FONT_SIZE, (u32*)pSize);
	}
	else
	{
		if (pSize)
			*pSize = 0;
		return MAE_RET_FAILED;
	}
#else
	if (pSize)
		*pSize = 0;
	return MAE_RET_FAILED;
#endif
}

/** WdgCommonSetLangDirection
* @brief  Get language direction to IWidget object.
*
* @param[in]    pWDGObject      The pointer of IDecorator interface object
*
* @retval       WdgLangDirection_e     A u8 value which indicates the text display style:
*                               LANG_DIR_L_TO_R if want the text display style of the widget is left-to-right, or
*                               LANG_DIR_R_TO_L if want the text display style of the widget is right-to-left
*
*/
WdgLangDirection_e WdgCommonGetLangDirection
(
    IWidget                 *pWDGObject
);


/** WdgCommonGetPaddingData
* @brief        Get widget padding size, include left, right, top and bottom size.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pPaddingData        The widget padding size which will be Get from the widget.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter(NULL).
*
*/
MAE_Ret WdgCommonGetPaddingData
(
    IWidget                 *pWDGObject,
    WdgPaddingData_t        *pPaddingData
);

/** WdgCommonGetPaddingLeft
* @brief        Get widget padding left size
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pPadding        The widget padding size which will be Get from the widget.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter(NULL).
*
*/
MAE_Ret WdgCommonGetPaddingLeft
(
    IWidget                 *pWDGObject,
    u8        *pPadding
);

/** WdgCommonGetPaddingRight
* @brief        Get widget padding right size
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pPadding        The widget padding size which will be Get from the widget.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter(NULL).
*
*/
MAE_Ret WdgCommonGetPaddingRight
(
    IWidget                 *pWDGObject,
    u8        *pPadding
);

/** WdgCommonGetCanBeFocused
* @brief        Ask the widget if it can be focused.Widget should check self visibility? not visible, can not focused.
*
* @param[in]    pWDGObject        The pointer of IWidget interface object
*
* @retval        boolean      boolean which will be set to TRUE if the widget can be focused or set to FALSE if the widget can not be focused
*
*/
boolean WdgCommonGetCanBeFocused
(
    IWidget                 *pWDGObject
);

/** WdgCommonGetIsOnFocused
* @brief        Ask the widget if it is focused now.
*
* @param[in]    pWDGObject    The pointer of IWidget interface object
*
* @retval        boolean      boolean which will be set to TRUE if the widget is focused or set to FALSE if the widget is not focused.
*
*/
boolean WdgCommonGetIsOnFocused
(
    IWidget                 *pWDGObject
);

/** WdgCommonGetIsVisible
* @brief        Ask this widget if visible
*
* @param[in]    pWDGObject        The pointer of IWidget interface object
*
*
* @retval        TRUE                Visible.
* @retval        FALSE               Invisible.
*
*/
boolean WdgCommonGetIsVisible
(
    IWidget                 *pWDGObject
);

/** WdgCommonGetComponet
* @brief        Get component widget from this widget(for pick widget¡Bdoubleitem widget¡Bimagetextimage widget¡Bimagedoubleitem widget¡Bmenu widget and tabwidget)
*
* @param[in]    pWDGObject                The pointer of IWidget interface object
* @param[in]    nCompId                   Component Id
*
*
* @retval         The widget which is the component widget
*
*/
IWidget* WdgCommonGetComponet
(
    IWidget                 *pWDGObject,
    u32                     nCompId
);

/** WdgCommonGetBorderData
* @brief        Get widget border relative data, include left, right, top and bottom border size and Border color.
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pBorderData         The widget border size and Border color which will be get from the widget.
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter(NULL).
*
*/
MAE_Ret WdgCommonGetBorderData
(
    IWidget                 *pWDGObject,
    WdgBorderData_t         *pBorderData
);

/** WdgCommonGetBGColor
* @brief        Get widget background color
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[out]   pBGColor            The widget background color which will be get from the widget
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed, Not Support or Error parameter(NULL).
*
*/
__INLINE MAE_Ret WdgCommonGetBGColor
(
    IWidget                 *pWDGObject,
    RGBColor_t              *pBGColor
)
{
    return WdgCommonGetProperty(pWDGObject, PROP_WDG_BG_COLOR, (u32*)pBGColor);
}

/** WdgCommonGetBGEnable
* @brief        Get widget background enable/disable
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
*
* @retval       boolean                The widget background enable/disable which will be get from the widget
*
*/
boolean WdgCommonGetBGEnable
(
    IWidget                 *pWDGObject
);

/** WdgCommonSetMultiTouchEnable
* @brief        Set widget multi-touch enable/disable
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
* @param[in]    bEnable             The widget multi-touch enable/disable which will be set to the widget
*
*
*/
__INLINE void WdgCommonSetMultiTouchEnable
(
 IWidget                 *pWDGObject,
 boolean                 bEnable
)
{
    WdgCommonSetProperty(pWDGObject, PROP_WDG_MULTI_TOUCH, (u32)bEnable);
}

/** WdgCommonGetMultiTouchEnable
* @brief        Get widget multi-touch enable/disable
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
*
* @retval       boolean                The widget multi-touch enable/disable which will be get from the widget
*
*/
boolean WdgCommonGetMultiTouchEnable
(
    IWidget                 *pWDGObject
);

/** WdgContainerGetWidgetPos
* @brief        Get position of child widget.
*
* @param[in]    pContainer  The pointer of Container
* @param[in]    pWidget     A pointer of child widget instance object in this container
*
* @retval       Rect_t.    constant rectangle coordinated to the child pWidget
*
*/
Rect_t WdgContainerGetWidgetPos
(
    IWidget        *pContainer,
    IWidget        *pWidget
);

/** WdgDestroyForWnd
* @brief        !!!!Use WND_DESTROY_WDG_IF instead of this function temporally.
*               Destroy Widget object in a window
*
* @param[in]    pWDGObject          The pointer of IWidget interface object
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
MAE_Ret WdgDestroyForWnd
(
    IWIDGET                    *pWDGObject
);

/** WND_DESTROY_WDG_IF
* @brief        Destroy MAE object
*
* @param[in]    pObj                The pointer of IWidget interface object
*
* @retval       MAE_RET_SUCCESS     Success
* @retval       others              Failed
*
*/
#define WND_DESTROY_WDG_IF(pObj) (pObj != NULL)?((MAE_RET_SUCCESS == WdgDestroyForWnd((IWidget*)pObj))?(pObj = 0, MAE_RET_SUCCESS):MAE_RET_FAILED):MAE_RET_FAILED


/** WdgCommonEnableScrollBar
* @brief        Create a vertical/horizontal scrollbar widget and attach to ScrolledWidget
*                Usually the ScrolledWidget will be type:
*                     CLSID_MFLCONTAINER
*                    CLSID_INPUTWIDGET
*                    CLSID_VIEWPORTWIDGET
*                    CLSID_TEXTWIDGET
*                    CLSID_ONELINE_LIST_WIDGET
*                    CLSID_VERT_LISTWIDGET
*               Be careful, Once you call this function, the scrolled widget parent container will be changed!
*
* @param[in]    hWin        The window handle
* @param[in]    pScrolledWidget   The pointer of IWidget interface object, which you wish to scrolled
* @param[in]    nScrollWidgetID   The scrollbar widget unique ID of window
* @param[in]    eScrollBarStyle   The scrollbar widget style
*
* @retval       The pointer of ScrollBar pointer        Success.
* @retval       NULL                                    Failed.
*
*/
IWidget *WdgCommonEnableScrollBar
(
        HWIN hWin,
        IWidget     *pScrolledWidget,
        u16         nScrollWidgetID,
        ScrollBarStyle_e eScrollBarStyle
);


/** WdgCommonEnableScrollindicator
* @brief        Create a Scrollindicator widget and attach to target widget
*                Usually the target widget will be List or Viewpoer widget
*               Be careful, Once you call this function, the scrolled widget parent container will be changed!
*
* @param[in]    hWin     The window handle
* @param[in]    pTargetWidget  The pointer of IWidget interface object
* @param[in]    nScrollWidgetID   The scrollbar widget unique ID of window
*
* @retval       The pointer of ScrollBar pointer        Success.
* @retval       NULL                                    Failed.
*
*/
IWidget *WdgCommonEnableScrollindicator
(
        HWIN hWin,
        IWidget     *pTargetWidget,
        u16         nScrollindicatorWidgetID
);


/** WdgSetNonDataModel
* @par Prototype
* WdgHlpr_SetWidgetModelData(IWidget *pWdg, MAE_IId IId, u32 data, IBase *pOwner)
*
* @brief  Helper user to set data to widget's model
*
* @param[in]	pWdg(IWidget*)	The pointer of IWidget interface object
* @param[in]	IId(MAE_IId)	Interface ID of the given widget's model
* @param[in]	data(u32)		Data to be set to model
* @param[in]	pOwner(IBase*)	Caller's instance
*
* @retval	MAE_RET_SUCCESS		Success. The widget can handle this request.
* @retval	MAE_RET_NOTSUPPORT	The MAE_IId is not supported yet.
*
* @note	Other error code please refer to model's return.
*/
MAE_Ret WdgSetNonDataModel(IWidget *pWdg, MAE_IId IId, u32 data, IBase *pOwner);

MAE_Ret WdgSetDataModel(IWidget *pWdg, void *pData, u32 nSizeofData, PfnModelFree pfFree);

/** WdgSetTextModel
* @brief	Set MAE_WChar string to the widget.
*
* @param[in]	IWidgetPtr(IWidget*)     The pointer of IWidget interface object
* @param[in]	pWChar(const MAE_WChar*) Pointer to MAE_WChar string.
*
* @retval	MAE_RET_SUCCESS		Success.
* @retval	MAE_RET_FAILED		Failed.
* @retval	MAE_RET_OUT_OF_MEMORY    No enough memory.
*/
MAE_Ret WdgSetTextModel(IWidget *IWidgetPtr, MAE_WChar *pWChar);

/** WdgAddViewMdlLsner
* @par Prototype
* WdgHlpr_AddViewMdlLsner(IBase *pThis, IWidget *pIWidget, ModelListener_t *pMdlLsnPtr)
*
* @brief  This function helps user to add listener to the viw model of widget.
*
* @param[in]  pOwner(IBase*)	Caller's instance
* @param[in]  pWdg(IWidget*)	The pointer of IWidget interface object
* @param[in]  pMdlLsnPtr(ModelListener_t *) The pointer of Model Listener structure(ModelListener_t).
*
*/
MAE_Ret WdgAddViewMdlLsner(IBase *pThis, IWidget *pIWidget, ModelListener_t *pMdlLsnPtr);

/**
* WdgContainerSetChildVisible
* @brief	Set the visibility of container's child
*
* @param	pIContainer		The pointer of IContainer interface object.
* @param	pChildWdg		A child widget of this container.
* @param	isVisible		Boolean value. TRUE is visible, FALSE is invisible.
*
* @retval	MAE_RET_SUCCESS	Success. The widget can handle this request.
* @retval	MAE_RET_FAILED	Failed. The widget can not handle this request.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid parameters.
*/
MAE_Ret WdgContainerSetChildVisible(IContainer *pIContainer, IWidget *pChildWdg, boolean isVisible);

/**
* WdgContainerGetChildVisible
* @brief	Get the visibility of container's child
*
* @param	pIContainer		The pointer of IContainer interface object.
* @param	pChildWdg		A child widget of this container.
* @param	pisVisible		A pointer of boolean value to retrieve the result.
*
* @retval	MAE_RET_SUCCESS	Success. The widget can handle this request.
* @retval	MAE_RET_FAILED	Failed. The widget can not handle this request.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid parameters.
*/
MAE_Ret WdgContainerGetChildVisible(IContainer *pIContainer, IWidget *pChildWdg, boolean *pisVisible);

/**
* WdgContainerMoveFocusToWidget
* @brief	This function can move the focus widget in container to the specific widget.
*          If the specific widget(pChildWdg) is not in this container, it will return MAE_RET_FAILED.
*
* @param	pIContainer		The pointer of IContainer interface object.
* @param	pChildWdg		A child widget of this container.
*
* @retval	MAE_RET_SUCCESS	    Success. The widget can handle this request.
* @retval	MAE_RET_FAILED	    Failed. The widget can not handle this request.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid parameters.
*/

MAE_Ret WdgContainerMoveFocusToWidget(IContainer *pIContainer, IWidget *pChildWdg);

MAE_Ret WdgContainerMoveFocusToTopWidget(IContainer *pIContainer);

MAE_Ret WdgContainerMoveFocusToBottomWidget(IContainer *pIContainer);

MAE_Ret WdgContainerMoveFocusToNextWidget(IContainer *pIContainer);

MAE_Ret WdgContainerMoveFocusToPrevWidget(IContainer *pIContainer);

/**
* WdgContainerGetFocusedWidget
* @brief	This function can get the focused widget object instance in the container.
*
* @param	pIContainer(IContainer*)    The pointer of IContainer interface object.
* @param	ppWdg(IWidget**)            A pointer of IWidget object pointer to retrieve focused widget in this container.
* @param	pOwner(IBase*)              A pointer of IBase object which will keep the focused widget.
*
* @retval	MAE_RET_SUCCESS	Success. The widget can handle this request.
* @retval	MAE_RET_FAILED	Failed. The widget can not handle this request.
* @retval  MAE_RET_BAD_PARAM   Failed. Invalid parameters.
*/
MAE_Ret WdgContainerGetFocusedWidget(IContainer *pIContainer, IWidget **ppWdg, IBase *pOwner);

MAE_Ret WdgCommonSetArrowWidth
(
    IWidget         *IWidgetPtr,
    u16             nWidth,
    Direction_e     eDirection
);

MAE_Ret WdgCommonSetArrowHeight
(
    IWidget         *IWidgetPtr,
    u16             nHeight,
    Direction_e     eDirection
);

MAE_Ret WdgCommonSetArrowActiveImg
(
    IWidget         *IWidgetPtr,
    IBitmap         *pActiveImage,
    Direction_e     eDirection
);

MAE_Ret WdgCommonSetArrowInActiveImg
(
    IWidget         *IWidgetPtr,
    IBitmap         *pInActiveImage,
    Direction_e     eDirection
);

#ifdef __TOUCH_SCREEN_MMI__
MAE_Ret WdgCommonSetArrowPressedImg
(
    IWidget         *IWidgetPtr,
    IBitmap         *pPressedImage,
    Direction_e     eDirection
);
#endif //__TOUCH_SCREEN_MMI__

/* Get function */
MAE_Ret WdgCommonGetArrowWidth
(
    IWidget         *IWidgetPtr,
    u16             *pWidth,
    Direction_e     eDirection
);

MAE_Ret WdgCommonGetArrowHeight
(
    IWidget         *IWidgetPtr,
    u16             *pHeight,
    Direction_e     eDirection
);

MAE_Ret WdgCommonGetClassId(IWidget *pIWidget, MAE_ClsId *pu16ClsId);

ModelListener_t* WdgCommonGetModelListener(IWidget *pIWidget);

MAE_Ret WdgAddNotifyCB(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData1, void *pUsrData2);
MAE_Ret WdgCancelNotifyCB(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, PFN_WIDGET_EVT_LISTENER pfnEvtListener, void *pUsrData1, void *pUsrData2);
void    WdgSendNotify(IWidget *pIWidget, WidgetEvtCode_t nEvtCode, u32 dwParam);
MAE_Ret WdgCommonGetMultitapCandidate(u32 nShiftMode, u8 nKeyID, u8 nKeyRepeatTimes, MAE_WChar *pOutFocusedCandidate);
void    WdgCommonSetMultitapCandidateLanguage(IWidget *pWDGInput, u32 nInLngCode);
MAE_Ret WdgCommonInitMultitapCandidate(IBase *pThis);
void    WdgCommonReleaseMultitapCandidate(IBase *pThis);
/*=============================================================*/

/** WdgCommonRegisterPreDrawCb
* @brief        Register callback : For handling draw before this widget draw, only enable one cb for each widget
*
* @param[in]    pIWidget          The widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgCommonRegisterPreDrawCb
(
    IWidget                 *pIWidget,
    PfnWdgPreDraw pfn,
    void                    *pUserData
);

/** WdgCommonDeregisterPreDrawCb
* @brief        Deregister PfnWdgPreDraw callback
*
* @param[in]    pIWidget          The widget which want to cancel callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgCommonDeregisterPreDrawCb
(
    IWidget                 *pIWidget,
    PfnWdgPreDraw pfn,
    void                    *pUserData
);

#endif //__MMI_WDGWRAP_Common_H__
