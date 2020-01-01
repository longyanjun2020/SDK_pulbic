/* rvadthread_t.h - rvadthread header file */
/************************************************************************
      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/

#ifndef RV_ADTHREAD_T_H
#define RV_ADTHREAD_T_H


#include "rvtypes.h"
#include <pthread.h>

typedef short /*pthread_attr_t*/ RvThreadBlock; /* We use block for attributes since we don't want them touched directly */

/********************************************************************************************
 * RvThreadId
 * An OS specific thread ID. Used to identify threads regardless
 * of whether or not a thread handle has been constructed for it.
 ********************************************************************************************/
typedef short /*pthread_t*/ RvThreadId;

/********************************************************************************************
 * RvThreadAttr
 * OS specific attributes and options used for threads. See definitions in rvthread.h
 * along with the default values in rvccoreconfig.h for more information.
 ********************************************************************************************/
typedef struct {
    /* These correspond to attributes in the pthread_attr struct that we let users set */
    int contentionscope;
    int policy;
    int inheritsched;
#if (RV_OS_TYPE == RV_OS_TYPE_SOLARIS)
    size_t guardsize; /* Solaris extention to standard attributes (use (size_t)(-1) for default*/
#endif
} RvThreadAttr;

#define RV_THREAD_PRIORITY_MAX 0
#define RV_THREAD_PRIORITY_MIN 20
#define RV_THREAD_PRIORITY_INCREMENT (-1)

#if (RV_OS_TYPE == RV_OS_TYPE_NETBSD)
#define RV_THREAD_WRAPPER_STACK (64 + 1024)
#else
#define RV_THREAD_WRAPPER_STACK (64 + 1024)//(64 + PTHREAD_STACK_MIN)  //RTK modify
#endif

/* OS specific options */
#define RV_THREAD_AUTO_DELETE       RV_YES  /* whether thread auto-delete is supported or not */
#define RV_THREAD_SETUP_STACK       RV_NO   /* whether to allocate stack if stackaddr == NULL */
/* POSIX (and variations) allow user allocated stacks, */
/* but we can't support that option due to problems detecting thread exit. */
#define RV_THREAD_STACK_ADDR_USER   RV_NO   /* whether user allocated stack is supported or not */
#define RV_THREAD_STACK_SIZE_OS     RV_YES  /* whether OS can determine stack size or not */


#endif
