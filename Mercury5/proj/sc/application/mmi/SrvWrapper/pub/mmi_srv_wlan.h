/**
* @file    mmi_srv_wlan.h
* @brief   The interface to provide the methods to manipulate the WLan module with the AP(access point) scanning and connecting actions. After the phone set connects to
*          a certain AP, the application can use TCP/IP to connect to internet via WiFi instead of GSM/GPRS networking. This service plays the role to construct the OSI lower layer
*          , not provide the TCP/IP protocol stack. Hence, scanning the surround APs and connecting to a selected AP are the primary function inside this service. Further, to get
*          the AP information and to filter (hide) the scanned AP are both the auxiliary functions.
*          
*
* @author  
* @version $Id:
*/

#ifndef __MMI_SRV_WLAN_H__
#define __MMI_SRV_WLAN_H__

/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_wlansrv.h"

/* callback function type */
/** SrvWLanPowerOnOffCnfCB
* @brief         The callback function to confirm the powering on/off request. (triggered by WLANSRV_EVT_PowerOnOffCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eErrCode           The error cause: WLANSRV_OK
*                                                    WLANSRV_FAIL
*                                                    WLANSRV_PARAM_ERROR
*                                                    WLANSRV_MEM_ALLOC_ERROR
*                                                    WLANSRV_REJECT
*                                                    WLANSRV_ABORT
*                                                    WLANSRV_TIMEOUT
*                                                    WLANSRV_FIFO_INIT_FAIL
*                                                    WLANSRV_NOT_READY
*                                                    WLANSRV_NULL_MAC
* @param[out]    ePowerStatus       The status to depict to be powered off(WLANSRV_POWER_STATUS_OFF) or on (WLANSRV_POWER_STATUS_ON).
*/
typedef void (*SrvWLanPowerOnOffCnfCB)(void *pThis,WLANSRV_ErrCode_e eErrCode,WLANSRV_PowerStatus_e ePowerStatus);
/** SrvWLanConnectCnfCB
* @brief         The callback function to confirm the connecting request. (triggered by WLANSRV_EVT_ConnectCnf or WLANSRV_EVT_DisconnectCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eErrCode           The error cause: ABL_WIFI_OK
*                                                    ABL_WIFI_FAIL
*                                                    ABL_WIFI_PARAM_ERROR
*                                                    ABL_WIFI_MEM_ALLOC_ERROR
*                                                    ABL_WIFI_REJECT
*                                                    ABL_WIFI_ABORT
*                                                    ABL_WIFI_TIMEOUT
*                                                    ABL_WIFI_FIFO_INIT_FAIL
*                                                    ABL_WIFI_NOT_READY
*                                                    ABL_WIFI_NULL_MAC
*/
typedef void (*SrvWLanConnectCnfCB)(void *pThis,ABL_WiFiErrCode_e eErrCode);
/** SrvWLanScanCnfCB
* @brief         The callback function to confirm the scanning request. (triggered by WLANSRV_EVT_StartScanCnf or WLANSRV_EVT_StopScanCnf)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eErrCode           The error cause: ABL_WIFI_OK
*                                                    ABL_WIFI_FAIL
*                                                    ABL_WIFI_PARAM_ERROR
*                                                    ABL_WIFI_MEM_ALLOC_ERROR
*                                                    ABL_WIFI_REJECT
*                                                    ABL_WIFI_ABORT
*                                                    ABL_WIFI_TIMEOUT
*                                                    ABL_WIFI_FIFO_INIT_FAIL
*                                                    ABL_WIFI_NOT_READY
*                                                    ABL_WIFI_NULL_MAC
*/
typedef void (*SrvWLanScanCnfCB)(void *pThis,ABL_WiFiErrCode_e eErrCode);
/** SrvWLanScanDoneIndCB
* @brief         The callback function to indicate the completion of scanning. (triggered by WLANSRV_EVT_ScanDoneInd)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    pScanResultData    The scanned result which pool is allocated by service so it's not necessary to release at applet.
* @param[out]    bIsAuto            The boolean value to depict whether this action is done automatically(TRUE) or by user-trigger(FALSE).
*/
typedef void (*SrvWLanScanDoneIndCB)(void *pThis,ABL_WiFiScanResultData_t *pScanResultData,boolean bIsAuto);
/** SrvWLanStatusUpdateIndCB
* @brief         The callback function to update the WLan manipulation status. (triggered by WLANSRV_EVT_StatusUpdateInd)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    eEvent             The updated event: ABL_WIFI_EVENT__CONNECT_FAIL
*                                                      ABL_WIFI_EVENT__CONNECTED
*                                                      ABL_WIFI_EVENT__DISCONNECTED
*                                                      ABL_WIFI_EVENT__ROAMING
*                                                      ABL_WIFI_EVENT__SCAN_DONE
*                                                      ABL_WIFI_EVENT__PASSWORD_FAIL
*                                                      ABL_WIFI_EVENT__FW_TEST_DONE
*                                                      ABL_WIFI_EVENT__ON
*                                                      ABL_WIFI_EVENT__OFF
*                                                      ABL_WIFI_EVENT__GETIP_OK (DHCP server can assign an IP)
*                                                      ABL_WIFI_EVENT__GETIP_FAIL (DHCP service is not available)
*                                                      ABL_WIFI_EVENT__AIRPLANE_ON
*/
typedef void (*SrvWLanStatusUpdateIndCB)(void *pThis,ABL_WiFi_Event_e eEvent);

/* APIs */
/** SrvWLanSetScanDoneCB
* @brief        Register/deregister a callback function which will be triggered when the AP scanning is completed.
*
* @param[in]    pfnCallBack              The callback function which will be called to notify the completion of scanning.
*
* @retval       MAE_RET_SUCCESS          If it succeeds.
* @retval       MAE_RET_BAD_PARAM        If there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_FAILED           If the registration or deregistration of the callback function fails.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED    If the notifier doesn't exist or the service is terminated.
*/
MAE_Ret SrvWLanSetScanDoneCB(SrvWLanScanDoneIndCB pfnCallBack);

/** SrvWLanSetStatusUpdateCB
* @brief        Register/deregister a callback function which will be triggered when the WLan manipulation status is changed.
*
* @param[in]    pfnCallBack              The callback function which will be called to notify the change of WLan manipulation status.
*
* @retval       MAE_RET_SUCCESS          If successful.
* @retval       MAE_RET_BAD_PARAM        If there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_FAILED           If the registration or deregistration of the callback function fails.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED    If the notifier doesn't exist or the service is terminated.
*/
MAE_Ret SrvWLanSetStatusUpdateCB(SrvWLanStatusUpdateIndCB pfnCallBack);

/** SrvWLanPowerOnOffReq
* @brief        Request to turn on/off WLan module.
* 
* @param[in]    eAction                      Turn WLan module off (WLANSRV_ACTION_POWER_OFF)/ turn WLan module on (WLANSRV_ACTION_POWER_ON)
* @param[in]    pfnCallBack                  The callback function which will be called to notify the success (WLANSRV_OK) or failure for turning WLan module on/off request.
*
* @retval       MAE_RET_SUCCESS              If successful.
* @retval       MAE_RET_BAD_PARAM            If the input action is invalid or there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_FAILED               If the registration or deregistration of the callback function fails.
* @retval       MAE_RET_OUT_OF_MEMORY        If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED        If the notifier doesn't exist or the service is terminated.
* @retval       MAE_RET_ILLEGAL_OPERATION    If the phone set is at airplane mode.
*/
MAE_Ret SrvWLanPowerOnOffReq(WLANSRV_PowerAction_e eAction,SrvWLanPowerOnOffCnfCB pfnCallBack);

/** SrvWLanGetPowerOnOffStatus
* @brief        Request to get the status of the WLan module (power on or off).
*
* @retval       WLANSRV_POWER_STATUS_OFF    The WLan module is turned off or WLan service is not available.
* @retval       WLANSRV_POWER_STATUS_ON     The WLan module is turned on.
*/
WLANSRV_PowerStatus_e SrvWLanGetPowerOnOffStatus(void);

/** SrvWLanGetAvailabilitySetting
* @brief        Request to get the setting of the WLan availability about automation.
*
* @retval       WLANSRV_SHOW_WLAN_OFF            Don't do any automation or WLan service is not available.
* @retval       WLANSRV_SHOW_WLAN_SCAN           Available to do AP scanning automatically if there's no connected AP. If there exists one connected AP, automation won't be taken.
* @retval       WLANSRV_SHOW_WLAN_SCANCONNECT    Available to do AP scanning then connect to a matched AP if there's no connected AP automatically. If there exists one connected AP, automation won't be taken.
* @retval       WLANSRV_SHOW_WLAN_FORCESCAN      Available to do AP scanning automatically no matter whether there's any connected AP.
*/
WLANSRV_ShowWLAN_e SrvWLanGetAvailabilitySetting(void);

/** SrvWLanGetScanNetworkSetting
* @brief        Request to get the time slot of automating to scan network.
*
* @retval       WLANSRV_SCAN_NETWORK_10SEC    Every 10 seconds to do scanning automatically or WLan service is not available.
* @retval       WLANSRV_SCAN_NETWORK_20SEC    Every 20 seconds to do scanning automatically.
* @retval       WLANSRV_SCAN_NETWORK_30SEC    Every 30 seconds to do scanning automatically.
* @retval       WLANSRV_SCAN_NETWORK_45SEC    Every 45 seconds to do scanning automatically.
* @retval       WLANSRV_SCAN_NETWORK_1MIN     Every 1 minute to do scanning automatically.
* @retval       WLANSRV_SCAN_NETWORK_2MIN     Every 2 minutes to do scanning automatically.
* @retval       WLANSRV_SCAN_NETWORK_5MIN     Every 5 minutes to do scanning automatically.
* @retval       WLANSRV_SCAN_NETWORK_10MIN    Every 10 minutes to do scanning automatically.
*/
WLANSRV_ScanNetwork_e SrvWLanGetScanNetworkSetting(void);

/** SrvWLanSetAvailability
* @brief        Request to set WLan availability about automation, WLANSRV_SHOW_WLAN_OFF, WLANSRV_SHOW_WLAN_SCAN, WLANSRV_SHOW_WLAN_SCANCONNECT or WLANSRV_SHOW_WLAN_FORCESCAN.
* 
* @param[in]    eSetting                 The setting of the WLan availability about automation.
*                                        WLANSRV_SHOW_WLAN_OFF            Don't do any automation.
*                                        WLANSRV_SHOW_WLAN_SCAN           Available to do AP scanning automatically if there's no connected AP. If there exists one connected AP, automation won't be taken.
*                                        WLANSRV_SHOW_WLAN_SCANCONNECT    Available to do AP scanning then connect to a matched AP if there's no connected AP automatically. If there exists one connected AP, automation won't be taken.
*                                        WLANSRV_SHOW_WLAN_FORCESCAN      Available to do AP scanning automatically no matter whether there's any connected AP.
*
* @retval       MAE_RET_SUCCESS          If successful.
* @retval       MAE_RET_BAD_PARAM        If the input setting is invalid or there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED    If the service is terminated.
*/
MAE_Ret SrvWLanSetAvailability(WLANSRV_ShowWLAN_e eSetting);

/** SrvWLanSetScanNetwork
* @brief        Request to scan network automatically by the input time slot with smart step or not.
*
* @param[in]    eSetting                 The time slot.
*                                        WLANSRV_SCAN_NETWORK_10SEC    Every 10 seconds to do scanning automatically.
*                                        WLANSRV_SCAN_NETWORK_20SEC    Every 20 seconds to do scanning automatically.
*                                        WLANSRV_SCAN_NETWORK_30SEC    Every 30 seconds to do scanning automatically.
*                                        WLANSRV_SCAN_NETWORK_45SEC    Every 45 seconds to do scanning automatically.
*                                        WLANSRV_SCAN_NETWORK_1MIN     Every 1 minute to do scanning automatically.
*                                        WLANSRV_SCAN_NETWORK_2MIN     Every 2 minutes to do scanning automatically.
*                                        WLANSRV_SCAN_NETWORK_5MIN     Every 5 minutes to do scanning automatically.
*                                        WLANSRV_SCAN_NETWORK_10MIN    Every 10 minutes to do scanning automatically.
* @param[in]    bSmartTimer              The boolean value to depict whether the time slot is increased smartly (TRUE) or not (FALSE).
*                                        This boolean value works only for at least 1 minute. When this boolean value is set TRUE,
*                                        the time slot will be 10 sec, 10 sec, 10 sec, 20 sec, 20 sec, 30 sec, 45 sec, to 1 min (2min/5min/10min).
*
* @retval       MAE_RET_SUCCESS          If successful.
* @retval       MAE_RET_BAD_PARAM        If the input setting is invalid or there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED    If the service is terminated.
*/
MAE_Ret SrvWLanSetScanNetwork(WLANSRV_ScanNetwork_e eSetting,boolean bSmartTimer);

/** SrvWLanScanReq
* @brief        Request to start or stop to scan WLan.
*
* @param[in]    eAction                  The action to start(WLANSRV_ACTION_START_SCAN) or stop(WLANSRV_ACTION_STOP_SCAN) to scan WLan.
* @param[in]    pfnCallBack              The callback function which will be called to notify the success (WLANSRV_OK) or failure for the request of starting/stopping to scan WLan.
* 
* @retval       MAE_RET_SUCCESS          If successful.
* @retval       MAE_RET_BAD_PARAM        If the input action is invalid or there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_FAILED           If the registration or deregistration of the callback function fails. Also, if the current state is not at WLan scanning.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED    If the notifier doesn't exist or the service is terminated.
*/
MAE_Ret SrvWLanScanReq(WLANSRV_ScanAction_e eAction,SrvWLanScanCnfCB pfnCallBack);

/** SrvWLanGetConnectAPInfo
* @brief        Request to get the information of the connected AP. It's not necessary to release the return pointer because it's pointed to one static space.
*
* @retval       NULL                         If there's no enough memory to do allocation or no connected AP. Also, if the service is terminated.
* @retval       WLANSRV_ConnectedAPInfo_t    The data pointer with SSID, the length of SSID, security mode, channel, signal level, speed and BSSID (MAC) etc.
*/
WLANSRV_ConnectedAPInfo_t *SrvWLanGetConnectAPInfo(void);

/** SrvWLanGetConnectStatus
* @brief        Request to get the status of connection.
*
* @retval       TRUE     If there's one connected AP
* @retval       FALSE    If there's no enough memory to do allocation or no connected AP. Also, if the service is terminated.
*/
boolean SrvWLanGetConnectStatus(void);

/** SrvWLanGetActiveMode
* @brief        Request to get WLan active mode.
* 
* @retval       WLANSRV_MODE_OFF             The WLan service is to depict the WLan module at power-off state.
* @retval       WLANSRV_MODE_INITIALIZING    The WLan service is initializing FIFO and setting MAC address.
* @retval       WLANSRV_MODE_ACTIVE          The WLan service is standby to accept connecting or scanning request.
* @retval       WLANSRV_MODE_SEARCHING       The WLan service is scanning APs.
* @retval       WLANSRV_MODE_CONNECTING      The WLan service is connecting to one specific AP.
* @retval       WLANSRV_MODE_CONNECTED       The WLan service completes the connection with one specific AP.
* @retval       WLANSRV_MODE_UNKNOWN         The unknown state.
*/
WLANSRV_Mode_e SrvWLanGetActiveMode(void);

/** SrvWLanCheckIfEverConnected
* @brief        Request to check whether the AP has ever been connected or not by the input AP device information.
*
* @param[in]    pConnectDeviceInfo          The AP device information. Use the MAC address of the AP to check whether it has ever been connected.
*
* @retval       WLANSRV_DEVICE_NOT_FOUND    Can't find the matched AP; that means the input AP is never connected.
* @retval       An index                    The index to the stored historical connected AP record.
*/
u8 SrvWLanCheckIfEverConnected(WLANSRV_DeviceInfo_t *pConnectDeviceInfo);

/** SrvWLanGetAPKey
* @brief        Request to get AP key (password) by the specific index pointing to the stored historical connected AP record.
*
* @param[in]    nIdx      The index to the stored historical connected AP record.
* 
* @retval       NULL      If the service is terminated or the index is out of range.
* @retval       AP key    If the index is valid and the corresponding key (password) of the specific AP can be retrieved.
*/
u8 *SrvWLanGetAPKey(u8 nIdx);

/** SrvWLanGetAPIPInfo
* @brief        Request to get the static IP information for the specific AP by the specific index pointing to the stored historical connected AP record.
*               The IP information contains IP address, mask, router address, DNS address.
*
* @param[in]    nIdx                     The index to the stored historical connected AP record.
* 
* @retval       NULL                     If the service is terminated or the index is out of range.
* @retval       static IP information    If the index is valid and the corresponding static IP information can be retrieved.
*/
WLANSRV_StaticIP_t *SrvWLanGetAPIPInfo(u8 nIdx);

/** SrvWLanConnectReq
* @brief        Request to connect or disconnect to the specific AP.
*
* @param[in]    eAction                    Request to connect(WLANSRV_ACTION_CONNECT) or disconnect(WLANSRV_ACTION_DISCONNECT) to the specific AP.
* @param[in]    pDeviceInfo                The device information of the specific AP.
* @param[in]    pIPInfo                    The static IP information. No static IP information is assigned if pIPInfo is NULL. Otherwise, assign the static IP information.
* @param[in]    pKey                       The AP key (password) for the specific AP.
* @param[in]    pfnCallBack                The callback function which will be called to notify the success (WLANSRV_OK) or failure for the request of connecting/disconnecting to the specific AP.
* 
* @retval       MAE_RET_SUCCESS            If successful.
* @retval       MAE_RET_BAD_PARAM          If the input action is invalid or there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_FAILED             If the registration or deregistration of the callback function fails. Also, if there exists an connected AP.
* @retval       MAE_RET_OUT_OF_MEMORY      If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED      If the WLan module is off or the service is terminated.
* @retval       MAE_RET_ASYNC_COMPLETED    For disconnect request, if there's no connecting AP (that mean a certain AP has been connected or no AP will be connected)
*/
MAE_Ret SrvWLanConnectReq(WLANSRV_ConnectAction_e eAction,WLANSRV_DeviceInfo_t *pDeviceInfo,WLANSRV_StaticIP_t *pIPInfo,u8 *pKey,SrvWLanConnectCnfCB pfnCallBack);

/** SrvWLanConnect
* @brief
*
* @retval
*/
MAE_Ret SrvWLanConnect(WLANSRV_ConnectProfile_t *pConnectProfile,SrvWLanConnectCnfCB pfnCallBack);

/** SrvWLanDisconnect
* @brief
*
* @retval
*/
MAE_Ret SrvWLanDisconnect(SrvWLanConnectCnfCB pfnCallBack);

/** SrvWLanStopConnectingReq
* @brief        Request to stop connecting to a certain AP.
*
* @param[in]    pfnCallBack                The callback function which will be called to notify the success (WLANSRV_OK) or failure for the request of stopping connecting to the specific AP.
* 
* @retval       MAE_RET_SUCCESS            If successful.
* @retval       MAE_RET_BAD_PARAM          If the input action is invalid or there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_FAILED             If the registration or deregistration of the callback function fails. Also, if there exists an connected AP.
* @retval       MAE_RET_OUT_OF_MEMORY      If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED      If the WLan module is off or the service is terminated.
* @retval       MAE_RET_ASYNC_COMPLETED    For disconnect request, if there's no connecting AP (that mean a certain AP has been connected or no AP will be connected)
*/
MAE_Ret SrvWLanStopConnectingReq(SrvWLanConnectCnfCB pfnCallBack);

/** SrvWLanSetFilterAP
* @brief        Request to filter AP with the input BSSID. The filtered APs with the matched BSSID won't be connected automatically.
*
* @param[in]    pFilterBSSID    6-byte MAC address of the AP.
*/
void SrvWLanSetFilterAP(u8 *pFilterBSSID);

/** SrvWLanCleanFilterAP
* @brief        Request to delete the record from the filtered AP set. The input BSSID will be removed from the filtered AP set if it exists inside the set.
*
* @param[in]    pFilterBSSID    6-byte MAC address of the AP.
*/
void SrvWLanCleanFilterAP(u8 *pFilterBSSID);

/** SrvWLanCheckIfEverFiltered
* @brief        Request to check whether the AP with the input BSSID has ever filtered or not.
*
* @param[in]    pFilterBSSID    6-byte MAC address of the AP.
* 
* @retval       TRUE            The AP with the input BSSID is filtered.
* @retval       FALSE           The AP with the input BSSID is not filtered. Also, if the service is not available or the input BSSID is null.
*/
boolean SrvWLanCheckIfEverFiltered(u8 *pFilterBSSID);

/** SrvWLanGetMACAddr
* @brief        Request to get the MAC address of the WLan module mounted on the phone set.
*
* @retval       NULL           If the service is not available.
* @retval       MAC address    6-byte MAC address of the WLan module. The space to return the MAC address is not necessary to release because it's kept inside the service space.
*/
u8 *SrvWLanGetMACAddr(void);

/** SrvWLanForcedConnectReq
* @brief        Request to force to disconnect a connected AP if there exists an connected AP then connect to the new assigned AP.
*
* @param[in]    pDeviceInfo              The device information of the specific new AP.
* @param[in]    pIPInfo                  The static IP information. No static IP information is assigned if pIPInfo is NULL. Otherwise, assign the static IP information.
* @param[in]    pKey                     The AP key (password) for the specific new AP.
* @param[in]    pfnCallBack              The callback function which will be called to notify the success (WLANSRV_OK) or failure for the request of connecting to the specific AP.
*
* @retval       MAE_RET_SUCCESS          If successful.
* @retval       MAE_RET_BAD_PARAM        If there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_FAILED           If the registration or deregistration of the callback function fails. Also, if there exists an connected AP.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED    If the WLan module is off or the service is terminated.
*/
MAE_Ret SrvWLanForcedConnectReq(WLANSRV_DeviceInfo_t *pDeviceInfo,WLANSRV_StaticIP_t *pIPInfo,u8 *pKey,SrvWLanConnectCnfCB pfnCallBack);

/** SrvWLanGetScanAPList
* @brief        Request to get the scanned AP list.
*
* @retval       NULL       If the service is not available.
* @retval       AP list    A set of scanned AP informations, included of SSID, channel, security, level speed, MAC address, etc.
*                          If there is no scanned AP, the element, num, at ABL_WiFiScanResultData_t will be 0.
*                          The return space is not necessary to be released because it's kept inside the WLan service.
*/
ABL_WiFiScanResultData_t *SrvWLanGetScanAPList(void);

/** SrvWLanIsNeglectAirplaneMode
* @brief        Request to check whether to neglect airplane mode. The setting to neglect airplane mode is only available at internal level, like EM.
*
* @retval       TRUE     The WLan service neglects airplane mode and still provides the service no matter whether the airplane mode is on or off.
* @retval       FALSE    The WLan service won't provide the service and the WLan module will be shut down if the airplane mode is on. Also, if the service is not available.
*/
boolean SrvWLanIsNeglectAirplaneMode(void);

/** SrvWLanAutoConnectReq
* @brief        Request to connect to a certain AP according to the automatic matching mechanism.
*               From the scanned AP set, the latest one existing at the ever-connected AP set will be selected to try to connect.
*
* @retval       MAE_RET_SUCCESS          If successful.
* @retval       MAE_RET_BAD_PARAM        If there exists the wrong parameter(s) inside the internal function.
* @retval       MAE_RET_FAILED           If there's no matched AP to do auto-connection.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED    If the WLan module is off or the service is terminated.
*/
MAE_Ret SrvWLanAutoConnectReq(void);

/** SrvWLanSetPowerSavingTimer
* @brief        Request to set the timer for power saving. The WLan module will shut down for power saving after the set time is expired.
*               The timer will be kicked off when the backlight is off and the phone set is not charged.
*
* @param[in]    u32Second                The time to power WLan module off. The unit of the timer is second.
*
* @retval       MAE_RET_SUCCESS          If successful.
* @retval       MAE_RET_FAILED           If the WLan service doesn't support power saving mechanism.
* @retval       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation.
* @retval       MAE_RET_NOT_SUPPORTED    If the WLan module is off or the service is terminated.
*/
MAE_Ret SrvWLanSetPowerSavingTimer(u32 u32Second);

/** SrvWLanGetPowerSavingTimer
* @brief        Request to get the timer for power saving. The unit of the timer is second.
*
* @retval       WLANSRV_POWERSAVING_OFF    0 second. If the WLan service doesn't support power saving mechanism. Also, If the WLan module is off or the service is terminated.
* @retval       n > 0                      n second to power WLan module off if the timer is kicked off.
*/
u32 SrvWLanGetPowerSavingTimer(void);

/** SrvWLanSetConnectedDevice
* @brief
*
* @retval
* @retval
*/
MAE_Ret SrvWLanSetConnectedDevice(u8 nIndex,WLANSRV_ConnectDeviceInfo_t *pDeviceInfo);

/** SrvWLanGetConnectedDevice
* @brief
*
* @retval
* @retval
*/
MAE_Ret SrvWLanGetConnectedDevice(u8 nIndex,WLANSRV_ConnectDeviceInfo_t *pDeviceInfo);

/** SrvWLanGetConnectedDeviceNumber
* @brief
*
* @retval
* @retval
*/
u8 SrvWLanGetConnectedDeviceNumber(void);

/** SrvWLanDeleteConnectedDevice
* @brief
*
* @retval
*/
MAE_Ret SrvWLanDeleteConnectedDevice(u8 *pBSSID);

/** SrvWLanIsAutoConnectOnOff
* @brief (Only support #ifdef __WLAN_AUTOCONNECT__)
*
* @retval
*/
MAE_Ret SrvWLanIsAutoConnectOnOff(boolean *pIsAutoConnectOnOff);

/** SrvWLanGetUsedCertNumber
* @brief
*
* @retval
*/
u8 SrvWLanGetUsedCertNumber(void);

/** SrvWLanGetMaxCertNumber
* @brief
*
* @retval
*/
u8 SrvWLanGetMaxCertNumber(void);

/** SrvWLanInsertCert
* @brief
*
* @retval
*/
MAE_Ret SrvWLanInsertCert(WLANSRV_CertFormatProfile_t *pCertFormatProfile);

/** SrvWLanDeleteCert
* @brief
*
* @retval
*/
MAE_Ret SrvWLanDeleteCert(u8 nIndex);

/** SrvWLanReplaceCert
* @brief
*
* @retval
*/
MAE_Ret SrvWLanReplaceCert(WLANSRV_CertFormatProfile_t *pCertFormatProfile);

/** SrvWLanGetCert
* @brief
*
* @retval
*/
MAE_Ret SrvWLanGetCert(u8 nIndex,WLANSRV_CertInfoProfile_t *pCertInfoProfile);

/** SrvWLanParseCertInfo
* @brief
*
* @retval
*/
MAE_Ret SrvWLanParseCertInfo(WLANSRV_CertFormatProfile_t *pCertFormatProfile,WLANSRV_CertInfoProfile_t *pCertInfoProfile);

/** SrvWLanParseCertType
* @brief
*
* @retval
*/
MAE_Ret SrvWLanParseCertType(u16 *pCertPath, WLANSRV_CertType_e *eCertType);

/** SrvWLanSetNetworkProfileAsDefault
* @brief
*
* @retval
*/
MAE_Ret SrvWLanSetNetworkProfileAsDefault(SrvSocketNetworkProfile_t *psNetworkProfile);

/*-----------------------------------------------------*/

#endif /* __MMI_SRV_WLAN_H__ */
