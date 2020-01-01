/**
* @file    mmi_wdg_animationcontainer.h
* @version $Id: mmi_wdg_animationcontainer.h
* @brief   This file defines the interface of AnimationContainer
*/
#ifndef __MMI_WDG_ANIMATIONCONTAINER_H__
#define __MMI_WDG_ANIMATIONCONTAINER_H__

#if defined(__FEATURE_MGL__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_common_interface.h"

enum
{
    ANIMATIONCONTAINER_TRANSFORM_TYPE_NONE = 0,

    ANIMATIONCONTAINER_TRANSFORM_TYPE_X_TRANSLATE,
    ANIMATIONCONTAINER_TRANSFORM_TYPE_Y_TRANSLATE,
    ANIMATIONCONTAINER_TRANSFORM_TYPE_Z_TRANSLATE,
    ANIMATIONCONTAINER_TRANSFORM_TYPE_TRANSLATE_END,

    ANIMATIONCONTAINER_TRANSFORM_TYPE_X_ROTATE = ANIMATIONCONTAINER_TRANSFORM_TYPE_TRANSLATE_END,
    ANIMATIONCONTAINER_TRANSFORM_TYPE_Y_ROTATE,
    ANIMATIONCONTAINER_TRANSFORM_TYPE_Z_ROTATE,
    ANIMATIONCONTAINER_TRANSFORM_TYPE_ROTATE_END,

};
typedef u32 AnimationContainer_TransformType_e;

/** PfnWdgAnimationContainerEventCB
* @brief
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  param             Relative info
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgAnimationContainerEventCB) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);

/** WdgAnimationContainerRegisterEventCb
* @brief        Register callback
*
* @param[in]    pAnimationContainer     Pointer to the AnimationContainer
* @param[in]    pfn                     callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAnimationContainerRegisterEventCb
(
    IWidget                         *pAnimationContainer,
    PfnWdgAnimationContainerEventCB pfn,
    void                            *pUserData
);

/** WdgAnimationContainerDeregisterEventCb
* @brief        Deregister callback
*
* @param[in]    pAnimationContainer    Pointer to the AnimationContainer
* @param[in]    pfn                     callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgAnimationContainerDeregisterEventCb
(
    IWidget                         *pAnimationContainer,
    PfnWdgAnimationContainerEventCB pfn,
    void                            *pUserData
);

/*=============================================================*/
// interface
/*=============================================================*/
/** WdgAnimationContainerCreateForWnd
* @brief        Create AnimationContainer Widget and set the AnimationContainer value for Window.
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWdgId         The widget unique ID of window

*
* @retval       The pointer of AnimationContainer     Success.
* @retval       NULL                                  Failed.
*
*/
IWidget* WdgAnimationContainerCreateForWnd
(
    HWIN               hWin,
    Pos_t              *pPos,
    WidgetSize_t       *pSize,
    u16                nWdgId
);

/*=============================================================*/
/** WdgAnimationContainerCreate
* @brief        Create AnimationContainer widget.
*
* @retval       The pointer of AnimationContainer  Success.
* @retval       NULL                               Failed.
*
*/
IWidget* WdgAnimationContainerCreate
(
    void
);

/** WdgAnimationContainerStartAnimation
* @brief        Start animation from first frame or last frame(reverse animation)
*
* @param[in]    pAnimationContainer        Pointer to the AnimationContainer.
* @param[in]    bReverseAnimation          reverse animation or not.
*
*
*/
void WdgAnimationContainerStartAnimation
(
    IWidget     *pAnimationContainer,
    boolean     bReverseAnimation
);

/** WdgAnimationContainerStopAnimation
* @brief        Stop animation. This API will reset some control data in container.
*
* @param[in]    pAnimationContainer           Pointer to the AnimationContainer.
*
*
*/
void WdgAnimationContainerStopAnimation
(
    IWidget     *pAnimationContainer
);

/** WdgAnimationContainerCheckAnimationThenSuspend
* @brief        To check the animation will launch a new applet after animation end or not.
*
* @param[in]    pAnimationContainer           Pointer to the AnimationContainer.
*
* @retval       TRUE                          Launch a new applet after animation end; after resume from the new applet, automatically start the reverse animation.
* @retval       FALSE                         Pure animation.
*
*/
boolean WdgAnimationContainerCheckAnimationThenSuspend
(
    IWidget     *pAnimationContainer
);

#endif
#endif    //__MMI_WDG_ANIMATIONCONTAINER_H__
/*=============================================================*/
// end of file
