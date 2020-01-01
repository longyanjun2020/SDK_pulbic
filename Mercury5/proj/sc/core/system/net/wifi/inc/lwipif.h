
//#define	WPS_AP_SUPPORT

#ifndef _INCLUDED_LWIP_IF_H_
#define _INCLUDED_LWIP_IF_H_


#include "err.h"

struct pbuf;
struct netif;

/******************************************************
 *             Constants
 ******************************************************/

/******************************************************
 *             Structures
 ******************************************************/

/******************************************************
 *             Function declarations
 ******************************************************/

err_t ethernetif_init(struct netif *netif);
err_t ethernet_input(struct pbuf *p, struct netif *netif);
err_t low_level_output(struct netif *netif, struct pbuf *p);
void host_network_process_ethernet_data(struct pbuf *p, struct netif *interface);
int low_level_init(struct netif *netif);

/******************************************************
 *             Global variables
 ******************************************************/


#endif /* define _INCLUDED_LWIP_IF_H_ */

