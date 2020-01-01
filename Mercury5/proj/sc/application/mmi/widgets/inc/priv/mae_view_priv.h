/**
 * \file    mae_view_priv.h
 * \brief   The document describes the private data structure used in mae_view.c
 * \author  steve.lee@mstarsemi.com
 * @version $Id: mae_view_priv.h 19076 2008-12-24 08:38:38Z paul.ouyang $
 */
#ifndef __MAE_VIEWPRIV_H__
#define __MAE_VIEWPRIV_H__

#include "mmi_mae_view.h"

typedef enum
{
	PROP_VIEW_ACTIVE = 0x1000     ///< view active visible property
}ViewExtProperty_e;

// for PROP_VIEW_ACTIVE
typedef enum
{
	VIEW_DEACTIVE = 0x0000,
	VIEW_ACTIVE
}ViewActiveType_e;

typedef enum
{
	VIEW_MAIN_WGT = 0,
	VIEW_SK_WGT
}ViewWgtType_e;

typedef enum
{
	VIEW_OBJ_FIRST_WDG = 0,
	VIEW_OBJ_SK_MDL,
	
	VIEW_OBJ_TYPE_NUM
}ViewObjectType_e;

#define INHERIT_IViewExt(IName) \
	INHERIT_IView(IView); \
	MAE_Ret    (*SetWidget)(IView*, ViewWgtType_e, IWidget*); \
	MAE_Ret    (*AddWidget)(IView*, u16, IWidget*); \
	MAE_Ret    (*GetOBject)(IView*, u16, IBase**, IBase*); \
	MAE_Ret    (*Hide)(IView*); \
	MAE_Ret    (*Show)(IView*)
	
DEFINE_INTERFACE(IViewExt);

#define IVIEWEXT_SetWidget(pView,id,pWdg)           GET_FUNCTBL(pView,IViewExt)->SetWidget(pView,id,pWdg)
#define IVIEWEXT_AddWidget(pView,id,ppWdg)          GET_FUNCTBL(pView,IViewExt)->AddWidget(pView,id,ppWdg)
#define IVIEWEXT_GetFirstWidget(pView,ppWdg,pOwner)      GET_FUNCTBL(pView,IViewExt)->GetOBject(pView,VIEW_OBJ_FIRST_WDG,(IBase**)ppWdg,pOwner)
#define IVIEWEXT_GetSoftkeyModel(pView,ppMdl,pOwner)     GET_FUNCTBL(pView,IViewExt)->GetOBject(pView,VIEW_OBJ_SK_MDL,(IBase**)ppMdl,pOwner)

#define IVIEW_SetActive(pView,val)              GET_FUNCTBL(pView,IView)->SetProperty(pView,PROP_VIEW_ACTIVE,val)
#define IVIEW_GetActive(pView,pval)             GET_FUNCTBL(pView,IView)->GetProperty(pView,PROP_VIEW_ACTIVE,pval)

#define IVIEWEXT_Hide(pView)           GET_FUNCTBL(pView,IViewExt)->Hide(pView)
#define IVIEWEXT_Show(pView)           GET_FUNCTBL(pView,IViewExt)->Show(pView)

#endif /* __MAE_VIEWPRIV_H__ */
