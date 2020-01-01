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
* @file    srv_drv_ofn_api.h
* @version
* @brief   This module defines the Unified Driver Interface (UDI) of OFN
*
*/

#ifndef __SRV_DRV_OFN_API_H__
#define __SRV_DRV_OFN_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_drv_ofn_forward.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 * @brief Clear OFN interrupt
 * @param void                          : void
 * @retval DRV_OFN_OK                   : Function request success
 * @retval DRV_OFN_FAIL                 : Function request fail
 */
DrvOfnErrCode_e DrvOfnClearInterrupt(void);

/**
 * @brief Unmask OFN interrupt
 * @param void                          : void
 * @retval DRV_OFN_OK                   : Function request success
 * @retval DRV_OFN_FAIL                 : Function request fail
 */
DrvOfnErrCode_e DrvOfnUnmaskInterrupt(void);

/** DrvOfnGetRawStatus
* @brief        get Raw Status of OFN interrupt in driver by check os state.
*
* @retval       OFN_OK         Success.
* @retval       Other             Failed.
*
*/
DrvOfnErrCode_e DrvOfnGetRawStatus(bool * bIntRawStatus);

/** DrvUnmaskOfnInterrupt
* @brief        Unmask OFN interrupt by keypad driver
*
* @retval       OFN_OK         Success.
* @retval       Other             Failed.
*
*/
DrvOfnErrCode_e DrvUnmaskOfnInterrupt(void);

/** DrvOfnProbe
* @brief        Probe the OFN device
*
* @retval       OFN_OK         Success.
* @retval       Other             Failed.
*
*/
DrvOfnErrCode_e DrvOfnProbe(void);


/** DrvOfnProcessed
* @brief        Decrement the key counter after the key has been processed by the customer binary
*
* @retval       OFN_OK         Success.
* @retval       Other             Failed.
*
*/
DrvOfnErrCode_e DrvOfnProcessed(void);

/**
 * @brief OFN enable
 *
 * @param void                        : void
 *
 * @retval DRV_OFN_OK                   : Function request success
 * @retval DRV_OFN_FAIL                 : Function request fail
 */
DrvOfnErrCode_e DrvOfnEnable(void);

/**
 * @brief OFN disable
 *
 * @param void                        : void
 *
 * @retval DRV_OFN_OK                   : Function request success
 * @retval DRV_OFN_FAIL                 : Function request fail
 */
DrvOfnErrCode_e DrvOfnDisable(void);

/**
 * @brief OFN get accelerometer
 *
 * @param ptOfnInfo                     : [out] accelerometer information
 *
 * @retval DRV_OFN_OK                   : Function request success
 * @retval DRV_OFN_FAIL                 : Function request fail
 */
DrvOfnErrCode_e DrvOfnGetInfo(DrvOfnData_t * ptOfnInfo);

#if defined(__DEVICE_INFO__)
/**
* @brief Ofn get device information
*
* @param id		: id
* @param str		: string point, copy device info into here
* @param MaxLen	: Max len of str
*
* @retval size      	: len of device information
*/
u16 DrvOfnGetStrInfo(u8 id, char *pStr, u16 maxLen);
#endif

DrvOfnErrCode_e DrvOfnSubscribe(u8 nMailbox);

#endif
