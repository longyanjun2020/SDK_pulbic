/**
 * @file    mmi_mae_view_defines.h
 * @brief   The document describes the enumerations used in IView
 * @author  steve.lee@mstarsemi.com
 * @version $Id: mmi_mae_view_defines.h 32753 2009-06-05 17:09:37Z steve.lee $
 */
#ifndef __MMI_MAE_VIEW_DEFINES_H__
#define __MMI_MAE_VIEW_DEFINES_H__

#include "mmi_mae_transition.h"

/* enum for Predefined_ViewId_t */
enum Predefined_ViewId_tag
{
	VIEWID_TOPVIEW = 0x0000,
	
	NUM_PREDF_VIEWID
};
typedef u16 Predefined_ViewId_t;

/* enum for ViewProperty_t */
enum ViewProperty_tag
{
	//PROP_VIEWTITLEWDG = 0x0100, ///< deprecated

	PROP_VIEWID = 0x0001,
	PROP_VIEWTYPE,
	PROP_VIEWDISPMODE,
	PROP_VIEW_SB_VISIBLE,     ///< statusbar widget visible property
	PROP_VIEW_SK_VISIBLE,     ///< softkey widget visible property
	PROP_VIEW_SB_TRANSP,      ///< Transparency of backgrounds of statusbar
	PROP_VIEW_SK_TRANSP,      ///< Transparency of backgrounds of softkey
	PROP_VIEW_DISP_FROMTOP,   ///< set main widget's start position the same position as statusbar widget's
	PROP_VIEWTITLE_WDGID,
	PROP_VIEW_ENTRY_TRANSITION_ID,
	PROP_VIEW_ENTRY_TRANSITION_DATA,
	PROP_VIEW_EXIT_TRANSITION_ID,
	PROP_VIEW_EXIT_TRANSITION_DATA,
	PROP_VIEW_SCENE_LEVEL,	
	PROP_VIEW_GP_VISIBLE,     ///< group widget visible property
	PROP_VIEW_GP_TRANSP,      ///< Transparency of backgrounds of group widget
	PROP_VIEW_WIDGET_LIST
};
typedef u16 ViewProperty_t;

/* enum for ViewType_t */
enum ViewType_tag
{
	VT_START = 0x0000, 

	VT_NORMAL = VT_START,
	VT_OSD_NORMAL = VT_NORMAL,
	
	VT_FULL_SCRN,
	VT_OSD_FULL_SCRN = VT_FULL_SCRN,

//Special view type start here
	VT_SPL_TYPE_START, 
	VT_OSD_OPT_MENU = VT_SPL_TYPE_START,
	
//Fade out type start here
	VT_FADEOUT_START,
	VT_OPT_MENU = VT_FADEOUT_START,
	VT_DIALOG,
	VT_POPUP,

	VT_TOTAL
};
typedef u16 ViewType_t;

/* enum for ViewSBVisType_t */
enum ViewSBVisType_tag
{
	VIEWSB_INVISIABLE = 0x0000,
	VIEWSB_VISIABLE
};
typedef u16 ViewSBVisType_t;

/* enum for ViewSKVisType_t */
enum ViewSKVisType_tag
{
	VIEWSK_INVISIABLE = 0x0000,
	VIEWSK_VISIABLE
};
typedef u16 ViewSKVisType_t;

/* enum for ViewGPVisType_t */
enum ViewGPVisType_tag
{
	VIEWGP_INVISIABLE = 0x0000,
	VIEWGP_VISIABLE
};
typedef u16 ViewGPVisType_t;

/* enum for ViewTranspType_t */
enum ViewTranspType_tag
{
	VIEW_TRANSPTYPE_NOTRANSP = 0x0000,
	VIEW_TRANSPTYPE_TRANSP
};
typedef u16 ViewTranspType_t;

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

/*
    View Transition data structure
 */
typedef struct
{
	u32 nTransitRegions;          ///< how many regions to perform transition
	TransitionParam_t *pTransitParams;  ///< parameters for each transition. NOTE:all nTotalSteps in each TransitionParam_t should be the same. if not, the MAX nTotalSteps will be applied.
}ViewTransition_t;


#endif /* __MAE_VIEW_DEFINES_H__ */
