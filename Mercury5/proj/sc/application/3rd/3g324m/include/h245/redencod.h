/***********************************************************************
        Copyright (c) 2005 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _REDENCOD_H
#define _REDENCOD_H

#include "cmH245GeneralDefs.h"

#ifdef __cplusplus
extern "C" {
#endif



typedef enum
{
  cmRedEncNonStandard=0,
  cmRedEncRtpAudio,
  cmRedEncH263Video
}cmRedundancyEncodingMethod;


typedef enum
{
  cmRoundrobin=0 ,
  cmCustom
}cmFrameToThreadMappingEnum;

typedef struct
{
  RvUint8 cmContainedThreads[256];
  RvUint8 cmContainedThreadsSize;
}cmContainedThreadsStruct;

typedef struct
{
  RvUint8                       cmNumberOfThreads;
  RvUint16                      cmFramesBetweenSyncPoints;
  cmContainedThreadsStruct      cmContainedThreads;
  cmFrameToThreadMappingEnum    cmFrameToThreadMapping;
}cmRTPH263VideoRedundancyEncoding;

typedef struct
{
  RvUint8 cmThreadNumber;
  RvUint8 cmFrameSequence[256];
  RvUint8 cmFrameSequenceSize;
}cmRTPH263RedundancyFrameMapping;



#if (RV_H245_LEAN_H223 == RV_NO)

RVAPI int RVCALLCONV
cmCreateNonStandardRedMethod(   IN   HAPP            hApp,
                                IN  cmNonStandardParam *nonStandard);

RVAPI int RVCALLCONV
cmAddH263VCustomFrameMapping( IN     HAPP            hApp,
                              int nodeId,
                              cmRTPH263RedundancyFrameMapping * rtpH263RedundancyFrameMapping,
                              int rtpH263RedundancyFrameMappingSize);


RVAPI int RVCALLCONV
cmCreateRtpAudioRedMethod( IN    HAPP            hApp);

RVAPI int RVCALLCONV
cmCreateH263VideoRedMethod( IN   HAPP            hApp,
                            IN cmRTPH263VideoRedundancyEncoding * h263VRedundancyEncoding);

RVAPI int RVCALLCONV
cmGetRedundancyEncodingMethod (IN    HAPP            hApp,
                               IN int redEncMethodId,
                               OUT cmRedundancyEncodingMethod * encodingMethod);
RVAPI int RVCALLCONV
cmGetH263RedundancyEncoding (IN  HAPP            hApp,
                             IN int h263EncMethodId,
                             OUT cmRTPH263VideoRedundancyEncoding * rtpH263RedundancyEncoding);
RVAPI int RVCALLCONV
cmGetCustomFrameToThreadMapping (IN  HAPP            hApp,
                             IN int h263EncMethodId,
                             INOUT cmRTPH263RedundancyFrameMapping * rtpH263RedundancyFrameMapping,
                             INOUT int * rtpH263RedundancyFrameMappingSize );

RVAPI int RVCALLCONV
cmAddH263VCustomFrameMapping( IN     HAPP            hApp,
                              int nodeId,
                              cmRTPH263RedundancyFrameMapping * rtpH263RedundancyFrameMapping,
                              int rtpH263RedundancyFrameMappingSize);


#endif


#ifdef __cplusplus
}
#endif

#endif
