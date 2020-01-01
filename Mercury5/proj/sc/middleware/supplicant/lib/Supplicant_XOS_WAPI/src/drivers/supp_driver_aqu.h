/*****************************************************************************
 *
 *  Copyright (c) 2008-2009 MStar Semiconductor, Inc.  All rights reserved.
 *  4F-1, No. 26, Tai-Yuan St., ChuPei, Hsinchu Hsien, Taiwan 302, R.O.C.
 *
 *  THE DELIVERY OF THIS SOFTWARE AS WELL AS THE HEREBY GRANTED
 *  NON-EXCLUSIVE, WORLDWIDE LICENSE TO USE, COPY, MODIFY, DISTRIBUTE
 *  AND SUBLICENSE THIS SOFTWARE IS FREE OF CHARGE.
 *
 *  THE LICENSED SOFTWARE IS PROVIDED "AS IS" AND MSTAR EXPRESSLY
 *  DISCLAIMS ALL REPRESENTATIONS AND WARRANTIES, WHETHER EXPRESS OR
 *  IMPLIED, INCLUDING WITHOUT LIMITATION, WARRANTIES OR REPRESENTATIONS
 *  OF WORKMANSHIP, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 *  DURABILITY, THAT THE OPERATING OF THE LICENSED SOFTWARE WILL BE ERROR
 *  FREE OR FREE OF NY THIRD PARTY CALIMS, INCLUDING WITHOUT LIMITATION
 *  CLAIMS OF THIRD PARTY INTELLECTUAL PROPERTY INFRINGEMENT.
 *
 *  EXCEPT FOR ANY LIABILITY DUE TO WILFUL ACTS OR GROSS NEGLIGENCE AND
 *  EXCEPT FOR ANY PERSONAL INJURY MSTAR SHALL IN NO EVENT BE LIABLE
 *  FOR ANY CLAIM OR DAMAGES OF ANY KIND, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  --------------------------------------------------------------------------
 *
 *      Project : Kona
 *      Module  : Aquarius NDIS interface
 *      Abstract: Header file define for NDIS interface
 *
 *  History:
 *      By            Date      Ver. Description
 *      ------------- --------  ---- -----------------------------------------
 *      Peter Lin     20090727  1.0  initial version
 *
 *****************************************************************************/
//**********************************************************************************
//                Constant
//**********************************************************************************
#define NDIS_MSG_COMPLETE       0x10
#define NDIS_DATA               0x01
#define NDIS_GET_OID            0x04
#define NDIS_SET_OID            0x05
#define NDIS_RESET              0x06
#define NDIS_INDICATION         0x07
#define NDIS_NOTIFICATION       0x08
#define NDIS_GET_OID_COMP       (NDIS_GET_OID | NDIS_MSG_COMPLETE)
#define NDIS_SET_OID_COMP       (NDIS_SET_OID | NDIS_MSG_COMPLETE)
#define NDIS_RESET_COMP         (NDIS_MSG_RESET | NDIS_MSG_COMPLETE)

#define RNDIS_STATUS_MEDIA_CONNECT              	0x4001000b
#define RNDIS_STATUS_MEDIA_DISCONNECT           	0x4001000c
#define RNDIS_STATUS_MEDIA_SPECIFIC_INDICATION  	0x40010012

enum {
    NDIS_REQ_SUCCESS,
    NDIS_REQ_FAIL,
    NDIS_REQ_TIMEOUT,
    NDIS_BUF_INSUFFICIENT,
};
typedef enum WIFI_DRV_INIT_STATUS {
	WIFI_DRV_INIT_START = 1,
	WIFI_DRV_INIT_SUCCESS, 
	WIFI_DRV_INIT_FAIL,
} WIFI_DRV_INIT_STATUS;
//**********************************************************************************
//                Structure Define
//**********************************************************************************
struct msg_hdr {
    u8  type;                       // specific NDIS message type
    u8  req_id;                     // each NDIS message is specified with differn req_id for debug
    u16 len;                        // the total length of message, including the message header itself
}__attribute__((packed));

struct ndis_data{
    struct msg_hdr hdr;
    u8  data[1];
};
struct ndis_get_oid {
    struct msg_hdr hdr;
    u32 oid;
    u8  info[1];
};
struct ndis_get_oid_comp {
    struct msg_hdr hdr;
    u32 status;
    u8  info[1];
};
struct ndis_set_oid {
    struct msg_hdr hdr;
    u32 oid;
    u8  info[1];
};
struct ndis_set_oid_comp {
    struct msg_hdr hdr;
    u32 status;
};
struct ndis_indicate {
    struct msg_hdr hdr;
    u32 type;
    u8 info[0];
};
struct ndis_notify {
    struct msg_hdr hdr;
    u32 type;
    u32 value;
};

#include "mdl_bind_wlan.h"
//struct sk_buff
//{
//    struct net_device   *dev;
//    unsigned char   *head;
//    unsigned char   *data;
//    unsigned char   *tail;
//    unsigned char   *end;
//    unsigned int    len;
//    unsigned char   pkt_type;
//    unsigned char   ip_summed;
//    unsigned short  protocol;
//    unsigned int    priority;
//    unsigned char   padload[0];
//};

//**********************************************************************************
//                Macro Define
//**********************************************************************************
//**********************************************************************************
//                Extern Function
//**********************************************************************************
extern unsigned char *skb_put(struct sk_buff *skb, int len);
extern void supp_skb_reserve(struct sk_buff *skb, int len);
extern struct sk_buff *alloc_skb(unsigned int len, int priority);
extern void wifi_send_oid(struct sk_buff *skb);
extern void dev_kfree_skb(struct sk_buff *skb);
extern unsigned int wpa_drv_set_notify(struct wpa_driver_ndis_data *drv, u32 notify, u32 value);
extern void wpa_driver_ndis_restart(struct wpa_driver_ndis_data *drv);
//**********************************************************************************
//                NDIS Define
//**********************************************************************************
#define RNDIS_STATUS_SUCCESS                    0x00000000
#define RNDIS_STATUS_FAILURE                    0xc0000001
#define RNDIS_STATUS_TIMEOUT                    0xc0000002
#define RNDIS_STATUS_WAIT                       0xc0000003
#define RNDIS_STATUS_NOT_ACCEPTED               0x00010003
#define RNDIS_STATUS_INVALID_DATA               0xc0010015
#define RNDIS_STATUS_ADAPTER_NOT_READY          0xc0010011
#define RNDIS_STATUS_NOT_SUPPORTED              0xc00000bb
#define RNDIS_STATUS_MEDIA_CONNECT              0x4001000b
#define RNDIS_STATUS_MEDIA_DISCONNECT           0x4001000c
#define RNDIS_STATUS_MEDIA_SPECIFIC_INDICATION  0x40010012
#define RNDIS_VENDOR_PKT_TST_DONE               0x40010013
#define RNDIS_STATUS_CUSTOM_SCAN_DONE           0x40010014
#define RNDIS_STATUS_CUSTOM_SHARED_KEY_FAIL	    0x40010015
#define RNDIS_STATUS_CUSTOM_MSG	    			0x40010016
#define RNDIS_STATUS_SOCKET_STATUS	    		0x40010017
#define RNDIS_STATUS_AQU_RESET                  0x40010018

static const u8 pae_group_addr[ETH_ALEN] =
{ 0x01, 0x80, 0xc2, 0x00, 0x00, 0x03 };
#define NDIS_OID_ACT_SET				1
#define NDIS_OID_ACT_GET				2

#define OID_802_3_PERMANENT_ADDRESS     0x01010101
#define OID_802_3_CURRENT_ADDRESS       0x01010102
#define OID_802_3_MULTICAST_LIST        0x01010103

/* FIX: to be removed once this can be compiled with the complete NDIS
 * header files */
#ifndef OID_802_11_BSSID
#define OID_802_11_BSSID 			0x0d010101
#define OID_802_11_SSID 			0x0d010102
#define OID_802_11_INFRASTRUCTURE_MODE		0x0d010108
#define OID_802_11_ADD_WEP					0x0D010113
#define OID_802_11_REMOVE_WEP				0x0D010114
#define OID_802_11_DISASSOCIATE				0x0D010115
#define OID_802_11_BSSID_LIST 				0x0d010217
#define OID_802_11_AUTHENTICATION_MODE		0x0d010118
#define OID_802_11_PRIVACY_FILTER			0x0d010119
#define OID_802_11_BSSID_LIST_SCAN 			0x0d01011A
#define OID_802_11_WEP_STATUS	 			0x0d01011B
#define OID_802_11_ENCRYPTION_STATUS OID_802_11_WEP_STATUS
#define OID_802_11_ADD_KEY 					0x0d01011D
#define OID_802_11_REMOVE_KEY 				0x0d01011E
#define OID_802_11_ASSOCIATION_INFORMATION	0x0d01011F
#define OID_802_11_TEST 					0x0d010120
#define OID_802_11_CAPABILITY 				0x0d010122
#define OID_802_11_PMKID 					0x0d010123
#define OID_802_11_POWER_MODE               0x0d010216

#define NDIS_802_11_LENGTH_SSID 32
#define NDIS_802_11_LENGTH_RATES 8
#define NDIS_802_11_LENGTH_RATES_EX 16

typedef UCHAR NDIS_802_11_MAC_ADDRESS[6];

typedef struct NDIS_802_11_SSID {
	ULONG SsidLength;
	UCHAR Ssid[NDIS_802_11_LENGTH_SSID];
} NDIS_802_11_SSID;

typedef LONG NDIS_802_11_RSSI;

typedef enum NDIS_802_11_NETWORK_TYPE {
	Ndis802_11FH,
	Ndis802_11DS,
	Ndis802_11OFDM5,
	Ndis802_11OFDM24,
	Ndis802_11NetworkTypeMax
} NDIS_802_11_NETWORK_TYPE;

typedef struct NDIS_802_11_CONFIGURATION_FH {
	ULONG Length;
	ULONG HopPattern;
	ULONG HopSet;
	ULONG DwellTime;
} NDIS_802_11_CONFIGURATION_FH;

typedef struct NDIS_802_11_CONFIGURATION {
	ULONG Length;
	ULONG BeaconPeriod;
	ULONG ATIMWindow;
	ULONG DSConfig;
	NDIS_802_11_CONFIGURATION_FH FHConfig;
} NDIS_802_11_CONFIGURATION;

typedef enum NDIS_802_11_NETWORK_INFRASTRUCTURE {
	Ndis802_11IBSS,
	Ndis802_11Infrastructure,
	Ndis802_11AutoUnknown,
	Ndis802_11InfrastructureMax
} NDIS_802_11_NETWORK_INFRASTRUCTURE;

typedef enum NDIS_802_11_AUTHENTICATION_MODE {
	Ndis802_11AuthModeOpen,
	Ndis802_11AuthModeShared,
	Ndis802_11AuthModeAutoSwitch,
	Ndis802_11AuthModeWPA,
	Ndis802_11AuthModeWPAPSK,
	Ndis802_11AuthModeWPANone,
	Ndis802_11AuthModeWPA2,
	Ndis802_11AuthModeWPA2PSK,
	Ndis802_11AuthModeMax
} NDIS_802_11_AUTHENTICATION_MODE;

typedef enum NDIS_802_11_WEP_STATUS {
	Ndis802_11WEPEnabled,
	Ndis802_11Encryption1Enabled = Ndis802_11WEPEnabled,
	Ndis802_11WEPDisabled,
	Ndis802_11EncryptionDisabled = Ndis802_11WEPDisabled,
	Ndis802_11WEPKeyAbsent,
	Ndis802_11Encryption1KeyAbsent = Ndis802_11WEPKeyAbsent,
	Ndis802_11WEPNotSupported,
	Ndis802_11EncryptionNotSupported = Ndis802_11WEPNotSupported,
	Ndis802_11Encryption2Enabled,
	Ndis802_11Encryption2KeyAbsent,
	Ndis802_11Encryption3Enabled,
	Ndis802_11Encryption3KeyAbsent
} NDIS_802_11_WEP_STATUS, NDIS_802_11_ENCRYPTION_STATUS;

typedef enum NDIS_802_11_PRIVACY_FILTER {
	Ndis802_11PrivFilterAcceptAll,
	Ndis802_11PrivFilter8021xWEP
} NDIS_802_11_PRIVACY_FILTER;

typedef UCHAR NDIS_802_11_RATES[NDIS_802_11_LENGTH_RATES];
typedef UCHAR NDIS_802_11_RATES_EX[NDIS_802_11_LENGTH_RATES_EX];

typedef struct NDIS_WLAN_BSSID_EX {
	ULONG Length;
	NDIS_802_11_MAC_ADDRESS MacAddress; /* BSSID */
	UCHAR Reserved[2];
	NDIS_802_11_SSID Ssid;
	ULONG Privacy;
	NDIS_802_11_RSSI Rssi;
	NDIS_802_11_NETWORK_TYPE NetworkTypeInUse;
	NDIS_802_11_CONFIGURATION Configuration;
	NDIS_802_11_NETWORK_INFRASTRUCTURE InfrastructureMode;
	NDIS_802_11_RATES_EX SupportedRates;
	ULONG IELength;
	UCHAR IEs[0];
} NDIS_WLAN_BSSID_EX;

typedef struct NDIS_802_11_BSSID_LIST_EX {
	ULONG NumberOfItems;
	NDIS_WLAN_BSSID_EX Bssid[1];
} NDIS_802_11_BSSID_LIST_EX;

typedef struct NDIS_802_11_FIXED_IEs {
	UCHAR Timestamp[8];
	USHORT BeaconInterval;
	USHORT Capabilities;
} NDIS_802_11_FIXED_IEs;

typedef struct NDIS_802_11_WEP {
	ULONG Length;
	ULONG KeyIndex;
	ULONG KeyLength;
	UCHAR KeyMaterial[1];
} NDIS_802_11_WEP;

typedef ULONG NDIS_802_11_KEY_INDEX;
typedef ULONGLONG NDIS_802_11_KEY_RSC;

typedef struct NDIS_802_11_KEY {
	ULONG Length;
	ULONG KeyIndex;
	ULONG KeyLength;
	NDIS_802_11_MAC_ADDRESS BSSID;
	NDIS_802_11_KEY_RSC KeyRSC;
	UCHAR KeyMaterial[0];
} NDIS_802_11_KEY;

typedef struct NDIS_802_11_REMOVE_KEY {
	ULONG Length;
	ULONG KeyIndex;
	NDIS_802_11_MAC_ADDRESS BSSID;
} NDIS_802_11_REMOVE_KEY;

typedef struct NDIS_802_11_AI_REQFI {
	USHORT Capabilities;
	USHORT ListenInterval;
	NDIS_802_11_MAC_ADDRESS CurrentAPAddress;
#ifdef BIND_TI_WIFI
	USHORT  reserved;
#endif
} NDIS_802_11_AI_REQFI;

typedef struct NDIS_802_11_AI_RESFI {
	USHORT Capabilities;
	USHORT StatusCode;
	USHORT AssociationId;
#ifdef BIND_TI_WIFI
	USHORT  reserved;
#endif
} NDIS_802_11_AI_RESFI;

typedef struct NDIS_802_11_ASSOCIATION_INFORMATION {
	ULONG Length;
	USHORT AvailableRequestFixedIEs;
	NDIS_802_11_AI_REQFI RequestFixedIEs;
	ULONG RequestIELength;
	ULONG OffsetRequestIEs;
	USHORT AvailableResponseFixedIEs;
	NDIS_802_11_AI_RESFI ResponseFixedIEs;
	ULONG ResponseIELength;
	ULONG OffsetResponseIEs;
} NDIS_802_11_ASSOCIATION_INFORMATION;

typedef struct NDIS_802_11_AUTHENTICATION_ENCRYPTION {
	NDIS_802_11_AUTHENTICATION_MODE AuthModeSupported;
	NDIS_802_11_ENCRYPTION_STATUS EncryptStatusSupported;
} NDIS_802_11_AUTHENTICATION_ENCRYPTION;

typedef struct NDIS_802_11_CAPABILITY {
	ULONG Length;
	ULONG Version;
	ULONG NoOfPMKIDs;
	ULONG NoOfAuthEncryptPairsSupported;
	NDIS_802_11_AUTHENTICATION_ENCRYPTION
		AuthenticationEncryptionSupported[1];
} NDIS_802_11_CAPABILITY;

typedef UCHAR NDIS_802_11_PMKID_VALUE[16];

typedef struct BSSID_INFO {
	NDIS_802_11_MAC_ADDRESS BSSID;
	NDIS_802_11_PMKID_VALUE PMKID;
} BSSID_INFO;

typedef struct NDIS_802_11_PMKID {
	ULONG Length;
	ULONG BSSIDInfoCount;
	BSSID_INFO BSSIDInfo[1];
} NDIS_802_11_PMKID;

typedef enum NDIS_802_11_STATUS_TYPE {
	Ndis802_11StatusType_Authentication,
	Ndis802_11StatusType_PMKID_CandidateList = 2,
	Ndis802_11StatusTypeMax
} NDIS_802_11_STATUS_TYPE;

typedef struct NDIS_802_11_STATUS_INDICATION {
	NDIS_802_11_STATUS_TYPE StatusType;
} NDIS_802_11_STATUS_INDICATION;

typedef struct PMKID_CANDIDATE {
	NDIS_802_11_MAC_ADDRESS BSSID;
	ULONG Flags;
} PMKID_CANDIDATE;

#define NDIS_802_11_PMKID_CANDIDATE_PREAUTH_ENABLED 0x01

typedef struct NDIS_802_11_PMKID_CANDIDATE_LIST {
	ULONG Version;
	ULONG NumCandidates;
	PMKID_CANDIDATE CandidateList[1];
} NDIS_802_11_PMKID_CANDIDATE_LIST;

typedef struct NDIS_802_11_AUTHENTICATION_REQUEST {
	ULONG Length;
	NDIS_802_11_MAC_ADDRESS Bssid;
	ULONG Flags;
} NDIS_802_11_AUTHENTICATION_REQUEST;

typedef enum _NDIS_802_11_POWER_MODE
{
    Ndis802_11PowerModeCAM,
    Ndis802_11PowerModePSP,
    Ndis802_11PowerModeMax      // not a real mode, defined as an upper bound
} NDIS_802_11_POWER_MODE, *PNDIS_802_11_POWER_MODE;

#define NDIS_802_11_AUTH_REQUEST_REAUTH			0x01
#define NDIS_802_11_AUTH_REQUEST_KEYUPDATE		0x02
#define NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR		0x06
#define NDIS_802_11_AUTH_REQUEST_GROUP_ERROR		0x0E

/*
 * Private parameters definition
 */
#define OID_802_11_PKT_TEST					0x0D018000
#define OID_802_11_RXFILTER					0x0D018001
#define OID_802_11_AQU_FW_VER				0x0D018002
#define OID_802_11_RF_REGWRITE				0x0D018003
#define OID_802_11_TX_SINTONE				0x0D018004
#define OID_802_11_MEM_WRITE   			    0x0d018005
#define OID_802_11_MEM_READ   			    0x0d018006
#define OID_802_11_RF_REGREAD				0x0D018007
#define OID_802_11_BT_STATUS                0x0D01a010
#define OID_802_11_GSM_STATUS				0x0D01A011
#define OID_MSTAR_HOST_PLATFORM             0x0D01A020
#define OID_802_11_SOCKET_STATUS			0x0D01A021
#define OID_802_11_WPA_KEY_STATUS			0x0D01A022
#define OID_802_11_ANTENNA_SWITCH_STATUS	0x0D01A023
#define OID_802_11_SUPPORT_CHAN             0x0D01A024
#define OID_802_11_PGA_STATUS				0x0D01A025
#define OID_802_11_IGNORE_BSSID_STATUS      0x0d01a026
#define OID_802_11_CHAN13_SPUR_SETTING      0x0d01a027

typedef enum {
    NO_IGNORE_BSSID_DEFAULT                     = 0,  //0 : default no ignore bssid
    IGNORE_BSSID                                = 1,  //1 : ignore bssid
} bss_filter_ctrl;

typedef enum {
    MSTAR_HOST_NONE,
    MSTAR_HOST_WINXP,
    MSTAR_HOST_BIG2_ARM9_RTK,
    MSTAR_HOST_U4_MIPS34K_LINUX,
} mstar_host_types;

typedef enum {
	BT_ENABLED,
	BT_DISABLED,
	SCO_CREATED,
	A2DP_CREATED,
	SCO_DESTORYED,
	A2DP_DESTORYED,
	SEARCH_START,
	SEARCH_STOP,
} bt_states;

struct bt_state {
	bt_states 	bt_state;			// Bluetooth state
} STRUCT_PACKED;

struct aqu_param {
	unsigned int 	oid;
	unsigned int 	data_len;
	unsigned char   *data;
};
#endif /* OID_802_11_BSSID */

#ifndef OID_802_11_PMKID
/* Platform SDK for XP did not include WPA2, so add needed definitions */

#define OID_802_11_CAPABILITY 			0x0d010122
#define OID_802_11_PMKID 			0x0d010123

#define Ndis802_11AuthModeWPA2 6
#define Ndis802_11AuthModeWPA2PSK 7

#define Ndis802_11StatusType_PMKID_CandidateList 2

typedef struct NDIS_802_11_AUTHENTICATION_ENCRYPTION {
	NDIS_802_11_AUTHENTICATION_MODE AuthModeSupported;
	NDIS_802_11_ENCRYPTION_STATUS EncryptStatusSupported;
} NDIS_802_11_AUTHENTICATION_ENCRYPTION;

typedef struct NDIS_802_11_CAPABILITY {
	ULONG Length;
	ULONG Version;
	ULONG NoOfPMKIDs;
	ULONG NoOfAuthEncryptPairsSupported;
	NDIS_802_11_AUTHENTICATION_ENCRYPTION
		AuthenticationEncryptionSupported[1];
} NDIS_802_11_CAPABILITY;

typedef UCHAR NDIS_802_11_PMKID_VALUE[16];

typedef struct BSSID_INFO {
	NDIS_802_11_MAC_ADDRESS BSSID;
	NDIS_802_11_PMKID_VALUE PMKID;
} BSSID_INFO;

typedef struct NDIS_802_11_PMKID {
	ULONG Length;
	ULONG BSSIDInfoCount;
	BSSID_INFO BSSIDInfo[1];
} NDIS_802_11_PMKID;

typedef struct PMKID_CANDIDATE {
	NDIS_802_11_MAC_ADDRESS BSSID;
	ULONG Flags;
} PMKID_CANDIDATE;

#define NDIS_802_11_PMKID_CANDIDATE_PREAUTH_ENABLED 0x01

typedef struct NDIS_802_11_PMKID_CANDIDATE_LIST {
	ULONG Version;
	ULONG NumCandidates;
	PMKID_CANDIDATE CandidateList[1];
} NDIS_802_11_PMKID_CANDIDATE_LIST;

#endif /* OID_802_11_CAPABILITY */
