/* rvadtstamp.h - rvadtstamp header file */
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

#ifndef RV_ADTSTAMP_H
#define RV_ADTSTAMP_H


#include "rvccore.h"

/* Lets make error codes a little easier to type */
#define RvTimestampErrorCode(_e) RvErrorCode(RV_ERROR_LIBCODE_CCORE, RV_CCORE_MODULE_TIMESTAMP, (_e))


/* Module specific error codes (-512..-1023). See rverror.h dor more details */
#define RV_TIMESTAMP_ERROR_NOCPUINFO RvTimestampErrorCode(-512) /* Linux only: /proc/cpuinfo file not found */
#define RV_TIMESTAMP_ERROR_NOTSC     RvTimestampErrorCode(-513) /* Linux only: CPU does not have TSC */
#define RV_TIMESTAMP_ERROR_NOMHZ     RvTimestampErrorCode(-514) /* Linux only: can't find CPU speed in /proc/cpuinfo */
#define RV_TIMESTAMP_ERROR_ZEROSPEED RvTimestampErrorCode(-515) /* CPU frequency of 0 reported */



#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************************
 * RvAdTimestampInit
 *
 * Called by RvTimestampInit.
 * Allows the timestamp adapter to perform OS specific module initialization.
 *
 * INPUT   : None.
 * OUTPUT  : None.
 * RETURN  : RV_OK if successful otherwise an error code.
 */
RvStatus RvAdTimestampInit(void);


/********************************************************************************************
 * RvAdTimestampEnd
 *
 * Called by RvTimestampEnd.
 * Allows the timestamp adapter to perform OS specific module clean up.
 *
 * INPUT   : None.
 * OUTPUT  : None.
 * RETURN  : None.
 */
void RvAdTimestampEnd(void);


/********************************************************************************************
 * RvAdTimestampGet
 *
 * Returns a timestamp value in nanoseconds. Values always grow up linearly.
 * This function is defined by pointer, which is set on adapter initialization.
 * This way enables the adapter to make some tests in run time before it chooses
 * the best realization of this function.
 * Function pointer declared here saves extra function call.
 *
 * INPUT   : None.
 * OUTPUT  : None.
 * RETURN  : Nanosecond timestamp.
 */
typedef RvInt64 (*RvAdTimestampGet_f)(void);
extern RvAdTimestampGet_f RvAdTimestampGet;


/********************************************************************************************
 * RvAdTimestampResolution
 *
 * Called by RvTimestampResolution.
 * Returns the resolution of the timestamp in nanoseconds.
 *
 * INPUT   : None.
 * OUTPUT  : None.
 * RETURN  : Resolution of the timestamp in nanoseconds.
 */
RvInt64 RvAdTimestampResolution(void);

#ifdef __cplusplus
}
#endif


#endif
