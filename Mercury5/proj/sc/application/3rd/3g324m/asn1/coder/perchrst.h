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


/*
  perCharString.h

  */

#ifndef _PERCHARSTRING_
#define _PERCHARSTRING_


#ifdef __cplusplus
extern "C" {
#endif


int perEncodeCharString(IN  HPER hPer,
            IN  int synParent,
            IN  int valParent, /* this is me */
            IN  RvInt32 fieldId);

int perDecodeCharString(IN  HPER hPer,
            IN  int synParent, /* parent in syntax tree */
            IN  int valParent, /* field parent in value tree */
            IN  RvInt32 fieldId);   /* enum of current field */



#ifdef __cplusplus
}
#endif

#endif /* _PERCHARSTRING_ */
