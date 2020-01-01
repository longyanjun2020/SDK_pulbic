/*
 * wlan_cli.c
 *
 *  Created on: 2018/1/30
 *  Author: titan.huang
 *  Here are command line usages of wlan
 */

/*===========================================================================
 * Include file
 *===========================================================================*/

#include "config_fw.h"
#if defined (_NET_SDK_) || CHIP == MCR_V2
#include "amn_config.h" //for building net.a MFG should be always off, and make SDK independent from Customer_config
#else
#include "Customer_config.h"
#endif
#include "os_wrap.h"
#include "ahc_utility.h"
#include "ahc_os.h"

#include "wlan.h"

#ifndef LINUX
  #include "wlanif.h"
  //#include "dhcp_server.h" //cannot be included
  #include "inet_chksum.h"
#endif
//#include "netif.h"
//#include "tcp.h"
//#include "dhcp.h"
#include "sockets.h"
//#include "ip.h"
//#include "api.h"
//#include "err.h"
#include "netconf.h"

#include "dhcp_server.h"
#include "netapp.h"
#include "amn_sysobjs.h"

#include "ahc_debugex.h" // for AHC_DBG_GetCurPrioEx
#include "UartShell.h"
//#endif


//******************************************************************************
// Extern functions
//******************************************************************************
#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)
extern void mtkwifi_set_info(char* szParam);
extern void mtkwifi_get_info(char* szParam);
#endif

#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_RTK)
extern void rtk_wifi_iwpriv(char *szParam);
extern void rtk_wifi_test(char *szParam);
#endif

//******************************************************************************
// UART Command set comes from Host/AHC_user/UI/AHC_Main.c, TurnkeyBase
//******************************************************************************
extern struct netif main_netdev;
static u16_t    ping_seq_num;

static struct tcp_pcb *connected_pcb = NULL;
#define SEND_BUFSIZE (1400)
static char send_buf[SEND_BUFSIZE];
#if 0
static unsigned txperf_client_connected = 0;
#endif


void  UartCmd_NetStart(char* szParam)
{
    extern void NetSimpleInit(void);
    NetSimpleInit();
}
void  UartCmd_WlanStart(char* szParam)
{
    nhw_drv_hdl h = WLAN_SYS_Start();
    nhw_set_handle(h);
    printc("wlan_start hdl = 0x%x\r\n", h);
}

void  UartCmd_WlanStop(char* szParam)
{
    WLAN_SYS_Stop(nhw_get_handle());
    printc("wlan_stop\r\n");
}

void  UartCmd_WlanScan(char* szParam)
{
    //char scan_buf[2*1024] = {0x00};
    void* pScanMemPtr;
    UINT32 uiScanBufLength = WLAN_SCAN_BUF_SIZE;

    WLAN_SCAN_RESULT *list;
    WLAN_BSS_INFO *bi;
    int i;

    pScanMemPtr = mem_malloc(uiScanBufLength);
    if(pScanMemPtr == NULL){
        printc("alloc scan buffer fail\n");
    }

    list = (WLAN_SCAN_RESULT*)pScanMemPtr;

    if(WLAN_STA_ScanAP(pScanMemPtr, uiScanBufLength) == -1)
        printc("wlan_scan_netwrok: failed\n");

    printc("wlan_scan_netwrok, AP count = %d\r\n", list->count);

    if (list->count > 0) {

      bi = list->bss_info;

      printc("count=%d\n",list->count);

      for (i = 0; i < list->count; i++, bi = (WLAN_BSS_INFO*)((BYTE*)bi + bi->length)) {
            char ssidbuf[129] = {0x00};

            printc("bi->length=%d\n",bi->length);
            /* SSID */
            printc("SSID = %s\n", bi->SSID);
            printc("SSID_len = %d\n", bi->SSID_len);

            if(bi->SSID_len > 32)
                memcpy(ssidbuf, bi->SSID, 32);
            else
                memcpy(ssidbuf, bi->SSID, bi->SSID_len);

            printc("SSID: %s, ", ssidbuf);

            /* BSSID */
            //bssid = wl_ether_etoa((struct ether_addr*)&bi->BSSID[0]);
            printc("BSSID: %02x:%02x:%02x:%02x:%02x:%02x, ",
                    bi->BSSID[0], bi->BSSID[1], bi->BSSID[2], bi->BSSID[3], bi->BSSID[4], bi->BSSID[5]);

            /* CHANNEL */
            printc("bi->chanspec = %d\n", bi->chanspec);
            printc("Ch: %d, ", WLAN_CHSPEC_CHANNEL(bi->chanspec));

            /* RSSI */
            printc("RSSI: %ddBm, ", (INT16)(bi->RSSI));

            /* Mode */
            printc("%s, ", CAPMODE2STR(bi->capability));

            /* Security */
            printc("Security: %s\n", (bi->capability & WLAN_DOT11_CAP_PRIVACY)? "Encrypted":"Open");
      }
    }
    mem_free(pScanMemPtr);

}

void  UartCmd_Wlanjoinnetwork(char* szParam)
{
    INT8 ssid[32];
    WLAN_AUTH_MODE authMode = 0;
    WLAN_ENCRYPTION encryption;
    INT8 key[64+1];
    char *bootProto;

    bootProto = (char *)amn_currConfig_get( "Net.Dev.1.BootProto" )->v.intVal;

    memset(ssid, 0, sizeof(ssid));
    memset(key, 0, sizeof(key));
//  WLAN_STA_JoinAP("iPhone for YC", WLM_WPA2_AUTH_PSK, WLM_ENCRYPT_AES, "yangyang");
//  WLAN_STA_JoinAP("SAPIDO_RB-1800_cb48a1", WLM_WPA_AUTH_DISABLED, WLM_ENCRYPT_WEP, "0229027390");
//  WLAN_STA_JoinAP("AIT_Network", WLM_WPA_AUTH_DISABLED, WLM_ENCRYPT_WEP, "1234567890");
//  WLAN_STA_JoinAP("DIR652-XuOpenWrt", WLM_WPA2_AUTH_PSK, WLM_ENCRYPT_AES, "alpha-image");
//  WLAN_STA_JoinAP("TP-LINK-5A9D12", WLM_WPA_AUTH_PSK, WLM_ENCRYPT_AES, "115A9D12");


    sscanfl( szParam, "%s %d %d %s", ssid, &authMode, &encryption, key);
    printc("%s %d %d %s", ssid, authMode, encryption, key);
    net_context.mode = NETAPP_WIFI_STATION_MODE;

    if (!strcasecmp("STATIC", bootProto)) {
        net_context.local_ip.addr   = inet_addr( amn_currConfig_get("Net.Dev.1.IPV4.Address")->v.strVal );
        net_context.gateway_ip.addr = inet_addr( amn_currConfig_get("Net.Dev.1.IPV4.Gateway")->v.strVal );
        net_context.net_mask.addr   = inet_addr( amn_currConfig_get("Net.Dev.1.IPV4.Mask")->v.strVal );
        netif_set_addr(&main_netdev, &net_context.local_ip,
                                     &net_context.net_mask,
                                     &net_context.gateway_ip);
    }
    else
    if (!strcasecmp( "DHCP", bootProto)) {
        IP4_ADDR(&net_context.local_ip,   0,0,0,0);
        IP4_ADDR(&net_context.net_mask,   0,0,0,0);
        IP4_ADDR(&net_context.gateway_ip, 0,0,0,0);
    }

    WLAN_STA_JoinAP((int8*)ssid, authMode, encryption, (int8*)key);
}

#define PING_ID             0xAFAF
#define PING_DATA_SIZE      (32)      /** ping additional data size to include in the packet */

static void ping_prepare_echo( struct icmp_echo_hdr *iecho, u16_t len )
{
    int i;

    ICMPH_TYPE_SET( iecho, ICMP_ECHO );
    ICMPH_CODE_SET( iecho, 0 );
    iecho->chksum = 0;
    iecho->id = PING_ID;
    iecho->seqno = htons( ++ping_seq_num );

    /* fill the additional data buffer with some data */
    for ( i = 0; i < PING_DATA_SIZE; i++ )
    {
        ( (char*) iecho )[sizeof(struct icmp_echo_hdr) + i] = i;
    }

    iecho->chksum = inet_chksum((void*) iecho, len );
}

static err_t ping_send( int socket_hnd, struct ip_addr *addr )
{
    int err;
    struct icmp_echo_hdr *iecho;
    struct sockaddr_in to;
    size_t ping_size = sizeof(struct icmp_echo_hdr) + PING_DATA_SIZE;

    // Allocate memory for packet
    if ( ( iecho = mem_malloc( ping_size ) ) == NULL)
    {
        printc("meme alloc failed\n");
        return ERR_MEM;
    }

    // Construct ping request
    ping_prepare_echo( iecho, ping_size );

    // Send the ping request
    to.sin_len = sizeof( to );
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = addr->addr;

    err = net_sendto( socket_hnd, (const void*)iecho, ping_size, 0, (struct sockaddr*) &to, sizeof( to ) );

    // free packet
    mem_free( (void*)iecho );

    return ( err ? ERR_OK : ERR_VAL );
}

static err_t ping_recv( int socket_hnd )
{
    char buf[64];
    int fromlen, len;
    struct sockaddr_in from;
    struct ip_hdr *iphdr;
    struct icmp_echo_hdr *iecho;

    while ( ( len = net_recvfrom( socket_hnd, buf, sizeof( buf ), 0,
            (struct sockaddr*) &from, (socklen_t*) &fromlen ) ) > 0 )
    {
        if ( len >= (int)( sizeof(struct ip_hdr) + sizeof(struct icmp_echo_hdr) ) )
        {
            iphdr = (struct ip_hdr *) buf;
            iecho = (struct icmp_echo_hdr *) ( buf + ( IPH_HL( iphdr ) * 4 ) );

            if ( ( iecho->id == PING_ID ) &&
                 ( iecho->seqno == htons( ping_seq_num ) ) &&
                 ( ICMPH_TYPE( iecho ) == ICMP_ER ) )
            {
                return ERR_OK; // Echo reply received - return success
            }
        }
    }

    return ERR_TIMEOUT; // No valid echo reply received before timeout
}

void UartCmd_Ping(char* szParam)
{
    int socket_hnd = -1;
    int recv_timeout = 1000;
    int i = 0;
    u32_t send_time;
    err_t result;
    char ip[20];
    struct ip_addr ipaddr;


    sscanfl( szParam, "%s", ip);
    ipaddr.addr = inet_addr(ip);
    // Open a local socket for pinging
    if ( ( socket_hnd = net_socket( AF_INET, SOCK_RAW, IP_PROTO_ICMP ) ) < 0 )
    {
        printc("unable to create socket for Ping\r\n");
        return;
    }

    // Set the receive timeout on local socket so pings will time out.
    net_setsockopt( socket_hnd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof( recv_timeout ) );

    printc("Pinging: %u.%u.%u.%u\r\n",
            (unsigned char) ( ( htonl(ipaddr.addr) >> 24 ) & 0xff ),
            (unsigned char) ( ( htonl(ipaddr.addr) >> 16 ) & 0xff ),
            (unsigned char) ( ( htonl(ipaddr.addr) >> 8 ) & 0xff ),
            (unsigned char) ( ( htonl(ipaddr.addr) >> 0 ) & 0xff ));


    do {
        printc("#%d ping\n", i+1);

        // Send a ping
        if ( ping_send( socket_hnd, (struct ip_addr*) &ipaddr.addr ) != ERR_OK )
        {
            printc("Unable to send Ping\r\n");
            return;
        }

        // Record time ping was sent
        send_time = sys_now( );

        // Wait for ping reply
        result = ping_recv( socket_hnd );

        if ( ERR_OK ==  result)
        {
            printc("Ping Reply %dms\r\n", (int)( sys_now( ) - send_time ));
        }
        else
        {
            printc("Ping timeout\r\n");
        }

        // Sleep until time for next ping
        AHC_OS_SleepMs(1000);
    } while (i++<100);

    printc("Ping completed!\n");
}


void UartCmd_GetVersion(char* szParam)
{
    printc("Driver release version is %s\n", WLAN_SYS_GetVersion());
}

void uart_wps_event_callback(WLAN_WPS_STATE event)
{
    printc("WPS CB : %d : ", event);

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
    {
        char * pConfigStr;
        WLAN_CONFIG_INFO wlan_config_info;
        WLAN_WPS_GetCredential(&wlan_config_info);

        //Record WPS Info (SSID !B ENCRP !B KEY)
        pConfigStr = amn_currConfig_get("Net.WIFI_STA.AP.1.EncType")->v.strVal;

        if(wlan_config_info.Enc_Mode == WLAN_ENCRYPT_WEP){
            strcpy(pConfigStr,"WEP");
            wlan_config_info.Enc_Mode = WPA_CRYPTO__WEP;
        }
        else if (wlan_config_info.Enc_Mode == WLAN_ENCRYPT_AES){
            strcpy(pConfigStr,"AES");
            wlan_config_info.Enc_Mode = WPA_CRYPTO__AES;
        }
        else if (wlan_config_info.Enc_Mode == WLAN_ENCRYPT_TKIP){
            strcpy(pConfigStr,"TKIP");
            wlan_config_info.Enc_Mode = WPA_CRYPTO__TKIP;
        }
        else if (wlan_config_info.Enc_Mode == WLAN_ENCRYPT_NONE){
            *pConfigStr = 0;
            wlan_config_info.Enc_Mode = WPA_CRYPTO__NONE;
        }
        else{
            printc(FG_RED("Unknown encry type = %d\n"),wlan_config_info.Enc_Mode);
            break;
        }

        pConfigStr = amn_currConfig_get("Net.WIFI_STA.AP.1.SSID")->v.strVal;

        memcpy(pConfigStr, wlan_config_info.Ssid.Ssid ,wlan_config_info.Ssid.SsidLength);
        *(pConfigStr + wlan_config_info.Ssid.SsidLength) = 0;

        pConfigStr = amn_currConfig_get("Net.WIFI_STA.AP.1.CryptoKey")->v.strVal;
        memcpy(pConfigStr, wlan_config_info.PresharedKey ,wlan_config_info.Psk_length);
        *(pConfigStr + wlan_config_info.Psk_length) = 0;

        AddWlanFavAP( 0, amn_currConfig_get("Net.WIFI_STA.AP.1.SSID")->v.strVal,
                         wlan_config_info.Enc_Mode,
                         amn_currConfig_get("Net.WIFI_STA.AP.1.CryptoKey")->v.strVal );

        //prepare network interface setting
        IP4_ADDR(&net_context.local_ip,   0,0,0,0);
        IP4_ADDR(&net_context.net_mask,   0,0,0,0);
        IP4_ADDR(&net_context.gateway_ip, 0,0,0,0);

        if(!strcasecmp( "STATIC", (char *)amn_currConfig_get( "Net.Dev.1.BootProto" )->v.intVal)){
            net_context.local_ip.addr   = inet_addr( amn_currConfig_get("Net.Dev.1.IPV4.Address")->v.strVal );
            net_context.gateway_ip.addr = inet_addr( amn_currConfig_get("Net.Dev.1.IPV4.Gateway")->v.strVal );
            net_context.net_mask.addr   = inet_addr( amn_currConfig_get("Net.Dev.1.IPV4.Mask")->v.strVal );
            netif_set_addr(&main_netdev,&net_context.local_ip,
                    &net_context.net_mask,
                    &net_context.gateway_ip);
        }
        printc("CONFIGURED");
    }
    break;
    default:
    break;
    }

    printc(": status : %d \n", WLAN_WPS_GetStatus());


}

/*
 * wpsstart mode, auto_join, bufsize_K, time, bssid0(hex), bssid1(hex), bssid2(hex), bssid3(hex), bssid4(hex), bssid5(hex)
 * Test with ZyXEL is OK by command - wpsstart 2 1 32 1000
 *   note: PBC(2) mode works, but PIN(1) mode fails
 * example:
 * wpsstart 2 1 32 1000
 */
void UartCmd_WPSSTART(char* szParam)
{
    WLAN_WPS_STATE state;
    WLAN_CONFIG_INFO wlan_config_info;
    WLAN_WPS_CONFIG wpsConfigInfo;
    UINT32 pin;
    UINT32 uiWPSMode, uiAutoJoin, uiScanBUFKB, uiAssocAPTime;
    UINT32 uiBssid[6];

    sscanfl( szParam, "%d %d %d %d %x %x %x %x %x %x",
            &uiWPSMode, &uiAutoJoin, &uiScanBUFKB, &uiAssocAPTime,
            &uiBssid[0], &uiBssid[1], &uiBssid[2], &uiBssid[3], &uiBssid[4], &uiBssid[5]);

    printc("Mode : %d, Auto: %d, ScanBUFKB: %d, uiAssocAPTime : %d , Bssid: %x : %x : %x : %x : %x : %x\n",
            uiWPSMode, uiAutoJoin, uiScanBUFKB, uiAssocAPTime,
            uiBssid[0], uiBssid[1], uiBssid[2], uiBssid[3], uiBssid[4], uiBssid[5]);

    net_context.mode = NETAPP_WIFI_STATION_MODE;

    if(uiWPSMode == 1){
        wpsConfigInfo.WscMode = 1; /* 1: PIN, 2:PBC */

        /* Generate PIN code */

        WLAN_WPS_GenPin(&pin);
        sprintf((char*)wpsConfigInfo.PIN, "%d", pin);
        printc("PIN is: %s\n", (char*)wpsConfigInfo.PIN);

        AHC_OS_SleepMs(2000);

        /* Set "MAC address" of target AP */
        wpsConfigInfo.Bssid[0] = uiBssid[0];
        wpsConfigInfo.Bssid[1] = uiBssid[1];
        wpsConfigInfo.Bssid[2] = uiBssid[2];
        wpsConfigInfo.Bssid[3] = uiBssid[3];
        wpsConfigInfo.Bssid[4] = uiBssid[4];
        wpsConfigInfo.Bssid[5] = uiBssid[5];


    }else if(uiWPSMode == 2){
        wpsConfigInfo.WscMode = 2; /* 1: PIN, 2:PBC */
    }

    wpsConfigInfo.JoinAP        = uiAutoJoin;  /* 0: Not to join AP, 1: to join AP */
    wpsConfigInfo.ScanBufSize   = uiScanBUFKB*1024; //32*1024 = 32KB
    wpsConfigInfo.AssocAPTime   = uiAssocAPTime;//20000;    //20s

    /* Prevent DHCP client from starting up
    at the first time WPS procedure use probe request of WPS protocol to connect to AP*/
    IP4_ADDR(&net_context.local_ip,   10,10,10,10);
    WLAN_WPS_Start(&wpsConfigInfo, (void*)uart_wps_event_callback);
    return;//Don't use polling
    do {
        state = WLAN_WPS_GetState();
        printc(FG_YELLOW("WPS state = %d task(%d)\n"), state, AHC_DBG_GetCurPrioEx());

        AHC_OS_SleepMs(1000);

    } while(state != WLAN_WPS_STATE_OFF && state != WLAN_WPS_STATE_CONFIGURED);

    printc("Final WPS state = %d, status : %d \n", state, WLAN_WPS_GetStatus());

    if(state == WLAN_WPS_STATE_CONFIGURED) {
        //Auto join meas that WiFi driver will auto join AP after WPS is done,so we should not join AP again!
        if(uiAutoJoin == 0){
            WLAN_WPS_GetCredential(&wlan_config_info);
            printc("Join Auto\n");
            if(wlan_config_info.Enc_Mode == WLAN_ENCRYPT_WEP){
                printc("wlan_config_info.Wep_Key[wlan_config_info.WepKeyToUse].KeyMaterial : %s \n", wlan_config_info.Wep_Key[wlan_config_info.WepKeyToUse].KeyMaterial);
                WLAN_STA_JoinAP((int8*)wlan_config_info.Ssid.Ssid,
                                wlan_config_info.Auth_Mode,
                                wlan_config_info.Enc_Mode,
                                (int8*)wlan_config_info.Wep_Key[wlan_config_info.WepKeyToUse].KeyMaterial);
            }else{
                extern int gbWifiConnect;
                int     i;
                printc("wlan_config_info.PresharedKey : %s \n", wlan_config_info.PresharedKey);
                WLAN_STA_JoinAP((int8*)wlan_config_info.Ssid.Ssid,
                                  wlan_config_info.Auth_Mode,
                                  wlan_config_info.Enc_Mode,
                                  (int8*)wlan_config_info.PresharedKey);
                for (i=0; i<20; i++) {
                    if (gbWifiConnect) break;;  // successfully JOIN
                    MMPF_OS_Sleep(500);
                }
                if (i >= 20) {
                    printc("WPS Join Failed\r\n");
                    return;
                }
            }
        }
    }else{
        printc("WPS FAIL \n");
    }
}

void UartCmd_WPSGetStatus(char* szParam)
{
    UINT32 uiStatus;

    uiStatus = WLAN_WPS_GetStatus();
    printc("Status : %d \n", uiStatus);
}

void UartCmd_WPSStop(char* szParam)
{
    WLAN_WPS_Stop();
}


void UartCmd_CreateSWAP(char* szParam)
{
    ip_addr_t ip, mask, gw;

    UINT32 uiHideSSID, err;
    int uiIP1,uiIP2,uiIP3,uiIP4,uiEnableWPS;
    char uiSSID[24],uiPSW[24];
    int uiCrypto=1, chan=1 ;
#ifdef WPS_AP_SUPPORT
    wps_config_info_t wps_config_info;
#endif


    memset(uiSSID,0,sizeof(uiSSID));
    memset(uiPSW,0,sizeof(uiPSW));

    uiEnableWPS = 0;
    uiHideSSID = AHC_FALSE;

    sscanfl( szParam, "%d %d %d %s %s %d %d %d %d",&uiEnableWPS,&uiCrypto,&chan,uiSSID,uiPSW,&uiIP1,&uiIP2,&uiIP3,&uiIP4);
    printc("\nWPS Enabled =%d   \n\
            Crypto=%d (0-AES-WPA  1-AES-WPA2  2-WEP 3-TKIP-WPA)\n\
            Channel=%d\n\
            SSID=%s\n\
            PSW=%s\n\
            IP=%d.%d.%d.%d\n",
            uiEnableWPS,uiCrypto, chan, uiSSID, uiPSW,uiIP1,uiIP2,uiIP3,uiIP4);

    IP4_ADDR(&ip,   uiIP1,uiIP2, uiIP3, uiIP4);
    IP4_ADDR(&gw,   uiIP1,uiIP2, uiIP3, uiIP4);
    IP4_ADDR(&mask, 255,255,255,0);

    netif_set_addr(&main_netdev, &ip, &mask, &gw);
    netif_set_up(&main_netdev);
    net_context.mode = NETAPP_WIFI_AP_MODE;

    switch (uiCrypto) {
    case 0:
        //sprintf( uiSSID, "AITAP-WPA-AES" );
        err = WLAN_AP_Create((int8*)uiSSID, WLAN_WPA_AUTH_PSK, WLAN_ENCRYPT_AES, (int8*)uiPSW, chan, uiHideSSID);
        break;
    case 1:
        //sprintf( uiSSID, "AITAP-WPA2-AES");
        //err = WLAN_AP_Create((int8*)uiSSID, WLAN_WPA2_AUTH_PSK, WLAN_ENCRYPT_AES, (int8*)"1234567890", 1, uiHideSSID);
        err = WLAN_AP_Create((int8*)uiSSID, WLAN_WPA2_AUTH_PSK, WLAN_ENCRYPT_AES, (int8*)uiPSW, chan, uiHideSSID);
        break;
    case 2:
        //sprintf( uiSSID, "AITAP-WEP" );
        err = WLAN_AP_Create((int8*)uiSSID,  WLAN_WPA_AUTH_DISABLED, WLAN_ENCRYPT_WEP, (int8*)uiPSW, chan, uiHideSSID);
        break;
    case 3:
        //sprintf( uiSSID, "AITAP-WPA-TKIP" );
        err = WLAN_AP_Create((int8*)uiSSID, WLAN_WPA_AUTH_PSK, WLAN_ENCRYPT_TKIP, (int8*)uiPSW, chan, uiHideSSID);
        break;
    case 4:
        //sprintf( uiSSID, "AITAP-WPA2-TKIP" );
        err = WLAN_AP_Create((int8*)uiSSID, WLAN_WPA2_AUTH_PSK, WLAN_ENCRYPT_TKIP, (int8*)uiPSW, chan, uiHideSSID);
        break;
    default:
        //sprintf( uiSSID, "AITAP-NONE" );
        err = WLAN_AP_Create((int8*)uiSSID, WLAN_WPA_AUTH_NONE, WLAN_ENCRYPT_NONE, (int8*)uiPSW, chan, uiHideSSID);
        break;
    }

    printc("Create SW AP '%s' %s\r\n", uiSSID, (err == -1) ? "Failed" :  "Success");

    if (!DhcpIsServerStart()){
        DhcpServerSetToDefault();
        DhcpServerStart();
    }

    if (uiEnableWPS == 0)
        return ;

#ifdef WPS_AP_SUPPORT
    memset(&wps_config_info, 0, sizeof(wps_config_info));
    wps_config_info.WscMode = 0x02; //PBC

    switch (uiCrypto) {
    case 0:
    case 1:
        wps_config_info.WscSecurityMode = WPAPSKAES;
        break;
    case 3:
    case 4:
        wps_config_info.WscSecurityMode = WPAPSKTKIP;
        break;
    default:
        printc(" ERROR in CRYPTO \n");
        return;
    }
    // KEY
    wps_config_info.WpaPskLen = strlen(uiPSW);
    strncpy((char*)wps_config_info.WpaPsk, uiPSW, wps_config_info.WpaPskLen);
    // SSID
    wps_config_info.Ssid.SsidLength = strlen(uiSSID);
    strncpy((char*)wps_config_info.Ssid.Ssid, uiSSID, wps_config_info.Ssid.SsidLength);
    wps_config_info.channel = chan;
    wps_config_info.ssidBcst = 0;
    AP_StartWPS(&wps_config_info, NULL);
#endif
}

void UartCmd_GetConnectionInfo(char* szParam)
{
    WLAN_CONNECTION_INFO wlan_connection_info;
    UINT32 nrate;

    WLAN_STA_GetConnectedINFO(&wlan_connection_info);

    if(wlan_connection_info.Ssid_len == 32) {
        char ssid[33] = {0x00};

        memcpy(ssid, wlan_connection_info.Ssid, 32);
        printc("SSID: %s\n", ssid);
    } else
        printc("SSID: %s\n", wlan_connection_info.Ssid);

    printc("RSSI: %d dBm\n", wlan_connection_info.Rssi);
    printc("Channel: %d\n", wlan_connection_info.channel);


#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)
    nrate = wlan_connection_info.Phy_rate;
    printc("data rate %d%s Mbps\n", nrate/2, (nrate % 2)?".5":"");
#elif(WIFI_DRIVER_TYPE == WIFI_DRIVER_RTK)
    printc("Not support yet!\n");
#elif(WIFI_DRIVER_TYPE == WIFI_DRIVER_ATBM)
    printc("Not support yet!\n");
#else
    nrate = wlan_connection_info.Phy_rate & WLAN_NRATE_RATE_MASK;
    if (wlan_connection_info.Phy_rate & WLAN_NRATE_MCS_INUSE)//802.11n
        printc("mcs index %d\n", nrate);
    else//other
        printc("legacy rate %d%s Mbps\n", nrate/2, (nrate % 2)?".5":"");
#endif
}

void UartCmd_WL(char* szParam)
{
    char buf[10][50] = {"wl",};
    char *argv[10] = {NULL};
    char* ptr = szParam;
    int i=1, j=0, k=0;

    printc("szParam : %s \n", szParam);

    /* To skip the first space */
    ptr++;

    while(*ptr != '\0') {
        if(*ptr == ' ') {
            i++;
            j=0;
        } else
            buf[i][j++] = *ptr;

        ptr++;
    }

    if(strlen(szParam))
        i++;

    for(k=0;k<i;k++){

        argv[k] = buf[k];
        printc("buf[ %d ] : %s \n", k, &buf[k]);
    }

    WLU_MAIN_ARGS(10, argv);
}

void UartCmd_AssocList(char* szParam)
{
    char buf[1024];
    int i;
    WLAN_MACLIST *maclist = (WLAN_MACLIST*) buf;
    WLAN_ETHER_ADDR *ea;

    if(WLAN_AP_GetAssocList((int8*)buf, 1024) < 0) {
        printc("UartCmd_AssocList failed\n");
        return;
    }

    printc("maclist->count = %d\n", maclist->count);

    for (i = 0, ea = maclist->ea; i < maclist->count; i++, ea++){
        printc("%s\n", WLAN_ETHER_ETOA((struct  ether_addr*)ea));
    }
}

void UartCmd_WIFIGetMode(char* szParam)
{
    INT32 iStatus;

    iStatus = nhw_get_sys_mode();

    printc("Mode : %d \n", iStatus);
}

void UartCmd_LwIPMemAlloc(char* szParam)
{
    mem_size_t size;
    void* memptr;

    sscanfl( szParam, "%d", &size);

    memptr = mem_malloc(size);

    printc("memptr : %x, %d \n", memptr, size);

}

void UartCmd_LwIPMemFree(char* szParam)
{
    UBYTE* memptr;
    UINT32 value;
    sscanfl( szParam, "%x", &value);
    memptr = (UBYTE*)value;
    printc("memptr : %x, %x \n", memptr, value);
    mem_free(memptr);
}

void UartCmd_GetAPInfo(char* szParam)
{
    INT8 chSSID[32];
    WLAN_BSS_INFO sInfo;

    memset(chSSID, 0, 32);
    sscanfl( szParam, "%s", chSSID);

    printc("SSID : %s \n", chSSID);

    if(WLAN_STA_ScanAPbySSID((int8*)chSSID, &sInfo) == 0){
        printc("Success\n");

    }else{

        printc("Failed\n");
    }
}

void UartCmd_ScanNthAPInfo(char* szParam)
{
    uint32 uiIndex, uiCount;
    int8*  pchTempBuf;

    sscanfl( szParam, "%d", &uiIndex);

    printc("uiIndex : %d \n", uiIndex);

    WLAN_STA_AllocateScanBuf();
    pchTempBuf = WLAN_STA_ScanAPbyModule(&uiCount);

    WLAN_STA_GetScanResultByIndex(uiIndex, pchTempBuf);
    WLAN_STA_FreeScanBuf();
}

#if NCFG_WIFI_MFG_EN == 1

void UartCmd_EnterWiFiMFGMode(char* szParam)
{
    nhw_set_wifi_mfg(1);
}
/*
1. 11b TX test
    wlan_mfg_tx_bg(ch, WLM_RATE_11M, txpwr)
    - ch: channel number
    - txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)

2. 11g TX test
    wlan_mfg_tx_bg(ch, WLM_RATE_54M, txpwr)
    - ch: channel number
    - txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)
*/
void UartCmd_MFGTxBG(char* szParam)
{
    UINT32 uiChannel, uiRate, uiPowerValue;
    INT32  iError;

    sscanfl( szParam, "%d %d %d", &uiChannel, &uiRate, &uiPowerValue);

    printc("Ch : %d, Rate : %d, PowerValue : %d \n", uiChannel, uiRate, uiPowerValue);

    iError = WLAN_MFG_TxBG(uiChannel,uiRate, uiPowerValue);

    printc("Tx BG Status : %d \n", iError);
}

/*
3. 11n TX test
    wlan_mfg_tx_n(ch, WLM_MCS_RATE_7, txpwr)
    - ch: channel number
    txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)
*/
void UartCmd_MFGTxN(char* szParam)
{
    UINT32 uiChannel, uiRate, uiPowerValue;
    INT32  iError;

    sscanfl( szParam, "%d %d %d", &uiChannel, &uiRate, &uiPowerValue);

    printc("Ch : %d, Rate : %d, PowerValue : %d \n", uiChannel, uiRate, uiPowerValue);

    iError = WLAN_MFG_TxN(uiChannel,uiRate, uiPowerValue);

    printc("Tx N Status : %d \n", iError);
}

/*
4. RX test
    wlan_mfg_rx(ch)
    - ch: channel number

*/
void UartCmd_MFGRx(char* szParam)
{
    UINT32 uiChannel;
    INT32  iError;

    sscanfl( szParam, "%d ", &uiChannel);

    printc("Ch : %d \n", uiChannel);

    iError = WLAN_MFG_RX(uiChannel);

    printc("Rx Status : %d \n", iError);
}
/*
5. Get received packets
    wlan_mfg_rx_getpkt(&count)
    - count: received packet count
*/
void UartCmd_MFGRxGetPkt(char* szParam)
{
    UINT32 uiCount;
    INT32  iError;

    iError = WLAN_MFG_RxGetPkt(&uiCount);

    printc("RxGetPkt Status : %d, Count : %d \n", iError, uiCount);
}

/*
6. Non-modulation TX test
    wlan_mfg_carrier_tone(ch)
    - ch; channel number
*/
void UartCmd_MFGCarrierTone(char* szParam)
{
    UINT32 uiChannel;
    INT32  iError;

    sscanfl( szParam, "%d ", &uiChannel);

    printc("Ch : %d \n", uiChannel);

    iError = WLAN_MFG_CarrierTone(uiChannel);

    printc("CarrierTone Status : %d \n", iError);
}

/*
7. Stop MFG test
    wlan_mfg_stop()
*/
void UartCmd_MFGStop(char* szParam)
{
    INT32  iError;

    iError = WLAN_MFG_Stop();

    printc("Stop Status : %d\n", iError);
}

/*
 * 8. 11b Continuous TX test wlan_mfg_con_tx_bg(ch, WLM_RATE_11M, txpwr)
 * - ch: channel number - txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)
 * 9. 11g Continuous TX test wlan_mfg_con_tx_bg(ch, WLM_RATE_54M, txpwr)
 * - ch: channel number - txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)
*/
void UartCmd_MFGConTxBG(char* szParam)
{
    UINT32 uiChannel, uiRate, uiPowerValue; INT32 iError;

    sscanfl( szParam, "%d %d %d", &uiChannel, &uiRate, &uiPowerValue);
    printc("Ch : %d, Rate : %d, PowerValue : %d \n", uiChannel, uiRate, uiPowerValue);
    iError = WLAN_MFG_Con_TxBG(uiChannel,uiRate, uiPowerValue);
    printc("Continuous Tx BG Status : %d \n", iError);
}

/*
 * 10. 11n Continuous TX test wlan_mfg_con_tx_n(ch, WLM_MCS_RATE_7, txpwr)
 * - ch: channel number txpwr: -1 means default power or value in mili dBm (15000 for 15dBm)
 */
void UartCmd_MFGConTxN(char* szParam)
{
    UINT32 uiChannel, uiRate, uiPowerValue; INT32 iError;
    sscanfl( szParam, "%d %d %d", &uiChannel, &uiRate, &uiPowerValue);
    printc("Ch : %d, Rate : %d, PowerValue : %d \n", uiChannel, uiRate, uiPowerValue);
    iError = WLAN_MFG_Con_TxN(uiChannel,uiRate, uiPowerValue);
    printc("Continuous Tx N Status : %d \n", iError);
}
#endif

//Notice the prefix must be "wifi "
UARTCOMMAND sWiFiUartCommand[] = {
    { "netstart",      "",                 "start net(lwip only)",      UartCmd_NetStart},
    { "wlanstart",     "",                 "start wlan",                UartCmd_WlanStart},
    { "wlanstop",      "",                 "stop wlan",                 UartCmd_WlanStop},
    { "wlanscan",      "",                 "start wlan scan",           UartCmd_WlanScan},
    { "wlanjoin",       "",                "join a network",            UartCmd_Wlanjoinnetwork},
    { "ping",          "",                 "start pinging gateway",     UartCmd_Ping},
    { "version",       "",                 "get driver release version",UartCmd_GetVersion},
    { "wpsstart",      "",                 "start WPS",                 UartCmd_WPSSTART},
    { "wpsstatus",      "",                "WPS status",                UartCmd_WPSGetStatus},
    { "wpsstop",       "",                 "stop WPS",                  UartCmd_WPSStop},
    { "crswap",        "",                 "Create SW AP",              UartCmd_CreateSWAP},
    { "info",          "",                 "Get Connection Info",       UartCmd_GetConnectionInfo},
    { "wl",            "",                 "wl command",                UartCmd_WL},
    { "assoc",         "",                 "Get assoc list",            UartCmd_AssocList},
    { "wgetmode",      "",                 "wifi get mode",             UartCmd_WIFIGetMode},
    { "lwipalloc",             "",         "LwIP memalloc",             UartCmd_LwIPMemAlloc},
    { "lwipfree",          "",             "LwIP memfree",              UartCmd_LwIPMemFree},
    { "getap",             "",             "getap",                     UartCmd_GetAPInfo},
    { "apindex",           "",             "apindex",                   UartCmd_ScanNthAPInfo},
#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)
    { "mtkset",            "",             "apindex",                   mtkwifi_set_info},
    { "mtkget",            "",             "apindex",                   mtkwifi_get_info},
#endif
#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_RTK)
    { "rtktest",            "",             "rtk mp commands",          rtk_wifi_test},
    { "iwpriv",             "",             "rtk mp commands",          rtk_wifi_iwpriv},
#endif
#if NCFG_WIFI_MFG_EN == 1
    { "mfgen",             "",              "MFG Enable(Start MFG)",    UartCmd_EnterWiFiMFGMode},
    { "mfgtxbg",           "",              "MFGTxBG",                  UartCmd_MFGTxBG},
    { "mfgtxn",            "",              "MFGTxN",                   UartCmd_MFGTxN},
    { "mfgrx",             "",              "MFGRx",                    UartCmd_MFGRx},
    { "mfgrxgetpkt",       "",              "MFGTxxGetPkt",             UartCmd_MFGRxGetPkt},
    { "mfgcarriertone",    "",              "MFGCarrierTone",           UartCmd_MFGCarrierTone},
    { "mfgstop",           "",              "MFGstop",                  UartCmd_MFGStop},
    { "mfgcontxbg",         "",             "MFGContinuousTxBG",        UartCmd_MFGConTxBG},
    { "mfgcontxn",          "",             "MFGContinuousTxN",         UartCmd_MFGConTxN},
#endif
    {0,0,0,0}
};





