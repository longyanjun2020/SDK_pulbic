#ifndef ONCE_HAL_DRV_API_H
#define ONCE_HAL_DRV_API_H

////////////////////////////////////////////////////////////////////////////////
///@file hal_drv_api.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_hal.h>
#include <infra_type.h>

#include "vm_types.ht"
#include "mdl_efat_pub.h"
#include "sys_MsWrapper_cus_os_sem.h"
#ifndef nomips16
#define nomips16
#endif

#ifndef efat_sem_t
#define efat_sem_t                   MsSemId_e
#endif
#ifndef efat_mutex_t
#define efat_mutex_t                 MsSemId_e
#endif
#ifndef efat_count32
#define efat_count32                 int
#endif



#ifndef efat_cond_t
#define efat_cond_t  rtk_cond2_t
#endif

#ifdef PKG_KERNEL

/*------------------------------------------------------------------------*/
/* Kernel co-resident version of API                                      */

#include <pkgconf_kernel.h>

#ifndef FUN_KERNEL_API_C
//#error Driver API requres Kernel API to be present
#endif

#include <kernel_kapi.h>

#define efat_drv_mutex_t                     efat_mutex_t
#define efat_drv_mutex_init                  efat_mutex_init
#define efat_drv_mutex_lock                  efat_mutex_lock
#define efat_drv_mutex_unlock                efat_mutex_unlock

#define efat_drv_cond_t                      efat_cond_t
#define efat_drv_cond_init                   efat_cond_init
#define efat_drv_cond_wait                   efat_cond_wait
#define efat_drv_cond_broadcast              efat_cond_broadcast

#define efat_drv_interrupt_create            efat_interrupt_create

#define efat_drv_spinlock_t                  efat_spinlock_t

#else /* PKG_KERNEL */

/*------------------------------------------------------------------------*/
/* Non-kernel version of API                                              */

typedef EFAT_ADDRWORD efat_addrword_t;        /* May hold pointer or word   */
typedef efat_addrword_t efat_handle_t;        /* Object handle              */
typedef efat_uint32   efat_priority_t;        /* type for priorities        */
typedef efat_uint32   efat_vector_t;          /* Interrupt vector id        */
typedef efat_uint32   efat_cpu_t;             /* CPU id                     */
typedef int          efat_bool_t;
typedef efat_int32    efat_code_t;            /* type for various codes     */

#if 0

typedef efat_uint32 efat_ISR_t( efat_vector_t vector, efat_addrword_t data);
typedef void efat_DSR_t(efat_vector_t vector, efat_ucount32 count, efat_addrword_t data);
externC void efat_drv_isr_lock(void);
externC void efat_drv_isr_unlock(void);
externC void efat_drv_dsr_lock(void);
externC void efat_drv_dsr_unlock(void);

externC void efat_drv_mutex_init( efat_drv_mutex_t *mutex );
externC efat_bool_t efat_drv_mutex_lock( efat_drv_mutex_t *mutex );
externC void efat_drv_mutex_unlock( efat_drv_mutex_t *mutex );
externC void efat_drv_cond_init( efat_drv_cond_t  *cond, efat_drv_mutex_t *mutex );
externC efat_bool_t efat_drv_cond_wait( efat_drv_cond_t *cond );
externC void efat_drv_cond_broadcast( efat_drv_cond_t *cond );

typedef struct efat_interrupt
{
    efat_vector_t        vector;
    efat_priority_t      priority;
    efat_ISR_t           *isr;
    efat_DSR_t           *dsr;
    EFAT_ADDRWORD        data;

    struct efat_interrupt* volatile next_dsr;
    volatile efat_int32             dsr_count;

#ifdef IMP_HAL_COMMON_INTERRUPTS_CHAIN
    struct efat_interrupt *next;
#endif

} efat_interrupt;

externC void efat_drv_interrupt_create(
                     efat_vector_t        vector,
                     efat_priority_t      priority,
                     efat_addrword_t      data,
                     efat_ISR_t           *isr,
                     efat_DSR_t           *dsr,
                     efat_handle_t        *handle,
                     efat_interrupt       *intr
                     );

enum efat_ISR_results
{
    EFAT_ISR_HANDLED  = 1,               /* Interrupt was handled             */
    EFAT_ISR_CALL_DSR = 2                /* Schedule DSR                      */
};


typedef struct
{
    efat_atomic          lock;
} efat_drv_spinlock_t;

#endif

#endif /* PKG_KERNEL */

/*------------------------------------------------------------------------*/
/* EOF drv_api.h                                                          */
#endif // ONCE_HAL_DRV_API_H

