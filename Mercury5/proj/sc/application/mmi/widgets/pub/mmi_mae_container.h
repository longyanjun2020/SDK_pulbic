/**
* @file    mmi_mmi_mae_container.h
* @version $Id: mmi_mmi_mae_container.h 38890 2009-08-29 16:22:38Z zinc.chen $
*
* @brief   This file defines IContainer interface.
* 
* <Interface Description>
*
* <Interface ID>
*     IID_CONTAINER
*/
#ifndef __MMI_MAE_CONTAINER_H__
#define __MMI_MAE_CONTAINER_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"


/*=============================================================*/
// type and define
/*=============================================================*/

/**
* Flags for calling invalidate
*/
typedef u32 InvFlag_t;
enum {
	IFLAG_NONE            = 0x0000,
	IFLAG_FORCE           = 0x0001,
	IFLAG_CONTENT_CHANGED = 0x0002,
	IFLAG_SIZE_CHANGED    = 0x0004,
	IFLAG_LAYOUT_CHANGED  = 0x0008,
	IFLAG_LOOK_CHANGED    = 0x0010
};



/**
* @brief   Sturcture for get/set widget's visibility in a specific container.
*          Using condition:
*          when event id: EVT_WIDGET_GET_PROPERTY/EVT_WIDGET_SET_PROPERTY
*          and property id: PROP_CHILD_WDG_VISIBLE
*          P2 is the pointer of WidgetVisible_t structure.
*/
typedef struct {
	IWidget *pIWidget;
	boolean bVisible;
} WidgetVisible_t;


/*=============================================================*/
// interface
/*=============================================================*/
///
/// Methods of IContainer interface
///
/**
* INHERIT_IContainer
* @brief   INHERIT_IContainer is IContainer interface inheritance definition. 
*          Defines the methods of IContainer interface.
*/
#define INHERIT_IContainer(IName) \
	INHERIT_IWidget(IName)

DEFINE_INTERFACE(IContainer);


/** WdgContainer_WdgAdd_t
* @brief	Structure for insert a widget to the container.
*
* @param[in]   pIWidget(IWidget*)           A pointer of IWidget interface object to add.
* @param[in]   pRefWidget(IWidget*)         The reference widget. A pointer of IWidget interface object to be reference.
*                                           If the parameter is NULL, it means that widget will be added to top-most or 
*                                           bottom-most depending on isUpper parameter.
* @param[in]   isBefore(boolean)             A boolean value. 
*                                           TRUE: add the widget to the above of the reference widget, 
*                                           FALSE: add the widget to the below of the reference widget.
* @param[in]   DescPtr(const void*)           This is a description structure. Different type by different container.
*
* @param[out]  ret(MAE_Ret)			The return code.
*														MAE_RET_SUCCESS         Success. Successfully to add.
*														MAE_RET_BAD_PARAM       Failed. pIWidget is NULL or pRefWidget not found.
*														MAE_RET_OUT_OF_MEMORY   Failed. Memory is not enough.
*/
typedef struct
{
    IWidget     *WidgetPtr;
    IWidget     *RefWidgetPtr;
    boolean     isBefore;
    const void *DescPtr;
    MAE_Ret ret;
}WdgContainer_WdgAdd_t;

typedef struct 
{
	IWidget *WidgetPtr;		///< A pointer of IWidget interface object to delete.
	MAE_Ret ret;		/// the return value
}WdgContainer_WdgDelete_t;

typedef struct
{
    IWidget *WidgetPtr;			///< A pointer of IWidget interface object to be moved.
    IWidget *RefWidgetPtr;		///< A pointer of IWidget interface object to be reference.
	boolean isBefore;				/** A boolean, TRUE is moving the widget to the above of referred widget, 
	                                             *   FALSE is moving the widget to the below of referred widget. */
    MAE_Ret ret;						///< the return value
}WdgContainer_WdgMove_t;

typedef struct
{
    IWidget *RefWidgetPtr;		///< A pointer of IWidget interface object to be reference.
    boolean isBefore;				///<  A boolean flag, TRUE to search to top(of the stack), FALSE to search to bottom(of the stack).
    boolean isWrap;					///< A boolean flag, TRUE means to search to top/bottom when at bottom/top.
    IBase   *pOwner;				///< A pointer to a IBase object which will keep the returned widget.
    IWidget *GetWdgPtr;			///< Get a widget according to the parameters condition
}WdgContainer_WdgGet_t;

typedef struct 
{
	IWidget *WidgetPtr;		/// A pointer of widget instance object in this container.
	const Rect_t *pRc; /// A pointer of constant rectangle coordinated to the widget of pWidget.
	InvFlag_t nFlags;				/// A flag for invalidating.
}WdgContainer_WdgInvalidate_t;

typedef struct
{
    IWidget     *WidgetPtr;				///< A pointer of widget instance object in this container
    IContainer  **ppRoot;				///< A pointer of IContainer object pointer to retrieve the root-container.
    Rect_t      *RelativeRectPtr;		///<  A pointer of Rect_t to retrieve the position of pWidget coordinate to root-container.
    IBase       *pOwner;					///<  A pointer to a IBase object which will keep the returned root-container.
    MAE_Ret     ret;							///< the return value
}WdgContainer_WdgLocate_t;


/** ICONTAINER_QueryInterface
* @brief	This function queries another interface from IContainer object. 
*          It will return an interface object which you want to query if successful.
*
* @param[in]   IContainerPtr(IContainer*)   A pointer of IContainer interface object.
* @param[in]   iid(MAE_IId)            An interface id to be queried.
* @param[out]  ppObj(void**)           A pointer of void pointer to retrieve an interface object which you want to query.
* @param[in]   pOwner(IBase*)          Shall be an IBase interface object to keep the return object.
*
* @retval   MAE_RET_SUCCESS         Success.
* @retval   MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define ICONTAINER_QueryInterface(IContainerPtr,iid,ppObj,pOwner) \
	GET_FUNCTBL((IContainerPtr),IContainer)->QueryInterface(IContainerPtr,iid,ppObj,pOwner)
#else
__INLINE MAERet_t ICONTAINER_QueryInterface (IContainer *IContainerPtr, MAEIId_t iid , void** ppObj , IBase* pOwner)
{
	return GET_FUNCTBL((IContainerPtr),IContainer)->QueryInterface(IContainerPtr, iid, ppObj, pOwner);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** ICONTAINER_HandleEvent
* @brief	This function handles events which passed to this IContainer object.
*
* @param[in]	IContainerPtr(IContainer*)   A pointer of IContainer interface object.
* @param[in]	eid(MAE_EventId)             Event Id sent to the IHandler object.
* @param[in]	p1(u32)                      Parameter 1 of 32-bits specific data.
* @param[in]	p2(u32)                      Parameter 2 of 32-bits specific data.
*
* @retval	TRUE		The object handled this event.
* @retval	FALSE		The object did NOT handle this event.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define ICONTAINER_HandleEvent(IContainerPtr,eid,p1,p2) \
	GET_FUNCTBL((IContainerPtr),IContainer)->HandleEvent(IContainerPtr,eid,p1,p2)
#else
__INLINE boolean ICONTAINER_HandleEvent (IContainer *IContainerPtr, MAEEvent_t eid, u32 p1, u32 p2)
{
	return GET_FUNCTBL((IContainerPtr),IContainer)->HandleEvent(IContainerPtr,eid,p1,p2);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

/** ICONTAINER_SetHandler
* @brief	This function is used for an application which want to hook this IContainer object's handle event function.
*
* @param[in]        IContainerPtr(IContainer*)   A pointer of IContainer interface object.
* @param[in][out]   pWHD(WidgetHandler_t*)       A pointer of WidgetHandler_t sturcture. The input is the
*                                                hook event handler function of application. The output is 
*                                                the original event handler.
*
* @retval	None.
*
* @note	pWHD will retrieve the old handler after calling ICONTAINER_SetHandler(). If application wants
*			to pass event to old handler, call WHANDLER_CALL() with old handler sturcture.
*/
#ifndef __MAE_VENEERED_INTERFACE__
#define ICONTAINER_SetHandler(IContainerPtr,pWHD) \
	GET_FUNCTBL((IContainerPtr),IContainer)->SetHandler(IContainerPtr,pWHD)
#else
__INLINE void ICONTAINER_SetHandler (IContainer *IContainerPtr, WidgetHandler_t *pHD)
{
	GET_FUNCTBL((IContainerPtr),IContainer)->SetHandler(IContainerPtr,pHD);
}
#endif /* __MAE_VENEERED_INTERFACE__ */

#endif	//__MAE_CONTAINER_H__
/*=============================================================*/
// end of file
