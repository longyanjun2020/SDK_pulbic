/*
 *
 * This defines the API between the Wireless LAN driver and the host application.
 * This interface provides APIs to:
 *   - Init/de-init the WLAN driver.
 *   - Perform scan.
 *
 */

#ifndef _INCLUDED_WLAN_IF_H_
#define _INCLUDED_WLAN_IF_H_

#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_BCM)
#define	WPS_AP_SUPPORT
#endif
#ifdef __cplusplus
extern "C" {
#endif

#include "net_cfg.h"
/* ---- Include Files ---------------------------------------------------- */

/* ---- Constants and Types ---------------------------------------------- */
typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned int	uint32;
typedef unsigned int	uint;
typedef signed char		int8;
typedef signed short	int16;

#define MCSSET_LEN  16  /* 16-bits per 8-bit set to give 128-bits bitmap of MCS Index */

typedef uint16 chanspec_t;

/* Wireless driver handle. */
typedef void* wl_drv_hdl;


/* Capability Information Field */
#define DOT11_CAP_ESS               0x0001  /* d11 cap. ESS */
#define DOT11_CAP_IBSS              0x0002  /* d11 cap. IBSS */
#define DOT11_CAP_POLLABLE          0x0004  /* d11 cap. pollable */
#define DOT11_CAP_POLL_RQ           0x0008  /* d11 cap. poll request */
#define DOT11_CAP_PRIVACY           0x0010  /* d11 cap. privacy */
#define DOT11_CAP_SHORT             0x0020  /* d11 cap. short */
#define DOT11_CAP_PBCC              0x0040  /* d11 cap. PBCC */
#define DOT11_CAP_AGILITY           0x0080  /* d11 cap. agility */
#define DOT11_CAP_SPECTRUM          0x0100  /* d11 cap. spectrum */
#define DOT11_CAP_SHORTSLOT         0x0400  /* d11 cap. shortslot */
#define DOT11_CAP_RRM           	0x1000  /* d11 cap. 11k radio measurement */
#define DOT11_CAP_CCK_OFDM          0x2000  /* d11 cap. CCK/OFDM */

#define HT_CAP_40MHZ        0x0002  /* FALSE:20Mhz, TRUE:20/40MHZ supported */
#define HT_CAP_SHORT_GI_20  0x0020  /* 20MHZ short guard interval support */
#define HT_CAP_SHORT_GI_40  0x0040  /* 40Mhz short guard interval support */

#define WL_CHANSPEC_BAND_MASK		0xf000
#define WL_CHANSPEC_BAND_SHIFT		12
#define WL_CHANSPEC_BAND_5G			0x1000
#define WL_CHANSPEC_BAND_2G			0x2000

#define WL_CHANSPEC_CHAN_MASK		0x00ff

#define WL_CHANSPEC_BW_MASK		0x0C00
#define WL_CHANSPEC_BW_SHIFT	10
#define WL_CHANSPEC_BW_10		0x0400
#define WL_CHANSPEC_BW_20		0x0800
#define WL_CHANSPEC_BW_40		0x0C00

#define CHSPEC_IS5G(chspec)	(((chspec) & WL_CHANSPEC_BAND_MASK) == WL_CHANSPEC_BAND_5G)
#define CHSPEC_IS2G(chspec)	(((chspec) & WL_CHANSPEC_BAND_MASK) == WL_CHANSPEC_BAND_2G)

#define CHSPEC_CHANNEL(chspec)	((uint8)((chspec) & WL_CHANSPEC_CHAN_MASK))

#define CHSPEC_IS20(chspec)	(((chspec) & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_20)
#define CHSPEC_IS40(chspec)	(((chspec) & WL_CHANSPEC_BW_MASK) == WL_CHANSPEC_BW_40)

#define NRATE_MCS_INUSE 0x00000080  /* MSC in use,indicates b0-6 holds an mcs */
#define NRATE_RATE_MASK 0x0000007f  /* rate/mcs value */

/* Supported authentication mode. */
/* Values are used to select the authentication mode used to join a network. */
enum {
	WLM_WPA_AUTH_DISABLED = 0x0000,	/* Legacy (i.e., non-WPA) */
	WLM_WPA_AUTH_NONE = 0x0001,		/* none (IBSS) */
	WLM_WPA_AUTH_PSK = 0x0004,		/* Pre-shared key */
	WLM_WPA2_AUTH_PSK = 0x0080		/* Pre-shared key */
};
typedef int WLM_AUTH_MODE;

/* WLAN Security Encryption. */
/* Values are used to select the type of encryption used for testing. */
enum {
	WLM_ENCRYPT_NONE = 0,    /* No encryption. */
	WLM_ENCRYPT_WEP = 1,     /* WEP encryption. */
	WLM_ENCRYPT_TKIP = 2,    /* TKIP encryption. */
	WLM_ENCRYPT_AES = 4,     /* AES encryption. */
	WLM_ENCRYPT_WSEC = 8,    /* Software WSEC encryption. */
	WLM_ENCRYPT_FIPS = 0x80  /* FIPS encryption. */
};
typedef int WLM_ENCRYPTION;

#ifndef NBBY		    /* the BSD family defines NBBY */
#define	NBBY	8	/* 8 bits per byte */
#endif /* #ifndef NBBY */
#define	isset(a, i)	(((const uint8 *)a)[(i)/NBBY] & (1<<((i)%NBBY)))

enum {
	WLM_CHANNEL_1 = 1,
	WLM_CHANNEL_2,
	WLM_CHANNEL_3,
	WLM_CHANNEL_4,
	WLM_CHANNEL_5,
	WLM_CHANNEL_6,
	WLM_CHANNEL_7,
	WLM_CHANNEL_8,
	WLM_CHANNEL_9,
	WLM_CHANNEL_10,
	WLM_CHANNEL_11,
	WLM_CHANNEL_12,
	WLM_CHANNEL_13
};
typedef int WLM_CHANNEL;

enum {
	WLM_RATE_AUTO = 0,
	WLM_RATE_1M = 2,
	WLM_RATE_2M = 4,
	WLM_RATE_5M5 = 11,
	WLM_RATE_6M = 12,
	WLM_RATE_9M = 18,
	WLM_RATE_11M = 22,
	WLM_RATE_12M = 24,
	WLM_RATE_18M = 36,
	WLM_RATE_24M = 48,
	WLM_RATE_36M = 72,
	WLM_RATE_48M = 96,
	WLM_RATE_54M = 108
};
typedef int WLM_RATE;

/* Supported MCS rates */
enum {
	WLM_MCS_RATE_0 = 0,
	WLM_MCS_RATE_1 = 1,
	WLM_MCS_RATE_2 = 2,
	WLM_MCS_RATE_3 = 3,
	WLM_MCS_RATE_4 = 4,
	WLM_MCS_RATE_5 = 5,
	WLM_MCS_RATE_6 = 6,
	WLM_MCS_RATE_7 = 7,
	WLM_MCS_RATE_8 = 8,
	WLM_MCS_RATE_9 = 9,
	WLM_MCS_RATE_10 = 10,
	WLM_MCS_RATE_11 = 11,
	WLM_MCS_RATE_12 = 12,
	WLM_MCS_RATE_13 = 13,
	WLM_MCS_RATE_14 = 14,
	WLM_MCS_RATE_15 = 15,
	WLM_MCS_RATE_16 = 16,
	WLM_MCS_RATE_17 = 17,
	WLM_MCS_RATE_18 = 18,
	WLM_MCS_RATE_19 = 19,
	WLM_MCS_RATE_20 = 20,
	WLM_MCS_RATE_21 = 21,
	WLM_MCS_RATE_22 = 22,
	WLM_MCS_RATE_23 = 23,
	WLM_MCS_RATE_24 = 24,
	WLM_MCS_RATE_25 = 25,
	WLM_MCS_RATE_26 = 26,
	WLM_MCS_RATE_27 = 27,
	WLM_MCS_RATE_28 = 28,
	WLM_MCS_RATE_29 = 29,
	WLM_MCS_RATE_30 = 30,
	WLM_MCS_RATE_31 = 31,
	WLM_MCS_RATE_32 = 32
};
typedef int WLM_MCS_RATE;

#if 0
enum {
	WLAN_DISCONNECTED = 0,
	WLAN_CONNECTED,
	WLAN_START_QUEUE,
	WLAN_STOP_QUEUE	
};
#else

/* Event messages */
#define WLC_E_SET_SSID		0	/* indicates status of set SSID */
#define WLC_E_JOIN		    1	/* differentiates join IBSS from found (WLC_E_START) IBSS */
#define WLC_E_START		    2	/* STA founded an IBSS or AP started a BSS */
#define WLC_E_AUTH		    3	/* 802.11 AUTH request */
#define WLC_E_AUTH_IND		4	/* 802.11 AUTH indication */
#define WLC_E_DEAUTH		5	/* 802.11 DEAUTH request */
#define WLC_E_DEAUTH_IND	6	/* 802.11 DEAUTH indication */
#define WLC_E_ASSOC		    7	/* 802.11 ASSOC request */
#define WLC_E_ASSOC_IND		8	/* 802.11 ASSOC indication */
#define WLC_E_REASSOC		9	/* 802.11 REASSOC request */
#define WLC_E_REASSOC_IND	10	/* 802.11 REASSOC indication */
#define WLC_E_DISASSOC		11	/* 802.11 DISASSOC request */
#define WLC_E_DISASSOC_IND	12	/* 802.11 DISASSOC indication */
#define WLC_E_QUIET_START	13	/* 802.11h Quiet period started */
#define WLC_E_QUIET_END		14	/* 802.11h Quiet period ended */
#define WLC_E_BEACON_RX		15	/* BEACONS received/lost indication */
#define WLC_E_LINK		    16	/* generic link indication */
#define WLC_E_MIC_ERROR		17	/* TKIP MIC error occurred */
#define WLC_E_NDIS_LINK		18	/* NDIS style link indication */
#define WLC_E_ROAM		    19	/* roam attempt occurred: indicate status & reason */
#define WLC_E_TXFAIL		20	/* change in dot11FailedCount (txfail) */
#define WLC_E_PMKID_CACHE	21	/* WPA2 pmkid cache indication */
#define WLC_E_RETROGRADE_TSF	22	/* current AP's TSF value went backward */
#define WLC_E_PRUNE	        23	/* AP was pruned from join list for reason */
#define WLC_E_AUTOAUTH		24	/* report AutoAuth table entry match for join attempt */
#define WLC_E_EAPOL_MSG		25	/* Event encapsulating an EAPOL message */
#define WLC_E_SCAN_COMPLETE	26	/* Scan results are ready or scan was aborted */
#define WLC_E_ADDTS_IND		27	/* indicate to host addts fail/success */
#define WLC_E_DELTS_IND		28	/* indicate to host delts fail/success */
#define WLC_E_BCNSENT_IND	29	/* indicate to host of beacon transmit */
#define WLC_E_BCNRX_MSG		30	/* Send the received beacon up to the host */
#define WLC_E_BCNLOST_MSG	31	/* indicate to host loss of beacon */
#define WLC_E_ROAM_PREP		32	/* before attempting to roam */
#define WLC_E_PFN_NET_FOUND	33	/* PFN network found event */
#define WLC_E_PFN_NET_LOST	34	/* PFN network lost event */
#define WLC_E_RESET_COMPLETE	35
#define WLC_E_JOIN_START	36
#define WLC_E_ROAM_START	37
#define WLC_E_ASSOC_START	38
#define WLC_E_IBSS_ASSOC	39
#define WLC_E_RADIO	        40
#define WLC_E_PSM_WATCHDOG	41	/* PSM microcode watchdog fired */

#if defined(BCMCCX) && defined(CCX_SDK)
#define WLC_E_CCX_ASSOC_START	42	/* CCX association start */
#define WLC_E_CCX_ASSOC_ABORT	43	/* CCX association abort */
#endif /* BCMCCX && CCX_SDK */

#define WLC_E_PROBREQ_MSG           44  /* probe request received */
#define WLC_E_SCAN_CONFIRM_IND      45
#define WLC_E_PSK_SUP		        46	/* WPA Handshake fail */
#define WLC_E_COUNTRY_CODE_CHANGED  47
#define	WLC_E_EXCEEDED_MEDIUM_TIME  48	/* WMMAC excedded medium time */
#define WLC_E_ICV_ERROR		        49	/* WEP ICV error occurred */
#define WLC_E_UNICAST_DECODE_ERROR  50	/* Unsupported unicast encrypted frame */
#define WLC_E_MULTICAST_DECODE_ERROR 51 /* Unsupported multicast encrypted frame */
#define WLC_E_TRACE		            52

#ifdef WLBTAMP
#define WLC_E_BTA_HCI_EVENT	53	/* BT-AMP HCI event */
#endif

#define WLC_E_IF		            54	/* I/F change (for dongle host notification) */

#ifdef WLP2P
#define WLC_E_P2P_DISC_LISTEN_COMPLETE 	55	/* listen state expires */
#endif

#define WLC_E_RSSI		            56	/* indicate RSSI change based on configured levels */
#define WLC_E_PFN_SCAN_COMPLETE	    57	/* PFN completed scan of network list */
#define WLC_E_EXTLOG_MSG            58
#define WLC_E_ACTION_FRAME          59 	/* Action frame Rx */
#define WLC_E_ACTION_FRAME_COMPLETE 60	/* Action frame Tx complete */
#define WLC_E_PRE_ASSOC_IND         61	/* assoc request received */
#define WLC_E_PRE_REASSOC_IND       62	/* re-assoc request received */
#define WLC_E_CHANNEL_ADOPTED       63
#define WLC_E_AP_STARTED            64	/* AP started */
#define WLC_E_DFS_AP_STOP           65	/* AP stopped due to DFS */
#define WLC_E_DFS_AP_RESUME         66	/* AP resumed due to DFS */
#define WLC_E_WAI_STA_EVENT         67	/* WAI stations event */
#define WLC_E_WAI_MSG               68	/* event encapsulating an WAI message */
#define WLC_E_ESCAN_RESULT          69	/* escan result event */
#define WLC_E_ACTION_FRAME_OFF_CHAN_COMPLETE 	70	/* action frame off channel complete */

#if defined(WLP2P) || defined(UNDER_CE)
#define WLC_E_PROBRESP_MSG	71	/* probe response received */
#define WLC_E_P2P_PROBREQ_MSG	72	/* P2P Probe request received */
#endif

#define WLC_E_DCS_REQUEST       73

#define WLC_E_FIFO_CREDIT_MAP	74 /* credits for D11 FIFOs. [AC0,AC1,AC2,AC3,BC_MC,ATIM] */

#define WLC_E_ACTION_FRAME_RX	75	/* Received action frame event WITH
                                     * wl_event_rx_frame_data_t header
                                     */
#define WLC_E_WAKE_EVENT	    76	/* Wake Event timer fired, used for wake WLAN test mode */
#define WLC_E_RM_COMPLETE	    77	/* Radio measurement complete */
#define WLC_E_HTSFSYNC		    78	/* Synchronize TSF with the host */
#define WLC_E_OVERLAY_REQ	    79	/* request an overlay IOCTL/iovar from the host */
#define WLC_E_CSA_COMPLETE_IND  80
#define WLC_E_EXCESS_PM_WAKE_EVENT	81	/* excess PM Wake Event to inform host  */
#define WLC_E_PFN_SCAN_NONE	    82	/* no PFN networks around */
#define WLC_E_PFN_SCAN_ALLGONE  83	/* last found PFN network gets lost */
#define WLC_E_LAST              84	/* highest val + 1 for range checking */
#endif

/* Supported join modes. */
/* Values are used to select the mode used to join a network. */
enum {
	WLM_MODE_IBSS = 0,   /* IBSS Mode. (Adhoc) */
	WLM_MODE_BSS = 1,    /* BSS Mode. */
	WLM_MODE_AUTO = 2    /* Auto. */
};
typedef int WLM_JOIN_MODE;

typedef struct wl_ssid
{
    /* SSID Length */
    unsigned long SsidLength;

    /* SSID information field */
    unsigned char Ssid[32];
} wl_ssid_t;

/** WEP_KEY */
typedef struct wl_wep_key
{
    unsigned long KeyLength;		//length in bytes
    unsigned char KeyMaterial[16];	//hexadecimal
} wl_wep_key_t;

typedef struct wl_config_info
{
    WLM_JOIN_MODE		InfrastructureMode;
    wl_ssid_t			Ssid;
	unsigned char 		InfraBssid[6];
	
    // Security settings
    WLM_AUTH_MODE   	Auth_Mode;
    WLM_ENCRYPTION   	Enc_Mode;
    wl_wep_key_t 		Wep_Key[4];
    unsigned char   	WepKeyToUse;		//Specifies the WEP key index(0:key 1, 1:key 2, 2:key 3, 3:key 4). 
    unsigned char		PresharedKey[64];	//Preshared key for WPA-PSK or WPA2-PSK    
    unsigned int 		Psk_length;    
} wl_config_info_t;

typedef enum _WscSecurityMode{
	WPA2PSKAES,
	WPA2PSKTKIP,
	WPAPSKAES,
	WPAPSKTKIP
}WSC_SECURITY_MODE;

/** WLAN_802_11_SSID */
#define	SSID_LEN	32
#define	WPAKEY_LEN	64
typedef struct _WLAN_802_11_SSID
{
    /* SSID Length */
    uint32 SsidLength;

    /* SSID information field */
    uint8 Ssid[SSID_LEN];
} WLAN_802_11_SSID;

typedef struct _WPS_CONFIG_INFO
{	
	unsigned long	WscMode;		// predefined WSC mode, 1: PIN, 2: PBC
	unsigned char	PIN[8];			// 8 bytes PIN nunmber
	unsigned char 	Bssid[6];
	unsigned char	JoinAP;			//1: to join AP after WPS success, 0: Not to join AP after WPS success
	unsigned int	ScanBufSize;	//WPS scan buffer size, max 32KB
	unsigned int	AssocAPTime;	//Time to associate target AP in mili-seconds, default is 20000 (20s)	
#ifdef WPS_AP_SUPPORT
	WLAN_802_11_SSID	Ssid;
	WSC_SECURITY_MODE 	WscSecurityMode;
	unsigned char       WpaPsk[64];
    int             	WpaPskLen;
	int 				channel; 
	int 				ssidBcst;	
#endif
} WPS_CONFIG_INFO, *PWPS_CONFIG_INFO;

typedef WPS_CONFIG_INFO wps_config_info_t;

#ifdef WPS_AP_SUPPORT

typedef	enum _WPSState
{
	WPS_STATE_OFF,
	WPS_STATE_INIT,
	WPS_STATE_START,
	WPS_STATE_FAIL,
   	WPS_STATE_CONFIGURED,
   	WPS_STATE_LINK_UP,
   	WPS_STATE_SEND_EAPOL_START,
	WPS_STATE_WAIT_EAPOL_START,
	WPS_STATE_WAIT_UPNP_START,
	WPS_STATE_WAIT_REQ_ID,
	WPS_STATE_WAIT_RESP_ID,
	WPS_STATE_WAIT_START,
	WPS_STATE_WAIT_M1,
	WPS_STATE_SENT_M1,
	WPS_STATE_SENT_M2D,
	WPS_STATE_WAIT_M2,
	WPS_STATE_RX_M2D,
	WPS_STATE_WAIT_PIN,
	WPS_STATE_WAIT_M3,
	WPS_STATE_WAIT_M4,
	WPS_STATE_WAIT_M5,
	WPS_STATE_WAIT_M6,
	WPS_STATE_WAIT_M7,
	WPS_STATE_WAIT_M8,
	WPS_STATE_WAIT_DONE,
	WPS_STATE_WAIT_ACK,
	WPS_STATE_WAIT_EAPFAIL,
	WPS_STATE_WAIT_DISCONN
}	WPS_STATE;

#else
// For WSC state machine states.
// We simplified it
typedef	enum _WPSState
{
	WPS_STATE_OFF,
	WPS_STATE_INIT,		
	WPS_STATE_START,
	WPS_STATE_CONN_FAIL,
	WPS_STATE_FAIL,	
	WPS_STATE_LINK_UP,
	WPS_STATE_WAIT_START,
	WPS_STATE_WAIT_M2,
	WPS_STATE_RX_M2D,	
	WPS_STATE_WAIT_M4,
	WPS_STATE_WAIT_M6,
	WPS_STATE_WAIT_M8,
	WPS_STATE_WAIT_EAPFAIL,
	WPS_STATE_WAIT_DISCONN,
	WPS_STATE_CONFIGURED
}	WPS_STATE;
#endif

// Wsc status code
#define	STATUS_WSC_NOTUSED						0x0000
#define	STATUS_WSC_IDLE							0x0001
#define	STATUS_WSC_START_ASSOC					0x0002		// Begin associating to WPS AP
#define	STATUS_WSC_LINK_UP						0x0003		// Associated to WPS AP
#define	STATUS_WSC_EAPOL_START_SENT				0x0004		// Sending EAPOL-Start
#define	STATUS_WSC_EAP_REQ_ID_SENT				0x0005		// Sending EAP-Rsp(ID)
#define	STATUS_WSC_EAP_REQ_WSC_START			0x0006		// Receive EAPReq WPS_Start
#define	STATUS_WSC_EAP_M1_SENT					0x0007		// Sending M1
#define	STATUS_WSC_EAP_M2_RECEIVED				0x0008		// Received M2
#define	STATUS_WSC_EAP_M2D_RECEIVED				0x0009		// Received M2D
#define	STATUS_WSC_EAP_RSP_ACK_SENT				0x000A		// Sending EAP Response (ACK)
#define	STATUS_WSC_EAP_M3_SENT					0x000B		// Sending M3
#define	STATUS_WSC_EAP_M4_RECEIVED				0x000C		// Received M4
#define	STATUS_WSC_EAP_M5_SENT					0x000D		// Sending M5
#define	STATUS_WSC_EAP_M6_RECEIVED				0x000E		// Received M6
#define	STATUS_WSC_EAP_M7_SENT					0x000F		// Sending M7
#define	STATUS_WSC_EAP_M8_RECEIVED				0x0010		// Received M8
#define	STATUS_WSC_EAP_RSP_DONE_SENT			0x0011		// Sending EAP Response (Done)
#define	STATUS_WSC_EAP_CONFIGURED				0x0012		// Configured
#define	STATUS_WSC_SCAN_AP						0x0013		// Scanning AP
#define STATUS_WSC_PIN_SEACH_MATCH_AP			0x0014		// search AP
#define STATUS_WSC_PBC_TIMEOUT					0x0015		// PBC time out
#define	STATUS_WSC_START_REASSOC				0x0016		// Begin associating to WPS AP
#define STATUS_WSC_EAP_RSP_NACK_SENT			0x0017		// Sending EAP Response (NACK)

// All error message dtarting from 0x0100
#define	STATUS_WSC_PBC_TOO_MANY_AP				0x0101		// Too many PBC AP avaliable
#define	STATUS_WSC_PBC_NO_AP					0x0102		// No PBC AP avaliable
#define	STATUS_WSC_EAP_FAIL_RECEIVED			0x0103		// Received EAP-FAIL
#define	STATUS_WSC_EAP_NONCE_MISMATCH			0x0104		// Receive EAP with wrong NONCE
#define	STATUS_WSC_EAP_INVALID_DATA				0x0105		// Receive EAP without integrity (Hmac mismatch)
#define STATUS_WSC_PASSWORD_MISMATCH			0x0106		// Error PIN Code (R-Hash mismatch)
#define	STATUS_WSC_EAP_REQ_WRONG_SMI			0x0107		// Receive EAP-Req with wrong WPS SMI Vendor Id
#define	STATUS_WSC_EAP_REQ_WRONG_VENDOR_TYPE	0x0108		// Receive EAPReq with wrong WPS Vendor Type

// Error message, UI stop querying
//#define	STATUS_WSC_INVALID_SSID					0x0201		// Invalid SSID/BSSID in PIN mode				//TODO: not used
//#define	STATUS_WSC_EAP_REQ_WRONG_SMI			0x0202		// Receive EAP-Req with wrong WPS SMI Vendor Id	//TODO: move to 0x01ff
//#define	STATUS_WSC_EAP_REQ_WRONG_VENDOR_TYPE	0x0203		// Receive EAPReq with wrong WPS Vendor Type	//TODO: move to 0x01ff
#define	STATUS_WSC_EAP_FAILED					0x0204		// WPS EAP process failed

#define BCM_MSG_IFNAME_MAX		16	/* max length of interface name */

typedef struct wl_connection_info
{
	uint8	Ssid_len;
	uint8	Ssid[32];
	int	 	Rssi;
	int		Phy_rate;
	int 	channel;
} wl_connection_info_t;

struct __attribute__((packed)) ether_addr_packed {
	uint8 mac[6];
};

/* ----------------------------------------------------------------------- */
char* wf_chspec_ntoa(chanspec_t chspec, char *buf);
const char* capmode2str(uint16 capability);
/* ----------------------------------------------------------------------- */

/*defined in "bcmevent.h" */
typedef struct __attribute__((packed)) wlan_event_msg
{
	uint16	version;
	uint16	flags;			/* see flags below */
	uint32	event_type;		/* Message (see below) */
	uint32	status;			/* Status code (see below) */
	uint32	reason;			/* Reason code (if applicable) */
	uint32	auth_type;		/* WLC_E_AUTH */
	uint32	datalen;		/* data buf */
	struct ether_addr_packed	addr;	/* Station address (if applicable) */
	char	ifname[BCM_MSG_IFNAME_MAX]; /* name of the packet incoming interface */
	uint8	ifidx;			/* destination OS i/f index */
	uint8	bsscfgidx;		/* source bsscfg index */
} wlan_event_msg_t;

typedef int WLAN_EVET_MSQ;
/****************************************************************************
* Function:   wlan_drv_event_callback
*
* Purpose:    User registered callback to receive events.
*
* Parameters: event      (in) Driver event.
*
* Returns:    Nothing.
*****************************************************************************
*/

typedef void (*wlan_drv_event_callback)(wlan_event_msg_t* event);

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
wl_drv_hdl wlan_start(wlan_drv_event_callback cb, uint tx_buf_cnt, uint rx_buf_cnt, uint scan_buf_size);



/****************************************************************************
* Function:   	wlan_stop
*
* Purpose:   	This routine is used to de-initialize GB9619 module.
*
* Parameters: hdl	Handle to the Wi-Fi driver.
*
* Returns:	None.
*****************************************************************************
*/
void wlan_stop(wl_drv_hdl hdl);


/****************************************************************************
* Function:   	wlan_scan_network
*
* Purpose:   	This routine is used to ask driver to perform site survey and return scan result.
*
* Parameters: scan_buf		Buffer to store the information of the found APs
*			buf_size		Size of the buffer
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int wlan_scan_network(char* scan_buf, uint buf_size);


/****************************************************************************
* Function:   	wlan_set_scan
*
* Purpose:   	This routine is used to ask driver to perform site survey.
*
* Parameters: None
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int wlan_set_scan(void);


/****************************************************************************
* Function:   	wlan_get_scan
*
* Purpose:   	This routine is used to ask driver to return scan result.
*
* Parameters: scan_buf		Buffer to store the information of the found APs
*			buf_size		Size of the buffer
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int wlan_get_scan(char* scan_buf, uint buf_size);


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
int wlan_join_network(char *ssid, WLM_AUTH_MODE authMode, WLM_ENCRYPTION encryption, const char *key);


/****************************************************************************
* Function:   	wlan_join_network
*
* Purpose:   	This routine is used to ask driver to join a netwrok.
*
* Parameters: ssid			SSID of the AP used to join a network
*			 bssid		BSSID of the AP			
*			 authMode	Authentication mode used to join a network
*			 encryption	Encryption mode used to join a network
*			 key			Passphrase used to join a network
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int wlan_join_network_bssid(char *ssid, char *bssid, WLM_AUTH_MODE authMode, WLM_ENCRYPTION encryption, const char *key);


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
int wlan_create_sw_ap(	char* ssid, WLM_AUTH_MODE authMode, WLM_ENCRYPTION encryption, 
							const char *key, WLM_CHANNEL channel, int ssidBcst );


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
int wlan_get_assoc_list(char* buf, uint buf_size);


/****************************************************************************
* Function:   	wlan_get_tx_queue_avail_count
*
* Purpose:   	This routine is used to return the available buffer count of driver TX queue
*
* Parameters: None
*
* Returns:	Returns # of available buffer count of driver TX queue.
*****************************************************************************
*/
int wlan_get_tx_queue_avail_count(void);


/****************************************************************************
* Function:   	wlan_get_version
*
* Purpose:   	This routine is used to return the driver release version
*
* Parameters: None
*
* Returns:	Returns the driver release version
*****************************************************************************
*/
char* wlan_get_version(void);


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
int wlan_get_connection_info(wl_connection_info_t *wlan_connection_info);


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
int wlan_get_mode(void);


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
void wlan_get_mac_addr(uint8* mac_addr);


/****************************************************************************
* Function:   	wlan_add_ie
*
* Purpose:   	This routine is used to add a vendor-specific IE to Beacon and Probe response management packets
*
* Parameters: pktflag 		A 4-bit field that indicates packets to which the IE is to be added. Bits defined as follows:
*							Bit 0: Beacons
*							Bit 1: Probe responses
*							Bit 2: Association and reassociation response
*							Bit 3: Authorization responses
*			oui			The vendors 3-byte organizationally unique identifier in the format xx:yy:zz
*			ie_data		The remaining IE bytes (excluding oui)
*			ie_data_len	Indicates the IEs byte length (ie_data + oui)
*
* Returns:	None.
*****************************************************************************
*/
int wlan_add_ie(int pktflag, char* oui, char* ie_data, int ie_data_len);


/****************************************************************************
* Function:   	wlan_del_ie
*
* Purpose:   	This routine is used to get wifi MAC addressi
*
* Parameters: pktflag 		A 4-bit field that indicates packets to which the IE is to be added. Bits defined as follows:
*							Bit 0: Beacons
*							Bit 1: Probe responses
*							Bit 2: Association and reassociation response
*							Bit 3: Authorization responses
*			oui			The vendors 3-byte organizationally unique identifier in the format xx:yy:zz
*			ie_data		The remaining IE bytes (excluding oui)
*			ie_data_len	Indicates the IEs byte length (ie_data + oui)
*
* Returns:	None.
*****************************************************************************
*/
int wlan_del_ie(int pktflag, char* oui, char* ie_data, int ie_data_len);


/****************************************************************************
 * Registers interest in a multicast address
 * Once a multicast address has been registered, all packets detected on the
 * medium destined for that address are forwarded to the host.
 * Otherwise they are ignored.
 *
 * @param mac: MAC address
 *
 * @return  0 : if the address was registered successfully
 *         	Nonzero  : if the address was not registered
 ****************************************************************************
 */
int wlan_wifi_register_multicast_address( uint8* mac );

/****************************************************************************
 * Unregisters interest in a multicast address
 * Once a multicast address has been unregistered, all packets detected on the
 * medium destined for that address are ignored.
 *
 * @param mac: MAC address
 *
 * @return  0 : if the address was unregistered successfully
 *          Nonzero  : if the address was not unregistered
 ****************************************************************************
 */
int wlan_wifi_unregister_multicast_address( uint8* mac );

/****************************************************************************
* Function:   wlan_wps_event_callback
*
* Purpose:    User registered callback to receive wps events.
*
* Parameters: event      (in) WPS events.
*
* Returns:    None.
*****************************************************************************
*/
typedef void (*wlan_wps_event_callback)(WPS_STATE event);


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
int wlan_wps_start(wps_config_info_t wps_config_info, wlan_wps_event_callback cb);


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
int wlan_wps_stop(void);


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
int wlan_wps_gen_pin(uint *pin);


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
int wlan_wps_get_credentials(wl_config_info_t *wlan_config_info);


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
unsigned long wlan_wps_get_state(void);


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
unsigned long wlan_wps_get_status(void);


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
int wlan_mfg_tx_bg(WLM_CHANNEL channel, WLM_RATE rate, int powerValue);


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
int wlan_mfg_tx_n(WLM_CHANNEL channel, WLM_MCS_RATE rate, int powerValue);


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
int wlan_mfg_rx(WLM_CHANNEL channel);


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
int wlan_mfg_rx_getpkt(unsigned int *count);


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
int wlan_mfg_carrier_tone(WLM_CHANNEL channel);
	

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
int wlan_mfg_stop(void);


/****************************************************************************
* Function:   	wlu_main_args
*
* Purpose:   	This routine is the main entry point of wl utility
*
* Parameters: argc		count of arguments
*			argv		the pointer of arguments
*
* Returns:	Returns 0 if succeed, otherwise a negative error code.
*****************************************************************************
*/
int wlu_main_args(int argc, char **argv);


#ifdef WPS_AP_SUPPORT
extern int AP_StartWPS(wps_config_info_t *pwps_config_info, wlan_wps_event_callback cb);
extern void AP_StopWPS(void* pVariable);
#endif

#ifdef __cplusplus
	}
#endif

#endif	/* _INCLUDED_WLAN_IF_H_ */
