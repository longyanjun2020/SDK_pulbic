/**
 * @file    mmi_wdg_mpdesktop_priv.h
 * @brief   The internal structure of the mp desktopwidget

 */

#ifndef __MMI_WDG_MPDESKTOP__PRIVH__
#define __MMI_WDG_MPDESKTOP__PRIVH__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_desktop.h"
#include "mmi_srv_header.h"
#include "rs_layout_id.h"

#define TITLE_TEXTCOLOR 0x435600

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__UI_STYLE_MMI_ANDROID_4_0_GADGET__)
#define __MP_DESKTOPWDG_3D_UI_M303_MMI__
#endif // 3D UI

enum
{
	MPDESKTOP_VOLUME_BTN = 0,
	MPDESKTOP_PREVIOUS_BTN,
	MPDESKTOP_PLAYSTOP_BTN,
	MPDESKTOP_NEXT_BTN,
#ifdef __MP_DESKTOPWDG_3D_UI_M303_MMI__
	MPDESKTOP_REPEAT_BTN,
	MPDESKTOP_SHUFFLE_BTN,
#endif
	MPDESKTOP_NUM_OF_BTN,
};

// Note this is # of subwidgets need to handle event
#define NUM_SUBWIDGET (MPDESKTOP_NUM_OF_BTN)

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__)

typedef struct
{
	DECLARE_BASECLASS_DESKTOPWIDGET

	// Subwidget codes
	IWidget			*pITitleTextWidget;
	IWidget			*pIVolumeBtnWidget;
	IWidget			*pIPreviousBtnWidget;
	IWidget			*pIPlayStopBtnWidget;
	IWidget			*pINextBtnWidget;

    IUSBSRV *pIUSBSrv;
	IAUDIOPLAYERSRV *pIMPlayerSrv;

	boolean			bTouchInSubwidget;
	boolean			bIsWaitConfirm;
    boolean         bIsStopbyPrevNext;
	u16				uSubwidgetIndex;
    boolean bSkipBackgroundInd; // A tricky flag tells MP desktop widget doesn't update title and buttons when this flag is set as TRUE

#ifdef __MP_DESKTOPWDG_3D_UI_M303_MMI__
    IAUDIOSRV 		*pIAudioSrv;
	AudioPlayerSrvFileInfo_t stCurrentMediaFileInfo; // the file info of the media from the mplayersrv
	AudioPlayerSrvID3Info_t stID3Info;
    MplayerDesktopWidget_Style_e eMplayerStyle;
	IDataModel      *pPlayingDataModel;			// This ArrayModel points to the playing list (It could be the same as the pPlaylistContentVectorModel)
	IPLAYLISTSRV    *pIPlayList;   // the interface of IPLAYLISTSRV
	MAE_WChar       *pPlayingPlayListFilename; // the current playing playlist
    IWidget         *pControlBarImageWdg;
    IWidget         *pRepeatButtonWdg;
    IWidget         *pIndexTextWdg;
    IWidget         *pShuffleSwitchIconWdg;
    IWidget         *pGLFotoListWdg;
    IWidget         *pID3ArtistTextWdg;
    IWidget         *pIndicatorTextWdg;
    IWidget         *pIndicatorWdg;
    IWidget         *pSlashTextWdg;
    IWidget         *pDurationTotalTextWdg;
	u32             nPlaylistSize;	// the size of the playlist
	u32             nPlayingIndex;	// the index of current playing media in the view list
	u32             nDuration;
	u32             nCurrentPosition;
#endif

    Subwidget_Geometry_Info subwgtGeoInfo[NUM_SUBWIDGET];
} MpDesktopWdg_t;

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
void MpDesktopWidget_BtnClickCb(void *pApplet, void *pUserData, WidgetEvtCode_t nEvtCode, u32 nParam,IWidget *pBtnWidget);
void MpDesktopWidgetFreeButtonDataModel(void *pUserData, IBase *pOwner);

#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__
#endif //__MMI_WDG_MPDESKTOP__PRIVH__
/*=============================================================*/
// end of file
