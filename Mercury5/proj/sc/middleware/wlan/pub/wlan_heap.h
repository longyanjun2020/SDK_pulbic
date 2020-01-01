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
* @file    wlan_heap.h
* @version
* @brief   WLAN heap header file
*/

#ifndef _WLAN_HEAP_H_
#define _WLAN_HEAP_H_


#include "mdl_bind_wlan.h"


/************************************************************************
 * Constant
 ************************************************************************/
#define HEAP_LOW_WATER_MARK     1
#define HEAP_HIGH_WATER_MARK    (HEAP_BLOCK_DEPTH - 10)

#define USE_PMALLOC             1


/************************************************************************
 * Data Type
 ************************************************************************/
typedef struct
{
    u8 aBuffer[HEAP_BLOCK_SIZE];
    void *next;
    u32 inuse;
    u32 lock;
    u8 pad[MEM_POOL_SIZE - HEAP_BLOCK_SIZE - 12];
} __attribute__ ((packed)) WIFI_HEAP_BLOCK_t;

struct WIFI_HEAP_HEAD
{
    u8 *org_heap;
    WIFI_HEAP_BLOCK_t *start_pool;
    WIFI_HEAP_BLOCK_t *end_pool;
    WIFI_HEAP_BLOCK_t *free_list;
    u16 free_cnt;
    u8 empty_flag;
};

typedef enum
{
    RX_MEM_POOL = 0,
    TX_MEM_POOL,
    HEAP_MEM_POOL

} MEM_POOL_TYPE_e;


/************************************************************************
 * Function Prototype
 ************************************************************************/

void wifi_rx_heap_init(u8 *pBuf);
void wifi_tx_heap_init(u8 *pBuf);

void wifi_rx_heap_free(void);
void wifi_tx_heap_free(void);

u8 *wifi_rx_malloc(u32 len);
u8 *wifi_tx_malloc(u32 len);

void wifi_rx_mfree(void *pBuffer, u8 force);
void wifi_tx_mfree(void *pBuffer, u8 force);
void wifi_mfree(void *pBuffer);
void force_wifi_mfree(void *pBuffer);

u32 wifi_rx_get_mlock(void *pBuffer);
u32 wifi_tx_get_mlock(void *pBuffer);
u32 wifi_get_mlock(void *pBuffer);

void wifi_rx_set_mlock(void *pBuffer, u32 lock);
void wifi_tx_set_mlock(void *pBuffer, u32 lock);
void wifi_set_mlock(void *pBuffer, u32 lock);

u16 wifi_rx_get_mfree_count(void);
u16 wifi_tx_get_mfree_count(void);

struct sk_buff *rx_alloc_skb(u32 len);
struct sk_buff *tx_alloc_skb(u32 len);
struct sk_buff *heap_alloc_skb(u32 len);
void dev_kfree_skb(struct sk_buff *pSkb);
u8 *skb_put(struct sk_buff *pSkb, int len);
void skb_reserve(struct sk_buff *pSkb, int len);

void dump_wifi_rx_pool(void);
void dump_wifi_tx_pool(void);

MEM_POOL_TYPE_e chk_memory_pool_type(void *pBuffer);


#endif //_WLAN_HEAP_H_
