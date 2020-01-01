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
* @file mmi_kingmovieapp_3dstyle_ext.h
* @brief
* @version
*/
#ifndef __MMI_KINGMOVIEAPP_3DSTYLE_EXT_H__
#define __MMI_KINGMOVIEAPP_3DSTYLE_EXT_H__

#if defined(__MMI_KING_MOVIE__) && defined(__3D_UI_KINGMOVIE__)

#include "mae_glwidget_common.h"
#include "mae_glcirclelistwidget.h"
#include "mae_widget_common.h"
#include "mmi_mae_file_util.h"
#include "mmi_common_vtm.h"
#include "mae_abscontainerbase.h"
#include "mmi_kingmovieapp.h"
#include "mmi_accessorysrv.h"
#include "mmi_kingmovieapp_priv.h"
#include "mmi_base_util.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define KINGMOVIE_MOVIELIST_ANIM_FRAME              (1)
#define KINGMOVIE_MOVIELIST_ANIM_STEP_VALUE         (KMV_3DSTYLE_MOVIEINFOCNTR_HEIGHT / KINGMOVIE_MOVIELIST_ANIM_FRAME)
#define KINGMOVIE_MOVIELIST_ANIM_TIMER              (6)

/*=============================================================*/
// Data type definition
/*=============================================================*/
enum
{
	MovieListAnimType_Raise = 0,
	MovieListAnimType_Fall,
	MovieListAnimType_Max
};
typedef u8 KMVMovieListAnimType_e;

typedef struct KMV3DMovieInfoWdgList_t_
{
	IWidget *pImgWdg;
	IWidget *pNameWdg;
	IWidget *pTimeWdg;
	IWidget *pInfoTextWdg;
	IWidget *pViewportWdg;
	IWidget *pPlayBtnWdg;
	IWidget *pBackBtnWdg;
	IWidget *pInfoPageTextWdg;
	IWidget *pPrevPageBtnWdg;
	IWidget *pNextPageBtnWdg;
} KMV3DMovieInfoWdgList_t;

typedef struct KMV3DMovieInfoWndData_t_
{
	KMV3DMovieInfoWdgList_t tWdgList;
} KMV3DMovieInfoWndData_t;

typedef struct KMVGlCircleListWndData_t_
{
	IWidget *pGlCircleWdg;
	IWidget *pAbsContainer;
	MenuWdgList_t tWdgList;
	IWidget *pReloadBtnWdg;
	IWidget *pPlayBtnWdg;
	IWidget *pDeleteBtnWdg;
	IWidget *pFavoriteBtnWdg;
	IWidget *pInfoBtnWdg;
	IWidget *pPasswordMgrBtnWdg;
	IWidget *pBackBtnWdg;
	IWidget *pMovieNameWdg;
	IWidget *pMoviePageWdg;
	IWidget *pFocusTxtWdg;
	IWidget *pGlobalReloadBtnWdg;
	IWidget *pGlobalBackBtnWdg;	
    IWidget *pGlobalMenuTabWdg;
	VectorClass_t *pTouchActionQueue;
	Pos_t   tPress;
	u32     nPressTime;
	boolean bAnimating;
	boolean bUserPressed;
	KMVMovieListAnimType_e eAnimType;
	u16 nAnimFrame;
} KMVGlCircleListWndData_t;

/*=============================================================*/
// Window handler function definition
/*=============================================================*/
MAE_Ret KMVGlCircleListWndHdl
(
 void *pCusHandle,
 const WindowMsg_t *pWndMsg,
 void *pWndData,
 u32 nWndInitParam
 );

MAE_Ret KMV3DMovieInfoWndHdl
(
 void *pCusHandle,
 const WindowMsg_t *pWndMsg,
 void *pWndData,
 u32 nWndInitParam
 );

/*=============================================================*/
// Event callback function definition
/*=============================================================*/
boolean KingMovieTouchPressCB
(
 IApplet *pApplet,
 u32 nEvt,
 u32 nParam1,
 u32 nParam2
 );

boolean KingMovieTouchReleaseCB
(
 IApplet *pApplet,
 u32 nEvt,
 u32 nParam1,
 u32 nParam2
 );

boolean KingMovieTouchMoveCB
(
 IApplet *pApplet,
 u32 nEvt,
 u32 nParam1,
 u32 nParam2
 );

boolean KingMovieTouchClickCB
(
 IApplet *pApplet, 
 u32 nEvt, 
 u32 nParam1, 
 u32 nParam2
);

boolean KingMovie3DStyleSuspendCB
(
 IApplet *pApplet,
 u32 nEvt,
 u32 nParam1,
 u32 nParam2
 );

boolean KingMovie3DStyleResumeCB
(
 IApplet *pApplet,
 u32 nEvt,
 u32 nParam1,
 u32 nParam2
 );

MAERet_t _KMVGlCircleListWndFavoriteConfirmCB
(
 void *pApplet,
 MAEEvent_t nEvt,
 u32 nParam1,
 u32 nParam2
 );

void _KMVGlCircleListWndDeleteConfirmCB
(
 void *pIApplet,
 KMVCategoryType_e eCateIdx
 );

void _KMVGlCircleListWndDeleteLastplayConfirmCB
(
 void *pIApplet
 );

void _KMVStartMovieListAnimation
(
 KingMovieAppData_t *pThis,
 KMVMovieListAnimType_e eType
 );

void  _KMVMovieListSetFocusAnimationCB
(
 void *pUser
 );

void KingMovieTouchHandleQueueAction(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

void KingMovieCaptureBg(IApplet *pApplet) ;

#endif //end of #if defined(__MMI_KING_MOVIE__) && defined(__3D_UI_KINGMOVIE__)

#endif //end of #ifdef __MMI_KINGMOVIEAPP_3DSTYLE_EXT_H__
