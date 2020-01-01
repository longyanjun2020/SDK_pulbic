/*===========================================================================
 * Include file 
 *===========================================================================*/
//This line is from Action Cam UI. Please Update UI code here
#define PORTING(...)

#include "ahc_common.h"
#include "ahc_general.h"
#include "ahc_menu.h"
#include "ahc_media.h"
#include "ahc_usb.h"
#include "ahc_parameter.h"
#include "ahc_warningmsg.h"
#include "ahc_os.h"
#include "ahc_message.h"
#include "dsc_Key.h"
#include "keyparser.h"
#include "StateNetFwUpdateMod.h"
#include "MenuSetting.h"
#include "Netapp.h"
PORTING( #include "StateCameraSettingsFunc.h")
PORTING( #include "DrawStateCameraSettingsFunc.h")
#include "SD_Updater.h"
#include "ledcontrol.h"



/*===========================================================================
 * Global variable
 *===========================================================================*/ 
extern AHC_BOOL     bShowHdmiWMSG;

static UINT32   NetFwUpdateTimerID       = AHC_OS_CREATE_TMR_INT_ERR;
static UINT32   NetFwUpdateCounter       = 0;


/*===========================================================================
 * Main body
 *===========================================================================*/ 

void NetFwUpdateTimer_ISR(void *tmr, void *arg)
{
    NetFwUpdateCounter++;

    if( 0 == NetFwUpdateCounter % 5 ) 
    {
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_UPDATE_MESSAGE, 0);
    }   
}

AHC_BOOL NetFwUpdateTimer_Stop(void)
{
    UINT8 ret = 0;

	if(NetFwUpdateTimerID != AHC_OS_CREATE_TMR_INT_ERR){

		printc(FG_PURPLE("NetFwUpdateTimer_Stop: %d \r\n"), NetFwUpdateTimerID);	  
        
	    ret = AHC_OS_StopTimer( NetFwUpdateTimerID, MMPF_OS_TMR_OPT_NONE );

		NetFwUpdateTimerID = AHC_OS_CREATE_TMR_INT_ERR;
        
	    if(ret)
	        return AHC_FALSE;
	    else
	        return AHC_TRUE;
	}else{
		return AHC_FALSE;
	}
}

AHC_BOOL NetFwUpdateTimer_Start(UINT32 ulTime)
{

	NetFwUpdateTimer_Stop();

    NetFwUpdateTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, NetFwUpdateTimer_ISR, (void*)NULL );

	printc(FG_PURPLE("NetFwUpdateTimer_Start: TimerID = %d\r\n"), NetFwUpdateTimerID);

    NetFwUpdateCounter = 0;

    if(AHC_OS_CREATE_TMR_INT_ERR == NetFwUpdateTimerID)
        return AHC_FALSE;
    else
        return AHC_TRUE;
}


AHC_BOOL NetFwUpdateFunc_Init(void* pData)
{
    NetFwUpdateTimer_Start( 200 );
	ncgi_op_feedback(pData, CGI_ERR_NONE /* OK */);
	return AHC_TRUE;
}

AHC_BOOL NetFwUpdateFunc_ShutDown(void* pData)
{
	NetFwUpdateTimer_Stop();
	return AHC_TRUE;
}

AHC_BOOL NetFwUpdateMode_Start(void)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    bShowHdmiWMSG = AHC_TRUE;

    //TODO: Port drawing UI here
    PORTING(DrawCameraWarningMenu( WARNING_MENU_FW_DOWNLOAD ));

    return ahc_ret;
}

//******************************************************************************
//
//                              AHC State Net FwUpdate Mode
//
//******************************************************************************
void StateNetFwUpdateMode( UINT32 ulEvent )
{       
    switch( ulEvent )
    {
        case EVENT_NONE                           :  
        break;
        
        case EVENT_POWER_OFF                      : 
            PORTING(if( CameraSettingConfig()->bUpdatingFw == AHC_TRUE ))
            {
                break;
            }

            AHC_NormalPowerOffPath();
        break;
        
        case EVENT_NET_FWUPDATE_FROM_SD           :
            if( SDUpdateIsFWExisted() == AHC_TRUE )
            {
                PORTING(CameraSettingConfig()->bUpdatingFw = AHC_TRUE);
                ncgi_op_feedback((void*)EVENT_NET_FWUPDATE_FROM_SD, CGI_ERR_NONE /*OK*/);
                PORTING(DrawCameraWarningMenu( WARNING_MENU_FW_UPDATE ));
			    AHC_SDUpdateMode();
            }
            else
            {
                ncgi_op_feedback((void*)EVENT_NET_FWUPDATE_FROM_SD, CGI_ERR_NO_CARD /*Error*/);
            }
        break;
        
        case EVENT_NET_FWUPDATE_UPDATE_FAIL       :      
            PORTING(DrawCameraWarningMenu( WARNING_MENU_FW_UPDATE_FAIL ));
            PORTING(LedCtrl_BlinkingEnable( LED_TYPE_ALARM, 0xFFFFFFFF, 4, 100 ));
            PORTING(MenuFunc_LockUI_Enable( LOCK_UI_TYPE_WAIT_KEY, 0xFFFFFFFF )); 
        break;
		
        case EVENT_NET_FWUPDATE_LEAVE_STATE       :      
            PORTING(if( GetLastShootingMode() == UI_CAMERA_SETTINGS_STATE ))
            {
                PORTING(CameraSettingsFunc_ResetSettings());
                PORTING(DrawCameraChangingMode( UI_CAMERA_SETTINGS_STATE ));
            }
            
            PORTING(GetLastShootingMode(StateSwitchMode( GetLastShootingMode() )));
        break;
        
        case EVENT_USB_DETECT                     :       
        break;
        
		case EVENT_USB_REMOVED                    :
        break;
        
        case EVENT_HDMI_DETECT                    : 
        break; 

        case EVENT_HDMI_REMOVED                   :
        break;
        
        case EVENT_SD_DETECT                      :  
        break;
        
        case EVENT_SD_REMOVED                     :
        break;
        
		case EVENT_NET_FWUPDATE_UPDATE_MESSAGE    :
        break;
        
        default:
        break;
    }
}

static STATE_HANDLE_RET NewFwUpdate_SwitchHandler(void* param)
{
	StateSwitch_StdHandler(UI_NET_FWUPDATE_STATE);
	if (NetFwUpdateMode_Start()) {
		return UI_STATE_HANDLE_OK;
	}
	return UI_STATE_HANDLE_FAIL;
}

static UINT32 KeyParser_NetFwUpdateEvent( UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam )
{
    switch( ulEvent )
    {
        case BUTTON_NONE           :     return EVENT_NONE;
		case BUTTON_REC_PRESS      : 	 return EVENT_NONE;
		case BUTTON_REC_LPRESS     :     return EVENT_NONE;
		case BUTTON_CAPTURE_PRESS  : 	 return EVENT_NONE;
		case BUTTON_CAPTURE_LPRESS :     return EVENT_NONE;
		case BUTTON_POWER_PRESS	   :	 return EVENT_NONE;
		case BUTTON_POWER_LPRESS   :	 return EVENT_POWER_OFF;
		case EVENT_NET_FWUPDATE_FROM_SD: return EVENT_NET_FWUPDATE_FROM_SD;
		case EVENT_NET_FWUPDATE_UPDATE_FAIL: return EVENT_NET_FWUPDATE_UPDATE_FAIL;
		case EVENT_NET_FWUPDATE_LEAVE_STATE: return EVENT_NET_FWUPDATE_LEAVE_STATE;

        case BUTTON_USB_DETECTED   :     return EVENT_USB_DETECT;
        case BUTTON_USB_REMOVED    :     return EVENT_POWER_OFF;
        case BUTTON_SD_DETECTED    :     return EVENT_SD_DETECT;
        case BUTTON_SD_REMOVED     :     return EVENT_SD_REMOVED;
        case BUTTON_TV_DETECTED    :     return EVENT_TV_DETECT;
        case BUTTON_TV_REMOVED     :     return EVENT_TV_REMOVED;
        case BUTTON_HDMI_DETECTED  :     return EVENT_HDMI_DETECT;
        case BUTTON_HDMI_REMOVED   :     return EVENT_HDMI_REMOVED;

        case BUTTON_UPDATE_MESSAGE :     return EVENT_NET_FWUPDATE_UPDATE_MESSAGE;

        default                    :     return EVENT_NONE;
    }
}

static STATE_HANDLE_RET NewFwUpdate_StateHandler(void* param)
{
	UINT32 *params = (UINT32*)param;
	UINT32 ulEvent;

	ulEvent = KeyParser_NetFwUpdateEvent( params[0]/*ulMsgId*/, params[1]/*ulEvent*/, params[2]/*ulParam*/);
	StateNetFwUpdateMode( ulEvent);
	return UI_STATE_HANDLE_OK;
}


#if AHC_MODULE_VER == 1
static int InitNetFwUpdate(void)
#else
static int InitNetFwUpdate(void *param)
#endif
{
	static UI_STATE_OP op = {NetFwUpdateFunc_Init, NetFwUpdateFunc_ShutDown, NewFwUpdate_SwitchHandler, NewFwUpdate_StateHandler};
	if (AHC_FALSE == StateModeOperationEx(UI_NET_FWUPDATE_STATE, &op)) {
		return -1;
	}
    return 0;
}

#define AIT_MODULE_INIT(order,id,func) ait_module_init(func)
#pragma arm section rwdata = "initcall_mod", zidata = "initcall_mod"
AIT_MODULE_INIT(STD_AIT_MODULE_ORDER, UISM_HEADER_ID, InitNetFwUpdate);
#pragma arm section code, rwdata,  zidata
