//==============================================================================
//
//  Description : 
//  Author      : 
//  Revision    : 
//    Truman@131224 For better portibility to other chips, switch the type from
//    AHC_Common.h to typedefs.h
//
//==============================================================================
#ifndef _WLAN_MTK_H
#define _WLAN_MTK_H

#include "wlanif.h"
#include "wlantypedefs.h"
#include "netif.h"//for "struct pbuf" which will be referred to in mtk_wifi_adapter.h
#include "mtk_wifi_adapter.h"
/***********************************************************************************

WIFI-Related
SSID:   Service Set ID
BSSID:  Basic Service Set ID, Mac-Address
ESSID:  Extended Service Set ID
IBSSID: Independent BSSID 

*/

#define WLAN_SCAN_BUF_SIZE  (4096)
#define WLAN_SCAN_FILE_NAME ("SD:\\DATA\\wlanscan.txt")
#define WLAN_NAME_LENGTH    (128)
#define WLAN_ETHER_ETOA     wl_ether_etoa
#define CAPMODE2STR         capmode2str
#define WLU_MAIN_ARGS       wlu_main_args
/* Wireless driver handle. */
typedef void* WLAN_DRV_HDL;


/* Capability Information Field */
#define WLAN_DOT11_CAP_ESS               0x0001  /* d11 cap. ESS */
#define WLAN_DOT11_CAP_IBSS              0x0002  /* d11 cap. IBSS */
#define WLAN_DOT11_CAP_POLLABLE          0x0004  /* d11 cap. pollable */
#define WLAN_DOT11_CAP_POLL_RQ           0x0008  /* d11 cap. poll request */
#define WLAN_DOT11_CAP_PRIVACY           0x0010  /* d11 cap. privacy */
#define WLAN_DOT11_CAP_SHORT             0x0020  /* d11 cap. short */
#define WLAN_DOT11_CAP_PBCC              0x0040  /* d11 cap. PBCC */
#define WLAN_DOT11_CAP_AGILITY           0x0080  /* d11 cap. agility */
#define WLAN_DOT11_CAP_SPECTRUM          0x0100  /* d11 cap. spectrum */
#define WLAN_DOT11_CAP_SHORTSLOT         0x0400  /* d11 cap. shortslot */
#define WLAN_DOT11_CAP_RRM           	 0x1000  /* d11 cap. 11k radio measurement */
#define WLAN_DOT11_CAP_CCK_OFDM          0x2000  /* d11 cap. CCK/OFDM */


#define WLAN_HT_CAP_40MHZ           0x0002  /* FALSE:20Mhz, TRUE:20/40MHZ supported */
#define WLAN_HT_CAP_SHORT_GI_20     0x0020  /* 20MHZ short guard interval support */
#define WLAN_HT_CAP_SHORT_GI_40     0x0040  /* 40Mhz short guard interval support */

#define WLAN_CHANSPEC_BAND_MASK     0xf000
#define WLAN_CHANSPEC_BAND_SHIFT    12
#define WLAN_CHANSPEC_BAND_5G       0x1000
#define WLAN_CHANSPEC_BAND_2G       0x2000

#define WLAN_CHANSPEC_CHAN_MASK     0x00ff

#define WLAN_CHANSPEC_BW_MASK       0x0C00
#define WLAN_CHANSPEC_BW_SHIFT      10
#define WLAN_CHANSPEC_BW_10         0x0400
#define WLAN_CHANSPEC_BW_20         0x0800
#define WLAN_CHANSPEC_BW_40         0x0C00

#define WLAN_CHSPEC_IS5G(chspec)	(((chspec) & WLAN_CHANSPEC_BAND_MASK) == WLAN_CHANSPEC_BAND_5G)
#define WLAN_CHSPEC_IS2G(chspec)	(((chspec) & WLAN_CHANSPEC_BAND_MASK) == WLAN_CHANSPEC_BAND_2G)

#define WLAN_CHSPEC_CHANNEL(chspec)	((uint8)((chspec) & WLAN_CHANSPEC_CHAN_MASK))

#define WLAN_CHSPEC_IS20(chspec)	(((chspec) & WLAN_CHANSPEC_BW_MASK) == WLAN_CHANSPEC_BW_20)
#define WLAN_CHSPEC_IS40(chspec)	(((chspec) & WLAN_CHANSPEC_BW_MASK) == WLAN_CHANSPEC_BW_40)

#define WLAN_NRATE_MCS_INUSE        0x00000080  /* MSC in use,indicates b0-6 holds an mcs */
#define WLAN_NRATE_RATE_MASK        0x0000007F  /* rate/mcs value */
#define WLAN_MCSSET_LEN             16  /* 16-bits per 8-bit set to give 128-bits bitmap of MCS Index */

typedef uint16 CHANSPEC;




/* BSS info structure
 * Applications MUST CHECK ie_offset field and length field to access IEs and
 * next bss_info structure in a vector (in wl_scan_results_t)
 */
typedef struct _WLAN_BSS_INFO
{
	uint32      version;        /* version field */
	uint32      length;         /* byte length of data in this record,
						 		  * starting at version and including IEs
						 		  */
	uint8		BSSID[6];
	uint16      beacon_period;  /* units are Kusec */
	uint16      capability;     /* Capability information */
	uint8       SSID_len;
	uint8       SSID[32];
	
	struct {
		uint32  count;          /* # rates in this set */
		uint8   rates[16];      /* rates in 500kbps units w/hi bit set if basic */
	} rateset;              	/* supported rates */
	
	CHANSPEC    chanspec;       /* chanspec for bss */
	uint16      atim_window;    /* units are Kusec */
	uint8       dtim_period;    /* DTIM period */
	int16       RSSI;           /* receive signal strength (in dBm) */
	int8        phy_noise;      /* noise (in dBm) */
	uint8       n_cap;          /* BSS is 802.11N Capable */
	uint32      nbss_cap;       /* 802.11N BSS Capabilities (based on HT_CAP_*) */
	uint8       ctl_ch;         /* 802.11N BSS control channel number */
	uint32      reserved32[1];  /* Reserved for expansion of BSS properties */
	uint8       flags;          /* flags */
	uint8       reserved[3];    /* Reserved for expansion of BSS properties */
	uint8       basic_mcs[WLAN_MCSSET_LEN];  /* 802.11N BSS required MCS set */
	uint16      ie_offset;      /* offset at which IEs start, from beginning */
	uint32      ie_length;      /* byte length of Information Elements */
	int16       SNR;            /* average SNR of during frame reception */
	/* Add new fields here */
	/* variable length Information Elements */
} WLAN_BSS_INFO;

typedef struct _WLAN_SCAN_RESULT {
	uint32 buflen;
	uint32 version;
	uint32 count;
	WLAN_BSS_INFO bss_info[1];
} WLAN_SCAN_RESULT;


/* Supported authentication mode. */
/* Values are used to select the authentication mode used to join a network. */
enum {
	WLAN_WPA_AUTH_DISABLED = 0x0000,	/* Legacy (i.e., non-WPA) */
	WLAN_WPA_AUTH_NONE = 0x0001,		/* none (IBSS) */
	WLAN_WPA_AUTH_PSK = 0x0004,		/* Pre-shared key */
	WLAN_WPA2_AUTH_PSK = 0x0080		/* Pre-shared key */
};
typedef int WLAN_AUTH_MODE;

/* WLAN Security Encryption. */
/* Values are used to select the type of encryption used for testing. */
enum {
	WLAN_ENCRYPT_NONE = 0,    /* No encryption. */
	WLAN_ENCRYPT_WEP = 1,     /* WEP encryption. */
	WLAN_ENCRYPT_TKIP = 2,    /* TKIP encryption. */
	WLAN_ENCRYPT_AES = 4,     /* AES encryption. */
	WLAN_ENCRYPT_WSEC = 8,    /* Software WSEC encryption. */
	WLAN_ENCRYPT_FIPS = 0x80  /* FIPS encryption. */
};
typedef int WLAN_ENCRYPTION;

#ifndef WLAN_NBBY		    /* the BSD family defines NBBY */
#define	WLAN_NBBY	8	/* 8 bits per byte */
#endif /* #ifndef NBBY */

#define	ISSET(a, i)	(((const uint8 *)a)[(i)/WLAN_NBBY] & (1<<((i)%WLAN_NBBY)))

enum {
	WLAN_CHANNEL_1 = 1,
	WLAN_CHANNEL_2,
	WLAN_CHANNEL_3,
	WLAN_CHANNEL_4,
	WLAN_CHANNEL_5,
	WLAN_CHANNEL_6,
	WLAN_CHANNEL_7,
	WLAN_CHANNEL_8,
	WLAN_CHANNEL_9,
	WLAN_CHANNEL_10,
	WLAN_CHANNEL_11,
	WLAN_CHANNEL_12,
	WLAN_CHANNEL_13
};
typedef int WLAN_CHANNEL;

enum {
	WLAN_RATE_1M = WNDRV_TEST_RATE_1M,		/* 1M          */
	WLAN_RATE_2M,         					/* 2M          */
	WLAN_RATE_5_5M,       					/* 5.5M        */
	WLAN_RATE_11M,        					/* 11M         */
	WLAN_RATE_6M,         					/* 6M          */
	WLAN_RATE_9M,         					/* 9M          */
	WLAN_RATE_12M,        					/* 12M         */
	WLAN_RATE_18M,        					/* 18M         */
	WLAN_RATE_24M,        					/* 24M         */
	WLAN_RATE_36M,        					/* 36M         */
	WLAN_RATE_48M,        					/* 48M         */
	WLAN_RATE_54M         					/* 54M         */
};
typedef int WLAN_RATE;

/* Supported MCS rates */
enum {
	WLAN_MCS_RATE_0 = WNDRV_TEST_MOD_MCS0,        	/* 802.11n MSC 0 */
	WLAN_MCS_RATE_1,        						/* 802.11n MSC 1 */
	WLAN_MCS_RATE_2,        						/* 802.11n MSC 2 */
	WLAN_MCS_RATE_3,        						/* 802.11n MSC 3 */
	WLAN_MCS_RATE_4,        						/* 802.11n MSC 4 */
	WLAN_MCS_RATE_5,        						/* 802.11n MSC 5 */
	WLAN_MCS_RATE_6,        						/* 802.11n MSC 6 */
	WLAN_MCS_RATE_7,        						/* 802.11n MSC 7 */
	WLAN_MCS_RATE_32       							/* 802.11n MSC 32 */
};
typedef int WLAN_MCS_RATE;

#if 0
enum {
	WLAN_DISCONNECTED = 0,
	WLAN_CONNECTED,
	WLAN_START_QUEUE,
	WLAN_STOP_QUEUE	
};
#else

/* Event messages */
#define WLAN_E_SET_SSID         0	/* indicates status of set SSID */
#define WLAN_E_JOIN             1	/* differentiates join IBSS from found (WLC_E_START) IBSS */
#define WLAN_E_START            2	/* STA founded an IBSS or AP started a BSS */
#define WLAN_E_AUTH             3	/* 802.11 AUTH request */
#define WLAN_E_AUTH_IND         4	/* 802.11 AUTH indication */
#define WLAN_E_DEAUTH           5	/* 802.11 DEAUTH request */
#define WLAN_E_DEAUTH_IND       6	/* 802.11 DEAUTH indication */
#define WLAN_E_ASSOC            7	/* 802.11 ASSOC request */
#define WLAN_E_ASSOC_IND        8	/* 802.11 ASSOC indication */
#define WLAN_E_REASSOC          9	/* 802.11 REASSOC request */
#define WLAN_E_REASSOC_IND      10	/* 802.11 REASSOC indication */
#define WLAN_E_DISASSOC         11	/* 802.11 DISASSOC request */
#define WLAN_E_DISASSOC_IND     12	/* 802.11 DISASSOC indication */
#define WLAN_E_QUIET_START      13	/* 802.11h Quiet period started */
#define WLAN_E_QUIET_END        14	/* 802.11h Quiet period ended */
#define WLAN_E_BEACON_RX        15	/* BEACONS received/lost indication */
#define WLAN_E_LINK             16	/* generic link indication */
#define WLAN_E_MIC_ERROR        17	/* TKIP MIC error occurred */
#define WLAN_E_NDIS_LINK        18	/* NDIS style link indication */
#define WLAN_E_ROAM             19	/* roam attempt occurred: indicate status & reason */
#define WLAN_E_TXFAIL           20	/* change in dot11FailedCount (txfail) */
#define WLAN_E_PMKID_CACHE      21	/* WPA2 pmkid cache indication */
#define WLAN_E_RETROGRADE_TSF   22	/* current AP's TSF value went backward */
#define WLAN_E_PRUNE            23	/* AP was pruned from join list for reason */
#define WLAN_E_AUTOAUTH         24	/* report AutoAuth table entry match for join attempt */
#define WLAN_E_EAPOL_MSG		25	/* Event encapsulating an EAPOL message */
#define WLAN_E_SCAN_COMPLETE	26	/* Scan results are ready or scan was aborted */
#define WLAN_E_ADDTS_IND		27	/* indicate to host addts fail/success */
#define WLAN_E_DELTS_IND		28	/* indicate to host delts fail/success */
#define WLAN_E_BCNSENT_IND      29	/* indicate to host of beacon transmit */
#define WLAN_E_BCNRX_MSG        30	/* Send the received beacon up to the host */
#define WLAN_E_BCNLOST_MSG      31	/* indicate to host loss of beacon */
#define WLAN_E_ROAM_PREP        32	/* before attempting to roam */
#define WLAN_E_PFN_NET_FOUND    33	/* PFN network found event */
#define WLAN_E_PFN_NET_LOST     34	/* PFN network lost event */
#define WLAN_E_RESET_COMPLETE   35
#define WLAN_E_JOIN_START       36
#define WLAN_E_ROAM_START       37
#define WLAN_E_ASSOC_START      38
#define WLAN_E_IBSS_ASSOC       39
#define WLAN_E_RADIO            40
#define WLAN_E_PSM_WATCHDOG     41	/* PSM microcode watchdog fired */

#define WLAN_E_PROBREQ_MSG              44  /* probe request received */
#define WLAN_E_SCAN_CONFIRM_IND         45
#define WLAN_E_PSK_SUP                  46  /* WPA Handshake fail */
#define WLAN_E_COUNTRY_CODE_CHANGED     47
#define	WLAN_E_EXCEEDED_MEDIUM_TIME     48  /* WMMAC excedded medium time */
#define WLAN_E_ICV_ERROR                49  /* WEP ICV error occurred */
#define WLAN_E_UNICAST_DECODE_ERROR     50  /* Unsupported unicast encrypted frame */
#define WLAN_E_MULTICAST_DECODE_ERROR   51  /* Unsupported multicast encrypted frame */
#define WLAN_E_TRACE                    52

#define WLAN_E_IF                       54	/* I/F change (for dongle host notification) */

#define WLAN_E_RSSI                     56	/* indicate RSSI change based on configured levels */
#define WLAN_E_PFN_SCAN_COMPLETE        57	/* PFN completed scan of network list */
#define WLAN_E_EXTLOG_MSG               58
#define WLAN_E_ACTION_FRAME             59 	/* Action frame Rx */
#define WLAN_E_ACTION_FRAME_COMPLETE    60	/* Action frame Tx complete */
#define WLAN_E_PRE_ASSOC_IND            61	/* assoc request received */
#define WLAN_E_PRE_REASSOC_IND          62	/* re-assoc request received */
#define WLAN_E_CHANNEL_ADOPTED          63
#define WLAN_E_AP_STARTED               64	/* AP started */
#define WLAN_E_DFS_AP_STOP              65	/* AP stopped due to DFS */
#define WLAN_E_DFS_AP_RESUME            66	/* AP resumed due to DFS */
#define WLAN_E_WAI_STA_EVENT            67	/* WAI stations event */
#define WLAN_E_WAI_MSG                  68	/* event encapsulating an WAI message */
#define WLAN_E_ESCAN_RESULT             69	/* escan result event */
#define WLAN_E_ACTION_FRAME_OFF_CHAN_COMPLETE   70	/* action frame off channel complete */

#define WLAN_E_DCS_REQUEST              73

#define WLAN_E_FIFO_CREDIT_MAP          74 /* credits for D11 FIFOs. [AC0,AC1,AC2,AC3,BC_MC,ATIM] */

#define WLAN_E_ACTION_FRAME_RX          75	/* Received action frame event WITH
                                             * wl_event_rx_frame_data_t header
                                             */
#define WLAN_E_WAKE_EVENT               76	/* Wake Event timer fired, used for wake WLAN test mode */
#define WLAN_E_RM_COMPLETE              77	/* Radio measurement complete */
#define WLAN_E_HTSFSYNC                 78	/* Synchronize TSF with the host */
#define WLAN_E_OVERLAY_REQ              79	/* request an overlay IOCTL/iovar from the host */
#define WLAN_E_CSA_COMPLETE_IND         80
#define WLAN_E_EXCESS_PM_WAKE_EVENT     81	/* excess PM Wake Event to inform host  */
#define WLAN_E_PFN_SCAN_NONE            82	/* no PFN networks around */
#define WLAN_E_PFN_SCAN_ALLGONE         83	/* last found PFN network gets lost */
#define WLAN_E_LAST                     84	/* highest val + 1 for range checking */
#endif

typedef int WLAN_EVET_MSQ;

/* Supported join modes. */
/* Values are used to select the mode used to join a network. */
enum {
	WLAN_MODE_IBSS = 0,   /* IBSS Mode. (Adhoc) */
	WLAN_MODE_BSS = 1,    /* BSS Mode. */
	WLAN_MODE_AUTO = 2    /* Auto. */
};
typedef int WLAN_JOIN_MODE;

typedef struct _WLAN_SSID
{
    /* SSID Length */
    uint32   SsidLength;

    /* SSID information field */
    uint8   Ssid[32];
}WLAN_SSID;

/** WEP_KEY */
typedef struct _WLAN_WEP_KEY
{
    uint32 KeyLength;		//length in bytes
    uint8 KeyMaterial[16];	//hexadecimal
    
} WLAN_WEP_KEY;

typedef struct _WLAN_CONFIG_INFO
{
    WLAN_JOIN_MODE  InfrastructureMode;
    WLAN_SSID		Ssid;
    uint8 		    InfraBssid[6];

    // Security settings
    WLAN_AUTH_MODE  Auth_Mode;
    WLAN_ENCRYPTION Enc_Mode;
    WLAN_WEP_KEY    Wep_Key[4];
    uint8           WepKeyToUse;		//Specifies the WEP key index(0:key 1, 1:key 2, 2:key 3, 3:key 4).
    uint8           PresharedKey[64];	//Preshared key for WPA-PSK or WPA2-PSK
    uint32          Psk_length;

} WLAN_CONFIG_INFO;


typedef struct _WLAN_WPS_CONFIG
{	
	uint32	WscMode;		// predefined WSC mode, 1: PIN, 2: PBC
	uint8	PIN[8];			// 8 bytes PIN nunmber
	uint8 	Bssid[6];
    uint8	JoinAP;			//1: to join AP after WPS success, 0: Not to join AP after WPS success
	uint32	ScanBufSize;	//WPS scan buffer size, max 32KB
	uint32	AssocAPTime;	//Time to associate target AP in mili-seconds, default is 20000 (20s)
} WLAN_WPS_CONFIG;

// For WSC state machine states.
// We simplified it
typedef	enum _WLAN_WPS_STATE
{
    WLAN_WPS_STATE_OFF,//0
    WLAN_WPS_STATE_INIT,		
    WLAN_WPS_STATE_START,
    WLAN_WPS_STATE_CONN_FAIL,
    WLAN_WPS_STATE_FAIL,//4
    
    WLAN_WPS_STATE_LINK_UP,//5
    WLAN_WPS_STATE_WAIT_START,
    WLAN_WPS_STATE_WAIT_M2,
    WLAN_WPS_STATE_RX_M2D,	
    WLAN_WPS_STATE_WAIT_M4,//9
    
    WLAN_WPS_STATE_WAIT_M6,//10
    WLAN_WPS_STATE_WAIT_M8,
    WLAN_WPS_STATE_WAIT_EAPFAIL,
    WLAN_WPS_STATE_WAIT_DISCONN,
    WLAN_WPS_STATE_CONFIGURED//14
}WLAN_WPS_STATE;

typedef enum {
	WLAN_MODE_B = 0,  
	WLAN_MODE_G = 1, 
	WLAN_MODE_N = 2 
}WLAN_11MODE;

// Wsc status code
#define	WLAN_WSC_STATUS_NOTUSED						0x0000
#define	WLAN_WSC_STATUS_IDLE						0x0001
#define	WLAN_WSC_STATUS_START_ASSOC					0x0002		// Begin associating to WPS AP
#define	WLAN_WSC_STATUS_LINK_UP						0x0003		// Associated to WPS AP
#define	WLAN_WSC_STATUS_EAPOL_START_SENT			0x0004		// Sending EAPOL-Start
#define	WLAN_WSC_STATUS_EAP_REQ_ID_SENT				0x0005		// Sending EAP-Rsp(ID)
#define	WLAN_WSC_STATUS_EAP_REQ_WSC_START			0x0006		// Receive EAPReq WPS_Start
#define	WLAN_WSC_STATUS_EAP_M1_SENT					0x0007		// Sending M1
#define	WLAN_WSC_STATUS_EAP_M2_RECEIVED				0x0008		// Received M2
#define	WLAN_WSC_STATUS_EAP_M2D_RECEIVED			0x0009		// Received M2D
#define	WLAN_WSC_STATUS_EAP_RSP_ACK_SENT			0x000A		// Sending EAP Response (ACK)
#define	WLAN_WSC_STATUS_EAP_M3_SENT					0x000B		// Sending M3
#define	WLAN_WSC_STATUS_EAP_M4_RECEIVED				0x000C		// Received M4
#define	WLAN_WSC_STATUS_EAP_M5_SENT					0x000D		// Sending M5
#define	WLAN_WSC_STATUS_EAP_M6_RECEIVED				0x000E		// Received M6
#define	WLAN_WSC_STATUS_EAP_M7_SENT					0x000F		// Sending M7
#define	WLAN_WSC_STATUS_EAP_M8_RECEIVED				0x0010		// Received M8
#define	WLAN_WSC_STATUS_EAP_RSP_DONE_SENT			0x0011		// Sending EAP Response (Done)
#define	WLAN_WSC_STATUS_EAP_CONFIGURED				0x0012		// Configured
#define	WLAN_WSC_STATUS_SCAN_AP						0x0013		// Scanning AP
#define WLAN_WSC_STATUS_PIN_SEACH_MATCH_AP			0x0014		// search AP
#define WLAN_WSC_STATUS_PBC_TIMEOUT					0x0015		// PBC time out
#define	WLAN_WSC_STATUS_START_REASSOC				0x0016		// Begin associating to WPS AP
#define WLAN_WSC_STATUS_EAP_RSP_NACK_SENT			0x0017		// Sending EAP Response (NACK)

// All error message dtarting from 0x0100
#define	WLAN_WSC_STATUS_PBC_TOO_MANY_AP				0x0101		// Too many PBC AP avaliable
#define	WLAN_WSC_STATUS_PBC_NO_AP					0x0102		// No PBC AP avaliable
#define	WLAN_WSC_STATUS_EAP_FAIL_RECEIVED			0x0103		// Received EAP-FAIL
#define	WLAN_WSC_STATUS_EAP_NONCE_MISMATCH			0x0104		// Receive EAP with wrong NONCE
#define	WLAN_WSC_STATUS_EAP_INVALID_DATA			0x0105		// Receive EAP without integrity (Hmac mismatch)
#define WLAN_WSC_STATUS_PASSWORD_MISMATCH			0x0106		// Error PIN Code (R-Hash mismatch)
#define	WLAN_WSC_STATUS_EAP_REQ_WRONG_SMI			0x0107		// Receive EAP-Req with wrong WPS SMI Vendor Id
#define	WLAN_WSC_STATUS_EAP_REQ_WRONG_VENDOR_TYPE	0x0108		// Receive EAPReq with wrong WPS Vendor Type

// Error message, UI stop querying
//#define	STATUS_WSC_INVALID_SSID					0x0201		// Invalid SSID/BSSID in PIN mode				//TODO: not used
//#define	STATUS_WSC_EAP_REQ_WRONG_SMI			0x0202		// Receive EAP-Req with wrong WPS SMI Vendor Id	//TODO: move to 0x01ff
//#define	STATUS_WSC_EAP_REQ_WRONG_VENDOR_TYPE	0x0203		// Receive EAPReq with wrong WPS Vendor Type	//TODO: move to 0x01ff
#define	WLAN_WSC_STATUS_WSC_EAP_FAILED				0x0204		// WPS EAP process failed

typedef struct _WLAN_CONNECTION_INFO
{
	uint8	Ssid_len;
	uint8	Ssid[32];
	int32	Rssi;
	int32	Phy_rate;
    int32 	channel;
} WLAN_CONNECTION_INFO;


typedef struct _WLAN_ETHER_ADDR
{
	uint8 mac[6];
	
}WLAN_ETHER_ADDR;

/* For ioctls that take a list of MAC addresses */
typedef struct _WLAN_MACLIST
{
	uint32 count;         /* number of MAC addresses */
	WLAN_ETHER_ADDR ea[1];    /* variable length array of MAC addresses */
}WLAN_MACLIST;

typedef struct _WLAN_TARGET_AP_INFO
{
    int8 ssid[WLAN_NAME_LENGTH];
    WLAN_AUTH_MODE authMode;
    WLAN_ENCRYPTION encryption;
    int8 key[WLAN_NAME_LENGTH];
}WLAN_TARGET_AP_INFO;

typedef struct _WLAN_DONGLE_STATS
{
	unsigned long rx_packets;		/* total packets received */
	unsigned long tx_packets;		/* total packets transmitted */
	unsigned long rx_bytes;		/* total bytes received */
	unsigned long tx_bytes;		/* total bytes transmitted */
	unsigned long rx_errors;		/* bad packets received */
	unsigned long tx_errors;		/* packet transmit problems */
	unsigned long rx_dropped;		/* packets dropped by dongle */
	unsigned long tx_dropped;		/* packets dropped by dongle */
	unsigned long multicast;      /* multicast packets received */

}WLAN_DONGLE_STATS;

typedef struct _WLAN_STATISTICS_INFO
{
	/* Stats for dongle-based data */
	//----------------------------------------------------------------------
	WLAN_DONGLE_STATS dstats;

	/* Additional stats for the bus level */
	//----------------------------------------------------------------------
	unsigned long tx_packets;	/* Data packets sent to dongle */
	unsigned long tx_multicast;	/* Multicast data packets sent to dongle */
	unsigned long tx_errors;	/* Errors in sending data to dongle */
	unsigned long tx_ctlpkts;	/* Control packets sent to dongle */
	unsigned long tx_ctlerrs;	/* Errors sending control frames to dongle */
	unsigned long rx_packets;	/* Packets sent up the network interface */
	unsigned long rx_multicast;	/* Multicast packets sent up the network interface */
	unsigned long rx_errors;	/* Errors processing rx data packets */
	unsigned long rx_ctlpkts;	/* Control frames processed from dongle */
	unsigned long rx_ctlerrs;	/* Errors in processing rx control frames */
	unsigned long rx_dropped;	/* Packets dropped locally (no memory) */
	unsigned long rx_flushed;  /* Packets flushed due to unscheduled sendup thread */
	unsigned long wd_dpc_sched;   /* Number of times dhd dpc scheduled by watchdog timer */

	unsigned long rx_readahead_cnt;	/* Number of packets where header read-ahead was used. */
	unsigned long tx_realloc;	/* Number of tx packets we had to realloc for headroom */
	unsigned long fc_packets;       /* Number of flow control pkts recvd */
}WLAN_STATISTICS_INFO;

typedef enum _PARAM_TYPE
{
	PARAM_TYPE_MAX_CLIENT_NUMBER	
} PARAM_TYPE;

/**************** SYS ********************/
void WLAN_SYS_StatusCallback(wlan_event_msg_t* event);
int8* WLAN_SYS_GetVersion(void);
WLAN_DRV_HDL WLAN_SYS_Start(void);
void WLAN_SYS_Stop(WLAN_DRV_HDL hdl);
int32 WLAN_SYS_GetMode(void);
void WLAN_SYS_GetMacAddr(uint8* addr);
void WLAN_SYS_GetMacAddrStr(int8* addrStr);
struct pbuf;
void WLAN_SYS_TxPkt(struct pbuf *p);
int32 WLAN_SYS_GetTXQueueAvailCount(void);
void WLAN_SYS_GetStatsInfo(WLAN_STATISTICS_INFO *stats, char *sdio_stat_buf, int sdio_stat_len);
void WLAN_SYS_InitHw(void);
void WLAN_SYS_ResetHw(void);
bool WLAN_SYS_IsStart(void);
/**************** STA ********************/
int32 WLAN_STA_AllocateScanBuf(void);
void WLAN_STA_FreeScanBuf(void);
int8* WLAN_STA_ScanBufAddr(void);
int8* WLAN_STA_ScanAPbyModule(uint32* uiCount);
int8* WLAN_STA_GetScanResultByIndex(uint32 uiIndex, int8* pchBuf);
int32 WLAN_STA_ScanAP(int8* scan_buf, uint32 buf_size);
int32 WLAN_STA_PutScanInfo(int8* scan_buf, uint32 buf_size);
int32 WLAN_STA_OpenScanInfo(uint32* puiFileHandler);
void WLAN_STA_CloseScanInfo(void);
int32 WLAN_STA_ScanAPbySSID(int8* pchSSID, WLAN_BSS_INFO *psInfo);
void WLAN_STA_ScanChannel(uint32* puiChannelList);
void WLAN_STA_AutoSelectChannel(uint32* puiChannel);
void WLAN_STA_AutoSelectChannel_PanaRule(uint32* puiChannel);
int32 WLAN_STA_SetTargetAP(int8 *ssid, WLAN_AUTH_MODE authMode, WLAN_ENCRYPTION encryption, const int8 *key);
int32 WLAN_STA_ConnectTargetAP(void);
int32 WLAN_STA_JoinAP(int8 *ssid, WLAN_AUTH_MODE authMode, WLAN_ENCRYPTION encryption, const int8 *key );
int32 WLAN_STA_GetConnectedINFO(WLAN_CONNECTION_INFO* info);

/**************** AP ********************/
int32 WLAN_AP_Create(int8* ssid,
                     WLAN_AUTH_MODE authMode, 
                     WLAN_ENCRYPTION encryption, 
                     const int8 *key,
                     WLAN_CHANNEL channel, 
                     bool bHideSSID);
int32 WLAN_AP_GetAssocList(int8* pchBuf, uint32 uiBufSize);
int WiFiAPConnectionLimit(void);

/**************** WPS ********************/
void WLAN_WPS_CallBack(WLAN_WPS_STATE event);
int32 WLAN_WPS_Start(WLAN_WPS_CONFIG* wps_config_info, void* pFunc);
void WLAN_WPS_Stop(void);
int32 WLAN_WPS_GenPin(uint32* uiPin);
bool WLAN_WPS_Enable(void);
WLAN_WPS_STATE WLAN_WPS_GetState(void);
uint32 WLAN_WPS_GetStatus(void);
int32 WLAN_WPS_GetCredential(WLAN_CONFIG_INFO *wlan_config_info);

/**************** MFG ********************/
int32 WLAN_MFG_TxBG(WLAN_CHANNEL channel, WLAN_RATE rate, int32 powerValue);
int32 WLAN_MFG_TxN(WLAN_CHANNEL channel, WLAN_MCS_RATE rate, int32 powerValue);
int32 WLAN_MFG_ContinousTx(WLAN_CHANNEL channel, uint32 rate, int32 powerValue);
int32 WLAN_MFG_RegisterRxCallback(void (*pCallback)(wndrv_test_rx_status_struct *));
int32 WLAN_MFG_RX(WLAN_CHANNEL channel);
int32 WLAN_MFG_RxGetPkt(uint32* uiCount);
int32 WLAN_MFG_CarrierTone(WLAN_CHANNEL channel);
int32 WLAN_MFG_Stop(void);
#endif
