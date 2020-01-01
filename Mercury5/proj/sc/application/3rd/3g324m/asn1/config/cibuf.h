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

/***************************************************************************

  cibuf.h  --  Configuration buffer services interface

***************************************************************************/


#ifndef __CIBUF_H
#define __CIBUF_H


#ifdef __cplusplus
extern "C" {
#endif



#define CI_BUF_ID_STRING   "**BUF**"    /* with an appended asciiz */
#define CI_BUF_ID_LEN      8


RVAPI
RvInt32 RVCALLCONV ciTargetBufferSize(
        IN  HCFG  hCfg
        );


RVAPI
int RVCALLCONV ciPrepareTargetBuffer(
        IN OUT  void *  buffer,
        IN      RvInt32 bufferSize
        );


RVAPI
int RVCALLCONV ciAllocateTargetBuffer(
        IN   HCFG     hCfg,
        OUT  void **  buffer,
        OUT  int *    bufferSize
        );


RVAPI
int RVCALLCONV ciFreeTargetBuffer(
        IN  HCFG    hCfg,
        IN  void *  buffer
        );



#ifdef __cplusplus
}
#endif


#endif /* __CIBUF_H */
