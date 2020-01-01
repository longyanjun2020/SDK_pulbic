/**
 * \page Battery Public Interface
 *
 *
 * \section intro_sec Introduction
 *
 * This document describes the Battery management Interface
 *
 *  <hr>
 * \section SectionMMI2Battery 1. MMI to Battery Interface
 *
 * \li \ref vm_batGetLevel
 * \li \ref vm_batGetChargerState
 * \li \ref vm_batGetChargingState
 * \li \ref vm_batGetVoltage
 * \li \ref vm_batGetCTNVoltage
 * \li \ref vm_batGetFirstChargerState
 * \li \ref vm_batSubscribe
 *
 *  <hr>
 * \section SectionBattery2MMI 2. Battery Layer to MMI Interface
 *
 *  \li \ref  BAT_LEVEL    message sent to indicated the battery level
 *  \li \ref  BAT_CHARGER_ON    message sent when the charger is plugged
 *  \li \ref  BAT_CHARGER_OFF    message sent when the charger is unplugged
 *  \li \ref  BAT_CHARGING_ON    message sent when the charging starts
 *  \li \ref  BAT_CHARGING_OFF    message sent when  the charging stops
 *  \li \ref  BAT_ALARM    message sent when a battery alarm occurs
 *  \li \ref  BAT_CTN    message sent when a CTN event occurs
 *
 *  <hr>
 * \section Usage 3. Usage
 *
 *  The client first calls \ref vm_batSubscribe to subscribe to the Battery service, then will receive messages
 *
 *  Then it can call one or more other functions to get the battery level, the charging level and so on
 *
 *
 *
 *  <hr>
 *  \section Notes 4. NOTES
 *
 *  Current limitations :
 *
 *
 */


/*!
 * \file mdl_vm_bat_pub.h
 * \brief MMI to battery
 *
 *  This file defines the battery public interface that is offered to the MMI.
 *
 *  The interface allows to :
 *   \li subscribe to battery messages
 *   \li get battery and charging info
 *
 */
#ifndef __MDL_VM_BAT_PUB_H__
#define __MDL_VM_BAT_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "vm_msgof.hc"

#include "drv_vm_bat_types.h"
#include "drv_batt_msg_def.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * \brief Possible values for battery level
 */
typedef enum
{
    BAT_FAKE_LOW_LEVEL = -4,    ///< send a fake low level to MMI for auto test .
    BAT_DUMMY_LEVEL,   ///< dummy value
    BAT_TOO_LOW_FOR_COMM,   ///< lowest level
    BAT_LOW_BATTERY,        ///< low battery, tell user
    BAT_LEVEL_0,            ///< level 0
    BAT_LEVEL_1,            ///< level 1
    BAT_LEVEL_2,            ///< level 2
    BAT_LEVEL_3,            ///< level 3
    BAT_LEVEL_4,            ///< level 4 (battery full)
} vm_batMmiBatteryLevel_t;

/**
 * \brief Battery mailbox id
 */
typedef enum
{
  BAT_MSG_ID = 0x2955,
  BAT_ACK_ID,
} vm_BatMsgId_e;

/**
 * \brief cause of battery change
 */
typedef enum
{
    BAT_CHANGE_CAUSE_LOW,
    BAT_CHANGE_CAUSE_FULL,
    BAT_CHANGE_CAUSE_BAT_UNPLUG,
    BAT_CHANGE_CAUSE_BAT_PLUG,
}vm_BatChangeCause_e;

/**
 * \brief Battery mailbox bitmap
 */
typedef enum
{
  BAT_CTN_BITMAP=1,
  BAT_CHARGER_BITMAP=0x2,
  BAT_CHARGING_BITMAP=0x4,
  BAT_LEVEL_BITMAP=0x8,
  BAT_ALARM_BITMAP=0x10,
  BAT_PRECHARGE_BITMAP=0x20,
  BAT_VBUS_STATE_BITMAP=0x40,
  BAT_BATTERY_CHANGE_BITMAP=0x80,
  BAT_BATTERY_PLUG_BITMAP=0x100,
} vm_BatBitMap_e;

/**
 * \brief Battery mailbox message
 */
typedef struct
{
    u32  BatteryTemperature;
    s8   BatteryLevel_S;
    s8   ChargedLevel_S;
    bool BatteryAlarm_S;
    s8   BatteryLevel;
    s8   ChargedLevel;
    s8   EndOfChargeValue;
    bool ChargingType;
    bool ChargerPlugged;
    bool BatteryAlarm;
    bool PreChargeState;
    bool VbusPollingState;
	vm_BatChangeCause_e ChangeBatCause;
    u16  BitMap;
    bool BatteryPlug;
    u8   BatPlugID;
    BatID_e BatteryID;
} vm_batmsg_t;

typedef void(* pfnMsgCallback)(vm_batmsg_t*);
typedef void(* pfnParseCallback)(u16);

/**  *\brief Battery Alarm type  */
typedef enum
{
    BAT_ALARM_TEMPERTURE = 1,
    BAT_ALARM_OVERVOLTAGE = 2,
} vm_BatAlarmType_e;

/**
 * \brief Possible values for end of charge reasons
 */
typedef enum
{
    BAT_CHARGE_COMPLETED,           ///< charging stopped because battery full
    BAT_SECURITY_CRITERION_USED     ///< charging stopped because security criterion (temperature or time)
} vm_batMmiEndOfCharge_t;


/**
 * \brief Structure used in battery level message
 */
typedef struct
{
    s8  BatteryLevel; ///< to take in \ref vm_batMmiBatteryLevel_t enumeration
    s8  ChargedLevel; ///< remaining battery capacity in percent
} vm_batLevel_t;

/**
 * \brief Structure used in \ref BAT_CHARGING_ON message
 */
typedef struct
{
    s8  EndOfChargeValue; ///< either \ref BAT_CHARGE_COMPLETED or \ref BAT_SECURITY_CRITERION_USED
} vm_batEndOfCharge_t;

/**
 * \brief Structure used in \ref BAT_CTN message
 */
typedef struct
{
    u16  BatteryTemperature; ///< battery temperature in mV
} vm_batTemperature_t;

/**
 * \brief Structure used in \ref BAT_CHARGER_ON or \ref BAT_CHARGER_OFF message
 */
typedef struct
{
    bool ChargerPlugged;  ///< TRUE if the charger is plugged, FALSE otherwise
    bool VbusDetected;  ///< TRUE if the VBUS is detected when charger plugged, FALSE otherwise
} vm_batChargerPlugged_t;

/**
 * \brief Structure used in \ref BAT_CHARGER_ON or \ref BAT_CHARGER_OFF message
 */
typedef struct
{
    bool VbusPollingState;  ///< TRUE if the VBUS is detected when polling VBUS, FALSE otherwise
} vm_batVbusPollingState_t;

#ifdef __LOW_BATT_DETECT__
extern u16 gabatVol[25];
#endif

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
s8   vm_batGetLevel (BatID_e BatID);
bool vm_batGetChargerState (void);
bool vm_batGetChargingState (void);
u16  vm_batGetVoltage(BatID_e BatID);
u16  vm_batGetCTNVoltage (void);
bool vm_batGetFirstChargerState (void);
void vm_batSubscribe (u8 mailbox);
void vm_batunSubscribe(void);
u16  vm_batGetChargerVoltage(void);
u16  vm_batGetChargerCurrent(void);
void vm_batMMISubscribe(pfnMsgCallback msgfunc, pfnParseCallback parsefunc);
void vm_batMMIunSubscribe(void);
void vm_batForceMmiLevelUpdate(void);
void vm_batBatteryDetectedBySW(bool * facts);
#ifdef __DUAL_BATT_DRV__
void vm_batChangeBattery(BatID_e BatID);
void vm_batGetBatteryPresence(BatID_e *BatID);
#endif

#endif  /* __MDL_VM_BAT_PUB_H__ */

