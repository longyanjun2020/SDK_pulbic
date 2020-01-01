//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#ifndef _OS_API_H_
#define _OS_API_H_

#include "hal_usbhost.h" // import hal definition

#ifdef KERNEL_OS_RTK
#include <MsCommon.h>
#include <MsOS.h>
#include <string.h> // for mem*
#else // eCos
#include <MsCommon.h>
/* Note, include for kernel service functions of eCos */
#include <cyg/hal/hal_misc.h> // for BITn
#include <cyg/hal/hal_diag.h>
#endif
#include "drvTypes.h"

#ifdef KERNEL_OS_RTK
extern signed char UartSendTrace(const char *strFormat, ...);
#define diag_printf UartSendTrace
#endif

/*** Timer management ***/
/* Delay routines */
#define mdelay(x)  MsOS_DelayTask(x)
#ifndef HAL_DELAY_US
#ifdef KERNEL_OS_RTK
    extern void DrvTimerUdelay(unsigned int us);
    #define hal_delay_us(us) DrvTimerUdelay(us)
    #define HAL_DELAY_US(n)    hal_delay_us(n)
#else
    externC void hal_delay_us(int us);
    #define HAL_DELAY_US(n)    hal_delay_us(n)
#endif
#endif

/*** Interrupt management ***/
#define IRQ_NONE              0
#define IRQ_HANDLED           1
#define TASK_UNINTERRUPTIBLE  0
/* ========================================  Data structures  ======================================== */

#define SPIN_LOCK_UNLOCKED  (spinlock_t)0
#define SPIN_LOCK_LOCKED    (spinlock_t)1

/* ========================================  Function Declaration  ======================================== */
extern void UHC_AttachInterrupt(InterruptNum eIntNum, void *func);
extern void UHC_DetachInterrupt(InterruptNum eIntNum);
extern void UHC_EnableInterrupt(InterruptNum eIntNum);
extern void UHC_DisableInterrupt(InterruptNum eIntNum);
extern int UHC_DisableAllInterrupts(void);
extern void UHC_RestoreAllInterrupts(int eIntNum);
extern void UHC_DisAllInterrupts(void);
extern void UHC_EnAllInterrupts(void);

#define DECLARE_WAITQUEUE(x,y)
#define init_waitqueue_head(x)
#define add_wait_queue(x,y)
#define remove_wait_queue(x,y)
#define wake_up(x)
#define signal_pending(x)     0

/* Spin lock functions */
#define osapi_spin_lock_init(lock)
#define osapi_spin_lock(lock)
#define osapi_spin_unlock(lock)
/* RTK not support xxx_DisableAllInterrupts() and xxx_RestoreAllInterrupts() */
#define osapi_spin_lock_irqsave(lock,flag)      {flag = UHC_DisableAllInterrupts();}
#define osapi_spin_unlock_irqrestore(lock,flag) UHC_RestoreAllInterrupts(flag)
#define osapi_spin_lock_irq(lock) UHC_DisAllInterrupts()
#define osapi_spin_unlock_irq(lock) UHC_EnAllInterrupts()

/* Semaphore functions */
#define osapi_up(x)
#define osapi_down(x)

/* Mutex functions */
#define osapi_mutex_init(x, str) \
	x = MsOS_CreateMutex(E_MSOS_FIFO, str, MSOS_PROCESS_SHARED)
#define osapi_mutex_lock(x)\
	MsOS_ObtainMutex(x, MSOS_WAIT_FOREVER)
#define osapi_mutex_unlock(x) \
	MsOS_ReleaseMutex(x)
#define osapi_mutex_delete(x) \
	MsOS_DeleteMutex(x)
//#define osapi_init_MUTEX(x) // NUSED
//#define osapi_init_MUTEX_LOCKED(x) // NUSED

/* Kernel function porting (Unsupport now, so just skip) */
#define set_current_state(x)
//#define osapi_local_irq_restore(x) // NUSED
//#define osapi_local_irq_save(x) // NUSED
//#define osapi_local_irq_disable() // NUSED
//#define osapi_local_irq_enable() // NUSED
//#define osapi_lock_kernel() // NUSED
//#define osapi_unlock_kernel() // NUSED
//#define osapi_schedule() // NUSED

#define osapi_atomic_read(v)        (v)->counter
static __inline__ void osapi_atomic_inc(atomic_t *cnt_p)
{
	(cnt_p->counter)++;
}

static __inline__ void osapi_atomic_dec(atomic_t *cnt_p)
{
	(cnt_p->counter)--;
}

static __inline__ int osapi_atomic_dec_and_test(atomic_t *count)
{
	(count->counter)--;
	return (count->counter == 0);
}

static __inline__ void osapi_atomic_set(atomic_t *count, int value)
{
	(count->counter) = value;
}

static __inline__ void osapi_schedule_timeout(int ms)
{
	mdelay(ms);
}

/*** Memory management ***/
#ifdef KERNEL_OS_RTK
extern void sys_Invalidate_data_cache(void);
extern void sys_Clean_and_flush_data_cache_buffer(unsigned int addr, int size);
inline static void Chip_Dcache_Flush(U32 addr, U32 sz)
{
	sys_Clean_and_flush_data_cache_buffer(addr, sz);
	sys_Invalidate_data_cache();
}
inline static void Chip_Dcache_Invalidate(U32 addr, U32 sz)
{
	/* already done at Chip_Read_Memory */
}
extern void HalAxiChipFlushMiuPipe(void);
extern void sys_Invalidate_data_cache(void);
inline static void Chip_Flush_Memory(void)
{
	HalAxiChipFlushMiuPipe();
}
inline static void Chip_Read_Memory(void)
{
	Chip_Flush_Memory();
	sys_Invalidate_data_cache();
}

#else // eCos
inline static void Chip_Dcache_Flush(U32 addr, U32 sz)
{
	MsOS_Dcache_Flush(addr, sz);
}
inline static void Chip_Dcache_Invalidate(U32 addr, U32 sz)
{
	MsOS_Dcache_Invalidate(addr, sz);
}
extern void MsOS_FlushMemory(void);
extern void MsOS_ReadMemory(void);
inline void Chip_Flush_Memory(void)
{
	MsOS_FlushMemory();
}
inline void Chip_Read_Memory(void)
{
	MsOS_ReadMemory();
}
#endif

#endif
