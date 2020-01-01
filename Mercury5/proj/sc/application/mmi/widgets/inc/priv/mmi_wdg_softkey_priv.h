/**
* \file    mmi_wdg_softkey_priv.h
* \brief   The document describes internal declartion of Softkey Widget
* \author  kenny.wu@mstarsemi.com
* @version $Id: mmi_wdg_softkey_priv.h 38510 2009-08-25 06:53:19Z mark.yang $
*/
#ifndef __MMI_WDG_SOFTKEY_PRIV_H__
#define __MMI_WDG_SOFTKEY_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_decorator.h"
#include "mmi_wdg_softkey.h"
#include "mmi_mae_softkeymodel.h"
#include "mmi_mae_resource.h"
#include "mae_textlabel.h"
#include "mae_propcontainerbase.h"
#include "mmi_mae_config.h"   /// for language change
#include "mmi_mae_config_types.h"
#ifdef __TOUCH_SCREEN_MMI__
#include "mmi_mae_touchsrv.h"
#endif //__TOUCH_SCREEN_MMI__
#include "img_data.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/* SK is defined in mae_softkey.h */
__SLDPM_FREE__ const u32 SK_ImageId[] =
{
	COMMON_IMG_SOFTKEY_OK,
	VIDEOPLAYER_IMG_SOFTKEY_PLAY, ///< SK_PLAY
	VIDEOPLAYER_IMG_SOFTKEY_PAUSE,///< SK_PAUSE
	VIDEOPLAYER_IMG_SOFTKEY_STOP, ///< SK_STOP
	CALL_IMG_SPEAKER_ON, ///< SK_SPEAKER_ON
	CALL_IMG_SPEAKER_OFF, ///< SK_SPEAKER_OFF
	COMMON_IMG_SOFTKEY_AM,	///< SK_AM
	COMMON_IMG_SOFTKEY_PM,	///< SK_PM
	VIDEOPLAYER_IMG_SOFTKEY_PLAY, ///< SK_SW_START
	VIDEOPLAYER_IMG_SOFTKEY_PAUSE,///< SK_SW_PAUSE
	VIDEOPLAYER_IMG_SOFTKEY_STOP, ///< SK_SW_RESUME
	VOICEMEMO_IMG_SOFTKEY_RECORD,  ///< SK_RECORD
	COMMON_IMG_SOFTKEY_INPUT_NUMBER,         ////< SK_INPUT_NUMBER
#ifdef __APP_MMI_BJX__
	PHONEBOOK_IMG_UPWARD,       ///< SK_SWITCH_UP
	PHONEBOOK_IMG_DOWNWARD,      ///< SK_SWITCH_DOWN
#endif //__APP_MMI_BJX__
	COMMON_IMG_SOFTKEY_MARK_END,		///< SK_ENDPOS
	COMMON_IMG_SOFTKEY_CUT,			///< SK_CUT
	VIDEOPLAYER_IMG_SOFTKEY_VOLUME, ///< SK_VOLUME
#ifdef __NATIVE_GAME_MMI_FRUIT__	
	COMMON_IMG_ACTIVATE_CENTER_BUTTON,  ///< SK_GAME_PLAY
#endif	
    COMMON_IMG_SOFTKEY_ADD_CONTACT,  ///< SK_ADD_CONTACT
	COMMON_IMG_SOFTKEY_ADD_EVENT,  ///< SK_ADD_EVENT
    CALL_IMG_BLUETOOTH_ON, ///< SK_BT_HEADSET
#ifdef __NCCQQ_MMI__
    QQ_IMG_SOFTKEYBLINK,
#endif
#ifdef __MMI_SMS_CHAT__
	SMS_SOFTKEY_SEND, // < SK_SEND_MSG
#endif
#ifdef __CCMTA_OPTION_MENU_MMI__
    CALL_IMG_SOFTKEY_ANSWER_CALL, ///< SK_ANSWER_CALL
#endif
	CALL_IMG_SOFTKEY_DIAL_CALL, ///< SK_DIAL_CALL
#ifdef __APP_MMI_AZAN__
    AZAN_IMG_SOFTKEY_PLUS_MINUS,
#endif
};

__SLDPM_FREE__ const u32 SK_TextId[] =
{
	TXT_NULL_ID,					///< SK_NONE, point to null string
	TXT_RSK_N_CANCEL,	///< SK_CANCEL
	TXT_LSK_N_SELECT,	///< SK_SELECT
	TXT_RSK_N_BACK,		///< SK_BACK
	TXT_LSK_N_CHANGE,	///< SK_CHANGE
	TXT_LSK_N_OK,		///< SK_OK_TEXT
	TXT_LSK_N_YES,		///< SK_YES
	TXT_RSK_N_NO,		///< SK_NO
	TXT_LSK_N_SOS,		///< SK_SOS
	TXT_LSK_N_SNOOZE,	///< SK_SNOOZE
	TXT_LSK_N_OPTIONS,	///< SK_OPTION
	TXT_LSK_N_SEND,     ///< SK_SEND
	TXT_LSK_N_SAVE,		///< SK_SAVE
	TXT_RSK_N_EXIT,		///< SK_EXIT
	TXT_LSK_N_ADD,		///< SK_ADD
	TXT_RSK_N_CLOSE,	///< SK_CLOSE
	TXT_LSK_N_NEXT,		///< For Input
	TXT_LSK_N_SPELL,	///< For Input
	TXT_LSK_N_ANSWER,	///< For CC
	TXT_RSK_N_QUIET,	///< For CC
	TXT_RSK_N_BUSY,		///< For CC
	TXT_LSK_N_REDIAL,	///< For CC
	TXT_LSK_N_SET,		///< For Camera
	TXT_LSK_N_SETTINGS,	///< For Camera
	TXT_LSK_N_UNLOCK,    ///< SK_UNLOCK
	TXT_LSK_N_CALL,			///< SK_Call
	TXT_RSK_N_QUIT,			///< SK_Call
	TXT_RSK_N_ZOOM_IN,	///< SK_ZOOM_IN
	TXT_LSK_N_ZOOM_OUT,		///< SK_ZOOM_OUT
	TXT_RSK_N_STOP,			///< SK_STOP
	TXT_LSK_N_CONT_SEL,	///< SK_CONT_SEL
	TXT_LSK_N_SPLIT,	///< SK_SPLIT
	TXT_LSK_N_RESET,	///< SK_RESET
	TXT_LSK_N_MOVE,		///< SK_MOVE
        TXT_LSK_N_MOVE_TO,     ///< SK_MOVE_TO
	TXT_LSK_N_VIEW,     ///< SK_VIEW
	TXT_RSK_N_MSG,       ///< SK_MSG
	TXT_LSK_N_EDIT,		///< SK_EDIT
	TXT_RSK_N_POWER_OFF,///<SK_POWER_OFF
	TXT_LSK_N_REPLY,	///<SK_REPLY
	TXT_LSK_N_BIG,		///<SK_BIG
	TXT_RSK_N_SMALL,		///<SK_SMALL
	TXT_LSK_N_REPLACE,	///<SK_REPLACE
	TXT_LSK_N_EXPORT,	///<SK_EXPORT
	TXT_RSK_N_MASTER,	///<SK_MASTER
	TXT_LSK_N_SLAVE,		///<SK_SLAVE
	TXT_RSK_N_CLEAR,		///<SK_CLEAR
	TXT_LSK_N_SEARCH,	///<SK_SEARCH
	TXT_LSK_N_PLUS_MINUS_SWITCH,   ///SK_PLUSMINUS
	TXT_LSK_N_NEW,		///<SK_NEW
	TXT_LIL_N_NEW_GAME,	///
	TXT_LSK_N_AGAIN,	///<SK_AGAIN
	TXT_LSK_N_PAUSE,	///<SK_GAME_PAUSE
	TXT_LSK_N_RESUME,	///<SK_GAME_RESUME
	TXT_RSK_N_MUTE,	///<For CC
	TXT_RSK_N_UNMUTE,	///<For CC
	TXT_OIL1_N_END_ACTIVE_CALL,	///<For CC SK_END_CALL
	TXT_LSK_N_CHECK,	///<SK_CHECK
	TXT_LSK_N_LIST,		///<SK_LIST
	TXT_PML_N_SUCCESS,	///<SK_EM_PASS
	TXT_PML_N_ERROR,		///<SK_EM_FAIL
	TXT_LSK_N_DELETE,       ////<SK_DELETE
	TXT_OIL1_N_HELP,       ////<SK_HELP
	TXT_LSK_N_COPY,					///<SK_COPY
	TXT_LSK_N_COPY_TO,			///<SK_COPY_TO
	TXT_LSK_N_PASTE,				///<SK_PASTE
	TXT_LSK_N_SUMMARY,			///<SK_SUMMARY
	TXT_LIL_N_RATE,					///<SK_RATE
	TXT_LSK_N_OPEN,					///<SK_OPEN
	TXT_LSK_N_SELECT,    		///<SK_Pick
	TXT_LSK_N_START,				///<SK_STARTPOS
	TXT_LSK_N_CONTINUE,			///<SK_CONTINUE
	TXT_LIL_N_EMU_START,		///<SK_START
	TXT_LIL_N_BACK_TO_MAP, 	///<SK_MAP
    TXT_OIL1_N_SPEAKER,		///<SK_SPEAKER
    TXT_OIL1_N_HANDSET,		///<SK_HANDSET
	TXT_OIL_N_UPDATE,       ///<SK_UPDATE
	TXT_OIL1_N_CONNECT,       ///<SK_CONNECT
	TXT_OIL1_N_RECORD,      /// <SK_Record_text
    TXT_RSK_N_PLAYLIST,      /// <SK_PLAYLIST
    TXT_LSK_N_PAUSE,    ///<SK_PAUSE_TEXT
    TXT_LSK_N_RESUME,   ///<SK_RESUME_TEXT
    TXT_LSK_N_DOWNLOAD,     // SK_DOWNLOAD
    TXT_LIL_N_DETAIL,   ///<SK_DETAIL
    TXT_LIL_N_IGNORE,   ///<SK_IGNORE
#ifdef __NCCQQ_MMI__
    TXT_LSK_N_MINIMIZE,     // SK_MINIMIZE
#endif

};

/*layout style, horizontal and vertical*/
typedef enum
{
	SK_WDG_HORIZONTAL = 0,
	SK_WDG_VERTICAL,
}SK_STYLE_e;

/*
* enum id to indicate child widget in softkey-widget
*/
enum
{
	SK_WDG_CHILD_LEFT_TEXT = 0,
	SK_WDG_CHILD_RIGHT_TEXT,
	SK_WDG_CHILD_MIDDLE_IMG,
	SK_WDG_CHILD_LEFT_IMG,
	SK_WDG_CHILD_RIGHT_IMG,
	SK_WDG_CHILD_END,
	SK_WDG_CHILD_NONE = SK_WDG_CHILD_END,
	SK_WDG_CHILD_NUM = SK_WDG_CHILD_END
};
typedef u8 _SkChildWdgId_t;


#ifdef __TOUCH_SCREEN_MMI__

//nTS_LP_Status should be the following enum value.
enum
{
	LONG_PRESS_NONE = 0,
	LONG_PRESS_VALID,  /// Long press is valid, it means that the pressed pointer is in the softkey(left or right or middle) rectangle.
	LONG_PRESS_INVALID,/// Long press is invalid, it means that the pressed pointer is out of the rectangle of (left/right/middle)softkey.
	LONG_PRESS_EVT_SENT,   /// Long press key event is already sent.
	LONG_PRESS_END
};
typedef u8 TSLongPressStatus_t;


#endif //__TOUCH_SCREEN_MMI__

typedef struct
{
	PropContainerBase_t PCntrBase;
	IImage *pBgImg;                      ///< IBitmap for background image.

	/*  Supposing that the layout of our softkey would be like this

	---------------
	| SK1 |=| SK2 |
	---------------

	However, SK would be an image also. So we reserve the pointer of 2 images
	widgets.

	*/
	IWidget *apChildWdg[SK_WDG_CHILD_NUM];/*!< The order is: left text-widget, right text-widget,
	                                           middle bitmap-widget, left bitmap-widget and right bitmap-widget.
	                                           We use these widgets to draw image and text string */
	u32     softkey[NUM_SK];       ///< softkey id value
	RGBColor_t rgbTextColor;       ///< Text color for string softkey
	RGBColor_t rgbOutlineColor;    ///< Text outline color for string softkey
	ConfigListener_t LangCfgLsn;   ///< a listener for language change.
	u32					nReloadRCFlag;		///< the flag record which rc property has been modified outside, those are not reload
	IImage *pPressedLRBgImg;	///< IBitmap for left,Right softkey background while pressed.
	IImage *pPressedCSKBgImg;  ///< IBitmap for center softkey background while pressed.

#ifdef __TOUCH_SCREEN_MMI__
	ITouchSrv *pITouchSrv;
	_SkChildWdgId_t nTSPressedKey;      /// A status to indicate which child widget is pressed now.
	TSLongPressStatus_t  nTS_LP_Status; /// A flag to indicate the status of touch longpress
#endif //__TOUCH_SCREEN_MMI__
	u8		backgroundMode; ///< SK_BACKGROUND_DEFAULT to draw background or SK_BACKGROUND_TRANSPARENT not to draw background
	u8		skStyle; 		///< vertical style or horizontal style
}_MAE_SoftkeyWidget_t;

// RELOAD flag
enum
{
	SOFTKEY_WDG_RELOAD_FLAG_START = 0,
	SOFTKEY_WDG_RELOAD_FLAG_BG = SOFTKEY_WDG_RELOAD_FLAG_START,   ///< pBgImg
	SOFTKEY_WDG_RELOAD_FLAG_LRBG,	///< pPressedLRBgImg
	SOFTKEY_WDG_RELOAD_FLAG_CSKBG,	///< pPressedCSKBgImg
	SOFTKEY_WDG_RELOAD_FLAG_END
};

/**
* Flag Mask
*/
#define SOFTKEY_WDG_RELOAD_MASK_BG         (1<<SOFTKEY_WDG_RELOAD_FLAG_BG)
#define SOFTKEY_WDG_RELOAD_MASK_LRBG        (1<<SOFTKEY_WDG_RELOAD_FLAG_LRBG)
#define SOFTKEY_WDG_RELOAD_MASK_CSKBG         (1<<SOFTKEY_WDG_RELOAD_FLAG_CSKBG)
/**
* Macro to get flag value
*/
#define SOFTKEY_WDG_BG_IS_MODIFIED(_pWdg) \
    (boolean)(((_pWdg)->nReloadRCFlag&SOFTKEY_WDG_RELOAD_MASK_BG)>>SOFTKEY_WDG_RELOAD_FLAG_BG)
#define SOFTKEY_WDG_LRBG_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SOFTKEY_WDG_RELOAD_MASK_LRBG)>>SOFTKEY_WDG_RELOAD_FLAG_LRBG)
#define SOFTKEY_WDG_CSKBG_IS_MODIFIED(_pWdg) \
	(boolean)(((_pWdg)->nReloadRCFlag&SOFTKEY_WDG_RELOAD_MASK_CSKBG)>>SOFTKEY_WDG_RELOAD_FLAG_CSKBG)
/**
* Macro to Set flag value
*/
#define SOFTKEY_WDG_BG_SET_MODIFIED(_pWdg, _b) \
    (_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SOFTKEY_WDG_RELOAD_MASK_BG))|(((u32)_b)<<SOFTKEY_WDG_RELOAD_FLAG_BG)
#define SOFTKEY_WDG_LRBG_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SOFTKEY_WDG_RELOAD_MASK_LRBG))|(((u32)_b)<<SOFTKEY_WDG_RELOAD_FLAG_LRBG)
#define SOFTKEY_WDG_CSKBG_SET_MODIFIED(_pWdg, _b) \
	(_pWdg)->nReloadRCFlag = ((_pWdg)->nReloadRCFlag&(~SOFTKEY_WDG_RELOAD_MASK_CSKBG))|(((u32)_b)<<SOFTKEY_WDG_RELOAD_FLAG_CSKBG)

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret SoftkeyWidget_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean SoftkeyWidget_DefHandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret _SoftkeyWidgetStructCtor(_MAE_SoftkeyWidget_t *pThis);
static void _SoftkeyWidget_Dtor(_MAE_SoftkeyWidget_t *pThis);

void SoftkeyWidget_SetSize (IPropContainer *pIPropContainer, WidgetSize_t *pSize);

MAE_Ret SoftKey_SetUserSK(IPropContainer *pISoftkeyWidget, u32 type, void *data);

__SLDPM_FREE__ void _SetSoftkeyToTextWidget(IWidget *pIWidget, u32 P2);
__SLDPM_FREE__ void _SetSoftkeyToImageWidget(IWidget *pIWidget, u32 P2);
MAE_WChar* _GetSoftkeyTextByID(u32 softkey);

__SLDPM_FREE__ static boolean _SoftkeyWidget_SetProperty(_MAE_SoftkeyWidget_t *pThis, u32 P1, u32 P2);
static boolean _SoftkeyWidget_GetProperty(_MAE_SoftkeyWidget_t *pThis, u32 P1, u32 P2);
__SLDPM_FREE__ static MAERet_t _SoftkeyWidget_ChangeBgMode(_MAE_SoftkeyWidget_t *pThis, u8 nMode, boolean bForced);
static MAERet_t _SoftkeyWidget_ChangeSkStyle(_MAE_SoftkeyWidget_t *pThis, u8 nStyle);

#ifdef __TOUCH_SCREEN_MMI__
__INLINE u32 _SoftkeyWidget_GetKeyCode(_SkChildWdgId_t TsPressedKey);
static void _SoftkeyWidget_PostKeyEvents(_MAE_SoftkeyWidget_t *pThis);
__SLDPM_FREE__ static MAERet_t _SoftkeyWidget_HookTSEvent(_MAE_SoftkeyWidget_t *pThis);
__SLDPM_FREE__ static MAERet_t _SoftkeyWidget_UnhookTSEvent(_MAE_SoftkeyWidget_t *pThis);
static SoftkeyID_e  _SoftkeyWidget_GetSKIdFromWdgId(_MAE_SoftkeyWidget_t *pThis, _SkChildWdgId_t WdgId);
static void _SoftkeyWidget_TSLongPressTimerCB(void *pUser);
__SLDPM_FREE__ static void _SoftkeyWidget_EnableTsPressedBg(_MAE_SoftkeyWidget_t *pThis, IWidget *pWdg, boolean bEnable);

#endif //__TOUCH_SCREEN_MMI__

static void _SoftkeyWidget_ChangeWdgBG(_MAE_SoftkeyWidget_t *pThis);
static void _SoftkeyWidget_ChangeTextColor(_MAE_SoftkeyWidget_t *pThis);
static void _SoftkeyWidget_LoadResource(_MAE_SoftkeyWidget_t *pThis);
static void _SoftkeyWidget_LangChangeCB(void *pUsrData, MAECfgCategory_t cat, MAECfgItemId_t id, void *pItemData);
__INLINE void _SoftkeyWidget_RegisterToConfig(_MAE_SoftkeyWidget_t *pThis);
static void _SoftkeyWidget_ReloadRC(_MAE_SoftkeyWidget_t *pThis, DisplayMode_e nDispMode);

#endif /* __MMI_WDG_SOFTKEY_PRIV_H__ */
