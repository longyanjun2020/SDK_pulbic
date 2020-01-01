#ifndef SYSDEP_H
#define SYSDEP_H

/*
 * Copyright (c) 1990- 1993, 1996 Open Software Foundation, Inc.
 * Copyright (c) 1989 by Hewlett-Packard Company, Palo Alto, Ca. &
 * Digital Equipment Corporation, Maynard, Mass.
 * Copyright (c) 1998 Microsoft.
 * To anyone who acknowledges that this file is provided "AS IS"
 * without any express or implied warranty: permission to use, copy,
 * modify, and distribute this file for any purpose is hereby
 * granted without fee, provided that the above copyright notices and
 * this notice appears in all source code copies, and that none of
 * the names of Open Software Foundation, Inc., Hewlett-Packard
 * Company, or Digital Equipment Corporation be used in advertising
 * or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Neither Open Software
 * Foundation, Inc., Hewlett-Packard Company, Microsoft, nor Digital Equipment
 * Corporation makes any representations about the suitability of
 * this software for any purpose.
 */

/*!
 * \file
 */

//#include "ithread.h"

/* change to point to where MD5 .h's live */
/* get MD5 sample implementation from RFC 1321 */
//#include <time.h>
#include "gui_global.h"
#include "__md5.h"

#include "UpnpStdInt.h"
//typedef unsigned long long uint64_t;

#if 0	//PORT_UUID
#include <sys/types.h>

#ifdef WIN32
	/* Do not #include <sys/time.h> */
#else
	#include <sys/time.h>
#endif
#endif	// PORTUUID
/*! set the following to the number of 100ns ticks of the actual resolution of
 * your system's clock */
#define UUIDS_PER_TICK 1024

/*! Set the following to a call to acquire a system wide global lock. */
//extern ithread_mutex_t gUUIDMutex;

typedef uint64_t uuid_time_t;

typedef struct {
	char nodeID[6];
} uuid_node_t;

void get_ieee_node_identifier(uuid_node_t * node);
void get_system_time(uuid_time_t * uuid_time);
void get_random_info(unsigned char seed[16]);

struct timezone {
    int tz_minuteswest;     /* minutes west of Greenwich */
    int tz_dsttime;         /* type of DST correction */
};

struct timeval {
#if defined (__RTK_OS__)
  char 			tv_isOV;		/*to handle overflow case*/
  unsigned int 	sys_ms;			/*system time in ms*/
#endif
  long    		tv_sec;         /* seconds */
  long    		tv_usec;        /* and microseconds */
};

#if !defined(TARGETOS_car)
struct timespec {
    unsigned int    tv_sec;                 /* seconds */
    long            tv_nsec;                /* nanoseconds */
};
#endif

void gettimeofday(struct timeval *ptime, struct timezone *pzone);
int gethostname(char *name, size_t len);

#if 1//#if !defined(TARGETOS_car)
#define	usleep(s)	sys_msleep((s)/1000)
#endif

#define	isleep(s)	sys_msleep(s)
#endif /* SYSDEP_H */
