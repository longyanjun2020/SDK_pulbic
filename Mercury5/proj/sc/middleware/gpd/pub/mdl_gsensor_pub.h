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
* @file    mdl_gsensor_pub.h
* @version
* @brief   This module defines the General Peripheral Device Driver API layer
*
*/

#ifndef __MDL_GSENSOR_PUB_H__
#define __MDL_GSENSOR_PUB_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "mdl_gpd_pub.h"
#include "sys_rtk_ho.h"
/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/**
 * @brief The enumeration defines G-sensor status.
 */
typedef enum
{
    MDL_GSENSOR_STATUS_OFF,     /**< G-sensor OFF Status */
    MDL_GSENSOR_STATUS_ON,      /**< G-sensor ON Status */
    MDL_GSENSOR_STATUS_UNKNOWN  /**< G-sensor unknown Status */
} MdlGsensorStatus_e;

/**
 * @brief The structure defines G-sensor accelerometer info.
 */
typedef struct
{
    s32 nAxisX;
    s32 nAxisY;
    s32 nAxisZ;  /**< Reserved */
} MdlGsensorAccelerometerMsg_t;


/**
 * @brief The structure defines G-sensor query timing information.
 */
typedef struct
{
    u32             nTickcount;
    u32             nTickset;
    rtk_TimerId_t   tTimerID;
    rtk_MailboxId_t tMBoxNo;
} MdlGsensorAccelerometer_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/**
 * @brief Switch G-sensor
 *
 * @param eOperation                    : Switch on, off
 * @param nPollingTime                  : Set the polling speed for G-sensor data. It should not less than 100 ms.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGsensorSwitch(MdlGpdGsensorOp_e eOperation, u32 nPollingTime);


/**
 * @brief Register notification for G-sensor. MMI will receive the notification if G-sensor status change.
 *
 * @param tNotifyCb                     : Notification for device status change
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGsensorRegNotify(MdlGsensorNotifyCb_t tNotifyCb, MdlGpdInfo_t *ptGpdInfo);


/**
 * @brief G-sensor X-axis and Y-axis data.
 *
 * @param NONE
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGsensorIndication(void);


/**
 * @brief G-sensor X-axis and Y-axis data calibration for different direction of chip placement.
 *
 * @param ptGsensorInfo                 : Gsensor X-axis and Y-axis polling data.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGsensorCalibration(MdlGsensorNotifyInfo_t *pGsensorNotifyInfo);


/**
 * @brief G-sensor Calibration
 *
 * @param save_to_e2p                   : Indicate if save calibration into E2P.
 * @param ptCalibration                 : Pointer of calibration data.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGsensorOffsetCalibration(u8 nSaveToE2p, MdlGsensorAccelerometerMsg_t* ptCalibration);


/**
 * @brief Normalize G-sensor X-axis and Y-axis data to -1024 ~ +1024
 *
 * @param ptGsensorInfo                 : Gsensor X-axis and Y-axis data to normalize.
 * @param ptGsensorNotifyInfo           : Gsensor X-axis and Y-axis data after normalize.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGsensorNormalize(MdlGsensorAccelerometerMsg_t *ptGsensorInfo, MdlGsensorNotifyInfo_t *ptGsensorNotifyInfo);

#ifdef __NEW_AUTO_TESTING__
MdlGpdErrCode_e MdlGsensorAutoTestRotate(u8 rotate);
#endif

#endif /* __MDL_GSENSOR_PUB_H__ */
