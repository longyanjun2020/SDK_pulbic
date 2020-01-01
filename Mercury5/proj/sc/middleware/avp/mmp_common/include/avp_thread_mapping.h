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


#ifndef THREAD_MAPPING_H
#define THREAD_MAPPING_H

#include <stdint.h>

#if defined(__RTK_OS__)
#include "sys_sys_task_priority.h"
#include "sys_MsWrapper_cus_os_sem.h"
#elif defined (_MSC_VER)
#include <windows.h> //THREAD_PRIORITY_NORMAL
#include <semaphore.h>
#include <pthread.h>
#elif defined(ECOS)
#define CYG_TH
#include <cyg/kernel/kapi.h>
#undef S8
#elif defined(NO_THREAD)
#else
#include <semaphore.h>
#include <pthread.h>
#endif

#if defined(__RTK_OS__)
#define GETFILEINFO_THREAD_PRIORITY         DYN_VD_PRIO
#define DX_THREAD_PRIORITY                  DYN_DX_PRIO
#define VD_THREAD_PRIORITY                  DYN_VD_PRIO
#define VD_THREAD_LOW_PRIORITY              7
#define AD_THREAD_PRIORITY                  DYN_AD_PRIO
#define VO_THREAD_PRIORITY                  DYN_VO_PRIO
#define STM_THREAD_PRIORITY                 DYN_VD_PRIO
#elif defined(_MSC_VER)
#define MMP_THREAD_PRIORITY_NORMAL THREAD_PRIORITY_NORMAL
#define GETFILEINFO_THREAD_PRIORITY         MMP_THREAD_PRIORITY_NORMAL
#define DX_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_LOW_PRIORITY              MMP_THREAD_PRIORITY_NORMAL
#define AD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VO_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#elif defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM == 3)
#define MMP_THREAD_PRIORITY_NORMAL  3
#define GETFILEINFO_THREAD_PRIORITY         MMP_THREAD_PRIORITY_NORMAL
#define DX_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_LOW_PRIORITY              MMP_THREAD_PRIORITY_NORMAL
#define AD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VO_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#elif defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM == 4)
#define MMP_THREAD_PRIORITY_NORMAL  3
#define GETFILEINFO_THREAD_PRIORITY         MMP_THREAD_PRIORITY_NORMAL
#define DX_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_LOW_PRIORITY              MMP_THREAD_PRIORITY_NORMAL
#define AD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VO_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#elif defined(CERAMAL_PLATFORM) && (CERAMAL_PLATFORM == 5)
#define MMP_THREAD_PRIORITY_NORMAL  5
#define GETFILEINFO_THREAD_PRIORITY         MMP_THREAD_PRIORITY_NORMAL
#define DX_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_LOW_PRIORITY              MMP_THREAD_PRIORITY_NORMAL
#define AD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VO_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#else
#define MMP_THREAD_PRIORITY_NORMAL 10
#define GETFILEINFO_THREAD_PRIORITY         MMP_THREAD_PRIORITY_NORMAL
#define DX_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VD_THREAD_LOW_PRIORITY              MMP_THREAD_PRIORITY_NORMAL
#define AD_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#define VO_THREAD_PRIORITY                  MMP_THREAD_PRIORITY_NORMAL
#endif

#define MMP_THREAD_PRIORITY_MP3 MMP_THREAD_PRIORITY_NORMAL

#ifdef CYG_TH
typedef cyg_handle_t             mmp_handle_t;
typedef cyg_mutex_t              mmp_mutex_t;
typedef cyg_thread               mmp_thread_t;
typedef cyg_sem_t                mmp_sem_t;
typedef cyg_cond_t               mmp_cond_t;

#elif defined(__RTK_OS__)
typedef uint8_t                  mmp_handle_t;
typedef Ms_Mutex_t               mmp_mutex_t;
typedef uint8_t                  mmp_thread_t;
typedef MsSemId_e                mmp_sem_t;

typedef struct mmp_cv_cond_s
{
    mmp_mutex_t cv_mutex;
    mmp_sem_t   cv_sem;
    uint8_t     wait;
} mmp_cv_cond_st;

typedef mmp_cv_cond_st           mmp_cond_t;

#elif defined(NO_THREAD)

#define mmp_handle_t             void *
#define mmp_thread_t             void *
#define mmp_mutex_t              void *
#define mmp_sem_t                void *
#define mmp_cond_t               void *

#else
typedef pthread_t                mmp_handle_t;
typedef pthread_mutex_t          mmp_mutex_t;
typedef pthread_t                mmp_thread_t;
typedef sem_t                    mmp_sem_t;
typedef pthread_cond_t           mmp_cond_t;

#endif

typedef void *                   mmp_thread_entry_t(void *);
typedef int                      mmp_bool_t;
typedef int64_t                  mmp_tick_count_t;


typedef struct mmp_thread_inst_s
{
    mmp_handle_t        handle_obj;
    mmp_thread_t        thread_obj;
    mmp_thread_entry_t *entry;
    void               *arg;
#ifdef __RTK_OS__
    mmp_sem_t           sem_finish;
#endif
} mmp_thread_inst;

//Mutex
void mmp_mutex_init(mmp_mutex_t *mutex);
mmp_bool_t mmp_mutex_lock(mmp_mutex_t *mutex);
void mmp_mutex_unlock(mmp_mutex_t *mutex);
void mmp_mutex_destroy(mmp_mutex_t *mutex);

//Semaphore
void mmp_semaphore_init(mmp_sem_t *sem, int val);
void mmp_semaphore_post(mmp_sem_t *sem);
void mmp_semaphore_peek(mmp_sem_t *sem, int *val);
mmp_bool_t mmp_semaphore_wait(mmp_sem_t *sem);
mmp_bool_t mmp_semaphore_timed_wait(mmp_sem_t *sem, uint32_t wait_time);
int mmp_semaphore_trywait(mmp_sem_t *sem);
void mmp_semaphore_destroy(mmp_sem_t *sem);
void mmp_semaphore_peek(mmp_sem_t *sem, int *val);
void mmp_semaphore_reset(void);

//Cond
void mmp_cond_init(mmp_cond_t *cond, mmp_mutex_t *mutex);
mmp_bool_t mmp_cond_wait(mmp_cond_t *cond, mmp_mutex_t *mutex);
void mmp_cond_signal(mmp_cond_t *cond);
void mmp_cond_destroy(mmp_cond_t *cond);
void mmp_cond_broadcast(mmp_cond_t *cond);

//Thread
int mmp_thread_create(
    uint32_t            sched_info,             /* scheduling info (eg pri)  */
    mmp_thread_entry_t  *entry,                 /* entry point function      */
    void                *entry_data,            /* entry data                */
    char                *name,                  /* optional thread name      */
    void                *stack_base,            /* stack base, NULL = alloc  */
    uint32_t            stack_size,             /* stack size, 0 = default   */
    mmp_thread_inst     *thread_inst_p          /* returned thread handle    */
);

void mmp_thread_exit(mmp_thread_inst *thread_inst_p);
void mmp_thread_yield(void);
mmp_bool_t mmp_thread_delete(mmp_thread_inst *thread_inst_p);
void mmp_thread_delay(int64_t delay);
mmp_bool_t mmp_thread_check_exit(mmp_thread_inst *thread_inst_p);
int mmp_thread_join(mmp_thread_inst *thread_inst_p, void **status);
void mmp_thread_change_priority(mmp_thread_inst *thread_inst_p, int32_t priority);
int mmp_start_profile(void);
int mmp_end_profile(void);
int mmp_query_CPU(mmp_thread_inst* thread_inst_p, int* cpu_usage);

//Time
int64_t mmp_get_current_time(void);
void mmp_reset_timer(void);

#endif
