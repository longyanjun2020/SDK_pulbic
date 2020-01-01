/**
* @file     mmi_srv_battery.h
* @brief   This describes the service wrapper interface of battery
*             You can get battery status / register a CB to listen the battery event          
*/

#ifndef __MMI_SRV_BATT_H__
#define __MMI_SRV_BATT_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_battery_forward.h"
#include "mmi_mae_battery.h"

/*=============================================================*/
// Specific Service ListenerCallBack API
/*=============================================================*/
/** SrvBatteryBattLevelChangeCB
@brief  The interface is the CB for battery level changes. 
           It will get battery level with certain battery ID. The event is EVT_BATTMODEL_BATTLEVEL_CHANGE

@param[out]     pThis             The pointer of Applet
@param[out]     MAEBatteryLevel_e    Current battery level
                          MAE_BATT_DUMMY_LEVEL       Uninitialized Dummy level
                          MAE_BATT_TOO_LOW_FOR_COMM  Battery level too low. Handset has to be turned off
                          MAE_BATT_LOW_BATTERY       Battery level low. Handset should warn the user
                          MAE_BATT_LEVEL_0           Battery level 0
                          MAE_BATT_LEVEL_1           Battery level 1
                          MAE_BATT_LEVEL_2           Battery level 2
                          MAE_BATT_LEVEL_3           Battery level 3
                          MAE_BATT_LEVEL_4           Battery level 4
                          MAE_BATT_LEVEL_5           Battery level 5
                          MAE_BATT_LEVEL_6           Battery level 6
                          MAE_BATT_LEVEL_7           Battery level 7
@param[out]     MAEBatteryID_e		The battery ID of level changes (MAE_BATT_MASTER/MAE_BATT_SLAVE)

*/
typedef void (*SrvBatteryBattLevelChangeCB)(void *pThis, MAEBatteryLevel_e eLevel, MAEBatteryID_e eBatID);
/** SrvBatteryChargingStatusChangeCB
@brief  The interface is the CB for battery charging status changes. 
           It will get the battery ID with its battery charging status. The event is EVT_BATTMODEL_CHARGINGSTATUS_CHANGE

@param[out]     pThis             The pointer of Applet
@param[out]     MAEChargingStatus_e    Current battery charging status
                          MAE_CHGSTATUS_NO_CHARGER: No Charger inserted
                          MAE_CHGSTATUS_CHARGING: Charging normally
                          MAE_CHGSTATUS_FULLY_CHARGED: Fully Charged
                          MAE_CHGSTATUS_BADCHARGER: Unknown Charger
                          MAE_CHGSTATUS_UNKNOWN: Unrecognized status
@param[out]     MAEBatteryID_e		   The battery ID of charging status changes (MAE_BATT_MASTER/MAE_BATT_SLAVE)

*/
typedef void (*SrvBatteryChargingStatusChangeCB)(void *pThis, MAEChargingStatus_e eChargingStatus, MAEBatteryID_e eBatID);
/** SrvBatteryExtPwrChangeCB
@brief  The interface is the CB for charger status changes. 
           It will get its battery charger status. The event is EVT_BATTMODEL_EXTPWR_CHANGE

@param[out]     pThis             The pointer of Applet
@param[out]     bChargerPlugged    The charger status is plugging in or out  (ON/OFF)(TRUE if Charger Plugged)

*/
typedef void (*SrvBatteryExtPwrChangeCB)(void *pThis, boolean bChargerPlugged);
/** SrvBatteryHardwareAlarmCB
@brief  The interface is the CB for charger voltage too high (>7.5) and can not charging anymore. 
           When you receive this CB, that means the charger can not work.
           The event is EVT_BATTMODEL_HARDWARE_ALARM

@param[out]     pThis             The pointer of Applet
*/
typedef void (*SrvBatteryHardwareAlarmCB)(void *pThis, MAEBattAlarmType_e eAlarmType); //EVT_BATTMODEL_HARDWARE_ALARM

/** SrvBatteryPreChargeOnOffCB
@brief  The interface is the CB for power on mode (charger power on/user power on). 
           The events are EVT_BATTMODEL_PRECHARGE_ON, EVT_BATTMODEL_PRECHARGE_OFF.

@param[out]     pThis             The pointer of Applet
@param[out]     bPreChargeOn    If you power on by charger , TRUE will be returned (EVT_BATTMODEL_PRECHARGE_ON)
                                                 If user power on without charger, FALSE  will be returned (EVT_BATTMODEL_PRECHARGE_OFF)
*/
typedef void (*SrvBatteryPreChargeOnOffCB)(void *pThis, boolean bPreChargeOn);
/** SrvBatteryPlugStatusChangeCB
@brief  The interface is the CB for battery plugged in or out status.  
           The event is EVT_BATTMODEL_PLUGSTATUS_CHANGE.
           This event will be triggered for dual battery

@param[out]     pThis             The pointer of Applet
@param[out]     MAEBatteryID_e   The battery ID of plugging status changes (MAE_BATT_MASTER/MAE_BATT_SLAVE)
                        bPlugBattStatus    If you plug in the battery , TRUE will be returned.
                                                   When you plug out, FALSE  will be returned 
*/
typedef void (*SrvBatteryPlugStatusChangeCB)(void *pThis, MAEBatteryID_e eBatID, boolean bPlugBattStatus);
/** SrvBatteryCurrBattChangeCB
@brief  The interface is the CB for battery ID changes.  
           The event is EVT_BATTMODEL_CURRBATT_CHANGE.
           This event will be triggered for dual battery

@param[out]     pThis             The pointer of Applet
@param[out]     MAEBatteryID_e   The current battery ID (MAE_BATT_MASTER/MAE_BATT_SLAVE)
                                                  When battery 1 is charging completed or low battery, it will change to battery2.
*/
typedef void (*SrvBatteryCurrBattChangeCB)(void *pThis, MAEBatteryID_e eBatID);

/*=============================================================*/
// Battery API - register a CB function
/*=============================================================*/
/** SrvBatterySetBattLevelChangeCB
@brief  The interface is to set CB which will be triggered when battery level changes (MAEBatteryLevel)

@param[in]     pfnLevelChangeCB    SrvBatteryBattLevelChangeCB CB to info owner Battery level change data

@retval  MAE_RET_SUCCESS     Successfully.
@retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
@retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
MAE_Ret SrvBatterySetBattLevelChangeCB(SrvBatteryBattLevelChangeCB pfnLevelChangeCB);

/** SrvBatterySetChargingStatusChangeCB
@brief  The interface is to set CB which will be triggered when charging status change (MAEChargingStatus)

@param[in]     pfnStatusChangeCB   SrvBatteryChargingStatusChangeCB CB to info owner charging status change data

@retval  MAE_RET_SUCCESS     Successfully.
@retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
@retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
MAE_Ret SrvBatterySetChargingStatusChangeCB(SrvBatteryChargingStatusChangeCB pfnStatusChangeCB);

/** SrvBatterySetExtPwrChangeCB
@brief  The interface is to set CB which will be triggered when external power change.
           The charger status is plugging in or out  (ON/OFF)(TRUE if Charger Plugged)

@param[in]     pfnExtPwrChangeCB   SrvBatteryExtPwrChangeCB CB to info owner charger change (plug in or out)

@retval  MAE_RET_SUCCESS     Successfully.
@retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
@retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
MAE_Ret SrvBatterySetExtPwrChangeCB(SrvBatteryExtPwrChangeCB pfnExtPwrChangeCB);

/** SrvBatterySetHardwareAlarmCB
@brief  The interface is use to Set CB which will trigger when hardware alarm.
           When the charger voltage is too high (>7.5), HW will trigger interrupt and stop charging

@param[in]     pfnHWAlarmCB        SrvBatteryHardwareAlarmCB CB to info owner hardware alarm

@retval  MAE_RET_SUCCESS     Successfully.
@retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
@retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
MAE_Ret SrvBatterySetHardwareAlarmCB(SrvBatteryHardwareAlarmCB pfnHWAlarmCB);

/** SrvBatterySetPreChargeOnOffCB
@brief  The interface is to set CB which will be triggered when precharge on/off.
           If you power on by charger , TRUE will be returned

@param[in]     pfnPreChargeCB      SrvBatteryPreChargeOnOffCB CB to info owner precharge on/off

@retval  MAE_RET_SUCCESS     Successfully.
@retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
@retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
MAE_Ret SrvBatterySetPreChargeOnOffCB(SrvBatteryPreChargeOnOffCB pfnPreChargeCB);

/** SrvBatterySetPlugStatusChangeCB
@brief  The interface is to set CB which will be triggered when battery is plugged in or out.

@param[in]     pfnPlugStatusCB   SrvBatteryPlugStatusChangeCB CB to indicate owner of pluging battery status (Plug in/out)
                                                   This event will be triggered for dual battery

@retval  MAE_RET_SUCCESS     Successfully.
@retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
@retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
MAE_Ret SrvBatterySetPlugStatusChangeCB(SrvBatteryPlugStatusChangeCB pfnPlugStatusCB);

/** SrvBatterySetCurrBattChangeCB
@brief   The interface is to set CB which will be triggered when current battery ID changes.

@param[in]     pfnCurrBattCB   SrvBatteryCurrBattChangeCB CB to indicate owner of changing current battery ID (change by driver)
                                                When battery 1 is charging completed or low battery, it will change to battery2.
                                                This event will be triggered for dual battery

@retval  MAE_RET_SUCCESS     Successfully.
@retval  MAE_RET_BAD_PARAM   Failed. Invalid paramater.
@retval  MAE_RET_NOT_READY   Failed. IBattery is not ready yet.
*/
MAE_Ret SrvBatterySetCurrBattChangeCB(SrvBatteryCurrBattChangeCB pfnCurrBattCB);

/*=============================================================*/
// Battery API - get/set battery status function
/*=============================================================*/
/** SrvBatteryGetBattStatus
@brief  Function identifies the current battery status of current battery ID.

@param[out]     MAEBattStatus_e      Indicates the current battery status of current battery ID.
				MAE_BATTSTATUS_POWERDOWN: Bettery level too low to keep handset operating. Power down required.
				MAE_BATTSTATUS_LOW: Battery needs to be charged
				MAE_BATTSTATUS_NORMAL: Battery is within operating level
				MAE_BATTSTATUS_UNRECOGNIZED: Unrecognized battery status
                       You can get the detailed battery level by SrvBatteryGetBattLevel                       

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_READY           Battery Srv is already terminated.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryGetBattStatus(MAEBattStatus_e *pStatus);

/** SrvBatteryGetChargerStatus
@brief  Function identifies the current charger status of current battery ID.

@param[out]     pStatus             Indicates the current charger status of current battery ID.
				MAE_CHGSTATUS_NO_CHARGER: No charger inserted
                            MAE_CHGSTATUS_CHARGING: Charging normally
                            MAE_CHGSTATUS_FULLY_CHARGED: Fully charged
                            MAE_CHGSTATUS_BADCHARGER: Charging stopped due to hardware error
                            MAE_CHGSTATUS_UNKNOWN: Charging stopped due to unknown reason 

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_BAD_PARAM     IBattery / pStatus is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryGetChargerStatus(MAEChargerStatus_e *pStatus);

/** SrvBatteryExternalPowerExist
@brief  Function identifies whether an external power source exist.

@param[out]     pbExtPower          TRUE value if a charger has been plugged

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_BAD_PARAM     IBattery / pbExtPower is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryExternalPowerExist(boolean *pbExtPower);

/** SrvBatteryGetChargerType
@brief  Function identifies the current charger type. (from wall charger or USB)

@param[out]     pType               indicate the current charger types
                            MAE_CHARGERTYPE_INVALID: Invalid charger type or charger didn't be plugged in
                            MAE_CHARGERTYPE_STANDARD: Standard wall charger/when the charger voltage is higher than MAEBATTERY_MIN_STANDARD_CHGR_VOLTAGE(5800mV), that means the charger is from wall charging
                            MAE_CHARGERTYPE_USB: Normal USB charger/when the charger voltage is higher than MAEBATTERY_MIN_USB_CHGR_VOLTAGE(3900mV) and the current is higher than MAEBATTERY_HIGH_USB_CURRENT(500mA), that means the charger is from USB
                            MAE_CHARGERTYPE_USB_LOW: Low current USB charger/when the charger voltage is higher than MAEBATTERY_MIN_USB_CHGR_VOLTAGE(3900mV) and the current is higher than MAEBATTERY_LOW_USB_CURRENT(100mA), that means the charger is from low USB

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_BAD_PARAM     IBattery / pType is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryGetChargerType(MAEChargerType_e *pType);

/** SrvBatteryIsPowerOnAllowed
@brief  Function identifies whether the battery has enough power for handset to power on.

@param[out]     pbAllow             Returned boolean. TRUE if allowed, FALSE if disallowed
                                                Can't power on handset when low battery.

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_BAD_PARAM     IBattery / pbAllow is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryIsPowerOnAllowed(boolean *pbAllow);

/** SrvBatteryIsPowerOnByCharger
@brief  Function identifies whether the handset is powered on due to insertion of an external power source.

@param[in]      pbPowerOn           Returned boolean. TRUE if power on by charger, FALSE if power on by user

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_BAD_PARAM     IBattery / pbPowerOn is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryIsPowerOnByCharger(boolean *pbPowerOn);

/** SrvBatteryGetBattLevel
@brief  Function returns current battery level.

@param[in]      MAEBatteryID_e    The battery ID that you want to get the battery level (MAE_BATT_MASTER/MAE_BATT_SLAVE)

@retval MAEBatteryLevel_e 
      MAE_BATT_DUMMY_LEVEL : invalid battery level
      MAE_BATT_TOO_LOW_FOR_COMM : Battery level too low. Handset has to be turned off
      MAE_BATT_LOW_BATTERY : Battery level low. Handset should warn the user and need to be charged
      MAE_BATT_LEVEL_0~MAE_BATT_LEVEL_7  : normal battery level
*/
MAEBatteryLevel_e SrvBatteryGetBattLevel(MAEBatteryID_e eBatID);

/** SrvBatteryGetBattVoltage
@brief  Function returns current battery voltage(mV).

@param[in]      MAEBatteryID_e    The battery ID that you want to get the battery voltage (MAE_BATT_MASTER/MAE_BATT_SLAVE)

@retval u16     battery voltage (mV)
*/
u16 SrvBatteryGetBattVoltage(MAEBatteryID_e eBatID);

/** SrvBatteryNotifyBattLevel
@brief  Function is used for ap to request for battery level notification.

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_FOUND      Battery model is NULL.
@retval MAE_RET_BAD_PARAM     IBattery is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryNotifyBattLevel(void);

/** SrvBatteryChangeBattery
@brief  Function is used for ap to set current battery ID. (change by user)

@param[in]      MAEBatteryID_e      The battery ID that you want to change to (MAE_BATT_MASTER/MAE_BATT_SLAVE)
                                                    For Dual battery, you can get change battery ID to MAE_BATT_MASTER / MAE_BATT_SLAVE. It is no used for single battery

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_BAD_PARAM     IBattery is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryChangeBattery(MAEBatteryID_e eBatID);

/** SrvBatteryGetBatteryPresence
@brief  Function is used for ap to get current battery ID.

@param[out]     MAEBatteryID_e      Indicates the current battery ID(MAE_BATT_MASTER/MAE_BATT_SLAVE)
                                                     For Dual battery, you can get MAE_BATT_MASTER / MAE_BATT_SLAVE. Or you will get MAE_BATT_MASTER all the time.

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_BAD_PARAM     IBattery is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryGetBatteryPresence(MAEBatteryID_e *pBatID);

/** SrvBatteryGetBattNumber
@brief  Function is used for ap to get current battery number.

@param[out]     nBatNum             Current battery number 
                                                  For Dual battery, you can get 1 or 2 battery number. Or you will get 1 all the time.

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_BAD_PARAM     IBattery is NULL.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
*/
MAE_Ret SrvBatteryGetBattNumber(u8 *pBatNum);

/** SrvBatteryCheckLowBattery
@brief   Force send notify to mmi if battery is low when executed.
@retval MAE_RET_SUCCESS         Always successful
*/
MAE_Ret SrvBatteryCheckLowBattery(void);

/** SrvBatteryIsBatteryExist
@brief  This function to get battery exist or not

@param[out]     pbExist             Returned boolean. TRUE if Exist, FALSE if unexist

@retval MAE_RET_SUCCESS         If successful.
@retval MAE_RET_NOT_READY      Battery Srv is already terminated.
@retval MAE_RET_OUT_OF_MEMORY   If malloc fail.
@retval MAE_RET_NOT_SUPPORTED   If not support power on without battery.
*/
MAE_Ret SrvBatteryIsBatteryExist(boolean *pbExist);

#endif /*__MMI_SRV_BATT_H__*/
