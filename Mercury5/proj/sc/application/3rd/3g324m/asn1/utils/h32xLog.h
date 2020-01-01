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

#ifndef _H32X_LOG_H_
#define _H32X_LOG_H_

/***********************************************************************
h32xLog.h

Global log used and needed in H.323, since the Common Core uses a
log manager per instance.
***********************************************************************/


/*-----------------------------------------------------------------------*/
/*                        INCLUDE HEADER FILES                           */
/*-----------------------------------------------------------------------*/
#include "rvlog.h"



#ifdef __cplusplus
extern "C" {
#endif



/*-----------------------------------------------------------------------*/
/*                           FUNCTIONS HEADERS                           */
/*-----------------------------------------------------------------------*/


/******************************************************************************
 * H32xLogInit
 * ----------------------------------------------------------------------------
 * General: Initialize the global log manager.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  None.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV H32xLogInit(void);


/******************************************************************************
 * H32xLogEnd
 * ----------------------------------------------------------------------------
 * General: Deinitialize the global log manager.
 *
 * Return Value: RV_OK on success, other on failure.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  None.
 * Output: None.
 *****************************************************************************/
RVAPI RvStatus RVCALLCONV H32xLogEnd(void);


/******************************************************************************
 * H32xLogGet
 * ----------------------------------------------------------------------------
 * General: Get the global log manager for the use of H.323.
 *
 * Return Value: Global log manager used.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  None.
 * Output: None.
 *****************************************************************************/
RVAPI RvLogMgr* RVCALLCONV H32xLogGet(void);



#ifdef __cplusplus
}
#endif

#endif /* _H32X_LOG_H_ */
