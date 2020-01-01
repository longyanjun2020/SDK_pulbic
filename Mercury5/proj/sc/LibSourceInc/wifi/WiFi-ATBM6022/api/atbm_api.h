#ifndef __ATBM_API_H__
#define __ATBM_API_H__

enum atbmwifi_event{
	ATBM_WIFI_DEAUTH_EVENT=0,
	ATBM_WIFI_JOIN_EVENT=1,
	ATBM_WIFI_AUTH_EVENT=2,
	ATBM_WIFI_ASSOC_EVENT=3,
	ATBM_WIFI_ASSOCRSP_TXOK_EVENT=4,
	ATBM_WIFI_DEASSOC_EVENT=5,
	ATBM_WIFI_SCANSTART_EVENT=6,
	ATBM_WIFI_SCANDONE_EVENT=7,

};

/*
event up to wpa_supplicant
event up to hostapd
event up to os

param: must copy to malloc buffer, will free 

*/
int atbm_wifiScan();

int atbmwifi_event_uplayer(struct atbmwifi_vif *priv,int eventid,void *param);
#endif //__ATBM_API_H__
