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
* @file    drv_proximity_sensor.h
* @version
* @brief   This file defines G-sensor driver function prototype and data structure
*
*/

#ifndef __DRV_PROXIMITY_SENSOR_H__
#define __DRV_PROXIMITY_SENSOR_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "sys_rtk_ho.h"
#include "drv_proximity_sensor_pub.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define PAISENSOR_DEBUG_LEVEL    (_CUS10 | LEVEL_12)

/* Configure pin of I2C SDA, SCL, interrupt in cust_gpio_xxx.c */
#define PAISENSOR_I2C_SDA_PIN    IO_CHIP_PROXIMITY_SENSOR_I2C_SDA  // PAD_NUM_DBB_GPIO_22_OUT
#define PAISENSOR_I2C_SCL_PIN    IO_CHIP_PROXIMITY_SENSOR_I2C_SCL  // PAD_NUM_DBB_GPIO_4_OUT
#define IO_CHIP_PAISENSOR_EXTINT IO_CHIP_PROXIMITY_SENSOR_INT      // PAD_NUM_DBB_GPIO_17_EXTINT4
#define IO_CHIP_PAISENSOR_LDOEN IO_CHIP_PROXIMITY_SENSOR_LDOEN      


/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 * @brief The function table defines proximity sensor driver function for different vendor.
 */
typedef struct
{
    bool (* pfnPaiSensorProbe)(void);
    bool (* pfnPaiSensorInit)(void);
    bool (* pfnPaiSensorEnable)(void);
    bool (* pfnPaiSensorDisable)(void);
    u16  (* pfnPaiSensorGetInfo)(DrvPaiSensorData_t*);
    bool (* pfnPaiSensorIntpInit)(u16 setHdata, u16 setLdata, u8 mode);
} DrvPaiSensorFuncTbl_t;


/*=============================================================*/
// Local function definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif /* __DRV_PROXIMITY_SENSOR_H__ */

