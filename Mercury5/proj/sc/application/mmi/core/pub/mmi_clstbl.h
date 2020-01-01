/**
* @file mmi_clstbl.h
* @version $Id: mmi_clstbl.h 41871 2009-09-30 11:56:21Z creck.wang $
*
* @brief
* This file defines the table of class ids and their constructors.
*
* The class ids in MAE platform are separated into several categories. Each category has
* a base value and forms an id-constructor relation table. These tables are used in shell's
* CreateInstance() method to allocate and construct an object instance.
*
* Note: max allowed class ids in each category is 0x1000 (4096)
*
*/
#ifndef __MMI_CLSTBL_H__
#define __MMI_CLSTBL_H__
#include "mmi_mae_shell.h"
#include "mmi_mae_clstbl.h"
#define DECLARE_VEN_APP_CLSID(_clsID) \
	MMI_DEFINE_CLSID(_clsID, VendorAppNew),
// macros to define class id and the associated new function
#if defined __MMI_CLSTBL_C__
#define MMI_DEFINE_CLS_CATEGORY(Cat) \
	extern const MAE_ClassInfo_t Cat[]; \
	const MAE_ClassInfo_t Cat[] =
#define MMI_DEFINE_CLSID_BASE(ClsId, Base, Constructor) {Constructor}
#define MMI_DEFINE_CLSID(ClsId, Constructor) {Constructor}
#define MMI_DEFINE_END_OF_CLSID(ClsId) {0}
#define MMI_DECLARE_NEW_FUNC(_func_) extern MAERet_t _func_(MAEClsId_t, void**)
#elif defined __MMI_ENUM_STRING__
#define MMI_DEFINE_CLS_CATEGORY(Cat) \
	enum class Cat##_e
#define MMI_DEFINE_CLSID_BASE(ClsId, Base, Constructor) ClsId = Base
#define MMI_DEFINE_CLSID(ClsId, Constructor) ClsId
#define MMI_DEFINE_END_OF_CLSID(ClsId) ClsId
#elif defined __NAME__
#define MMI_DEFINE_CLS_CATEGORY(Cat) \
	extern char Cat##_t[][40];\
	char Cat##_t[][40]=
#define MMI_DEFINE_CLSID_BASE(ClsId, Base, Constructor)		#ClsId
#define MMI_DEFINE_CLSID(ClsId, Constructor)	#ClsId
#define MMI_DEFINE_END_OF_CLSID(ClsId)			#ClsId
#elif defined __ID__
#define MMI_DEFINE_CLS_CATEGORY(Cat) \
	enum
#define MMI_DEFINE_CLSID_BASE(ClsId, Base, Constructor) ClsId = Base
#define MMI_DEFINE_CLSID(ClsId, Constructor) ClsId
#define MMI_DEFINE_END_OF_CLSID(ClsId) ClsId
#else
#define MMI_DEFINE_CLS_CATEGORY(Cat) \
	extern const MAE_ClassInfo_t Cat[]; \
	enum
#define MMI_DEFINE_CLSID_BASE(ClsId, Base, Constructor) ClsId = Base
#define MMI_DEFINE_CLSID(ClsId, Constructor) ClsId
#define MMI_DEFINE_END_OF_CLSID(ClsId) ClsId
#endif // __MMI_CLSTBL_C__ || __MMI_ENUM_STRING__
//
// header file or prototype declaration for the new function of each class
//
#ifdef __MMI_CLSTBL_C__
// widget classes
/**-----------------------------------------------------*
*	Platform Style Area	(1/5)							*
*------------------------------------------------------*/
MMI_DECLARE_NEW_FUNC(DispCanvas_New);
MMI_DECLARE_NEW_FUNC(ViewMgr_New);
MMI_DECLARE_NEW_FUNC(View_New);
MMI_DECLARE_NEW_FUNC(WndMgr_New);
MMI_DECLARE_NEW_FUNC(TextWidget_New);

#ifdef __SLIM_MMI__
/*TextBubble widget is disabled in SMALL_ROM_32 products */
#define TextBubbleWidget_New NULL
#else
MMI_DECLARE_NEW_FUNC(TextBubbleWidget_New);
#endif  //__SLIM_MMI__

MMI_DECLARE_NEW_FUNC(SoftkeyWidget_New);
MMI_DECLARE_NEW_FUNC(BitmapWidget_New);
MMI_DECLARE_NEW_FUNC(CaretWidget_New);
MMI_DECLARE_NEW_FUNC(ImageTextImageWidget_New);
MMI_DECLARE_NEW_FUNC(InputWidget_New);
MMI_DECLARE_NEW_FUNC(StatusBarWidget_New);
MMI_DECLARE_NEW_FUNC(InputController_New);
MMI_DECLARE_NEW_FUNC(ListWidget_New);
MMI_DECLARE_NEW_FUNC(MenuWidget_New);
MMI_DECLARE_NEW_FUNC(ProgressWidget_New);
MMI_DECLARE_NEW_FUNC(FormatInputWidget_New);
MMI_DECLARE_NEW_FUNC(FadeoutWidget_New);
MMI_DECLARE_NEW_FUNC(OptionMenuWidget_New);
MMI_DECLARE_NEW_FUNC(PopupSelectWidget_New);
MMI_DECLARE_NEW_FUNC(DoubleItem_New);
MMI_DECLARE_NEW_FUNC(Image_DoubleItem_New);
MMI_DECLARE_NEW_FUNC(SwitchIconWidget_New);
MMI_DECLARE_NEW_FUNC(SwitchIconItemWidget_New);
MMI_DECLARE_NEW_FUNC(InputGridWidget_New);
MMI_DECLARE_NEW_FUNC(InputCandidateWidget_New);
MMI_DECLARE_NEW_FUNC(CommonPickItem_New);
MMI_DECLARE_NEW_FUNC(TimerFormatWidget_New);
MMI_DECLARE_NEW_FUNC(InputHelperWidget_New);

#ifdef __IME_MMI_MY_INPUT_HELPER__
#define _InputHelperWidget_New InputHelperWidget_New
#else
#define _InputHelperWidget_New NULL
#endif
MMI_DECLARE_NEW_FUNC(ButtonWidget_New);
MMI_DECLARE_NEW_FUNC(VolumeWidget_New);
MMI_DECLARE_NEW_FUNC(OsdWidget_New);
#if defined __HANDWRITING_MMI__ && defined __TOUCH_SCREEN_MMI__
MMI_DECLARE_NEW_FUNC(HandWritingWidget_New);
#else
#define HandWritingWidget_New NULL
#endif
#if defined __IME_MMI_SOFTKEYBOARD__ && defined __TOUCH_SCREEN_MMI__
MMI_DECLARE_NEW_FUNC(SoftKeyboardWidget_New);
#else
#define SoftKeyboardWidget_New NULL
#endif
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
MMI_DECLARE_NEW_FUNC(Softkeyboard_HighlightWidget_New);
#else
#define Softkeyboard_HighlightWidget_New NULL
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__
#ifdef __TOUCH_SCREEN_MMI__
MMI_DECLARE_NEW_FUNC(SlideSwitchWidget_New);
#else
#define SlideSwitchWidget_New NULL
#endif
#ifndef __WIDGET_DISABLE_FINGERCOMMAND__
MMI_DECLARE_NEW_FUNC(FCTimeWidget_New);
MMI_DECLARE_NEW_FUNC(FCDateWidget_New);
#else
#define FCTimeWidget_New NULL
#define FCDateWidget_New NULL
#endif
MMI_DECLARE_NEW_FUNC(EventWidget_New);

#ifdef __SLIM_MMI__
//DummyWidget, pulldownWidget and BasicBitmapWidget
//are disabled in SMALL_ROM_32 products
#define DummyWidget_New NULL
#define PullDownWidget_New NULL
#define BasicBitmapWidget_New NULL
#else
MMI_DECLARE_NEW_FUNC(DummyWidget_New);
MMI_DECLARE_NEW_FUNC(PullDownWidget_New);
MMI_DECLARE_NEW_FUNC(BasicBitmapWidget_New);
#endif //__SLIM_MMI__

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
MMI_DECLARE_NEW_FUNC(DesktopWidget_New);
MMI_DECLARE_NEW_FUNC(CalendarDesktopWidget_New);
MMI_DECLARE_NEW_FUNC(DclockDesktopWidget_New);
MMI_DECLARE_NEW_FUNC(AclockDesktopWidget_New);
#else
#define DesktopWidget_New NULL
#define CalendarDesktopWidget_New NULL
#define DclockDesktopWidget_New NULL
#define AclockDesktopWidget_New NULL
#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__ || __3D_UI_IDLE_SIMPLE__

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__) || defined(__3D_UI_IDLE_MULTIPAGE__)
MMI_DECLARE_NEW_FUNC(MpDesktopWidget_New);
MMI_DECLARE_NEW_FUNC(OpDesktopWidget_New);
MMI_DECLARE_NEW_FUNC(ShortcutDesktopWidget_New);
MMI_DECLARE_NEW_FUNC(SearchDesktopWidget_New);
#if defined(__APP_MMI_FM_RADIO__)
MMI_DECLARE_NEW_FUNC(FmDesktopWidget_New);
#else
#define FmDesktopWidget_New NULL
#endif
#else
#define MpDesktopWidget_New NULL
#define OpDesktopWidget_New NULL
#define ShortcutDesktopWidget_New NULL
#define SearchDesktopWidget_New NULL
#define FmDesktopWidget_New NULL
#endif //__GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__ || __3D_UI_IDLE_MULTIPAGE__

#if defined(__3D_UI_IDLE_SIMPLE__)
MMI_DECLARE_NEW_FUNC(RotateCubeWidget_New);
#else
#define RotateCubeWidget_New NULL
#endif /* __3D_UI_IDLE_SIMPLE__ */

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
MMI_DECLARE_NEW_FUNC(ShortcutBarWidget_New);
#ifndef __WIDGET_DISABLE_DATEICON__
MMI_DECLARE_NEW_FUNC(DateIconWidget_New);
#else
#define DateIconWidget_New NULL
#endif
MMI_DECLARE_NEW_FUNC(AliveWidget_New);
MMI_DECLARE_NEW_FUNC(NoteDesktopWidget_New);
MMI_DECLARE_NEW_FUNC(ProfileWidget_New);
#else
#define ShortcutBarWidget_New NULL
#define DateIconWidget_New NULL
#define AliveWidget_New NULL
#define NoteDesktopWidget_New NULL
#define ProfileWidget_New NULL
#endif // __GADGETS_MMI__ || __3D_UI_IDLE_GADGETBAR__

#if defined(__3D_UI_IDLE_MULTIPAGE__)
MMI_DECLARE_NEW_FUNC(MessageDesktopWidget_New);
MMI_DECLARE_NEW_FUNC(PhonebookDesktopWidget_New);
MMI_DECLARE_NEW_FUNC(PhotoDesktopWidget_New);
#else
#define MessageDesktopWidget_New NULL
#define PhonebookDesktopWidget_New NULL
#define PhotoDesktopWidget_New NULL
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__) && defined(__APP_MMI_NOTEPAD__)
MMI_DECLARE_NEW_FUNC(NotepadDesktopWidget_New);
#else
#define NotepadDesktopWidget_New NULL
#endif

#if defined(__WDG_ANIMIMAGE__) || defined(__DROPDOWN_STATUSPAGE__) || defined(__3D_UI_KEYGUARD__)
MMI_DECLARE_NEW_FUNC(AnimImageWidget_New);
#else
#define AnimImageWidget_New NULL
#endif

#if defined(__APP_MMI_GROUP_APP__)
MMI_DECLARE_NEW_FUNC(GroupWidget_New);
#else
#define GroupWidget_New NULL
#endif

#define TabDesktopWidget_New NULL
#define InfoDesktopWidget_New NULL

#if defined(__3D_UI_MAINMENU__)
MMI_DECLARE_NEW_FUNC(GlMenuWidget_New);
#else
#define GlMenuWidget_New NULL
#endif //__3D_UI_MAINMENU__

#if defined(__3D_MESSAGE_BOX__)
MMI_DECLARE_NEW_FUNC(GlBoxListWdg_New);
#else
#define GlBoxListWdg_New NULL
#endif

#if defined(__DROPDOWN_STATUSPAGE__)
MMI_DECLARE_NEW_FUNC(StatusPageWidget_New);
#else
#define StatusPageWidget_New NULL
#endif

#if defined(__FEATURE_MGL__)
MMI_DECLARE_NEW_FUNC(FlipEffectWdg_New);
MMI_DECLARE_NEW_FUNC(Gl3dLoaderWdg_New);
MMI_DECLARE_NEW_FUNC(GLTransformWidget_New);
MMI_DECLARE_NEW_FUNC(AnimationContainer_New);
#else
#define FlipEffectWdg_New NULL
#define Gl3dLoaderWdg_New NULL
#define GLTransformWidget_New NULL
#define AnimationContainer_New NULL
#endif //__FEATURE_MGL__

#if defined(__APP_MMI_SCREENSAVER__) && defined(__3D_UI_SCREENSAVER_EFFECT__)
MMI_DECLARE_NEW_FUNC(ScreensaverEffect_New);
#else
#define ScreensaverEffect_New NULL
#endif

#if defined(__MMI_BEAUTY_CLK_APP__) || defined(__3D_UI_EBOOK__)
MMI_DECLARE_NEW_FUNC(MagnifyWdg_New);
#else
#define MagnifyWdg_New NULL
#endif //__MMI_BEAUTY_CLK_APP__ || __3D_UI_EBOOK__

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_MPLAYER__)
MMI_DECLARE_NEW_FUNC(GlAlbumSlideWdg_New);
#else
#define GlAlbumSlideWdg_New NULL
#endif //__3D_UI_IDLE_MULTIPAGE__ || __3D_UI_MPLAYER__

#if defined(__3D_UI_MPLAYER__)
MMI_DECLARE_NEW_FUNC(SpectrumWidget_New);
#else
#define SpectrumWidget_New NULL
#endif //__3D_UI_MPLAYER__

#if defined(__MMI_BEAUTY_CLK_APP__) || defined(__3D_UI_KEYGUARD_BEAUTY_CLK__)
MMI_DECLARE_NEW_FUNC(ClothEffectWdg_New);
#else
#define ClothEffectWdg_New NULL
#endif //__MMI_BEAUTY_CLK_APP__ || __3D_UI_KEYGUARD_BEAUTY_CLK__

#if defined(__3D_UI_KINGMOVIE__)
MMI_DECLARE_NEW_FUNC(GlCircleListWdg_New);
#else
#define GlCircleListWdg_New NULL
#endif //__3D_UI_KINGMOVIE__

#if defined(__UI_STYLE_MMI_MAIN_MENU_3D_SPIN__)
MMI_DECLARE_NEW_FUNC(GlRotationMenuWidget_New);
#else
#define GlRotationMenuWidget_New NULL
#endif //__UI_STYLE_MMI_MAIN_MENU_3D_SPIN__

#if defined(__APP_MMI_FM_RADIO__) && defined(__3D_UI_FMRADIO__)
MMI_DECLARE_NEW_FUNC(FlipTextWidget_New);
#else
#define FlipTextWidget_New NULL
#endif //__APP_MMI_FM_RADIO__ && __3D_UI_FMRADIO__

#if defined(__3D_UI_KEYGUARD_GLOW__)
MMI_DECLARE_NEW_FUNC(GlowTextWidget_New);
#else
#define GlowTextWidget_New NULL
#endif //__3D_UI_KEYGUARD_GLOW__

#if defined(__3D_UI_COVERFLOW_MMI__)
MMI_DECLARE_NEW_FUNC(GlCoverFlowWdg_New);
#else
#define GlCoverFlowWdg_New NULL
#endif

#if defined(__3D_UI_PHOTOSLIDE_MMI__)
MMI_DECLARE_NEW_FUNC(GlPhotoSlideWdg_New);
#else
#define GlPhotoSlideWdg_New NULL
#endif

#if defined(__3D_UI_IDLE_GADGETBAR__)
MMI_DECLARE_NEW_FUNC(PropCircleContainer_New);
#else
#define PropCircleContainer_New NULL
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__)
MMI_DECLARE_NEW_FUNC(MultipageContainer_New);
#else
#define MultipageContainer_New NULL
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE_CUBEVIEW__)
MMI_DECLARE_NEW_FUNC(GlMlpgWdg_New);
#else
#define GlMlpgWdg_New NULL
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__) && !defined(__3D_UI_IDLE_MULTIPAGE_CUBEVIEW__)
MMI_DECLARE_NEW_FUNC(GlMultiIdlePageWdg_New);
#else
#define GlMultiIdlePageWdg_New NULL
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_PHOTOSLIDE_MMI__)
MMI_DECLARE_NEW_FUNC(GlFotoListPageWdg_New);
#else
#define GlFotoListPageWdg_New NULL
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_IDLE_SIMPLE__)
MMI_DECLARE_NEW_FUNC(GlTimeIndWdg_New);
#else
#define GlTimeIndWdg_New NULL
#endif

#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_STYLE_SWITCH__)
MMI_DECLARE_NEW_FUNC(IFoneWidget_New);
#else
#define IFoneWidget_New NULL
#endif /* __UI_STYLE_MMI_IFONE__  || __UI_STYLE_MMI_STYLE_SWITCH__*/

#if defined(__UI_STYLE_MMI_ANDROID_IDLE__)
MMI_DECLARE_NEW_FUNC(DragWidget_New);
#else
#define DragWidget_New NULL
#endif// __UI_STYLE_MMI_ANDROID_IDLE__

#if defined(__LIVE_WALLPAPER__)
MMI_DECLARE_NEW_FUNC(WallpaperWidget_New);
#else
#define WallpaperWidget_New     NULL
#endif //__LIVE_WALLPAPER__

#ifdef __SCREEN_EFFECTS_SUPPORT__
MMI_DECLARE_NEW_FUNC(ScreenEffectWidget_New);
#else
#define ScreenEffectWidget_New NULL
#endif // __SCREEN_EFFECTS_SUPPORT__

#ifdef __MULTI_TOUCH__
MMI_DECLARE_NEW_FUNC(MultiTouchTestWidget_New);
#else
#define MultiTouchTestWidget_New NULL
#endif

// container classes
MMI_DECLARE_NEW_FUNC(AbsContainer_New);
MMI_DECLARE_NEW_FUNC(PropContainer_New);
MMI_DECLARE_NEW_FUNC(RootContainer_New);
MMI_DECLARE_NEW_FUNC(MFLContainer_New);
MMI_DECLARE_NEW_FUNC(SheetContainer_New);
MMI_DECLARE_NEW_FUNC(ViewerContainer_New);
// decorator classes
MMI_DECLARE_NEW_FUNC(ImageWidget_New);
MMI_DECLARE_NEW_FUNC(OverlayImageWidget_New);
MMI_DECLARE_NEW_FUNC(SnapshotWidget_New);
MMI_DECLARE_NEW_FUNC(ScrollbarWidget_New);
MMI_DECLARE_NEW_FUNC(ViewportWidget_New);
MMI_DECLARE_NEW_FUNC(TitleWidget_New);
MMI_DECLARE_NEW_FUNC(ScrollIndicatorWidget_New);
MMI_DECLARE_NEW_FUNC(IndicatorWidget_New);
MMI_DECLARE_NEW_FUNC(TabWidget_New);
MMI_DECLARE_NEW_FUNC(IMEAssistWidget_New);
MMI_DECLARE_NEW_FUNC(PickWidget_New);
#ifndef __WIDGET_DISABLE_RINGLIST__
MMI_DECLARE_NEW_FUNC(RingListWidget_New);
#else
#define RingListWidget_New NULL
#endif
#ifndef __WIDGET_DISABLE_TRANSITION__
MMI_DECLARE_NEW_FUNC(TranWidget_New);
#else
#define TranWidget_New NULL
#endif

#if defined(__UI_STYLE_MMI_MAIN_MENU_ANIMATION__)
MMI_DECLARE_NEW_FUNC(MainMenuAnimatedWdg_New);
#else
#define MainMenuAnimatedWdg_New NULL
#endif

MMI_DECLARE_NEW_FUNC(CanvasWidget_New);
#if defined(__UI_STYLE_FLIPDCLOCK__)
MMI_DECLARE_NEW_FUNC(FlipDClockWidget_New);
#else
#define FlipDClockWidget_New NULL
#endif

#ifdef __DUAL_LCD__
#define SubStatusBarWidget_New StatusBarWidget_New
#else
#define SubStatusBarWidget_New NULL
#endif
#ifdef __APP_MMI_TUDOU_MENU_ITEM_WDG__
MMI_DECLARE_NEW_FUNC(ImageDoubleItemMultiFieldWdg_New);
#else
#define ImageDoubleItemMultiFieldWdg_New  NULL
#endif

// extra keyguard widget
#ifdef __MMI_BALLSLIDE_WDG_SUPPORT__
MMI_DECLARE_NEW_FUNC(BallSlideWidget_New);
#else
#define BallSlideWidget_New  NULL
#endif

/**-----------------------------------------------------*
*	End of Style Area	(1/5)							*
*------------------------------------------------------*/

// models
MMI_DECLARE_NEW_FUNC(TextModel_New);
MMI_DECLARE_NEW_FUNC(MenuModel_New);
MMI_DECLARE_NEW_FUNC(SoftkeyModel_New);
MMI_DECLARE_NEW_FUNC(IMEAssistModel_New);
#ifdef __MMI_SCRIPT_EASY_EDITOR__
MMI_DECLARE_NEW_FUNC(kmx_TextModel_New);
#endif /*__MMI_SCRIPT_EASY_EDITOR__*/
// services
MMI_DECLARE_NEW_FUNC(STATUSMODEL_New);
/* SRV DECLARE Generated by SMD ###Class Begin */
MMI_DECLARE_NEW_FUNC(ACCESSORYSRV_New);
MMI_DECLARE_NEW_FUNC(ALARMSRV_New);

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
MMI_DECLARE_NEW_FUNC(ALIVEWDGSRV_New);
#else
#define ALIVEWDGSRV_New NULL
#endif
MMI_DECLARE_NEW_FUNC(VideoPlayerSrvNew);
#if defined (__ENABLE_CAMERA__) || defined(__ENABLE_CAMCORDER__)
MMI_DECLARE_NEW_FUNC(CameraSrvNew);
#else
#define CameraSrvNew NULL
#endif
#ifdef __ATV_MMI__
MMI_DECLARE_NEW_FUNC(TvSrvNew);
#else
#define TvSrvNew NULL
#endif
MMI_DECLARE_NEW_FUNC(AudioRecSrvNew);
MMI_DECLARE_NEW_FUNC(AudioSrvNew);
MMI_DECLARE_NEW_FUNC(AudioEnvSrvNew);
#if defined(__BLUETOOTH_OBEX_MMI__)
MMI_DECLARE_NEW_FUNC(BTOBEXSRV_New);
#else
#define BTOBEXSRV_New NULL
#endif

#if defined(__BLUETOOTH_MMI__)
MMI_DECLARE_NEW_FUNC(BTSRV_New);
#else
#define BTSRV_New NULL
#endif
MMI_DECLARE_NEW_FUNC(CALLLOGSRV_New);
MMI_DECLARE_NEW_FUNC(CBS_New);
MMI_DECLARE_NEW_FUNC(CCSRV_New);
#ifdef __VT_3G324M__
MMI_DECLARE_NEW_FUNC(VtCcSrvNew);
MMI_DECLARE_NEW_FUNC(VtmSrvNew);
#else
#define VtCcSrvNew NULL
#define VtmSrvNew NULL
#endif
MMI_DECLARE_NEW_FUNC(CLIPBOARDSRV_New);
MMI_DECLARE_NEW_FUNC(CORESRV_New);
#if defined(__APP_MMI_COUNTDOWN_TIMER__)
MMI_DECLARE_NEW_FUNC(COUNTDOWNTIMERSRV_New);
#else
#define COUNTDOWNTIMERSRV_New NULL
#endif
MMI_DECLARE_NEW_FUNC(CPHSSRV_New);
MMI_DECLARE_NEW_FUNC(DIALOGSRV_New);
//
#if defined(__MMI_OMA_DRM_V1__)
MMI_DECLARE_NEW_FUNC(DRMAGENTSRV_New);
#else
#define DRMAGENTSRV_New NULL
#endif
//
MMI_DECLARE_NEW_FUNC(EVTCENTERSRV_New);
MMI_DECLARE_NEW_FUNC(FDNSRV_New);

#if defined(__APP_MMI_FM_RADIO__)
MMI_DECLARE_NEW_FUNC(FmradioSrvNew);
#else
#define FmradioSrvNew NULL
#endif
MMI_DECLARE_NEW_FUNC(HASHMAPSRV_New);
#if defined(__JAVA_MMI__)
MMI_DECLARE_NEW_FUNC(JAVASRV_New);
#else
#define JAVASRV_New NULL
#endif
MMI_DECLARE_NEW_FUNC(MCI_New);
#if defined(__MMS_MMI_CDMMS__)
MMI_DECLARE_NEW_FUNC(MMS_New);
#else
#define MMS_New NULL
#endif
MMI_DECLARE_NEW_FUNC(MMSRV_New);
#if defined(__MMS_MMI_CDMMS__)
MMI_DECLARE_NEW_FUNC(MMSTRANSSRV_New);
#else
#define MMSTRANSSRV_New NULL
#endif
MMI_DECLARE_NEW_FUNC(MOI_New);
MMI_DECLARE_NEW_FUNC(AudioPlayerSrvNew);
MMI_DECLARE_NEW_FUNC(OBJPROCESSINGSRV_New);
#if defined(__NATIVE_GAME_MMI_PEDOMETER__)
MMI_DECLARE_NEW_FUNC(PEDOMETERSRV_New);
#else
#define PEDOMETERSRV_New NULL
#endif
MMI_DECLARE_NEW_FUNC(PHBSRV_New);
MMI_DECLARE_NEW_FUNC(PLAYLISTSRV_New);
MMI_DECLARE_NEW_FUNC(PREVIEWLINE2SRV_New);
#if defined(__APP_MMI_PRIVATEPROTECT__)
MMI_DECLARE_NEW_FUNC(PrivateprotectSrvNew);
#else
#define PrivateprotectSrvNew NULL
#endif
MMI_DECLARE_NEW_FUNC(PROFILESRV_New);
MMI_DECLARE_NEW_FUNC(SHORTCUTSSRV_New);
MMI_DECLARE_NEW_FUNC(SIMSRV_New);
MMI_DECLARE_NEW_FUNC(SMI_New);
MMI_DECLARE_NEW_FUNC(SMS_New);
MMI_DECLARE_NEW_FUNC(SSSRV_New);
MMI_DECLARE_NEW_FUNC(STKSRV_New);
MMI_DECLARE_NEW_FUNC(TXI_New);
MMI_DECLARE_NEW_FUNC(UsbSrvNew);
MMI_DECLARE_NEW_FUNC(VCALSTORESRV_New);
#ifdef __SDK_API__
MMI_DECLARE_NEW_FUNC(VENDORSRV_New);
#else
#define VENDORSRV_New NULL
#endif //__SDK_API__

MMI_DECLARE_NEW_FUNC(CFGSrv_New);
MMI_DECLARE_NEW_FUNC(STATUSBARSRV_New);
#ifdef __CALENDAR_SUPPORT_VCS_MMI__
MMI_DECLARE_NEW_FUNC(VCALENDAR_New);
MMI_DECLARE_NEW_FUNC(VCALPARSER_New);
#define VCALPARSER_New NULL
MMI_DECLARE_NEW_FUNC(VEVENT_New);
#ifdef __APP_MMI_TODOLIST_VTODO__
MMI_DECLARE_NEW_FUNC(VTODO_New);
#endif
MMI_DECLARE_NEW_FUNC(VPARAM_New);
MMI_DECLARE_NEW_FUNC(VPROPERTY_New);
#else
#define VCALENDAR_New NULL
#define VCALPARSER_New NULL
#define VEVENT_New NULL
#define VTODO_New NULL
#define VPARAM_New NULL
#define VPROPERTY_New NULL
#endif // End of __CALENDAR_SUPPORT_VCS_MMI__
MMI_DECLARE_NEW_FUNC(CodecSrvNew);
MMI_DECLARE_NEW_FUNC(VoiceCallSrvNew);
#ifdef  __SOCKETSRV_SUPPORT__
MMI_DECLARE_NEW_FUNC(SocketSrvNew);
#else
#define SocketSrvNew NULL
#endif ///  __SOCKETSRV_SUPPORT__
#if defined(__GPS_MMI__)
MMI_DECLARE_NEW_FUNC(GPSSrvNew);
#else
#define GPSSrvNew NULL
#endif
#if defined(__WLAN_MMI__)
MMI_DECLARE_NEW_FUNC(WLANSRV_New);
#else
#define WLANSRV_New NULL
#endif
#ifdef __CALLER_LOCATION__
MMI_DECLARE_NEW_FUNC(CLSRV_New);
#else
#define CLSRV_New NULL
#endif //__CALLER_LOCATION__
#if defined(__TTS__)
MMI_DECLARE_NEW_FUNC(TTSSRV_New);
#else
#define TTSSRV_New NULL
#endif
#ifdef __TOUCH_HOTKEY__
MMI_DECLARE_NEW_FUNC(TOUCHSHORTCUTSRV_New);
#else
#define TOUCHSHORTCUTSRV_New NULL
#endif // __TOUCH_HOTKEY__
#if defined(__MSYNC_TOOL__)
MMI_DECLARE_NEW_FUNC(ATSYNCSRV_New);
#else
#define ATSYNCSRV_New NULL
#endif
#if defined (__UNIT_TEST_SRV__)
MMI_DECLARE_NEW_FUNC(UnitTestSrvNew);
#else
#define UnitTestSrvNew NULL
#endif
MMI_DECLARE_NEW_FUNC(SCHSRV_New);
// applications

/**-----------------------------------------------------*
*	Platform Style Area	(2/5)							*
*------------------------------------------------------*/
MMI_DECLARE_NEW_FUNC(AlarmAppNew);
#if defined(__ANTI_STEAL_MMI__)
MMI_DECLARE_NEW_FUNC(AntiStealAppNew);
#else
#define AntiStealAppNew NULL
#endif
#if defined(__ATV_MMI__)
MMI_DECLARE_NEW_FUNC(AtvAppNew);
#else
#define AtvAppNew NULL
#endif
#if defined(__FT_AUTO_TEST__)
MMI_DECLARE_NEW_FUNC(AutotestAppNew);
#else
#define AutotestAppNew NULL
#define AutotestAppPreNew DUMMY_PRE_NEW
#endif
#if defined(__TOUCH_SCREEN_MMI__) && defined(__APP_MMI_BJX__)
MMI_DECLARE_NEW_FUNC(BjxAppNew);
#else
#define BjxAppNew NULL
#endif
#if defined(__APP_MMI_BMI__)
MMI_DECLARE_NEW_FUNC(BmiAppNew);
#else
#define BmiAppNew NULL
#endif

#if defined(__APP_MMI_LICENSEMGR__)
MMI_DECLARE_NEW_FUNC(LicenseMgrAppNew);
#else
#define LicenseMgrAppNew NULL
#endif


#if defined(__UI_STYLE_MMI_ANDROID_IDLE__)
MMI_DECLARE_NEW_FUNC(ANDROID_IDLEAPP_New);
#else
#define ANDROID_IDLEAPP_New NULL
#endif

#ifdef __UI_STYLE_MMI_ANDROID_KEYGUARD__
MMI_DECLARE_NEW_FUNC(AndroidKeyGuardAppNew);
#else
#define AndroidKeyGuardAppNew NULL
#define AndroidKeyGuardAppPreNew DUMMY_PRE_NEW
#endif

#if defined(__UI_STYLE_MMI_ANDROID_MAIN_MENU__)
MMI_DECLARE_NEW_FUNC(MAINMENUANDROID_New);
#else
#define MAINMENUANDROID_New NULL
#endif


#if defined(__APP_MMI_PRIVATEPROTECT__)
MMI_DECLARE_NEW_FUNC(PrivateprotectAppNew);
MMI_DECLARE_NEW_FUNC(PrivateprotectpwAppNew);
#else
#define PrivateprotectAppNew NULL
#define PrivateprotectpwAppNew NULL
#endif

MMI_DECLARE_NEW_FUNC(VoiceMailAppNew);

#if defined(__BLUETOOTH_MMI__)
MMI_DECLARE_NEW_FUNC(BtAppNew);
#else
#define BtAppNew NULL
#endif
#if defined(__BLUETOOTH_MMI__)
MMI_DECLARE_NEW_FUNC(BtNotifyAppNew);
#else
#define BtNotifyAppNew NULL
#endif
#if defined(__APP_MMI_CALCULATOR__)
MMI_DECLARE_NEW_FUNC(CalculatorAppNew);
#else
#define CalculatorAppNew NULL
#endif
#if defined(__APP_MMI_CALCULATOR_PLUS__)
MMI_DECLARE_NEW_FUNC(CalculatorPlusAppNew);
#else
#define CalculatorPlusAppNew NULL
#endif
#if defined(__APP_MMI_CALENDAR__)
MMI_DECLARE_NEW_FUNC(CALENDARAPP_New);
#else
#define CALENDARAPP_New NULL
#define CalendarPreNew DUMMY_PRE_NEW
#endif
#if defined(__TOUCH_SCREEN_MMI__)
MMI_DECLARE_NEW_FUNC(CalibrationAppNew);
#else
#define CalibrationAppNew NULL
#define CalibrationAppPreNew DUMMY_PRE_NEW
#endif
MMI_DECLARE_NEW_FUNC(CallLogAppNew);
MMI_DECLARE_NEW_FUNC(CallSettingAppNew);
#if defined (__ENABLE_CAMERA__) || defined(__ENABLE_CAMCORDER__)
MMI_DECLARE_NEW_FUNC(CAMAPP_New);
#else
#define CAMAPP_New NULL
#define CameraPreNew DUMMY_PRE_NEW
#endif
MMI_DECLARE_NEW_FUNC(CBSAPP_New);
MMI_DECLARE_NEW_FUNC(CCAPP_New);
MMI_DECLARE_NEW_FUNC(CCMTA_New);
#if defined(__APP_VIDEO_TELEPHONY__)
MMI_DECLARE_NEW_FUNC(VideoTelephonyApp_New);
#else
#define VideoTelephonyApp_New NULL
#define VideoTelephonyAppPreNew DUMMY_PRE_NEW
#endif

#if defined(__WAP_MMI_CDWAP__)
MMI_DECLARE_NEW_FUNC(CdWapAppNew);
#else
#define CdWapAppNew NULL
#endif

#if defined(__CALLER_LOCATION__)
MMI_DECLARE_NEW_FUNC(CallerLocationAppNew);
#else
#define CallerLocationAppNew NULL
#endif

#ifdef __NCCQQ_MMI__
MMI_DECLARE_NEW_FUNC(QQAppNew);
MMI_DECLARE_NEW_FUNC(QQSrvNew);
#else
#define QQAppNew NULL
#define QQSrvNew NULL
#endif

#if defined(__MMI_CONNECT_SETTING__)
MMI_DECLARE_NEW_FUNC(ConSettingAppNew);
#else
#define ConSettingAppNew NULL
#endif

#if defined(__APP_MMI_COUNTDOWN_TIMER__)
MMI_DECLARE_NEW_FUNC(CountdownTimerAppNew);
#else
#define CountdownTimerAppNew NULL
#endif
MMI_DECLARE_NEW_FUNC(DialerAppNew);
#if defined(__APP_MMI_GROUP_APP__)
MMI_DECLARE_NEW_FUNC(DialerGroupAppNew);
MMI_DECLARE_NEW_FUNC(FavoritePhb_New);
#elif defined(__UI_STYLE_MMI_IFONE__)
#define DialerGroupAppNew NULL
MMI_DECLARE_NEW_FUNC(FavoritePhb_New);
#else
#define DialerGroupAppNew NULL
#define FavoritePhb_New NULL
#endif
MMI_DECLARE_NEW_FUNC(DialogAppNew);
#if defined(__DICTAPP_MMI__)
MMI_DECLARE_NEW_FUNC(DictNew);
#else
#define DictNew NULL
#endif

#ifdef __SDK_API__
MMI_DECLARE_NEW_FUNC(VendorAppNew);
#else
#define VendorAppNew NULL
#define VendorAppPreNew DUMMY_PRE_NEW
#endif //__SDK_API__

#if defined(__APP_MMI_WORLDCLOCK__)
MMI_DECLARE_NEW_FUNC(WorldClockAppNew);
#else
#define WorldClockAppNew NULL
#define WorldClockPreNew DUMMY_PRE_NEW
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__)
MMI_DECLARE_NEW_FUNC(ShortcutPhbNew);
MMI_DECLARE_NEW_FUNC(IdlePreviewAppNew);
#else
#define IdlePreviewAppNew NULL
#define ShortcutPhbNew NULL
#define ShortcutPhbPreNew DUMMY_PRE_NEW
#endif

#if defined(__3D_UI_IDLE_MULTIPAGE__) || defined(__3D_UI_PHOTOSLIDE_MMI__)
MMI_DECLARE_NEW_FUNC(PicPreviewAppNew);
#else
#define PicPreviewAppNew NULL
#define PicPreviewAppPreNew DUMMY_PRE_NEW
#endif

#if defined(__GAME_ENGINE_EMU_MMI__)
MMI_DECLARE_NEW_FUNC(EmuAppNew);
#else
#define EmuAppNew NULL
#endif

#if defined(__NATIVE_GAME_MMI_PACMAN__)
MMI_DECLARE_NEW_FUNC(PacManNew);
#else
#define PacManNew NULL
#endif
#if defined(__NATIVE_GAME_MMI_FRUIT__)
MMI_DECLARE_NEW_FUNC(FruitGambleGameNew);
#else
#define FruitGambleGameNew NULL
#endif

#if defined(__NATIVE_GAME_MMI_BIG2__)
MMI_DECLARE_NEW_FUNC(Big2New);
#else
#define Big2New NULL
#endif

#if defined(__E_BOOK_MMI__)
MMI_DECLARE_NEW_FUNC(EbookAppNew);
#else
#define EbookAppNew NULL
#define EbookPreNew DUMMY_PRE_NEW
#endif
MMI_DECLARE_NEW_FUNC(EmAppNew);
#if defined(__APP_MMI_EVENTCENTER__)
MMI_DECLARE_NEW_FUNC(EvtCenterAppNew);
#else
#define EvtCenterAppNew NULL
#define EvtCenterAppPreNew DUMMY_PRE_NEW
#endif
MMI_DECLARE_NEW_FUNC(FDNAPP_New);
MMI_DECLARE_NEW_FUNC(FILEMGRAPP_New);
#if defined(__APP_MMI_FM_RADIO__)
MMI_DECLARE_NEW_FUNC(FmRadioAppNew);
#else
#define FmRadioAppNew NULL
#endif
#if defined(__APP_MMI_FM_SCHEDULE__)
MMI_DECLARE_NEW_FUNC(FmSchAppNew);
#else
#define FmSchAppNew NULL
#endif

#if defined(__MMI_SEARCH_APP__)
MMI_DECLARE_NEW_FUNC(SearchAppNew);
#else
#define SearchAppNew NULL
#endif

#if defined(__MMI_BEAUTY_CLK_APP__)
MMI_DECLARE_NEW_FUNC(BeautyClkSettingAppNew);
#else
#define BeautyClkSettingAppNew NULL
#endif

#if defined(__3D_UI_MAINMENU__)
MMI_DECLARE_NEW_FUNC(G3dMainMenuAppNew);
#else
#define G3dMainMenuAppNew NULL
#endif

#if defined(__GOGOBOX_GAME__)
MMI_DECLARE_NEW_FUNC(GogoBoxGameNew);
#else
#define GogoBoxGameNew  NULL
#endif

#if defined(__ANGRYBIRD_GAME__)
MMI_DECLARE_NEW_FUNC(AngryBirdNew);
#else
#define AngryBirdNew  NULL
#endif

#if defined(__FRUITSLICE_GAME__)
MMI_DECLARE_NEW_FUNC(FruitSliceGameNew);
#else
#define FruitSliceGameNew  NULL
#endif

#if defined(__IPLAYCUBE_GAME__)
MMI_DECLARE_NEW_FUNC(IplayCubeGameNew);
#else
#define IplayCubeGameNew  NULL
#endif

#if defined(__RUBIKCUBE_GAME__)
MMI_DECLARE_NEW_FUNC(RubiksCubeNew);
#else
#define RubiksCubeNew  NULL
#endif

#if defined(__LABYRINTH_GAME__)
MMI_DECLARE_NEW_FUNC(LabyrinthGameNew);
#else
#define LabyrinthGameNew  NULL
#endif

#if defined(__CUTROPE_GAME__)
MMI_DECLARE_NEW_FUNC(CutRopeNew);
#else
#define CutRopeNew  NULL
#endif

#if defined(__FISHFURY_GAME__)
MMI_DECLARE_NEW_FUNC(FishFuryGameNew);
#else
#define FishFuryGameNew  NULL
#endif

#if defined(__VAMPIRE_GAME__)
MMI_DECLARE_NEW_FUNC(VampireGameNew);
#else
#define VampireGameNew  NULL
#endif

#if defined(__ZOMBIE_GAME__)
MMI_DECLARE_NEW_FUNC(ZombieGameNew);
#else
#define ZombieGameNew  NULL
#endif

#if defined(__NATIVE_GAME_MMI_GOBANG__)
MMI_DECLARE_NEW_FUNC(GoBangAppNew);
#else
#define GoBangAppNew NULL
#endif
#if defined(__NATIVE_GAME_MMI_HAMSTERFIGHT__)
MMI_DECLARE_NEW_FUNC(HamsterFightAppNew);
#else
#define HamsterFightAppNew NULL
#endif
#ifndef __UI_STYLE_MMI_ANDROID_IDLE__
MMI_DECLARE_NEW_FUNC(IDLEAPP_New);
#else
#define IDLEAPP_New NULL
#endif
#if defined(__JAVA_MMI__)
MMI_DECLARE_NEW_FUNC(JavaAppNew);
#else
#define JavaAppNew NULL
#endif

#if defined(__UI_STYLE_MMI_STYLE_SWITCH__) || !defined(__UI_STYLE_MMI_ANDROID_KEYGUARD__)
MMI_DECLARE_NEW_FUNC(KeyGuardAppNew);
#else
#define KeyGuardAppNew NULL
#define KeyGuardAppPreNew DUMMY_PRE_NEW
#endif

#if defined(__NATIVE_GAME_MMI_LINKUP__)
MMI_DECLARE_NEW_FUNC(LinkUpAppNew);
#else
#define LinkUpAppNew NULL
#endif
#if defined(__APP_MMI_SCREENSAVER__)
MMI_DECLARE_NEW_FUNC(ScreensaverAppNew);
#else
#define ScreensaverAppNew NULL
#endif
#if defined(__MMI_KING_MOVIE__)
MMI_DECLARE_NEW_FUNC(KingMovieAppNew);
#else
#define KingMovieAppNew NULL
#endif
MMI_DECLARE_NEW_FUNC(MAINMENUAPP_New);
#ifdef __MAP_MMI__
MMI_DECLARE_NEW_FUNC(MapNew);
#else
#define MapNew NULL
#endif
MMI_DECLARE_NEW_FUNC(McaAppNew);
#if defined(__MMS_MMI_CDMMS__)
MMI_DECLARE_NEW_FUNC(MMSA_New);
#else
#define MMSA_New NULL
#endif
MMI_DECLARE_NEW_FUNC(MPlayerNew);
MMI_DECLARE_NEW_FUNC(MsaNew);
MMI_DECLARE_NEW_FUNC(MTA_New);
MMI_DECLARE_NEW_FUNC(NetworkAppNew);
#if defined(__APP_MMI_NOTEPAD__)
MMI_DECLARE_NEW_FUNC(NotepadAppNew);
#else
#define NotepadAppNew NULL
#endif
MMI_DECLARE_NEW_FUNC(SwitchModeNew);
MMI_DECLARE_NEW_FUNC(OffAppNew);
MMI_DECLARE_NEW_FUNC(OnAppNew);
MMI_DECLARE_NEW_FUNC(PHBAP_New);
MMI_DECLARE_NEW_FUNC(PicViewerAppNew);
MMI_DECLARE_NEW_FUNC(ProfileAppNew);
#if defined(__ANTI_STEAL_REMOTE_CONTROL_MMI__)
MMI_DECLARE_NEW_FUNC(RemoteControlAppNew);
#else
#define RemoteControlAppNew NULL
#endif
#if defined(__NATIVE_GAME_MMI_PUZZLE__)
MMI_DECLARE_NEW_FUNC(PuzzleAppNew);
#else
#define PuzzleAppNew NULL
#endif
MMI_DECLARE_NEW_FUNC(SeaNew);
MMI_DECLARE_NEW_FUNC(SecNew);
MMI_DECLARE_NEW_FUNC(SendviaAppNew);
MMI_DECLARE_NEW_FUNC(SettingAppNew);
#if defined(__APP_MMI_SHORTCUT__)
MMI_DECLARE_NEW_FUNC(ShortcutsNew);
#else
#define ShortcutsNew NULL
#define ShortcutsPreNew DUMMY_PRE_NEW
#endif
MMI_DECLARE_NEW_FUNC(StkNew);
#if defined(__APP_MMI_SKETCHNOTE__)
MMI_DECLARE_NEW_FUNC(SnoteAppNew);
#else
#define SnoteAppNew NULL
#endif
#if defined(__APP_MMI_SOHU_UPDATER__)
MMI_DECLARE_NEW_FUNC(SoHuUpdaterAppNew);
#else
#define SoHuUpdaterAppNew NULL
#endif
#if defined(__APP_MMI_STOPWATCH__)
MMI_DECLARE_NEW_FUNC(StopwatchAppNew);
#else
#define StopwatchAppNew NULL
#endif
#if defined(__NATIVE_GAME_MMI_SOKOBAN__)
MMI_DECLARE_NEW_FUNC(SokobanAppNew);
#else
#define SokobanAppNew NULL
#endif
#if defined(__NATIVE_GAME_MMI_SUDOKU__)
MMI_DECLARE_NEW_FUNC(SudokuAppNew);
#else
#define SudokuAppNew NULL
#endif
MMI_DECLARE_NEW_FUNC(SVA_New);
#if defined(__PC_SIMULATOR__)
//MMI_DECLARE_NEW_FUNC(TESTAPP_New);
#define TESTAPP_New NULL
#else
#define TESTAPP_New NULL
#endif
#if defined(__APP_MMI_TODOLIST__)
MMI_DECLARE_NEW_FUNC(ToDoListAppNew);
#else
#define ToDoListAppNew NULL
#endif
#if defined(__APP_MMI_UNITCONVERTER__)
MMI_DECLARE_NEW_FUNC(UNITCONVERTER_New);
#else
#define UNITCONVERTER_New NULL
#endif
#if defined(__UNIT_TEST_APP__)
MMI_DECLARE_NEW_FUNC(UNITTESTAPP_New);
#else
#define UNITTESTAPP_New NULL
#endif
MMI_DECLARE_NEW_FUNC(UsbAppNew);
MMI_DECLARE_NEW_FUNC(UssdAppNew);
#ifdef __SDK_API__
MMI_DECLARE_NEW_FUNC(VendorAppNew);
#else
#define VendorAppNew NULL
#endif //__SDK_API__
MMI_DECLARE_NEW_FUNC(VideoPlayerNew);
#if defined(__APP_MMI_VOICE_MEMO__)
MMI_DECLARE_NEW_FUNC(VoiceMemoAppNew);
#else
#define VoiceMemoAppNew NULL
#define VoiceMemoPreNew DUMMY_PRE_NEW
#endif

#if defined(__APP_MMI_NTP__)
MMI_DECLARE_NEW_FUNC(NtpAppNew);
#else
#define NtpAppNew NULL
#endif

#if defined(__MGL_DEMO__)
MMI_DECLARE_NEW_FUNC(MglDemoAppNew);
#else
#define MglDemoAppNew NULL
#endif

#if defined(__G3D_MMI__)  && defined(__APP_MMI_WDG3DEMO__)
MMI_DECLARE_NEW_FUNC(OglDemoAppNew);
MMI_DECLARE_NEW_FUNC(WdgDemoAppNew);
#else
#define OglDemoAppNew NULL
#define WdgDemoAppNew NULL
#endif

MMI_DECLARE_NEW_FUNC(Animation_New);
#if defined(__JAVA_MMI__) || defined(__DALVIK__)
#define _JAVAAPP_New VendorAppNew
#else
#define _JAVAAPP_New NULL
#endif
#if !defined(__JAVA_MMI__)
#define JavaamsPreNew DUMMY_PRE_NEW
#endif
#if !defined(__GAME_ENGINE_EMU_MMI__)
#define EmuAppPreNew DUMMY_PRE_NEW
#endif
#if !defined(__WAP_MMI_CDWAP__)
#define CdWapAppPreNew DUMMY_PRE_NEW
#endif
#if !defined(__MMI_CONNECT_SETTING__)
#define ConSettingAppPreNew DUMMY_PRE_NEW
#endif
#if !defined(__APP_MMI_SOHU_UPDATER__)
#define SoHuUpdaterAppPreNew DUMMY_PRE_NEW
#endif
#if !defined(__APP_MMI_FM_SCHEDULE__)
#define FmSchPreNew DUMMY_PRE_NEW
#define FmRadioPreNew DUMMY_PRE_NEW
#endif
#if defined(__WLAN_MMI__)
MMI_DECLARE_NEW_FUNC(WiFiAppNew);
#else
#define WiFiAppNew NULL
#define WiFiPreNew DUMMY_PRE_NEW
#endif
#if !defined(__TOUCH_SCREEN_MMI__) || !defined(__APP_MMI_BJX__)
#define BjxPreNew DUMMY_PRE_NEW
#endif
#if !defined(__BLUETOOTH_MMI__)
#define BtPreNew DUMMY_PRE_NEW
#define BtNotifyPreNew DUMMY_PRE_NEW
#endif
#if !defined(__MMS_MMI_CDMMS__)
#define MmsaPreNew DUMMY_PRE_NEW
#endif
#ifdef __EMAIL_MMI__
MMI_DECLARE_NEW_FUNC(EmailAppNew);
MMI_DECLARE_NEW_FUNC(EmailSrvNew);
#else
#define EmailAppNew NULL
#define EmailSrvNew NULL
#define EmailAppPreNew DUMMY_PRE_NEW
#endif
#if !defined(__JAVA_MMI__)
#define JavaFactoryAppNew NULL
#define JavaFactoryAppPreNew DUMMY_PRE_NEW
#else
MMI_DECLARE_NEW_FUNC(JavaFactoryAppNew);
#endif

#if defined(__APP_MMI_CHECKDISK__)
MMI_DECLARE_NEW_FUNC(CheckDiskAppNew);
#else
#define CheckDiskAppNew NULL
#define CheckDiskAppPreNew DUMMY_PRE_NEW
#endif

#ifdef __RFID_MMI__
MMI_DECLARE_NEW_FUNC(RfidDemoAppNew);

#else
#define RfidDemoAppNew NULL
#endif


#if defined(__APP_MMI_AZAN__)
MMI_DECLARE_NEW_FUNC(AzanAppNew);
#else
#define AzanAppNew  NULL
#endif

#ifdef __NETWORK_COUNTER_MMI__
MMI_DECLARE_NEW_FUNC(NetworkCounterAppNew);
#else
#define NetworkCounterAppNew NULL
#define NetworkCounterAppPreNew DUMMY_PRE_NEW
#endif
#ifdef __APP_MMI_TUDOU__
MMI_DECLARE_NEW_FUNC(TuDouAppNew);
#else
#define TuDouAppNew NULL
#endif
#ifndef __FDN_MMI__
#define FDNAPP_New NULL
#define FdnPreNew DUMMY_PRE_NEW
#endif
/**-----------------------------------------------------*
*	End of Style Area	(2/5)							*
*------------------------------------------------------*/

//###TOOL_NEWFUN_DECLAR_STAR###"
//###TOOL_NEWFUN_DECLAR_END###"
#endif // __MMI_CLSTBL_C__ for the declaration of new functions
//
// id and new function of widget classes
//
/**-----------------------------------------------------*
*	Platform Style Area	(3/5)							*
*------------------------------------------------------*/
MMI_DEFINE_CLS_CATEGORY(MAE_WidgetClass)
{
	//
	// predefine basic widgets/views
	//
	// ** Note: do NOT modify this section
	// view objects
	MMI_DEFINE_CLSID_BASE(CLSID_VIEWMGR,MAE_WIDGET_CLASS_BASE, ViewMgr_New),
		MMI_DEFINE_CLSID(CLSID_VIEW,			View_New),
		MMI_DEFINE_CLSID(CLSID_DISPCANVAS,		DispCanvas_New),
		// basic container objects
		MMI_DEFINE_CLSID(CLSID_ABSCONTAINER,	AbsContainer_New),
		MMI_DEFINE_CLSID(CLSID_ANIMATIONCONTAINER,	AnimationContainer_New),
		MMI_DEFINE_CLSID(CLSID_MULTIPAGECONTAINER,	MultipageContainer_New),
		MMI_DEFINE_CLSID(CLSID_PROPCONTAINER,	PropContainer_New),
		MMI_DEFINE_CLSID(CLSID_ROOTCONTAINER,	RootContainer_New),
		MMI_DEFINE_CLSID(CLSID_MFLCONTAINER,	MFLContainer_New),
		// basic decorator objects
		MMI_DEFINE_CLSID(CLSID_IMAGEWIDGET,				ImageWidget_New),
		MMI_DEFINE_CLSID(CLSID_OVERLAYIMAGEWIDGET,		OverlayImageWidget_New),
		MMI_DEFINE_CLSID(CLSID_ANIMIMAGEWIDGET,			AnimImageWidget_New),
		MMI_DEFINE_CLSID(CLSID_IMEASSISTWIDGET,			IMEAssistWidget_New),
		MMI_DEFINE_CLSID(CLSID_SCROLLBARWIDGET,			ScrollbarWidget_New),
		MMI_DEFINE_CLSID(CLSID_SCROLLINDICATORWIDGET,	ScrollIndicatorWidget_New),
		MMI_DEFINE_CLSID(CLSID_VIEWPORTWIDGET,			ViewportWidget_New),
		MMI_DEFINE_CLSID(CLSID_TITLEWIDGET,				TitleWidget_New),
		MMI_DEFINE_CLSID(CLSID_GRIDWIDGET,				ListWidget_New),
		MMI_DEFINE_CLSID(CLSID_MAINMENUANIMATED_WIDGET,	MainMenuAnimatedWdg_New),
		MMI_DEFINE_CLSID(CLSID_FLIPDCLOCK_WIDGET,       FlipDClockWidget_New),
		MMI_DEFINE_CLSID(CLSID_DRAGWIDGET, 		        DragWidget_New),
		MMI_DEFINE_CLSID(CLSID_CANVASWIDGET,	CanvasWidget_New),
		MMI_DEFINE_CLSID(CLSID_IFONEWIDGET, 		    IFoneWidget_New),
		// basic widget objects
		MMI_DEFINE_CLSID(CLSID_TEXTWIDGET,				TextWidget_New),
		MMI_DEFINE_CLSID(CLSID_STATUSBARWIDGET,			StatusBarWidget_New),
		MMI_DEFINE_CLSID(CLSID_SUBSTATUSBARWIDGET,		SubStatusBarWidget_New),
		MMI_DEFINE_CLSID(CLSID_SOFTKEYWIDGET,			SoftkeyWidget_New),
		MMI_DEFINE_CLSID(CLSID_FADEOUTWIDGET,			FadeoutWidget_New),
		MMI_DEFINE_CLSID(CLSID_BITMAPWIDGET,			BitmapWidget_New),
		MMI_DEFINE_CLSID(CLSID_SWITCHICONWIDGET,		SwitchIconWidget_New),
		MMI_DEFINE_CLSID(CLSID_PROGRESSWIDGET,			ProgressWidget_New),
		MMI_DEFINE_CLSID(CLSID_BUTTONWIDGET,			ButtonWidget_New),
		MMI_DEFINE_CLSID(CLSID_OSDWIDGET,				OsdWidget_New),
		MMI_DEFINE_CLSID(CLSID_GLMENUWIDGET,            GlMenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_GLROTATIONMENUWIDGET,	GlRotationMenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_GLALBUMSLIDE_WIDGET,	    GlAlbumSlideWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLCIRCLEWIDGET,			GlCircleListWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLFLIP_EFFECT_WIDGET,	FlipEffectWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLCLOTH_EFFECT_WIDGET,	ClothEffectWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLMAGNIFY_WIDGET,	    MagnifyWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLMULTIIDLEPAGE_WIDGET,	GlMultiIdlePageWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLMLPG_WIDGET,	        GlMlpgWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLBOXLIST_WIDGET,        GlBoxListWdg_New),
		MMI_DEFINE_CLSID(CLSID_PROPCIRCLECONTAINER,	    PropCircleContainer_New),
		MMI_DEFINE_CLSID(CLSID_GLTRANSFORMWIDGET,		GLTransformWidget_New),
		MMI_DEFINE_CLSID(CLSID_SPECTRUM_WIDGET,         SpectrumWidget_New),
		MMI_DEFINE_CLSID(CLSID_GROUPWIDGET, 			GroupWidget_New),
		MMI_DEFINE_CLSID(CLSID_SCREENSAVEREFFECT_WIDGET, ScreensaverEffect_New),
		//
		// ext widgets
		//
		// ** Add widgets in this section
		MMI_DEFINE_CLSID(CLSID_WIDGET_DEFAULT,	NULL),
		MMI_DEFINE_CLSID(CLSID_WIDGET_DEFAULT_INTERNAL,	NULL),
		MMI_DEFINE_CLSID(CLSID_WIDGET_COMMON,	NULL),
		MMI_DEFINE_CLSID(CLSID_COMMON,	NULL),
		MMI_DEFINE_CLSID(CLSID_RSLAYOUT,	NULL),
		// container objects
		MMI_DEFINE_CLSID(CLSID_SHEETCONTAINER,	SheetContainer_New),
		MMI_DEFINE_CLSID(CLSID_VIEWERCONTAINER,	ViewerContainer_New),
		// decorator objects
		MMI_DEFINE_CLSID(CLSID_SWITCHICONITEMWIDGET,	SwitchIconItemWidget_New),
		MMI_DEFINE_CLSID(CLSID_TAB_WIDGET,				TabWidget_New),
		MMI_DEFINE_CLSID(CLSID_HORZ_LISTWIDGET,			ListWidget_New),
		MMI_DEFINE_CLSID(CLSID_VERT_LISTWIDGET,			ListWidget_New),
		MMI_DEFINE_CLSID(CLSID_PICK_WIDGET,				PickWidget_New),
		MMI_DEFINE_CLSID(CLSID_RINGLIST_WIDGET,			RingListWidget_New),
		MMI_DEFINE_CLSID(CLSID_TRANSITION_WIDGET,		TranWidget_New),
		MMI_DEFINE_CLSID(CLSID_WALLPAPER_WIDGET,        WallpaperWidget_New),
		MMI_DEFINE_CLSID(CLSID_SCREENEFFECT_WIDGET,     ScreenEffectWidget_New),
		// general widget objects
		MMI_DEFINE_CLSID(CLSID_TEXTLABELWIDGET,			TextWidget_New),
		MMI_DEFINE_CLSID(CLSID_TEXTHIGHLIGHTWIDGET,     TextWidget_New),
		MMI_DEFINE_CLSID(CLSID_TEXTBUBBLEWIDGET,        TextBubbleWidget_New),
		MMI_DEFINE_CLSID(CLSID_INDICATORWIDGET,			IndicatorWidget_New),
		MMI_DEFINE_CLSID(CLSID_TIMERFORMAT_WIDGET,		TimerFormatWidget_New),
		MMI_DEFINE_CLSID(CLSID_VOLUMEWIDGET,			VolumeWidget_New),
		MMI_DEFINE_CLSID(CLSID_VOLUMEDLGWIDGET,			VolumeWidget_New),
		MMI_DEFINE_CLSID(CLSID_SHORTCUTBARWIDGET,	    ShortcutBarWidget_New),
		MMI_DEFINE_CLSID(CLSID_SLIDESWITCHWIDGET,		SlideSwitchWidget_New),
		MMI_DEFINE_CLSID(CLSID_FLIPTEXTWIDGET,		    FlipTextWidget_New),
		MMI_DEFINE_CLSID(CLSID_GLOWTEXTWIDGET,		    GlowTextWidget_New),
		MMI_DEFINE_CLSID(CLSID_GLCOVERFLOWWIDGET,	    GlCoverFlowWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLPHOTOSLIDEWIDGET,	    GlPhotoSlideWdg_New),
		MMI_DEFINE_CLSID(CLSID_EVENTWIDGET,				EventWidget_New),
		MMI_DEFINE_CLSID(CLSID_DATEICONWIDGET,			DateIconWidget_New),
		MMI_DEFINE_CLSID(CLSID_TIMEICONWIDGET,			DateIconWidget_New),
		MMI_DEFINE_CLSID(CLSID_CLOCKICONWIDGET,			DateIconWidget_New),
		MMI_DEFINE_CLSID(CLSID_PULLDOWNWIDGET,			PullDownWidget_New),
		MMI_DEFINE_CLSID(CLSID_BASICBITMAPWIDGET,       BasicBitmapWidget_New),
		MMI_DEFINE_CLSID(CLSID_DUMMYWIDGET,	DummyWidget_New),
		MMI_DEFINE_CLSID(CLSID_FCTIME_WIDGET,			FCTimeWidget_New),
		MMI_DEFINE_CLSID(CLSID_FCDATE_WIDGET,			FCDateWidget_New),
		MMI_DEFINE_CLSID(CLSID_COUNTDOWNTIME_WIDGET,	FCTimeWidget_New),
		// widget objects:Input related
		MMI_DEFINE_CLSID(CLSID_CARETWIDGET,				CaretWidget_New),
		MMI_DEFINE_CLSID(CLSID_IPWIDGET,				FormatInputWidget_New),
		MMI_DEFINE_CLSID(CLSID_TIMEWIDGET,				FormatInputWidget_New),
		MMI_DEFINE_CLSID(CLSID_DATEWIDGET,				FormatInputWidget_New),
		MMI_DEFINE_CLSID(CLSID_INPUTWIDGET,				InputWidget_New),
		MMI_DEFINE_CLSID(CLSID_INPUTCONTROLLER,			InputController_New),
		MMI_DEFINE_CLSID(CLSID_INPUTCANDIDATEWIDGET,    InputCandidateWidget_New),
		MMI_DEFINE_CLSID(CLSID_SYMBOLTABLEWIDGET,       InputGridWidget_New),
		MMI_DEFINE_CLSID(CLSID_INPUTLANGWIDGET,         InputGridWidget_New),
		MMI_DEFINE_CLSID(CLSID_SMARTINPUTONOFFWIDGET,   InputGridWidget_New),
#if defined __HANDWRITING_MMI__
		MMI_DEFINE_CLSID(CLSID_HANDWRITINGONOFFWIDGET,  InputGridWidget_New),
#endif
		MMI_DEFINE_CLSID(CLSID_INPUTCOPYORCOPYALL,      InputGridWidget_New),
		MMI_DEFINE_CLSID(CLSID_INPUTMETHODWIDGET,       InputGridWidget_New),
		MMI_DEFINE_CLSID(CLSID_MYWORDWIDGET,			InputHelperWidget_New),
		MMI_DEFINE_CLSID(CLSID_INPUTHELPERWIDGET,	    _InputHelperWidget_New),
		MMI_DEFINE_CLSID(CLSID_HANDWRITINGWIDGET,		HandWritingWidget_New),
		MMI_DEFINE_CLSID(CLSID_SOFTKEYBOARDWIDGET,		SoftKeyboardWidget_New),
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
		MMI_DEFINE_CLSID(CLSID_SOFTKEYBOARD_HIGHLIGHTWIDGET,   Softkeyboard_HighlightWidget_New),
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__
		// widget objects:menu widget related
		MMI_DEFINE_CLSID(CLSID_MENUWIDGET,				MenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_HORZ_MENUWIDGET,			MenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_NUMERIC_MENUWIDGET,		MenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_IMGGRID_MENUWIDGET,		MenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_TXTGRID_MENUWIDGET,		MenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_GRID_MENUWIDGET,		    MenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_OPTIONMENUWIDGET,		OptionMenuWidget_New),
		MMI_DEFINE_CLSID(CLSID_POPUPSELECTWIDGET,		PopupSelectWidget_New),
		MMI_DEFINE_CLSID(CLSID_NUMERIC_POPUPSELECTWIDGET, PopupSelectWidget_New),
		// widget objects:image-text-image related
		MMI_DEFINE_CLSID(CLSID_IMAGETEXTIMAGEWIDGET,	ImageTextImageWidget_New),
		MMI_DEFINE_CLSID(CLSID_IMAGETEXTWIDGET,         ImageTextImageWidget_New),
		MMI_DEFINE_CLSID(CLSID_TEXTIMAGEWIDGET,         ImageTextImageWidget_New),
		// widget objects:double item related
		MMI_DEFINE_CLSID(CLSID_DOUBLE_ITI_WIDGET,		NULL),
		MMI_DEFINE_CLSID(CLSID_DOUBLE_TEXT_WIDGET,		DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_TEXT_INPUT_WIDGET,		DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_TEXT_DATE_WIDGET,		DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_TEXT_TIME_WIDGET,		DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_TEXT_IP_WIDGET,			DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_IT_STEXT_WIDGET,			DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_IT_SIT_WIDGET,			DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_IT_STI_WIDGET,			DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_IT_SINPUT_WIDGET,		DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_TEXT_LINE2INFO_WIDGET,		DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_IT_ABS_WIDGET,			DoubleItem_New),
		// widget objects:image double item related
		MMI_DEFINE_CLSID(CLSID_IMAGE_DOUBLE_ITI_WIDGET,		NULL),
		MMI_DEFINE_CLSID(CLSID_IMAGE_DOUBLE_TEXT_WIDGET,	Image_DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_IMAGE_TITEXT_WIDGET,			Image_DoubleItem_New),
		MMI_DEFINE_CLSID(CLSID_IMAGE_TITI_WIDGET,			Image_DoubleItem_New),
		// widget objects:text pick related
		MMI_DEFINE_CLSID(CLSID_TEXTPICK_TEXTWIDGET,				CommonPickItem_New),
		MMI_DEFINE_CLSID(CLSID_TEXTPICK_IMAGETEXTWIDGET,		CommonPickItem_New),
		MMI_DEFINE_CLSID(CLSID_IMAGETEXTPICK_IMAGETEXTWIDGET,	CommonPickItem_New),
		MMI_DEFINE_CLSID(CLSID_LINE2INFOPICK_TEXTWIDGET,        CommonPickItem_New),
		MMI_DEFINE_CLSID(CLSID_FORMAT_INPUTWIDGET,			NULL),
		MMI_DEFINE_CLSID(CLSID_GRIDBASE_WIDGET,			    NULL),
		// widget objects:desktop widget related
		MMI_DEFINE_CLSID(CLSID_DESKTOPWIDGET_START,	NULL),
		MMI_DEFINE_CLSID(CLSID_ALIVEWIDGET,	AliveWidget_New),
		MMI_DEFINE_CLSID(CLSID_DESKTOPWIDGET, DesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_SHORTCUTDESKTOP_WIDGET,	ShortcutDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_PROFILE_WIDGET,	ProfileWidget_New),
		MMI_DEFINE_CLSID(CLSID_MPDESKTOPWIDGET,	MpDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_FMDESKTOPWIDGET,	FmDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_SEARCHDESKTOPWIDGET,		SearchDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_CALENDARDESKTOPWIDGET,	CalendarDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_OPDESKTOPWIDGET,	OpDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_NOTEDESKTOPWIDGET,	NoteDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_NOTEPADDESKTOPWIDGET,	NotepadDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_DCLOCKDESKTOPWIDGET,	DclockDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_ACLOCKDESKTOPWIDGET,	AclockDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_PHONEBOOKDESKTOP_WIDGET,	PhonebookDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_PHOTODESKTOP_WIDGET,	PhotoDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_MESSAGEDESKTOP_WIDGET,	MessageDesktopWidget_New),
		MMI_DEFINE_CLSID(CLSID_STATUSPAGEWIDGET,	StatusPageWidget_New),
		MMI_DEFINE_CLSID(CLSID_ROTATECUBE_WIDGET,	RotateCubeWidget_New),
		MMI_DEFINE_CLSID(CLSID_DESKTOPWIDGET_END,	NULL),
		MMI_DEFINE_CLSID(CLSID_WNDMGR,		WndMgr_New),
		MMI_DEFINE_CLSID(CLSID_ANIMATION,   Animation_New),
		// widget objects:3D widget related
		MMI_DEFINE_CLSID(CLSID_3D_LOADER_WIDGET,       Gl3dLoaderWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLTIME_IND_WIDGET,       GlTimeIndWdg_New),
		MMI_DEFINE_CLSID(CLSID_GLFOTOLIST_PAGE_WIDGET, GlFotoListPageWdg_New),
		MMI_DEFINE_CLSID(CLSID_IMAGE_TEXT_ITIT_WIDGET, ImageDoubleItemMultiFieldWdg_New),
		MMI_DEFINE_CLSID(CLSID_IMAGE_TEXT_CITT_WIDGET, ImageDoubleItemMultiFieldWdg_New),
		MMI_DEFINE_CLSID(CLSID_MULTITOUCHTESTWIDGET, MultiTouchTestWidget_New),
		// widget objects: extra keyguard objects
#ifdef __MMI_BALLSLIDE_WDG_SUPPORT__
		MMI_DEFINE_CLSID(CLSID_BALLSLIDEWIDGET, BallSlideWidget_New),
#endif
        MMI_DEFINE_CLSID(CLSID_SNAPSHOTWIDGET,          SnapshotWidget_New),
		MMI_DEFINE_END_OF_CLSID(CLSID_END_OF_WIDGET)
};
/**-----------------------------------------------------*
*	End of Style Area	(3/5)							*
*------------------------------------------------------*/
//
// id and new function of mmi model classes
//
MMI_DEFINE_CLS_CATEGORY(MMI_ModelClass)
{
	//
	// predefine mmi models
	//
	// ** Note: do NOT modify this section
	MMI_DEFINE_CLSID_BASE(CLSID_TEXTMODEL, MMI_MODEL_CLASS_BASE, TextModel_New),
		MMI_DEFINE_CLSID(CLSID_MENUMODEL,		MenuModel_New),
		MMI_DEFINE_CLSID(CLSID_SOFTKEYMODEL,	SoftkeyModel_New),
		MMI_DEFINE_CLSID(CLSID_IMEASSISTMODEL,	IMEAssistModel_New),
		// ** Add new models after this line
#ifdef __MMI_SCRIPT_EASY_EDITOR__
		MMI_DEFINE_CLSID(CLSID_KMX_TEXTMODEL,		kmx_TextModel_New),
#endif
		MMI_DEFINE_END_OF_CLSID(CLSID_END_OF_MMI_MODEL)
};

//
// id and new function for MMI basic classes
//
MMI_DEFINE_CLS_CATEGORY(MMI_BasicClass)
{
	MMI_DEFINE_CLSID_BASE(CLSID_MMICOM, MMI_BASIC_CLASS_BASE, 0), // dummy class for classifying system events
		MMI_DEFINE_CLSID(CLSID_MMIRIL, 0), // dummy class for classifying protocol events
		MMI_DEFINE_CLSID(CLSID_MMIDEV, 0), // dummy class for classifying device layer events
		MMI_DEFINE_CLSID(CLSID_MMISDK, 0), // dummy class for SDK and 3rd party application events
		MMI_DEFINE_END_OF_CLSID(CLSID_EO_MMI_BASIC)
};

//
// id and new function of service classes
//
MMI_DEFINE_CLS_CATEGORY(MAE_ServiceClass)
{
	MMI_DEFINE_CLSID_BASE(CLSID_ACCESSORYSRV, MAE_SERVICE_CLASS_BASE, ACCESSORYSRV_New),
		MMI_DEFINE_CLSID(CLSID_ALARMSRV, ALARMSRV_New),
		MMI_DEFINE_CLSID(CLSID_ALIVEWDGSRV, ALIVEWDGSRV_New),
		MMI_DEFINE_CLSID(CLSID_BTOBEXSRV, BTOBEXSRV_New),
		MMI_DEFINE_CLSID(CLSID_BTSRV, BTSRV_New),
		MMI_DEFINE_CLSID(CLSID_CALLLOGSRV, CALLLOGSRV_New),
		MMI_DEFINE_CLSID(CLSID_CBS, CBS_New),
		MMI_DEFINE_CLSID(CLSID_CCSRV, CCSRV_New),
		MMI_DEFINE_CLSID(CLSID_CLIPBOARDSRV, CLIPBOARDSRV_New),
		MMI_DEFINE_CLSID(CLSID_CORESRV, CORESRV_New),
		MMI_DEFINE_CLSID(CLSID_COUNTDOWNTIMERSRV, COUNTDOWNTIMERSRV_New),
		MMI_DEFINE_CLSID(CLSID_CPHSSRV, CPHSSRV_New),
		MMI_DEFINE_CLSID(CLSID_DIALOGSRV, DIALOGSRV_New),
		MMI_DEFINE_CLSID(CLSID_DRMAGENTSRV, DRMAGENTSRV_New),
		MMI_DEFINE_CLSID(CLSID_EVTCENTERSRV, EVTCENTERSRV_New),
		MMI_DEFINE_CLSID(CLSID_FDNSRV, FDNSRV_New),
		MMI_DEFINE_CLSID(CLSID_FMRADIOSRV, FmradioSrvNew),
		MMI_DEFINE_CLSID(CLSID_HASHMAPSRV, HASHMAPSRV_New),
		MMI_DEFINE_CLSID(CLSID_JAVASRV, JAVASRV_New),
		MMI_DEFINE_CLSID(CLSID_MCI, MCI_New),
		MMI_DEFINE_CLSID(CLSID_MMS, MMS_New),
		MMI_DEFINE_CLSID(CLSID_MMSRV, MMSRV_New),
		MMI_DEFINE_CLSID(CLSID_MMSTRANSSRV, MMSTRANSSRV_New),
		MMI_DEFINE_CLSID(CLSID_MOI, MOI_New),
		MMI_DEFINE_CLSID(CLSID_AUDIOPLAYERSRV, AudioPlayerSrvNew),
		MMI_DEFINE_CLSID(CLSID_OBJPROCESSINGSRV, OBJPROCESSINGSRV_New),
		MMI_DEFINE_CLSID(CLSID_PEDOMETERSRV, PEDOMETERSRV_New),
		MMI_DEFINE_CLSID(CLSID_PHBSRV, PHBSRV_New),
		MMI_DEFINE_CLSID(CLSID_PLAYLISTSRV, PLAYLISTSRV_New),
		MMI_DEFINE_CLSID(CLSID_PREVIEWLINE2SRV, PREVIEWLINE2SRV_New),
		MMI_DEFINE_CLSID(CLSID_PRIVATEPROTECTSRV, PrivateprotectSrvNew),
		MMI_DEFINE_CLSID(CLSID_PROFILESRV, PROFILESRV_New),
		MMI_DEFINE_CLSID(CLSID_SHORTCUTSSRV, SHORTCUTSSRV_New),
		MMI_DEFINE_CLSID(CLSID_SIMSRV, SIMSRV_New),
		MMI_DEFINE_CLSID(CLSID_SMI, SMI_New),
		MMI_DEFINE_CLSID(CLSID_SMS, SMS_New),
		MMI_DEFINE_CLSID(CLSID_SSSRV, SSSRV_New),
		MMI_DEFINE_CLSID(CLSID_STKSRV, STKSRV_New),
		MMI_DEFINE_CLSID(CLSID_TOUCHSHORTCUTSRV, TOUCHSHORTCUTSRV_New),
		MMI_DEFINE_CLSID(CLSID_TXI, TXI_New),
		MMI_DEFINE_CLSID(CLSID_USBSRV, UsbSrvNew),
		MMI_DEFINE_CLSID(CLSID_VCALSTORESRV, VCALSTORESRV_New),
		MMI_DEFINE_CLSID(CLSID_VENDORSRV, VENDORSRV_New),
		MMI_DEFINE_CLSID(CLSID_WLANSRV, WLANSRV_New),
		MMI_DEFINE_CLSID(CLSID_CFGSRV, 			CFGSrv_New),
		MMI_DEFINE_CLSID(CLSID_STATUSBARSRV,	STATUSBARSRV_New),
#ifdef __CALENDAR_SUPPORT_VCS_MMI__
		MMI_DEFINE_CLSID(CLSID_VCALENDAR,		VCALENDAR_New),
		MMI_DEFINE_CLSID(CLSID_VCALPARSER,		VCALPARSER_New),
		MMI_DEFINE_CLSID(CLSID_VEVENT,			VEVENT_New),
#ifdef __APP_MMI_TODOLIST_VTODO__
		MMI_DEFINE_CLSID(CLSID_VTODO,			VTODO_New),
#endif
		MMI_DEFINE_CLSID(CLSID_VPARAM,			VPARAM_New),
		MMI_DEFINE_CLSID(CLSID_VPROPERTY,		VPROPERTY_New),
#endif // End of __CALENDAR_SUPPORT_VCS_MMI__
		MMI_DEFINE_CLSID(CLSID_ATSYNCSRV,       ATSYNCSRV_New),
		MMI_DEFINE_CLSID(CLSID_EMAILSRV, EmailSrvNew),
#ifdef __NCCQQ_MMI__
		MMI_DEFINE_CLSID(CLSID_QQSRV, QQSrvNew),
#endif
		// model for specific services
		MMI_DEFINE_CLSID(CLSID_STATUSMODEL,		STATUSMODEL_New),
		MMI_DEFINE_CLSID(CLSID_VIDEOPLAYERSRV,	VideoPlayerSrvNew),
		MMI_DEFINE_CLSID(CLSID_CAMERASRV,		CameraSrvNew),
		MMI_DEFINE_CLSID(CLSID_TVSRV,			TvSrvNew),
		MMI_DEFINE_CLSID(CLSID_AUDIORECSRV,			AudioRecSrvNew),
		MMI_DEFINE_CLSID(CLSID_AUDIOSRV,		AudioSrvNew),
		MMI_DEFINE_CLSID(CLSID_AUDIOENVSRV,		AudioEnvSrvNew),
		MMI_DEFINE_CLSID(CLSID_CODECSRV, CodecSrvNew),
		MMI_DEFINE_CLSID(CLSID_VOICECALLSRV, VoiceCallSrvNew),
		MMI_DEFINE_CLSID(CLSID_CLSRV, CLSRV_New),
		MMI_DEFINE_CLSID(CLSID_SOCKETSRV,		 SocketSrvNew),
		MMI_DEFINE_CLSID(CLSID_TTSSRV,		 TTSSRV_New),
		MMI_DEFINE_CLSID(CLSID_GPSSRV, GPSSrvNew),

		MMI_DEFINE_CLSID(CLSID_VTCCSRV,		 VtCcSrvNew),
		MMI_DEFINE_CLSID(CLSID_VTMSRV,		 VtmSrvNew),
		MMI_DEFINE_CLSID(CLSID_UNITTESTSRV,  UnitTestSrvNew),
		MMI_DEFINE_CLSID(CLSID_SCHEDULERSRV,		 SCHSRV_New),
		MMI_DEFINE_END_OF_CLSID(CLSID_END_OF_SERVICE)
};
//
// The Pre new function of applet classes for applet communication mechanism.
// The default Pre new function is DUMMY_PRE_NEW
//
#define DUMMY_PRE_NEW MaeDummyExtPreNewFunc

/**-----------------------------------------------------*
*	Platform Style Area	(4/5)							*
*------------------------------------------------------*/
#define MMI_DEFINE_APPLET_DEF_FUNC_TBL	\
	DEFINE_APPLET_DEF_FUNC_TBL(APPLET_PRE_NEW_TBL) \
	MMI_DEFINE_APPFUNC_BASE(CLSID_ALARMAPP, MAE_APPLET_CLASS_BASE, AlarmPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_ANTISTEALAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_ATVAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_AUTOTESTAPP, AutotestAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_ANDROID_IDLEAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_ANDROID_MAINMENUAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_BJXAPP, BjxPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_BMI, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_LICENSEMGRAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_PRIVATEPROTECT, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_PRIVATEPROTECTPW, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_BTAPP, BtPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_BTNOTIFYAPP, BtNotifyPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CALCULATORAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_CALCULATORPLUSAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_CALENDARAPP, CalendarPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CALIBRATIONAPP, CalibrationAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CALLLOGAPP, CallLogAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CALLSETTINGAPP, CallSettingAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CAMAPP, CameraPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CBSAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_CCAPP, CcAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CALLERLOCATIONAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_VIDEOTELEPHONYAPP, VideoTelephonyAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CCMTA, CcMtaPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CDWAPAPP, CdWapAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_CONSETTINGAPP, ConSettingAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_COUNTDOWNTIMER, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_DIALERAPP, DialerAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_DIALERGROUPAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_DIALOGAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_DIALOGAPP_TOP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_DIALOGAPP_ALARM, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_DICTAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_EMUAPP, EmuAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_PACMAN, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_FRUITGAMBLEGAME, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_FAVORITEPHB, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_BIG2, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_E_BOOK, EbookPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_EMAPP, EmPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_EVTCENTERAPP, EvtCenterAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_FDNAPP, FdnPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_FILEMGRAPP, FileMgrAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_FMRADIOAPP, FmRadioPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_FMSCHAPP, FmSchPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_FAVORITEPHB, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_GOBANGAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_HAMSTERFIGHTAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_IDLEAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_JAVAAMSAPP, JavaamsPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_JAVAFACTORYAPP, JavaFactoryAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_KEYGUARDAPP, KeyGuardAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_ANDROID_KEYGUARDAPP, AndroidKeyGuardAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_KINGMOVIEAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_3DKINGMOVIEAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_LINKUPAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_MAINMENUAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_MAPAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_MCA, McaAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_MMSA, MmsaPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_MPLAYERAPP, MPlayerPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_MSA, MsaPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_MTA, MtaPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_NETWORKAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_ONAPP, OnPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_OFFAPP, OffAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_SWITCHMODE, SwitchModePreNew) \
	MMI_DEFINE_APPFUNC(CLSID_TODOLISTAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_PHBAP, PHBAPPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_PHBAP2, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_PUZZLEAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_PICPREVIEWAPP, PicPreviewAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_PICVIEWERAPP, PicViewerPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_PROFILEAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_REMOTECONTROLAPP, DUMMY_PRE_NEW)\
	MMI_DEFINE_APPFUNC(CLSID_SEA, SeaPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_SECAPP, SecPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_SENDVIAAPP, SendviaPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_SETTINGAPP, SettingPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_SHORTCUTPHB, ShortcutPhbPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_SHORTCUTSAPP, ShortcutsPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_SNOTEAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_SOHUUPDATERAPP, SoHuUpdaterAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_STKAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_STOPWATCHAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_SOKOBANAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_SUDOKUAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_SVA, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_TESTAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_UNITCONVERTER, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_UNITTEST, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_USBAPP, UsbAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_USSDAPP, UssdAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_VENDORAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_VENDORLISTAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_VIDEOPLAYERAPP, VideoPlayerPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_VOICEMAILAPP, VoiceMailPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_VOICEMEMOAPP, VoiceMemoPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_WORLDCLOCKAPP, WorldClockPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_IDLEAPP_DIALINGVIEW, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_STKAPP2, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_WAPAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_JAVAAPP, VendorAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_WIFIAPP, WiFiPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_EMAILAPP, EmailAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_QQAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_SCREENSAVERAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_CHECKDISKAPP, CheckDiskAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_QQAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_RFIDDEMOAPP, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_AZANAPP,DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_FRUITSLICEGAME, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_DIALOGAPP_BTSTATUS, DUMMY_PRE_NEW) \
	MMI_DEFINE_APPFUNC(CLSID_NETWORKCOUNTERAPP, NetworkCounterAppPreNew) \
	MMI_DEFINE_APPFUNC(CLSID_TUDOUAPP, DUMMY_PRE_NEW) \
	DEFINE_END_OF_APPFUNC(CLSID_END_OF_APPLET)

/**-----------------------------------------------------*
*	End of Style Area	(4/5)							*
*------------------------------------------------------*/


#ifndef __MMI_CLSTBL_C__
#define MMI_DEFINE_APPFUNC(CLS_ID, PRE_NEW)
#define MMI_DEFINE_APPFUNC_BASE(CLS_ID, CLS_ID_BASE, PRE_NEW)
#define DEFINE_END_OF_APPFUNC(CLS_ID)
#define DEFINE_APPLET_DEF_FUNC_TBL(TBL_NAME) \
	extern const AppletDefFunc_t TBL_NAME[];
extern void MaeDummyExtPreNewFunc(void);
MMI_DEFINE_APPLET_DEF_FUNC_TBL
#endif
//
// id and new function of applet classes
//
/**-----------------------------------------------------*
*	Platform Style Area	(5/5)							*
*------------------------------------------------------*/
MMI_DEFINE_CLS_CATEGORY(MAE_AppletClass)
{
	MMI_DEFINE_CLSID_BASE(CLSID_ALARMAPP, MAE_APPLET_CLASS_BASE, AlarmAppNew),
		MMI_DEFINE_CLSID(CLSID_ANTISTEALAPP, AntiStealAppNew),
		MMI_DEFINE_CLSID(CLSID_ATVAPP, AtvAppNew),
		MMI_DEFINE_CLSID(CLSID_AUTOTESTAPP, AutotestAppNew),
		MMI_DEFINE_CLSID(CLSID_ANDROID_IDLEAPP, ANDROID_IDLEAPP_New),
		MMI_DEFINE_CLSID(CLSID_ANDROID_MAINMENUAPP, MAINMENUANDROID_New),
		MMI_DEFINE_CLSID(CLSID_BJXAPP, BjxAppNew),
		MMI_DEFINE_CLSID(CLSID_BMI, BmiAppNew),
		MMI_DEFINE_CLSID(CLSID_LICENSEMGRAPP, LicenseMgrAppNew),
		MMI_DEFINE_CLSID(CLSID_PRIVATEPROTECT, PrivateprotectAppNew),
		MMI_DEFINE_CLSID(CLSID_PRIVATEPROTECTPW, PrivateprotectpwAppNew),
		MMI_DEFINE_CLSID(CLSID_BCSAPP, BeautyClkSettingAppNew),
		MMI_DEFINE_CLSID(CLSID_BTAPP, BtAppNew),
		MMI_DEFINE_CLSID(CLSID_BTNOTIFYAPP, BtNotifyAppNew),
		MMI_DEFINE_CLSID(CLSID_CALCULATORAPP, CalculatorAppNew),
		MMI_DEFINE_CLSID(CLSID_CALCULATORPLUSAPP, CalculatorPlusAppNew),
		MMI_DEFINE_CLSID(CLSID_CALENDARAPP, CALENDARAPP_New),
		MMI_DEFINE_CLSID(CLSID_CALIBRATIONAPP, CalibrationAppNew),
		MMI_DEFINE_CLSID(CLSID_CALLLOGAPP, CallLogAppNew),
		MMI_DEFINE_CLSID(CLSID_CALLSETTINGAPP, CallSettingAppNew),
		MMI_DEFINE_CLSID(CLSID_CAMAPP, CAMAPP_New),
		MMI_DEFINE_CLSID(CLSID_CBSAPP, CBSAPP_New),
		MMI_DEFINE_CLSID(CLSID_CCAPP, CCAPP_New),
		MMI_DEFINE_CLSID(CLSID_VIDEOTELEPHONYAPP, VideoTelephonyApp_New),
		MMI_DEFINE_CLSID(CLSID_CCMTA, CCMTA_New),
		MMI_DEFINE_CLSID(CLSID_CDWAPAPP, CdWapAppNew),
		MMI_DEFINE_CLSID(CLSID_CALLERLOCATIONAPP, CallerLocationAppNew),
		MMI_DEFINE_CLSID(CLSID_CONSETTINGAPP, ConSettingAppNew),
		MMI_DEFINE_CLSID(CLSID_COUNTDOWNTIMER, CountdownTimerAppNew),
		MMI_DEFINE_CLSID(CLSID_DIALERAPP, DialerAppNew),
		MMI_DEFINE_CLSID(CLSID_DIALERGROUPAPP, DialerGroupAppNew),
		MMI_DEFINE_CLSID(CLSID_DIALOGAPP, DialogAppNew),
		MMI_DEFINE_CLSID(CLSID_DIALOGAPP_TOP, DialogAppNew),
		MMI_DEFINE_CLSID(CLSID_DIALOGAPP_ALARM, DialogAppNew),
		MMI_DEFINE_CLSID(CLSID_DICTAPP, DictNew),
		MMI_DEFINE_CLSID(CLSID_EMUAPP, EmuAppNew),
		MMI_DEFINE_CLSID(CLSID_PACMAN, PacManNew),
		MMI_DEFINE_CLSID(CLSID_FRUITGAMBLEGAME, FruitGambleGameNew),
		MMI_DEFINE_CLSID(CLSID_FAVORITEPHB, FavoritePhb_New),
		MMI_DEFINE_CLSID(CLSID_BIG2, Big2New),
		MMI_DEFINE_CLSID(CLSID_E_BOOK, EbookAppNew),
		MMI_DEFINE_CLSID(CLSID_EMAPP, EmAppNew),
		MMI_DEFINE_CLSID(CLSID_EVTCENTERAPP, EvtCenterAppNew),
		MMI_DEFINE_CLSID(CLSID_FDNAPP, FDNAPP_New),
		MMI_DEFINE_CLSID(CLSID_FILEMGRAPP, FILEMGRAPP_New),
		MMI_DEFINE_CLSID(CLSID_FMRADIOAPP, FmRadioAppNew),
		MMI_DEFINE_CLSID(CLSID_FMSCHAPP, FmSchAppNew),
		MMI_DEFINE_CLSID(CLSID_FRUITSLICEGAME, FruitSliceGameNew),
		MMI_DEFINE_CLSID(CLSID_G3DMAINMENUAPP, G3dMainMenuAppNew),
		MMI_DEFINE_CLSID(CLSID_GOBANGAPP, GoBangAppNew),
		MMI_DEFINE_CLSID(CLSID_GOGOBOXGAME,  GogoBoxGameNew),
		MMI_DEFINE_CLSID(CLSID_ANGRYBIRDGAME,  AngryBirdNew),
		MMI_DEFINE_CLSID(CLSID_FISHFURYGAME,  FishFuryGameNew),
        MMI_DEFINE_CLSID(CLSID_VAMPIREGAME,  VampireGameNew),
		MMI_DEFINE_CLSID(CLSID_ZOMBIEGAME,  ZombieGameNew),
		MMI_DEFINE_CLSID(CLSID_HAMSTERFIGHTAPP, HamsterFightAppNew),
		MMI_DEFINE_CLSID(CLSID_IDLEAPP, IDLEAPP_New),
		MMI_DEFINE_CLSID(CLSID_IDLEPREVIEWAPP, IdlePreviewAppNew),
		MMI_DEFINE_CLSID(CLSID_IPLAYCUBEGAME,  IplayCubeGameNew),
		MMI_DEFINE_CLSID(CLSID_JAVAAMSAPP, JavaAppNew),
		MMI_DEFINE_CLSID(CLSID_JAVAFACTORYAPP, JavaFactoryAppNew),
		MMI_DEFINE_CLSID(CLSID_KEYGUARDAPP, KeyGuardAppNew),
		MMI_DEFINE_CLSID(CLSID_ANDROID_KEYGUARDAPP, AndroidKeyGuardAppNew),
		MMI_DEFINE_CLSID(CLSID_KINGMOVIEAPP, KingMovieAppNew),
		MMI_DEFINE_CLSID(CLSID_3DKINGMOVIEAPP,KingMovieAppNew),
		MMI_DEFINE_CLSID(CLSID_LABYRINTHGAME,  LabyrinthGameNew),
		MMI_DEFINE_CLSID(CLSID_CUTROPEGAME,  CutRopeNew),
		MMI_DEFINE_CLSID(CLSID_LINKUPAPP, LinkUpAppNew),
		MMI_DEFINE_CLSID(CLSID_MAINMENUAPP, MAINMENUAPP_New),
		MMI_DEFINE_CLSID(CLSID_MAPAPP, MapNew),
		MMI_DEFINE_CLSID(CLSID_MCA, McaAppNew),
		MMI_DEFINE_CLSID(CLSID_MGLDEMOAPP, MglDemoAppNew),
		MMI_DEFINE_CLSID(CLSID_OGLDEMOAPP, OglDemoAppNew),
		MMI_DEFINE_CLSID(CLSID_WDGDEMOAPP, WdgDemoAppNew),
		MMI_DEFINE_CLSID(CLSID_PICPREVIEWAPP, PicPreviewAppNew),
		MMI_DEFINE_CLSID(CLSID_MMSA, MMSA_New),
		MMI_DEFINE_CLSID(CLSID_MPLAYERAPP, MPlayerNew),
		MMI_DEFINE_CLSID(CLSID_MSA, MsaNew),
		MMI_DEFINE_CLSID(CLSID_MTA, MTA_New),
		MMI_DEFINE_CLSID(CLSID_NETWORKAPP, NetworkAppNew),
		MMI_DEFINE_CLSID(CLSID_NOTEPADAPP, NotepadAppNew),
		MMI_DEFINE_CLSID(CLSID_NTPAPP, NtpAppNew),
		MMI_DEFINE_CLSID(CLSID_SWITCHMODE, SwitchModeNew),
		MMI_DEFINE_CLSID(CLSID_OFFAPP, OffAppNew),
		MMI_DEFINE_CLSID(CLSID_ONAPP, OnAppNew),
		MMI_DEFINE_CLSID(CLSID_PHBAP, PHBAP_New),
		MMI_DEFINE_CLSID(CLSID_PHBAP2, PHBAP_New),
		MMI_DEFINE_CLSID(CLSID_PUZZLEAPP, PuzzleAppNew),
		MMI_DEFINE_CLSID(CLSID_PICVIEWERAPP, PicViewerAppNew),
		MMI_DEFINE_CLSID(CLSID_PROFILEAPP, ProfileAppNew),
		MMI_DEFINE_CLSID(CLSID_REMOTECONTROLAPP, RemoteControlAppNew),
		MMI_DEFINE_CLSID(CLSID_RUBIKCUBEGAME,  RubiksCubeNew),
		MMI_DEFINE_CLSID(CLSID_SEA, SeaNew),
		MMI_DEFINE_CLSID(CLSID_SEARCHAPP, SearchAppNew),
		MMI_DEFINE_CLSID(CLSID_SECAPP, SecNew),
		MMI_DEFINE_CLSID(CLSID_SECREMOTECONTROLAPP, SecNew),
		MMI_DEFINE_CLSID(CLSID_SENDVIAAPP, SendviaAppNew),
		MMI_DEFINE_CLSID(CLSID_SETTINGAPP, SettingAppNew),
		MMI_DEFINE_CLSID(CLSID_SHORTCUTPHB, ShortcutPhbNew),
		MMI_DEFINE_CLSID(CLSID_SHORTCUTSAPP, ShortcutsNew),
		MMI_DEFINE_CLSID(CLSID_SNOTEAPP, SnoteAppNew),
		MMI_DEFINE_CLSID(CLSID_SOHUUPDATERAPP, SoHuUpdaterAppNew),
		MMI_DEFINE_CLSID(CLSID_STKAPP, StkNew),
		MMI_DEFINE_CLSID(CLSID_STOPWATCHAPP, StopwatchAppNew),
		MMI_DEFINE_CLSID(CLSID_SOKOBANAPP, SokobanAppNew),
		MMI_DEFINE_CLSID(CLSID_SUDOKUAPP, SudokuAppNew),
		MMI_DEFINE_CLSID(CLSID_SVA, SVA_New),
		MMI_DEFINE_CLSID(CLSID_TESTAPP, TESTAPP_New),
		MMI_DEFINE_CLSID(CLSID_TODOLISTAPP,  ToDoListAppNew),
		MMI_DEFINE_CLSID(CLSID_TODOTASKVIEWER, ToDoListAppNew),
		MMI_DEFINE_CLSID(CLSID_UNITCONVERTER, UNITCONVERTER_New),
		MMI_DEFINE_CLSID(CLSID_UNITTEST, UNITTESTAPP_New),
		MMI_DEFINE_CLSID(CLSID_USBAPP, UsbAppNew),
		MMI_DEFINE_CLSID(CLSID_USSDAPP, UssdAppNew),
		MMI_DEFINE_CLSID(CLSID_VENDORAPP, VendorAppNew),
		MMI_DEFINE_CLSID(CLSID_VENDORLISTAPP, NULL),
		MMI_DEFINE_CLSID(CLSID_VIDEOPLAYERAPP, VideoPlayerNew),
		MMI_DEFINE_CLSID(CLSID_VOICEMAILAPP, VoiceMailAppNew),	// Changed by nick
		MMI_DEFINE_CLSID(CLSID_VOICEMEMOAPP, VoiceMemoAppNew),
		MMI_DEFINE_CLSID(CLSID_WORLDCLOCKAPP, WorldClockAppNew),
		MMI_DEFINE_CLSID(CLSID_IDLEAPP_DIALINGVIEW,	IDLEAPP_New),
		MMI_DEFINE_CLSID(CLSID_STKAPP2,				StkNew),
		MMI_DEFINE_CLSID(CLSID_WAPAPP,				VendorAppNew),
		MMI_DEFINE_CLSID(CLSID_WIFIAPP, WiFiAppNew),
		MMI_DEFINE_CLSID(CLSID_JAVAAPP,	_JAVAAPP_New),
		MMI_DEFINE_CLSID(CLSID_EMAILAPP, EmailAppNew),
		MMI_DEFINE_CLSID(CLSID_SCREENSAVERAPP, ScreensaverAppNew),
		MMI_DEFINE_CLSID(CLSID_CHECKDISKAPP, CheckDiskAppNew),
		MMI_DEFINE_CLSID(CLSID_QQAPP, QQAppNew),
#ifdef __RFID_MMI__
		MMI_DEFINE_CLSID(CLSID_RFIDDEMOAPP, RfidDemoAppNew),
#endif

		MMI_DEFINE_CLSID(CLSID_AZANAPP, AzanAppNew),
		MMI_DEFINE_CLSID(CLSID_DIALOGAPP_BTSTATUS, DialogAppNew),
		MMI_DEFINE_CLSID(CLSID_NETWORKCOUNTERAPP, NetworkCounterAppNew),
		MMI_DEFINE_CLSID(CLSID_TUDOUAPP, TuDouAppNew),
#include "ven_apptbl_pub.h"
		MMI_DEFINE_END_OF_CLSID(CLSID_END_OF_APPLET)
};

/**-----------------------------------------------------*
*	End of Style Area	(5/5)							*
*------------------------------------------------------*/

MMI_DEFINE_CLS_CATEGORY(MMI_TemplateClass)
{
	MMI_DEFINE_CLSID_BASE(CLSID_VTMAPP, MMI_TEMPLATE_CLASS_BASE, 0), // dummy class for classifying system events
		MMI_DEFINE_CLSID(CLSID_VTMDATEINPUT,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMIMG,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMINPUT,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMPROMPTINPUT,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMTIMEINPUT,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMIMGGRID,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMIMGTHUMB,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMMENU,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMSIMSELECTION,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMTABMENU,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMTXTGRID,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMIPINPUT,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMOPTIONMENU,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMPOPUPINFO,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMPOPUPINPUT,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMPOPUPPROMPT,NULL),
		MMI_DEFINE_CLSID(CLSID_VTMPOPUPSELECT,NULL),
		MMI_DEFINE_CLSID(CLSID_DLGCONFIRM,NULL),
		MMI_DEFINE_CLSID(CLSID_DLGINFO,NULL),
		MMI_DEFINE_CLSID(CLSID_DLGWAITTING,NULL),
		MMI_DEFINE_CLSID(CLSID_DLGPROGRESS,NULL),
		MMI_DEFINE_CLSID(CLSID_DLGVOLUME,NULL),
		MMI_DEFINE_CLSID(CLSID_DLGREDAIL,NULL),
		MMI_DEFINE_CLSID(CLSID_DLGRECORD,NULL),
		MMI_DEFINE_END_OF_CLSID(CLSID_END_OF_VTM)
};

#undef DECLARE_VEN_APP_CLSID
#endif // __MMI_CLSTBL_H__
// end of file
