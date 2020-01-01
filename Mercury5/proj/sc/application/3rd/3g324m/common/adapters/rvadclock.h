/* rvadclock.h - rvadclock header file */
/************************************************************************
      Copyright (c) 2001 - 2008 RADVISION Inc. and RADVISION Ltd.
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

#ifndef RV_ADCLOCK_H
#define RV_ADCLOCK_H


#include "rvccore.h"
#include "rvtime.h"


#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************
 * RvAdClockInit
 *
 * Allows the clock adapter to perform OS specific module initialization.
 *
 * INPUT   : None.
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
void RvAdClockInit(void);


/********************************************************************************************
 * RvAdClockGet
 *
 * Returns a value of a clock converted to the RvType type.  Values always grow up linearly.
 *
 * INPUT   : valid pointer to the structure of the RvTime type.
 * OUTPUT  : pointer to the structure of RvTime type filled with the value of clock.
 * RETURN  : None.
 */
void RvAdClockGet(OUT RvTime * t);


/********************************************************************************************
 * RvAdClockSet
 *
 * Sets the the OS system clock to the value corresponding tothe specified value in nanoseconds.
 *
 * INPUT   : valid pointer to the structure of the RvTime type containing the time value to be set.
 * OUTPUT  : None.
 * RETURN  : Error code.
 */
RvStatus RvAdClockSet(IN const RvTime * t);


/********************************************************************************************
 * RvAdClockResolution
 *
 * Called by RvAdClockResolution.
 * Returns the resolution of the timestamp in nanoseconds.
 *
 * INPUT   : valid pointer to the structure of the RvTime type.
 * OUTPUT  : pointer to the structure of RvTime type filled with the value of resolution of the clock in nanoseconds.
 * RETURN  : None.
 */
void RvAdClockResolution(OUT RvTime * t);

#ifdef __cplusplus
}
#endif


#endif
