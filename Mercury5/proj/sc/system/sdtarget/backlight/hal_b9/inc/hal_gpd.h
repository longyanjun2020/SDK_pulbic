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
* @file    hal_gpd.h
* @version
* @brief   This module defines the General Peripheral Device (GPD) hal layer
*
*/

#ifndef __HAL_GPD_H__
#define __HAL_GPD_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* MACRO DEFINITION                                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* DATA TYPE DEFINITION                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* VARIABLE DEFINITION                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTION PROTOTYPE DECLARATION AND DEFINITION                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/**
 * @brief    White led toggle
 * @param    nLevel    : Switch level (0~15)
 * @retval   1         : Success
 * @retval   0         : fail
 *
 */
u8 HalGpdWLedToggle(u16 nLevel);


/**
 * @brief    White led GPO toggle
 * @param    nLed      : Switch which WLED(1~4)
 * @param    on        : Switch on/off
 * @retval   1         : Success
 * @retval   0         : fail
 *
 */
u8 HalGpdWLedGpoToggle(u8 nLed, bool on);


/**
 * @brief    Set WLed current
 * @param    nWLedCurrent  : WLed current.
 * @retval   1         : Success.
 * @retval   0         : fail.
 *
 */
u8 HalGpdSetWLedCurrent(u8 nWLedCurrent);

#endif //__HAL_PLL_H__
