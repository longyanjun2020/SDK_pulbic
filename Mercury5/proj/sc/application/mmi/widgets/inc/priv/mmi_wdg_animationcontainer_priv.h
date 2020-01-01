/**
* @file    mmi_wdg_animationcontainer_priv.h
* @version $Id: mmi_wdg_animationcontainer_priv.h 
* @brief   This is the private header file for mmi_wdg_animationcontainer.c
*/
#ifndef __MMI_WDG_ANIMATIONCONTAINER_PRIV_H__
#define __MMI_WDG_ANIMATIONCONTAINER_PRIV_H__

#if defined(__FEATURE_MGL__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_AnimationContainer.h"
#include "mae_abscontainerbase.h"
#include "mgl_Core_shape.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define ANIMATION_TIME_INTERVAL           5
#define ANIMATION_TOTAL_FRAME             5

///structure for animation-container
typedef struct {
    AbsContainerBase_t    AbsCntrBase;

    boolean bAnimating;
    boolean bFinishThenSuspend;    
    boolean bReverseAnimation;
    u32     u16AnimationFrame;
	u16 	u16AnimationTotalFrames;
	u16 	u16MinPos;
	u16 	u16MaxPos;

    AnimationContainer_TransformType_e eTransformType;
    mgl_float fTranslateStep;
    mgl_float fRotateAngle;
    mgl_float fStartAngle;
    Vertex3D  vRotatePivot;    

	mgl_u16 u16SceneHandleId;
	mgl_u32 u32ContainerNodeID;
	TransformOP pTrans[1];

} AnimationContainer_t;


///structure of widget cell used in animation-Container
typedef struct AnimationWidgetCell_Tag {
	AbsWidgetCell_t absWCell;
	u32             u32ItemTextureId; // a MGL texture id
	u16		u16AnimOffset;			

} AnimationWidgetCell_t;


/*=============================================================*/
// New function and Event handler
/*=============================================================*/
//new function
MAE_Ret AnimationContainer_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgAnimationContainerDefHandleEvent(IAbsContainer *pIAnimationContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret WdgAnimationContainerConstructor(AnimationContainer_t *pThis);
void WdgAnimationContainerDestructor(AnimationContainer_t *pThis);

void AnimationContainerTimerCB(void * pUser);

#endif
#endif //__MMI_WDG_ANIMATIONCONTAINER_PRIV_H__
/*=============================================================*/
// end of file
