/**
* @file     mae_GLMULTIIDLEPAGEWIDGET_priv.h
* @brief
*
* @version $Id:$
*/

#ifndef __MAE_GLMULTIIDLEPAGEWIDGET_PRIV_H__
#define __MAE_GLMULTIIDLEPAGEWIDGET_PRIV_H__

#if defined(__FEATURE_MGL__) && defined(__3D_UI_IDLE_MULTIPAGE__) && defined(__3D_UI_IDLE_MULTIPAGE_PAGEVIEW__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_glmultiidlepagewidget.h"
#include "mae_widgetbase.h"
#include "mae_glwidget_common.h"
#include "mmi_mae_util_easing.h"
#include "mgl_Scene_NodeMgr.h"
#include "mgl_Core_shape.h"
#include "mgl_Scene_Environment.h"
#include "mgl_Egl.h"
#include "mmi_common_util.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define GLMULTIIDLEPAGE_TIMER 5
#define MULTIIDLEPAGE_PLANE_SCALE_TIME 3
#define MULTIIDLEPAGE_TATAL_FRAME 3
#define MULTIIDLEPAGE_SHIFT_FRAME_NUM 2
#define MULTIIDLEPAGE_FOCUS_BOARD 3

//layout.
#define MULTIIDLEPAGE_PLANE_GAP 5
#define MULTIIDLEPAGE_PLANE_SMALL_HEIGHT (MAIN_LCD_HEIGHT- MAIN_STBAR_HEIGHT -MULTIIDLEPAGE_PLANE_GAP*6)/3 //100
#define MULTIIDLEPAGE_PLANE_SMALL_WIDTH (MAIN_LCD_WIDTH-MULTIIDLEPAGE_PLANE_GAP*6)/3 //60

#define MULTIIDLEPAGE_PLANE_L_START_POS_X -(MULTIIDLEPAGE_PLANE_SMALL_WIDTH)
#define MULTIIDLEPAGE_PLANE_L_START_POS_Y MULTIIDLEPAGE_PLANE3_Y
#define MULTIIDLEPAGE_PLANE_R_START_POS_X (MAIN_LCD_WIDTH+MULTIIDLEPAGE_PLANE_SMALL_WIDTH)
#define MULTIIDLEPAGE_PLANE_R_START_POS_Y MULTIIDLEPAGE_PLANE3_Y
#define MULTIIDLEPAGE_PLANE_POS_Z -50
#define MULTIIDLEPAGE_PLANE_FLYIN_START_POS_X 0
#define MULTIIDLEPAGE_PLANE_FLYIN_START_POS_Y 0
#define MULTIIDLEPAGE_PLANE_FLYIN_START_POS_Z MULTIIDLEPAGE_PLANE_POS_Z

#define MULTIIDLEPAGE_PLANE1_X MULTIIDLEPAGE_PLANE_GAP
#define MULTIIDLEPAGE_PLANE1_Y MULTIIDLEPAGE_PLANE_GAP + MAIN_STBAR_HEIGHT
#define MULTIIDLEPAGE_PLANE1_Z MULTIIDLEPAGE_PLANE_POS_Z

#define MULTIIDLEPAGE_PLANE2_X MULTIIDLEPAGE_PLANE_SMALL_WIDTH*2 + MULTIIDLEPAGE_PLANE_GAP*5
#define MULTIIDLEPAGE_PLANE2_Y MULTIIDLEPAGE_PLANE_GAP +MAIN_STBAR_HEIGHT
#define MULTIIDLEPAGE_PLANE2_Z MULTIIDLEPAGE_PLANE_POS_Z

#define MULTIIDLEPAGE_PLANE3_X MULTIIDLEPAGE_PLANE_SMALL_WIDTH + MULTIIDLEPAGE_PLANE_GAP*3
#define MULTIIDLEPAGE_PLANE3_Y MULTIIDLEPAGE_PLANE_SMALL_HEIGHT + MULTIIDLEPAGE_PLANE_GAP*3 +MAIN_STBAR_HEIGHT
#define MULTIIDLEPAGE_PLANE3_Z MULTIIDLEPAGE_PLANE_POS_Z

#define MULTIIDLEPAGE_PLANE4_X MULTIIDLEPAGE_PLANE1_X
#define MULTIIDLEPAGE_PLANE4_Y MULTIIDLEPAGE_PLANE_SMALL_HEIGHT*2 + MULTIIDLEPAGE_PLANE_GAP*5 +MAIN_STBAR_HEIGHT
#define MULTIIDLEPAGE_PLANE4_Z MULTIIDLEPAGE_PLANE_POS_Z

#define MULTIIDLEPAGE_PLANE5_X MULTIIDLEPAGE_PLANE2_X
#define MULTIIDLEPAGE_PLANE5_Y MULTIIDLEPAGE_PLANE_SMALL_HEIGHT*2 + MULTIIDLEPAGE_PLANE_GAP*5 +MAIN_STBAR_HEIGHT
#define MULTIIDLEPAGE_PLANE5_Z MULTIIDLEPAGE_PLANE_POS_Z

#define MULTIIDLEPAGE_FOCUS_INVERT_POS MAIN_LCD_HEIGHT

typedef struct
{
    WidgetBaseEx_t  WdgBase;
    ModelListener_t MdlLsnr;
    Pos_t tCurPos;

    Vertex3D stStartImgPos[MULTIIDLEPAGE_PAGE_NUM];
    Vertex3D stEndImgPos[MULTIIDLEPAGE_PAGE_NUM];
    Vertex2D stStartFocusSize;
    Vertex2D stEndFocusSize;

    u16     u16SceneHandleId;
    u32     nodeID;
    mgl_u32         nRawDataID[MULTIIDLEPAGE_PAGE_NUM];
    IBitmap *pPageBmp[MULTIIDLEPAGE_PAGE_NUM];

    u8 nTmpDataIdArray[MULTIIDLEPAGE_PAGE_NUM];
    u8 nDataIdArray[MULTIIDLEPAGE_PAGE_NUM];
    u8 nInsertCfg[MULTIIDLEPAGE_PAGE_NUM];
    u8 nInsertFrom;
    u8 nInsertTo;


    u32 nCurFrameIdx;
    u8 nCurFocusIdx; //From 0~Page num-1.
    GLMULTIIDLEPAGEEFFECT eEffectDir;
    boolean bAnim;

    Rect_t PressedRc;
    Pos_t PressdPosOffset;
    u8 nTScount;

    Rect_t LastTsRect;
    Rect_t RcDraw;
} GlMultiIdlePageWdg_t;

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret GlMultiIdlePageWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret GlMultiIdlePageWdg_Ctor(GlMultiIdlePageWdg_t *pThis);
static void GlMultiIdlePageWdg_Dtor(GlMultiIdlePageWdg_t *pThis);
static void GlMultiIdlePageWdg_WidgetFree(void *pData);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean GlMultiIdlePageWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void GlMultiIdlePageWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
boolean _GlMultiIdlePageWdg_SetProperty(GlMultiIdlePageWdg_t *pThis, u32 P1, u32 P2);
boolean _GlMultiIdlePageWdg_GetProperty(GlMultiIdlePageWdg_t *pThis, u32 P1, u32 P2);
#endif //__FEATURE_MGL__ && __3D_UI_IDLE_MULTIPAGE__ && __3D_UI_IDLE_MULTIPAGE_PAGEVIEW__
#endif //__MAE_GLMULTIIDLEPAGEWIDGET_PRIV_H__
