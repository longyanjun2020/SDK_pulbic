/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
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
#ifndef __ARCH_SYS_ARCH_H__
#define __ARCH_SYS_ARCH_H__

#include "cc.h"
#include "os_wrap.h"
#include "sys_MsWrapper_cus_os_util.h"
#include <string.h>


#ifdef SYS_ARCH_GLOBALS
#define SYS_ARCH_EXT
#else
#define SYS_ARCH_EXT extern
#endif

#define  APP_ID                       8427
#define  ETHERNET_DRV_ID              APP_ID+1
#define  ETHERNET_TSK_ID              APP_ID+2
#define  LWIP_TSK_ID                  0 // APP_ID+3

/*-----------------macros-----------------------------------------------------*/

#if defined(__RTK_OS__)
#define ENHANCE_FILE_TX_BY_MULTI_THREAD		1
#else
#define __AIT_THREAD_ALLOC_FROM_HIGH_PRIO__
#endif

#if defined(__RTK_OS__)
#define LWIP_STK_SIZE          4096
#define LWIP_TASK_MAX          20 //Total number of tasks used by LWIP and WLAN driver.

#if(ENHANCE_FILE_TX_BY_MULTI_THREAD)
#define LWIP_TASK_START_PRIO   169//must sync with TASK_NET_INTERNAL_PRIO_END + 1
#else
#define LWIP_TASK_START_PRIO   168//must sync with TASK_NET_INTERNAL_PRIO_END
#endif
#define LWIP_TASK_END_PRIO     (LWIP_TASK_START_PRIO + LWIP_TASK_MAX)//must sync with TASK_NET_INTERNAL_PRIO_START - 1
#define LWIP_OS_SEMID_MAX      250
#else
#define LWIP_STK_SIZE          4096  /* TASK_STK_SIZE */
#define LWIP_TASK_MAX          13 //Total number of tasks used by LWIP
#define LWIP_TASK_START_PRIO   40
#define LWIP_TASK_END_PRIO     (LWIP_TASK_START_PRIO + LWIP_TASK_MAX)
#endif

//max number of lwip tasks (TCPIP) note LWIP TASK start with 1


#define LWIP_START_PRIO	  LWIP_TASK_START_PRIO		//first prio of lwip tasks in uC/OS-II

#define MAX_QUEUES        32	// the number of mailboxes
#define MAX_QUEUE_ENTRIES 128	// the max size of each mailbox

#define SYS_MBOX_NULL (void *)0
#define SYS_SEM_NULL  (void *)0

#define sys_arch_mbox_tryfetch(mbox,msg) \
      sys_arch_mbox_fetch(mbox,msg,1)

#define slprintf  snprintf

/*-----------------type define------------------------------------------------*/
#define MBOX_VER (2)
/** struct of LwIP mailbox */

typedef struct {
	ms_Queue_t	Queue;
#if MBOX_VER >= 2
    u32   		QProduceSemId;
    u32   		QLimitSemId;
    u32     	QId;
#endif
} TQ_DESCR, *PQ_DESCR;

//typedef OS_EVENT *sys_sem_t; // type of semaphores
//typedef OS_EVENT *sys_mutex_t; // type of mutex
typedef u32 sys_sem_t; // type of semaphores
typedef	u32 sys_mutex_t; // type of mutex

typedef PQ_DESCR sys_mbox_t; // type of mailboxes
typedef u8 sys_thread_t; // type of id of the new thread

typedef u8 sys_prot_t;

/*-----------------global variables-------------------------------------------*/


#endif /* __SYS_RTXC_H__ */

