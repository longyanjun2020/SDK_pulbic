/**
* @file    mmi_mae_sensormgr.h
* @brief   The document describes the interface of ISensorMgr
* ISensorMgr defines a set of interface to get information from several sensor installed on system
*
* Accelerometer (G-Sensor)
* ------------------------------
* An accelerometer is a device for measuring acceleration and gravity induced reaction forces.
* The 3-axis is defined as following. Z-axis was ignored for 2-axis model.
*
*            ^
*            | Y-axis                            .
*            |       /                   Z-axis /|\   /\        
*       .---------. /                            |   /   Y-axis
*       | .-----. |/                           .-|------.
*       | |     | |                           / .|----. /|
*       | |     | |                          / / |   / //
*       | |     | |                         / /  |  / //
* ----- | .-----. |-----> X-axis     ----- / .-----. //-----> X-axis
*       | == o == |                       / == o == //
*       |  1/2 3  |                      /  1 2 3  //
*       |  / 5 6  |                     /  4 5 6  //
*       | /7 8 9  |                    /  7 8 9  //
*       ./--------.                   ._________./
*       /    |                        .----/----.|
*      /     |                            /      |
*     V      |                           /       |
*   Z-axis
*           (1)                                  (2)
*
* The output value from g-sensor for the above two example are:
* (1) (x, y, z) = (0g, -1g, 0g)
* (2) (x, y, z) = (0g, 0g, -1g)
* which indicate direction of the gravity induced reaction forces.
* The unit for the output value is not g directly and you can use GSENSOR_VALUE_TO_G macro to convert the value
* to the g unit.
* To prevent the using of floating number, the output value for G-sensor is integer and located between
* GSENSOR_VALUE_MIN and GSENSOR_VALUE_MAX.
*
* If you need the value in G unit, you can use GSENSOR_VALUE_TO_G macro to convert it to G value and you
* may need to use a float or double type to handle this value.
* Here is the mapping between the output value and the g unit value:
*
* output value: GSENSOR_VALUE_MIN     <--> ... <--> GSENSOR_GVALUE_0G <-->  ... <--> GSENSOR_VALUE_MAX
*       g unit: GSENSOR_GVALUE_MIN(g) <--> ...  <-->      0g          <-->  ... <--> GSENSOR_GVALUE_MAX(g)
* and
* output value: GSENSOR_GVALUE_0G-GSENSOR_COUNTS_1G <--> GSENSOR_GVALUE_0G <--> GSENSOR_GVALUE_0G+GSENSOR_COUNTS_1G
*       g unit:                 -1g                 <-->        0g         <-->                  1g
*
* GSENSOR_COUNTS_1G is the count level for 1g, that is, ouput value exists GSENSOR_COUNTS_1G steps between 0g and 1g.
*
* Note: 1g = STANDARD_GRAVITY m/s^2
*
* If you are interested in the motion instead the real sensor value provided here, you can consider to
* use a implementaion of IMotionDetector. IMotionDetector provides a higher view for these g-sensor data.
*
*
* Implementations:
* CLSID_SENSORMGR, current implementation and device only support a 2-axis accelerometer sensor.
* References:
* degree	X(g)	value	Y(g)	value
* ------------------------------------------
*   90		1.000	33792	0.000	32768
*   85		0.996	33788	0.087	32856
*   80		0.985	33776	0.174	32946
*   70		0.940	33730	0.342	33118
*   60		0.866	33654	0.500	33280
*   45		0.707	33492	0.707	33492
*   30		0.500	33280	0.866	33654
*   20		0.342	33118	0.94	33730
*   10		0.174	32946	0.985	33776
*   05		0.087	32856	0.996	33788
*   00		0.000	32768	1.000	33792
*
* @author  mark.yang@mstarsemi.com
* @version $Id: mmi_mae_sensormgr.h 540 2009-03-31 11:04:04Z mark.yang $
*/
#ifndef __MMI_MAE_SENSORMGR_H__
#define __MMI_MAE_SENSORMGR_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_handler.h"
#include "mmi_mae_sensormgr_forward.h"

typedef enum
{
    SENSORMGR_LISTENER_PARAM_SWITCH_CONTEXT = 0,
    SENSORMGR_LISTENER_PARAM_LISTEN_ON_POWERSAVING
}SENSORMGR_LISTENER_PARAM_e;


/* Notify callback function prototype */
typedef void (*PfnMAE_SensorNotifyCb)(SENSOR_e sensor, SensorInfo_u* pSensorInfo, IBase *pObj);

#define INHERIT_ISensorMgr(IName)\
	INHERIT_IHandler(IName);\
	MAE_Ret (*AddListener)(IName *pThis, SENSOR_e sensor, SENSOR_NOTIFY_DELAY_e delay, boolean bSwitchContext, boolean listenOnPowerSavingMode, PfnMAE_SensorNotifyCb pNotifyCb, IBase *pObj);\
	MAE_Ret (*RemoveListener)(IName *pThis, SENSOR_e sensor, IBase *pObj);\
	MAE_Ret (*SetListenerParam)(IName *pThis, SENSOR_e sensor, IBase *pObj, SENSORMGR_LISTENER_PARAM_e param, u32 value);\
	MAE_Ret (*SetNotifyDelay)(IName *pThis, SENSOR_e sensor, SENSOR_NOTIFY_DELAY_e delay);\
	MAE_Ret (*GetNotifyDelay)(IName *pThis, SENSOR_e sensor, SENSOR_NOTIFY_DELAY_e *pOutDelay);\
	MAE_Ret (*SetPowerSavingMode)(IName *pThis, boolean isPowerSavingOn);\
    MAE_Ret (*GetDevInfo)(IName *pThis, SENSOR_e sensor, SensorDevInfo_u *pDevInfoOut)

DEFINE_INTERFACE(ISensorMgr);

/**
 * ISENSORMGR_QueryInterface
 * @param pThis Pointer to the ISensorMgr interface
 * @param id Interface ID. In this function, only IID_FILEMGR is supported.
 * @param pp Reference to a pointer to a function table if this interface is supported
 * @return number of reference count
 */
#define ISENSORMGR_QueryInterface(pThis, id, pp, pOwner)					GET_FUNCTBL(pThis,ISensorMgr)->QueryInterface(pThis,id,pp,pOwner)

/**
 * Register a listener to a sensor to get the information regularly.
 * A instance can register only once for one sensor (and associate a call back).
 *
 * The sensor can be turn-on only when there exist register for that sensor,
 * and can be turn-off if no one is interested in the specific sensor to save power.
 *
 * @param pThis Pointer to the ISensorMgr interface
 * @param sensor Sensor ID
 * @param delay Delay level enum value for from SENSOR_NOTIFY_DELAY_et
 * @param listenOnPowerSavingMode if this client need the sensor's information
 *        when entering power saving mode
 * @param pNOtifyCb The call back function. This function will be called regularly and bring the sensor's information to client
 * @param pObj object instance, bypass to the call back function
 */
#define ISENSORMGR_AddListener(pThis, sensor, delay, pNotifyCb, pObj)	GET_FUNCTBL(pThis,ISensorMgr)->AddListener(pThis, sensor, delay, TRUE, FALSE, pNotifyCb, pObj)
#define ISENSORMGR_AddListenerEx(pThis, sensor, delay, listenOnPowerSavingMode, pNotifyCb, pObj)	GET_FUNCTBL(pThis,ISensorMgr)->AddListener(pThis, sensor, delay, TRUE, listenOnPowerSavingMode, pNotifyCb, pObj)

/**
 * Remove listener for a specific sensor and instance.
 *
 * @param pThis Pointer to the ISensorMgr interface
 * @param sensor Sensor ID
 * @param pObj object instance
 */
#define ISENSORMGR_RemoveListener(pThis, sensor, pObj)					GET_FUNCTBL(pThis,ISensorMgr)->RemoveListener(pThis, sensor, pObj)

/**
 * Change the listener to listen on power saving mode or not.
 *
 * @param pThis Pointer to the ISensorMgr interface
 * @param sensor Sensor ID
 * @param pObj listener object instance
 * @param listenOnPowerSavingMode listen on power saving mode or not
 */
#define ISENSORMGr_SetListenOnPowerSaveingMode(pThis, sensor, pObj, listenOnPowerSavingMode)	GET_FUNCTBL(pThis,ISensorMgr)->SetListenerParam(pThis, sensor, pObj, SENSORMGR_LISTENER_PARAM_LISTEN_ON_POWERSAVING, listenOnPowerSavingMode)

/**
 * Change the delay for a specific sensor.
 * If there exist more than one listener for this sensor, this will effect all these clients.
 *
 * @param pThis Pointer to the ISensorMgr interface
 * @param sensor Sensor ID
 * @param delay delay time in millisecond
 */
#define ISENSORMGR_SetNotifyDelay(pThis, sensor, delay)					GET_FUNCTBL(pThis,ISensorMgr)->SetNotifyDelay(pThis,sensor,delay)

/**
* Get current notify delay for sensor
*/
#define ISENSORMGR_GetNotifyDelay(pThis, sensor, pOutDelay)				GET_FUNCTBL(pThis,ISensorMgr)->GetNotifyDelay(pThis, sensor, pOutDelay)

/**
* Tell SensorMgr to enter or leave power saving mode.
* Enter power saving mode will cause the sensor to stop working and could
* save energy if all existed client for this sensor do not need the sensor
* information in power saving mode. If exist clients which need the sensor's
* information, go into power saving mode will try to turn off the sensor and
* only those clients will continue receive the sensor's information.
*
* @param pThis Pointer to the ISensorMgr interface
* @param isPowerSavingOn TRUE Enter power saving mode
*             FALSE Leave power saving mode
* @see ISENSORMGR_AddListenerExt
*/
#define ISENSORMGR_SetPowerSavingMode(pThis, isPowerSavingOn)					GET_FUNCTBL(pThis,ISensorMgr)->SetPowerSavingMode(pThis, isPowerSavingOn)

/**
 * Get the sensor device's profile
 * @param pThis Pointer to the ISensorMgr interface
 * @param out Pointer to SensorDevInfo_u for fill the information
 * @return MAE_RET_SUCCESS if get info success
 * @return MAE_RET_NOT_READY if the information is not ready for get
 * @return MAE_RET_BAD_PARAM if the system do not support this sensor currently
 */
#define ISENSORMGR_GetDevInfo(pThis, sensor, out) 							    GET_FUNCTBL(pThis,ISensorMgr)->GetDevInfo(pThis, sensor, out)

MAE_Ret MAESensorMgr_New(MAE_ClsId nClsID, void **ppObj);

#endif //  __MMI_MAE_SENSORMGR_H__
