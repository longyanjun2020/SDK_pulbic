/*
 * PCBA config file
 */
#ifndef __CONFIG_SDK__
#define __CONFIG_SDK__

#include "dsc_Key.h"
#include "mmps_3gprecd.h"
#include "mmp_gpio_inc.h"
//#include "mmpf_sensor.h"
#include "ahc_common.h"
#if !defined(MINIBOOT_FW) && !defined(UPDATER_FW)
#include "GUI.h"
#endif

/*===========================================================================
 *  DBG Config
 *===========================================================================*/

#include "Config_SDK_EVB_C_TV_Decoder.h"

#define CUS_MIC_SENSITIVITY

#endif // __CONFIG_SDK__
