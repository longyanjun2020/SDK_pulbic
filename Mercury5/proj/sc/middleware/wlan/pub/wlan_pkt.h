/*****************************************************************************
 *
 *  Copyright (c) 2010 MStar Semiconductor, Inc.  All rights reserved.
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
 *****************************************************************************/

/*
* @file    wlan_pkt.h
* @version
* @brief   packet type definition
*/

#ifndef _WLAN_PKT_H_
#define _WLAN_PKT_H_

#include "mdl_bind_wlan.h"


/*****************************************************************************
 * Constants
 *****************************************************************************/

//Ethernet Protocol type
#define ETH_P_IP    0x0800
#define ETH_P_ARP   0x0806
#define ETH_P_EAPOL 0x888e
#define ETH_P_WAI  	0x88B4

//dummy buffer needed by TCP/IP
#define TCPIP_DUMMY_BUF_LEN     64

#define MAX_ETH_PKT_SIZE        1514

#define NG_WIFI_PKT_TYPE_TX     0
#define NG_WIFI_PKT_TYPE_RX     1
#define NG_WIFI_PKT_TYPE_HEAP   2

#define ND_WR_CREATE_SWITCH_ON   1
#define ND_WR_CREATE_SWITCH_OFF  0

//originally defined in proj\sc\middleware\supplicant\src\supplicant.c
#define IP_WIFI_FLOW_STOP     	0  /* flow closed */
#define IP_WIFI_FLOW_START       1  /* flow open */


/*****************************************************************************
 * Aquarius Message Data Types
 *****************************************************************************/

/* Message Type */
typedef enum
{
    eMSG_DATA           = 0x1,
    eMSG_QOID           = 0x4,
    eMSG_QOID_CMPLT     = 0x14,
    eMSG_SOID           = 0x5,
    eMSG_SOID_CMPLT     = 0x15,
    eMSG_INDICATION     = 0x7,
    eMSG_HOST_NOTIFY    = 0x8,
    eMSG_TMT_MSG        = 0x9,
    eMSG_CARD_GET       = 0xa,
    eMSG_CARD_SET       = 0xb,

} MSG_TYPE_e;

/* Indication Type */
typedef enum
{
    eINDICATE_CONNECT=0,
    eINDICATE_AUTH=1,
    eINDICATE_RSSI=2

} INDICATE_TYPE_e;

/* Message Header */
typedef struct
{
    u8  msg_type;
    u8  req_id;
    u16 msg_len;
} __attribute__ ((packed)) MSG_HEADER_t;

/* Query Message */
typedef struct
{
    MSG_HEADER_t msg_header;
    u32 oid;
    //u8 info[0];
} QOID_MSG_t;

/* Query Complete Message */
typedef struct
{
    MSG_HEADER_t msg_header;
    u32 status;
    //u8 info[0];
} QOID_CMPLT_t;

/* Set Message */
typedef struct
{
    MSG_HEADER_t msg_header;
    u32 oid;
    //u8 info[0];
} SOID_MSG_t;

/* Set Complete Message */
typedef struct
{
    MSG_HEADER_t msg_header;
    u32 status;
} SOID_CMPLT_t;

/* Data Message */
typedef struct
{
    MSG_HEADER_t msg_header;
	u16	b2_align_padding;
    //u8 info[0];
} __attribute__ ((packed)) DATA_MSG_t;

/* Indication Message */
typedef struct
{
    MSG_HEADER_t msg_header;
    //u8 info[0];
} INDICATE_MSG_s;

/* TMT Message */
typedef struct
{
    MSG_HEADER_t msg_header;
    //u8         msg[0];
} TMT_MSG_t;

//used by the 2nd parameter of sdio_tx_data()
typedef enum
{
    SKB_DATA_OID,
    SKB_DATA_PACKET

} SKB_DATA_TYPE_e;

typedef struct {
    u16   req_id;
    u16   str_id;
    int   buf_size;
    void *buf_addr;
} CARD_GET_S;

typedef struct {
    u16   req_id;
    u16   str_id;
    int   data_size;
    u8    data[1];
} CARD_SET_S;

/*****************************************************************************
 * SKB Data Types
 *****************************************************************************/

 /*
 *	IEEE 802.3 Ethernet magic constants.  The frame sizes omit the preamble
 *	and FCS/CRC (frame check sequence).
 */

#define ETH_ALEN	6		/* Octets in one ethernet addr	 */
#define ETH_HLEN	14		/* Total octets in header.	 */
#define ETH_ZLEN	60		/* Min. octets in frame sans FCS */
#define ETH_DATA_LEN	1500		/* Max. octets in payload	 */
#define ETH_FRAME_LEN	1514		/* Max. octets in frame sans FCS */
#define ETH_FCS_LEN	4		/* Octets in the FCS		 */

struct ethhdr {
	u8 h_dest[ETH_ALEN];	/* destination eth addr	*/
	u8 h_source[ETH_ALEN];	/* source ether addr	*/
	u16 h_proto;		/* packet type ID field	*/
} __attribute__((packed));

#define __LITTLE_ENDIAN_BITFIELD

struct iphdr {
#if defined(__LITTLE_ENDIAN_BITFIELD)
	u8	ihl:4,
		version:4;
#elif defined (__BIG_ENDIAN_BITFIELD)
	__u8	version:4,
  		ihl:4;
#else
#error	"Please fix <asm/byteorder.h>"
#endif
	u8	tos;
	u16	tot_len;
	u16	id;
	u16	frag_off;
	u8	ttl;
	u8	protocol;
	u16	check;
	u32	saddr;
	u32	daddr;
	/*The options start here. */
};

struct layer2_eth
{
    u8 dst_mac[6];
    u8 src_mac[6];
    u16 ethType;

} __attribute__((packed));

//**********************************************************************************
//                Macro Define and Inline function
//**********************************************************************************
#define bswap_16(v) (((v & 0xff) << 8) | (v >> 8))
#define bswap_32(v) (((v & 0xff) << 24) | ((v & 0xff00) << 8) | ((v & 0xff0000) >> 8) | (v >> 24))


/************************************************************************
 * Function Prototype
 ************************************************************************/

/* TX and RX */
int wifi_send_packet(void *pPacket);
int wifi_send_pkt(void *pPacket);
int wifi_send_oid(struct sk_buff *pSkb);
void netif_rx_ni(struct sk_buff *pSkb);
void wifi_recv_pkt(struct sk_buff *pSkb);


#endif //_WLAN_PKT_H_
