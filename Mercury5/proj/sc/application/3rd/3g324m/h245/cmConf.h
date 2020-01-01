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



#ifndef _CONFH_
#define _CONFH_

#include "pvaltree.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    confNonStandard=1,
    confNullData,
    confVideoData,
    confAudioData,
    confData,

    /* Not supported data types */
    confEncryptionData,
    confH235Control,
    confH235Media,
    confMultiplexedStream,
    confRedundancyEncoding,
    confMultiplePayloadStream,
    confFec
} confDataType;



int /* RV_TRUE or negative value on failure */
confLoad(
     /* Load configuration parameters */
     IN  HPVT hVal,
     IN  int confRootId,
     IN  char *prefix /* to configuration parameters */
     );

int /* RV_TRUE or negative value on failure */
confGetDataTypeName(
            /* Generate dataName using field name as in H.245 standard. */
            IN  HPVT hVal,
            IN  int dataTypeId, /* Data type node id */
            IN  int dataNameSize,
            OUT char *dataName, /* copied into user allocate space [128 chars] */
            OUT confDataType* type, /* of data */
            OUT RvInt32* typeId /* node id of media type */
            );

int
confGetDataType(
        /* Search channel name in channels conf. and create appropriate dataType tree */
        IN  HPVT hVal,
        IN  int confRootId,
        IN  const RvChar* channelName, /* in channels conf */
        OUT int dataTypeId, /* node id: user supplied */
        OUT RvBool* isDynamicPayload, /* true if dynamic */
        RvBool nonH235 /*If true means remove h235Media.mediaType level */
        );

int /* real number of channels or negative value on failure */
confGetChannelNames(
            /* build array of channels names as in configuration */
            IN  HPVT hVal,
            IN  int confRootId,
            IN  int nameArSize, /* number of elements in nameArray */
            IN  int nameLength, /* length of each name in array */
            OUT char** nameArray /* user allocated array of strings */
            );


int /* RV_TRUE if found. negative value if not found */
confGetModeEntry(
         /* Search mode name in configuration. */
         IN  HPVT hVal,
         IN  int confRootId,
         IN  char *modeName, /* in conf. */
         OUT RvInt32 *entryId /* mode entry id */
         );

#ifdef __cplusplus
}
#endif

#endif



