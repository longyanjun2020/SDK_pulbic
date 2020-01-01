/***********************************************************************
        Copyright (c) 2003 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************

  strutils.h  --  String utilities interface

  Module Authors: Oz Solomonovich, Sasha Ruditsky
  This Comment:   1-Jan-1996

  Abstract:       Various string manipulation utilities.

  Platforms:      All,

  Known Bugs:     None.

****************************************************************************/


#ifndef __STRUTILS_H
#define __STRUTILS_H

#include "rvtypes.h"
#include "rverror.h"


/* ascii->bmp string - returns bytes written to target buffer */
RVINTAPI int RVCALLCONV
chr2bmp(IN const RvChar *str, OUT RvUint8 *bmpStr);

/* same as chr2bmp, with maximum length */
RVINTAPI int RVCALLCONV
chrn2bmp(IN const RvChar *str, IN RvSize_t maxStrLen, OUT RvUint8 *bmpStr);

/* bmp->ascii string - returns negative value on failure if conversion was unsuccessful */
RVINTAPI int RVCALLCONV
bmp2chr(OUT RvChar *str, IN const RvUint8 *bmpStr, IN RvSize_t bmpLen);

/* case insensitive strncmp */
int strncmp_ci(const RvChar *dst, const RvChar *src, RvSize_t count);



#endif  /* __STRUTILS_H */

#ifdef __cplusplus
}
#endif



