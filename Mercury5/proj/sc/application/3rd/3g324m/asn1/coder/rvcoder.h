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


#ifndef CODER_H
#define CODER_H

#include "pvaltree.h"


#ifdef __cplusplus
extern "C" {
#endif

RVAPI
int RVCALLCONV cmEmEncode(
            IN      HPVT            valH,
            IN      RvPvtNodeId     vNodeId,
            OUT     RvUint8*        buffer,
            IN      int             length,
            OUT     int*            encoded);

RVAPI
int RVCALLCONV cmEmEncodeTolerant(
            IN      HPVT            valH,
            IN      RvPvtNodeId     vNodeId,
            OUT     RvUint8*        buffer,
            IN      int             length,
            OUT     int*            encoded);

RVAPI
int RVCALLCONV cmEmDecode(
            IN      HPVT            valH,
            IN      RvPvtNodeId     vNodeId,
            IN      RvUint8*        buffer,
            IN      int             length,
            OUT     int*            decoded);


/************************************************************************
 * cmEmInstall
 * purpose: Initializes the encode/decode manager.
 *          This function should be called by applications that want to
 *          encode and decode ASN.1 messages without initializing and using 
 *          the CM for this purpose.
 * input  : maxBufSize  - Maximum size of the buffer that is supported (messages 
 *                        larger than this size in bytes cannot be decoded/encoded).
 * output : None.
 * return : Non-negative value on success. Negative value on failure.
 ************************************************************************/
RVAPI
int RVCALLCONV cmEmInstall(IN int maxBufSize);


/************************************************************************
 * cmEmEnd
 * purpose: Un-initializes the encode/decode manager.
 *          This function should be called by applications that called
 *          cmEmInstall() directly to clean up used memory.
 * input  : None.
 * output : None.
 * return : Non-negative value on success. Negative value on failure.
 ************************************************************************/
RVAPI
int RVCALLCONV cmEmEnd(void);



#ifdef __cplusplus
}
#endif

#endif

