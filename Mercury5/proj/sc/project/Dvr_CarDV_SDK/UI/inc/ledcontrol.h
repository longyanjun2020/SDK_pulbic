//==============================================================================
//
//  File        : ZoomContorl.h
//  Description : INCLUDE File for the Zoom Control function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _LED_CONTROL_H_
#define _LED_CONTROL_H_

/*===========================================================================
 * Function prototype
 *===========================================================================*/

UINT32 		FlashLED_GetEV(void);
AHC_BOOL 	FlashLED_Timer_Start(UINT32 ulTime);
AHC_BOOL 	FlashLED_Timer_Stop(void);
void 		LedCtrl_FlashLed(AHC_BOOL bOn );
UINT8 		LedCtrl_GetFlashLEDStatus(void);
void 		LedCtrl_ButtonLed(int LED_Gpio, AHC_BOOL bOn);
void 		LedCtrl_FlickerLed(int LED_Gpio, UINT32 ultime);
void 		LedCtrl_FlickerLedBeep(int LED_Gpio, UINT32 ultime, UINT32 ulMs);
void		LedCtrl_FlickerLedBySDMMC(UINT8 LED_Gpio, UINT8 SDMMCMemoryLevel);
AHC_BOOL    RecLED_Timer_Start(UINT32 ulTime);
AHC_BOOL    RecLED_Timer_Stop(void);
void        LedCtrl_PowerLed(AHC_BOOL bOn);
AHC_BOOL	FwUpdateLED_Timer_Start(UINT32 ulTime);
AHC_BOOL	FwUpdateLED_Timer_Stop(void);

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
AHC_BOOL    WiFiStreamingLED_Timer_Start(UINT32 ulTime);
AHC_BOOL    WiFiStreamingLED_Timer_Stop(void);
void        LedCtrl_WiFiLed(AHC_BOOL bOn);
#endif


void 		LedCtrl_VideoModeLed(AHC_BOOL bOn );
void 		LedCtrl_CameraModeLed(AHC_BOOL bOn );
void 		LedCtrl_PlaybackModeLed(AHC_BOOL bOn );
void 		LedCtrl_AfLed(AHC_BOOL bOn );
void		LedCtrl_LcdBackLightLock(AHC_BOOL bLock);
void 		LedCtrl_LcdBackLight(AHC_BOOL bOn );
void 		LedCtrl_PowerLed(AHC_BOOL bOn );
void 		LedCtrl_SelfTimerLed(AHC_BOOL bOn );
AHC_BOOL 	LedCtrl_GetAfLedStatus(void);
void 		LedCtrl_SetAfLedStatus(AHC_BOOL bOn);
void		LedCtrl_ChargingStatus(void);
void 		LedCtrl_ChangeStatus_Power(void);
void 		LedCtrl_ChangeStatus_SelfTimer(void);
UINT8 		LedCtrl_GetBacklightStatus(void);
void 		RTNA_LCD_Backlight( AHC_BOOL bEnable );

#endif
