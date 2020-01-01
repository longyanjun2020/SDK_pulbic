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
 *      Module  : NDIS interface
 *      Abstract: Header file define for NDIS interface
 *
 *  History:
 *      By            Date      Ver. Description
 *      ------------- --------  ---- -----------------------------------------
 *      Peter Lin     20090727  1.0  initial version
 *
 *****************************************************************************/
#ifndef _WPA_CTRL_INF
#define _WPA_CTRL_INF
//**********************************************************************************
//                Constant Define
//**********************************************************************************
#define WPA_CMD_OPEN				0x00043001
#define WPA_CMD_STOP				0x00043002
#define WPA_CMD_SET_RESET			0x00043003
#define WPA_CMD_SET_SCAN			0x00043004
#define WPA_CMD_SET_CONNECT			0x00043005
#define WPA_CMD_SET_DISCONNECT		0x00043006
#define WPA_CMD_SET_CONFIGURATION	0x00043007
#define WPA_CMD_SET_POWER_SAVING	0x00043008
#define WPA_CMD_GET_SCAN_RESULTS	0x00043009
#define WPA_CMD_GET_CONFIGURATION	0x0004300A
#define WPA_CMD_GET_BSS				0x0004300B
#define WPA_CMD_STOP_SCAN 			0x0004300C
#define WPA_CMD_SET_BT_STATUS       0x0004300D
#define WPA_CMD_SET_FW_TEST			0x0004300E
#define WPA_CMD_GET_FW_TEST_RESULT  0x0004300F
#define WPA_CMD_SET_HW_REG			0x00043010
#define WPA_CMD_GET_HW_REG			0x00043011
#define WPA_CMD_SET_RXFILTER		0x00043012
#define WPA_CMD_GET_RXFILTER_RESULT	0x00043013
#define WPA_CMD_GET_AQU_FW_VER		0x00043014
#define WPA_CMD_SET_GSM_STATUS		0x00043015
#define WPA_CMD_SET_RF_REGISTER		0x00043016
#define WPA_CMD_GET_RF_REGISTER		0x00043017
#define WPA_CMD_SET_TX_SINTONE		0x00043018
#define WPA_CMD_SET_CONT_TX_STOP	0x00043019
#define WPA_CMD_SET_AQUA_MEM		0x0004301a
#define WPA_CMD_GET_AQUA_MEM		0x0004301b


#define WPA_EVENT_CONNECT_FAIL		0x00044001
#define WPA_EVENT_CONNECT_OK		0x00044002
#define WPA_EVENT_DISCONECTED		0x00044003
#define WPA_EVENT_ROMMING			0x00044004
#define WPA_EVENT_SCAN_DONE			0x00044005
#define WPA_EVENT_PASSWORD_FAIL		0x00044006
#define WPA_EVENT_FW_TEST_DONE		0x00044007
#define WPA_EVENT_CERT_FAIL                     0x00044008
#define WPA_EVENT_CERT_UNKNOWN_ISSUER           0x00044009
#define WPA_EVENT_CERT_UNTRUSTED_ROOT           0x0004400A
#define WPA_EVENT_CERT_INVALID_TIME             0x0004400B
#define WPA_EVENT_CERT_INVALID_SIGNATURE        0x0004400C
#define WPA_EVENT_CERT_REVOKED                  0x0004400D
#define WPA_EVENT_CERT_INVALID_USAGE            0x0004400E
#define WPA_EVENT_CERT_FAIL_UNKNOW              0x0004400F

#define WPA_MAX_CMD_REPLY			4096

#define WPA_CMD_OK					1
#define WPA_CMD_FAIL				2
#define WPA_CMD_DATA_INVALID		3
#define WPA_CMD_NON_SUPPORT			4

#define WPA_SECURITY_NONE  			0x00000001
#define WPA_SECURITY_WEP40   		0x00000002
#define WPA_SECURITY_WEP104			0x00000004
#define WPA_SECURITY_WPA   			0x00000008
#define WPA_SECURITY_WPA2  			0x00000010
#define WPA_SECURITY_WAPI_PSK       0x00000020
#define WPA_SECURITY_WPA_EAP        0x00000040
#define WPA_SECURITY_WPA2_EAP       0x00000080
#define WPA_SECURITY_WAPI_CERT      0x00000100

//Host notification
#define NOTIFY_TYPE_SOCKET_STATUS       0x00000001

//**********************************************************************************
//                Structure Define
//**********************************************************************************
struct cert_rai {
    u32 rid;
    u32 len;
};

struct wifi_ssid_conf {
    u8  ssid[32];           //SSID
    u32 ssid_len;           //SSID length, 0 => use any ssid
    /*
	 *	#define WPA_SECURITY_NONE  			0x00000001
	 *	#define WPA_SECURITY_WEP40   		0x00000002
	 *	#define WPA_SECURITY_WEP104			0x00000004
	 *	#define WPA_SECURITY_WPA   			0x00000008
	 *	#define WPA_SECURITY_WPA2  			0x00000010
     *  #define WPA_SECURITY_WAPI_PSK       0x00000020
     *  #define WPA_SECURITY_WPA_EAP        0x00000040
     *  #define WPA_SECURITY_WPA2_EAP       0x00000080
     *  #define WPA_SECURITY_WAPI_CERT      0x00000100
     */
    u32 security;           //NONE, WEP, WPA and WPA2
	u32 keyidx;             //key index 0~3
    u8  key[64];            //key context, WEP40 => 5, WEP104 =>13, WPA and RSN => 8~64
    #if 0
    u16 user_cert[FILEMGR_MAX_FILEPATH_SIZE]; //user cert
    u16 ca_cert[FILEMGR_MAX_FILEPATH_SIZE];   //ca cert
    #else
    u32 nCaRaiId;
    u32 nClientRaiId;
    u16 nCaRaiSize;
    u16 nClientRaiSize;
    #endif
    u8  bssid[6];           //BSSID
} STRUCT_PACKED;

struct wifi_scan_res {
    u8  ssid[32];           //SSID
    u32 ssid_len;           //SSID length, 0 => use any ssid
    /*
	 *	#define WPA_SECURITY_NONE  			0x00000001
	 *	#define WPA_SECURITY_WEP40   		0x00000002
	 *	#define WPA_SECURITY_WEP104			0x00000004
	 *	#define WPA_SECURITY_WPA   			0x00000008
	 *	#define WPA_SECURITY_WPA2  			0x00000010
    */
    u32 security;           //NONE, WEP, WPA and WPA2
    u32 channel;			//1~14
    // qual and noise are invalid in current implementation
	int qual;				//Quality
	int noise;				//Noise Level
	/*
	 * The received signal strength indication (RSSI), in dBm.
	 * Typical values range from -10 through -200 dBm.
	 */
	int level;				//Signal level
	/*
	 * #define IEEE80211_MODE_INFRA	0
     * #define IEEE80211_MODE_IBSS	1
	 */
	u32 mode;
	/*
	 * 11 for 11Mbps, 54 for 54 Mbps
	 */
	u32 speed;				//11Mbps for 11b and 54Mbps for 11g
	u8  bssid[6];           //BSSID
} STRUCT_PACKED;

struct wifi_scan {
	u32 num;
	struct wifi_scan_res scan_res[1];
};

struct wifi_conf {
	//wpa_states wpa_state;	// WPA state machine
	u8  own_addr[ETH_ALEN];	// Own MAC address
	u8  pad[2];				// for alignment issue
} STRUCT_PACKED;
struct wifi_fw_tst_conf {
	u32 tx_rate;			// Tx rate for test packet [ 0 ~ 15]
	u32 channel;			// Test channel number [1 ~ 11]
	u32 pkt_len;			// Test packet length  [40 ~ 1500]
	u32 pkt_num;			// Number of packet to send	[0 ~ ]
	s32 pga;				// pga [-1, 0 ~ 30]
	u32 option;				//
	u8  dest_mac[6];		// destination MAC address
	u8  src_mac[6];			// source MAC address
	u8  pad[2];
};
struct wifi_fw_tst_results {
	u32 total_pkt;			// the number that how many packets are sent
	u32 recv_pkt;			// the number that how many packets are received
	u32 fail_pkt;           // the number that how many packets are failed to be received
	u32 per;				// Packet error rate
	u32 oppo_pkt;			// the number that how many packets are received by the other site
};
struct wifi_fw_tst_results_aqu {
	u32 total_pkt;			// the number that how many packets are sent
	u32 recv_pkt;			// the number that how many packets are received
	u32 fail_pkt;           // the number that how many packets are failed to be received
	u32 per_int;			// Packet error rate
	u32 per_dec;			// Packet error rate
	u32 oppo_pkt;			// the number that how many packets are received by the other site
};
struct wifi_hw_reg {
	u8 bank;				// register bank
	u8 reg;					// register address
	//u8 byte;				// 0:LSB, 1:MSB
	u16 data;				// register value
} STRUCT_PACKED;
struct wifi_rx_filter {
	u32 rate;
	u32 len;
	u32 chan;
	u8  filtermac[6];
	u8  pad[2];
} STRUCT_PACKED;
struct wifi_rx_filter_result {
	u32 rx_pkt;
	u32 rx_fcsfitpkt;
	u32 rx_fcsfailpkt;
	u32 rx_avgagc;
	u32 rx_sdagc;
	u32 rx_agc_max;
	u32 rx_agc_min;
} STRUCT_PACKED;
struct wifi_rx_filter_result_aqu {
	u32 rx_pkt;
	u32 rx_fcsfitpkt;
	u32 rx_fcsfailpkt;
	u32 rx_avgagc_int;
	u32 rx_avgagc_dec;
	u32 rx_sdagc_int;
	u32 rx_sdagc_dec;
	u32 rx_agc_max;
	u32 rx_agc_min;
} STRUCT_PACKED;
struct wifi_fw_ver {
	u32 aqu_ver;
	u32 supplicant_ver;
} STRUCT_PACKED;

struct wifi_rf_reg {
	u8 reg;
	u8 val;
	u8 pad[2];
} STRUCT_PACKED;

struct wifi_mem {
	u32 addr;
	u32 val;
	u32 len;
} STRUCT_PACKED;

struct ctrl_msg {
	u32 cmd;
	u16 pad;
	u16 len;
	u8  data[1];
} STRUCT_PACKED;

struct mail_msg {
	u32 cmd_id;				// Command ID
    u8* in_buf;             // Message buffer to wpa_supplicant
    u32 in_len;             // Message Length to wpa_supplicant
    u8 *out_buf;            // Message buffer from wpa_supplicant
    u32 out_len;            // Message Reserve Length from wpa_supplicant
    u32 ret_len;           	// Message Length from wpa_supplicant
    u32 status;				// Message status
};
struct ctrl_iface_priv {
	struct wpa_supplicant *wpa_s;
	os_mailbox	ctrl_mbox;
	os_mailbox	sup_mbox;
	os_handle rx_sock;
	os_handle tx_sock;
	struct wpa_ctrl_dst *ctrl_dst;
	u32 (*event_notify)(u32 id, u16 data);
};
typedef enum HOST_SOCKET_STATUS{
    SOCKET_STATUS_CLOSE = 1,
	SOCKET_STATUS_OPEN
} HOST_SOCKET_STATUS;

typedef enum WPA_KEY_STATUS {
	WPA_KEY_EXCHG_START = 1,
	WPA_KEY_EXCHG_END,
} WPA_KEY_STATUS;
//**********************************************************************************
//                Extern Variable Define
// **********************************************************************************
//**********************************************************************************
//                Extern Function Declaration
// **********************************************************************************
extern os_handle wpa_supplicant_ctrl_iface_rx_sock(void);
extern os_handle wpa_supplicant_ctrl_iface_tx_sock(void);
extern u32 wpa_event_notify(u32 id, u16 data);
extern int wpa_supplicant_update_bss_info(struct wpa_supplicant *wpa_s);
extern void wpa_req_cpu_speed_up(void);
extern void wpa_req_cpu_speed_down(void);
extern void wpa_supplicant_ctrl_set_key_status(WPA_KEY_STATUS key_status);
extern void wpa_supplicant_ctrl_set_socket_status(HOST_SOCKET_STATUS socket_status);

#endif



