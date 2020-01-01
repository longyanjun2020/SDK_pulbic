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



#ifndef __DRV_BACKLIGHT_API_H__
#define __DRV_BACKLIGHT_API_H__

/**
* @file    drv_backlight_api.h
* @version
* @brief   This module defines the Unified Driver Interface (UDI) of backlight & breathlight.
*
*/


/**
 * @defgroup Backlight Backlight Driver
 * @ingroup Driver
 * @brief Backlight controller interface.
 *        These functions will connect to customer's Backlight functions.
 * @details These APIs are used for control different Backlights
 * @note Detect correct customer's driver is not Support.\n
 *        Reference : msw8533x_backlight_apn_v01.pdf
 **/


/** \addtogroup Backlight
 *  @{
 * \file
 */


#include "vm_types.ht"
#include "drv_backlight_forward.h"


/**
 * \fn DrvBacklightErrCode_e DrvBacklightInit(void)
 * \brief Find out correct customer backlight driver and run it's init code
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvBacklightInit(void);

/**
 * \fn DrvBacklightErrCode_e DrvBacklightSetLevel(u16 nLevel, u16 nCurLevel)
 * \brief Set backlight level, this function will
 * link to customer backlight function.
 * \param[in] nLevel Purpose Level. It is between 0 and max level. DrvBacklightLevelCount() can get it's max level.
 * \param[in] nCurLevel Current Level
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvBacklightSetLevel(u16 nLevel, u16 nCurLevel);

/// @cond INTERNAL
/**
 * \fn DrvBacklightErrCode_e DrvBacklightSingleStep(void)
 * \brief Push forward single step, this function will
 * link to customer backlight function.
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvBacklightSingleStep(void);
/// @endcond


/**
 * \fn u16 DrvBacklightGetStrInfo(u8 id, char *pStr, u16 maxLen)
 * \brief Get backlight string information, this function will
 * link to customer backlight function.
 * \param[in] id For Identification if need
 * \param[out] *pStr String point, copy device info into here
 * \param[in] maxLen Length of maximum store size
 * \return Len of string
 */
u16 DrvBacklightGetStrInfo(u8 id, char *pStr, u16 maxLen);

/**
 * \fn u32 DrvBacklightLevelCount(void)
 * \brief Return max Level, this function will return customer backlight max level.
 * \return Max Level
 */
u32 DrvBacklightLevelCount(void);

#ifdef __SUBBACKLIGHT_DRV__
/**
 * \fn DrvBacklightErrCode_e DrvSubBacklightInit(void)
 * \brief Find out correct customer backlight driver and run it's init code
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvSubBacklightInit(void);

/**
 * \fn DrvBacklightErrCode_e DrvSubBacklightSetLevel(u16 nLevel, u16 nCurLevel)
 * \brief Set backlight level, this function will
 * link to customer backlight function.
 * \param[in] nLevel Purpose Level. DrvSubBacklightLevelCount() can get it's max level.
 * \param[in] nCurLevel Current Level
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvSubBacklightSetLevel(u16 nLevel, u16 nCurLevel);

/// @cond INTERNAL

/**
 * \fn DrvBacklightErrCode_e DrvSubBacklightSingleStep(void)
 * \brief Push forward single step, this function will
 * link to customer backlight function.
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvSubBacklightSingleStep(void);
/// @endcond


/**
 * \fn u16 DrvSubBacklightGetStrInfo(u8 id, char *pStr, u16 maxLen)
 * \brief Get backlight string information, this function will
 * link to customer backlight function.
 * \param[in] id For Identification if need
 * \param[out] *pStr String point, copy device info into here
 * \param[in] maxLen Length of maximum store size
 * \return Len of string
 */
u16 DrvSubBacklightGetStrInfo(u8 id, char *pStr, u16 maxLen);

/**
 * \fn u32 DrvSubBacklightLevelCount(void)
 * \brief Return max Level, this function will return customer backlight max level.
 * \return Max Level
 */
u32 DrvSubBacklightLevelCount(void);
#endif



#ifdef __BREATHLIGHT_DRV__


/**
 * \fn DrvBacklightErrCode_e DrvBreathlightInit(void)
 * \brief Find out correct customer breathlight driver and run it's init code
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvBreathlightInit(void);

/**
 * \fn DrvBacklightErrCode_e DrvBreathlightSetLevel(u16 nLevel)
 * \brief Set breathlight level, this function will
 * link to customer breathlight function.
 * \param[in] nLevel Purpose Level. It is between 0 and max level. DrvBreathlightLevelCount() can get it's max level.
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvBreathlightSetLevel(u16 nLevel);
#ifdef __EXTEND_BREATHLIGHT_LED_DRV__

/**
 * \fn DrvBacklightErrCode_e DrvBreathlightSetExtendLevel(u32 nLevel, u32 nLevel2)
 * \brief Set breathlight extend level, this function will
 * link to customer breathlight function.
 * \param[in] nLevel Purpose Level
 * \param[in] nCurLevel Current Level
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvBreathlightSetExtendLevel(u32 nLevel, u32 nLevel2);
#endif

/// @cond INTERNAL

/**
 * \fn DrvBacklightErrCode_e DrvBreathlightSingleStep(void)
 * \brief Push forward single step, this function will
 * link to customer breathlight function.
 * \retval       DRV_BACKLIGHT_OK                           Success.
 * \retval       DRV_BACKLIGHT_FAIL                         Fail. Design for customer.
 */
DrvBacklightErrCode_e DrvBreathlightSingleStep(void);

/// @endcond


/**
 * \fn u16 DrvBreathlightGetStrInfo(u8 id, char *pStr, u16 maxLen)
 * \brief Get breathlight string information, this function will
 * link to customer breathlight function.
 * \param[in] id For Identification if need
 * \param[out] *pStr String point, copy device info into here
 * \param[in] maxLen Length of maximum store size
 * \return Len of string
 */
u16 DrvBreathlightGetStrInfo(u8 id, char *pStr, u16 maxLen);

/**
 * \fn u32 DrvBreathlightLevelCount(void)
 * \brief Return max Level, this function will return customer breathlight max level.
 * \return Max Level
 */
u32 DrvBreathlightLevelCount(void);

#endif

/** @}*/


#endif
