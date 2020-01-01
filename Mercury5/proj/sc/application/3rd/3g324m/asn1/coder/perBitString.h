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

#ifndef _PERBITSTRING_
#define _PERBITSTRING_



#ifdef __cplusplus
extern "C" {
#endif


int
perEncodeBitString(IN  HPER hPer,
             IN  int synParent,
             IN  int valParent,
             IN  RvInt32 fieldId);

int
perDecodeBitString(IN  HPER hPer,
             IN  int synParent, /* parent in syntax tree */
             IN  int valParent, /* field parent in value tree */
             IN  RvInt32 fieldId);   /* enum of current field */


#ifdef __cplusplus
}
#endif


#endif

