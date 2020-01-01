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

#ifndef CM_H245_MIB_H
#define CM_H245_MIB_H


#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    enumh245ControlChannelMSDState,
    enumh245ControlChannelTerminalType,
    enumh245ControlChannelNumberOfMSDRetries,
    enumh245ControlChannelIsTunneling,

    enumh245CapExchangeState,
    enumh245CapExchangeProtocolId,
    enumh245CapExchangeRejectCause,
    enumh245CapExchangeMultiplexCapability,
    enumh245CapExchangeCapability,
    enumh245CapExchangeCapabilityDescriptors,

    enumh245LogChannelsChannelState,
    enumh245LogChannelsMediaTableType,
    enumh245LogChannelsSessionId,
    enumh245LogChannelsAssociateSessionId,
    enumh245LogChannelsMediaChannel,
    enumh245LogChannelsMediaGuaranteedDelivery,
    enumh245LogChannelsMediaControlChannel,
    enumh245LogChannelsMediaControlGuaranteedDelivery,
    enumh245LogChannelsSilenceSuppression,
    enumh245LogChannelsDestination,
    enumh245LogChannelsDynamicRTPPayloadType,
    enumh245LogChannelsH261aVideoPacketization,
    enumh245LogChannelsRTPPayloadDescriptor,
    enumh245LogChannelsRTPPayloadType,
    enumh245LogChannelsTransportCapability,
    enumh245LogChannelsRedundancyEncoding,
    enumh245LogChannelsSrcTerminalLabel

}mibControlParamTypeT;


typedef enum
{
    lcseAwaitingEstablishment=1,
    lcseEstablished,
    lcseAwaitingRelease,
    lcseAwaitingConfirmation
}lcseStateT;


#ifdef __cplusplus
}
#endif


#endif  /* CM_H245_MIB_H */

