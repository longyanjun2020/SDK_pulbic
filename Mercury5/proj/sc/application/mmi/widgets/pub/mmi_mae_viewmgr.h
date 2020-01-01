/**
 * @file mmi_mae_viewmgr.h
 *
 * TODO: Add desctiptions here
 * 
 * @version $Id: mmi_mae_viewmgr.h 2011-09-27$
 * @note: This file is from inc/mae_viewmgr.h and is renamed as
 *   pub/mmi_mae_viewmgr.h for becoming a public header. 
 */

#ifndef __MMI_MAE_VIEWMGR_H__
#define __MMI_MAE_VIEWMGR_H__

#include "mmi_mae_view.h"
#include "mmi_mae_event.h"
#include "mmi_mae_transition.h"
#include "mmi_wdg_group.h"

#define __SUPPORT_VIEW_STACK__

/* enum for ViewMgrProperty_t */
enum ViewMgrProperty_tag
{
	VIEWMGR_PROP_ACTIVEDISP = 0,
	VIEWMGR_PROP_DISPLAY,
	VIEWMGR_PROP_DISPMODE,         ///< display mode, DISPMODE_PORTRAIT or DISPMODE_LANDSCAPE. reference to mae_display.h
	VIEWMGR_PROP_BG_VIS,           ///< Visibility of background in ViewMgr
	VIEWMGR_PROP_BG_TYPE,          ///< Type of background in ViewMgr
	VIEWMGR_PROP_BG_COLOR,         ///< color of background in ViewMgr
	VIEWMGR_PROP_AP_ENTRY_TRANSITION_ID,    ///< the transition id to play when the very first view pushed/set to viewmgr.
	VIEWMGR_PROP_AP_EXIT_TRANSITION_ID,     ///< the transition id to play when the very first view pushed/set to viewmgr.
	VIEWMGR_PROP_DISABLE_AP_TRANSITION,
    VIEWMGR_PROP_DISPLAY_INVISIBLE,
	VIEWMGR_PROP_SK_LEFT_USER_ICON,
	VIEWMGR_PROP_SK_MIDDLE_USER_ICON,
	VIEWMGR_PROP_SK_RIGHT_USER_ICON,
	VIEWMGR_PROP_DISPLAY_BITMAP,
	VIEWMGR_PROP_THEMES_CHANGED,
	VIEWMGR_PROP_DISPMODE_FORCE_UPDATE
};
typedef u32 ViewMgrProperty_t;


//Jerry: move this to mae_view_defines.h
/*
// enum for ViewMgrBGVis_e
enum ViewMgrBGVis_tag
{
	VIEWMGR_BGVIS_VIS,
	VIEWMGR_BGVIS_INVIS,
	VIEWMGR_BGVIS_AUTOHIDE,

	VIEWMGR_BGVIS_SUM
};
typedef u32 ViewMgrBGVis_e;

// enum for ViewMgrBGTpye_e
enum ViewMgrBGTpye_tag
{
	VIEWMGR_BGTYPE_COLOR,
	VIEWMGR_BGTYPE_IMAGE_COLOR,

	VIEWMGR_BGTYPE_SUM
};
typedef u32 ViewMgrBGTpye_e;
*/

/* enum for ViewMgrTransitionSetting_t */
enum ViewMgrTransitionMode_tag
{
	VIEWMGR_TRANSITION_MODE_DISABLE,         ///< Disable transition
	VIEWMGR_TRANSITION_MODE_AUTO,            ///< Auto select pre view's exit  or new view's entry transition by comparing their scene level
	VIEWMGR_TRANSITION_MODE_FORCE_ENTRY,     ///< Force play new view's entry transition
	VIEWMGR_TRANSITION_MODE_FORCE_EXIT,      ///< Force play pre view's exit transition

	VIEWMGR_TRANSITION_MODE_SUM
};
typedef u32 ViewMgrTransitionMode_t;

enum ViewMgrPlayTransitionType_tag
{
	VIEWMGR_PLAYTRANS_ENTRY,         ///< play the top view's entry transition
	VIEWMGR_PLAYTRANS_EXIT,             ///< play the top view's exit transition
	VIEWMGR_PLAYTRANS_CUSTOM         ///< play transition in function param
};
typedef u32 ViewMgrPlayTransitionType_t;

///
/// IViewMgr interface
///
/// Although IViewMgr is derived from IHandler, it is not considered as an individual execution unit
/// as IApplet or IService. Its HandleEvent and SetHandler (which may be obsolete) methods are the
/// bridge between the applet and its widgets.
///
#ifdef __AP_USE_ML__
#define GET_INV_RECT_FUNC(IName) \
	boolean    (*GetInvalidateRect)(IName*, const MAE_DispId_t, Rect_t**)
#else
#define GET_INV_RECT_FUNC(IName) \
	boolean    (*GetInvalidateRect)(IName*, const MAE_DispId_t, Rect_t*)
#endif


#ifdef __SUPPORT_VIEW_STACK__
#define INHERIT_IViewMgr(IName) \
	INHERIT_IHandler(IName); \
	MAE_Ret (*SetHandler)(IName*, WidgetHandler_t*); \
	MAE_Ret    (*SetView)(IName*, const MAE_DispId_t, IView*, ViewMgrTransitionMode_t); \
	MAE_Ret    (*PushView)(IName*, const MAE_DispId_t, IView*, ViewMgrTransitionMode_t); \
	MAE_Ret    (*PopView)(IName*, const MAE_DispId_t, IView**, IBase*); \
	MAE_Ret    (*GetView)(IName*, const MAE_DispId_t, const u32, IView**, IBase*); \
	MAE_Ret    (*SetTopViewProp)(IName*, const MAE_DispId_t, u32, u32); \
	void       (*Draw)(IName*, const MAE_DispId_t, Rect_t*, boolean bTop); \
	boolean    (*IsFullOpaque)(IName*, const MAE_DispId_t); \
	GET_INV_RECT_FUNC(IName); \
	void       (*PlayTransition)(IName*, const MAE_DispId_t, ViewMgrPlayTransitionType_t, const u32, const ViewTransition_t*); \
	MAE_Ret    (*Hide)(IName*, const MAE_DispId_t); \
	MAE_Ret    (*Show)(IName*, const MAE_DispId_t)
#else
#define INHERIT_IViewMgr(IName) \
	INHERIT_IHandler(IName); \
	MAE_Ret (*SetHandler)(IName*, WidgetHandler_t*); \
	MAE_Ret    (*SetView)(IName*, const MAE_DispId_t, IView*, ViewMgrTransitionMode_t); \
	MAE_Ret    (*PopView)(IName*, const MAE_DispId_t, IView**, IBase*); \
	MAE_Ret    (*GetView)(IName*, const MAE_DispId_t, const u32, IView**, IBase*); \
	MAE_Ret    (*SetTopViewProp)(IName*, const MAE_DispId_t, u32, u32); \
	void       (*Draw)(IName*, const MAE_DispId_t, Rect_t*, boolean bTop); \
	boolean    (*IsFullOpaque)(IName*, const MAE_DispId_t); \
	GET_INV_RECT_FUNC(IName); \
	void       (*PlayTransition)(IName*, const MAE_DispId_t, ViewMgrPlayTransitionType_t, const u32, const ViewTransition_t*); \
	MAE_Ret    (*Hide)(IName*, const MAE_DispId_t); \
	MAE_Ret    (*Show)(IName*, const MAE_DispId_t)
#endif

DEFINE_INTERFACE(IViewMgr);

#define IVIEWMGR_QueryInterface(pMgr,iid,ppObj,pOwner)    GET_FUNCTBL(pMgr,IViewMgr)->QueryInterface(pMgr,iid,ppObj,pOwner)
#define IVIEWMGR_SetHandler(pMgr,p2)                GET_FUNCTBL(pMgr,IViewMgr)->SetHandler(pMgr,p2)
#define IVIEWMGR_HandleEvent(pMgr,t1,c1,c2)         GET_FUNCTBL(pMgr,IViewMgr)->HandleEvent(pMgr,t1,c1,c2)

/** IVIEWMGR_SetView, IVIEWMGR_SetViewEx
* @brief		To set view to view manager
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
* @param[in]	pView(IView*)  IView to be set to view manager
* @param[in]	mode(ViewMgrTransitionMode_t)  Transition mode (IVIEWMGR_SetViewEx only)
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
* @note This function will auto pop previous view(s) if the view type of pView is
*           VT_NORMA, VT_OSD_NORMAL, VT_FULL_SCRN, or VT_OSD_FULL_SCRN.
*
*/
#define IVIEWMGR_SetView(pMgr,DispId,pView)           GET_FUNCTBL(pMgr,IViewMgr)->SetView(pMgr,DispId,pView,VIEWMGR_TRANSITION_MODE_AUTO)
#define IVIEWMGR_SetViewEx(pMgr,DispId,pView,mode)           GET_FUNCTBL(pMgr,IViewMgr)->SetView(pMgr,DispId,pView,mode)

#ifdef __SUPPORT_VIEW_STACK__
/** IVIEWMGR_PushView, IVIEWMGR_PushViewEx
* @brief		To push view to view manager
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
* @param[in]	pView(IView*)  IView to be pushed to view manager
* @param[in]	mode(ViewMgrTransitionMode_t)  Transition mode (IVIEWMGR_PushViewEx only)
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
*/
#define IVIEWMGR_PushView(pMgr,DispId,pView)          GET_FUNCTBL(pMgr,IViewMgr)->PushView(pMgr,DispId,pView,VIEWMGR_TRANSITION_MODE_FORCE_ENTRY)
#define IVIEWMGR_PushViewEx(pMgr,DispId,pView,mode)          GET_FUNCTBL(pMgr,IViewMgr)->PushView(pMgr,DispId,pView,mode)
#endif

/** IVIEWMGR_PopView
* @brief		To pop the toppest view
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
* @param[out]	ppView(IView**)  The poped view will be store in this pointer. If you don't need it anymore, just pass NULL.
* @param[in]	pOwner(IBase*)  The caller instance
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
* @note If ppView is not NULL, the poped view will be store in *ppView and its reference count will be +1 for pOwner.
*
*/
#define IVIEWMGR_PopView(pMgr,DispId,ppView,pOwner)   GET_FUNCTBL(pMgr,IViewMgr)->PopView(pMgr,DispId,ppView,pOwner)

/** IVIEWMGR_GetView
* @brief		To get view with the given id from view manager
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
* @param[in]	id(const u32)  The specific view id.
* @param[out]	ppView(IView**)  The found view will be store in this pointer
* @param[in]	pOwner(IBase*)  The caller instance
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
* @note The reference count of output IView will be +1 for pOwner.
*
*/
#define IVIEWMGR_GetView(pMgr,DispId,id,ppView,pOwner)      GET_FUNCTBL(pMgr,IViewMgr)->GetView(pMgr,DispId,id,ppView,pOwner)
//#define IVIEWMGR_SetTopViewProp(pVierMgr,DispId,id,val)   GET_FUNCTBL(pMgr,IViewMgr)->SetTopViewProp(pMgr,DispId,id,val)

/** IVIEWMGR_GetTopView
* @brief		To get the toppest view from view manager
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
* @param[out]	ppView(IView**)  The found view will be store in this pointer
* @param[in]	pOwner(IBase*)  The caller instance
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
* @note The reference count of output IView will be +1 for pOwner.
*
*/
#define IVIEWMGR_GetTopView(pMgr,DispId,ppView,pOwner)      GET_FUNCTBL(pMgr,IViewMgr)->GetView(pMgr,DispId,VIEWID_TOPVIEW,ppView,pOwner)

/** IVIEWMGR_SetTopViewSBVisible
* @brief		To set the visibility of statusbar of the toppest view
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
* @param[in]	val(ViewSBVisType_t)  New visibility of statusbar.
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
*/
#define IVIEWMGR_SetTopViewSBVisible(pMgr,DispId,val) GET_FUNCTBL(pMgr,IViewMgr)->SetTopViewProp(pMgr,DispId,PROP_VIEW_SB_VISIBLE,val)

/** IVIEWMGR_SetTopViewSKVisible
* @brief		To set the visibility of softkey of the toppest view
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
* @param[in]	val(ViewSKVisType_t)  New visibility of softkey.
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
*/
#define IVIEWMGR_SetTopViewSKVisible(pMgr,DispId,val) GET_FUNCTBL(pMgr,IViewMgr)->SetTopViewProp(pMgr,DispId,PROP_VIEW_SK_VISIBLE,val)

/** IVIEWMGR_SetTopViewGPVisible
* @brief        To set the visibility of group of the toppest view
*
* @param[in]    pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]    DispId(const MAE_DispId_t)  The specific display id.
* @param[in]    val(ViewSBVisType_t)  New visibility of group.
*
* @retval   MAE_RET_SUCCESS       Success.
* @retval   others      Failed.
*
*/
#define IVIEWMGR_SetTopViewGPVisible(pMgr,DispId,val) GET_FUNCTBL(pMgr,IViewMgr)->SetTopViewProp(pMgr,DispId,PROP_VIEW_GP_VISIBLE,val)

/** IVIEWMGR_SetTopViewSBSKTransparency
* @brief		To set the background transparent setting of statusbar and softkey of the toppest view
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
* @param[in]	val(ViewTranspType_t)  New transparent setting of softkey/statusbar background.
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
*/

#define IVIEWMGR_SetTopViewSBSKTransparency(pMgr,DispId,val) GET_FUNCTBL(pMgr,IViewMgr)->SetTopViewProp(pMgr,DispId,PROP_VIEW_SBSK_TRANSP,val)

/** IVIEWMGR_Hide
* @brief		To inform viewmgr that it will not be drawn. It can try to release some resource like preload images.
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
*/
#define IVIEWMGR_Hide(pMgr, DispId)    GET_FUNCTBL(pMgr,IViewMgr)->IVIEWMGR_UnloadViews(pMgr,DispId)

/** IVIEWMGR_Show
* @brief		To inform viewmgr that it will be drawn soon. It should restore the released resource by IVIEWMGR_Hide()
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	DispId(const MAE_DispId_t)  The specific display id.
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
*/
#define IVIEWMGR_Show(pMgr, DispId)    GET_FUNCTBL(pMgr,IViewMgr)->IVIEWMGR_ReloadViews(pMgr,DispId)

/** IVIEWMGR_SetProperty
* @brief		To set property to view manager
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	PropId(ViewMgrProperty_t)  The specific property id.
* @param[in]	Value(u32)  New value of PropId
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
* @note New property will affect current active display only
*/
__INLINE MAE_Ret IVIEWMGR_SetProperty(IViewMgr *pViewMgr, ViewMgrProperty_t PropId, u32 Value)
{
	if(IVIEWMGR_HandleEvent(pViewMgr, MAE_EVT_SET_PROPERTY, PropId, Value) == TRUE)
		return MAE_RET_SUCCESS;
	return MAE_RET_FAILED;
}

/** IVIEWMGR_GetProperty
* @brief		To get property from view manager
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	PropId(ViewMgrProperty_t)  The specific property id.
* @param[in]	pValue(u32*)  To store value of PropId
*
* @retval	MAE_RET_SUCCESS       Success.
* @retval	others      Failed.
*
* @note The function gets the property value of current active display
*/
__INLINE MAE_Ret IVIEWMGR_GetProperty(IViewMgr *pViewMgr, ViewMgrProperty_t PropId, u32 *pValue)
{
	if(IVIEWMGR_HandleEvent(pViewMgr, MAE_EVT_GET_PROPERTY, PropId, (u32)pValue) == TRUE)
		return MAE_RET_SUCCESS;
	return MAE_RET_FAILED;
}

/** IVIEWMGR_Draw
* @brief		This function will make the specific IViewMgr object to update the screen.
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	id(const MAE_DispId_t)  Display Id. To indicate which display to draw. Support Main-display or Sub-display now.
* @param[in]	pRc(Rect_t*)            A pointer of Rect_t, which is needed to draw.
* @param[in]	bT(boolean)             A boolean value to indicate if this is a top applet.
*
* @retval	None
*/
#define IVIEWMGR_Draw(pMgr,id,pRc,bT) \
	GET_FUNCTBL(pMgr,IViewMgr)->Draw(pMgr,id,pRc,bT)

/** IVIEWMGR_IsFullOpaque
* @brief		This function can get the status the specific IViewMgr object if the screen is full opaque by itself.
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	id(const MAE_DispId_t)  Display Id. To specify which display is full opaque.
*
* @retval	TRUE       The screen is opaqued by the object is view manager.
* @retval	FALSE      The screen is not opaqued by the object is view manager.
*/
#define IVIEWMGR_IsFullOpaque(pMgr,id) \
	GET_FUNCTBL(pMgr,IViewMgr)->IsFullOpaque(pMgr,id)

/** IVIEWMGR_GetInvalidateRect
* @brief		To get the dirty region from view manager by the specific display id.
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	id(const MAE_DispId_t)  The specific display id.
* @param[out]	pRc(Rect_t*)            A pointer of Rect_t, which is the output of dirty region.
*
* @retval	TRUE       There is dirty region.
* @retval	FALSE      There is no dirty region.
*/
#define IVIEWMGR_GetInvalidateRect(pMgr,id,pRc) \
	GET_FUNCTBL(pMgr,IViewMgr)->GetInvalidateRect(pMgr,id,pRc)

/** IVIEWMGR_PlayTransitionByID
* @brief		To play exit transition of top view
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	id(const MAE_DispId_t)  The specific display id.
* @param[in]	transID(const u32)  The specific transition id.
*
*/
#define IVIEWMGR_PlayTransitionByID(pMgr, id, transID) 	GET_FUNCTBL(pMgr,IViewMgr)->PlayTransition(pMgr,id, VIEWMGR_PLAYTRANS_CUSTOM,transID,0)

/** IVIEWMGR_PlayTransitionByData
* @brief		To play exit transition of top view
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	id(const MAE_DispId_t)  The specific display id.
* @param[in]	pData(const ViewTransition_t*)  A pointer of transition structure.
*
*/
#define IVIEWMGR_PlayTransitionByData(pMgr, id, pData) 	GET_FUNCTBL(pMgr,IViewMgr)->PlayTransition(pMgr,id, VIEWMGR_PLAYTRANS_CUSTOM,VIEWTRANSITION_ID_NONE,pData)

/** IVIEWMGR_SetAPEntryTransitionID
* @brief		To set transition ID to play when the very first IView is set
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	transID(u32)  The transition ID.
*
*/
#define IVIEWMGR_SetAPEntryTransitionID(pMgr, transID)    IVIEWMGR_SetProperty(pMgr, VIEWMGR_PROP_AP_ENTRY_TRANSITION_ID, transID)

/** IVIEWMGR_SetAPExitTransitionID
* @brief		To set transition id to play when AP exit
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	transID(u32)  The transition ID.
*
*/
#define IVIEWMGR_SetAPExitTransitionID(pMgr, transID)    IVIEWMGR_SetProperty(pMgr, VIEWMGR_PROP_AP_EXIT_TRANSITION_ID, transID)

#ifdef __AP_USE_ML__
/** IVIEWMGR_SetLayerOffset
* @brief		Set the offset of specified layer, only works if the Top View of Mgr use ML and ML buffer created, and will cause Screen Update
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	nLayer				the specified layer
* @param[in]   (x, y)				the offset
*
* @retval	MAE_RET_SUCCESS       successfully set offset and update screen
* @retval	MAE_RET_BAD_PARAM		pMgr is NULL or nLayer is illegal
* @retval  MAE_RET_FAILED			if top view isn't ML or buffer not created
*/
MAE_Ret IVIEWMGR_SetLayerOffset(IViewMgr *pMgr, DisplayLayer_e nLayer, u32 x, u32 y);

/** IVIEWMGR_SetLayerVisible
* @brief		Set the visibility of specified layer, only works if the Top View of Mgr use ML and ML buffer created, and will cause Screen Update
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]	nLayer				the specified layer
* @param[in]   bvisible				the layer visibility
*
* @retval	MAE_RET_SUCCESS       successfully set offset and update screen
* @retval	MAE_RET_BAD_PARAM		pMgr is NULL or nLayer is illegal
* @retval  MAE_RET_FAILED			if top view isn't ML or buffer not created
*/
MAE_Ret IVIEWMGR_SetLayerVisible(IViewMgr *pMgr, DisplayLayer_e nLayer, boolean bVisible);
#endif

/** IVIEWMGR_SetGroupAP
* @brief		Set the current AP of group
*
* @param[in]	pMgr(IViewMgr*)         A pointer of IViewMgr object.
* @param[in]   nCurrAppType	      current AP type
*
* @retval	MAE_RET_SUCCESS            successfully set current AP
*/

MAE_Ret IVIEWMGR_SetGroupAP(IViewMgr *pMgr, GROUP_APPLET_TYPE nCurrAppType);


#endif // __MMI_MAE_VIEWMGR_H__
