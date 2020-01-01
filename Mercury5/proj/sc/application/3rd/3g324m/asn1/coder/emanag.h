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

#ifndef EMANAG_H
#define EMANAG_H

#include "pvaltree.h"


#ifdef __cplusplus
extern "C" {
#endif
    

/* Struct holding information needed for encode/decode functions */
typedef struct 
{
    HPST        hSyn; /* syntax tree */
    HPVT        hVal; /* value tree */
    RvUint8     *buffer; /* Pointer to encode/decode buffer */
    int         length; /* Length of the buffer in bits */
    RvBool      isTolerant; /* RV_TRUE if we're allowing non-valid encodings */
} emanagStruct;


typedef enum {
  emPER,
  emQ931,
  emBER
} emPrivateTags;


typedef struct
{
    int (*Encode)(
        IN  emanagStruct    *emanag,
        IN  RvPvtNodeId     vNodeId,
        OUT int             *encoded);
    int (*Decode)(
        IN  emanagStruct    *emanag,
        IN  RvPvtNodeId     vNodeId,
        IN  RvInt32         fieldId,
        OUT int             *decoded);
} emTypeOfEncoding;


int emSetEncoding(
    IN  int                 privateTag,
    IN  emTypeOfEncoding*   encoding);

int emEncode(
    IN  emanagStruct    *emanag,
    IN  RvPvtNodeId     vNodeId,
    OUT int             *encoded);

int emDecode(
    IN  emanagStruct    *emanag,
    IN  RvPvtNodeId     vNodeId,
    IN  RvInt32         fieldId,
    OUT int             *decoded);



#ifdef __cplusplus
}
#endif

#endif /* EMANAG_H */
