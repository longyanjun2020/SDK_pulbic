/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
#ifndef __LWIP_STATS_H__
#define __LWIP_STATS_H__

#include "opt.h"

#include "mem.h"
#include "memp.h"

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_STATS

#ifndef LWIP_STATS_LARGE
#define LWIP_STATS_LARGE 1
#endif

#if LWIP_STATS_LARGE
#define STAT_COUNTER     u32_t
#define STAT_COUNTER_F   U32_F
#else
#define STAT_COUNTER     u16_t
#define STAT_COUNTER_F   U32_F
#endif 

struct stats_proto {
  STAT_COUNTER xmit;             /* Transmitted packets. */
  STAT_COUNTER recv;             /* Received packets. */
  STAT_COUNTER fw;               /* Forwarded packets. */
  STAT_COUNTER drop;             /* Dropped packets. */
  STAT_COUNTER chkerr;           /* Checksum error. */
  STAT_COUNTER lenerr;           /* Invalid length error. */
  STAT_COUNTER memerr;           /* Out of memory error. */
  STAT_COUNTER rterr;            /* Routing error. */
  STAT_COUNTER proterr;          /* Protocol error. */
  STAT_COUNTER opterr;           /* Error in options. */
  STAT_COUNTER err;              /* Misc error. */
  STAT_COUNTER cachehit;
};

struct stats_igmp {
  STAT_COUNTER xmit;             /* Transmitted packets. */
  STAT_COUNTER recv;             /* Received packets. */
  STAT_COUNTER drop;             /* Dropped packets. */
  STAT_COUNTER chkerr;           /* Checksum error. */
  STAT_COUNTER lenerr;           /* Invalid length error. */
  STAT_COUNTER memerr;           /* Out of memory error. */
  STAT_COUNTER proterr;          /* Protocol error. */
  STAT_COUNTER rx_v1;            /* Received v1 frames. */
  STAT_COUNTER rx_group;         /* Received group-specific queries. */
  STAT_COUNTER rx_general;       /* Received general queries. */
  STAT_COUNTER rx_report;        /* Received reports. */
  STAT_COUNTER tx_join;          /* Sent joins. */
  STAT_COUNTER tx_leave;         /* Sent leaves. */
  STAT_COUNTER tx_report;        /* Sent reports. */
};

struct stats_mem {

#ifdef LWIP_DEBUG
  const char *name;
#endif /* LWIP_DEBUG */

  mem_size_t avail;
  mem_size_t used;
  mem_size_t max;
  STAT_COUNTER err;
  STAT_COUNTER illegal;
};

struct stats_syselem {
  STAT_COUNTER used;
  STAT_COUNTER max;
  STAT_COUNTER err;
};

struct stats_sys {
  struct stats_syselem sem;
  struct stats_syselem mutex;
  struct stats_syselem mbox;
};

struct stats_socket {
  STAT_COUNTER send_req;         /* packets send request via lwip_send */
  STAT_COUNTER sendto_req;       /* packets send request via lwip_sendto */
  STAT_COUNTER sendmsg_req;      /* packets send request via lwip_sendmsg */
  STAT_COUNTER send_err;         /* packets send request via lwip_send */
  STAT_COUNTER sendto_err;       /* packets send request via lwip_sendto */
  STAT_COUNTER sendmsg_err;      /* packets send request via lwip_sendmsg */
};

struct stats_ {

#if LINK_STATS
  struct stats_proto link;
#endif///< LINK_STATS

#if ETHARP_STATS
  struct stats_proto etharp;
#endif

#if IPFRAG_STATS
  struct stats_proto ip_frag;
#endif
#if IP_STATS
  struct stats_proto ip;
#endif
#if ICMP_STATS
  struct stats_proto icmp;
#endif
#if IGMP_STATS
  struct stats_igmp igmp;
#endif
#if UDP_STATS
  struct stats_proto udp;
#endif
#if TCP_STATS
  struct stats_proto tcp;
#endif
#if MEM_STATS
  struct stats_mem mem;
#endif
#if MEMP_STATS
  struct stats_mem memp[MEMP_MAX];
#endif
#if SYS_STATS
  struct stats_sys sys;
#endif
#if SOCKET_STATS
  struct stats_socket sock;
#endif
};

extern struct stats_ lwip_stats;

void stats_init(void);

#define STATS_INC(x) ++lwip_stats.x
#define STATS_DEC(x) --lwip_stats.x
#define STATS_INC_USED(x, y) do {   lwip_stats.x.used += y; \
                                    if (lwip_stats.x.max < lwip_stats.x.used) { \
                                        lwip_stats.x.max = lwip_stats.x.used; \
                                    } \
                             } while(0)
#else /* LWIP_STATS */
#define stats_init()
#define STATS_INC(x)
#define STATS_DEC(x)
#define STATS_INC_USED(x)
#endif /* LWIP_STATS */

#if TCP_STATS
#define TCP_STATS_INC(x)       STATS_INC(x)
#define TCP_STATS_DISPLAY(pst) stats_display_proto(&(pst)->tcp, "TCP")
#else /* TCP_STATS */
#define TCP_STATS_INC(x)
#define TCP_STATS_DISPLAY(pst)
#endif /* TCP_STATS */

#if UDP_STATS
#define UDP_STATS_INC(x)       STATS_INC(x)
#define UDP_STATS_DISPLAY(pst) stats_display_proto(&(pst)->udp, "UDP")
#else /* UDP_STATS */
#define UDP_STATS_INC(x)
#define UDP_STATS_DISPLAY(pst)
#endif /* UDP_STATS */

#if ICMP_STATS
#define ICMP_STATS_INC(x)       STATS_INC(x)
#define ICMP_STATS_DISPLAY(pst) stats_display_proto(&(pst)->icmp, "ICMP")
#else /* ICMP_STATS */
#define ICMP_STATS_INC(x)
#define ICMP_STATS_DISPLAY(pst)
#endif /* ICMP_STATS */

#if IGMP_STATS
#define IGMP_STATS_INC(x)       STATS_INC(x)
#define IGMP_STATS_DISPLAY(pst) stats_display_igmp(&(pst)->igmp)
#else /* ICMP_STATS */
#define IGMP_STATS_INC(x)
#define IGMP_STATS_DISPLAY(pst)
#endif /* ICMP_STATS */

#if IP_STATS
#define IP_STATS_INC(x)        STATS_INC(x)
#define IP_STATS_DISPLAY(pst)  stats_display_proto(&(pst)->ip, "IP")
#else /* IP_STATS */
#define IP_STATS_INC(x)
#define IP_STATS_DISPLAY(pst)
#endif /* IP_STATS */

#if IPFRAG_STATS
#define IPFRAG_STATS_INC(x)        STATS_INC(x)
#define IPFRAG_STATS_DISPLAY(pst)  stats_display_proto(&(pst)->ip_frag, "IP_FRAG")
#else
#define IPFRAG_STATS_INC(x)
#define IPFRAG_STATS_DISPLAY(pst)
#endif

#if ETHARP_STATS
#define ETHARP_STATS_INC(x)        STATS_INC(x)
#define ETHARP_STATS_DISPLAY(pst)  stats_display_proto(&(pst)->etharp, "ETHARP")
#else
#define ETHARP_STATS_INC(x)
#define ETHARP_STATS_DISPLAY(pst)
#endif

#if LINK_STATS
#define LINK_STATS_INC(x)          STATS_INC(x)
#define LINK_STATS_DISPLAY(pst)    stats_display_proto(&(pst)->link, "LINK")
#else
#define LINK_STATS_INC(x)
#define LINK_STATS_DISPLAY(pst)
#endif

#if MEM_STATS
#define MEM_STATS_AVAIL(x, y)       lwip_stats.mem.x = y
#define MEM_STATS_INC(x)            STATS_INC(mem.x)
#define MEM_STATS_INC_USED(x, y)    STATS_INC_USED(mem, y)
#define MEM_STATS_DEC_USED(x, y)    lwip_stats.mem.x -= y
#define MEM_STATS_DISPLAY(pst)      stats_display_mem(&(pst)->mem, "HEAP")
#else
#define MEM_STATS_AVAIL(x, y)
#define MEM_STATS_INC(x)
#define MEM_STATS_INC_USED(x, y)
#define MEM_STATS_DEC_USED(x, y)
#define MEM_STATS_DISPLAY(pst)
#endif

#if MEMP_STATS
#define MEMP_STATS_AVAIL(x, i, y)   lwip_stats.memp[i].x = y
#define MEMP_STATS_INC(x, i)        STATS_INC(memp[i].x)
#define MEMP_STATS_DEC(x, i)        STATS_DEC(memp[i].x)
#define MEMP_STATS_INC_USED(x, i)   STATS_INC_USED(memp[i], 1)
#define MEMP_STATS_DISPLAY(pst,i)   stats_display_memp(&((pst)->memp[i]), i)
#else///< MEMP_STATS
#define MEMP_STATS_AVAIL(x, i, y)
#define MEMP_STATS_INC(x, i)
#define MEMP_STATS_DEC(x, i)
#define MEMP_STATS_INC_USED(x, i)
#define MEMP_STATS_DISPLAY(pst,i)
#endif///< MEMP_STATS

#if SYS_STATS
#define SYS_STATS_INC(x)        STATS_INC(sys.x)
#define SYS_STATS_DEC(x)        STATS_DEC(sys.x)
#define SYS_STATS_INC_USED(x)   STATS_INC_USED(sys.x, 1)
#define SYS_STATS_DISPLAY(pst)  stats_display_sys(&(pst)->sys)
#else
#define SYS_STATS_INC(x)
#define SYS_STATS_DEC(x)
#define SYS_STATS_INC_USED(x)
#define SYS_STATS_DISPLAY(pst)
#endif

#if SOCKET_STATS
#define SOCKET_STATS_INC(x)        STATS_INC(sock.x)
#define SOCKET_STATS_DEC(x)        STATS_DEC(sock.x)
#define SOCKET_STATS_INC_USED(x)   STATS_INC_USED(sock.x, 1)
#define SOCKET_STATS_DISPLAY(pst)  stats_display_socket(&(pst)->sock)
#else
#define SOCKET_STATS_INC(x)
#define SOCKET_STATS_DEC(x)
#define SOCKET_STATS_INC_USED(x)
#define SOCKET_STATS_DISPLAY(pst)
#endif

/* Display of statistics */
#if LWIP_STATS_DISPLAY
void stats_display(void);
void stats_display_proto(struct stats_proto *proto, const char *name);
void stats_display_igmp(struct stats_igmp *igmp);
void stats_display_mem(struct stats_mem *mem, const char *name);
void stats_display_memp(struct stats_mem *mem, int index);
void stats_display_sys(struct stats_sys *sys);
void stats_display_socket(struct stats_socket *sock);
#else /* LWIP_STATS_DISPLAY */
#define stats_display()
#define stats_display_proto(proto, name)
#define stats_display_igmp(igmp)
#define stats_display_mem(mem, name)
#define stats_display_memp(mem, index)
#define stats_display_sys(sys)
#define stats_display_socket(sock)
#endif /* LWIP_STATS_DISPLAY */

#ifdef __cplusplus
}
#endif

#endif /* __LWIP_STATS_H__ */
