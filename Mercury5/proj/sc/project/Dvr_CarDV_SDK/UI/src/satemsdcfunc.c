/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_config.h"
#include "ahc_common.h"
#include "ahc_sensor.h"
#include "ahc_menu.h"
#include "ahc_media.h"
#include "ahc_parameter.h"
#include "ahc_usb.h"
#include "ahc_warningmsg.h"
#include "ahc_os.h"
#include "ahc_message.h"
#include "ahc_general_cardv.h"
#include "ahc_display.h"
#include "keyparser.h"
#include "statemsdcfunc.h"
#include "MenuSetting.h"
#include "ledcontrol.h"
#include "dsc_charger.h"
#include "drawstatemsdcfunc.h"
#include "mmps_usb.h"
#include "ait_utility.h"
#if WIFI_PORT == 1
#include "netapp.h"
#endif

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE == 1)
#include "pCam_api.h"
#include "statevideofunc.h"
#endif
#include "mmps_system.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

static AHC_BOOL bUsbMsdcMode        = AHC_FALSE;
static UINT32   MSDCCounter         = 0;
static UINT8    MSDCPowerOffCounter = 0;
UINT32          MSDCTimerID         = 0;
UINT8           ubUSBLedStatus      = AHC_TRUE;
UINT8           gi=0;

static AHC_BOOL bUsbPCCAMMode       = AHC_FALSE;

/*===========================================================================
 * Local function
 *===========================================================================*/ 

#ifdef  MSDC_STATUS_LED
static void MsdcLedUpdate(void);
#endif

/*===========================================================================
 * Extern varible
 *===========================================================================*/

extern AHC_BOOL bForce_PowerOff;
extern AHC_BOOL bChargeFull;
extern AHC_BOOL gbAhcDbgBrk;

/*===========================================================================
 * Main body
 *===========================================================================*/ 

void MSDCTimer_ResetCounter(void)
{
    MSDCCounter = 0;
}

void MSDCTimer_ISR(void *tmr, void *arg)
{  
    MSDCCounter++;
    
    if( MSDCCounter & 0x01)
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0);
}

AHC_BOOL MSDCTimer_Start(UINT32 ulTime)
{
    MSDCTimer_ResetCounter();
    
    MSDCTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, MSDCTimer_ISR, (void*)NULL );
    
    if(AHC_OS_CREATE_TMR_INT_ERR != MSDCTimerID)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

AHC_BOOL MSDCTimer_Stop(void)
{
    UINT8 ret = 0;
    
    ret = AHC_OS_StopTimer(MSDCTimerID, AHC_OS_TMR_OPT_NONE);
  
    if(ret)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

AHC_BOOL MSDCFunc_Status(void)
{
    return bUsbMsdcMode;
}

#if (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) 
#include "mmpf_usbvend.h"
#define MSDC_AIT_SCSI_CUSTOMER_CMD_OK (0x00)
#define MSDC_AIT_SCSI_CUSTOMER_CMD_FAIL (0x01)

MMP_ULONG MSDCFunc_AIT_SCSI_CUSTOMER_CB(const MMP_UBYTE *pCmd, MMP_UBYTE *pTxBuf, MMP_ULONG ulCmdLen, MMP_ULONG ulMaxTxBufLen)
{
    MMP_ULONG ulTxBufLen = 0;
    
    printc(FG_RED("\r\n\r\n%s,%d\r\n\r\n"), __func__, __LINE__);
    printc(FG_RED("Cmd:0x%x\r\n"), pCmd[0]);

    switch(pCmd[0]){
        case 1:
#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE)            
            memset((void *)pTxBuf, 0x0, ulMaxTxBufLen);
            
            pTxBuf[0] = MSDC_AIT_SCSI_CUSTOMER_CMD_OK;

            ulTxBufLen = 16;
            AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_MSDC_SCSI_CMD_SWITCH_UVC_MODE, 0);            
#endif            
            break;
        case 2:
            break;
        default:
            break;            
    }
    
    return ulTxBufLen;
}
#endif

AHC_BOOL MSDCFunc_Enable(AHC_BOOL bEnable)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    if( bEnable )
    {
        if( !bUsbMsdcMode )
        {
        #if (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) 
            AHC_AitScsiCustomerCmd_Register_CB((MSDC_AIT_SCSI_CUSTOMER_CB)MSDCFunc_AIT_SCSI_CUSTOMER_CB);
        #endif
            bUsbMsdcMode = AHC_TRUE;
            ahc_ret = AHC_SetMode(AHC_MODE_USB_MASS_STORAGE);
        }
    }
    else
    {
        if( bUsbMsdcMode )
        {
            bUsbMsdcMode = AHC_FALSE;
            ahc_ret = AHC_SetMode(AHC_MODE_IDLE);
        }
    }

    return ahc_ret;
}

AHC_BOOL PCCAMFunc_Enable(AHC_BOOL bEnable)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    if( bEnable )
    {
        if( !bUsbPCCAMMode )
        {
            bUsbPCCAMMode = AHC_TRUE;
            ahc_ret = AHC_SetMode(AHC_MODE_USB_WEBCAM);
        }
    }
    else
    {
        if( bUsbPCCAMMode )
        {
            bUsbPCCAMMode = AHC_FALSE;
            ahc_ret = AHC_SetMode(AHC_MODE_IDLE);
        }
    }

    return ahc_ret;
}

void MSDC_Func_CheckLCDstatus(void)
{
    UINT8 status;

    if ((AHC_FALSE == AHC_IsTVConnectEx()) && (AHC_FALSE == AHC_IsHdmiConnect()))
    {
        AHC_LCD_GetStatus(&status);
            
        AHC_SetKitDirection(status, AHC_TRUE, AHC_SNR_NOFLIP, AHC_FALSE);
    }
}

AHC_BOOL MSDCMode_Start(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = MSDCFunc_Enable(AHC_TRUE);
    
    MSDC_Func_CheckLCDstatus();
    MSDCTimer_ResetCounter();
    MSDCTimer_Start(100);
        
    if(AHC_TRUE == ahc_ret )
    {
        DrawStateMSDCUpdate( EVENT_USB_DETECT );

#ifdef CFG_MSDC_BYPASS_CHANGE_ICON //may be defined in config_xxx.h
        #if OSD_SHOW_BATTERY_STATUS == 1
        AHC_EnableChargingIcon(AHC_TRUE);
        #endif
#endif
    }

    return ahc_ret;
}

AHC_BOOL PCCAMMode_Start(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

#if (SUPPORT_UVC_FUNC)
    ahc_ret = PCCAMFunc_Enable(AHC_TRUE);
    MSDCTimer_Start(100);
        
    if(AHC_TRUE == ahc_ret )
    {
        printc("%s ,share with MSDC draw \r\n", __FUNCTION__);
        DrawStateMSDCUpdate( EVENT_USB_DETECT );

    #ifdef CFG_MSDC_BYPASS_CHANGE_ICON //may be defined in config_xxx.h
        #if OSD_SHOW_BATTERY_STATUS == 1
        AHC_EnableChargingIcon(AHC_TRUE);
        #endif
    #endif
    }
#else
    AHC_PRINT_RET_ERROR(0, 0);
#endif

    return ahc_ret;
}

//******************************************************************************
//
//                              AHC State MSDC Mode
//
//******************************************************************************

UINT32 StateMSDCModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam)
{
    UINT32 ulMSDCEvent = 0;
    
    ulMSDCEvent  = KeyParser_MsdcEvent(ulMsgId, ulEvent, ulParam);
    StateMSDCMode(ulMSDCEvent);
    StateModeDoHandlerEvent(ulMsgId, ulMSDCEvent, ulParam);

    return 0;    
}

void StateMSDCMode( UINT32 ulEvent )
{       
    switch( ulEvent )
    {
        case EVENT_NONE                           :
        break;
        
        case EVENT_POWER_OFF                      :
            AHC_PowerOff_NormalPath();
        break;
        
        //Device
        case EVENT_USB_DETECT                     :
        break;
    #ifdef NET_SYNC_PLAYBACK_MODE
        case EVENT_NET_ENTER_PLAYBACK :
            if(AHC_USB_GetLastStatus() == AHC_USB_NORMAL) // MSDC/PCCAM mode
            {
                AHC_USB_OP_MODE uiMode;
                AHC_GetUsbMode(&uiMode);

                bUsbMsdcMode = AHC_FALSE;
                MSDCTimer_Stop();
                AHC_USB_DisConnectDevice();
                if (uiMode == AHC_USB_MODE_MASS_STORAGE) {
                    RTNA_DBG_Str(0, "AHC_USB_MODE_MASS_STORAGE\r\n");
                    AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
                    StateSwitchMode(UI_NET_PLAYBACK_STATE);

                    // Unlock HDMI/TV state when USB plug-out
                    //AHC_LockHdmiConnectionStatus(AHC_FALSE, AHC_FALSE);
                    //AHC_LockTVConnectionStatus(AHC_FALSE, AHC_FALSE);
                }
                else
                if (uiMode == AHC_USB_MODE_WEBCAM) {
                    RTNA_DBG_Str(0, "AHC_USB_MODE_WEBCAM\r\n");
                    PCCAMFunc_Enable(AHC_FALSE);
                    StateSwitchMode(UI_NET_PLAYBACK_STATE);    
                }
                else
                {
                    StateSwitchMode(UI_NET_PLAYBACK_STATE);   
                }
                // Unlock HDMI/TV state when USB plug-out
                //AHC_LockHdmiConnectionStatus(AHC_FALSE, AHC_FALSE);
                //AHC_LockTVConnectionStatus(AHC_FALSE, AHC_FALSE);
            }
    
            CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
        break;
    #endif
        
        case EVENT_LCD_COVER_OPEN                  :
            LedCtrl_LcdBackLight(AHC_TRUE);
        break;
        
        case EVENT_LCD_COVER_CLOSE                :
            LedCtrl_LcdBackLight(AHC_FALSE);
        break;    
            
        case EVENT_LCD_COVER_NORMAL               :
        case EVENT_LCD_COVER_ROTATE               :
            AHC_DrawRotateEvent(ulEvent);   
        break;

        case EVENT_MSDC_UPDATE_MESSAGE:
            if(!AHC_IsUsbConnect())
            {           
                if(MSDCPowerOffCounter == MSDC_POWEROFF_COUNT)
                {
                    printc("--I-- exceed to MSDC_POWEROFF_COUNT, going to power off\r\n");
                    
                    #ifdef MSDC_OUT_NOT_OFF
                    // Not to Power off after MSDC out
                    #else
                    bForce_PowerOff = AHC_TRUE; 
                    AHC_PowerOff_NormalPath();
                    #endif
                }

                MSDCPowerOffCounter++;
            }
            else
            {
                #ifdef  MSDC_STATUS_LED
                MsdcLedUpdate();
                #endif

                MSDCPowerOffCounter = 0;
            }
        break;
            
        default:
        break;
    }
}

#ifdef  MSDC_STATUS_LED

static int _ledblk = 0;
static int _ledper = 0;
static int _ledcnt = 0;

void _uiMsdcLed(int rw, int err)
{
    if (err == 0) {
        _ledblk = 1;
        _ledper = 5;
    }
}

void MsdcLedUpdate(void)
{
    if (_ledcnt > 0) {
        // MSDC is reading or writing 
        LedCtrl_ButtonLed(MSDC_READ_LED, (_ledcnt & 1));
        _ledcnt--;
    } else {
        if (_ledblk) {
            // MSDC start to read or write
            _ledblk = 0;
            _ledcnt = _ledper;
        }
        LedCtrl_ButtonLed(MSDC_READ_LED, AHC_FALSE);
    }
}
#endif

AHC_BOOL MSDCFunc_Init_FromMenu(void* pData)
{
#if (1)
    printc("%s,%d \n", __func__, __LINE__);
#endif

    return AHC_TRUE;
}

AHC_BOOL StateMSDCModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    StateLedControl(UI_MSDC_STATE);

    /* The StateLCDCheckStatus will set Sensor Direction,
    * and it may cause system crash when USB plugin in Brower mode for RY04
    * It needs check, Canlet
    */
    #ifndef CFG_MENU_IGNORE_MSDC_LCD_CHECK //may be defined in config_xxx.h
    if ((AHC_FALSE == AHC_IsTVConnectEx()) && (AHC_FALSE == AHC_IsHdmiConnect()))
        StateLCDCheckStatus(UI_MSDC_STATE);
    #endif

    AHC_SetMode(AHC_MODE_IDLE);
    UartSendTrace("====MSDC====\r\n");
    ahcRet = MSDCMode_Start();
    
    return ahcRet;
}

AHC_BOOL StateMSDCModeShutDown(void* pData)
{
#if (1)
    printc("%s,%d \n", __func__, __LINE__);
#endif
    
    return AHC_TRUE;
}

AHC_BOOL PCCAMFunc_Init_FromMenu(void* pData)
{
#if (1)
    printc("%s,%d \n", __func__, __LINE__);
#endif
    
    return AHC_TRUE;
}

AHC_BOOL StatePCCAMModeInit(void* pData)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    StateLedControl(UI_PCCAM_STATE);

    /* The StateLCDCheckStatus will set Sensor Direction,
    * and it may cause system crash when USB plugin in Brower mode for RY04
    * It needs check, Canlet
    */
    #ifndef CFG_MENU_IGNORE_MSDC_LCD_CHECK //may be defined in config_xxx.h
    if ((AHC_FALSE == AHC_IsTVConnectEx()) && (AHC_FALSE == AHC_IsHdmiConnect()))
        StateLCDCheckStatus(UI_PCCAM_STATE);
    #endif

    AHC_SetMode(AHC_MODE_IDLE);
    VideoFunc_SetAttribute();
    ahcRet = PCCAMMode_Start();
    
    return ahcRet;
}

AHC_BOOL StatePCCAMModeShutDown(void* pData)
{
#if (1)
    printc("%s,%d \n", __func__, __LINE__);
#endif

    AHC_SetMode(AHC_MODE_IDLE);

    return AHC_TRUE;
}


//******************************************************************************
//
//                              AHC State MSDC Mode
//
//******************************************************************************


DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_POWER_OFF)
{
    AHC_PowerOff_NormalPath();
}

//#define MSDC_OUT_NOT_OFF
//#define PCCAM_OUT_NOT_OFF
DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_USB_REMOVED)
{
    if(AHC_USB_GetLastStatus() == AHC_USB_NORMAL) // MSDC/PCCAM mode
    {
        AHC_USB_OP_MODE uiMode;
        AHC_GetUsbMode(&uiMode);
    
        bUsbMsdcMode = AHC_FALSE;
        MSDCTimer_Stop();
        AHC_USB_DisConnectDevice();
    
        #ifdef  MSDC_OUT_NOT_OFF
        if (uiMode == AHC_USB_MODE_MASS_STORAGE) {
            RTNA_DBG_Str(0, "AHC_USB_MODE_MASS_STORAGE\r\n");
            AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
            AHC_SetMode(AHC_MODE_IDLE);
            StateSwitchMode(UI_VIDEO_STATE);
        }
        else
        #endif
        #ifdef PCCAM_OUT_NOT_OFF 
        if (uiMode == AHC_USB_MODE_WEBCAM) {
            RTNA_DBG_Str(0, "AHC_USB_MODE_WEBCAM\r\n");
            PCCAMFunc_Enable(AHC_FALSE);
            AHC_SetMode(AHC_MODE_IDLE);
            StateSwitchMode(UI_VIDEO_STATE);
        }
        else
        #endif
        {
            bForce_PowerOff = AHC_TRUE;
            AHC_PowerOff_NormalPath();
        }
    }
    
    if (AHC_IsDcCableConnect() == AHC_FALSE)
        AHC_Charger_SetEnable(AHC_FALSE);

}

DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_SD_DETECT)
{
    AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
}

DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_SD_REMOVED)
{
    if(AHC_TRUE == AHC_SDMMC_IsSD1MountDCF()) {
        AHC_DisMountStorageMedia(AHC_MEDIA_MMC);
        Enable_SD_Power(0 /* Power Off */);
    }
}

DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_LCD_COVER_OPEN)
{
    LedCtrl_LcdBackLight(AHC_TRUE);
}

DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_LCD_COVER_CLOSE)
{
    LedCtrl_LcdBackLight(AHC_FALSE);
}

DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_LCD_COVER_NORMAL)
{
    AHC_DrawRotateEvent(ulEvent);
}

DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_LCD_COVER_ROTATE)
{
    AHC_DrawRotateEvent(ulEvent);   
}

DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_MSDC_UPDATE_MESSAGE)
{
    if(!AHC_IsUsbConnect())
    {           
        if(MSDCPowerOffCounter == MSDC_POWEROFF_COUNT)
        {
            printc("--I-- exceed to MSDC_POWEROFF_COUNT, going to power off\r\n");
            
        #ifdef MSDC_OUT_NOT_OFF
            // Not to Power off after MSDC out
        #else
            bForce_PowerOff = AHC_TRUE; 
            AHC_PowerOff_NormalPath();
        #endif
        }
    
        MSDCPowerOffCounter++;
    }
    else
    {
    #ifdef  MSDC_STATUS_LED
        MsdcLedUpdate();
    #endif
    
        MSDCPowerOffCounter = 0;
    }
}

DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_ENTER_NET_PLAYBACK)
{
    if(AHC_USB_GetLastStatus() == AHC_USB_NORMAL) // MSDC/PCCAM mode
    {
        AHC_USB_OP_MODE uiMode;
        AHC_GetUsbMode(&uiMode);

        bUsbMsdcMode = AHC_FALSE;
        MSDCTimer_Stop();
        AHC_USB_DisConnectDevice();
        if (uiMode == AHC_USB_MODE_MASS_STORAGE) {
            RTNA_DBG_Str(0, "AHC_USB_MODE_MASS_STORAGE\r\n");
            AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect);
            StateSwitchMode(UI_NET_PLAYBACK_STATE);

            // Unlock HDMI/TV state when USB plug-out
            //AHC_LockHdmiConnectionStatus(AHC_FALSE, AHC_FALSE);
            //AHC_LockTVConnectionStatus(AHC_FALSE, AHC_FALSE);
        }
        else
        if (uiMode == AHC_USB_MODE_WEBCAM) {
            RTNA_DBG_Str(0, "AHC_USB_MODE_WEBCAM\r\n");
            PCCAMFunc_Enable(AHC_FALSE);
            StateSwitchMode(UI_NET_PLAYBACK_STATE);    
        }
        else
        {
            StateSwitchMode(UI_NET_PLAYBACK_STATE);   
        }
        // Unlock HDMI/TV state when USB plug-out
        //AHC_LockHdmiConnectionStatus(AHC_FALSE, AHC_FALSE);
        //AHC_LockTVConnectionStatus(AHC_FALSE, AHC_FALSE);
    }
    
    CGI_SET_STATUS(ulEvent, CGI_ERR_NONE /* SUCCESSFULLY */);
}

#if defined(MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) && (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) 
DECL_AHC_EV_HANDLER(STATE_MSDC_MODE_EVENT_SCSI_CMD_SWITCH_UVC_MODE)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    ahc_ret = MSDCFunc_Enable(AHC_FALSE);

    AHC_USB_DisConnectDevice();

    MMPS_System_AllocateFSBuffer();

    AHC_DCF_Init();

#if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE == 1)
    {
        VideoFunc_UVCXUCmdRegisterHandler();

        pcam_usb_set_mix_mode(MMP_TRUE);

        CheckRtcAndAutoSetRtc();
        StateSwitchMode(UI_VIDEO_STATE);
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_USB_DETECTED, 0);
    }
#endif
}

AHC_BOOL StateSelectFuncUSB_MSDC_PCAM_Mode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;

    StateModeSetOperation(UI_MSDC_STATE, StateMSDCModeInit, StateMSDCModeShutDown, StateMSDCModeHandler);
    StateModeSetOperation(UI_PCCAM_STATE, StatePCCAMModeInit, StatePCCAMModeShutDown, StateMSDCModeHandler);

    RegisterEventCb(EVENT_POWER_OFF,                        STATE_MSDC_MODE_EVENT_POWER_OFF);

    RegisterEventCb(EVENT_USB_REMOVED,                      STATE_MSDC_MODE_EVENT_USB_REMOVED);
    RegisterEventCb(EVENT_SD_DETECT,                        STATE_MSDC_MODE_EVENT_SD_DETECT);
    RegisterEventCb(EVENT_SD_REMOVED,                       STATE_MSDC_MODE_EVENT_SD_REMOVED);

    RegisterEventCb(EVENT_LCD_COVER_OPEN,                   STATE_MSDC_MODE_EVENT_LCD_COVER_OPEN);
    RegisterEventCb(EVENT_LCD_COVER_CLOSE,                  STATE_MSDC_MODE_EVENT_LCD_COVER_CLOSE);
    RegisterEventCb(EVENT_LCD_COVER_NORMAL,                 STATE_MSDC_MODE_EVENT_LCD_COVER_NORMAL);
    RegisterEventCb(EVENT_LCD_COVER_ROTATE,                 STATE_MSDC_MODE_EVENT_LCD_COVER_ROTATE);
    RegisterEventCb(EVENT_MSDC_UPDATE_MESSAGE,              STATE_MSDC_MODE_EVENT_MSDC_UPDATE_MESSAGE);
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
    RegisterEventCb(EVENT_NET_ENTER_PLAYBACK,               STATE_MSDC_MODE_EVENT_ENTER_NET_PLAYBACK);
#endif

#if defined(MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) && (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD)
    RegisterEventCb(EVENT_MSDC_SCSI_CMD_SWITCH_UVC_MODE, STATE_MSDC_MODE_EVENT_SCSI_CMD_SWITCH_UVC_MODE);
#endif

    return ahcRet;
}
#endif

