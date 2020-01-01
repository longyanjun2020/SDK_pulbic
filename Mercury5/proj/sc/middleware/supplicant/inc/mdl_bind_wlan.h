////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_supplicant.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


#ifndef __MDL_BIND_WLAN_H__
#define __MDL_BIND_WLAN_H__

#if defined(__cplusplus)
extern "C" {
#endif

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define HEAP_BLOCK_SIZE         1728

#define RX_HEAP_BLOCK_DEPTH     64
#define TX_HEAP_BLOCK_DEPTH     64

#define MEM_POOL_SIZE           0x800   //for efficient memory address mapping
#define MEM_POOL_MASK           (MEM_POOL_SIZE - 1)
#define MEM_POOL_SHIFT_BIT      11


/*=============================================================*/
// Data type definition
/*=============================================================*/
struct net_device_stats
{
    int tx_packets;
    int tx_bytes;
    int tx_errors;
    int rx_packets;
    int rx_bytes;
};

struct net_device
{
 	void *priv;
 	struct net_device_stats stats;
 	u8 dev_addr[6];
 	u8 name[32];
};

struct sk_buff
{
    struct net_device *dev;
    u8 *head;
    u8 *data;
    u8 *tail;
    u8 *end;
    u32 len;
    u8 pkt_type;
    u8 ip_summed;
    u16 protocol;
    u32 priority;
};

struct wlan_callback_ops {
    struct sk_buff * (*tx_alloc_skb)(u32 len);
    int (*wifi_send_pkt)(void *pPacket);
};
/*=============================================================*/
// Function Declaration
/*=============================================================*/
extern void supp_register_wlan_callback(struct wlan_callback_ops *wlan_cb);
#if defined(__cplusplus)
}
#endif

#endif // __MDL_SUPPLICANT_H__
