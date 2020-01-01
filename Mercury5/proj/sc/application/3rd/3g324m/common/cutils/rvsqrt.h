/************************************************************************
 File Name     : rvansi.h
 Description   :
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

#ifndef RV_SQRT_H
#define RV_SQRT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rvtypes.h"

#if RV_SQRT_TYPE != RV_SQRT_NONE

/* Define RvSqrt and export appropriate library function macro depending on chosen algorithm */

/* RV_SQRT_TYPE is a bit mask of  RV_SQRT_STANDARD, RV_SQRT_MBORG, RV_SQRT_ALGR, etc */
#if RV_SQRT_TYPE & RV_SQRT_STANDARD 
/* standard sqrt is available, use it */	

#include <math.h>

#ifndef RvSqrt
#define RvSqrt(n) (RvUint32)sqrt((double)(n))
#endif

#endif /*  RV_SQRT_TYPE & RV_SQRT_STANDARD */

#if RV_SQRT_TYPE & RV_SQRT_MBORG  

#ifndef RvSqrt
#define RvSqrt RvSqrtMborg   /* rename RvSqrt to be RvSqrtMborg */
#endif

RVCOREAPI
RvUint32 RVCALLCONV RvSqrtMborg(RvUint32 n);

#endif /* RV_SQRT_TYPE & RV_SQRT_MBORG */


#if RV_SQRT_TYPE & RV_SQRT_FRED

#ifndef RvSqrt
#define RvSqrt RvSqrtFred   /* rename RvSqrt to be RvSqrtFred */
#endif

RVCOREAPI
RvUint32 RVCALLCONV RvSqrtFred(RvUint32 n);

#endif  /* RV_SQRT_TYPE & RV_SQRT_FRED */

#if RV_SQRT_TYPE & RV_SQRT_ALGR

#ifndef RvSqrt
#define RvSqrt RvSqrtAlgr  /* rename RvSqrt to be RvSqrtAlgr */
#endif

RVCOREAPI
RvUint32 RVCALLCONV RvSqrtAlgr(RvUint32 n);

#endif /* RV_SQRT_TYPE & RV_SQRT_ALGR */

#if RV_SQRT_TYPE & RV_SQRT_FAST

#ifndef RvSqrt
#define RvSqrt RvSqrtFast
#endif

RVCOREAPI
RvUint32 RVCALLCONV RvSqrtFast(RvUint32 n);

#endif

#endif  /* RV_SQRT_TYPE != RV_SQRT_NONE */

#ifdef __cplusplus
}
#endif

#endif
