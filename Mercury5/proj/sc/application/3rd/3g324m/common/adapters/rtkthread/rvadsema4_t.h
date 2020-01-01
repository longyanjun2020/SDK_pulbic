/* rvadsema4_t.h - rvadsema4_t header file */
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

#ifndef RV_ADSEMA4_T_H
#define RV_ADSEMA4_T_H


#include "rvtypes.h"

#if (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_POSIX)

#include <semaphore.h>
typedef sem_t RvSemaphore;

#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_CONDVAR)

#include <pthread.h>

typedef struct {
    pthread_cond_t cond_var;
    pthread_mutex_t mutex;
    int sem_cnt;
    int waiters;
} RvSemaphore;

#elif (RV_SEMAPHORE_TYPE == RV_SEMAPHORE_RTK)

#define RvSemaphore short //rtk_Semaphor_t

#endif

typedef int RvSemaphoreAttr;


#endif
