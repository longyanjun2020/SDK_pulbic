/**
 * @file mmi_mae_view.h
 *
 * IVIEW interface
 *
 * @version $Id: mmi_mae_view.h 38890 2009-08-29 16:22:38Z zinc.chen $
 */
#ifndef __MMI_MAE_VIEW_H__
#define __MMI_MAE_VIEW_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_retcode.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_view_defines.h"

///
/// IView interface
///
#ifdef __AP_USE_ML__
#define INHERIT_IView(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret    (*SetProperty)(IName*, u32, u32); \
	MAE_Ret    (*GetProperty)(IName*, u32, u32*); \
	MAE_Ret    (*GetWidget)(IName*, u16, IWidget**, IBase*); \
	MAE_Ret    (*SetSoftkey)(IName*, u16, u32); \
	MAE_Ret    (*GetSoftkey)(IName*, u16, u32*); \
	MAE_Ret	 (*SetLayerInfo)(IName*, LayerCreateInfo_t*, DisplayLayer_e); \
	MAE_Ret	 (*GetLayerInfo)(IName*, LayerCreateInfo_t**, DisplayLayer_e); \
	u8	(*IsUseML)(IName*); \
	MAE_Ret	(*SetTranspBGbyInfo)(IName*); \
	MAE_Ret	(*DisableTranspBG)(IName*)
//    MAE_Ret    (*GetMainWidget)(IName*, IWidget*) 
#else
#define INHERIT_IView(IName) \
	INHERIT_IBase(IName); \
	MAE_Ret    (*SetProperty)(IName*, u32, u32); \
	MAE_Ret    (*GetProperty)(IName*, u32, u32*); \
	MAE_Ret    (*GetWidget)(IName*, u16, IWidget**, IBase*); \
	MAE_Ret    (*SetSoftkey)(IName*, u16, u32); \
	MAE_Ret    (*GetSoftkey)(IName*, u16, u32*)
//    MAE_Ret    (*GetMainWidget)(IName*, IWidget*) 
#endif

DEFINE_INTERFACE(IView);

#define IVIEW_QueryInterface(p1,c1,p2,pOwner)      GET_FUNCTBL(p1,IView)->QueryInterface(p1,c1,p2,pOwner)

/** 
 *  IVIEW_SetProperty(IView *pView, u32 id, u32 val)
 *
 *  @brief  This function sets property to the given view
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  id              Property ID
 *  @param  val             New value of the given proerty
 *
 *  @retval MAE_RET_SUCCESS         Success
 *  @retval MAE_RET_NOT_SUPPORTED   Property ID is not supported
 *  @retval MAE_RET_BAD_PARAM       pView is NULL
 */
#define IVIEW_SetProperty(pView,id,val)         GET_FUNCTBL(pView,IView)->SetProperty(pView,id,val)

/** 
 *  IVIEW_GetProperty(IView *pView, u32 id, u32 *pVal)
 *
 *  @brief  This function sets property to the given view
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  id              Property ID
 *  @param  pVal            Pointer to the memory to store property
 *
 *  @retval MAE_RET_SUCCESS         Success
 *  @retval MAE_RET_NOT_SUPPORTED   Property ID is not supported
 *  @retval MAE_RET_BAD_PARAM       pView or pVal is NULL
 */
#define IVIEW_GetProperty(pView,id,pVal)         GET_FUNCTBL(pView,IView)->GetProperty(pView,id,pVal)

/** 
 *  IVIEW_GetWidget(IView *pView, u16 id, IWidget **ppWgt, IBase *pOwner)
 *
 *  @brief  This function gets the widget with the given ID
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  id              Widget ID in the given view
 *  @param  ppWgt           Pointer to widget pointer to store the found widget
 *  @param  pOwner          Instance of the object who uses this interface, for reference check.
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_NOT_FOUND   Widget of the given id is not found
 *  @retval MAE_RET_BAD_PARAM   Anyone of pView, ppWgt, and pOwner is NULL
 *
 *  @note If the return value is MAE_RET_SUCCESS, *ppWgt is guaranteed not NULL
 */
#define IVIEW_GetWidget(pView,id,ppWgt,pOwner)        GET_FUNCTBL(pView,IView)->GetWidget(pView,id,ppWgt,pOwner)

/** 
 *  IVIEW_SetSoftkey(IView *pView, u16 skType, u32 id)
 *
 *  @brief  This function sets softkey value if the view
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  skType          Softkey type (Softkey_Type)
 *  @param  id              Softkey ID (predefined ID)
 *
 *  @retval MAE_RET_SUCCESS         Success
 *  @retval MAE_RET_BAD_PARAM       pView is NULL or skType is illegal
 */
#define IVIEW_SetSoftkey(pView,skType,id)          GET_FUNCTBL(pView,IView)->SetSoftkey(pView,skType,id)

/** 
 *  IVIEW_GetSoftkey(IView *pView, u16 skType, u32 *pId)
 *
 *  @brief  This function sets softkey value if the view
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  skType          Softkey type (Softkey_Type)
 *  @param  pId             Pointer to the memory to store softkey id
 *
 *  @retval MAE_RET_SUCCESS         Success
 *  @retval MAE_RET_BAD_PARAM       pView or pId is NULL, or skType is illegal
 */
#define IVIEW_GetSoftkey(pView,skType,pId)          GET_FUNCTBL(pView,IView)->GetSoftkey(pView,skType,pId)

#define IVIEW_SetViewType(p1,c1)            GET_FUNCTBL(p1,IView)->SetProperty(p1,PROP_VIEWTYPE,c1)
#define IVIEW_GetViewType(p1,p2)            GET_FUNCTBL(p1,IView)->GetProperty(p1,PROP_VIEWTYPE,p2)
#define IVIEW_SetViewID(p1,c1)              GET_FUNCTBL(p1,IView)->SetProperty(p1,PROP_VIEWID,c1)
#define IVIEW_GetViewID(p1,p2)              GET_FUNCTBL(p1,IView)->GetProperty(p1,PROP_VIEWID,p2)

/** 
 *  IVIEW_SetSBVisible(IView *pView, ViewSBVisType_e eVisible)
 *
 *  @brief  This function sets the given view's statusbar visible state.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  eVisible        VIEWSB_INVISIABLE/VIEWSB_VISIABLE
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_NOT_SUPPORTED  The given view is not a Non-Fadeout view
 *
 *  Note: (1) Only Non-Fadeout view can support this function
 *        (2) Only works when the pView is not set to ViewManager yet
 *            Once the view is set to ViewManager, IVIEWMGR_SetTopViewProp should be
 *            used instead.
 */
#define IVIEW_SetSBVisible(pView,eVisible)           GET_FUNCTBL(pView,IView)->SetProperty(pView,PROP_VIEW_SB_VISIBLE,eVisible)

/** 
 *  IVIEW_GetSBVisible(IView *pView, ViewSBVisType_e *peVisible)
 *
 *  @brief  This function gets the given view's statusbar visible state.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  peVisible       Pointer to the memory to store visible state
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_NOT_SUPPORTED  The given view is not a Non-Fadeout view
 *
 *  Note: Only Non-Fadeout view can support this function
 */
#define IVIEW_GetSBVisible(pView,peVisible)           GET_FUNCTBL(pView,IView)->GetProperty(pView,PROP_VIEW_SB_VISIBLE,peVisible)

/** 
 *  IVIEW_SetSKVisible(IView *pView, ViewSKVisType_e eVisible)
 *
 *  @brief  This function sets the given view's softkey visible state.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  eVisible        VIEWSK_INVISIABLE/VIEWSK_VISIABLE
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_NOT_SUPPORTED  The given view is not a Non-Fadeout view
 *
 *  Note: (1) Only Non-Fadeout view can support this function
 *        (2) Only works when the pView is not set to ViewManager yet.
 *            Once the view is set to ViewManager, IVIEWMGR_SetTopViewProp should be
 *            used instead.
 */
#define IVIEW_SetSKVisible(pView,eVisible)           GET_FUNCTBL(pView,IView)->SetProperty(pView,PROP_VIEW_SK_VISIBLE,eVisible)

/** 
 *  IVIEW_GetSKVisible(IView *pView, ViewSKVisType_e *peVisible)
 *
 *  @brief  This function gets the given view's softkey visible state.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  peVisible       Pointer to the memory to store visible state
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_NOT_SUPPORTED  The given view is not a Non-Fadeout view
 *
 *  Note: Only Non-Fadeout view can support this function
 */
#define IVIEW_GetSKVisible(pView,peVisible)           GET_FUNCTBL(pView,IView)->GetProperty(pView,PROP_VIEW_SK_VISIBLE,peVisible)

/** 
 *  IVIEW_SetGPVisible(IView *pView, ViewSKVisType_e eVisible)
 *
 *  @brief  This function sets the given view's group visible state.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  eVisible        VIEWGP_INVISIABLE/VIEWGP_VISIABLE
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_NOT_SUPPORTED  The given view is not a Non-Fadeout view
 *
 *  Note: (1) Only Non-Fadeout view can support this function
 *        (2) Only works when the pView is not set to ViewManager yet.
 *            Once the view is set to ViewManager, IVIEWMGR_SetTopViewProp should be
 *            used instead.
 */
#define IVIEW_SetGPVisible(pView,eVisible)           GET_FUNCTBL(pView,IView)->SetProperty(pView,PROP_VIEW_GP_VISIBLE,eVisible)

/** 
 *  IVIEW_GetGPVisible(IView *pView, ViewSKVisType_e *peVisible)
 *
 *  @brief  This function gets the given view's group visible state.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  peVisible       Pointer to the memory to store visible state
 *
 *  @retval MAE_RET_SUCCESS     Success
 *  @retval MAE_RET_NOT_SUPPORTED  The given view is not a Non-Fadeout view
 *
 *  Note: Only Non-Fadeout view can support this function
 */
#define IVIEW_GetGPVisible(pView,peVisible)           GET_FUNCTBL(pView,IView)->GetProperty(pView,PROP_VIEW_GP_VISIBLE,peVisible)

/** 
 *  IVIEW_SetGPTransparency(IView *pView, boolean bTransp)
 *
 *  @brief  This function sets the transparency of status bar in the view.
 *          Transparency here means the background images' visibility of status bar.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  bTransp         TRUE/FALSE
 *
 *  @retval MAE_RET_SUCCESS     Success
 *
 *  Note: Only works when the pView is not set to ViewManager yet.
 *        Once the view is set to ViewManager, IVIEWMGR_SetTopViewProp should be
 *        used instead.
 */
#define IVIEW_SetGPTransparency(pView,bTransp)           GET_FUNCTBL(pView,IView)->SetProperty(pView,PROP_VIEW_GP_TRANSP,bTransp)

/** 
 *  IVIEW_GetGPTransparency(IView *pView, boolean *pbTransp)
 *
 *  @brief  This function gets the transparency of status bar in the view.
 *          Transparency here means the background images' visibility of status bar.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  pbTransp        Pointer to the memory to store transparency state
 *
 *  @retval MAE_RET_SUCCESS     Success
 */
#define IVIEW_GetGPTransparency(pView,pbTransp)           GET_FUNCTBL(pView,IView)->GetProperty(pView,PROP_VIEW_GP_TRANSP,pbTransp)


/** 
 *  IVIEW_SetSBTransparency(IView *pView, boolean bTransp)
 *
 *  @brief  This function sets the transparency of status bar in the view.
 *          Transparency here means the background images' visibility of status bar.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  bTransp         TRUE/FALSE
 *
 *  @retval MAE_RET_SUCCESS     Success
 *
 *  Note: Only works when the pView is not set to ViewManager yet.
 *        Once the view is set to ViewManager, IVIEWMGR_SetTopViewProp should be
 *        used instead.
 */
#define IVIEW_SetSBTransparency(pView,bTransp)           GET_FUNCTBL(pView,IView)->SetProperty(pView,PROP_VIEW_SB_TRANSP,bTransp)

/** 
 *  IVIEW_GetSBTransparency(IView *pView, boolean *pbTransp)
 *
 *  @brief  This function gets the transparency of status bar in the view.
 *          Transparency here means the background images' visibility of status bar.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  pbTransp        Pointer to the memory to store transparency state
 *
 *  @retval MAE_RET_SUCCESS     Success
 */
#define IVIEW_GetSBTransparency(pView,pbTransp)           GET_FUNCTBL(pView,IView)->GetProperty(pView,PROP_VIEW_SB_TRANSP,pbTransp)

/** 
 *  IVIEW_SetSKTransparency(IView *pView, boolean bTransp)
 *
 *  @brief  This function sets the transparency of softkey in the view.
 *          Transparency here means the background images' visibility of softkey.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  bTransp         TRUE/FALSE
 *
 *  @retval MAE_RET_SUCCESS     Success
 *
 *  Note: Only works when the pView is not set to ViewManager yet.
 *        Once the view is set to ViewManager, IVIEWMGR_SetTopViewProp should be
 *        used instead.
 */
#define IVIEW_SetSKTransparency(pView,bTransp)           GET_FUNCTBL(pView,IView)->SetProperty(pView,PROP_VIEW_SK_TRANSP,bTransp)

/** 
 *  IVIEW_GetSKTransparency(IView *pView, boolean *pbTransp)
 *
 *  @brief  This function gets the transparency of softkey in the view.
 *          Transparency here means the background images' visibility of softkey.
 *   
 *  @param  pView           Pointer to the IView Object
 *  @param  pbTransp        Pointer to the memory to store transparency state
 *
 *  @retval MAE_RET_SUCCESS     Success
 */
#define IVIEW_GetSKTransparency(pView,pbTransp)           GET_FUNCTBL(pView,IView)->GetProperty(pView,PROP_VIEW_SK_TRANSP,pbTransp)

/** 
 * IVIEW_GetWidgetList(IView *pView, void **ppWdgList) 
 *
 * @brief  This function gets the widget list of the IView
 *
 * @param  [in]pView           Pointer to the IView Object
 * @param  [in]ppWdgList       Pointer to store the pointer of widget list
 *
 * @retval	MAE_RET_SUCCESS    Success
 * @retval  MAE_RET_BAD_PARAM  pView is NULL or ppWdgList is NULL
 *
 * @note   The widget list only list the widget with ID in VDF
 */
 #define IVIEW_GetWidgetList(pView,ppWdgList)  GET_FUNCTBL(pView,IView)->GetProperty(pView,PROP_VIEW_WIDGET_LIST,(u32*)ppWdgList)

#ifdef __VIEW_TRANSITION__
/** 
 * MAE_View_CreateTransitionData
 *
 * @brief		Help user to allocate memory for transition data.
 *
 * @param[in]	nRegions(u32)         Number of regions of the transition.
 *
 * @retval	NULL       nRegions is 0 or memory is not enough
 * @retval others     Address of allocated memory
 */
ViewTransition_t* MAE_View_CreateTransitionData(u32 nRegions);

/** 
 * MAE_View_DeleteTransitionData
 *
 * @brief		Help user to destroy the transition data created by MAE_ViewMgr_CreateTransitionParam()
 *
 * @param[in]	pParam(ViewTransition_t*)         Transition parameter pointer created by MAE_ViewMgr_CreateTransitionParam()
 */
void MAE_View_DeleteTransitionData(ViewTransition_t *pData);
#endif
/** 
 * ViewGetMainWidget
 *
 * @brief		Help user to get the mainwdg of view, It's a hide abscontainer named BaseContainer
 *
 * @param  [in]pView           Pointer to the IView Object
 * @param  [out]pWgt    Pointer to a IWidget object pointer
  *
 * @retval MAE_RET_SUCCESS     Success
 * @retval others              Failed
 */
#ifdef __AP_USE_ML__
MAE_Ret ViewGetMainWidget(IView *pView, IWidget **pWgt, IBase *pOwner, DisplayLayer_e nLayer);
#else
MAE_Ret ViewGetMainWidget(IView *pView, IWidget **pWgt);
#endif

#ifdef __AP_USE_ML__
/** 
 * ViewSetMainWidget
 *
 * @brief		Help user to set the mainwdg of view, It's a hide abscontainer named BaseContainer
 *
 * @param  [in]pView           Pointer to the IView Object
 * @param  [in]pWgt    Pointer to a IWidget object pointer
 *
 * @retval MAE_RET_SUCCESS     Success
 * @retval others              Failed
 */
MAE_Ret ViewSetMainWidget(IView *pView, IWidget *pWgt, DisplayLayer_e nLayer);
#endif

/** ViewCheckWidget
* @brief        check a widget is in the view or not
*
* @param[in]    pView	Pointer to the IView Object
* @param[in]    nId		widget ID
*
* @retval       TRUE	the widget in the view
* @retval       FALSE   the widget do not contain in the view
*/
boolean ViewCheckWidget(IView *pView, u32 id);

/** ViewRemoveWidget
* @brief        Remove widget from view list
*
* @param[in]    pView	Pointer to the IView Object
* @param[in]    pWgt	widget point
*
* @retval       TRUE	the widget in the view
* @retval       FALSE   the widget do not contain in the view
*/
boolean ViewRemoveWidget(IView *pView, IWidget *pWgt);


#ifdef __AP_USE_ML__
/** 
*  IVIEW_SetLayerInfo(IView *pView, LayerCreateInfo_t* pInfo, DisplayLayer_e nLayer)
*
*  @brief  This function sets used layer size information.
*   
*  @param  pView           Pointer to the IView Object
*  @param  pInfo			 the layer size and position (x, y, w, h)
*  @param  nLayer			the used layer
*
*  @retval MAE_RET_SUCCESS         Success
*  @retval MAE_RET_BAD_PARAM       pView is NULL or pInfo is NULL or nLayer is illegal
*/
#define IVIEW_SetLayerInfo(pView,pInfo,nLayer)          GET_FUNCTBL(pView,IView)->SetLayerInfo(pView, pInfo, nLayer)
/** 
*  IVIEW_GetLayerInfo(IView *pView, LayerCreateInfo_t** ppInfo, DisplayLayer_e nLayer)
*
*  @brief  This function sets used layer size information.
*   
*  @param  pView           Pointer to the IView Object
*  @param  ppInfo			 the layer size and position (x, y, w, h)
*  @param  nLayer			the used layer
*
*  @retval MAE_RET_SUCCESS         Success
*  @retval MAE_RET_BAD_PARAM       pView is NULL or nLayer is illegal
*/
#define IVIEW_GetLayerInfo(pView,pInfo,nLayer)          GET_FUNCTBL(pView,IView)->GetLayerInfo(pView, pInfo, nLayer)
/** 
*  IVIEW_IsUseML(IView *pView)
*
*  @brief  This function return if the view use multi layer
*   
*  @param  pView           Pointer to the IView Object
*  @retval TRUE         use ML
*  @retval FALSE       not USE ML
*/
#define IVIEW_IsUseML(pView)	GET_FUNCTBL(pView, IView)->IsUseML(pView)

/** 
*  IVIEW_SetTranspBGbyInfo(IView *pView)
*
*  @brief  This function sets the flag that if need draw transparent BG, by layer info
*   
*  @param  pView           Pointer to the IView Object
*
*  @retval MAE_RET_SUCCESS         Success
*  @retval MAE_RET_BAD_PARAM       pView is NULL or nLayer is illegal
*/
#define IVIEW_SetTranspBGbyInfo(pView)          GET_FUNCTBL(pView,IView)->SetTranspBGbyInfo(pView)

/** 
*  IVIEW_SetTranspBGbyInfo(IView *pView)
*
*  @brief  This function sets the flag that if need draw transparent BG to FALSE, used when can't draw on ML
*   
*  @param  pView           Pointer to the IView Object
*
*  @retval MAE_RET_SUCCESS         Success
*  @retval MAE_RET_BAD_PARAM       pView is NULL or nLayer is illegal
*/
#define IVIEW_DisableTranspBG(pView)          GET_FUNCTBL(pView,IView)->DisableTranspBG(pView)

#endif

#endif /* __MAE_VIEW_H__ */
