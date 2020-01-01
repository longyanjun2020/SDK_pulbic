//==============================================================================
//
//  Description :
//  Author      :
//  Revision    :
//
//==============================================================================

#if 0
void __HEADER__(){}
#endif
/* AHC */
#include "config_fw.h" //for chip define and possibly PIN config
#if (CHIP == P_V2)
    #include "Customer_config.h" //for PIN config
#elif (CHIP == MCR_V2)
    #include "mmpf_pio.h"
#endif
#include "ahc_fs.h"
#include "ahc_general.h" //for GPIO
//#include "AHC_OS.h"
#include "ahc_msgqueue.h"
#include "ahc_message.h"
#include "ahc_stream.h"
#ifndef __CARDV_DSC_KEYPAD_H__
//#include "dsc_key.h"
#endif
#include "wlan_BCM.h"
/* WIFI Driver gb9662 headers  NOTE: add this path in MCP: WiFiDrv/WiFi-GB9662/wlan/src */
//#undef   CEIL      // differing in redefinition from Broadcom's header && lib_retina.h
//#include "bcmutils.h"
#include "osl_ext.h"
#include "dhd.h"
#include "dhd_bus.h"
//#undef   CEIL      // differing in redefinition from Broadcom's header && lib_retina.h

#include "mem.h"
#include "netapp.h"
#include "amn_config.h"
#include <string.h>
#ifndef LINUX
#include "lib_retina.h"//for printc
#endif
#include "netif.h"
#include "netconf.h"
//extern void wlan_get_mac_addr(uint8* mac_addr);
//something which is not in gb9619.h
extern void wlan_tx_pkt(struct pbuf *);
extern void UartCmd_WL(char* szParam);
/*----------------------------------------------------------------------------*/
/*                      DEFINITIONS                                           */
/*----------------------------------------------------------------------------*/

#if 0
void __VARIABLE__(){}
#endif

/*----------------------------------------------------------------------------*/
/*                      VARIABLES                                             */
/*----------------------------------------------------------------------------*/
extern struct netif main_netdev;
extern MMPF_OS_SEMID	g_assocsemi;
static AHC_BOOL m_bWPSStart       = AHC_FALSE;
static AHC_BOOL m_bWiFiStatus     = AHC_FALSE;
static UINT32 m_uiScanFileHandler = NULL;
static void* m_pScanBufPtr = NULL;
static WLAN_TARGET_AP_INFO m_sTargetAPInfo;

static UINT32 m_uiTxBufCnt = NCFG_TXBUF_COUNT;
static UINT32 m_uiRxBufCnt = NCFG_RXBUF_COUNT;
static UINT32 m_uiMaxScanBufSize = 0;
static UINT8	gEncrpType = 0;	
int gbWifiConnect = 0; 
extern AHC_BOOL     gbAhcDbgBrk;
/*----------------------------------------------------------------------------*/
/*                      PROTOTYPES                                            */
/*----------------------------------------------------------------------------*/

#if 0
void __SYS__(){}
#endif
void WLAN_SYS_StatusCallback(wlan_event_msg_t* event)
{

	MMPF_OS_AcquireSem(g_assocsemi,0);
	if (!gbAhcDbgBrk) {
    printc("WLAN CB : %d : ", event->event_type);
	}
    switch(event->event_type){

	case WLAN_E_LINK:
		
		if(event->flags){
			if( nhw_get_cur_wifi_mode() == NETAPP_WIFI_STATION_MODE &&
				/*gEncrpType != WLAN_ENCRYPT_WEP &&*/
				gEncrpType != WLAN_ENCRYPT_TKIP &&
				gEncrpType != WLAN_ENCRYPT_AES ){
				// Station Mode
	    		printc("Station Mode CONNECTED \n");
	    		gbWifiConnect++;
	    		if (main_netdev.flags & NETIF_FLAG_LINK_UP)
	    			nhw_set_status(NETAPP_NET_STATUS_READY);
	    		
	    		//inform network task for starting up dhcp client if necessary
	    		nhw_wifi_link_report(1);
			}
		}
		else{
			//link down 
			printc("link down reason = %d\n",event->reason);
			nhw_wifi_link_report(0);
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
    	
    	if (gbWifiConnect == 0){
      		//gbWifiConnect == 0
      	    AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_CONNECT_FAIL, 0 );
     	}
     	
    	printc("DISCONNECTED %d\n", gbWifiConnect);
    	if (gbWifiConnect == 0) {
    		ncfg_allow_APP_access(0);
	    	nhw_set_status(NETAPP_NET_STATUS_IDLE);
#ifdef	ALWAYS_STREAM_ON
			aitstreamer_run("none");
#endif
		}
    	break;

    case WLAN_E_ASSOC_IND://8
    	// AP Mode
	    if( 0 == nhw_add_connected_sta(event->addr.mac))
	    	gbWifiConnect++;
	    AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_CONNECT_SUCCESS, 0 );
	    printc(BG_GREEN("Client Connect SoftAP %d")"\r\n", gbWifiConnect);

		// TODO: 
	    if (gbWifiConnect == 1) {
	    	nhw_set_status(NETAPP_NET_STATUS_READY);
#ifdef	ALWAYS_STREAM_ON
			aitstreamer_run("MJPEG.0");
#endif
	    }
	    break;
	    
    case WLAN_E_SCAN_COMPLETE://26
	    printc("Scan Done \n");	    
	    break;
	
	case WLAN_E_TXFAIL:
		// TODO:
		printc("!!! TX FAILED !!!\r\n");
		break;
	case WLAN_E_PSK_SUP:
		
		if( nhw_get_cur_wifi_mode() == NETAPP_WIFI_STATION_MODE &&
			( /*gEncrpType == WLAN_ENCRYPT_WEP ||*/
			gEncrpType == WLAN_ENCRYPT_TKIP ||
			gEncrpType == WLAN_ENCRYPT_AES ) ){
			// Station Mode
	    	printc("Station Mode CONNECTED \n");
	    	gbWifiConnect++;
	    	if (main_netdev.flags & NETIF_FLAG_LINK_UP)
	    		nhw_set_status(NETAPP_NET_STATUS_READY);
	    	
	    	//inform network task for starting up dhcp client if necessary
	    	nhw_wifi_link_report(1);
		}
	 	break;
    default:
    	printc("NO Mapping");
	    break;
	}
	
	printc("\n");
	MMPF_OS_ReleaseSem(g_assocsemi);

}

int8* WLAN_SYS_GetVersion(void)
{
    return (int8*)wlan_get_version();
}

#define GB9619_FW_LOADING_TIME 200
static void WLAN_SYS_WaitForLoading9619(void)
{
    //GB9616 dependent according to 9619 FAE.
    MMPF_OS_SleepMs(GB9619_FW_LOADING_TIME);//wait for firmware loading.
    AHC_GPIO_SetData(NCFG_RESET_PIN, AHC_TRUE);
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
nhw_drv_hdl WLAN_SYS_Start(void)
{
    wl_drv_hdl h;
    char wlcmd[64] = {0};
    
    //according to Yining, here it loads the FW.
    h = wlan_start(WLAN_SYS_StatusCallback, m_uiTxBufCnt, m_uiRxBufCnt, m_uiMaxScanBufSize);

    WLAN_SYS_WaitForLoading9619();

    m_bWiFiStatus = AHC_TRUE;
	
	//short/long frame retry counter of MAC layer set to 15 for reducing packet loss
	sprintf( wlcmd, " lrl 15");
	UartCmd_WL( wlcmd );
	
	wlcmd[0] = 0;
	sprintf( wlcmd, " srl 15");
	UartCmd_WL( wlcmd );
	
    return h;
}

void WLAN_SYS_Stop(nhw_drv_hdl hdl)
{
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
    if(m_bWiFiStatus == AHC_TRUE)
        return wlan_get_mode();
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

#pragma arm section code = "WIFISpeedUp", rwdata = "WIFISpeedUp",  zidata = "WIFISpeedUp"
void WLAN_SYS_TxPkt(struct pbuf *p)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return;
    wlan_tx_pkt(p);
}


INT32 WLAN_SYS_GetTXQueueAvailCount(void)
{
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;
    else
        return wlan_get_tx_queue_avail_count();
}
#pragma arm section code, rwdata,  zidata

void WLAN_SYS_GetStatsInfo(WLAN_STATISTICS_INFO *stats, char *sdio_stat_buf, int sdio_stat_size)
{
	extern dhd_pub_t *g_dhd_info;  // It's opaque!! Actual declaration is: dhd_info_t *g_dhd_info;
	struct bcmstrbuf strbuf;

	#define __copy_bcm_stats(_s_)     stats->_s_ = g_dhd_info->_s_

	// Get statistics of dhd_bus_t, located in WiFiDrv/WiFi-GB9662/wlan/src/dhd/sys/dhd_sdio.c
	//----------------------------------------------------------------------
	strbuf.buf  = strbuf.origbuf  = sdio_stat_buf;
	strbuf.size = strbuf.origsize = sdio_stat_size;
	dhd_bus_dump( g_dhd_info, &strbuf );

	// dngl_stats_t dstats;	/* Stats for dongle-based data */
	//----------------------------------------------------------------------
	__copy_bcm_stats( dstats.rx_packets );		/* total packets received */
	__copy_bcm_stats( dstats.tx_packets );		/* total packets transmitted */
	__copy_bcm_stats( dstats.rx_bytes );		/* total bytes received */
	__copy_bcm_stats( dstats.tx_bytes );		/* total bytes transmitted */
	__copy_bcm_stats( dstats.rx_errors );		/* bad packets received */
	__copy_bcm_stats( dstats.tx_errors );		/* packet transmit problems */
	__copy_bcm_stats( dstats.rx_dropped );		/* packets dropped by dongle */
	__copy_bcm_stats( dstats.tx_dropped );		/* packets dropped by dongle */
	__copy_bcm_stats( dstats.multicast );      /* multicast packets received */

	/* Additional stats for the bus level */
	//----------------------------------------------------------------------
	__copy_bcm_stats( tx_packets );	/* Data packets sent to dongle */
	__copy_bcm_stats( tx_multicast );	/* Multicast data packets sent to dongle */
	__copy_bcm_stats( tx_errors );	/* Errors in sending data to dongle */
	__copy_bcm_stats( tx_ctlpkts );	/* Control packets sent to dongle */
	__copy_bcm_stats( tx_ctlerrs );	/* Errors sending control frames to dongle */
	__copy_bcm_stats( rx_packets );	/* Packets sent up the network interface */
	__copy_bcm_stats( rx_multicast );	/* Multicast packets sent up the network interface */
	__copy_bcm_stats( rx_errors );	/* Errors processing rx data packets */
	__copy_bcm_stats( rx_ctlpkts );	/* Control frames processed from dongle */
	__copy_bcm_stats( rx_ctlerrs );	/* Errors in processing rx control frames */
	__copy_bcm_stats( rx_dropped );	/* Packets dropped locally (no memory) */
	__copy_bcm_stats( rx_flushed );  /* Packets flushed due to unscheduled sendup thread */
	__copy_bcm_stats( wd_dpc_sched );   /* Number of times dhd dpc scheduled by watchdog timer */

	__copy_bcm_stats( rx_readahead_cnt );	/* Number of packets where header read-ahead was used. */
	__copy_bcm_stats( tx_realloc );	/* Number of tx packets we had to realloc for headroom */
	__copy_bcm_stats( fc_packets );       /* Number of flow control pkts recvd */
}

static UINT32 WLAN_SYS_Init9619(void)
{
    // WIFI's wake-on-LAN INPUT. Basically it's not implemented
    // printc("Config WIFI GPIO - WAKE\r\n");
    AHC_GPIO_SetOutputMode( NCFG_WAKEUP_PIN, AHC_FALSE );

    // WIFI module's RESET output, active-low
    // printc("Config WIFI GPIO - RESET\r\n");
    AHC_GPIO_SetOutputMode( NCFG_RESET_PIN,  AHC_TRUE  );
    AHC_GPIO_SetData( NCFG_RESET_PIN, 1 );

    MMPF_OS_SleepMs(GB9619_FW_LOADING_TIME);   // sleeping for a while: NET should be waken after media's readiness.
    return 0;
}

static UINT32 WLAN_SYS_Reset9619(void)
{
    AHC_GPIO_SetData( NCFG_RESET_PIN, 0 );
    MMPF_OS_SleepMs(100);
    AHC_GPIO_SetData( NCFG_RESET_PIN, 1 );
    MMPF_OS_SleepMs(3000);
    return 0;
}

/* Because there is only one module is ported.
 * Wait until there are many WLAN modules are ported so that it would become something like camera sensor files.
 * Now it centralize HW module dependent functions here.
 */
//Use function pointers or compiler options while there are other WLAN modules.
//Move *9619 to other functions if needed.
void WLAN_SYS_InitHw(void)
{
    osl_ext_sdio_internal_set_id(NCFG_SDIO_PAD);
    (void)WLAN_SYS_Init9619();
}

void WLAN_SYS_ResetHw(void)
{
    (void)WLAN_SYS_Reset9619();
}


#if 0
void __STA__(){} //Station
#endif


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
	int i;
	
    if(m_bWiFiStatus == AHC_FALSE)
        return NULL;
    
    list = (WLAN_SCAN_RESULT*)pchBuf;

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
        return wlan_scan_network((char*)scan_buf, buf_size);
}

int32 WLAN_STA_PutScanInfo(int8* scan_buf, uint32 buf_size)
{
    uint32 uiWriteCount;
    
    if(AHC_FS_FileOpen(WLAN_SCAN_FILE_NAME, sizeof(WLAN_SCAN_FILE_NAME),
                        "wb", sizeof("wb"), &m_uiScanFileHandler) !=0){
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
                       "rb", sizeof("rb"), &m_uiScanFileHandler) !=0){
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

#if 0
void __AP__(){}
#endif
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
	int32 ret;
	char wlcmd[64] = {0};
	
    if(m_bWiFiStatus == AHC_FALSE)
        return -1;

    LwIP_set_ap_conf((char*)ssid, NULL, channel);

    if(bHideSSID == AHC_TRUE){
        printc("Hide SSID \n");
	}else{
        printc("broadcast SSID \n");
	}
	
	ret = wlan_create_sw_ap((char*)ssid, authMode, encryption, (char*)key, channel, bHideSSID);
	
	sprintf( wlcmd, " maxassoc %d", NCFG_WIFI_MAX_CONNECTION);
	UartCmd_WL( wlcmd );
	
	//Improve TXOP of AC_VI and AC_VO for getting better throughput
	wlcmd[0] = 0;
	sprintf( wlcmd, " wme_ac ap vo txop 0x200");//512*32 us =  16 ms
	UartCmd_WL( wlcmd );
	
	wlcmd[0] = 0;
	sprintf( wlcmd, " wme_ac ap vi txop 0x200");//512*32 us =  16 ms
	UartCmd_WL( wlcmd );
	
	return ret;
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

#if 0
void __WPS__(){} //Wifi Protected Setup?
#endif

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
	
	/*case WLAN_WPS_STATE_CONN_FAIL:
        printc("CONN FAIL");
    break;*/
    
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
        
    wps_config.WscMode      = wpsConfigInfo->WscMode;
    
    memcpy(wps_config.PIN, wpsConfigInfo->PIN, 8);
    memcpy(wps_config.Bssid, wpsConfigInfo->Bssid, 6);
    
    wps_config.JoinAP       = wpsConfigInfo->JoinAP;
    wps_config.ScanBufSize  = wpsConfigInfo->ScanBufSize;
    wps_config.AssocAPTime  = wpsConfigInfo->AssocAPTime;
    #if 0
    printc("WPS Config \n");
    printc("Mode        : %d \n", wps_config.WscMode);
    printc("PIN         : %s \n", wps_config.PIN);
    printc("Bssid       : %s \n", wps_config.Bssid);
    printc("JoinAP      : %d \n", wps_config.JoinAP);
    printc("ScanBufSize : %d \n", wps_config.ScanBufSize);
    printc("AssocAPTime : %d \n", wps_config.AssocAPTime);
    
    #endif
	error = wlan_wps_start(wps_config, (wlan_wps_event_callback)pFunc);
	
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
        
    return wlan_wps_get_status();
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
* Function:   	wlan_mfg_tx_bg
*
* Purpose:   	This routine is used to perform manufacturing 11b/g continuous TX test
*
* Parameters: channel		Channel used for TX
*			 rate			11b/g rate used for TX
*			 powerValue	Output power in units of milli-dBm, -1 means default power
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
INT32 WLAN_MFG_TxBG(WLAN_CHANNEL channel, WLAN_RATE rate, INT32 powerValue)
{
    return wlan_mfg_tx_bg(channel, rate, powerValue);
}

/****************************************************************************
* Function:   	wlan_mfg_tx_n
*
* Purpose:   	This routine is used to perform manufacturing 11n continuous TX test
*
* Parameters: channel		Channel used for TX
*			 rate			11n rate used for TX
*			 powerValue	Output power in units of milli-dBm, -1 means default power
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/

INT32 WLAN_MFG_TxN(WLAN_CHANNEL channel, WLAN_MCS_RATE rate, INT32 powerValue)
{
    return wlan_mfg_tx_n(channel, rate, powerValue);
}

/****************************************************************************
* Function:   	wlan_mfg_rx
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
    return wlan_mfg_rx(channel);
}

/****************************************************************************
* Function:   	wlan_mfg_rx_getpkt
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
    return wlan_mfg_rx_getpkt(uiCount);
}

/****************************************************************************
* Function:   	wlan_mfg_carrier_tone
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
    return wlan_mfg_carrier_tone(channel);
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
    return wlan_mfg_stop();
}
