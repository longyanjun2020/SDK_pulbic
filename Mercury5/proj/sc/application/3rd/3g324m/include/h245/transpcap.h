/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _TRANSPCAP_H
#define _TRANSPCAP_H

#include "cmH245GeneralDefs.h"


#ifdef __cplusplus
extern "C" {
#endif




#define cmQosCapabilityNonStandard  0x1
#define cmQosCapabilityAtmParameters    0x2
#define cmQosCapabilityRsvpParameters   0x4

typedef enum
{
  cmNoneQos=0,
  cmGuaranteedQOS,
  cmControlledLoad

}cmQOSMode;

typedef struct
{
  cmQOSMode cmQosMode;
  RvBool    cmQosModeValue;
  RvInt32   cmTokenRate;
  RvInt32   cmBucketSize;
  RvInt32   cmPeakRate;
  RvInt32   cmMinPoliced;
  RvInt32   cmMaxPktSize;

}cmRSVPParameters;

typedef struct
{
  RvInt16   cmMaxNTUSize;
  RvBool    cmAtmUBR;
  RvBool    cmAtmrtVBR;
  RvBool    cmAtmnrtVBR;
  RvBool    cmAtmABR;
  RvBool    cmAtmCBR;
}cmATMParameters;



typedef enum
{
  cmIP_UDP=0,
  cmIP_TCP,
  cmAtm_AAL5_UNIDIR,
  cmAtm_AAL5_BIDIR
}cmMediaTransportType;


typedef struct
{
  cmMediaTransportType cmTransportType;
}cmMediaChannelCapability;




typedef struct
{
  cmNonStandardParam cmNonStandard;
  cmRSVPParameters cmRsvpParameters;
  cmATMParameters  cmAtmParameters;
  RvUint8 cmQosCapabilityParamUsed;
}cmQosCapability;


#if (RV_H245_SUPPORT_H225_PARAMS == RV_YES)


RVAPI int RVCALLCONV
cmCreateTranspCapability( IN     HAPP            hApp,
                            cmNonStandardParam *nonStandard
                            );

RVAPI int RVCALLCONV
cmAddQosCapability( IN   HAPP            hApp,
                      IN int capTransport,
                      IN  cmQosCapability *qosCapability);



RVAPI int RVCALLCONV
cmAddMediaChannelCap( IN     HAPP            hApp,
                        IN int capTransport,
                        IN  cmMediaChannelCapability * mediaCap
                       );


RVAPI int RVCALLCONV
cmGetTransportCapabilities(             IN  HCALL       hsCall);


RVAPI int RVCALLCONV
cmGetTransportCapNonStandard(   IN   HAPP            hApp,
                              IN int transpId,
                              OUT cmNonStandardParam *nonStandard   );

RVAPI int RVCALLCONV
cmGetTransportCapQosParameters(IN    HAPP            hApp,
                              IN int transpId,
                              INOUT  cmQosCapability * cmQOSCapability,
                              INOUT int  * cmQOSCapabilitySize);

RVAPI int RVCALLCONV
cmGetTransportCapMedia(IN    HAPP            hApp,
                              IN int transpId,
                              INOUT cmMediaChannelCapability * mediaChannelCapability ,
                              OUT int *mediaChannelCapabilitySize);


#endif /* (RV_H245_SUPPORT_H225_PARAMS == RV_YES) */

#ifdef __cplusplus
}
#endif

#endif  /* _TRANSPCAP_H */


