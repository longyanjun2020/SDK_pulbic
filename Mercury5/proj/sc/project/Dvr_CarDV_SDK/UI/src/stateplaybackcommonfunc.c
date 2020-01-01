/*===========================================================================
 * Include file 
 *===========================================================================*/ 
#include "stateplaybackcommonfunc.h"
#include "ahc_menu_inc.h"
#include "ahc_message.h"
#include "MenuSetting.h"
#include "statemoviepbfunc_inc.h"
#include "statephotopbfunc_inc.h"
#include "stateaudiopbfunc_inc.h"
#include "ahc_dcf.h"
#include <stdio.h>
/*===========================================================================
 * Macro define 
 *===========================================================================*/ 


/*===========================================================================
 * Global varible
 *===========================================================================*/ 
static UI_STATE_OP      m_PBStateOP;
/*===========================================================================
 * Extern varible
 *===========================================================================*/
extern AHC_BOOL         gbAhcDbgBrk;
/*===========================================================================
 * Extern function
 *===========================================================================*/

/*===========================================================================
 * Main body
 *===========================================================================*/
AHC_BOOL StatePBModeSetOperation(void* pfInit, void* pfShutDown, void* pfHandler)
{
    m_PBStateOP.pfInitFunc = (pfFunc)pfInit;
    m_PBStateOP.pfShutDownFunc = (pfFunc)pfShutDown;
    m_PBStateOP.pfUIStateHandlerFunc = (pfHandlerFunc)pfHandler;
    
    return AHC_TRUE;
}

UINT32 StateCommonPBModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    return m_PBStateOP.pfUIStateHandlerFunc(ulMsgId, ulEvent, ulParam);
}

AHC_BOOL StateCommonPBModeInit(void* pData)
{    
    return m_PBStateOP.pfInitFunc(pData);
}

AHC_BOOL StateCommonPBModeShutDown(void* pData)
{
    return m_PBStateOP.pfShutDownFunc(pData);
}

AHC_BOOL StateSelectPBFunc(UINT8 ubUIMode)
{
    if( MOVPB_MODE == ubUIMode){
        #if (HDMI_ENABLE)
            if (AHC_IsHdmiConnect()){
                StatePBModeSetOperation((void*)StateMoviePlaybackModeInitHDMI, (void*)StateMoviePlaybackModeShutDown, (void *)StateMoviePlaybackModeHandler);
            }else
        #endif
        #if (TVOUT_ENABLE)
            if (AHC_IsTVConnectEx())
            {

                StatePBModeSetOperation((void*)StateMoviePlaybackModeInitTV, (void*)StateMoviePlaybackModeShutDown, (void *)StateMoviePlaybackModeHandler);
            }else
        #endif
            {
                StatePBModeSetOperation((void*)StateMoviePlaybackModeInitLCD, (void*)StateMoviePlaybackModeShutDown, (void *)StateMoviePlaybackModeHandler);
            }
    }
    else if( JPGPB_MODE == ubUIMode){
        #if (HDMI_ENABLE)
            if (AHC_IsHdmiConnect()){
                StatePBModeSetOperation((void*)StatePhotoPlaybackModeInitHDMI, (void*)StatePhotoPlaybackModeShutDown, (void *)StatePhotoPlaybackModeHandler);
            }else
        #endif
        #if (TVOUT_ENABLE)
            if (AHC_IsTVConnectEx())
            {
                StatePBModeSetOperation((void*)StatePhotoPlaybackModenitTV, (void*)StatePhotoPlaybackModeShutDown, (void *)StatePhotoPlaybackModeHandler);
            }else
        #endif
            {
                StatePBModeSetOperation((void*)StatePhotoPlaybackModeInitLCD, (void*)StatePhotoPlaybackModeShutDown, (void *)StatePhotoPlaybackModeHandler);
            }
    }
    else if( AUDPB_MODE == ubUIMode){
        StatePBModeSetOperation((void*)StateAudioPlaybackModeInit, (void*)StateAudioPlaybackModeShutDown, (void *)StateAudioPlaybackModeHandler);                    
    }
    else if( JPGPB_MOVPB_MODE == ubUIMode){
        UINT32 uiCurrentIdx;
        UINT8  ubFileType;
        AHC_UF_GetCurrentIndex(&uiCurrentIdx);
        AHC_UF_GetFileTypebyIndex(uiCurrentIdx, &ubFileType);
        if ( ubFileType == DCF_OBG_JPG ){
        #if (HDMI_ENABLE)
            if (AHC_IsHdmiConnect()){
                StatePBModeSetOperation((void*)StatePhotoPlaybackModeInitHDMI, (void*)StatePhotoPlaybackModeShutDown, (void *)StatePhotoPlaybackModeHandler);
            }else
        #endif
        #if (TVOUT_ENABLE)
            if (AHC_IsTVConnectEx())
            {
                StatePBModeSetOperation((void*)StatePhotoPlaybackModenitTV, (void*)StatePhotoPlaybackModeShutDown, (void *)StatePhotoPlaybackModeHandler);
            }else
        #endif
            {
                StatePBModeSetOperation((void*)StatePhotoPlaybackModeInitLCD, (void*)StatePhotoPlaybackModeShutDown, (void *)StatePhotoPlaybackModeHandler);
            }
        }
        else{
        #if (HDMI_ENABLE)
            if (AHC_IsHdmiConnect()){
                StatePBModeSetOperation((void*)StateMoviePlaybackModeInitHDMI, (void*)StateMoviePlaybackModeShutDown, (void *)StateMoviePlaybackModeHandler);
            }else
        #endif
        #if (TVOUT_ENABLE)
            if (AHC_IsTVConnectEx())
            {
                StatePBModeSetOperation((void*)StateMoviePlaybackModeInitTV, (void*)StateMoviePlaybackModeShutDown, (void *)StateMoviePlaybackModeHandler);
            }else
        #endif
            {
                StatePBModeSetOperation((void*)StateMoviePlaybackModeInitLCD, (void*)StateMoviePlaybackModeShutDown, (void *)StateMoviePlaybackModeHandler);
            }
        }
    }                
    
    return AHC_TRUE;
}

AHC_BOOL StateSelectFuncPlaybackMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    if(MOVPB_MODE == GetCurrentOpMode())
    {
        ahcRet = StateSelectPBFunc(MOVPB_MODE);
    
        RegisterEventCb(EVENT_KEY_UP,                           STATE_MOVPB_MODE_EVENT_KEY_UP);
        RegisterEventCb(EVENT_KEY_DOWN,                         STATE_MOVPB_MODE_EVENT_KEY_DOWN);
        RegisterEventCb(EVENT_KEY_LEFT/*EVENT_MOVPB_TOUCH_BKWD_PRESS*/,         STATE_MOVPB_MODE_EVENT_MOVPB_KEY_LEFT);
        RegisterEventCb(EVENT_KEY_RIGHT/*EVENT_MOVPB_TOUCH_FRWD_PRESS*/,            STATE_MOVPB_MODE_EVENT_MOVPB_KEY_RIGHT);
        RegisterEventCb(EVENT_MOVPB_PLAY_START/*EVENT_MOVPB_TOUCH_PLAY_PRESS*/,         STATE_MOVPB_MODE_EVENT_MOVPB_PLAY_START);
        RegisterEventCb(EVENT_MOVPB_MODE/*EVENT_MOVPB_TOUCH_RETURN*/,               STATE_MOVPB_MODE_EVENT_MOVPB_MODE);
        RegisterEventCb(EVENT_KEY_MENU,                         STATE_MOVPB_MODE_EVENT_KEY_MENU);
        RegisterEventCb(EVENT_MOVPB_PREV_PRESS,             STATE_MOVPB_MODE_EVENT_MOVPB_PREV_PRESS);
        RegisterEventCb(EVENT_MOVPB_NEXT_PRESS,             STATE_MOVPB_MODE_EVENT_MOVPB_NEXT_PRESS);
        RegisterEventCb(EVENT_VIDEO_PREVIEW,                    STATE_MOVPB_MODE_EVENT_VIDEO_PREVIEW);
        RegisterEventCb(EVENT_CAMERA_PREVIEW,                   STATE_MOVPB_MODE_EVENT_CAMERA_PREVIEW);
        RegisterEventCb(EVENT_FILE_DELETING,                    STATE_MOVPB_MODE_EVENT_FILE_DELETING);
        RegisterEventCb(EVENT_LOCK_FILE_M,                      STATE_MOVPB_MODE_EVENT_LOCK_FILE_M);

        RegisterEventCb(EVENT_DC_CABLE_IN,                      STATE_MOVPB_MODE_EVENT_DC_CABLE_IN);
        RegisterEventCb(EVENT_DC_CABLE_OUT,                     STATE_MOVPB_MODE_EVENT_DC_CABLE_OUT);
        RegisterEventCb(EVENT_USB_DETECT,                       STATE_MOVPB_MODE_EVENT_USB_DETECT);
        RegisterEventCb(EVENT_USB_REMOVED,                      STATE_MOVPB_MODE_EVENT_USB_REMOVED);
        RegisterEventCb(EVENT_SD_DETECT,                        STATE_MOVPB_MODE_EVENT_SD_DETECT);
        RegisterEventCb(EVENT_SD_REMOVED,                       STATE_MOVPB_MODE_EVENT_SD_REMOVED);
    #if (TVOUT_ENABLE)
        RegisterEventCb(EVENT_TV_DETECT,                        STATE_MOVPB_MODE_EVENT_TV_DETECT);
        RegisterEventCb(EVENT_TV_REMOVED,                       STATE_MOVPB_MODE_EVENT_TV_REMOVED);
    #endif
    #if (HDMI_ENABLE)
        RegisterEventCb(EVENT_HDMI_DETECT,                      STATE_MOVPB_MODE_EVENT_HDMI_DETECT);
        RegisterEventCb(EVENT_HDMI_REMOVED,                     STATE_MOVPB_MODE_EVENT_HDMI_REMOVED);
    #endif
        RegisterEventCb(EVENT_USB_B_DEVICE_DETECT,              STATE_PLAYBACK_MODE_EVENT_USB_B_DEVICE_DETECT);
        RegisterEventCb(EVENT_USB_B_DEVICE_REMOVED,             STATE_PLAYBACK_MODE_EVENT_USB_B_DEVICE_REMOVED);
        RegisterEventCb(EVENT_MOVPB_UPDATE_MESSAGE,             STATE_MOVPB_MODE_EVENT_MOVPB_UPDATE_MESSAGE);
        RegisterEventCb(EVNET_SUB_MODE_ENTER,                   STATE_MOVPB_MODE_EVENT_SUB_MODE_ENTER);
        RegisterEventCb(EVNET_SUB_MODE_EXIT,                    STATE_MOVPB_MODE_EVENT_SUB_MODE_EXIT);
    #if defined(WIFI_PORT) && (WIFI_PORT == 1) 
        RegisterEventCb(EVENT_NET_ENTER_PLAYBACK,               STATE_MOVPB_MODE_EVENT_ENTER_NET_PLAYBACK);
    #endif
    }
    else if (JPGPB_MODE == GetCurrentOpMode())
    {
        ahcRet = StateSelectPBFunc(JPGPB_MODE);

        RegisterEventCb(EVENT_KEY_UP,                           STATE_PHOTOPB_MODE_EVENT_KEY_UP);
        RegisterEventCb(EVENT_KEY_DOWN,                         STATE_PHOTOPB_MODE_EVENT_KEY_DOWN);
        RegisterEventCb(EVENT_KEY_LEFT,                         STATE_PHOTOPB_MODE_EVENT_KEY_LEFT);
        RegisterEventCb(EVENT_KEY_RIGHT,                        STATE_PHOTOPB_MODE_EVENT_KEY_RIGHT);
        RegisterEventCb(EVENT_KEY_SET,                          STATE_PHOTOPB_MODE_EVENT_KEY_SET);
        RegisterEventCb(EVENT_KEY_MODE/*EVENT_JPGPB_TOUCH_RETURN*/,             STATE_PHOTOPB_MODE_EVENT_JPGPB_KEY_MODE);
        RegisterEventCb(EVENT_KEY_MENU,                         STATE_PHOTOPB_MODE_EVENT_KEY_MENU);
        //RegisterEventCb(EVENT_JPGPB_TOUCH_PREV_PRESS,         STATE_PHOTOPB_MODE_EVENT_JPGPB_TOUCH_PREV_PRESS);
        //RegisterEventCb(EVENT_JPGPB_TOUCH_NEXT_PRESS,         STATE_PHOTOPB_MODE_EVENT_JPGPB_TOUCH_NEXT_PRESS);
        RegisterEventCb(EVENT_VIDEO_PREVIEW,                    STATE_PHOTOPB_MODE_EVENT_VIDEO_PREVIEW);
        RegisterEventCb(EVENT_CAMERA_PREVIEW,                   STATE_PHOTOPB_MODE_EVENT_CAMERA_PREVIEW);
        RegisterEventCb(EVENT_FILE_DELETING,                    STATE_PHOTOPB_MODE_EVENT_FILE_DELETING);
        RegisterEventCb(EVENT_LOCK_FILE_M,                      STATE_PHOTOPB_MODE_EVENT_LOCK_FILE_M);

        RegisterEventCb(EVENT_DC_CABLE_IN,                      STATE_PHOTOPB_MODE_EVENT_DC_CABLE_IN);
        RegisterEventCb(EVENT_DC_CABLE_OUT,                     STATE_PHOTOPB_MODE_EVENT_DC_CABLE_OUT);
        RegisterEventCb(EVENT_USB_DETECT,                       STATE_PHOTOPB_MODE_EVENT_USB_DETECT);
        RegisterEventCb(EVENT_USB_REMOVED,                      STATE_PHOTOPB_MODE_EVENT_USB_REMOVED);
        RegisterEventCb(EVENT_SD_DETECT,                        STATE_PHOTOPB_MODE_EVENT_SD_DETECT);
        RegisterEventCb(EVENT_SD_REMOVED,                       STATE_PHOTOPB_MODE_EVENT_SD_REMOVED);
#if (TVOUT_ENABLE)
        RegisterEventCb(EVENT_TV_DETECT,                        STATE_PHOTOPB_MODE_EVENT_TV_DETECT);
        RegisterEventCb(EVENT_TV_REMOVED,                       STATE_PHOTOPB_MODE_EVENT_TV_REMOVED);
#endif
#if (HDMI_ENABLE)
        RegisterEventCb(EVENT_HDMI_DETECT,                      STATE_PHOTOPB_MODE_EVENT_HDMI_DETECT);
        RegisterEventCb(EVENT_HDMI_REMOVED,                     STATE_PHOTOPB_MODE_EVENT_HDMI_REMOVED);
#endif
#if (UVC_HOST_VIDEO_ENABLE)
        RegisterEventCb(EVENT_USB_B_DEVICE_DETECT,              STATE_PLAYBACK_MODE_EVENT_USB_B_DEVICE_DETECT);
        RegisterEventCb(EVENT_USB_B_DEVICE_REMOVED,             STATE_PLAYBACK_MODE_EVENT_USB_B_DEVICE_REMOVED);
#endif
        RegisterEventCb(EVENT_JPGPB_UPDATE_MESSAGE,             STATE_PHOTOPB_MODE_EVENT_JPGPB_UPDATE_MESSAGE);
        RegisterEventCb(EVENT_JPGPB_UPDATE_LCD,                 STATE_PHOTOPB_MODE_EVENT_JPGPB_UPDATE_LCD);

        RegisterEventCb(EVNET_SUB_MODE_ENTER,                   STATE_PHOTOPB_MODE_EVENT_SUB_MODE_ENTER);
        RegisterEventCb(EVNET_SUB_MODE_EXIT,                    STATE_PHOTOPB_MODE_EVENT_SUB_MODE_EXIT);  
    #if defined(WIFI_PORT) && (WIFI_PORT == 1) 
        RegisterEventCb(EVENT_NET_ENTER_PLAYBACK,               STATE_PHOTOPB_MODE_EVENT_ENTER_NET_PLAYBACK);
    #endif      
    }
    
    StateModeSetOperation(UI_PLAYBACK_STATE, StateCommonPBModeInit, StateCommonPBModeShutDown, StateCommonPBModeHandler);                    

    ahcRet =  SwitchUIDrawSetPlaybackMode();
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,ahcRet); return ahcRet;} 

    return ahcRet;    
}

