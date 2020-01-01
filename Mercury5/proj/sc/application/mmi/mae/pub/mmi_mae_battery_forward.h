/**
 * @file mmi_mae_battery_forward.h
 *
 * This header file defines IBattery forward declaration.
 *
 * @version $Id: mmi_mae_battery_forward.h $
 */
#ifndef __MMI_MAE_BATTERY_FORWARD_H__
#define __MMI_MAE_BATTERY_FORWARD_H__

typedef_opaque_enum(MAEBatteryEvent_e_, MAEBatteryEvent_e);
typedef_opaque_enum(MAEBatteryLevel_e_, MAEBatteryLevel_e);
typedef_opaque_enum(MAEChargingStatus_e_, MAEChargingStatus_e);
typedef_opaque_enum(MAEBatteryID_e_, MAEBatteryID_e);
typedef_opaque_enum(MAEChargerStatus_e_, MAEChargerStatus_e);
typedef_opaque_enum(MAEChargerType_e_, MAEChargerType_e);
typedef_opaque_enum(MAEBattStatus_e_, MAEBattStatus_e);
typedef_opaque_enum(MAEBattMsgTypes_e_, MAEBattMsgTypes_e);
typedef_opaque_enum(MAEBattAlarmType_e_, MAEBattAlarmType_e);
typedef_opaque_enum(MAEBattChangeCause_e_, MAEBattChangeCause_e);

typedef struct MAESRVBattery_t_ MAESRVBattery_t;

#endif //__MMI_MAE_BATTERY_FORWARD_H__
