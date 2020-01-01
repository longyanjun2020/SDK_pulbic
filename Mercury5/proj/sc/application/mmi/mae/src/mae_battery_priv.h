/**
 * \file    mae_battery_priv.h
 * \brief   The document describes the interface of IBATTERY
 * \author  christoph.kuo@mstarsemi.com
 */
#ifndef __MAEBattery_H_PRIV_H__
#define __MAEBattery_H_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_forward.h"

/**
 * External Events
 */

/* The minimum voltage(in mV) to allow handset to power on */
#define MAEBATTERY_POWER_ON_ALLOWED_VOLT  (3400)

/* The allowable power on voltage(in mV) is higher if charger is plugged in. It is due to avoid sudden low power
warning after charger is plugged in and handset consumes power faster than charger charging it */
#define MAEBATTERY_POWER_ON_ALLOWED_VOLT_WITH_CHARGER  (3600)

/* Voltage(in mV) indicates low power warning */
#define MAEBATTERY_VOLT_LOW_WARNING        (3500)

/* Voltage(in mV) indicates power being too low and powering handset off */
#define MAEBATTERY_VOLT_VLOW_POWEROFF   (3400)

/* Maximum charger voltage(in mV) */
#define MAEBATTERY_MAX_CHGR_VOLTAGE            (10000)

/* Voltage(in mV) threshold for standard charger. If lower, then USB charger is in use */
#define MAEBATTERY_MIN_STANDARD_CHGR_VOLTAGE   (5800)

/* Low Voltage(in mV) threshold for USB */
#define MAEBATTERY_MIN_USB_CHGR_VOLTAGE        (3900)

/* High USB Current(in mA) */
#define MAEBATTERY_HIGH_USB_CURRENT         (500)

/* LOW USB Current(in mA) */
#define MAEBATTERY_LOW_USB_CURRENT          (100)

/* Maximum allowable Current(in mA) threshold for standard chargers  */
#define MAEBATTERY_MAX_STD_CURRENT          (400)


/**
 * Application structure
 */
typedef struct
{
    DECLARE_FUNCTBL(IBattery);	// function table pointer
    u32		RefCnt;		// reference count
    /* Add custom fields below */
    IMODEL                      *pIBatteryModel;
    boolean                     bChargerPlugged;
    boolean                     bIsPowerOnAllowed;
    boolean                     bTerminateState;
    boolean                     bPreChargeMode;
    s8                         nEndOfChargeReason; //MAEEndOfChargeReason
    s8                         nBatteryLevel; //MAEBatteryLevel
    s8                         nChargingStatus;  //MAEChargingStatus
    s8                          nBatteryChargedLevel;
    u16                         nBatteryTemperature;
	// Dual battery
	bool   						bPlugStatus;	// in/out
	u8   						nBatPlugID;		// plug ID
	u8   						nCurrBattID;	// current ID
} MAEBattery_t;

/* These Events are for IBATTERY to recognize the end of charge reason */
typedef enum
{
    MAE_BATT_CHARGE_COMPLETED,         /* Charging Complete */
    MAE_BATT_SECURITY_CRITERION_USED   /* Unknown Hardware Error */
} MAEEndOfChargeReason_e;

#endif /* __MAEBattery_H_PRIV_H__ */
