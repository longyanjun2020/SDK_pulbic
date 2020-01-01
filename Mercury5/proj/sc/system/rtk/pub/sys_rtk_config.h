#ifndef __SYS_RTK_CONFIG_H__
#define __SYS_RTK_CONFIG_H__

/*!
 *    \file sys_rtk_config.h
 *
 *    constants that defines the configuration of rtk
 *
 */

#define  __RTK_MEMORY_ALIGN32__

/*!
 *    \brief defines the maximum number of tasks
 *
 */
#define RTK_MAX_TASKS 200

/*!
 *    \brief max priority value ( all tasks priorities have to be lower or equal than this one )
 *
 */
#define RTK_MAX_TASK_PRIORITY RTK_MAX_TASKS

/*!
 *    \brief count of reserved system tasks
 */
#ifndef __MSTAR_DUAL_SIM__
#define RTK_MAX_SYSTEM_TASKS  40
#else
#define RTK_MAX_SYSTEM_TASKS  50
#endif

/*!
 *    \brief count of reserved customer tasks
 */
#define RTK_MAX_CUSTOMER_TASKS (RTK_MAX_TASKS - RTK_MAX_SYSTEM_TASKS)

/*!
 *    \brief first customer task identifier
 */
#define RTK_FIRST_CUSTOMER_TASKID RTK_MAX_SYSTEM_TASKS


/*!
 *    \brief defines the maximum number of mailboxes
 *
 */
#define RTK_MAX_MAILBOXES 200

/*!
 *    \brief first customer mailbox id 
 *    each customer task is associated to a customer mailbox
 */
#ifndef __MSTAR_DUAL_SIM__
#define RTK_FIRST_CUSTOMER_MAILBOXID 40
#else
#define RTK_FIRST_CUSTOMER_MAILBOXID 50
#endif

#define RTK_MAX_SYSTEM_MBOXS		RTK_FIRST_CUSTOMER_MAILBOXID
#define RTK_MAX_CUSTOMER_MBOXS	(RTK_MAX_MAILBOXES - RTK_MAX_SYSTEM_MBOXS)

// check the current configuration

#if ((RTK_FIRST_CUSTOMER_MAILBOXID+RTK_MAX_CUSTOMER_TASKS) > RTK_MAX_MAILBOXES)

#error not enough mailboxes for the customer tasks

#endif


// length in bytes of the task state bitmap array
#define RTK_TASKS_BITMAP_LENGTH ((RTK_MAX_TASKS+7)/8)

#ifdef __RTK_DIAGNOSE_ENHANCE__
#define RTK_IRQ_MODE	0x12
#define RTK_FIQ_MODE	0x11
#endif
#define RTK_TIMER_DYNAMIC_COMPENSATE_EN	(1)
#define RTK_CPU_LOADING_EN				(0)
#define RTK_MAX_TASK_TIMEOUT_COUNT  	(0x2000) /*8,192*/
#define RTK_MAX_TASK_TIMEOUT_DISABLE 	(0xFFFFFFFF)
#endif // __SYS_RTK_CONFIG_H__

