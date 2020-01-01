/**
 * @brief
 * @file 	mae_gltransformwidget_priv.h
 * @version	$Id:$
 *
 */
#ifndef __MAE_GLTRANSFORMWIDGET_PRIV_H__
#define __MAE_GLTRANSFORMWIDGET_PRIV_H__

#if defined(__3D_UI_KINGMOVIE__)

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_util_gles.h"
#include "mae_glcirclelistwidget.h"
#include "mgl_core_types.h"
#include "mgl_utility_common.h"
#include "mae_widgetbase.h"
#include "mmi_common_display.h"
//#include "mae_basicwidget.h"
#include "mmi_mae_image.h"
#include "mmi_mae_helper.h"
#include "mae_widget_common.h"
#include "img_data.h"
#include "mgl_Egl.h"
#include "mmi_mae_vectormodel.h"

// mgl
#include "mgl_Scene_Environment.h"
#include "mgl_Core_Shape.h"
#include "mmi_mae_util_easing.h"
#include "srv_mmi_filemgr.h"
#include "mmi_mae_view_wrapper.h"


/*=============================================================*/
// type and define
/*=============================================================*/
#define GLCIRCLEWDG_MAX_NODE        (30)

enum
{
	GLCLWDG_ANIM_SLIDE_START = 0,
	GLCLWDG_ANIM_SLIDE_FINISH,
	GLCLWDG_ANIM_ZOOMIN_START,	
	GLCLWDG_ANIM_ZOOMIN_END,		
	GLCLWDG_ANIM_ZOOMOUT_START,	
	GLCLWDG_ANIM_ZOOMOUT_END,
	GLCLWDG_ANIM_STEP_MAX,
};
typedef u8 GLCircleListAnimStep_e;

typedef struct
{
    Vertex3D        Pos;
	Vertex2D        Size;
	mgl_float       Alpha;
}GLCircleListTexInfo_t;

typedef struct
{
	u32                     u32ItemTextureId;
    u32                     u32ItemNameId;
    IBitmap                 *pItemBitmap;
    GLCircleListTexInfo_t   tTextInfo;
    IBitmap                 *pItemNameBitmap;
    Vertex2D                tItemNameSize;
}GlCircleListItemData_t;

typedef struct
{
	WidgetBaseEx_t              WdgBase;
    u8                          eMaxDispNum;
    u8                          eAnimType;
    GLCircleListAnimStep_e      eAnimStep;    
    boolean                     bAnimating;
    u32                         u32AnimFrame;    
    u32                         u32TotalFrame;
    boolean                     bGlTextBgEnable;
    u32                         u32GlTextLeftBgId;
    u32                         u32GlTextRightBgId;
    u32                         u32GlTextMidBgId;
    Pos_t                       tGlClWdgPos;
    Pos_t                       tVirCenter;
    WidgetSize_t                tItemSize;
    s32                         nFocusIdx;
    IVectorModel                *pItemVector;
    u16                         u16SceneHandleId;
    mgl_u32                     u32ItemNodeID[GLCIRCLEWDG_MAX_NODE];    
    
    mgl_float                   fAnimUnitDis;
    s32                         nCumulateDis;

}GlCircleListWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/

/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlCircleListWdg_New(MAE_ClsId ClsID, void **ppObj);
/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
void WdgGlCircleListWdgDefDraw(IWidget *pThis, IDispCanvas *pIDispCanvas, s32 x, s32 y);
boolean WdgGlCircleListWdgDefHandleEvent(IWidget* pClWdg, MAE_EventId evt, u32 P1, u32 P2);
/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
//static void GLCircleListWidgetSetSize(GLCircleListWidget_t *pClWdg, WidgetSize_t *pSize);

/*------------------------------------------------------------------------------------------
* For other functions
------------------------------------------------------------------------------------------*/

#endif


#endif //__MAE_GLCIRCLELISTWIDGET_PRIV_H__
/*=============================================================*/
// end of file
