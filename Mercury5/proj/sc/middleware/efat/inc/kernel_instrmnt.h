#ifndef ONCE_KERNEL_INSTRMNT_HXX
#define ONCE_KERNEL_INSTRMNT_HXX
////////////////////////////////////////////////////////////////////////////////
///@file kernel_instmnt.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <kernel_ktypes.h>
#include <infra_ass.h>            // assertion macros

// -------------------------------------------------------------------------
// Underlying instrumentation function

externC void efat_instrument( efat_uint32 type, EFAT_ADDRWORD arg1, EFAT_ADDRWORD arg2 );

// -------------------------------------------------------------------------
// The following functions are used to enable and disable specific
// instrumentation classes and events. The class must be one of the
// class defines below. The event may be one of the event defines below
// or zero, in which case all of the events in the class are enabled or
// disabled.

#ifdef DBG_KERNEL_INSTRUMENT_FLAGS

externC void efat_instrument_enable( efat_uint32 cl, efat_uint32 event );

externC void efat_instrument_disable( efat_uint32 cl, efat_uint32 event );

externC efat_bool efat_instrument_state( efat_uint32 cl, efat_uint32 event );

#endif

#ifdef DBG_KERNEL_INSTRUMENT_MSGS
externC char * efat_instrument_msg(EFAT_WORD16 type);
#endif

// -------------------------------------------------------------------------
// Instrumentation macros

#ifdef PKG_KERNEL_INSTRUMENT

#define EFAT_INSTRUMENT(_type_,_arg1_,_arg2_) efat_instrument(_type_, (EFAT_ADDRWORD)(_arg1_), (EFAT_ADDRWORD)(_arg2_))

#else   // ifdef PKG_KERNEL_INSTRUMENT

#define EFAT_INSTRUMENT(_type_,_arg1_,_arg2_)

#endif  // ifdef PKG_KERNEL_INSTRUMENT

// -------------------------------------------------------------------------
// Type codes.
// Each code is 16 bit with an event class in the top 8 bits
// and an event code in the lower 8 bits.


// Scheduler events
#define EFAT_INSTRUMENT_EVENT_SCHED_LOCK         1
#define EFAT_INSTRUMENT_EVENT_SCHED_UNLOCK       2
#define EFAT_INSTRUMENT_EVENT_SCHED_RESCHEDULE   3
#define EFAT_INSTRUMENT_EVENT_SCHED_TIMESLICE    4

// Event classes
#define EFAT_INSTRUMENT_CLASS_SCHED              0x0100
#define EFAT_INSTRUMENT_CLASS_THREAD             0x0200
#define EFAT_INSTRUMENT_CLASS_INTR               0x0300
#define EFAT_INSTRUMENT_CLASS_MUTEX              0x0400
#define EFAT_INSTRUMENT_CLASS_CONDVAR            0x0500
#define EFAT_INSTRUMENT_CLASS_BINSEM             0x0600
//separate
#define EFAT_INSTRUMENT_CLASS_CNTSEM             0x0700
#define EFAT_INSTRUMENT_CLASS_CLOCK              0x0800
#define EFAT_INSTRUMENT_CLASS_ALARM              0x0900
#define EFAT_INSTRUMENT_CLASS_MBOXT              0x0a00
#define EFAT_INSTRUMENT_CLASS_SMP                0x0b00
#define EFAT_INSTRUMENT_CLASS_MLQ                0x0c00

#define EFAT_INSTRUMENT_CLASS_USER               0x0f00

#define EFAT_INSTRUMENT_CLASS_MAX                EFAT_INSTRUMENT_CLASS_USER

// Thread events
#define EFAT_INSTRUMENT_EVENT_THREAD_SWITCH      1
#define EFAT_INSTRUMENT_EVENT_THREAD_SLEEP       2
#define EFAT_INSTRUMENT_EVENT_THREAD_WAKE        3
#define EFAT_INSTRUMENT_EVENT_THREAD_SUSPEND     4
#define EFAT_INSTRUMENT_EVENT_THREAD_RESUME      5
#define EFAT_INSTRUMENT_EVENT_THREAD_PRIORITY    6
//separate
#define EFAT_INSTRUMENT_EVENT_THREAD_DELAY       7
#define EFAT_INSTRUMENT_EVENT_THREAD_ALARM       8
#define EFAT_INSTRUMENT_EVENT_THREAD_ENTER       9
#define EFAT_INSTRUMENT_EVENT_THREAD_CHECK_STACK 10
#define EFAT_INSTRUMENT_EVENT_THREAD_ATTACH_STACK 11
#define EFAT_INSTRUMENT_EVENT_THREAD_CREATE      12

// Mutex events
#define EFAT_INSTRUMENT_EVENT_MUTEX_LOCK         1
#define EFAT_INSTRUMENT_EVENT_MUTEX_WAIT         2
#define EFAT_INSTRUMENT_EVENT_MUTEX_LOCKED       3
#define EFAT_INSTRUMENT_EVENT_MUTEX_TRY          4
#define EFAT_INSTRUMENT_EVENT_MUTEX_UNLOCK       5
#define EFAT_INSTRUMENT_EVENT_MUTEX_WAKE         6
#define EFAT_INSTRUMENT_EVENT_MUTEX_RELEASE      7
#define EFAT_INSTRUMENT_EVENT_MUTEX_RELEASED     8


// Interrupt events
#define EFAT_INSTRUMENT_EVENT_INTR_RAISE         1
#define EFAT_INSTRUMENT_EVENT_INTR_END           2
#define EFAT_INSTRUMENT_EVENT_INTR_RESTORE       3
#define EFAT_INSTRUMENT_EVENT_INTR_POST_DSR      4
#define EFAT_INSTRUMENT_EVENT_INTR_CALL_DSR      5
#define EFAT_INSTRUMENT_EVENT_INTR_ATTACH        6
#define EFAT_INSTRUMENT_EVENT_INTR_DETACH        7
#define EFAT_INSTRUMENT_EVENT_INTR_SET_VSR       8
//separate
#define EFAT_INSTRUMENT_EVENT_INTR_DISABLE       9
#define EFAT_INSTRUMENT_EVENT_INTR_ENABLE        10
#define EFAT_INSTRUMENT_EVENT_INTR_MASK          11
#define EFAT_INSTRUMENT_EVENT_INTR_UNMASK        12
#define EFAT_INSTRUMENT_EVENT_INTR_CONFIGURE     13
#define EFAT_INSTRUMENT_EVENT_INTR_ACK           14
#define EFAT_INSTRUMENT_EVENT_INTR_CHAIN_ISR     15
#define EFAT_INSTRUMENT_EVENT_INTR_SET_CPU       16
#define EFAT_INSTRUMENT_EVENT_INTR_GET_CPU       17

// Condition variable events
#define EFAT_INSTRUMENT_EVENT_CONDVAR_WAIT       1
#define EFAT_INSTRUMENT_EVENT_CONDVAR_WOKE       2
#define EFAT_INSTRUMENT_EVENT_CONDVAR_SIGNAL     3
#define EFAT_INSTRUMENT_EVENT_CONDVAR_WAKE       4
#define EFAT_INSTRUMENT_EVENT_CONDVAR_BROADCAST  5
#define EFAT_INSTRUMENT_EVENT_CONDVAR_TIMED_WAIT 6

// Counting semaphore events
#define EFAT_INSTRUMENT_EVENT_CNTSEM_CLAIM       1
#define EFAT_INSTRUMENT_EVENT_CNTSEM_WAIT        2
#define EFAT_INSTRUMENT_EVENT_CNTSEM_WOKE        3
#define EFAT_INSTRUMENT_EVENT_CNTSEM_TRY         4
#define EFAT_INSTRUMENT_EVENT_CNTSEM_POST        5
#define EFAT_INSTRUMENT_EVENT_CNTSEM_WAKE        6
#define EFAT_INSTRUMENT_EVENT_CNTSEM_TIMEOUT     7

// Binary semaphore events
#define EFAT_INSTRUMENT_EVENT_BINSEM_CLAIM       1
#define EFAT_INSTRUMENT_EVENT_BINSEM_WAIT        2
#define EFAT_INSTRUMENT_EVENT_BINSEM_WOKE        3
#define EFAT_INSTRUMENT_EVENT_BINSEM_TRY         4
#define EFAT_INSTRUMENT_EVENT_BINSEM_POST        5
#define EFAT_INSTRUMENT_EVENT_BINSEM_WAKE        6
#define EFAT_INSTRUMENT_EVENT_BINSEM_TIMEOUT     7

// Clock events
#define EFAT_INSTRUMENT_EVENT_CLOCK_TICK_START   1
#define EFAT_INSTRUMENT_EVENT_CLOCK_TICK_END     2
#define EFAT_INSTRUMENT_EVENT_CLOCK_ISR          3

// Mboxt events
#define EFAT_INSTRUMENT_EVENT_MBOXT_WAIT         1
#define EFAT_INSTRUMENT_EVENT_MBOXT_GET          2
#define EFAT_INSTRUMENT_EVENT_MBOXT_GOT          3
#define EFAT_INSTRUMENT_EVENT_MBOXT_TIMEOUT      4
#define EFAT_INSTRUMENT_EVENT_MBOXT_WAKE         5
#define EFAT_INSTRUMENT_EVENT_MBOXT_TRY          6
#define EFAT_INSTRUMENT_EVENT_MBOXT_PUT          7

// Alarm events
#define EFAT_INSTRUMENT_EVENT_ALARM_ADD          1
#define EFAT_INSTRUMENT_EVENT_ALARM_REM          2
#define EFAT_INSTRUMENT_EVENT_ALARM_CALL         3
#define EFAT_INSTRUMENT_EVENT_ALARM_INIT         4
#define EFAT_INSTRUMENT_EVENT_ALARM_TRIGGER      5
#define EFAT_INSTRUMENT_EVENT_ALARM_INTERVAL     6

// MLQ scheduler events

#define EFAT_INSTRUMENT_EVENT_MLQ_SCHEDULE       1
#define EFAT_INSTRUMENT_EVENT_MLQ_RESCHEDULE     2
#define EFAT_INSTRUMENT_EVENT_MLQ_ADD            3
#define EFAT_INSTRUMENT_EVENT_MLQ_REM            4
#define EFAT_INSTRUMENT_EVENT_MLQ_TIMESLICE      5
#define EFAT_INSTRUMENT_EVENT_MLQ_YIELD          6
#define EFAT_INSTRUMENT_EVENT_MLQ_ENQUEUE        7
#define EFAT_INSTRUMENT_EVENT_MLQ_DEQUEUE        8
#define EFAT_INSTRUMENT_EVENT_MLQ_REMOVE         9

// SMP events
#define EFAT_INSTRUMENT_EVENT_SMP_LOCK_INC       1
#define EFAT_INSTRUMENT_EVENT_SMP_LOCK_ZERO      2
#define EFAT_INSTRUMENT_EVENT_SMP_LOCK_SET       3
#define EFAT_INSTRUMENT_EVENT_SMP_CPU_START      4
#define EFAT_INSTRUMENT_EVENT_SMP_LOCK_WAIT      5
#define EFAT_INSTRUMENT_EVENT_SMP_LOCK_GOT       6
#define EFAT_INSTRUMENT_EVENT_SMP_RESCHED_SEND   8
#define EFAT_INSTRUMENT_EVENT_SMP_RESCHED_RECV   9


// User events

//separate

#define EFAT_INSTRUMENT_EVENT_USER_9             9
#define EFAT_INSTRUMENT_EVENT_USER_10            10
#define EFAT_INSTRUMENT_EVENT_USER_11            11
#define EFAT_INSTRUMENT_EVENT_USER_12            12
#define EFAT_INSTRUMENT_EVENT_USER_13            13
#define EFAT_INSTRUMENT_EVENT_USER_14            14
#define EFAT_INSTRUMENT_EVENT_USER_15            15
//separate

#define EFAT_INSTRUMENT_EVENT_USER_1             1
#define EFAT_INSTRUMENT_EVENT_USER_2             2
#define EFAT_INSTRUMENT_EVENT_USER_3             3
#define EFAT_INSTRUMENT_EVENT_USER_4             4
#define EFAT_INSTRUMENT_EVENT_USER_5             5
#define EFAT_INSTRUMENT_EVENT_USER_6             6
#define EFAT_INSTRUMENT_EVENT_USER_7             7
#define EFAT_INSTRUMENT_EVENT_USER_8             8

//separate

#define EFAT_INSTRUMENT_EVENT_USER_16            16
#define EFAT_INSTRUMENT_EVENT_USER_17            17
#define EFAT_INSTRUMENT_EVENT_USER_18            18
#define EFAT_INSTRUMENT_EVENT_USER_19            19

// -------------------------------------------------------------------------
#define INST_EVENT(_class_,_event_) \
((EFAT_INSTRUMENT_CLASS_##_class_)|(EFAT_INSTRUMENT_EVENT_##_class_##_##_event_))

// -------------------------------------------------------------------------
// Scheduler instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_SCHED

#define EFAT_INSTRUMENT_SCHED(_event_,_arg1_,_arg2_)
#else
#define EFAT_INSTRUMENT_SCHED(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(SCHED,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// Thread instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_THREAD
#define EFAT_INSTRUMENT_THREAD(_event_,_arg1_,_arg2_)
#else
#define EFAT_INSTRUMENT_THREAD(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(THREAD,_event_),_arg1_,_arg2_)
#endif

// -------------------------------------------------------------------------
// Interrupt instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_INTR

#define EFAT_INSTRUMENT_INTR(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_INTR(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(INTR,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// Mutex instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_MUTEX

#define EFAT_INSTRUMENT_MUTEX(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_MUTEX(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(MUTEX,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// Condition variable instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_CONDVAR

#define EFAT_INSTRUMENT_CONDVAR(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_CONDVAR(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(CONDVAR,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// Binary semaphore instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_BINSEM

#define EFAT_INSTRUMENT_BINSEM(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_BINSEM(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(BINSEM,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// Counting semaphore instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_CNTSEM

#define EFAT_INSTRUMENT_CNTSEM(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_CNTSEM(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(CNTSEM,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// Clock instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_CLOCK

#define EFAT_INSTRUMENT_CLOCK(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_CLOCK(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(CLOCK,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// Alarm instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_ALARM

#define EFAT_INSTRUMENT_ALARM(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_ALARM(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(ALARM,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// Mboxt instrumentation macros

#ifndef DBG_KERNEL_INSTRUMENT_MBOXT

#define EFAT_INSTRUMENT_MBOXT(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_MBOXT(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(MBOXT,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// SMP instrumentation

#ifndef DBG_KERNEL_INSTRUMENT_SMP

#define EFAT_INSTRUMENT_SMP(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_SMP(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(SMP,_event_),_arg1_,_arg2_)

#endif


// -------------------------------------------------------------------------
// MLQ instrumentation

#ifndef DBG_KERNEL_INSTRUMENT_MLQ

#define EFAT_INSTRUMENT_MLQ(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_MLQ(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT(INST_EVENT(MLQ,_event_),_arg1_,_arg2_)

#endif

// -------------------------------------------------------------------------
// User instrumentation

#ifndef DBG_KERNEL_INSTRUMENT_USER

#define EFAT_INSTRUMENT_USER(_event_,_arg1_,_arg2_)

#else

#define EFAT_INSTRUMENT_USER(_event_,_arg1_,_arg2_) EFAT_INSTRUMENT((EFAT_INSTRUMENT_CLASS_USER|(_event_)),_arg1_,_arg2_)

#endif


// -------------------------------------------------------------------------
#endif // ifndef ONCE_KERNEL_INSTRMNT_HXX
// EOF instrmnt.h
