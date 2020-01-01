#ifndef ONCE_KERNEL_KAPI_H
#define ONCE_KERNEL_KAPI_H
////////////////////////////////////////////////////////////////////////////////
///@file kernel_kapi.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


#include <pkgconf_system.h>
#include <pkgconf_kernel.h>

#ifdef FUN_KERNEL_API_C
#include <infra_type.h>

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/
/* The following are derived types, they may have different                  */
/* definitions from these depending on configuration.                        */

typedef EFAT_ADDRWORD   efat_addrword_t;      /* May hold pointer or word      */
typedef efat_addrword_t efat_handle_t;        /* Object handle                 */
typedef efat_uint32     efat_priority_t;      /* type for priorities           */
typedef efat_int32      efat_code_t;          /* type for various codes        */
typedef efat_uint32     efat_vector_t;        /* Interrupt vector id           */
typedef efat_uint32     efat_cpu_t;           /* CPU id type                   */

typedef efat_uint64 efat_tick_count_t;

typedef int efat_bool_t;
#if 0

/* Exception handler function definition                                     */
typedef void efat_exception_handler_t(
    efat_addrword_t data,
    efat_code_t   exception_number,
    efat_addrword_t info
);

/*---------------------------------------------------------------------------*/
struct efat_thread;
typedef struct efat_thread efat_thread;

struct efat_interrupt;
typedef struct efat_interrupt efat_interrupt;

struct efat_counter;
typedef struct efat_counter efat_counter;

struct efat_clock;
typedef struct efat_clock efat_clock;

struct efat_alarm;
typedef struct efat_alarm efat_alarm;

struct efat_mbox;
typedef struct efat_mbox efat_mbox;
#if 0
struct efat_sem_t;
typedef struct efat_sem_t efat_sem_t;
#endif
struct efat_flag_t;
typedef struct efat_flag_t efat_flag_t;

#if 0
struct efat_mutex_t;
typedef struct efat_mutex_t efat_mutex_t;

struct efat_cond_t;
typedef struct efat_cond_t efat_cond_t;
#endif

struct efat_spinlock_t;
typedef struct efat_spinlock_t efat_spinlock_t;

/*---------------------------------------------------------------------------*/

void efat_scheduler_start(void) __THROW ;
void efat_scheduler_lock(void) __THROW;
void efat_scheduler_unlock(void) __THROW;
void efat_scheduler_safe_lock(void) __THROW;
efat_ucount32 efat_scheduler_read_lock(void) __THROW;

/*---------------------------------------------------------------------------*/

typedef void efat_thread_entry_t(efat_addrword_t);

void efat_thread_create(
    efat_addrword_t      sched_info,             /* scheduling info (eg pri)  */
    efat_thread_entry_t  *entry,                 /* entry point function      */
    efat_addrword_t      entry_data,             /* entry data                */
    char                *name,                  /* optional thread name      */
    void                *stack_base,            /* stack base, NULL = alloc  */
    efat_ucount32        stack_size,             /* stack size, 0 = default   */
    efat_handle_t        *handle,                /* returned thread handle    */
    efat_thread          *thread                 /* put thread here           */
) __THROW;

void efat_thread_exit(void) __THROW;

/* It may be necessary to arrange for the victim to run for it to disappear */
void efat_thread_kill(efat_handle_t thread) __THROW;
void efat_thread_release(efat_handle_t thread) __THROW;
void efat_thread_yield(void) __THROW;
efat_handle_t efat_thread_self(void) __THROW;
efat_handle_t efat_thread_idle_thread(void) __THROW;

efat_bool_t efat_thread_delete(efat_handle_t thread) __THROW; /* false if NOT deleted */
efat_bool_t efat_thread_check_exit(efat_handle_t thread) __THROW; /* false if NOT deleted */
void efat_thread_suspend(efat_handle_t thread) __THROW;
void efat_thread_resume(efat_handle_t thread) __THROW;

/* Priority manipulation */

void efat_thread_set_priority(efat_handle_t thread, efat_priority_t priority ) __THROW;

efat_priority_t efat_thread_get_priority(efat_handle_t thread) __THROW;
efat_priority_t efat_thread_get_current_priority(efat_handle_t thread) __THROW;

/* Deadline scheduling control (optional) */

void efat_thread_deadline_wait(
    efat_tick_count_t    start_time,             /* abs earliest start time   */
    efat_tick_count_t    run_time,               /* worst case execution time */
    efat_tick_count_t    deadline                /* absolute deadline         */
) __THROW;

/* Stack information */
efat_addrword_t efat_thread_get_stack_base(efat_handle_t thread) __THROW;

efat_uint32 efat_thread_get_stack_size(efat_handle_t thread) __THROW;

#ifdef FUN_KERNEL_THREADS_STACK_MEASUREMENT
efat_uint32 efat_thread_measure_stack_usage(efat_handle_t thread) __THROW;
#endif

/*---------------------------------------------------------------------------*/
/* Thread enumeration and information                                        */

typedef struct
{
    efat_handle_t        handle;
    efat_uint16          id;
    efat_uint32          state;
    char                *name;
    efat_priority_t      set_pri;
    efat_priority_t      cur_pri;
    efat_addrword_t      stack_base;
    efat_uint32          stack_size;
    efat_uint32          stack_used;
} efat_thread_info;

efat_bool_t efat_thread_get_next( efat_handle_t *thread, efat_uint16 *id ) __THROW;
efat_uint16 efat_thread_get_id( efat_handle_t thread ) __THROW;

efat_handle_t efat_thread_find( efat_uint16 id ) __THROW;

efat_bool_t efat_thread_get_info( efat_handle_t thread,
                                efat_uint16 id,
                                efat_thread_info *info ) __THROW;



/*---------------------------------------------------------------------------*/
/* Per-thread Data                                                           */

#ifdef VAR_KERNEL_THREADS_DATA
EFAT_ADDRWORD efat_thread_get_data(efat_ucount32 index) __THROW;

EFAT_ADDRWORD *efat_thread_get_data_ptr(efat_ucount32 index) __THROW;

void efat_thread_set_data(efat_ucount32 index, EFAT_ADDRWORD data) __THROW;

efat_ucount32 efat_thread_new_data_index(void) __THROW;

void efat_thread_free_data_index(efat_ucount32 index) __THROW;

#endif

/*---------------------------------------------------------------------------*/
/* Thread destructors                                                        */

#ifdef PKG_KERNEL_THREADS_DESTRUCTORS

typedef void (*efat_thread_destructor_fn)(efat_addrword_t);
efat_bool_t efat_thread_rem_destructor( efat_thread_destructor_fn fn,
                                      efat_addrword_t data ) __THROW;

efat_bool_t efat_thread_add_destructor( efat_thread_destructor_fn fn,
                                      efat_addrword_t data ) __THROW;

#endif

/*---------------------------------------------------------------------------*/




/* Clear exception hander to default value                                   */
void efat_exception_clear_handler(
    efat_code_t                  exception_number
) __THROW;

void efat_exception_set_handler(
    efat_code_t                  exception_number,
    efat_exception_handler_t     *new_handler,
    efat_addrword_t                new_data,
    efat_exception_handler_t     **old_handler,
    efat_addrword_t                *old_data
) __THROW;

/* Invoke exception handler                                                  */
void efat_exception_call_handler(
    efat_handle_t                thread,
    efat_code_t                  exception_number,
    efat_addrword_t              exception_info
) __THROW;


/*---------------------------------------------------------------------------*/
/* Interrupt handling                                                        */
typedef void            efat_VSR_t(void);
typedef efat_uint32      efat_ISR_t(efat_vector_t vector, efat_addrword_t data);
typedef void            efat_DSR_t( efat_vector_t vector,
                                   efat_ucount32 count,
                                   efat_addrword_t data);


enum efat_ISR_results
{
    EFAT_ISR_HANDLED  = 1,               /* Interrupt was handled             */
    EFAT_ISR_CALL_DSR = 2                /* Schedule DSR                      */
};

void efat_interrupt_create(
    efat_vector_t        vector,         /* Vector to attach to               */
    efat_priority_t      priority,       /* Queue priority                    */
    efat_addrword_t      data,           /* Data pointer                      */
    efat_ISR_t           *isr,           /* Interrupt Service Routine         */
    efat_DSR_t           *dsr,           /* Deferred Service Routine          */
    efat_handle_t        *handle,        /* returned handle                   */
    efat_interrupt       *intr           /* put interrupt here                */
) __THROW;
void efat_interrupt_attach( efat_handle_t interrupt ) __THROW;

void efat_interrupt_detach( efat_handle_t interrupt ) __THROW;

void efat_interrupt_delete( efat_handle_t interrupt ) __THROW;

/* VSR manipulation */
void efat_interrupt_set_vsr(
    efat_vector_t        vector,         /* vector to set                     */
    efat_VSR_t           *vsr            /* vsr to set                        */
) __THROW;

void efat_interrupt_get_vsr(
    efat_vector_t        vector,         /* vector to get                     */
    efat_VSR_t           **vsr           /* vsr got                           */
) __THROW;



/* CPU level interrupt mask                                                  */
void efat_interrupt_disable(void) __THROW;

void efat_interrupt_enable(void) __THROW;

/* Interrupt controller access                                               */

void efat_interrupt_unmask(efat_vector_t vector) __THROW;
void efat_interrupt_unmask_intunsafe(efat_vector_t vector) __THROW;

void efat_interrupt_mask(efat_vector_t vector) __THROW;
void efat_interrupt_mask_intunsafe(efat_vector_t vector) __THROW;

void efat_interrupt_acknowledge(efat_vector_t vector) __THROW;

void efat_interrupt_set_cpu(
    efat_vector_t        vector,         /* vector to control                 */
    efat_cpu_t           cpu             /* CPU to set                        */
) __THROW;

void efat_interrupt_configure(
    efat_vector_t        vector,         /* vector to configure               */
    efat_bool_t          level,          /* level or edge triggered           */
    efat_bool_t          up              /* rising/faling edge, high/low level*/
) __THROW;

efat_cpu_t efat_interrupt_get_cpu(
    efat_vector_t        vector          /* vector to control                 */
) __THROW;

/*---------------------------------------------------------------------------*/
/* Counters, Clocks and Alarms                                               */

void efat_counter_create(
    efat_handle_t        *handle,        /* returned counter handle           */
    efat_counter         *counter        /* put counter here                  */
) __THROW;

void efat_counter_delete(efat_handle_t counter) __THROW;

/* Return current value of counter                                           */
efat_tick_count_t efat_counter_current_value(efat_handle_t counter) __THROW;

/* Set new current value                                                     */
void efat_counter_set_value(
    efat_handle_t        counter,
    efat_tick_count_t new_value
) __THROW;

/* Advance counter by one tick                                               */
void efat_counter_tick(efat_handle_t counter) __THROW;

/* Advance counter by multiple ticks                                         */
void efat_counter_multi_tick(efat_handle_t counter, efat_tick_count_t _ticks) __THROW;


#define EFAT_RESOLUTION_T_MEMBERS  \
    efat_uint32  dividend;         \
    efat_uint32  divisor;

typedef struct
{
    EFAT_RESOLUTION_T_MEMBERS
} efat_resolution_t;


void efat_clock_delete(efat_handle_t clock) __THROW;

/* Create a clock object                */
void efat_clock_create(
    efat_resolution_t    resolution,     /* Initial resolution                */
    efat_handle_t        *handle,        /* Returned clock handle             */
    efat_clock           *clock          /* put clock here                    */
) __THROW;



/* convert a clock handle to a counter handle so we can use the              */
/* counter API on it.                                                        */

void efat_clock_set_resolution(
    efat_handle_t        clock,
    efat_resolution_t    resolution      /* New resolution                    */
) __THROW;

void efat_clock_to_counter(
    efat_handle_t        clock,
    efat_handle_t        *counter
) __THROW;



efat_resolution_t efat_clock_get_resolution(efat_handle_t clock) __THROW;

/* handle of real time clock                                                 */
efat_handle_t efat_real_time_clock(void) __THROW;

/* returns value of real time clock's counter.
   This is the same as:
   (efat_clock_to_counter(efat_real_time_clock(), &h),
    efat_counter_current_value(h))                                            */
efat_tick_count_t efat_current_time(void) __THROW;

/* Alarm handler function                                                    */
typedef void efat_alarm_t(efat_handle_t alarm, efat_addrword_t data);

void efat_alarm_create(
    efat_handle_t        counter,        /* Attached to this counter          */
    efat_alarm_t         *alarmfn,       /* Call-back function                */
    efat_addrword_t      data,           /* Call-back data                    */
    efat_handle_t        *handle,        /* Returned alarm object             */
    efat_alarm           *alarm          /* put alarm here                    */
) __THROW;

/* Disable alarm, detach from counter and invalidate handles                 */

void efat_alarm_initialize(
    efat_handle_t        alarm,
    efat_tick_count_t    trigger,        /* Absolute trigger time             */
    efat_tick_count_t    interval        /* Relative retrigger interval       */
) __THROW;

void efat_alarm_delete( efat_handle_t alarm) __THROW;



void efat_alarm_get_times(
    efat_handle_t        alarm,
    efat_tick_count_t    *trigger,       /* Next trigger time                 */
    efat_tick_count_t    *interval       /* Current interval                  */
) __THROW;

void efat_alarm_enable( efat_handle_t alarm ) __THROW;

void efat_alarm_disable( efat_handle_t alarm ) __THROW;

/*---------------------------------------------------------------------------*/
/* Mail boxes                                                                */
void efat_mbox_create(
    efat_handle_t        *handle,
    efat_mbox            *mbox
) __THROW;

void efat_mbox_delete(efat_handle_t mbox) __THROW;

void *efat_mbox_get(efat_handle_t mbox) __THROW;

#ifdef FUN_KERNEL_THREADS_TIMER
void *efat_mbox_timed_get(
    efat_handle_t mbox,
    efat_tick_count_t abstime
    ) __THROW;
#endif

void *efat_mbox_tryget(efat_handle_t mbox) __THROW;

void *efat_mbox_peek_item(efat_handle_t mbox) __THROW;

#ifdef MFN_KERNEL_SYNCH_MBOXT_PUT_CAN_WAIT
efat_bool_t efat_mbox_put(efat_handle_t mbox, void *item) __THROW;
#ifdef FUN_KERNEL_THREADS_TIMER
efat_bool_t efat_mbox_timed_put(
    efat_handle_t mbox,
    void *item,
    efat_tick_count_t abstime
    ) __THROW;
#endif
#endif

efat_bool_t efat_mbox_tryput(efat_handle_t mbox, void *item) __THROW;

efat_count32 efat_mbox_peek(efat_handle_t mbox) __THROW;

efat_bool_t efat_mbox_waiting_to_get(efat_handle_t mbox) __THROW;

efat_bool_t efat_mbox_waiting_to_put(efat_handle_t mbox) __THROW;


/*-----------------------------------------------------------------------*/
/* Memory pools                                                          */

/* These definitions are found in the "memalloc" package as this is      */
/* where the implementation lives.                                       */

#ifdef PKG_MEMALLOC
#endif

/*---------------------------------------------------------------------------*/
/* Semaphores                                                                */

void      efat_semaphore_init(
    efat_sem_t           *sem,            /* Semaphore to init                */
    efat_count32         val              /* Initial semaphore value          */
) __THROW;

void efat_semaphore_destroy( efat_sem_t *sem ) __THROW;

efat_bool_t efat_semaphore_wait( efat_sem_t *sem ) __THROW;

#ifdef FUN_KERNEL_THREADS_TIMER
efat_bool_t efat_semaphore_timed_wait(
    efat_sem_t          *sem,
    efat_tick_count_t   abstime
    ) __THROW;
#endif

efat_bool_t efat_semaphore_trywait( efat_sem_t *sem ) __THROW;

void efat_semaphore_post( efat_sem_t *sem ) __THROW;

void efat_semaphore_peek( efat_sem_t *sem, efat_count32 *val ) __THROW;

/*---------------------------------------------------------------------------*/
/* Flags                                                                     */

typedef efat_uint32 efat_flag_value_t;
typedef efat_uint8  efat_flag_mode_t;
#define EFAT_FLAG_WAITMODE_AND ((efat_flag_mode_t)0) /* all bits must be set */
#define EFAT_FLAG_WAITMODE_OR  ((efat_flag_mode_t)2) /* any bit must be set  */
#define EFAT_FLAG_WAITMODE_CLR ((efat_flag_mode_t)1) /* clear when satisfied */

#endif

/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

/*---------------------------------------------------------------------------*/
#include <kernel_kapidata.h>

/*---------------------------------------------------------------------------*/
/* EOF kapi.h                                                                */
#endif /* FUN_KERNEL_API_C   */
#endif /* ONCE_KERNEL_KAPI_H */

