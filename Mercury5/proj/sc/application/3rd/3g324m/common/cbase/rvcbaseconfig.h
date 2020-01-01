/***********************************************************************
Filename   : rvcbaseconfig.h
Description: cbase configuration
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
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
#ifndef RV_CBASECONFIG_H
#define RV_CBASECONFIG_H

/* Include configuration definitions. Look at this file for possible settings */
#include "rvcbasedefs.h"

/* rvqueue: Select queue type to use - Exclude by default !!! */
#if !defined(RV_QUEUE_TYPE)
#define RV_QUEUE_TYPE RV_QUEUE_NONE
#endif

/* rvtimer: Select timer type to use */
#define RV_TIMER_TYPE RV_TIMER_STANDARD

/* rvtimerengine: Select timer engine type to use */
#define RV_TIMERENGINE_TYPE RV_TIMERENGINE_STANDARD

#endif /* RV_CBASECONFIG_H */
