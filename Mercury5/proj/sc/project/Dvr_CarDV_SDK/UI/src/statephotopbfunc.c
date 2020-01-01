/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_common.h"
#include "ahc_parameter.h"
#include "ahc_sensor.h"
#include "ahc_message.h"
#include "ahc_utility.h"
#include "ahc_display.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_browser.h"
#include "ahc_menu.h"
#include "ahc_os.h"
#include "ahc_media.h"
#include "ahc_usb.h"
#include "ahc_warningmsg.h"
#include "ahc_general_cardv.h"
#include "IconPosition.h"
#include "statephotopbfunc.h"
#include "statehdmifunc.h"
#include "statetvfunc.h"
#include "mediaplaybackctrl.h"
#include "drawstatephotopbfunc.h"
#include "MenuSetting.h"
#include "MenuTouchButton.h"
#include "keyparser.h"
#include "ledcontrol.h"
#include "dsc_charger.h"
#include "MenuDrawCommon.h"
#include "ait_utility.h"
#if WIFI_PORT == 1
#include "netapp.h"
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define  PHOTOPB_TIMER_UNIT                       (100)
#define  PHOTOPB_OSD_SHOWTIME                       (3)  //unit :sec.

/*===========================================================================
 * Global varible
 *===========================================================================*/

UINT32      PhotoPBTimerID          = AHC_OS_CREATE_TMR_INT_ERR;
UINT32      PhotoPBCounter          = 0;
AHC_BOOL    PhotoOSDShowUp          = AHC_TRUE;
AHC_BOOL    bLockCurJpegFile        = AHC_FALSE;
AHC_BOOL    m_ubZoomLock            = AHC_FALSE;

#if (SUPPORT_TOUCH_PANEL)
AHC_BOOL    m_ubShowJpgPBTouchPage  = AHC_FALSE;
#endif

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern UINT32   ObjSelect;
extern AHC_BOOL bForce_PowerOff;
extern AHC_BOOL     bShowHdmiWMSG; //Andy Liu. Remove it later.
/*===========================================================================
 * Extern function
 *===========================================================================*/
//extern void InitOSD(void);
//extern void MoviePBMode_Update(void);
//extern void AudioPBMode_Update(void);
/*===========================================================================
 * Main body
 *===========================================================================*/

void PhotoPBTimer_ResetCounter(void)
{
    PhotoPBCounter = 0;
}

void PhotoPBTimer_ISR(void *tmr, void *arg)
{
    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_LCD, 0);

    if( PhotoOSDShowUp )
    {
        PhotoPBCounter++;

        if( 0 == PhotoPBCounter%(PHOTOPB_OSD_SHOWTIME*10) )
        {
            PhotoPBCounter = 0;

            switch(uiGetCurrentState())
            {
#if 0
                case  UI_HDMI_STATE:
                case  UI_TVOUT_STATE:
                    AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0);
                break;
#endif
                case  UI_PLAYBACK_STATE:
                break;
            }
        }
    }
}

AHC_BOOL PhotoPBTimer_Start(UINT32 ulTime)
{
    if(PhotoPBTimerID == AHC_OS_CREATE_TMR_INT_ERR)
    {
        PhotoPBTimer_ResetCounter();
        PhotoPBTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, PhotoPBTimer_ISR, (void*)NULL );

        if(AHC_OS_CREATE_TMR_INT_ERR == PhotoPBTimerID)
            return AHC_FALSE;
        else
            return AHC_TRUE;
    }
    else {
        return AHC_FALSE;
    }
}

AHC_BOOL PhotoPBTimer_Stop(void)
{
    UINT8 ret = 0;

    if(PhotoPBTimerID != AHC_OS_CREATE_TMR_INT_ERR)
    {
        ret = AHC_OS_StopTimer( PhotoPBTimerID, AHC_OS_TMR_OPT_PERIODIC );

        PhotoPBTimerID = AHC_OS_CREATE_TMR_INT_ERR;

        if(ret)
            return AHC_FALSE;
        else
            return AHC_TRUE;
    }
    else {
        return AHC_FALSE;
    }
}

AHC_BOOL PhotoPBFunc_IsZoomLock(void)
{
    return m_ubZoomLock;
}

void PhotoPBFunc_SetZoomLock(AHC_BOOL bZoomlock)
{
    m_ubZoomLock = bZoomlock;
}

void PhotoPBFunc_CheckLCDstatus(void)
{
    UINT8 status;

    AHC_LCD_GetStatus(&status);

    AHC_SetDisplayMode(DISPLAY_MODE_DISABLE);
    AHC_SetKitDirection(status, AHC_TRUE, AHC_SNR_NOFLIP, AHC_FALSE);
}

void PhotoPBFunc_SetOSDShowStatus(AHC_BOOL state)
{
    PhotoOSDShowUp = state;
}

AHC_BOOL PhotoPBFunc_GetOSDShowStatus(void)
{
    return PhotoOSDShowUp;
}

#if 0
void PhotoPBFunc_SDMMC_Out(void)
{
#if 1
    StateSwitchMode(UI_BROWSER_STATE);
#else
    AHC_SetMode(AHC_MODE_IDLE);

    PhotoPBTimer_Stop();
    JpgPlaybackParamReset();
    AHC_UF_GetCurrentIndex(&ObjSelect);
#endif
}
#endif

AHC_BOOL PhotoPBMode_Start(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    PhotoOSDShowUp   = AHC_TRUE;

    AHC_SetMode(AHC_MODE_IDLE);

    JpgPlaybackParamReset();
    //PhotoPBFunc_CheckLCDstatus();
    MediaPlaybackConfig(PLAYBACK_CURRENT);

    ahc_ret = JpgPlayback_Play();

#if (QUICK_FILE_EDIT_EN)
    bLockCurJpegFile = AHC_CheckCurFileLockStatus();
#endif

    if(AHC_TRUE == ahc_ret )
    {
#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
        KeyParser_ResetTouchVariable();
        KeyParser_TouchItemRegister(&JpgPBMainPage_TouchButton[0], ITEMNUM(JpgPBMainPage_TouchButton));
#endif

        PhotoPBTimer_Start(PHOTOPB_TIMER_UNIT);
        //DrawStatePhotoPb_handler_Lcd(EVENT_JPGPB_MODE_INIT);//DrawStateJpgPlaybackUpdate(EVENT_JPGPB_MODE_INIT);
    }
    return ahc_ret;
}

void PhotoPBMode_Update(void)
{
    UINT32  MaxObjIdx;

    MaxObjIdx = AHC_GetMappingFileNum(FILE_PHOTO);

    if(MaxObjIdx == 0)
    {
        //PhotoPBTimer_Stop();
        //JpgPlaybackParamReset();
        //AHC_UF_GetCurrentIndex(&ObjSelect);
        StateSwitchMode(UI_BROWSER_STATE);
        return;
    }

#if (QUICK_FILE_EDIT_EN)
    bLockCurJpegFile = AHC_CheckCurFileLockStatus();
#endif

#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
    KeyParser_ResetTouchVariable();
    KeyParser_TouchItemRegister(&JpgPBMainPage_TouchButton[0], ITEMNUM(JpgPBMainPage_TouchButton));
#endif

    DrawStateJpgPbMode_Update();
}

//******************************************************************************
//
//                              AHC State JPG Playback Mode
//
//******************************************************************************
//extern AHC_HDMI_STATUS        m_HdmiStatus;
//extern AHC_BOOL           bHdmiMenuMode;
//extern    AHC_TV_STATUS           m_TVStatus ;
//extern UINT8      m_DelFile;
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_KEY_UP)
{
#if (HDMI_ENABLE)
    if (AHC_IsHdmiConnect()){}else
#endif
#if (TVOUT_ENABLE)
    if (AHC_IsTVConnectEx()){


    }else
#endif
    {
        if(!PhotoPBFunc_IsZoomLock())
            JpgPlayback_Zoom(JPGPB_ZOOM_IN);
        else
            JpgPlayback_Pan(JPGPB_PAN_UP);
    }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_KEY_DOWN)
{
#if (HDMI_ENABLE)
    if (AHC_IsHdmiConnect()){

    }else
#endif
#if (TVOUT_ENABLE)
    if (AHC_IsTVConnectEx()){

    }else
#endif
    {
        if(!PhotoPBFunc_IsZoomLock())
            JpgPlayback_Zoom(JPGPB_ZOOM_OUT);
        else
            JpgPlayback_Pan(JPGPB_PAN_DOWN);
    }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_KEY_LEFT)
{
//  #if (HDMI_ENABLE)
//      if (AHC_IsHdmiConnect()){
//          if(m_DelFile==DEL_FILE_SELECT_NO) {
//              m_DelFile = DEL_FILE_SELECT_YES;
//              DrawStatePhotoPb_handler_Hdmi(EVENT_KEY_DOWN);
//          }
//          else if(m_DelFile==DEL_FILE_NONE){
//              if(HDMIFunc_PhotoPBPrevious())
//                  DrawStatePhotoPb_handler_Lcd(EVENT_KEY_LEFT);
//          }
//      }else
//  #endif
//  #if (TVOUT_ENABLE)
//      if (AHC_IsTVConnectEx()){
//          if(m_DelFile==DEL_FILE_SELECT_NO) {
//              m_DelFile = DEL_FILE_SELECT_YES;
//              DrawStatePhotoPb_handler_Tv(EVENT_KEY_DOWN);
//          }
//          else if(m_DelFile==DEL_FILE_NONE){
//              if(TVFunc_PhotoPBPrevious())
//                  DrawStatePhotoPb_handler_Lcd(EVENT_KEY_LEFT);
//          }
//      }else
//  #endif
        {
            if(!PhotoPBFunc_IsZoomLock())
            {
                MediaPlaybackConfig(PLAYBACK_PREVIOUS);
                JpgPlayback_Play();
                DrawStatePhotoPb_handler_Lcd(ulEvent);
            }
            else
                JpgPlayback_Pan(JPGPB_PAN_LEFT);
        }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_KEY_RIGHT)
{
//  #if (HDMI_ENABLE)
//      if (AHC_IsHdmiConnect()){
//          if(m_DelFile==DEL_FILE_SELECT_YES) {
//              m_DelFile = DEL_FILE_SELECT_NO;
//              DrawStatePhotoPb_handler_Hdmi(EVENT_KEY_DOWN);
//          }
//          else if(m_DelFile==DEL_FILE_NONE){
//              if(HDMIFunc_PhotoPBNext())
//                  DrawStatePhotoPb_handler_Lcd(EVENT_KEY_RIGHT);
//          }
//      }else
//  #endif
//  #if (TVOUT_ENABLE)
//      if (AHC_IsTVConnectEx()){
//          if(m_DelFile==DEL_FILE_SELECT_YES) {
//              m_DelFile = DEL_FILE_SELECT_NO;
//              DrawStatePhotoPb_handler_Tv(EVENT_KEY_DOWN);
//          }
//          else if(m_DelFile==DEL_FILE_NONE){
//              if(TVFunc_PhotoPBNext())
//                  DrawStatePhotoPb_handler_Lcd(EVENT_KEY_RIGHT);
//          }
//      }else
//  #endif
        {
            if(!PhotoPBFunc_IsZoomLock())
            {
                MediaPlaybackConfig(PLAYBACK_NEXT);
                JpgPlayback_Play();
                DrawStatePhotoPb_handler_Lcd(ulEvent);
            }
            else
                JpgPlayback_Pan(JPGPB_PAN_RIGHT);
        }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_KEY_SET)
{
    UINT32      uState;
    AHC_GetSystemStatus(&uState);
    #if (TVOUT_ENABLE)
        if (AHC_IsTVConnectEx()){
            StatePhotoPlaybackMode(EVENT_TV_BROWSER_KEY_PLAYBACK);
        }else
    #endif
    #if (HDMI_ENABLE)
        if (AHC_IsHdmiConnect()){
            StatePhotoPlaybackMode(EVENT_HDMI_BROWSER_KEY_PLAYBACK);
        }else
    #endif
        {
            if(GetJpgConfig()->iCurZoomLevel!=0 && !PhotoPBFunc_IsZoomLock())
            {
                PhotoPBFunc_SetZoomLock(AHC_TRUE);
                AHC_DBG_MSG(1, "Zoom_Lcok=1\r\n");
            }
            else if(PhotoPBFunc_IsZoomLock())
            {
                PhotoPBFunc_SetZoomLock(AHC_FALSE);
                AHC_DBG_MSG(1, "Zoom_Lcok=0\r\n");
            }
        }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_JPGPB_KEY_MODE)
{
    AHC_BOOL ret;

    //PhotoPBFunc_SetZoomLock(AHC_FALSE);
    //PhotoPBTimer_Stop();
    //JpgPlaybackParamReset();
    //AHC_UF_GetCurrentIndex(&ObjSelect);
    ret = StateSwitchMode(UI_BROWSER_STATE);
}

DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_KEY_MENU)
{
#if CR_USE_STATE_SWITCH_SUB_MODE
        StateReplaceSubMode(UI_PLAYBACK_MENU_STATE);
#else
    AHC_BOOL    ahcRet = AHC_TRUE;
    UI_STATE_ID ubParentUIState = 0;
#if 1
    StateModeGetParent(uiGetCurrentState(), &ubParentUIState);
    if(UI_STATE_UNSUPPORTED != ubParentUIState){
        AHC_DBG_MSG(1, "%s,%d, DettachSubMode:%d\r\n", __func__, __LINE__, uiGetCurrentState());
        ahcRet = StateDetachSubMode();
        if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, ahcRet);}
    }
    ahcRet = StateAttachSubMode(UI_PLAYBACK_MENU_STATE);
    if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ahcRet); /*return ahcRet;*/}
#else
    StateSwitchMode(UI_PLAYBACK_MENU_STATE);
#endif
#endif
}

DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_VIDEO_PREVIEW)
{
    AHC_BOOL ret;

    //PhotoPBFunc_SetZoomLock(AHC_FALSE);
    //PhotoPBTimer_Stop();
    //JpgPlaybackParamReset();
    ret = StateSwitchMode(UI_VIDEO_STATE);
}

DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_CAMERA_PREVIEW)
{
    AHC_BOOL ret;

    //PhotoPBFunc_SetZoomLock(AHC_FALSE);
    //PhotoPBTimer_Stop();
    //JpgPlaybackParamReset();
    ret = StateSwitchMode(UI_CAMERA_STATE);
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_FILE_DELETING)
{
    AHC_BOOL ret;

    ret = QuickFileOperation(DCF_FILE_DELETE_ALL_CAM);

    if(ret!=EDIT_FILE_SUCCESS)
    {
        DrawFileOperationResult(ret);
    }
    else
    {
        //PhotoPBTimer_Stop();
        //JpgPlaybackParamReset();
        ret = StateSwitchMode(UI_BROWSER_STATE);
    }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_LOCK_FILE_M)
{
    AHC_BOOL ret;
    {
        if(AHC_CheckCurFileLockStatus())
        {
            ret = QuickFileOperation(DCF_FILE_NON_READ_ONLY_ALL_CAM);//Unprotect
            bLockCurJpegFile = AHC_FALSE;
        }
        else
        {
            ret = QuickFileOperation(DCF_FILE_READ_ONLY_ALL_CAM);;//Protect
            bLockCurJpegFile = AHC_TRUE;
        }

        if(ret!=EDIT_FILE_SUCCESS)
        {
            DrawFileOperationResult(ret);
        }
    }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_DC_CABLE_IN)
{
#if (CHARGER_IN_ACT_OTHER_MODE==ACT_RECORD_VIDEO)
    //PhotoPBFunc_SetZoomLock(AHC_FALSE);
    //PhotoPBTimer_Stop();
    //JpgPlaybackParamReset();
    ret = StateSwitchMode(UI_VIDEO_STATE);
    AHC_SetRecordByChargerIn(3);
#elif (CHARGER_IN_ACT_OTHER_MODE == ACT_FORCE_POWER_OFF)
    SetKeyPadEvent(KEY_POWER_OFF);
#endif
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_DC_CABLE_OUT)
{
    AHC_Charger_SetEnable(AHC_FALSE);
#if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
    AHC_SetShutdownByChargerOut(AHC_TRUE);
#endif
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_USB_DETECT)
{
    if(IsAdapter_Connect())
    {
        #if (CHARGER_IN_ACT_OTHER_MODE==ACT_RECORD_VIDEO)
        //PhotoPBFunc_SetZoomLock(AHC_FALSE);
        //PhotoPBTimer_Stop();
        //JpgPlaybackParamReset();
        ret = StateSwitchMode(UI_VIDEO_STATE);
        AHC_SetRecordByChargerIn(3);
        #elif (CHARGER_IN_ACT_OTHER_MODE == ACT_FORCE_POWER_OFF)
        SetKeyPadEvent(KEY_POWER_OFF);
        #endif
    }
    else
    {
        //PhotoPBFunc_SetZoomLock(AHC_FALSE);
        //PhotoPBTimer_Stop();
        //JpgPlaybackParamReset();
        //AHC_OSDUninit();//to fixed mantis:0988313. by cz
        //AHC_SetDisplayOutputDev(DISP_OUT_LCD, AHC_DISPLAY_DUPLICATE_1X);
        //InitOSD();
        #if (USB_MODE_SELECT_EN)
        if (MMPS_USB_NORMAL == MMPS_USB_GetStatus()) {
            StateSwitchMode(UI_USBSELECT_MENU_STATE);
        }
        else
        {
            #ifdef CFG_POWER_ON_ENTER_CAMERA_STATE
            StateSwitchMode(UI_CAMERA_STATE);
            #else
            StateSwitchMode(UI_VIDEO_STATE);
            #endif
        }
        #else
        if(MenuSettingConfig()->uiUSBFunction == MENU_SETTING_USB_MSDC)
        {
            StateSwitchMode(UI_MSDC_STATE);
        }
        else
        {
            StateSwitchMode(UI_PCCAM_STATE);
        }
        #endif
    }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_USB_REMOVED)
{
    if(AHC_USB_GetLastStatus() == AHC_USB_NORMAL) // MSDC mode
    {
        AHC_SetMode(AHC_MODE_IDLE);
        bForce_PowerOff = AHC_TRUE;
        AHC_PowerOff_NormalPath();
    }
    else
    {
        if (AHC_IsDcCableConnect() == AHC_TRUE)
            return;//break;

        AHC_Charger_SetEnable(AHC_FALSE);
        #if (CHARGER_OUT_ACT_OTHER_MODE==ACT_FORCE_POWER_OFF || CHARGER_OUT_ACT_OTHER_MODE==ACT_DELAY_POWER_OFF)
        AHC_SetShutdownByChargerOut(AHC_TRUE);
        #endif
    }
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_SD_DETECT)
{
    AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_SD_REMOVED)
{
#if 0
    PhotoPBFunc_SetZoomLock(AHC_FALSE);
    PhotoPBTimer_Stop();
    JpgPlaybackParamReset();
    AHC_UF_GetCurrentIndex(&ObjSelect);

    if(AHC_TRUE == AHC_SDMMC_GetMountState())
    {
        AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
        AHC_OS_Sleep(100);
        Enable_SD_Power(0 /* Power Off */);
    }
#endif
    if(AHC_TRUE == AHC_SDMMC_IsSD1MountDCF()){
        AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
        AHC_OS_Sleep(100);
        Enable_SD_Power(0 /* Power Off */);
    }

    StateSwitchMode(UI_BROWSER_STATE);
}

#if (HDMI_ENABLE)
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_HDMI_DETECT)
{
    StateSwitchMode(UI_PLAYBACK_STATE);
    //StateSwitchMode(UI_BROWSER_STATE);
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_HDMI_REMOVED)
{
    bShowHdmiWMSG = AHC_TRUE;

    StateSwitchMode(UI_PLAYBACK_STATE);
    //StateSwitchMode(UI_BROWSER_STATE);
}
#endif

#if (TVOUT_ENABLE)
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_TV_DETECT)
{
    //SetTVState(AHC_TV_BROWSER_STATUS);
    StateSwitchMode(UI_PLAYBACK_STATE);
    //StateSwitchMode(UI_BROWSER_STATE);
}
DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_TV_REMOVED)
{
    StateSwitchMode(UI_PLAYBACK_STATE);
}
#endif

DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_JPGPB_UPDATE_MESSAGE)
{
    #if (TVOUT_ENABLE)
        if (AHC_IsTVConnectEx()){

        }else
    #endif
    #if (HDMI_ENABLE)
        if (AHC_IsHdmiConnect()){

        }else
    #endif
        {
            DrawStatePhotoPb_handler_Lcd(ulEvent);
        }
}

DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_JPGPB_UPDATE_LCD)
{
    DrvLCDRefresh();
}

DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_SUB_MODE_ENTER)
{

}

DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_SUB_MODE_EXIT)
{
#if 1
    PhotoPBMode_Update();
#else
    if( MOVPB_MODE == GetCurrentOpMode())
    {
        MoviePBMode_Update();
    }
    else if( JPGPB_MODE == GetCurrentOpMode())
    {
        PhotoPBMode_Update();
    }
    else if( AUDPB_MODE == GetCurrentOpMode())
    {
        AudioPBMode_Update();
    }
    else if( JPGPB_MOVPB_MODE == GetCurrentOpMode())
    {
        UINT32 uiCurrentIdx;
        UINT8  ubFileType;
        AHC_UF_GetCurrentIndex(&uiCurrentIdx);
        AHC_UF_GetFileTypebyIndex(uiCurrentIdx, &ubFileType);
        if ( ubFileType == DCF_OBG_JPG )
            PhotoPBMode_Update();
        else
            MoviePBMode_Update();
    }
#endif
}

DECL_AHC_EV_HANDLER(STATE_PHOTOPB_MODE_EVENT_ENTER_NET_PLAYBACK)
{
    StateSwitchMode(UI_NET_PLAYBACK_STATE);
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE/*0*/ /* SUCCESSFULLY */);
}

UINT32 StatePhotoPlaybackModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    UINT32 ulPhotoPlaybackEvent = 0;

    ulPhotoPlaybackEvent  = KeyParser_JpgPlaybackEvent(ulMsgId, ulEvent, ulParam);
    StatePhotoPlaybackMode(ulPhotoPlaybackEvent);
    StateModeDoHandlerEvent(ulMsgId, ulPhotoPlaybackEvent, ulParam);
    DrvLCDRefresh();
    return 0;
}

void StatePhotoPlaybackMode(UINT32 ulEvent)
{
    UINT32      ulJobEvent  = ulEvent;

    if(ulJobEvent == EVENT_NONE)
        return;

    PhotoPBTimer_ResetCounter();

    switch(ulJobEvent)
    {
        case EVENT_NONE                           :
        break;

        case EVENT_POWER_OFF                      :
            AHC_PowerOff_NormalPath();
        break;

        //Special Event
        case EVENT_LCD_POWER_SAVE           :
            AHC_SwitchLCDBackLight();
        break;

        case EVENT_SWITCH_PANEL_TVOUT:
            AHC_SwitchLCDandTVOUT();
        break;

#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
        case EVENT_SWITCH_TOUCH_PAGE:
            m_ubShowJpgPBTouchPage ^= 1;

            if(m_ubShowJpgPBTouchPage)
            {
                KeyParser_ResetTouchVariable();
                KeyParser_TouchItemRegister(&JpgPBCtrlPage_TouchButton[0], ITEMNUM(JpgPBCtrlPage_TouchButton));

                DrawStateJpgPbPageSwitch(TOUCH_CTRL_PAGE);
            }
            else
            {
                KeyParser_ResetTouchVariable();
                KeyParser_TouchItemRegister(&JpgPBMainPage_TouchButton[0], ITEMNUM(JpgPBMainPage_TouchButton));

                DrawStateJpgPbPageSwitch(TOUCH_MAIN_PAGE);
            }
        break;
#endif

    //Device

        case EVENT_LCD_COVER_OPEN                  :
            LedCtrl_LcdBackLight(AHC_TRUE);
        break;

        case EVENT_LCD_COVER_CLOSE                :
            LedCtrl_LcdBackLight(AHC_FALSE);
        break;

        case EVENT_LCD_COVER_NORMAL               :
        case EVENT_LCD_COVER_ROTATE               :
            AHC_DrawRotateEvent(ulJobEvent);
        break;

        //Update Message
        case EVENT_JPGPB_UPDATE_MESSAGE           :
            DrawStatePhotoPb_handler_Lcd(ulJobEvent);//DrawStateJpgPlaybackUpdate(ulJobEvent);
        break;

        default:
        break;
    }
}

AHC_BOOL  StatePhotoPlaybackModeInitLCD(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevLCD();

    PhotoPBFunc_CheckLCDstatus();
    RTNA_LCD_Backlight(MMP_TRUE);

    ahcRet = PhotoPBMode_Start();
    DrawStatePhotoPb_handler_Lcd(EVENT_JPGPB_MODE_INIT);
    return ahcRet;
}

#if (HDMI_ENABLE)
AHC_BOOL  StatePhotoPlaybackModeInitHDMI(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevHDMI();

    ahcRet = PhotoPBMode_Start();

    DrawStatePhotoPb_handler_Hdmi(EVENT_HDMI_CHANGE_MODE_INIT);

    return ahcRet;
}
#endif

#if (TVOUT_ENABLE)
AHC_BOOL  StatePhotoPlaybackModenitTV(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevTVout();

    ahcRet = PhotoPBMode_Start();
    DrawStatePhotoPb_handler_Tv(EVENT_TV_CHANGE_MODE_INIT);
    return ahcRet;
}
#endif

AHC_BOOL  StatePhotoPlaybackModeShutDown(void* pData)
{
    Component_Display_CloseDevice();
    PhotoPBFunc_SetZoomLock(AHC_FALSE);
    PhotoPBTimer_Stop();
    JpgPlaybackParamReset();
    //AHC_UF_GetCurrentIndex(&ObjSelect); //???

    AHC_SetMode(AHC_MODE_IDLE);

    return AHC_TRUE;
}

