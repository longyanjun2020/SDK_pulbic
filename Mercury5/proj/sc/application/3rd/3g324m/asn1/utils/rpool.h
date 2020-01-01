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

/*
  rpool.h


  Rpool of memory handling.
  Allocates contineous memory for each chunk.

  - malloc
  - calloc
  - realloc
  - free
  - copy
  - move
  - compare

  */

#ifndef _RV_RPOOL_H
#define _RV_RPOOL_H


#include "rvtypes.h"
#include "rvlog.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Handle of an RPOOL object */
RV_DECLARE_HANDLE(HRPOOL);

/* Handle of an RPOOL memory element */
RV_DECLARE_HANDLE(HRPOOLELEM);



/*** construct ***/

/************************************************************************
 * rpoolConstruct
 * purpose: Create an RPOOL object.
 * input  : elemSize        - Size of elements in the RPOOL in bytes.
 *          maxNumOfBlocks  - Number of blocks in RPOOL.
 *          threadSafe      - RV_TRUE to make allocations and deallocations
 *                            thread-safe.
 *          name            - Name of RPOOL (used in log messages).
 *          logMgr          - Log manager to use.
 * output : none
 * return : Handle to RPOOL constructed on success.
 *          NULL on failure.
 ************************************************************************/
RVINTAPI HRPOOL RVCALLCONV
rpoolConstruct(
    IN int              elemSize,
    IN int              maxNumOfBlocks,
    IN RvBool           threadSafe,
    IN const RvChar*    name,
    IN RvLogMgr*        logMgr);


/************************************************************************
 * rpoolClear
 * purpose: Clear the RPOOL from any allocations
 * input  : pool    - RPOOL handle
 * output : none
 * return : none
 ************************************************************************/
void rpoolClear(IN HRPOOL pool);


/************************************************************************
 * rpoolDestruct
 * purpose: Deallocate an RPOOL object
 * input  : pool    - RPOOL handle
 * output : none
 * return : none
 ************************************************************************/
RVINTAPI void RVCALLCONV
rpoolDestruct(IN HRPOOL pool);




/*** allocation handling ***/

/************************************************************************
 * rpoolAlloc
 * purpose: Allocate a chunk of memory from RPOOL.
 *          The allocation is automatically set to zero in all of its bytes
 * input  : pool    - RPOOL handle
 *          size    - Size of allocation in bytes
 * output : none
 * return : Pointer to memory chunk on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI HRPOOLELEM RVCALLCONV
rpoolAlloc(
      IN HRPOOL pool,
      IN int    size);


/************************************************************************
 * rpoolAllocCopyExternal
 * purpose: Allocate a chunk of memory from RPOOL and set it to a specified
 *          value from a buffer in memory
 * input  : pool    - RPOOL handle
 *          offset  - Offset to allocate the memory at
 *          src     - Source pointer of the external buffer set
 *                    If NULL, then the memory allocated is set to zero
 *          size    - Size of allocation in bytes
 * output : none
 * return : Pointer to memory chunk on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI HRPOOLELEM RVCALLCONV
rpoolAllocCopyExternal(
       IN HRPOOL        pool,
       IN int           offset,
       IN const void*   src,
       IN int           size);


/************************************************************************
 * rpoolAllocCopyInternal
 * purpose: Allocate a chunk of memory from RPOOL and duplicate its value
 *          from another allocation in RPOOL
 * input  : destPool- Destination RPOOL handle, where the new buffer will
 *                    be allocated
 *          srcPool - Source RPOOL handle, where the buffer we copy from
 *                    resides
 *          src     - Source pointer of the internal buffer set
 *                    It is actually an RPOOL allocation handle returned
 *                    by rpoolAlloc() and other functions in RPOOL
 *                    If NULL, then the memory allocated is set to zero
 *          size    - Size of allocation in bytes
 * output : none
 * return : Pointer to memory chunk on success
 *          NULL on failure
 ************************************************************************/
HRPOOLELEM rpoolAllocCopyInternal(
       IN HRPOOL        destPool,
       IN HRPOOL        srcPool,
       IN const void*   src,
       IN int           size);


/************************************************************************
 * rpoolRealloc
 * purpose: Reallocate chunk of memory, leaving any old bytes with the
 *          same value they had previously and setting new allocated
 *          bytes to zero.
 * input  : pool    - RPOOL handle
 *          src     - Element in RPOOL ot reallocate
 *          size    - Size of allocation in bytes
 * output : none
 * return : Non-negative value on success, other on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
rpoolRealloc(
       IN HRPOOL        pool,
       IN HRPOOLELEM    ptr,
       IN int           size);


/************************************************************************
 * rpoolFree
 * purpose: Free an element allocation in RPOOL
 * input  : pool    - RPOOL handle
 *          ptr     - Element in RPOOL
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
rpoolFree(
     IN HRPOOL      pool,
     IN HRPOOLELEM  ptr);




/* Internal Operations */


/************************************************************************
 * rpoolCopyFromExternal
 * purpose: Copy an external memory buffer into an RPOOL element
 * input  : pool    - RPOOL handle
 *          dest    - Element in RPOOL to copy to
 *          src     - Source buffer in memory
 *          shift   - Offset in RPOOL block to copy to
 *          size    - Size of buffer to copy
 * output : none
 * return : Destination element on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI HRPOOLELEM RVCALLCONV
rpoolCopyFromExternal(
    IN HRPOOL       pool,
    IN HRPOOLELEM   dest,
    IN const void*  src,
    IN int          shift,
    IN int          size);


/************************************************************************
 * rpoolCopyToExternal
 * purpose: Copy information from an RPOOL element to a memory buffer
 * input  : pool    - RPOOL handle
 *          dest    - Destination buffer in memory
 *          src     - Element in RPOOL to copy from
 *          shift   - Offset in RPOOL block to copy from
 *          size    - Size of buffer to copy
 * output : none
 * return : Destination memory buffer on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI void*  RVCALLCONV
rpoolCopyToExternal(
    IN HRPOOL       pool,
    IN void*        dest,
    IN HRPOOLELEM   src,
    IN int          shift,
    IN int          size);



int /* as memcmp returns */
rpoolCompareExternal(
             /* Compare dest to src */
             HRPOOL pool,
             HRPOOLELEM dest,
             void *src,
             int size
             );


/* Compares two allocated elements from pool */
/* Returns int that is less , equal greater then 0 */
/* if ptr1 is less, equal or greater than ptr2*/
int
rpoolCompareInternal(
             IN HRPOOL      pool,
             IN HRPOOLELEM  ptr1,
             IN HRPOOLELEM  ptr2,
             IN int         size
             );


/*** status ***/


#if 0
void
rpoolPrint(
      /* print pool allocated and free chunks into stdout. */
      HRPOOL pool
      );
#endif

RVINTAPI RvStatus RVCALLCONV
rpoolStatistics(
           /* Get pool statistics (space is in bytes) */
           IN  HRPOOL pool,
           OUT RvInt32* poolSize, /* max size of pool */
           OUT RvInt32* maxUsedSpace, /* maximum space allocated in the past */
           OUT RvInt32* allocatedSpace  /* currently allocated space */
          );

RVINTAPI int RVCALLCONV
rpoolChunkSize(
           IN HRPOOL        pool,
           IN HRPOOLELEM    ptr
           );


/***************************************************************************************
 * rpoolGetPtr
 *
 * purpose: To get an hrpool message and offset and return a real pointer to that location
 *          and the length until the end of the contiguous part.
 *          If the offset reaches or exceeds the end of the element the length is returned as -1
 *
 * Input:  pool - the pool in question
 *         element - the element on which we are working
 *         offset - the offset in bytes into the element
 *
 * Output: pointer - A real pointer to the place calculated by the offset.
 *
 * returned value: Length - The size of the contiguous area from the pointer to the end
 *                          of the current segment of the element.
 *                 0 - The offset is out of the RPOOL element's range
 *                 Negative value - Failure.
 ****************************************************************************************/
RVINTAPI int RVCALLCONV
rpoolGetPtr(IN  HRPOOL      pool,
            IN  HRPOOLELEM  element,
            IN  int         offset,
            OUT void**      pointer);

/******************************************************************************
 * raAddWatchdogResource
 * ----------------------------------------------------------------------------
 * General: Add an RA instance as a resource handled by the watchdog.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  raH          - RA instance handle.
 *         watchdog     - The watchdog instance to add this RA to.
 *         name         - Name of resource to use.
 *         group        - Group name for this resource.
 *         description  - Short description about this resource.
 *****************************************************************************/
#define rpoolAddWatchdogResource(_pool, _watchdog, _name, _group, _description) \
    raAddWatchdogResource((HRA)(_pool), (_watchdog), (_name), (_group), (_description))


/***************************************************************************************
 * rpoolGetElemSize
 *
 * purpose: To get the size of a single element, as given in rpoolConstruct.
 *
 * Input:  pool - the pool in question
 *
 * Output: none.
 *
 * returned value: The size an element.
 ****************************************************************************************/
RVINTAPI int RVCALLCONV
rpoolGetElemSize(IN  HRPOOL      pool);


#ifdef __cplusplus
}
#endif

#endif  /* _RV_RPOOL_H */

