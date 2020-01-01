#ifndef __VEN_WLAN_H_
#define __VEN_WLAN_H_
/***************************************************************************/
/*  File : ven_wlan.h                                                        */
/*-------------------------------------------------------------------------*/
/*  Scope: This file defines the WLAN related vendor request API,    */
/*         and MMI response API.                                           */
/*                                                                         */
/***************************************************************************/

#include "ven_sdk.h"
#include "ven_socket.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/
typedef enum
{
    VEN_WLAN_RET_SUCCESS      = 0,					///< operation completed successfully
    VEN_WLAN_RET_BAD_PARAM    = 1,                  ///< invalid input parameters
    VEN_WLAN_RET_FAILED       = 2,                  ///< WHAT? every code here is failed
    VEN_WLAN_RET_OUT_OF_MEMORY    = 3,              ///< memory is not enough to complete the operation
} ven_wlan_ret_t;

typedef struct
{
    u32                         u32IP;
    u32                         u32Mask;
    u32                         u32Router;
    u32                         u32MasterDNS;
    u32                         u32SlaveDNS;
} ven_wlan_static_ip_t;

typedef struct
{
    u8                         u8IP0;
    u8                         u8IP1;
    u8                         u8IP2;
    u8                         u8IP3;
} ven_wlan_ip_t;

typedef struct
{
    ven_wlan_static_ip_t        tStaticIP;
    u8                          aSSID[32];
    u32                         nSSIDLen;
    u8                          aBSSID[6];
    u8                          aKey[64];
    u32                         nSecurity;
    u32                         nCaRaiId;
    u32                         nClientRaiId;
} ven_wlan_connected_device_info_t;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/
/**
 *  ven_wlan_get_cur_connected_device_info
 *
 *  @brief  This function will help to get the information of wlan device if connected.
 *
 *  @param  handle       [in] vendor handle
 *  @param  pbIsWlanConnted       [out] To check whether the wlan is connected
 *  @param  psConnectDeviceInfo       [out] To get the information of wlan device if connected
 *
 *  @retval VEN_WLAN_RET_SUCCESS if success
 *          VEN_WLAN_RET_FAILED if failed
 *          VEN_WLAN_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_wlan_ret_t ven_wlan_get_cur_connected_device_info(u32 handle, bool *pbIsWlanConnted , ven_wlan_connected_device_info_t *psConnectDeviceInfo);

/**
 *  ven_wlan_convert_ipvalue
 *
 *  @brief  This function will help to convert IP u32 value to 4 u8 value
 *
 *  @param  nIPValue       [in] IP value
 *  @param  pIp       [out] the pointer to  4 IP u8 value structure
 *
 *  @retval ven_wlan_ip_t  	If the IP is "123.255.77.88", u8IP0 = 123, u8IP1 = 255, u8IP2 = 77, u8IP3 = 88
 */
ven_wlan_ret_t ven_wlan_convert_ipvalue(u32 nIPValue, ven_wlan_ip_t *pIp);


ven_wlan_ret_t ven_wlan_set_network_profile_as_default(u32 handle, ven_socket_network_profile_ex_t *psProfile);


#endif
