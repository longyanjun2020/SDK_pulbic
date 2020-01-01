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
* @file    mdl_gpd_util_pub.h
* @version
* @brief   This module defines General Peripheral Device Driver core API layer
*
*/
#ifndef __MDL_GPD_UTIL_PUB_H__
#define __MDL_GPD_UTIL_PUB_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "mdl_gpd_pub.h"

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
 * @brief The enumeration defines the wled current.
 */
typedef enum
{
    MDL_GPD_WLED_CURRENT_7_5 = 0,   /**< WLed current 7.5ma */
    MDL_GPD_WLED_CURRENT_10,        /**< WLed current 10ma */
    MDL_GPD_WLED_CURRENT_12_5,      /**< WLed current 12.5ma */
    MDL_GPD_WLED_CURRENT_15,        /**< WLed current 15ma */
    MDL_GPD_WLED_CURRENT_17_5,      /**< WLed current 17.5ma */
    MDL_GPD_WLED_CURRENT_20,        /**< WLed current 20ma */
    MDL_GPD_WLED_CURRENT_22_5,      /**< WLed current 22.5ma (default) */   
    MDL_GPD_WLED_CURRENT_25         /**< WLed current 25ma */
} MdlGpdWLedCurrent_e;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/**
 * @brief Get the power on cause.
 *
 * @param pPwrOnCause                   : [out] Power on cause
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdPowerOnCause(MdlGpdPwrOnCause_e *pePwrOnCause);


/**
 * @brief Get the version.
 *
 * @param eVerType                      : Version type
 * @param pVersion                      : [out] Version string
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdGetVersion(MdlGpdVerType_e eVerType, char *pVersion);


/**
 * @brief Dump E2P error.
 *
 * @param                               : None
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdDumpE2pError(void);

/**
 * @brief Dump per-task stack profile result.
 *
 * @param pStkInfo                      : [Out] where to put the result
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdGetStackProfile(MdlGpdSysStkUsgInfo_t* pStkInfo);

/**
 * @brief Dump INFO_LCD.
 *
 * @param                               : None
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdDumpInfoLcd(u32 Port);

/**
 * @brief Set wled current.
 *
 * @param eWLedCurrent                  : WLed current
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdSetWLedCurrent(MdlGpdWLedCurrent_e eWLedCurrent);

#endif /* __MDL_GPD_UTIL_PUB_H__ */

