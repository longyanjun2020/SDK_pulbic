

#ifndef __MMI_SHORTCUTSSRV_CFG__H__
#define __MMI_SHORTCUTSSRV_CFG__H__

#include "mmi_mae_common_def.h"
#define SHORTCUTS_TEXT_WCHAR_LEN (42)
#define SHORTCUTS_TEXT_BYTE_LEN (104)
#define SHORTCUTS_PARAM_LEN (128)
#if defined(__3D_UI_SHORTCUTAPP__) && (defined(__LCM_QVGA_MMI__)||defined(__LCM_WQVGA_240_400_MMI__))
#define SHORTCUTS_LIST_MAX_ITEM (9)
#else
#define SHORTCUTS_LIST_MAX_ITEM (12)
#endif
enum
{
    SHORTCUTS_PARAM_NONE=0,
    SHORTCUTS_PARAM_CALLLOG_ALL,
    SHORTCUTS_PARAM_CALLLOG_MISSED_CALL,
    SHORTCUTS_PARAM_CALLLOG_RECEIVED_CALL,
    SHORTCUTS_PARAM_CALLLOG_DIALED_CALL,
    SHORTCUTS_PARAM_CAM_PICTURE_MODE,
    SHORTCUTS_PARAM_CAM_VIDEO_MODE,
    SHORTCUTS_PARAM_MCA_MAIN_MENU,
    SHORTCUTS_PARAM_MCA_INBOX,
    SHORTCUTS_PARAM_MCA_DRAFT,
    SHORTCUTS_PARAM_MCA_OUTBOX,
    SHORTCUTS_PARAM_MCA_NEW_MSG,
    SHORTCUTS_PARAM_MCA_VOICE_MAIL,
    SHORTCUTS_PARAM_STKMENU,
    SHORTCUTS_PARAM_SETTINGS_DATETIME,
    SHORTCUTS_PARAM_SETTINGS_TIME,
    SHORTCUTS_PARAM_SETTINGS_AUTOONOFF,
    SHORTCUTS_PARAM_SETTINGS_PHONESETTINGS,
    SHORTCUTS_PARAM_SETTINGS_DISPLAYSETTINGS,
    SHORTCUTS_PARAM_SETTINGS_RINGTONESETTINGS,
    SHORTCUTS_PARAM_SETTINGS_CALLSETTINGS,
    SHORTCUTS_PARAM_SETTINGS_CONNECTSETTINGS,
    SHORTCUTS_PARAM_SETTINGS_NETWORKSETTINGS,
    SHORTCUTS_PARAM_SETTINGS_SECURITY,
    SHORTCUTS_PARAM_SETTINGS_CAMERATYPE,
    SHORTCUTS_PARAM_EVTCENTER_ALL,
    SHORTCUTS_PARAM_EVTCENTER_IDLE,
    SHORTCUTS_PARAM_KEYGUARD_HOTKEY,
    SHORTCUTS_PARAM_KEYGUARD_AUTO,
    SHORTCUTS_PARAM_PHONEBOOK,
    SHORTCUTS_PARAM_NEW_CONTACT,
    SHORTCUTS_PARAM_SHORTCUTS,
    SHORTCUTS_PARAM_MAINMENU_SETTINGS,
    SHORTCUTS_PARAM_MUSIC_PLAYER,
    SHORTCUTS_PARAM_VIDEO_PLAYER,
    SHORTCUTS_PARAM_PHOTO_VIEWER,
    SHORTCUTS_PARAM_SWITCH_MODE,
	SHORTCUTS_PARAM_TV_ATV,
	SHORTCUTS_PARAM_TV_ISDBT,
	SHORTCUTS_PARAM_FMRADIO_SCH_REC,
	SHORTCUTS_PARAM_FMRADIO_SCH_PLAY,
    /* #if defined(__ZYUE_ENGINE__) */
    SHORTCUTS_PARAM_ZHANGYUE_EBOOK,
    SHORTCUTS_PARAM_ZHANGYUE_MAGA,
    SHORTCUTS_PARAM_ZHANGYUE_CART,
    SHORTCUTS_PARAM_ZHANGYUE_SELECTOR,
    /* #endif */
	SHORTCUTS_PARAM_SXM_VIDEO, //Sxmobi video chat
    SHORTCUTS_PARAM_SXM_BOOK,  //sxmboi book
	SHORTCUTS_PARAM_SXM_GAME,  //sxmobi game
    SHORTCUTS_PARAM_CALLER_LOCATION,
    SHORTCUTS_PARAM_CDWAP_YOUTUBE, //Directly open youtube through CDWAP
    SHORTCUTS_PARAM_CDWAP_YOUKU, //Directly open youku through CDWAP
    SHORTCUTS_PARAM_CDWAP_VUCLIP, //Directly open vuclip through CDWAP
    SHORTCUTS_PARAM_CDWAP_BAIDU, //Directly open baidu through CDWAP
    SHORTCUTS_PARAM_NTPAPP,     //Directly open NTPApp
	SHORTCUTS_PARAM_TQQ_E_ENTRY_DEFAULT,    //Tencent Mcare Menu  (default)
	SHORTCUTS_PARAM_TQQ_E_ENTRY_QQB,        //Tencent Tqq Browser
	SHORTCUTS_PARAM_TQQ_E_ENTRY_MAX,        //DUMMY for Tencent max count (please add other option before this dummy value)
    SHORTCUTS_PARAM_TOTAL
};
typedef u8 ShortcutsParamId_e;
enum
{
    SHORTCUTS_FUNC_HANDLE_BASE=0,
    SHORTCUTS_FUNC_NONE=SHORTCUTS_FUNC_HANDLE_BASE/*No Function*/,
    SHORTCUTS_FUNC_UNASSIGN/*Unassign Function*/,
    SHORTCUTS_FUNC_PHONENUMBER/*Phone Number (for Shortcuts)*/,
    SHORTCUTS_FUNC_MAINMENU/*Main Menu*/,
    SHORTCUTS_FUNC_VOICEMAIL/*Voicemail*/,
    SHORTCUTS_FUNC_EVENTCENTER_IDLE/*Event Center (Idle style)*/,
    SHORTCUTS_FUNC_KEYGUARD_HOTKEY/*Keypad Lock (launch by hotkey)*/,
    SHORTCUTS_FUNC_KEYGUARD_AUTO/*Keypad Lock (launch automatically)*/,
    SHORTCUTS_FUNC_ALARM/*Alarm*/,
	SHORTCUTS_FUNC_AZAN/*Azan*/,
	SHORTCUTS_FUNC_BCS/*Beauty Clk Setting*/,
    SHORTCUTS_FUNC_BLUETOOTH/*Bluetooth*/,
    SHORTCUTS_FUNC_BOOKMARK/*Bookmark*/,
    SHORTCUTS_FUNC_CALCULATOR/*Calculator*/,
	SHORTCUTS_FUNC_CALCULATOR_PLUS/*Calculator Plus*/,
    SHORTCUTS_FUNC_CALENDAR/*Calendar*/,
    SHORTCUTS_FUNC_TODOLIST/*ToDoListApp*/,
    SHORTCUTS_FUNC_CALLLOG/*Call History*/,
    SHORTCUTS_FUNC_CALLSETTINGS/*Call Settings*/,
    SHORTCUTS_FUNC_CAMERA/*Camera*/,
    SHORTCUTS_FUNC_CONNECTSETTINGS/*Connect Settings*/,
    SHORTCUTS_FUNC_COUNTDOWNTIMER/*Countdown Timer*/,
    SHORTCUTS_FUNC_DATEANDTIME/*Date and Time*/,
    SHORTCUTS_FUNC_TIME/*Time*/,
    SHORTCUTS_FUNC_DIALING/*Dialing*/,
    SHORTCUTS_FUNC_DICT/*Dict app*/,
    SHORTCUTS_FUNC_DISPLAYSETTINGS/*Display Settings*/,
    SHORTCUTS_FUNC_EVENTCENTER_FULL/*Event Center (full page style)*/,
    SHORTCUTS_FUNC_FILEMANAGER/*File Manager*/,
    SHORTCUTS_FUNC_FMRADIO/*FM Radio*/,
    SHORTCUTS_FUNC_FMRADIO_SCH_REC/*FM SCH REC*/,
    SHORTCUTS_FUNC_FMRADIO_SCH_PLAY/*FM SCH PLAY*/,
    SHORTCUTS_FUNC_GAMES_EMU/*EMU Game*/,
	SHORTCUTS_FUNC_GAMES_BIG2/*Big 2 game*/,
	SHORTCUTS_FUNC_GAMES_FRUIT/*Fruit game*/,
	SHORTCUTS_FUNC_GAMES_PACMAN/*Pacman game*/,
	SHORTCUTS_FUNC_GAMES_GOBANG/*Gobang game*/,
	SHORTCUTS_FUNC_GAMES_HAMSTERFIGHT/*Hamster Fight game*/,
	SHORTCUTS_FUNC_GAMES_LINKUP/*Linkup game*/,
	SHORTCUTS_FUNC_GAMES_PUZZLE/*Puzzle game*/,
	SHORTCUTS_FUNC_GAMES_SOKOBAN/*Sokoban game*/,
	SHORTCUTS_FUNC_GAMES_SUDOKU/*Sudoku game*/,
    SHORTCUTS_FUNC_GAMES_GOGOBOX/*GogoBox game*/,
	SHORTCUTS_FUNC_GAMES_ANGRYBIRD/*AngryBird game*/,
    SHORTCUTS_FUNC_GAMES_FRUITSLICE/*FruitSlice game*/,
    SHORTCUTS_FUNC_GAMES_LABYRINTH/*Labyrinth game*/,
	SHORTCUTS_FUNC_GAMES_CUTROPE/*Cutrope game*/,
	SHORTCUTS_FUNC_GAMES_IPLAYCUBE/*match box Game*/,
	SHORTCUTS_FUNC_GAMES_RUBIKCUBE/*Rubik Cube Game*/,
    SHORTCUTS_FUNC_GAMES_FISHFURY/*Fishfury Game*/,
    SHORTCUTS_FUNC_GAMES_VAMPIRE/*Vampire Game*/,
    SHORTCUTS_FUNC_GAMES_ZOMBIE/*Zombie Game*/,
    SHORTCUTS_FUNC_INBOX/*Inbox*/,
    SHORTCUTS_FUNC_KINGMOVIE/*KingMovie*/,
    SHORTCUTS_FUNC_3DKMV/*3D KingMovie*/,
    SHORTCUTS_FUNC_LICENSEMGR/*License manager*/,
    SHORTCUTS_FUNC_MAINMENU_SETTINGS/*Main Menu Settings*/,
    SHORTCUTS_FUNC_MEDIAPLAYER/*Media Player*/,
    SHORTCUTS_FUNC_MESSAGECENTER/*Message Center*/,
    SHORTCUTS_FUNC_MMS/*MMS*/,
    SHORTCUTS_FUNC_MUSICPLAYER/*Music Player*/,
    SHORTCUTS_FUNC_NETWORKSETTINGS/*Network Settings*/,
    SHORTCUTS_FUNC_NEWCONTACT/*New Contact*/,
    SHORTCUTS_FUNC_NEWMESSAGE/*New Message*/,
    SHORTCUTS_FUNC_NOTEPAD/*Notepad*/,
	SHORTCUTS_FUNC_PHONEBOOK/*Phonebook*/,
	SHORTCUTS_FUNC_FAVORITEPHB/*Favorite phonebook*/,
    SHORTCUTS_FUNC_PHONESETTINGS/*Phone Settings*/,
    SHORTCUTS_FUNC_PHOTOVIEWER/*Photo Viewer*/,
    SHORTCUTS_FUNC_PHOTOSLIDE/*Photo Slide - Landscape Style*/,
    SHORTCUTS_FUNC_PROFILES/*Profiles*/,
    SHORTCUTS_FUNC_RINGTONESETTINGS/*Ringtone Settings*/,
	SHORTCUTS_FUNC_SEARCH/*Search*/,
    SHORTCUTS_FUNC_SECURITY/*Security*/,
    SHORTCUTS_FUNC_CAMERA_TYPE/*Camera Selection*/,
    SHORTCUTS_FUNC_SETTINGS/*Settings*/,
    SHORTCUTS_FUNC_SHORTCUTS/*Shortcuts*/,
    SHORTCUTS_FUNC_SNOTE/*Snote*/,
    SHORTCUTS_FUNC_STK_MASTER/*STK (Master SIM)*/,
    SHORTCUTS_FUNC_STK_SLAVE/*STK (Slave SIM)*/,
    SHORTCUTS_FUNC_STOPWATCH/*Stopwatch*/,
    SHORTCUTS_FUNC_SWITCHMODE/*Switch Mode*/,
    SHORTCUTS_FUNC_UNITCONVERTER/*Unit Converter*/,
    SHORTCUTS_FUNC_VIDEOPLAYER/*Video Player*/,
    SHORTCUTS_FUNC_VIDEORECORDER/*Camcorder*/,
    SHORTCUTS_FUNC_VOICEMEMO/*Voice Memo*/,
    SHORTCUTS_FUNC_WORLDCLOCK/*World Clock*/,
    SHORTCUTS_FUNC_CDWAP/*CDWAP*/,
    SHORTCUTS_FUNC_EMAIL/*Email*/,
    SHORTCUTS_FUNC_E_BOOK/*E-Book*/,
    SHORTCUTS_FUNC_BMI/*BMI*/,
	SHORTCUTS_FUNC_RFID,	//__RFID_MMI__
    SHORTCUTS_FUNC_JAVAAMS/*Java*/,
    SHORTCUTS_FUNC_PCSYNCTOOL/*PC Sync Tool*/,
    SHORTCUTS_FUNC_ATV/*ATV*/,
    SHORTCUTS_FUNC_ISDBT/*ISDBT*/,
    SHORTCUTS_FUNC_UNITTESTAPP/*UNITTESTAPP*/,
    SHORTCUTS_FUNC_MAP/*Map*/,
    SHORTCUTS_FUNC_QQ/*QQ*/,
    SHORTCUTS_FUNC_VENDOR_GAMES/*Vendor Games*/,
    SHORTCUTS_FUNC_TENCENT_DEFAULT/*tencent QQ Default*/,
    SHORTCUTS_FUNC_TENCENT_QQB/* tencent QQ browser*/,
    SHORTCUTS_FUNC_TENCENT_MAX/* tencent series max number for checking the boundry (add new option of Tencent before this value, order reference to VendorAppTqqStartParam_e in mmi_vendorapp.h)*/,
    SHORTCUTS_FUNC_NATIVE_QQ/*native QQ*/,
    SHORTCUTS_FUNC_ZMOL_APP,
    SHORTCUTS_FUNC_SXM_VCHAT/*sxm video chart*/,
    SHORTCUTS_FUNC_SXM_BOOK/*sxm ebook*/,
    SHORTCUTS_FUNC_SXM_GAME/*sxm game  */,
	SHORTCUTS_FUNC_ZHANGYUE_EBOOK /* #if defined(__ZYUE_ENGINE__) */,
    SHORTCUTS_FUNC_VENDOR_LIST/*Vendor List*/,
	SHORTCUTS_FUNC_CALLER_LOCATION,
	SHORTCUTS_FUNC_TUDOU,
    SHORTCUTS_FUNC_YOUTUBE/*YOUTUBE*/,  
    SHORTCUTS_FUNC_YOUKU/*YOUKU*/,  
    SHORTCUTS_FUNC_VUCLIP/*VUCLIP*/,   
    SHORTCUTS_FUNC_BAIDU/*BAIDU*/,  
    SHORTCUTS_FUNC_NTPAPP/*NTPAPP*/,
    SHORTCUTS_FUNC_HANDLE_END,
    SHORTCUTS_FUNC_NOT_HANDLE_BASE=SHORTCUTS_FUNC_HANDLE_END,
    SHORTCUTS_FUNC_SILENT_MODE=SHORTCUTS_FUNC_NOT_HANDLE_BASE,
    SHORTCUTS_FUNC_IDLE_DIALING,
    SHORTCUTS_FUNC_NOT_HANDLE_END,
    SHORTCUTS_FUNC_WIFI/*WiFi*/,
    SHORTCUTS_FUNC_TOTAL
};
typedef u16 ShortcutsFuncId_e;
enum
{
    MAIN_MENU_BOOL_FALSE=0,
    MAIN_MENU_BOOL_TRUE=1
};
typedef u8 MAIN_MENU_BOOL_E;
typedef struct _ShortcutsParamInfo_t
{
    MAE_WChar ucs2Text[SHORTCUTS_TEXT_WCHAR_LEN];
    u8 utf8Param[SHORTCUTS_PARAM_LEN];
	u32 u32ContactImageId;
} ShortcutsParamInfo_t;
typedef struct _ShortcutsKeyFuncInfo_t
{
    ShortcutsFuncId_e nLongPressFuncId;
    ShortcutsFuncId_e nShortPressFuncId;
    u8 nSpecialChar;
} ShortcutsKeyFuncInfo_t;
typedef struct _ShortcutsNaviKeyInfo_t
{
    boolean bIsLocked;
    ShortcutsFuncId_e nFuncId;
} ShortcutsNaviKeyInfo_t;
typedef struct _ShortcutsSoftKeyInfo_t
{
    boolean bIsLocked;
    ShortcutsParamInfo_t stParams;
    ShortcutsFuncId_e nFuncId;
} ShortcutsSoftKeyInfo_t;
typedef struct _ShortcutsNumKeyInfo_t
{
    boolean bIsLocked;
    ShortcutsParamInfo_t stParams;
    ShortcutsKeyFuncInfo_t tFuncInfo;
} ShortcutsNumKeyInfo_t;
typedef struct _ShortcutsListInfo_t
{
    boolean bIsLocked;
    ShortcutsParamInfo_t stParams;
    ShortcutsFuncId_e nFuncId;
} ShortcutsListInfo_t;
typedef struct _MainMenuItem_t
{
    ShortcutsFuncId_e eShortcutsFuncId;
    MAIN_MENU_BOOL_E bIsLocked;
    MAIN_MENU_BOOL_E bIsEnable;
} MainMenuItem_t;


//shortcut
#if defined(__3D_UI_IDLE_MULTIPAGE__)
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_UP CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_UP, ShortcutsNaviKeyInfo_t, 1, {FALSE/*bIsLocked*/, SHORTCUTS_FUNC_NEWMESSAGE/*nFuncId*/})
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_DOWN CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_DOWN, ShortcutsNaviKeyInfo_t, 1, {FALSE/*bIsLocked*/, SHORTCUTS_FUNC_SHORTCUTS/*nFuncId*/})
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_LEFT CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_LEFT, ShortcutsNaviKeyInfo_t, 1, {TRUE/*bIsLocked*/, SHORTCUTS_FUNC_NEWMESSAGE/*nFuncId*/})
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_RIGHT CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_RIGHT, ShortcutsNaviKeyInfo_t, 1, {TRUE/*bIsLocked*/, SHORTCUTS_FUNC_PROFILES/*nFuncId*/})
#else
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_UP CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_UP, ShortcutsNaviKeyInfo_t, 1, {FALSE/*bIsLocked*/, SHORTCUTS_FUNC_PHONEBOOK/*nFuncId*/})
#ifdef __APP_MMI_SHORTCUTLIST__
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_DOWN CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_DOWN, ShortcutsNaviKeyInfo_t, 1, {FALSE/*bIsLocked*/, SHORTCUTS_FUNC_SHORTCUTS/*nFuncId*/})
#else
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_DOWN CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_DOWN, ShortcutsNaviKeyInfo_t, 1, {FALSE/*bIsLocked*/, SHORTCUTS_FUNC_CAMERA/*nFuncId*/})
#endif
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_LEFT CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_LEFT, ShortcutsNaviKeyInfo_t, 1, {FALSE/*bIsLocked*/, SHORTCUTS_FUNC_NEWMESSAGE/*nFuncId*/})
#define CONFIG_AMR_SHORTCUTS_NAVIKEY_RIGHT CONFIG_DEFINE(CFGIT_SHORTCUTS_NAVIKEY_RIGHT, ShortcutsNaviKeyInfo_t, 1, {FALSE/*bIsLocked*/, SHORTCUTS_FUNC_PROFILES/*nFuncId*/})
#endif
#define CONFIG_AMR_SHORTCUTS_SOFTKEY_LEFT CONFIG_DEFINE(CFGIT_SHORTCUTS_SOFTKEY_LEFT, ShortcutsSoftKeyInfo_t, 1, {TRUE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_DIALING/*nFuncId*/})
#define CONFIG_AMR_SHORTCUTS_SOFTKEY_MIDDLE CONFIG_DEFINE(CFGIT_SHORTCUTS_SOFTKEY_MIDDLE, ShortcutsSoftKeyInfo_t, 1, {TRUE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_MAINMENU/*nFuncId*/})
#define CONFIG_AMR_SHORTCUTS_SOFTKEY_RIGHT CONFIG_DEFINE(CFGIT_SHORTCUTS_SOFTKEY_RIGHT, ShortcutsSoftKeyInfo_t, 1, {TRUE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_PHONEBOOK/*nFuncId*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_1 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_1, ShortcutsNumKeyInfo_t, 1, {TRUE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_VOICEMAIL/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_2 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_2, ShortcutsNumKeyInfo_t, 1, {FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_UNASSIGN/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_3 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_3, ShortcutsNumKeyInfo_t, 1, {FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_UNASSIGN/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_4 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_4, ShortcutsNumKeyInfo_t, 1, {FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_UNASSIGN/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_5 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_5, ShortcutsNumKeyInfo_t, 1, {FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_UNASSIGN/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_6 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_6, ShortcutsNumKeyInfo_t, 1, {FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_UNASSIGN/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_7 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_7, ShortcutsNumKeyInfo_t, 1, {FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_UNASSIGN/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0x70/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_8 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_8, ShortcutsNumKeyInfo_t, 1, {FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_UNASSIGN/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_9 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_9, ShortcutsNumKeyInfo_t, 1, {FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_UNASSIGN/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_STAR CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_STAR, ShortcutsNumKeyInfo_t, 1, {TRUE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_NONE/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_0 CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_0, ShortcutsNumKeyInfo_t, 1, {TRUE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_NONE/*nLongPressFuncId*/, SHORTCUTS_FUNC_NONE/*nShortPressFuncId*/, 0x2b/*nSpecialChar*/}/*tFuncInfo*/})
#define CONFIG_AMR_SHORTCUTS_NUMKEY_HASH CONFIG_DEFINE(CFGIT_SHORTCUTS_NUMKEY_HASH, ShortcutsNumKeyInfo_t, 1, {TRUE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, {SHORTCUTS_FUNC_SILENT_MODE/*nLongPressFuncId*/, SHORTCUTS_FUNC_KEYGUARD_HOTKEY/*nShortPressFuncId*/, 0/*nSpecialChar*/}/*tFuncInfo*/})
#ifdef __3D_UI_SHORTCUTAPP__
#if (SHORTCUTS_LIST_MAX_ITEM == 9)
#define CONFIG_AMR_SHORTCUTS_LIST CONFIG_DEFINE(CFGIT_SHORTCUTS_LIST, ShortcutsListInfo_t, SHORTCUTS_LIST_MAX_ITEM, \
{{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_DIALING/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_CALENDAR/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_ALARM/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_PROFILES/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_MUSICPLAYER/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_SETTINGS/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_INBOX/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_CAMERA/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_MESSAGECENTER/*nFuncId*/}})
#elif (SHORTCUTS_LIST_MAX_ITEM == 12)
#define CONFIG_AMR_SHORTCUTS_LIST CONFIG_DEFINE(CFGIT_SHORTCUTS_LIST, ShortcutsListInfo_t, SHORTCUTS_LIST_MAX_ITEM, \
{{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_DIALING/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_CALENDAR/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_ALARM/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_BLUETOOTH/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_PROFILES/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_MUSICPLAYER/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_SETTINGS/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_INBOX/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_CAMERA/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_CALCULATOR/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_MESSAGECENTER/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_CDWAP/*nFuncId*/}})
#endif
#else //2d shortcut
#define CONFIG_AMR_SHORTCUTS_LIST CONFIG_DEFINE(CFGIT_SHORTCUTS_LIST, ShortcutsListInfo_t, SHORTCUTS_LIST_MAX_ITEM, \
{{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/},\
{FALSE/*bIsLocked*/, {{L""}/*ucs2Text*/, {0}/*utf8Param*/}/*stParams*/, SHORTCUTS_FUNC_NONE/*nFuncId*/}})
//shortcut end
#endif

#define SHORTCUTSSRV_AMR_ALL_CONFIG \
                              CONFIG_AMR_SHORTCUTS_NAVIKEY_UP \
                              CONFIG_AMR_SHORTCUTS_NAVIKEY_DOWN \
                              CONFIG_AMR_SHORTCUTS_NAVIKEY_LEFT \
                              CONFIG_AMR_SHORTCUTS_NAVIKEY_RIGHT \
                              CONFIG_AMR_SHORTCUTS_SOFTKEY_LEFT \
                              CONFIG_AMR_SHORTCUTS_SOFTKEY_MIDDLE \
                              CONFIG_AMR_SHORTCUTS_SOFTKEY_RIGHT \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_1 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_2 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_3 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_4 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_5 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_6 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_7 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_8 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_9 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_STAR \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_0 \
                              CONFIG_AMR_SHORTCUTS_NUMKEY_HASH \
                              CONFIG_AMR_SHORTCUTS_LIST \

#endif  //__MMI_SHORTCUTSSRV_CFG__H__
