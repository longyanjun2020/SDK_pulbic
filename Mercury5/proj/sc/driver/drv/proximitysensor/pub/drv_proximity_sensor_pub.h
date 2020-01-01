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
* @file    drv_proximity_sensor_pub.h
* @version
* @brief   This module defines the Unified Driver Interface (UDI) of Pai-sensor
*
*/

#ifndef ___DRV_PROXIMITY_SENSOR_PUB_H__
#define ___DRV_PROXIMITY_SENSOR_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/

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
 *  @brief The enumeration defines error codes of GPD drivers .
 */
typedef enum
{
    DRV_PAISENSOR_OK,                /**< Function complete successfully */
    DRV_PAISENSOR_FAIL,              /**< Function common fail */
} DrvPaiSensorErrCode_e;

/**
 * @brief The enumeration defines the operations of Pai-sensor.
 */
typedef enum
{
    DRV_PAISENSOR_OP_OFF = 0,        /**< Turn off Pai-sensor */
    DRV_PAISENSOR_OP_ON,             /**< Turn on Pai-sensor */
    DRV_PAISENSOR_OP_CHANGE_POLLING_TIME,             /**< Turn on Pai-sensor */
} DrvPaiSensorOp_e;


/**
 * @brief The structure defines the ccelerometer information of pai-sensor.
 */
typedef struct
{
    u16 dataL;                    /**< data--L thro */
    u16 dataH;                    /**< data--H thro */
    u16 op_flag;
} DrvPaiSensorData_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function declaration
/*=============================================================*/

/**
* @brief Pai-sensor initialization
*
* @param NONE
*
* @retval DRV_PAISENSOR_OK                   : Function request success
* @retval DRV_PAISENSOR_FAIL                 : Function request fail
*/
DrvPaiSensorErrCode_e DrvPaiSensorInit(void);

/**
 * @brief Pai-sensor power on/off
 *
 * @param eOperation                        : [in] power on/off
 *
 * @retval DRV_PAISENSOR_OK                   : Function request success
 * @retval DRV_PAISENSOR_FAIL                 : Function request fail
 */
DrvPaiSensorErrCode_e DrvPaiSensorSwitch(DrvPaiSensorOp_e eOperation);

/**
 * @brief Pai-sensor get accelerometer
 *
 * @param ptGsensorInfo                     : [out] accelerometer information
 *
 * @retval DRV_PAISENSOR_OK                   : Function request success
 * @retval DRV_PAISENSOR_FAIL                 : Function request fail
 */
DrvPaiSensorErrCode_e DrvPaiSensorGetData(DrvPaiSensorData_t* ptPaiSensorData);

/**
 * @brief Pai-sensor Calibration
 *
 * @param ptGsensorInfo                     : accelerometer information
 *
 * @retval DRV_GSENSOR_OK                   : Function request success
 * @retval DRV_GSENSOR_FAIL                 : Function request fail
 */

/**
* @brief Pai-sensor initialization
*
* @param NONE
*
* @retval DRV_PAISENSOR_OK                   : Function request success
* @retval DRV_PAISENSOR_FAIL                 : Function request fail
*/
DrvPaiSensorErrCode_e DrvPaiSensorIntpInit(u16 setHdata, u16 setLdata, u8 mode);

/**
* @brief Pai-sensor probe
*
* @param NONE
*
* @retval DRV_PAISENSOR_OK                   : Function request success
* @retval DRV_PAISENSOR_FAIL                 : Function request fail
*/
DrvPaiSensorErrCode_e DrvPaiSensorProbe(void);

#endif //___DRV_PROXIMITY_SENSOR_PUB_H__

