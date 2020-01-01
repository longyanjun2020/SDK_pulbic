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
* @file    wlan_msg.h
* @version
* @brief   WLAN message header file
*/

#ifndef _WLAN_MSG_H_
#define _WLAN_MSG_H_


/******************************************
 * Data Type Definition
 ******************************************/

#ifndef BOOL
#define BOOL unsigned char
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif


/******************************************
 * DMA Alignment
 ******************************************/

#define PIF_DMA_ALIGNMENT  32

/* Setup the correct byte alignment mask for the defined byte alignment. */
#if PIF_DMA_ALIGNMENT == 32
	#define PIF_DMA_ALIGNMENT_MASK ( ( u32 ) 0x0000001f )
#elif PIF_DMA_ALIGNMENT == 16
	#define PIF_DMA_ALIGNMENT_MASK ( ( u32 ) 0x0000000f )
#elif PIF_DMA_ALIGNMENT == 8
	#define PIF_DMA_ALIGNMENT_MASK ( ( u32 ) 0x00000007 )
#elif PIF_DMA_ALIGNMENT == 4
	#define PIF_DMA_ALIGNMENT_MASK ( ( u32 ) 0x00000003 )
#elif PIF_DMA_ALIGNMENT == 2
	#define PIF_DMA_ALIGNMENT_MASK ( ( u32 ) 0x00000001 )
#elif PIF_DMA_ALIGNMENT == 1
	#define PIF_DMA_ALIGNMENT_MASK ( ( u32 ) 0x00000000 )
#else
	#error "Invalid PIF_DMA_ALIGNMENT definition"
#endif


/******************************************
 * Semaphore
 ******************************************/
#define WLAN_DRV_LOCK()     MsConsumeSem(WLAN_DRV_SEM)
#define WLAN_DRV_UNLOCK()   MsProduceSem(WLAN_DRV_SEM)

/******************************************
 * Control PCU speed according to socket
 * status and how long there is no TX/RX
 ******************************************/

//timeout interval
#define WIFI_TIMEOUT_MS         1000

/******************************************
 * Mail Box Flag and Message
 ******************************************/

/* WIFI flags */
#define WIFI_FLAG_OPEN          0x0001
#define WIFI_FLAG_CLOSE_REQ     0x0002

/* WIFI Mailbox Messages Types */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum
{
#include "wlan_message_define__.hi"
} WIFI_MBOX_MSG_e;

typedef struct
{
    Header_t        Header;

} WifiMsg_t;

typedef enum
{
    WLAN_CB_MIN = 0,

    WLAN_CB_TX_M_LOW_WATER = WLAN_CB_MIN,
    WLAN_CB_RX_M_LOW_WATER,

    WLAN_CB_TX_Q_LOW_WATER,
    WLAN_CB_RX_Q_LOW_WATER,

    WLAN_CB_MAX = WLAN_CB_RX_Q_LOW_WATER,

} WIFI_CB_ID_e;

typedef void (*wlan_CbFn)(u16 senderID, u32 userValue, void *pWifiInfo);

/* define host platform */
#define HOST_PLATFORM_NONE                  0
#define HOST_PLATFORM_MS_WINDOWS            1
#define HOST_PLATFORM_BIG2                  2
#define HOST_PLATFORM_BIG3                  3
#define HOST_PLATFORM_URANUS                4
#define HOST_PLATFORM_TITANIA               5
#define HOST_PLATFORM_BRAVO                 6
#define HOST_PLATFORM_BIG5                  7

/* define product ID */
#define MSTAR_AQUARIUS_U01                  ( 0x10 | (HOST_PLATFORM_NONE << 8) )
#define MSTAR_AQUARIUS_U02                  ( 0x11 | (HOST_PLATFORM_NONE << 8) )
#define MSTAR_NORMA_U01                     ( 0x20 | (HOST_PLATFORM_NONE << 8) )
#define MSTAR_NORMA_U02                     ( 0x21 | (HOST_PLATFORM_NONE << 8) )
#define MSTAR_NORMA_U03                     ( 0x22 | (HOST_PLATFORM_NONE << 8) )
#define MSTAR_NORMA2_U01                    ( 0x30 | (HOST_PLATFORM_NONE << 8) )
#define MSTAR_WINDOWS_XP                    ( 0x10 | (HOST_PLATFORM_MS_WINDOWS << 8) )
#define MSTAR_BIG2_NORMA_PHONE              ( 0x10 | (HOST_PLATFORM_BIG2 << 8) )
#define MSTAR_BIG2_NORMA_RDA                ( 0x20 | (HOST_PLATFORM_BIG2 << 8) )
#define MSTAR_BIG2_NORMA_RDA2               ( 0x21 | (HOST_PLATFORM_BIG2 << 8) )
#define MSTAR_BIG3_MB303A                   ( 0x10 | (HOST_PLATFORM_BIG3 << 8) )
#define MSTAR_URANUS_U4                     ( 0x10 | (HOST_PLATFORM_URANUS << 8) )
#define MSTAR_TITANIA_T12                   ( 0x20 | (HOST_PLATFORM_TITANIA << 8) )
#define MSTAR_BRAVO_N10                     ( 0x10 | (HOST_PLATFORM_BRAVO << 8) )
#define MSTAR_BIG5_NAND                     ( 0x10 | (HOST_PLATFORM_BIG5 << 8) )
#define MSTAR_BIG5_NOR                      ( 0x20 | (HOST_PLATFORM_BIG5 << 8) )
#define MSTAR_BIG5_33BN_DUAL_ANT            ( 0x15 | (HOST_PLATFORM_BIG5 << 8) ) // NAND
#define MSTAR_BIG5_32B2_DUAL_ANT            ( 0x25 | (HOST_PLATFORM_BIG5 << 8) ) // NOR

/* RX Results */
typedef enum
{
    RX_CONTINUE = 0,
    RX_DONE,
    RX_NO_MEMORY_POOL,
    RX_NO_HEAP,
    RX_TURN_OFF_WIFI,

} RX_RESULT_e;

enum event_types { 	DRV_EVENT_CONNECT,
					DRV_EVENT_DISCONNECT,
					DRV_EVENT_MEDIA_SPECIFIC,
					DRV_EVENT_ADAPTER_ARRIVAL,
					DRV_EVENT_ADAPTER_REMOVAL,
					// watch dog happened and wpa_supplicant need to suspend request to driver
					DRV_EVENT_WATCHDOG_SUSPEND,
					// watch dog handle done and wpa_supplicant can resume the request to driver
					DRV_EVENT_WATCHDOG_RESUME,
					DRV_EVENT_SLEEP_SUSPEND,
					DRV_EVENT_SLEEP_RESUME,
					DRV_EVENT_PKT_TST_DONE,
					DRV_EVENT_SCAN_RESULTS,
					DRV_EVENT_SHARED_KEY_FAIL,
					DRV_EVENT_SOCKET_STATUS,
					DRV_EVENT_UNKNOWN };

/************************************************************************
 * Function Prototype
 ************************************************************************/
void wifi_send_msg(u16 dst, u16 msg_type);
u8 wifi_register_callback(WIFI_CB_ID_e cbID, wlan_CbFn cbFn);
u8 wifi_unregister_callback(WIFI_CB_ID_e cbID);
u8 wlan_reg_cb(WIFI_CB_ID_e cbID, wlan_CbFn cbFn);
u8 wlan_unreg_cb(WIFI_CB_ID_e cbID);
void WifiSocketStatusChange(u8 isOn);
u16 DrvWIFIGetStrInfo(u8 id, char *pStr, u16 maxLen);
void do_watchdog_reset(void);


#endif //_WLAN_MSG_H_
