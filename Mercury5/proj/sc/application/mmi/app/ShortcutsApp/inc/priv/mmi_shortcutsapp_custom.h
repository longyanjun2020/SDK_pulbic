/**
* @file mmi_shortcutsapp_custom.h
*
* @version $Id$
*/
#ifndef __MMI_SHORTCUTSAPP_CUSTOM_H__
#define __MMI_SHORTCUTSAPP_CUSTOM_H__

/*-------------------------------------------------------------------------*/
#include "mmi_shortcutssrv_cfg.h"

/*-------------------------------------------------------------------------*/
const static ShortcutsFuncId_e ShortcutAppListTbl[] =
{
    SHORTCUTS_FUNC_ALARM,
#ifdef __APP_MMI_AZAN__
	SHORTCUTS_FUNC_AZAN,
#endif
#ifdef __ATV_MMI__
	SHORTCUTS_FUNC_ATV,
#ifdef __ATV_ISDBT__
    SHORTCUTS_FUNC_ISDBT,
#endif
#endif
#ifdef __BLUETOOTH_MMI__
    SHORTCUTS_FUNC_BLUETOOTH,
#endif
#ifdef __APP_MMI_BMI__
    SHORTCUTS_FUNC_BMI,
#endif
#ifdef __APP_MMI_CALCULATOR__
    SHORTCUTS_FUNC_CALCULATOR,
#endif
#ifdef __APP_MMI_CALENDAR__
    SHORTCUTS_FUNC_CALENDAR,
#endif
#if defined(__ENABLE_CAMCORDER__)
    SHORTCUTS_FUNC_VIDEORECORDER,
#endif
#if defined(__ENABLE_CAMERA__)
    SHORTCUTS_FUNC_CAMERA,
#endif
#ifdef __APP_MMI_COUNTDOWN_TIMER__
    SHORTCUTS_FUNC_COUNTDOWNTIMER,
#endif
    SHORTCUTS_FUNC_DATEANDTIME,
    SHORTCUTS_FUNC_DIALING,
#ifdef __DICTAPP_MMI__
    SHORTCUTS_FUNC_DICT,
#endif
#ifdef __E_BOOK_MMI__
    SHORTCUTS_FUNC_E_BOOK,
#endif
#if defined(__GAME_ENGINE_EMU_MMI__)
    SHORTCUTS_FUNC_GAMES_EMU,
#endif
#ifdef __APP_MMI_EVENTCENTER__
    SHORTCUTS_FUNC_EVENTCENTER_FULL,
#endif
    SHORTCUTS_FUNC_FILEMANAGER,
#ifdef __APP_MMI_FM_RADIO__
    SHORTCUTS_FUNC_FMRADIO,
#endif
#if defined(__APP_MMI_FM_SCHEDULE__) && !defined(__3D_UI_SHORTCUTAPP__)
    SHORTCUTS_FUNC_FMRADIO_SCH_REC,
    SHORTCUTS_FUNC_FMRADIO_SCH_PLAY,
#endif
	SHORTCUTS_FUNC_INBOX,
#ifdef __JAVA_MMI__
    SHORTCUTS_FUNC_JAVAAMS,
#endif
#ifdef __MMI_KING_MOVIE__
    SHORTCUTS_FUNC_KINGMOVIE,
#endif
#if defined (__MMI_KING_MOVIE_3D__) && defined(__MMI_KING_MOVIE_3D_APP_INDIE__)
    SHORTCUTS_FUNC_3DKMV,
#endif
#ifdef __APP_MMI_LICENSEMGR__
	SHORTCUTS_FUNC_LICENSEMGR,
#endif
    SHORTCUTS_FUNC_MESSAGECENTER,
    SHORTCUTS_FUNC_MUSICPLAYER,
#ifdef __APPLIST_SUPPORT_NEWCONTACT__
    SHORTCUTS_FUNC_NEWCONTACT,
#endif
    SHORTCUTS_FUNC_NEWMESSAGE,
#ifdef __APP_MMI_NOTEPAD__
    SHORTCUTS_FUNC_NOTEPAD,
#endif
    SHORTCUTS_FUNC_PHONEBOOK,
    SHORTCUTS_FUNC_PHOTOVIEWER,
    SHORTCUTS_FUNC_PROFILES,
	SHORTCUTS_FUNC_SETTINGS,
#ifdef  __APP_MMI_SHORTCUTLIST__
    SHORTCUTS_FUNC_SHORTCUTS,
#endif
#ifdef __APP_MMI_SKETCHNOTE__
	SHORTCUTS_FUNC_SNOTE,
#endif

#ifdef __APPLIST_SUPPORT_STK__
    SHORTCUTS_FUNC_STK_MASTER,
    SHORTCUTS_FUNC_STK_SLAVE,
#endif
#ifdef __APP_MMI_STOPWATCH__
    SHORTCUTS_FUNC_STOPWATCH,
#endif
#ifdef __APP_MMI_TODOLIST__
    SHORTCUTS_FUNC_TODOLIST,
#endif
#ifdef __APP_MMI_UNITCONVERTER__
    SHORTCUTS_FUNC_UNITCONVERTER,
#endif
    SHORTCUTS_FUNC_VIDEOPLAYER,
#ifdef __APP_MMI_VOICE_MEMO__
    SHORTCUTS_FUNC_VOICEMEMO,
#endif
#ifdef __WAP_MMI_CDWAP__
    SHORTCUTS_FUNC_CDWAP,
#endif
#ifdef __EMAIL_MMI__
    SHORTCUTS_FUNC_EMAIL,
#endif
#ifdef __APP_MMI_WORLDCLOCK__
    SHORTCUTS_FUNC_WORLDCLOCK,
#endif
#ifdef __MAP_MMI__
    SHORTCUTS_FUNC_MAP,
#endif
#ifdef __SKYENGINE__
    SHORTCUTS_FUNC_QQ,
    SHORTCUTS_FUNC_VENDOR_GAMES,
#endif

#ifdef __ZMOL__
    SHORTCUTS_FUNC_ZMOL_APP,
#endif

// Only one of TENCENT QQ & NATIVE QQ will be used at the same time
#ifdef __TENCENT_MCARE__
    SHORTCUTS_FUNC_TENCENT_DEFAULT,
    //SHORTCUTS_FUNC_TENCENT_QQB,
// add rest TENCENT launch option before SHORTCUTS_FUNC_TENCENT_MAX, (same order as ShortcutsFuncId_e and ShortcutsParamId_e)
    //SHORTCUTS_FUNC_TENCENT_MAX,
#endif
#ifdef __NCCQQ_MMI__
    SHORTCUTS_FUNC_NATIVE_QQ,
#endif

#ifdef __ZYUE_ENGINE__
    SHORTCUTS_FUNC_ZHANGYUE_EBOOK,
#endif

#ifdef __SXMENGINE__
    SHORTCUTS_FUNC_SXM_VCHAT,
#ifdef __SXMENGINE_BOOKSTORE__
    SHORTCUTS_FUNC_SXM_BOOK,
#endif
#ifdef __SXMENGINE_GAME__
    SHORTCUTS_FUNC_SXM_GAME,
#endif
#endif
#if (defined(__SDK_MMI_VENDOR_ENTRY__) && defined(__APP_MMI_VENDOR_LIST__))
    SHORTCUTS_FUNC_VENDOR_LIST,
#endif
#ifdef __APP_MMI_NTP__
     SHORTCUTS_FUNC_NTPAPP,
#endif
    SHORTCUTS_FUNC_NONE
};

/*-------------------------------------------------------------------------*/
#endif /* __MMI_SHORTCUTSAPP_CUSTOM_H__ */
