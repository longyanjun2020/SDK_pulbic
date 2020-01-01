/**
 * @file    mmi_util_pwroff.h
 *
 * @brief   This file defines the interface to access VML related to power off utilities.
 * @author	kenny.wu@mstatsemi.com
 *
 * @version $Id: mmi_util_pwroff.h 5244 2007-12-13 07:25:23Z kenny.wu $
 */
#ifndef __MMI_UTIL_PWROFF_H__
#define __MMI_UTIL_PWROFF_H__
 
#include "mmi_mae_common_def.h"
 
/** mmi_pwroff_SwitchOffReq()
 * @brief Provide an interface to ask platform to switch off.
 * @retval TRUE Success
 * @retval FALSE Already in power down process.
 */
u8 mmi_pwroff_SwitchOffReq(void);

/** mmi_pwroff_SwitchOffAndChangeBandReq()
 * @brief Switch of the phone and request to change band during next power up.
 * @param band  
 */
u8 mmi_pwroff_SwitchOffAndChangeBandReq(u8 band);
#endif /*__MMI_UTIL_PWROFF_H__*/
