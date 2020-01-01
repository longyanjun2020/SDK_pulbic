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
#ifndef _H324MCALLMUXTABLE_H_
#define _H324MCALLMUXTABLE_H_


#include "cmH245GeneralDefs.h"
#include "h324mStackObject.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************
 * muxProcessStruct
 * ----------------------------------------------------------------------------
 * General: This function receives data of a mux table entry and translates it
 *          into pvt tree.
 *          This function doesn't support canonical lists, as these are not
 *          supported by the multiplexer.
 *
 * Return Value: RV_OK  - if success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hH324m               - handle to the application
 *         entryIndex           - the table entry index.
 *         muxEntry             - the struct that represents one entry in the
 *                                mux table. This will be translated into the
 *                                pvt message.
 *         muxEntrySize         - The size of the muxEntry.
 *         descriptorsNodeId    - Node ID of type
 *                                MultiplexEntrySend.multiplexEntryDescriptors.
 *                                A new element in this SEQUENCE OF will be
 *                                created by this function call.
 * output: None.
 *****************************************************************************/
RvStatus  muxProcessStruct(
    IN    H324mStack   *h324m,
    IN    RvUint32      entryIndex,
    IN    TMuxTblAtom  *muxEntry,
    IN    RvUint32      muxEntrySize,
    IN    RvPvtNodeId   descriptorsNodeId);


/******************************************************************************
 * DEMUXProcessPvt
 * ----------------------------------------------------------------------------
 * General: get the data from the multiplexEntrySend message and put it into the
 *          local incoming MUX table.
 *          in the proccess of converting the data we also have to check that each
 *          table entry compile with the maxsimum demend of our mux.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hdemux       - Handle to a muxer instance.
 *         hVal         - Value tree handle
 *         message      - the nodeId of the message pvt tree
 * output: entries      - Entries we processed successfully
 *         isComplex    - In case we will fail to insert the data in the demux table
 *                        and have to return a reject APDU, this flag will tell us if
 *                        the reject reason is too complicated (isComplex == true) or is
 *                        it unspecified.
 *****************************************************************************/
RvStatus  DEMUXProcessPvt(
    IN  HDEMUX          hdemux,
    IN  HPVT            hVal,
    IN  RvPvtNodeId     message,
    OUT RvUint16        *entries,
    OUT RvBool          *isComplex);


#ifdef __cplusplus
}
#endif

#endif /* _H324MCALLMUXTABLE_H_ */
