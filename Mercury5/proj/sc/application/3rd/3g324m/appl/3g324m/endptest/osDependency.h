/************************************************************************
        Copyright (c) 2003 RADVISION Inc. and RADVISION Ltd.
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

/********************************************************************************************
 *                                osDependency.h
 *
 * Operating Systems dependent code needed for test applications.
 * This code allows better execution of our test applications in all the OSs we support
 * without making them too big to handle.
 * This file should be included in each of the source files of the test application itself
 *
 *
 *
 ********************************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

#include "rvtypes.h"
#include <stdlib.h>
#include <stdio.h>


/******************************************************************************
 * GetFilename
 * ----------------------------------------------------------------------------
 * General: Return the given filename in a way that should work on the given
 *          filesystem.
 *
 * Return Value: Filename to use for the given file system
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  filename - Base filename, without any path
 *****************************************************************************/
const RvChar* GetFilename(IN const RvChar* filename);





#if (RV_OS_TYPE == RV_OS_TYPE_WINCE)
/*---------------------------- Windows CE -------------------------------*/

int ceprintf(const char* string, ...);

/* Replace the old printf() */
#undef printf
#define printf ceprintf

#endif



#ifdef __cplusplus
}
#endif


