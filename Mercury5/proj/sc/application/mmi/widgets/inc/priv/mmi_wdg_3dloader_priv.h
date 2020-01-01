/**
* @file 	mmi_wdg_3dloader_priv.h
* @brief
*
* @version $Id:$
*/

#ifndef __MMI_WDG_3DLOADER_PRIV_H__
#define __MMI_WDG_3DLOADER_PRIV_H__

#define PBUFFER_BG_COLOR_RED    1

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_3dloader.h"
#include "mae_widgetbase.h"
#include "mmi_common_display.h"
#include "mmi_mae_image.h"
#include "mmi_mae_helper.h"
#include "mae_widget_common.h"
#include "img_data.h"
// mgl
#include "mgl_Scene_Environment.h"
#include "mgl_Core_Shape.h"
#include "mmi_filemgr.h"
#include "mmi_mae_view_wrapper.h"

#include "mmi_mae_util_easing.h"

#include "mgl_3DS_loader.h"

/*=============================================================*/
// Marco
/*=============================================================*/
#define GL_3DLOADER_TIMER 20
#define GL_3DS_OBJ_MAX MGL_3DS_OBJ_MAX

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct _3DLoaderCallBackFrame_t
{
    u32 nFrame;
}_3DLoaderCallBackFrame;

typedef struct _3DLoaderSingleKeyFrameMode_t
{
	boolean bSingleKFMode;
	u32 nTotalAnimFrames;
	u32 nKeyFrameIdx;
}_3DLoaderSingleKeyFrameMode;

typedef struct _3DLoaderObjectAnimation_t
{
	boolean bAnimation;
	float nRotateStartAngle;
	float nRotateEndAngle;
	float nRotatePivotX;
	float nRotatePivotY;
	float nRotatePivotZ;
	float nTranslateStartX;
	float nTranslateStartY;
	float nTranslateStartZ;
	float nTranslateEndX;
	float nTranslateEndY;
	float nTranslateEndZ;
}_3DLoaderObjectAnimation;

// only leave nPlayingFrameIdx
typedef struct _3DPlayer_t
{
     //single keyframe mode, using one keyframe
     _3DLoaderSingleKeyFrameMode 		SingleKFModeData;
     _3DLoaderObjectAnimation     			ObjectAnimation[GL_3DS_OBJ_MAX];
     u32                                 							nSingleKFPlayingFrameIdx;
     WdgEasingType_t                     						EasingType; //used for easing function

    //////////////////////

    u32 	nFrameStepIdx;       //current step of animation
    u32 	nPlayingFrameIdx;   // get from easing function, default easing function is linear , so default nAnimPlayingFrameIdx is equal to nFrameStepIdx.
    u32 	nPlayingStartFrame; //user defined, if no defined the default value is nStartFrame
    u32 	nPlayingEndFrame;   //user defined , if no defined the default value is nEndFrame
    boolean bRepeat;
    _3DLoaderPlayDirection ePlayDirection;
}_3DPlayer;

typedef struct _3DBGInfo_t
{
	boolean isImageID;
    mgl_u32 u32BGImageID;
}_3DBGInfo;

typedef struct
{
	WidgetBaseEx_t  WdgBase;
    s32             x;
    s32             y;
	mgl_u16         nSceneHandle;	///< MGL scene id
	mgl_u32         nodeID;
	mgl_s16 anID;
#if defined(__FEATURE_MGL__)
    IWidget *pBgImgWdg;
#endif
    _3DLoaderCallBackFrame DecodeCallback;
    _3DLoaderCallBackFrame ChangeImgCallback;
    u32                    nCommonCBFrameList[GL3DLOADER_COMMON_CALLBACK_MAX];

    boolean         bTimerStop;
    boolean         bTimerPause;
    boolean         bDrawObject;

    //picking
    boolean bMoveCbExist;
    boolean bPressed;
    u32 nPressObjIdx;
    u32 nTimerValue;

    boolean bTransparent;   /* global alpha */

    /* background */
    _3DBGInfo backGroundImg;

	boolean bKeyPress[GL_3DS_OBJ_MAX];
      _3DSObjectImageInfo ImageInfoNormal[GL_3DS_OBJ_MAX];
      _3DSObjectImageInfo ImageInfoPress[GL_3DS_OBJ_MAX];
      _3DSObjectAlphaInfo alphaInfo[GL_3DS_OBJ_MAX];
    _3DPlayer				GlPlayer3DS;
    u16     sceneCap;
	u8	nCountValue;
}Gl3dLoaderWdg_t;


/*=============================================================*/
// functions
/*=============================================================*/


/*------------------------------------------------------------------------------------------
* New function, Constructor and Destructor
------------------------------------------------------------------------------------------*/
MAE_Ret Gl3dLoaderWdg_New(MAE_ClsId ClsID, void **ppObj);
MAE_Ret Gl3dLoaderWdg_Ctor(Gl3dLoaderWdg_t *pThis);
static void Gl3dLoaderWdg_Dtor(Gl3dLoaderWdg_t *pThis);

/*------------------------------------------------------------------------------------------
* For IHandler interface
------------------------------------------------------------------------------------------*/
static boolean Gl3dLoaderWdg_DefHandleEvent(IWidget *pWdg, MAE_EventId evt, u32 P1, u32 P2);

/*------------------------------------------------------------------------------------------
* For IWidget interface
------------------------------------------------------------------------------------------*/
static void Gl3dLoaderWdg_Draw(IWidget *pWdg, IDispCanvas *pDispCanvas, s32 x, s32 y);
static boolean Gl3dLoaderWdg_SetProperty(Gl3dLoaderWdg_t *pThis, u32 P1, u32 P2);
static boolean Gl3dLoaderWdg_GetProperty(Gl3dLoaderWdg_t *pThis, u32 P1, u32 P2);
static boolean Gl3dLoaderWdg_IntersectOpaque(Gl3dLoaderWdg_t *pThis, u32 P1, u32 P2);

#endif //__MMI_WDG_3DLOADER_PRIV_H__
