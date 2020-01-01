/***********************************************************************
Filename   : rvrandomgenerator.h
Description: Random number generator
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
#ifndef RV_RANDOMGENERATOR_H
#define RV_RANDOMGENERATOR_H

#include "rvtypes.h"
#include "rverror.h"

typedef RvUint32 RvRandom;

#define RV_RAND_MAX ((RvRandom)~0)


typedef struct
{
	RvRandom state; /* State of the random generator's seed value */
} RvRandomGenerator;


#if defined(__cplusplus)
extern "C" {
#endif 

/********************************************************************************************
 * RvRandomGeneratorConstruct
 * construct a random generator object.
 * INPUT   : r - a random generator object.
 *           seed - random generator seed.
 * OUTPUT  : None
 * RETURN  : RV_OK.
 */
RVCOREAPI RvStatus RVCALLCONV
RvRandomGeneratorConstruct(IN RvRandomGenerator* r, IN RvRandom seed);

#define RvRandomGeneratorDestruct(_r) ((_r)->state = RV_OK)

#define RvRandomGeneratorGetMax(_r) (RV_RAND_MAX)

/********************************************************************************************
 * RvRandomGeneratorGetValue
 * returns a random value.
 * INPUT   : r - a random generator object.
 * OUTPUT  : value - the random value.
 * RETURN  : RV_OK.
 */
RVCOREAPI RvStatus RVCALLCONV
RvRandomGeneratorGetValue(IN RvRandomGenerator* r, OUT RvRandom* value);

/********************************************************************************************
 * RvRandomGeneratorGetInRange
 * returns a random value.
 * INPUT   : r - a random generator object.
 * INPUT   : n - maximal random value.
 * OUTPUT  : value - the random value in range [0;n-1].
 * RETURN  : RV_OK/RV_ERROR_BADPARAM - if value==NULL
 */
RVCOREAPI RvStatus RVCALLCONV
RvRandomGeneratorGetInRange(RvRandomGenerator* r, RvRandom n, OUT RvRandom* value);

#if defined(__cplusplus)
}
#endif 

#endif /* RV_RANDOMGENERATOR_H */

