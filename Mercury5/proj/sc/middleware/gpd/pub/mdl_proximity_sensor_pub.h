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
* @file    mdl_proximity_sensor.h
* @version
* @brief   This module defines the General Peripheral Device Driver API layer
*
*/

#ifndef __MDL_PROXIMITY_SENSOR_H__
#define __MDL_PROXIMITY_SENSOR_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "mdl_gpd_pub.h"
#include "drv_batt_types.h"

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

#ifdef __PROXIMITY_SENSOR_DRV__
/*
 * @brief Register notification for proximity sensor. MMI will receive the notification if G-sensor status change.
 *
 * @param tNotifyCb          : Notification for device status change
 *
 * @retval MDL_GPD_OK        : Function request success
 * @retval MDL_GPD_FAIL      : Function request fail
 */
MdlGpdErrCode_e MdlProximitySensorRegNotify(MdlProximitySensorNotifyCb_t tNotifyCb);

#ifndef __DUAL_BATT_DRV__
/**
 * @brief Proximity sensor indication.
 *
 * @param data
 *
 * @retval MDL_GPD_OK        : Function request success
 * @retval MDL_GPD_FAIL      : Function request fail
 */
MdlGpdErrCode_e MdlProximitySensorIndication(u32 data);

/**
 * @brief Proximity sensor timeout.
 *
 * @param none
 *
 * @retval MDL_GPD_OK        : Function request success
 * @retval MDL_GPD_FAIL      : Function request fail
 */
MdlGpdErrCode_e MdlProximitySensorTimeout(void);
#endif

/**
 * @brief Switch Proximity Sensor
 *
 * @param eOperation         : Switch on, off
 * @param nPollingTime       : Set the polling speed for Proximity Sensor data. It should not less than 100 ms.
 *
 * @retval MDL_GPD_OK        : Function request success
 * @retval MDL_GPD_FAIL      : Function request fail
 */
MdlGpdErrCode_e MdlProximitySensorSwitch(MdlProximitySensorOp_e eOperation, u32 nPollingTime);

/**
 * @brief G-sensor X-axis and Y-axis data.
 *
 * @param none
 *
 * @retval MDL_GPD_OK        : Function request success
 * @retval MDL_GPD_FAIL      : Function request fail
 */
MdlGpdErrCode_e MdlPaiSensorIndication(void);


#endif
#endif /* __MDL_PROXIMITY_SENSOR_H__ */
