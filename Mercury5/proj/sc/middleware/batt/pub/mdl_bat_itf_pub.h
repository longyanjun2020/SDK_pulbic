/**
 * \file mdl_bat_itf_pub.h
 * \brief battery interface for MMI
*/
#ifndef __MDL_BAT_ITF_PUB_H__
#define __MDL_BAT_ITF_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "vm_msgof.hc"
#include "mdl_vm_bat_pub.h"  // for vm_batMmiBatteryLevel_t

#include "drv_batt_types.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/
typedef enum
{
    BAT_ALARM_CHARGER_OVER_VOLTAGE = 0, ///<  message sent to indicated the charger over voltage
    BAT_ALARM_BATTERY_OVER_TEMPERATURE, ///<  message sent to indicated the battery over temperature
    BAT_ALARM_LAST_MSG
} bat_AlarmTypes_t;

typedef struct
{
    //u32 Pad[4];
    bat_AlarmTypes_t BatAlarmTypes;
} bat_Alarm_t;

typedef struct
{
    u16 NbSleepedFrames;
} bat_MeasureMsg_t;

typedef struct
{
    BatID_e batid;
} bat_batid_t;

#ifndef __DUAL_BATT_DRV__

typedef enum
{
    BAT_ADC_OK,
    BAT_ADC_FAIL,
    BAT_ADC_BUSY
} bat_AdcStatus_e;
typedef void(* pfnADCCallBack)(u16 chlData, bat_AdcStatus_e status);
typedef struct
{
    bat_AdcChl_e adcChl;
    pfnADCCallBack callBackFunc;
} bat_MeasureADCMsg_t;

#endif
/**
 * Function Prototypes
 */
BattErrorno_e MdlBatGetLevel(vm_batMmiBatteryLevel_t *BatLevel, BatID_e BatID);
BattErrorno_e MdlBatGetChargerState(bool *ChargerState);
BattErrorno_e MdlBatGetChargingState(bool *ChargerState);
BattErrorno_e MdlBatGetVoltage(u16 *Voltage, BatID_e BatID);
BattErrorno_e MdlBatGetCTNVoltage(u16 *CTNVoltage);
BattErrorno_e MdlBatGetFirstChargerState(bool *FChargerState);
void MdlBatSubscribe(u8 mailbox);
void MdlBatForceMmiLevelUpdate(void);
void MdlMMIBatSubscribe(pfnMsgCallback msgfunc, pfnParseCallback parsefunc);
void MdlMMIBatunSubscribe(void);
BattErrorno_e MdlBatGetChargerVoltage(u16 *ChargerVoltage);
BattErrorno_e MdlBatGetChargerCurrent(u16 *ChargerCurrent);

/** 
 * \fn void MdlBatBatteryDetectedBySW(bool * facts)
 * \brief interface function provided to MMI: Get Battery existence status. 
 * \param[in] facts -- TRUE value if Battery did plug-in handset.
 * \return NULL
 */
void MdlBatBatteryDetectedBySW(bool * facts);

#ifdef __DUAL_BATT_DRV__
void MdlBatChangeBattery(BatID_e BatID);
void MdlBatGetBatteryPresence(BatID_e *BatID);
#else
BattErrorno_e MdlBatExtendADCRequest(bat_AdcChl_e ADC_channel, pfnADCCallBack msgfunc);
#endif

#ifdef __NEW_AUTO_TESTING__
void MdlBatBatteryTestCase(vm_batMmiBatteryLevel_t BatLevel);
#endif
/*=============================================================*/
// Local function prototype & definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif /* __MDL_BAT_ITF_PUB_H__ */

