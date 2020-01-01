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
* @file    wlan_queue.h
* @version
* @brief   WLAN queue header file
*/

#ifndef _WLAN_QUEUE_H_
#define _WLAN_QUEUE_H_


/*****************************************************************************
 * Constant
 *****************************************************************************/

#define New_RX_Q_LOW_WATER_MARK_TRIGGER     1
#define New_TX_Q_LOW_WATER_MARK_TRIGGER     0

#define WMM_SUPPORT     1

/*
 * For supportng: RX buffer can be re-routed to TX queue
 * RX queue must > (RX + TX memory pools)
 */
#define MAX_RXQ_DEPTH               (RX_HEAP_BLOCK_DEPTH + TX_HEAP_BLOCK_DEPTH + 1)
#define RX_QUEUE_LOW_WATER_MARK     1

/*
 * For supportng: RX buffer can be re-routed to TX queue
 * TX queue must > (RX + TX memory pools)
 */
#define MAX_TXQ_DEPTH               (RX_HEAP_BLOCK_DEPTH + TX_HEAP_BLOCK_DEPTH + 1)
#define TX_QUEUE_LOW_WATER_MARK     1

#define WMM_AC_BK_TXQ   0       /* background */
#define WMM_AC_BE_TXQ   1       /* best effort */
#define WMM_AC_VI_TXQ   2       /* video */
#define WMM_AC_VO_TXQ   3       /* voice */
#define OID_TXQ         4       /* OID queue */

#define QOS_DEPTH       4


/*****************************************************************************
 * Data Structure
 *****************************************************************************/

struct my_packet
{
    struct sk_buff      *pSkb;
};

struct my_packet_header
{
	u16	                head;
    u16	                tail;
    u16                 cnt;
    char                name[32];
};


/*****************************************************************************
 * Macro
 *****************************************************************************/

#define reorder_priority_to_index(_ac) ((_ac == 0) ? 1 : (_ac == 1) ? 0 : _ac)

#define DSCP_TO_WMM_AC(_tid) (      \
    ((_tid) == 0 || (_tid) == 3) ? WMM_AC_BE_TXQ : \
    ((_tid) < 3) ? WMM_AC_BK_TXQ : \
    ((_tid) < 6) ? WMM_AC_VI_TXQ : \
    WMM_AC_VO_TXQ)


/************************************************************************
 * Function Prototype
 ************************************************************************/

void rx_queue_init(void);
BOOL rx_enqueue(struct sk_buff *pSkb);
void* rx_dequeue(void);
u16 get_rx_queue_count(void);
void rx_clean_queue(void);
void set_rx_q_low_water_mark(u8 val);

#if New_RX_Q_LOW_WATER_MARK_TRIGGER
void checkRxQueueLowWaterMark(void);
#endif

void tx_queue_init(void);
BOOL tx_enqueue(u8 q_index, struct sk_buff *pSkb);
void* tx_dequeue(u8 q_index);
void* wmm_tx_dequeue(void);
void tx_clean_queue(void);
void tx_clean_pkt_queue(void);
void set_tx_q_low_water_mark(u8 val);

#if New_TX_Q_LOW_WATER_MARK_TRIGGER
void checkTxQueueLowWaterMark(void);
#endif

#endif //_WLAN_QUEUE_H_
