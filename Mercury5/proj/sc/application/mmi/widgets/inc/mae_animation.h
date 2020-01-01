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
#ifndef __MAE_ANIMATION_H__
#define __MAE_ANIMATION_H__

/*=============================================================*/
// application programmer interface
/*=============================================================*/

/** API List
 * #define IANIMATION_SetTransAnimation(pThis,pIWidget,nEndX,EndY,nDurationTime,nParam,etransType) 
 * #define IANIMATION_StartAnimation(pThis)            
 * #define IANIMATION_StopAnimation(pThis)       
 * #define IANIMATION_SetScrollMode(pThis,bMode,nX,nY)                                                        
 * #define IANIMATION_SetRepeatCount(pThis,nRepeatCount)                                   
 * #define IANIMATION_SetEndHandler(pThis,animEndHandler,param1)                       
 * #define IANIMATION_SetRepeatInfinite(pThis)          
 * #define IANIMATION_SetRepeatOnce(pThis)  
 */

/** 
 *  IANIMATION_SetTransAnimation
 *  @brief  Set motion transition from A point to B point, it can use tweener to moving a widget from A to B.
 *             make sure the widget under a IAbsContainer. This animation can't work if the widget under other container 
 *  @param  pAnim       		       Pointer of interface of the IAnimation object.
 *  @param  pIWidget     			Pointer of interface of the IWidget.
 *  @param  nEndX 				The end x position, means the x of B point 
 *  @param  nEndY 				The end y position, means the y of B point
 *  @param  nDurationTime 			The duration time of animation
 *  @param  nParam 				Parameter for tweener equation, it means the amount of overshoot in animation,where the higher the value, the greater the overshoot.
 *  @param  etransType 			Tweener transition type, please refer the ANIMATION_TRANSITION_TYPE 
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_SetTransAnimation(pAnim,pIWidget,nEndX,nEndY,nDurationTime,nParam,etransType)          GET_FUNCTBL(pAnim,IAnimation)->SetTransAnimation(pAnim,pIWidget,nEndX,nEndY,nDurationTime,nParam,etransType)

/** 
 *  IANIMATION_StartAnimation
 *  @brief  start animation 
 *  @param  pAnim       		      Pointer of interface of the IAnimation object.
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_StartAnimation(pAnim)                                                                 GET_FUNCTBL(pAnim,IAnimation)->StartAnimation(pAnim)

/** 
 *  IANIMATION_StopAnimation
 *  @brief  stop animation 
 *  @param  pAnim       		      Pointer of interface of the IAnimation object.
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_StopAnimation(pAnim)                                                                  GET_FUNCTBL(pAnim,IAnimation)->StopAnimation(pAnim)

/** 
 *  IANIMATION_SetScrollMode
 *  @brief  set scroll mode in animation for some special case, ex. viewport widget, cdwap, 
 *             because these widgets cannot be move directly by IAbsContainer, so it must send
 *             scroll data for motion of widget
 *  @param  pAnim       		      Pointer of interface of the IAnimation object.
 *  @param  nX       		             The start x position. must have set start x position in scroll mode
 *  @param  nY       		             The start y position. must have set start y position in scroll mode
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_SetScrollMode(pAnim,bMode,nX,nY)                                                      GET_FUNCTBL(pAnim,IAnimation)->SetScrollMode(pAnim,bMode,nX,nY)

/** 
 *  IANIMATION_SetEndHandler
 *  @brief  set end callback in animation, the animation call the callback when animation end 
 *  @param  pAnim       		      Pointer of interface of the IAnimation object.
 *  @param  animEndHandler             Pointer of callback function
 *  @param  param1       		      Parameter for callback function
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_SetEndHandler(pAnim,animEndHandler,param1)                                            GET_FUNCTBL(pAnim,IAnimation)->SetEndHandler(pAnim,animEndHandler,param1)

/** 
 *  IANIMATION_SetRepeatHandler
 *  @brief  set repeat callback in animation, the animation send repeat count to the callback when animation repeat 
 *  @param  pAnim       		      Pointer of interface of the IAnimation object.
 *  @param  animRepeatHandler        Pointer of callback function
 *  @param  param1       		      Parameter for callback function
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_SetRepeatHandler(pAnim,animRepeatHandler,param1)                                      GET_FUNCTBL(pAnim,IAnimation)->SetRepeatHandler(pAnim,animRepeatHandler,param1)

/** 
 *  IANIMATION_SetRepeatCount
 *  @brief  set repeat count of animation
 *  @param  pAnim       		      Pointer of interface of the IAnimation object.
 *  @param  nRepeatCount       	      The repeat count
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_SetRepeatCount(pAnim,nRepeatCount)                                                    GET_FUNCTBL(pAnim,IAnimation)->SetRepeatCount(pAnim,nRepeatCount)

/** 
 *  IANIMATION_SetRepeatInfinite
 *  @brief  set infinite repeat count
 *  @param  pAnim       		      Pointer of interface of the IAnimation object.
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_SetRepeatInfinite(pAnim)                                                              IANIMATION_SetRepeatCount(pAnim, 0)

/** 
 *  IANIMATION_SetRepeatOnce
 *  @brief  set repeat count to one, means no repeat.
 *  @param  pAnim       		      Pointer of interface of the IAnimation object.
 *  @retval MAE_RET_SUCCESS          SUCCESS.
 *  @retval MAE_RET_FAILED 	      FAIL.
 */
#define IANIMATION_SetRepeatOnce(pAnim)                                                                  IANIMATION_SetRepeatCount(pAnim, 1)


//#define ANIMATION_FIXPOINT

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_abscontainer.h"
#include "mmi_mae_applet.h"
#include "mmi_common_util.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef s32 (*ANIMATION_TWEEN_FUNCTION) (s32,s32,s32,s32,s32);
typedef void (*ANIMATION_END_HANDLER) (void * param1);
typedef void (*ANIMATION_REPEAT_HANDLER) (void * param1, u32 nRepeatCount);

typedef enum
{
    ANIMATION_LINEAR = 0,
    ANIMATION_EASE_IN_QUAD,
    ANIMATION_EASE_OUT_QUAD,
    ANIMATION_EASE_INOUT_QUAD,
    ANIMATION_EASE_OUTIN_QUAD,
    ANIMATION_EASE_IN_BACK, 
    ANIMATION_EASE_OUT_BACK, 
    ANIMATION_EASE_INOUT_BACK,
    ANIMATION_EASE_OUTIN_BACK,
    ANIMATION_EASE_IN_ELASTIC,
    ANIMATION_EASE_OUT_ELASTIC,
    ANIMATION_EASE_INOUT_ELASTIC,
    ANIMATION_EASE_OUTIN_ELASTIC,
    ANIMATION_EASE_IN_BOUNCE,
    ANIMATION_EASE_OUT_BOUNCE,
    ANIMATION_EASE_INOUT_BOUNCE,
    ANIMATION_EASE_OUTIN_BOUNCE,
    ANIMATION_EASE_IN_QUINT,
    ANIMATION_EASE_OUT_QUINT,
    ANIMATION_EASE_INOUT_QUINT,
    ANIMATION_EASE_OUTIN_QUINT,
    ANIMATION_EASE_IN_EXPO,
    ANIMATION_EASE_OUT_EXPO,
    ANIMATION_EASE_INOUT_EXPO,
    ANIMATION_EASE_OUTIN_EXPO,
    ANIMATION_EASE_IN_CUBIC,
    ANIMATION_EASE_OUT_CUBIC,
    ANIMATION_EASE_INOUT_CUBIC,
    ANIMATION_EASE_OUTIN_CUBIC,
    ANIMATION_EASE_IN_QUART,
    ANIMATION_EASE_OUT_QUART,
    ANIMATION_EASE_INOUT_QUART,
    ANIMATION_EASE_OUTIN_QUART,
    ANIMATION_EASE_IN_SINE,
    ANIMATION_EASE_OUT_SINE,
    ANIMATION_EASE_INOUT_SINE,
    ANIMATION_EASE_OUTIN_SINE,
    ANIMATION_EASE_IN_CIRC,
    ANIMATION_EASE_OUT_CIRC,
    ANIMATION_EASE_INOUT_CIRC,
    ANIMATION_EASE_OUTIN_CIRC,
    ANIMATION_TRANSITION_COUNT
}ANIMATION_TRANSITION_TYPE;

#define INHERIT_IAnimation(IName) \
    INHERIT_IBase(IName); \
    MAE_Ret (*SetTransAnimation) (IName *pAnimation, IWidget *pIWidget, s32 nEndX, s32 nEndY, u32 nDurationTime, u32 nParam, ANIMATION_TRANSITION_TYPE animTransType); \
    MAE_Ret (*StartAnimation) (IName *pAnimation); \
    void (*StopAnimation) (IName *pAnimation); \
    void (*SetScrollMode) (IName *pAnimation,boolean bMode,u32 nX, u32 nY); \
    void (*SetRepeatCount) (IName *pAnimation,u32 nRepeatCount); \
    void (*SetRepeatHandler) (IName *pAnimation,ANIMATION_REPEAT_HANDLER animRepeatHandler, void * param1); \
    void (*SetEndHandler) (IName *pAnimation,ANIMATION_END_HANDLER animEndHandler, void * param1)

DEFINE_INTERFACE( IAnimation );

#endif    //__MAE_ABSCONTAINER_H__
