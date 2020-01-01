
/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_common.h"
#include "ahc_display.h"
#include "ahc_general_cardv.h"
#include "MenuCommon.h"
#include "MenuDrawingFunc.h"
#include "keyparser.h"
#include "ledcontrol.h"
#include "IconPosition.h"
#include "dsc_charger.h"

#include "statecamerafunc.h"
#include "statevideofunc.h"
#include "statebrowserfunc.h"
#include "statemoviepbfunc.h"
#include "statephotopbfunc.h"
#include "stateslideshowfunc.h"
#include "statemsdcfunc.h"
#include "statehdmifunc.h"
#include "statetvfunc.h"
#include "statenetplaybackfunc.h"

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "netapp.h"
#include "ahc_stream.h"
#endif

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern AHC_BOOL PowerOff_InProcess;
extern AHC_BOOL Deleting_InBrowser;
extern AHC_BOOL Delete_File_Confirm;
extern AHC_BOOL Protecting_InBrowser;
extern AHC_BOOL Protect_File_Confirm;
extern AHC_BOOL UnProtect_File_Confirm;
//extern AHC_BOOL bForceSwitchBrowser;
extern AHC_BOOL bForce_PowerOff;
extern UINT8    ssFileType;
extern AHC_BOOL PowerOff_Option;
extern AHC_BOOL bRefreshBrowser;
extern AHC_BOOL m_ubParkingModeRecTrigger;
extern AHC_BOOL gbAhcDbgBrk;
/*===========================================================================
 * Extern function
 *===========================================================================*/

extern AHC_BOOL VideoFunc_GetRecordStatus(void);
extern AHC_BOOL VideoFunc_GPSPageStatus(void);
extern AHC_BOOL HDMIFunc_IsPreview(void);
extern AHC_BOOL HDMIFunc_IsPlayback(void);
//extern AHC_BOOL TVFunc_IsPreview(void);

/*===========================================================================
 * Main Body
 *===========================================================================*/

#if 0
void ________KeyEvent_Function_________(){ruturn;} //dummy
#endif

UINT32 KeyParser_CheckBrowserOkButton( UINT32 button )
{
    UINT32  retEvent = EVENT_THUMBNAIL_KEY_PLAYBACK;

    if(button == KEY_PRESS_REC||button == KEY_REL_REC)
    {
        if((Protecting_InBrowser==2)||(Protecting_InBrowser==1)||(Deleting_InBrowser))
        {
            if(button == KEY_REL_REC)
            {
                retEvent = EVENT_THUMBNAIL_KEY_EDIT_CONFIRM;
            }
            else if(button == KEY_PRESS_REC)
            {
                retEvent = EVENT_NONE;
            }
        }
    }

    return retEvent;
}

#if (USB_MODE_SELECT_EN)
UINT32 KeyParser_USBModeSelectEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
    switch( ulEvent ){
        case BUTTON_NONE           :     return EVENT_NONE;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;

        //case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        //case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        //case BUTTON_DC_CABLE_IN    :   return EVENT_DC_CABLE_IN;
        //case BUTTON_DC_CABLE_OUT   :   return EVENT_DC_CABLE_OUT;

        default                    :     return EVENT_NONE;
    }
}
#endif

UINT32 KeyParser_VideoRecEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
    //if((ulEvent != BUTTON_UPDATE_MESSAGE)&&(ulEvent != BUTTON_UPDATE_CHARGE_ICON)){
    //    printc("[Event:%x,%x,%x]\r\n",ulMsgId, ulEvent, ulParam);
    //}

#if defined(WIFI_PORT) && (WIFI_PORT == 1) && CR_SUPPORT_VID_REC_NET_MSG_ROUTE
    // Add these lines to enable NET message bypassing
    if (ulMsgId == AHLM_NET) {
        return ulEvent;
    }
#endif
    switch( ulEvent )
    {

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
        case BUTTON_NET_DOWNLOAD   :     return EVENT_NET_DOWNLOAD;
        case BUTTON_FUNC3_REL:      return EVENT_WIFI_SWITCH_ENABLE;
#endif
        case BUTTON_NONE           :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

#if (VIDEO_DIGIT_ZOOM_EN) // Video Recording With Zoom Test
        case BUTTON_UP_LPRESS      :
        case BUTTON_UP_PRESS       :     return EVENT_KEY_TELE_PRESS;
        case BUTTON_UP_LREL        :
        case BUTTON_UP_REL         :     return EVENT_KEY_TELE_STOP;

        case BUTTON_DOWN_LPRESS    :
        case BUTTON_DOWN_PRESS     :     return EVENT_KEY_WIDE_PRESS;
        case BUTTON_DOWN_LREL      :
        case BUTTON_DOWN_REL       :     return EVENT_KEY_WIDE_STOP;
#endif

        case BUTTON_SOS_REL        :     return (VideoFunc_GetRecordStatus())?(EVENT_LOCK_VR_FILE):(EVENT_SWITCH_VMD_MODE);
        case BUTTON_SOS_LPRESS     :     return EVENT_WIFI_SWITCH_TOGGLE;

        //GPIO Key
        case BUTTON_SET_PRESS      :     return EVENT_KEY_SET;

        // Link with KEY_VIDEO_RECORD
        case BUTTON_REC_REL        :
            return (AHC_IsHdmiConnect())? (EVENT_NONE):(EVENT_VIDEO_KEY_RECORD);

        // Link with KEY_VIDEO_CAPTURE
        case BUTTON_REC_LPRESS     :     return (AHC_IsHdmiConnect())? (EVENT_NONE):(EVENT_VIDEO_KEY_CAPTURE);

        case BUTTON_MENU_REL       :     return (VideoFunc_GetRecordStatus()||uiGetParkingModeEnable())?(EVENT_NONE):(EVENT_KEY_MENU);
        case BUTTON_MENU_LPRESS    :     return EVENT_PARKING_KEY;

        case BUTTON_MODE_REL       :     return (VideoFunc_GetRecordStatus())?(EVENT_LOCK_VR_FILE):(EVENT_KEY_MODE);
        case BUTTON_MODE_LPRESS    :     return EVENT_SWITCH_WIFI_STREAMING_MODE;
        case BUTTON_MUTE_REL       :     return EVENT_RECORD_MUTE;
        case BUTTON_MUTE_LPRESS    :     return EVENT_LCD_POWER_SAVE;
        case BUTTON_POWER_LPRESS   :     return EVENT_POWER_OFF;
        case BUTTON_POWER_REL      :     return EVENT_SHOW_GPS_INFO;
        case BUTTON_UP_LPRESS      :     return EVENT_VIDEO_KEY_SWAP_PIP;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;

        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :     return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :     return EVENT_DC_CABLE_OUT;

        case BUTTON_CUS_SW1_ON     :     return EVENT_CUS_SW1_ON;
        case BUTTON_CUS_SW1_OFF    :     return EVENT_CUS_SW1_OFF;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        #if (AHC_EMERGENTRECD_SUPPORT)
        case BUTTON_LOCK_FILE_G    :
            if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE)
                return EVENT_LOCK_FILE_G;
            else
                return EVENT_VR_EMERGENT;
        #endif

        #if AHC_SHAREENC_SUPPORT
        case BUTTON_REC_SHORT      :     return EVENT_VR_SHORT;
        #endif

        //Update Message
        case BUTTON_UPDATE_FILE    :     //return EVENT_SLIDESHOW_UPDATE_FILE;
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE:     return EVENT_VIDREC_UPDATE_MESSAGE;
        case BUTTON_TIMESTAMP_UPDATE:   return EVENT_TIMESTAMP_UPDATE;

        //Record Callback
        case BUTTON_VRCB_MEDIA_FULL:    return EVENT_VRCB_MEDIA_FULL;
        case BUTTON_VRCB_FILE_FULL :     return EVENT_VRCB_FILE_FULL;
        case BUTTON_VRCB_LONG_TIME_FILE_FULL :  return EVENT_VRCB_LONG_TIME_FILE_FULL;
        case BUTTON_VRCB_MEDIA_SLOW:     return EVENT_VRCB_MEDIA_SLOW;
        case BUTTON_VRCB_MEDIA_ERROR:    return EVENT_VRCB_MEDIA_ERROR;
        case BUTTON_VRCB_SEAM_LESS :     return EVENT_VRCB_SEAM_LESS;
        case BUTTON_VRCB_MOTION_DTC:     return EVENT_VRCB_MOTION_DTC;
        case BUTTON_VRCB_VR_START  :     return EVENT_VR_START;
        case BUTTON_VRCB_VR_STOP   :     return EVENT_VR_STOP;
        case BUTTON_VRCB_VR_POSTPROC:    return EVENT_VR_WRITEINFO;
        case BUTTON_VRCB_EMER_DONE  :    return EVENT_VRCB_EMER_DONE;
        case BUTTON_VRCB_RECDSTOP_CARDSLOW:     return EVENT_VRCB_RECDSTOP_CARDSLOW;
        case BUTTON_VRCB_PREVIEW_ERR:    return EVENT_VRCB_PREVIEW_ERROR;
        case BUTTON_VRCB_SHARE_FILE_FULL:   return EVENT_VRCB_SHARE_FILE_FULL;

        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;

        #if (POWER_ON_BUTTON_ACTION)
        case BUTTON_POWER_ON_MENU  :     return EVENT_SHOW_FW_VERSION;
        case BUTTON_POWER_ON_MODE  :     return EVENT_FORMAT_RESET_ALL;
        case BUTTON_POWER_ON_REC   :     return EVENT_NONE;
        case BUTTON_POWER_ON_PLAY  :     return EVENT_NONE;
        #endif
        case BUTTON_LDWS_START:
            #if (ENABLE_ADAS_LDWS)
            return EVENT_LDWS_START;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_LDWS_STOP:
            #if (ENABLE_ADAS_LDWS)
            return EVENT_LDWS_STOP;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_FCWS_START:
            #if (ENABLE_ADAS_FCWS)
            return EVENT_FCWS_START;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_FCWS_STOP:
            #if (ENABLE_ADAS_FCWS)
            return EVENT_FCWS_STOP;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_ADAS_WRITE_LOG :
            return EVENT_ADAS_WRITE_LOG;
        case BUTTON_SAG_START:
            #if (ENABLE_ADAS_SAG)
            return EVENT_SAG_START;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_SAG_STOP:
            #if (ENABLE_ADAS_SAG)
            return EVENT_SAG_STOP;
            #else
            return EVENT_NONE;
            #endif
        case BUTTON_FUNC1_PRESS     :
            return EVENT_VIDEO_KEY_SWAP_PIP;
        break;
        case BUTTON_FUNC2_PRESS     :
            return EVENT_VIDEO_KEY_SEND_FILE;
        break;
        case BUTTON_TV_DECODER_SRC_TYPE   :
            return EVENT_TV_DECODER_SRC_TYPE;
        break;
        case BUTTON_SUB_MODE_ENTER:
            return EVNET_SUB_MODE_ENTER;
            break;
        case BUTTON_SUB_MODE_EXIT:
            return EVNET_SUB_MODE_EXIT;
            break;
        case BUTTON_EV_MODIFY:
            return EVENT_EV_MODIFY;
            break;
        case BUTTON_MENU_EXIT:
            return EVENT_MENU_EXIT;
            break;

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE)
        case BUTTON_VIDEO_UVC_XU_RECORDTIME_CONTROL:
            return EVENT_VIDEO_UVC_XU_RECORDTIME_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_RECORDRES_CONTROL:
            return EVENT_VIDEO_UVC_XU_RECORDRES_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_FILE_CONTROL:
            return EVENT_VIDEO_UVC_XU_FILE_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_PICTURE_CONTROL:
            return EVENT_VIDEO_UVC_XU_PICTURE_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_GSENSOR_CONTROL:
            return EVENT_VIDEO_UVC_XU_GSENSOR_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_AUDIO_CONTROL:
            return EVENT_VIDEO_UVC_XU_AUDIO_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_STATUS_CONTROL:
            return EVENT_VIDEO_UVC_XU_STATUS_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_REC_MODE_CONTROL:
            return EVENT_VIDEO_UVC_XU_REC_MODE_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_FIRMWARE_CONTROL:
            return EVENT_VIDEO_UVC_XU_FIRMWARE_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_MMC_CONTROL:
            return EVENT_VIDEO_UVC_XU_MMC_CONTROL;
            break;
        case BUTTON_VIDEO_UVC_XU_SWITCH_MSDC_MODE:
            return EVENT_VIDEO_UVC_XU_SWITCH_MSDC_MODE;
            break;
#endif

        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_CaptureEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{

    switch( ulEvent )
    {

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    #endif
        case BUTTON_NONE           :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

#if (DSC_DIGIT_ZOOM_ENABLE)
        case BUTTON_UP_PRESS       :     return EVENT_KEY_TELE_PRESS;
        case BUTTON_DOWN_PRESS     :     return EVENT_KEY_WIDE_PRESS;
        case BUTTON_UP_REL         :     return EVENT_KEY_TELE_STOP;
        case BUTTON_DOWN_REL       :     return EVENT_KEY_WIDE_STOP;
#else
        case BUTTON_UP_PRESS       :     return EVENT_NONE;
        case BUTTON_DOWN_PRESS     :     return EVENT_NONE;
        case BUTTON_UP_REL         :     return EVENT_NONE;
        case BUTTON_DOWN_REL       :     return EVENT_NONE;
#endif
        // Link with KEY_DSC_CAPTURE
        case BUTTON_REC_REL        :     return EVENT_DSC_KEY_CAPTURE;

        case BUTTON_MENU_REL       :     return EVENT_KEY_MENU;
        case BUTTON_MODE_REL       :     return EVENT_KEY_MODE;
//      case BUTTON_MUTE_REL       :     return EVENT_NONE;
//      case BUTTON_MUTE_LPRESS    :     return EVENT_LCD_POWER_SAVE;
        case BUTTON_POWER_LPRESS   :     return EVENT_POWER_OFF;
        case BUTTON_UP_LPRESS      :     return EVENT_DSC_KEY_SWAP_PIP;

        case BUTTON_SOS_REL        :     return EVENT_SWITCH_VMD_MODE;
        case BUTTON_SOS_LPRESS     :     return EVENT_SWITCH_TIME_LAPSE_EN;

        case BUTTON_SET_PRESS      :     return EVENT_DSC_KEY_CHANGE_SHOT_MODE;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :     return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :     return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Callback
        case BUTTON_VRCB_MOTION_DTC:     return EVENT_VRCB_MOTION_DTC;

        //Update Message
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_DSC_KEY_UPDATE_MESSAGE;
        case BUTTON_TIMESTAMP_UPDATE :  return EVENT_TIMESTAMP_UPDATE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;

        case BUTTON_SUB_MODE_ENTER:
            return EVNET_SUB_MODE_ENTER;
            break;

        case BUTTON_SUB_MODE_EXIT:
            return EVNET_SUB_MODE_EXIT;
            break;
        case BUTTON_MENU_EXIT:
            return EVENT_MENU_EXIT;
            break;

        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_ThumbnailEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
    switch( ulEvent )
    {
    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    #endif
        case BUTTON_NONE           :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

#if (DIR_KEY_TYPE == KEY_TYPE_4KEY)
        case BUTTON_UP_LPRESS      :     return EVENT_KEY_UP;
        case BUTTON_UP_PRESS       :     return EVENT_KEY_UP;
        case BUTTON_DOWN_LPRESS    :     return EVENT_KEY_DOWN;
        case BUTTON_DOWN_PRESS     :     return EVENT_KEY_DOWN;
#else
        case BUTTON_UP_LPRESS      :     return EVENT_KEY_LEFT;
        case BUTTON_UP_PRESS       :     return EVENT_KEY_LEFT;
        case BUTTON_DOWN_LPRESS    :     return EVENT_KEY_RIGHT;
        case BUTTON_DOWN_PRESS     :     return EVENT_KEY_RIGHT;
#endif

        case BUTTON_LEFT_LPRESS    :     return EVENT_KEY_LEFT;
        case BUTTON_LEFT_PRESS     :     return EVENT_KEY_LEFT;
        case BUTTON_RIGHT_LPRESS   :     return EVENT_KEY_RIGHT;
        case BUTTON_RIGHT_PRESS    :     return EVENT_KEY_RIGHT;
        case BUTTON_REC_REL        :     return KeyParser_CheckBrowserOkButton(ulEvent);

        //GPIO Key
        //case BUTTON_REC_PRESS      :     return KeyParser_CheckBrowserOkButton(ulEvent);
        case BUTTON_REC_PRESS      :     return EVENT_NONE;
        case BUTTON_SET_PRESS      :     return EVENT_THUMBNAIL_KEY_PLAYBACK;
        case BUTTON_MENU_REL       :     return EVENT_KEY_MENU;
        case BUTTON_MENU_LPRESS    :     return EVENT_MOVPB_MODE;
        case BUTTON_MODE_REL       :     return EVENT_KEY_MODE;
        case BUTTON_MODE_LPRESS    :     return EVENT_NONE;
        case BUTTON_MUTE_REL       :     return EVENT_NONE;
        case BUTTON_MUTE_LPRESS    :     return EVENT_NONE;
        case BUTTON_POWER_LPRESS   :     return EVENT_POWER_OFF;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :     return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :     return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_UPDATE_FILE    :     return EVENT_SLIDESHOW_UPDATE_FILE;
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_THUMBNAIL_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;

        case BUTTON_SUB_MODE_ENTER:
            return EVNET_SUB_MODE_ENTER;
            break;

        case BUTTON_SUB_MODE_EXIT:
            return EVNET_SUB_MODE_EXIT;
            break;

        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_JpgPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{

    switch( ulEvent )
    {

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    #endif
        case BUTTON_NONE           :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

        case BUTTON_UP_PRESS       :     return EVENT_KEY_LEFT;//EVENT_JPGPB_TOUCH_PREV_PRESS;
        case BUTTON_DOWN_PRESS     :     return EVENT_KEY_RIGHT;//EVENT_JPGPB_TOUCH_NEXT_PRESS;
        //case BUTTON_LEFT_PRESS   :     return EVENT_KEY_UP;
        //case BUTTON_RIGHT_PRESS  :     return EVENT_KEY_DOWN;

        //GPIO Key
        case BUTTON_REC_PRESS      :     return EVENT_NONE;
        case BUTTON_MENU_REL       :     return EVENT_KEY_MENU;
        case BUTTON_MENU_LPRESS    :     return EVENT_NONE;
        case BUTTON_MODE_REL       :     return EVENT_KEY_MODE;//EVENT_JPGPB_TOUCH_RETURN;
        case BUTTON_MODE_LPRESS    :     return EVENT_NONE;
        case BUTTON_MUTE_REL       :     return EVENT_NONE;
        case BUTTON_MUTE_LPRESS    :     return EVENT_NONE;
        case BUTTON_POWER_LPRESS   :     return EVENT_POWER_OFF;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :     return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :     return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_JPGPB_UPDATE_MESSAGE;
        case BUTTON_UPDATE_LCD     :     return EVENT_JPGPB_UPDATE_LCD;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;

        case BUTTON_SUB_MODE_ENTER:
            return EVNET_SUB_MODE_ENTER;
            break;

        case BUTTON_SUB_MODE_EXIT:
            return EVNET_SUB_MODE_EXIT;
            break;

        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_MovPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{

    switch( ulEvent )
    {

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    #endif

        case BUTTON_NONE           :     return EVENT_NONE;
#if (SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_PRESS    :     return AhcCheckTouchButton( &ulParam,  AHC_FALSE );
        case BUTTON_TOUCH_MOVE     :     return AhcCheckTouchButton( &ulParam,  AHC_TRUE);
#endif

        case BUTTON_UP_PRESS       :     return EVENT_KEY_LEFT;//EVENT_MOVPB_TOUCH_BKWD_PRESS;
        case BUTTON_DOWN_PRESS     :     return EVENT_KEY_RIGHT;//EVENT_MOVPB_TOUCH_FRWD_PRESS;

        //GPIO Key
        case BUTTON_REC_PRESS      :     return EVENT_MOVPB_PLAY_START;//EVENT_MOVPB_TOUCH_PLAY_PRESS;
        case BUTTON_SET_PRESS      :     return EVENT_MOVPB_PLAY_START;//EVENT_MOVPB_TOUCH_PLAY_PRESS;
        case BUTTON_MENU_REL       :     return EVENT_KEY_MENU;
        case BUTTON_MENU_LPRESS    :     return EVENT_NONE;//EVENT_MOVPB_MODE;
        case BUTTON_MODE_REL       :     return EVENT_MOVPB_MODE;//EVENT_MOVPB_TOUCH_RETURN;
        case BUTTON_MODE_LPRESS    :     return EVENT_NONE;
        case BUTTON_MUTE_REL       :     return EVENT_NONE;
        case BUTTON_MUTE_LPRESS    :     return EVENT_NONE;
        case BUTTON_POWER_LPRESS   :     return EVENT_POWER_OFF;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :     return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :     return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_MOVPB_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_OSD_HIDE       :     return EVENT_SLIDESHOW_OSD_HIDE;
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;

        case BUTTON_SUB_MODE_ENTER:
            return EVNET_SUB_MODE_ENTER;
            break;

        case BUTTON_SUB_MODE_EXIT:
            return EVNET_SUB_MODE_EXIT;
            break;

        default                    :     return EVENT_NONE;
    }
}

UINT32 KeyParser_AudPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
#if (AUDIO_REC_PLAY_EN)

    UINT32 LCDstatus;

    AHC_GetParam(PARAM_ID_LCD_STATUS,&LCDstatus);

    switch( ulEvent )
    {

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case AHLM_WIRELESS_CONNECT:
        switch( ulEvent )
        {
        #ifdef NET_SYNC_PLAYBACK_MODE
            case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
        #endif
        }
        break;
    #endif

        case BUTTON_NONE           :     return EVENT_NONE;

        //ADC Key
        case BUTTON_UP_PRESS       :     return EVENT_KEY_UP;
        case BUTTON_DOWN_PRESS     :     return EVENT_KEY_DOWN;
        case BUTTON_UP_REL         :     return EVENT_KEY_TELE_STOP;
        case BUTTON_DOWN_REL       :     return EVENT_KEY_WIDE_STOP;
        case BUTTON_LEFT_PRESS     :     return EVENT_MOVPB_TOUCH_BKWD_PRESS;
        case BUTTON_RIGHT_PRESS    :     return EVENT_MOVPB_TOUCH_FRWD_PRESS;
        case BUTTON_SET_PRESS      :     return EVENT_MOVPB_PLAY_START;//EVENT_MOVPB_TOUCH_PLAY_PRESS;

        //GPIO Key
        case BUTTON_MENU_REL       :     return EVENT_KEY_MENU;
        case BUTTON_MODE_REL       :     return EVENT_MOVPB_MODE;//EVENT_MOVPB_TOUCH_RETURN;
        case BUTTON_REC_PRESS          :     return EVENT_MOVPB_PLAY_START;//EVENT_MOVPB_TOUCH_PLAY_PRESS;
        case BUTTON_POWER_LPRESS   :     return EVENT_POWER_OFF;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_NONE;
        case BUTTON_DC_CABLE_IN    :     return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :     return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_MOVPB_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;

        case BUTTON_SUB_MODE_ENTER:
            return EVNET_SUB_MODE_ENTER;
            break;

        case BUTTON_SUB_MODE_EXIT:
            return EVNET_SUB_MODE_EXIT;
            break;

        default                    :     return EVENT_NONE;
    }
#endif

    return EVENT_NONE;
}

UINT32 KeyParser_MsdcEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{

    switch( ulEvent )
    {

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    #endif

        case BUTTON_NONE           :     return EVENT_NONE;

        //ADC Key
        case BUTTON_UP_PRESS       :     return EVENT_NONE;
        case BUTTON_DOWN_PRESS     :     return EVENT_NONE;

        //GPIO Key
        case BUTTON_REC_PRESS      :     return EVENT_NONE;
        case BUTTON_MENU_REL       :     return EVENT_NONE;
        case BUTTON_MENU_LPRESS    :     return EVENT_NONE;
        case BUTTON_MODE_REL       :     return EVENT_NONE;
        case BUTTON_MODE_LPRESS    :     return EVENT_NONE;
        case BUTTON_MUTE_REL       :     return EVENT_NONE;
        case BUTTON_MUTE_LPRESS    :     return EVENT_NONE;
        case BUTTON_POWER_LPRESS   :     return EVENT_POWER_OFF;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_DC_CABLE_IN    :     return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :     return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Update Message
        case BUTTON_UPDATE_MESSAGE :     return EVENT_MSDC_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;

        case BUTTON_SUB_MODE_ENTER:
            return EVNET_SUB_MODE_ENTER;
            break;

        case BUTTON_SUB_MODE_EXIT:
            return EVNET_SUB_MODE_EXIT;
            break;

#if defined(MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) && (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD)
        case BUTTON_MSDC_SCSI_CMD_SWITCH_UVC_MODE:
            return EVENT_MSDC_SCSI_CMD_SWITCH_UVC_MODE;
#endif

        default                    :     return EVENT_NONE;
    }
}


UINT32 KeyParser_ClockSettingEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{

    switch( ulEvent )
    {

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
    #endif
        case BUTTON_USB_DETECTED: return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED : return EVENT_USB_REMOVED;

        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;

#if (TVOUT_ENABLE)
        case BUTTON_TV_DETECTED : return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED  : return EVENT_TV_REMOVED;
#endif
#if (HDMI_ENABLE)
        case BUTTON_HDMI_DETECTED   : return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED    : return EVENT_HDMI_REMOVED;
#endif

        default                    :     return EVENT_NONE;
    }
}

#if 0
void ________NetEvent_Function_________(){ruturn;} //dummy
#endif

#if 1 //Andy Liu TBD.
UINT32 KeyParser_NetStreaming2ParentEvent(UINT32 *pulMsgId, UINT32 *pulEvent, UINT32 *pulParam)
{
   AHC_MODE_ID mode = AHC_GetAhcSysMode();

    *pulMsgId = AHLM_UI_NOTIFICATION;

    switch( *pulEvent ){

        case WIRELESS_RECORD:
            printc("=====> WIRELESS_RECORD currentmode=0x%X\r\n",mode);
            if(mode == AHC_MODE_VIDEO_RECORD || mode == AHC_MODE_RECORD_PRERECD || mode == AHC_MODE_RECORD_PREVIEW)
               *pulEvent = BUTTON_REC_REL;

            //*pulParam = *pulParam;
            break;

        case WIRELESS_CAPTURE:
            printc("=====> WIRELESS_CAPTURE currentmode=0x%X\r\n",mode);
            if(mode == AHC_MODE_VIDEO_RECORD || mode == AHC_MODE_RECORD_PRERECD || mode == AHC_MODE_RECORD_PREVIEW){
                *pulEvent = BUTTON_REC_LPRESS;
            }
            else if(mode == AHC_MODE_CAPTURE_PREVIEW){
                *pulEvent = BUTTON_REC_REL;
            }else{

            }

            //*pulParam = *pulParam;
            break;
        case WIRELESS_REC_EMERGENCY:
            printc("=====> WIRELESS_REC_EMERGENCY\r\n");
            *pulEvent = KEYPAD_NONE;//TBD
            //*pulParam = *pulParam;
            break;
        case WIRELESS_REC_SHORT:
            printc("=====> WIRELESS_REC_SHORT\r\n");
            *pulEvent = BUTTON_REC_SHORT;//TBD
            //*pulParam = *pulParam;
            break;

        default:
            //NOP
            break;
    }

    return 0;
}

UINT32 KeyParser_NetStreamingEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    switch( ulMsgId ){
        case AHLM_NET:
            switch( ulEvent ){
                case WIRELESS_SET_UIMODE :
                    return ulEvent;
            }
            return WIRELESS_NOT_NET_EVENT;
        case AHLM_WIRELESS_CONNECT:
            switch( ulEvent ){
                case WIRELESS_SET_STREAMING_MODE:
                case WIRELESS_SET_FLICKER:
                case WIRELESS_SET_AWB:
                case WIRELESS_SET_EV:
                case WIRELESS_SET_MOT:
                case WIRELESS_SET_MOVIE_SIZE:
                case WIRELESS_SET_CLIP_TIME:
                case WIRELESS_SET_VQUALITY:
                case WIRELESS_SET_IMAGE_SIZE:
                case WIRELESS_SET_POWROFF_DELAY:
                case WIRELESS_SET_AUTO_PWROFF_TIME:
                case WIRELESS_SET_MTD:
                case WIRELESS_SET_TIME_FMT:
                case WIRELESS_SET_TV_SYS:
                case WIRELESS_SET_LCD_PWRS:
                case WIRELESS_SET_PHOTOBURST:
                case WIRELESS_SET_TIMELAPSE:
                case WIRELESS_SET_UPSIDEDOWN:
                case WIRELESS_SET_SPOTMETER:
                case WIRELESS_SET_HDR:
                case WIRELESS_SET_Q_SHOT:
                case WIRELESS_SET_STATUSLIGHTS:
                case WIRELESS_SET_SOUNDINDICATOR:
                case WIRELESS_SET_POWERSAVING:
                case WIRELESS_SET_UIMODE:
                case WIRELESS_SET_LOOPINGVIDEO:
                case WIRELESS_REC_EMERGENCY:
                case WIRELESS_SET_GSENSOR_SENSITIVITY:
                case WIRELESS_SET_REC_MUTE:
                //case WIRELESS_TX_REPORT:
                    return ulEvent;
                    break;
                case WIRELESS_REC_SHORT:
                default:
                    return WIRELESS_NOT_NET_EVENT;
                    break;
            }
            break;
       case AHLM_UI_NOTIFICATION:
       case AHLM_GPIO_BUTTON_NOTIFICATION:
       case AHLM_LGPIO_BUTTON_NOTIFICATION:
       case AHLM_SGPIO_BUTTON_NOTIFICATION:
       case AHLM_ADCX_NOTIFICATION:

            //Any parking mode events must be processed by video state.
            if(ulParam == EVENT_VRCB_MOTION_DTC)
                return WIRELESS_NOT_NET_EVENT;

            switch( ulEvent )
            {
            #if defined(LOCK_KEYPAD_UNDER_WIFI_STREAMING)
                //GPIO Key
                case BUTTON_SET_PRESS       :
                case BUTTON_REC_PRESS       :
                case BUTTON_REC_REL         :
                case BUTTON_REC_LPRESS      :
                case BUTTON_MENU_REL        :
                case BUTTON_MENU_LPRESS     :
                case BUTTON_MENU_PRESS      :
                case BUTTON_MODE_REL        :
                case BUTTON_MODE_LPRESS     :
                case BUTTON_MODE_PRESS      :
                case BUTTON_MUTE_REL        :
                case BUTTON_MUTE_LPRESS     :
                case BUTTON_MUTE_PRESS      :
                case BUTTON_UP_PRESS        :
                case BUTTON_DOWN_PRESS      :
                case BUTTON_LEFT_PRESS      :
                case BUTTON_RIGHT_PRESS     :
                    return EVENT_DROP;
            #endif
                default                    :     return WIRELESS_NOT_NET_EVENT;
            }
            break;

        default:
            return WIRELESS_NOT_NET_EVENT;
            break;
    }

    return ulEvent;
}

UINT32 KeyParser_NetFWUpdateEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    //TBD
    return ulEvent;
}

UINT32 KeyParser_NetCGICmd2ParentEvent(UINT32 *pulMsgId, UINT32 *pulEvent, UINT32 *pulParam)
{
#if CR_FIX_CGI_REC_CAPTURE
    AHC_MODE_ID mode = AHC_GetAhcSysMode();
#endif

    *pulMsgId = AHLM_UI_NOTIFICATION;

    switch( *pulEvent ){

        //Convert UI event here!
        //case xxx:
        //    break;
#if CR_FIX_CGI_REC_CAPTURE
        case WIRELESS_RECORD:
            printc("=====> WIRELESS_RECORD currentmode=0x%X\r\n",mode);
            if(mode == AHC_MODE_VIDEO_RECORD || mode == AHC_MODE_RECORD_PRERECD || mode == AHC_MODE_RECORD_PREVIEW)
               *pulEvent = BUTTON_REC_REL;

            //*pulParam = *pulParam;
            break;

        case WIRELESS_CAPTURE:
            printc("=====> WIRELESS_CAPTURE currentmode=0x%X\r\n",mode);
            if(mode == AHC_MODE_VIDEO_RECORD || mode == AHC_MODE_RECORD_PRERECD || mode == AHC_MODE_RECORD_PREVIEW){
                *pulEvent = BUTTON_REC_LPRESS;
            }
            else if(mode == AHC_MODE_CAPTURE_PREVIEW){
                *pulEvent = BUTTON_REC_REL;
            }else{

            }

            //*pulParam = *pulParam;
            break;
#endif
        case WIRELESS_REC_EMERGENCY:
            printc("=====> WIRELESS_REC_EMERGENCY\r\n");
            *pulEvent = BUTTON_LOCK_FILE_G;//KEYPAD_NONE;//TBD
            //*pulParam = *pulParam;
            break;
        case WIRELESS_REC_SHORT:
            printc("=====> WIRELESS_REC_SHORT\r\n");
            *pulEvent = BUTTON_REC_SHORT;//KEYPAD_NONE;//TBD
            //*pulParam = *pulParam;
            break;

        default:
            *pulEvent = *pulEvent; //Bypass event
            break;
    }

    return 0;
}

UINT32 KeyParser_NetCGICmdEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    switch( ulMsgId ){

        case AHLM_NET:
            switch( ulEvent ){
                case WIRELESS_SET_UIMODE :
                    return ulEvent;
            }
            return WIRELESS_NOT_NET_EVENT;

        case AHLM_WIRELESS_CONNECT:
            switch( ulEvent ){

                case WIRELESS_SET_FLICKER:
                case WIRELESS_SET_AWB:
                case WIRELESS_SET_EV:
                case WIRELESS_SET_MOT:
                case WIRELESS_SET_MOVIE_SIZE:
                case WIRELESS_SET_CLIP_TIME:
                case WIRELESS_SET_VQUALITY:
                case WIRELESS_SET_IMAGE_SIZE:
                case WIRELESS_SET_POWROFF_DELAY:
                case WIRELESS_SET_AUTO_PWROFF_TIME:
                case WIRELESS_SET_MTD:
                case WIRELESS_SET_TIME_FMT:
                case WIRELESS_SET_TV_SYS:
                case WIRELESS_SET_LCD_PWRS:
                case WIRELESS_SET_PHOTOBURST:
                case WIRELESS_SET_TIMELAPSE:
                case WIRELESS_SET_UPSIDEDOWN:
                case WIRELESS_SET_SPOTMETER:
                case WIRELESS_SET_HDR:
                case WIRELESS_SET_Q_SHOT:
                case WIRELESS_SET_STATUSLIGHTS:
                case WIRELESS_SET_SOUNDINDICATOR:
                case WIRELESS_SET_POWERSAVING:
                case WIRELESS_SET_UIMODE:
                case WIRELESS_SET_LOOPINGVIDEO:
                case WIRELESS_SET_GSENSOR_SENSITIVITY:
                case WIRELESS_SET_REC_MUTE:
                    return ulEvent;
                    break;

                default:
                    return WIRELESS_NOT_NET_EVENT;
                    break;
            }
            break;

        default:
            return WIRELESS_NOT_NET_EVENT;
            break;
    }

    return ulEvent;
}
#endif

UINT32 KeyParser_NetPlaybackEvent(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
    switch( ulEvent )
    {
        case WIRELESS_CONNECT_FAIL:
            printc("=====> WIRELESS_CONNECT_FAIL\r\n");
            return EVENT_WIRELESS_CONNECT_FAIL;
        case WIRELESS_ENTER_PLAYBACK:
            printc("=====> WIRELESS_ENTER_PLAYBACK\r\n");
            return EVENT_NET_ENTER_PLAYBACK;
        case WIRELESS_EXIT_PLAYBACK:
        case EVENT_NET_EXIT_PLAYBACK:
            printc("=====> WIRELESS_EXIT_PLAYBACK\r\n");
            return EVENT_NET_EXIT_PLAYBACK;
        case WIRELESS_PLAYBACK_HEARTBEAT:
            printc("=====> WIRELESS_PLAYBACK_HEARTBEAT\r\n");
            return EVENT_NET_PLAYBACK_HEARTBEAT;
        //GPIO Key
        case BUTTON_REC_PRESS      :     return EVENT_DROP;
        case BUTTON_SET_PRESS      :     return EVENT_DROP;
        case BUTTON_MENU_REL       :     return EVENT_DROP;
        case BUTTON_MENU_LPRESS    :     return EVENT_DROP;
        case BUTTON_MODE_REL       :     return EVENT_DROP;
        case BUTTON_MODE_LPRESS    :     return EVENT_DROP;
        case BUTTON_MUTE_REL       :     return EVENT_DROP;
        case BUTTON_MUTE_LPRESS    :     return EVENT_DROP;
        case BUTTON_POWER_LPRESS   :     return EVENT_DROP;


        case BUTTON_SOS_REL        :     return EVENT_SWITCH_VMD_MODE;
        case BUTTON_SOS_LPRESS     :     return EVENT_SWITCH_TIME_LAPSE_EN;

        //Device
        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_USB_REMOVED;
        case BUTTON_USB_B_DEVICE_DETECTED   : return EVENT_USB_B_DEVICE_DETECT;
        case BUTTON_USB_B_DEVICE_REMOVED    : return EVENT_USB_B_DEVICE_REMOVED;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;
        case BUTTON_DC_CABLE_IN    :     return EVENT_DC_CABLE_IN;
        case BUTTON_DC_CABLE_OUT   :     return EVENT_DC_CABLE_OUT;

        case BUTTON_LCD_NORMAL     :     return EVENT_LCD_COVER_NORMAL;
        case BUTTON_LCD_ROTATE     :     return EVENT_LCD_COVER_ROTATE;
        case BUTTON_COVER_OPEN     :     return EVENT_LCD_COVER_OPEN;
        case BUTTON_COVER_CLOSED   :     return EVENT_LCD_COVER_CLOSE;

        //Callback
        //case BUTTON_VRCB_MOTION_DTC:     return EVENT_VRCB_MOTION_DTC;

        //Update Message
        case BUTTON_BATTERY_DETECTION:
        case BUTTON_UPDATE_MESSAGE :     return EVENT_DSC_KEY_UPDATE_MESSAGE;
        case BUTTON_CLEAR_WMSG     :     return EVENT_CLEAR_WMSG;
        case BUTTON_TV_DECODER_SRC_TYPE   : return EVENT_TV_DECODER_SRC_TYPE;
        default                    :     return EVENT_NONE;
    }
}
#if 0
void ________MenuEvent_Function_________(){ruturn;} //dummy
#endif

UINT32 MenuButtonToMenuOp(UINT32 ulEvent ,UINT32 ulPosition)
{
    switch( ulEvent ){
        case BUTTON_UPDATE_MESSAGE :    return MENU_UPDATE_MESSAGE;
#if(SUPPORT_TOUCH_PANEL)
        case BUTTON_TOUCH_MOVE     :     return MENU_TOUCH_MOVE;
        case BUTTON_TOUCH_PRESS    :      return AhcCheckTouchButton( &ulPosition,  AHC_FALSE );
        case BUTTON_TOUCH_REL      :     return MENU_TOUCH_RELEASE;
#endif

        case BUTTON_VIRTUAL_RESET  :
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_INIT);

        case BUTTON_UP_PRESS       :
        case BUTTON_UP_LPRESS      :
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_UP);
        case BUTTON_UP_REL     :
        case BUTTON_DOWN_REL       :
            return MENU_NONE;

        case BUTTON_DOWN_PRESS     :
        case BUTTON_DOWN_LPRESS    :
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_DOWN);

        case BUTTON_LEFT_PRESS       :
        case BUTTON_LEFT_LPRESS      :
#if DIR_KEY_TYPE == KEY_TYPE_4KEY
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_LEFT);
#else
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_DOWN);
#endif

        case BUTTON_RIGHT_PRESS     :
        case BUTTON_RIGHT_LPRESS    :
#if DIR_KEY_TYPE == KEY_TYPE_4KEY
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_RIGHT);
#else
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_UP);
#endif

        //case BUTTON_TV_DETECTED    :     return (PowerOff_InProcess)?(MENU_NONE):(MENU_TV_DETECT);

        case BUTTON_SET_PRESS      :
        case BUTTON_REC_PRESS      :
        case BUTTON_REC_LPRESS      :
        case BUTTON_REC_LREL        :
            return MENU_NONE;
        case BUTTON_REC_REL    :
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_OK);

        case BUTTON_MENU_REL       :
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_MENU);

        case BUTTON_MODE_REL       :
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_RIGHT);

        case BUTTON_MUTE_REL       :
            return (PowerOff_InProcess)?(MENU_NONE):(MENU_NONE);

#if (FLIP_CTRL_METHOD & CTRL_BY_KEY) && (KEY_ROTATE_OSD_SNR != BUTTON_ID_UNKNOWN)
        case KEY_ROTATE_OSD_SNR       : //No use anymore?
            {
                UINT32 LCDstatus;

                AHC_GetParam(PARAM_ID_LCD_STATUS,&LCDstatus);
                return (LCDstatus==0)?(MENU_LCD_ROTATE):(MENU_LCD_NORMAL);
            }
#endif

        //Exit menu and return to parent state.
        case KEY_POWER_OFF      :
        case BUTTON_DC_CABLE_IN:
        case BUTTON_DC_CABLE_OUT:
        //case BUTTON_USB_DETECTED   :
        //case BUTTON_USB_REMOVED    :
        case BUTTON_TV_DECODER_SRC_TYPE:
        case BUTTON_COVER_OPEN     :
        case BUTTON_COVER_CLOSED    :
        case SD_CARD_IN            :
        case SD_CARD_OUT           :

        //      case BUTTON_TV_DETECTED    :     return (PowerOff_InProcess)?(MENU_NONE):(MENU_TV_DETECT);
        //      case BUTTON_TV_REMOVED     :     return (PowerOff_InProcess)?(MENU_NONE):(MENU_TV_REMOVED);
        //      case BUTTON_HDMI_DETECTED  :     return (PowerOff_InProcess)?(MENU_NONE):(MENU_HDMI_DETECT);
        //      case BUTTON_HDMI_REMOVED   :     return (PowerOff_InProcess)?(MENU_NONE):(MENU_HDMI_REMOVED);
        //case BUTTON_TV_DETECTED    :     //return EVENT_TV_DETECT;
        //case BUTTON_TV_REMOVED     :     //return EVENT_TV_REMOVED;
        //case BUTTON_HDMI_DETECTED  :     //return EVENT_HDMI_DETECT;
        //case BUTTON_HDMI_REMOVED   :     //return EVENT_HDMI_REMOVED;

        case DEVICE_LCD_NOR        :     //return MENU_LCD_NORMAL;
        case DEVICE_LCD_INV        :     //return MENU_LCD_ROTATE;
        case BUTTON_BATTERY_DETECTION :  //return MENU_BATTERY_DETECTION;
            return MENU_EXIT;

        case BUTTON_TV_DETECTED    :     //return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     //return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     //return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     //return EVENT_HDMI_REMOVED;
        {
            if(UI_CLOCK_SETTING_STATE == uiGetCurrentState())
                return MENU_NONE;
            else
                return MENU_EXIT;
        }
        break;
        case BUTTON_USB_DETECTED   :
        case BUTTON_USB_REMOVED    :
        {
            if(UI_CLOCK_SETTING_STATE == uiGetCurrentState())
                return MENU_NONE;
            else
                return EVENT_USB_DETECT;//MENU_EXIT;
        }
            break;

        case BUTTON_USB_B_DEVICE_DETECTED:
        case BUTTON_USB_B_DEVICE_REMOVED:
        {
            if(UI_CLOCK_SETTING_STATE == uiGetCurrentState())
                return MENU_NONE;
            else
                return MENU_EXIT;
        }
        break;

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
        case WIRELESS_ENTER_PLAYBACK :
        {
            UI_STATE_ID sParentState;
            StateModeGetParent(uiGetCurrentState(), &sParentState);
            if(UI_CLOCK_SETTING_STATE == sParentState)
                return EVENT_NET_ENTER_PLAYBACK;
            else
                return MENU_EXIT;
        }
        break;
#endif

#if 0
        case xxx: //Pass to parent state.
            return MENU_NOT_MENU_EVENT;
            break;
#endif

        default:
            return MENU_NOT_MENU_EVENT; // MENU_NONE ???
            break;
    }

    return MENU_NONE;
}

#if 0
void ________GlobalEvent_Function_________(){ruturn;} //dummy
#endif

AHC_BOOL uiIsUsingLcd(void)
{
    return AHC_TRUE
#if (TVOUT_ENABLE)
            && (AHC_FALSE == AHC_IsTVConnect())
#endif
#if (HDMI_ENABLE)
            && (AHC_FALSE == AHC_IsHdmiConnect())
#endif
    ;
}

AHC_BOOL uiStateProcessGlobalEvent( UINT32 ulMsgId, UINT32* pulEvent , UINT32* pulParam)
{
#ifdef FACTORY_RESET
    if (FACTORY_RESET == *pulEvent) {
        RestoreFromDefaultSetting();
        Menu_RenewMenuSetting(AHC_TRUE);
        Menu_WriteLcdSnrTVHdmiStauts2SF();
    }
#endif

    if (MenuSettingConfig()->uiBeep == BEEP_ON &&
        MenuSettingConfig()->uiVolume != 0)
    {
        if(VideoFunc_GetRecordStatus()==AHC_TRUE || VideoFunc_PreRecordStatus()==AHC_TRUE)
            goto L_PowerSave;

        switch( *pulEvent )
        {
        #ifdef NET_SYNC_PLAYBACK_MODE
            case WIRELESS_ENTER_PLAYBACK:
                    AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
            break;
            case WIRELESS_EXIT_PLAYBACK :
                    AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
            break;
        #endif
            case BUTTON_UP_PRESS:
            case BUTTON_DOWN_PRESS:
            case BUTTON_MENU_PRESS:
            case BUTTON_MODE_PRESS:
            //case BUTTON_MUTE_PRESS:
            case BUTTON_POWER_PRESS:
            case BUTTON_MENU_LPRESS:
            case BUTTON_MODE_LPRESS:
            //case BUTTON_MUTE_LPRESS:
            case BUTTON_POWER_LPRESS:
            case BUTTON_REC_LPRESS:
            case BUTTON_SET_PRESS:
            case BUTTON_SOS_PRESS:
                AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
            break;

            case BUTTON_MUTE_PRESS:
            case BUTTON_MUTE_LPRESS:
                if(uiGetCurrentState()!=UI_PLAYBACK_STATE)
                    AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);
            break;

            case BUTTON_REC_PRESS:
            #if (USE_SHUTTER_SOUND)
                if(uiGetCurrentState()!=UI_CAMERA_STATE)
            #endif
                    AHC_PlaySoundEffect(AHC_SOUNDEFFECT_BUTTON);

                if(uiGetCurrentState()==UI_VIDEO_STATE)
                {
                    UINT8       ubSoundEffectStatus;
                    UINT32      wait_cnt=0;

                    do{
                        AHC_GetSoundEffectStatus(&ubSoundEffectStatus);
                        AHC_OS_Sleep(100);
                        if((++wait_cnt) > 50){
                            printc("Warning! AHC_PlaySoundEffect is too long\r\n");
                            wait_cnt = 0;
                        }
                    }while((AHC_SOUND_EFFECT_STATUS_STOP != ubSoundEffectStatus) && (AHC_SOUND_EFFECT_STATUS_INVALID != ubSoundEffectStatus));
                }
            break;

            default:
                //NOP
            break;
        }
    }

L_PowerSave:

    if( (*pulEvent != BUTTON_NONE)              &&
        (*pulEvent != BUTTON_UPDATE_MESSAGE)    &&
        (*pulEvent != BUTTON_BATTERY_DETECTION) &&
        (*pulEvent != BUTTON_HDMI_REMOVED)      &&
        (*pulEvent != BUTTON_VRCB_MOTION_DTC)   &&
        (*pulEvent != BUTTON_UPDATE_CHARGE_ICON)&&
        (*pulEvent != BUTTON_TIMESTAMP_UPDATE))
    {
        AutoPowerOffCounterReset();
    }

    if (MenuSettingConfig()->uiLCDPowerSave != LCD_POWER_SAVE_OFF)
    {
        switch( *pulEvent )
        {
            //Key Event
            case BUTTON_UP_PRESS:
            case BUTTON_UP_LPRESS:
            case BUTTON_DOWN_PRESS:
            case BUTTON_DOWN_LPRESS:
            case BUTTON_LEFT_PRESS:
            case BUTTON_LEFT_LPRESS:
            case BUTTON_RIGHT_PRESS:
            case BUTTON_RIGHT_LPRESS:
            case BUTTON_REC_PRESS:
            case BUTTON_REC_LPRESS:
            case BUTTON_SET_PRESS:
            case BUTTON_SET_LPRESS:
            case BUTTON_MENU_PRESS:
            case BUTTON_MENU_LPRESS:
            case BUTTON_MODE_PRESS:
            case BUTTON_MODE_LPRESS:
            case BUTTON_MUTE_PRESS:
            case BUTTON_MUTE_LPRESS:
            case BUTTON_POWER_PRESS:
            case BUTTON_POWER_LPRESS:
            case BUTTON_SOS_PRESS:
            case BUTTON_SOS_LPRESS:
                    //Andy Liu TBD.
                // Just ignore key event
                if ((KEY_POWER_OFF != *pulEvent) || ((KEY_POWER_OFF == *pulEvent) && (!bForce_PowerOff))){
                    if(LedCtrl_GetBacklightStatus()==AHC_FALSE){
                        if(uiIsUsingLcd()){
                            //if(uiGetCurrentState() != UI_HDMI_STATE && uiGetCurrentState() != UI_TVOUT_STATE){
                            *pulEvent = BUTTON_NONE;
                        }
                    }
                }
            break;

            case BUTTON_UP_REL:
            case BUTTON_UP_LREL:
            case BUTTON_DOWN_REL:
            case BUTTON_DOWN_LREL:
            case BUTTON_LEFT_REL:
            case BUTTON_LEFT_LREL:
            case BUTTON_RIGHT_REL:
            case BUTTON_RIGHT_LREL:
            case BUTTON_REC_REL:
            case BUTTON_REC_LREL:
            case BUTTON_SET_REL:
            case BUTTON_SET_LREL:
            case BUTTON_MENU_REL:
            case BUTTON_MENU_LREL:
            case BUTTON_MODE_REL:
            case BUTTON_MODE_LREL:
            case BUTTON_MUTE_REL:
            case BUTTON_MUTE_LREL:
            case BUTTON_POWER_REL:
            case BUTTON_POWER_LREL:
            case BUTTON_SOS_REL:
            case BUTTON_SOS_LREL:
                if (KEY_POWER_OFF == *pulEvent)
                {
                    if(!bForce_PowerOff)
                    {
                        LCDPowerSaveCounterReset();
                        if(LedCtrl_GetBacklightStatus()==AHC_FALSE)
                        {
                            if(uiIsUsingLcd()){
                                //if(uiGetCurrentState()!=UI_HDMI_STATE && uiGetCurrentState()!=UI_TVOUT_STATE)
                                LedCtrl_LcdBackLight(AHC_TRUE);
                                *pulEvent = BUTTON_NONE;
                            }
                        }
                    }
                }
                else {
                    LCDPowerSaveCounterReset();
                    if(LedCtrl_GetBacklightStatus()==AHC_FALSE)
                    {
                        //Andy Liu TBD
                        if(uiIsUsingLcd()){
                            //if(uiGetCurrentState()!=UI_HDMI_STATE && uiGetCurrentState()!=UI_TVOUT_STATE)
                            LedCtrl_LcdBackLight(AHC_TRUE);
                            if((EVENT_VRCB_MOTION_DTC == (*pulParam)) && ((*pulEvent) == KEY_VIDEO_RECORD))
                            {
                                #if MDT_REC_ALWAYS_BACKLIGHT_OFF
                                printc("@@turn on backlight and start record!\r\n");
                                #else
                                m_ubParkingModeRecTrigger = AHC_FALSE;
                                *pulEvent = BUTTON_NONE;
                                #endif
                            }
                            else
                            {
                                *pulEvent = BUTTON_NONE;
                            }
                        }
                    }
                }
            break;

            //Device Event
            case BUTTON_USB_DETECTED:
            case BUTTON_USB_REMOVED:
            case BUTTON_TV_DETECTED:
            case BUTTON_TV_REMOVED:
            case BUTTON_HDMI_DETECTED:
            case BUTTON_HDMI_REMOVED:
            case BUTTON_DC_CABLE_IN:
            case BUTTON_DC_CABLE_OUT:
            case BUTTON_SD_DETECTED:
            case BUTTON_SD_REMOVED:

            case BUTTON_USB_B_DEVICE_DETECTED:
            case BUTTON_USB_B_DEVICE_REMOVED:
            case BUTTON_REVERSE_GEAR:

            case BUTTON_TV_DECODER_SRC_TYPE:
                LCDPowerSaveCounterReset();
                if(LedCtrl_GetBacklightStatus()==AHC_FALSE)
                {
                    if(uiIsUsingLcd()){
                        //if(uiGetCurrentState()!=UI_HDMI_STATE && uiGetCurrentState()!=UI_TVOUT_STATE)
                        LedCtrl_LcdBackLight(AHC_TRUE);
                    }
                }
            break;

            default:
                //NOP
            break;
        }
    }

#if (POWER_OFF_CONFIRM_PAGE_EN)

    if(PowerOff_InProcess==AHC_TRUE)
    {
        switch( *pulEvent )
        {
            case BUTTON_UP_PRESS:
                PowerOff_Option = CONFIRM_OPT_YES;
                MenuDrawChangeSubItem_PowerOff();
                printc("LEFT: PowerOff_Option YES\r\n");
                *pulEvent = BUTTON_NONE;
            break;

            case BUTTON_DOWN_PRESS:
                PowerOff_Option = CONFIRM_OPT_NO;
                MenuDrawChangeSubItem_PowerOff();
                printc("RIGHT: PowerOff_Option NO\r\n");
                *pulEvent = BUTTON_NONE;
            break;

            case BUTTON_REC_PRESS:
                printc("OK: PowerOff_Option %s\r\n",(PowerOff_Option)?("NO"):("YES"));
                AHC_PowerOff_Option(PowerOff_Option);
                *pulEvent = BUTTON_NONE;
            break;

            case KEY_POWER_OFF:
            #if (POWER_OFF_CONFIRM_PAGE_EN)
                if(!bForce_PowerOff)
                    *pulEvent = BUTTON_NONE;
            #endif
            break;

            //Device Event
            case BUTTON_USB_DETECTED:
            case BUTTON_DC_CABLE_IN:
            case BUTTON_SD_DETECTED:
            case BUTTON_SD_REMOVED:
            case BUTTON_TV_DETECTED:
            case BUTTON_TV_REMOVED:
            case BUTTON_HDMI_DETECTED:
            case BUTTON_HDMI_REMOVED:
            case BUTTON_COVER_OPEN:
            case BUTTON_COVER_CLOSED:
            case BUTTON_BATTERY_DETECTION:
            case BUTTON_UPDATE_MESSAGE:
                //NOP
            break;

            case BUTTON_DC_CABLE_OUT:
            case BUTTON_USB_REMOVED:
                AHC_Charger_SetEnable(AHC_FALSE);
                #if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
                AHC_SetShutdownByChargerOut(AHC_TRUE);
                #endif
            break;

            case BUTTON_LCD_NORMAL:
                AHC_DrawMenuRotateEvent(MENU_LCD_NORMAL, NULL);
                *pulEvent = BUTTON_NONE;
            break;

            case BUTTON_LCD_ROTATE:
                AHC_DrawMenuRotateEvent(MENU_LCD_ROTATE, NULL);
                *pulEvent = BUTTON_NONE;
            break;
            case BUTTON_USB_B_DEVICE_DETECTED:
                printc("BUTTON_USB_B_DEVICE_DETECTED,%s,%d\r\n", __func__, __LINE__);
                break;
            case BUTTON_USB_B_DEVICE_REMOVED:
                printc("BUTTON_USB_B_DEVICE_REMOVED,%s,%d\r\n", __func__, __LINE__);
                break;
            case BUTTON_TV_DECODER_SRC_TYPE:
                printc("BUTTON_TV_DECODER_SRC_TYPE,%s,%d\r\n", __func__, __LINE__);
                break;
            default:
                *pulEvent = BUTTON_NONE;
            break;
        }
    }
#endif

    if(Deleting_InBrowser || Protecting_InBrowser)
    {
        switch( *pulEvent )
        {
        #if (SUPPORT_TOUCH_PANEL)
            case BUTTON_TOUCH_PRESS:
        #endif
            case BUTTON_UP_PRESS:
            case BUTTON_DOWN_PRESS:
            case BUTTON_REC_PRESS:
            case BUTTON_REC_REL:
            case BUTTON_MENU_REL:
            case BUTTON_SET_PRESS:
            case BUTTON_SET_LPRESS:
                //NOP
            break;

            case BUTTON_MODE_REL:
                if(Delete_File_Confirm || Protect_File_Confirm || UnProtect_File_Confirm)
                    *pulEvent = BUTTON_NONE;
            break;

            case KEY_POWER_OFF:
            #if (POWER_OFF_CONFIRM_PAGE_EN)
                if(!bForce_PowerOff)
                    *pulEvent = BUTTON_NONE;
            #endif
            break;

            //Device Event
            case BUTTON_USB_DETECTED:
            case BUTTON_DC_CABLE_IN:
            case BUTTON_SD_DETECTED:
            case BUTTON_SD_REMOVED:
            case BUTTON_TV_DETECTED:
            case BUTTON_TV_REMOVED:
            case BUTTON_HDMI_DETECTED:
            case BUTTON_HDMI_REMOVED:
            case BUTTON_COVER_OPEN:
            case BUTTON_COVER_CLOSED:
            case BUTTON_BATTERY_DETECTION:
            case BUTTON_UPDATE_MESSAGE:
                //NOP
                break;

            case BUTTON_DC_CABLE_OUT:
            case BUTTON_USB_REMOVED:
                AHC_Charger_SetEnable(AHC_FALSE);
                #if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
                AHC_SetShutdownByChargerOut(AHC_TRUE);
                #endif
            break;

            case BUTTON_LCD_NORMAL:
                AHC_DrawMenuRotateEvent(MENU_LCD_NORMAL, NULL);
                *pulEvent = BUTTON_NONE;
            break;

            case BUTTON_LCD_ROTATE:
                AHC_DrawMenuRotateEvent(MENU_LCD_ROTATE, NULL);
                *pulEvent = BUTTON_NONE;
            break;

                case BUTTON_USB_B_DEVICE_DETECTED:
                    printc("BUTTON_USB_B_DEVICE_DETECTED,%s,%d\r\n", __func__, __LINE__);
                    break;
                case BUTTON_USB_B_DEVICE_REMOVED:
                    printc("BUTTON_USB_B_DEVICE_REMOVED,%s,%d\r\n", __func__, __LINE__);
                    break;
                case BUTTON_TV_DECODER_SRC_TYPE:
                    printc("BUTTON_TV_DECODER_SRC_TYPE,%s,%d\r\n", __func__, __LINE__);
                    break;
            default:
                *pulEvent = BUTTON_NONE;
            break;
        }
    }

    if(!IN_MENU())
    {
        #if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(CFG_WIFI_ON_UNDER_VIDEO_MODE_ONLY)
        {
            UINT8    wifi_switch_on;

            switch (uiGetCurrentState()) {
            //////////////////////////////////////////////////////////
            case UI_VIDEO_STATE:
                wifi_switch_on = AHC_TRUE;
                break;

            default:
                wifi_switch_on = AHC_FALSE;
                break;
            }

            AHC_WiFi_Switch(wifi_switch_on);
        }
        #endif
    }

#if (POWER_ON_BY_GSENSOR_EN) && defined(GSENSOR_INT)
    if( (*pulEvent == BUTTON_POWER_PRESS)       ||
        (*pulEvent == BUTTON_MODE_PRESS)        ||
        (*pulEvent == BUTTON_MENU_PRESS)        ||
        (*pulEvent == BUTTON_UP_PRESS)          ||
        (*pulEvent == BUTTON_DOWN_PRESS)        ||
        (*pulEvent == BUTTON_LEFT_PRESS)        ||
        (*pulEvent == BUTTON_RIGHT_PRESS)       ||
        (*pulEvent == BUTTON_REC_PRESS) )
    {
        extern AHC_BOOL ubGsnrPwrOnActStart;

        if (AHC_TRUE == ubGsnrPwrOnActStart)
        {
            RTNA_DBG_Str(0, FG_GREEN("Cancel G-Sensor Power-On State, retrun normal VR\r\n"));
            ubGsnrPwrOnActStart = AHC_FALSE;
        }
    }
#endif

    if (WMSG_LAYER_WINDOW_ID == OSD_LAYER_WINDOW_ID) {
        // The warning message layer and the OSD layer window is shared.
        if (AHC_WMSG_GetInfo() != WMSG_NONE) {
            if (BUTTON_UPDATE_MESSAGE == *pulEvent) {
                *pulEvent = BUTTON_NONE;
                return AHC_FALSE;
            }
        }
    }

    return AHC_TRUE;
}
