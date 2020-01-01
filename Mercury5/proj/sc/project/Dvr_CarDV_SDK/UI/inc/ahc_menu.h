///@file ahc_menu.h Menu header for each project.
//==============================================================================
//
//  File        : ahc_menu.h
//  Description : INCLUDE File for the AHC Menu function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_MENU_H_
#define _AHC_MENU_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_common.h"
#include "ahc_menu_inc.h"
#include "config_fw.h"
#include "MenuSetting.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#ifndef FW_RUN_CALI_MODE_EN
#define FW_RUN_CALI_MODE_EN         (0)    // FW run calibration mode (special mode for calibration)
#endif

// Key pressed
#define FLGKEY_UP                   0x00000001
#define FLGKEY_DOWN                 0x00000002
#define FLGKEY_LEFT                 0x00000004
#define FLGKEY_RIGHT                0x00000008
#define FLGKEY_SET                  0x00000010
#define FLGKEY_ZOOMT                0x00000020
#define FLGKEY_ZOOMW                0x00000040
#define FLGKEY_MENU                 0x00000080
#define FLGKEY_MODE                 0x00000100
#define FLGKEY_RECORD               0x00000200
#define FLGKEY_BROWSER              0x00000400
#define FLGKEY_NONE                 0x00000800
#define FLGKEY_PRESS_MASK           0x0000FFFF

extern UINT32 KeyFlag;

//Keypad Definition
#define BUTTON_NONE                 KEYPAD_NONE

/* Short Press */
#define BUTTON_UP_PRESS             KEY_PRESS_UP
#define BUTTON_DOWN_PRESS           KEY_PRESS_DOWN
#define BUTTON_LEFT_PRESS           KEY_PRESS_LEFT
#define BUTTON_RIGHT_PRESS          KEY_PRESS_RIGHT
#define BUTTON_SET_PRESS            KEY_PRESS_OK
#define BUTTON_MENU_PRESS           KEY_PRESS_MENU
#define BUTTON_MODE_PRESS           KEY_PRESS_MODE
#define BUTTON_REC_PRESS            KEY_PRESS_REC
#define BUTTON_PLAYBACK_PRESS       KEY_PRESS_PLAY
#define BUTTON_POWER_PRESS          KEY_PRESS_POWER

#define BUTTON_TELE_PRESS           KEY_PRESS_TELE
#define BUTTON_WIDE_PRESS           KEY_PRESS_WIDE
#define BUTTON_SOS_PRESS            KEY_PRESS_SOS
#define BUTTON_MUTE_PRESS           KEY_PRESS_MUTE
#define BUTTON_CAPTURE_PRESS        KEY_PRESS_CAPTURE
#define BUTTON_FUNC1_PRESS          KEY_PRESS_FUNC1
#define BUTTON_FUNC2_PRESS          KEY_PRESS_FUNC2
#define BUTTON_FUNC3_PRESS          KEY_PRESS_FUNC3

#define BUTTON_USB_DETECTED         USB_CABLE_IN
#define BUTTON_SD_DETECTED          SD_CARD_IN
#define BUTTON_TV_DETECTED          TV_CABLE_IN
#define BUTTON_HDMI_DETECTED        HDMI_CABLE_IN
#define BUTTON_LCD_ROTATE           DEVICE_LCD_INV
#define BUTTON_COVER_OPEN           DEVICE_LCD_OPEN
#define BUTTON_DC_CABLE_IN          DC_CABLE_IN
#define BUTTON_CUS_SW1_ON           CUS_SW1_ON
#define BUTTON_CUS_SW2_ON           CUS_SW2_ON
#define BUTTON_USB_B_DEVICE_DETECTED USB_B_DEVICE_IN
#define BUTTON_TV_DECODER_SRC_TYPE  TV_DECODER_SRC_TYPE_CHANGED

#define BUTTON_SUB_MODE_ENTER       SUB_MODE_ENTER
#define BUTTON_SUB_MODE_EXIT        SUB_MODE_EXIT

/* Short Release */
#define BUTTON_UP_REL               KEY_REL_UP
#define BUTTON_DOWN_REL             KEY_REL_DOWN
#define BUTTON_LEFT_REL             KEY_REL_LEFT
#define BUTTON_RIGHT_REL            KEY_REL_RIGHT
#define BUTTON_SET_REL              KEY_REL_OK
#define BUTTON_MENU_REL             KEY_REL_MENU
#define BUTTON_MODE_REL             KEY_REL_MODE
#define BUTTON_REC_REL              KEY_REL_REC
#define BUTTON_PLAYBACK_REL         KEY_REL_PLAY
#define BUTTON_POWER_REL            KEY_REL_POWER

#define BUTTON_TELE_REL             KEY_REL_TELE
#define BUTTON_WIDE_REL             KEY_REL_WIDE
#define BUTTON_SOS_REL              KEY_REL_SOS
#define BUTTON_MUTE_REL             KEY_REL_MUTE
#define BUTTON_CAPTURE_REL          KEY_REL_CAPTURE
#define BUTTON_FUNC1_REL            KEY_REL_FUNC1
#define BUTTON_FUNC2_REL            KEY_REL_FUNC2
#define BUTTON_FUNC3_REL            KEY_REL_FUNC3

#define BUTTON_USB_REMOVED          USB_CABLE_OUT
#define BUTTON_REVERSE_GEAR         USB_REARCAM_REVERSE_GEAR//reverse gear
#define BUTTON_SD_REMOVED           SD_CARD_OUT
#define BUTTON_TV_REMOVED           TV_CABLE_OUT
#define BUTTON_HDMI_REMOVED         HDMI_CABLE_OUT
#define BUTTON_LCD_NORMAL           DEVICE_LCD_NOR
#define BUTTON_COVER_CLOSED         DEVICE_LCD_COVERED
#define BUTTON_DC_CABLE_OUT         DC_CABLE_OUT
#define BUTTON_CUS_SW1_OFF          CUS_SW1_OFF
#define BUTTON_CUS_SW2_OFF          CUS_SW2_OFF
#define BUTTON_USB_B_DEVICE_REMOVED USB_B_DEVICE_OUT

#define BUTTON_DEVICES_READY        DEVICES_READY

/* Long Press */
#define BUTTON_UP_LPRESS            KEY_LPRESS_UP
#define BUTTON_DOWN_LPRESS          KEY_LPRESS_DOWN
#define BUTTON_LEFT_LPRESS          KEY_LPRESS_LEFT
#define BUTTON_RIGHT_LPRESS         KEY_LPRESS_RIGHT
#define BUTTON_SET_LPRESS           KEY_LPRESS_OK
#define BUTTON_MENU_LPRESS          KEY_LPRESS_MENU
#define BUTTON_MODE_LPRESS          KEY_LPRESS_MODE
#define BUTTON_REC_LPRESS           KEY_LPRESS_REC
#define BUTTON_PLAYBACK_LPRESS      KEY_LPRESS_PLAY
#define BUTTON_POWER_LPRESS         KEY_LPRESS_POWER

#define BUTTON_TELE_LPRESS          KEY_LPRESS_TELE
#define BUTTON_WIDE_LPRESS          KEY_LPRESS_WIDE
#define BUTTON_SOS_LPRESS           KEY_LPRESS_SOS
#define BUTTON_MUTE_LPRESS          KEY_LPRESS_MUTE
#define BUTTON_CAPTURE_LPRESS       KEY_LPRESS_CAPTURE
#define BUTTON_FUNC1_LPRESS         KEY_LPRESS_FUNC1
#define BUTTON_FUNC2_LPRESS         KEY_LPRESS_FUNC2
#define BUTTON_FUNC3_LPRESS         KEY_LPRESS_FUNC3

/* Long Release */
#define BUTTON_UP_LREL              KEY_LREL_UP
#define BUTTON_DOWN_LREL            KEY_LREL_DOWN
#define BUTTON_LEFT_LREL            KEY_LREL_LEFT
#define BUTTON_RIGHT_LREL           KEY_LREL_RIGHT
#define BUTTON_SET_LREL             KEY_LREL_OK
#define BUTTON_MENU_LREL            KEY_LREL_MENU
#define BUTTON_MODE_LREL            KEY_LREL_MODE
#define BUTTON_REC_LREL             KEY_LREL_REC
#define BUTTON_PLAYBACK_LREL        KEY_LREL_PLAY
#define BUTTON_POWER_LREL           KEY_LREL_POWER

#define BUTTON_TELE_LREL            KEY_LREL_TELE
#define BUTTON_WIDE_LREL            KEY_LREL_WIDE
#define BUTTON_SOS_LREL             KEY_LREL_SOS
#define BUTTON_MUTE_LREL            KEY_LREL_MUTE
#define BUTTON_CAPTURE_LREL         KEY_LREL_CAPTURE
#define BUTTON_FUNC1_LREL           KEY_LREL_FUNC1
#define BUTTON_FUNC2_LREL           KEY_LREL_FUNC2
#define BUTTON_FUNC3_LREL           KEY_LREL_FUNC3

/* Touch Panel */
#define BUTTON_TOUCH_PRESS          TOUCH_PANEL_PRESS
#define BUTTON_TOUCH_MOVE           TOUCH_PANEL_MOVE
#define BUTTON_TOUCH_REL            TOUCH_PANEL_REL

/* Power On Button */
#define BUTTON_POWER_ON_MENU        301
#define BUTTON_POWER_ON_MODE        302
#define BUTTON_POWER_ON_REC         303
#define BUTTON_POWER_ON_PLAY        304
#define BUTTON_POWER_ON_UP          305
#define BUTTON_POWER_ON_DOWN        306

/* Combo Key */
#define BUTTON_COMBO_SET1           311
#define BUTTON_COMBO_SET2           312
#define BUTTON_COMBO_SET3           313

#define BUTTON_TIMESTAMP_UPDATE     89
#define BUTTON_GPSGSENSOR_UPDATE    90
#define BUTTON_MENU_TIMEOUT         91
#define BUTTON_LOCK_FILE_G          92
#define BUTTON_LOCK_FILE_M          93
#define BUTTON_FOCUS_PASS           94
#define BUTTON_LENS_WMSG            95
#define BUTTON_CLEAR_WMSG           96
#define BUTTON_UPDATE_FILE          97
#define BUTTON_OSD_HIDE             98
#define BUTTON_UPDATE_MESSAGE       99
#define BUTTON_UPDATE_CHARGE_ICON   100
#define BUTTON_UPDATE_LCD           101
#define GSENSOR_ACT                 (BUTTON_LOCK_FILE_G)

#define BUTTON_VRCB_RECDSTOP_CARDSLOW   VRCB_RECDSTOP_CARDSLOW
#define BUTTON_VRCB_AP_STOP_VIDEO_RECD  VRCB_AP_STOP_VIDEO_RECD
#define BUTTON_VRCB_MEDIA_FULL          VRCB_MEDIA_FULL
#define BUTTON_VRCB_FILE_FULL           VRCB_FILE_FULL
#define BUTTON_VRCB_LONG_TIME_FILE_FULL VRCB_LONG_TIME_FILE_FULL
#define BUTTON_VRCB_MEDIA_SLOW          VRCB_MEDIA_SLOW
#define BUTTON_VRCB_MEDIA_ERROR         VRCB_MEDIA_ERROR
#define BUTTON_VRCB_SEAM_LESS           VRCB_SEAM_LESS
#define BUTTON_VRCB_MOTION_DTC          VRCB_MOTION_DTC
#define BUTTON_VRCB_VR_START            VRCB_VR_START
#define BUTTON_VRCB_VR_STOP             VRCB_VR_STOP
#define BUTTON_VRCB_VR_POSTPROC         VRCB_VR_POSTPROCESS
#define BUTTON_VRCB_EMER_DONE           VRCB_VR_EMER_DONE
#define BUTTON_VRCB_PREVIEW_ERR         VRCB_PREVIEW_ERR
#define BUTTON_VRCB_SHARE_FILE_FULL     VRCB_SHARE_FILE_FULL

#define BUTTON_BATTERY_DETECTION    BATTERY_DETECTION

#define BUTTON_LDWS_START                       (272)
#define BUTTON_LDWS_STOP                        (273)
#define BUTTON_FCWS_START                       (275)
#define BUTTON_FCWS_STOP                        (276)
#define BUTTON_SAG_START                        (277)
#define BUTTON_SAG_STOP                         (278)
#define BUTTON_ADAS_WRITE_LOG                   (279)
#define BUTTON_EV_MODIFY                        (280)
#define BUTTON_MENU_EXIT                        (281)

#define BUTTON_REC_SHORT                        (299)
#define BUTTON_NET_DOWNLOAD                     (300)

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE)
#define BUTTON_VIDEO_UVC_XU_RECORDTIME_CONTROL (400) //Andy Liu TBD
#define BUTTON_VIDEO_UVC_XU_RECORDRES_CONTROL (401)
#define BUTTON_VIDEO_UVC_XU_FILE_CONTROL (402)
#define BUTTON_VIDEO_UVC_XU_PICTURE_CONTROL (403)
#define BUTTON_VIDEO_UVC_XU_GSENSOR_CONTROL (404)
#define BUTTON_VIDEO_UVC_XU_AUDIO_CONTROL (405)
#define BUTTON_VIDEO_UVC_XU_STATUS_CONTROL (406)
#define BUTTON_VIDEO_UVC_XU_REC_MODE_CONTROL (407)
#define BUTTON_VIDEO_UVC_XU_FIRMWARE_CONTROL (408)
#define BUTTON_VIDEO_UVC_XU_MMC_CONTROL (409)
#define BUTTON_VIDEO_UVC_XU_SWITCH_MSDC_MODE (410)
#endif
#define BUTTON_MSDC_SCSI_CMD_SWITCH_UVC_MODE (411)

/*
Below is reserved for wireless messages,all UI defined events don't exceed it!
It means the legnth of wireless messages is limited by 4096 
*/
#define WIRELESS_MESSAGE_START (0x7ffff000)

typedef void (*AHC_EVENT_HANDLER)(UINT32 ulEvent);
void _RegisterEventCb(UINT32 _a, AHC_EVENT_HANDLER _b);
#define RegisterEventCb(a, b) _RegisterEventCb(a, b)

typedef void (*AHC_NET_EVENT_HANDLER)(UINT32 ulEvent, UINT32 ulParam);
void uiStateRegisterNetEventHandler(UINT32 ulFunc, AHC_NET_EVENT_HANDLER pfEventHandler);
/// A callback function from UI task which handling global network events.
typedef AHC_BOOL (*UI_GLOBAL_EVENT_HANDLER)( UINT32 pulMsgId, UINT32* pulEvent , UINT32* pulParam );
void uiStateRegisterGlobalNetEventHandler(UI_GLOBAL_EVENT_HANDLER pfEventHandler);
void uiStateRegisterCommonCgiHandlers(void);
typedef UINT32 (*UI_KEYPARSER_FUNC)(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
UINT32 uiStateNetProcessMsg(UI_KEYPARSER_FUNC keyParser, UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);

//==== Debugging Options ====
#define DBG_UI_NET_EVENT (0) //turn on detailed debugging messages. Default is 0
/* enable this to assert that EventID for network is always != 0.
 * Typically if ulEvent == 0, it means the message is routed wrong.
 * Default is 0 */
#define ASSERT_UI_NET_EVENT (0)


//==== Feature Options and Fixes ====

/* FIXME To be reviewed. The target is to remove this define in case (1).
 * Enable this so that it would use common transit mode code */
#define CR_USE_STATE_SWITCH_SUB_MODE (1)


/* FIXME To be reviewed. The target is to remove this define in case (1).
 * Enable this so that any CGI will pass record and capture to parent mode.
 * This would fix capture and record under CGI.
 * The streaming mode already supports this. */
#define CR_FIX_CGI_REC_CAPTURE (1)

/* FIXME To be reviewed. The target is to remove this define in case (1).
 * In the future, the AHLM_NET and AHLM_CONNECT will be separated.
 * AHLM_CONNECT is mainly for WIFI connection info, which should be global processing.
 * AHLM_NET is mainly for Network UI Notification, but with key parser bypassing the translation from
 * BUTTON_ to EVENT_. This would simplify the message routing and avoid extra key mapping. */
#define CR_SUPPORT_VID_REC_NET_MSG_ROUTE (1)


//==== End of Review ===

/*===========================================================================
 * Enum define
 *===========================================================================*/

/*===========================================================================
 * Structure define
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/

UINT32      MenuButtonToMenuOp(UINT32 ulEvent ,UINT32 ulPosition);
AHC_BOOL    StateSwitchMode(UI_STATE_ID mState);
void        uiStateSystemStart(void);
void        uiStateMachine( UINT32 ulMsgId, UINT32 ulEvent ,UINT32 ulParam );
void        uiStateSetLocked(AHC_BOOL bLock);
UINT8       uiGetCurrentState(void);
void        uiSaveCurrentState(void);
UINT8       uiGetLastState(void);

void        AHC_DCF_Init(void);
void        uiPowerOffPicture(void);
void        uiCheckDefaultMenuExist(void);
void        StateLedControl( UINT32 uiMode );

/* Text Menu setting */
#define MENU_FILTER_NONE            0           /* not allow to set all of reserved */
#define MENU_FILTER_DATETIME        1           /* allow to set date/time as enabled */
#define MENU_FILTER_ALL             0xffffffff  /* allow all of setting */

#define POST_DELETE                 2
#define POST_RENAME                 3

#define     TXT_NO_COMMENT          0
#define     TXT_COMMENT             1
#define     TXT_VERSION             2
#define     TXT_MENU_ACT            0
#define     TXT_MENU_ALL            4

int         ParseMenuSet(char *file, MenuInfo* pmi /*out*/, int fliter /* MENU_FILTER_** */);
int         ParseDateTime(char *dt, int format, unsigned short *y, unsigned short *m, unsigned short *d,
                          unsigned short *hh, unsigned short *mm, unsigned short *ss);
AHC_BOOL    ImportMenuInfo(MenuInfo *pmi);
AHC_BOOL    ExportMenuAtom(char *file, int flag);
AHC_BOOL    ApplyUserTextSetting(char *file, MenuInfo* pmi);
int         Getfp_VideoTime(void);
int         Getfp_ResetTime(void);

#define IN_MENU()   (GetCurrentMenu() != NULL)

UINT32 MenuStateExecutionCommon( UINT32 ulEvent, UINT32 ulPosition);
UINT32 MenuStateHandlerCommon(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
//void   STATE_COMMON_DROP_EVENT(UINT32 ulEvent, UINT32 ulParam);
DECL_AHC_EV_HANDLER(STATE_COMMON_DROP_EVENT);
void    uiSetWorkingState(UINT8 uWorkingState);
UINT8   uiGetWorkingState(void);

AHC_BOOL StateModeFindState(UI_STATE_ID sState,  UI_STATE_ID sWantedState);
void   StateModeGetParent(UI_STATE_ID sState, UI_STATE_ID *psParentState);
AHC_BOOL StateModeSetOperation(UINT8 mState, pfFunc pfInit, pfFunc pfShutDown, pfHandlerFunc pfHandler);
AHC_BOOL StateModeDoHandler(UI_STATE_ID sState, UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
AHC_BOOL StateModeDoHandlerEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
void StateLCDCheckStatus(UINT8 mode);
#if CR_USE_STATE_SWITCH_SUB_MODE
void _StateReplaceSubMode(UI_STATE_ID mState, const char *funcName, UINT32 line);
#define StateReplaceSubMode(mState) _StateReplaceSubMode(mState, __FUNCTION__, __LINE__)
#endif
AHC_BOOL StateAttachSubMode(UI_STATE_ID mState);
AHC_BOOL StateSelectPBFunc(UINT8 ubUIMode);
AHC_BOOL StateDetachSubMode(void);
AHC_BOOL StateDetachWorkingSubMode(UI_STATE_ID mState);
#define StateDettachSubMode StateDetachSubMode

void CheckRtcAndAutoSetRtc(void);

#endif //_AHC_MENU_H_
