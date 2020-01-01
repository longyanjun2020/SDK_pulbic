////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mae_animation.h
* @brief   This file is the implementation of animation
*/



/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifndef __MAE_ABSCONTAINER_PRIV_H__
#define __MAE_ABSCONTAINER_PRIV_H__

#define PI                       3.14159265

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_animation.h"
#include "mmi_log.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/

typedef struct {
    s32 nStartX;
    s32 nStartY;
    s32 nEndX;
    s32 nEndY;
    u32 nDurationTime;
    u32 nStartTime;
    u32 nParam;
    //for testing
    u32 nCurrTime;
}Animation_Transition;

typedef struct
{
	void *pData; ///< pointer to the context data which will be passed into handler function and free function.
	WHANDLER_HDL_FUNC_PTR pfHandle; ///< the handler function which will be called in WHANDLER_CALL().
	WHANDLER_FREE_FUNC_PTR pfFree;	///< the free function which will be called in WHANDLER_FREE().
} AnimationHandler_t;

typedef struct {
    DECLARE_FUNCTBL( IAnimation );   // function table pointer
	IWidget *pActWidget;
    IAbsContainer *pAbsContainer;
    Animation_Transition animTransition;
    ANIMATION_TWEEN_FUNCTION animTweenFunction;
    ANIMATION_END_HANDLER animEndHandler;
    ANIMATION_REPEAT_HANDLER animRepeatHandler;
    void * pEndParam;
    void * pRepeatParam;
    u32 nRefCnt;
    u32 nRepeatCount;
    u32 nRepeatCurrCount;
    boolean bIsScrollMode;
    boolean bStop;
} Animation_t;

/*=============================================================*/
// private function
/*=============================================================*/

static MAE_Ret Animation_Ctor(Animation_t *pThis, const FUNCTBL(IAnimation) *FtblPtr);
static MAE_Ret Animation_QueryInterface( IAnimation *pAnimation,MAE_IId iId,void **ppObj,IBase *pOwner );
static MAE_Ret Animation_SetTransAnimation(IAnimation *pAnimation, IWidget *pIWidget, s32 nEndX, s32 nEndY, u32 nDurationTime, u32 nParam, ANIMATION_TRANSITION_TYPE animTransType);
static MAE_Ret Animation_StartAnimation(IAnimation *pAnimation);
static void Animation_StopAnimation(IAnimation *pAnimation);
static void Animation_SetScrollMode(IAnimation *pAnimation,boolean bMode,u32 nX, u32 nY);
static void Animation_SetRepeatCount(IAnimation *pAnimation,u32 nRepeatCount);
static void Animation_SetRepeatHandler(IAnimation *pAnimation, ANIMATION_REPEAT_HANDLER animRepeatHandler, void * param1);
static void Animation_SetEndHandler(IAnimation *pAnimation, ANIMATION_END_HANDLER animEndHandler, void * param1);
static void _Animation_ExecAnimation(void *pAnimation);
static MAE_Ret _Animation_SetTweenFunction (Animation_t * pThis,ANIMATION_TRANSITION_TYPE animTransType);

static u32 Animation_AddRef( IAnimation *pAnimation );
static u32 Animation_Release( IAnimation *pAnimation );

#ifdef ANIMATION_FIXPOINT
s32 Animation_Math_Linear(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInBack(s32 t, s32 b, s32 c, s32 d, s32 fx_s);
s32 Animation_Math_EaseOutBack(s32 t, s32 b, s32 c, s32 d, s32 fx_s);
s32 Animation_Math_EaseInOutBack(s32 t, s32 b, s32 c, s32 d, s32 fx_s);
s32 Animation_Math_EaseInQuad(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutQuad(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutQuad(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInExpo(s32 t, s32 b, s32 c, s32 d, s32 a);
s32 Animation_Math_EaseOutExpo(s32 t, s32 b, s32 c, s32 d, s32 a);
s32 Animation_Math_EaseInOutExpo(s32 t, s32 b, s32 c, s32 d, s32 a);
s32 Animation_Math_EaseInQuint(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutQuint(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutQuint(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInBounce(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutBounce(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutBounce(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);

#else
s32 Animation_Math_Linear(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInQuad(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutQuad(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutQuad(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutInQuad(s32 t, s32 b, s32 c, s32 d, s32 s);
s32 Animation_Math_EaseInBack(s32 t, s32 b, s32 c, s32 d, s32 fx_s);
s32 Animation_Math_EaseOutBack(s32 t, s32 b, s32 c, s32 d, s32 fx_s);
s32 Animation_Math_EaseInOutBack(s32 t, s32 b, s32 c, s32 d, s32 fx_s);
s32 Animation_Math_EaseOutInBack(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInElastic(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutElastic(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutElastic(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutInElastic(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInBounce(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutBounce(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutBounce(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutInBounce(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInQuint(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutQuint(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutQuint(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutInQuint(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInExpo(s32 t, s32 b, s32 c, s32 d, s32 a);
s32 Animation_Math_EaseOutExpo(s32 t, s32 b, s32 c, s32 d, s32 a);
s32 Animation_Math_EaseInOutExpo(s32 t, s32 b, s32 c, s32 d, s32 a);
s32 Animation_Math_EaseOutInExpo(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInCubic(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutCubic(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutCubic(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutInCubic(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInQuart(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutQuart(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutQuart(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutInQuart(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInSine(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutSine(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutSine(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutInSine(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInCirc(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutCirc(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseInOutCirc(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
s32 Animation_Math_EaseOutInCirc(s32 tt, s32 bb, s32 cc, s32 dd, s32 aa);
#endif // ANIMATINO_FIXPOINT

#endif	//__MAE_ABSCONTAINER_H__
