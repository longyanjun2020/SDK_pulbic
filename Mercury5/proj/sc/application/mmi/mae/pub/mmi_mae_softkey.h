/**
 * \file    mmi_mae_softkey.h
 * \brief   The document defines softkey type and id
 * \author  steve.lee@mstarsemi.com
 *
 * @version $Id: mmi_mae_softkey.h 1650 2009-08-25 06:52:59Z mark.yang $
 */

#ifndef __MMI_MAE_SOFTKEY_H__
#define __MMI_MAE_SOFTKEY_H__

/* 
 * NOTICE:
 * When changing the enum of SoftkeyID,
 * you should also change SK_ImageId[] (in mmi_wdg_softkey_priv.h) as well.
 * Otherwise the wrong image will be displayed.
 * */
typedef enum
{
	DEFAULT_SK = 0,
	SK_TEXTSOFTKEY_BASE,
	SK_NONE = SK_TEXTSOFTKEY_BASE,
    SK_CANCEL,
    SK_SELECT,
    SK_BACK,
    SK_CHANGE,
    SK_OK_TEXT,
    SK_YES,
    SK_NO,
    SK_SOS,
    SK_SNOOZE,
    SK_OPTION,
    SK_SEND,
	SK_SAVE,
	SK_EXIT,
	SK_ADD,
	SK_CLOSE,
	SK_NEXT,
	SK_SPELL,
	SK_ANSWER,
	SK_QUIET,
	SK_BUSY,
	SK_REDIAL,
	SK_SET,
	SK_SETTINGS,
	SK_UNLOCK,
	SK_CALL,
	SK_QUIT,
	SK_ZOOM_IN,
	SK_ZOOM_OUT,
	SK_STOP_TEXT,
	SK_CONT_SEL,
	SK_SPLIT,	///< stopwatch use
	SK_RESET,	///< stopwatch use
	SK_MOVE,	///< media player use
	SK_MOVE_TO,
	SK_VIEW,    ///< Cell Broadcast in Idle
    SK_MSG,     ///< Event Center in Idle
	SK_EDIT,	///< alarm use
	SK_POWER_OFF,	///< alarm use
	SK_REPLY,	///< mm use
	SK_BIG,		///< game use
	SK_SMALL,   ///< game use
	SK_REPLACE,	///< shortcut use
	SK_EXPORT,	///< theme use
	SK_MASTER,
	SK_SLAVE,
	SK_CLEAR,
	SK_SEARCH,
	SK_PLUSMINUS,  ///< calculator use
	SK_NEW,			///< native game use
	SK_NEWGAME,	// breakout
	SK_AGAIN,	    ///< native game: play again
	SK_GAME_PAUSE,	///< native game use
	SK_GAME_RESUME,	///< native game use
	SK_MUTE,			///<For CC
	SK_UNMUTE,			///<For CC
	SK_END_CALL,		///<For CC
	SK_CHECK,		///< to do list
	SK_LIST,		///< voice memo use
	SK_EM_PASS,		///<Engineer Mode use
	SK_EM_FAIL,		///<Engineer Mode use
	SK_DELETE,
	SK_HELP,
	SK_COPY,
	SK_COPY_TO,
	SK_PASTE,
	SK_SUMMARY,
	SK_RATE,
    SK_OPEN,
    SK_PICK,        // note: text lable is Select
	SK_STARTPOS,
    SK_CONTINUE,
    SK_START,
    SK_MAP,   // for map applet
    SK_SPEAKER,
    SK_HANDSET,
	SK_UPDATE,
	SK_CONNECT,
	SK_RECORED_TEXT,
    SK_PLAYLIST,
    SK_PAUSE_TEXT,
    SK_RESUME_TEXT,
    SK_DOWNLOAD,
    SK_DETAIL,
    SK_IGNORE,
#ifdef __NCCQQ_MMI__
    SK_MINIMIZE,
#endif
    SK_SKEYBOARD,
	SK_USER_DEFINED_TEXT,  ///< provide user defined softkey which could be updated on run time.
    SK_TEXTSOFTKEY_END,
    SK_IMAGESOFTKEY_BASE = SK_TEXTSOFTKEY_END,
    SK_OK = SK_IMAGESOFTKEY_BASE,
	SK_PLAY,
	SK_PAUSE,
	SK_STOP,
	SK_SPEAKER_ON,
	SK_SPEAKER_OFF,
	SK_AM,
	SK_PM,
	SK_SW_START,	///< stopwatch use
	SK_SW_PAUSE,	///< stopwatch use
	SK_SW_RESUME,	///< stopwatch use
	SK_RECORD,		///< voicememo use
	SK_INPUT_NUMBER, ///< CCAP use
#ifdef __APP_MMI_BJX__
    SK_SWITCH_UP,    ///< BJX use
    SK_SWITCH_DOWN,  ///< BJX use
#endif //__APP_MMI_BJX__
	SK_ENDPOS,
	SK_CUT,
	SK_VOLUME,		///< voicememo, file manager use
#ifdef __NATIVE_GAME_MMI_FRUIT__	
	SK_GAME_PLAY,    /// game play button
#endif	
    SK_ADD_CONTACT,
	SK_ADD_EVENT,
    SK_BT_HEADSET,
#ifdef __NCCQQ_MMI__
    SK_QQ,
#endif
#ifdef __MMI_SMS_CHAT__
	SK_SEND_MSG, //for send msg in sms chat
#endif
#ifdef __CCMTA_OPTION_MENU_MMI__
    SK_ANSWER_CALL, ///< CCMTA use
#endif
    SK_DIAL_CALL,   ///< CCAP use
#ifdef __APP_MMI_AZAN__
    SK_PLUS_MINUS_IMG,
#endif
    SK_SMS_REJECT,		///<For CC SMS Reject MT call
    SK_KEYBOARD,
    SK_USER_DEFINED_IMAGE,
    SK_IMAGESOFTKEY_END,
	SK_SOFTKEY_NUM = SK_IMAGESOFTKEY_END
}SoftkeyID;
typedef u32 SoftkeyID_e;
#endif /* __MAE_SOFTKEY_H__ */
