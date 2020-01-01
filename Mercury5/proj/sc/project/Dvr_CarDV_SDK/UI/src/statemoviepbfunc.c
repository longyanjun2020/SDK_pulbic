/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_common.h"
#include "ahc_parameter.h"
#include "ahc_sensor.h"
#include "ahc_mediaplayback.h"
#include "ahc_message.h"
#include "ahc_utility.h"
#include "ahc_display.h"
#include "ahc_audio.h"
#include "ahc_dcf.h"
#include "ahc_uf.h"
#include "ahc_browser.h"
#include "ahc_menu.h"
#include "ahc_os.h"
#include "ahc_media.h"
#include "ahc_usb.h"
#include "ahc_warningmsg.h"
#include "ahc_general_cardv.h"
#include "mediaplaybackctrl.h"
#include "MenuSetting.h"
#include "MenuDrawCommon.h"
#include "MenuTouchButton.h"
#include "keyparser.h"
#include "statemoviepbfunc.h"
#include "statehdmifunc.h"
#include "statetvfunc.h"
#include "drawstatemoviepbfunc.h"
#include "IconPosition.h"
#include "ledcontrol.h"
#include "dsc_charger.h"
#include "dsc_Key.h"
#include "ait_utility.h"
#if WIFI_PORT == 1
#include "netapp.h"
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define MOVPB_OSD_SHOWTIME                           (5)  //unit :sec.
#define MOVPB_TIMER_UNIT                           (200)  //unit :sec.
#define MOVPB_ADJVOLTIMER_UNIT                     (500)  //unit :msec.

/*===========================================================================
 * Global varible
 *===========================================================================*/
AHC_BOOL                    m_bMovieOSDShowUp       = AHC_FALSE;
AHC_BOOL                    m_bMovieOSDForceShowUp  = AHC_TRUE;
UINT32                      MovPBTimerID            = AHC_OS_CREATE_TMR_INT_ERR;
UINT32                      MovPBAdjVolumeTimerID   = AHC_OS_CREATE_TMR_INT_ERR;
UINT32                      MovPbCounter            = 0;
UINT32                      MovPbVolumeCnt          = 0;//delay time=cnt*MOVPB_TIMER_UNIT
UINT32                      m_VideoCurPlayTime      = 0;
UINT8                       m_MovDrawCounter        = 0;
AHC_BOOL                    bLockCurMovFile         = AHC_FALSE;
// Make FFS/REW start from x2
UINT32                      m_MovPlayFFSpeed        = 1;    //MOVPB_MIN_SPEED;
UINT32                      m_MovPlayREWSpeed       = 1;    //MOVPB_MIN_SPEED;
AHC_BOOL                    bEnterMenuPause         = AHC_FALSE;
AHC_BOOL                    gbEnterPowerOffPagePause = AHC_FALSE;
UINT8                       bMovieState             = MOVIE_STATE_PAUSE;
AHC_BOOL                    bMovPbExitFromHdmi      = AHC_FALSE;
AHC_BOOL                    bMovPbEnterToHdmi       = AHC_FALSE;
AHC_BOOL                    bMovPbExitFromTV        = AHC_FALSE;
AHC_BOOL                    bMovPbEnterToTV         = AHC_FALSE;

#if (SUPPORT_TOUCH_PANEL)
AHC_BOOL                    m_ubShowMovPBTouchPage  = AHC_FALSE;
#endif

//UINT8                     bHdmiMovieState  = MOVIE_STATE_STOP;
//UINT8                         m_DelFile        = DEL_FILE_NONE;
/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern UINT32               ObjSelect;
extern AHC_BOOL             bForce_PowerOff;
//extern AHC_BOOL               bForceSwitchBrowser;
extern UINT8                bHdmiMovieState;
//extern UINT8              bTVMovieState;
extern AHC_BOOL             m_ubPlaybackRearCam;
extern AHC_BOOL             bShowHdmiWMSG; //Andy Liu TBD
extern AHC_BOOL             gbAhcDbgBrk;
#if (HDMI_ENABLE)
//extern AHC_BOOL               bHaveInitOsdHdmi;
#endif
/*===========================================================================
 * Extern function
 *===========================================================================*/

//extern void PhotoPBFunc_SDMMC_Out(void);
//extern void AudPBFunc_SDMMC_Out(void);
//extern void InitOSD(void);

/*===========================================================================
 * Main body
 *===========================================================================*/

void MovPBTimer_ResetCounter(void)
{
    MovPbCounter = 0;
}

void MovPBTimer_ISR(void *tmr, void *arg)
{
    UINT32 ustatus;

    if( MOV_STATE_PLAY  == GetMovConfig()->iState ||
        MOV_STATE_FF    == GetMovConfig()->iState ||
        MOV_STATE_PAUSE == GetMovConfig()->iState) {
        AHC_GetVideoPlayStopStatus(&ustatus);

        if ((AHC_VIDEO_PLAY_EOF == ustatus) ||
            (AHC_VIDEO_PLAY_ERROR_STOP == ustatus)) {
            GetMovConfig()->iState = MOV_STATE_STOP;
            m_bMovieOSDShowUp = AHC_TRUE;
            AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0);
            MovPBFunc_ResetPlaySpeed();
            return;
        }
        else if (ustatus == AHC_VIDEO_PLAY_FF_EOS ||
                 ustatus == AHC_VIDEO_PLAY_BW_BOS) {
            GetMovConfig()->iState = MOV_STATE_PAUSE;
            MovPBFunc_ResetPlaySpeed();
            m_bMovieOSDShowUp = AHC_TRUE;
        }

        if( ustatus == AHC_VIDEO_PLAY ||
            ustatus == AHC_VIDEO_PLAY_FF_EOS ||
            ustatus == AHC_VIDEO_PLAY_BW_BOS) {
            if (m_bMovieOSDShowUp) {
                AHC_SendAHLMessageEnable(AHC_TRUE);
                AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0);
            }
            else {
                MovPbCounter = 0;

                if (m_bMovieOSDForceShowUp) {
                    AHC_SendAHLMessageEnable(AHC_TRUE);
                    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0);
                }
            }

            LCDPowerSaveCounterReset();
        }
    }
}

AHC_BOOL MovPBTimer_Start(UINT32 ulTime)
{

    if (AHC_OS_CREATE_TMR_INT_ERR == MovPBTimerID)
    {
        MovPBTimer_ResetCounter();
        MovPBTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, MovPBTimer_ISR, (void*)NULL );
    }

    if(AHC_OS_CREATE_TMR_INT_ERR == MovPBTimerID) {
        AHC_DBG_ERR(1, FG_RED("--E-- Create MovPB Timer fail ID:x%x!!!\n"), MovPBTimerID);
        return AHC_FALSE;
    }
    else {
        //AHC_DBG_MSG(1, FG_GREEN("--E-- Create MovPB Timer ok ID:x%x!!!\n"), MovPBTimerID);
        return AHC_TRUE;
    }
}

void MovPBAdjVolumeTimer_ISR(void *tmr, void *arg)
{
    UINT32 ustatus;

    //if(   MOV_STATE_PLAY  == GetMovConfig()->iState ||
    //  MOV_STATE_FF    == GetMovConfig()->iState ||
    //  MOV_STATE_PAUSE == GetMovConfig()->iState)
    {
        AHC_GetVideoPlayStopStatus(&ustatus);

        if(MovPbVolumeCnt >= 1)
        {
            AHC_DBG_MSG(1, "MovPbVolumeCnt = %d\r\n",MovPbVolumeCnt);
            MovPbVolumeCnt -= 1;

            if(MovPbVolumeCnt == 0)
            {
                AHC_DBG_MSG(1, "BUTTON_OSD_HIDE\r\n");
                AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_OSD_HIDE, 0);
            }
        }
    }
}

//unit:msec
AHC_BOOL MovPBAdjValumeTimer_Start(UINT32 ulTime)
{
    if (MovPBAdjVolumeTimerID == AHC_OS_CREATE_TMR_INT_ERR)
    {
        //MovPBTimer_ResetCounter();
        MovPbVolumeCnt = 0;
        MovPBAdjVolumeTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, MovPBAdjVolumeTimer_ISR, (void*)NULL );

        if(AHC_OS_CREATE_TMR_INT_ERR != MovPBAdjVolumeTimerID) {
            AHC_DBG_MSG(1, FG_GREEN("--E-- Create MovPBVol Timer ok !!!\n"));
            return AHC_TRUE;
        }
    }
    AHC_DBG_ERR(1, FG_RED("--E-- Create MovPBVol Timer fail !!!\n"));
    return AHC_FALSE;
}

AHC_BOOL MovPBAdjVolumeTimer_Stop(void)
{
    UINT8 ret = 0;

    if(MovPBAdjVolumeTimerID != AHC_OS_CREATE_TMR_INT_ERR)
    {
        ret = AHC_OS_StopTimer( MovPBAdjVolumeTimerID, AHC_OS_TMR_OPT_PERIODIC );

        MovPBAdjVolumeTimerID = AHC_OS_CREATE_TMR_INT_ERR;

        if(0 == ret) {
            return AHC_TRUE;
        }
    }

    return AHC_FALSE;
}

AHC_BOOL MovPBTimer_Stop(void)
{
    UINT8 ret = 0;

    if(MovPBTimerID != AHC_OS_CREATE_TMR_INT_ERR)
    {
        ret = AHC_OS_StopTimer( MovPBTimerID, AHC_OS_TMR_OPT_PERIODIC );

        MovPBTimerID = AHC_OS_CREATE_TMR_INT_ERR;

        if(0 == ret) {
            return AHC_TRUE;
        }
    }

    return AHC_FALSE;
}

void MovPBFunc_CheckLCDstatus(void)
{
    UINT8 status;

    AHC_LCD_GetStatus(&status);

    AHC_SetDisplayMode(DISPLAY_MODE_DISABLE);
    AHC_SetKitDirection(status, AHC_TRUE, AHC_SNR_NOFLIP, AHC_FALSE);
}

void MovPBFunc_SetOSDShowStatus(AHC_BOOL state)
{
    m_bMovieOSDShowUp = state;
}

AHC_BOOL MovPBFunc_GetOSDShowStatus(void)
{
    return m_bMovieOSDShowUp;
}

void MovPBFunc_ResetPlaySpeed(void)
{
    m_MovPlayFFSpeed    = 1;//MOVPB_MIN_SPEED;
    m_MovPlayREWSpeed   = 1;//MOVPB_MIN_SPEED;
}

AHC_BOOL MovPBFunc_SeekSOS(void)
{
    AHC_SetVideoPlayStartTime(0);

    #if (MOVIE_PB_FF_EOS_ACTION==EOS_ACT_PAUSE_AT_FIRST_FRAME)
    AHC_SetParam(PARAM_ID_MOVIE_AUTO_PLAY, 1);
    #endif

    MovPlaybackParamReset();
    MediaPlaybackConfig(PLAYBACK_CURRENT);
    MovPlayback_Play();
    MovPBFunc_ResetPlaySpeed();

    #if (MOVIE_PB_FF_EOS_ACTION==EOS_ACT_PAUSE_AT_FIRST_FRAME)
    AHC_SetParam(PARAM_ID_MOVIE_AUTO_PLAY, 0);
    UpdateMovPBStatus(MOVIE_STATE_PAUSE);
    DrawStateMovPlaybackUpdate(EVENT_MOVPB_PAUSE/*EVENT_MOVPB_TOUCH_PAUSE_PRESS*/);
    #else
    UpdateMovPBStatus(MOVIE_STATE_PLAY);
    DrawStateMovPlaybackUpdate(EVENT_MOVPB_PLAY_START/*EVENT_MOVPB_TOUCH_PLAY_PRESS*/);
    #endif

    return AHC_TRUE;
}

AHC_BOOL MoviePBMode_Start(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    m_bMovieOSDShowUp = AHC_TRUE;

    AHC_SetMode(AHC_MODE_IDLE);

    MovPlaybackParamReset();
    //MovPBFunc_CheckLCDstatus();
    MediaPlaybackConfig(PLAYBACK_CURRENT);

    DBG_AutoTestPrint(ATEST_ACT_PB_VID_0x0003, ATEST_STS_START_0x0001, 0, 0, gbAhcDbgBrk);
    ahc_ret = MovPlayback_Play();
    MovPBFunc_ResetPlaySpeed();

#if (QUICK_FILE_EDIT_EN)
    bLockCurMovFile = AHC_CheckCurFileLockStatus();
#endif

    if(AHC_TRUE == ahc_ret )
    {
#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
        KeyParser_ResetTouchVariable();
        KeyParser_TouchItemRegister(&MovPBMainPage_TouchButton[0], ITEMNUM(MovPBMainPage_TouchButton));
#endif
        if(!bMovPbExitFromHdmi && !bMovPbExitFromTV)
        {
            UpdateMovPBStatus(MOVIE_STATE_PLAY);
        }
        else
        {
            bMovPbExitFromHdmi = AHC_FALSE;
            bMovPbExitFromTV   = AHC_FALSE;
        }
        MovPBTimer_Start(MOVPB_TIMER_UNIT);
        DrawStateMovPlaybackUpdate(EVENT_MOVPB_MODE_INIT);
    }

    return ahc_ret;
}

void MoviePBMode_Update(void)
{
    UINT32  MaxObjIdx;

    MaxObjIdx = AHC_GetMappingFileNum(FILE_MOVIE);

    if(MaxObjIdx == 0)
    {
        //MovPBTimer_Stop();
        //MovPlaybackParamReset();
        //AHC_UF_GetCurrentIndex(&ObjSelect);
        StateSwitchMode(UI_BROWSER_STATE);
        return;
    }

    if(GetMovConfig()->iState == MOV_STATE_PAUSE)
    {
        if(bEnterMenuPause==AHC_TRUE)
        {
            MovPlayback_Resume();
            bEnterMenuPause = AHC_FALSE;
        }
        else
        {
            UpdateMovPBStatus(MOVIE_STATE_PAUSE);
        }
    }

#if (QUICK_FILE_EDIT_EN)
    bLockCurMovFile = AHC_CheckCurFileLockStatus();
#endif

#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
    KeyParser_ResetTouchVariable();
    KeyParser_TouchItemRegister(&MovPBMainPage_TouchButton[0], ITEMNUM(MovPBMainPage_TouchButton));
#endif

    DrawStateMovPbMode_Update();
}

//******************************************************************************
//
//                              AHC State Movie Playback Mode
//
//******************************************************************************

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_KEY_UP)
{
    MovPBAdjValumeTimer_Start(MOVPB_ADJVOLTIMER_UNIT);
    MovPbVolumeCnt = 5;//delay time=cnt*MOVPB_ADJVOLTIMER_UNIT
    AHC_ChangeVolume(AHC_FALSE, 1);
    DrawStateMovPlaybackUpdate(EVENT_KEY_TELE_PRESS);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_KEY_DOWN)
{
    MovPBAdjValumeTimer_Start(MOVPB_ADJVOLTIMER_UNIT);
    MovPbVolumeCnt = 5;
    AHC_ChangeVolume(AHC_FALSE, 0);
    DrawStateMovPlaybackUpdate(EVENT_KEY_WIDE_PRESS);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_MOVPB_KEY_LEFT)
{
    //TL_2018_0112: Patch -> When user click backward key repeatedly , device will jump to browser without warning.
    UINT32 ulCurTime;
    AHC_GetVideoCurrentPlayTime(&ulCurTime);
    if (ulCurTime == 1) {
        return;
    }
    if(bMovieState!=MOVIE_STATE_FF || m_MovPlayREWSpeed==1)
    {
        m_MovPlayREWSpeed = ( (m_MovPlayREWSpeed<<1) > MOVPB_MAX_SPEED )?(MOVPB_MIN_SPEED):(m_MovPlayREWSpeed<<1);
    }
    AHC_VIDPLAY_SetPlaySpeed(AHC_PB_MOVIE_BACKWARD_RATE, m_MovPlayREWSpeed+1);
    UpdateMovPBStatus(MOVIE_STATE_REW);
    MovPBTimer_Start(MOVPB_TIMER_UNIT);
    MovPlayback_Backward();
    DrawStateMovPlaybackUpdate(EVENT_MOVPB_UPDATE_MESSAGE);
    DrawStateMovPlaybackUpdate(EVENT_KEY_LEFT/*EVENT_MOVPB_TOUCH_BKWD_PRESS*/);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_MOVPB_KEY_RIGHT)
{
    //TL_2018_0112: Patch -> When user click forward key repeatedly , device will jump to browser without warning.
    UINT32 ulCurTime, ulTotalTime;
    GetMovTotalTime(&ulTotalTime);
    AHC_GetVideoCurrentPlayTime(&ulCurTime);
    if (ulCurTime >= ulTotalTime) {
        return;
    }
    if(bMovieState!=MOVIE_STATE_REW || m_MovPlayFFSpeed==1)
    {
        m_MovPlayFFSpeed = ( (m_MovPlayFFSpeed<<1) > MOVPB_MAX_SPEED )?(MOVPB_MIN_SPEED):(m_MovPlayFFSpeed<<1);
    }
    AHC_VIDPLAY_SetPlaySpeed(AHC_PB_MOVIE_FAST_FORWARD_RATE, m_MovPlayFFSpeed+1);
    UpdateMovPBStatus(MOVIE_STATE_FF);
    MovPBTimer_Start(MOVPB_TIMER_UNIT);
    MovPlayback_Forward();
    DrawStateMovPlaybackUpdate(EVENT_MOVPB_UPDATE_MESSAGE);
    DrawStateMovPlaybackUpdate(EVENT_KEY_RIGHT/*EVENT_MOVPB_TOUCH_FRWD_PRESS*/);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_MOVPB_PLAY_START)
{
    UINT32      uState;
    AHC_GetSystemStatus(&uState);

    switch(uState)
    {
        case STATE_MOV_IDLE :
            DrawStateMovPlaybackUpdate(EVENT_KEY_TELE_STOP);
            UpdateMovPBStatus(MOVIE_STATE_PLAY);
            MediaPlaybackConfig(PLAYBACK_CURRENT);
            MovPlayback_Play();
            DrawStateMovPlaybackUpdate(EVENT_MOVPB_PLAY_START/*EVENT_MOVPB_TOUCH_PLAY_PRESS*/);
        #if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
            KeyParser_ResetTouchVariable();
            KeyParser_TouchItemRegister(&MovPBCtrlPage_TouchButton[0], ITEMNUM(MovPBCtrlPage_TouchButton));
        #endif
        break;

        case STATE_MOV_EXECUTE :
            if(MOV_STATE_FF == GetMovConfig()->iState)
            {
                UpdateMovPBStatus(MOVIE_STATE_PLAY);
                MovPlayback_NormalSpeed();
                DrawStateMovPlaybackUpdate(EVENT_MOVPB_PLAY_START/*EVENT_MOVPB_TOUCH_PLAY_PRESS*/);
            }
            else
            {
                UpdateMovPBStatus(MOVIE_STATE_PAUSE);
                MovPlayback_Pause();
                DrawStateMovPlaybackUpdate(EVENT_MOVPB_PAUSE/*EVENT_MOVPB_TOUCH_PAUSE_PRESS*/);
            }
        #if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
            KeyParser_ResetTouchVariable();
            KeyParser_TouchItemRegister(&MovPBCtrlPage_TouchButton[0], ITEMNUM(MovPBCtrlPage_TouchButton));
        #endif
        break;

        case STATE_MOV_PAUSE   :
            UpdateMovPBStatus(MOVIE_STATE_PLAY);
            MovPlayback_NormalSpeed();
            MovPlayback_Resume();
            DrawStateMovPlaybackUpdate(EVENT_MOVPB_PLAY_START/*EVENT_MOVPB_TOUCH_PLAY_PRESS*/);
        #if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
            KeyParser_ResetTouchVariable();
            KeyParser_TouchItemRegister(&MovPBCtrlPage_TouchButton[0], ITEMNUM(MovPBCtrlPage_TouchButton));
        #endif
        break;

        default                :
        break;
    }
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_MOVPB_MODE)
{
    AHC_BOOL ret;
#if 0
    MovPBTimer_Stop();
    MovPBAdjVolumeTimer_Stop();
    MovPlaybackParamReset();
    DrawStateMovPlaybackUpdate(EVENT_KEY_WIDE_STOP);
    AHC_UF_GetCurrentIndex(&ObjSelect);
#endif

    ret = StateSwitchMode(UI_BROWSER_STATE);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_KEY_MENU)
{
#if CR_USE_STATE_SWITCH_SUB_MODE == 0
    AHC_BOOL    ahcRet = AHC_TRUE;
    UI_STATE_ID ubParentUIState = 0;
#endif
    //TL_2018_0704: Patch -> When user click menu repeatedly , device stop after leaving menu.
    UINT32 ulCurTime, ulTotalTime;
    GetMovTotalTime(&ulTotalTime);
    AHC_GetVideoCurrentPlayTime(&ulCurTime);
    if (ulCurTime >= ulTotalTime) {
        return;
    }
    {
        if(GetMovConfig()->iState == MOV_STATE_PLAY || GetMovConfig()->iState == MOV_STATE_FF)
        {
            MovPlayback_Pause();
            bEnterMenuPause = AHC_TRUE;
        }
        else if(GetMovConfig()->iState == MOV_STATE_PAUSE)
        {
            bEnterMenuPause = AHC_FALSE;
        }
        DrawMovPB_VolumeBar(AHC_TRUE);
#if 1
        #if CR_USE_STATE_SWITCH_SUB_MODE
        StateReplaceSubMode(UI_PLAYBACK_MENU_STATE);
        #else

        StateModeGetParent(uiGetCurrentState(), &ubParentUIState);
        if(UI_STATE_UNSUPPORTED != ubParentUIState){
            AHC_DBG_MSG(1, "%s,%d, DettachSubMode:%d\r\n", __func__, __LINE__, uiGetCurrentState());
            ahcRet = StateDetachSubMode();
            if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, ahcRet);}
        }
        ahcRet = StateAttachSubMode(UI_PLAYBACK_MENU_STATE);
        if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0,ahcRet); /*return ahcRet;*/}
        #endif
#else
        StateSwitchMode(UI_PLAYBACK_MENU_STATE);
#endif
    }
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_MOVPB_PREV_PRESS)
{
    MediaPlaybackConfig(PLAYBACK_PREVIOUS);
    MovPlayback_Play();
    DrawStateMovPlaybackUpdate(ulEvent);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_MOVPB_NEXT_PRESS)
{
    MediaPlaybackConfig(PLAYBACK_NEXT);
    MovPlayback_Play();
    DrawStateMovPlaybackUpdate(ulEvent);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_VIDEO_PREVIEW)
{
    AHC_BOOL ret;

    ret = StateSwitchMode(UI_VIDEO_STATE);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_CAMERA_PREVIEW)
{
    AHC_BOOL ret;

    ret = StateSwitchMode(UI_CAMERA_STATE);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_FILE_DELETING)
{
    AHC_BOOL ret;

    ret = QuickFileOperation(DCF_FILE_DELETE_ALL_CAM);
    if(ret!=EDIT_FILE_SUCCESS)
    {
        DrawFileOperationResult(ret);
    }
    else
    {
        ret = StateSwitchMode(UI_BROWSER_STATE);
    }
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_LOCK_FILE_M)
{
    AHC_BOOL ret;

    if(AHC_CheckCurFileLockStatus())
    {
        ret = QuickFileOperation(DCF_FILE_NON_READ_ONLY_ALL_CAM);//Unprotect
        bLockCurMovFile = AHC_FALSE;
    }
    else
    {
        ret = QuickFileOperation(DCF_FILE_READ_ONLY_ALL_CAM);;//Protect
        bLockCurMovFile = AHC_TRUE;
    }

    if(ret!=EDIT_FILE_SUCCESS)
    {
        DrawFileOperationResult(ret);
    }
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_DC_CABLE_IN)
{
#if (CHARGER_IN_ACT_OTHER_MODE==ACT_RECORD_VIDEO)
    ret = StateSwitchMode(UI_VIDEO_STATE);
    AHC_SetRecordByChargerIn(3);
#elif (CHARGER_IN_ACT_OTHER_MODE == ACT_FORCE_POWER_OFF)
    SetKeyPadEvent(KEY_POWER_OFF);
#endif
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_DC_CABLE_OUT)
{

}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_USB_DETECT)
{
    if(IsAdapter_Connect())
    {
        #if (CHARGER_IN_ACT_OTHER_MODE==ACT_RECORD_VIDEO)
        ret = StateSwitchMode(UI_VIDEO_STATE);
        AHC_SetRecordByChargerIn(3);
        #elif (CHARGER_IN_ACT_OTHER_MODE == ACT_FORCE_POWER_OFF)
        SetKeyPadEvent(KEY_POWER_OFF);
        #endif
    }
    else
    {
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

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_USB_REMOVED)
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

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_SD_DETECT)
{
    AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_SD_REMOVED)
{
#if 0
    MovPBFunc_SDMMC_Out();

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
DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_HDMI_DETECT)
{
    AHC_GetVideoCurrentPlayTime(&m_VideoCurPlayTime);
    AHC_SetVideoPlayStartTime(m_VideoCurPlayTime);
    //bMovPbEnterToTV = AHC_TRUE;
    StateSwitchMode(UI_PLAYBACK_STATE);

    //StateSwitchMode(UI_BROWSER_STATE);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_HDMI_REMOVED)
{
    bShowHdmiWMSG = AHC_TRUE;

    AHC_GetVideoCurrentPlayTime(&m_VideoCurPlayTime);
    AHC_SetVideoPlayStartTime(m_VideoCurPlayTime);
    //bMovPbEnterToTV = AHC_TRUE;
    StateSwitchMode(UI_PLAYBACK_STATE);

}
#endif

#if (TVOUT_ENABLE)
DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_TV_DETECT)
{
#if 1 //TBD
    AHC_GetVideoCurrentPlayTime(&m_VideoCurPlayTime);
    AHC_SetVideoPlayStartTime(m_VideoCurPlayTime);
    //bMovPbEnterToTV = AHC_TRUE;
    StateSwitchMode(UI_PLAYBACK_STATE);
#else
    //SetTVState(AHC_TV_BROWSER_STATUS);
    StateSwitchMode(UI_BROWSER_STATE);
#endif
}
DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_TV_REMOVED)
{
    AHC_GetVideoCurrentPlayTime(&m_VideoCurPlayTime);
    AHC_SetVideoPlayStartTime(m_VideoCurPlayTime);
    //bMovPbEnterToTV = AHC_TRUE;
    StateSwitchMode(UI_PLAYBACK_STATE);
}
#endif

#if (UVC_HOST_VIDEO_ENABLE)
DECL_AHC_EV_HANDLER(STATE_PLAYBACK_MODE_EVENT_USB_B_DEVICE_DETECT)
{
    AHC_USB_PauseDetection(0);
    if((AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_DETECTED) ||
            (AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_REMOVED)){
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else{
        AHC_PRINT_RET_ERROR(0, 0);
        AHC_DBG_ERR(1, "KeyEventID: BUTTON_USB_B_DEVICE_DETECTED,REMOVED is interrupted.\r\n");
    }
}

DECL_AHC_EV_HANDLER(STATE_PLAYBACK_MODE_EVENT_USB_B_DEVICE_REMOVED)
{
    AHC_USB_PauseDetection(0);
    if((AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_DETECTED) ||
            (AHC_GetCurKeyEventID() == BUTTON_USB_B_DEVICE_REMOVED)){
        AHC_SetCurKeyEventID(EVENT_NONE);
    }
    else{
        AHC_PRINT_RET_ERROR(0, 0);
        AHC_DBG_ERR(1, "KeyEventID: BUTTON_USB_B_DEVICE_DETECTED,REMOVED is interrupted.\r\n");
    }
}
#endif

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_MOVPB_UPDATE_MESSAGE)
{
    AHC_BOOL ret;

    if(MOV_STATE_STOP == GetMovConfig()->iState)
    {
#if 0
        MovPBTimer_Stop();
        MovPBAdjVolumeTimer_Stop();
        MovPlaybackParamReset();
        DrawStateMovPlaybackUpdate(EVENT_KEY_WIDE_STOP);
#endif

        //AHC_UF_GetCurrentIndex(&ObjSelect); //???
        ret = StateSwitchMode(UI_BROWSER_STATE);
        return;
    }
    else if(MOV_STATE_PAUSE == GetMovConfig()->iState)
    {
        UINT32  ulState;

        AHC_GetVideoPlayStopStatus(&ulState);

        if(ulState == AHC_VIDEO_PLAY_FF_EOS || ulState == AHC_VIDEO_PLAY_BW_BOS)
        {
            #if ( MOVIE_PB_FF_EOS_ACTION==EOS_ACT_RESTART || \
                  MOVIE_PB_FF_EOS_ACTION==EOS_ACT_PAUSE_AT_FIRST_FRAME )
            MovPBFunc_SeekSOS();
            #endif
        }
    }

    if(m_bMovieOSDShowUp)
        DrawStateMovPlaybackUpdate(EVENT_MOVPB_UPDATE_MESSAGE);
    else
        DrawStateMovPlaybackUpdate(EVENT_MOVPB_OSD_HIDE);
}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_SUB_MODE_ENTER)
{

}

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_SUB_MODE_EXIT)
{
#if 1
    MoviePBMode_Update();
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

DECL_AHC_EV_HANDLER(STATE_MOVPB_MODE_EVENT_ENTER_NET_PLAYBACK)
{
#if 0
    MovPBTimer_Stop();
    MovPBAdjVolumeTimer_Stop();
    MovPlaybackParamReset();
#endif
    StateSwitchMode(UI_NET_PLAYBACK_STATE);
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}

UINT32 StateMoviePlaybackModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    UINT32 ulMoviePlaybackEvent = 0;

    ulMoviePlaybackEvent  = KeyParser_MovPlaybackEvent(ulMsgId, ulEvent, ulParam);
    StateMoviePlaybackMode(ulMoviePlaybackEvent);
    StateModeDoHandlerEvent(ulMsgId, ulMoviePlaybackEvent, ulParam);

    return 0;
}

void StateMoviePlaybackMode(UINT32 ulEvent)
{
    UINT32      ulJobEvent  = ulEvent;
    UINT32      uState;

    if(ulJobEvent == EVENT_NONE)
        return;

    if(EVENT_MOVPB_UPDATE_MESSAGE != ulJobEvent)
        MovPBTimer_ResetCounter();

    AHC_GetSystemStatus(&uState);

    switch(ulJobEvent)
    {
        case EVENT_SLIDESHOW_OSD_HIDE:
        case EVENT_KEY_WIDE_STOP : //Clear VolumeBar
        case EVENT_KEY_TELE_STOP :
            DrawStateMovPlaybackUpdate(EVENT_KEY_WIDE_STOP);
        break;

        case EVENT_MOVPB_MODE:
            #if AHC_MULTI_TRACK_EN
            m_ubPlaybackRearCam = (m_ubPlaybackRearCam == AHC_TRUE)? AHC_FALSE : AHC_TRUE;
            AHC_GetVideoCurrentPlayTime(&m_VideoCurPlayTime);
            MovPlaybackParamReset();
            AHC_SetMode(AHC_MODE_IDLE);
            if( m_ubPlaybackRearCam == AHC_TRUE )
            {
                MMPS_VIDPLAY_SetCurrentTrack(1);  //playback rear cam.
            }
            else
            {
                MMPS_VIDPLAY_SetCurrentTrack(0);  //playback front cam.
            }
            AHC_SetVideoPlayStartTime(m_VideoCurPlayTime);
            MovPlayback_Play();
            #endif
        break;

        case EVENT_POWER_OFF                      :
            if(GetMovConfig()->iState == MOV_STATE_PLAY || GetMovConfig()->iState == MOV_STATE_FF)
            {
                MovPlayback_Pause();
                gbEnterPowerOffPagePause = AHC_TRUE;
            }
            else if(GetMovConfig()->iState == MOV_STATE_PAUSE)
            {
                gbEnterPowerOffPagePause = AHC_FALSE;
            }

            AHC_PowerOff_NormalPath();
        break;

        case EVENT_LCD_POWER_SAVE           :
            AHC_SwitchLCDBackLight();
        break;
        case EVENT_SWITCH_PANEL_TVOUT:
            AHC_SwitchLCDandTVOUT();
        break;

#if (SUPPORT_TOUCH_PANEL)//disable temporally, wait touch UI
        case EVENT_SWITCH_TOUCH_PAGE:
            m_ubShowMovPBTouchPage ^= 1;

            if(m_ubShowMovPBTouchPage)
            {
                KeyParser_ResetTouchVariable();
                KeyParser_TouchItemRegister(&MovPBCtrlPage_TouchButton[0], ITEMNUM(MovPBCtrlPage_TouchButton));

                DrawStateMovPbPageSwitch(TOUCH_CTRL_PAGE);
            }
            else
            {
                KeyParser_ResetTouchVariable();
                KeyParser_TouchItemRegister(&MovPBMainPage_TouchButton[0], ITEMNUM(MovPBMainPage_TouchButton));

                DrawStateMovPbPageSwitch(TOUCH_MAIN_PAGE);
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
        default:
        break;
    }
}

AHC_BOOL StateMoviePlaybackModeInitLCD(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevLCD();

    MovPBFunc_CheckLCDstatus();
    RTNA_LCD_Backlight(MMP_TRUE);

    ahcRet = MoviePBMode_Start();
    return ahcRet;
}

#if (SUPPORT_HDMI)
AHC_BOOL StateMoviePlaybackModeInitHDMI(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    AHC_DISPLAY_OUTPUTPANEL sCurDevice;

    //Get current output device.
    AHC_GetDisplayOutputDev(&sCurDevice);

    RTNA_LCD_Backlight(MMP_FALSE);
#ifdef CFG_ENBLE_PANEL_SLEEP
    RTNA_LCD_Enter_Sleep();
#endif

    ahcRet = AHC_SwitchDisplayOutputDevHDMI();

    ahcRet = MoviePBMode_Start();
    return ahcRet;
}
#endif

#if (TVOUT_ENABLE)
AHC_BOOL StateMoviePlaybackModeInitTV(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_SwitchDisplayOutputDevTVout();
    ahcRet = MoviePBMode_Start();

    return ahcRet;
}
#endif

AHC_BOOL StateMoviePlaybackModeShutDown(void* pData)
{
    MovPBTimer_Stop();
    MovPBAdjVolumeTimer_Stop();
    MovPlaybackParamReset();

    //DrawStateMovPlaybackUpdate(EVENT_KEY_WIDE_STOP); //???
    //AHC_UF_GetCurrentIndex(&ObjSelect); //???

    AHC_SetMode(AHC_MODE_IDLE);

    return AHC_TRUE;
}


