#if (0)
******************************************************************************
Filename    :
Description :
******************************************************************************
                Copyright (c) 1999 RADVision Inc.
************************************************************************
NOTICE:
This document contains information that is proprietary to RADVision LTD.
No part of this publication may be reproduced in any form whatsoever 
without written prior approval by RADVision LTD..

RADVision LTD. reserves the right to revise this publication and make 
changes without obligation to notify any person of such revisions or 
changes.
******************************************************************************
$Revision:$
$Date:$
$Author: S. Cipolli$
******************************************************************************
#endif
#ifndef RV_PTRVECTOR_H
#define RV_PTRVECTOR_H

#include "rvccore.h"
#include "rvvector.h"

#if defined(__cplusplus)
extern "C" {
#endif

rvDeclareVectorEx(RvVoidPtr,RVCOREAPI)

/* PtrVector iterators */
#define RvPtrVectorIter				RvVectorIter(RvVoidPtr)
#define rvPtrVectorIterData(i)		(i)
#define rvPtrVectorIterPrev(i)		((i) - 1)
#define rvPtrVectorIterNext(i)		((i) + 1)

#define RvPtrVectorIterData(i)		(i)
#define RvPtrVectorIterPrev(i)		((i) - 1)
#define RvPtrVectorIterNext(i)		((i) + 1)

#define RvPtrVectorRevIter			RvVectorRevIter(RvVoidPtr)
#define rvPtrVectorRevIterData(i)	(i)
#define rvPtrVectorRevIterPrev(i)	((i) + 1)
#define rvPtrVectorRevIterNext(i)	((i) - 1)

#define RvPtrVectorRevIterData(i)	(i)
#define RvPtrVectorRevIterPrev(i)	((i) + 1)
#define RvPtrVectorRevIterNext(i)	((i) - 1)

/* Public PtrVector interface */
typedef RvVector(RvVoidPtr) RvPtrVector;
#define rvPtrVectorConstruct		rvVectorConstruct(RvVoidPtr)
#define rvPtrVectorConstructN		rvVectorConstructN(RvVoidPtr)
#define rvPtrVectorConstructCopy	rvVectorConstructCopy(RvVoidPtr)
#define rvPtrVectorCopy				rvVectorCopy(RvVoidPtr)
#define rvPtrVectorDestruct			rvVectorDestruct(RvVoidPtr)
#define rvPtrVectorGetAllocator		rvVectorGetAllocator
#define rvPtrVectorSize				rvVectorSize
#define rvPtrVectorBegin			rvVectorBegin
#define rvPtrVectorEnd				rvVectorEnd
#define rvPtrVectorRevBegin			rvVectorRevBegin
#define rvPtrVectorRevEnd			rvVectorRevEnd
#define rvPtrVectorAt(v, i)			(rvVectorAt(v, i))
#define rvPtrVectorPopFront			rvVectorPopFront(RvVoidPtr)
#define rvPtrVectorPopBack			rvVectorPopBack(RvVoidPtr)
#define rvPtrVectorErase			rvVectorErase(RvVoidPtr)
#define rvPtrVectorClear			rvVectorClear(RvVoidPtr)
#define rvPtrVectorFill				rvVectorFill(RvVoidPtr)
#define rvPtrVectorSwap				rvVectorSwap(RvVoidPtr)
#define rvPtrVectorEqual			rvVectorEqual(RvVoidPtr)
#define rvPtrVectorRemoveIf			rvVectorRemoveIf(RvVoidPtr)

RVCOREAPI
RvVoidPtr rvPtrVectorFront(RvPtrVector* l);

RVCOREAPI
RvVoidPtr rvPtrVectorBack(RvPtrVector* l);

RVCOREAPI
RvPtrVectorIter rvPtrVectorPushBack(RvPtrVector* l, RvVoidPtr x);

RVCOREAPI
RvPtrVectorIter rvPtrVectorInsert(RvPtrVector* l, RvPtrVectorIter i, RvVoidPtr x);

#if defined(__cplusplus)
}
#endif

#endif
