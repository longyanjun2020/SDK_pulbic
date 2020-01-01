////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
/**
 * \file mdl_bat_pars_pub.h
 * \brief Battery internal constants and functions
*/

#ifndef __MDL_BAT_PARS_PUB_H__
#define __MDL_BAT_PARS_PUB_H__


/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_batt_forward.h"
#include "drv_batt_msg_def.h"
#include "mdl_vm_bat_pub.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
/* --- Value which can be return in the API ---*/
#define UNKNOWN_HANDLE                         (-1)
#define BAT_BAD_PARAMETER                      (-2)
#define BAT_CHARGER_NOT_PRESENT                (-3)
#define BAT_BATTERY_NOT_PRESENT                (-4)

#define SAMPLING_ARRAY_SIZE 25
#define MAX_MEASUREMENT_PERIOD   7000*9/40 // max delay  preiod 7s* ms of average frames 9ms/ frames fo average time 40frames

/* --- Timing management constants */
/* --- Definition of the Number of Frames every which
       battery data should be acquired on the Frame Interrupt */
#define CTN_BATTERY_STATUS_TIMEOUT RTK_S_TO_TICK (3)    // 3 seconds

/* battery status timer period when charging state change */
#define LOW_TRANSITIONAL_CHARGER_STATUS_TIMEOUT  RTK_MS_TO_TICK (5000)  // 5 seconds
#define TRANSITIONAL_CHARGER_STATUS_TIMEOUT      RTK_S_TO_TICK (5)     // 5 seconds

/* battery level >= level1 battery voltage in high level */
 
#define UNPLUGGED_HIGH_BATTERY_STATUS_TIMEOUT_S  (60)    // 1 minute

#define UNPLUGGED_HIGH_BATTERY_STATUS_TIMEOUT    RTK_S_TO_TICK (UNPLUGGED_HIGH_BATTERY_STATUS_TIMEOUT_S)    // 1 minute

/* battery level <level1 battery capacity less than 50% */

#define UNPLUGGED_LOW_BATTERY_STATUS_TIMEOUT_S   (30)     // 30 seconds

#define UNPLUGGED_LOW_BATTERY_STATUS_TIMEOUT     RTK_S_TO_TICK (UNPLUGGED_LOW_BATTERY_STATUS_TIMEOUT_S)     // 30 seconds

/* battery status timer period in charging */
#define PLUGGED_BATTERY_STATUS_TIMEOUT RTK_S_TO_TICK (10)    // 10 seconds

/* battery status timer period when battery low */
#define LOW_BATTERY_STATUS_TIMEOUT RTK_S_TO_TICK (10)    // 10 seconds

/* Battery status timer period when charger unplug*/
#define BAT_CHARGER_UNPLUG_STATUS_TIMEOUT  RTK_MS_TO_TICK(300) //1s
#ifndef __DUAL_BATT_DRV__
/*--- ADC Reacquire period ---*/
// user for AUX0 AUX1 adc acquire when ADC in used
#define BAT_ADC_DLEAY_TIME  RTK_MS_TO_TICK(50)
#endif

#ifdef __DUAL_BATT_DRV__
#define UPDATE_BAT_PLUG_VOLTAGE_TIMEOUT RTK_MS_TO_TICK(1000)
#define WAIT_CAP_DISCHARG_TIME           RTK_MS_TO_TICK(80)
#endif
/* ADC sample period */
#define BAT_BATTERY_LOW_SAMPLE             3000  // 3s
#define BAT_BATTERY_HIGH_SAMPLE            6000  // 6s
#define BAT_CHARGER_PLUG_SAMPLE            500   // 500ms
#define BAT_CHARGER_UNPLUG_SAMPLE          50    // 300ms
#define BAT_BATTERY_ALARM_SAMPLE           500   // 500ms
#define BAT_BATTERY_PLUG_SAMPLE            200    //200ms
/**
 * \brief macro used to average measured data
 */
#define BAT_AVERAGE(x,n) (x / n)
#define MEASURE_ARRAY_SIZE                 20  /* Must be <= 25 */

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/
/**
 * \brief Possible values for level calculating reasons
 */
typedef enum
{
    LEVEL_CHECK,
    LEVEL_CALCULATE,
} BatteryChargedLevelOption_e;

/* --- Information measured on the battery --- */
typedef struct
{
#ifdef __DUAL_BATT_DRV__
    Voltage_t     BatteryVolt_S;
#endif
    Voltage_t     BatteryVolt;
    Voltage_t     ChargerVolt;
    Current_t     ChargerCurrent;
    Temperature_t BatteryTemp;
    bool          ChargerPlugged;
} bat_Data_t;

typedef enum
{
    CHARGER_UNPLUGGED,
    TRICKLE_CHARGING,
    FAST_CHARGING,
    SECURITY_WAIT,
    ENOUGH_DISCHARGE_WAIT,
    DISCHARGE_WAIT,
    NO_CHARGING
} BatteryChargingState_e;

typedef enum
{
    CHARGE_MODE_CC,
    CHARGE_MODE_CV
} BatteryChargingMode_e;

/**
 * \brief Structures used in the stack
 */
typedef struct
{
    s16 batcoeff;
    u16 chargcoeff;
    u16 Ichargcoeff;
    u16 tempcoeff;
    s32 batoffset;
    s32 chargoffset;
    s32 Ichargoffset;
    s32 tempoffset;
}bat_AdcParam_t;

/* --- Adds the structure for battery informations */
typedef struct
{
    u32   BattVoltageValue;
#ifdef __DUAL_BATT_DRV__
		u32   BattVoltageSValue;
#endif
    u32   ChargVoltageValue;
    s32   ChargCurrentValue;
    u32   TemperatureValue;
    bool  ChargerState;
} bat_Measures_t;

typedef enum {
    CHG_UNPLUG_INIT = 0,
    CHG_UNPLUG_WAIT_ADC,
    CHG_UNPLUG_ADC_CONF
} bat_ChgUnPlugState_t;

typedef struct
{
    u16 aActualVbat[2];
    u16 aRawVbat[2];
    s16 nCoeff;
    s32 nOffset;
}CaliVbat_t;

typedef struct
{
    u8      nChrFullVoltDebounceCount;     ///< Debounce count for charge to full state.    
    u8      nVoltageBufferForChargingFull;     ///< Battery charge to full state with voltage debounce buffer.
    bool    bChrFullBatteryVolt;        ///< TRUE if battery charging volt reach to full state.
}bat_CheckVolt_t;

#ifdef __DUAL_BATT_DRV__
typedef enum
{
    CHG_ENABLE_CHARGE,
    CHG_STOP_CHARGE,
    CHG_DISABLE_CHARGE,
} bat_DualBatEnChargeState_e;
#endif
/*=============================================================*/
// Local function prototype & definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

void MdlBaBatteryEvent(void);
void MdlBatAcquireBatteryData(u16 NbSleepedFrames);
s32  bat_drv_SetSamplingParameters(const u32 DelayInFrames);
void MdlBatGetChargedLevel(BatteryChargedLevelOption_e state, s8 *Percentage);
#ifdef __DUAL_BATT_DRV__
void MdlSwitchSlaveBattery(void);
void MdlSwitchMasterBattery(void);
#endif
#ifdef __G1_ADC_CALIBRATION__
void _MdlGetVoltLimit(u8 *OriVoltLmt, u8 *CaliVoltLmt);
bool _MdlGetAdcRawData(u16 *ActualBatVolt, u16 *RawData, u8 AverageCount);
bool _MdlGetCalibratePara(u16 Parameter[], u8 PtsNumber);
#endif
#ifndef __DUAL_BATT_DRV__
bool _MdlBatGetVoltData(u16 *BatVolt, u8 AverageCount);
#endif
#endif /* __MDL_BAT_PARS_PUB_H__ */






