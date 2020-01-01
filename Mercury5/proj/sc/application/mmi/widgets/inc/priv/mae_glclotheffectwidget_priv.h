/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mae_glclotheffectwidget_priv.h
 *
 *
 * HISTORY
 *      2011.04.01       Evan Chang         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __MAE_GLCLOTHEFFECTWIDGET_PRIV_H__
#define __MAE_GLCLOTHEFFECTWIDGET_PRIV_H__

#if defined(__MMI_BEAUTY_CLK_APP__) || defined(__3D_UI_KEYGUARD_BEAUTY_CLK__)

/*=============================================================*/
// include
/*=============================================================*/

#include "mae_glclotheffectwidget.h"
#include "mgl_core_types.h"
#include "mgl_utility_common.h"
#include "mae_widgetbase.h"
#include "mgl_Effect_ClothModeling.h"
#include "mmi_coresrv.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum
{
	CLOTH_EFFECT_TOUCH_PHASE_NORMAL,
	CLOTH_EFFECT_TOUCH_PHASE_TWEENER,
	CLOTH_EFFECT_TOUCH_PHASE_MOVE,
} ClothEffectTouchPhase_e;

typedef struct{
	WidgetBaseEx_t  WdgBase;
	ModelListener_t MdlLsnr;
	ICORESRV	*pICoreSrv;

    ClothEffectTouchPhase_e eTouchPhase;

    /* MGL */
	mgl_u16     nSceneHandle;
	mgl_u32     nClothEffectNodeId;

    /* Cloth Info */
	CLOTH_MODELING_EFFECT   eEffectType;
    mgl_u32                 nRawDataID;
	IBitmap                 *pCacheScreenBmp;
    Vertex2D                vClothSize;
    Vertex2D                vInitPosition;
    Vertex2D                vMove;
    Vertex2D                vLastMove;

    /* Others */
    mgl_u16     nAnimateFrame;
    mgl_u16     nInitAnimateFrame;
    mgl_float   fCurtainExpandRatio;
    boolean     bDropCloth;
    Vertex3D    vWind;
    Vertex3D    vGravityFold;

    mgl_u16     nFrameIdx;
    mgl_u16     nTotalFrame;

    /* Touch Screen */
    Vertex2D    vTotalMovement;
    Vertex2D    vTS_CurrentPos;
    Vertex2D    vTS_OffsetPos;

#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv   *pITouchSrv;
	boolean     bIsPressed;
    boolean     bDisableTouchEvt;
#endif //__TOUCH_SCREEN_MMI__

    ClothMoveType_e eMoveType;
    boolean bIsAlphaFadeout;
    boolean bStartAnim;
    boolean bMglDraw;
}ClothEffectWdg_t;

//Get flag value
#ifdef __TOUCH_SCREEN_MMI__
#define GL_CLOTHEFFECT_WDG_IS_DISABLE_TOUCH(_pWdg) \
	(boolean)((_pWdg)->bDisableTouchEvt)

#define GL_CLOTHEFFECT_WDG_SET_DISALBE_TOUCH(_pWdg, _b) \
	(_pWdg)->bDisableTouchEvt = (boolean)(_b)
#endif //__TOUCH_SCREEN_MMI__

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret ClothEffectWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret ClothEffectWdg_Ctor(ClothEffectWdg_t *pThis);
void ClothEffectWdg_Dtor(ClothEffectWdg_t *pThis);
static void ClothEffectWdg_WidgetFree(void *pData);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean _ClothEffectWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void _ClothEffectWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
static boolean _ClothEffectWdg_GetProperty(ClothEffectWdg_t *pThis, u32 P1, u32 P2);
static boolean _ClothEffectWdg_SetProperty(ClothEffectWdg_t *pThis, u32 P1, u32 P2);

#endif /* defined(__MMI_BEAUTY_CLK_APP__) || defined(__3D_UI_KEYGUARD_BEAUTY_CLK__) */
#endif //__MAE_GLCLOTHEFFECTWIDGET_PRIV_H__

