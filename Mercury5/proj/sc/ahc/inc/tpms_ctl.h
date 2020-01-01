//------------------------------------------------------------------------------
//
//  File        : TPMS_ctl.h
//  Description : 
//  Author      : 
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _TPMS_ctl_H_
#define _TPMS_ctl_H_

/*===========================================================================
 * Include file
 *===========================================================================*/

///#include "data_type.h"
#include "config_fw.h"
#include "Customer_config.h"
#include "os_wrap.h"
#include "ahc_general.h"
#include "TPMS_driver.h"
/*===========================================================================
 * Macro define
 *===========================================================================*/


/*===========================================================================
 * Enum define
 *===========================================================================*/
enum TPMSSCANFTOKEN
{
	TPMS_SCAN_TOKS_COMPARE   = 1,
    TPMS_SCAN_TOKS_PERCENT   = 2,
    TPMS_SCAN_TOKS_WIDTH     = 3, 
    TPMS_SCAN_TOKS_TYPE      = 4 
};

typedef enum
{
	TPMS_ERR_NO_SIGNAL = 0x0001,
	TPMS_ERR_LOW_BATTERY = 0x0002,
	TPMS_ERR_PRESSURE = 0x0004,
	TPMS_ERR_TEMPERATURE = 0x0008
} TPMS_ERROR_TYPE;

/*===========================================================================
 * Structure define
 *===========================================================================*/
 typedef struct _SWHEEL_DATA
 {
 	MMP_BOOL bNoSignal;
 	MMP_BOOL bLowBattery;
 	float fPressure;
 	MMP_LONG lTemperature;
 	
 } SWHEEL_DATA;
 
 typedef struct _WHEEL_DATA
 {
 	SWHEEL_DATA sWheelData[4];
 } WHEEL_DATA;

/*===========================================================================
 * Extern varible
 *===========================================================================*/

/*===========================================================================
 * Callback
 *===========================================================================*/
typedef void (*TPMS_CALLBACK_ERROR)(int sensor, int err);

/*===========================================================================
 * Function prototype
 *===========================================================================*/
MMP_BOOL TPMSCtrl_GetConnectStatus(void);
MMP_BOOL TPMSCtrl_GetInitStatus(void);
MMP_BOOL TPMSCtrl_GetWheelInformation(MMP_UBYTE ubWheelNum);
MMP_BOOL TPMSCtrl_GetBatteryIndication(MMP_UBYTE ubWheelNum);
MMP_BOOL TPMSCtrl_IsAvailable(UINT32 SensorNum);
MMP_BOOL TPMSCtrl_GetWheelDataUpdateIndication(MMP_UBYTE ubWheelNum);
float TPMSCtrl_GetTirePressure(MMP_UBYTE ubWheelNum);
MMP_LONG TPMSCtrl_GetTireTemp(MMP_UBYTE ubWheelNum);
void TPMSCtrl_GetWheelData(WHEEL_DATA*);
#if (0)
void TPMSCtrl_Initial(TPMS_CALLBACK_ERROR);
#else
void TPMSCtrl_Initial(void);
#endif
void TPMSCtrl_EnterLearnMode(PTPMSLEARNMODE_CALLBACK pCallback, UINT32 TimeOut);
void TPMSCtrl_ExitLearnMode(void);

#endif