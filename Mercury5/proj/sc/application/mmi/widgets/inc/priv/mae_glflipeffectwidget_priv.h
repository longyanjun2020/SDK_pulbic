/**
* @file 	mae_glflipeffectwidget_priv.h
* @brief
*
* @version $Id:$
*/

#ifndef __MAE_GLFLIPEFFECTWIDGET_PRIV_H__
#define __MAE_GLFLIPEFFECTWIDGET_PRIV_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mae_glflipeffectwidget.h"
#include "mgl_core_types.h"
#include "mgl_utility_common.h"
#include "mae_widgetbase.h"
#include "mgl_Effect_BezierSurface.h"

/*=============================================================*/
// type and define
/*=============================================================*/
enum
{
	FLIP_STATUS_OPEN,
	FLIP_STATUS_CLOSE,
	FLIP_STATUS_NONE
};
typedef u16 Flip_Status_e;


typedef struct {
	WidgetBaseEx_t  WdgBase;
	ModelListener_t MdlLsnr;


	/* Time */
	Vertex3D pos;
    Vertex2D size;
    u8       nAnimCount;

	boolean   bIsFlipping;
	boolean   bIsMoveToTargetFIdx;
    mgl_u16	nMoveFrameIdx;

	/* MGL part */
    Flip_Status_e   flag;
    mgl_u16         nFrameIdx;
    mgl_u16         nTotalFrame;
    mgl_u16         nEasyFrame;
	mgl_u16         nSceneHandle;	///< MGL scene id
	u32             nFlipEffectNodeId;
    mgl_u32         nRawDataID;
	IBitmap         *pCacheScreenBmp;
    mgl_u32         nBGRawDataID;
	IBitmap         *pCacheBGBmp;
	
	mgl_u32		    nBackImgId;
	BEZIER_EFFECT   eEffect;
    mgl_float       nWeightRatio;

	//touch screen pos.
//    WPos_t          stMoveBeginPos;
	boolean bIsPressed;
	boolean bEnableInterrupt;
	boolean bQuickRelease;
	boolean bUseFliterLinear;
	ITouchSrv          *pITouchSrv;
    s32 nFliptimer;

	u16 nAnimInterval;
#ifdef __TOUCH_SCREEN_MMI__
    boolean bDisableTouchEvt;
#endif
}FlipEffectWdg_t;

//Get flag value
#ifdef __TOUCH_SCREEN_MMI__
#define GL_FLIPEFFECT_WDG_IS_DISABLE_TOUCH(_pWdg) \
	(boolean)((_pWdg)->bDisableTouchEvt)

#define GL_FLIPEFFECT_WDG_SET_DISALBE_TOUCH(_pWdg, _b) \
	(_pWdg)->bDisableTouchEvt = (boolean)(_b)
#endif //__TOUCH_SCREEN_MMI__

/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret FlipEffectWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret FlipEffectWdg_Ctor(FlipEffectWdg_t *pThis);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
boolean _FlipEffectWdg_SetProperty(FlipEffectWdg_t *pThis, u32 P1, u32 P2);
boolean _FlipEffectWdg_GetProperty(FlipEffectWdg_t *pThis, u32 P1, u32 P2);
//void FlipEffectWdg_DataChangedCb(IWidget *pWdg, GlFotoListDataChangedEvt_t *pInfo);

#endif //__MAE_GLFLIPEFFECTWIDGET_PRIV_H__
