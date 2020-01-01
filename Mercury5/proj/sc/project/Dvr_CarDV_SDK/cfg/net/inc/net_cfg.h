//------------------------------------------------------------------------------
//
//  File        : net_cfg.h
//  Description :
//  Author      : Titan
//  Revision    : 1.0
//
//------------------------------------------------------------------------------

#ifndef _NET_CFG_H_
#define _NET_CFG_H_

#define WIFI_DRIVER_UNKNOW      0
#define WIFI_DRIVER_BCM         1
#define WIFI_DRIVER_MTK         2
#define WIFI_DRIVER_RTK         3
#define WIFI_DRIVER_ATBM        4

#if defined(BCM_AP6181_WIFI)
#define WIFI_DRIVER_TYPE        WIFI_DRIVER_BCM
#define WIFI_USB_HOST           0
#elif defined(MTK_7601_WIFI)
#define WIFI_DRIVER_TYPE        WIFI_DRIVER_MTK
#define WIFI_USB_HOST           1
#elif defined(RTK_8188ftv_WIFI)
#define WIFI_DRIVER_TYPE        WIFI_DRIVER_RTK
#define WIFI_USB_HOST           1
#elif defined(ATBM_6022_WIFI)
#define WIFI_DRIVER_TYPE        WIFI_DRIVER_ATBM
#define WIFI_USB_HOST           1
#else
#define WIFI_DRIVER_TYPE        WIFI_DRIVER_UNKNOW
#define WIFI_USB_HOST           0
#endif

#if(WIFI_USB_HOST == 1)
#define WIFI_RESET_GPIO         (0)//MMP_GPIO53
#define WIFI_EINT_GPIO          (0)//MMP_GPIO42
#define WIFI_ENABLE_GPIO        (0)//MMP_GPIO43
#else//WIFI_USB_HOST == 1
//SDIO WIFI
#define WIFI_RESET_GPIO         (0)//MMP_GPIO53
#define WIFI_EINT_GPIO          (0)//MMP_GPIO42
#define WIFI_ENABLE_GPIO        (0)//MMP_GPIO43
#endif//WIFI_USB_HOST == 1

// Enable special WIFI MFG mode: not for normal WLAN operation, but for EMI/MFG.
// The gb9662.a in Firmware/NET/wifi/, needs to be replaced with gb9662_MFG.a
// In MTK case,use mt7751_lib.a for MFG
//-------------------------------------------------
#if (WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK || WIFI_DRIVER_TYPE == WIFI_DRIVER_RTK)
//MFG mode and Normal mode FW are the same version.
#define NCFG_WIFI_MFG_EN            1
#else
#define NCFG_WIFI_MFG_EN            0
#endif

#define NCFG_SDIO_PAD               1
#define NCFG_WIFI_MAX_CONNECTION    4

typedef enum _NCFG_WLAN_PIN_FUNC{
    NCFG_WLAN_PIN_FUNC_ENABLE   = 0,
    NCFG_WLAN_PIN_FUNC_RESET,
    NCFG_WLAN_PIN_FUNC_EINT,
    NCFG_WLAN_PIN_FUNC_26M_CLK,
    NCFG_WLAN_PIN_FUNC_32K_CLK,
    NCFG_WLAN_PIN_FUNC_TOTAL
}NCFG_WLAN_PIN_FUNC;

#ifndef NCFG_WIFI_DEFAULT_PIN
#define NCFG_WIFI_DEFAULT_PIN \
{ WIFI_ENABLE_GPIO, WIFI_RESET_GPIO, WIFI_EINT_GPIO, 0, 0}
#endif

#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)

#define WLAN_ZERO_COPY
#define WIFI_MAC_ON_HOST        1

typedef enum _NCFG_WLAN_CAL_TYPE{
    NCFG_WLAN_CAL_TYPE_MAC = 0,
    NCFG_WLAN_CAL_TYPE_TX_POWER,
    NCFG_WLAN_CUSTOM_REG_DOMAIN,
    NCFG_WLAN_CAL_TYPE_TOTAL
}NCFG_WLAN_CAL_TYPE;

#define NCFG_WIFI_DEFAULT_TXPWR_2400M_EVB \
{ 0x13, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
  0x10, 0x10, 0x10, 0x10, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

//Below MAC address will be used in WIFI driver as a default MAC in COB(WIFI chip on baord) solution
//Set it all zero means we are under module solution,WIFI chip will apply MAC address from it's own flash.
#define NCFG_WIFI_DEFAULT_MAC_ADDERSS \
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

//Country code,currently support EN/CA/US/JP/CN ,default is JP(Japan),Only EN can pass EN300.328 1.9.1 adaptivity certification
#define NCFG_WIFI_DEFAULT_REG_DOMAIN (('J' << 8) | 'P')

#else//#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)

#define NCFG_WAKEUP_PIN         (WIFI_EINT_GPIO)
#define NCFG_RESET_PIN          (WIFI_RESET_GPIO)
#define WIFI_MAC_ON_HOST        0

#endif//#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)

#if(WIFI_MAC_ON_HOST)
#define SD_MAC_UPDATER_BURNIN   1
#define SD_MAC_POWERON_BURNIN   1
#define SD_MAC_REMOVE_SOURCE    1
#else
#define SD_MAC_UPDATER_BURNIN   0
#define SD_MAC_POWERON_BURNIN   0
#define SD_MAC_REMOVE_SOURCE    0
#endif

#define SD_MAC_FILENAME         "SD:\\HostBurnInMAC.bin"
#define SF_MAC_FILENAME         "SF:1:\\MAC.bin"


#endif // _NET_CFG_H_

