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
* @file    mmi_mplayerapp_priv.h
* @version
* @brief   Media player applet private header file
*
*/

#ifndef __MMI_MPLAYERAPP_PRIV_H__
#define __MMI_MPLAYERAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
//AP
#include "mmi_mplayerapp.h"
#include "mmi_common_mimetype.h"
#include "mmi_common_util.h"
#include "mmi_common_custom.h"
#include "mmi_common_dialog_id.h"
#include "mmi_baseapplet.h"
#include "mmi_srv_header.h"
#include "mmi_common_vtm.h"
#include "mmi_mplayerapp_id.h"
#include "mplayerapp_resource.h"

#ifdef __3D_UI_MPLAYER__
#include "mae_animation.h"
#include "mmi_wdg_gltransformwidget.h"
#include "mae_glflipeffectwidget.h"
#include "mgl_Effect_BezierSurface.h"
#endif

#include "mmi_launcher_common.h"
#include "mmi_launcher_filemanager.h"

#ifdef  __G_SENSOR_MMI__
#ifdef  __COVER_FLOW_MMI__
#define __MPLAYERAP_GMOTION_ROTATE__

enum
{
	// This is decoding cover order.
	COVER_LEFT_1,
	COVER_RIGHT_1,
	COVER_LEFT_2,
	COVER_RIGHT_2,
	COVER_MIDDLE,
	NUM_COVERS
};

#define NO_COVER_TO_DECODE (0xFFFF)
#endif /* __COVER_FLOW_MMI__ */
#define __MPLAYERAP_GMOTION_SHAKE__
#endif /* __G_SENSOR_MMI__ */

#if !defined(__APP_MMI_SMALLROM__)
#define __MPLAYERAP_SHOW_SEEK_BAR__
#ifdef __MMI_AUDIO_SEEK__
#if defined(__TOUCH_SCREEN_MMI__) && defined(__MPLAYERAP_SHOW_SEEK_BAR__)
#define __MPLAYERAP_TOUCH_SEEK__
#endif //
#define __MMI_MPLAYERAPP_FF_REWIND__
#endif
#endif //

#ifdef __MMI_ID3_SUPPORT__
#define __MPLAYERAP_ID3_INFO__
#endif

#if defined(__LCM_WVGA__) || defined(__LCM_LANDSCAPE_WVGA__) || defined(__LCM_HVGA_320_480__) || defined(__LCM_LANDSCAPE_HVGA__) || defined(__LCM_WQVGA_240_400__) || defined(__LCM_LANDSCAPE_WQVGA_240_400__) || defined(__LCM_QVGA__) || defined(__LCM_LANDSCAPE_QVGA__) || defined(__LCM_LANDSCAPE_QCIF__) || defined(__LCM_QCIF_PLUS__)
#if !defined(__APP_MMI_SMALLROM__)
#define __MPLAYERAP_NEW_UI__
#if defined(__MPLAYERAP_ID3_INFO__)
#define __MPLAYERAP_ID3V2_IMG__
#endif
#endif
#endif
//*******************************************************************//
#if defined(__LANTERN_BY_AUDIO__) && !defined(__APP_MMI_SMALLROM__) && !defined(__3D_UI_MPLAYER__)
#define __MPLAYERAP_SPECTRUM__
#define NOWPLAY_SPECTRUM_INTERVAL           (75)
#define NOWPLAY_SPECTRUM_LEVEL_QUANTIZER    (5)

typedef enum
{
    MMI_MPLAYER_SpectrumLevel_0=0,
    MMI_MPLAYER_SpectrumLevel_1=1,
    MMI_MPLAYER_SpectrumLevel_2=2,
    MMI_MPLAYER_SpectrumLevel_3=3,
    MMI_MPLAYER_SpectrumLevel_4=4,
    MMI_MPLAYER_SpectrumLevel_5=5,
    MMI_MPLAYER_SpectrumLevel_6=6,
    MMI_MPLAYER_SpectrumLevel_7=7,
    MMI_MPLAYER_SpectrumLevel_8=8,
    MMI_MPLAYER_SpectrumLevel_9=9,
    MMI_MPLAYER_SpectrumLevel_10=10,
    MMI_MPLAYER_SpectrumLevel_11=11,
    MMI_MPLAYER_SpectrumLevel_12=12,
    MMI_MPLAYER_SpectrumLevel_13=13,
    MMI_MPLAYER_SpectrumLevel_14=14,
    MMI_MPLAYER_SpectrumLevel_15=15,
    MMI_MPLAYER_SpectrumLevel_16=16,
    MMI_MPLAYER_SpectrumLevel_Min=MMI_MPLAYER_SpectrumLevel_0,
    MMI_MPLAYER_SpectrumLevel_Max=MMI_MPLAYER_SpectrumLevel_16
} MPlayerSpectrumLevel_e;
typedef enum
{
    NOWPLAY_SPECTRUM_BAR_1 = 0,
    NOWPLAY_SPECTRUM_BAR_2,
    NOWPLAY_SPECTRUM_BAR_3,
    NOWPLAY_SPECTRUM_BAR_4,
    NOWPLAY_SPECTRUM_BAR_5,
    NOWPLAY_SPECTRUM_BAR_6,
    NOWPLAY_SPECTRUM_BAR_7,
    NOWPLAY_SPECTRUM_BAR_8,
    NOWPLAY_SPECTRUM_BAR_9,
    NOWPLAY_SPECTRUM_BAR_10,
    NOWPLAY_SPECTRUM_BAR_11,
    NOWPLAY_SPECTRUM_BAR_12,
    NOWPLAY_SPECTRUM_BAR_13,
    NOWPLAY_SPECTRUM_BAR_14,
    NOWPLAY_SPECTRUM_BAR_15,
    NOWPLAY_SPECTRUM_BAR_16,
    NOWPLAY_SPECTRUM_BAR_NUM
} MPlayerSpectrumIndex_e;
#endif

typedef enum
{
    MPLAYER_GOTOTIME_NONE = 0,
    MPLAYER_GOTOTIME_SEEKCMD,
    MPLAYER_GOTOTIME_SEEKING
} MPlayerGoToTimeState_e;

#ifdef __MPLAYERAP_ID3V2_IMG__
typedef enum MplayerPictureType_e_
{
    MPLAYER_PICTURE_DEFAULT,
    MPLAYER_PICTURE_PLYAYLIST_COVER,
    MPLAYER_PICTURE_ID3V2_IMAGE,
    MPLAYER_PICTURE_MAX_NUM
} MplayerPictureType_e;
#endif

typedef struct
{
#ifndef __MPLAYERAPP_SMALLROM__
    IWidget *pMP_NOWPLAYING_BG_IMAGEWIDGET;
#endif
#ifdef __MPLAYERAP_NEW_UI__
    IWidget *pPlayListCoverWdg;
#endif
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
    IWidget *pLyricsTextWdg;
#endif
    IWidget *pID3TitleImageWdg;
    IWidget *pID3AlbumImageWdg;
    IWidget *pID3ArtistImageWdg;
    IWidget *pVolumeIncreaseButtonWdg;
    IWidget *pVolumeDecreaseButtonWdg;
    IWidget *pMP_NOWPLAYING_EMPTY_VOLUME_IMAGEWIDGET;
    IWidget *pVolumeImageWdg;
    IWidget *pID3TitleTextWdg;
    IWidget *pID3AlbumTextWdg;
    IWidget *pID3ArtistTextWdg;
    IWidget *pIndicatorTextWdg;
    IWidget *pIndexTextWdg;
    IWidget *pRepeatButtonWdg;
#ifdef __MMI_MPLAYER_3DSURROUND_ENABLE__
    IWidget *p3DSurroundSwitchIconWdg;
#endif
    IWidget *pShuffleSwitchIconWdg;
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
    IWidget *pLyricsSwitchIconWdg;
#endif
    IWidget *pPlayPreviousButtonWdg;
    IWidget *pPlaybackButtonWdg;
    IWidget *pPlayNextButtonWdg;
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
    IWidget *pBatteryWdg;
    IWidget *pBatteryBgWdg;
#endif
#ifdef __MPLAYERAPP_SMALLROM__
    IWidget *pTitleBarImageWdg;
    IWidget *pBgImageWdg;
#endif
#ifdef __MPLAYERAP_SHOW_SEEK_BAR__
    IWidget *pIndicatorWdg;
#endif
#ifdef __MPLAYERAP_SPECTRUM__
    IWidget *pSpectrumSwitchIconWdg;
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
    IWidget *pSpectrumLyricTextWdg;
#endif
    IWidget *pSpectrumTitleTextWdg;
    IWidget *pSpectrumTitleImageWdg;
    IWidget *pSpectrumBarContainer;
    IWidget *pSpectrumBarBgListWdg;
    IWidget *pSpectrumDegreeImageWdg;
    IWidget *paSpectrumBarImageWdg[NOWPLAY_SPECTRUM_BAR_NUM];
#endif
#ifdef __3D_UI_MPLAYER__
    IWidget *pInfoAbsCntr;
    IWidget *pGLRotateAbsCntr;
    IWidget *pGLFotoListFlipWdg;
    IWidget *pGLFotoListCntr;
    IWidget *pGLFotoListWdg;
    IWidget *pGLFotoListImgWdg;
    IWidget *pListFlipWdg;
    IWidget *pListRotateAbsCntr;
    IWidget *pListAbsCntr;
    IWidget *pListMenuWdg;
    IWidget *pListImgWdg;
    IWidget *pListMenuButtonWdg;
    IWidget *pListBackButtonWdg;
    IWidget *pLyricAbsCntr;
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
    IWidget *pLyricImgWdg;
    IWidget *pLyricMenuButtonWdg;
    IWidget *pLyricBackButtonWdg;
#endif
    IWidget *pControlBarWdg;
    IWidget *pControlBarImageWdg;
    IWidget *pDurationTotalTextWdg;
    IWidget *pGLAlbumSlideWdg;
    IWidget *pMainAnimCntr;
    IWidget *pSpectrumWdg;
#endif
}MP_NOWPLAYING_VIEW_WdgList;

#if defined(ENABLE_SRSWOWHD)
typedef struct
{
    IWidget *pMflContainer;
    IWidget *pSRSStatusCmnPickWdg;
    IWidget *pSRSTypeCmnPickWdg;
} MP_SRSSETTING_VIEW_WdgList;

typedef struct
{
    IWidget *pMflContainer;
    IWidget *pScrollbarWdg;
    IWidget *pSRSTruBassCmnPickWdg;
    IWidget *pSRS3DCenterCmnPickWdg;
    IWidget *pSRS3DSpaceCmnPickWdg;
    IWidget *pSRSFocusCmnPickWdg;
    IWidget *pSRSDefinitionCmnPickWdg;
} MP_SRSPARAM_VIEW_WdgList;
#endif // defined(ENABLE_SRSWOWHD)

//*******************************************************************//

typedef struct
{
    IWidget *pAbsContainer;
    IWidget *pLeft2CoverImageWdg;
    IWidget *pRight2CoverImageWdg;
    IWidget *pLeft1CoverImageWdg;
    IWidget *pRight1CoverImageWdg;
    IWidget *pMiddleCoverImageWdg;
    IWidget *pPlaylistNameTextWdg;

#if defined(__3D_UI_COVERFLOW_MMI__)
    IWidget *pGlcoverFlowWdg;
    IWidget *pGlcoverNameWdg;
#endif //__3D_UI_COVERFLOW_MMI__
}MP_COVER_FLOW_VIEW_WdgList;
//*******************************************************************//
typedef struct
{
	u32			nSrvFileMgrMarkListHandle;
	u32			nPickFileNumber;
} MPLAYERAPP_FILEMGR_PICKFILES;

typedef struct
{
	MAE_WChar *pName;
	MAE_WChar *pType;
	u32 nSize;
	MAE_WChar *	pDate;
	u32 nLocationType;
}MPLAYERAPP_DETAILS_DBINFO;

#ifdef __PLAYLIST_COVER_MMI__
typedef struct
{
	boolean             bCacheCoverImg;
}MPLAYERAPP_SET_COVER_INFO;

typedef struct
{
    IImage      *pImage;
    u32         u32Idx;
    MAE_WChar   *pPlaylistName;
}MPLAYERAPP_PLIST_IMG_DECODE_ITEM;

#define MPLAYER_PLIST_TBL_MAX_NUM 100
#endif /* __PLAYLIST_COVER_MMI__ */

#ifdef __MMI_MPLAYERAPP_FF_REWIND__
#define MSEC_PER_SEC	1000
typedef enum MPlayerFFRewindAction_e_
{
     MPLAYER_FFREWIND_NONE,
     MPLAYER_FASTFORWARD_ACTION,
     MPLAYER_REWIND_ACTION
} MPlayerFFRewindAction_e;

#define FFREWIND_START_TIMER            300
#define FFREWIND_STOP_TIMER             5
#define FASTFORWARD_REWIND_TIME_UNIT    20
#define FASTFORWARD_REWIND_TIME_DURATION        (10)
#endif
/*-------------------------------------------------------------------------*/

typedef struct
{
    u32			nSrvFileMgrSearchListHandle;
    u32			nSearchedFileNumber;
#if defined(__DUAL_CARD__)
    u32			nSrvFileMgrSearchListHandleInCard2;
    u32			nSearchedFileNumberInCard2;
#endif
#ifdef __ONBOARD_USER_STORAGE_MMI__
    u32			nSrvFileMgrSearchListHandleInNand;
    u32			nSearchedFileNumberInNand;
#endif
    boolean     bCancelled;
} MPlayerSearchFileInfo_t;


typedef enum
{
	MPLAYER_FLIP_EFFECT_TYPE_NONE = 0,
	MPLAYER_FLIP_EFFECT_TYPE_LIST_MENU,
	MPLAYER_FLIP_EFFECT_TYPE_LIST_BACK,
	MPLAYER_FLIP_EFFECT_TYPE_FOTO,
	MPLAYER_FLIP_EFFECT_TYPE_LYRIC_MENU,
	MPLAYER_FLIP_EFFECT_TYPE_LYRIC_BACK,
	MPLAYER_FLIP_EFFECT_TYPE_TURN_PAGE_PREV_PAUSE,
	MPLAYER_FLIP_EFFECT_TYPE_TURN_PAGE_NEXT_PAUSE,
	MPLAYER_FLIP_EFFECT_TYPE_TURN_PAGE_PREV,
	MPLAYER_FLIP_EFFECT_TYPE_TURN_PAGE_NEXT,
	MPLAYER_FLIP_EFFECT_TYPE_TURN_PAGE_ID3V2_IMAGE,
	MPLAYER_FLIP_EFFECT_TYPE_ANIMATION,
	MPLAYER_FLIP_EFFECT_TYPE_TRANSFORM_PREV_PHASE1,
	MPLAYER_FLIP_EFFECT_TYPE_TRANSFORM_PREV_PHASE2,
	MPLAYER_FLIP_EFFECT_TYPE_TRANSFORM_NEXT_PHASE1,
	MPLAYER_FLIP_EFFECT_TYPE_TRANSFORM_NEXT_PHASE2,
	MPLAYER_FLIP_EFFECT_TYPE_TRANSFORM_PREV_ROLLBACK_PHASE1,
	MPLAYER_FLIP_EFFECT_TYPE_TRANSFORM_NEXT_ROLLBACK_PHASE1,
    MPLAYER_FLIP_EFFECT_TYPE_TRANSFORM_PREV_ROLLBACK_PHASE2,
	MPLAYER_FLIP_EFFECT_TYPE_TRANSFORM_NEXT_ROLLBACK_PHASE2,
	MPLAYER_FLIP_EFFECT_TYPE_ZOOM_IN_PHASE,
} MPlayerFlipEffectType_e;

/**
* Application structure
*/
typedef struct
{
    ///////////////////////////////////////////////////
    APPLET_BASE_ELEMENTS;

    MMI_MPLAYER_MODE_e eActivatedMode;
    AudioPlayerSrvID3InfoEx_t stID3InfoEx;
    AudioPlayerSrvFileInfo_t stCurrentMediaFileInfo; // the file info of the media from the mplayersrv
    AudioPlayerSrvFileInfo_t stTmpMediaFileInfo;	// the file info to the media to keep the result from IMEDIA
    MAE_WChar *pPlayListFilename; // the current open m3u file name
    MAE_WChar *pM3UFolder;	// The folder we read \ write M3U files
    MAE_WChar *pSelectedPlaylist; // The current highlight \ selected playlist name (used by option menu)
    MAE_WChar *pNewFilename;
    MAE_WChar *pOldFilename;
    MAE_WChar *pEditorContent;
    MAE_WChar *pSelectedMedia; // the current highlight \ selected media filename (used by option menu)
    MAE_WChar *pPlayingPlayListFilename; // the current playing playlist
    MAE_WChar *pPlayingListTitle;
    MAE_WChar *pPlayingMusicURL;
    VectorClass_t *pPlaylistsVectorClass;    // The VectorClass keeps the play lists
    IDataModel *pPlaylistContentDataModel;	// The ArrayModel keeps the content of the play list.
    IDataModel *pPlayingDataModel;			// This ArrayModel points to the playing list (It could be the same as the pPlaylistContentVectorModel)
    IWidget *pDetailDurationTextWidget;
    MPLAYERAPP_FILEMGR_PICKFILES *pFileMgrPickFiles;
    MPlayerSearchFileInfo_t tSearchFileInfo;

#ifdef __PLAYLIST_COVER_MMI__
    MPLAYERAPP_SET_COVER_INFO   *pSetCoverData;
    MPLAYERAPP_PLIST_IMG_DECODE_ITEM atPlistDecodeTbl[MPLAYER_PLIST_TBL_MAX_NUM];
    u32	u32PlistDecodeTblNum;
    MAE_WChar *pCoverStrURL;
    boolean bPickCoverImg;
#endif /* __PLAYLIST_COVER_MMI__ */

    u32 nPlaylistsMenuFirstItemIndex;
    u32 nPlaylistsMenuHighlightIndex;
    u32 nPlaylistContentMenuFirstItemIndex;
    u32 nPlaylistContentMenuHighlightIndex;
    //u32 nPlaylistContentMenuPlayingIndex;
    u32 nPlaylistSize;				// the size of the playlist
    u32 nPlayingIndex;				// the index of current playing media in the view list
    u32 nCurrentPosition;				// the current (starting) position of current playing media.
#ifdef __MPLAYERAP_TOUCH_SEEK__
    u32 nSetPosition;               // the position to seek
    MPlayerGoToTimeState_e eGoToTimeState;
    u8 nAllowCancel;
    boolean bAllowEnableSeekBar;
#endif
    u32 nFocusIndex;				// the index of current focus media in the list.
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
    boolean bIsLyricsExist;		// Indicate if the LRC is on.
#endif
    boolean bIsPredefinedList;		// check if the user chooses predefined play list
    boolean bIsPlayingPredefinedList; // check if the playing list is predefined list.
    //boolean bNoNeedToRedraw;
    //boolean bIsClosedByMinimize;
    //boolean bIsPlaylistEmpty;		// TO BE REMOVED. Indicate if the play list empty
    boolean bIsKeyLocked;			// Indicate if the key is available
    boolean bPlaylistsMenuLogHistory;
    boolean bPlaylistContentMenuLogHistory;
    //boolean bIsLongPress;       // Identify if the key  is long press while it is released.
    boolean bIsExtMemPresented;  // denotes the external card is inserted or not. it may be changed while the inserting/extracting occurs
#if defined(__DUAL_CARD__)
    boolean bIsExtMem2Presented;  //denotes the external card2 is inserted or not. it may be change while the inserting/extracting occurs
#endif
    boolean bUpdatePlaylist;
    boolean bDisableKeyguardScreenSaver;
    boolean bSetPlaylistAfterModify;
    //boolean bNeedToResume; // indicate if the video needs to be resumed
    //boolean bIsFromNowPlaying;
    boolean bCloseAfterResume;
    boolean bRequestPlaylistOperation;
    boolean bDoSearchAfterLoadPlaylistContent;
    boolean bNeedtoCloseAp;
    boolean bActived;
    boolean bWaitingPlayCnf;
    boolean bWaitingPauseCnf;
    boolean bWaitingStopCnf;
    boolean bWaitingSeekCnf;
    boolean bViewPlaylistWaitingStopCnf;
    MPlayer_Shuffle_e eShuffleMode;
    MPlayer_Repeat_e eRepeatMode;
#ifdef __MMI_MPLAYER_EQ_ENABLE__
    MPlayer_EQ_e eEQMode;
#endif
#ifdef __MMI_MPLAYER_3DSURROUND_ENABLE__
    MPlayer_3DSurround_e e3DSurround;
#endif
#if defined(ENABLE_BASS)
    MPlayer_VirtualBass_e eVirtualBassMode;
#endif
#if defined(ENABLE_SRSWOWHD)
    MPlayer_SRS_e eSRSMode;
    MPlayer_SRS_Type_e eSRSType;
#endif
    MPlayer_BackgroundPlay_e eBackgroundPlay;
    MPlayer_TimeStretch_e eTSMode;
    MPlayer_Reverb_e eReverbMode;
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
    MPlayer_Lyric_e eLyricMode;
#endif
    MPlayer_VolLevel_e eVolumeLevel;
    PLAYLISTSRV_PlaylistType_e ePlaylistType;
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
    MAEBatteryID_e nActiveBatteryID;
    MAEBatteryLevel_e nMasterBatteryLevel;
    MAEBatteryLevel_e nSlaveBatteryLevel;
    MAEChargerStatus_e nBatteryStatus;
#endif
    u8 eCurrentMenu;                  // the status of menu
    u8 ePlayingStatus;              // playing status of the mplayerapp
    u8 eStopReason;                // stop reason
    boolean bDialogOn;
    boolean bRequestUpdatePlaylist; // for check updating playlist
    boolean bWarnTempUsePhone;

#ifdef __MPLAYERAP_GMOTION_ROTATE__
    ORIENTATION_e eCurrentOrientation;
#endif
#ifdef __MMI_MPLAYER_EQ_ENABLE__
    boolean bEQSupport; // for check EQ Setting is supported.
#endif
#ifdef __MMI_MPLAYER_3DSURROUND_ENABLE__
    boolean b3DSurroundSupport; // for check 3D surround setting is supported.
#endif
#if defined(ENABLE_BASS)
    boolean bVirtualBassSupport; // for check Virtual bass setting is supported.
#endif
#if defined(ENABLE_SRSWOWHD)
    boolean bSRSSupport;
#endif
    boolean bTSSupport; // for check Time Stretch setting is supported.
    boolean bReverbSupport; // for check Reverb setting is supported.

#ifdef __MMI_MPLAYERAPP_FF_REWIND__
    MPlayerFFRewindAction_e eFFRewindAction;
#endif
#ifdef __MPLAYERAP_SPECTRUM__
    MPlayer_Spectrum_e eSpectrumMode;
#endif

///////////////////////////////////////////////////////
#ifdef __3D_UI_MPLAYER__
    s32 nCurrentControlBarPosX;
    s32 nCurrentControlBarPosY;
    boolean bViewPlayingOnly;
    boolean bPlayAnim;
    u32 nG3DPlaylistsMenuHighlightIndex;
#ifdef __MPLAYERAP_ID3V2_IMG__
    boolean bDoFlipEffect;
#endif
    IAnimation *pAnimation;
    IWidget *pSetFlipWdg;
    MPlayerFlipEffectType_e eFlipEffectType;
#endif

} MMI_MPLAYERAPP;

///////////////////////////////////////////////////////
//  Macro definition
///////////////////////////////////////////////////////

#define MPLAYER_ASSERTIF(r, s)				\
{											\
	if(r != MAE_RET_SUCCESS) 				\
{										\
	LOG_TRACE(MMI_LEVEL_MPLAYER, s, r);	\
	ASSERT(FALSE);						\
}										\
}

#define MPLAYER_ASSERTIF_NULLPTR(p)			\
{											\
	if(NULL == p)			 				\
{										\
	LOG_TRACE(MMI_LEVEL_MPLAYER, "[MPLAYERAPP] This is a null pointer."); \
	ASSERT(FALSE);						\
}										\
}

///////////////////////////////////////////////////////
// WndData structure definition
///////////////////////////////////////////////////////
typedef struct
{
	IWidget			*pIMenuWdg;
} PlaylistsWndData_t;

typedef struct
{
	IWidget *pOptionMenuWidget;
} OptionMenuWndData_t;

#ifdef __COVER_FLOW_MMI__
typedef struct
{
	u32				u32PlaylistTotal;

	/* Default's Cover. */
	IImage			*pIImage_DC_Middle;
	IImage			*pIImage_DC_Left_1;
	IImage			*pIImage_DC_Left_2;
	IImage			*pIImage_DC_Right_1;
	IImage			*pIImage_DC_Right_2;

	/* User selected Cover. */
	IImage			*pIImage_UC_Middle;
	IImage			*pIImage_UC_Left_1;
	IImage			*pIImage_UC_Left_2;
	IImage			*pIImage_UC_Right_1;
	IImage			*pIImage_UC_Right_2;

	MP_COVER_FLOW_VIEW_WdgList tWdgList;

	boolean bIsCoverDecoding;
	boolean abCoverDecoded[NUM_COVERS];
#if defined(__3D_UI_COVERFLOW_MMI__)
    VectorClass_t 	*pCoverBmpVectorClass;    // The VectorClass keeps the cover bitmaps
    u32				nDecodeIdx;
	u32				nDoubleNum;
#ifdef __ADD_COVER_MASK__
	IImage			*pIImage_TransCover;
#endif //__ADD_COVER_MASK__
#endif //__3D_UI_COVERFLOW_MMI__
} CoverFlowWndData_t;
#endif

typedef struct
{
    IDataModel *p3DSurroundDataModel;
    IDataModel *pShuffleDataModel;
    IDataModel *pLyricsDataModel;
    MP_NOWPLAYING_VIEW_WdgList   tWdgList;
#ifdef __MPLAYERAP_ID3V2_IMG__
    IImage *pID3v2Img;
    MplayerPictureType_e eCurPicType;
#endif
 } NowplayingWndData_t;

#if defined(ENABLE_SRSWOWHD)
typedef struct
{
    u32 nFocusWdgId;
    MP_SRSSETTING_VIEW_WdgList  tWdgList;
} SRSSettingWndData_t;

typedef struct
{
    MPlayer_SRS_Type_e eCurrSRSType;
} SRSTypeOptionMenuWndData_t;

typedef struct
{
    u32 nFocusWdgId;
    MPlayer_SRS_Type_e eCurrSRSType;
    MPlayer_SRS_Param_t tCurrSRSParam;
    MP_SRSPARAM_VIEW_WdgList tWdgList;
} SRSParamWndData_t;

typedef struct
{
    u32 nFocusWdgId;
    MPlayer_SRS_Type_e eCurrSRSType;
    MPlayer_SRS_Param_t tCurrSRSParam;
} SRSParamOptionMenuWndData_t;
#endif // defined(ENABLE_SRSWOWHD)

typedef struct
{
	IDataModel *pViewListDataModel;
	IWidget *pIMenuWdg;
	u8 eChangeOrderStatus;
	u32 nMoveItemIndex;
	u32 nNewItemIndex;
	boolean bMarkItem;
} ChangeOrderWndData_t;

typedef struct
{
	IWidget				*pIMenuWdg;
	boolean             bCacheCoverImg;
} ChangeCoverMenuWndData_t;
///////////////////////////////////////////////////////
#define MPLAYER_ADD_ITEMS_GROW_NUM (0)
#define NO_OF_PREDEFINED_PLAYLISTS	2

#define START_PLAY_POSITION 0
#define LENGTH_OF_INDEXINFO	9

#ifdef __PLAYLIST_COVER_MMI__
// temp definition, they'll be removed after the layout is lock down
#ifdef __3D_UI_MPLAYER__
#define COVER_IMG_CACHE_W  (MP_DESKTOPWDG_FOTOLIST_WIDGET_WIDTH)
#define COVER_IMG_CACHE_H  (MP_DESKTOPWDG_FOTOLIST_WIDGET_HEIGHT)
#else
#ifdef __COVER_FLOW_MMI__
#define COVER_IMG_CACHE_W	RS_COVERFLOW_MIDDLE_COVER_WIDTH
#define COVER_IMG_CACHE_H   RS_COVERFLOW_MIDDLE_COVER_HEIGHT
#else
#define COVER_IMG_CACHE_W	100
#define COVER_IMG_CACHE_H   100
#endif
#endif
#define COVER_IMG_CACHE_COUNTMAX    (PLAYLISTSRV_MAX_PALYLISTS_NUM + 2 /* all music/video */)
#endif /* __PLAYLIST_COVER_MMI__ */
#define M3U_FOLDER_REQ_SIZE 1 // 1KB to create folder

//#define _MPLAYER_TRACE_KEYLOCKED_FLAG
#if defined(_MPLAYER_TRACE_KEYLOCKED_FLAG)
#define _MPLAYER_TRACE_KEY_LOCKED	{ LOG_INFO(MMI_LEVEL_MPLAYER, "@@ key locked <<<<<<<<<<"); }
#define _MPLAYER_TRACE_KEY_UNLOCKED	{ LOG_INFO(MMI_LEVEL_MPLAYER, "@@ key unlocked >>>>>>>>>>"); }
#else
#define _MPLAYER_TRACE_KEY_LOCKED
#define _MPLAYER_TRACE_KEY_UNLOCKED
#endif

enum
{
	MENU_DEFAULT = 0,
	MENU_DISPLAYPLAYLIST,
	MENU_VIEWPLAYLIST,
	MENU_PLAYMUSIC
};

enum
{
	ALL_MUSIC = 0,
	ALL_VIDEOS
};

enum
{
	PLAYSTATUS_STOP,
	PLAYSTATUS_PAUSE,
	PLAYSTATUS_PLAY,
	PLAYSTATUS_SEEK
};

enum
{
	STOP_BY_ENDKEY,
	STOP_BY_USER,
	STOP_BY_BACK,
	STOP_BY_PAUSE,
	STOP_BY_UPDATE_PLAYLIST,
	STOP_BY_SWITCH_PLAYLIST,
	STOP_BY_SWITCH_PLAYLIST_CONTENT,
	STOP_BY_DELETE
};

enum
{
	CHANGEORDER_DISPLAYLIST,
	CHANGEORDER_MARK,
	CHANGEORDER_UPDATE
};

typedef enum
{
	MPLAYER_RET_CREATE_FOLDER_FAIL = (CLSID_MPLAYERAPP << 16) | 0x70
} MPlayerRetCode_e;

#ifdef __PLAYLIST_COVER_MMI__
enum
{
	COVER_DEF_PIC_ITEM_IDX = 0,
	COVER_CUSTOM_ITEM_IDX,
};
#endif

enum
{
    NOWPLAY_FUNCTION_BUTTON_IDX_0 = 0,
    NOWPLAY_FUNCTION_BUTTON_IDX_1,
    NOWPLAY_FUNCTION_BUTTON_IDX_2,
    NOWPLAY_FUNCTION_BUTTON_IDX_3,
    NOWPLAY_FUNCTION_BUTTON_IDX_4,
    NOWPLAY_FUNCTION_BUTTON_MAX_NUM
};

enum
{
    NOWPLAY_FUNCTION_BUTTON_VISIBLE_NUM_0 = 0,
    NOWPLAY_FUNCTION_BUTTON_VISIBLE_NUM_1,
    NOWPLAY_FUNCTION_BUTTON_VISIBLE_NUM_2,
    NOWPLAY_FUNCTION_BUTTON_VISIBLE_NUM_3,
    NOWPLAY_FUNCTION_BUTTON_VISIBLE_NUM_4,
    NOWPLAY_FUNCTION_BUTTON_VISIBLE_NUM_5
};

typedef enum
{
	HORIZONTAL_MODE,
	VERTICAL_MODE
}MPLAYERAPP_DISPLAYMODE_e;

typedef enum
{
#ifdef __MMI_MPLAYER_EQ_ENABLE__
    MPLAYERAPP_AUDIO_EFFECT_EQ,
#endif
#ifdef __MMI_MPLAYER_3DSURROUND_ENABLE__
    MPLAYERAPP_AUDIO_EFFECT_3D,
#endif
    MPLAYERAPP_AUDIO_EFFECT_DOLBY,
#if defined(ENABLE_TIMEPITCH_STRETCH)
    MPLAYERAPP_AUDIO_EFFECT_PITCH,
#endif
#if defined(ENABLE_TIME_STRETCH)
    MPLAYERAPP_AUDIO_EFFECT_TS,
#endif
#if defined(ENABLE_REVERB)
    MPLAYERAPP_AUDIO_EFFECT_REVERB,
#endif
#if defined(ENABLE_SRSWOWHD)
    MPLAYERAPP_AUDIO_EFFECT_SRS,
#endif
#if defined(ENABLE_BASS)
    MPLAYERAPP_AUDIO_EFFECT_BASS,
#endif
    MPLAYERAPP_AUDIO_EFFECT_TOTAL_NUM,
} MPLAYERAPP_AUDIO_EFFECT_e;
///////////////////////////////////////////////////////////////////////////////////////
/* All Wnd Id definition */
///////////////////////////////////////////////////////////////////////////////////////

typedef enum MplayerNotifyType_e_
{
	//Mapping to SrvAudioPlayerPlayStatus_e
	MPLAYER_NOTIFY_TYPE_PLAY_SUCCESS = 0,
	MPLAYER_NOTIFY_TYPE_PLAY_FAILED,
	MPLAYER_NOTIFY_TYPE_PAUSE_SUCCESS,
	MPLAYER_NOTIFY_TYPE_PAUSE_FAILED,
	MPLAYER_NOTIFY_TYPE_STOP_SUCCESS,
	MPLAYER_NOTIFY_TYPE_STOP_FAILED,
	MPLAYER_NOTIFY_TYPE_SUSPEND_IND,
	MPLAYER_NOTIFY_TYPE_RESUME_IND,
	MPLAYER_NOTIFY_TYPE_PLAYBACKGROUND_IND,
	//Mapping to SrvAudioPlayerCommonNotify_e
	MPLAYER_NOTIFY_TYPE_PLAY_MUSIC,
	MPLAYER_NOTIFY_TYPE_PLAY_NEXT,
	MPLAYER_NOTIFY_TYPE_PLAY_PREVIOUS,
	MPLAYER_NOTIFY_TYPE_SUSPEND_DONE,
	MPLAYER_NOTIFY_TYPE_END_PLAYING,
	MPLAYER_NOTIFY_TYPE_LYRICS_SUCCESS,
	MPLAYER_NOTIFY_TYPE_LYRICS_FAILED,
	MPLAYER_NOTIFY_TYPE_PCLINK_ACTIVATED,
	MPLAYER_NOTIFY_TYPE_SDDB_DISABLE,
	MPLAYER_NOTIFY_TYPE_COMMAND_SKIP,
	MPLAYER_NOTIFY_TYPE_COMMAND_REJECT,
	MPLAYER_NOTIFY_TYPE_FILE_FORMAT_NOT_SUPPORT,
	MPLAYER_NOTIFY_TYPE_FILE_NOT_EXIST,
	MPLAYER_NOTIFY_TYPE_LOAD_LAST_PLAYINFO_DONE
} MplayerNotifyType_e;

///////////////////////////////////////////////////////////////////////////////////////
//New function.
///////////////////////////////////////////////////////////////////////////////////////
MAE_Ret MPlayerWndCreatePlaylists(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyPlaylists(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndShowPlaylists(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertPlaylists(void *pCusHandle, void *pWndData);

#ifdef __COVER_FLOW_MMI__
MAE_Ret MPlayerWndCreateCoverFlow(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndShowCoverFlow(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyCoverFlow(void *pCusHandle, void *pWndData);
#endif

MAE_Ret MPlayerWndCreatePlaylistContent(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyPlaylistContent(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndShowPlaylistContent(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertPlaylistContent(void *pCusHandle, void *pWndData);

#ifndef __3D_UI_MPLAYER__
MAE_Ret MPlayerWndCreateNowplaying(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyNowplaying(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndShowNowplaying(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertNowplaying(void *pCusHandle, void *pWndData);
#endif

MAE_Ret MPlayerWndCreateNewPlaylist(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyNewPlaylist(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertNewPlaylist(void *pCusHandle, void *pWndData);

MAE_Ret MPlayerWndCreateEditPlaylist(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyEditPlaylist(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertEditPlaylist(void *pCusHandle, void *pWndData);

MAE_Ret MPlayerWndCreateChangeOrder(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyChangeOrder(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertChangeOrder(void *pCusHandle, void *pWndData);

MAE_Ret MPlayerWndCreateDetails(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyDetails(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertDetails(void *pCusHandle, void *pWndData);

#if defined(ENABLE_SRSWOWHD)
MAE_Ret MPlayerWndCreateSRSSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroySRSSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndShowSRSSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertSRSSetting(void *pCusHandle, void *pWndData);
#endif

#if defined(ENABLE_SRSWOWHD)
MAE_Ret MPlayerWndCreateSRSType(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroySRSType(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertSRSType(void *pCusHandle, void *pWndData);
#endif

#if defined(ENABLE_SRSWOWHD)
MAE_Ret MPlayerWndCreateSRSTypeOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret MPlayerWndDestroySRSTypeOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertSRSTypeOptionMenu(void *pCusHandle, void *pWndData);
#endif

#if defined(ENABLE_SRSWOWHD)
MAE_Ret MPlayerWndCreateSRSParam(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret MPlayerWndDestroySRSParam(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndShowSRSParam(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertSRSParam(void *pCusHandle, void *pWndData);
#endif

#if defined(ENABLE_SRSWOWHD)
MAE_Ret MPlayerWndCreateSRSParamOptionMenu(void *pCusHandle, void *pWndData, u32 nWndInitParam);
MAE_Ret MPlayerWndDestroySRSParamOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertSRSParamOptionMenu(void *pCusHandle, void *pWndData);
#endif

#ifdef __MMI_MPLAYER_EQ_ENABLE__
MAE_Ret MPlayerWndCreateEqSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyEqSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertEqSetting(void *pCusHandle, void *pWndData);
#endif

MAE_Ret MPlayerWndCreateTsSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyTsSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertTsSetting(void *pCusHandle, void *pWndData);

MAE_Ret MPlayerWndCreateReverbSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyReverbSetting(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertReverbSetting(void *pCusHandle, void *pWndData);

MAE_Ret MPlayerWndCreateChangeCoverMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyChangeCoverMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertChangeCoverMenu(void *pCusHandle, void *pWndData);

#ifdef __MPLAYERAP_ID3_INFO__
MAE_Ret MPlayerWndCreateSongInfo(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroySongInfo(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertSongInfo(void *pCusHandle, void *pWndData);
#endif

MAE_Ret MPlayerWndCreatePlaylistOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyPlaylistOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertPlaylistOptionMenu(void *pCusHandle, void *pWndData);

MAE_Ret MPlayerWndCreatePlaylistContentOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyPlaylistContentOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertPlaylistContentOptionMenu(void *pCusHandle, void *pWndData);

MAE_Ret MPlayerWndCreateNowplayingOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndDestroyNowplayingOptionMenu(void *pCusHandle, void *pWndData);
MAE_Ret MPlayerWndConvertNowplayingOptionMenu(void *pCusHandle, void *pWndData);


MAE_Ret MPlayerWndCreateNewPlaylistOptionMenu(void *pCusHandle, void *pScenData);
MAE_Ret MPlayerWndDestroyNewPlaylistOptionMenu(void *pCusHandle, void *pScenData);
MAE_Ret MPlayerWndConvertNewPlaylistOptionMenu(void *pCusHandle, void *pScenData);

MAE_Ret MPlayerWndCreateEditPlaylistOptionMenu(void *pCusHandle, void *pScenData);
MAE_Ret MPlayerWndDestroyEditPlaylistOptionMenu(void *pCusHandle, void *pScenData);
MAE_Ret MPlayerWndConvertEditPlaylistOptionMenu(void *pCusHandle, void *pScenData);

//////////////////////////////////////////////////////////////////////////////////////
// MPLAYERSRV & PLAYLISTSRV CALLBACK
//////////////////////////////////////////////////////////////////////////////////////
void _MPlayerPlayStatusCB(void *pApplet, SrvAudioPlayerPlayStatus_e ePlayStatus);
void _MPlayerPlayTickCB(void *pApplet, u32 nTimeElapsed);
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
void _MPlayerLyricsInfoCB(void *pApplet, MAE_WChar *pLyricsInfo);
#endif
void _MPlayerPlayingIndexCB(void *pApplet, u32 nPlayingIndex);
#if defined (__MPLAYERAP_TOUCH_SEEK__) || defined (__MMI_MPLAYERAPP_FF_REWIND__)
void _MPlayerSeekCancelCB(void *pApplet, u32 nParam1);
#endif
void _MPlayerCommonCB(void *pApplet, SrvAudioPlayerCommonNotify_e eCommonNotify);
void _MPlayerPlayingIndexCB(void *pApplet, u32 nPlayingIndex);
void _MPlayerPlayMusicInfoCB(void *pApplet, AudioPlayerSrvFileInfo_t* pMediaFileInfo);

void _MPlayerLoadPlaylistDataCB(void *pApplet, PLAYLISTSRV_Rquest_Result_e eResult, IDataModel *pPlaylistDataModel);
void _MPlayerPlaylistSrvCmnCB(void *pApplet, PLAYLISTSRV_Rquest_Result_e eResult);
#ifdef  __MPLAYERAP_GMOTION_ROTATE__
void _MPlayerMotionDetectorOrientationCB(void *pApplet, ORIENTATION_e eResult);
#endif
#ifdef  __MPLAYERAP_GMOTION_SHAKE__
void _MPlayerMotionDetectorSimpleActionCB(void *pApplet, SIMPLE_ACTINO_e eResult);
#endif
MAE_Ret _MPlayerRetrieveDBInfoByURI(MMI_MPLAYERAPP *pThis, MAE_WChar *pURI, MPLAYERAPP_DETAILS_DBINFO **ppDetailsInfo);

void _MPlayerUsbSbjListener(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);
void _MPlayerPlugStatusChangedCB(void *pApplet, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
void _MPlayerBatteryLevelChangedCB(void *pApplet, MAEBatteryLevel_e eLevel, MAEBatteryID_e eBatID);
void _MPlayerBatteryExtPowerChangedCB(void *pApplet, boolean bChargerPlugged);
#endif
//////////////////////////////////////////////////////////////////////////////////////
// BTSRV CALLBACK
//////////////////////////////////////////////////////////////////////////////////////
#if defined(__BLUETOOTH_MMI__) && defined(__BLUETOOTH_A2DP_MMI__)
void _MPlayerBtAudioLinkCB(void *pApplet, u8 nItem, BTSRV_Link_Status_e eLinkStatus);
#endif
//////////////////////////////////////////////////////////////////////////////////////
// OBJPROCESSING SRV CALLBACK : USE IN CHANGE COVER MENU
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __PLAYLIST_COVER_MMI__
void _MPlayerGetPreviewDataDoneCB(void *pApplet, OPSrv_LaunchFor_e eCurrentOP, OPSrvRsltInfo_t *pRsltInfo);
void _MPlayerSrvStoppedCB(void *pApplet);
#endif //__PLAYLIST_COVER_MMI__

//////////////////////////////////////////////////////////////////////////////////////
// APP Level handle function
//////////////////////////////////////////////////////////////////////////////////////
void _MPlayerHandlePlaySuccess(MMI_MPLAYERAPP* pThis);
void _MPlayerHandlePlayFailed(MMI_MPLAYERAPP* pThis);
void _MPlayerHandleEndPlaying(MMI_MPLAYERAPP* pThis);
void _MPlayerHandlePauseSuccessStopCnf(MMI_MPLAYERAPP* pThis, SrvAudioPlayerPlayStatus_e ePlayStatus);
//////////////////////////////////////////////////////////////////////////////////////
// Playlists Wnd function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndPlaylistsCreateWnd(MMI_MPLAYERAPP *pThis, PlaylistsWndData_t *pWndData);
MAE_Ret _MPlayerWndPlaylistsDestroyWnd(MMI_MPLAYERAPP *pThis, PlaylistsWndData_t *pWndData);
MAE_Ret _MPlayerWndPlaylistsPrepareData(MMI_MPLAYERAPP *pThis);
void _MPlayerWndPlaylistsPlaylistElementVectorClassFree(void *pData, void *pOwner);
//Menu AdaptGet/FreeItem
void _MPlayerWndPlaylistsMenuAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
void _MPlayerWndPlaylistsMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
//Menu Widget Wrapper CB.
void _MPlayerWndPlaylistsMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndPlaylistsMenuOnFocusCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusInfo_t *pFocusInfo, IWidget *pWidget);
void _MPlayerWndPlaylistsMenuSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
//Handle CB Event function
void _MPlayerWndPlaylistsMenuSuspendCB(MMI_MPLAYERAPP* pThis);				    //MAE_EVT_APP_SUSPEND
void _MPlayerWndPlaylistsMenuResumeCB(MMI_MPLAYERAPP* pThis);					//MAE_EVT_APP_RESUME
#ifdef __PLAYLIST_COVER_MMI__
MAE_Ret _MPlayerWndPlaylistsUpdateMenuIcon(MMI_MPLAYERAPP *pThis, IWidget *pMenuWdg, u32 nUpdateIndex, MAE_WChar* pItemName, IImage *pPreImage);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// PlaylistsOptionMenu Wnd function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndPlaylistsOptionMenuCreateWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndPlaylistsOptionMenuDestroyWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
MAE_Ret _MPlayerCommonCreateOptionMenuL2(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData, u32 nSelectedID);
//Option Menu Widget Wrapper CB.
void _MPlayerWndPlaylistsOptionMenuL1CancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndPlaylistsOptionMenuL1ReqOption2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndPlaylistsOptionMenuL1SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndPlaylistsOptionMenuL2SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret _MPlayerCommonHandleOptionMenuL2Select(MMI_MPLAYERAPP *pThis, u32 nSelectedID);

//////////////////////////////////////////////////////////////////////////////////////
// CoverFlow Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __COVER_FLOW_MMI__
#if !defined(__3D_UI_COVERFLOW_MMI__)
MAE_Ret _MPlayerWndCoverFlowCreateWnd(MMI_MPLAYERAPP *pThis, CoverFlowWndData_t *pWndData);
MAE_Ret _MPlayerWndCoverFlowCreateView(HWIN hWin, MP_COVER_FLOW_VIEW_WdgList *pWdgList);
#endif
MAE_Ret _MPlayerWndCoverFlowDestroyWnd(MMI_MPLAYERAPP *pThis, CoverFlowWndData_t *pWndData);
void _MPlayerWndCoverFlowHandlePressKeyAndTouchClick(MMI_MPLAYERAPP* pThis);	    //MAE_EVT_KEY_PRESS, MAE_EVT_TS_CLICK
void _MPlayerWndCoverFlowHandlePressDownKeyAndTouchLeft(MMI_MPLAYERAPP* pThis);	    //MAE_EVT_KEY_PRESS, MAE_EVT_TS_LEFT
void _MPlayerWndCoverFlowHandlePressUpKeyAndTouchRight(MMI_MPLAYERAPP* pThis);	//MAE_EVT_KEY_PRESS, MAE_EVT_TS_RIGHT
void _MPlayerWndCoverFlowHandleCreatePlaylistDataModel(MMI_MPLAYERAPP* pThis);	    //MPLAYERAPP_IEVT_CreatePlaylistDataModel
void _MPlayerWndCoverFlowHandleRequestResult(MMI_MPLAYERAPP* pThis, IDataModel *pPlaylistDataModel);			    //PLAYLISTSRV_EVT_REQUEST_RESULT
void _MPlayerWndCoverFlowHandleSuspend(MMI_MPLAYERAPP* pThis);					    //MAE_EVT_APP_SUSPEND
void _MPlayerWndCoverFlowHandleResume(MMI_MPLAYERAPP* pThis);					    //MAE_EVT_APP_RESUME
void _MPlayerWndCoverFlowHandleStopSuccessAndCommandSkip(MMI_MPLAYERAPP* pThis);	//MPLAYERSRV_EVT_CommandSkip ,MPLAYERSRV_EVT_StopSuccess
void _MPlayerWndCoverFlowHandlePlayMusic(MMI_MPLAYERAPP *pThis);					//MPLAYERAPP_EVT_PlayMusic
void _MPlayerWndCoverFlowCheckSizeThenPlayMusic(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerStartDecodeCover(MMI_MPLAYERAPP* pThis, CoverFlowWndData_t *pWndData, u32 u32PlayListIdx, u32 u32WdigetId);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// PlaylistContent Wnd function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndPlaylistContentCreate(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerWndPlaylistContentCreateWnd(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerWndPlaylistContentDestroyWnd(MMI_MPLAYERAPP *pThis);
//Menu AdaptGet
void _MPlayerWndPlaylistContentMenuAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
void _MPlayerWndPlaylistContentFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
//Menu Widget Wrapper CB.
void _MPlayerWndPlaylistContentMenuSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
//MPlayer SRV CB.
void _MPlayerPlaylistContentHandleStopSuccessCommandSkip(MMI_MPLAYERAPP* pThis);
//Playlist SRV load data CB.
void _MPlayerWndPlaylistContentLoadPlaylistDataCB(MMI_MPLAYERAPP *pThis, PLAYLISTSRV_Rquest_Result_e eResult, IDataModel *pPlaylistDataModel);
//Keypress CB
boolean _MPlayerWndPlaylistContentKeypressCB(MMI_MPLAYERAPP *pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
//Utility
void _MPlayerWndPlaylistContentPlay(MMI_MPLAYERAPP *pThis, u32 nFocusIndex, boolean bIsReplaceWnd);
void _MPlayerWndPlaylistContentUpdate(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerWndPlaylistContentDeleteBackupPlaylist(MMI_MPLAYERAPP *pThis, MAE_WChar *pPlaylistFileName);
MAE_Ret _MPlayerWndPlaylistContentRestoreBackupPlaylist(MMI_MPLAYERAPP *pThis, MAE_WChar *pPlaylistFileName);
MAE_Ret _MPlayerWndPlaylistContentUpdatePlayingMusicItemIcon(MMI_MPLAYERAPP* pThis);
MAE_Ret _MPlayerWndPlaylistContentUpdateMenuIcon(MMI_MPLAYERAPP *pThis, IWidget *pMenuWdg, u32 nUpdateIndex, u32 nImageId);
MAE_Ret _MPlayerWndPlaylistContentUpdatePlaylistConfirmDialogKeypressCB(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);

//////////////////////////////////////////////////////////////////////////////////////
// PlaylistContentOptionMenu Wnd function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndPlaylistContentOptionMenuCreateWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndPlaylistContentOptionMenuDestroyWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
//Option Menu Widget Wrapper CB.
void _MPlayerWndPlaylistContentOptionMenuL1CancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndPlaylistContentOptionMenuL1ReqOption2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndPlaylistContentOptionMenuL1SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndPlaylistContentOptionMenuL2SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

//////////////////////////////////////////////////////////////////////////////////////
// Nowplaying Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __3D_UI_MPLAYER__
MAE_Ret _MPlayerWndNowplayingCreateWnd(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
#ifdef __TOUCH_SCREEN_MMI__
MAE_Ret _MPlayerWndNowplayingDestroyWnd(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
#endif
MAE_Ret _MPlayerWndNowplayingCreateView(MMI_MPLAYERAPP *pThis, HWIN hWin, MP_NOWPLAYING_VIEW_WdgList *pWdgList);
#endif
//Callback
#ifdef __TOUCH_SCREEN_MMI__
#ifndef __3D_UI_MPLAYER__
void _MPlayerWndNowplayingRepeatButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWndNowplayingPlaybackButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWndNowplayingPlayNextButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWndNowplayingPlayPreviousButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
#ifdef __MMI_MPLAYERAPP_FF_REWIND__
void _MPlayerWndNowplayingPlayNextButtonLongPressCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWndNowplayingPlayPreviousButtonLongPressCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWndNowplayingPlayNextButtonInvalidCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid, IWidget *pWidget);
void _MPlayerWndNowplayingPlayPreviousButtonInvalidCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, boolean bValid, IWidget *pWidget);
#endif
void _MPlayerWndNowplayingIncreaseVolumeButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void _MPlayerWndNowplayingDecreaseVolumeButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
#ifdef __MMI_MPLAYER_3DSURROUND_ENABLE__
//Justin: Change (IDataModel* pDataModel, ) --> (u32 dwParam) The data word param (NOT use now)
void _MPlayerWndNowplaying3DSurroundSwitchIconDataChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
//Justin: Change (IDataModel* pDataModel, ) --> (u32 dwParam) The data word param (NOT use now)
void _MPlayerWndNowplayingShuffleSwitchIconDataChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
//Justin: Change (IDataModel* pDataModel, ) --> (u32 dwParam) The data word param (NOT use now)
void _MPlayerWndNowplayingLyricsSwitchIconDataChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif
//Handle KeyPress
boolean _MPlayerWndNowplayingKeypressCB(MMI_MPLAYERAPP *pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _MPlayerWndNowPlayingUpdatePlaylistConfirmDialogKeypressCB(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
#ifdef __MMI_MPLAYERAPP_FF_REWIND__
boolean _MPlayerWndNowplayingKeyLongPressCB(MMI_MPLAYERAPP *pThis, u32 nParam);
boolean _MPlayerWndNowplayingKeyReleaseCB(MMI_MPLAYERAPP *pThis, u32 nParam);
#endif
//Utility
void _MPlayerWndNowplayingUpdatePredefinedPlaylist(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerWndNowplayingStartUpdatePredefinedPlaylist(MMI_MPLAYERAPP *pThis);
#if defined(__MMI_BATTERY_ICON_DISPLAY__)
MAE_Ret _MPlayerWndNowplayingUpdateBatteryIcon(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
#endif
void _MPlayerWndNowplayingUpdateVolume(MMI_MPLAYERAPP *pThis, NowplayingWndData_t * pWndData);
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
MAE_Ret _MPlayerWndNowplayingEnableLyricsZone(MMI_MPLAYERAPP *pThis, boolean bEnabled, NowplayingWndData_t *pWndData);
MAE_Ret _MPlayerWndNowplayingUpdateLyricsZone(MMI_MPLAYERAPP *pThis, MAE_WChar *pLyrics, NowplayingWndData_t *pWndData);
#endif
#ifndef __3D_UI_MPLAYER__
#ifdef __MPLAYERAP_ID3V2_IMG__
void _MPlayerID3ImageFreeFunc(void *pData);
void _MPlayerID3ImageDecodeNotifyCb(IImage* pImage, IBase* pOwner, ImgStatus_t tStatus);
void _MPlayerWndNowplayingDisplayCoverImg(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
void _MPlayerWndNowplayingUpdateCoverImgInfo(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
#endif
#endif
void _MPlayerWndNowplayingUpdateTitleAuthorInfo(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
void _MPlayerWndNowplayingUpdateSwitchIcons(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
MAE_Ret _MPlayerWndNowplayingUpdatePlaybackIcon(MMI_MPLAYERAPP* pThis, NowplayingWndData_t *pWndData);
MAE_Ret _MPlayerWndNowplayingSetIndicatorText(MMI_MPLAYERAPP *pThis, IWidget *pIndicatorTextWidget);
MAE_Ret _MPlayerWndNowplayingSetIndexText(MMI_MPLAYERAPP *pThis, IWidget *pTextWidget);
MAE_Ret _MPlayerWndNowplayingConvertIndexInfo(MMI_MPLAYERAPP *pThis, MAE_WChar **pWString);
// Spectrum
#ifdef __MPLAYERAP_SPECTRUM__
MAE_Ret _MPlayerSetSpectrumCfgItem(MMI_MPLAYERAPP *pThis, MPlayer_Spectrum_e eSpectrum);
MAE_Ret _MPlayerWndNowplayingCreateSpectrumFrame(MMI_MPLAYERAPP *pThis, HWIN hWin, MP_NOWPLAYING_VIEW_WdgList *pWdgList);
 MAE_Ret _MPlayerWndNowplayingConvertSpectrumFrame(MMI_MPLAYERAPP *pThis, HWIN hWin, MP_NOWPLAYING_VIEW_WdgList *pWdgList);
 MAE_Ret _MPlayerWndNowplayingEnableSpectrumFrame(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData, MPlayer_Spectrum_e eSpectrum);
MAE_Ret _MPlayerWndNowplayingResetSpectrumData(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
MAE_Ret _MPlayerWndNowplayingUpdateSpectrumData(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData, MediaSrvSpectrumInfo_t *pSpectrumInfo);
void _MPlayerSpectrumInfoCB(void *pApplet, u32 nCusData, MediaSrvSpectrumInfo_t *pSpectrumInfo);
void _MPlayerWndNowplayingSpectrumBarListFreeItem (WdgListItem_t *pItemDataPtr, HWIN hWin, WdgListItemType_e eItemType);
void _MPlayerWndNowplayingSpectrumSwitchIconDataChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// NowplayingOptionMenu Wnd function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndNowplayingOptionMenuCreateWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndNowplayingOptionMenuDestroyWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
//Option Menu Widget Wrapper CB.
void _MPlayerWndNowplayingOptionMenuL1CancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndNowplayingOptionMenuL1ReqOption2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndNowplayingOptionMenuL1SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndNowplayingOptionMenuL2SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
//For handle MPLAYERSRV CALLBACK.
void _MPlayerPlayMusicHandleFail(MMI_MPLAYERAPP *pThis, MplayerNotifyType_e eNotifyType);
void _MPlayerPlayMusicHandlePlaySuccess(MMI_MPLAYERAPP* pThis, NowplayingWndData_t *pWndData);
void _MPlayerPlayMusicHandleStopSuccessCommandSkip(MMI_MPLAYERAPP* pThis, MplayerNotifyType_e eNotifyType, NowplayingWndData_t *pWndData);
#ifdef __MMI_MPLAYER_LYRIC_ENABLE__
void _MPlayerPlayMusicHandleLyricsSuccess(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
void _MPlayerPlayMusicHandleLyricsFailed(MMI_MPLAYERAPP *pThis, NowplayingWndData_t *pWndData);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// NewPlaylist & EditPlaylist Wnd common function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndEditorCreateWnd(MMI_MPLAYERAPP *pThis, u32 nTitleID, MAE_WChar *pDefaultText);
MAE_Ret _MPlayerWndEditorDestroyWnd(MMI_MPLAYERAPP *pThis);
//Callback
void _MPlayerWndEditorTextChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, TextInfo *pTextInfo, IWidget *pWidget);

//////////////////////////////////////////////////////////////////////////////////////
// NewPlaylist Wnd function
//////////////////////////////////////////////////////////////////////////////////////
boolean _MPlayerWndNewPlaylistKeypressCB(MMI_MPLAYERAPP *pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _MPlayerWndNewPlaylistLoadPlaylistDataCB(MMI_MPLAYERAPP* pThis, PLAYLISTSRV_Rquest_Result_e eResult, IDataModel *pPlaylistDataModel);
void _MPlayerWndNewPlaylistHandleFsError(MMI_MPLAYERAPP* pThis, MAE_Ret nRetVal);
void _MPlayerWndNewPlaylistSave(MMI_MPLAYERAPP* pThis);

//////////////////////////////////////////////////////////////////////////////////////
// EditPlaylist Wnd function
//////////////////////////////////////////////////////////////////////////////////////
boolean _MPlayerWndEditPlaylistKeypressCB(MMI_MPLAYERAPP *pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _MPlayerWndEditPlaylistUpdate(MMI_MPLAYERAPP *pThis);

//////////////////////////////////////////////////////////////////////////////////////
// NewPlaylistOptionMenu & EditPlaylistOptionMenu Wnd function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndNewPlaylistOptionMenuCreateWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndNewPlaylistOptionMenuDestroyWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
//Option Menu Widget Wrapper CB.
void _MPlayerWndNewPlaylistOptionMenuL1CancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndNewPlaylistOptionMenuL1ReqOption2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndNewPlaylistOptionMenuL1SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndNewPlaylistOptionMenuL2SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret _MPlayerWndEditPlaylistOptionMenuCreateWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndEditPlaylistOptionMenuDestroyWnd(MMI_MPLAYERAPP *pThis, OptionMenuWndData_t *pWndData);
//Option Menu Widget Wrapper CB.
void _MPlayerWndEditPlaylistOptionMenuL1CancelCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndEditPlaylistOptionMenuL1ReqOption2CB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndEditPlaylistOptionMenuL1SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
void _MPlayerWndEditPlaylistOptionMenuL2SelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

MAE_Ret _MPlayerWndEditorOptionMenuCreateWnd(MMI_MPLAYERAPP *pThis, boolean bIsRenamePlaylist, OptionMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndEditorOptionMenuDestroyWnd(MMI_MPLAYERAPP *pThis, boolean bIsRenamePlaylist, OptionMenuWndData_t *pWndData);

//////////////////////////////////////////////////////////////////////////////////////
// Details Wnd function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndDetailsCreateWnd(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerWndDetailsDestroyWnd(MMI_MPLAYERAPP *pThis);
boolean _MPlayerWndDetailsKeypressCB(MMI_MPLAYERAPP *pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _MPlayerWndDetailsAudFileInfoCB(void *pData, MediaSrvErrCode_e eErrorCode, u32 nCusData, AudioSrvFileInfo_t *pAudFileInfo);
MAE_WChar* _MPlayerWndDetailsGetCurrentPlayingURL(MMI_MPLAYERAPP *pThis);
MAE_WChar* _MPlayerWndDetailsGenerateDetailsString(MMI_MPLAYERAPP *pThis, MPLAYERAPP_DETAILS_DBINFO  *pDetailsInfo, MAE_WChar *pDurationStr);
void _MPlayerWndDetailsCheckFileIsExist(MMI_MPLAYERAPP *pThis);

//////////////////////////////////////////////////////////////////////////////////////
// SRSSetting Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#if defined(ENABLE_SRSWOWHD)
MAE_Ret _MPlayerWndSRSSettingCreateView(MMI_MPLAYERAPP *pThis, HWIN hWin, MP_SRSSETTING_VIEW_WdgList *pWdgList);
MAE_Ret _MPlayerWndSRSSettingUpdateSRSStatus(MMI_MPLAYERAPP *pThis, SRSSettingWndData_t *pWndData);
MAE_Ret _MPlayerWndSRSSettingUpdateSRSType(MMI_MPLAYERAPP *pThis, SRSSettingWndData_t *pWndData);
boolean _MPlayerWndSRSSettingKeypressCB(MMI_MPLAYERAPP *pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _MPlayerWndSRSSettingStatusCmnPickWdgFocusChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusChangeData, IWidget *pWidget);
void _MPlayerWndSRSSettingMflContainerFocusChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _MPlayerWndSRSSettingMflContainerFocusSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _MPlayerWndSRSSettingItemSelectHdl(void *pApplet, u32 nSelectedWdgID);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// SRSType Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#if defined(ENABLE_SRSWOWHD)
MAE_Ret _MPlayerWndSRSTypeActivateSelectedType(MMI_MPLAYERAPP *pThis, MPlayer_SRS_Type_e eSRSType);
void _MPlayerWndSRSTypeMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// SRSType Option Menu Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#if defined(ENABLE_SRSWOWHD)
void _MPlayerWndSRSTypeOptionMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// SRSParam Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#if defined(ENABLE_SRSWOWHD)
MAE_Ret _MPlayerWndSRSParamCreateView(MMI_MPLAYERAPP *pThis, HWIN hWin, MP_SRSPARAM_VIEW_WdgList *pWdgList);
MAE_Ret _MPlayerWndSRSParamUpdateParamLevel(MMI_MPLAYERAPP *pThis, SRSParamWndData_t *pWndData);
MAE_Ret _MPlayerWndSRSParamItemSelectHdl(MMI_MPLAYERAPP *pThis, u32 nSelectedWdgID);
boolean _MPlayerWndSRSParamKeypressCB(MMI_MPLAYERAPP *pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
void _MPlayerWndSRSParamMflContainerFocusChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _MPlayerWndSRSParamMflContainerFocusSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, MFLFocusData_t *pMFLFocusData, IWidget *pWidget);
void _MPlayerWndSRSParamLevelCmnPickWdgFocusChangeCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *pFocusChangeData, IWidget *pWidget);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// SRSParam Option Menu Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#if defined(ENABLE_SRSWOWHD)
void _MPlayerWndSRSParamOptionMenuSoftkeyActCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret _MPlayerWndSRSParamOptionMenuRestoreSRSParams(MMI_MPLAYERAPP *pThis, MPlayer_SRS_Type_e eSRSType, MPlayer_SRS_Param_t tSRSParam);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// EqSetting Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __MMI_MPLAYER_EQ_ENABLE__
MAE_Ret _MPlayerWndEqSettingCreateWnd(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerWndEqSettingDestroyWnd(MMI_MPLAYERAPP *pThis);
//Menu Callback
void _MPlayerWndEqSettingMenuSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// SongInfo Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __MPLAYERAP_ID3_INFO__
MAE_Ret _MPlayerWndSongInfoCreateWnd(MMI_MPLAYERAPP *pThis, boolean bHasID3Info);
MAE_Ret _MPlayerWndSongInfoDestroyWnd(MMI_MPLAYERAPP *pThis);
#endif
//Press Callback
boolean _MPlayerWndSongInfoKeypressCB(MMI_MPLAYERAPP *pThis, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_WChar* _MPlayerWndSongInfoGenerateSongInfoString(MMI_MPLAYERAPP *pThis, AudioPlayerSrvID3InfoEx_t *pId3ExInfo, boolean bHasID3Info);
void _MPlayerWndGetSongInfo(MMI_MPLAYERAPP *pThis);

//////////////////////////////////////////////////////////////////////////////////////
// DeletePlaylist function
//////////////////////////////////////////////////////////////////////////////////////
void _MPlayerWndDeletePlaylistDelele(MMI_MPLAYERAPP* pThis);
MAE_Ret _MPlayerWndPlaylistsDeleteConfirmDialogKeypressCB(void *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);

//////////////////////////////////////////////////////////////////////////////////////
// DeleteMedia function
//////////////////////////////////////////////////////////////////////////////////////
void _MPlayerWndDeleteMediaLoadPlaylistDataCB(MMI_MPLAYERAPP* pThis, PLAYLISTSRV_Rquest_Result_e eResult);
void _MPlayerWndDeleteMediaDelele(MMI_MPLAYERAPP* pThis);
MAE_Ret _MPlayerWndPlaylistContentDeleteConfirmDialogKeypressCB(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);

//////////////////////////////////////////////////////////////////////////////////////
// AddMedia Wnd function
//////////////////////////////////////////////////////////////////////////////////////
void _MPlayerWndAddMediaSaveLoadPlaylistDataCB(MMI_MPLAYERAPP *pThis, PLAYLISTSRV_Rquest_Result_e eResult);
MAE_Ret _MPlayerLaunchPickFiles(MMI_MPLAYERAPP *pThis);
void _MPlayerReleaseFileMgrPickFiles(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerSavePlaylistFromFileMgr(MMI_MPLAYERAPP *pThis);
void _MPlayerWndAddMediaSave(MMI_MPLAYERAPP *pThis);
void _MPlayerWndAddMediaPickFileSaveHandle(MMI_MPLAYERAPP* pThis);
void _MPlayerWndAddMediaHandleStopSuccessCommandSkip(MMI_MPLAYERAPP *pThis);

//////////////////////////////////////////////////////////////////////////////////////
// ChangeOrder Wnd function
//////////////////////////////////////////////////////////////////////////////////////
MAE_Ret _MPlayerWndChangeOrderCreateWnd(MMI_MPLAYERAPP *pThis, ChangeOrderWndData_t *pWndData);
MAE_Ret _MPlayerWndChangeOrderDestroyWnd(MMI_MPLAYERAPP *pThis, ChangeOrderWndData_t *pWndData);
//Menu AdaptGet/FreeItem
void _MPlayerChangeOrderMenuAdaptGet(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenuWdg, u32 nIndex);
void _MPlayerChangeOrderMenuFreeItem(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
//Menu Callback
void _MPlayerWndChangeOrderMenuSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
//Playlist Callback
void _MPlayerWndChangeOrderLoadPlaylistDataCB(MMI_MPLAYERAPP *pThis, PLAYLISTSRV_Rquest_Result_e eResult);
void _MPlayerWndChangeOrderHandleStopSuccess(MMI_MPLAYERAPP *pThis);
//Update
void _MPlayerWndChangeOrderUpdate(MMI_MPLAYERAPP* pThis);
MAE_Ret _MPlayerWndChangeOrderUpdateMenuIcon(MMI_MPLAYERAPP *pThis, IWidget *pMenuWdg, u32 nMoveItemIndex, boolean bMark);

//////////////////////////////////////////////////////////////////////////////////////
// SetCover Wnd function
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __PLAYLIST_COVER_MMI__
MAE_Ret _MPlayerWndChangeCoverMenuCreateWnd(MMI_MPLAYERAPP *pThis, ChangeCoverMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndChangeCoverMenuDestroyWnd(MMI_MPLAYERAPP *pThis, ChangeCoverMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndChangeCoverMenuConvertWnd(MMI_MPLAYERAPP *pThis, ChangeCoverMenuWndData_t *pWndData);

void _MPlayerWndChangeCoverMenuPickCover(MMI_MPLAYERAPP *pThis, ChangeCoverMenuWndData_t *pWndData);
void _MPlayerWndChangeCoverMenuSaveThumbImg(MMI_MPLAYERAPP *pThis, ChangeCoverMenuWndData_t *pWndData, MAE_WChar *pPickFileUrl);
void _MPlayerPListImgDecodeNotify(IImage *pImage, IBase *pData, ImgStatus_t nStatus);
void _MPlayerWndChangeCoverMenuReleaseIfSetCoverData(MPLAYERAPP_SET_COVER_INFO **ppSetCover, IBase *pOwner);
MAE_Ret _MPlayerWndChangeCoverMenuLaunchPickerForCover(MMI_MPLAYERAPP *pThis, ChangeCoverMenuWndData_t *pWndData);
MAE_Ret _MPlayerWndChangeCoverMenuStartToCacheCoverImg(MMI_MPLAYERAPP *pThis, ChangeCoverMenuWndData_t *pWndData, MAE_WChar *pPickFileUrl);
void _MPlayerWndChangeCoverMenuSoftkeyCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);
MAE_Ret _MPlayerWndChangeCoverMenuSetCurrentCoverAsDefault(MMI_MPLAYERAPP *pThis);
void _MPlayerGetCoverImageFileContentFilterCb(FileManagerFileInfo_t *sFileInfo, boolean *pbReject, u32 *pnWarningMsgTextId);
void _MPlayerGetFileByBrowseForSetCoverCb(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
#endif

//////////////////////////////////////////////////////////////////////////////////////
// Common Utility
//////////////////////////////////////////////////////////////////////////////////////
void _MPlayerShowInfoDialog(MMI_MPLAYERAPP *pThis, u32 nTextID, MPLAYERAPP_DISPLAYMODE_e eDisplayMode, PFN_DlgHandler pfnInfoDialogHdlCB);
void _MPlayerShowWaitingDialog(MMI_MPLAYERAPP *pThis, u32 nTextID, MPLAYERAPP_DISPLAYMODE_e eDisplayMode, SoftkeyID_e eLsk, SoftkeyID_e eCsk, SoftkeyID_e eRsk, PFN_DlgHandler pfnDialogHdlCB);
void _MPlayerShowConfirmDialog(MMI_MPLAYERAPP *pThis, u32 nTextID, PFN_DlgHandler pfnDialogHdlCB);
void _MPlayerShowPlaylistSpaceFullDialog(MMI_MPLAYERAPP *pThis, MPLAYERAPP_DISPLAYMODE_e eDisplayMode, PFN_DlgHandler pfnInfoDialogHdlCB);
MAE_Ret _MPlayerSearchingDialogCB(void *pApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);

MAE_Ret _MPlayerUpdateOperationCheck(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerGetID3Info(MMI_MPLAYERAPP *pThis);
#ifdef __MPLAYERAP_ID3_INFO__
void _MPlayerGetID3InfoExCB(void *pApplet, u32 nCusData, MediaSrvErrCode_e eErrorCode, AudioPlayerSrvID3InfoEx_t *pID3Info);
void _MPlayerOptionMenuSelectGetID3InfoExCB(void *pApplet, u32 nCusData, MediaSrvErrCode_e eErrorCode, AudioPlayerSrvID3InfoEx_t *pID3InfoEx);
#endif
MAE_Ret _MPlayerSetModifiedPlayingResource(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerGetPlayingResourceFromService(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerGetCurrentServiceState(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerSetPlayingResourceToService(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerReleasePlayingPlaylistResource(MMI_MPLAYERAPP *pThis);

MAE_Ret _MPlayerTriggerDoneTimeoutCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _MPlayerTriggerDuplicateNameTimeoutCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _MPlayerTriggerErrorTimeoutCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
MAE_Ret _MPlayerTriggerTempUsePhoneTimeoutCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
#ifndef __ONBOARD_USER_STORAGE_MMI__
MAE_Ret _MPlayerTriggerStopAppTimeoutCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
#if defined(ENABLE_SRSWOWHD)
MAE_Ret _MPlayerTriggerSRSParamRestoredTimeoutCB(void *pData, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
#ifdef __BLUETOOTH_AVRCP_MMI__
void _MPlayerExtDevPlaybackReqCB(AudioPlayerSrvActionType_e eAction, AudioPlayerSrvActionResult_e *eAcceptRes, IBase *pListener);
#endif
void _MPlayerGeneratePlaylistFileFullPath(MMI_MPLAYERAPP *pThis, MAE_WChar *pInFilename, MAE_WChar **pOutFilename, PLAYLISTSRV_PlaylistType_e ePlaylistType);

MAE_Ret _MPlayerCreatePlaylistDataModel(MMI_MPLAYERAPP *pThis, boolean* bHasReloadPlaylist);
void _MPlayerDecideIfReloadPlaylistDataModel(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerCheckSDFreeSpace(MMI_MPLAYERAPP *pThis, u32 nReqSpace);
MAE_Ret _MPlayerMakeM3UFolder(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerMakeMusicFolder(MMI_MPLAYERAPP *pThis);

void _MPlayerDeregisterAllCb(void);
void _MPlayerCheckCloseAp(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerUpdateDetailInfo(MMI_MPLAYERAPP* pThis, MAE_WChar *pURL, u32 *pTotalTime);
u32 _MPlayerUpdateMediaInfo(MMI_MPLAYERAPP* pThis, AudioPlayerSrvFileInfo_t *pMediaFileInfo);
boolean _MPlayerIsPredfinedList(MMI_MPLAYERAPP *pThis, u32 nIndex);
void _MPlayerDeleteOptionMenuItem(IWidget *pOptionMenuWdg, u32 nMenuId);
void _MPlayerUpdateRepeatIcon(MMI_MPLAYERAPP *pThis, IWidget *pImageWidget);
MAE_Ret _MPlayerStartPlay(MMI_MPLAYERAPP *pThis);
u32 _MPlayerGeneratePlayListFilePath(MMI_MPLAYERAPP *pThis, u32 nIndex);
MAE_Ret _MPlayerUpdateViewPlaylistData(MMI_MPLAYERAPP *pThis);
void _MPlayerGeneratePlaylistFilename(MAE_WChar *pInFilename, MAE_WChar **pOutFilename, PLAYLISTSRV_PlaylistType_e ePlaylistType);
void _MPlayerFreeDetailsInfo(MPLAYERAPP_DETAILS_DBINFO *pDetailsInfo);
MAE_Ret _MPlayerStopByUpdatePlayList(MMI_MPLAYERAPP *pThis, u8 eStopReason);
#ifdef __PLAYLIST_COVER_MMI__
MAE_WChar* _MPlayerGenerateCurrentPlstURL(MMI_MPLAYERAPP *pThis);
#endif
MAE_Ret _MPlayerResetConflictAudioEffect(MMI_MPLAYERAPP *pThis, MPLAYERAPP_AUDIO_EFFECT_e eActEffect, boolean *pResetEffect);
#ifdef __MPLAYERAP_ID3_INFO__
void _MPlayerFreeID3ExInfoContent(AudioPlayerSrvID3InfoEx_t *pID3ExInfo);
MAE_Ret _MPlayerDupID3ExInfo(AudioPlayerSrvID3InfoEx_t *pDstID3Info, AudioPlayerSrvID3InfoEx_t *pSrcID3Info);
#endif

//Search
void _MPlayerSearchFolderMp3Files(MMI_MPLAYERAPP *pThis, MAE_WChar *pDirPath);
void _MPlayerWndAppendContentAfterSearchResultCb(void *pApplet, PLAYLISTSRV_Rquest_Result_e eResult, IDataModel *pPlaylistDataModel);
void _MPlayerDestoryAllSearchMarkListHandle(MMI_MPLAYERAPP *pThis);
void _MPlayerDestorySearchMarkListHandle(MMI_MPLAYERAPP* pThis);

#if defined(__DUAL_CARD__)
void _MPlayerWndAppendContentAfterSearchResultInCard2Cb(void *pApplet, PLAYLISTSRV_Rquest_Result_e eResult, IDataModel *pPlaylistDataModel);
void _MPlayerDestorySearchInCard2MarkListHandle(MMI_MPLAYERAPP* pThis);
#endif

#ifdef __ONBOARD_USER_STORAGE_MMI__
void _MPlayerWndAppendContentAfterSearchResultInNandCb(void *pApplet, PLAYLISTSRV_Rquest_Result_e eResult, IDataModel *pPlaylistDataModel);
void _MPlayerDestorySearchInNandMarkListHandle(MMI_MPLAYERAPP* pThis);
#endif

#ifdef __MPLAYERAP_SHOW_SEEK_BAR__
MAE_Ret _AudioPlayerUpdateProgressBar(MMI_MPLAYERAPP *pThis, boolean nReset);
#endif

//Pick
void _MPlayerGetFileByBrowseCb(void *pvUserData, MAE_Ret nRspCode, AppGetFileRspData_t *psRspData, AppGetFileByBrowseRspDataFreeCb pfnRspDataFreeCb);
void _MPlayerPfnFileManagerMultiPickGetOptionMenuCb(void *pUserData, u32 nFolderLevel, void *pFileInfo, u32 *pOptonMeneuItemNum, const WdgStaticMenuItem_t **pOptionMeneuItemList, PfnFileMgrOptMenuSelectCb *pfnSelectCb);

//Utility
MAE_WChar* _MPlayerConvertPlaylistIndexToDisplayName(MMI_MPLAYERAPP *pThis, u32 nPlaylistIndex);
void _MPlayerEnableKeyguardAndScreenSaver(MMI_MPLAYERAPP *pThis, boolean bEnable);
#ifdef __ONBOARD_USER_STORAGE_MMI__
MAE_Ret _MPlayerDeletePhonePredefinedPlaylist(MMI_MPLAYERAPP *pThis);
#endif

#ifdef __MMI_MPLAYERAPP_FF_REWIND__
// Fast Forward and Rewind
MAE_Ret _MPlayerFFRewindStart(MMI_MPLAYERAPP* pThis);
void _MPlayerTimeoutFFRewindStart_CB(void *pUser, void *pUserData);
MAE_Ret _MPlayerFFRewindStop(MMI_MPLAYERAPP *pThis);
MAE_Ret _MPlayerCancelFFRewind(MMI_MPLAYERAPP * pThis);
#endif
#ifdef __MPLAYERAP_TOUCH_SEEK__
void _MPlayerTimeoutUpdateCancelBtn_CB(void *pUser, void *pUserData);
void _MPlayerCancelUpdateCancelBtn(void *pUser);
#endif
#if defined(__MPLAYERAP_TOUCH_SEEK__) || defined(__MPLAYERAP_SHOW_SEEK_BAR__)
    void _AudioPlayerDisableSeekBar(void *pApplet, boolean bDisable);
#endif
#ifdef __MPLAYERAP_TOUCH_SEEK__
MAE_Ret _AudioPlayerInitIndicatorWidgetCBFunc(IWidget * pIWidget);
#endif
#ifdef __MPLAYERAP_SHOW_SEEK_BAR__
MAE_Ret _AudioPlayerUpdateDurTextProgressBar(MMI_MPLAYERAPP *pThis, boolean bNeedUpdateScreen);
MAE_Ret _AudioPlayerNormalScreenUpdateInfo(MMI_MPLAYERAPP *pThis);
#endif
///////////////////////////////////////////////////////////////////////////////////////

#endif //__MMI_MPLAYERAPP_PRIV_H__
