
#ifndef ATBM_WIFI_API_H
#define ATBM_WIFI_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "wlan_ATBM.h"

typedef int INT32;
typedef unsigned int UINT32;
typedef void* wl_drv_hdl;

typedef enum
{
    ATBM_WIFI_AP_MODE = 0,
    ATBM_WIFI_STA_MODE
}ATBM_WIFI_MODE;

typedef enum _SECURITY_TYPE
{
    KEY_NONE = 0,
    KEY_WEP,
    KEY_WEP_SHARE,
    KEY_WPA,
    KEY_WPA2,
    KEY_MIX,
    KEY_MAX,
}SECURITY_TYPE;

typedef struct _WLAN_CONNECTION_INFO ATBM_WLAN_CONNECTION_INFO;

/****************************************************************************
* Function:     atbm_wifi_hw_init
*
* Purpose:      This function is used to initialize and start atbm wifi  hardware.
            may be GPO, BUS PROBE, firmware init etc.
*
* Parameters: none
*
* Returns:  Returns driver handle, otherwise a NULL pointer.
****************************************************************************/
INT32  atbm_wifi_hw_init(void);



/****************************************************************************
* Function:     atbm_wifi_on
*
* Purpose:      This function is used to initialize and start atbm wifi  module as AP mode or STA mode.
*
* Parameters: AP_sta_mode     0: Ap Mode, 1 STA mode
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
****************************************************************************/
wl_drv_hdl atbm_wifi_on(ATBM_WIFI_MODE AP_sta_mode);



/****************************************************************************
* Function:     atbm_wifi_off
*
* Purpose:      This function is used to stop atbm wifi  module.
*
* Returns:  Returns none.
*****************************************************************************/
void  atbm_wifi_off();



/****************************************************************************
* Function:     atbm_wifi_scan_network
*
* Purpose:      This function is used to ask driver to perform channel scan and return scan result.
*
* Parameters: scan_buf      Buffer to store the information of the found APs
*           buf_size        Size of the buffer
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
******************************************************************************/
int atbm_wifi_scan_network(char* scan_buf, uint buf_size);



/****************************************************************************
* Function:     atbm_wifi_get_mode
*
* Purpose:      This function is used to get  wifi mode
*
* Parameters: None
*
* Returns:  Returns 0 if in STA mode, 1 in SW AP mode.
******************************************************************************/
INT32 atbm_wifi_get_current_mode(void);   //0 : sta, 1: SW AP



/****************************************************************************
* Function:     atbm_wifi_get_mac_address
*
* Purpose:      This function is used to get wifi MAC addressi
*
* Parameters: point to buffer of MAC address
*
* Returns:  None.
******************************************************************************/
void atbm_wifi_get_mac_address(unsigned char *addr);



/****************************************************************************
* Function:     atbm_wifi_tx_pkt
*
* Purpose:      This function is used to send packet to wifi driver
*
* Parameters: point to buffer of packet
*
* Returns:  None.
******************************************************************************/
void atbm_wifi_tx_pkt(void *p);


//void atbm_wifi_rx_pkt(netif, total_len);   //not required here ,   lwip_tcp_opt.net_rx = ethernetif_input.



/****************************************************************************
* Function:     atbm_wifi_get_avail_tx_queue_count
*
* Purpose:      This function is used to return the available buffer count of driver TX queue
*
* Parameters: None
*
* Returns:  Returns number of available buffer count of driver TX queue.
******************************************************************************/
INT32 atbm_wifi_get_avail_tx_queue_count(void);




/****************************************************************************
* Function:     atbm_wifi_sta_join_ap
*
* Purpose:      This function is used to ask driver to join a netwrok.
*
* Parameters: ssid          SSID of the AP used to join a network
*            authMode   authentication mode used to join a network
*            encryption encryption mode used to join a network
*            key            passphrase used to join a network
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
******************************************************************************/
INT32 atbm_wifi_sta_join_ap(char *ssid, char *bssid, WLM_AUTH_MODE authMode, WLM_ENCRYPTION encryption, const char *key);



/****************************************************************************
* Function:     atbm_wifi_get_driver_version
*
* Purpose:      This function is used to return the driver's release version
*
* Parameters: None
*
* Returns:  Returns the driver release version
*****************************************************************************
*/
signed char* atbm_wifi_get_driver_version(void);



/****************************************************************************
* Function:     wlan_get_connection_info
*
* Purpose:      This function is used to get the current connection information at STA mode
*
* Parameters: wlan connection information
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.

typedef struct _WLAN_CONNECTION_INFO
{
    uint8   Ssid_len;
    uint8   Ssid[32];
    int32   Rssi;
    int32   Phy_rate;
    int32   channel;
} WLAN_CONNECTION_INFO;
*****************************************************************************
*/

int atbm_wifi_get_connected_info(ATBM_WLAN_CONNECTION_INFO *wlan_connection_info );

/****************************************************************************
* Function:     wlan_get_connection_info
*
* Purpose:      This function is used to get the current connection information at STA mode
*
* Parameters: wlan connection information
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
****************************************************************************/














/*************************************************************************************

**************                SW AP functions                                                                        *********

**************************************************************************************/

/****************************************************************************
* Function:     atbm_wifi_ap_create
*
* Purpose:      This function is used to create a SW AP network
*
* Parameters: ssid          SSID of the SW AP to be created
*            authMode   Authentication mode used for the SW AP
*            encryption Encryption mode used for the SW AP
*            key            Passphrase used for the SW AP
*            channel        Channle used for the SW AP
*            ssidBcst       0: to broadcast SSID, 1: to hide SSID
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 atbm_wifi_ap_create(char* ssid, int authMode, int encryption,
                            const char *key, int channel, bool ssidBcst );



/****************************************************************************
* Function:     wlan_get_assoc_list
*
* Purpose:      This function is used to the associated client list in SW AP mode
*
* Parameters: buf           The buffer to store the associated client list
*                    uiBufSize       size of the buffer
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.

* For ioctls that take a list of MAC addresses *
typedef struct _WLAN_MACLIST
{
    uint32 count;              // number of MAC addresses
    WLAN_ETHER_ADDR ea[1];     // variable length array of MAC addresses
}WLAN_MACLIST;
******************************************************************************/
int atbm_wifi_get_associated_client_list(void *pchBuf, unsigned int uiBufSize);












/*************************************************************************************

**************                  Manufacturing test functions                                                     *********

**************************************************************************************/

void  atbm_wifi_mfg_start();


/**************************************************************************************
* Function:     atbm_wifi_mfg_set_pktTxBG
*
* Purpose:      This function is used to perform manufacturing 11b/g continuous TX test
*
* Parameters:   channel       Channel used for TX
*                     rate          11b/g rate used for TX
*                     powerValue    Output power index, -1 means default power
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
****************************************************************************************/
INT32 atbm_wifi_mfg_set_pktTxBG(WLAN_CHANNEL channel, WLAN_RATE rate, INT32 powerValue);


/***********************************************************************************
* Function:     atbm_wifi_mfg_set_PktTxN
*
* Purpose:      This function is used to perform manufacturing 11n continuous TX test
*
* Parameters:   channel       Channel used for TX
*                  rate          11n rate used for TX
*                     powerValue    Output power index, -1 means default power
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
************************************************************************************/
INT32 atbm_wifi_mfg_set_PktTxN(WLAN_CHANNEL channel, WLAN_RATE rate, INT32 powerValue);


/****************************************************************************
* Function:     atbm_wifi_mfg_CarrierTone
*
* Purpose:      This function is used to perform manufacturing non-modulation TX test
*
* Parameters:   channel       Channel used for test
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
******************************************************************************/
INT32 atbm_wifi_mfg_CarrierTone(WLAN_CHANNEL channel);


/****************************************************************************
* Function:     atbm_wifi_mfg_set_PktRxMode
*
* Purpose:      This function  is used to perform manufacturing RX test
*
* Parameters:   channel     Channel used for RX
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
******************************************************************************/
INT32 atbm_wifi_mfg_set_PktRxMode(WLAN_CHANNEL channel);


/****************************************************************************
* Function:     atbm_wifi_mfg_get_RxPkt
*
* Purpose:      This function is used to get received packet count
*
* Parameters:   uiCount     Received packet count
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
******************************************************************************/
INT32 atbm_wifi_mfg_get_RxPkt(UINT32* uiCount);



/****************************************************************************
* Function:     atbm_wifi_mfg_stop
*
* Purpose:      This function is used to stop manufacturing test
*
* Parameters:   None
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
******************************************************************************/
INT32 atbm_wifi_mfg_stop(void);

#ifdef __cplusplus
    }
#endif

#endif  /* ATBM_WIFI_H */

