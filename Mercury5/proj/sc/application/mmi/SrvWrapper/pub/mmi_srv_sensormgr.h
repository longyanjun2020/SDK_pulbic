/**
* @file    mmi_srv_sensormgr.h
* @brief  only support Accelerometer sensor(G-Sensor) now
*
*/

#ifndef __MMI_SRV_SENSORMGR_H__
#define __MMI_SRV_SENSORMGR_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_sensormgr_forward.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef void (*SrvSensorMgrSensorNotify_CB)(SENSOR_e eSensor, SensorInfo_u *pSensorInfo, IBase *pUserdata);


/*=============================================================*/
// functions
/*=============================================================*/
/** SrvSensorMgrSetSensorNotifyCb
* @brief   The interface is used to Set CB which will trigger when a sensor change status.
* A instance can register only once for one sensor (and associate a call back).
*
* The sensor can be turn-on only when there exist register for that sensor,
* and can be turn-off if no one is interested in the specific sensor to save power.
*
* @param[in]       eSensor                     Sensor ID which notify the object when this sensor status change
* @param[in]       eDelay                      Delay level enum value reference to SENSOR_NOTIFY_DELAY_et
* @param[in]       bNotifyOnPowerSavingMode    Set TRUE if this client need the sensor's information  when entering power saving mode
* @param[in]       pfnCallBack                 a call back function which trigger sensor status changed
*
* @retval MAE_RET_SUCCESS                      Success
* @retval MAE_RET_NOT_SUPPORTED                Do not support more than one listener for one object
*/
MAE_Ret SrvSensorMgrSetSensorNotifyCb(SENSOR_e eSensor,
                                      SENSOR_NOTIFY_DELAY_e eDelay,
                                      boolean bNotifyOnPowerSavingMode,
                                      SrvSensorMgrSensorNotify_CB pfnCallBack);


/** SrvSensorMgrSetNotifyOnPowerSavingMode
* @brief  Change the listener to listen on power saving mode or not.
*
* @param[in]  eSensor                          Sensor ID which notify the object when this sensor status change
* @param[in]  bNotifyOnPowerSavingMode         Set TRUE if change the listener to listen on power saving mode
*
* @retval MAE_RET_SUCCESS                      Success
* @retval MAE_RET_NOT_SUPPORTED                Listener not found
*/
MAE_Ret SrvSensorMgrSetNotifyOnPowerSavingMode(SENSOR_e eSensor, boolean bNotifyOnPowerSavingMode);

/** SrvSensorMgrSetNotifyDelay
* @brief  Change the delay time of a notify for a specific sensor.
*
* @param[in]       eSensor                     Sensor ID which notify the object when this sensor status change
* @param[in]       eDelay                      Delay level enum value reference to SENSOR_NOTIFY_DELAY_et
*
* @retval MAE_RET_SUCCESS                      Success
* @retval MAE_RET_BAD_PARAM                    If eSensor is not SENSOR_ACCELEROMETER
*/
MAE_Ret SrvSensorMgrSetNotifyDelay(SENSOR_e eSensor, SENSOR_NOTIFY_DELAY_e eDelay);

/** SrvSensorMgrGetNotifyDelay
* @brief  Get current notify delay type for this sensor
*
* @param[in]       eSensor                     Sensor ID which notify the object when this sensor status change
* @param[in]       pDelay                      point to SENSOR_NOTIFY_DELAY_et with the result of delay level enum value
*
* @retval MAE_RET_SUCCESS                       Success
* @retval MAE_RET_FAILED                        Bad parameter
*/
MAE_Ret SrvSensorMgrGetNotifyDelay(SENSOR_e eSensor, SENSOR_NOTIFY_DELAY_e *pDelay);

/** SrvSensorMgrSetPowerSavingMode
* @brief  Tell SensorMgr to enter or leave power saving mode.
* Enter power saving mode will cause the sensor to stop working and could
* save energy if all existed client for this sensor do not need the sensor
* information in power saving mode. If exist clients which need the sensor's
* information, go into power saving mode will try to turn off the sensor and
* only those clients will continue receive the sensor's information.
*
* @param[in]          bisPowerSavingOn                       Set TRUE to enter power saving mode and set FALSE to leave power saving mode
* 
* @retval MAE_RET_SUCCESS                       Success
* @retval others                                Param error or out of memory
*/
MAE_Ret SrvSensorMgrSetPowerSavingMode(boolean bisPowerSavingOn);

/** SrvSensorMgrGetDevInfo
* @brief  Get device information for this sensor
*
* @param[in]       eSensor                     Sensor ID which notify the object when this sensor status change
* @param[in]       pDevInfoOut                 point to SensorDevInfo_u with the result of device information
*/
MAE_Ret SrvSensorMgrGetDevInfo(SENSOR_e eSensor, SensorDevInfo_u *pDevInfoOut);

#endif // __MMI_SRV_SENSORMGR_H__

