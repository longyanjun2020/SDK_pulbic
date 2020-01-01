/***********************************************************************
        Copyright (c) 2006 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _RV_H245_H
#define _RV_H245_H

#include "rvconfig.h"

#if (RV_H245_LEAN_H223 == RV_YES)
#include "h245_lean.h"
#define h245GetSyntax h245_leanGetSyntax

#elif (RV_H245_LEAN_H223 == RV_NO)
#include "h245_full.h"
#define h245GetSyntax h245_fullGetSyntax

#else
#error RV_H245_LEAN_H223 not defined!
#endif


#endif /* _RV_H245_H */
