#include "net_cfg.h"
#include "wlanif.h"
#include "pbuf.h"
#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)
#include "mtk_wifi_adapter.h"
#include "wlan_MTK.h"
#endif
#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_BCM)
#include "osl.h"
#include "dhd.h"
#include "wlan_BCM.h"
#endif
#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_RTK)
#include "wlan_RTK.h"
#endif
/*
 * wlan_dummy_lib.c
 *
 *  Created on: 2017/12/25
 *      Author: titan.huang
 *      Because wifi library are not ready,to compile with no error,temporarily create this file,
 *      the goal is replacing this file by wifi library of vendors
 */

char* wf_chspec_ntoa(chanspec_t chspec, char *buf)
{
	return 0;
}

#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_BCM)
char * wl_ether_etoa(const struct ether_addr *n)
{
	return 0;
}

const char* capmode2str(uint16 capability)
{
	return 0;
}
#endif

static char fakehandler[128];

wl_drv_hdl wlan_start(wlan_drv_event_callback cb, uint tx_buf_cnt, uint rx_buf_cnt, uint scan_buf_size)
{
	return fakehandler;
}

void wlan_stop(wl_drv_hdl hdl)
{
	return;
}

int wlan_scan_network(char* scan_buf, uint buf_size)
{
	return -1;
}

int wlan_set_scan(void)
{
	return -1;
}

int wlan_get_scan(char* scan_buf, uint buf_size)
{
	return -1;
}

int wlan_join_network(char *ssid, WLM_AUTH_MODE authMode, WLM_ENCRYPTION encryption, const char *key)
{
	return -1;
}

int wlan_join_network_bssid(char *ssid, char *bssid, WLM_AUTH_MODE authMode, WLM_ENCRYPTION encryption, const char *key)
{
	return -1;
}

int wlan_create_sw_ap(	char* ssid, WLM_AUTH_MODE authMode, WLM_ENCRYPTION encryption,
							const char *key, WLM_CHANNEL channel, int ssidBcst )
{
	return -1;
}

int wlan_get_assoc_list(char* buf, uint buf_size)
{
	return -1;
}

int wlan_get_tx_queue_avail_count(void)
{
	return 0xff;
}

char* wlan_get_version(void)
{
	return 0;
}

int wlan_get_connection_info(wl_connection_info_t *wlan_connection_info)
{
	return -1;
}

int wlan_get_mode(void)
{
	return -1;
}

void wlan_get_mac_addr(uint8* mac_addr)
{
	return ;
}

void wlan_add_ie(int pktflag, char* oui, char* ie_data, int ie_data_len)
{
	return;
}

void wlan_del_ie(int pktflag, char* oui, char* ie_data, int ie_data_len)
{
	return;
}

int wlan_wifi_register_multicast_address( uint8* mac )
{
	return -1;
}

int wlan_wifi_unregister_multicast_address( uint8* mac )
{
	return -1;
}

int wlan_wps_start(wps_config_info_t wps_config_info, wlan_wps_event_callback cb)
{
	return -1;
}

int wlan_wps_stop(void)
{
	return -1;
}

int wlan_wps_gen_pin(uint *pin)
{
	return -1;
}

int wlan_wps_get_credentials(wl_config_info_t *wlan_config_info)
{
	return -1;
}

WPS_STATE wlan_wps_get_state(void)
{
	return 0;
}

unsigned long wlan_wps_get_status(void)
{
	return 0;
}

int wlan_mfg_tx_bg(WLM_CHANNEL channel, WLM_RATE rate, int powerValue)
{
	return -1;
}

int wlan_mfg_tx_n(WLM_CHANNEL channel, WLM_MCS_RATE rate, int powerValue)
{
	return -1;
}

int wlan_mfg_rx(WLM_CHANNEL channel)
{
	return -1;
}

int wlan_mfg_rx_getpkt(unsigned int *count)
{
	return -1;
}

int wlan_mfg_carrier_tone(WLM_CHANNEL channel)
{
	return -1;
}

int wlan_mfg_stop(void)
{
	return -1;
}

void wlan_tx_pkt(struct pbuf *p)
{
	pbuf_free(p);
	return;
}

unsigned int kalGetTxAvaliableFrameCount(void)
{
	return 0;
}

void wlan_config_func_pin(unsigned char function, unsigned char pin)
{
	return;
}

#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_MTK)
unsigned int wndrv_dbglevel;
unsigned int HostapdDebugLevel;

int wlan_set_parameter(PARAM_TYPE type, void* pValue)
{
	return 0;
}

void wlan_config_cal_data(unsigned char calibrateType, void *data)
{
	return;
}

void RFTool_WiFi_EnterTestMode(void)
{
	return;
}
void RFTool_WiFi_Stop(void)
{
	return;
}
void RFTool_WiFi_ContTx(kal_uint8 country_code[2], wndrv_test_tx_struct cont_tx)
{
	return;
}
void RFTool_WiFi_CarrierSupp(kal_uint8 country_code[2], wndrv_test_tx_struct carrier_supp)
{
	return;
}
void RFTool_WiFi_LocalFreq(kal_uint8 country_code[2], wndrv_test_tx_struct local_freq)
{
	return;
}
void RFTool_WiFi_PktTx(kal_uint8 country_code[2], wndrv_test_pkt_tx_struct pkt_tx)
{
	return;
}
void RFTool_WiFi_PktRx(kal_uint32 ch_freq, void (* callback) (wndrv_test_rx_status_struct* result))
{
	return;
}
#endif

#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_BCM)

dhd_pub_t *g_dhd_info;

int wlmClosedSet(int val)
{
    return -1;
}

void dhd_bus_dump(dhd_pub_t *dhdp, struct bcmstrbuf *strbuf)
{
	return;
}

int wlu_main_args(int argc, char **argv)
{
	return -1;
}

#if defined(WPS_AP_SUPPORT)
int AP_StartWPS(wps_config_info_t *pwps_config_info, wlan_wps_event_callback cb)
{
	return -1;
}
void AP_StopWPS(void* pVariable)
{
	return;
}
#endif

#endif
