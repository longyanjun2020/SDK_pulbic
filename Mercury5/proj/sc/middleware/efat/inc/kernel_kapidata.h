#ifndef ONCE_KERNEL_KAPIDATA_H
#define ONCE_KERNEL_KAPIDATA_H
////////////////////////////////////////////////////////////////////////////////
///@file kernel_kapidata.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <pkgconf_kernel.h>
#include <infra_type.h>
//#include <hal_hal_intr.h>           // exception defines

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/

#ifndef NUM_KERNEL_SCHED_BITMAP_SIZE
#if defined(SEM_KERNEL_SCHED_MLQUEUE)
#define NUM_KERNEL_SCHED_BITMAP_SIZE 32
#elif defined(SEM_KERNEL_SCHED_BITMAP)
#define NUM_KERNEL_SCHED_BITMAP_SIZE 32
#endif
#endif

#if NUM_KERNEL_SCHED_BITMAP_SIZE <= 8
typedef efat_ucount8 efat_sched_bitmap;
#elif NUM_KERNEL_SCHED_BITMAP_SIZE <= 16
typedef efat_ucount16 efat_sched_bitmap;
#elif NUM_KERNEL_SCHED_BITMAP_SIZE <= 32
typedef efat_ucount32 efat_sched_bitmap;
#elif NUM_KERNEL_SCHED_BITMAP_SIZE <= 64
typedef efat_ucount8 efat_sched_bitmap;
#define IMP_KERNEL_SCHED_TWO_LEVEL_BITMAP
#define NUM_KERNEL_SCHED_BITMAP2_SIZE 	8
#define NUM_KERNEL_SCHED_BITMAP2_SHIFT	3
#define NUM_KERNEL_SCHED_BITMAP2_MASK	0x07
#elif NUM_KERNEL_SCHED_BITMAP_SIZE <= 256
typedef efat_ucount16 efat_sched_bitmap;
#define IMP_KERNEL_SCHED_TWO_LEVEL_BITMAP
#define NUM_KERNEL_SCHED_BITMAP2_SIZE 	16
#define NUM_KERNEL_SCHED_BITMAP2_SHIFT	4
#define NUM_KERNEL_SCHED_BITMAP2_MASK	0x0F
#elif NUM_KERNEL_SCHED_BITMAP_SIZE <= 1024
typedef efat_ucount32 efat_sched_bitmap;
#define IMP_KERNEL_SCHED_TWO_LEVEL_BITMAP
#define NUM_KERNEL_SCHED_BITMAP2_SIZE 	32
#define NUM_KERNEL_SCHED_BITMAP2_SHIFT	5
#define NUM_KERNEL_SCHED_BITMAP2_MASK	0x1F
#else
#error Bitmaps greater than 1024 bits not currently allowed
#endif

#if 0

typedef struct
{
#if defined(SEM_KERNEL_SCHED_BITMAP)

    efat_sched_bitmap map;

#elif defined(SEM_KERNEL_SCHED_MLQUEUE)

    efat_thread *queue;

#elif defined(SEM_KERNEL_SCHED_LOTTERY)

    efat_thread *queue;

#else

#error Undefined scheduler type

#endif
} efat_threadqueue;

/*---------------------------------------------------------------------------*/

struct efat_interrupt
{
    efat_vector_t        vector;
    efat_priority_t      priority;
    efat_ISR_t           *isr;
    efat_DSR_t           *dsr;
    EFAT_ADDRWORD        data;

#ifdef IMP_KERNEL_INTERRUPTS_DSRS_LIST
    efat_ucount32        dsr_count;
    efat_interrupt       *next_dsr;
#endif
#ifdef IMP_KERNEL_INTERRUPTS_CHAIN
    efat_interrupt       *next;
#endif
};


/*---------------------------------------------------------------------------*/


#if defined(IMP_KERNEL_COUNTERS_SINGLE_LIST)
# define EFAT_COUNTER_ALARM_LIST_MEMBER \
    efat_alarm           *alarm_list;
#elif defined(IMP_KERNEL_COUNTERS_MULTI_LIST)
# define EFAT_COUNTER_ALARM_LIST_MEMBER \
    efat_alarm           *alarm_list[NUM_KERNEL_COUNTERS_MULTI_LIST_SIZE];
#else
# define EFAT_COUNTER_ALARM_LIST_MEMBER
#endif

#define EFAT_COUNTER_MEMBERS              \
    EFAT_COUNTER_ALARM_LIST_MEMBER        \
    efat_tick_count_t    counter;         \
    efat_uint32          increment;

struct efat_counter
{
    EFAT_COUNTER_MEMBERS
};

/*---------------------------------------------------------------------------*/

struct efat_clock
{
    EFAT_COUNTER_MEMBERS
    EFAT_RESOLUTION_T_MEMBERS
};

/*---------------------------------------------------------------------------*/


#if defined(IMP_KERNEL_COUNTERS_SINGLE_LIST) ||  \
    defined(IMP_KERNEL_COUNTERS_MULTI_LIST)
# define EFAT_ALARM_LIST_MEMBERS                     \
    efat_alarm           *next;                      \
    efat_alarm           *prev;
#else
# define EFAT_ALARM_LIST_MEMBERS
#endif

#define EFAT_ALARM_MEMBERS           \
    EFAT_ALARM_LIST_MEMBERS          \
    efat_counter         *counter;   \
    efat_alarm_t         *alarm;     \
    EFAT_ADDRWORD        data;       \
    efat_tick_count_t    trigger;    \
    efat_tick_count_t    interval;   \
    efat_bool            enabled;

struct efat_alarm
{
    EFAT_ALARM_MEMBERS
};

/*---------------------------------------------------------------------------*/
/* Hardware Thread structure                                                 */

#ifdef FUN_KERNEL_THREADS_STACK_LIMIT
#define EFAT_HARDWARETHREAD_STACK_LIMIT_MEMBER EFAT_ADDRESS stack_limit;    /* movable stack limit */
#else
#define EFAT_HARDWARETHREAD_STACK_LIMIT_MEMBER
#endif

#ifdef DBG_KERNEL_DEBUG_GDB_THREAD_SUPPORT
#define EFAT_HARDWARETHREAD_SAVED_CONTEXT_MEMBER void *saved_context; // If non-zero, this points at a more interesting context than stack_ptr.
#else
#define EFAT_HARDWARETHREAD_SAVED_CONTEXT_MEMBER
#endif

typedef void efat_thread_entry(EFAT_ADDRWORD data);

#define EFAT_HARDWARETHREAD_MEMBERS                                           \
    EFAT_ADDRESS         stack_base;   /* pointer to base of stack area */    \
    efat_uint32          stack_size;   /* size of stack area in bytes */      \
    EFAT_HARDWARETHREAD_STACK_LIMIT_MEMBER                                    \
    EFAT_ADDRESS         stack_ptr;    /* pointer to saved state on stack */  \
    efat_thread_entry   *entry_point;  /* main entry point (code pointer!) */ \
    EFAT_ADDRWORD        entry_data;   /* entry point argument */             \
    EFAT_HARDWARETHREAD_SAVED_CONTEXT_MEMBER

typedef struct
{
    EFAT_HARDWARETHREAD_MEMBERS
} efat_hardwarethread;


/*---------------------------------------------------------------------------*/
/* Exception controller                                                      */

#ifdef PKG_KERNEL_EXCEPTIONS

# ifdef SEM_KERNEL_EXCEPTIONS_DECODE
#  define EFAT_EXCEPTION_CONTROL_MEMBERS                                     \
    efat_exception_handler_t *exception_handler[NUM_HAL_EXCEPTION_COUNT]; \
    EFAT_ADDRWORD            exception_data[NUM_HAL_EXCEPTION_COUNT];
# else
#  define EFAT_EXCEPTION_CONTROL_MEMBERS                                \
    efat_exception_handler_t *exception_handler; /* Handler function */ \
    EFAT_ADDRWORD            exception_data;     /* Handler data */
# endif

typedef struct
{
    EFAT_EXCEPTION_CONTROL_MEMBERS
} efat_exception_control;

#endif

/*---------------------------------------------------------------------------*/
/* Scheduler Thread structure                                                */

#ifdef PKG_KERNEL_SMP_SUPPORT
# define EFAT_SCHEDTHREAD_CPU_MEMBER \
    efat_uint32          cpu;            // CPU id of cpu currently running
#else
# define EFAT_SCHEDTHREAD_CPU_MEMBER
#endif

#ifdef SEM_KERNEL_SCHED_TIMESLICE_ENABLE
# define EFAT_SCHEDTHREAD_TIMESLICE_ENABLED_MEMBER \
    efat_bool            timeslice_enabled; /* per-thread timeslice enable */
#else
# define EFAT_SCHEDTHREAD_TIMESLICE_ENABLED_MEMBER
#endif

#if defined(SEM_KERNEL_SCHED_BITMAP)
# define EFAT_SCHEDTHREAD_SCHEDIMP_MEMBERS \
    efat_priority_t      priority;       /* current thread priority */
#elif defined(SEM_KERNEL_SCHED_MLQUEUE)
# define EFAT_SCHEDTHREAD_SCHEDIMP_MEMBERS                                    \
    efat_thread *next;                                                        \
    efat_thread *prev;                                                        \
    efat_priority_t      priority;             /* current thread priority */  \
    EFAT_SCHEDTHREAD_CPU_MEMBER                                               \
    EFAT_SCHEDTHREAD_TIMESLICE_ENABLED_MEMBER
#elif defined(SEM_KERNEL_SCHED_LOTTERY)
# define EFAT_SCHEDTHREAD_SCHEDIMP_MEMBERS                                    \
    efat_thread *next;                                                        \
    efat_thread *prev;                                                        \
    efat_priority_t      priority;             /* current thread priority */  \
    efat_priority_t      compensation_tickets; /* sleep compensation */
#else
# error Undefined scheduler type
#endif

#ifndef SEM_KERNEL_SCHED_ASR_GLOBAL
#  define EFAT_SCHEDTHREAD_ASR_NONGLOBAL_MEMBER \
    void              (*asr)(EFAT_ADDRWORD);   // ASR function
#else
#  define EFAT_SCHEDTHREAD_ASR_NONGLOBAL_MEMBER
#endif

#ifdef SEM_KERNEL_SCHED_ASR_SUPPORT
# define EFAT_SCHEDTHREAD_ASR_MEMBER                                         \
    volatile efat_ucount32 asr_inhibit; /* If true, blocks calls to ASRs */  \
    volatile efat_bool     asr_pending; /* If true, this thread's ASR    */  \
                                       /* should be called. */              \
    EFAT_SCHEDTHREAD_ASR_NONGLOBAL_MEMBER                                    \
    EFAT_SCHEDTHREAD_ASR_DATA_NONGLOBAL_MEMBER
#else
# define EFAT_SCHEDTHREAD_ASR_MEMBER
#endif


#ifndef SEM_KERNEL_SCHED_ASR_DATA_GLOBAL
#  define EFAT_SCHEDTHREAD_ASR_DATA_NONGLOBAL_MEMBER \
    EFAT_ADDRWORD        asr_data;       // ASR data pointer
#else
#  define EFAT_SCHEDTHREAD_ASR_DATA_NONGLOBAL_MEMBER
#endif


#ifdef SEM_KERNEL_SYNCH_MUTEX_PRIORITY_INVERSION_PROTOCOL
# define EFAT_SCHEDTHREAD_MUTEX_INV_PROTO_MEMBERS   \
    efat_count32         mutex_count;               \
    EFAT_SCHEDTHREAD_MUTEX_INV_PROTO_SIMPLE_MEMBERS
#else
# define EFAT_SCHEDTHREAD_MUTEX_INV_PROTO_MEMBERS
#endif


#ifdef SEM_KERNEL_SYNCH_MUTEX_PRIORITY_INVERSION_PROTOCOL_SIMPLE
# define EFAT_SCHEDTHREAD_MUTEX_INV_PROTO_SIMPLE_MEMBERS \
    efat_priority_t      original_priority;              \
    efat_bool            priority_inherited;
#else
# define EFAT_SCHEDTHREAD_MUTEX_INV_PROTO_SIMPLE_MEMBERS
#endif

#define EFAT_SCHEDTHREAD_MEMBERS               \
    EFAT_SCHEDTHREAD_SCHEDIMP_MEMBERS          \
    efat_threadqueue     *queue;               \
    EFAT_SCHEDTHREAD_ASR_MEMBER                \
    EFAT_SCHEDTHREAD_MUTEX_INV_PROTO_MEMBERS


typedef struct
{
    EFAT_SCHEDTHREAD_MEMBERS
} efat_schedthread;

#if defined(__GNUC__) && (__GNUC__ < 3)
#define EFAT_THREADTIMER_MEMBERS \
    efat_alarm           alarm;  \
    efat_thread          *thread;
#else
#define EFAT_THREADTIMER_MEMBERS \
    EFAT_ALARM_MEMBERS           \
    efat_thread          *thread;
#endif

/*---------------------------------------------------------------------------*/
/* Thread structure                                                          */

typedef struct
{
    EFAT_THREADTIMER_MEMBERS
} efat_threadtimer;


typedef enum
{
    EFAT_REASON_NONE,
    EFAT_REASON_WAIT,
    EFAT_REASON_DELAY,
    EFAT_REASON_TIMEOUT,
    EFAT_REASON_BREAK,
    EFAT_REASON_DESTRUCT,
    EFAT_REASON_EXIT,
    EFAT_REASON_DONE
} efat_reason_t;

#if defined(PKG_KERNEL_EXCEPTIONS) && !defined(SEM_KERNEL_EXCEPTIONS_GLOBAL)
# define EFAT_THREAD_EXCEPTION_CONTROL_MEMBER \
    efat_exception_control       exception_control;
#else
# define EFAT_THREAD_EXCEPTION_CONTROL_MEMBER
#endif

#ifdef FUN_KERNEL_THREADS_TIMER
# define EFAT_THREAD_TIMER_MEMBER \
    efat_threadtimer     timer;
#else
# define EFAT_THREAD_TIMER_MEMBER
#endif

#ifdef VAR_KERNEL_THREADS_DATA
# define EFAT_THREAD_THREAD_DATA_MEMBER \
    EFAT_ADDRWORD        thread_data[NUM_KERNEL_THREADS_DATA_MAX];
#else
# define EFAT_THREAD_THREAD_DATA_MEMBER
#endif

#ifdef VAR_KERNEL_THREADS_NAME
# define EFAT_THREAD_NAME_MEMBER \
    char                *name;
#else
# define EFAT_THREAD_NAME_MEMBER
#endif

#ifdef VAR_KERNEL_THREADS_LIST
# define EFAT_THREAD_LIST_NEXT_MEMBER \
    efat_thread          *list_next;
#else
# define EFAT_THREAD_LIST_NEXT_MEMBER
#endif



#ifdef SEM_KERNEL_THREADS_DESTRUCTORS_PER_THREAD
struct Efat_Destructor_Entry {
    efat_thread_destructor_fn fn;
    efat_addrword_t data;
};
# define EFAT_THREAD_DESTRUCTORS_MEMBER \
   struct Efat_Destructor_Entry destructors[ NUM_KERNEL_THREADS_DESTRUCTORS ];
#else
# define EFAT_THREAD_DESTRUCTORS_MEMBER
#endif


#define EFAT_THREAD_MEMBERS                        \
    EFAT_HARDWARETHREAD_MEMBERS                    \
    EFAT_SCHEDTHREAD_MEMBERS                       \
                                                  \
    efat_uint32                  state;            \
    efat_ucount32                suspend_count;    \
    efat_ucount32                wakeup_count;     \
    EFAT_ADDRWORD                wait_info;        \
    efat_uint16                  unique_id;        \
                                                  \
    EFAT_THREAD_EXCEPTION_CONTROL_MEMBER           \
    EFAT_THREAD_TIMER_MEMBER                       \
                                                  \
    efat_reason_t        sleep_reason;             \
    efat_reason_t        wake_reason;              \
                                                  \
    EFAT_THREAD_THREAD_DATA_MEMBER                 \
    EFAT_THREAD_DESTRUCTORS_MEMBER                 \
    EFAT_THREAD_NAME_MEMBER                        \
    EFAT_THREAD_LIST_NEXT_MEMBER


struct efat_thread
{
    EFAT_THREAD_MEMBERS
};

/*---------------------------------------------------------------------------*/

struct efat_mbox
{
    efat_count32         base;           /* index of first used slot          */
    efat_count32         count;          /* count of used slots               */
    efat_threadqueue     get_threadq;    /* Queue of waiting threads          */
#ifdef MFN_KERNEL_SYNCH_MBOXT_PUT_CAN_WAIT
    efat_threadqueue     put_threadq;    /* Queue of waiting threads          */
#endif
    void *              itemqueue[ NUM_KERNEL_SYNCH_MBOX_QUEUE_SIZE ];
};

/*---------------------------------------------------------------------------*/
#if 0
struct efat_sem_t
{
    efat_count32         count;          /* The semaphore count          */
    efat_threadqueue     queue;          /* Queue of waiting threads     */
};
#endif
/*---------------------------------------------------------------------------*/

struct efat_flag_t
{
    efat_flag_value_t    value;          /* The flag value               */
    efat_threadqueue     queue;          /* Queue of waiting threads     */
};

/*---------------------------------------------------------------------------*/

typedef enum
{
    EFAT_MUTEX_PROTOCOL_NONE,
    EFAT_MUTEX_PROTOCOL_INHERIT,
    EFAT_MUTEX_PROTOCOL_CEILING
} efat_mutex_protocol_t;


/*------------------------------------------------------------------------*/

struct efat_spinlock_t
{
    efat_uint32          lock;           /* lock word                     */
};

/*------------------------------------------------------------------------*/

/* Memory allocator types now come from the "memalloc" package which is   */
/* where the implementation lives.                                        */

#endif

#ifdef PKG_MEMALLOC
#endif

#ifdef __cplusplus
}
#endif

/*---------------------------------------------------------------------------*/
/* EOF kapidata.h                                                            */
#endif /* ONCE_KERNEL_KAPIDATA_H */
