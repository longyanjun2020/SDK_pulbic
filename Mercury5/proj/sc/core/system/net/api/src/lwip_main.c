//==============================================================================
//
//  Description : LWIP Network Initialization
//  Author      : Bernard Shyu
//  Revision    : 1.0
//
//==============================================================================
#include "lwipif.h"
#include "netconf.h"
#include "wlan.h"
#include "ahc_utility.h"
#include "ahc_message.h"
#include "osl_ext.h"

#include "dhcp_server.h"
#include "ahc_sd.h"
#include "netapp.h"
#include "net_utility.h"
//#include "wlan.h"

#include "amn_sysobjs.h"
#include "amnss_mmobjs.h"
#include "amn_event.h"
#include "Customer_config.h" //CarDV...
#include "mmpf_system.h" //For task monitor //CarDV...

/*
#ifndef NCFG_WAKEUP_PIN
#error "NCFG_WAKEUP_PIN is not defined"
#endif

#ifndef NCFG_RESET_PIN
#error "NCFG_RESET_PIN is not defined"
#endif

#ifndef NCFG_SDIO_PAD
#error "NCFG_SDIO_PAD is not defined"
#endif
*/

/* ********************************************************************* */
/* Global definitions */

//#define __AIT_UTEST_TELNET__
//#define __AIT_UTEST_HTTPD__
#define STA_RECONNC_TIME                15      //seconds
#define AP_CHECK_ASSOC_TIME             8       //seconds
/* nonstatic debug cmd option, exported in lwipopts.h */
unsigned char lwip_debug_flags;

struct netif main_netdev;

extern nhw_drv_hdl  g_hdl;
extern void UartCmd_ProcessAgent(void);

/* ********************************************************************* */
static int  netif_status;
static struct ammo_evmsg *psSTAReconnTimer = NULL;
static struct ammo_evmsg *psAPAssocTimer = NULL;

#define CUSTOM_SSID_LEN     32
#define CUSTOM_PSWD_LEN     16

//For AP mode
static void apply_customer_ssid(char * pssid ,char * pswd)
{
    CUSTOMIZED_SSIDPSWD_CB  pfCSSIDcb;

    if((pfCSSIDcb = ncfg_get_customized_ssid_cb()) != NULL ){

        if(strcmp(amn_factConfig_get("Net.WIFI_AP.SSID")->v.strVal,pssid) == 0){

            pfCSSIDcb(pssid,pswd,CUSTOM_SSID_LEN,CUSTOM_PSWD_LEN);

        }
    }
}

static void stop_assoc_timer(void)
{
    if(psAPAssocTimer){
        evmsg_remove(psAPAssocTimer);
        psAPAssocTimer = NULL;
    }
}

static void* ap_check_assoc_job(void *arg)
{
    unsigned char buf1[128],buf2[128];
    int i,num;
    WLAN_MACLIST *maclist = (WLAN_MACLIST*) buf1;
    WLAN_ETHER_ADDR *ea;

    if(WLAN_AP_GetAssocList((int8*)buf1, sizeof(buf1)) < 0) {
        printc("UartCmd_AssocList failed\n");
        return NULL;
    }

    //printc("maclist->count = %d\n", maclist->count);

    for (i = 0, ea = maclist->ea; i < maclist->count; i++, ea++){
        memcpy(buf2 + (6 * i),ea->mac,6);
    }

    num = nhw_check_sta_leave(buf2,maclist->count,buf1);

    //Inform that STA was disconnected
    for(i = 0 ; i < num ; i++){
        wlan_event_msg_t event;
        //make a fake wlan event
        event.event_type = WLAN_E_DISASSOC_IND;
        memcpy((char *)event.addr.mac,buf1 + (6 * i),6);
        WLAN_SYS_StatusCallback(&event);
    }

    return NULL;
}

static void ap_check_assoc_timer( struct ammo_evmsg *e, void *ss )
{
    add_NetworkJob(ap_check_assoc_job, NULL, 1);
    kick_NetworkJob();
}

//For STA mode
static void stop_reconn_timer(void)
{
    if(psSTAReconnTimer){
        evmsg_remove(psSTAReconnTimer);
        psSTAReconnTimer = NULL;
    }
}

static void* sta_reconn_job(void *arg)
{
//printt(__MODULE__"@%d\r\n", __LINE__);
    LwIP_join_WLAN_auto(1);
    return NULL;
}

static void sta_reconn_timer( struct ammo_evmsg *e, void *ss )
{
    add_NetworkJob(sta_reconn_job, NULL, 1);
    kick_NetworkJob();
}

static void wifi_link_up(void)
{

    if(nhw_get_cur_wifi_mode() == NETAPP_WIFI_STATION_MODE){

        stop_reconn_timer();

        if(NETAPP_NET_STATUS_DOWN == nhw_get_status())
            return;

        AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_CONNECT_SUCCESS, 0 );

        if(ip_addr_isany(&net_context.local_ip)){
            //net interface is DHCP type
printt("wifi_link_up @%d\r\n", __LINE__);
            if (LwIP_start_DHCP() < 0) {
                printc("Get IP Failed\r\n");
                nhw_set_status(NETAPP_NET_STATUS_NOIP);
                AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_NETWORK_WPS_FAIL, 0 );
            } else {
printt("wifi_link_up @%d\r\n", __LINE__);
                ip_addr_set(&net_context.local_ip,&main_netdev.ip_addr);
                ip_addr_set(&net_context.net_mask,&main_netdev.netmask);
                ip_addr_set(&net_context.gateway_ip,&main_netdev.gw);
                netif_set_up(&main_netdev);
                AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_NETWORK_IP_READY, 0 );
            }
        }
    }
}

static void wifi_link_down(void)
{
    if(nhw_get_cur_wifi_mode() == NETAPP_WIFI_STATION_MODE){
        //prepare network interface setting
        AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_CONNECT_FAIL, 0 );

        if(!strcasecmp( "DHCP", (char *)amn_currConfig_get( "Net.Dev.1.BootProto" )->v.intVal)){
            IP4_ADDR(&net_context.local_ip,   0,0,0,0);
            IP4_ADDR(&net_context.net_mask,   0,0,0,0);
            IP4_ADDR(&net_context.gateway_ip, 0,0,0,0);
        }
        //start reconnection timer
        if(!psSTAReconnTimer)
            psSTAReconnTimer = evmsg_new_timer( STA_RECONNC_TIME * 1000, 0, sta_reconn_timer, 0 );
    }
}

static void network_shutdown(void)
{
    session_destroyall();
    stop_reconn_timer();
    stop_assoc_timer();
    if(WLAN_WPS_Enable())   WLAN_WPS_Stop();
    if(DhcpIsServerStart()) DhcpServerStop();
    netif_set_down(&main_netdev);
    WLAN_SYS_Stop(nhw_get_handle());
    nhw_set_status(NETAPP_NET_STATUS_DOWN);
    ns_set_streaming_status(NETAPP_STREAM_NONE);
}

static void LwIP_load_system_config()
{
    int i, crypto;
    char *ssid, *key, *str;

    memset( &net_context, 0, sizeof(net_context) );
    strcpy( net_context.host_name, "AIT.HomeCAM." __DATE__ __TIME__ );

    for (i=1; i <= amn_currConfig_get("Net.WIFI_STA.AP.Totals")->v.intVal; i++) {
        ssid = amn_currConfig_get_enum( "Net.WIFI_STA.AP.%d.SSID", i ) -> v.strVal;
        key  = amn_currConfig_get_enum( "Net.WIFI_STA.AP.%d.CryptoKey", i ) -> v.strVal;
        str  = amn_currConfig_get_enum( "Net.WIFI_STA.AP.%d.EncType", i ) -> v.strVal;
        if      (!strcasecmp(str, "WEP"))  crypto = WPA_CRYPTO__WEP;
        else if (!strcasecmp(str, "AES"))  crypto = WPA_CRYPTO__AES;
        else if (!strcasecmp(str, "TKIP")) crypto = WPA_CRYPTO__TKIP;
        else                               crypto = WPA_CRYPTO__NONE;
        AddWlanFavAP( -1, ssid, crypto, key );
    }
}

static void LwIP_set_net_context(int i, int is_AP)
{
    char *bootProto = amn_currConfig_get_enum( "Net.Dev.%d.BootProto", i )->v.strVal;
    if (!strcasecmp("STATIC", bootProto) || is_AP) {
        net_context.local_ip.addr   = inet_addr( amn_currConfig_get_enum("Net.Dev.%d.IPV4.Address", i)->v.strVal );
        net_context.gateway_ip.addr = inet_addr( amn_currConfig_get_enum("Net.Dev.%d.IPV4.Gateway", i)->v.strVal );
        net_context.net_mask.addr   = inet_addr( amn_currConfig_get_enum("Net.Dev.%d.IPV4.Mask", i)->v.strVal );
    }
    else
    if (!strcasecmp( "DHCP", bootProto)) {
        IP4_ADDR(&net_context.local_ip,   0,0,0,0);
        IP4_ADDR(&net_context.net_mask,   0,0,0,0);
        IP4_ADDR(&net_context.gateway_ip, 0,0,0,0);
    }
    else
        LWIP_DEBUGF(OS_PORT_DEBUG, ("NETCFG:: device %d unknown BootProto=%s \n", i, bootProto));
}

/* ********************************************************************* */
#define IFNAME0 'w'
#define IFNAME1 'l'

err_t main_netif_init(struct netif *netif)
{
    netif->name[0]    = IFNAME0;
    netif->name[1]    = IFNAME1;
    netif->output     = etharp_output;
    netif->linkoutput = low_level_output;

    return ((low_level_init(netif) == 1)? ERR_OK : ERR_IF);
}


//move this into wlan.c as WLAN_SYS_InitHw()
/*
void wifi_ctrl_init()
{
    osl_ext_sdio_internal_set_id(NCFG_SDIO_PAD);

    // WIFI's wake-on-LAN INPUT. Basically it's not implemented
    printc("Config WIFI GPIO - WAKE\r\n");
    AHC_GPIO_SetOutputMode( NCFG_WAKEUP_PIN, AHC_FALSE );

    // WIFI module's RESET output, active-low
    printc("Config WIFI GPIO - RESET\r\n");
    AHC_GPIO_SetOutputMode( NCFG_RESET_PIN,  AHC_TRUE  );
    AHC_GPIO_SetData( NCFG_RESET_PIN, 1 );
}
*/

//move this into wlan.c as WLAN_SYS_ResetHw()
/*
void wifi_ctrl_reset()
{
    AHC_GPIO_SetData( NCFG_RESET_PIN, 0 );
    AHC_OS_SleepMs(100);
    AHC_GPIO_SetData( NCFG_RESET_PIN, 1 );
    AHC_OS_SleepMs(3000);
}
*/

/* ********************************************************************* */
static void init_netifs(void)
{
    WLAN_SYS_ResetHw();

    #if PPP_SUPPORT
    sio_fd_t ppp_sio;
    pppInit();

    #if PPP_PTY_TEST
    ppp_sio = sio_open(2);
    #else///< PPP_PTY_TEST
    ppp_sio = sio_open(0);
    #endif///< PPP_PTY_TEST

    if(!ppp_sio)
    {
        perror("Error opening device: ");
        exit(1);
    }

    #ifdef LWIP_PPP_CHAP_TEST
    pppSetAuth(PPPAUTHTYPE_CHAP, "lwip", "mysecret");
    #endif

    pppOpen(ppp_sio, pppLinkStatusCallback, NULL);
    #endif /* PPP_SUPPORT */

    if (netif_add(  &main_netdev,
                &net_context.local_ip,
                &net_context.net_mask,
                &net_context.gateway_ip,
                NULL,
                main_netif_init,
                tcpip_input ) == NULL) {
        // FAILED!!
        netif_status = -1;
        return;
    }

    netif_status = 0;
    netif_set_default(&main_netdev);
}

static void tcpip_init_done(void *arg)
{
    sys_sem_t *sem;
    sem = (sys_sem_t *)arg;

    init_netifs();

    sys_sem_signal(sem);
}

struct net_context_t *load_netconfig(int *isap)
{
    int     i, j;
    char *str1;

    for (i=1; i <= amn_currConfig_get("Net.Dev.Totals")->v.intVal; i++) {
        j = amn_currConfig_get_enum( "Net.Dev.%d.Start", i )->v.intVal;
        str1 = amn_currConfig_get_enum( "Net.Dev.%d.Type", i )->v.strVal;
        LWIP_DEBUGF(OS_PORT_DEBUG, ("NETCFG:: init DEV.%d Type=%s Start=%d \n", i, str1, j));
        if (!j)  continue;
        // Net.Dev.*.Name is host name
        strncpy(net_context.host_name, amn_currConfig_get_enum( "Net.Dev.%d.Name", i )->v.strVal, MAX_NAME_LENGTH - 1);

        if ( ! strcasecmp( str1, "AP" ) ) {
            LwIP_set_net_context( i, 1 );
            LwIP_start_netif( NULL, NULL );
            *isap = 1;
            nhw_set_wifi_mode(NETAPP_WIFI_AP_MODE);
            net_context.mode = NETAPP_WIFI_AP_MODE;
            stop_reconn_timer();
            stop_station_service();
            nhw_init_ap_check_assoc();
            if (!psAPAssocTimer)
                psAPAssocTimer = evmsg_new_timer( AP_CHECK_ASSOC_TIME * 1000, 0, ap_check_assoc_timer, 0 );
            return &net_context;
        }
        else if ( ! strcasecmp( str1, "STA" ) ) {
            // TODO: station mode, static IP or from DHCP
            // Load the settings of network config
            LwIP_load_system_config();
            nhw_set_wifi_mode(NETAPP_WIFI_STATION_MODE);

            *isap = 0;
            if (!WLAN_SYS_IsStart()) {
                // START WiFi wWhen WiFi is OFF!
                nhw_set_handle(WLAN_SYS_Start());
            }else {
                WLAN_SYS_Stop(nhw_get_handle());
                /* delay 8 second to let clients off line */
                MMPF_OS_Sleep(3000);
                nhw_set_handle(WLAN_SYS_Start());
            }
            net_context.mode = NETAPP_WIFI_STATION_MODE;
            LwIP_set_net_context( i, 0 );
            //start wifi connection timer
            if (LwIP_join_WLAN_auto(1) < 0) {
                if (!psSTAReconnTimer)
                    psSTAReconnTimer = evmsg_new_timer( STA_RECONNC_TIME * 1000, 0, sta_reconn_timer, 0 );
            }
            start_station_service();
            return &net_context;
        }
        else {
            LWIP_DEBUGF(OS_PORT_DEBUG, ("NETCFG:: unknown Net.Dev.%d.Type=%s\n", i, str1 ));
        }
    }
    return NULL;
}

int load_wificonfig(int apset, char **pssid, int *pcrypto, char **pckey, int *hidden, int *pchan)
{
    char    *secu;
    char    apcfg[16], key[32];

    if (apset == 0) {
        strcpy(apcfg,  "Net.WIFI_AP");
    } else {
        sprintf(apcfg, "Net.WIFI_AP%d", apset);
    }
    sprintf(key, "%s.EncType", apcfg);
    secu = amn_currConfig_get( key )->v.strVal;
    if      (!strcasecmp(secu, "WEP"))  *pcrypto = WPA_CRYPTO__WEP;
    else if (!strcasecmp(secu, "AES"))  *pcrypto = WPA_CRYPTO__AES;
    else if (!strcasecmp(secu, "TKIP")) *pcrypto = WPA_CRYPTO__TKIP;
    else                                *pcrypto = WPA_CRYPTO__NONE;
    sprintf(key, "%s.SSID", apcfg);
    *pssid  = amn_currConfig_get( key )->v.strVal;
    printc(BG_RED("%s = SSID is %s")"\r\n", key, (*pssid != NULL)? *pssid : "(NULL)");
    sprintf(key, "%s.CryptoKey", apcfg);
    *pckey  = amn_currConfig_get( key )->v.strVal;
    sprintf(key, "%s.HideSSID", apcfg);
    *hidden = amn_currConfig_get( key )->v.intVal;
    sprintf(key, "%s.Channel", apcfg);
    *pchan  = amn_currConfig_get( key )->v.intVal;
    if (*pchan <= 0) {
        // Auto select channel, it works at first time and keep return in _channel
        // after WiFi Off then ON, the function may return 0, but it is an invalid channel.
        // return _channel instead of 0! <== Fixed by Titan

    #if NHW_PANA_RULE
        if(NHW_AUTO_CHANNEL_PANA_RULE == nhw_get_auto_chan_rule())
            WLAN_STA_AutoSelectChannel_PanaRule((UINT32*)pchan);
        else
    #endif
            WLAN_STA_AutoSelectChannel( (UINT32*)pchan );

    }
    printc(BG_RED("Channel is %d")"\r\n", *pchan);
    return 1;
}

/* ********************************************************************* */
extern void UartCmd_WL(char* szParam);
int NETWORK_init()
{
    static int lwip_initialized = 0;
    //char      wlcmd[64];
    sys_sem_t   sem;
    int         timeOut = 10 * 1000;
    int         wifiAP; /* is AP(1) or STA(0) */

    if (lwip_initialized) {
        if(nhw_get_wifi_mfg()){
            g_hdl = WLAN_SYS_Start();
            LWIP_DEBUGF(OS_PORT_DEBUG, ("NETCFG:: start WIFI-MFG mode\n"));
            return 0;
        }
        // TODO: only for AP mode, need add STATION mode
        nhw_turn_on_wlan();
        nhw_set_status(NETAPP_NET_STATUS_IDLE);
        return 0;
    }
    nhw_set_status(NETAPP_NET_STATUS_INIT);
    WLAN_SYS_InitHw();

    lwip_debug_flags = (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT);
    LWIP_DEBUGF(OS_PORT_DEBUG, ("\n\n==============================================\n"));
    LWIP_DEBUGF(OS_PORT_DEBUG, ("%s(): %s %s \n", __func__, __DATE__, __TIME__));
    //
    if(sys_sem_new(&sem, 0) != ERR_OK) {
        LWIP_ASSERT("Failed to create semaphore", 0);
        goto _end_NETWORK_init;
    }
    if (tcpip_init(tcpip_init_done, &sem))
        goto _end_NETWORK_init;

    sys_sem_wait(&sem);
    sys_sem_free(&sem);
    if (netif_status != 0) {
        LWIP_DEBUGF(OS_PORT_DEBUG, ("Net Interface failed.\n"));
        goto _end_NETWORK_init;
    }
    LWIP_DEBUGF(OS_PORT_DEBUG, ("TCP/IP initialized.\n"));
    lwip_initialized = 1;

    #ifdef __AIT_UTEST_TELNET__
    shell_init();
    #endif

    #ifdef __AIT_UTEST_HTTPD__
    httpd_init();
    #endif
    aitstreamer_init();
    // Load the settings of network config
    LwIP_load_system_config();


#if NCFG_WIFI_MFG_EN == 1
    if(nhw_get_wifi_mfg()){
        LWIP_DEBUGF(OS_PORT_DEBUG, ("NETCFG:: start WIFI-MFG mode\n"));
        return 0;
    }
#endif

    if (load_netconfig(&wifiAP)) {
        if (wifiAP) {
            int         crypto, auth, enc, chan;
            char        *ssid, *ckey;
            int         hidden;
            int         apset;
            /* is AP mode */
            apset = ncam_get_ui_ap_setting();
            load_wificonfig(apset, &ssid, &crypto, &ckey, &hidden, &chan);
            LwIP_convert_WLAN_crypto( crypto, &auth, &enc );
            apply_customer_ssid(ssid,ckey);

            if ( WLAN_AP_Create( (int8*)ssid, auth, enc, (int8*)ckey, chan, hidden) < 0 ) {
                LWIP_DEBUGF(OS_PORT_DEBUG, ("NETCFG:: Fail starting SoftAP: %s CH: %d, crypto %s\n", ssid, chan, ckey ));
            } else {
                LWIP_DEBUGF(OS_PORT_DEBUG, ("NETCFG:: Success started SoftAP: %s CH: %d, crypto %s\n", ssid, chan, ckey ));
                nhw_set_status(NETAPP_NET_STATUS_IDLE);
            }

            if (amn_currConfig_get( "Net.DHCPD.Start" )->v.intVal && !DhcpIsServerStart())
                DhcpServerStart();
        } else {
            /* is STA mode */
            // Nothing to do
        }
    } else {
        /* load config failed! */
    }

    /*Default threshold is "DOT11_DEFAULT_RTS_LEN" which is defined in WiFi driver.
    For fixing failed items in basic association(WiFi Certification STA mode),
    this command should be removed*/
    //Set the RTS-Threshold to MTU-1, which is 1499
    //sprintf( wlcmd, " rtsthresh %d", main_netdev.mtu - 1 );
    //UartCmd_WL( wlcmd );

    /*
     * always start server up, not need to check network status for STA/WPS.
     */
    if (amn_currConfig_get("Ass.Start")->v.intVal/* && netif_is_up(&main_netdev)*/) {
        // waiting for the network ready
        //AHC_OS_SleepMs(10 * 1000);
printt0("wait net status ...");
        while ((timeOut > 0)) {
            int     sts;

            sts = nhw_get_status();
            if (sts == NETAPP_NET_STATUS_IDLE || sts == NETAPP_NET_STATUS_READY)
                break;
            MMPF_OS_SleepMs(100);
            timeOut -= 100;
        }
printt0("...done\r\n");

        nhw_set_status(NETAPP_NET_STATUS_IDLE);
        {}aitupnp_init();
        aitstreamer_start();
        return 0;
    }
_end_NETWORK_init:
    nhw_set_status(NETAPP_NET_STATUS_INIT_FAIL);
    return -1;

}

int NETWORK_reset(void)
{
    struct net_context_t *thenet;
    int     isap;
    char    *ssid, *ckey;
    int     hidden, crypto, chan, auth, enc ;
    int     err;

    session_destroyall();
    stop_reconn_timer();
    stop_assoc_timer();
    ns_set_streaming_status(NETAPP_STREAM_NONE);

    // TCP/IP Network
    if ((thenet = load_netconfig(&isap)) == NULL)
        return 0;   // FAIL!!
    if (isap) {
        int     apset;
        // AP mode
        netif_set_down(&main_netdev);
        netif_set_addr(&main_netdev, &thenet->local_ip,
                                     &thenet->net_mask,
                                     &thenet->gateway_ip);
        netif_set_up(&main_netdev);
        // WiFi configuration
        apset = ncam_get_ui_ap_setting();

        //must before load_wificonfig,or auto-channel will not be excuted!
        WLAN_SYS_Stop(nhw_get_handle());
        /* delay 8 second to let clients off line */
        /* Titan : This delay will cause task timeout,I temporarily modfity it to 3sec */
        MMPF_OS_Sleep(3000);
        nhw_set_handle(WLAN_SYS_Start());

        load_wificonfig(apset, &ssid, &crypto, &ckey, &hidden, &chan);
        DhcpServerSetToDefault();
        DhcpServerStart();
        LwIP_convert_WLAN_crypto( crypto, &auth, &enc );
        apply_customer_ssid(ssid,ckey);
        err = WLAN_AP_Create( (int8*)ssid, auth, enc, (int8*)ckey, chan, hidden);
        return (err == 0);
    } else {
        // TODO: STATION mode
        DhcpServerStop();
        if(WLAN_WPS_Enable())
            WLAN_WPS_Stop();
    }
    return 1;
}

typedef void *(*job_routine)(void *arg);
typedef struct {
    job_routine network_routine;
    void*       arg;
} Network_Job_t;
#define MAX_NETWORKJOB  8
static Network_Job_t    _network_job[MAX_NETWORKJOB] = {{0}};
MMPF_OS_SEMID   _jobsemi = -1;

static void init_NetwrokJob()
{
    memset(_network_job, MAX_NETWORKJOB * sizeof(Network_Job_t), 0);
    osal_mutex_init(&_jobsemi);
}

void* add_NetworkJob(job_routine routine, void *arg ,MMP_BOOL bneedlock)
{
    int i;

    for (i = 0; i < MAX_NETWORKJOB; i++) {
        if (_network_job[i].network_routine == NULL)
            break;
    }
    if (i == MAX_NETWORKJOB) {
        return NULL;
    }

    if(bneedlock)   osal_mutex_lock(&_jobsemi);
    _network_job[i].arg             = arg;
    _network_job[i].network_routine = routine;
    if(bneedlock)   osal_mutex_unlock(&_jobsemi);
    return &_network_job[i];
}

//extern MMPF_OS_FLAGID Network_Flag;
//#define   SEND_NETWORK_EVENT(e)   MMPF_OS_SetFlags(Network_Flag, e, MMPF_OS_FLAG_SET)
void kick_NetworkJob()
{
    SEND_NETWORK_EVENT(SYS_FLAG_MSG_NETWORK_JOB);
}

void run_NetworkJob()
{
    int     i;
    int     flag;

    do {
        flag = 0;
        for (i = 0; i < MAX_NETWORKJOB; i++) {
            if (_network_job[i].network_routine == NULL)
                continue;

            osal_mutex_lock(&_jobsemi);
            _network_job[i].network_routine(_network_job[i].arg);
            _network_job[i].network_routine = NULL;
            osal_mutex_unlock(&_jobsemi);

            flag = 1;
        }
    } while (flag);
}

static int  init_network = 0;
int network_init_done()
{
    return init_network;
}
//
void NETWORK_TaskHandler_init(void *p_arg)
{
    UartSendTrace("NETWORK_TaskHandler_init\n\r");
    init_NetwrokJob();
}
void NETWORK_TaskHandler(void *p_arg)
{
    MMPF_OS_FLAGS       flags;
    const MMPF_OS_FLAGS wfs = SYS_FLAG_MSG_NETWORK_INIT |
                              SYS_FLAG_MSG_NETWORK_UNIN |
                              SYS_FLAG_MSG_NETWORK_RESET|
                              SYS_FLAG_MSG_NETWORK_JOB  |
                              SYS_FLAG_MSG_NETWORK_UINOTIFY |
                              SYS_FLAG_MSG_NETWORK_CMD |
                              SYS_FLAG_MSG_NETWORK_WIFILINK_IND |
                              SYS_FLAG_MSG_NETWORK_WIFILINK_DOWN_IND;

    (void)p_arg;
#if 0
    init_NetwrokJob();
#endif
    while (1) {
        extern MMPF_OS_FLAGID   Network_Flag;

        MMPF_OS_WaitFlags(Network_Flag,
                          wfs,
                          MMPF_OS_FLAG_WAIT_SET_ANY | MMPF_OS_FLAG_CONSUME,
                          0, &flags);

        if (flags) {

            if (flags & SYS_FLAG_MSG_NETWORK_UNIN)
                network_shutdown();

            if (flags & SYS_FLAG_MSG_NETWORK_INIT) {
                /* change priority for pthread_cond_broadcast.
                 * In NETWORK_init(), if not lift this priority, the pthread_cond_broadcast
                 * will run before pthread_cond_wait() in some case.
                 * after NETWORK_init done, the pthread_cond_broadcast will send event
                 * (SYS_FLAG_MSG_NETWORK_JOB) to do, and this task was at low priority.
                 */
                MMPF_OS_ChangeTaskPriority(TASK_NETWORK_PRIO, TASK_NETWORK_BRUST_PRIO);
                init_network = 0;
                NETWORK_init();
                init_network = 1;
                MMPF_OS_ChangeTaskPriority(TASK_NETWORK_PRIO, TASK_NETWORK_PRIO);

                //Inform UI that network init done
                AHC_SendAHLMessage( AHLM_WIRELESS_CONNECT, WIRELESS_NETWORK_READY, 0 );
            }
            if (flags & SYS_FLAG_MSG_NETWORK_CMD) {
                UartCmd_ProcessAgent();
            }
            if (flags & SYS_FLAG_MSG_NETWORK_RESET) {
                nhw_set_status(NETAPP_NET_STATUS_NONE);
                ncam_save_net_conf();
                if (NETWORK_reset()) {
                    if (nhw_get_status() == NETAPP_NET_STATUS_NONE)
                        nhw_set_status(NETAPP_NET_STATUS_IDLE);
                }
            }
            if (flags & SYS_FLAG_MSG_NETWORK_UINOTIFY) {
                // to inform client Camera Status changed
                ncgi_send_camera_state();
            }
            if (flags & SYS_FLAG_MSG_NETWORK_JOB)
                run_NetworkJob();

            if(flags & SYS_FLAG_MSG_NETWORK_WIFILINK_DOWN_IND)
                wifi_link_down();
            if (flags & SYS_FLAG_MSG_NETWORK_WIFILINK_IND)
                wifi_link_up();
        }

    }
}

/*
*   init net TCP/IP
*   only for wifi test command
*/
static void* simple_init_job(void *arg)
{
    sys_sem_t   sem;

    nhw_set_status(NETAPP_NET_STATUS_INIT);
    WLAN_SYS_InitHw();
    lwip_debug_flags = (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT);
    LWIP_DEBUGF(OS_PORT_DEBUG, ("\n\n==============================================\n"));
    LWIP_DEBUGF(OS_PORT_DEBUG, ("%s(): %s %s \n", __func__, __DATE__, __TIME__));
    //
    if(sys_sem_new(&sem, 0) != ERR_OK) {
        LWIP_ASSERT("Failed to create semaphore", 0);
        return NULL;
    }
    if (tcpip_init(tcpip_init_done, &sem))
        return NULL;
    sys_sem_wait(&sem);
    if (netif_status != 0) {
        LWIP_DEBUGF(OS_PORT_DEBUG, ("Net Interface failed.\n"));
        return NULL;
    }
    LWIP_DEBUGF(OS_PORT_DEBUG, ("TCP/IP initialized.\n"));


    aitstreamer_init();
    // Load the settings of network config
    LwIP_load_system_config();

    aitstreamer_start();

    return NULL;
}

void NetSimpleInit(void)
{
    add_NetworkJob(simple_init_job, NULL, 1);
    kick_NetworkJob();
}

