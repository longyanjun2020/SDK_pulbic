/*
*********************************************************************************************************
*                         AIT Multimedia Network Streaming Server
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: Definition of OS Abstraction Layer
*
*/
#ifndef __AMN_OS_ABS_LAYER_DEFINITIONS__
#define __AMN_OS_ABS_LAYER_DEFINITIONS__


#define AMN_EVMAN_MSGQ_DEPTH  MAX_QUEUE_ENTRIES

////////////////////////////////////////////////////////////////////////////////
#ifdef __AMN_OS_LINUX__
///////////////////////////////////////
#define INLINE  inline
//#define __AMNSS_TCPIP_USE_LWIP__     // Under Linux, we may use LWIP or not
#else
///////////////////////////////////////
#ifndef INLINE
#define INLINE  __inline
#endif

#include "os_wrap.h"
#include "cdvmem.h"
#include "mmpf_hw_counter.h"
#include "mmpf_timingmark.h"
#if defined (__RTK_OS__)
#include "halex_timer.h"
#endif
//#include "fs_api.h"

#define __TMARK_ENABLE               0
#define TIMING_GROUP__MQUE_SYNC        0x00000010
#define TIMING_GROUP__THREAD_SEL       0x00000020
#define TIMING_GROUP__THREAD_MQUE      0x00000040
#define TIMING_GROUP__GRAB_FRAME       0x00000080
#define TIMING_GROUP__XMIT_FRAME       0x00000100
#define TIMING_GROUP__                 0x00000100

#define __LITTLE_ENDIAN     0
#define __BIG_ENDIAN        1

#define __AMNSS_TCPIP_USE_LWIP__       // Under uC/OS, we will always use LWIP
#define __BYTE_ORDER __LITTLE_ENDIAN
///////////////////////////////////////
#endif

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#ifdef __AMNSS_TCPIP_USE_LWIP__
///////////////////////////////////////
//#include "arch/cc.h"
#include "opt.h"
#include "arch.h"
#include "init.h"
#include "mem.h"
#include "memp.h"
#include "sys.h"
#include "tcpip.h"
#include "sockets.h"

#ifndef SOL_TCP
#define SOL_TCP IPPROTO_TCP
#endif
#ifndef net_fcntl
#define net_fcntl lwip_fcntl
#endif

// lwip/sockets.h will define the blow to lwip_xxx
#ifndef __ENABLE_LWIP_SOCKET_REDEFINE__
#undef read
#undef write
#undef close
#endif

#else
///////////////////////////////////////
typedef unsigned   char    u8_t;    /* Unsigned 8 bit quantity         */
typedef signed     char    s8_t;    /* Signed    8 bit quantity        */
typedef unsigned   short   u16_t;   /* Unsigned 16 bit quantity        */
typedef signed     short   s16_t;   /* Signed   16 bit quantity        */
typedef unsigned   int     u32_t;   /* Unsigned 32 bit quantity        */
typedef signed     int     s32_t;   /* Signed   32 bit quantity        */
typedef unsigned   int     uint_t;  /* Unsigned int, CPU's WORD width  */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>
#include <endian.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
///////////////////////////////////////
#endif

#include "list.h"


////////////////////////////////////////////////////////////////////////////////
/////////////// DEBUGGING APIs ////////////////////////////
#define DBGL_ERR          1
#define DBGL_WARN         2
#define DBGL_INFO         3
#define DBGL_VERBOSE      4
#define DBGL_DEBUG        5
#define DBGL_NONE         255

#ifdef __AMN_OS_LINUX__
extern u32_t osal_debug_flag;
#endif

/////// Timing Mark APIs ///////////////////////////////////////
#if __TMARK_ENABLE
extern u32_t osal_systime_init;
static INLINE u32_t osal_systime()
{
	if (osal_systime_init == 0)
		osal_systime_init = MMPF_OsCounterGet();
	return (MMPF_OsCounterGet() - osal_systime_init) * 10 / MMPF_OsCounterGetFreqKhz();
}

#define osal_timingmark_init()   do { \
	osal_systime(); \
	MMPF_TimingInit(5000); \
	MMPF_TimingStart(TIMING_GROUP__THREAD_MQUE | TIMING_GROUP__THREAD_SEL | TIMING_GROUP__MQUE_SYNC | TIMING_GROUP__GRAB_FRAME | TIMING_GROUP__XMIT_FRAME); \
} while (0)

#define osal_timingmark(a,b,c)   do { \
	static int iTiming = c; \
	MMPF_TimingMarkF(a,b,iTiming++); \
} while (0)

#define osal_timingmark_cnt(a,b,c)   MMPF_TimingMarkF(a,b,c)

#else
#define osal_timingmark_init()
#define osal_timingmark(a,b,c)
#define osal_timingmark_cnt(a,b,c)
#define osal_systime()                 0
#endif

#if defined (__RTK_OS__)
#define OSAL_TIMER_MAX_COUNTER			(HAL_GLOBAL_TIMER_MAX_COUNT/GLOBAL_CLK_N)
#endif
#ifdef __AMN_OS_LINUX__
//*******************************************************************************************************
// Linux POSIX abstraction
//*******************************************************************************************************
#define osal_exit(n) do { \
		osal_dprint(ERR, "Will EXIT the system -- %d !!!", n); \
		exit(n); \
} while (0)

#define osal_strerror()               strerror( errno )
#define cc__func__                    __FUNCTION__


/////////////// DEBUGGING APIs ////////////////////////////
#ifdef __AMNSS_DEBUG__
//
#define osal_dprint( level, fmt, ... ) do { \
	if (DBGL_ ## level <= osal_debug_flag) \
		printf( "##" #level "## %s:%d " fmt "\n", cc__func__, __LINE__, ##__VA_ARGS__); \
} while (0)

#define osal_ftrace() printf( "##FT## %s %s:%d \n", __FILE__, cc__func__, __LINE__)

// conditional print, expected to be placed at busy execution path, only output conditionally
#define osal_cond_print(fmt, ...) do { \
	if (*cond_print_var) printf( fmt "\n", ##__VA_ARGS__); \
} while(0)

// conditional print with TIME
#define osal_cond_tprint(fmt, ...) do { \
	struct timeval now; \
	time_now( &now ); \
	osal_cond_print( "[%d] " fmt, (now.tv_sec << 20) + now.tv_usec, ##__VA_ARGS__); \
} while(0)

#else
#define osal_dprint( level, fmt, ... )
#define osal_ftrace()
#define osal_cond_print(fmt, ...)
#define osal_cond_tprint(fmt, ...)
#endif
#define osal_dbglevel(level)    DBGL_ ## level <= osal_debug_flag

#define osal_assert( exp, fmt, ... )  do { \
		if (!(exp)) { \
			osal_dprint( ERR, "ASSERT: " #exp fmt, ##__VA_ARGS__ ); \
		} \
} while (0)


/////// TIMING MANAGEMENT APIs ////////////////////////////
#define time_now( tv )       gettimeofday( (tv), NULL )
#define osal_time(tloc)      time(tloc)     // time in seconds, since the Epoch
#define osal_msleep(msec)    usleep(msec * 1000)

static INLINE u32_t osal_jiffies(void)      // it's a fake system clock ticks
{
	struct timeval now;
	time_now( &now );
	return now.tv_sec * 1000 + now.tv_usec / 1000;
}

/////// MEMORY MANAGEMENT APIs ////////////////////////////
#define osal_free(ptr) do { \
	if (!ptr)  osal_dprint(WARN, "freeing NULL memory, from %s", __FILE__); \
	else       free(ptr); \
} while(0);

#define osal_zmalloc(sz) ({ /* simple memory allocation */ \
	void *ptr = malloc(sz); \
	memset(ptr, 0, sz); \
	ptr; \
})

#define osal_malloc(sz)          malloc(sz)
#define osal_realloc(ptr, sz)    realloc(ptr, sz)

#define osal_bgmalloc(sz)        malloc(sz) /* memory allocation of BIG size requirement */
#define osal_bgfree(ptr)         osal_free(ptr)


/////// PTHREAD SYNCHRONIZATION APIs ////////////////////////////
#define osal_mutex_t   pthread_mutex_t 

#define osal_mutex_init(m)              pthread_mutex_init(m, NULL)
#define osal_mutex_destroy(m)           pthread_mutex_destroy(m)
#define osal_mutex_lock(m)              pthread_mutex_lock(m)
#define osal_mutex_unlock(m)            pthread_mutex_unlock(m)

typedef pthread_t osal_thread_pid_t;
static INLINE osal_thread_pid_t  osal_thread_getpid()
{
	return pthread_self();
}
#define osal_thread_equal(t1, t2)       pthread_equal(t1, t2)

#define osal_thread_new(f,d)            do { \
	pthread_t thread; \
	pthread_create( &thread, NULL, f, d ); \
} while(0);

#define osal_thread_RETURN   NULL
typedef void * osal_thread_t;

/////// Message Queue for EventManager /////////////////////////
#if 0
typedef struct __msg_queue_t {
	mqd_t sndID;
	mqd_t rcvID;
} osal_msg_queue_t;

#define osal_mque_new(mq)   do { \
	struct mq_attr attr; \
	memset( &attr, 0, sizeof(attr)); \
	attr.mq_maxmsg = AMN_EVMAN_MSGQ_DEPTH; \
	attr.mq_msgsize = sizeof(void*); \
	mq_unlink("/amnss_mque" __TIME__); \
	(mq)->sndID = mq_open("/amnss_mque" __TIME__, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, &attr); \
	(mq)->rcvID = mq_open("/amnss_mque" __TIME__, O_RDONLY ); \
	osal_dprint(VERBOSE, "MsgQue ID %d, %d", (mq)->sndID, (mq)->rcvID); \
} while (0)

#define osal_mque_post(mq, msg, prio)       mq_send((mq).sndID, (char*)(&(msg)), sizeof(void*), prio)
#define osal_mque_pend(mq, msg)             mq_receive((mq).rcvID, (char*)(&(msg)), 1 + sizeof(void*), NULL)
#else
#define osal_msg_queue_t              mqd_t
#define osal_mque_new(mq)   do { \
	struct mq_attr attr; \
	memset( &attr, 0, sizeof(attr)); \
	attr.mq_maxmsg = AMN_EVMAN_MSGQ_DEPTH; \
	attr.mq_msgsize = sizeof(void*); \
	mq_unlink("/amnss_mque"); \
	*(mq) = mq_open("/amnss_mque", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, &attr); \
	osal_dprint(VERBOSE, "MsgQue ID %d", *(mq)); \
} while (0)

#if 0
static INLINE int osal_mque_post(osal_msg_queue_t mq, void *msg, int prio)
{
	struct   timespec tm;
	clock_gettime(CLOCK_REALTIME, &tm);
	tm.tv_sec += 1;
	return mq_timedsend(mq, (char*)(&(msg)), sizeof(void*), prio, &tm);
}
#else
#define osal_mque_post(mq, msg, prio)       mq_send(mq, (char*)(&(msg)), sizeof(void*), prio)
#endif

#define osal_mque_pend(mq, msg)             mq_receive(mq, (char*)(&(msg)), 1 + sizeof(void*), NULL)
#endif

#define osal_mque_check_err(res)            (res < 0)

static INLINE int osal_mque_query(osal_msg_queue_t mq)
{
	struct mq_attr attr = { 0 };
	mq_getattr( mq, &attr );
	return attr.mq_curmsgs;
}


#else // __AMN_OS_LINUX__
//*******************************************************************************************************
// uC/OS-II abstraction
//*******************************************************************************************************
#define osal_exit(n) do { \
		osal_dprint(ERR, "Will EXIT the system -- %d !!!", n); \
		return n; \
} while (0)

static INLINE char *osal_strerror()
{
	static char buf[16];
	sprintf( buf, "%d", errno );
	return buf;
}

#define cc__func__                    (char*)__func__

/////////////// DEBUGGING APIs ////////////////////////////
#ifdef __AMNSS_DEBUG__
#if 1
#define DPRINTF_VER 3
void amn_dprintf(short level, const char* func, int line, const char *format, ...);
#if DPRINTF_VER == 2
    #define osal_dprint(level, ...) do {amn_dprintf(DBGL_ ## level, "##" #level "## " cc__func__, __LINE__, __VA_ARGS__);} while(0)
#elif DPRINTF_VER == 3
    #define osal_dprint(level, ...) do {amn_dprintf(DBGL_ ## level, cc__func__, __LINE__, __VA_ARGS__);} while(0)
#endif
#else
#define osal_dprint( level, ... ) do { \
	if (DBGL_ ## level <= osal_debug_flag) { \
		ait_printf( "##" #level "## %s:%d ", cc__func__, __LINE__ ); \
		ait_printf( __VA_ARGS__ ); \
		ait_printf( "\n" ); \
	} \
} while (0)
#endif
#define osal_ftrace() ait_printf( "##FT## %s %s:%d""\r\n", __MODULE__, cc__func__, __LINE__)

// conditional print, expected to be placed at busy execution path, only output conditionally
#define osal_cond_print(fmt, ...) do { \
	if (*cond_print_var)  printd( fmt "\n", __VA_ARGS__); \
} while(0)

// conditional print with TIME
#define osal_cond_tprint(fmt, ...) do { \
	MMP_ULONG msec; \
	MMPF_OS_GetTime( &msec ); \
	osal_cond_print( "[%d] " fmt, msec, __VA_ARGS__); \
} while(0)

#else
#define osal_dprint( level, fmt, ... )
#define osal_ftrace()
#define osal_cond_print(fmt, ...)
#define osal_cond_tprint(fmt, ...)
#endif
#define osal_dbglevel(level)    DBGL_ ## level <= osal_debug_flag

#define osal_assert( exp, fmt, ... )  do { \
        if (!(exp)) { \
            osal_dprint( ERR, "ASSERT: " fmt, ##__VA_ARGS__ ); \
        } \
} while (0)

//#if !defined(TARGETOS_ucos) && !defined(TARGETOS_car)
#if !defined (__RTK_OS__)
int strcasecmp (const char *s1, const char *s2);
//#define strcmpi strcasecmp
int	strcmpi(char *s1, char *s2);
#endif
int stricmp (const char *s1, const char *s2);
int strncasecmp(const char* pszStr1, const char* pszStr2, size_t len);
/////// TIMING MANAGEMENT APIs ////////////////////////////
static INLINE void time_set( struct timeval *tr, u32_t msec );
#define time_now( tv )   do { \
	MMP_ULONG msec; \
	MMPF_OS_GetTime( &msec ); \
	time_set( tv, msec ); \
} while (0)

static INLINE u32_t osal_jiffies(void)    // it's a genuine system clock ticks
{
	MMP_ULONG msec;
	MMPF_OS_GetTime( &msec );
	return msec;
}
#define osal_msleep(msec)    MMPF_OS_Sleep(msec)
// time functions
#include <time.h>
#define ASCTIME_R_BUFFER_SIZE 26
typedef struct _FS_FILETIME FS_FILETIME;
time_t filetime2time_t(FS_FILETIME* ft);
struct tm *gmtime_r(const time_t *timer, struct tm *tmbuf);
char *asctime_r(const struct tm *tm, char *buf);


/////// MEMORY MANAGEMENT APIs ////////////////////////////
#if defined (__RTK_OS__)
#define osal_free(ptr) do { \
	if (!ptr)  osal_dprint(WARN, "freeing NULL memory, from %s", __FILE__); \
	else       mem_free((void*)(ptr)); \
} while(0);
#else
#define osal_free(ptr) do { \
	if (!ptr)  osal_dprint(WARN, "freeing NULL memory, from %s", __FILE__); \
	else       mem_free((void*)TO_PHYSICAL((unsigned int)ptr)); \
} while(0);
#endif
#include "stats.h"
static INLINE void* amn__malloc(u32_t sz, const char *func, int LineNo)
{
#if LWIP_DEBUG_LEVEL >= 2
    void *ptr = _mem_malloc(sz, func, LineNo);
#else
    void *ptr = mem_malloc(sz);
#endif

	if (!ptr) {
		ait_printf( "##WARN## %s:%d NULL malloc(%d)\n", func, LineNo, sz);
		MEM_STATS_DISPLAY(&lwip_stats);
	}
	return ptr;
}

static INLINE void* __zmalloc(int sz, const char *func, int LineNo)
{
	void *ptr = amn__malloc( sz, func, LineNo );
	if (ptr != NULL) {
	    memset(ptr, 0, sz);
	}
	return ptr;
}

static INLINE void* __realloc(void *ptr, int sz, const char *func, int LineNo)
{
	void *np = NULL;

	if (ptr == NULL)
		return amn__malloc( sz, func, LineNo );

	if (sz > 0) {
		np = amn__malloc( sz, func, LineNo );
		if (np) {
		    memcpy( np, ptr, sz );
        	osal_free( ptr );
		}
	}
	return np;
}

#define osal_zmalloc(sz)        __zmalloc(sz,  cc__func__, __LINE__ )
#define osal_malloc(sz)         amn__malloc(sz,   cc__func__, __LINE__ )
#define osal_realloc(ptr, sz)   __realloc(ptr, sz, cc__func__, __LINE__ )

#define osal_bgmalloc(sz)       osal_malloc(sz)  /* memory allocation of BIG size requirement */
#define osal_bgfree(ptr)        osal_free(ptr)


/////// PTHREAD SYNCHRONIZATION APIs ////////////////////////////
#define osal_mutex_t   				u32
#define	OSAL_MUTEX_CODE				(0xFE)
#define osal_mutex_init(m)      	sys_sem_new(m,1)
#define osal_mutex_destroy(m)   	sys_sem_free(m)
//#define osal_mutex_lock(m)      	sys_arch_sem_wait(m,0)
//#define osal_mutex_unlock(m)    	sys_sem_signal(m)
//#define	osal_mutex_lockwait(m, t)	sys_arch_sem_wait(m, t)
#define	osal_mutex_query(m, c, w)	sys_arch_sem_query(m, c)//MMPF_OS_QuerySemEx( *(m), c, w)
#define	osal_mutex_queryEx(m, c)	sys_arch_sem_query(m, c)

static INLINE int	osal_mutex_lock(sys_sem_t *sem)
{
	u32 ret;

	ret = sys_arch_sem_wait(sem, 0);

	if (ret == SYS_ARCH_TIMEOUT) return -1;

	return 0;
}

static INLINE int	osal_mutex_unlock(sys_sem_t *sem)
{
	u32 ret = ERR_MEM;
	s16 cnt;

	sys_arch_sem_query(sem,&cnt);

	if(cnt <= 0)
		ret = sys_sem_signal(sem);

	return ret;
}

static INLINE int	osal_mutex_lockwait(sys_sem_t *sem, u32 timeout)
{
	u32 ret;

	ret = sys_arch_sem_wait(sem, timeout);

	if (ret == SYS_ARCH_TIMEOUT)
		return -1;
	else
		return 0;
}

typedef int osal_thread_pid_t;
static INLINE osal_thread_pid_t  osal_thread_getpid(void)
{
	return sys_thread_getpid();
}
#define osal_thread_equal(t1, t2)    ((t1) == (t2))

#define osal_thread_new(f,d)    sys_thread_new( #f, f, d, LWIP_STK_SIZE, 0 )
int sys_thread_avaliable(int stacksize, int prio);

#define osal_thread_RETURN
typedef void osal_thread_t;

/////// Message Queue for EventManager /////////////////////////
extern void* m_AMN_EvMan_MsgQ[];

#define osal_msg_queue_t	u32

static INLINE int osal_mque_new(osal_msg_queue_t *mq)
{
	sys_mbox_t mbox;

	if(ERR_OK == sys_mbox_new( &mbox, AMN_EVMAN_MSGQ_DEPTH)) {
		*mq = mbox->QId;
		return 0;
	}
	else {
		osal_dprint(ERR, "Create MQ Failed \r\n"); 
		*mq = 0xff;
		return -1;
	}
}

static INLINE int osal_mque_post(osal_msg_queue_t mq, void *msg, int prio)
{
	sys_mbox_t mbox;

	osal_timingmark( TIMING_GROUP__MQUE_SYNC, "[MQPost] %d ", 0 );
	mbox = sys_mbox_find_by_id(mq);
	sys_mbox_post(&mbox,msg);
	return 0;
}

static INLINE int __mque_pend(osal_msg_queue_t mq, void **msg)
{
	u32 res;
	sys_mbox_t mbox;

	mbox = sys_mbox_find_by_id(mq);
	res = sys_arch_mbox_fetch(&mbox, msg, 0);
	osal_timingmark( TIMING_GROUP__MQUE_SYNC, "[MQPend] %d ", 0 );  // [MQPost] -> [MQPend] : schedudling delay

	if(SYS_ARCH_TIMEOUT != res)
		return 0;
	else
		return -1;
}

static INLINE int osal_mque_query(osal_msg_queue_t mq)
{
	u16_t uwCount;
	sys_mbox_t mbox;

	mbox = sys_mbox_find_by_id(mq);
	sys_mbox_query(&mbox,&uwCount);

	return uwCount;
}

#define osal_mque_pend(mq, msg)             __mque_pend(mq, (void*)&(msg))
#define osal_mque_check_err(res)            (res != 0)


#endif // __AMN_OS_LINUX__
//*******************************************************************************************************
// this meter provides basic statistics measurements of data values

#define METER_EXP_AVERAGE_ALPHA       256    // we will use 2^N to simplify division operation
struct ammo_basic_meter_t {
	// static fields
	//-----------------------------------------------------
	char  *name;
    u16_t period;    // period of meter counting
    u8_t  div_shift; // period in 2^N power shift for division

	// dynamic fields
	//-----------------------------------------------------
    u32_t count;
    u32_t exp_avg;   // exponential average
    u32_t sum_val;   // summation of metering values over observation <period>, for simple-AVERAGE
    u32_t max_val;   // maximum over observation <period>
    u32_t min_val;   // minimum over observation <period>
};

void basic_meter_init( struct ammo_basic_meter_t *m, int period, char *name );
void basic_meter_measure( struct ammo_basic_meter_t *m, u32_t val );


//*******************************************************************************************************

/////// COMMON DEBUGGING APIs ////////////////////////////
#if defined(__AMNSS_DEBUG__) && !defined(__AMN_OS_LINUX__)
#define MAX_CALL_TRACE   32

#define osal_ctrace(_v) do { \
	if (__ctrace_mutex_lock == (osal_mutex_t)-1)  osal_mutex_init( &__ctrace_mutex_lock ); \
	osal_mutex_lock( &__ctrace_mutex_lock ); \
	__ctrace_file[call_trace_index] = __FILE__; \
	__ctrace_func[call_trace_index] = cc__func__; \
	__ctrace_line[call_trace_index] = __LINE__; \
	__ctrace_time[call_trace_index] = osal_jiffies(); \
	__ctrace_pid[call_trace_index]  = osal_thread_getpid(); \
	__ctrace_var[call_trace_index]  = (unsigned)(_v); /* generic variable */ \
	call_trace_index = (call_trace_index + 1) % MAX_CALL_TRACE; \
	osal_mutex_unlock( &__ctrace_mutex_lock ); \
} while(0)

#define osal_get_ctrace(_i, _F, _f, _l, _p, _t, _v) do { \
	int j = (call_trace_index - i - 1 + 2*MAX_CALL_TRACE) % MAX_CALL_TRACE; \
	_F = __ctrace_file[j]; \
	_f = __ctrace_func[j]; \
	_l = __ctrace_line[j]; \
	_p = __ctrace_pid[j]; \
	_t = __ctrace_time[j]; \
	_v = __ctrace_var[j]; \
} while(0)

#define osal_cond_print_var()   (*cond_print_var)
#define osal_set_cond_print(_v) do { /* _v should be an INT type variable */ \
	cond_print_var = &(_v); \
} while(0)


#ifdef __AMN_OS_MAIN__
// Vars for osal_ctrace() && osal_get_ctrace()
unsigned int call_trace_index=0;
char *__ctrace_file[MAX_CALL_TRACE];
char *__ctrace_func[MAX_CALL_TRACE];
unsigned __ctrace_line[MAX_CALL_TRACE];
unsigned __ctrace_pid[MAX_CALL_TRACE];
unsigned __ctrace_time[MAX_CALL_TRACE];
unsigned __ctrace_var[MAX_CALL_TRACE];
osal_mutex_t  __ctrace_mutex_lock = (osal_mutex_t)-1;

// Vars for osal_cond_print() & osal_cond_tprint()
int  *cond_print_var=NULL;
#else
extern unsigned int call_trace_index;
extern char *__ctrace_file[MAX_CALL_TRACE];
extern char *__ctrace_func[MAX_CALL_TRACE];
extern unsigned __ctrace_line[MAX_CALL_TRACE];
extern unsigned __ctrace_pid[MAX_CALL_TRACE];
extern unsigned __ctrace_time[MAX_CALL_TRACE];
extern unsigned __ctrace_var[MAX_CALL_TRACE];
extern osal_mutex_t  __ctrace_mutex_lock;

extern int  *cond_print_var;
#endif

#else
#define MAX_CALL_TRACE   0
#define osal_ctrace(_v)
#define osal_get_ctrace(_i, _F, _f, _l, _p, _t, _v)
#define osal_cond_print_var()       0
#define osal_set_cond_print(_v)
#endif


/////// TIMING MANAGEMENT APIs ////////////////////////////
#define time_msec(t)   (t)
#define time_sec(t)    (t * 1000)

#if(OSAL_TIMER_MAX_COUNTER != 0xFFFFFFFF)
u32_t time_diff(struct timeval * tr_start,struct timeval * tr_end );
#else
#define time_diff( tr_start, tr_end ) \
	(( ((tr_end)->tv_sec - (tr_start)->tv_sec) * 1000000 + \
		(tr_end)->tv_usec - (tr_start)->tv_usec + 500) / 1000)
#endif

#if(OSAL_TIMER_MAX_COUNTER != 0xFFFFFFFF)
#define time_add( tr, msec )  do { \
	if((tr)->sys_ms + msec > OSAL_TIMER_MAX_COUNTER){\
		(tr)->sys_ms = (tr)->sys_ms + msec - OSAL_TIMER_MAX_COUNTER;\
		(tr)->tv_isOV = 1;\
	}\
	else {\
		(tr)->sys_ms += msec;\
		(tr)->tv_isOV = 0;\
	}\
	(tr)->tv_sec  =  (tr)->sys_ms / 1000; \
	(tr)->tv_usec = ((tr)->sys_ms % 1000) * 1000; \
} while (0)
#else
#define time_add( tr, msec )  do { \
	(tr)->tv_sec  +=  msec / 1000; \
	(tr)->tv_usec += (msec % 1000) * 1000; \
	if( (tr)->tv_usec >= 1000000 ) { \
		(tr)->tv_usec -= 1000000; \
		++(tr)->tv_sec; \
	} \
} while (0)
#endif

static INLINE void time_set( struct timeval *tr, u32_t msec )
{
#if(OSAL_TIMER_MAX_COUNTER != 0xFFFFFFFF)
	(tr)->tv_isOV = 0;
	tr->sys_ms = msec;
#endif
	tr->tv_sec  =  msec / 1000;
	tr->tv_usec = (msec % 1000) * 1000;
}

static INLINE u32_t time_ago( struct timeval *tr )
{
	struct timeval now; 
	time_now( &now );
	return time_diff( tr, &now );
}

#define time_future( tr, msec )  do { \
	time_now( tr ); \
	time_add( tr, msec ); \
} while(0)

//*******************************************************************************************************


#endif
