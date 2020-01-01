/***********************************************************************
Filename   : rvstrutils.h
Description: rvstrutils header file
************************************************************************
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

/***********************************************************************
 This module provides string manipulations functions
 ***********************************************************************/

#ifndef RV_STRUTILS_H
#define RV_STRUTILS_H

#include "rvtypes.h"

#define RvStrcasecmp(s1, s2) strcasecmp(s1, s2)
#define RvStrncasecmp(s1, s2, size) strncasecmp(s1, s2, size) 

#if (RV_OS_TYPE == RV_OS_TYPE_WIN32)

#define strcasecmp(a,b)		_stricmp(a,b)
#define strncasecmp(a,b,n)	_strnicmp(a,b,n)

#endif

#if (RV_OS_TYPE == RV_OS_TYPE_VXWORKS) || (RV_OS_TYPE == RV_OS_TYPE_NUCLEUS)   || \
    (RV_OS_TYPE == RV_OS_TYPE_MOPI)    || (RV_OS_TYPE == RV_OS_TYPE_PSOS)      || \
    (RV_OS_TYPE == RV_OS_TYPE_OSE)     || (RV_OS_TYPE == RV_OS_TYPE_INTEGRITY) || \
    (RV_OS_TYPE == RV_OS_TYPE_WINCE)

#if defined(__cplusplus)
extern "C" {
#endif 
    
#define NEED_STRCASECMP
    
    
/********************************************************************************************
 * strcasecmp
 * Performs case insensitive comparison of two null terminated strings
 * INPUT   : s1
 *           s2 - strings to compare
 * OUTPUT  : None
 * RETURN  : 0 if strings are the same or lexical difference in the
 *           first differing character.
 */
RVCOREAPI 
int RVCALLCONV strcasecmp(
    IN const char *s1,
    IN const char *s2);

/********************************************************************************************
 * strncasecmp
 * Performs case insensitive comparison of first 'n' bytes of two strings
 * INPUT   : s1
 *           s2 - strings to compare
 *           n  - number of bytes to compare
 * OUTPUT  : None
 * RETURN  : 0 if strings are the same or lexical difference in the
 *           first differing character.
 */
RVCOREAPI 
int RVCALLCONV strncasecmp(
    IN const char *s1,
    IN const char *s2,
    IN size_t n);
       

#if defined(__cplusplus)
}
#endif

#else

#include <string.h>

#endif


#endif /* RV_STRUTILS_H */
