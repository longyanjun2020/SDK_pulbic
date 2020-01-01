///@file ahc_menu.h Menu header for each project.
//==============================================================================
//
//  File        : ahc_menu_inc.h
//  Description : INCLUDE File for the AHC Menu function porting.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_MENU_INC_H_
#define _AHC_MENU_INC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
////Do not include other files in xxx_inc.h

/*===========================================================================
 * Macro define
 *===========================================================================*/
//Use this macro in case the interface changes
#define DECL_AHC_EV_HANDLER(h) void h(UINT32 ulEvent)

/*===========================================================================
 * Enum define
 *===========================================================================*/
typedef enum _UI_STATE_ID
{
    //The followings are used as UI state
    UI_CAMERA_STATE           ,
    UI_VIDEO_STATE            ,
    UI_BROWSER_STATE          ,
    UI_PLAYBACK_STATE         ,
    UI_SLIDESHOW_STATE        ,
    UI_MSDC_STATE             ,
    UI_POWERON_SET            ,
    UI_SD_UPDATE_STATE        ,
    UI_VIDEO_RECORD_STATE,  // Touch Panel project
    UI_PCCAM_STATE            ,
    UI_CAMERA_BURST_STATE     ,
    UI_TIME_LAPSE_STATE       ,
    UI_CAMERA_SETTINGS_STATE  ,
    UI_NET_PLAYBACK_STATE, //WIFI_PORT == 1
    UI_NET_FWUPDATE_STATE, //WIFI_PORT == 1
    //The followings are used as UI sub-mode
    UI_CAMERA_MENU_STATE      ,
    UI_VIDEO_MENU_STATE       ,
    UI_PLAYBACK_MENU_STATE    ,
    UI_EDIT_TOOL_MENU_STATE   ,
    UI_CLOCK_SETTING_STATE    ,
    UI_MODESELECT_MENU_STATE  ,
    UI_USBSELECT_MENU_STATE   ,
    UI_BROWSELECT_MENU_STATE  ,
    UI_NET_CGICMD_STATE, //WIFI_PORT == 1
    UI_NET_STREAMING_STATE, //WIFI_PORT == 1

    UI_STATE_UNSUPPORTED,

    UI_STATE_NUM
}UI_STATE_ID;

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef struct _UI_STATE_INFO
{
    UI_STATE_ID        CurrentState;
    UI_STATE_ID        WorkingState;
    UI_STATE_ID        LastState;
    AHC_BOOL           bModeLocked;///< true means the state of state machine is locked and we can not change the state by
}UI_STATE_INFO;

typedef AHC_BOOL (*pfFunc)(void*);
typedef UINT32 (* pfHandlerFunc) (UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);

typedef struct _UI_STATE_OP{
    UI_STATE_ID sParentUIState;

    pfFunc pfInitFunc;
    pfFunc pfShutDownFunc;
    pfHandlerFunc pfUIStateHandlerFunc;
} UI_STATE_OP;
/*===========================================================================
 * Function prototype
 *===========================================================================*/

#endif //_AHC_MENU_INC_H_
