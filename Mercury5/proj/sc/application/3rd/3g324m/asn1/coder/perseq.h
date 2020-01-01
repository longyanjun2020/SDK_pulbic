#ifdef __cplusplus
extern "C" {
#endif



/*
***********************************************************************************

NOTICE:
This document contains information that is proprietary to RADVISION LTD..
No part of this publication may be reproduced in any form whatsoever without
written prior approval by RADVISION LTD..

RADVISION LTD. reserves the right to revise this publication and make changes
without obligation to notify any person of such revisions or changes.

***********************************************************************************
*/

/*
  perSequence.h
  */

#ifndef _PERSEQUENCE_
#define _PERSEQUENCE_

int
perEncodeSequece(IN  HPER hPer,
         IN  int synParent,
         IN  int valParent,
         IN  RvInt32 fieldId);
int
perDecodeSequece(IN  HPER hPer,
         IN  int synParent, /* parent in syntax tree */
         IN  int valParent, /* field parent in value tree */
         IN  RvInt32 fieldId);   /* enum of current field */

#endif
#ifdef __cplusplus
}
#endif



