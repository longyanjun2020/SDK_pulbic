#include "wlan_ATBM.h"
#include "ahc_message.h"
#include "ahc_stream.h"
#include "netapp.h"

#include "atbm_wifi_driver_api.h"

static AHC_BOOL m_bWiFiStatus = AHC_FALSE;
static void* m_pScanBufPtr = NULL;
static UINT32 m_uiScanFileHandler = NULL;
static WLAN_TARGET_AP_INFO m_sTargetAPInfo;
UINT8 gEncrpType = 0;
int gbWifiConnect = 0;
void* g_scan_buf = NULL;
AHC_OS_SEMID g_scan_sem = 0xFF;
bool release_scan_sem = 0;

extern struct netif main_netdev;
extern MMPF_OS_SEMID g_assocsemi;
extern AHC_BOOL gbAhcDbgBrk;

/********** Functions below is for RTK compile success **********/

#define ETHER_ADDR_LEN      6

int wlmClosedSet(int val)
{
    return -1;
}

int wlu_main_args(int argc, char **argv)
{
    return -1;
}

int AP_StartWPS(wps_config_info_t *pwps_config_info, wlan_wps_event_callback cb)
{
    return -1;
}

const char* capmode2str(uint16 capability)
{
    capability &= (DOT11_CAP_ESS | DOT11_CAP_IBSS);

    if (capability == DOT11_CAP_ESS)
        return "Managed";
    else if (capability == DOT11_CAP_IBSS)
        return "Ad Hoc";
    else
        return "<unknown>";
}

char* wl_ether_etoa(const struct ether_addr_packed *n)
{
    static char etoa_buf[ETHER_ADDR_LEN * 3];
    char *c = etoa_buf;
    int i;

    for (i = 0; i < ETHER_ADDR_LEN; i++) {
        if (i)
            *c++ = ':';
        c += sprintf(c, "%02X", n->mac[i] & 0xff);
    }
    return etoa_buf;
}



/********** Functions below is Wlan API **********/

void WLAN_SYS_StatusCallback(wlan_event_msg_t* event)
{
    MMPF_OS_AcquireSem(g_assocsemi, 0);

    if (!gbAhcDbgBrk) {
        printc("WLAN CB : %d : ", event->event_type);
    }

    switch(event->event_type) {

        case WLAN_E_LINK:
            if(event->flags) {
                if(nhw_get_cur_wifi_mode() == NETAPP_WIFI_STATION_MODE
                    && gEncrpType != WLAN_ENCRYPT_TKIP
                    && gEncrpType != WLAN_ENCRYPT_AES) {
                    // Station Mode
                    printc("Station Mode CONNECTED \n");
                    gbWifiConnect++;
                    if (main_netdev.flags & NETIF_FLAG_LINK_UP)
                        nhw_set_status(NETAPP_NET_STATUS_READY);

                    //inform network task for starting up dhcp client if necessary
                    nhw_wifi_link_report(1);
                }
            }
            else {
                //link down
                printc("link down reason = %d\n", event->reason);
                nhw_wifi_link_report(0);
            }
            break;

        case WLAN_E_PSK_SUP:
            if(nhw_get_cur_wifi_mode() == NETAPP_WIFI_STATION_MODE
                && (gEncrpType == WLAN_ENCRYPT_TKIP
                || gEncrpType == WLAN_ENCRYPT_AES)) {
                // Station Mode
                printc("Station Mode CONNECTED \n");
                gbWifiConnect++;
                if (main_netdev.flags & NETIF_FLAG_LINK_UP)
                    nhw_set_status(NETAPP_NET_STATUS_READY);

                //inform network task for starting up dhcp client if necessary
                nhw_wifi_link_report(1);
            }
            break;

        case WLAN_E_ASSOC_IND:
            if(0 == nhw_add_connected_sta(event->addr.mac))
                gbWifiConnect++;
            AHC_SendAHLMessage(AHLM_WIRELESS_CONNECT, WIRELESS_CONNECT_SUCCESS, 0);
            printc(BG_GREEN("Client Connect SoftAP %d\n"), gbWifiConnect);


            if (gbWifiConnect == 1 &&
                ns_get_streaming_status() != NETAPP_STREAM_PLAY) {
                nhw_set_status(NETAPP_NET_STATUS_READY);
#ifdef  ALWAYS_STREAM_ON
                aitstreamer_run("MJPEG.0");
#endif
            }
            //nhw_wifi_link_report(1);
            break;

        case WLAN_E_DISASSOC_IND:
            if(NETAPP_STREAM_PLAY == ns_get_streaming_status()) {
                if(!nhw_cmp_streaming_mac((unsigned char *)event->addr.mac))
                    AHC_SendAHLMessage(AHLM_WIRELESS_CONNECT, WIRELESS_SET_STREAMING_MODE, AHC_STREAM_OFF);
            }

            nhw_remove_disconnected_sta(event->addr.mac);
            if (gbWifiConnect > 0)
                gbWifiConnect--;
            AHC_SendAHLMessage(AHLM_WIRELESS_CONNECT, WIRELESS_CONNECT_FAIL, 0);
            printc("DISCONNECTED %d\n", gbWifiConnect);


            if (gbWifiConnect == 0) {
                ncfg_allow_APP_access(0);
                nhw_set_status(NETAPP_NET_STATUS_IDLE);
#ifdef  ALWAYS_STREAM_ON
                aitstreamer_run("none");
#endif
            }
            //nhw_wifi_link_report(0);
            break;

        case WLAN_E_SCAN_COMPLETE:
            printc("Scan Done \n");
            if(release_scan_sem == 1)
            {
                //AHC_OS_ReleaseSem(g_scan_sem);
                release_scan_sem = 0;
            }
            break;

        case WLAN_E_TXFAIL:
            printc("TX FAILED \n");
            break;

        default:
            printc("NO Mapping \n");
            break;
    }

    printc("\n");
    MMPF_OS_ReleaseSem(g_assocsemi);
}

int8* WLAN_SYS_GetVersion(void)
{
    return (int8*)atbm_wifi_get_driver_version();
}

/****************************************************************************
* Function:     wlan_start
*
* Purpose:      This routine is used to initialize GB9619 module.
*
* Parameters: callback function to receive driver events.
*            tx_buf_cnt     count of buf in tx queue, default is 32 if 0 is set
*            rx_buf_cnt     count of buf in rx queue, default is 16 if 0 is set
*           scan_buf_size       scan buf size, default is 32KB if 0 is set
*
* Returns:  Returns driver handle, otherwise a NULL pointer.
*****************************************************************************
*/
nhw_drv_hdl WLAN_SYS_Start(void)
{
    int wifi_mode;
    nhw_drv_hdl hdl = NULL;

    atbm_wifi_hw_init(); // TBD

    printc("[Wifi] Enter WLAN_SYS_Start \n");

#if NCFG_WIFI_MFG_EN
    if(nhw_get_wifi_mfg())
    {
        atbm_wifi_on(ATBM_WIFI_STA_MODE);
        atbm_wifi_mfg_start();
    }
    else
#endif
    {
        wifi_mode = nhw_get_target_wifi_mode();
        if(wifi_mode == NETAPP_WIFI_AP_MODE)
        {
            printc("[Wifi] Start AP Mode!\n");
            atbm_wifi_on(ATBM_WIFI_AP_MODE);
        }
        else if(wifi_mode == NETAPP_WIFI_STATION_MODE)
        {
            printc("[Wifi] Start STA Mode!\n");
            atbm_wifi_on(ATBM_WIFI_STA_MODE);
        }

        hdl = atbm_wifi_vif_get();
        g_scan_sem = AHC_OS_CreateSem(0);
    }

    m_bWiFiStatus = AHC_TRUE;

    printc("[Wifi] Leave WLAN_SYS_Start \n");

    return hdl;
}

void WLAN_SYS_Stop(nhw_drv_hdl hdl)
{
    printc("[Wifi] Enter %s \n", __func__);

    atbm_wifi_off();
    AHC_OS_DeleteSem(g_scan_sem);
    m_bWiFiStatus = AHC_FALSE;
    gbWifiConnect = 0;

    printc("[Wifi] Leave %s \n", __func__);
}

bool WLAN_SYS_IsStart(void)
{
    return m_bWiFiStatus;
}

/****************************************************************************
* Function:     wlan_get_mode
*
* Purpose:      This routine is used to current mode of Wi-Fi
*
* Parameters: None
*
* Returns:  Returns 0 if in STA mode, 1 in SW AP mode and 2 when WPS is in progress.
*****************************************************************************
*/
INT32 WLAN_SYS_GetMode(void)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    return atbm_wifi_get_current_mode();
}

/****************************************************************************
* Function:     wlan_get_mac_addr
*
* Purpose:      This routine is used to get wifi MAC addressi
*
* Parameters: buffer to store MAC address
*
* Returns:  None.
*****************************************************************************
*/
void WLAN_SYS_GetMacAddr(uint8* addr)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return;

    atbm_wifi_get_mac_address((char *)addr);
    printc(FG_GREEN("MAC : %#x %#x %#x %#x %#x %#x\n"), addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
}

void WLAN_SYS_GetMacAddrStr(int8* addrStr)
{
    uint8 byMacAddr[6];
    uint32 i;
    uint8 byTempChar;

    if(m_bWiFiStatus == AHC_FALSE)
        return;

    WLAN_SYS_GetMacAddr(byMacAddr);

    for(i = 0; i < 6; i++) {

        byTempChar = (byMacAddr[i] & 0xF0) >> 4;

        if(byTempChar < 10) {
            byTempChar += '0';
        } else {
            byTempChar += ('A' - 10);
        }

        *addrStr = byTempChar;
        addrStr++;

        byTempChar = (byMacAddr[i] & 0xF);

        if(byTempChar < 10) {
            byTempChar += '0';
        } else {
            byTempChar += ('A' - 10);
        }

        *addrStr = byTempChar;
        addrStr++;
    }
}

#pragma arm section code = "WIFISpeedUp", rwdata = "WIFISpeedUp",  zidata = "WIFISpeedUp"

void WLAN_SYS_TxPkt(struct pbuf *p)
{
    if(m_bWiFiStatus == AHC_FALSE)
    {
        pbuf_free(p);
        return;
    }

    atbm_wifi_tx_pkt(p);
}

void WLAN_SYS_RxPkt(struct netif *netif, int total_len)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return;

    //atbm_wifi_rx_pkt(netif, total_len);   ??? directly call lwip rx_fun or set here???
}

INT32 WLAN_SYS_GetTXQueueAvailCount(void)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    return atbm_wifi_get_avail_tx_queue_count();
}

#pragma arm section code, rwdata, zidata

void WLAN_SYS_GetStatsInfo(WLAN_STATISTICS_INFO *stats, char *sdio_stat_buf, int sdio_stat_size)
{
    return;
}

void WLAN_SYS_InitHw(void)
{
    printc("[Wifi] Enter WLAN_SYS_InitHw \n");

    //sdio_set_internal_device_id(NCFG_SDIO_PAD);
    //rtw_sdio_bus_ops.bus_probe();

    //hw system initialization

    //atbm_wifi_hw_init();
    printc("[Wifi] Leave WLAN_SYS_InitHw \n");

    return;
}

void WLAN_SYS_ResetHw(void)
{
    return;
}

INT32 WLAN_STA_AllocateScanBuf(void)
{
    if(m_pScanBufPtr != NULL)
        return 0;

    m_pScanBufPtr = (void*)mem_malloc(WLAN_SCAN_BUF_SIZE);

    if(m_pScanBufPtr == NULL){
        printc("Alloc scan buffer fail\n");
        return -1;
    }

    return 0;
}

void WLAN_STA_FreeScanBuf(void)
{
    mem_free(m_pScanBufPtr);
}

int8* WLAN_STA_ScanBufAddr(void)
{
    return m_pScanBufPtr;
}

int8* WLAN_STA_ScanAPbyModule(uint32* uiCount)
{
    WLAN_SCAN_RESULT *list;

    if(m_pScanBufPtr == NULL)
        return NULL;

    if(m_bWiFiStatus == AHC_FALSE)
        return NULL;

    WLAN_STA_ScanAP(m_pScanBufPtr, WLAN_SCAN_BUF_SIZE);

    list = (WLAN_SCAN_RESULT*)m_pScanBufPtr;
    *uiCount = list->count;

    return (int8*)m_pScanBufPtr;
}

int8* WLAN_STA_GetScanResultByIndex(uint32 uiIndex, int8* pchBuf)
{
    WLAN_SCAN_RESULT *list;
    WLAN_BSS_INFO *bi;
    int i;

    if(m_bWiFiStatus == AHC_FALSE)
        return NULL;

    if((list->count > 0) && (uiIndex < list->count)) {

        bi = list->bss_info;

        for(i = 0; i < uiIndex; i++, bi = (WLAN_BSS_INFO*)((BYTE*)bi + bi->length)) {
        }

        return (int8*)bi;
    }else
        return NULL;
}

int32 WLAN_STA_ScanAP(int8* scan_buf, uint32 buf_size)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    g_scan_buf = (void *)scan_buf;
    memset(scan_buf, 0, buf_size);

    return atbm_wifi_scan_network((char*)scan_buf, buf_size);

    //release_scan_sem = 1;
    //if(AHC_OS_AcquireSem(g_scan_sem, MS_TO_TICK(SCAN_LONGEST_WAIT_TIME)) != OS_NO_ERR)
    //  return -1;

    return 0;
}

int32 WLAN_STA_PutScanInfo(int8* scan_buf, uint32 buf_size)
{
    uint32 uiWriteCount;

    if(AHC_FS_FileOpen(WLAN_SCAN_FILE_NAME, sizeof(WLAN_SCAN_FILE_NAME),
                        "wb", sizeof("wb"), &m_uiScanFileHandler) !=0) {
        m_uiScanFileHandler = NULL;
        return -1;
    }

    AHC_FS_FileWrite(m_uiScanFileHandler, (UINT8*)scan_buf, buf_size, &uiWriteCount);

    AHC_FS_FileClose(m_uiScanFileHandler);

    return 0;
}

INT32 WLAN_STA_OpenScanInfo(UINT32* puiFileHandler)
{
    if(AHC_FS_FileOpen(WLAN_SCAN_FILE_NAME, sizeof(WLAN_SCAN_FILE_NAME),
                        "rb", sizeof("rb"), &m_uiScanFileHandler) !=0) {
        m_uiScanFileHandler = NULL;
        return -1;
    }

    return 0;
}

void WLAN_STA_CloseScanInfo(void)
{
    AHC_FS_FileClose(m_uiScanFileHandler);

    m_uiScanFileHandler = NULL;
}

int32 WLAN_STA_ScanAPbySSID(int8* pchSSID, WLAN_BSS_INFO *psInfo)
{
    void* pScanMemPtr;
    uint32 uiScanBufLength = WLAN_SCAN_BUF_SIZE;
    WLAN_SCAN_RESULT *list;
    WLAN_BSS_INFO *bi;
    AHC_BOOL bFind = AHC_FALSE;
    uint32 i;

    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    pScanMemPtr = (void*)mem_malloc(uiScanBufLength);
    if(pScanMemPtr == NULL)
        printc("Alloc scan buffer fail\n");

    list = (WLAN_SCAN_RESULT*)pScanMemPtr;

    if(WLAN_STA_ScanAP(pScanMemPtr, uiScanBufLength) == -1)
        printc("WLAN_STA_ScanAP: failed\n");

    printc("SSID : %s, size : %d \n", pchSSID, sizeof(pchSSID));

    if (list->count > 0) {

        bi = list->bss_info;

        for (i = 0; i < list->count; i++, bi = (WLAN_BSS_INFO*)((BYTE*)bi + bi->length)) {
            if(sizeof(pchSSID) == bi->SSID_len) {
                if(!strncmp((char*)pchSSID, (char*)bi->SSID, sizeof(bi->SSID))) {

                    printc("SSID = %s\n", bi->SSID);
                    printc("SSID_len = %d\n", bi->SSID_len);
                    bFind = AHC_TRUE;
                    memcpy(psInfo, bi, sizeof(WLAN_BSS_INFO));

                    break;
                }
            }
        }
    }

    mem_free(pScanMemPtr);

    if(bFind == AHC_TRUE){
        return 0;
    }else{
        return -1;
    }
}

void WLAN_STA_ScanChannel(UINT32* puiChannelList)
{
    void* pScanMemPtr;
    UINT32 uiScanBufLength = WLAN_SCAN_BUF_SIZE;
    WLAN_SCAN_RESULT *list;
    WLAN_BSS_INFO *bi;
    UINT32 uiChannel, i;
    uiChannel = 0;

    if(m_bWiFiStatus == AHC_FALSE)
        return;

    pScanMemPtr = (void*)mem_malloc(uiScanBufLength);
    if(pScanMemPtr == NULL)
        printc("Alloc scan buffer fail\n");

    list = (WLAN_SCAN_RESULT*)pScanMemPtr;

    if(WLAN_STA_ScanAP(pScanMemPtr, uiScanBufLength) == -1)
        printc("WLAN_STA_ScanAP: failed\n");

    if (list->count > 0) {

        bi = list->bss_info;

        for (i = 0; i < list->count; i++, bi = (WLAN_BSS_INFO*)((BYTE*)bi + bi->length)) {
            uiChannel |= (1 << (WLAN_CHSPEC_CHANNEL(bi->chanspec)));
        }
    }

    mem_free(pScanMemPtr);

    *puiChannelList = uiChannel;
}

int32 WLAN_STA_SetTargetAP(int8 *ssid, WLAN_AUTH_MODE authMode, WLAN_ENCRYPTION encryption, const int8 *key)
{
    memset(m_sTargetAPInfo.ssid, 0, WLAN_NAME_LENGTH);

    strcpy((char *)m_sTargetAPInfo.ssid, (char *)ssid);

    m_sTargetAPInfo.authMode = authMode;
    m_sTargetAPInfo.encryption = encryption;

    memset(m_sTargetAPInfo.key, 0, WLAN_NAME_LENGTH);

    strcpy((char *)m_sTargetAPInfo.key, (char *)key);

    return 0;
}

INT32 WLAN_STA_ConnectTargetAP(void)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    return WLAN_STA_JoinAP(m_sTargetAPInfo.ssid,
                                m_sTargetAPInfo.authMode,
                                m_sTargetAPInfo.encryption,
                                m_sTargetAPInfo.key );
}

/****************************************************************************
* Function:     wlan_join_network
*
* Purpose:      This routine is used to ask driver to join a netwrok.
*
* Parameters: ssid          SSID of the AP used to join a network
*            authMode   authentication mode used to join a network
*            encryption encryption mode used to join a network
*            key            passphrase used to join a network
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int32 WLAN_STA_JoinAP(int8 *ssid, WLAN_AUTH_MODE authMode, WLAN_ENCRYPTION encryption, const int8 *key )
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    gEncrpType = encryption;
    return atbm_wifi_sta_join_ap(ssid,NULL, authMode, encryption, key);
}

/****************************************************************************
* Function:     wlan_get_connection_info
*
* Purpose:      This routine is used to get the current connection information at STA mode
*
* Parameters: wlan connection information
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_STA_GetConnectedINFO(WLAN_CONNECTION_INFO* info)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    return atbm_wifi_get_connected_info((WLAN_CONNECTION_INFO *)info);
}

/****************************************************************************
* Function:     wlan_create_sw_ap
*
* Purpose:      This routine is used to create a SW AP network
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
int32 WLAN_AP_Create(int8* ssid,
                     WLAN_AUTH_MODE authMode,
                     WLAN_ENCRYPTION encryption,
                     const int8 *key,
                     WLAN_CHANNEL channel,
                     bool bHideSSID)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    printc("WLAN_AP_Create++channel %d\n",channel);

    return atbm_wifi_ap_create(ssid, authMode, encryption, key, channel, bHideSSID);
}

/****************************************************************************
* Function:     wlan_get_assoc_list
*
* Purpose:      This routine is used to the associated client list in SW AP mode
*
* Parameters: buf           The buffer to store the associated client list
*            buf_size       size of the buffer
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int32 WLAN_AP_GetAssocList(int8* pchBuf, uint32 uiBufSize)
{
    WLAN_MACLIST *maclist = (WLAN_MACLIST*)pchBuf;

    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    memset(pchBuf, 0, uiBufSize);
    maclist->count = NCFG_WIFI_MAX_CONNECTION;
    return atbm_wifi_get_associated_client_list((void *)pchBuf, uiBufSize);
}

void WLAN_WPS_CallBack(WLAN_WPS_STATE event)
{
    return;
}

/****************************************************************************
* Function:     wlan_wps_start
*
* Purpose:      This routine is used to perform WPS
*
* Parameters: wps configuration
*           cb  wps event callback
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_WPS_Start(WLAN_WPS_CONFIG* wpsConfigInfo, void* pFunc)
{
    return 0;
}
/****************************************************************************
* Function:     wlan_stop_wps
*
* Purpose:      This routine is used to stop WPS
*
* Parameters: None
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
void WLAN_WPS_Stop(void)
{
    return;
}

/****************************************************************************
* Function:     wlan_wps_gen_pin
*
* Purpose:      This routine is used to generate WPS PIN
*
* Parameters: pin   generated PIN
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_WPS_GenPin(UINT32* uiPin)
{
    return 0;
}

bool WLAN_WPS_Enable(void)
{
    return 0;
}

/****************************************************************************
* Function:     wlan_wps_get_state
*
* Purpose:      This routine is used to get state of WPS process
*
* Parameters: None
*
* Returns:  State of WPS process
*****************************************************************************
*/
WLAN_WPS_STATE WLAN_WPS_GetState(void)
{
    return 0;
}

/****************************************************************************
* Function:     wlan_wps_get_status
*
* Purpose:      This routine is used to get status of WPS process
*
* Parameters: None
*
* Returns:  Status of WPS process
*****************************************************************************
*/
UINT32 WLAN_WPS_GetStatus(void)
{
    return 0;
}

/****************************************************************************
* Function:     wlan_wps_get_credentials
*
* Purpose:      This routine is used to get credentials after WPS succeed
*
* Parameters: Credentials of the AP
*
* Returns:  Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_WPS_GetCredential(WLAN_CONFIG_INFO *wlan_config_info)
{
    return 0;
}


/****************************************************************************
* Function:     rtk_wifi_iwpriv
*
* Purpose:      This routine is the entry of MP function
*
* Parameters:   szParam  pointer to command string after "iwpriv"
*
* Returns:      void
*****************************************************************************/

#ifndef WLAN0_NAME
     #define WLAN0_NAME "wlan0"
#endif
void rtk_wifi_iwpriv(char *szParam)
{
    EAT_WHITE(szParam);
    if(szParam)
    {
        wext_private_command(WLAN0_NAME, szParam, 1);
    }
    else
    {
        printc("\n\rUsage: iwpriv COMMAND PARAMETERS");
    }
}

void rtk_wifi_test(char *szParam)
{
    EAT_WHITE(szParam);

    if(szParam)
    {
        interactive_mode(szParam);
    }
    else
    {
        printc("\n\rUsage: rtktest COMMAND PARAMETERS");
    }
}

/**************************************************************************************
* Function:     WLAN_MFG_TxBG
*
* Purpose:      This routine is used to perform manufacturing 11b/g continuous TX test
*
* Parameters:   channel       Channel used for TX
*               rate          11b/g rate used for TX
*               powerValue    Output power index, -1 means default power
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
***************************************************************************************
*/
INT32 WLAN_MFG_TxBG(WLAN_CHANNEL channel, WLAN_RATE rate, INT32 powerValue)
{
    return atbm_wifi_mfg_set_pktTxBG(channel, rate, powerValue);
}


/***********************************************************************************
* Function:     WLAN_MFG_TxN
*
* Purpose:      This routine is used to perform manufacturing 11n continuous TX test
*
* Parameters:   channel       Channel used for TX
*               rate          11n rate used for TX
*               powerValue    Output power index, -1 means default power
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
***********************************************************************************
*/
INT32 WLAN_MFG_TxN(WLAN_CHANNEL channel, WLAN_RATE rate, INT32 powerValue)
{
    return atbm_wifi_mfg_set_PktTxN(channel, rate, powerValue);
}

/****************************************************************************
* Function:     WLAN_MFG_CarrierTone
*
* Purpose:      This routine is used to perform manufacturing non-modulation TX test
*
* Parameters:   channel       Channel used for test
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_CarrierTone(WLAN_CHANNEL channel)
{
    return atbm_wifi_mfg_CarrierTone(channel);
}

/****************************************************************************
* Function:     WLAN_MFG_RX
*
* Purpose:      This routine is used to perform manufacturing RX test
*
* Parameters:   channel       Channel used for RX
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_RX(WLAN_CHANNEL channel)
{
     return atbm_wifi_mfg_Set_PktRxMode(channel);
}

/****************************************************************************
* Function:     WLAN_MFG_RxGetPkt
*
* Purpose:      This routine is used to get received packet count
*
* Parameters:   count     Received packet count
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_RxGetPkt(UINT32* uiCount)
{
    return atbm_wifi_mfg_get_RxPkt(uiCount);
}

/****************************************************************************
* Function:     WLAN_MFG_Stop
*
* Purpose:      This routine is used to stop manufacturing test
*
* Parameters:   None
*
* Returns:      Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_Stop(void)
{
    return atbm_wifi_mfg_stop();
}

