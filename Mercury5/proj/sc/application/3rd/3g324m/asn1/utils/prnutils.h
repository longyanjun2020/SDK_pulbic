/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _PRNUTILS_H
#define _PRNUTILS_H

#include "rvlog.h"

#ifdef __cplusplus
extern "C" {
#endif


#if (RV_LOGMASK & RV_LOGLEVEL_DEBUG)
RVINTAPI void RVCALLCONV
printHexBuff(RvUint8* buf, int len, RvLogSource * msa);
#else
#define printHexBuff(buf,len,msa)
#endif


#ifdef __cplusplus
}
#endif

#endif  /* _PRNUTILS_H */

