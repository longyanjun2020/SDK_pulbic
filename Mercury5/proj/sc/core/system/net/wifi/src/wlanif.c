

#include "etharp.h"
#include "stats.h"
#include "netif.h"
#include "os_wrap.h"
#include "netapp.h"
#include "igmp.h"
#include "wlanif.h"

extern err_t tcpip_input(struct pbuf *p, struct netif *inp);

#if LWIP_IGMP

/**
 * Interface between LwIP IGMP MAC filter and MAC filter
 */
static err_t lwip_igmp_mac_filter( struct netif *netif, ip_addr_t *group, u8_t action )
{
#if(WIFI_DRIVER_TYPE == WIFI_DRIVER_BCM)
    uint8 multicast_mac[6];

    //Multicast IP to MAC
    multicast_mac[0] = 0x01;
    multicast_mac[1] = 0x00;
    multicast_mac[2] = 0x5e;
    multicast_mac[3] = ((uint8*)group)[1] & 0x7F;
    multicast_mac[4] = ((uint8*)group)[2];
    multicast_mac[5] = ((uint8*)group)[3];

    switch ( action )
    {
        case IGMP_ADD_MAC_FILTER:
            if ( wlan_wifi_register_multicast_address( multicast_mac ) != 0 )
            {
                return ERR_VAL;
            }
            break;

        case IGMP_DEL_MAC_FILTER:
            if ( wlan_wifi_unregister_multicast_address( multicast_mac ) != 0 )
            {
                return ERR_VAL;
            }
            break;

        default:
            return ERR_VAL;
    }

    return ERR_OK;
#else
    return ERR_OK;
#endif
}
#endif

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */

int
low_level_init(struct netif *netif)
{
    nhw_drv_hdl hdl = WLAN_SYS_Start();

    if(hdl) {
        nhw_set_handle(hdl);
        /* set MAC hardware address length */
        netif->hwaddr_len = ETHARP_HWADDR_LEN;

        /* set MAC hardware address */
        /* Setup the physical address of this IP instance.
        */
        WLAN_SYS_GetMacAddr(netif->hwaddr);

        /* maximum transfer unit */
        //netif->mtu = GB9662_LINK_MTU;
        netif->mtu = 1500;

        /* device capabilities */
        /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
        netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

    #if LWIP_IGMP
        netif->flags |= NETIF_FLAG_IGMP;
        netif_set_igmp_mac_filter(netif, lwip_igmp_mac_filter);
    #endif

    #if(WIFI_DRIVER_TYPE == WIFI_DRIVER_ATBM)
        atbm_set_netif(netif); // TBD
    #endif

        return 1;   // success
    }
    return 0;   // fail
}

#pragma arm section code = "WIFISpeedUp", rwdata = "WIFISpeedUp",  zidata = "WIFISpeedUp"
/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

 // dynamically allocate bandwidth?
err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    int cnt;
    (void) netif;   //unused parameter

    pbuf_ref(p);    // take a reference to this packet
    cnt = WLAN_SYS_GetTXQueueAvailCount();

    if (cnt <= 8) {
        if (cnt > 4) {
            LINK_STATS_INC(link.err);
            MMPF_OS_Sleep(1);      // simple throttle
        }
        else {
            LINK_STATS_INC(link.opterr);
            while(1) {
                MMPF_OS_Sleep(1);  // complex throttle
                if ((WLAN_SYS_GetTXQueueAvailCount() - cnt) >= 1) break;
            }
        }
    }

#if 0
    iperf_check_datagram(p);
#endif

    WLAN_SYS_TxPkt(p);
    //uiEndTime = sys_now();
    /*
    if((uiEndTime > uiStartTime) && (uiEndTime - uiStartTime) > ){


    }
    */
    LINK_STATS_INC(link.xmit);

    return ERR_OK;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param p : the incoming ethernet packet
 */
void host_network_process_ethernet_data(struct pbuf *p, struct netif *interface)
{
    struct eth_hdr *ethhdr;
    //struct netif *tmpNetif;

    if (p == NULL) return;

    /* points to packet payload, which starts with an Ethernet header */
    ethhdr = (struct eth_hdr*)p->payload;

    if(interface == NULL)
    {
        // Received a packet for a network interface is not initialised
        // Cannot do anything with packet - just drop it.
        pbuf_free(p);
        p = NULL;
        LINK_STATS_INC(link.drop);
        return;
    }

    LINK_STATS_INC(link.recv);

    switch (htons(ethhdr->type)) {
    /* IP or ARP packet? */
    case ETHTYPE_IP:
    case ETHTYPE_ARP:
    #if PPPOE_SUPPORT
    /* PPPoE packet? */
    case ETHTYPE_PPPOEDISC:
    case ETHTYPE_PPPOE:
    #endif /* PPPOE_SUPPORT */
        /* full packet send to tcpip_thread to process */
        if (tcpip_input(p, interface)!=ERR_OK)
        {
            LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));

            pbuf_free(p);
            p = NULL;
        }

        break;

    default:

        LINK_STATS_INC(link.proterr);
        pbuf_free(p);
        p = NULL;
        break;
    }
}
#pragma arm section code, rwdata,  zidata
