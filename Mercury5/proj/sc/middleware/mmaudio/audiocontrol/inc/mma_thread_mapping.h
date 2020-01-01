////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MMA_THREAD_MAPPING_H
#define MMA_THREAD_MAPPING_H

#include <stdint.h>

#ifndef __SDK_SIMULATION__
#if defined (_MSC_VER)
#include <windows.h> //THREAD_PRIORITY_NORMAL
#include <semaphore.h>
#include <pthread.h>
#define P_TH
#elif defined(ECOS)
#define CYG_TH
#include <cyg/kernel/kapi.h>
#undef S8
#elif defined(__RTK_OS__)
#include "sys_sys_task_priority.h"
#include "sys_MsWrapper_cus_os_sem.h"
#elif defined(LINUX)
#include <semaphore.h>
#include <pthread.h>
#define P_TH
#endif

#else
#define __RTK_OS__
#include "sys_sys_task_priority.h"
#include "sys_MsWrapper_cus_os_sem.h"
#endif

#ifdef _MSC_VER

#elif defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM == 3)
#elif defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM == 4)
#elif defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM == 5)
#elif defined(__RTK_OS__)
//#define audio thread priority here
// A2DP_THREAD_PRIORITY                         MAP_THREAD_PRIORITY_NORMAL
#else
#endif


#ifdef CYG_TH
typedef cyg_handle_t             map_handle_t;
typedef cyg_mutex_t              map_mutex_t;
typedef cyg_thread               map_thread_t;
typedef cyg_sem_t                map_sem_t;
typedef cyg_cond_t               map_cond_t;
typedef cyg_flag_t               map_flag_t;
typedef cyg_alarm                map_alarm;
typedef cyg_alarm_t              map_alarm_t;

#elif defined(__RTK_OS__)
typedef uint8_t                  map_handle_t;
typedef Ms_Mutex_t               map_mutex_t;
typedef uint8_t                  map_thread_t;
typedef MsSemId_e                map_sem_t;

typedef struct map_cv_cond_s
{
    map_mutex_t cv_mutex;
    map_sem_t   cv_sem;
    uint8_t     wait;
} map_cv_cond_st;

typedef map_cv_cond_st           map_cond_t;
typedef int                      map_flag_t;
typedef int                      map_alarm;
typedef void                     map_alarm_t(map_handle_t alarm, uint32_t data);

#elif defined(P_TH)
typedef pthread_t                map_handle_t;
typedef pthread_mutex_t          map_mutex_t;
typedef pthread_t                map_thread_t;
typedef sem_t                    map_sem_t;
typedef pthread_cond_t           map_cond_t;
typedef sem_t                    map_flag_t;
typedef int                      map_alarm;
typedef void                     map_alarm_t(map_handle_t alarm, uint32_t data);

#else
#define map_handle_t             void *
#define map_thread_t             void *
#define map_mutex_t              void *
#define map_sem_t                void *
#define map_cond_t               void *
#define map_flag_t               void *
#endif

typedef void *                   map_thread_entry_t(void *);
typedef int                      map_bool_t;
typedef int64_t                  map_tick_count_t;
typedef int                      map_flag_value_t;


typedef struct map_thread_inst_s
{
    map_handle_t        handle_obj;
    map_thread_t        thread_obj;
    map_thread_entry_t *entry;
    void               *arg;
#ifdef __RTK_OS__
    map_sem_t           sem_finish;
#endif
} map_thread_inst;

//Mutex
void map_mutex_init(map_mutex_t *mutex);
map_bool_t map_mutex_lock(map_mutex_t *mutex);
void map_mutex_unlock(map_mutex_t *mutex);
void map_mutex_destroy(map_mutex_t *mutex);

//Semaphore
void map_semaphore_init(map_sem_t *sem, int val);
void map_semaphore_post(map_sem_t *sem);
void map_semaphore_peek(map_sem_t *sem, int *val);
map_bool_t map_semaphore_wait(map_sem_t *sem);
map_bool_t map_semaphore_timed_wait(map_sem_t *sem, uint32_t wait_time);
int map_semaphore_trywait(map_sem_t *sem);
void map_semaphore_destroy(map_sem_t *sem);
void map_semaphore_peek(map_sem_t *sem, int *val);
void map_semaphore_reset(void);

//Cond
void map_cond_init(map_cond_t *cond, map_mutex_t *mutex);
map_bool_t map_cond_wait(map_cond_t *cond, map_mutex_t *mutex);
void map_cond_signal(map_cond_t *cond);
void map_cond_destroy(map_cond_t *cond);
void map_cond_broadcast(map_cond_t *cond);

//Thread
int map_thread_create(
    uint32_t            sched_info,             /* scheduling info (eg pri)  */
    map_thread_entry_t  *entry,                 /* entry point function      */
    void                *entry_data,            /* entry data                */
    char                *name,                  /* optional thread name      */
    void                *stack_base,            /* stack base, NULL = alloc  */
    uint32_t            stack_size,             /* stack size, 0 = default   */
    map_thread_inst     *thread_inst_p          /* returned thread handle    */
);

void map_thread_exit(map_thread_inst *thread_inst_p);
void map_thread_yield(void);
map_bool_t map_thread_delete(map_thread_inst *thread_inst_p);
void map_thread_delay(int64_t delay);
map_bool_t map_thread_check_exit(map_thread_inst *thread_inst_p);
int map_thread_join(map_thread_inst *thread_inst_p, void **status);
void map_thread_change_priority(map_thread_inst *thread_inst_p, int32_t priority);
void map_enter_ctritical_section(void);
void map_leave_ctritical_section(void);
int map_start_profile(void);
int map_end_profile(void);
int map_query_CPU(map_thread_inst* thread_inst_p, int* cpu_usage);

//Flag
void map_flag_setbits(map_flag_t *flag, map_flag_value_t value);
void map_flag_maskbits(map_flag_t *flag, map_flag_value_t value);
void map_flag_init(map_flag_t* flag);
void map_flag_destroy(map_flag_t *flag);

//Time
int64_t map_get_current_time(void);
void map_reset_timer(void);

#endif

