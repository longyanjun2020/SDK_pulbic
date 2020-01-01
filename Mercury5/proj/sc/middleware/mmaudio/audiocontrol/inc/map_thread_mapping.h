#ifndef MAP_THREAD_MAPPING_H
#define MAP_THREAD_MAPPING_H

//#include "thread_mapping.h"
#include "sys_MsWrapper_cus_os_sem.h"
#include "sys_MsWrapper_cus_os_util.h"

#define cyg_count32              int
#define cyg_addrword_t           uint32_t

#define cyg_handle_t             mmp_thread_t
#define cyg_flag_t               mmp_flag_t
#define cyg_flag_value_t         mmp_flag_value_t
#define cyg_alarm                mmp_alarm
#define cyg_bool_t               mmp_bool_t
#define cyg_mutex_t              mmp_mutex_t
#define cyg_thread               mmp_thread_t
#define cyg_sem_t                mmp_sem_t
#define cyg_cond_t               mmp_cond_t

#define cyg_thread_entry_t       mmp_thread_entry_t
#define cyg_alarm_t              mmp_alarm_t

#if 0
#define cyg_mutex_init           mmp_mutex_init
#define cyg_mutex_lock           mmp_mutex_lock
#define cyg_mutex_unlock         mmp_mutex_unlock
#define cyg_mutex_destroy        mmp_mutex_destroy
#define cyg_mutex_trylock        mmp_mutex_trylock
#else
#define cyg_mutex_init(x)
#define cyg_mutex_lock(x)
#define cyg_mutex_unlock(x)
#define cyg_mutex_destroy(x)
#define cyg_mutex_trylock(x)
#endif

//#define MyLock					 mmp_mutex_lock
//#define MyUnLock				 mmp_mutex_unlock
#define MyLock(x) //big3
#define MyUnlock(x) //big3

//#define cyg_semaphore_init       mmp_semaphore_init
//#define cyg_semaphore_post       mmp_semaphore_post
//#define cyg_semaphore_wait       mmp_semaphore_wait
#if 1
#define cyg_semaphore_init MsInitSem
#define cyg_semaphore_post(p) MsProduceSem(p)
#define cyg_semaphore_wait(p) MsConsumeSem(p)
#else
#define cyg_semaphore_init(s1,n)
#define cyg_semaphore_post(p)
#define cyg_semaphore_wait(p)
#endif
#define cyg_semaphore_peek(p1,p2)
#define cyg_semaphore_timed_wait mmp_semaphore_timed_wait
#define cyg_semaphore_trywait    mmp_semaphore_trywait
#define cyg_semaphore_destroy    mmp_semaphore_destroy

#define cyg_cond_init            mmp_cond_init
#define cyg_cond_wait            mmp_cond_wait
#define cyg_cond_signal          mmp_cond_signal
#define cyg_cond_destroy         mmp_cond_destroy
#define cyg_cond_broadcast       mmp_cond_broadcast

#define cyg_thread_create        mmp_thread_create
#define cyg_thread_release       mmp_thread_release
//#define cyg_thread_exit          mmp_thread_exit
#define cyg_thread_exit()
#define cyg_thread_yield         mmp_thread_yield
#define cyg_thread_delete        mmp_thread_delete
#define cyg_thread_self          mmp_thread_self
//#define cyg_thread_delay         mmp_thread_delay
#define cyg_thread_delay         MsSleep
#define cyg_thread_resume        mmp_thread_resume
#define cyg_thread_check_exit    mmp_thread_check_exit

#define cyg_flag_setbits         mmp_flag_setbits
#define cyg_flag_maskbits        mmp_flag_maskbits
#define cyg_flag_init            mmp_flag_init
#define cyg_flag_destroy         mmp_flag_destroy

#define cyg_current_time         mmp_get_current_time


#define fs_opendir(x)    opendir(x)
#define fs_open(x,y)  open(x, y)
#define fs_rename(x,y)  rename(x, y)
#define fs_rmdir(x)   rmdir(x)
#define fs_unlink(x)  unlink(x)
#define fs_mkdir(x,y)  mkdir(x, y)
#define fs_stat(x,y)     stat(x, y)
#define fs_strrchr(x, y) strrchr(x, y)

#define fs_strcmp(x,y)   strcmp(x, y)
#define fs_strlen(x)  strlen(x)
#define fs_strcat(x, y)  strcat(x,y)
#define fs_strncpy(x, y, z)  strncpy(x, y, z)
#define fs_strcpy(x, y)  strcpy(x, y)
#define fs_strtok(x, y)  strtok(x, y)
#define fs_itoa(x, y)  itoa_(x, y)

#endif

