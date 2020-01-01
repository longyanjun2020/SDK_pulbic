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
  perSequenceOf.h
  */

#ifndef _PERSEQUENCEOF_
#define _PERSEQUENCEOF_

int
perEncodeSequeceOF(IN  HPER hPer,
           IN  int synParent,
           IN  int valParent, /* this is me */
           IN  RvInt32 fieldId);

int
perDecodeSequeceOF(IN  HPER hPer,
           IN  int synParent, /* parent in syntax tree */
           IN  int valParent, /* field parent in value tree */
           IN  RvInt32 fieldId);   /* enum of current field */


#endif
#ifdef __cplusplus
}
#endif



