/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_config.h" 
#include "ahc_common.h"
//#include "ahc_parameter.h"
//#include "ahc_general.h"
//#include "ahc_general_cardv.h"
//#include "ahc_message.h"
//#include "ahc_utility.h"
#include "ahc_display.h"
//#include "ahc_menu.h"
#include "ahc_os.h"
#include "ledcontrol.h"
#include "isp_if.h"
#if(BUTTON_BIND_LED)
#include "statevideofunc.h"
#endif
#include "statetvfunc.h"
#include "statehdmifunc.h"
#include "ahc_media.h"
//#include "lib_retina.h"

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "netapp.h"
#include "wlan.h"
#endif

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define FLASH_LED_OFF 		(0)
#define FLASH_LED_ON		(1)
#define FLASH_LED_EV_TH_H	(650)//TBD
#define FLASH_LED_EV_TH_L	(220)//TBD

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

static AHC_BOOL bBackLightStatus;

static UINT8  	FlashLEDTimerID = AHC_OS_CREATE_TMR_INT_ERR;
static UINT32  	FlashLEDCounter = 0;
static UINT8	FlashLEDStatus  = FLASH_LED_OFF;
static UINT8 	RecLEDTimerID	= AHC_OS_CREATE_TMR_INT_ERR;
static UINT32  	RecLEDCounter = 0;
#ifdef LED_GPIO_FW_UPDATE
static UINT8	FwUpdateLEDTimerID = 0xFF;
static UINT32	FwUpdateLEDCounter = 0;
#endif
#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(LED_GPIO_WIFI_STATE)
static UINT8 	StreamingLEDTimerID	= 0xFF;
static UINT32  	StreamingLEDCounter = 0;
#endif

/*===========================================================================
 * Extern function
 *===========================================================================*/ 

extern MMP_ULONG AHC_GetVideoModeLedGPIOpin(void);
extern MMP_ULONG AHC_GetCameraModeLedGPIOpin(void);
extern MMP_ULONG AHC_GetPBModeLedGPIOpin(void);
extern MMP_ULONG AHC_GetSelfTimerLedGPIOpin(void);
extern MMP_ULONG AHC_GetAFLedGPIOpin(void);
extern MMP_ULONG AHC_GetLCDBacklightGPIOpin(void);
extern AHC_BOOL	bMuteRecord;

/*===========================================================================
 * Main body
 *===========================================================================*/ 

MMP_ULONG AHC_GetPBModeLedGPIOpin(void)
{
	#ifdef LED_GPIO_PLAYBACK
	MMP_ULONG temp = LED_GPIO_PLAYBACK;
	#else
	MMP_ULONG temp = MMP_GPIO_MAX;
	#endif
	return temp;
}

MMP_ULONG AHC_GetVideoModeLedGPIOpin(void)
{
	#ifdef LED_GPIO_VIDEO
	MMP_ULONG temp = LED_GPIO_VIDEO;
	#else
	MMP_ULONG temp = MMP_GPIO_MAX;
	#endif
	return temp;
}

MMP_ULONG AHC_GetCameraModeLedGPIOpin(void)
{
	#ifdef LED_GPIO_CAMERA
	MMP_ULONG temp = LED_GPIO_CAMERA;
	#else
	MMP_ULONG temp = MMP_GPIO_MAX;
	#endif
	return temp;
}

MMP_ULONG AHC_GetPowerLedGPIOpin(void)
{
	#ifdef LED_GPIO_POWER
	MMP_ULONG temp = LED_GPIO_POWER;
	#else
	MMP_ULONG temp = MMP_GPIO_MAX;
	#endif
	return temp;
}

MMP_ULONG AHC_GetSelfTimerLedGPIOpin(void)
{
	#ifdef LED_GPIO_SELF_TIMER
	MMP_ULONG temp = LED_GPIO_SELF_TIMER;
	#else
	MMP_ULONG temp = MMP_GPIO_MAX;
	#endif
	return temp;
}

MMP_ULONG AHC_GetAFLedGPIOpin(void)
{
	#ifdef LED_GPIO_AFLED_EN
	MMP_ULONG temp = LED_GPIO_AFLED_EN;
	#else
	MMP_ULONG temp = MMP_GPIO_MAX;
	#endif
	return temp;
}

MMP_ULONG AHC_GetLCDBacklightGPIOpin(void)
{
	MMP_ULONG temp = LCD_GPIO_BACK_LIGHT;
	return temp;
}

#if 0
void _____Flash_LED_Function_________(){ruturn;} //dummy
#endif

UINT32 FlashLED_GetEV(void)
{
	UINT32 ulLightLux = 0;
	
	ulLightLux = ISP_IF_AE_GetLightCond();
	
	return ulLightLux;
}

static void FlashLED_Timer_ISR(void *tmr, void *arg)
{   
    FlashLEDCounter++;
	
    if(0 == FlashLEDCounter%15) 
    {    
        if(FlashLEDStatus==FLASH_LED_ON && FlashLED_GetEV()>=FLASH_LED_EV_TH_H)
        	LedCtrl_FlashLed(AHC_FALSE);
        else if(FlashLEDStatus==FLASH_LED_ON && FlashLED_GetEV()<FLASH_LED_EV_TH_L)
        	;//Do nothing
        else if(FlashLEDStatus==FLASH_LED_OFF && FlashLED_GetEV()>=FLASH_LED_EV_TH_H)
        	;//Do nothing
        else if(FlashLEDStatus==FLASH_LED_OFF && FlashLED_GetEV()<FLASH_LED_EV_TH_L)
        	LedCtrl_FlashLed(AHC_TRUE);    	
    }         
}

AHC_BOOL FlashLED_Timer_Start(UINT32 ulTime)
{
    if(FlashLEDTimerID == AHC_OS_CREATE_TMR_INT_ERR)
    {
	    FlashLEDCounter = 0;
	    FlashLEDTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, FlashLED_Timer_ISR, (void*)NULL );

	    if(AHC_OS_CREATE_TMR_INT_ERR == FlashLEDTimerID)
			return AHC_FALSE;
		else
			return AHC_TRUE;
	}	
	return AHC_FALSE;		
}

AHC_BOOL FlashLED_Timer_Stop(void)
{
    UINT8 ret = 0;
	
	if(FlashLEDTimerID != AHC_OS_CREATE_TMR_INT_ERR)
	{
	    ret = AHC_OS_StopTimer( FlashLEDTimerID, AHC_OS_TMR_OPT_PERIODIC );

		FlashLEDCounter = 0;
		FlashLEDTimerID = AHC_OS_CREATE_TMR_INT_ERR;

	    if(ret)
	 		return AHC_FALSE;
		else
			return AHC_TRUE;
	}
	return AHC_FALSE;	
}

static void RecLED_Timer_ISR(void *tmr, void *arg)
{   
#if(BUTTON_BIND_LED)
	static UINT8	ubRecLedStatus		=	1;
	
	// Default
    if(VideoFunc_GetRecordStatus())//REC and MIC LED
	{
        LedCtrl_ButtonLed(AHC_GetVideoModeLedGPIOpin(), ubRecLedStatus & 0x08);
        ubRecLedStatus++;
    }
    else
    {
    	ubRecLedStatus = AHC_FALSE;

		#ifdef CFG_SDMMC_ERROR_TURNON_REC_LED
		if(AHC_FALSE == AHC_SDMMC_IsSD1MountDCF())
		{
			LedCtrl_ButtonLed(AHC_GetVideoModeLedGPIOpin(), AHC_TRUE);
		}
		else
		#endif
		{
			LedCtrl_ButtonLed(AHC_GetVideoModeLedGPIOpin(), AHC_FALSE);
		}
	}


#endif//BUTTON_BIND_LED
}

AHC_BOOL RecLED_Timer_Start(UINT32 ulTime)
{
    if(AHC_OS_CREATE_TMR_INT_ERR == RecLEDTimerID)
    {
	    RecLEDCounter = 0;
	    RecLEDTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, RecLED_Timer_ISR, (void*)NULL );

	    if(AHC_OS_CREATE_TMR_INT_ERR == RecLEDTimerID)
			return AHC_FALSE;
		else
			return AHC_TRUE;
	}	
	
	return AHC_FALSE;
}

AHC_BOOL RecLED_Timer_Stop(void)
{
    UINT8 ret = 0;

	#ifdef CFG_REC_STATUS_INDEX
	if (CFG_REC_STATUS_INDEX != MMP_GPIO_MAX)
		AHC_GPIO_SetData(CFG_REC_STATUS_INDEX, 0);
	#endif

	if(AHC_OS_CREATE_TMR_INT_ERR != RecLEDTimerID)
	{
	    ret = AHC_OS_StopTimer( RecLEDTimerID, AHC_OS_TMR_OPT_PERIODIC );

		RecLEDCounter = 0;
		RecLEDTimerID = AHC_OS_CREATE_TMR_INT_ERR;

	    if(ret)
	 		return AHC_FALSE;
		else
			return AHC_TRUE;
	}
    
	return AHC_FALSE;	
}

// For SD Card FW Update
#ifdef LED_GPIO_FW_UPDATE
static void FwUpdateLED_Timer_ISR(void *tmr, void *arg)
{
	static UINT8	ubUpdateLedStatus		=	1;

	LedCtrl_ButtonLed(LED_GPIO_FW_UPDATE, ubUpdateLedStatus);
	ubUpdateLedStatus ^= 1;
}
#endif

AHC_BOOL FwUpdateLED_Timer_Start(UINT32 ulTime)
{
#ifdef LED_GPIO_FW_UPDATE 
	if (LED_GPIO_FW_UPDATE == MMP_GPIO_MAX)
		return AHC_FALSE;

    if(FwUpdateLEDTimerID >= 0xFE)
    {
	    FwUpdateLEDCounter = 0;
	    FwUpdateLEDTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, FwUpdateLED_Timer_ISR, (void*)NULL );

	    if (0xFE <= FwUpdateLEDTimerID)
			return AHC_FALSE;
		else
			return AHC_TRUE;
	}
#endif

	return AHC_FALSE;
}

AHC_BOOL FwUpdateLED_Timer_Stop(void)
{
#ifdef LED_GPIO_FW_UPDATE 
    UINT8 ret = 0;

	if (FwUpdateLEDTimerID < 0xFE)
	{
	    ret = AHC_OS_StopTimer( FwUpdateLEDTimerID, AHC_OS_TMR_OPT_PERIODIC );

		FwUpdateLEDCounter = 0;
		FwUpdateLEDTimerID = 0xFF;

	    if(0xFF == ret)
	 		return AHC_FALSE;
		else
			return AHC_TRUE;
	}
#endif

	return AHC_FALSE;
}

#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(LED_GPIO_WIFI_STATE)
static void StreamingLED_Timer_ISR(void *tmr, void *arg)
{   
#ifdef CUS_STREAMING_LED_FUNC

	CUS_STREAMING_LED_FUNC();

#else

	static UINT8 ubStreamingLedStatus = AHC_TRUE;
    INT32 appStatus = nhw_get_status();
    INT32 StreamingStatus = ns_get_streaming_status();

	if (WLAN_SYS_GetMode() == -1)
	{	
        LedCtrl_WiFiLed(AHC_FALSE);
        ubStreamingLedStatus = 0;
    }
    else
    {
    	//Streaming status
    	if(IS_WIFI_STREAM_FAIL(StreamingStatus))
    	{
        	LedCtrl_WiFiLed(ubStreamingLedStatus & 0x04);
            ubStreamingLedStatus++;
        }
    	else if(StreamingStatus & NETAPP_STREAM_PLAY)
    	{
            LedCtrl_WiFiLed(ubStreamingLedStatus & 0x08);
            ubStreamingLedStatus++;
        }
        else
        {
    		//Net status
        	switch (appStatus) {

        	case NETAPP_NET_STATUS_READY:
            	LedCtrl_WiFiLed(AHC_TRUE);
            	ubStreamingLedStatus = 0;
            	break;

       		case NETAPP_NET_STATUS_IDLE:
            	ubStreamingLedStatus = 0;

        		if (WLAN_SYS_GetMode() != -1) {
        			// Wi-Fi turn-on but no client
	            	LedCtrl_WiFiLed(AHC_TRUE);
	            	break;
        		}
			
            	LedCtrl_WiFiLed(AHC_FALSE);
            	break;
                    
        	default:
            
            	LedCtrl_WiFiLed(AHC_FALSE);
            	ubStreamingLedStatus = 0;
        	}
        }
    }

#endif		// #ifdef CUS_STREAMING_LED_FUNC
}
#endif

AHC_BOOL WiFiStreamingLED_Timer_Start(UINT32 ulTime)
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(LED_GPIO_WIFI_STATE)
	if (LED_GPIO_WIFI_STATE != MMP_GPIO_MAX)
	{
	    if (0xFE <= StreamingLEDTimerID)
	    {
		    StreamingLEDCounter = 0;
		    StreamingLEDTimerID = AHC_OS_StartTimer( ulTime, AHC_OS_TMR_OPT_PERIODIC, StreamingLED_Timer_ISR, (void *) NULL );

		    if (0xFE <= StreamingLEDTimerID)
				return AHC_FALSE;
			else
				return AHC_TRUE;
		}
	}
#endif
    
	return AHC_FALSE;
}

AHC_BOOL WiFiStreamingLED_Timer_Stop(void)
{
#if defined(WIFI_PORT) && (WIFI_PORT == 1) && defined(LED_GPIO_WIFI_STATE)
    if (LED_GPIO_WIFI_STATE != MMP_GPIO_MAX)
    {
        if (0xFE > StreamingLEDTimerID)
        {
            UINT8 ret = 0;

            ret = AHC_OS_StopTimer( StreamingLEDTimerID, AHC_OS_TMR_OPT_PERIODIC );

            StreamingLEDCounter = 0;
            StreamingLEDTimerID = 0xFF;

            if (0xFF == ret)
                return AHC_FALSE;
        }
    }
#endif
    
	return AHC_FALSE;
}

void LedCtrl_FlashLed(AHC_BOOL bOn)
{
#ifdef	LED_GPIO_FLASH_LIGHT
    AHC_BOOL bOutput = ((LED_GPIO_FLASH_LIGHT_ACT_LEVEL == GPIO_HIGH) ? GPIO_LOW : GPIO_HIGH);
    
    if (bOn)
        bOutput = LED_GPIO_FLASH_LIGHT_ACT_LEVEL;
        
    FlashLEDStatus = bOutput;

    AHC_GPIO_ConfigPad(LED_GPIO_FLASH_LIGHT, PAD_OUT_DRIVING(0));
	AHC_GPIO_SetOutputMode(LED_GPIO_FLASH_LIGHT, AHC_TRUE);
	AHC_GPIO_SetData(LED_GPIO_FLASH_LIGHT, bOutput);
#endif
}
   
UINT8 LedCtrl_GetFlashLEDStatus(void)
{
	return FlashLEDStatus;
}

#if 0
void _____Other_LED_Function_________(){ruturn;} //dummy
#endif
   
void LedCtrl_VideoModeLed(AHC_BOOL bOn)
{
	if(AHC_GetVideoModeLedGPIOpin() != MMP_GPIO_MAX)
    {
	    AHC_BOOL bOutput;
	    
    	bOutput = (bOn)?(1):(0);

        AHC_GPIO_ConfigPad(AHC_GetVideoModeLedGPIOpin(), PAD_OUT_DRIVING(0));
		AHC_GPIO_SetOutputMode(AHC_GetVideoModeLedGPIOpin(), AHC_TRUE);
		AHC_GPIO_SetData(AHC_GetVideoModeLedGPIOpin(), bOutput);
	}
}

void LedCtrl_CameraModeLed(AHC_BOOL bOn)
{
	if(AHC_GetCameraModeLedGPIOpin() != MMP_GPIO_MAX)
    {
	    AHC_BOOL bOutput;
	    
    	bOutput = (bOn)?(1):(0);

        AHC_GPIO_ConfigPad(AHC_GetCameraModeLedGPIOpin(), PAD_OUT_DRIVING(0));
		AHC_GPIO_SetOutputMode(AHC_GetCameraModeLedGPIOpin(), AHC_TRUE);
		AHC_GPIO_SetData(AHC_GetCameraModeLedGPIOpin(), bOutput);
	}
}

void LedCtrl_PlaybackModeLed(AHC_BOOL bOn)
{  
    if(AHC_GetPBModeLedGPIOpin() != 0xFFF) //0xFFF = PIO_REG_UNKNOWN 
    {
	    AHC_BOOL bOutput;
	    
    	bOutput = (bOn)?(1):(0);

        AHC_GPIO_ConfigPad(AHC_GetPBModeLedGPIOpin(), PAD_OUT_DRIVING(0));
		AHC_GPIO_SetOutputMode(AHC_GetPBModeLedGPIOpin(), AHC_TRUE);
		AHC_GPIO_SetData(AHC_GetPBModeLedGPIOpin(), bOutput);
	}
}

void LedCtrl_PowerLed(AHC_BOOL bOn)
{  
#if defined(LED_GPIO_POWER)
	if (LED_GPIO_POWER != MMP_GPIO_MAX)
	{
	    AHC_BOOL bOutput;

	    #if defined(LED_GPIO_POWER_ACT_LEVEL) //may be defined in config_xxx.h
	    bOutput = (bOn)?(LED_GPIO_POWER_ACT_LEVEL):(!LED_GPIO_POWER_ACT_LEVEL);
		#elif defined(CFG_LED_BUTTON_HIGH_AS_ON)
	    bOutput = (bOn)?(1):(0);
	    #else
	    bOutput = (bOn)?(0):(1);
	    #endif

        AHC_GPIO_ConfigPad(LED_GPIO_POWER, PAD_OUT_DRIVING(0));
		AHC_GPIO_SetOutputMode(LED_GPIO_POWER, AHC_TRUE);
		AHC_GPIO_SetData(LED_GPIO_POWER, bOutput);
	}
#endif
}

void LedCtrl_LaserLed(AHC_BOOL bOn)
{
#if 0//defined(LED_GPIO_LASER) && (LED_GPIO_LASER != MMP_GPIO_MAX)
    AHC_BOOL bOutput;

    #ifdef LED_GPIO_LASER_ACT_LEVEL //may be defined in config_xxx.h
    bOutput = (bOn)?(LED_GPIO_LASER_ACT_LEVEL):(!LED_GPIO_LASER_ACT_LEVEL);
    #else
    bOutput = (bOn)?(0):(1);
    #endif
   if(pf_GetLaserLedStatus())
   	{
        AHC_GPIO_ConfigPad(LED_GPIO_LASER, PAD_OUT_DRIVING(0));
		AHC_GPIO_SetOutputMode(LED_GPIO_LASER, AHC_TRUE);
		AHC_GPIO_SetData(LED_GPIO_LASER, bOutput);
   	}
#endif
}
#if defined(WIFI_PORT) && (WIFI_PORT == 1)
void LedCtrl_WiFiLed(AHC_BOOL bOn)
{  
#if 0
#if defined(LED_GPIO_WIFI_STATE)
	if (LED_GPIO_WIFI_STATE != MMP_GPIO_MAX) {
        AHC_GPIO_ConfigPad(LED_GPIO_WIFI_STATE, PAD_OUT_DRIVING(0));
		AHC_GPIO_SetOutputMode(LED_GPIO_WIFI_STATE, AHC_TRUE);
		AHC_GPIO_SetData(LED_GPIO_WIFI_STATE, (bOn)?(LED_GPIO_WIFI_ACT_LEVEL):(!LED_GPIO_WIFI_ACT_LEVEL));
	}
#endif
#endif
}
#endif

/*
 * The function helps to control LCD backlight ON/OFF when System up to escape
 * LCD's nonsense blinking 
 */
static AHC_BOOL	m_ubLcdBk_lock = 0;
static int		_ui_mmpPIP     = 1;
void LedCtrl_LcdBackLightLock(AHC_BOOL bLock)
{
	m_ubLcdBk_lock = bLock;
}

void LedCtrl_LcdBackLight(AHC_BOOL bOn)
{
	extern AHC_BOOL bInLCDPowerSave;
	
	if (m_ubLcdBk_lock)
		return;

	if (!AHC_IsTVConnectEx()	 &&
		!AHC_IsHdmiConnect() &&
		AHC_GetLCDBacklightGPIOpin() != CONFIG_PIO_REG_UNKNOWN)
    {
	    if(bOn)
	    {

	    	bBackLightStatus = 1;
	    
	    	if(bInLCDPowerSave)
	    		bInLCDPowerSave = AHC_FALSE;
	    }
	    else
	    {
	    	
	        bBackLightStatus = 0;
		}

		RTNA_LCD_Backlight(bBackLightStatus);        

	}
}

UINT8 LedCtrl_GetBacklightStatus(void)
{
	if(AHC_GetLCDBacklightGPIOpin() != MMP_GPIO_MAX) {
		return bBackLightStatus;
	} else {
		return _ui_mmpPIP;
	}
}

void LedCtrl_ButtonLed(int LED_Gpio, AHC_BOOL bOn)
{
#if 0
    AHC_BOOL bOutput;
    
    if(LED_Gpio == MMP_GPIO_MAX)
    	return;

    #ifdef CFG_LED_BUTTON_HIGH_AS_ON //may be defined in config_xxx.h
    bOutput = (bOn)?(1):(0);
    #else
    bOutput = (bOn)?(0):(1);
    #endif
        
    AHC_GPIO_ConfigPad(LED_Gpio, PAD_OUT_DRIVING(0));
	AHC_GPIO_SetOutputMode(LED_Gpio, AHC_TRUE);
	AHC_GPIO_SetData(LED_Gpio, bOutput);
#endif	
}

void LedCtrl_FlickerLed(int LED_Gpio, UINT32 ultime)
{  
#if 0
	int	t = 0;

    if (LED_Gpio != MMP_GPIO_MAX) {	
        AHC_GPIO_ConfigPad(LED_Gpio, PAD_OUT_DRIVING(0));
    	AHC_GPIO_SetOutputMode(LED_Gpio, AHC_TRUE);

    	while(t < ultime)
    	{
    		AHC_GPIO_SetData(LED_Gpio, 1);
    		AHC_OS_SleepMs(200);
    		AHC_GPIO_SetData(LED_Gpio, 0);
    		AHC_OS_SleepMs(200);
    		t++;
    	}
    }
#endif    
}
void LedCtrl_FlickerLedEx(int LED_Gpio, UINT32 ultime,UINT32 ums)
{
#if 0
	int	t = 0;

    if (LED_Gpio != MMP_GPIO_MAX) {	
        AHC_GPIO_ConfigPad(LED_Gpio, PAD_OUT_DRIVING(0));
    	AHC_GPIO_SetOutputMode(LED_Gpio, AHC_TRUE);

    	while(t < ultime)
    	{
    		AHC_GPIO_SetData(LED_Gpio, 1);
    		AHC_OS_SleepMs(ums);
    		AHC_GPIO_SetData(LED_Gpio, 0);
    		AHC_OS_SleepMs(ums);
    		t++;
    	}
    }
#endif    
}

void LedCtrl_FlickerLedBeep(int LED_Gpio, UINT32 ultime, UINT32 ulMs)
{  
#if 0
	int	t = 0;
	
    if (LED_Gpio != MMP_GPIO_MAX) {	
        AHC_GPIO_ConfigPad(LED_Gpio, PAD_OUT_DRIVING(0));
    	AHC_GPIO_SetOutputMode(LED_Gpio, AHC_TRUE);

    	while(t < ultime)
    	{
    		AHC_BUZZER_Alert(1000, 1, ulMs);
    		AHC_GPIO_SetData(LED_Gpio, 1);
    		AHC_OS_SleepMs(50);
    		AHC_GPIO_SetData(LED_Gpio, 0);
    		AHC_OS_SleepMs(50);
    		t++;
    	}
    }
#endif    
}


void LedCtrl_FlickerLedByCustomer(MMP_GPIO_PIN LED_Gpio, UINT32 period, UINT32 times)
{
#if 0
	if (MMP_GPIO_MAX == LED_Gpio)
		return;

	while (times--) {
		LedCtrl_ButtonLed(LED_Gpio, AHC_TRUE);
		AHC_OS_SleepMs(period >> 1);
		LedCtrl_ButtonLed(LED_Gpio, AHC_FALSE);
		AHC_OS_SleepMs(period >> 1);
	}
#endif	
}

// Call by mmpf to enable/disable PIP window for BLANK DISPLAY OUPUT
int ui_mmpBacklightOff()
{
	return _ui_mmpPIP;
}

// Dummy function for compiler issue
void LedCtrl_ForceCloseTimer(AHC_BOOL enable)
{

}
