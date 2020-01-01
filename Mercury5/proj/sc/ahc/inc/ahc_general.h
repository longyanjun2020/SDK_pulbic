//==============================================================================
//
//  File        : ahc_general.h
//  Description : INCLUDE File for the AHC general function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_GENERAL_H_
#define _AHC_GENERAL_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"
#include "ahc_dcf.h"
#include "config_fw.h"
#include "AHC_Config_SDK.h"
#include "ahc_capture.h"
#include "ahc_video.h"
#include "ahc_motor.h"
#include "ahc_rtc.h"

/*===========================================================================
 * Global variable
 *===========================================================================*/ 

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

/*===========================================================================
 * Structure define
 *===========================================================================*/ 


/*===========================================================================
 * Enum define
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/
int         AHC_IsInVideoMode(void);

// Others

UINT32      AHC_GetChargerPowerOffTime(void);

// PIR
#if (ENABLE_PIR_MODE)
void        AHC_PIR_CheckStart(void);
void        AHC_PIR_SetEnable(AHC_BOOL bEnable); 
#endif
AHC_BOOL    AHC_PIR_IsStarted(void);

AHC_BOOL    AHC_CheckSysCalibMode(void);

void        AHC_BUZZER_Alert(UINT32 ulFrquency, UINT32 ulTimes, UINT32 ulMs);

void        AHC_SetFastAeAwbMode( AHC_BOOL bEnable );

#if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
void        uiSetParkingModeStateInit(void);
void        uiSetParkingModeEnable(UINT8 enable);
void        uiSetParkingModeMenuState(AHC_BOOL enable, AHC_BOOL ParkingStartDrawed);
void        uiSetParkingModeRecordState(AHC_BOOL enable);
void        uiSetParkingModeRecord(AHC_BOOL recorded);
AHC_BOOL    uiGetParkingModeRecord(void);
AHC_BOOL    uiGetParkingStartDrawed(void);

AHC_BOOL    uiSetBootUpUIMode(void);
#endif

UINT8       uiGetParkingModeEnable(void);

ULONG       AHC_CheckWiFiOnOffInterval(MMP_ULONG waiting_time);
AHC_BOOL    AHC_WiFi_Switch(AHC_BOOL wifi_switch_on);
void        AHC_WiFi_Toggle_StreamingMode(void);

// HDMI-out Focus
#if (SUPPORT_HDMI_OUT_FOCUS)
AHC_BOOL    AHC_CheckHdmiOutFocus(void);
#endif

AHC_BOOL    AHC_KeyEventIDCheckConflict(UINT32 ulCurKeyEventID);
void        AHC_SetCurKeyEventID(UINT32 ulCurKeyEventID);
UINT32      AHC_GetCurKeyEventID(void);
AHC_BOOL    AHC_RestoreFromDefaultSetting(void);

#endif // _AHC_GENERAL_H_

