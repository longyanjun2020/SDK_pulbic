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
* @file    mmi_mplayerapp_3d.h
* @version
* @brief   Media player 3d header file
*
*/

#ifndef __MMI_MPLAYERAPP_3D_H__
#define __MMI_MPLAYERAPP_3D_H__


#if defined(__3D_UI_COVERFLOW_MMI__)
#include "mmi_wdg_glcoverflowwidget.h"
#include "mmi_wdg_glwidget_common.h"
#endif  //__3D_UI_COVERFLOW_MMI__

#ifdef __3D_UI_MPLAYER__
#include "mmi_mplayerapp_priv.h"
#include "mae_animation.h"
#include "mmi_wdg_gltransformwidget.h"
#include "mae_glflipeffectwidget.h"
#include "mgl_Effect_BezierSurface.h"
#include "mae_widget_common.h"
#include "mmi_wdg_spectrumwidget.h"
#include "mmi_wdg_glalbumslidewidget.h"
#include "mae_glwidget_common.h"
#endif //__3D_UI_MPLAYER__


#if defined(__3D_UI_COVERFLOW_MMI__)
MAE_Ret _MPlayerWnd3DCoverFlowCreateView(MMI_MPLAYERAPP *pThis, HWIN hWin, MP_COVER_FLOW_VIEW_WdgList *pWdgList);
MAE_Ret _MPlayerWnd3DCoverFlowCreateWnd(MMI_MPLAYERAPP *pThis, CoverFlowWndData_t *pWndData);
void _MPlayerWnd3DCoverFlowEventCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWnd3DCoverFlowCoverBmpElementVectorClassFree(void *pData, void *pOwner);
void _MPlayer3DCoverDecodeNotify(IImage *pIImage, IBase *pData, ImgStatus_t nStatus);
#endif //__3D_UI_COVERFLOW_MMI__


#ifdef __3D_UI_MPLAYER__

#define MPLAYER_FOTO_ROTATE_TOTAL_FRAME (3)
#define MPLAYER_FOTO_ROLLBACK_STEPS (3)
#define MPLAYER_FOTO_ROLLBACK_END_POS_X (RS_GL_MPLAYERAPP_INFO_ABSCONTAINER_X_POSITION)
#define MPLAYER_FOTO_ROLLBACK_END_POS_Y (RS_GL_MPLAYERAPP_INFO_ABSCONTAINER_Y_POSITION)
#define MPLAYER_FOTO_ROLLBACK_SHIFT_OFFSETS (20)
#define MPLAYER_FOTO_ROLLBACK_ANIMATION_TYPE (ANIMATION_EASE_OUT_QUAD)
#define MPLAYER_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_FRAME (2)
#define MPLAYER_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_MIN_POS (200)
#define MPLAYER_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_MAX_POS (200)
#define __MPLAYER_ZOOMIN_EFFECT_HIDE_TEXTWDG__

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Global function prototype declaration
/*=============================================================*/

void _G3DMPLAYERAPP_PauseSpectrum(MMI_MPLAYERAPP * pThis);
void _G3DMPLAYERAPP_ResumeSpectrum(MMI_MPLAYERAPP * pThis);
void _MPlayerWndNowplaying3DPlaybackButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWndNowplaying3DPlayNextButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWndNowplaying3DPlayPreviousButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
MAE_Ret _G3DMPLAYERAPP_GetPlaylistContent(MMI_MPLAYERAPP *pThis);
MAE_Ret _G3DMPLAYERAPP_PlaylistContentUpdateMenuIcon(MMI_MPLAYERAPP *pThis, IWidget *pMenuWdg, u32 nUpdateIndex, u32 nImageId);
MAE_Ret _G3DMPLAYERAPP_StartAnimation(MMI_MPLAYERAPP *pThis);
MAE_Ret _G3DMPLAYERAPP_StartRollBackAnimation(MMI_MPLAYERAPP *pThis, boolean bNext);
void _G3DMPLAYERAPP_StartZoomInAnimCntr(MMI_MPLAYERAPP* pThis, IWidget *pWidget, u32 nParam);
MAE_Ret _G3DMPLAYERAPP_SwitchPlaylist(MMI_MPLAYERAPP * pThis);
MAE_Ret _G3DMPLAYERAPP_InitPlaylist(MMI_MPLAYERAPP * pThis);
void _G3DMPLAYERAPP_GetPlaylistData(MMI_MPLAYERAPP *pThis);
MAE_Ret _G3DMPLAYERAPP_SearchPlaylistIndexByName(MMI_MPLAYERAPP *pThis, MAE_WChar *strPlaylistName, boolean bIsPlayingPredef, u32 *pnPlaylistIdx);
void  _G3DMPLAYERAPP_InitAfterReloadPlaylistDataModel(MMI_MPLAYERAPP * pThis, u32 nResultEvent, IDataModel *pPlaylistDataModel);
void  _G3DMPLAYERAPP_AfterReloadPlaylistDataModel(MMI_MPLAYERAPP * pThis, u32 nResultEvent, IDataModel *pPlaylistDataModel);
void _G3DMPLAYERAPP_ReloadPlaylistDataModel(MMI_MPLAYERAPP * pThis);
MAE_Ret _G3DMPLAYERAPP_UpdateDurationText(MMI_MPLAYERAPP *pThis, u32 uTotalTime, IWidget *pTextWidget);
MAE_Ret _G3DMPLAYERAPP_UpdateTotalDurationText(MMI_MPLAYERAPP *pThis, u32 uTotalTime);
void _G3DMPLAYERAPP_StartFlipEffect(MMI_MPLAYERAPP * pThis, boolean bNext);
MAE_Ret _MPlayerWndNowplayingCreate3DView(MMI_MPLAYERAPP *pThis, HWIN hWin, MP_NOWPLAYING_VIEW_WdgList *pWdgList);
MAE_Ret _MPlayerWndNowplayingCreate3DWnd(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
MAE_Ret _MPlayerWndNowplayingDestroy3DWnd(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
MAE_Ret MPlayerWndCreate3DNowplaying(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroy3DNowplaying(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvert3DNowplaying(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndShow3DNowplaying(void *pCusHandle, void *pWndData);

void _G3DMPLAYERAPP_ListRotateLeftAnimWdgCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _G3DMPLAYERAPP_FotoListRotateLeftAnimWdgCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _G3DMPLAYERAPP_FotoListRotateRightAnimWdgCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _G3DMPLAYERAPP_ListRotateRightAnimWdgCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _G3DMPLAYERAPP_SlideEffectStart(MMI_MPLAYERAPP * pThis, boolean bNext, boolean bStart);
void _G3DMPLAYERAPP_SlideEffectWdgCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _G3DMPLAYERAPP_SlideEffect_DelayDeleteWdgTimerCB(void* pApplet);
MAE_Ret _G3DMPLAYERAPP_Update_RepeatIcon(MMI_MPLAYERAPP *pThis, IWidget *pRepeatBtnWdg);
void  _G3DMPLAYERAPP_AudFileInfoCB(void *pData, MediaSrvErrCode_e eErrorCode, u32 nCusData, AudioSrvFileInfo_t *pAudFileInfo);
MAE_Ret _G3DMPLAYERAPP_GetFileInfo(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerWndNowplaying3DSetIndicatorText(MMI_MPLAYERAPP *pThis, IWidget *pIndicatorTextWidget);
void _MPlayer3DPlayingIndexCB(MMI_MPLAYERAPP *pThis);
void _MPlayerWndNowplaying3DLoadPlaylistDataCB(MMI_MPLAYERAPP* pThis, PLAYLISTSRV_Rquest_Result_e eResult, IDataModel *pPlaylistDataModel);
void _MPlayer3DStartCB(MMI_MPLAYERAPP* pThis);
void _MPlayerWndNowplaying3DTouchClickCB(MMI_MPLAYERAPP* pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _MPlayerWndNowplaying3DTouchLeftCB(MMI_MPLAYERAPP* pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _MPlayerWndNowplaying3DTouchRightCB(MMI_MPLAYERAPP* pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _MPlayer3DHandlePauseSuccessStopCnf(MMI_MPLAYERAPP* pThis, SrvAudioPlayerPlayStatus_e ePlayStatus);
void _MPlayer3DHandleEndPlaying(MMI_MPLAYERAPP* pThis);
void _MPlayer3DHandlePlaySuccess(MMI_MPLAYERAPP* pThis, u32 nOldIndex);
void _MPlayer3DWndNewPlaylistSave(MMI_MPLAYERAPP* pThis);
void _MPlayer3DPlayMusicHandleStopSuccessCommandSkip(MMI_MPLAYERAPP* pThis, MplayerNotifyType_e eNotifyType, NowplayingWndData_t *pWndData);
boolean _MPlayer3DIsNeededFlipEffect(MMI_MPLAYERAPP * pThis);

#ifdef __MPLAYERAP_ID3V2_IMG__
void _MPlayer3DID3ImageFreeFunc(void *pData);
void _MPlayer3DID3ImageDecodeNotifyCb(IImage* pImage, IBase* pOwner, ImgStatus_t tStatus);
void _MPlayerWndNowplaying3DDisplayCoverImg(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
void _MPlayerWndNowplaying3DUpdateCoverImgInfo(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
#endif

#endif /* __3D_UI_MPLAYER__ */
#endif /* __MMI_MPLAYERAPP_3D_H__ */

