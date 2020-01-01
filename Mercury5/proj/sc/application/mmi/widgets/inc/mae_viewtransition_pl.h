/**
 * @file    mae_viewtransition_pl.h
 * 
 * @version $Id: mae_viewtransition_pl.h 35539 2009-07-10 08:42:10Z steve.lee $
 */
#ifndef __MAE_VIEWTRANSITION_PL_H__
#define __MAE_VIEWTRANSITION_PL_H__
#include "mmi_mae_common_def.h"
#include "mae_viewmgr.h"
#include "mmi_mae_bitmap.h"

#ifdef __FEATURE_MGL__
#include "mae_widget_common.h"
#include "mgl_Utility_common.h"
#include "mgl_Scene_Nodemgr.h"
#include "mgl_Scene_Environment.h"
#include "mmi_mae_util_easing.h"
#endif

typedef struct
{
	MAE_ClsId ClsId;
	u16       DispWidth;
	u16       DispHeight;
	u16       SBHeight;       ///< height of statusbar widget, portrait mode
	u16       SKHeight;       ///< height of softkey widget, portrait mode
	u16       SKWidth_L;       ///< width of softkey widget, landscape mode
}ViewMgrDispInfo_t;

enum
{
	VIEWMGRPL_FRAME_TYPE_PRE,
	VIEWMGRPL_FRAME_TYPE_NEW,
	VIEWMGRPL_FRAME_TYPE_TRANSLUCENT_PRE,
	VIEWMGRPL_FRAME_TYPE_TRANSLUCENT_NEW,
	VIEWMGRPL_FRAME_TYPE_BG_ONLY,
};
typedef u8 ViewTransFrameType_t;

enum
{
	VIEWMGRPL_TRANSFORMTYPE_NONE,
	VIEWMGRPL_TRANSFORMTYPE_SCALE,
	VIEWMGRPL_TRANSFORMTYPE_PERSPECTIVE,
};
typedef u8 TransformType_t;

typedef struct
{
	u32 width;
	u32 height;
}ScaleParam_t;


/*
      UP          DOWN       RIGHT      LEFT

     topW
     ----      ----------    |\            /|
    / |  \     \   |    /    |  \        /  |
   /  h   \     \  h   /     |-h-| topW |-h-|
  /   |    \     \ |  /      |  /        \  |
 ------------     ----       |/            \|
                  topW
  h = height
  topW = topWidth
*/
typedef struct
{
	TransitionDirection_t tDir;
	u16 height;	
	u16 topWidth;
}PerspectiveParam_t;

typedef union
{
	ScaleParam_t tScale;
	PerspectiveParam_t tPerspective;
}TransformParam_t;

typedef struct
{
	s32 x;
	s32 y;
	Rect_t tRcCA;
	TransformType_t tTransformType;
	TransformParam_t tParam;
}ViewTransDrawParam_t;

typedef void (*PFN_VIEWMGR_DRAWFRAME)(ViewTransFrameType_t tFrameType, u32 nTransitNum, ViewTransDrawParam_t *pDrawParam, void *pViewMgrData, boolean bUpdate);
typedef IBitmap* (*PFN_VIEWMGR_CREATEFRAME)(ViewTransFrameType_t tFrameType, u32 nTransitNum, void *pViewMgrData, Rect_t *pRc);
typedef void (*PFN_VIEWMGR_RELEASEFRAME)(ViewTransFrameType_t tFrameType, u32 nTransitNum, void *pViewMgrData);

typedef struct
{
	void *pTransData;
	void *pViewmgrData;
	boolean bPlayByAPI;
	PFN_VIEWMGR_DRAWFRAME pfnDrawFrame;
	PFN_VIEWMGR_CREATEFRAME pfnCreateFrame; ///< use this function to create new/previous frame. if memory resource is enough, this function returns IBitmap* for advance using.
	                                        ///< user can use IBitmap (DIB) to do extra trasition effect which is not provided by default.
	                                        ///< Note: Do not release this IBitmap manually. pfnReleaseFrame will release it.
	PFN_VIEWMGR_RELEASEFRAME pfnReleaseFrame;
	IDisplay *pDisp;
}ViewMgrDoTransitionParam_t;

extern const ViewMgrDispInfo_t atViewMgrDispInfo[];
extern const ViewMgrBGTpye_e nViewMgr_DefBGType;
extern const RGBColor_t nViewMgr_DefBGColor;
extern const ViewMgrBGVis_e nViewMgr_DefBGVis;
extern const u32 nViewMgr_DefBGThemeImg;
extern const boolean bEnableViewTransition;
extern const u32 nWdgProp_BgColor;
extern const u32 nWdgProp_EnableStatusBarBG;
///////////////////////////////////////////////////////////////////////////
// data for fly and push
// Fly and push are familiar. Push will push old frame away but fly won't.
typedef struct
{
	s32 Max;
	s32 Cur;
	u32 bPush : 1;
}ViewTransFlyPush_t;

// data for flip over
typedef struct
{
	TransitionDirection_t  DirNew;
	s32 preH;
	s32 MaxH;
	s32 MaxW;
}ViewTransFlipOver_t;

// data for flip paper
typedef struct
{
	u32 WidthLeft;
	u32 blockH;
}ViewTransFlipPaper_t;

typedef struct
{
	TransitionDirection_t  DirNew;
	s32 preH;
	s32 MaxH;
	s32 MaxW;
}ViewTransRolling_t;

typedef struct
{
	boolean bInitStartStep;
    u16 nStartStep;
}ViewTransDoor_t;


typedef struct ViewTransData_t_
{
	u32 nTotalSteps;
	IBitmap *pBmpNew;
	IBitmap *pBmpPre;
	IBitmap *pBmpBG;
	
#ifdef __FEATURE_MGL__
    mgl_u32 nNewFrameRawId;
    mgl_u32 nPreFrameRawId;
    mgl_u32 nNodeId;
#endif	
	union
	{
		ViewTransFlyPush_t tFly;
		ViewTransFlipOver_t tFlipOver;
		ViewTransFlipPaper_t tFlipPaper;
        ViewTransRolling_t tRolling;
        ViewTransDoor_t tDoor;
	}uTransData;
}ViewTransData_t;

typedef void (* PFN_ViewTransInit)(TransitionParam_t *, ViewTransData_t *);
typedef void (* PFN_ViewTransDo)(ViewMgrDoTransitionParam_t *, u32 , u32 , ViewTransData_t *);
typedef void (* PFN_ViewTransEnd)(ViewTransData_t *);

typedef struct ViewTransTypeFunc_t_
{
	TransitionType_t nType;
	PFN_ViewTransInit pfnViewTransInit;
	PFN_ViewTransDo pfnViewTransDo;
	PFN_ViewTransEnd pfnViewTransEnd;
}ViewTransTypeFunc_t;

const ViewTransition_t* ViewTransGetViewTransitionDataByID(u32 id);
void* ViewTransInitTransition(ViewTransition_t *pTransitParam);
void ViewTransDoTransition(ViewMgrDoTransitionParam_t *pDoParam);
void ViewTransEndTransition(void *pTransData);
///////////////////////////////////////////////////////////////////////////
#endif /*__MAE_VIEWTRANSITION_PL_H__*/

