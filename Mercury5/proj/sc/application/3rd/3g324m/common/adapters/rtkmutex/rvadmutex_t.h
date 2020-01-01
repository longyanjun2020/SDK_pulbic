/* rvadmutex_t.h - rvadmutex_t header file */
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

#ifndef RV_ADMUTEX_T_H
#define RV_ADMUTEX_T_H


#include "rvtypes.h"
#include <pthread.h>

//typedef short  pthread_mutex_t;

typedef short RvAdMutex;

/************************************************************************
 * RvMutexAttr:
 *	OS specific attributes and options used for mutexes. 
 *	See definitions in rvmutex.h
 *  along with the default values in rvccoreconfig.h for more information.
 ************************************************************************/
typedef struct {
	/* These correspond to attributes in the pthread_mutexattr struct that we let users set */
	int pshared;  /* used only by Solaris */
	int protocol; /* used only by Solaris */
} RvMutexAttr;


#endif
