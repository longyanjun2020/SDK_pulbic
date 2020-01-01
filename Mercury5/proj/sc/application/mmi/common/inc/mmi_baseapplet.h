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
* @file    mmi_baseapplet.h
* @version
* @brief   Base applet header file
*
*/

#ifndef __MMI_BASEAPPLET_H__
#define __MMI_BASEAPPLET_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_api.h"
#include "mmi_mae_types.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_window.h"
#include "mmi_mae_bitmap_types.h"
#include "mmi_mae_graphic.h"
#include "mmi_mae_common_content.h"
#include "mmi_mae_clock_base.h"
#include "mmi_mae_clock_types.h"
#include "mmi_mae_config.h"
#include "mmi_mae_config_types.h"
#include "mmi_mae_dib.h"
#include "mmi_mae_dib_types.h"
#include "mmi_mae_font.h"
#include "mmi_mae_font_types.h"
#include "mmi_mae_imagemaker.h"
#include "mmi_mae_imagemaker_types.h"
#include "mmi_mae_util.h"
#include "mmi_mae_thmmgr.h"
#include "mmi_mae_customization_types.h"
#include "mmi_mae_resource_types.h"
#include "mmi_mae_sensormgr_types.h"
#include "mmi_mae_touchsrv_types.h"
#include "mmi_mae_viewmgr.h"
#include "mmi_mae_subwindow.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_text.h"
#include "mmi_wdg_image.h"
#include "img_data.h"
#include "mmi_common_util.h"
#include "mmi_common_appletprop.h"
#include "mmi_subject.h"
#include "mmi_blockingsubject.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/
typedef struct APPStatus_t_
{
    unsigned int nKeyCount : 4;
    unsigned int bReceiveAllEvts : 1;
    unsigned int bInitFail : 1;
    //unsigned int Reserved : 26;
}APPStatus_t;

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define BEGIN_EVENTCB_TABLE(g_tEventToFuncCBTbl) \
    static const EventToFuncCB_t g_tEventToFuncCBTbl[] = {

#define END_EVENTCB_TABLE   \
{MAE_EVT_NONE,  NULL}}

#define APPLET_BASE_FUNCTBL \
    DECLARE_FUNCTBL(IApplet)

#define APPLET_BASE_ELEMENTS \
    DECLARE_FUNCTBL(IApplet);\
    u32 nRefCnt;            \
    IViewMgr *pViewMgr;     \
    IWndMgr *pWndMgr;       \
	IDisplay *pMainDisplay;       \
	IDisplay *pSubDisplay;       \
    const EventToFuncCB_t *pEvtToCBTbl;   \
    void *pClientTbl;       \
    void *pCBModule ;       \
    u32 nAppInterruptible ;    \
    u32 nEnabledHotKey; \
    APPStatus_t nAPStatus;    \
	void *pLauncherData;    \
	u32 nAppSceneHandleId;  \
	u16 nAPResId;  \
	PFN_LauncherCleanCb pfnLauncherCleanCb;\
    MultiBKLSetting *pBacklightSetting; \
    boolean bUseDefaultBacklightSetting; \
    boolean bMultiTouch

#define LOAD_APP_RESOURCE(nAPResId)   BaseAppletLoadApResource(NULL, nAPResId)
/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef boolean (*AppFuncCB)( IApplet *, u32, u32, u32 );
/*===================================================================================*/
// typedef boolean (*AppFuncHandler)( IApplet *, MAEEvent_t, u32, u32 );
// typedef MAE_Ret    (*AppConstructor) ( IApplet * );
// typedef MAE_Ret    (*AppDestructor) ( IApplet * );
// typedef boolean    (*AppHookDraw) ( IApplet *, const MAE_DispId_t , Rect_t *, boolean );
// typedef boolean    (*AppHookIsFullOpaque) ( IApplet *, const MAE_DispId_t );
// typedef boolean    (*AppHookGetInvalidateRect) ( IApplet *, const MAE_DispId_t, Rect_t * );
/*===================================================================================*/
typedef void (*PFN_LauncherCleanCb)(void *);
typedef struct
{
    MAEEvent_t tEvtId;
    AppFuncCB pfn;
}EventToFuncCB_t;

typedef struct
{
    APPLET_BASE_ELEMENTS;
}BaseApplet_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** BaseAppletAddRef
* @brief      IBase Interface
*
* @param[in]  pApplet
*
* @retval     u32                    Object reference count
*
*/
u32 BaseAppletAddRef
(
    IApplet         *pApplet
);

/** BaseAppletRelease
* @brief      IBase Interface
*
* @param[in]  pApplet
*
* @retval     u32                    Object reference count
*
*/
u32 BaseAppletRelease
(
    IApplet         *pApplet
);

/** BaseAppletQueryInterface
* @brief      IBase Interface
*
* @param[in]  pApplet
* @param[in]  IId                       Interface Id
* @param[out] ppObj
* @param[in]  pOwner                    The owner instance
*
* @retval     MAE_RET_SUCCESS           Success
* @retval     MAE_RET_BAD_PARAM         Bad Parameter
* @retval     MAE_RET_NOT_SUPPORTED     Not support
*
*/
MAE_Ret BaseAppletQueryInterface
(
    IApplet         *pApplet,
    MAE_IId         IId,
    void            **ppObj,
    IBase           *pOwner
);

/** BaseAppletHandleEvent
* @brief      IHandler Interface
*
* @param[in]  pApplet
* @param[in]  nEvt                      Event Id
* @param[in]  nParam1
* @param[in]  nParam2
*
* @retval     TRUE                      Event is handled
* @retval     FALSE                     Event needs to pass to another handler
*
*/
boolean BaseAppletHandleEvent
(
    IApplet         *pApplet,
    MAEEvent_t      nEvt,
    u32             nParam1,
    u32             nParam2
);

/** BaseAppletDraw
* @brief      IApplet Interface
*
* @param[in]  pApplet
* @param[in]  pDispInfo            Display Information(Display id and Display handle)
* @param[in]  pRect
* @param[in]  isTopAp
*
*/
void BaseAppletDraw
(
    IApplet             *pApplet,
    const MAE_DispId_t  nDisplayId,
    Rect_t              *pRect,
    boolean             bIsTopAp
);

/** BaseAppletDrawOnBmp
* @brief      Draw the applet on a given bitmap, include all window in this applet
*
* @param[in]  pApplet
* @param[in]  nDisplayId            Display ID
* @param[in]  pRect
* @param[in]  pBmp
*
*/
void BaseAppletDrawOnBmp
(
    IApplet             *pApplet,
    const MAE_DispId_t  nDisplayId,
    Rect_t              *pRect,
    IBase             *pBmp
);

/** BaseAppletPrepareTransitionFrame
* @brief      Draw currently top window only, except softkey and status bar,
*                the result will be keep on a special IBitmap, and used as previous frame in transition
*
* @param[in]  pApplet
*
*/
void BaseAppletPrepareTransitionFrame(IApplet *pApplet);

/** BaseAppletIsFullOpaque
* @brief      IApplet Interface
*
* @param[in]  pApplet
* @param[in]  pDispInfo            Display Information(Display id and Display handle)
*
* @retval     TRUE
* @retval     FALSE
*
*/
boolean BaseAppletIsFullOpaque
(
    IApplet             *pApplet,
    const MAE_DispId_t  nDisplayId
);

/** BaseAppletGetInvalidateRect
* @brief      IApplet Interface
*
* @param[in]  pApplet
* @param[in]  pDispInfo            Display Information(Display id and Display handle)
* @param[in]  pRect
*
* @retval     TRUE
* @retval     FALSE
*
*/
boolean BaseAppletGetInvalidateRect
(
    IApplet             *pApplet,
    const MAE_DispId_t  nDisplayId,
#ifdef __AP_USE_ML__
    Rect_t              **pRect
#else
	Rect_t              *pRect
#endif
);

/** BaseAppletGetClientTable
* @brief      IApplet Interface, for service
*
* @param[in]  pApplet
*
* @retval                   A pointer to Client Table
*
*/
void * BaseAppletGetClientTable
(
    IApplet        *pApplet
);

/** BaseAppletGetCBListModule
* @brief      IApplet Interface, for service
*
* @param[in]  pApplet
*
* @retval                   A pointer to Callback List
*
*/
void * BaseAppletGetCBListModule
(
    IApplet        *pApplet
);

/** BaseAppletDisplayInvisible
* @brief      IApplet Interface, for service
*
* @param[in]  pApplet
*
*
*/
void BaseAppletDisplayInvisible
(
    IApplet     *pApplet,
    MAE_DispId_t nDisp,
    boolean     bIsVisible
);

//3Dswitch
/** BaseAppletUpdate3DMode
* @brief      IApplet Interface, for 2d/3d dynamic switch
*
* @param[in]  pApplet
*
*
*/
boolean BaseAppletUpdate3DMode
(
    IApplet     *pApplet
);


/** BaseAppletRestoreThm
* @brief      IApplet Interface, for restore applet private theme when switch context
*
* @param[in]  pApplet
*
*
*/
void BaseAppletRestoreThm
(
    IApplet     *pApplet
);

/** BaseAppletInit
* @brief      Common applet initial function
*
* @param[in]  nClsId                The class Id.
* @param[in]  ppObj
* @param[in]  nSize                 Applet structure size,
* @param[in]  pEvtCB                Pointer to event to callback table
*
* @retval     MAE_RET_SUCCESS        Success
* @retval     others                Failed
*
*/

MAE_Ret BaseAppletInit
(
    MAE_ClsId       nClsId,
    void            **ppObj,
    u32             nSize,
    const EventToFuncCB_t *pEvtCB
 );

/** BaseAppletUninit
* @brief      Free base elements
*
* @param[in]  ppObj
*
* @retval     MAE_RET_SUCCESS       Success
* @retval     others                Failed
*
*/
void BaseAppletUninit(void **ppObj);

/** BaseAppletDefDraw
* @brief      IApplet Interface
*
* @param[in]  pApplet
* @param[in]  nDisplayId            Display Id
* @param[in]  pRect
* @param[in]  isTopAp
*
*/
void BaseAppletDefDraw
(
    IApplet         *pApplet,
    MAE_DispId_t   nDisplayId,
    Rect_t          *pRect,
    boolean         bIsTopAp
);

/** BaseAppletDefIsFullOpaque
* @brief      IApplet Interface
*
* @param[in]  pApplet
* @param[in]  nDisplayId            Display Id
*
* @retval     TRUE
* @retval     FALSE
*
*/
boolean BaseAppletDefIsFullOpaque
(
    IApplet         *pApplet,
    MAE_DispId_t    nDisplayId
);

/** BaseAppletDefGetInvalidateRect
* @brief      IApplet Interface
*
* @param[in]  pApplet
* @param[in]  nDisplayId            Display Id
* @param[in]  pRect
*
* @retval     TRUE
* @retval     FALSE
*
*/
boolean BaseAppletDefGetInvalidateRect
(
    IApplet         *pApplet,
    MAE_DispId_t    nDisplayId,
#ifdef __AP_USE_ML__
    Rect_t          **pRect
#else
	Rect_t          *pRect
#endif
);

/** BaseAppletDisableTransition
* @brief      This is used to disable Applet entry/exit transition.
*             Call this in AppNew function or MAE_EVT_CONSTRUCT callback function.
*
* @param[in]  pApplet
*
* @retval     void
*
*/
void BaseAppletDisableTransition(IApplet *pApplet);

/** BaseAppletSetTransition
* @brief      This is used to set Applet entry/exit transition Id by transition property.
*
* @param[in]  pApplet
* @param[in]  eAppTransProp  The transition property.
* @param[in]  nTransId(u32)  The transition ID.
*
* @retval     void
*
*/
void BaseAppletSetTransition(IApplet *pApplet, AppTransitionProp_e eAppTransProp, u32 nTransId);

/** BaseAppletGetDisplay
* @brief      This is used to get the instance of display for certain Applet
*
* @param[in]  pApplet
*
* @param[in]  nDispId
*
* @retval     IDisplay
*
*/
IDisplay* BaseAppletGetDisplay(IApplet *pApplet, MAE_DispId_t nDispId);

/** BaseAppletReceiveAllEvents
* @brief      This is used to receive all events by App. Normally, when a event passed to App,
*             view manager will handle it at first: view manager will ask all the widgets if wanted to handle.
*             If the widget handled this event, this event will no more pass to App.
*
* @param[in]  pApplet
*
* @param[in]  bIsReceivedAllEvts    If TRUE, the app will also receive the event even if one widget handled.
*
* @retval     void
*
*/
void BaseAppletReceiveAllEvents(IApplet *pApplet, boolean nAPStatus);

/** BaseAppletSubjectSubscribe
* @brief      This is used to subscribe some subject for Applet (ex: Memory subject, USB subject etc.).
*             Compare with SubjectScribe, this function is for Applet only.
*
* @param[in]  pSbjName          Subject's name
*
* @param[in]  pUser             pApplet
*
* @param[in]  pfnCB             When subject's status changes, this function will be called to let pUser know the subject's status.
*
* @param[in]  eSuccessStatus    Subscribe will return success when subject's status is in eSuccessStatus, otherwise it will return MAE_RET_FAILED.
*
* @param[in]  eAutoHandleStatus When subject's status changes to eAutoHandleStatus, subject will call subject's default handler to handle status change.
*                               When subject changes its status to some status not in eAutoHandleStatus, subject will call user defined callback pfnCB.
*                               If eAutoHandleStatus = SUBJECT_NO_AUTO_HANDLE, subject will always call user defined callback pfnCB.
*
* @retval     MAE_RET_SUCCESS
* @retval     MAE_RET_FAILED
* @retval     MAE_RET_NOT_FOUND
*
*/
MAE_Ret BaseAppletSubjectSubscribe(char *pSbjName, void *pUser, PfnSubjectListener pfnCB, SubjectStatus_e eSuccessStatus, SubjectStatus_e eAutoHandleStatus);

/** BaseAppletSubjectUnSubscribe
* @brief      This is used to unsubscribe some subject for Applet (ex: Memory subject, USB subject etc.).
*             Compare with SubjectUnScribe, this function is for Applet only.
*
* @param[in]  pSbjName
*
* @param[in]  pUser
*
* @retval     MAE_RET_SUCCESS
* @retval     MAE_RET_FAILED
*
*/
MAE_Ret BaseAppletSubjectUnSubscribe(char *pSbjName, void *pUser);

/** BaseAppletSubjectUnSubscribeAll
* @brief      This is used to unsubscribe ALL subject for Applet. This function will be called automatically
*             in BaseAppletUninit().
*
* @param[in]  pUser
*
* @retval     MAE_RET_SUCCESS
* @retval     MAE_RET_FAILED
*
*/
MAE_Ret BaseAppletSubjectUnSubscribeAll(void *pUser);

/** BaseAppletLoadApResource
* @brief      It will load the CUS data for the specific resource id nAPResId
*
* @param[in]  pApplet
*
* @param[in]  nAPResId
*
* @retval     MAE_RET_SUCCESS
* @retval     MAE_RET_FAILED
* @retval     MAE_RET_NOT_FOUND
*/
MAE_Ret BaseAppletLoadApResource(IApplet *pApplet, u16 nAPResId);

#if defined(__FEATURE_MGL__)
/** BaseAppletGetSceneHandleId
* @brief      This API is used to get the scene ID for this applet that recorded before.
*             The scene ID is got from calling mgl_SceneMgr_Create(). Every applet should use its own scene ID to draw 3D object.
*
* @param[in]  pApplet           Point to an IApplet structure.
*
* @param[in]  pSceneHandleId    The scene ID recorded in baseapplet before.
*
* @retval     MAE_RET_SUCCESS   This value means operation success.
*             MAE_RET_BAD_PARAM This value means there are some miss-matched input parameters.
*             MAE_RET_FAILED    This value means there is no correct scene ID.
*
*/
MAE_Ret BaseAppletGetSceneHandleId(IApplet *pApplet, u16 *pSceneHandleId);

/** BaseAppletSetSceneHandleId
* @brief      This API is used to record the scene ID for this applet.
*             The scene ID is got from calling mgl_SceneMgr_Create(). Every applet should use its own scene ID to draw 3D object.
*
* @param[in]  pApplet           Point to an IApplet structure.
*
* @param[in]  nSceneHandleId    The scene ID that applet got from calling mgl_SceneMgr_Create().
*
* @retval     MAE_RET_SUCCESS   This value means operation success.
*             MAE_RET_BAD_PARAM This value means there are some miss-matched input parameters.
*
*/
MAE_Ret BaseAppletSetSceneHandleId(IApplet *pApplet, u16 nSceneHandleId);
#endif


/** BaseAppletGetDisplayInvisible
* @brief      get this applet is visible or not
*
* @param[in]  pApplet           Point to an IApplet structure.
* @param[in]  nDisp              Display ID.
*
* @retval     the applet is invisible or not.
*
*/
boolean BaseAppletGetDisplayInvisible(IApplet *pApplet, MAE_DispId_t nDisp);

MAE_Ret BaseAppletSetMultiTouch(IApplet *pApplet, boolean bEnable);
boolean BaseAppletGetMultiTouch(IApplet *pApplet);

#endif // __MAE_APPLETBASE_H__

