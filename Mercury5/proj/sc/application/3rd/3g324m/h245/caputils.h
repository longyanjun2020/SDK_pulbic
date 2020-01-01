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


#ifndef _CAPUTILS_
#define _CAPUTILS_

#include "cmH245GeneralDefs.h"
#include "cmctrl.h"


#ifdef __cplusplus
extern "C" {
#endif


int
capStructBuild(
           IN  HPVT hVal,
           IN  int capEntryId,
           cmCapStruct *capability
           );

int
capSetBuild(
        /* build array of capability set */
        IN  HPVT hVal,
        IN  int termCapSetId, /* terminalCapabilitySet node id */
        IN  int capabilitiesSize, /* number of elements in capabilities array */
        OUT cmCapStruct** capabilities /* cap names array */
        );

/******************************************************************************
 * capDescBuild
 * ----------------------------------------------------------------------------
 * General: Build an array of capability descriptors from a TCS message sorted
 *          in ascending order of capabilityDescriptorNumbers.
 *          The capDesc array is built in 4 hierarchical levels:
 *          CapabilityDescriptor -> simultaneousCapabilities ->
 *          AlternativeCapabilitySet -> CapabilityTableEntry.
 *          Each one of the above 4 levels is built on capDesc according to hierarchy
 *          and separated by NULL pointers.
 *          Therefore, the caller to this function, should do a (cmCapStruct****)
 *          casting to capDesc to be able to read the content of the array.
 *          The figure below displays how it is done:
 *
 *          A: Alternative
 *          S: Simultaneous
 *          D: Descriptor
 *          -: null
 *
 *          (capDesc)
 *          \/
 *          ---------------------------------------------------------
 *          | D D ..D - S S S - S S - ==>  ...  <== A A - A A A A - |
 *          ---------------------------------------------------------
 *
 *
 * Return Value: If successful - Non negative.
 *               other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hVal              - The PVT handle.
 *         termCapSetId      - TerminalCapabilitySet node id.
 *         capabilities      - The actual capabilities from capabilityTable in TCS.
 *         capSetArraySize   - Maximum size of the capabilities array.
 *         capDescArraySize  - Number of elements in capDesc array.
 * Output: capDesc           - The descriptors array. This array should be allocated
 *                             before calling this function.
 *****************************************************************************/
int capDescBuild(
         IN  HPVT           hVal,
         IN  int            termCapSetId,
         IN  cmCapStruct    **capabilities,
         IN  int            capSetArraySize,
         IN  int            capDescArraySize,
         OUT void           **capDesc);


int
capStructBuildFromStruct(
             /* build single capability entry */
             IN  HPVT hVal,
             IN  int confRootId, /* configuration root id */
             OUT int capId,
             IN  cmCapStruct *capability
             );
int
capSetBuildFromStruct(
              /* Build capability table from capability structure array.
             - The capabilityId field is updated here.
             - if name != 0 then the configuration channel data definition is used.
             - if name == 0 and capabilityHandle >=0 then the specified data tree is used.
             - type and direction values shall be set.
             */
              IN  HPVT hVal,
              IN  int confRootId, /* configuration root id */
              OUT int termCapSetId, /* terminalCapabilitySet node id */
              IN  cmCapStruct** capabilities /* cap names array */
              );

int
capDescBuildFromStruct(
               /* build capability combinations from nested array.
              - The capabilityId shall be set to correct value, meaning
              this is called after capStructBuildFromStruct().
              */
               IN  HPVT hVal,
               OUT int termCapSetId, /* terminalCapabilitySet node id */
               IN  cmCapStruct*** capabilities[] /* cap names array */
               );


#ifdef __cplusplus
}
#endif

#endif



