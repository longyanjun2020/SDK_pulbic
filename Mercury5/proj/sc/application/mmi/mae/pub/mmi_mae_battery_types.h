/**
 * @file mmi_mae_battery_types.h
 *
 * This header file defines IBattery enums and data types.
 *
 * @version $Id: mmi_mae_battery_types.h $
 */
#ifndef __MMI_MAE_BATTERY_TYPES_H__
#define __MMI_MAE_BATTERY_TYPES_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_clstbl.h"

/*-------------------------------------------------------------------------*/
/* Battery Model Events */
/*-------------------------------------------------------------------------*/

/* These Events are for Battery Model to notify their listener about the current status change */
opaque_enum(MAEBatteryEvent_e_)
{
    EVT_BATTMODEL_EXTPWR_CHANGE      = (CLSID_IBATTERY << 16 | 0),         /* Event which notifies an extrenal power source plugged in or off */
    EVT_BATTMODEL_BATTSTATUS_CHANGE,     /* Event which notifies current Battery Status change (unused for now) */
    EVT_BATTMODEL_BATTLEVEL_CHANGE,      /* Event which notifies current Battery level change */
    EVT_BATTMODEL_CHARGINGSTATUS_CHANGE, /* Event which notifies current Charging Status change */
    EVT_BATTMODEL_POWERON_ALLOWED,       /* Event which notifies if power on is allowed. Usually used after handset if forced to turn off */
    EVT_BATTMODEL_HARDWARE_ALARM,        /* Event which notifies a hardware related error */
    EVT_BATTMODEL_PRECHARGE_ON,          /* Event which notifies driver enters pre-charge mode(charging very slowly, requires handset to turn off all possible power consumption)*/
    EVT_BATTMODEL_PRECHARGE_OFF,         /* Event which notifies driver exit pre-charge mode */
    EVT_BATTMODEL_PLUGSTATUS_CHANGE,	 /* Plug In/Out Status Change*/
    EVT_BATTMODEL_CURRBATT_CHANGE,		 /* Current Battery Change*/
    EVT_BATTMODEL_UNRECOGNIZED           /* Event which notifies an unknown event is received from driver */
};

/* These Events are for Battery Model to notify their listener about the current Battery level change */
opaque_enum(MAEBatteryLevel_e_)
{
    MAE_BATT_LOW_BATTERY_ATCMD = -4,
    MAE_BATT_DUMMY_LEVEL,
    MAE_BATT_TOO_LOW_FOR_COMM,  /* Battery level too low. Handset has to be turned off */
    MAE_BATT_LOW_BATTERY,       /* Battery level low. Handset should warn the user */
    MAE_BATT_LEVEL_0,           /* Battery level 0 */
    MAE_BATT_LEVEL_1,           /* Battery level 1 */
    MAE_BATT_LEVEL_2,           /* Battery level 2 */
    MAE_BATT_LEVEL_3,           /* Battery level 3 */
    MAE_BATT_LEVEL_4,           /* Battery level 4 */
    MAE_BATT_LEVEL_5,           /* Battery level 5 */
    MAE_BATT_LEVEL_6,           /* Battery level 6 */
    MAE_BATT_LEVEL_7            /* Battery level 7 */
} ;

/* These Events are for Battery Model to notify their listener about the current charging status change */
opaque_enum(MAEChargingStatus_e_)
{
    MAE_CHARGINGSTATUS_CHARGING_DISABLE,   /* Charging functionality is disabled. Usually means no charger is attached */
    MAE_CHARGINGSTATUS_CHARGING_ON,        /* Charging is in progress */
    MAE_CHARGINGSTATUS_CHARGING_COMPLETE,  /* Charging Complete */
    MAE_CHARGINGSTATUS_CHARGING_OFF_SECURITY_CRITERION_USED,  /* Charging stopped due to hardware error */
    MAE_CHARGINGSTATUS_CHARGING_OFF_UNKNOWN      /* Charging stopped due to unknown reason */
};

opaque_enum(MAEBatteryID_e_)
{
    MAE_BATT_MASTER = 1,
    MAE_BATT_SLAVE,
    MAE_BATT_BOTH_MASTER_SUPPLY,
    MAE_BATT_BOTH_SLAVE_SUPPLY=7,
    MAE_BATT_NULL,
 };

/*-------------------------------------------------------------------------*/
/* IBATTERY Service Query Status */
/*-------------------------------------------------------------------------*/

/* These status indicates the current Charger Status. They are the return value of IBATTERY_GetChargerStatus */
opaque_enum(MAEChargerStatus_e_)
{
    MAE_CHGSTATUS_NO_CHARGER,
    MAE_CHGSTATUS_CHARGING,
    MAE_CHGSTATUS_FULLY_CHARGED,
    MAE_CHGSTATUS_PRECHARGE, /* A status indicates that driver enters pre-charge mode(charging very slowly, requires handset to turn off all possible power consumption)*/
    MAE_CHGSTATUS_UNKNOWN,
    MAE_CHGSTATUS_BADCHARGER,
    MAE_CHGSTATUS_CHARGING_DISABLED,
    MAE_CHGSTATUS_END
};

/* These status values indicate the current Charger Types. They are the return value of IBATTERY_GetChargerType */
opaque_enum(MAEChargerType_e_)
{
    MAE_CHARGERTYPE_INVALID,
    MAE_CHARGERTYPE_USB,
    MAE_CHARGERTYPE_STANDARD,
    MAE_CHARGERTYPE_USB_LOW,
    MAE_CHARGERTYPE_END
};

/* These status values indicate the simplified current Battery Status. They are the return value of IBATTERY_GetBattStatus */
opaque_enum(MAEBattStatus_e_)
{
    MAE_BATTSTATUS_POWERDOWN,
    MAE_BATTSTATUS_LOW,
    MAE_BATTSTATUS_NORMAL,
    MAE_BATTSTATUS_UNKNOWN,
    MAE_BATTSTATUS_UNRECOGNIZED,
    MAE_BATTSTATUS_MAX
};


opaque_enum(MAEBattMsgTypes_e_)
{
    MAE_BAT_LEVEL , ///<  message sent to indicated the battery level
    MAE_BAT_CHARGER_ON, ///< message sent when the charger is plugged
    MAE_BAT_CHARGER_OFF, ///< message sent when the charger is unplugged
    MAE_BAT_CHARGING_ON, ///< message sent when the charging starts
    MAE_BAT_CHARGING_OFF, ///< message sent when  the charging stops
    MAE_BAT_ALARM, ///< message sent when a battery alarm occurs
    MAE_BAT_CTN, ///< message sent when a CTN event occurs
    /* MST_CR_22330 -- begin */
    MAE_BAT_PRECHARGE_ON, /// charger power on and enter pre-charge mode
    MAE_BAT_PRECHARGE_OFF, /// charger power on and leave pre-charge mode
    /* MST_CR_22330 -- end */
    MAE_BAT_VBUS_STATE_ON, ///< message sent when VBUS is detected in polling VBUS
    MAE_BAT_VBUS_STATE_OFF,///< message sent when VBUS is not detected in polling VBUS
    /* Dual Battery */
    MAE_BAT_BATTCHANGE,
    MAE_BAT_PLUGSTATUS,    
    MAE_BAT_LAST_EXT_MSG
};

struct MAESRVBattery_t_
{
    s8                         nBatteryLevel; 	// battery level
    s8                         nChargingStatus;  // charging status
    boolean                    bChargerPlugged;
    // Dual battery
    boolean						bPlugStatus;	// in/out
    u8   						nBatPlugID;		// plug ID
    u8   						nCurrBattID;	// current ID
    u8                          nChangeBatCause;    //change battery cause
};

opaque_enum(MAEBattAlarmType_e_)
{
  MAE_BATTALARM_TEMPERTURE = 1,
  MAE_BATTALARM_OVERVOLTAGE = 2,
  MAE_BATTALARM_END
};

opaque_enum(MAEBattChangeCause_e_)
{
  MAE_BATT_CHANGECAUSE_LOW,
  MAE_BATT_CHANGECAUSE_FULL,
  MAE_BATT_CHANGECAUSE_END
};


#endif //__MMI_MAE_BATTERY_TYPES_H__

