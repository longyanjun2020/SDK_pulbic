#ifndef WLANCONFIG_H
#define WLANCONFIG_H

#define CONFIG_HARDWARE_8188F 1
#if !defined(CONFIG_PLATFORM_8195A)
//#define PLATFORM_UCOSII 	1
#define PLATFORM_RTK_OS 	1
//#define CONFIG_GSPI_HCI
//#define CONFIG_SDIO_HCI
#define CONFIG_USB_HCI
#else
#define CONFIG_LX_HCI
#endif
//#define CONFIG_PLATFORM_MSTAR_MSC8328D	1
#define CONFIG_PLATFORM_MSTAR_MSC8339	1
#define CONFIG_WLAN_DRV_IN_SRAM	1
#define CONFIG_WLAN_DRV_IN_ITCM	1
#define CONFIG_USING_MSTAR_TIMER_API	1
//#define CONFIG_SEMAPHORE_SHRINK	1

#define CONFIG_LITTLE_ENDIAN
#define CONFIG_80211N_HT 
#define CONFIG_RECV_REORDERING_CTRL
#define RTW_NOTCH_FILTER 0
#if !defined(CONFIG_PLATFORM_8195A)
#define CONFIG_EMBEDDED_FWIMG 1
#define CONFIG_PHY_SETTING_WITH_ODM
#define CONFIG_ODM_REFRESH_RAMASK
#define HAL_MAC_ENABLE 1
#define HAL_BB_ENABLE 1
#define HAL_RF_ENABLE 1
#endif
#if defined(CONFIG_PLATFORM_8195A)
/* Patch when dynamic mechanism is not ready */
#define CONFIG_DM_PATCH
#endif

#define CONFIG_DEBUG
//#define CONFIG_DEBUG_RTL871X
#if defined(CONFIG_PLATFORM_8195A)
#define CONFIG_MEM_MONITOR	MEM_MONITOR_SIMPLE
#define WLAN_INTF_DBG		0 
#define CONFIG_DEBUG_DYNAMIC
//#define DBG_TX 1
//#define DBG_XMIT_BUF 1
//#define DBG_XMIT_BUF_EXT 1
#define DBG_TX_DROP_FRAME	
#else
//#define CONFIG_MEM_MONITOR	MEM_MONITOR_SIMPLE
//#define CONFIG_TRACE_SKB
//#define WLAN_INTF_DBG
#endif

//#define CONFIG_POWER_SAVING
#if !defined(CONFIG_PLATFORM_8195A)
//#define CONFIG_IPS
//#define CONFIG_LPS
#if defined(CONFIG_LPS)
//#define CONFIG_LPS_LCLK
//#define CONFIG_WAIT_PS_ACK
#endif
#define CONFIG_SUSPEND
#if defined(CONFIG_SUSPEND)
#define CONFIG_WOWLAN
#define CONFIG_GPIO_WAKEUP
#endif
#endif

#if defined(CONFIG_PLATFORM_8195A)
//#define CONFIG_XMIT_THREAD_MODE
//1 Chris
#define CONFIG_RECV_TASKLET_THREAD
#define CONFIG_XMIT_TASKLET_THREAD
#else
#ifdef CONFIG_SDIO_HCI
#define CONFIG_XMIT_THREAD_MODE
#endif
#ifdef CONFIG_USB_HCI
#define CONFIG_RECV_THREAD_MODE				/* Wlan IRQ Polling  Mode*/
#endif
#endif
//#define CONFIG_RECV_THREAD_MODE				/* Wlan IRQ Polling  Mode*/


//#define CONFIG_ISR_THREAD_MODE_POLLING		/* Wlan IRQ Polling  Mode*/

//1 Chris
//#define CONFIG_ISR_THREAD_MODE_INTERRUPT	/* Wlan IRQ Interrupt  Mode*/

#if defined(CONFIG_ISR_THREAD_MODE_POLLING) && defined(CONFIG_ISR_THREAD_MODE_INTERRUPT)
#error "CONFIG_ISR_THREAD_MODE_POLLING and CONFIG_ISR_THREAD_MODE_INTERRUPT are mutually exclusive. "
#endif

#if defined(CONFIG_PLATFORM_8195A)
/* CRC DMEM optimized mode consume 1k less SRM memory consumption */
#define CRC_IMPLEMENTATION_MODE CRC_IMPLEMENTATION_DMEM_OPTIMIZED
#endif

/* AES DMEM optimized mode comsume 10k less memory compare to 
     IMEM optimized mode AES_IMPLEMENTATION_IMEM_OPTIMIZED */
#define AES_IMPLEMENTATION_MODE AES_IMPLEMENTATION_DMEM_OPTIMIZED

#define USE_SKB_AS_XMITBUF	1
#if defined(CONFIG_PLATFORM_8195A)
#define USE_XMIT_EXTBUFF	1
#else
#define USE_XMIT_EXTBUFF	0
#endif
#define USE_MUTEX_FOR_SPINLOCK	1
#define SUPPORT_5G_CHANNEL	0
#if defined(CONFIG_PLATFORM_8195A)
#define SUPPORT_FAKE_EFUSE	0
#endif
#if 0 
#ifdef CONFIG_USE_USB_BUFFER_ALLOC_RX
#else
	#define CONFIG_PREALLOC_RECV_SKB
	#ifdef CONFIG_PREALLOC_RECV_SKB
		/* #define CONFIG_FIX_NR_BULKIN_BUFFER */ /* only use PREALLOC_RECV_SKB buffer, don't alloc skb at runtime */
	#endif
#endif
#endif

//#define CONFIG_AUTO_RECONNECT 1//YAN_MASK
#ifdef CONFIG_GSPI_HCI
#define ENABLE_HWPDN_PIN
#endif
#define SUPPORT_SCAN_BUF	1
#if !defined(CONFIG_PLATFORM_8195A)
#define BE_I_CUT			1
#endif

/* For tune throughput */
#if !defined(CONFIG_PLATFORM_8195A)
//#define CONFIG_DONT_CARE_TP
#define CONFIG_MEMORY_ACCESS_ALIGNED
//#define CONFIG_USE_ISR_THRED_OUTSIDE
#define CONFIG_HIGH_TP
#endif

//#define CONFIG_BACKGROUND_NOISE_MONITOR
//#define CONFIG_AUTO_CHNL_SEL_NHM
//#define DBG_AUTO_CHNL_SEL_NHM
/* For WPA2 */
#define CONFIG_INCLUDE_WPA_PSK
#ifdef CONFIG_INCLUDE_WPA_PSK
#define CONFIG_MULTIPLE_WPA_STA
//#define CONFIG_WPA2_PREAUTH
#define PSK_SUPPORT_TKIP	1
#endif

/* For promiscuous mode */
//#define CONFIG_PROMISC

#define PROMISC_DENY_PAIRWISE	0

/* For Simple Link */
#define CONFIG_INCLUDE_SIMPLE_CONFIG 1

// for probe request with custom vendor specific IE
// #define CONFIG_CUSTOM_IE

#if !defined(CONFIG_PLATFORM_8195A)
/* For multicast */
#define CONFIG_MULTICAST

/* For STA+AP Concurrent MODE */
//#define CONFIG_CONCURRENT_MODE//YAN_MASK
#endif
#ifdef CONFIG_CONCURRENT_MODE
#define NET_IF_NUM 2
#else
#define NET_IF_NUM 1
#endif

#define CONFIG_RF_GAIN_OFFSET


/* For WPS and P2P */
//#define CONFIG_WPS
#if 0//def CONFIG_WPS
#define CONFIG_WPS_AP
#define CONFIG_P2P_NEW
#if (!defined(SUPPORT_SCAN_BUF)||!defined(CONFIG_WPS_AP)) && defined(CONFIG_P2P_NEW)
#error "If CONFIG_P2P_NEW, need to SUPPORT_SCAN_BUF"
#endif
#endif

#if !defined(CONFIG_PLATFORM_8195A)
#define CONFIG_NEW_SIGNAL_STAT_PROCESS
#endif

/* For Tx Power By Rate */
#ifndef CONFIG_TXPWR_BY_RATE_EN
#define CONFIG_TXPWR_BY_RATE_EN 2/*by efuse*/
#endif

#ifndef CONFIG_TXPWR_LIMIT_EN
/* For Tx Power Limit */
#define CONFIG_TXPWR_LIMIT_EN 0 /*by efuse*/
#endif

#if !defined(CONFIG_PLATFORM_8195A)
/* For Enable Adaptivity */
extern unsigned char g_rtw_adaptivity_en;
#define CONFIG_RTW_ADAPTIVITY_EN g_rtw_adaptivity_en
#endif
/* For AP_MODE */
#define CONFIG_AP_MODE
#if defined(CONFIG_PLATFORM_8195A)
#define AP_STA_NUM	3	//2014/10/27 modify to 3
#define USE_DEDICATED_BCN_TX	0
#if USE_DEDICATED_BCN_TX
#error "WLAN driver for Ameba should not enable USE_DEDICATED_BCN_TX"
#endif
#else
extern unsigned int g_ap_sta_num;
#define AP_STA_NUM g_ap_sta_num//YAN_MASK
#endif
#ifdef CONFIG_AP_MODE
	#define CONFIG_NATIVEAP_MLME
#if defined(CONFIG_PLATFORM_8195A)
	#define CONFIG_INTERRUPT_BASED_TXBCN
#endif
	#ifdef CONFIG_INTERRUPT_BASED_TXBCN
		//#define CONFIG_INTERRUPT_BASED_TXBCN_EARLY_INT
		#define CONFIG_INTERRUPT_BASED_TXBCN_BCN_OK_ERR
	#endif
//	#define CONFIG_GK_REKEY
#if !defined(CONFIG_PLATFORM_8195A)
	#define USE_DEDICATED_BCN_TX	1
#endif
#else
#if !defined(CONFIG_PLATFORM_8195A)
	#define USE_DEDICATED_BCN_TX	0
#endif
#endif

#if defined(CONFIG_AP_MODE) && defined(CONFIG_GK_REKEY) && !defined(CONFIG_MULTIPLE_WPA_STA)
#error "If CONFIG_GK_REKEY when CONFIG_AP_MODE, need to CONFIG_MULTIPLE_WPA_STA"
#endif

#if !defined(CONFIG_PLATFORM_8195A)
#if !defined(CONFIG_AP_MODE) && defined(CONFIG_CONCURRENT_MODE)
#error "If CONFIG_CONCURRENT_MODEE, need to CONFIG_AP_MODE"
#endif
#endif

#if defined(CONFIG_PLATFORM_8195A)
/* For Package type */
#define PACKAGE_TYPE_QFN56		1
//#define PACKAGE_TYPE_QFN88		1
//#define PACKAGE_TYPE_QFN216		1
//#define PACKAGE_TYPE_BGA96		1
#endif
/* For MP_MODE */
//#define CONFIG_MP_INCLUDED
#ifdef CONFIG_MP_INCLUDED
	#define MP_DRIVER		1
	#define CONFIG_MP_IWPRIV_SUPPORT
	#define HAL_EFUSE_MEMORY
#if defined(CONFIG_PLATFORM_8195A)
	#define MP_REG_TEST
	#define FIX_TX_AGC_POWER_INDEX 0
	#define RATE_ADAPTIVE_SUPPORT 0
	#define CONFIG_POWER_TRAINING_WIL 0
#endif
#else
	#define MP_DRIVER		0
#if defined(CONFIG_PLATFORM_8195A)
	#define FIX_TX_AGC_POWER_INDEX 1
	#define RATE_ADAPTIVE_SUPPORT 1
	#define CONFIG_POWER_TRAINING_WIL 0
	//Control wifi mcu function
	#define CONFIG_LITTLE_WIFI_MCU_FUNCTION_THREAD
	#define CONFIG_ODM_REFRESH_RAMASK
#endif
#endif // #ifdef CONFIG_MP_INCLUDED

#if defined(CONFIG_PLATFORM_8195A)
//#define CONFIG_RTL8188E 0
#define RTL8188ES_SUPPORT 0
#define RTL8188E_SUPPORT 0
#elif defined(CONFIG_HARDWARE_8188F)
#define CONFIG_RTL8188F
#define RTL8188F_SUPPORT 1
#else
#define CONFIG_RTL8188E
//#define RTL8188ES_SUPPORT 1
#define RTL8188E_SUPPORT 1
#endif
#define RTL8192C_SUPPORT 0
#define RTL8192CE_SUPPORT 0
#define RTL8192CU_SUPPORT 0
#define RTL8192D_SUPPORT 0
#define RTL8192DE_SUPPORT 0
#define RTL8192DU_SUPPORT 0
#define RTL8723A_SUPPORT 0
#define RTL8723AU_SUPPORT 0
#define RTL8723AS_SUPPORT 0
#define RTL8192E_SUPPORT 0
#define RTL8812A_SUPPORT 0
#define RTL8821A_SUPPORT 0
#define RTL8723B_SUPPORT 0
#if defined(CONFIG_PLATFORM_8195A)
#define RTL8195A_SUPPORT 1
#else
#define RTL8195A_SUPPORT 0
#endif
#define TEST_CHIP_SUPPORT 0

#define RTL8723_FPGA_VERIFICATION 0
#define RTL8188E_FOR_TEST_CHIP 0
#define RTL8188E_FPGA_TRUE_PHY_VERIFICATION 0
//#define DBG 0
#if !defined(CONFIG_PLATFORM_8195A)
//#define RATE_ADAPTIVE_SUPPORT 0
//#else
#define RATE_ADAPTIVE_SUPPORT 1
#define POWER_BY_RATE_SUPPORT 0
#endif

#if defined(CONFIG_PLATFORM_8195A)
#define CONFIG_RTL8195A 1
#define RTL8195A_FOR_TEST_CHIP 0

#if defined(CONFIG_RTL8188F)
#define RATE_ADAPTIVE_SUPPORT 0
#endif

//#define CONFIG_WIFI_TEST 1
//#define CONFIG_MAC_LOOPBACK_DRIVER 1
//#define CONFIG_WLAN_HAL_TEST 1
//#define SKB_PRE_ALLOCATE_TX	1
#define SKB_PRE_ALLOCATE_RX	1
#define TX_CHECK_DSEC_ALWAYS		1


//Control wifi mcu function
//#define CONFIG_LITTLE_WIFI_MCU_FUNCTION_THREAD 0

//Enable mac loopback for test mode (Ameba)
//#define ENABLE_MAC_LB_FOR_TEST_MODE // for test mode
#ifdef ENABLE_MAC_LB_FOR_TEST_MODE
#define CONFIG_SUDO_PHY_SETTING
#define INT_HANDLE_IN_ISR 1
#define CONFIG_LWIP_LAYER    0
#define CONFIG_WLAN_HAL_TEST
#define CONFIG_WLAN_HAL_RX_TASK
#define CONFIG_MAC_LOOPBACK_DRIVER_RTL8195A 1
//#define CONFIG_TWO_MAC_TEST_MODE 
#define DISABLE_BB_RF 1
#else
//#define CONFIG_TWO_MAC_DRIVER //for mornal driver; two mac
#ifndef CONFIG_TWO_MAC_DRIVER
#define HAL_MAC_ENABLE 1
#define HAL_BB_ENABLE 1
#define HAL_RF_ENABLE 1
#define DISABLE_BB_RF 0
#else
#define CONFIG_SUDO_PHY_SETTING
#define DISABLE_BB_RF 1
#endif

//#define INT_HANDLE_IN_ISR 1

#endif

#define CONFIG_DBG_DISABLE_RDU_INTERRUPT
//3 Chris
#define CONFIG_EMBEDDED_FWIMG   1
#define CONFIG_PHY_SETTING_WITH_ODM


//#define CONFIG_WLAN_HAL_RX_TASK

//#define CONFIG_MAC_LOOPBACK_DRIVER 
#endif
#define CONFIG_LWIP_LAYER    1
#define CONFIG_MAC_ADDRESS 0
/*read efuse or file*/
#define CONFIG_CHOOSE_READ_EFUSE 1
#if defined(CONFIG_RTL8188F) || defined(CONFIG_RTL8188E)
#define CONFIG_WRITE_MAC_TO_FLASH 0
#else
#define CONFIG_WRITE_MAC_TO_FLASH 1
/*For fast reconnection*/
#define CONFIG_EXAMPLE_WLAN_FAST_CONNECT 1
#endif
#endif //WLANCONFIG_H
