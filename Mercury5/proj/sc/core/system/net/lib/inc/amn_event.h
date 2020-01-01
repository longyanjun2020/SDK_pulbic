/*
*********************************************************************************************************
*                         AIT Multimedia Network Event Manager
*                     (c) Copyright 2012, Alpha Imaging Technology Corp.
*               All rights reserved. Protected by international copyright laws.
*********************************************************************************************************
*
* Description: Header definition for AIT Network Event Manager
*
*/
#ifndef __AMN_EVENT_MANAGER_CLASSES_DEFINITIONS__
#define __AMN_EVENT_MANAGER_CLASSES_DEFINITIONS__

// Event Message Manager
// Description: Event Manager handling the delivery of messages across Nodes & Pipelines
//              The implemenation relies on POSIX message queues on Linux (man mq_overview)
//              and Message Queue on uC/OS-II (OSQPost / OSQPend)
//*******************************************************************************************************
struct ammo_evmsg;
typedef void (*evmsg_cback_ft)( struct ammo_evmsg *m, void *d );

enum {
	AMMO_EVMSG_TYP__TIMER,
	AMMO_EVMSG_TYP__FD,
	AMMO_EVMSG_TYP__MESSAGE,
	AMMO_EVMSG_TYP__TOTAL,
	AMMO_EVMSG_TYP__END
};

#define AMMO_EVMSG_FLG__ENABLED     1
#define AMMO_EVMSG_FLG__RUNNING     2
#define AMMO_EVMSG_FLG__ONESHOT     4
#define AMMO_EVMSG_FLG__WAIT        8
#define AMMO_EVMSG_FLG__REMOVE     16

struct ammo_evmsg {
	struct list_head link;
	evmsg_cback_ft func;
	void *data;
	u8_t type;
	u8_t flags;

	u32_t time_embarked;  // time when this event was put into queue

	/// For AMMO_EVMSG_TYP__FD ////
	u8_t fd;
	u8_t write;  // 0 = read, 1 = write

	/// For AMMO_EVMSG_TYP__TIMER ////
	struct timeval fire;
	int ival;
};

#if 0  // whether to trace EVMSG calls, and shown by UARTCMD: net ass dbg 88
#define EVMSG_CALL_TRACE(v)    osal_ctrace(v)
#else
#define EVMSG_CALL_TRACE(v)
#endif

//*******************************************************************************************************
struct ammo_evmsg *evmsg_new_FD( int fd, int write, unsigned int flags, evmsg_cback_ft f, void *arg );
struct ammo_evmsg *evmsg_new_timer( int msec, unsigned int flags, evmsg_cback_ft f, void *arg );
struct ammo_evmsg *evmsg_new_alarm( struct timeval *t, unsigned int flags, evmsg_cback_ft f, void *arg );
struct ammo_evmsg *evmsg_new_message( evmsg_cback_ft f, void *arg, int wait );
#if 1
struct ammo_evmsg *evmsg_do(evmsg_cback_ft f, void* arg, int wait, int schedule);
#else
#define evmsg_do(f, arg, wait, schedule) if (schedule) evmsg_new_message( f, arg, 0 ); else f( NULL, arg )

#endif
void   evmsg_remove( struct ammo_evmsg *e );
void   evmsg_set_interval( struct ammo_evmsg *e, int msec );
void   evmsg_set_enabled( struct ammo_evmsg *e, int enabled );
int    evmsg_get_enabled( struct ammo_evmsg *e );
void   evmsg_initialize(void);

//*******************************************************************************************************
extern osal_mutex_t  evman_exec_lock;

#endif
