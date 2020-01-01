/*
 * pthread
 */
#ifndef	__PTHREAD_H__
#define	__PTHREAD_H__

#include <stddef.h>
#include "sysdep.h"
/* Detach state.  */
enum
{
  PTHREAD_CREATE_JOINABLE,
#define PTHREAD_CREATE_JOINABLE	PTHREAD_CREATE_JOINABLE
  PTHREAD_CREATE_DETACHED
#define PTHREAD_CREATE_DETACHED	PTHREAD_CREATE_DETACHED
};

/* Scheduler inheritance.  */
enum
{
  PTHREAD_INHERIT_SCHED,
#define PTHREAD_INHERIT_SCHED   PTHREAD_INHERIT_SCHED
  PTHREAD_EXPLICIT_SCHED
#define PTHREAD_EXPLICIT_SCHED  PTHREAD_EXPLICIT_SCHED
};


/* Scope handling.  */
enum
{
  PTHREAD_SCOPE_SYSTEM,
#define PTHREAD_SCOPE_SYSTEM    PTHREAD_SCOPE_SYSTEM
  PTHREAD_SCOPE_PROCESS
#define PTHREAD_SCOPE_PROCESS   PTHREAD_SCOPE_PROCESS
};


/* Process shared or private flag.  */
enum
{
  PTHREAD_PROCESS_PRIVATE,
#define PTHREAD_PROCESS_PRIVATE PTHREAD_PROCESS_PRIVATE
  PTHREAD_PROCESS_SHARED
#define PTHREAD_PROCESS_SHARED  PTHREAD_PROCESS_SHARED
};



/* Conditional variable handling.  */
#define PTHREAD_COND_INITIALIZER { { 0, 0, 0, 0, 0, (void *) 0, 0, 0 } }

typedef struct {
	int		state;	
	size_t	stacksize;
	int		priority;
} pthread_attr_t;

typedef struct {
	pthread_attr_t	attr;
} pthread_t;

typedef	int	pthread_cond_t;
typedef int pthread_mutex_t;
typedef	void* pthread_mutexattr_t;
typedef void* pthread_condattr_t;	

//#define	pthread_mutex_init		(osal_mutex_init(m) >= 0xFE)
#define	pthread_mutex_lock		osal_mutex_lock
#define	pthread_mutex_unlock	osal_mutex_unlock
#define	pthread_mutex_destroy	osal_mutex_destroy
#define	pthread_mutex_lockwait	osal_mutex_lockwait

#define	pthread_cond_signal			pthread_mutex_unlock
#define	pthread_cond_wait(p1, p2)	pthread_mutex_unlock(p2);	\
									pthread_mutex_lock(p1);		\
									pthread_mutex_lock(p2)
									
#define	pthread_cond_init(p1, p2)	pthread_mutex_init(p1, p2)
#define	pthread_cond_destroy		pthread_mutex_destroy

#define	pthread_self	sys_thread_getpid

int pthread_mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr);
int pthread_attr_init(void *attr);
int pthread_attr_setstacksize(void* attr, size_t stacksize);
int pthread_attr_setdetachstate(void *attr, int state);
int pthread_attr_destroy(void *pattr);
int pthread_cond_broadcast(pthread_cond_t *cond);
struct timespec;
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, struct timespec* abstime);
int pthread_create(pthread_t *pthread, void *attr, void *(*start_routine)(void *), void *arg);
int pthread_detach(pthread_t thread);

#endif	// __PTHREAD_H__
