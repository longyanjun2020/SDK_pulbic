/**
* @file    mmi_wdg_3dloader.h
* @brief
* @version $Id: mmi_wdg_3dloader.h
*/

#ifndef __MMI_WDG_3DLOADER_H__
#define __MMI_WDG_3DLOADER_H__

#define GL3DLOADER_COMMON_CALLBACK_MAX 6


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"

typedef struct
{
    u8* pObjectName;
	u32 PosX;
	u32 PosY;
}TSData_t;

typedef enum _3DLoaderPlayDirection_e
{
    GL3D_PLAY_NORMAL = 0,
	GL3D_PLAY_FORWARD,
	GL3D_PLAY_BACKWARD,
}_3DLoaderPlayDirection;

typedef enum _3DLoaderImageType_e
{
    	GL3D_IMAGE_FILE = 0,
    	GL3D_IMAGE_ID,
    	GL3D_IMAGE_BITMAP
}_3DLoaderImageType;

typedef enum _3DLoaderImageState_e
{
    	GL3D_IMAGE_FOCUS_STATE = 0,
    	GL3D_IMAGE_NORMAL_STATE,
    	GL3D_IMAGE_PRESS_STATE
}_3DLoaderImageState;

typedef struct _3DLoaderObjectBitmap_t
{
	u8 * pObjectName;
	IBitmap * pBitmap;
	u16 nImageWidth;
	u16 nImageHeight;
	boolean bMirrorVert;
	boolean bMirrorHorz;
}_3DLoaderObjectBitmap;

typedef struct _3DLoaderObjectImageID_t
{
    u8 * pObjectName;
    u32 nImageID;
    boolean bMirrorVert;
    boolean bMirrorHorz;
}_3DLoaderObjectImageID;

typedef void (*WDG3DLOADER_HANDLER) (void * param1);
typedef void (*WDG3DLOADER_PICKING_CB) (u8* pObjectName, void * pUserData, u32 x, u32 y);

typedef void (*PfnWdg3DLoaderDecode) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nFrame, IWidget *pIWidget);
typedef void (*PfnWdg3DLoaderChangeImage) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nFrame, IWidget *pIWidget);
typedef void (*PfnWdg3DLoaderEnd) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nReserve, IWidget *pIWidget);
typedef void (*PfnWdg3DLoaderTSClick) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pIWidget);
typedef void (*PfnWdg3DLoaderTSPress) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nFrame, IWidget *pIWidget);
typedef void (*PfnWdg3DLoaderTSRelease) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nFrame, IWidget *pIWidget);
typedef void (*PfnWdg3DLoaderTSMove) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 nFrame, IWidget *pIWidget);

enum
{
	/* 3D Loader Widget notify events */
	Wdg3DLoader_Event_Notify_DecodeCb = 1,
	Wdg3DLoader_Event_Notify_ChangeImageCb,
	Wdg3DLoader_Event_Notify_EndCb,
	Wdg3DLoader_Event_Notify_TSClickCb,
	Wdg3DLoader_Event_Notify_TSPressCb,
	Wdg3DLoader_Event_Notify_TSReleaseCb,
	Wdg3DLoader_Event_Notify_TSMoveCb,
	Wdg3DLoader_Event_Notify_CommonCb,
	AliveWidget_Event_End
};
typedef u16 Wdg3DLoader_Event_e;

/////////////////////////////////////////////////////////////

IWidget* Wdg3dLoaderCreate(void);
IWidget* Wdg3dLoaderCreateForWnd(HWIN hWin,Pos_t *pPos,WidgetSize_t *pSize,u16 nWidgetID);
//start 3dloader renderer
MAE_Ret Wdg3dLoaderStartAnim(IWidget *pWidget);
//start 3dloader renderer and set value of count for optimize animation
MAE_Ret Wdg3dLoaderStartAnimEx(IWidget *pWidget,u32 nCountValue);
//stop 3dloader renderer
MAE_Ret Wdg3dLoaderStopAnim(IWidget *pWidget);
//pause 3dloader renderer
MAE_Ret Wdg3dLoaderPauseAnim(IWidget *pWidget);
//load 3ds content from file
MAE_Ret Wdg3dLoaderSetupForFile(IWidget *pWidget, MAE_WChar *pFileName);
//load 3ds content from memory
MAE_Ret Wdg3dLoaderSetupForMemData(IWidget *pWidget, u8 *pMemAddr, u32 nSize);
//change 3ds data
MAE_Ret Wdg3dLoaderChangeMemData(IWidget *pWidget, u8 *pMemAddr, u32 nSize);
MAE_Ret Wdg3dLoaderChangeFile(IWidget *pWidget, MAE_WChar *pFileName);
//set the start frame of renderer
MAE_Ret Wdg3dLoaderSetStartFrame(IWidget *pWidget, u32 nStartFrame);
//get the start frame of renderer
u32 Wdg3dLoaderGetStartFrame(IWidget *pWidget);
//set the end frame of renderer
MAE_Ret Wdg3dLoaderSetEndFrame(IWidget *pWidget, u32 nEndFrame);
//get the end frame of renderer
u32 Wdg3dLoaderGetEndFrame(IWidget *pWidget);
//set the repeat mode, renderer will repeat render.
MAE_Ret Wdg3dLoaderSetRepeatMode(IWidget *pWidget, boolean bRepeat);
//set bitmap for 3d object
MAE_Ret Wdg3dLoaderSetBitmap(IWidget *pWidget, u8 * pObjectName,IBitmap * pBitmap, u16 nImageWidth, u16 nImageHeight, boolean bMirrorVert,boolean bMirrorHorz);
//set press bitmap for 3d object, widget will show press image when user press the object
MAE_Ret Wdg3dLoaderSetPressBitmap(IWidget *pWidget, u8 * pObjectName,IBitmap * pBitmap, u16 nImageWidth, u16 nImageHeight, boolean bMirrorVert,boolean bMirrorHorz);
//set image id for 3d object
MAE_Ret Wdg3dLoaderSetImageID(IWidget *pWidget, u8 * pObjectName,u32 nImageID,boolean bMirrorVert,boolean bMirrorHorz);
//set press image id for 3d object, widget will show press image when user press the object
MAE_Ret Wdg3dLoaderSetPressImageID(IWidget *pWidget, u8 * pObjectName,u32 nImageID,boolean bMirrorVert,boolean bMirrorHorz);

//set common callback, if AP needs to do something.
MAE_Ret Wdg3dLoaderRegisterCommonCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderDecode pfn,void *pUserData,u32 nFrameList[], u32 nListSize);
//set decode callback, if AP needs to decode image.
MAE_Ret Wdg3dLoaderRegisterDecodeCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderDecode pfn,void *pUserData,u32 nFrame);
//set change image callback, if AP needs to change image for 3d object.
MAE_Ret Wdg3dLoaderRegisterChangeImageCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderChangeImage pfn,void *pUserData,u32 nFrame);
//set end callback, if AP needs to do something when renderer is end
MAE_Ret Wdg3dLoaderRegisterEndCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderEnd pfn,void *pUserData);
//set click/press/release callback, if AP needs to do something when user click/press/release the 3d object on UI
MAE_Ret Wdg3dLoaderRegisterTSClickCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderTSClick pfn,void *pUserData);
MAE_Ret Wdg3dLoaderRegisterTSPressCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderTSPress pfn,void *pUserData);
MAE_Ret Wdg3dLoaderRegisterTSReleaseCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderTSRelease pfn,void *pUserData);
MAE_Ret Wdg3dLoaderRegisterTSMoveCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderTSMove pfn,void *pUserData);
MAE_Ret Wdg3dLoaderDeregisterCommonCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderDecode pfn,void *pUserData);
MAE_Ret Wdg3dLoaderDeregisterDecodeCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderDecode pfn,void *pUserData);
MAE_Ret Wdg3dLoaderDeregisterChangeImageCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderChangeImage pfn,void *pUserData);
MAE_Ret Wdg3dLoaderDeregisterEndCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderEnd pfn,void *pUserData);
MAE_Ret Wdg3dLoaderDeregisterTSClickCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderTSClick pfn,void *pUserData);
MAE_Ret Wdg3dLoaderDeregisterTSPressCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderTSPress pfn,void *pUserData);
MAE_Ret Wdg3dLoaderDeregisterTSReleaseCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderTSRelease pfn,void *pUserData);
MAE_Ret Wdg3dLoaderDeregisterTSMoveCb(IWidget *pWDG3DLoader,PfnWdg3DLoaderTSMove pfn,void *pUserData);

//set the background color for 3d renderer
MAE_Ret Wdg3dLoaderSetBGBitmap(IWidget *pWidget, IBitmap * pBitmap, u16 nImageWidth, u16 nImageHeight);
MAE_Ret Wdg3dLoaderSetBGImageID(IWidget *pWidget, u32 nImageID);

MAE_Ret Wdg3dLoaderSetSingleKFMode(IWidget *pWidget, boolean bSingleKFMode,u32 nTotalAnimFrames,u32 nKeyFrameIdx);
//include object name, rotate , translate, ..., total frames.
MAE_Ret Wdg3dLoaderSetObjAnimation(IWidget *pWidget, u8 * pObjectName,float nRotateStartAngle,float nRotateEndAngle,
                float nRotatePivotX,float nRotatePivotY,float nRotatePivotZ,float nTranslateStartX,
                float nTranslateStartY,float nTranslateStartZ,float nTranslateEndX,float nTranslateEndY,float nTranslateEndZ);
MAE_Ret Wdg3dLoaderSetEasingType(IWidget *pWidget, WdgEasingType_t EasingType);
// indicate keyframe.
MAE_Ret Wdg3dLoaderSetKeyFrame(IWidget *pWidget, u32 nKeyFrame);

MAE_Ret Wdg3dLoaderSetTransparent(IWidget *pWidget, boolean bTransparent);

MAE_Ret Wdg3dLoaderSetTimerValue(IWidget *pWidget, u32 nMSecs);

MAE_Ret Wdg3dLoaderSetObjAlpha(IWidget *pWidget,u8 * pObjectName,float nStartAlpha,float nEndAlpha );

MAE_Ret Wdg3dLoaderSetObjConstAlpha(IWidget *pWidget,u8 * pObjectName,float nAlpha);

MAE_Ret Wdg3dLoaderSetPlayDirection(IWidget *pWidget, _3DLoaderPlayDirection playDirection);

//set alignment center, only for 2 triangle object (set from 3D Max)
MAE_Ret Wdg3dLoaderSetAlignCenter(IWidget *pWidget, boolean bAlignCenter);

//get the start frame from 3ds file
u32 Wdg3dLoaderGet3DFileStartFrame(IWidget *pWidget);
//get the end frame from 3ds file
u32 Wdg3dLoaderGet3DFileEndFrame(IWidget *pWidget);
//get current frame from 3dloader
u32 Wdg3dLoaderGetCurrFrame(IWidget *pWidget);

boolean Wdg3dLoaderGetSingleKFMode(IWidget *pWidget);

void Wdg3dLoaderSetSceneCap(IWidget *pWidget, u16 cap);

#endif /* __MMI_WDG_3DLOADER_H__ */
/*=============================================================*/
// end of file
