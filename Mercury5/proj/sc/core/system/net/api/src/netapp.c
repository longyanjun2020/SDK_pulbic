/**
@file netapp.c
  Created on: 2013/10/17
      Author: Truman

      This module centralized as bridge or fire wall interfaces.
      MMI, ASS, WLAN, LWIP, Net Daemon could be the "client module".
      The client module can set and get status with this module.
      The client module can post event here and the message would be dispatched to other modules.

      Because so many client modules belong to different layers or packages, there is no appropriate existing prefix
      for this. Since NetApp exists, it was used.

      Listed client modules:

      new naming:
      nhw: Network Hardware, which is WiFi now.
      ns:  Network Server, typically streaming server
      ncam: Network CAMera, called from other module to AHC or UI.
      ncgi: Network CGI. CGI is complex which might use CGI, AHC or UI function
      nui: Network UI. This typically with NUI_CALL that it would be project dependent and might not be implemented.
      netapp: Net APP for general system utilities

      obsolete naming:
      MMI: AHC_Main(33)
      ASS:
      WLAN: start->Network_Task(54)->tcp_init->tcp_thread(40) before the real TCP thread.
      LWIP: netif
      Net Daemon:
      Web Server:(UPNP) (41 or 42)->CONNECT(43~53)->handle request
      DHCP Server:(in LWIP package)
*/

#include "netapp.h"
#include "amn_cgi.h"
#include "wlan.h"
#include "netconf.h"
#include "dhcp_server.h"
#include "amnss_mmobjs.h"
#include "inet_pton.h"
#include "ahc_parameter.h"
//#include "all_fw.h"

/*testing*/
//#include "ahc_common.h" //for GPIO & AHC_SendAHLMessage


#include "osl_ext.h"
#include "net_utility.h"

#include "ahc_general.h" //for GPIO & AHC_SendAHLMessage
#include "ahc_stream.h"
#include "ahc_version.h" //for AHC_GetMinorVersion()
#include "ahc_dcf.h"
#if (HDMI_PREVIEW_EN)
#include "ahc_display.h"
#endif
#include "ahc_debugex.h"
#include "ahc_modectl.h"
#include "ahc_msgqueue.h"
#include "ahc_uf.h"
#include "keyparser.h"
#include "ahc_menu.h"
#include "ahc_wireless.h"
#include "ahc_warningmsg.h"
#include "statecamerafunc.h"
#include "statevideofunc.h"
#include "mmps_vidplay.h"
#include "ldws.h"
#include "snr_cfg.h"
#include "mmpf_usbh_uvc.h"

#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_BCM && NCFG_WIFI_MFG_EN)
static unsigned char gbEnterRFTestMode = 1;
#else
//For MTK solution,trigger by UART or UI
static unsigned char gbEnterRFTestMode = 0;
#endif

#define STD_CGI_TIME_OUT ((void*)6000)
/** @version 1.0 Original version from 8427 Car DV SDK.
 *  @version 1.1 Reference APP is using this version, includes new features for 8428.
 *  @version 1.2(Developing Release Candidate) New features for recent projects, which may not be included in
 *  Reference APP. Include customized broadcast messages.
 *
 *  <b> Current version: 1.2 </b>
 */
#define NCGI_VERSION (102) // Current CGI version 1.2 This is release candidate since reference APP is using 1.1.

/** These CGI_MENU_MAP and ncgi_get_menu are intentionally put here in a c file.
 *  These variables are shared ONLY between here and the c file in UI (probably MenuSetting.c)
 *  MenuSetting.c in each project MUST provides every map. Use an empty map if not supported.
 */
#define ncgi_get_menu(menu) CGI_MENU_##menu
extern CGI_MENU_MAP CGI_MENU_UI_STATE[];
extern CGI_MENU_MAP CGI_MENU_VIDEO_RES[];
extern CGI_MENU_MAP CGI_MENU_IMAGE_RES[];
extern CGI_MENU_MAP CGI_MENU_VIDEO_CLIP[];
extern CGI_MENU_MAP CGI_MENU_WB[];
extern CGI_MENU_MAP CGI_MENU_EXPO[];
extern CGI_MENU_MAP CGI_MENU_FLICKER[];
extern CGI_MENU_MAP CGI_MENU_MTD[];
extern CGI_MENU_MAP CGI_MENU_OFF_DELAY[];
extern CGI_MENU_MAP CGI_MENU_QUALITY[];
extern CGI_MENU_MAP CGI_MENU_TIME_FMT[];
extern CGI_MENU_MAP CGI_MENU_TV_SYSTEM[];
extern CGI_MENU_MAP CGI_MENU_LCD_POWER_SAVE[];
extern CGI_MENU_MAP CGI_MENU_PHOTO_BURST[];
extern CGI_MENU_MAP CGI_MENU_TIMELAPSE[];
extern CGI_MENU_MAP CGI_MENU_UPSIDE_DOWN[];
extern CGI_MENU_MAP CGI_MENU_SPOT_METER[];
extern CGI_MENU_MAP CGI_MENU_LOOPING_VIDEO[];
extern CGI_MENU_MAP CGI_MENU_HDR[];
extern CGI_MENU_MAP CGI_MENU_Q_SHOT[];
extern CGI_MENU_MAP CGI_MENU_STATUS_LIGHTS[];
extern CGI_MENU_MAP CGI_MENU_SOUND_INDICATOR[];
extern CGI_MENU_MAP CGI_MENU_POWER_SAVING[];
extern CGI_MENU_MAP CGI_MENU_SD0[];
extern CGI_MENU_MAP CGI_MENU_GSENSOR[];
#if(AHC_USER_SFBACKUP)
extern volatile AHC_USERFAT_PARTITION   ulSFUSERActiveNO;
#endif

//Using this to hint that this function is used only by netapp.c and cgi_main.c for CGI
#define CGI_RW //Supports read and write. This function should be in both netapp.c and cgi_main.c
#define CGI_WO //Supports write only.     This function should be only in netapp.c case there is no getter function.

// Functions for conversion of BootUpMode index and ID
//UINT8 CameraSettingsFunc_GetBootUpUIState( UINT8 uiBootUpMode ); //Andy Liu TBD
//UINT8 CameraSettingsFunc_GetBootUpMode( UINT8 uiUIState ); //Andy Liu TBD

#define CGIOP_DBG_INFO (1) //info about CGI wait and feed back, it's a independent setting from CGIOP_DBG
#if CGIOP_DBG
struct ncgi_ret ncgi_send_ui_msg_dbg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, void *arg, char* func, int line);
struct ncgi_ret ncgi_send_ui_std_msg_dbg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, PFN_CGI_OP_CALLBACK pfn_s, char* func, int line);
#define ncgi_send_ui_msg(msg, p1, wait, arg) ncgi_send_ui_msg_dbg(msg, p1, wait, arg, __FUNCTION__, __LINE__)
#define ncgi_send_ui_std_msg(msg, p1, wait, pfn_s) ncgi_send_ui_std_msg_dbg(msg, p1, wait, pfn_s, __FUNCTION__, __LINE__)
#else
struct ncgi_ret ncgi_send_ui_msg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, void *arg);
struct ncgi_ret ncgi_send_ui_std_msg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, PFN_CGI_OP_CALLBACK pfn_s);
#endif

#if 0
void ____nui____() {} //dummy. Network User Interface. Functions that controls network hardware
#endif

/*
 * Get which SET for WiFi AP used.
 * return 0 or 1 for AP configuration set 0 or 1
 */
int ncam_get_ui_ap_setting(void)
{
    printc(">>>>> %s,%d Wifi TBD. <<<<<\r\n",__func__,__LINE__); //Andy Liu TBD
    return 0;
    //return (MenuSettingConfig()->uiWirelessStatus == WIRELESS_STATUS_REMOTE)? 1 : 0;
}


#if 0
void ____nhw____() {} //dummy. Network Hard-Ware. Functions that controls network hardware
#endif

typedef struct  {
    uint8       mac[6];
}STA_MAC;

typedef struct {
    uint8       ulnumofconnSTA;
    STA_MAC     aConnectedSTATAddrable[NCFG_WIFI_MAX_CONNECTION];

} AP_MODE_STA_INFO;

#define NET_MAC_IS_ZERO(m)      (m[0]==0 && m[1]==0 && m[2]==0 && m[3]==0 && m[4]==0 && m[5]==0)
#define NET_COMPARE_MAC(m1,m2)  (m1[0]==m2[0] && m1[1]==m2[1] && m1[2]==m2[2] && m1[3]==m2[3] && m1[4]==m2[4] && m1[5]==m2[5])
static int      gbAllowAppAccss = 0;
static int      g_WifiTargetMode = NETAPP_WIFI_AP_MODE;
static int      _format_sd = FORMAT_SD_NONE;
static uint8    g_astreamingmac[] = {0,0,0,0,0,0};
nhw_drv_hdl     g_hdl = NULL;
MMPF_OS_SEMID   g_assocsemi = 0xff;
static AP_MODE_STA_INFO gsSTAinfo;

void nhw_init_ap_check_assoc(void)
{
    memset(&gsSTAinfo,0,sizeof(AP_MODE_STA_INFO));

    if(g_assocsemi != 0xff){
        g_assocsemi = MMPF_OS_CreateSem(1);
        if(g_assocsemi >= 0xfe)
            printc(FG_RED("create g_assocsemi error!\n"));
    }
}

/*
@return
        0   : a vailed MAC
        -1  : a duplicated MAC
*/
int nhw_add_connected_sta(unsigned char * mac)
{
    int i;

    if(!mac)
        return 0;

    //Scan if there is the same MAC in DRAM
    for(i = 0 ; i < NCFG_WIFI_MAX_CONNECTION ;i++){
        if(NET_COMPARE_MAC(gsSTAinfo.aConnectedSTATAddrable[i].mac,mac)){
            printc("Warning : A duplicated MAC!\n");
            return -1;
        }
    }

    //Search a empty one to record MAC
    for(i = 0 ; i < NCFG_WIFI_MAX_CONNECTION ;i++){
        if(NET_MAC_IS_ZERO(gsSTAinfo.aConnectedSTATAddrable[i].mac)){
            memcpy(gsSTAinfo.aConnectedSTATAddrable[i].mac,mac,6);
            gsSTAinfo.ulnumofconnSTA++;
            return 0;
        }
    }

    return 0;
}

void nhw_remove_disconnected_sta(unsigned char * mac)
{
    int i;

    if(!mac)
        return;

    if(gsSTAinfo.ulnumofconnSTA == 0)
        return;

    for(i = 0 ; i < NCFG_WIFI_MAX_CONNECTION ;i++){
        if(NET_COMPARE_MAC(gsSTAinfo.aConnectedSTATAddrable[i].mac,mac)){
            memset(gsSTAinfo.aConnectedSTATAddrable[i].mac,0,6);
            gsSTAinfo.ulnumofconnSTA -- ;
            return;
        }
    }
}

/** @brief      Check current connected STAs and update it into DRAM.
 *
 *  @param[in]  curmaclist       A pointer of the memory which contain current scanned STA's MAC
 *  @param[in]  curlistcount        The number of scanned STA for param 1
 *  @param[out] leavemaclist    A pointer of the caller's memory which will be fill with leaving STA's MAC list
 *  @return         The number of disconnected STA in result.
 */
int nhw_check_sta_leave(unsigned char * curmaclist ,unsigned char curlistcount, unsigned char * leavemaclist)
{
    int     i, leavecnt;
    uint8   *pcmpmac, *pleavemac;

    if(!curmaclist || !leavemaclist){
        printc("do nothing in nhw_check_sta_leave\n");
        return 0;
    }

    if(gsSTAinfo.ulnumofconnSTA == 0)
        return 0;

    leavecnt = 0;
    pleavemac = leavemaclist;

    for(i = 0 ; i < NCFG_WIFI_MAX_CONNECTION ;i++)
    {
        int j;
        uint8 bmatched = 0;

        if(NET_MAC_IS_ZERO(gsSTAinfo.aConnectedSTATAddrable[i].mac))
            continue;

        for(j = 0 ; j < curlistcount ; j++){

            pcmpmac = curmaclist + (j * 6);

            if(NET_COMPARE_MAC(gsSTAinfo.aConnectedSTATAddrable[i].mac,pcmpmac)){
                bmatched = 1;
                break;
            }
        }

        if(0 == bmatched){
            //Add mac from gsSTAinfo.aConnectedSTATAddrable[i].mac into leavemaclist
            memcpy(pleavemac,gsSTAinfo.aConnectedSTATAddrable[i].mac,6);
            leavecnt ++;
            pleavemac += 6;
        }

    }

    return leavecnt;
}

void nhw_set_streaming_mac(unsigned char * mac)
{
    memcpy(g_astreamingmac,mac,6);

    {
        int i ;
        printc("Streaming MAC : ");
        for(i=0;i<6;i++)
            printc("%02x ",g_astreamingmac[i]);
        printc("\r\n");
    }
}

void nhw_get_streaming_mac(unsigned char * mac)
{
    memcpy(mac,g_astreamingmac,6);
}

/*
*return 0 if mac matched,ow return -1
*/
int nhw_cmp_streaming_mac(unsigned char * mac)
{
    int i = 0;
    for(; i < 6 ;i++)
        if(mac[i] != g_astreamingmac[i])
            return -1;
    return 0;
}

void nhw_set_handle(nhw_drv_hdl h)
{
    g_hdl = h;
}

nhw_drv_hdl* nhw_get_handle()
{
    return g_hdl;
}

static int  _netappstatus = NETAPP_NET_STATUS_NONE;
static int  _netstreamingstatus = NETAPP_STREAM_NONE;

#ifndef _NETAPP_DEBUG
int nhw_set_status(int status)
{
    return (_netappstatus = status);
}
#else
int nhw_set_status_dbg(int status, char *file, int line)
{
    printc("nhw_set_status_dbg: %s %d 0x%08x\r\n", file, line, status);
    return (_netappstatus = status);
}
#endif

int nhw_get_status(void)
{
    return _netappstatus;
}


int ns_set_streaming_status(int status)
{
#ifdef _NETAPP_DEBUG
    printc("ns_set_streaming_status : 0x%08x => 0x%08x\r\n",_netstreamingstatus, status);
#endif
    if(status == NETAPP_STREAM_NONE || status == NETAPP_STREAM_TEARDOWN)
        return (_netstreamingstatus = status);
    else
        return (_netstreamingstatus |= status);
}

int ns_get_streaming_status(void)
{
    return _netstreamingstatus;
}

int nhw_get_sys_mode(void)
{
    return (int)WLAN_SYS_GetMode();
}

extern MMPF_OS_FLAGID   Network_Flag;
int nhw_send_event(unsigned int event)
{
    return (int)MMPF_OS_SetFlags(Network_Flag, event, MMPF_OS_FLAG_SET);
}

int nhw_wifi_link_report(int updown)
{
    if(updown)
        return (int)SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_WIFILINK_IND);
    else
        return (int)SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_WIFILINK_DOWN_IND);
}

int nhw_init_network(void)
{
    AHC_BOOL ret;
    ret = uiRegisterNetworkCallback();
    if (ret != AHC_TRUE) {
        printd(BG_RED("Unable to register network callbacks")"\r\n");
        //still continue network init
    }
    return (int)SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_INIT);
}

int nhw_stop_network(void)
{
    return (int)SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_UNIN);
}

int nhw_reset_network(void)
{
    return (int)SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_RESET);
}

int nhw_cmd_network(void)
{
    return (int)SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_CMD);
}

#if NHW_PANA_RULE
static enum nhw_auto_chan_rule_t gAutoChRule = NHW_AUTO_CHANNEL_AIT_RULE;

void nhw_set_auto_chan_rule(enum nhw_auto_chan_rule_t rule)
{
    gAutoChRule = rule;
}


enum nhw_auto_chan_rule_t nhw_get_auto_chan_rule(void)
{
    return gAutoChRule;
}
#endif

static enum nhw_country_chan_t gWifiCountry = NHW_COUNTRY_ALL;
void nhw_set_country(enum nhw_country_chan_t country)
{
    gWifiCountry = country;
}

enum nhw_country_chan_t nhw_get_country(void)
{
    return gWifiCountry;
}

struct net_context_t *load_netconfig(int *isap);
int load_wificonfig(int apset, char **pssid, int *pcrypto, char **pckey, int *hidden, int *pchan);
extern struct netif main_netdev;//in lwip_main.c
//extern int gbWifiConnect;//in wlan

/***********************************************************************************************/
//      function: TurnOffWiFiModule()
//   description: To turn off the WiFi module..
//      input   : none.
/***********************************************************************************************/
//currently called in AHC_Main UI
int nhw_turn_off_wlan(void)
{
    return nhw_stop_network();
/*
    netif_set_down(&main_netdev);
    WLAN_SYS_Stop(g_hdl);
    nhw_set_status(NETAPP_IDLE);
    gbWifiConnect = 0;
    return 0;
*/
}

/***********************************************************************************************/
//      function: nhw_turn_on_wlan()
//   description: To turn on the WiFi module..
//      input   : none.
/***********************************************************************************************/
//currently called in AHC_Main UI
int  nhw_turn_on_wlan(void)
{
    struct net_context_t *thenet;
    int     isap;
    char    *ssid, *ckey;
    int     hidden, crypto, chan, auth, enc;
    int     err;

//function in lwip_main.c, return type in Firmware/lwip/port/include/netconf.h(Firmware/NET/Common/netconfig.c)
    if ((thenet = load_netconfig(&isap)) == NULL)
        return -1;

//function in netif.c, Firmware/lwip/port/include/netif.h
//main_detdev (handle) in lwip_main.c
    if (isap) {
        int     apset;
        netif_set_addr(&main_netdev, &thenet->local_ip,
                                     &thenet->net_mask,
                                     &thenet->gateway_ip);
        netif_set_up(&main_netdev);
        apset = ncam_get_ui_ap_setting();

        //must before "load_wificonfig",or auto-channel will not be execute!
        g_hdl = WLAN_SYS_Start();

        load_wificonfig(apset, &ssid, &crypto, &ckey, &hidden, &chan);
        DhcpServerSetToDefault();
        DhcpServerStart();

    // handle in ahc_netmain.c

        printc("wlan_start g_hdl = 0x%x\r\n", g_hdl);
        printc("Create SW AP : ");
        LwIP_convert_WLAN_crypto( crypto, &auth, &enc );
        err = WLAN_AP_Create( (int8*)ssid, auth, enc, (int8*)ckey, chan, hidden);
        return (int)err;
    }else{
        //TODO
        //if IP is STATIC type ,set netif here
        /*netif_set_addr(&main_netdev,
                    &thenet->local_ip,
                    &thenet->net_mask,
                    &thenet->gateway_ip);
        netif_set_up(&main_netdev);*/

        //Titan : WLAN_SYS_Start has done in load_netconfig,call it twice will cause SDIO failed.
        //g_hdl = WLAN_SYS_Start();
        //printc("wlan_start g_hdl = 0x%x\r\n", g_hdl);
    }
//move to WLAN_SYS_Start(), it's GB9616 code
#if 0
    //FIXME GB9616 dependent or Wifi spec dependent?
    AHC_OS_SleepMs(200);
    //FIXME GB9616 dependent?
    AHC_GPIO_SetData(NCFG_RESET_PIN, AHC_TRUE);
#endif
    return 0;
}

/* get wifi STA connection strength, only support in STA mode --
---return value should be -20~-110 dB */
int nhw_get_sta_rssi(void)
{
    WLAN_CONNECTION_INFO info;
    if (WLAN_STA_GetConnectedINFO(&info)==0)
    {
        return info.Rssi;
    }
    return 0;
}

/*
 * Broadcast SSID or not
 * return 1 : OK
 *        0 : FAILED
 */
int nhw_broadcast_ssid(int enable)
{
    #define SSID_BROADCAST  0
    #define SSID_HIDDEN     1
    extern int wlmClosedSet(int val);
    return wlmClosedSet((enable == 0)? SSID_HIDDEN : SSID_BROADCAST);
}

static MMP_UBYTE netapp_mac[6];

void nhw_get_wifi_mac(MMP_UBYTE* addr)
{
	nhw_drv_hdl hdl;

	if(netapp_mac[0] && netapp_mac[1] && netapp_mac[2])
	{
		memcpy(addr,netapp_mac,6);
		return;
	}

	if(WLAN_SYS_IsStart())
	{
		WLAN_SYS_GetMacAddr(netapp_mac);
	}
	else
	{
		WLAN_SYS_InitHw();

		if(!mem_is_ready())
		{
			mem_init();
			sys_init();
		}

		hdl = WLAN_SYS_Start();

		if(hdl){

			WLAN_SYS_GetMacAddr(netapp_mac);
			WLAN_SYS_Stop(hdl);
		}
	}

	memcpy(addr,netapp_mac,6);
}

/*
 * return 1: AP mode (NETAPP_WIFI_AP_MODE)
 *        2: STA mode (NETAPP_WIFI_STATION_MODE)
 */
int nhw_get_cur_wifi_mode(void)
{
    return net_context.mode;
}

/*
 * return 1: AP mode(NETAPP_WIFI_AP_MODE)
 *        2: STA mode(NETAPP_WIFI_STATION_MODE)
 */
int nhw_get_target_wifi_mode(void)
{
    return g_WifiTargetMode;
}
/*
 * mode     1: AP mode (NETAPP_WIFI_AP_MODE)
 *          2: STA mode (NETAPP_WIFI_STATION_MODE)
 */
int nhw_set_wifi_mode(int mode)
{
    g_WifiTargetMode = mode;
    return 0;
}

/*
 * return unsigned int (little endian) for ipv4
 *        ip: xxx.xxx.xxx.xxx = byte0.byte1.byte2.byte3
 */
unsigned int nhw_get_ip_addr(void)
{
    return main_netdev.ip_addr.addr;
}

static void wps_event_callback(WLAN_WPS_STATE event)
{
    printc("WPS CB : %d : ", event);

    switch(event){

    case WLAN_WPS_STATE_OFF:
        if(WLAN_WPS_Enable())
            AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_NETWORK_WPS_FAIL, 0 );
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

//net hardware, start station mode WPS
int nhw_start_sta_wps(void)
{
    if(network_init_done()){

        WLAN_WPS_CONFIG wpsConfigInfo;

        wpsConfigInfo.WscMode       = 2;            /* 1: PIN, 2:PBC */
        wpsConfigInfo.JoinAP        = 1;            /* 0: Not to join AP, 1: to join AP */
        wpsConfigInfo.ScanBufSize   = 32*1024;      //32KB
        wpsConfigInfo.AssocAPTime   = 20000;        //20s

        /* Prevent DHCP client from starting up
        at the first time WPS procedure use probe request of WPS protocol to connect to AP*/
        IP4_ADDR(&net_context.local_ip,   10,10,10,10);

        WLAN_WPS_Start(&wpsConfigInfo, (void*)wps_event_callback);
        return 0;
    }
    else{
        return -1;
    }
}

int nhw_reset_wps_info(void)
{
    *amn_currConfig_get("Net.WIFI_STA.AP.1.SSID")->v.strVal = 0;
    *amn_currConfig_get("Net.WIFI_STA.AP.1.EncType")->v.strVal = 0;
    *amn_currConfig_get("Net.WIFI_STA.AP.1.CryptoKey")->v.strVal = 0;
    DelWlanFavAP_idx(0);
    return 0;
}

int nhw_is_wps_paired(void)
{
    return *amn_currConfig_get("Net.WIFI_STA.AP.1.SSID")->v.strVal;
}

static void* auto_join_job(void *arg)
{
    LwIP_join_WLAN_auto(1);
    return NULL;
}

int nhw_auto_join_ap(void)
{
    add_NetworkJob(auto_join_job, NULL, 1);
    kick_NetworkJob();
    return 0;
}

void nhw_set_wifi_mfg(unsigned char enable)
{
    gbEnterRFTestMode = enable;
}

unsigned char nhw_get_wifi_mfg(void)
{
    return gbEnterRFTestMode;
}

#if 0
void ____ncam____() {} //dummy. Net Camera. Functions that controls the device (AHC/UI)
#endif

/*
 * return Camera Status, bit0 - 1 for video recording.
 */
int ncam_get_app_status(void)
{
    int     status;

    status  = 0;
    status |= ncam_is_recording()? 1 : 0;
    return status;
}


/**
 *
 * It uses virtual key so that all UI job and GUI drawing would be the the same as Human UI controlling.
 * Later it would need to use other task to turn on the streaming.
 *
 * @param enable 1 to turn on the streaming. 0 to turn off the streaming
 * @retval 1 The request is processed.
 * @retval 0 The request is ignored because it does not require changing.
 * @retval <-1 Other error.
 */
extern int transcoding;
int ncam_set_streaming(short enable)
{
    bool    bOn;
    char    *wl_cmd;
    AHC_STREAMING_MODE  stmode;

    stmode = AHC_GetStreamingMode();
    if (stmode == AHC_STREAM_OFF) {
        if (!AHC_IsInVideoMode() && !transcoding) return -1;
    }
    if (!aitstreamer_is_ready())
        return -2;

    bOn = ns_get_streaming_status() & NETAPP_STREAM_PLAY;
    if(!bOn && enable) {
        wl_cmd = "VIDEO.0/EncMJPEG";
    } else if (!enable) {
        wl_cmd = "none";
    } else {
        return 0;
    }
    aitstreamer_run(wl_cmd);
    return 1;
}


//get current record mode status.
int ncam_is_recording(void)
{
    return VideoFunc_GetRecordStatus();
}

// Get timestamp of still capture capturing
int ncam_is_capturing(void)
{
    return 0;
}

// If HDMI is connected
int ncam_is_hdmi_on(void)
{
#if (HDMI_PREVIEW_EN)
    return AHC_IsHdmiConnect();
#else
    return 0;
#endif
}

int ncam_is_h264_streaming_supported(void)
{
    return 1;
}

//get value of year from RTC time.
int ncam_get_rtc_year()
{
    AHC_RTC_TIME sRtcTime;
    AHC_RTC_GetTime(&sRtcTime);

    return sRtcTime.uwYear;
}

//get value of month from RTC time.
int ncam_get_rtc_month()
{
    AHC_RTC_TIME sRtcTime;
    AHC_RTC_GetTime(&sRtcTime);

    return sRtcTime.uwMonth;
}

//get value of day from RTC time.
int ncam_get_rtc_day()
{
    AHC_RTC_TIME sRtcTime;
    AHC_RTC_GetTime(&sRtcTime);

    return sRtcTime.uwDay;
}

//get value of hour from RTC time.
int ncam_get_rtc_hour()
{
    AHC_RTC_TIME sRtcTime;
    AHC_RTC_GetTime(&sRtcTime);

    return sRtcTime.uwHour;
}

//get value of minute from RTC time.
int ncam_get_rtc_minute()
{
    AHC_RTC_TIME sRtcTime;
    AHC_RTC_GetTime(&sRtcTime);

    return sRtcTime.uwMinute;
}

//get value of second from RTC time.
int ncam_get_rtc_second()
{
    AHC_RTC_TIME sRtcTime;
    AHC_RTC_GetTime(&sRtcTime);

    return sRtcTime.uwSecond;
}

// get version
//char* AHC_CB_GetFwVersion(void) __attribute__((weak));
WEAK_FUNC(char* AHC_CB_GetFwVersion(void));
const char* ncam_get_fw_version(void)
{
    #define MAX_VERSION_LEN 20
    static char version[MAX_VERSION_LEN] = {0};
    char    *ver;
    int     l;

    if (version[0] != 0) return version;
    l = 0;
    if (AHC_CB_GetFwVersion) {
        ver = AHC_CB_GetFwVersion();
        for (; *ver != '\0'; ver++) {
            if (isdigit((int)*ver)) {
                version[l++] = *ver;
            }
        }
    }
    snprintf(version + l, MAX_VERSION_LEN - 1 - l, "%04d", AHC_GetMinorVersion());
    return version;
}

int ncam_get_mjpeg_bitrate(void)
{
    UINT32 bitrate;
    UINT32 codecType;
    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_CODEC_TYPE, &codecType);
    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_BITRATE, &bitrate);
    if ((codecType == AHC_MOVIE_VIDEO_CODEC_MJPEG) || (codecType == AHC_MOVIE_VIDEO_CODEC_YUV422)) {
        return bitrate;
    }
    else {
        //default bitrate, make it weird so that we could tell it's default value
        printc("\r\n codec Type %d\r\n", codecType);
        return 4000001;
    }
}

int ncam_get_mjpeg_res(unsigned short *w, unsigned short *h, char *name)
{
    int ret = 0;
    int conf_w, conf_h;

    ret = ncfg_get_v_res("Camera.Preview.MJPEG", &conf_w, &conf_h);
    //ncgi_cfg_get("Camera.Preview.MJPEG.w", &conf_w);
    //ncgi_cfg_get("Camera.Preview.MJPEG.h", &conf_h);
    if (ret == 0) {
        AHC_AdjustMJpegStreamResFromSnr(conf_w, conf_h, w, h);
        printc(">>>> CGI Get %s %d %d\r\n", name, *w, *h);
    }
    return ret;
}

/** @brief Get H.264 resolution used in Encoder
 *
 * @param[out] w Width used in encoder.
 * @param[out] h Height used in encoder.
 * @param[out] cropBottom Cropping in pixels
 * @param[out] cropRight Cropping in pixels.
 * @return 0 for success. -1 for fail.
 */
int ncam_get_h264_res(unsigned short *w, unsigned short *h, unsigned short *cropBottom, unsigned short *cropRight)
{
#if (SUPPORT_H264_WIFI_STREAM)
    UINT16 mmpResIdx;
    int conf_w, conf_h;

    if (ncfg_get_h264_res(&conf_w, &conf_h) < 0) {
        return -1;
    }

    *w = (unsigned short) conf_w;
    *h = (unsigned short) conf_h;

    if (AIHC_CalH264EncResolution(w, h, cropBottom, cropRight, &mmpResIdx) == AHC_TRUE) {
        return 0;
    }
#endif
    return -1;
}

static ncam_val_t m_values[NCS_MAX] = {
    {VALUE_TYPE_INT, {NCS_AUDIO_SAMPLING_RATE}},
    {VALUE_TYPE_INT, {NCS_AUDIO_PREVIEW}},
    {VALUE_TYPE_STR, {NCS_TRANSCODE_FILE_NAME}},
    {VALUE_TYPE_INT, {NCS_FILE_DURATION}}
};

int ncam_get_setting(enum ncam_setting_t setting, ncam_val_t* v)
{
    if (NULL == v) {
        return 0;
    }
    if (setting >= NCS_MAX) {
        printc("Invalid net app get setting:%d\r\n", setting);
        v->type = VALUE_TYPE_UNDEFINED;
        v->v.ptr = NULL;
        return 0;
    }

    v->type = m_values[setting].type;
    switch(setting) {
    case NCS_AUDIO_SAMPLING_RATE:
        //m_values[setting].v.i32 = AHC_VIDEO_GetDefaultAudioSamplingRate();
        break;
    default:
        break;
    }

    v->v = m_values[setting].v;
    return 1;
}

int ncam_set_setting(enum ncam_setting_t setting, ncam_val_t* v)
{
    if (NULL == v) {
        return 0;
    }
    if (setting >= NCS_MAX) {
        printc("Invalid net app set setting:%d\r\n", setting);
        return 0;
    }
    if (v->type != m_values[setting].type) {
        printc("unmatched net app setting:%d type %d, expected type %d\r\n", setting, v->type, m_values[setting].type);
        return 0;
    }

    m_values[setting].v = v->v;


    //add special post setting code here
    switch(setting) {
    //case NADS_AUDIO_PREVIEW:
    //    break;
    default:
        break;
    }
    return 1;
}

/*
 * FIXME: Truman: This function is tricky.
 * Because this function is called from HTTP request handing task (CGI task),
 * It should send message to UI and let UI decide which state supports this streaming mode attachment.
 * Here it attach sub mode Streaming.
 *
 * Would it be thread-safe problem? since it changes
 *
 * @note same thing happens in ncgi_send_ui_event()
 */
int ncam_enable_ui_streaming_mode(unsigned int mode)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT8 ubCurUIState = 0;
    UI_STATE_ID sParentUIStateID;

    ubCurUIState = uiGetCurrentState();
    StateModeGetParent(ubCurUIState, &sParentUIStateID);

    if(UI_NET_STREAMING_STATE != ubCurUIState){
        UI_STATE_ID ubParentUIState = 0;

        StateModeGetParent(ubCurUIState, &ubParentUIState);

        if((UI_NET_CGICMD_STATE == ubCurUIState) && ((UI_VIDEO_STATE == ubParentUIState) || (UI_CAMERA_STATE == ubParentUIState))){
            //Now is in Net CGI cmd mode. Dettach it.
            ahcRet = StateDetachSubMode();
            if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); return -1;}
        }
        else if((mode | AHC_STREAM_TRANSCODE) && (UI_NET_PLAYBACK_STATE == ubCurUIState || UI_BROWSER_STATE == ubCurUIState)){
            if(sParentUIStateID != UI_STATE_UNSUPPORTED){
                ahcRet = StateDetachSubMode();
                if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); return -1;}
            }
        }
        else if(!((UI_VIDEO_STATE == ubCurUIState) || (UI_CAMERA_STATE == ubCurUIState))){
            //Only Video and camera mode can be attached by Wifi streaming mode.
            AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); return -1;
        }

        ahcRet = StateAttachSubMode(UI_NET_STREAMING_STATE);
    #if defined(DBG_UI_NET_EVENT) && DBG_UI_NET_EVENT
        printd(BG_RED("attach streaming mode")"\r\n");
    #endif
        if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); return -1;}
    }
    return 0;
}

void acquire_streaming_and_cgi_op(void);
void release_streaming_and_cgi_op(void);
#if 1//new
/** @brief Set AHC streaming and wait for the result
*/
int ncam_set_streaming_mode(unsigned int mode)
{
    int iNetRet = -1;

#if 0
	if (TASK_AHC_INIT_PRIO == AHC_DBG_GetCurPrioEx()) {
		printc(FG_YELLOW("[WARN] %s should not be called in AHC_Main_Task."
						 " Please call AHC_SetStreamingMode() instead.\r\n"), __FUNCTION__);
	}
#endif

    //SZ version.
    if((AHC_STREAM_OFF == AHC_GetStreamingMode()) && (AHC_STREAM_OFF == mode)){
        printc(FG_RED("%s, redundent stop! NOP!")"\r\n", __FUNCTION__);
        iNetRet = 0;
        return iNetRet;
    }

    acquire_streaming_and_cgi_op();

    if (ncam_enable_ui_streaming_mode(mode) < 0) {
        release_streaming_and_cgi_op();
        return iNetRet;
    }

    //The object case, send the message, and wait for the result
    //wait the response that depends on return value of AHC_SetStreamingMode()

    if (NETAPP_DONE ==
        ncgi_send_ui_msg(WIRELESS_SET_STREAMING_MODE,
                        mode,
                        wait_streaming_op_uiproc,
                        STD_CGI_TIME_OUT).netapp){
        iNetRet = 0; //return 0;
    }
    else{
        printc(FG_RED("%s failed")"\r\n", __FUNCTION__);
        iNetRet = -1;//return -1;
    }

    release_streaming_and_cgi_op();
    //Because currently there could be error until almost the last step of start streaming,
    //the step could not simply check->send_event->report success->leave.
    //The streaming-start allocates the memory in starting, and it could be error there.

    return iNetRet;
}
#else//old
/** @brief Set AHC streaming and wait for the result
*/
int ncam_set_streaming_mode(unsigned int mode)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT8 ubCurUIState = 0;
    int iNetRet = -1;

#if 0
	if (TASK_AHC_INIT_PRIO == AHC_DBG_GetCurPrioEx()) {
		printc(FG_YELLOW("[WARN]"__FUNCTION__" should not be called in AHC_Main_Task."
						 " Please call AHC_SetStreamingMode() instead.\r\n"));
	}
#endif

#if 0//direct calls the function
    if (AHC_SetStreamingMode(mode) == AHC_TRUE) {
        return 0;
    }
#else

    //SZ version.
    if((AHC_STREAM_OFF == AHC_GetStreamingMode()) && (AHC_STREAM_OFF == mode)){
        printc(FG_RED(__FUNCTION__ ", redundent stop! NOP!")"\r\n");
        iNetRet = 0;
        return iNetRet;
    }

    ubCurUIState = uiGetCurrentState();
    if(UI_NET_STREAMING_STATE != ubCurUIState){
        UI_STATE_ID ubParentUIState = 0;

        StateModeGetParent(ubCurUIState, &ubParentUIState);

        if((UI_NET_CGICMD_STATE == ubCurUIState) && ((UI_VIDEO_STATE == ubParentUIState) || (UI_CAMERA_STATE == ubParentUIState))){
            //Now is in Net CGI cmd mode. Dettach it.
            ahcRet = StateDetachSubMode();
            if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); return iNetRet;}
        }
        else if(!((UI_VIDEO_STATE == ubCurUIState) || (UI_CAMERA_STATE == ubCurUIState))){
            //Only Video and camera mode can be attached by Wifi streaming mode.
            AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); return iNetRet;
        }

        ahcRet = StateAttachSubMode(UI_NET_STREAMING_STATE);
        if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); return iNetRet;}


    }

    //The object case, send the message, and wait for the result
    //wait the response that depends on return value of AHC_SetStreamingMode()

    if (NETAPP_DONE ==
        ncgi_send_ui_msg(WIRELESS_SET_STREAMING_MODE,
                        mode,
                        wait_streaming_op_uiproc,
                        STD_CGI_TIME_OUT).netapp){
        iNetRet = 0; //return 0;
    }
    else{
        printc(FG_RED(__FUNCTION__ " failed")"\r\n");
        iNetRet = -1;//return -1;
    }


#if 0 //TBD
    if (NETAPP_DONE ==
        ncgi_send_ui_msg(WIRELESS_SET_STREAMING_MODE,
                        mode,
                        wait_streaming_op_uiproc,
                        STD_CGI_TIME_OUT).netapp)
    {
        return 0;
    }
    else
    {
		printc(FG_RED(__FUNCTION__ " failed")"\r\n");
        return -1;
    }
#endif
    //Because currently there could be error until almost the last step of start streaming,
    //the step could not simply check->send_event->report success->leave.
    //The streaming-start allocates the memory in starting, and it could be error there.
#endif

    return iNetRet;
}
#endif

int ncam_del_file(char *path)
{
    char    *ptr;

    ptr = strrchr(path, '\\');
    if (!ptr) return -1;
    *ptr = 0;
    ptr++;
    return (AHC_UF_FileOperation((unsigned char*)path,
                                  (unsigned char*)ptr,
                                  DCF_FILE_DELETE_ALL_CAM,
                                  NULL, NULL) != 0)? 0 : -1;
}

#define MAX_PATH_LEN 64
int ncam_check_filelock(char *path)
{
    static char gadelfile[MAX_PATH_LEN] ;
    strcpy(gadelfile, path);
    return AHC_DCFDT_IsReadOnlybyFilename(gadelfile);
}

//Turn a time string into an integer
void ncam_parse_date_time(int* datetime, char* timestr)
{
    int     i;
    char    *tok;

    //Year/Month/Day/Hour/Minute/Second
    tok = strtok(timestr, "$");
    for (i = 0; i < 6 && tok != NULL; i++) {
        datetime[i] = atoi(tok);
        tok = strtok(NULL,"$");
    }
    for (; i < 6; i++) datetime[i] = 0;
    //printc("netapp_DateTime_Parser : %d %d %d %d %d %d\r\n",datetime[0],datetime[1],datetime[2],datetime[3],datetime[4],datetime[5]);
}

//identify the sensor is working or not
// TODO: review it, Canlet
const char* ncam_get_sensor_status()
{
    AHC_MODE_ID mode;

    mode = AHC_GetAhcSysMode();
    switch (mode) {
    case AHC_MODE_VIDEO_RECORD:
    case AHC_MODE_RECORD_PRERECD:
    case AHC_MODE_RECORD_PREVIEW:
        return "Videomode"; // for compatibility with old version
    case AHC_MODE_CAPTURE_PREVIEW:
        return ncgi_get_ui_state();
    default:
        break;
    }
    if (ncam_get_streaming_mode()) {
        // for transcoding
        return "Streaming";
    }
    return "Idlemode";
}
/*
 * for H264 streaming to get SPS/PPS at RTSP starting.
 */
int AHC_OpenVideoStream(void *handle);
int AHC_CloseVideoStream(void *handle);
int ncam_enable_h264_stream(int bEnabled)
{
    int w, h;
    MOVIESIZE_SETTING res;

    if (bEnabled) {
        AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_CODEC_TYPE, AHC_MOVIE_VIDEO_CODEC_H264);
        AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_STREAM, AHC_VIDEO_STREAMING, AHC_TRUE);
        ncfg_get("Camera.Preview.H264.w", &w);
        ncfg_get("Camera.Preview.H264.h", &h);

        if (w == 1920 && h == 1080) {
            res = MOVIE_SIZE_1080_30P;
        }
        else if (w == 1920 && h == 1440) {
            res = MOVIE_SIZE_1440_30P;
        }
        else if (w == 1280 && h == 720) {
            res = MOVIE_SIZE_720_30P;
        }
        else if (w == 640 && h == 360) {
            res = MOVIE_SIZE_360_30P;
        }
        else if (w == 1472 && h == 736) {
            res = MOVIE_SIZE_1080_30P;
        }
        else if (w == 736 && h == 736) {
            res = MOVIE_SIZE_1080_30P;
        }
        else if (w == 1280 && h == 640) {
            res = MOVIE_SIZE_1080_30P;
        }
        else if (w == 320 && h == 240) {
            res = MOVIE_SIZE_360_30P;
        }
        else {
            bEnabled = 0;
        }

        if (bEnabled) {
            VideoFunc_SetResolution(res);
            if (0 == AHC_OpenVideoStream(NULL)) {
                return 0;//error
            }
        }
    } else {
        AHC_CloseVideoStream(NULL);
    }
    return bEnabled;
}

// Get SD0 Status [NONE|READY|FORMATING|ERROR]
const char* ncam_get_ui_sd0_status(void)
{
    if (MenuSettingConfig()->uiMediaSelect == MEDIA_SETTING_SD_CARD) {
        switch (_format_sd) {
        case FORMAT_SD_NONE:
        case FORMAT_SD_DONE: {
            #if 0
            if (MenuFunc_CheckAvailableSpace( uiGetCurrentState() ) == AHC_TRUE)
                return "READY";
            else {
				printc(">>>>> %s,%d Wifi TBD. <<<<<\r\n",__FUNCTION__,__LINE__); //Andy Liu TBD
                return "CARDFULL";
            }
            #else
            return "READY";
            #endif
        }
        case FORMAT_SD_DOING:
            return "FORMATING";
        default:
            return "ERROR";
        }
    }
    return "NONE";
}
// Format SD0 status
int ncam_set_ui_sd0_status(int status)
{
    if (_format_sd != status) {
        _format_sd = status;
        ncgi_notify_uichange(NULL);
    }
    return _format_sd;
}

/*
 * the function called must be in streaming.
 * Get Recording Start time in streaming time line
 */
//
int ncam_get_rec_time_start(void)
{
    int     total, curr;

    AHC_VIDEO_GetCurRecordingTime((unsigned int*)&total);
    total += (unsigned int)VideoFunc_GetRecordTimeOffset();
    curr  = AHC_StreamingTimer_GetMs();
    printc(BG_RED("Total %d at %d start AT %d")"\r\n", total, curr, curr - total);
    // if the start time is negtive, it means Recording start before streaming.
    return curr - total;
}
//
int ncam_get_rec_time_total(void)
{
    //Total elapsed time of recording ,it will be reset to 0 when stopping record
    unsigned int ultime;

    AHC_VIDEO_GetCurRecordingTime(&ultime);
    ultime += VideoFunc_GetRecordTimeOffset();
//    printc("TOTAL %d at %d\n", (int)ultime, MMPF_Streaming_GetTime());
    return (int)ultime;
}
int ncam_get_rec_time_remaining(void)
{
    //Total remaining time for record in SD Card, include current elapsed time of recording
    int vRemainingInSec;

#if 0
    //vRemainingInSec =     CameraSettingConfig()->byRemainingHour * 3600 + //Andy Liu TBD
    //                  CameraSettingConfig()->byRemainingMinute * 60 +
    //                  CameraSettingConfig()->byRemainingSecond;
#else
    unsigned char bHour, bMin, bSec;

    AHC_VIDEO_AvailableRecTimeEx(0, &bHour, &bMin, &bSec);
    vRemainingInSec =   bHour * 3600 +
                        bMin * 60 +
                        bSec;
#endif

    return vRemainingInSec;
}
int ncam_get_rec_time_available(void)
{
    //Total available time for record in SD Card :
    //Total remaining time for record in SD Card - current elapsed time of recording
    int vAvailableInSec;
    int vRecrdTimeInSec;
    int vRemainingInSec;

#if 0
    //vRemainingInSec = CameraSettingConfig()->byRemainingHour * 3600 + //Andy Liu TBD
    //                  CameraSettingConfig()->byRemainingMinute * 60 +
    //                  CameraSettingConfig()->byRemainingMinute;

    //vRecrdTimeInSec =     CameraSettingConfig()->byRecordedHour * 3600 + //Andy Liu TBD
    //                  CameraSettingConfig()->byRecordedMinute * 60 +
    //                  CameraSettingConfig()->byRecordedSecond;
#else
    vRemainingInSec =   ncam_get_rec_time_remaining();
    vRecrdTimeInSec =   (unsigned int)VideoFunc_GetRecordTimeOffset();
#endif

    vAvailableInSec =   vRemainingInSec - vRecrdTimeInSec;

    return  vAvailableInSec;
}
int ncam_get_ui_cap_remaining(void)
{
#if 0
    //it will be updated after each capture done or swtiching to capture mode
    return 0;
    //return CameraSettingConfig()->uiRemainingShots; //Andy Liu TBD
#else
    unsigned long long  freeBytes;
    unsigned int        remainCaptureNum;

    CaptureFunc_CheckMemSizeAvailable(&freeBytes, &remainCaptureNum);

    return remainCaptureNum;
#endif
}

int ncam_get_ui_power_level(void)
{
    int vBatPercen = -1;

    switch(MenuSettingConfig()->uiBatteryVoltage)
    {
    case BATTERY_VOLTAGE_EMPTY:
    case BATTERY_VOLTAGE_LOW:
        vBatPercen = 0;
        break;
    case BATTERY_VOLTAGE_LEVEL_0:
        vBatPercen = 25;
        break;
    case BATTERY_VOLTAGE_LEVEL_1:
        vBatPercen = 50;
        break;
    case BATTERY_VOLTAGE_LEVEL_2:
        vBatPercen = 75;
        break;
    case BATTERY_VOLTAGE_LEVEL_3:
    case BATTERY_VOLTAGE_FULL:
        vBatPercen = 100;
        break;
    default:
        break;
    }
    return vBatPercen;
}

/////SHOW LDWS WARNING TO WIFI APP
static int g_ldws_val;
char* netapp_get_LdwsResult()
{
    if (g_ldws_val == LDWS_STATE_DEPARTURE_LEFT) {
        return "LEFT";
    }
    else if (g_ldws_val == LDWS_STATE_DEPARTURE_RIGHT) {
        return "RIGHT";
    }
    return "NORMAL"; //vBatPercen;
}

#define LDWS_CNT_LEVEL  20
void netapp_set_LdwsResult(int val)
{
    static int normal_cnt = LDWS_CNT_LEVEL;
    if (val==LDWS_STATE_NORMAL) {
        normal_cnt ++;
        if ((normal_cnt >= LDWS_CNT_LEVEL)&&((g_ldws_val==LDWS_STATE_DEPARTURE_LEFT)||
            (val==LDWS_STATE_DEPARTURE_RIGHT))) {
            g_ldws_val = val;
            normal_cnt = 0;
//          netapp_UINotifyChanged(NULL);
        }
        if (normal_cnt > 10*LDWS_CNT_LEVEL)
            normal_cnt = LDWS_CNT_LEVEL;
    }else if ((val==LDWS_STATE_DEPARTURE_LEFT)||(val==LDWS_STATE_DEPARTURE_RIGHT)) {
        normal_cnt++;

        if (normal_cnt >= LDWS_CNT_LEVEL) {
            g_ldws_val = val;
            normal_cnt = 0;
            ncgi_notify_uichange(NULL);
        }
    }
}

/////SHOW FCWS WARNING TO WIFI APP
static bool g_fcws_val=false;
char* netapp_get_FcwsResult()
{
    if (g_fcws_val) {
        g_fcws_val = false;
        return "ALARM";
    }
    return "NORMAL";
}

void netapp_set_FcwsResult(bool alarm)
{
    g_fcws_val = alarm;
    if (alarm)
        ncgi_notify_uichange(NULL);
}

/////SHOW SAG WARNING TO WIFI APP
static bool g_sag_val=false;
char* netapp_get_SagResult()
{
    if (g_sag_val) {
        g_sag_val = false;
        return "ALARM";
    }
    return "NORMAL";
}

void netapp_set_SagResult(bool alarm)
{
    g_sag_val = alarm;
    if (alarm)
        ncgi_notify_uichange(NULL);
}


/*
 * parameter:
 *     video_format supports FORMAT_MJPEG
 *     audio_format supports FORMAT_PCM, FORMAT_AAC
 */
int ncam_parse_file(char *file_name, int video_format, int audio_format)
{
    int err;
    AHC_MODE_ID ahcMode = AHC_GetAhcSysMode();
    MMP_BYTE    bFilePath[200];
    MMP_ULONG ulFileNameLen;
    ncam_val_t value;
    unsigned short i;


    if (file_name != NULL) {
        printc(FG_RED("Use file %s\r\n"), file_name);
    } else {
        printc(FG_YELLOW("Use live streaming\r\n"));
        return -1;
    }

    if (AHC_MODE_RECORD_PREVIEW == ahcMode) {
        //MMPS_VIDPLAY_SetDramMallocAddr(MMPS_3GPRECD_GetPreviewEndAddr());
    }

    #if (FS_INPUT_ENCODE == UCS2)
    uniStrcpy(bFilePath, vidFileName);
    ulFileNameLen = uniStrlen((short *)bFileName);
    #elif (FS_INPUT_ENCODE == UTF8)
    //STRCPY(bFilePath, "SD:0:\\"/*FS_1ST_DEV*/);
    STRCPY(bFilePath, "SD:");
    STRCAT(bFilePath, file_name);
    ulFileNameLen = STRLEN(bFilePath);
    #endif
    for (i = 0; i < ulFileNameLen; ++i) {
        if (bFilePath[i] == '/') {
            bFilePath[i] = '\\';
        }
    }

    err = AIHC_OpenTranscode();
    if (err != 0) {
        return -4;
    }

    err = MMPS_VIDPLAY_Open(bFilePath, ulFileNameLen, 0, MMP_TRUE, MMP_TRUE, NULL);

    if (err != MMP_ERR_NONE) {

        printc("File Name : %s\r\n"
               "Unable to open the file (%X).\r\n", bFilePath, err);

        if(err != MMP_3GPPLAY_ERR_INCORRECT_STATE_OPERATION){
            printc("Close Video\r\n");
            AIHC_CloseTranscode();
        }
        return -2;
    }

    value.type = VALUE_TYPE_INT;
    MMPS_VIDPLAY_GetCurFileDuration((MMP_ULONG*)&value.v.i32);
    if (!ncam_set_setting(NCS_FILE_DURATION, &value)) {
        return -3;
    }
    return 0;
}

// 0: liveRTSP, 1: txRTSP
// TODO: txRTSP should run under PLAYBACK mode only
int ncam_is_streamable(int streamtype)
{
    //QUERY_TYPE_WIFI_STREAMABLE is in ahc_menu.h, Please port from SDK
    return uiQueryStatusInfo(QUERY_TYPE_WIFI_STREAMABLE, &streamtype, NULL, NULL);
}

// 1: can flash FW
// 0: can NOT flash FW
int ncam_is_flashable(void)
{
    UI_STATE_ID ubParentUIState = 0;
    int         state;

    state = (int)uiGetCurrentState();

    StateModeGetParent(state, &ubParentUIState);

    #if 0
    if(ubParentUIState != UI_STATE_UNSUPPORTED)
        state = ubParentUIState;
    #endif

    if(ubParentUIState != UI_STATE_UNSUPPORTED)
        return (StateModeFindState(state, UI_NET_FWUPDATE_STATE))? 1 : 0;
    else
        return (state == UI_NET_FWUPDATE_STATE) ? 1 : 0;

}

//
int ncam_update_audio_sampling_rate(int transcode)
{
    ncam_val_t value = {VALUE_TYPE_INT, {NCS_FILE_DURATION_UNDEFINED}};
    const char *str = NULL;

    if (transcode) {
        str = "transcoding bit rate";
        MMPD_VIDPSR_GetParameter(MMPD_VIDPLAY_PARAMETER_AUDIO_SAMPLING_RATE, &value.v.i32);
    } else {
        str = "live streaming";
        value.v.i32 = AHC_VIDEO_GetDefaultAudioSamplingRate();
    }
    printc("%s %d\r\n", str, value.v.i32);

    if (!ncam_set_setting(NCS_AUDIO_SAMPLING_RATE, &value)) {
        osal_dprint(ERR, "set %s", value.v.str);
        return -1;
    }
    return 0;
}

unsigned int ncam_get_streaming_timer(void)
{
    return AHC_StreamingTimer_GetMs();
}

/** Stop transcoding streaming. Typically RTSP
 *
 * @return 0 if successful. < 1 if failed.
 */
int ncam_stop_transcoding(void)
{
    struct amn_session_t *s;
    struct ammo_node* node = NULL;
    char src_name[] = "VIDEO.0/EncMJPEG"; //double-check this with conf file.

	printc("%s %d\r\n", __FUNCTION__, __LINE__);

    //static void __aitstreamer_set_running( char *src_name, int running )
    node = node_find_name( AMMO_TYPE__NODE_SOURCE, src_name, -1 );

    if (node) {
        struct list_head *l;
        struct ammo_pipe *p;
        /* see if anybody else is listening */
        list_for_each( l, &(node->pl->pipe_TO_list) ) {
            p = list_entry( l, struct ammo_pipe, link );
            printc("name:%s type:%d\r\n", p->to_node->name, p->to_node->node_type);
            if (p->to_node->node_type == AMMO_TYPE__NODE_SINK) {
                int i;
                for (i=0; ;i++) {
                    s = session_search_owner(p->to_node, i);
                    if (NULL != s) {
                        printc("found session of %s\r\n", p->to_node->name);
                        session_destroy(s, "stop transcoding");
                    } else {
                        break;
                    }
                }
            }
        }
    }
    else {
        printc("set_running for Source Node '%s' : invalid \r\n", src_name);
        return -1;
    }
    return 0;
}


int ncam_upload_progress(unsigned int cursize, unsigned int total)
{
    // TODO: Call to UI to show progress
    static char prm[] = "\\|/-";
    static int  idx = 0;
    static int uiPercentage = -1;
    printc("%c %u/%u\r", prm[(idx++) & 0x03], cursize, total);

    if( AHC_DrawNetFwDownloadProgress != NULL )
    {
        if( uiPercentage != ((cursize*100)/total) )
        {
            uiPercentage = (cursize*100)/total;
            AHC_DrawNetFwDownloadProgress( uiPercentage );
        }
    }
    return 0;
}

//  close transcodig only without handling network sessions. This is for net code only.
int ncam_close_transcoding(void)
{
    return AIHC_CloseTranscode();
}

int ncam_get_streaming_mode(void)
{
    return AHC_GetStreamingMode();
}

int ncam_get_cam_src(unsigned int vMode)
{
    struct amn_cfgspace_value_t *cfg_val;

    if (((AHC_STREAMING_MODE)vMode == AHC_STREAM_MJPEG)||
        ((AHC_STREAMING_MODE)vMode == AHC_STREAM_H264)) {

        cfg_val = amn_config_get(CONFIG_SPACE_TYPE_CURRENT, "Camera.Preview.Source.1.Camid");
        if(cfg_val == NULL)
            return AHC_STREAM_FRONT;
        if (strcmp(cfg_val->v.strVal,"front")&&strcmp(cfg_val->v.strVal,"rear")) {
            amn_config_set(CONFIG_SPACE_TYPE_CURRENT,"Camera.Preview.Source.1.Camid", "front");
            return AHC_STREAM_FRONT;
        }
        else if (!strcmp(cfg_val->v.strVal,"front")) {
            return AHC_STREAM_FRONT;
        }
        else {
            if (MMP_IsUSBCamExist()){
                AHC_BOOL bUVCStatus = MMP_TRUE;
            #if (USB_EN && SUPPORT_USB_HOST_FUNC)
                MMPF_USBH_GetUVCPrevwSts(&bUVCStatus);
            #endif

                if(bUVCStatus)
                    return AHC_STREAM_REAR_USBH;
                else
                    return AHC_STREAM_FRONT;
            }
            else if(MMP_IsScdCamExist()){
                return AHC_STREAM_REAR_VIF;
            }
            else{
                amn_config_set(CONFIG_SPACE_TYPE_CURRENT,"Camera.Preview.Source.1.Camid", "front");
                return AHC_STREAM_FRONT;
            }
        }
    }
    return AHC_STREAM_FRONT;
}

int ncam_switch_cam(void)
{
    AHC_STREAMING_MODE sMode,vMode,aMode;

    sMode = AHC_GetStreamingMode();
    vMode = (sMode & AHC_STREAM_V_MASK) | AHC_STREAM_KEEP_TIMER_ALIVE;
    aMode = (sMode & AHC_STREAM_A_MASK) | AHC_STREAM_KEEP_TIMER_ALIVE;
    if (vMode == AHC_STREAM_OFF)
        return 0;
#if 0
    AHC_SetStreamingMode(aMode);
    AHC_SetStreamingMode(vMode|aMode);
#else
    if (ncam_set_streaming_mode(aMode)==0) {
        //Set audio and video mode at the same time and dispatch it to UI task.
        return ncam_set_streaming_mode(vMode|aMode);
    }
#endif
    return 0;
}

static int rcamstate=0;
int ncam_is_rear_cam_ready(void)
{
    return rcamstate;
}

void ncam_set_rear_cam_ready(int state)
{
    rcamstate = state;
}

#if 0
void ____ns____() {} //dummy. Network Server
#endif

#ifdef STREAM_FLAG_PUMP_STREAM
void ns_pump_streaming(void)
{
    extern MMPF_OS_FLAGID   Streaming_Flag;
    MMP_UBYTE MMPF_OS_SetFlags(MMPF_OS_FLAGID ulFlagID, MMPF_OS_FLAGS flags, MMPF_OS_FLAG_OPT opt);
    MMPF_OS_SetFlags(Streaming_Flag, STREAM_FLAG_PUMP_STREAM, MMPF_OS_FLAG_SET);
}
#endif

// Broadcast frame rate of video source (v4L) to each AMN NODE
int ns_set_fps(int fps, char* name)
{
    struct ammo_node* node = NULL;

    node = node_find_name( AMMO_TYPE__NODE_SOURCE, name, -1 );
    if (NULL == node) {
        printc("net ass framerate <NODE_NAME> in out\r\n <NODE_NAME> supports MJPEG only\r\n");
        return ASS_ERR_PARAM;
    }
    return pipeline_set_node_attr_all(node, PLCFG__SET_FRAMERATE, (void*)fps);
}

//set frame rate conversion
int ns_set_frc(int inx1000, int outx1000, char* name)
{
    struct plcfg_frc_t frc;
    struct ammo_node* node = NULL;
    ass_err err;

    node = node_find_name( AMMO_TYPE__NODE_SOURCE, name, -1 );
    if (NULL == node) {
        printc("net ass frc <NODE_NAME> in out\r\n <NODE_NAME> supports MJPEG only\r\n");
        return ASS_ERR_PARAM;
    } else {
        frc.inx1000 = inx1000;
        frc.outx1000 = outx1000;
        err = node_set_attr(node, PLCFG__SET_FRC, &frc);
        if (ASS_ERR_NONE != err) {
            printc(BG_RED("Error(%d): %s %d setting node %s")"\r\n", err, __FUNCTION__, __LINE__, name);
            return err;
        }
    }
    return ASS_ERR_NONE;
}


struct _NS_EVENT_HANDLER ns_event_handlers[NS_EVENT_MAX];

static NS_EVENT_HANDLER ns_get_event_handler(NS_EVENT_HANDLER_TYPE handler_type)
{
    if (handler_type >= NS_EVENT_MAX)
    {
        return NULL;
    }
    return &ns_event_handlers[handler_type];
}

NS_EV_RET ns_handle_event(NS_EVENT_HANDLER_TYPE handler_type, void* eventData)
{
    int ret = NSE_ERR;
    NS_EVENT_HANDLER handler;

    handler = ns_get_event_handler(handler_type);
    if (handler) {
        if (handler->callback) {
            ret = handler->callback(eventData, handler->userData);
        } else {
            ret = NSE_CB_NOT_FOUND;
            //printc("[INFO]:ns event callback not found\r\n");
        }
    } else {
        ret = NSE_HANDLER_NOT_FOUND;
        printc("[ERR]: ns event handler not found\r\n");
    }
    return ret;
}

NS_EV_RET ns_set_ev_handler(NS_EVENT_HANDLER_TYPE handler_type, NS_EVENT_CB callback, void* userData)
{
    if (handler_type >= NS_EVENT_MAX)
    {
        return NSE_PARAM;
    }
    ns_event_handlers[handler_type].callback = callback;
    ns_event_handlers[handler_type].userData = userData;
    return 0;
}

int ns_has_stream_control(void)
{
    return aitstreamer_has_stream_control();
}


#if 0
void ____ncgi____() {} //dummy.
#endif

static WMSG_INFO m_web_WMSG_Info;

//get if it is on warning state.
int ncgi_has_warning_msg(void)
{
    if(m_web_WMSG_Info == WMSG_NONE) {
        return AHC_FALSE;
    }
    else {
        return AHC_TRUE;
    }
}

//set warning message information.
int ncgi_set_warning_msg(int m_WMSG_Info)
{
    m_web_WMSG_Info = (WMSG_INFO)m_WMSG_Info;
    return 0;
}

//get warning message information.It still have many to implement.
int ncgi_get_warning_msg(void)
{
    switch(m_web_WMSG_Info)
    {
    case WMSG_NO_CARD:
        ncgi_set_warning_msg(WMSG_NONE);
        return 1;
    default:
        break;
    }
    return 0;
}


#define INVALID_ID  (-1)
/*
 * return MENU ID or INVALID_ID if NOT FOUND
 */
static int GetMenuIDbyCGIval(char *cgival, CGI_MENU_MAP *map)
{
    int     i;

    for (i = 0; map[i].cgi_val != NULL; i++) {
        if (stricmp(cgival, map[i].cgi_val) == 0)
            return map[i].menu_id;
    }
    return INVALID_ID;
}
/*
 * return CGI value string or NULL if NOT FOUND
 */
static const char* GetCGIvalbyMenuId(int menuid, CGI_MENU_MAP *map)
{
    int     i;

    for (i = 0; map[i].cgi_val != NULL; i++) {
        if (menuid == map[i].menu_id)
            return (const char*)map[i].cgi_val;
    }
    printc(FG_YELLOW("[WARN]")"Unknown menu id %d\r\n", menuid);
    return "UNKNOWN";
}

//get Video Resolution.
const char* ncgi_get_video_res(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiMOVSize, ncgi_get_menu(VIDEO_RES));
}

//get video clip time
const char* ncgi_get_video_clip_time(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiMOVClipTime,
                             ncgi_get_menu(VIDEO_CLIP));
}

//get Image Resolution.
const char* ncgi_get_image_res(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiIMGSize,
                             ncgi_get_menu(IMAGE_RES));
}
// get White balance
const char* ncgi_get_wb()
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiWB,
                             ncgi_get_menu(WB));
}
// get flicker (50HZ, 60HZ)
const char* ncgi_get_flicker_hz()
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiFlickerHz,
                             ncgi_get_menu(FLICKER));
}
// get Motion Detection Level
const char* ncgi_get_mtd_level()
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiMotionDtcSensitivity,
                             ncgi_get_menu(MTD));
}
// get Exposure
const char* ncgi_get_ev_level()
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiEV,
                             ncgi_get_menu(EXPO));
}
// get Power off delay
const char* ncgi_get_power_off_delay()
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiMOVPowerOffTime,
                             ncgi_get_menu(OFF_DELAY));
}
//get GSensor sensitivity
const char* ncam_get_gsensor_sensitivity(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiGsensorSensitivity, ncgi_get_menu(GSENSOR));

}
//get Did & Token
const char* ncgi_get_did_token(void)
{
    NET_DID_ACCESS_CB pdid_token_cb = ncfg_get_didtoken_accessed_cb();

    if(pdid_token_cb && gbAllowAppAccss)
    {
        int ret;
        struct amn_cfgspace_value_t *cfg_val;

        cfg_val = amn_config_get(CONFIG_SPACE_TYPE_CURRENT, "DidToken");

        ret = pdid_token_cb(0,cfg_val->v.strVal,cfg_val->max_strlen);

        if(-1 == ret)
            return "UNKNOWN";
        else
            return cfg_val->v.strVal;
    }
    else
    {
        return "UNKNOWN";
    }

}
const char* ncgi_get_lcdpower()
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiLCDPowerSave,ncgi_get_menu(LCD_POWER_SAVE));
}
const char* ncgi_get_filenum()
{
    UINT32 nDB1 = 0;
    //UINT32 nDB2 = 0;
    UINT32 nDB3 = 0;
    //UINT32 nDB4 = 0;
    //UINT32 nDB5 = 0;
    //int ret;
    struct amn_cfgspace_value_t *cfg_val;
    //char nDBFileNum[16]={0};
    cfg_val = amn_config_get(CONFIG_SPACE_TYPE_CURRENT, "Camera.DBFileNum");
    AHC_DCFDT_GetTotalFileCountByDB(DCF_DB_TYPE_DB0_NORMAL, &nDB1);
    //AHC_DCFDT_GetTotalFileCountByDB(DCF_DB_TYPE_DB1_PARKING, &nDB2);
    AHC_DCFDT_GetTotalFileCountByDB(DCF_DB_TYPE_DB2_EVENT, &nDB3);
    //AHC_DCFDT_GetTotalFileCountByDB(DCF_DB_TYPE_DB3_PHOTO, &nDB4);
    //AHC_DCFDT_GetTotalFileCountByDB(DCF_DB_TYPE_DB4_SHARE, &nDB5);
    printc("%s,nDB1=%d,nDB3=%d!!!!\n\r",__func__,nDB1,nDB3);
    //printc("%s,nDB4=%d,nDB5=%d!!!!\n\r",__func__,nDB4,nDB5);
    //snprintf(nDBFileNum,sizeof(nDBFileNum),"%d+%d",nDB2,nDB3);
    snprintf(cfg_val->v.strVal,cfg_val->max_strlen-1,"%d+%d",nDB1,nDB3);
    printc("***********%s,%s**********\n\r",__func__,cfg_val->v.strVal);

    return cfg_val->v.strVal;
}
const char* ncgi_get_normaldbsize()
{
    UINT64 uNDBSize = 0;
    AHC_FS_DISK_INFO sMediaInfo;
    UINT32 BytesPerCluster = 0;
    UINT64 uiiTotalBytesInSD = 0;
    struct amn_cfgspace_value_t *cfg_val;
    cfg_val = amn_config_get(CONFIG_SPACE_TYPE_CURRENT, "Camera.NormalDBSize");
    AHC_GetStorageMediaInfo(&sMediaInfo);
    BytesPerCluster = sMediaInfo.usSecPerCluster * sMediaInfo.usBytesPerSector;
    uiiTotalBytesInSD = (UINT64)sMediaInfo.ulTotalClusters*BytesPerCluster;
    uNDBSize = uiiTotalBytesInSD*DCF_CLUSTER_NUMERATOR_DB0/DCF_CLUSTER_DENOMINATOR;
    uNDBSize = uNDBSize/1024/1024;
    snprintf(cfg_val->v.strVal,cfg_val->max_strlen-1,"%lld",uNDBSize);
	printc("***********%s,%s**********\n\r",__FUNCTION__,cfg_val->v.strVal);
    return cfg_val->v.strVal;
}
/*
 * Return UI State ID
 */
unsigned char ncgi_get_ui_state_id(void)
{
    UINT8 ubCurUIState = 0;
    UI_STATE_ID ubParentUIState = 0;
    MMP_SHORT  usStateLayerMaxCount = 5;

    ubCurUIState = uiGetCurrentState();

    do{

        StateModeGetParent(ubCurUIState, &ubParentUIState);
        usStateLayerMaxCount--;

        if(ubParentUIState != UI_STATE_UNSUPPORTED)
            ubCurUIState = ubParentUIState;
        else
            break;

    }while(usStateLayerMaxCount >= 0 );

    return ubCurUIState;
}

/*
 * Return UI State CGI value string
 */
const char* ncgi_get_ui_state(void)
{
    return GetCGIvalbyMenuId(ncgi_get_ui_state_id(), ncgi_get_menu(UI_STATE));
}
/*
 * Return Default UIMode after bootup
 */
const char* ncgi_get_def_ui_state(void)
{
    int state;
    // Convert menu index to setting id
	printc(">>>>> %s,%d Wifi TBD. Force at UI_VIDEO_STATE <<<<<\r\n",__FUNCTION__,__LINE__); //Andy Liu TBD
    state = UI_VIDEO_STATE;
    //state = CameraSettingsFunc_GetBootUpUIState(MenuSettingConfig()->uiBootUpMode);

    return GetCGIvalbyMenuId(state, ncgi_get_menu(UI_STATE));
}
/*
 * Return UI State CGI value string by ID
 */
const char* ncgi_get_ui_state_by_id(int uId)
{
    const char  *p;

    p = GetCGIvalbyMenuId(uId, ncgi_get_menu(UI_STATE));
    return (p)? p : "UNKNOWN";
}

#if 0
const char* ncgi_get_grp_mode_str(int uId, char* file_name)
{
    const char  *p;
    const char *GroupModeStr;

    if (AHC_DCF_GetCusGrpModeStr(file_name, &GroupModeStr)) {
        return GroupModeStr;
    }
    p = GetCGIvalbyMenuId(uId, ncgi_get_menu(UI_STATE));
    return (p)? p : "UNKNOWN";
}
#endif

/*
 * Get camera status
 */
const char* ncgi_get_photo_burst(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiBurstShot, ncgi_get_menu(PHOTO_BURST));
}
const char* ncgi_get_timelapse(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiTimeLapseTime, ncgi_get_menu(TIMELAPSE));
}
const char* ncgi_get_up_side_down(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiImageUpsideDown, ncgi_get_menu(UPSIDE_DOWN));
}
const char* ncgi_get_hdr(void)
{
    return (char*)GetCGIvalbyMenuId(MenuSettingConfig()->uiWDR, ncgi_get_menu(HDR));
}
const char* ncgi_get_looping_video(void)
{
    INT32 clipTime;

    if (pf_General_EnGet(COMMON_KEY_VR_CLIP_TIME, &clipTime) == AHC_FALSE)
        clipTime = MOVIE_CLIP_TIME_OFF;

    return GetCGIvalbyMenuId(clipTime, ncgi_get_menu(LOOPING_VIDEO));
}
const char* ncgi_get_spot_meter(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiMetering, ncgi_get_menu(SPOT_METER));
}
const char* ncgi_get_q_shot(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiAutoRec, ncgi_get_menu(Q_SHOT));
}
const char* ncgi_get_status_lights(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiStatusLight, ncgi_get_menu(STATUS_LIGHTS));
}
const char* ncgi_get_sound_indicator(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiBeep, ncgi_get_menu(SOUND_INDICATOR));
}
const char* ncgi_get_power_saving(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiAutoPowerOff, ncgi_get_menu(POWER_SAVING));
}
const char* ncgi_get_tv_system(void)
{
    return GetCGIvalbyMenuId(MenuSettingConfig()->uiTVSystem, ncgi_get_menu(TV_SYSTEM));
}
// Get Camera with HTMI status
const char* ncgi_get_tv_status(void)
{
    if (ncam_is_hdmi_on()) {
        return "HDMI";
    }

    return (const char *) "NONE";
}

/*
const char* ncgi_get_status(void)
{
    int ret;
    char* string = NULL;
    ret = ns_handle_event(NS_EVENT_GET_STATUS, (void*)string);
    if (ret == NSE_CB_NOT_FOUND) {
        return "703\n""Invalid state";
    }
    return string;
}
*/

/**
 *
 * It accept web command and set as keyevent to do corresponding actions.
 *
 * input: web event
 */
#if CGIOP_DBG
struct ncgi_ret ncgi_send_ui_msg_dbg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, void *arg, char* func,
        int line)
#else
struct ncgi_ret ncgi_send_ui_msg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, void *arg)
#endif
{
    struct ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    // Speed up WiFi event!
    // Send the WiFi message into High Priority Queue,
    // If send to normal queue by AHC_SendAHLMessage,
    // it will wait for normal messages finished like as
    // AHLM_UI_NOTIFICATION/BUTTON_UPDATE_MESSAGE, when system is busy!!
    AHC_SendAHLMessage_HP(AHLM_WIRELESS_CONNECT, msg, param1);

    if (pfn_wait) {
    #if CGIOP_DBG
        printc("Send uimsg %s@%d\r\n", func, line);
    #endif
        // Wait, webwait_uiproc()
        ret.cgi = pfn_wait((void*)msg, arg);
    #if CGIOP_DBG_INFO
        printc("--> COMMAND FINISH %d\n", ret.cgi, cgi_err_resp_code(ret.cgi), cgi_err_text(cgi_err_resp_code(ret.cgi)));
    #else
        printc("--> COMMAND FINISH %d\n", ret.cgi);
    #endif
        if (ret.cgi < 0) {
            ret.netapp = NETAPP_FAIL;
        }
    }
    return ret;
}

#if CGIOP_DBG
struct ncgi_ret ncgi_send_ui_std_msg_dbg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait,
        PFN_CGI_OP_CALLBACK pfn_s, char* func, int line)
#else
struct ncgi_ret ncgi_send_ui_std_msg(unsigned int msg, unsigned int param1, PFN_WEBWAIT pfn_wait, PFN_CGI_OP_CALLBACK pfn_s)
#endif
{
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    ncgi_op_callback(pfn_s);
    //ret = ncgi_send_ui_msg(msg, param1, pfn_wait, STD_CGI_TIME_OUT);
    AHC_SendAHLMessage_HP(AHLM_NET, msg, param1);

    if (pfn_wait) {
    #if CGIOP_DBG
        printc("Send uimsg %s@%d\r\n", func, line);
    #endif
        // Wait, webwait_uiproc()
        ret.cgi = pfn_wait((void*)msg, STD_CGI_TIME_OUT);
        printc("--> CGI DONE %d\n", ret.cgi);
        if (ret.cgi < 0) {
            ret.netapp = NETAPP_FAIL;
        }
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set UIMode  | 1.0 | | | |
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.UIMode  | set 1.2\n get 1.0 | | | |
  Keep CGI_VER_MATRIX in one line.*/ // property=UIMode&value=[VIDEO|CAMERA|BURST|TIMELAPSE|SETTING|PLAYBACK]
/** Handle property=UIMode
 *
 * Possible values:VIDEO|CAMERA|BURST|TIMELAPSE|SETTING|PLAYBACK
 * @ref CGI_MENU_UI_STATE for more info
 *
 * @param key, val, pfn_w, pfn_s ref template of PFN_CGI_HANDLER
 * @return  ref template of PFN_CGI_HANDLER
 */
CGI_RW ncgi_ret Handle_UIMode(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_ERR_INVALID_PARAM;
    ret.netapp = NETAPP_FAIL;

    if ((id = GetMenuIDbyCGIval(val, ncgi_get_menu(UI_STATE))) != INVALID_ID) {
        ret = ncgi_send_ui_std_msg(WIRELESS_SET_UIMODE, id, pfn_w, pfn_s);
    }

    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set DefMode  | 1.0 | 1.1 | 1.2 | Set default UI State |
  [CGI_VER_MATRIX]       | get Camera.Menu.DefMode  | 1.0 | 1.1 | 1.2 | Set default UI State |
  Keep CGI_VER_MATRIX in one line.*/ // property=DefMode&value=[VIDEO|CAMERA|BURST|TIMELAPSE|SETTING]
CGI_RW ncgi_ret Handle_DefMode(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;
    id = GetMenuIDbyCGIval(val, ncgi_get_menu(UI_STATE));

    if (id != INVALID_ID) {
        //ncgi_send_ui_msg(WIRELESS_SET_BOOTUPMODE,
        //                      CameraSettingsFunc_GetBootUpMode(id), pfn_w, (void*)0);
		printc(">>>>> %s,%d Wifi TBD. <<<<<\r\n",__FUNCTION__,__LINE__); //Andy Liu TBD
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set Video record/capture   | 1.0 | | | Main video operation. |
  [CGI_VER_MATRIX]       | set Video rec_emer/rec_short   | 1.2 | | | Main video operation. |
  Keep CGI_VER_MATRIX in one line.*/ // property=Video&value=[record|capture|rec_short|rec_emer]
CGI_WO ncgi_ret Handle_VideoOperation(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (stricmp(val, "record") == 0) {
        ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_RECORD, 0, pfn_w, STD_CGI_TIME_OUT);
    } else if (stricmp(val, "capture") == 0) {
        ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_CAPTURE, 0, pfn_w, STD_CGI_TIME_OUT);
    } else if (stricmp(val, "rec_emer") == 0) {
        ncgi_op_callback(pfn_s);//triggers emergency record
        ret = ncgi_send_ui_msg(WIRELESS_REC_EMERGENCY, 0, pfn_w, STD_CGI_TIME_OUT);
    } else if (stricmp(val, "rec_short") == 0) {
        ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_REC_SHORT, 0, pfn_w, STD_CGI_TIME_OUT);
    } else if (stricmp(val, "mute") == 0) {
        ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_REC_MUTE, 1, pfn_w, STD_CGI_TIME_OUT);
    } else if (stricmp(val, "unmute") == 0) {
        ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_REC_MUTE, 0, pfn_w, STD_CGI_TIME_OUT);
    }
    else if (stricmp(val, "MUP") == 0) {
        //ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_MOT, 0, NULL, STD_CGI_TIME_OUT);
    }else if (stricmp(val, "MDOWN") == 0) {
        //ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_MOT, 1, NULL, STD_CGI_TIME_OUT);
    }else if (stricmp(val, "MLEFT") == 0) {
        //ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_MOT, 2, NULL, STD_CGI_TIME_OUT);
    }else if (stricmp(val, "MRIGHT") == 0) {
        //ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_MOT, 3, NULL, STD_CGI_TIME_OUT);
    }else if (stricmp(val, "MRELEASE") == 0) {
        //ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_MOT, 4, NULL, STD_CGI_TIME_OUT);
    }else if (stricmp(val, "MCLIPS") == 0) {
        //ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_MOT, 5, NULL, STD_CGI_TIME_OUT);
    } else if (stricmp(val, "MSPEEDUP") == 0) {
        //ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_MOT, 6, NULL, STD_CGI_TIME_OUT);
    } else if (stricmp(val, "MSPEEDDOWN") == 0) {
        //ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_SET_MOT, 7, NULL, STD_CGI_TIME_OUT);
    }
    else {
        ret.netapp = NETAPP_FAIL;
        ret.cgi = CGI_ERR_INVALID_PARAM;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set WiFi     | 1.0 | | | Turn off WiFi module. |
  Keep CGI_VER_MATRIX in one line.*/ //property=WiFi&value=.....
CGI_WO ncgi_ret Handle_Wifi(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (stricmp(val, "off") == 0) {
        ret = ncgi_send_ui_msg(WIRELESS_SET_WIFI, 0, NULL, (void*)0);
    }else {
        ret.netapp = NETAPP_FAIL;
    }
    return ret;

}
/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set Videores | 1.0 | 1.2 | | Set video recording resolution: `value=` resolution string |
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.VideoRes | set 1.2\n get 1.0 | | | Set video recording resolution: `value=` resolution string |

  Keep CGI_VER_MATRIX in one line.*/  // property=Videores&value=...
CGI_RW ncgi_ret Handle_VideoResolution(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (!ncam_is_recording()) {
        id = GetMenuIDbyCGIval(val, ncgi_get_menu(VIDEO_RES));
        if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
            ncgi_send_ui_msg(WIRELESS_SET_MOVIE_SIZE, id, NULL, (void*)0);
#else
            //MenuSettingConfig()->uiMOVSize = id;
            ImportMenuInfo(MenuSettingConfig());
            if( uiGetCurrentState() == UI_VIDEO_STATE )
            {
                VideoTimer_Stop();
                VideoRecMode_PreviewUpdate();
            }
#endif
        } else {
            ret.cgi = CGI_ERR_INVALID_PARAM;
            ret.netapp = NETAPP_FAIL;
        }
    } else {
        ret.cgi = CGI_ERR_INVALID_STATE;
        ret.netapp = NETAPP_FAIL;   // the command failed!!
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set Imageres  | 1.0 | 1.2 | | Set Image capturing resolution: `value=` resolution string.\n Typically used for UI Camera State. |
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.ImageRes  | set 1.2\n get 1.0 | | | Image resolution for capturing: `value=` resolution string.\n Typically used for UI Camera State. |

  Keep CGI_VER_MATRIX in one line.*/ // property=Imageres&value=...
CGI_RW ncgi_ret Handle_ImageResolution(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(IMAGE_RES));
    if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
        ncgi_send_ui_msg(WIRELESS_SET_IMAGE_SIZE, id, NULL, (void*)0);
#else
        //MenuSettingConfig()->uiIMGSize = id;
        ImportMenuInfo(MenuSettingConfig());
        if( uiGetCurrentState() == UI_CAMERA_STATE ) {
            CaptureTimer_Stop();
            CaptureMode_PreviewUpdate();
        }
#endif
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set DeFlickerfMode  | 1.0 | 1.2 | | Set Anti-Flicker mode. |
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.Flicker  | set 1.2\n get 1.0 | | | Set Anti-Flicker mode. |
  Keep CGI_VER_MATRIX in one line.*/ // property=Flicker&value=...
CGI_RW ncgi_ret Handle_Flicker(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(FLICKER));
    if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
        ncgi_send_ui_msg(WIRELESS_SET_FLICKER, id, pfn_w, (void*)0);
#else
        //MenuSettingConfig()->uiFlickerHz = id;
        ImportMenuInfo(MenuSettingConfig());
        Menu_SetFlickerHz(MenuSettingConfig()->uiFlickerHz);
#endif
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set AWB  | 1.0 | 1.2 | | Set Auto White Balance mode. |
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.AWB  | set 1.2\n get 1.0 | | | Set Auto White Balance mode. |
  Keep CGI_VER_MATRIX in one line.*/ // property=AWB&value=...
CGI_RW ncgi_ret Handle_WB(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(WB));
    if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
#if 1
        ncgi_send_ui_msg(WIRELESS_SET_AWB, id, 0, (void*)0);
#else
        ncgi_op_callback(pfn_s);
        ncgi_send_ui_msg(WIRELESS_SET_AWB, id, pfn_w, (void*)6000);
#endif
#else
        //MenuSettingConfig()->uiWB = id;
        ImportMenuInfo(MenuSettingConfig());
        Menu_SetAWB(0, MenuSettingConfig()->uiWB);
#endif
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set TimeSettings  | 1.0 | | | Set Real-Time-Clock (RTC) time.\n `value=Year$Month$Day$Hour$Minute$Second` |
  Keep CGI_VER_MATRIX in one line.*/ // property=TimeSettings&value=...
CGI_WO ncgi_ret Handle_TimeSettings(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret ret;
    int     mDatetime[6] = {2011,01,01,12,0,0};

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    ncam_parse_date_time(mDatetime, val);
#if WIFI_SEAL <= 1
    if(AHC_Validate_ClockSetting(mDatetime, CHECK_ALL, AHC_TRUE)==CHECK_PASS)
#endif
    {
        AHC_SetParam(PARAM_ID_USE_RTC,AHC_TRUE);
        AHC_SetClock(mDatetime[0],  mDatetime[1],  mDatetime[2], 0,
                     mDatetime[3],  mDatetime[4],  mDatetime[5], 0, 0);
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set Net    | 1.0 | | | Reset network function and find the camera.\n Note that it would store network settings into Flash.|
  Keep CGI_VER_MATRIX in one line.*/ // property=Net&value=...
CGI_WO ncgi_ret Handle_Net(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (stricmp(val, "reset") == 0) {
        nhw_reset_network();
    } else if (stricmp(val, "findme")==0) {
        AHC_PlaySoundEffectEx(AHC_SOUNDEFFECT_FINDME, AHC_MSOUND_NULL, AHC_SOUND_IMPORTANCE_NECESSARY);
        AHC_BUZZER_Alert(BUZZER_SOUND_HZ, 1, 1000);
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set Camera.Preview.MJPEG.[x]    | 1.0 | | | Set MJPEG live preview parameters. Such as width and height.|
  Keep CGI_VER_MATRIX in one line.*/ // property=Camera.Preview.MJPEG.[x]&value=...
#define MJPEG_CFG_TAG "Camera.Preview.MJPEG."
CGI_WO ncgi_ret Handle_MJPEG(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    key += sizeof(MJPEG_CFG_TAG) - 1;
    if (strcmp(key, "bitrate") == 0) {
        // return 0, the AMN Config will store the value
        ret.netapp = NETAPP_CONT;
    }
    else if (strcmp(key, "w") == 0) {//Warning! State machine! "h" must be set after this.
        //DO NOTHING
        // return 0, the AMN Config will store the value
        ret.netapp = NETAPP_CONT;
    }
    else if (strcmp(key, "h") == 0) {//warning! State machine! This based on "w" & "fps"
        //DO NOTHING
        // return 0, the AMN Config will store the value
        ret.netapp = NETAPP_CONT;
    }
    else if (strcmp(key, "fps") == 0) {
        //DO NOTHING
        // return 0, the AMN Config will store the value
        ret.netapp = NETAPP_CONT;
    }
    else {
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set EV    | 1.0 | 1.2 | | Set Camera Exposure Value.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.EV    | set 1.2\n get 1.0 | | | Set Camera Exposure Value.|
  Keep CGI_VER_MATRIX in one line.*/ // property=EV&value=...
CGI_RW ncgi_ret Handle_EV(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(EXPO));
    if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
        ncgi_send_ui_msg(WIRELESS_SET_EV, id, pfn_w, (void*)0);
#else
        //MenuSettingConfig()->uiEV = id;
        ImportMenuInfo(MenuSettingConfig());
        Menu_SetEV(0, MenuSettingConfig()->uiEV);
#endif
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set MTD    | 1.1 | | | Set MoTion Detection Mode.\n Typically for parking mode, with level or off.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.MTD    | set 1.2\n get 1.0 | | | Set MoTion Detection Mode.\n Typically for parking mode, with level or off.|
  Keep CGI_VER_MATRIX in one line.*/ // property=MTD&value=...
CGI_RW ncgi_ret Handle_MTD(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(MTD));
    if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
        printc(FG_RED("\r\nPlease modify here!\r\n"));

        if(!uiGetParkingModeEnable())
            ncgi_send_ui_msg(WIRELESS_SET_MTD, id, pfn_w, (void*)0);

        AHC_PRINT_RET_ERROR(0, 0);
#else
        extern void AHC_SwitchMotionDetectionMode(void);
        MenuSettingConfig()->uiMotionDtcSensitivity = id;
        ImportMenuInfo(MenuSettingConfig());
        Menu_SetMotionDtcSensitivity(MenuSettingConfig()->uiMotionDtcSensitivity);
        // Switch MVD mode when sensitivity is changed
        AHC_SwitchMotionDetectionMode();
#endif
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set PhotoBurst    | 1.0 | 1.2 | | Set Photo Burst Mode interval.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.PhotoBurst | set 1.2\n get 1.0 | | | Set Photo Burst Mode interval.|
  Keep CGI_VER_MATRIX in one line.*/ // property=PhotoBurst&value=...
CGI_RW ncgi_ret Handle_PhotoBurst(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(PHOTO_BURST));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_PHOTOBURST, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set Timelapse    | 1.0 | 1.2 | | Set Timelapse Shot interval.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.Timelapse | set 1.2\n get 1.0 | | | Set Timelapse Shot interval.|
  Keep CGI_VER_MATRIX in one line.*/ // property=Timelapse&value=...
CGI_RW ncgi_ret Handle_Timelapse(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(TIMELAPSE));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_TIMELAPSE, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set UpsideDown    | 1.0 | 1.2 | | Set Orientation of Camera Image Sensor.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.UpsideDown | set 1.2\n get 1.0  | | | Set Orientation of Camera Image Sensor.|
  Keep CGI_VER_MATRIX in one line.*/ // property=UpsideDown&value=...
CGI_RW ncgi_ret Handle_UpsideDown(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(UPSIDE_DOWN));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_UPSIDEDOWN, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set SpotMeter    | 1.0 | 1.2 | | Set Camera Spot Meter mode.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.SpotMeter | set 1.2\n get 1.0 | | | Set Camera Spot Meter mode.|
  Keep CGI_VER_MATRIX in one line.*/ // property=SpotMeter&value=...
CGI_RW ncgi_ret Handle_SpotMeter(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(SPOT_METER));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_SPOTMETER, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set LoopingVideo    | 1.0 | 1.2 | | Set Video recording looping mode. Not looping or cut the video for the requested interval.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.LoopingVideo | set 1.2\n get 1.0 | | | Set Video recording looping mode. Not looping or cut the video for the requested interval.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.VideoClipTime | set 1.2\n get 1.0 | | | Set Video recording looping mode. Not looping or cut the video for the requested interval.|
  Keep CGI_VER_MATRIX in one line.*/ // property=LoopingVideo&value=...
CGI_RW ncgi_ret Handle_LoopingVideo(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (ncam_is_recording()) {
        ret.cgi = CGI_ERR_INVALID_STATE;
        ret.netapp = NETAPP_FAIL;
        return ret;
    }

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(LOOPING_VIDEO));
    if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
        ncgi_send_ui_msg(WIRELESS_SET_LOOPINGVIDEO, id, pfn_w, (void*)0);
#else
        //MenuSettingConfig()->uiMOVClipTime = id;
        ImportMenuInfo(MenuSettingConfig());
#endif
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}
// property=VideoQuality&value=...
CGI_RW ncgi_ret Handle_VideoQuality(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (ncam_is_recording()) {
        ret.cgi = CGI_ERR_INVALID_STATE;
        ret.netapp = NETAPP_FAIL;
        return ret;
    }

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(QUALITY));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_VQUALITY, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set HDR    | 1.0 | 1.2 | | Set HDR mode. Typically on or off. |
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.HDR | set 1.2\n get 1.0 | | | Set HDR mode. Typically on or off.|
  Keep CGI_VER_MATRIX in one line.*/ // property=HDR&value=...
CGI_RW ncgi_ret Handle_HDR(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (ncam_is_recording()) {
        ret.cgi = CGI_ERR_INVALID_STATE;
        ret.netapp = NETAPP_FAIL;
        return ret;
    }

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(HDR));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_HDR, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set Q-SHOT    | 1.0 | 1.2 | | Set Q shot mode.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.Q-SHOT | set 1.2\n get 1.0 | | | Set Q shot mode.|
  Keep CGI_VER_MATRIX in one line.*/ // property=Q-SHOT&value=...
CGI_RW ncgi_ret Handle_Q_SHOT(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (ncam_is_recording()) {
        ret.cgi = CGI_ERR_INVALID_STATE;
        ret.netapp = NETAPP_FAIL;
        return ret;
    }

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(Q_SHOT));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_Q_SHOT, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set StatusLights    | 1.0 | 1.2 | | Set status LED. It's typically for customized LED controlling.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.StatusLights | set 1.2\n get 1.0 | | | Set status LED. It's typically for customized LED controlling.|
  Keep CGI_VER_MATRIX in one line.*/ // property=StatusLights&value=...
CGI_RW ncgi_ret Handle_StatusLights(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(STATUS_LIGHTS));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_STATUSLIGHTS, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set SoundIndicator    | 1.0 | 1.2 | | Controls status beeper or speaker. It's typically a customized feature.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.SoundIndicator | set 1.2\n get 1.0 | | | Controls status beeper or speaker. It's typically a customized feature.|
  Keep CGI_VER_MATRIX in one line.*/ // property=SoundIndicator&value=...
CGI_RW ncgi_ret Handle_SoundIndicator(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(SOUND_INDICATOR));
    if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
        // TODO: Sound Indicator ON/OFF
        ncgi_send_ui_msg(WIRELESS_SET_SOUNDINDICATOR, id, pfn_w, (void*)0);
#else
        //MenuSettingConfig()->uiBeep = id;
        ImportMenuInfo(MenuSettingConfig());
#endif
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set PowerSaving    | 1.0 | 1.2 | | Set power saving timer.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.PowerSaving | set 1.2\n get 1.0 | | | Set power saving timer.|
  Keep CGI_VER_MATRIX in one line.*/ // property=PowerSaving&value=...
CGI_RW ncgi_ret Handle_PowerSaving(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(POWER_SAVING));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_POWERSAVING, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set TVSystem    | 1.0 | 1.2 | | Set TV system as NTSC or PAL.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.TVSystem | set 1.2\n get 1.0 | | | Set TV system as NTSC or PAL.|
  Keep CGI_VER_MATRIX in one line.*/ // property=TVSystem&value=...
CGI_RW ncgi_ret Handle_TVSystem(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    // TV Output (NTSC/PAL)
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(TV_SYSTEM));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_TV_SYS, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set TimeFormat    | 1.0 | | | Set Time format, such as YMD or DMY.|
  Keep CGI_VER_MATRIX in one line.*/ // property=TimeFormat&value=...
CGI_RW ncgi_ret Handle_TimeFormat(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    // Time format (YY/MM/DD, DD/MM/YY...)
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (ncam_is_recording()) {
        ret.cgi = CGI_ERR_INVALID_STATE;
        ret.netapp = NETAPP_FAIL;
        return ret;
    }

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(TIME_FMT));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_TIME_FMT, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set LCDPowerSave    | 1.0 | | | Set LCD power saving timer.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.LCDPower | set 1.2\n get 1.0 | | | Set LCD power saving timer.|
  Keep CGI_VER_MATRIX in one line.*/ // property=LCDPowerSave&value=...
CGI_RW ncgi_ret Handle_LCDPowerSave(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    // LCDPowerSave
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(LCD_POWER_SAVE));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_LCD_PWRS, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set GSensor    | 1.0 | | | Set G-sensor sensitivity.|
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.GSensor | set 1.2\n get 1.0 | | | Set G-sensor sensitivity.|
  Keep CGI_VER_MATRIX in one line.*/ //property=GSensor&value=......
CGI_RW ncgi_ret Handle_GsensorSensitivity(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(GSENSOR));
    if (id != INVALID_ID) {
        ncgi_send_ui_msg(WIRELESS_SET_GSENSOR_SENSITIVITY, id, pfn_w, (void*)0);
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

extern char galastdidtoken[];
//property=DidToken&value="did+token"
CGI_RW ncgi_ret Handle_SetDidToken(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret ret;
    NET_DID_ACCESS_CB pdid_token_cb = ncfg_get_didtoken_accessed_cb();

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if(!pdid_token_cb || !gbAllowAppAccss){
        ret.netapp = NETAPP_FAIL;
        return ret;
    }

	printc("%s key=%s DidToken val=%s!!!\r\n",__FUNCTION__,key,val);

    if (val){

        char *p;

        if(pdid_token_cb(1,val,strlen(val)) == 0){
            galastdidtoken[0] = 0;
            strcpy(galastdidtoken,val);
            p = strchr(galastdidtoken,'+');
            if(p)
                *p = 0;
            printc("galastdidtoken=%s\n",galastdidtoken);
        }
    }
    return ret;
}

//propert=UserConfirm
CGI_RW ncgi_ret Handle_UserConfirm(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    ncgi_op_callback(pfn_s);
    ret = ncgi_send_ui_msg(WIRELESS_CONNECTION_CONFIRM, (uint32)val, pfn_w, (void*)11000);
    if(NETAPP_DONE == ret.netapp)
        ncfg_allow_APP_access(1);

    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set PowerOffDelay | 1.0 | 1.2 | | Set power off delay time |
  [CGI_VER_MATRIX]       | set\n get Camera.Menu.PowerOffDelay | set 1.2\n get 1.0 | | | Set power off delay time |
  Keep CGI_VER_MATRIX in one line.*/ // property=PowerOffDelay&value=...
CGI_RW ncgi_ret Handle_PowerOffDelay(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    // LCDPowerSave
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(OFF_DELAY));
    if (id != INVALID_ID) {
#if 1 //Andy Liu TBD
        ncgi_send_ui_msg(WIRELESS_SET_POWROFF_DELAY, id, pfn_w, (void*)0);
#else
        //MenuSettingConfig()->uiMOVPowerOffTime = id;
        ImportMenuInfo(MenuSettingConfig());
#endif
    } else {
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set SD0 | 1.0 | 1.1 | | `value=format` to format SD card to Camera preferred format. |
  [CGI_VER_MATRIX]       | get Camera.Menu.SD0 | 1.0 | 1.1 | | `value=format` to format SD card to Camera preferred format. |
  Keep CGI_VER_MATRIX in one line.*/ // property=SD0&value=format
CGI_RW ncgi_ret Handle_SD0(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (ncam_is_recording()) {
        ret.cgi = CGI_ERR_INVALID_STATE;
        ret.netapp = NETAPP_FAIL;
        return ret;
    }

    id = GetMenuIDbyCGIval(val, ncgi_get_menu(SD0));
    if (id != INVALID_ID) {
        // TODO: Format SD0
        //ncgi_send_ui_msg(WIRELESS_FORMAT_SD0, id, pfn_w, (void*)0);
        //printc(">>>>> %s,%d Wifi TBD. <<<<<\r\n",__func__,__LINE__); //Andy Liu TBD
        _format_sd = FORMAT_SD_DOING;
        if (AHC_FormatStorageMedia(AHC_MEDIA_MMC) &&
            AHC_MountStorageMedia(AHC_MEDIA_MMC)  &&
            AHC_RemountDevices(MenuSettingConfig()->uiMediaSelect)) {
            _format_sd = FORMAT_SD_DONE;
        } else {
            _format_sd = FORMAT_SD_ERROR;
        }
    } else {
        _format_sd = FORMAT_SD_ERROR;
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

// property=FactoryReset&value=Camera
CGI_WO ncgi_ret Handle_FactoryReset(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id = 0;
    ncgi_ret ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (ncam_is_recording()) {
        ret.cgi = CGI_ERR_INVALID_STATE;
        ret.netapp = NETAPP_FAIL;
        return ret;
    }

    if (id != INVALID_ID) {
        printc("Factory Reset!! - %s\n", key);
        if (stricmp(key, "Camera") == 0) {
            // TODO: Do factory reset
            //void RestoreFromDefaultSetting(void);
            //RestoreFromDefaultSetting();
            AHC_RestoreFromDefaultSetting();//CarDV
        }
    } else {
        //_format_sd = FORMAT_SD_ERROR;
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

#ifdef NET_SYNC_PLAYBACK_MODE
/* Used in NCGI_VERSION: | Command      | Since  | Obsolete  | Removed | Remarks |
  [CGI_VER_MATRIX]       | set Playback | 1.1 | | | Enter/Leave UI_NET_PLAYBACK_STATE.\n APP also sends heart beat periodically to notify Camera that it's still alive.\n **Plan to use UIMode for entering and leaving.** |
  Keep CGI_VER_MATRIX in one line.*/ // property=Playback&value=[enter|exit|heartbeat]
CGI_WO ncgi_ret Handle_Playback(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    ncgi_ret        ret;

    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (stricmp(val, "heartbeat") == 0){
        ret = ncgi_send_ui_msg(WIRELESS_PLAYBACK_HEARTBEAT, 0, NULL, NULL);
    }
    else if (stricmp(val, "enter") == 0){
        ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_ENTER_PLAYBACK, 0, pfn_w, STD_CGI_TIME_OUT);
    }
    else{
        ncgi_op_callback(pfn_s);
        ret = ncgi_send_ui_msg(WIRELESS_EXIT_PLAYBACK, 0, pfn_w, STD_CGI_TIME_OUT);
    }
    return ret;
}
#endif

// property=Camera.Preview.Adas.SaveData
#define ADAS_CFG_TAG "Camera.Preview.Adas.SaveData"
CGI_RW ncgi_ret Handle_AdasSaveData(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int id = 0;
    ncgi_ret ret;
    printc(BG_RED("AdasSaveData: Need to Link to ldws_set_roi()\r\n"));
    ret.cgi = CGI_RET_UNASSIGNED;
    ret.netapp = NETAPP_DONE;

    if (id != INVALID_ID) {
        //printc("AdasSaveData Reset!! - %s\n", key);

    } else {
        //_format_sd = FORMAT_SD_ERROR;
        ret.cgi = CGI_ERR_INVALID_PARAM;
        ret.netapp = NETAPP_FAIL;
    }
    return ret;
}

#define CGI_CMD(k)  (k), sizeof(k) - 1
/* Note: the key compared with cmdKeyLen, be care for cmdKey being Substring of key */
CGI_HANDLER cgi_handler[] = {
    {CGI_CMD("UIMode"),         Handle_UIMode},
    {CGI_CMD("DefMode"),        Handle_DefMode},
    {CGI_CMD("Video"),          Handle_VideoOperation},
    {CGI_CMD("Videores"),       Handle_VideoResolution},
    {CGI_CMD("VideoClipTime"),  Handle_LoopingVideo},
    {CGI_CMD("VideoQuality"),   Handle_VideoQuality},
    {CGI_CMD("Imageres"),       Handle_ImageResolution},
    {CGI_CMD("Exposure"),       Handle_EV},
    {CGI_CMD("EV"),             Handle_EV},
    {CGI_CMD("MTD"),            Handle_MTD},
    {CGI_CMD("Flicker"),        Handle_Flicker},
    {CGI_CMD("Net"),            Handle_Net},
    {CGI_CMD(MJPEG_CFG_TAG),    Handle_MJPEG},
    {CGI_CMD("TimeSettings"),   Handle_TimeSettings},
    {CGI_CMD("AWB"),            Handle_WB},
    {CGI_CMD("PhotoBurst"),     Handle_PhotoBurst},
    {CGI_CMD("Timelapse"),      Handle_Timelapse},
    {CGI_CMD("UpsideDown"),     Handle_UpsideDown},
    {CGI_CMD("SpotMeter"),      Handle_SpotMeter},
    {CGI_CMD("LoopingVideo"),   Handle_LoopingVideo},
    {CGI_CMD("HDR"),            Handle_HDR},
    {CGI_CMD("Q-SHOT"),         Handle_Q_SHOT},
    {CGI_CMD("StatusLights"),   Handle_StatusLights},
    {CGI_CMD("Camera.Menu.SoundIndicator"), Handle_SoundIndicator},
    {CGI_CMD("SoundIndicator"), Handle_SoundIndicator},
    {CGI_CMD("PowerSaving"),    Handle_PowerSaving},
    {CGI_CMD("TVSystem"),       Handle_TVSystem},
    {CGI_CMD("Beep"),           Handle_SoundIndicator},
    {CGI_CMD("AutoPowerOff"),   Handle_PowerSaving},
    {CGI_CMD("TimeFormat"),     Handle_TimeFormat},
    {CGI_CMD("LCDPowerSave"),   Handle_LCDPowerSave},
    {CGI_CMD("PowerOffDelay"),  Handle_PowerOffDelay},
    {CGI_CMD("SD0"),            Handle_SD0},
    {CGI_CMD("FactoryReset"),   Handle_FactoryReset},
    {CGI_CMD(ADAS_CFG_TAG),     Handle_AdasSaveData},
#ifdef NET_SYNC_PLAYBACK_MODE
    {CGI_CMD("Playback"),       Handle_Playback},
#endif
    {CGI_CMD("GSensor"),        Handle_GsensorSensitivity},
    {CGI_CMD("WiFi"),           Handle_Wifi},
    {CGI_CMD("DidToken"),       Handle_SetDidToken},
    {CGI_CMD("UserConfirm"),    Handle_UserConfirm},
    // End of Map
    {NULL, 0}
};

/*
 * the command has not processed yet -> return  0
 * the command processes failed      -> return -2
 * the command processed             -> return -1
 */
ncgi_ret ncgi_send_ui_event(char *key, char *val, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    UINT8 ubCurUIState = 0;
    UI_STATE_ID ubParentUIState = 0;

    ubCurUIState = uiGetCurrentState();

    // UI_NET_STREAMING_STATE can also receive CGI command.
    if(!((UI_NET_STREAMING_STATE == ubCurUIState) || (UI_NET_CGICMD_STATE == ubCurUIState))){

        StateModeGetParent(ubCurUIState, &ubParentUIState);
        if(UI_STATE_UNSUPPORTED != ubParentUIState){
            printc("%s,%d, DettachSubMode:%d\r\n", __FUNCTION__, __LINE__, ubCurUIState);
            ahcRet = StateDetachSubMode();
            if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); /*return 0;*/}
        }

    #if defined(DBG_UI_NET_EVENT) && DBG_UI_NET_EVENT
        printc(FG_GREEN(" + UI_NET_CGICMD_STATE")"\r\n");
    #endif
        ahcRet = StateAttachSubMode(UI_NET_CGICMD_STATE);
        if(ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0/*gbAhcDbgBrk*/, ahcRet); /*return 0;*/}
    }

    return cgi_handle_net_cmd(cgi_handler, key, val, pfn_w, pfn_s);

}

//
int ncgi_flash_fw(char *filename, PFN_WEBWAIT pfn_w, PFN_CGI_OP_CALLBACK pfn_s)
{
    int     ret;

    printc("Flash FW in %s\n", (filename == NULL)? "CALL DEFAULT" : filename);
    ncgi_op_callback(pfn_s);
    // ret = ncgi_send_ui_msg(WIRELESS_SET_UIMODE, id, pfn_w, STD_CGI_TIME_OUT);

    //printc(">>>>> %s,%d Wifi TBD. <<<<<\r\n",__func__,__LINE__);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, EVENT_NET_FWUPDATE_FROM_SD, 6000);

    if (pfn_w) {
        // Wait
        //printc(">>>>> %s,%d Wifi TBD. <<<<<\r\n",__func__,__LINE__);
        ret = pfn_w((void*)EVENT_NET_FWUPDATE_FROM_SD, STD_CGI_TIME_OUT);

        printc("--> COMMAND FINISH %d\n", ret);
        if (ret >= 0)
            return NETAPP_DONE;
        else
            return NETAPP_FAIL;
    }
    return NETAPP_DONE;
}

#define PREOID_TO_BROADCAST (2 * 1000)  // 2 seconds
#define TIMES_UI_BROADCAST  3
#define PACK_VERSION        NCGI_VERSION
#define BROADCAST_TIME_OUT  (TIMES_UI_BROADCAST * PREOID_TO_BROADCAST)

static unsigned int bc_uiticket = 0;
typedef struct {
    int             ticket;
    int             times;
    int             version;
    int             checkSumReady;
    time_t          unixtime;
    osl_ext_sem_t   sem;
    MMPF_OS_TMRID   tid;
    notify_reason_t *notification;
} BROADCAST_PACK;
static BROADCAST_PACK   bcpack = {0};
//static void Broadcast_UIChanged(void *p1, void* p2);

typedef struct _notify_reason_t {
    int     reason;
    int     shots;
    int     datalen;
    char    *customized_data;
    char    data[32];
} notify_reason_t;

static notify_reason_t _nrson = { 0 };

void ncgi_notify_set_len(notify_reason_t* notify, int datalen)
{
    if (notify)
        notify->datalen = datalen;
}

notify_reason_t* ncgi_notify_uiroll(int reason, void *data)
{
    char *customized_data = NULL;
    if (_nrson.reason != NOTIFY_NULL) {
        printc(BG_RED("%s %d: There is a notification (%d) not to send yet!!!")"\r\n",
					__FUNCTION__, __LINE__, _nrson.reason);
        return NULL;
    }
    switch (reason) {
    case NOTIFY_CAPTURE:
    case NOTIFY_TIMELAPSE:
        _nrson.shots  = 1;
        sprintf(_nrson.data, "%u", (unsigned int)AHC_StreamingTimer_GetMs());
        break;
    case NOTIFY_TIMELAPSE_STOP:
        _nrson.shots  = 1;
        sprintf(_nrson.data, "%s", "STOP");
        break;
    case NOTIFY_FWUPDATED:
        _nrson.shots  = 1;
        sprintf(_nrson.data, "%s", ((int)data == 0)? "done" : "failed");
        break;
    case NOTIFY_CUSTOMIZE:
        _nrson.shots = 3;
        customized_data = data;
        break;
    default:
        printc(FG_RED("[ERR] Unknown reason %d")"\r\n", reason);
        return NULL;
        break;
    }
    _nrson.customized_data = customized_data;
    _nrson.reason = reason;
    return &_nrson;
}

#if defined(__RTK_OS__)
//typedef void (*MMPF_OS_TMR_CALLBACK)(MsTimerId_e eTimerID,u32 UserData);
static void Broadcast_UIChanged(MsTimerId_e eTimerID,u32 UserData)
{
    SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_UINOTIFY);
}

#else
/*
 *
 */
static void Broadcast_UIChanged(void *p1, void* p2)
{
    SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_UINOTIFY);
}
#endif

/* Notify that UI has been changed via CGI
 * ncgi_notify_uichange
 * Call by UI when something changed, like as settings,
 * start to video record/continuous snapshot by key
 */
int ncgi_notify_uichange(notify_reason_t* somethingchanged)
{
    unsigned int        netstatus;
    notify_reason_t*    reas;
    int bSkipBroadcast = 0;

    netstatus = nhw_get_status();
    if (netstatus == NETAPP_NET_STATUS_NONE ||
        netstatus == NETAPP_NET_STATUS_INIT ||
        netstatus == NETAPP_NET_STATUS_DOWN) {
        // network isn't ready, not to do anything!!
        return -1;
    }
    if (bcpack.sem == 0) {
        if (osl_ext_sem_create(NULL, 1, &bcpack.sem) != OSL_EXT_SUCCESS) {
			printc("%s %d: Create Sem ERROR\n", __FUNCTION__, __LINE__);
        }
    }
    // Check broadcast running and stop it
    // Avoid ncgi_send_camera_state called during setup
    if (bcpack.sem != 0 &&
        osl_ext_sem_take(&bcpack.sem, BROADCAST_TIME_OUT) != OSL_EXT_SUCCESS) {
		printc(BG_RED("%s %d: Sem Timeout or ERROR\n"), __FUNCTION__, __LINE__);
    }

    //if (bcpack.notification && bcpack.notification->reason == NOTIFY_CUSTOMIZE) {
    if (bcpack.notification && bcpack.notification->reason != NOTIFY_NULL) {
        bSkipBroadcast = -2;
		printc(FG_YELLOW("%s %d: Not broadcasting reason:%d")"\r\n", __FUNCTION__, __LINE__, bcpack.notification->reason);
    }
    if (bSkipBroadcast == 0) {
        if (bcpack.tid != 0) {
            MMPF_OS_StopTimer(bcpack.tid, MMPF_OS_TMR_OPT_NONE);
        }
        reas = /*(notify_reason_t*)*/somethingchanged;
        bcpack.tid     = 0;
        bcpack.ticket  = ++bc_uiticket;
        bcpack.unixtime= time(NULL);
        bcpack.version = PACK_VERSION;
        bcpack.times   = (reas == NULL)? TIMES_UI_BROADCAST - 1 : reas->shots - 1;
        bcpack.notification    = /*(void*)*/reas;
        bcpack.checkSumReady = 0;

        SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_UINOTIFY);
    }
    if (bcpack.sem != 0)
        osl_ext_sem_give(&bcpack.sem);
    return bSkipBroadcast;
}


static unsigned int checksum(char* buf)
{
    unsigned int    i, sum;

    for (i = 0, sum = 0; *(buf + i) != 0; i++)
        sum += *(buf + i);
    return sum;
}

//all file name are full file path
struct boradcast_t {
    char fn[NCGI_MAX_FN_NUM][MAX_FULL_FILENAME_SIZE];
} m_broadcast_fn;


int ncgi_notify_fn(int type, char* full_fn)
{
    char *fn = m_broadcast_fn.fn[type];
    if (type >= NCGI_MAX_FN_NUM) {
        return -1;
    }
    strncpy(fn, full_fn, MAX_FULL_FILENAME_SIZE);
    //later while file server reports back to UI. It would be converted into FS naming.
    //(SD:\\). so the convert is not needed and is done in APP side.
    //ns_convert_fn_fs_to_web(fn, NULL);
    ncgi_notify_uichange(NCGI_DEF_REASON);
    return 0;
}

int ncgi_get_notify_fn(int type, char** full_fn)
{
    char *fn = m_broadcast_fn.fn[type];
    if (type >= NCGI_MAX_FN_NUM) {
        return -1;
    }
    *full_fn = fn;
    if (fn[0] == '\0') {
        return -1; //empty string
    }
    return 0;
}

int ncgi_clr_notify_fn(int type, char* full_fn)
{
    //char *fn = m_broadcast_fn.fn[type];
    int from = 0, to = NCGI_MAX_FN_NUM - 1;
    int i;

    if (type > NCGI_ANY_FN || (full_fn == NULL)) {
        return -1;
    }
    if (type < NCGI_MAX_FN_NUM) {
        from = to = type;
    }
    for (i = from; i <= to; ++i) {
        if (strncmp(full_fn, m_broadcast_fn.fn[i], MAX_FULL_FILENAME_SIZE) == 0) {
            m_broadcast_fn.fn[i][0] = '\0';
            return 0;
        }
    }
    return -1; //not found
}

#define N(p, m) (*(((unsigned char*)(&p)) + m))
//add standard broadcast header
int ncgi_notify_add_std_hdr(BROADCAST_PACK *ppack, char* list, int len, int maxlen)
{
    unsigned int    ip;

    ip = nhw_get_ip_addr();
    len += snprintf(list + len, maxlen - len, "IP=%u.%u.%u.%u\n", N(ip, 0), N(ip, 1), N(ip,2), N(ip, 3));
    len += snprintf(list + len, maxlen - len,   "ver=%d\n",     ppack->version);
    len += snprintf(list + len, maxlen - len,   "ticket=%u\n",  ppack->ticket);
    return len;
}

/*
 *
 */
#define BROADCAST_BUFFER_MAXLEN 4096
static int collectChanged(BROADCAST_PACK *ppack, char **buf)
{
    char            *list;
    int             len, maxlen;
    unsigned int    ip;
    int             customized = 0;

    ip = nhw_get_ip_addr();
    if (buf == NULL) return 0;
    maxlen = BROADCAST_BUFFER_MAXLEN;
    *buf = NULL;
    if (ppack->notification == NULL || ppack->notification->reason != NOTIFY_CUSTOMIZE) {
        list = osal_malloc(maxlen);
    } else {
        list = ppack->notification->customized_data;
        customized = 1;
    }
    if (list == NULL) return 0;
    len = 0;
    if (ppack->notification != NULL) {
        notify_reason_t*    reas = /*(notify_reason_t*)*/ppack->notification;
        switch(reas->reason) {
        case NOTIFY_CAPTURE:
            len += snprintf(list + len, maxlen - len, "Capturing=%s\n", reas->data);
            break;
        case NOTIFY_TIMELAPSE:
        case NOTIFY_TIMELAPSE_STOP:
            len += snprintf(list + len, maxlen - len, "Timelapse=%s\n", reas->data);
            break;
        case NOTIFY_FWUPDATED:
            len += snprintf(list + len, maxlen - len, "fwflash=%s\n", reas->data);
            break;
        case NOTIFY_CUSTOMIZE:
            len = reas->datalen;
            break;
        default:
            printc(FG_RED("unrecognized reason %d")"\r\n", reas->reason);
            break;
        }
        if (ppack->times < 1)
            reas->reason = NOTIFY_NULL; // Clean, allow next to send
    } else {
        char *fn;
        struct NS_ON_CGI_BUF_PARAM param;
        NS_EV_RET ret;

        //common list items prologue
        len += snprintf(list + len, maxlen - len, "IP=%u.%u.%u.%u\n", N(ip, 0), N(ip, 1), N(ip,2), N(ip, 3));
        len += snprintf(list + len, maxlen - len,
                        "ver=%d\n",     ppack->version);
        len += snprintf(list + len, maxlen - len,
                        "ticket=%u\n",  ppack->ticket);

        param.maxlen = maxlen;
        param.curLen = &len;
        param.listBuf = list;
        ret = ns_handle_event(NS_EVENT_BROADCAST_PROLOGUE, &param);
        if (ANY_NS_ERR(ret) && (ret != NSE_CB_NOT_FOUND)) {
            printc("Broadcast prologue err:%d\r\n", ret);
            goto cut_list;
        }

        if (ncgi_get_notify_fn(NCGI_SHORT_FN, &fn) == 0) {
        //if (AHC_TRUE == AHC_VIDEO_GetShareRecdFileName(&fn, AHC_TRUE)) {
            len += snprintf(list + len, maxlen - len,
                        "shortFn=%s\n", fn);
        }

#if (EMER_RECORD_DUAL_WRITE_ENABLE == 1)
        if (ncgi_get_notify_fn(NCGI_EMER_FN, &fn) == 0) {
            len += snprintf(list + len, maxlen - len,
                        "emerFn=%s\n", fn);
        }
#endif
        if (ncgi_get_notify_fn(NCGI_VR_CAP_FN, &fn) == 0) {
            len += snprintf(list + len, maxlen - len,
                        "VRCapFn=%s\n", fn);
        }
        if (ncgi_get_notify_fn(NCGI_DL_FN, &fn) == 0) {
            len += snprintf(list + len, maxlen - len,
                        "dlFn=%s\n", fn);
        }
        len += snprintf(list + len, maxlen - len,
                        "time=%u\n",    (unsigned int)ppack->unixtime);
        len += snprintf(list + len, maxlen - len,
                        "Videores=%s\n", ncgi_get_video_res());
        len += snprintf(list + len, maxlen - len,
                        "Imageres=%s\n", ncgi_get_image_res());
        len += snprintf(list + len, maxlen - len,
                        "UIMode=%s\n", ncgi_get_ui_state());
        len += snprintf(list + len, maxlen - len,
                        "AWB=%s\n",     ncgi_get_wb());
        len += snprintf(list + len, maxlen - len,
                        "Flicker=%s\n", ncgi_get_flicker_hz());
        len += snprintf(list + len, maxlen - len,
                        "Timelapse=%s\n",   ncgi_get_timelapse());
        len += snprintf(list + len, maxlen - len,
                        "PhotoBurst=%s\n",  ncgi_get_photo_burst());
        len += snprintf(list + len, maxlen - len,
                        "Upsidedown=%s\n",  ncgi_get_up_side_down());
        len += snprintf(list + len, maxlen - len,
                        "HDR=%s\n", ncgi_get_hdr());
        len += snprintf(list + len, maxlen - len,
                        "LoopingVideo=%s\n",ncgi_get_looping_video());
        len += snprintf(list + len, maxlen - len,
                        "SpotMeter=%s\n",   ncgi_get_spot_meter());
        len += snprintf(list + len, maxlen - len,
                        "Q-SHOT=%s\n",  ncgi_get_q_shot());
        len += snprintf(list + len, maxlen - len,
                        "StatusLights=%s\n",ncgi_get_status_lights());
        len += snprintf(list + len, maxlen - len,
                        "SoundIndicator=%s\n",  ncgi_get_sound_indicator());
        len += snprintf(list + len, maxlen - len,
                        "PowerSaving=%s\n", ncgi_get_power_saving());
        len += snprintf(list + len, maxlen - len,
                        "TVSystem=%s\n",    ncgi_get_tv_system());
        len += snprintf(list + len, maxlen - len,
                        "EV=%s\n",      ncgi_get_ev_level());
        len += snprintf(list + len, maxlen - len, "Recording=%s\n",
                        ncam_is_recording()? "YES" : "NO");
        len += snprintf(list + len, maxlen - len, "Streaming=%s\n",
                        (ncam_get_streaming_mode())? "YES" : "NO");
        len += snprintf(list + len, maxlen - len,
                        "TV=%s\n", ncgi_get_tv_status());
        len += snprintf(list + len, maxlen - len,
                        "SD0=%s\n", ncam_get_ui_sd0_status());
        len += snprintf(list + len, maxlen - len,
                        "Power=%d\n", ncam_get_ui_power_level());
        len += snprintf(list + len, maxlen - len,
                        "LDWS=%s\n", netapp_get_LdwsResult());
        len += snprintf(list + len, maxlen - len,
                        "FCWS=%s\n", netapp_get_LdwsResult());
        len += snprintf(list + len, maxlen - len,
                        "SAG=%s\n", netapp_get_SagResult());

        ret = ns_handle_event(NS_EVENT_BROADCAST_EPILOGUE, &param);
        if (ANY_NS_ERR(ret) && (ret != NSE_CB_NOT_FOUND)) {
            printc("Broadcast epilogue err:%d\r\n", ret);
            goto cut_list;
        }
    }

cut_list://when callback function has any error, skip the rest of the list

    // end of data, add new status before this line
    if (!ppack->checkSumReady) {
        if (customized) {
            //append header
            len = ncgi_notify_add_std_hdr(ppack, list, len, maxlen);
        }
        len += snprintf(list + len, maxlen - len, "CHKSUM=%u", checksum(list));
        if (len > maxlen) {
            printc(BG_RED("FATAL ERROR! %s %d: need len %d but MAXLEN %d\n"),
					__FUNCTION__, __LINE__, len, maxlen);
        }
        if (ppack->notification != NULL) {
            ppack->notification->datalen = len;
        }
        ppack->checkSumReady = 1;
    }
    *buf = list;
    return len;
}
/*
 * ncgi_send_camera_state()
 */
#define BROADCAST_IP   "255.255.255.255"
#define BROADCAST_PORT 49142
void ncgi_send_camera_state(void)
{
    SOCKET brsock;
    struct sockaddr_storage __ss;
    struct sockaddr_in *DestAddr4 = (struct sockaddr_in *)&__ss;
    socklen_t socklen = sizeof(struct sockaddr_storage);
    unsigned long replyAddr = web_server_get_ip_int();//inet_addr(gIF_IPV4);
    int ttl = 4;
    ssize_t rc;
    char            *data;
    unsigned int    len;
    BROADCAST_PACK  *ppack = &bcpack;

    // Avoid ncgi_notify_uichange called during broadcasting
    if (ppack->sem != 0 &&
        osl_ext_sem_take(&ppack->sem, BROADCAST_TIME_OUT) != OSL_EXT_SUCCESS) {
		printc("%s %d: Sem Timeout or ERROR\n", __FUNCTION__, __LINE__);
    }
    len = collectChanged(ppack, &data);
    if (len == 0) {
		printc("ERROR: %s %d: Length %d\n", __FUNCTION__, __LINE__, len);
        goto end_SendCameraState;
    }
    memset(&__ss, 0, sizeof(__ss));
    DestAddr4->sin_family = (sa_family_t)AF_INET;
    inet_pton(AF_INET, BROADCAST_IP, &DestAddr4->sin_addr);
    DestAddr4->sin_port = htons(BROADCAST_PORT);

    brsock = net_socket((int)DestAddr4->sin_family, SOCK_DGRAM, 0);
    if (brsock == INVALID_SOCKET) {
        goto end_SendCameraState;
    }
    net_setsockopt(brsock, IPPROTO_IP, IP_MULTICAST_IF,
           (char *)&replyAddr, sizeof(replyAddr));
    net_setsockopt(brsock, IPPROTO_IP, IP_MULTICAST_TTL,
           (char *)&ttl, sizeof(int));
    socklen = sizeof(struct sockaddr_in);
    rc = net_sendto(brsock, (const void*)data,
            len, 0, (const struct sockaddr *)DestAddr4, socklen);
    if (rc == -1) {
        goto end_NewRequestHandler;
    }

 end_NewRequestHandler:
    if (net_shutdown(brsock, SD_BOTH) == -1) {
    }
    net_close(brsock);
    //
    // Trigger next
    if (ppack->tid != 0) {
        MMPF_OS_StopTimer(ppack->tid, MMPF_OS_TMR_OPT_NONE);
        ppack->tid = 0;
    }
    // Trigger for next broadcasting
    if (ppack->times != 0) {
        ppack->times--;
        //printc("%s %d: %d\n", __func__, __LINE__, ppack->times);
        ppack->tid = MMPF_OS_StartTimer(PREOID_TO_BROADCAST,
                                        MMPF_OS_TMR_OPT_ONE_SHOT,
                                        Broadcast_UIChanged,
                                        ppack);
        //printc("%s %d: NEXT timer id %u\n", __func__, __LINE__, ppack->tid);
        if (ppack->tid == MMPF_OS_CREATE_TMR_INT_ERR) {
			printc("FATAL ERROR:%s %d Timer failed!\n", __FUNCTION__, __LINE__);
        }
    }
end_SendCameraState:
    if (bcpack.notification == NULL || (bcpack.notification->reason != NOTIFY_CUSTOMIZE)) {
        if (data) osal_free(data);
        if (bcpack.notification) bcpack.notification = NULL;
    }
    if (bcpack.sem != 0)
        osl_ext_sem_give(&bcpack.sem);
    //
    return;
}

//from webserver.c, not in webserver.h
extern void acquire_cgi_Callback(void);
extern void release_cgi_Callback(void);
extern osl_ext_sem_t _streaming_op_sem;

static int  _streaming_op_uiret;
int wait_streaming_op_uiproc(void *handle, void *arg)
{
    //printc("%s %d\r\n", __func__, __LINE__);
    if (osl_ext_sem_take(&_streaming_op_sem, (osl_ext_time_ms_t)arg) == OSL_EXT_SUCCESS) {
        return _streaming_op_uiret;
    } else {
        printc(FG_RED("take _streaming_op_sem timeout!!\n"));
        return -100;    // timeout!!
    }
}

int nstreaming_op_feedback(void *handle, int result)
{
	int16 count;

	//printc(__FUNCTION__ " ret:%d\r\n", (int)result);
	_streaming_op_uiret = result;
	osl_ext_sem_query(&_streaming_op_sem, (uint16*)&count);

	if(count <= 0)
		osl_ext_sem_give(&_streaming_op_sem);
	return 1;
}

static PFN_CGI_OP_CALLBACK pfn_CGIop_callback = NULL;
static AHC_BOOL bAcquire_cgi_Callback = AHC_FALSE;
int ncgi_op_callback(PFN_CGI_OP_CALLBACK pfn)
{
    if(pfn_CGIop_callback){
        bAcquire_cgi_Callback = AHC_TRUE;
        acquire_cgi_Callback();
    }
    pfn_CGIop_callback = pfn;
    return 0;
}

int ncgi_is_need_feedback(void)
{
    if(pfn_CGIop_callback)
        return 1;
    return 0;
}
/*
 * Call by UI/AHC, after finished the CGI request to call this function
 * with the result.
 * handle is a value of enum WIRELESS_CONNECT_MESSAGE
 * result: < 0 - failed, others - success
 */
#if CGIOP_DBG
int ncgi_op_feedback_dbg(void *handle, enum cgi_err_t result, char *callfile, int line)
#else
int ncgi_op_feedback(void *handle, enum cgi_err_t result)
#endif
{
#if CGIOP_DBG
	printc(FG_YELLOW("%s: CALL from %s %d\n"), __FUNCTION__, callfile, line);
#endif
    if (pfn_CGIop_callback) {//typically calls webwait_uisignal
    #if CGIOP_DBG_INFO
		printc("%s:Handle %d(0x%X) RESULT %d\n", __FUNCTION__, (int)handle, (int)handle, result);
    #endif
        pfn_CGIop_callback(handle, result);
        pfn_CGIop_callback = NULL;
        if(bAcquire_cgi_Callback){
            release_cgi_Callback();
            bAcquire_cgi_Callback = AHC_FALSE;
        }
        return 1;
    }
    return 0;
}

#if 0
void ____ncfg____() {} //dummy. Network Configuration. Functions that uses net conf info
#endif

static CUSTOMIZED_SSIDPSWD_CB gfpCustomSSIDcb = NULL;
static NET_DID_ACCESS_CB    gfpDiDTokencb = NULL;

/** @brief Get resolution from conf setting
 *
 *  @param[in] conf The starting prefix of network config. The naming convention would be "[conf].w" and "[conf].w"
 *                  e.g. pass "Camera.Preview.H264" and this function will find
 *                  "Camera.Preview.H264.w" and "Camera.Preview.H264.h"
 * @param[out] w Width
 * @param[out] h Height
 * @return 0 for success. -1 for fail
 */
int ncfg_get_v_res(const char *conf, int *w, int *h)
{
#define CONF_STR_LEN (64)
    char conf_str[CONF_STR_LEN];
    int ret;

    snprintf(conf_str, CONF_STR_LEN, "%s.w", conf);
    ret = ncfg_get(conf_str, w);
    if (ret < 0) {
        return -1;
    }
    snprintf(conf_str, CONF_STR_LEN, "%s.h", conf);
    ret = ncfg_get(conf_str, h);
    if (ret < 0) {
        return -1;
    }
    return 0;
}

//Get H.264 resolution from net configuration (.conf file)
int ncfg_get_h264_res(int *conf_w, int *conf_h)
{
    int ret;

    ret = ncfg_get_v_res("Camera.Preview.H264", conf_w, conf_h);
    if (ret != 0) {
        printc("Unable to get H.264 resolution from conf\r\n");
        return -1;
    }
    return 0;
}

//Get H.264 bit rate from net configuration (.conf file)
int ncfg_get_h264_bitrate(void)
{
    UINT32 bitrate;
    int result;

    result = ncfg_get(NCFG_H264_BITRATE, &bitrate);
    if (result < 0 || bitrate < 50*1000) {
        printc(FG_YELLOW("[WARN]")" Invalid H.264 bitrate! Set to default bitrate 1mps\r\n");
        bitrate = 1000000;
    }

    return bitrate;
}


// Save network configures in storage
int ncam_save_net_conf(void)
{
	#if(AHC_USER_SFBACKUP)
	if(ulSFUSERActiveNO == SF2_ACTIVE)
		return export_net_config_file(CONFIG_SPACE_TYPE_CURRENT, NCFG_USERSET_SF3);
	else if(ulSFUSERActiveNO == SF3_ACTIVE)
		return export_net_config_file(CONFIG_SPACE_TYPE_CURRENT, NCFG_USERSET_SF2);
	else
	{
		printc(BG_RED("Abnormal SF active partition")"\r\n", 1);
		return 1;
	}
	#else
    return export_net_config_file(CONFIG_SPACE_TYPE_CURRENT, NCFG_USERSET_FILE_NAME);
	#endif
}

int ncfg_get(char* key, void* val)
{
    struct amn_cfgspace_value_t *cfg_val;
    char* cfg_name = key;
    int i = amn_config_locate(key);
    if (i >= 0) {
        cfg_val  = amn_config_get( CONFIG_SPACE_TYPE_CURRENT, cfg_name );
        if (cfg_val->type == CFGSPACE_VALTYP__STR)
            val = cfg_val->v.strVal;
        else if (cfg_val->type == CFGSPACE_VALTYP__INT)
            *(int*)val = cfg_val->v.intVal;
        else
            return -1;  // ERROR!!
    }
    return i;
}

int ncfg_set(char* key, void* val)
{
    struct amn_cfgspace_value_t *cfg_val;
    char* cfg_name = key;
    int i = amn_config_locate(key);
    if (i >= 0) {
        cfg_val  = amn_config_get( CONFIG_SPACE_TYPE_CURRENT, cfg_name );
        if (cfg_val->type == CFGSPACE_VALTYP__STR){
            if(cfg_val->max_strlen < strlen((char *)val))
                return -1;  // ERROR!!
            *cfg_val->v.strVal = 0;
            strcpy(cfg_val->v.strVal,(char *)val);
        }
        else if (cfg_val->type == CFGSPACE_VALTYP__INT)
            cfg_val->v.intVal = *(int*)val;
        else
            return -1;  // ERROR!!
    }
    return i;
}
/*
@brief : For cuntomized WIFI SSID & Password
- UI decide the rule in the callback function.
- Must be called/registered by UI before network initialization.
@param[in]:
The callback function will be triggered as :
- The first time of network initialization
- The SSID which is in the facrtory setting(SF:1:\\defnetconf.txt) is the same with Current SSID,
    that is, there is no custmoer's SSID in the user setting(SF:1:\\usernetconf.txt).
*/
void ncfg_register_customer_ssidpswd(CUSTOMIZED_SSIDPSWD_CB cb)
{
    gfpCustomSSIDcb = cb;
    return;
}

CUSTOMIZED_SSIDPSWD_CB ncfg_get_customized_ssid_cb(void)
{
    return gfpCustomSSIDcb;
}

void ncfg_register_didtoken_accessed(NET_DID_ACCESS_CB cb)
{
    gfpDiDTokencb = cb;
    return;
}

NET_DID_ACCESS_CB ncfg_get_didtoken_accessed_cb(void)
{
    return gfpDiDTokencb;
}

void ncfg_allow_APP_access(int alloworreject)
{
    gbAllowAppAccss = alloworreject;
}

#if 0
void ____netapp____() {} //dummy.
#endif
// To protect between GET-VIDEO-THUMBNAIL and CAPTURE/BURST/TIMELAPSE
// to avoid system crashing.
// return 0 - successful, go ahead
//        1 - failed, encode JPEG is busy
#if LOCK_DEBUG
int netapp_cap_lock_dbg(int enLock, unsigned int timeout, char *f, int l)
#else
int netapp_cap_lock(int enLock, unsigned int timeout)
#endif
{
    static MMPF_OS_SEMID    _capsemi = -1;
    unsigned char           ret;
    unsigned short          cnt;

#if LOCK_DEBUG
	printc(FG_RED("%s %d (%d): %s %d\n"), __FUNCTION__, enLock, timeout, f, l);
#endif
    if (_capsemi == -1) {
        if (osal_mutex_init(&_capsemi)) {
            // ERROR! System resource is not enough!!
            _capsemi = -1;
			printc(BG_RED("%s %d: Create semi Error!\n"), __FUNCTION__, __LINE__);
            return 0;   // go ahead!!
        }
    }
    if (osal_mutex_queryEx(&_capsemi, &cnt)) {
        // ERROR!, for debug
		printc(BG_RED("%s %d: QUERY semi Error!")"\r\n", __FUNCTION__, __LINE__);
        return 0;   // go ahead!!
    }
    if (enLock) {
        if (cnt == 0 && timeout == 0)
            return 1;
        if (cnt > 1) {
            // ERROR!, for debug
			printc(BG_RED("%s %d: LOCK semi Error!cnt=%d")"\r\n", __FUNCTION__, __LINE__,cnt);
            return 0;   // go ahead!!
        }
        ret = osal_mutex_lockwait(&_capsemi, timeout);

	} else {
		/*if (cnt != 0) {
			// ERROR!, for debug
			printc(BG_RED("%s %d: UNLOCK semi Error!cnt=%d")"\r\n", __FUNCTION__, __LINE__,cnt);
			return 0;	// go ahead!!
		}*/
		ret = osal_mutex_unlock(&_capsemi);
	}

	if (ret == MMPF_OS_ERR_NONE) {
		return 0;
	}
	printc(BG_RED("%s %d:mutex Error! ret=0x%x for enLock=%d cnt=%d")"\r\n", __FUNCTION__, __LINE__, ret, enLock, cnt);
	return 1;
}

// get audio sample rate of source
// return should be 8000, 16000, 24000, 32000, 48000
int ncam_get_audio_sampling_rate(void)
{
    return AHC_VIDEO_GetAudioSamplingRate(VR_AUDIO_TYPE);
}

//broascast ip to AP
#if 0
////////receive hotspot udp broadcast
#define BROADCAST_RECV_PORT 49132
#define BUFSIZE 2500
#define DISCOVER_STR "DISCOVER.CAMERA.IP"
static int fd_recv = 0;
void ncam_hotspotbroadcast_task(void *fd) {
    fd_set rdSet;
    int ret = 0;
    //int stopSock = 0;
    int byte_count;
    socklen_t fromlen;
    struct sockaddr addr;
    char buf[512];

    //struct sockaddr *from, socklen_t *fromlen

    int recv_fd;
    recv_fd = *((int*)fd);

    while (1) {
        FD_ZERO(&rdSet);
        //FD_ZERO(&expSet);
        /* FD_SET()'s */
        FD_SET(recv_fd, &rdSet);
        memset(buf,0,sizeof(buf));
        ret = net_select(recv_fd+1, &rdSet, NULL, NULL, NULL);

        fromlen = sizeof addr;
        byte_count = net_recvfrom(recv_fd, buf, sizeof(buf), 0, &addr, &fromlen);
        if (byte_count > 0) {
            //printc("UDP receive data =%s\n",buf);
            if (!strncasecmp(buf,DISCOVER_STR,byte_count)) {
                ncgi_notify_uichange(NULL);
            }
        }
    }
    net_close(recv_fd);
}

int ncam_stabroadcast_receive_start()
{
    struct sockaddr_in myaddr;
//    int fd;
    int task;
    if ((fd_recv = net_socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printc("cannot create socket\n");
        return 0;
    }

    //printc("####net_socket net_socket = %d\n",fd_recv);
    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(BROADCAST_RECV_PORT);

    if (net_bind(fd_recv, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        printc("bind failed");
        return 0;
    }
    task = osal_thread_new(ncam_hotspotbroadcast_task, (void*)&fd_recv);
    if (task <= 0)
        return 0;
    return task;
    /* never exits */

}

void ncam_hotspotbroadcast_routine_stop()
{
    int ret;
    if (fd_recv > 0) {
        ret = net_close(fd_recv);
        //printc("####net_close = %d\n",ret);
        fd_recv = 0;
    }

}
#endif

// CarDV +++
#ifdef REARVIEW_STREAMING_TEST
/* add for rear MJPEG test start*/
char* buf_data;
char* buf_tdata;
char* netapp_test_malloc()
{

    buf_data=osal_malloc(256*1024);
    buf_tdata=osal_malloc(256*1024);
    //ait_printf("DDDDATA ADDR=%p \n",buf_data);

    return buf_data;
}


void netapp_test_mfree()
{
    osal_free(buf_data);
    osal_free(buf_tdata);
}

OSAL_FILE *hdl=NULL;
static unsigned int g_offset;
static unsigned int f_cnt;
static unsigned int t_cnt;
void netapp_avi_fileopen(char* filename)
{
    unsigned int frames;
    g_offset = 0;
    f_cnt =0;
    frames = 0;
    if (hdl == NULL) {
        hdl = osal_fopen(filename, "rb");
        osal_fseek(hdl,0,SEEK_SET);
        osal_fread(buf_tdata,sizeof(char),512,hdl);
        frames = buf_tdata[51]*256*256*256+buf_tdata[50]*256*256+buf_tdata[49]*256+buf_tdata[48];
        printc("######### Total frames=%d \n",frames);
        t_cnt = frames;

    }
    if (hdl != NULL)
        ait_printf("FILE %s OPEN OK \n",filename);
    else
        ait_printf(" FILE %s OPEN FAILED \n",filename);
}

unsigned int netapp_avi_filegetframe(MMP_ULONG baddr)
{
#if 1
    unsigned int rd,offset_start,offset_end,f_size,i;
    if ((hdl == NULL)||(buf_tdata==NULL))
        return 0;
    if (f_cnt >= t_cnt)
    {
        f_cnt=g_offset = 0;
        //return 0;
    }
    osal_fseek(hdl,g_offset/*256*/,SEEK_SET);
    osal_invalidate_dcache(((unsigned int)(buf_tdata) & ~(MEM_ALIGNMENT_HEAP - 1)) , 64*1024);
    rd = osal_fread(buf_tdata,sizeof(char),64*1024,hdl);
    for (i=0;i<rd;i++)
    {
        if ((buf_tdata[i]==0xff)&&(buf_tdata[i+1]==0xd8))
            break;
    }
    offset_start = i;

    for (i=offset_start;i<rd;i++)
    {
        if ((buf_tdata[i]==0xff)&&(buf_tdata[i+1]==0xd9))
            break;
    }
    offset_end = i+1;

    g_offset += (offset_end);

    f_size = offset_end-offset_start+1;
    memcpy((void*)baddr/*buf_data*/,buf_tdata+offset_start,f_size);
    f_cnt ++;
    g_offset = (g_offset/512)*512;
//  ait_printf("\n f_size = %d addr=%p\n",f_size,baddr);
    return f_size;
#endif

}

void netapp_avi_fileclose(OSAL_FILE *hdl)
{
    osal_fclose(hdl);
    hdl = NULL;
}

int netapp_avi_stopstream(void)
{
    struct amn_session_t *s;
    struct ammo_node* node = NULL;
    char src_name[] = "VIDEO.1/EncRMJPEG"; //double-check this with conf file.

	printc("%s %d\r\n", __FUNCTION__, __LINE__);

    //static void __aitstreamer_set_running( char *src_name, int running )
    node = node_find_name( AMMO_TYPE__NODE_SOURCE, src_name, -1 );

    if (node) {
        struct list_head *l;
        struct ammo_pipe *p;
        /* see if anybody else is listening */
        list_for_each( l, &(node->pl->pipe_TO_list) ) {
            p = list_entry( l, struct ammo_pipe, link );
            printc("name:%s type:%d\r\n", p->to_node->name, p->to_node->node_type);
            if (p->to_node->node_type == AMMO_TYPE__NODE_SINK) {
                int i;
                for (i=0; ;i++) {
                    s = session_search_owner(p->to_node, i);
                    if (NULL != s) {
                        printc("found session of %s\r\n", p->to_node->name);
                        session_destroy(s, "stop transcoding");
                    } else {

                        break;
                    }
                }
            }
        }
    }
    else {
        printc("set_running for Source Node '%s' : invalid \r\n", src_name);
        return -1;
    }
    return 0;
}
/* add for rear MJPEG test end*/
#endif
