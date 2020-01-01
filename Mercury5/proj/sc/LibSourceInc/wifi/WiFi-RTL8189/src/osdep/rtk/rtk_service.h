#ifndef __UCOSII_TYPE_H_
#define __UCOSII_TYPE_H_

//----- ------------------------------------------------------------------
// Include Files
//----- ------------------------------------------------------------------
#include  <stdlib.h>
#include  <string.h>
//#include  <rlx/rlx_cpu.h>
#include "wireless.h"
#ifdef CONFIG_PLATFORM_MSTAR_MSC8339
#include "usb_io_mstar.h"
#include "osl_ext.h"
#endif

// --------------------------------------------
//	Platform dependent type define
// --------------------------------------------
typedef unsigned char 		UINT8,*PUINT8,u8;
typedef unsigned short      UINT16,u16;
typedef unsigned int		UINT32,u32,uint;
typedef unsigned long 		ULONG;
typedef unsigned long long	UINT64,u64;
typedef signed char 		SINT8,s8;
typedef signed short		s16;
typedef signed int 			SINT32,s32,sint;
typedef signed long 		SLONG;
typedef signed long long 	s64;

typedef unsigned int		__kernel_size_t;
typedef int			__kernel_ssize_t;
typedef	__kernel_size_t		SIZE_T;	
typedef	__kernel_ssize_t	SSIZE_T;
#define FIELD_OFFSET(s,field)	((SSIZE_T)&((s*)(0))->field)
typedef char			osdepCHAR;
typedef float			osdepFLOAT;
typedef double			osdepDOUBLE;
typedef long			osdepLONG;
typedef short			osdepSHORT;
typedef unsigned long	osdepSTACK_TYPE;
typedef long			osdepBASE_TYPE;
typedef unsigned long	osdepTickType;

typedef void * 				PVOID;
typedef long 				net_id;

typedef unsigned long	dma_addr_t;

#ifdef CONFIG_USB_HCI
typedef struct urb *  PURB;
#endif

#define _SUCCESS	1
#define _FAIL		0
#define VOID void

#if 0//YAN_MASK
#undef _TRUE
#define _TRUE		1

#undef _FALSE
#define _FALSE		0

#undef NULL
#define NULL		0

#undef TRUE
#define TRUE  		1
#undef FALSE 
#define FALSE 		0
#endif

#ifndef bool
typedef unsigned char				bool;
#define  true				1
#define  false				0
#endif

typedef unsigned int		_irqL;
typedef unsigned char 	_thread_hdl_;//YAN_MASK
//typedef void*			_thread_hdl_;
typedef void			thread_return;
typedef void*			thread_context;
typedef void*	_timerHandle;
//typedef void*	_sema;
//typedef void*	_mutex;
//typedef void*	_lock;
typedef void*	_queueHandle;
typedef void*	_xqueue;
typedef unsigned char		_buffer;

typedef void (*task_func_t)(void *context);
#define WQ_THREAD_ENTRY(parameter)		rtw_wq_task_thread(void* argv)
//typedef  void (*TIMER_FUN)(void *ptmr, void *parg);
typedef void (*TIMER_FUN)(void *context);//YAN_MASK

typedef struct _ADAPTER ADAPTER, *PADAPTER; 

typedef int (*wifi_priv_handler)(char *extra);

#define IN
#define OUT

#define TMR_NAME_SIZE     16//OS_TMR_CFG_NAME_SIZE //CJ_MASK

#define ATOMIC_T atomic_t
#define HZ			10000000
#define jiffies 	0
#define   KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
/* emulate a modern version */
#define LINUX_VERSION_CODE KERNEL_VERSION(2, 6, 17)

#define LIST_CONTAINOR(ptr, type, member) \
	((type *)((char *)(ptr)-(SIZE_T)((char *)&((type *)ptr)->member - (char *)ptr)))
#define container_of(p,t,n) (t*)((p)-&(((t*)0)->n))

#define RTK_TASK_START_PRIO 	37//prio 37.38.39 is for wifi module
#define RTK_TASK_INVALID_PRIO   255;
#define TASK_PRORITY_LOW  				2
#define TASK_PRORITY_MIDDLE   			1
#define TASK_PRORITY_HIGH    			0
#if (defined(CONFIG_PLATFORM_MSTAR_MSC8339) && defined(CONFIG_HIGH_TP))
#define TASK_PRORITY_RX			(-12) //set rx prio to 25 for throughput test
#endif

#define TIMER_MAX_DELAY    				0xFFFFFFFF

// rtl8195a uses receive_tasklet for wps
// 8189em uses interrupt_thread for wps 
#if defined(CONFIG_WPS) 
#define RECV_STACK_FOR_WPS 448//512//384 //Change to 512 for WPS (IAR STM32) stack overflow
#else
#define RECV_STACK_FOR_WPS 0
#endif

#ifdef CONFIG_DONT_CARE_TP
#define XMIT_STACKSIZE		192 //256
#define CMD_STACKSIZE		384 //512 
#else
#define XMIT_STACKSIZE		256
#define CMD_STACKSIZE		512 //1024
#endif //CONFIG_DONT_CARE_TP

#ifdef CONFIG_INCLUDE_WPA_PSK
#if PSK_SUPPORT_TKIP
#define RECV_STACKSIZE		(512 + 256 + 128 + RECV_STACK_FOR_WPS)
#else
#define RECV_STACKSIZE		(512 + 256 + RECV_STACK_FOR_WPS )
#endif
#else
#define RECV_STACKSIZE		(512 + 256 + RECV_STACK_FOR_WPS)	//Can be reduced
#endif

#define TASKLET_STACKSIZE	(1024 + RECV_STACK_FOR_WPS)
#define SDIOXMIT_STACKSIZE	256


#if 0
__inline static _list *get_next(_list	*list)
{
	return list->next;
}	

__inline static _list	*get_list_head(_queue	*queue)
{
	return (&(queue->queue));
}
#endif
struct rtw_netdev_priv_indicator {
	void *priv;
	u32 sizeof_priv;
};

#define rtw_netdev_priv(netdev) ( ((struct rtw_netdev_priv_indicator *)netdev_priv(netdev))->priv )

#define FUNC_NDEV_FMT "%s"
#define FUNC_NDEV_ARG(ndev) __func__

void save_and_cli(void);
void restore_flags(void);
void cli(void);

//----- ------------------------------------------------------------------
// Common Definition
//----- ------------------------------------------------------------------

#define __init
#define __exit
#define __devinit
#define __devexit

#define KERN_ERR
#define KERN_INFO
#define KERN_NOTICE

#define GFP_KERNEL			1
#define GFP_ATOMIC			1

#define SET_MODULE_OWNER(some_struct)	do { } while (0)
#define SET_NETDEV_DEV(dev, obj)	do { } while (0)
#define register_netdev(dev)		(0)
#define unregister_netdev(dev)		do { } while (0)
#define netif_queue_stopped(dev)	(0)
#define netif_wake_queue(dev)		do { } while (0)
#define printk				printc
#define printf				printc
#define DBG_ERR	printc
#if WLAN_INTF_DBG
#define DBG_TRACE	printc
#define DBG_INFO	printc
#else
#define DBG_TRACE
#define DBG_INFO
#endif

#define HALT()				do { cli(); for(;;);} while(0)
#ifndef ASSERT 
#define ASSERT(exp) \
		do { if (!(exp)) osl_assert(#exp, __FILE__, __LINE__); } while (0)
#endif
#undef DBG_ASSERT
#define DBG_ASSERT(x, msg)		do { \
						if((x) == 0) \
							printc("\n\r%s, Assert(" #x ") failed on line %d in file %s", msg, __LINE__, __FILE__); \
					} while(0)

#ifdef __func__
#define __RTL_FUNC__	__func__
#elif defined __FUNC__
#define __RTL_FUNC__	__FUNC__
#elif defined __function__
#define __RTL_FUNC__	__function__
#elif defined __FUNCTION__
#define __RTL_FUNC__	__FUNCTION__
#else
#define __STRINGIFY(x) #x
#define __STRINGIFY_2(x) __STRINGIFY(x)
#define __FUNCTION__	__func__
#define __RTL_FUNC__	__FUNCTION__
#endif

//----- ------------------------------------------------------------------
// Atomic Operation
//----- ------------------------------------------------------------------

/*
 * atomic_read - read atomic variable
 * @v: pointer of type atomic_t
 *
 * Atomically reads the value of @v.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
#define atomic_read(v)  ((v)->counter)

/*
 * atomic_set - set atomic variable
 * @v: pointer of type atomic_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.  Note that the guaranteed
 * useful range of an atomic_t is only 24 bits.
 */
#define atomic_set(v,i) ((v)->counter = (i))

 /*
  *      These inlines deal with timer wrapping correctly. You are 
  *      strongly encouraged to use them
  *      1. Because people otherwise forget
  *      2. Because if the timer wrap changes in future you wont have to
  *         alter your driver code.
  *
  * time_after(a,b) returns true if the time a is after time b.
  *
  * Do this with "<0" and ">=0" to only test the sign of the result. A
  * good compiler would generate better code (and a really good compiler
  * wouldn't care). Gcc is currently neither.
  */
 #define time_after(a,b)	((long)(b) - (long)(a) < 0)
 #define time_before(a,b)	time_after(b,a)
  
 #define time_after_eq(a,b)	((long)(a) - (long)(b) >= 0)
 #define time_before_eq(a,b)	time_after_eq(b,a)

#if 0//YAN_MASK
//list
typedef struct list_head
{
	struct	list_head *prev, *next;
}_list;
#endif
//lock and semaphore
typedef struct semaphore{
#ifdef CONFIG_PLATFORM_MSTAR_MSC8339
	osl_ext_sem_t rtk_osl_sem;
#else
	OS_EVENT *pucosii_event;
#endif
	//unsigned char event_name[64];
}_lock,_sema,_mutex;

typedef void* osl_ext_task_arg_t;

//timer  must revise later
typedef struct rtk_timer_list {
	osl_ext_timer_t rtk_timer_id;
	unsigned char timer_name[TMR_NAME_SIZE];
	osl_ext_timer_callback callback;
	osl_ext_timer_arg_t context;
	osl_ext_timer_mode_t opt;
} _timer;

#if 0
struct	__queue	{
	struct	list_head	queue;
	_lock			lock;
};

typedef struct	__queue		_queue;
#endif

#if 0//ndef CONFIG_PLATFORM_MSTAR_MSC8339
struct list_head {
	struct list_head *next, *prev;
};
#endif
struct	__queue	{
	struct	list_head	queue;
	_lock			lock;
};

typedef struct	__queue		_queue;
typedef struct	list_head	_list;

extern _list *get_next(_list	*list);
extern _list	*get_list_head(_queue	*queue);
extern void	rtw_init_listhead(_list *list);
extern u32	rtw_is_list_empty(_list *phead);
extern void	rtw_list_insert_head(_list *plist, _list *phead);
extern void	rtw_list_insert_tail(_list *plist, _list *phead);
extern void	rtw_list_delete(_list *plist);
typedef int spinlock_t;

#endif

