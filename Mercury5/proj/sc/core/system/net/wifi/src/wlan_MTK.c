//==============================================================================
//
//  Description :
//  Author      :
//  Revision    :
//
//==============================================================================
#include "config_fw.h" //for chip define and possibly PIN config
#include "ahc_fs.h"
#include "ahc_general.h" //for GPIO
#include "ahc_msgqueue.h"
#include "ahc_message.h"
#include "ahc_stream.h"

/* lwIP and AMAPAK*/
//#include "gb9662if.h"
#include "wlan_MTK.h"
#include "mem.h"
#include "netapp.h"
#include "amn_config.h"
#include <string.h>

#include "wlanif.h" //for wlan_event_msg_t
#include "lwipif.h"
#include "osl_ext.h"
#ifndef LINUX
#include "lib_retina.h"//for printc
#endif


static void EM_wifi_pktRx_callback(wndrv_test_rx_status_struct* result);
/*----------------------------------------------------------------------------*/
/*                      VARIABLES                                             */
/*----------------------------------------------------------------------------*/
extern struct netif main_netdev;

static AHC_BOOL m_bWPSStart       = AHC_FALSE;
static AHC_BOOL m_bWiFiStatus     = AHC_FALSE;
static UINT32 m_uiScanFileHandler = NULL;
static void* m_pScanBufPtr = NULL;
static WLAN_TARGET_AP_INFO m_sTargetAPInfo;
static void (* pPktRxCallback) (wndrv_test_rx_status_struct* result) = EM_wifi_pktRx_callback;
static UINT8	gEncrpType = 0;
#define PRINT_MAC(a) a[0],a[1],a[2],a[3],a[4],a[5]

static const UINT32 gWiFiGChannelMapping[] =
{
   0,
   2412000,
   2417000,
   2422000,
   2427000,
   2432000,
   2437000,
   2442000,
   2447000,
   2452000,
   2457000,
   2462000,
   2467000,
   2472000,
   2484000
};

int gbWifiConnect = 0; 
osl_ext_sem_t sem_wps = OSL_CREATE_SEM_INT_ERR;
char in_wps_process = 0;
extern MMPF_OS_SEMID	g_assocsemi;
extern int nhw_wifi_link_report(int updown);
extern 	int wlan_set_parameter(PARAM_TYPE type, void* pValue);
//wlan_config_func_pin(function, pin);
//wlan_config_cal_data(calibrateType, data);
static void EM_wifi_pktRx_callback(wndrv_test_rx_status_struct* result);

static int WLAN_Get_Default_Txpower(WLAN_11MODE mode)
{
	uint8	aDefaultTxpower[] = NCFG_WIFI_DEFAULT_TXPWR_2400M_EVB;
	
	//B
	if(mode == WLAN_MODE_B)
		return aDefaultTxpower[0] & 0x3f ;
	//G
	else if(mode == WLAN_MODE_G)
		return aDefaultTxpower[14] & 0x3f ;
	//N
	else
		return aDefaultTxpower[16] & 0x3f ;
}

void WLAN_SYS_StatusCallback(wlan_event_msg_t* event)
{

	MMPF_OS_AcquireSem(g_assocsemi,0);
	
    printc("WLAN CB : %d : ", event->event_type);

    switch(event->event_type){

	case WLAN_E_SET_SSID://0
		// Station Mode
/*		if( nhw_get_cur_wifi_mode() == NETAPP_WIFI_STATION_MODE &&
				gEncrpType != WLAN_ENCRYPT_WEP &&
				gEncrpType != WLAN_ENCRYPT_TKIP &&
				gEncrpType != WLAN_ENCRYPT_AES )*/
				{
				// Station Mode
	    		printc("Station Mode CONNECTED \n");
	    		gbWifiConnect++;
	    		if (main_netdev.flags & NETIF_FLAG_LINK_UP)
	    			nhw_set_status(NETAPP_NET_STATUS_READY);
	    		
	    		//inform network task for starting up dhcp client if necessary
	    		nhw_wifi_link_report(1);
		}
	    break;
	    
	case WLAN_E_DISASSOC_IND://12
	
		if(ns_get_streaming_status() & NETAPP_STREAM_PLAY)
		{
			if(!nhw_cmp_streaming_mac((unsigned char *)event->addr.mac))
				AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_SET_STREAMING_MODE, AHC_STREAM_OFF );
		}
		
		nhw_remove_disconnected_sta(event->addr.mac);
    	if (gbWifiConnect > 0) {
    		gbWifiConnect--;
    	}
    	AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_CONNECT_FAIL, 0 );
    	printc("DISCONNECTED %d\n", gbWifiConnect);
    	if (gbWifiConnect == 0) {
    		ncfg_allow_APP_access(0);
	    	nhw_set_status(NETAPP_NET_STATUS_IDLE);
#ifdef	ALWAYS_STREAM_ON
			aitstreamer_run("none");
#endif
		}		
		nhw_wifi_link_report(0);
    	break;

    case WLAN_E_ASSOC_IND://8
    	// AP Mode
	    if( 0 == nhw_add_connected_sta(event->addr.mac))
	    	gbWifiConnect++;
	    AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_CONNECT_SUCCESS, 0 );
	    printc(BG_GREEN("Client Connect SoftAP %d\n"), gbWifiConnect);

		// TODO: 
	    if (gbWifiConnect == 1) {
	    	nhw_set_status(NETAPP_NET_STATUS_READY);
#ifdef	ALWAYS_STREAM_ON
			aitstreamer_run("MJPEG.0");
#endif
	    }
		nhw_wifi_link_report(1);
	    break;
	    
    case WLAN_E_SCAN_COMPLETE://26
	    printc("Scan Done \n");	    
	    break;
	
	case WLAN_E_TXFAIL:
		// TODO:
		printc("!!! TX FAILED !!!\r\n");
		break;
    default:
    	printc("NO Mapping");
	    break;
	}
	
	printc("\n");
	MMPF_OS_ReleaseSem(g_assocsemi);

}

void WLAN_SYS_SET_PARAMETER(PARAM_TYPE type, void* pValue)
{
	
	switch(type)
	{
		case PARAM_TYPE_MAX_CLIENT_NUMBER:
			printc("set max client number(%d) into driver\n", *(unsigned char*)pValue);
			break;
		default:
			printc("un-supported parameter type\n");
			break;
	}
	wlan_set_parameter(type, pValue);
}	

int8* WLAN_SYS_GetVersion(void)
{

    return (int8*)wlan_get_version();
}

/****************************************************************************
* Function:   	wlan_start
*
* Purpose:   	This routine is used to initialize GB9619 module.
*
* Parameters: callback function to receive driver events.
*			 tx_buf_cnt		count of buf in tx queue, default is 32 if 0 is set
*			 rx_buf_cnt		count of buf in rx queue, default is 16 if 0 is set
*			scan_buf_size		scan buf size, default is 32KB if 0 is set
*
* Returns:	Returns driver handle, otherwise a NULL pointer.
*****************************************************************************
*/

WLAN_DRV_HDL WLAN_SYS_Start(void)
{	
	
    wl_drv_hdl h;
    int i = 0;
    uint8 aWifigpio[] = NCFG_WIFI_DEFAULT_PIN;
    uint8 aMac[] = NCFG_WIFI_DEFAULT_MAC_ADDERSS;
    uint8 aTxpower[] = NCFG_WIFI_DEFAULT_TXPWR_2400M_EVB;
    uint8 maxconn = NCFG_WIFI_MAX_CONNECTION;
	uint32 regDomain = NCFG_WIFI_DEFAULT_REG_DOMAIN;
    
    printc("==WLAN_SYS_Start==\n");

	if(sem_wps >= OSL_CREATE_SEM_EXCEED_MAX)
	{
		osl_ext_sem_create("MTK_WPS",1,&sem_wps);

		if(sem_wps >= OSL_CREATE_SEM_EXCEED_MAX){
			 printc("!!!!!sem_wps == NULL!!!!!!!\n");
			return 0;
		}
	}
	
	//set all gpio
	for( ; i < NCFG_WLAN_PIN_FUNC_TOTAL ; i++){
		if(aWifigpio[i])
			wlan_config_func_pin(i,aWifigpio[i]);
	}
	//set default mac
	wlan_config_cal_data(NCFG_WLAN_CAL_TYPE_MAC,aMac);
	//set default TX power
	wlan_config_cal_data(NCFG_WLAN_CAL_TYPE_TX_POWER,aTxpower);
	//set default region domain
	wlan_config_cal_data(NCFG_WLAN_CUSTOM_REG_DOMAIN,&regDomain);
	//max connection
	WLAN_SYS_SET_PARAMETER(PARAM_TYPE_MAX_CLIENT_NUMBER,&maxconn );

	h = wlan_start((wlan_drv_event_callback)WLAN_SYS_StatusCallback, (uint)(main_netdev.hwaddr),0,0);

#if NCFG_WIFI_MFG_EN
	if(nhw_get_wifi_mfg())
		RFTool_WiFi_EnterTestMode();
#endif

    m_bWiFiStatus = AHC_TRUE;
    return h;
}

void WLAN_SYS_Stop(WLAN_DRV_HDL hdl)
{	
	printc("==WLAN_SYS_Stop==\n");
    wlan_stop(hdl);
    m_bWiFiStatus = AHC_FALSE;
    gbWifiConnect = 0;
}

bool WLAN_SYS_IsStart(void)
{
	return m_bWiFiStatus;
}

/****************************************************************************
* Function:   	wlan_get_mode
*
* Purpose:   	This routine is used to current mode of Wi-Fi
*
* Parameters: None
*
* Returns:	Returns 0 if in STA mode, 1 in SW AP mode and 2 when WPS is in progress.
*****************************************************************************
*/
INT32 WLAN_SYS_GetMode(void)
{
	INT32 ret = 0;
	 
    if(m_bWiFiStatus == AHC_TRUE)
    {
    	ret = wlan_get_mode();
    	return ret;
    }
    else
        return -1;
}

/****************************************************************************
* Function:   	wlan_get_mac_addr
*
* Purpose:   	This routine is used to get wifi MAC addressi
*
* Parameters: buffer to store MAC address
*
* Returns:	None.
*****************************************************************************
*/
void WLAN_SYS_GetMacAddr(uint8* addr)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return;
    wlan_get_mac_addr(addr);
}

void WLAN_SYS_GetMacAddrStr(int8* addrStr)
{
    
    uint8 byMacAddr[6];
    uint32 i;
    uint8 byTempChar;
    
    if(m_bWiFiStatus == AHC_FALSE)
        return;
    
    wlan_get_mac_addr(byMacAddr);
    
    for(i = 0; i < 6; i++){
        
        byTempChar = (byMacAddr[i] & 0xF0) >> 4;
        
        if(byTempChar < 10){
        
            byTempChar += '0';
        }else{
            byTempChar += ('A' - 10);
        }
        
        *addrStr = byTempChar;
        addrStr++;
        
        byTempChar = (byMacAddr[i] & 0xF);
        
        if(byTempChar < 10){
        
            byTempChar += '0';
        }else{
            byTempChar += ('A' - 10);
        }
        
        *addrStr = byTempChar;
        addrStr++;
    
    }
}

void WLAN_SYS_TxPkt(struct pbuf *p)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return;
    wlan_tx_pkt(p);
}

#pragma arm section code = "WIFISpeedUp", rwdata = "WIFISpeedUp",  zidata = "WIFISpeedUp"
void wlan_sys_rx_pkt(struct pbuf *p)
{
	host_network_process_ethernet_data(p, &main_netdev);
}

INT32 WLAN_SYS_GetTXQueueAvailCount(void)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;
    else
        return kalGetTxAvaliableFrameCount();//return 5;
}
#pragma arm section code, rwdata,  zidata

void WLAN_SYS_GetStatsInfo(WLAN_STATISTICS_INFO *stats, char *sdio_stat_buf, int sdio_stat_size)
{
	return;
}

void WLAN_SYS_InitHw(void)
{
	return;
}

void WLAN_SYS_ResetHw(void)
{
	return;
}



INT32 WLAN_STA_AllocateScanBuf(void)
{
    //void* pScanMemPtr;
    
    if(m_pScanBufPtr != NULL)
        return 0;
    
    m_pScanBufPtr = mem_malloc(WLAN_SCAN_BUF_SIZE);

    if(m_pScanBufPtr == NULL){
        printc("alloc scan buffer fail\n");
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
        
    wlan_scan_network(m_pScanBufPtr, WLAN_SCAN_BUF_SIZE);
    
    list = (WLAN_SCAN_RESULT*)m_pScanBufPtr;
    *uiCount = list->count;
    
    return (int8*)m_pScanBufPtr;
}
/*
start from 0.
*/
int8* WLAN_STA_GetScanResultByIndex(uint32 uiIndex, int8* pchBuf)
{
	WLAN_SCAN_RESULT *list;
	WLAN_BSS_INFO *bi;
	int i = 0;

    if(m_bWiFiStatus == AHC_FALSE)
        return NULL;
	if( (list->count > 0) && (uiIndex < list->count) ){
	  
        bi = list->bss_info;
        
        //printc("St Addr : %x \n", bi );
	    
	    for (i = 0; i < uiIndex; i++, bi = (WLAN_BSS_INFO*)((BYTE*)bi + bi->length)){
	        //printc("i : %d , bi : %x \n", i, bi);
	    }
	    
        #if 0
	    printc("Final Addr : %x \n", bi );
	    
	    printc("*********************** \n");
	    
		printc("SSID = %s\n", bi->SSID);
		printc("SSID_len = %d\n", bi->SSID_len);
		/* BSSID */
		printc("BSSID: %02x:%02x:%02x:%02x:%02x:%02x, ",
				bi->BSSID[0], bi->BSSID[1], bi->BSSID[2], bi->BSSID[3], bi->BSSID[4], bi->BSSID[5]);

		/* CHANNEL */
		printc("bi->chanspec = %d\n", bi->chanspec);
		printc("Ch: %d, ", WLAN_CHSPEC_CHANNEL(bi->chanspec));
		
		/* RSSI */
		printc("RSSI: %ddBm, ", (INT16)(bi->RSSI));
		
		/* Mode */			
		printc("%s, ", capmode2str(bi->capability));

		/* Security */	
		printc("Security: %s\n", (bi->capability & WLAN_DOT11_CAP_PRIVACY)? "Encrypted":"Open");			
        #endif
	    return (int8*)bi;
	}else{
	    return NULL;
	}
}


/**
scan_buf must be 32 bit alignment.
*/
int32 WLAN_STA_ScanAP(int8* scan_buf, uint32 buf_size)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;
    else
    {
    	osl_ext_sem_take (&sem_wps, 0);
		if(in_wps_process)
		{
			printc("wps in process, skip scan\n");
			memset(scan_buf, 0, buf_size);
			osl_ext_sem_give(&sem_wps);
			return 0;
		}
		osl_ext_sem_give(&sem_wps);
        return wlan_scan_network((char*)scan_buf, buf_size);
    }
}

int32 WLAN_STA_PutScanInfo(int8* scan_buf, uint32 buf_size)
{
   // uint32 uiWriteCount;
    
    
    return 0;
}

INT32 WLAN_STA_OpenScanInfo(UINT32* puiFileHandler)
{
    
    return 0;
}

void WLAN_STA_CloseScanInfo(void)
{
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
	printc("wlan_MTK.c %s\n", __func__);

	if(m_bWiFiStatus == AHC_FALSE)
		return -1;

	pScanMemPtr = mem_malloc(uiScanBufLength);

	if(pScanMemPtr == NULL){
		printc("alloc scan buffer fail\n");
	}
	
	list = (WLAN_SCAN_RESULT*)pScanMemPtr;
		
	if(WLAN_STA_ScanAP(pScanMemPtr, uiScanBufLength) == -1)
		printc("wlan_scan_netwrok: failed\n");
	
	printc("SSID : %s, size : %d \n", pchSSID, sizeof(pchSSID));
	
	if (list->count > 0) {

		bi = list->bss_info;

		for (i = 0; i < list->count; i++, bi = (WLAN_BSS_INFO*)((BYTE*)bi + bi->length)) {
			if(sizeof(pchSSID) == bi->SSID_len){
				if(!strncmp((char*)pchSSID, (char*)bi->SSID, sizeof(bi->SSID))){
				
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
		//printc("SUCCESS\n");
		return 0;
	}else{
		//printc("FAILED\n");
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
	printc("wlan_MTK.c %s\n", __func__);

	if(m_bWiFiStatus == AHC_FALSE)
	   return;
	   
	pScanMemPtr = mem_malloc(uiScanBufLength);

	if(pScanMemPtr == NULL){
	   printc("alloc scan buffer fail\n");
	}

	list = (WLAN_SCAN_RESULT*)pScanMemPtr;

	if(WLAN_STA_ScanAP(pScanMemPtr, uiScanBufLength) == -1)
	   printc("wlan_scan_netwrok: failed\n");

	if (list->count > 0) {

	   bi = list->bss_info;

	   for (i = 0; i < list->count; i++, bi = (WLAN_BSS_INFO*)((BYTE*)bi + bi->length)) {
		   //printc("Channle : %d \n", WLAN_CHSPEC_CHANNEL(bi->chanspec));
		   uiChannel |= (1 << (WLAN_CHSPEC_CHANNEL(bi->chanspec)));
	   }
	}

	mem_free(pScanMemPtr);

	*puiChannelList = uiChannel;
}



int32 WLAN_STA_SetTargetAP(int8 *ssid, WLAN_AUTH_MODE authMode, WLAN_ENCRYPTION encryption, const int8 *key)
{	
	printc("wlan_MTK.c %s\n", __func__);
	memset(m_sTargetAPInfo.ssid, 0, WLAN_NAME_LENGTH);
    
    strcpy((char*)m_sTargetAPInfo.ssid, (char*)ssid);
    
    m_sTargetAPInfo.authMode = authMode;
    m_sTargetAPInfo.encryption = encryption;
    
    memset(m_sTargetAPInfo.key, 0, WLAN_NAME_LENGTH);
    
    strcpy((char*)m_sTargetAPInfo.key, (char*)key);
    
    return 0;
}

INT32 WLAN_STA_ConnectTargetAP(void)
{

	if(m_bWiFiStatus == AHC_FALSE)
        return -1;
    else
        return wlan_join_network((char*)m_sTargetAPInfo.ssid,  
                                 m_sTargetAPInfo.authMode, 
                                 m_sTargetAPInfo.encryption, 
                                 (char*)m_sTargetAPInfo.key );
}
/****************************************************************************
* Function:   	wlan_join_network
*
* Purpose:   	This routine is used to ask driver to join a netwrok.
*
* Parameters: ssid			SSID of the AP used to join a network
*			 authMode	authentication mode used to join a network
*			 encryption	encryption mode used to join a network
*			 key			passphrase used to join a network
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int32 WLAN_STA_JoinAP(int8 *ssid, WLAN_AUTH_MODE authMode, WLAN_ENCRYPTION encryption, const int8 *key )
{	

	if(m_bWiFiStatus == AHC_FALSE)
        return -1;
    
    
    gEncrpType = encryption;
    return wlan_join_network((char*)ssid, authMode, encryption, (char*)key);
}

/****************************************************************************
* Function:   	wlan_get_connection_info
*
* Purpose:   	This routine is used to get the current connection information at STA mode
*
* Parameters: wlan connection information
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
/*
support multi-task.
*/
INT32 WLAN_STA_GetConnectedINFO(WLAN_CONNECTION_INFO* info)
{


	if(m_bWiFiStatus == AHC_FALSE)
		return -1;
	else
		return wlan_get_connection_info((wl_connection_info_t*)info);
}

/****************************************************************************
* Function:   	wlan_create_sw_ap
*
* Purpose:   	This routine is used to create a SW AP network
*
* Parameters: ssid			SSID of the SW AP to be created
*			 authMode	Authentication mode used for the SW AP
*			 encryption	Encryption mode used for the SW AP
*			 key			Passphrase used for the SW AP
*			 channel		Channle used for the SW AP
*			 ssidBcst		0: to broadcast SSID, 1: to hide SSID
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
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

    if(bHideSSID == AHC_TRUE){
        printc("Hide SSID \n");
    	return wlan_create_sw_ap((char*)ssid, authMode, encryption, (char*)key, channel, 1);
	}else{
        printc("broadcast SSID \n");
	    return wlan_create_sw_ap((char*)ssid, authMode, encryption, (char*)key, channel, 0);
	}        
}

/****************************************************************************
* Function:   	wlan_get_assoc_list
*
* Purpose:   	This routine is used to the associated client list in SW AP mode
*
* Parameters: buf			The buffer to store the associated client list
*			 buf_size		size of the buffer
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int32 WLAN_AP_GetAssocList(int8* pchBuf, uint32 uiBufSize)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;
    return wlan_get_assoc_list((char*)pchBuf, uiBufSize);    
}

void WLAN_WPS_CallBack(WLAN_WPS_STATE event)
{
    printc("WPS CB : %d : ", event);

#if WIFI_SEAL == 0
#endif

    switch(event){
    
    case WLAN_WPS_STATE_OFF:
        printc("OFF");
    break;
    case WLAN_WPS_STATE_INIT:
        printc("INIT");
    break;
	
	case WLAN_WPS_STATE_START:
        printc("START");
    break;
	
	case WLAN_WPS_STATE_CONN_FAIL:
        printc("CONN FAIL");
    break;
    
	case WLAN_WPS_STATE_FAIL:
        printc("FAIL");
    break;
    
	case WLAN_WPS_STATE_LINK_UP:
        printc("LINK UP");
    break;
	
	case WLAN_WPS_STATE_WAIT_START:
        printc("WAIT START");
    break;
	
	case WLAN_WPS_STATE_WAIT_M2:
        printc("WAIT M2");
    break;
	
	case WLAN_WPS_STATE_RX_M2D:
        printc("RX M2D");
    break;
    
	case WLAN_WPS_STATE_WAIT_M4:

        printc("WAIT M4");
    break;
	
	case WLAN_WPS_STATE_WAIT_M6:

        printc("WAIT M6");
    break;
	
	case WLAN_WPS_STATE_WAIT_M8:
        printc("WAIT M8");
    break;
	
	case WLAN_WPS_STATE_WAIT_EAPFAIL:

        printc("WAIT EAP FAIL");
    break;
	
	case WLAN_WPS_STATE_WAIT_DISCONN:

        printc("WAIT DISCONN");
    break;
	
	case WLAN_WPS_STATE_CONFIGURED:
        printc("CONFIGURED");
    break;
    
    }
    
    printc(": status : %d \n", WLAN_WPS_GetStatus());

}

/****************************************************************************
* Function:   	wlan_wps_start
*
* Purpose:   	This routine is used to perform WPS
*
* Parameters: wps configuration
*			cb	wps event callback
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/

INT32 WLAN_WPS_Start(WLAN_WPS_CONFIG* wpsConfigInfo, void* pFunc)
{
	INT32 error;
    wps_config_info_t wps_config;  

    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    osl_ext_sem_take(&sem_wps, 0);
	in_wps_process = 1;
	osl_ext_sem_give(&sem_wps);

    wps_config.WscMode      = wpsConfigInfo->WscMode;
    
    memcpy(wps_config.PIN, wpsConfigInfo->PIN, 8);
    memcpy(wps_config.Bssid, wpsConfigInfo->Bssid, 6);
    
    wps_config.JoinAP       = wpsConfigInfo->JoinAP;
    wps_config.ScanBufSize  = wpsConfigInfo->ScanBufSize;
    wps_config.AssocAPTime  = wpsConfigInfo->AssocAPTime;
	
	
	error = wlan_wps_start(wps_config, (wlan_wps_event_callback)pFunc);

	osl_ext_sem_take(&sem_wps, 0);
	in_wps_process = 0;
	osl_ext_sem_give(&sem_wps);
	
	m_bWPSStart = AHC_TRUE;
    
    return error;
}
/****************************************************************************
* Function:   	wlan_stop_wps
*
* Purpose:   	This routine is used to stop WPS
*
* Parameters: None
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
void WLAN_WPS_Stop(void)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return;
	m_bWPSStart = AHC_FALSE;
	wlan_wps_stop();    
}

/****************************************************************************
* Function:   	wlan_wps_gen_pin
*
* Purpose:   	This routine is used to generate WPS PIN
*
* Parameters: pin	generated PIN
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_WPS_GenPin(UINT32* uiPin)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;
	
    return wlan_wps_gen_pin(uiPin);   
}

bool WLAN_WPS_Enable(void)
{
    return m_bWPSStart;

}

/****************************************************************************
* Function:   	wlan_wps_get_state
*
* Purpose:   	This routine is used to get state of WPS process
*
* Parameters: None
*
* Returns:	State of WPS process
*****************************************************************************
*/

WLAN_WPS_STATE WLAN_WPS_GetState(void)
{
    WPS_STATE state;

    
    if(m_bWiFiStatus == AHC_FALSE)
        return WLAN_WPS_STATE_OFF;
    
    state = wlan_wps_get_state();
    
    if(state == WPS_STATE_OFF || state == WPS_STATE_CONFIGURED)
        m_bWPSStart = AHC_FALSE;

    return state;
}

/****************************************************************************
* Function:   	wlan_wps_get_status
*
* Purpose:   	This routine is used to get status of WPS process
*
* Parameters: None
*
* Returns:	Status of WPS process
*****************************************************************************
*/

UINT32 WLAN_WPS_GetStatus(void)
{

    if(m_bWiFiStatus == AHC_FALSE)
        return -1;
    return -1;
}

/****************************************************************************
* Function:   	wlan_wps_get_credentials
*
* Purpose:   	This routine is used to get credentials after WPS succeed
*
* Parameters: Credentials of the AP
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/

INT32 WLAN_WPS_GetCredential(WLAN_CONFIG_INFO *wlan_config_info)
{

    if(m_bWiFiStatus == AHC_FALSE)
        return -1;
        
    return wlan_wps_get_credentials((wl_config_info_t*)wlan_config_info);
}

#if 0
void __MFG__(){}
#endif
/*
1. 11b TX test
	wlan_mfg_tx_bg(ch, WLM_RATE_11M, txpwr)
	- ch: channel number
	- txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)
	
2. 11g TX test
	wlan_mfg_tx_bg(ch, WLM_RATE_54M, txpwr)
	- ch: channel number
	- txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)
	
3. 11n TX test
	wlan_mfg_tx_n(ch, WLM_MCS_RATE_7, txpwr)
	- ch: channel number
	txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)
	
4. RX test
	wlan_mfg_rx(ch)
	- ch: channel number
	
5. Get received packets
	wlan_mfg_rx_getpkt(&count)
	- count: received packet count
	
6. Non-modulation TX test
	wlan_mfg_carrier_tone(ch)
	- ch; channel number

7. Stop MFG test
	wlan_mfg_stop()

*/
/****************************************************************************
* Function:   	WLAN_MFG_TxBG
*
* Purpose:   	This routine is used to perform manufacturing 11b/g continuous TX test
*
* Parameters: channel		Channel used for TX
*			 rate			11b/g rate used for TX
*			 powerValue	Output power in units of half dBm, -1 means default power
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_TxBG(WLAN_CHANNEL channel, WLAN_RATE rate, INT32 powerValue)
{
	kal_uint8 country_code[2];
	
	wndrv_test_pkt_tx_struct contx_tx;
	int i;
	
	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);

	country_code[0] = 'U';
	country_code[1] = 'S';
	
	contx_tx.ch_freq = gWiFiGChannelMapping[channel];
	contx_tx.tx_rate = rate;//WNDRV_TEST_RATE_1M;
	contx_tx.txAnt = 0;
	contx_tx.txBw = WNDRV_TEST_BW_20MHZ;
	contx_tx.txGI = WNDRV_TEST_TX_GI_800NS;
	contx_tx.txMode = WNDRV_TEST_TX_GREEN_FIELD;
	contx_tx.pktCount = 0xffffffff;
	contx_tx.pktInterval = 100;
	contx_tx.pktLength = 1024;
	contx_tx.pattern = WNDRV_TX_ALL_ZEROS;	// WNDRV_TX_PSEUDO_RANDOM
	contx_tx.is_short_preamble = 0;
	
	if(-1 == powerValue){
		if( rate <= WNDRV_TEST_RATE_11M)
		{
			//b mode
			contx_tx.tx_gain_dac = WLAN_Get_Default_Txpower(WLAN_MODE_B) * 2;
		}
		else
		{
			//g mode
			contx_tx.tx_gain_dac = WLAN_Get_Default_Txpower(WLAN_MODE_G) * 2;
		}
	}
	else
		contx_tx.tx_gain_dac = powerValue;
		
	for (i=0 ; i<24; i++)
		contx_tx.mac_header[i] = 0;			// ?

	RFTool_WiFi_PktTx(country_code, contx_tx);

	return 0;
}

/****************************************************************************
* Function:   	WLAN_MFG_TxN
*
* Purpose:   	This routine is used to perform manufacturing 11n continuous TX test
*
* Parameters: channel		Channel used for TX
*			 rate			11n rate used for TX
*			 powerValue	Output power in units of half dBm, -1 means default power
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/

INT32 WLAN_MFG_TxN(WLAN_CHANNEL channel, WLAN_MCS_RATE rate, INT32 powerValue)
{
	kal_uint8 country_code[2];
	wndrv_test_pkt_tx_struct contx_tx;
	int i;
	
	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);
	country_code[0] = 'U';
	country_code[1] = 'S';
	
	contx_tx.ch_freq = gWiFiGChannelMapping[channel];
	contx_tx.tx_rate = rate;//WNDRV_TEST_RATE_1M;
	contx_tx.txAnt = 0;
	contx_tx.txBw = WNDRV_TEST_BW_20MHZ;
	contx_tx.txGI = WNDRV_TEST_TX_GI_800NS;
	contx_tx.txMode = WNDRV_TEST_TX_GREEN_FIELD;
	contx_tx.pktCount = 0xffffffff;
	contx_tx.pktInterval = 100;
	contx_tx.pktLength = 1024;
	contx_tx.pattern = WNDRV_TX_ALL_ZEROS;	// WNDRV_TX_PSEUDO_RANDOM
	contx_tx.is_short_preamble = 0;
	
	if(-1 == powerValue)
		contx_tx.tx_gain_dac = WLAN_Get_Default_Txpower(WLAN_MODE_N) * 2;
	else
		contx_tx.tx_gain_dac = powerValue;
		
	for (i=0 ; i<24; i++)
		contx_tx.mac_header[i] = 0;			// ?

	RFTool_WiFi_PktTx(country_code, contx_tx);

	return 0;
}

/****************************************************************************
* Function:   	WLAN_MFG_ContinousTx
*
* Purpose:   	This routine is used to perform manufacturing continuous TX test
*
* Parameters: channel		Channel used for TX
*			 rate			11 b/g/n rate used for TX
*			 powerValue	Output power in units of half dBm, -1 means default power
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int32 WLAN_MFG_ContinousTx(WLAN_CHANNEL channel, uint32 rate, int32 powerValue)
{
	kal_uint8 country_code[2];
	wndrv_test_tx_struct contx_tx;

	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);

	country_code[0] = 'U';
	country_code[1] = 'S';
	contx_tx.ch_freq = gWiFiGChannelMapping[channel];
	contx_tx.tx_rate = rate;
	contx_tx.txAnt = 0;
	contx_tx.txBw = WNDRV_TEST_BW_20MHZ;
	contx_tx.txGI = WNDRV_TEST_TX_GI_800NS;
	contx_tx.txMode = WNDRV_TEST_TX_GREEN_FIELD;

	if(-1 == powerValue)
		contx_tx.tx_gain_dac = WLAN_Get_Default_Txpower(WLAN_MODE_N) * 2;
	else
		contx_tx.tx_gain_dac = powerValue;
		
	RFTool_WiFi_ContTx(country_code, contx_tx);
	return 0;
}

/****************************************************************************
* Function:   	WLAN_MFG_RegisterRxCallback
*
* Purpose:   	This routine is used to register manufacturing RX call back function
*
* Parameters: 	pointer to the call back function that will be executed every second.
*
* Returns:		Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_RegisterRxCallback(void (*pCallback)(wndrv_test_rx_status_struct *))
{
	pPktRxCallback = pCallback;
	return 0;
}

/****************************************************************************
* Function:   	WLAN_MFG_RX
*
* Purpose:   	This routine is used to perform manufacturing RX test
*
* Parameters: channel		Channel used for RX
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_RX(WLAN_CHANNEL channel)
{
	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);
	RFTool_WiFi_PktRx(gWiFiGChannelMapping[channel],pPktRxCallback);
	return -1;
}

/****************************************************************************
* Function:   	WLAN_MFG_RxGetPkt
*
* Purpose:   	This routine is used to get received packet count
*
* Parameters: count		Received packet count
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_RxGetPkt(UINT32* uiCount)
{
	//Doesn't need,MTK solution use callback function to print recived packets.
	return -1;
}

/****************************************************************************
* Function:   	WLAN_MFG_CarrierTone
*
* Purpose:   	This routine is used to perform manufacturing non-modulation TX test
*
* Parameters: channel		Channel used for test
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_CarrierTone(WLAN_CHANNEL channel)
{
	kal_uint8 country_code[2];
	wndrv_test_tx_struct local_freq;
	
	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);

	country_code[0] = 'U';
	country_code[1] = 'S';
	local_freq.ch_freq = gWiFiGChannelMapping[channel];
	local_freq.tx_rate = WNDRV_TEST_RATE_1M;
	local_freq.txAnt = 0;
	local_freq.tx_gain_dac = WLAN_Get_Default_Txpower(WLAN_MODE_N) * 2;
#if 1
	local_freq.txBw = WNDRV_TEST_BW_20MHZ;
	local_freq.txGI = WNDRV_TEST_TX_GI_800NS;
	local_freq.txMode = WNDRV_TEST_TX_GREEN_FIELD;
#endif
	RFTool_WiFi_LocalFreq(country_code, local_freq);
	return 0;
}

/****************************************************************************
* Function:   	wlan_mfg_stop
*
* Purpose:   	This routine is used to stop manufacturing test
*
* Parameters: None
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_Stop(void)
{
	RFTool_WiFi_Stop();
	return 0;
}


int AP_StartWPS(wps_config_info_t *pwps_config_info, wlan_wps_event_callback cb)
{
	return -1;
}

const char *
capmode2str(uint16 capability)
{
	capability &= (DOT11_CAP_ESS | DOT11_CAP_IBSS);

	if (capability == DOT11_CAP_ESS)
		return "Managed";
	else if (capability == DOT11_CAP_IBSS)
		return "Ad Hoc";
	else
		return "<unknown>";
}


#define	ETHER_ADDR_LEN		6

char *
wl_ether_etoa(const struct ether_addr_packed *n)
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


int
wlu_main_args(int argc, char **argv)
{
	return -1;
}

int wlmClosedSet(int val)
{
	return -1;
}

extern unsigned int wndrv_dbglevel;
extern unsigned int HostapdDebugLevel;

#define DEMO_WIFI_EM_TEST

#ifdef DEMO_WIFI_EM_TEST
void Demo_EM_wifi_enter(void)
{
	RFTool_WiFi_EnterTestMode();
}

void Demo_EM_wifi_contTX(void)
{
	kal_uint8 country_code[2];
	wndrv_test_tx_struct contx_tx;

	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);

	country_code[0] = 'U';
	country_code[1] = 'S';
	contx_tx.ch_freq = 2412000;
	contx_tx.tx_rate = WNDRV_TEST_RATE_1M;
	contx_tx.txAnt = 0;
	contx_tx.tx_gain_dac = 0;
	contx_tx.txBw = WNDRV_TEST_BW_20MHZ;
	contx_tx.txGI = WNDRV_TEST_TX_GI_800NS;
	contx_tx.txMode = WNDRV_TEST_TX_GREEN_FIELD;

	RFTool_WiFi_ContTx(country_code, contx_tx);
}

void Demo_EM_wifi_carrierSupp(void)
{
	kal_uint8 country_code[2];
	wndrv_test_tx_struct carrier_supp;

	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);
	
	country_code[0] = 'U';
	country_code[1] = 'S';
	carrier_supp.ch_freq = 2412000;
	carrier_supp.tx_rate = WNDRV_TEST_RATE_1M;
	carrier_supp.txAnt = 0;
	carrier_supp.tx_gain_dac = 0;
#if 1	
	carrier_supp.txBw = WNDRV_TEST_BW_20MHZ;
	carrier_supp.txGI = WNDRV_TEST_TX_GI_800NS;
	carrier_supp.txMode = WNDRV_TEST_TX_GREEN_FIELD;
#endif
	RFTool_WiFi_CarrierSupp(country_code, carrier_supp);
}

void Demo_EM_wifi_localFreq(void)
{
	kal_uint8 country_code[2];
	wndrv_test_tx_struct local_freq;

	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);

	country_code[0] = 'U';
	country_code[1] = 'S';
	local_freq.ch_freq = 2412000;
	local_freq.tx_rate = WNDRV_TEST_RATE_1M;
	local_freq.txAnt = 0;
	local_freq.tx_gain_dac = 0;
#if 1
	local_freq.txBw = WNDRV_TEST_BW_20MHZ;
	local_freq.txGI = WNDRV_TEST_TX_GI_800NS;
	local_freq.txMode = WNDRV_TEST_TX_GREEN_FIELD;
#endif
	RFTool_WiFi_LocalFreq(country_code, local_freq);
}

void Demo_EM_wifi_pktTx(void)
{
	kal_uint8 country_code[2];
	wndrv_test_pkt_tx_struct cont_tx;
	kal_uint8 i;
	
	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);
	
	country_code[0] = 'U';
	country_code[1] = 'S';
	cont_tx.ch_freq = 2412000;
	cont_tx.tx_rate = WNDRV_TEST_RATE_1M;//WNDRV_TEST_MOD_MCS7;
	cont_tx.txAnt = 0;
	cont_tx.tx_gain_dac = 0;
	cont_tx.txBw = WNDRV_TEST_BW_20MHZ;
	cont_tx.txGI = WNDRV_TEST_TX_GI_800NS;
	cont_tx.txMode = WNDRV_TEST_TX_GREEN_FIELD;
	cont_tx.pktCount = 0;
	cont_tx.pktInterval = 100;
	cont_tx.pktLength = 1024;
	cont_tx.pattern = WNDRV_TX_ALL_ZEROS;	// WNDRV_TX_PSEUDO_RANDOM
	cont_tx.is_short_preamble = 0;

	for (i=0 ; i<24; i++)
		cont_tx.mac_header[i] = 0;			// ?

	RFTool_WiFi_PktTx(country_code, cont_tx);
}


typedef struct{
	kal_uint32 rx_total_err;
	kal_uint32 rx_total;
	kal_uint32 rx_lastSec_err;
	kal_uint32 rx_lastSec;
}EM_WIFI_RX;

EM_WIFI_RX em_wifi_rx;

static void EM_wifi_pktRx_callback(wndrv_test_rx_status_struct* result)
{
	float per_total  = 0;
	float per_lastSec = 0;

	em_wifi_rx.rx_lastSec_err	= result->int_crc_err_num - em_wifi_rx.rx_total_err;
	em_wifi_rx.rx_lastSec		= result->int_rx_ok_num - em_wifi_rx.rx_total;
	em_wifi_rx.rx_total_err 	= result->int_crc_err_num;
	em_wifi_rx.rx_total 		= result->int_rx_ok_num;

	per_lastSec = (float)em_wifi_rx.rx_lastSec_err/(float)em_wifi_rx.rx_lastSec;
	per_total = (float)em_wifi_rx.rx_total_err/(float)em_wifi_rx.rx_total;

	printc("LastSecond: OK %d ERR %d ALL %d -- %f ;	Total: OK %d ERR %d ALL %d -- %f\n", \
			em_wifi_rx.rx_lastSec- em_wifi_rx.rx_lastSec_err, em_wifi_rx.rx_lastSec_err, em_wifi_rx.rx_lastSec, per_lastSec, \
			em_wifi_rx.rx_total - em_wifi_rx.rx_total_err, em_wifi_rx.rx_total_err, em_wifi_rx.rx_total, per_total);
}

void EM_wifi_pktRx(void)
{
	RFTool_WiFi_Stop();
	osl_ext_os_sleep(100);
	memset(&em_wifi_rx, 0, sizeof(EM_WIFI_RX));
	RFTool_WiFi_PktRx(2412000,EM_wifi_pktRx_callback);
}
#endif

extern int sscanfl( char* szInput, char* szFormat, ... );
void mtkwifi_set_info(char* szParam)
{
	char module[16];
	char param[32];
	unsigned int value = 0;

	printc("you have input: %s\n",szParam);
	sscanfl( szParam, "%s %s", module, param);

	if(!strcmp(module, "wndrv"))
	{
		sscanfl(szParam, "%s %s %x", module, param, &value);
		if(!strcmp(param, "debug"))
		{
			printc("set wndrv debuglevel: 0x%x\n", value);
			wndrv_dbglevel = value;
		}
		else
		{
			goto err;
		}
	}
	else if(!strcmp(module, "hostapd"))
	{
		sscanfl(szParam, "%s %s %x", module, param, &value);
		if(!strcmp(param, "debug"))
		{
			printc("set hostapd debuglevel: 0x%x\n", value);
			HostapdDebugLevel = value;
		}
		else
		{
			goto err;
		}
	}
#ifdef DEMO_WIFI_EM_TEST
	else if(!strcmp(module, "em"))
	{
		sscanfl(szParam, "%s %s %x", module, param, &value);
		if(!strcmp(param, "enter"))
		{
			printc("set em enter: 0x%x\n", value);
			Demo_EM_wifi_enter();

		}
		else if(!strcmp(param, "tx"))
		{
			printc("set em tx: 0x%x\n", value);
			if(value == 0)
			{
				Demo_EM_wifi_contTX();
			}
			else if(value == 1)
			{
				Demo_EM_wifi_carrierSupp();
			}
			else if(value == 2)
			{
				Demo_EM_wifi_localFreq();
			}
			else if(value == 3)
			{
				Demo_EM_wifi_pktTx();
			}
			else
			{
				goto err;
			}

		}
		else if(!strcmp(param, "rx"))
		{
			printc("set em rx: 0x%x\n", value);
			EM_wifi_pktRx();
		}
		else
		{
			goto err;
		}
	}
#endif	
	else
	{
		goto err;
	}
	return;

err:
	printc("not found command: wifi set %s\n",szParam);
}

void mtkwifi_get_info(char* szParam)
{
	char module[16];
	char param[32];
	
	printc("you have input: %s\n",szParam);
	sscanfl( szParam, "%s %s", module, param);

	if(!strcmp(module, "wndrv"))
	{
		if(!strcmp(param, "debug"))
		{
			printc("get wndrv debuglevel: 0x%x\n", wndrv_dbglevel);
		}
		else
		{
			goto err;
		}
		
	}
	else if(!strcmp(module, "hostapd"))
	{
		if(!strcmp(param, "debug"))
		{
			printc("get hostapd debuglevel: 0x%x\n", HostapdDebugLevel);
		}
		else
		{
			goto err;
		}
	}
	else
	{
		goto err;
	}
	return;
	
err:
	printc("not found command: wifi get %s\n",szParam);
}

