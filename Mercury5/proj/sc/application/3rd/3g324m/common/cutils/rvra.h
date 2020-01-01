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
  ra.h

  RADVISION static array implementation.

  The RA module provides basic memory allocation services to the rest of the
  stack moduels.
  RA is designed to be fast. Most validity checks are not done in release modes
  and on errors they send exception messages to the log.

*/


#ifndef RV_RA_H
#define RV_RA_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rvlog.h"
#include "rvtypes.h"



/* This definition makes sure we're using the workingSet feature in RA.
   RA uses a freelist from within the vacant elements. The usual allocation
   of elements from the freelist is done in FIFO mode, making it harder for
   the cache memory to be used sensibly. The working set breaks this
   implementation into smaller sets of allocations when possible, but also
   takes more time to calculate and handle.
   Put the following definition in a comment if you don't want to use the
   more complex working set implementation. */
#define RV_RA_SUPPORT_WORKING_SET

#if defined(RV_DEBUG)
#define RV_RA_DEBUG
#endif

#define getBit(ptr, bit) \
    ((unsigned int)(((RvUint8 *)(ptr))[((RvUint32)(bit))>>3] & (0x80 >> ((RvUint32)(bit) & 7))))


/************************************************************************
 * setBit
 * purpose: This marco is used to set a bit within a bits array to a RV_TRUE
 *          or RV_FALSE value
 * syntex : void setBit(RvUint8 *ptr, RvUint32 bit, unsigned int value);
 * input  : bitsBuffer  - Pointer to bits buffer
 *          bitIndex    - Bit to change (0-based)
 *          bitValue    - RV_TRUE/RV_FALSE value of the bit
 * output : none
 * return : none
 ************************************************************************/
#define setBit(bitsBuffer, bitIndex, bitValue)  \
{                                                                                       \
    if ((unsigned int)(bitValue))                                                       \
        ((RvUint8*)(bitsBuffer))[((RvUint32)(bitIndex)) >> 3] |=                        \
            (0x80 >> (((RvUint32)(bitIndex)) & 7));                                     \
    else                                                                                \
        ((RvUint8*)(bitsBuffer))[((RvUint32)(bitIndex)) >> 3] &=                        \
            ~(0x80 >> (((RvUint32)(bitIndex)) & 7));                                    \
}

#define setBitTrue(bitsBuffer, bitIndex) \
{                                                                                       \
        ((RvUint8*)(bitsBuffer))[((RvUint32)(bitIndex)) >> 3] |=                        \
            (0x80 >> (((RvUint32)(bitIndex)) & 7));                                     \
}

#define setBitFalse(bitsBuffer, bitIndex) \
{                                                                                       \
        ((RvUint8*)(bitsBuffer))[((RvUint32)(bitIndex)) >> 3] &=                        \
            ~(0x80 >> (((RvUint32)(bitIndex)) & 7));                                    \
}

/* Handle to an RA object */
RV_DECLARE_HANDLE(HRA);


/* RA element pointer declaration */
RV_DECLARE_HANDLE(RAElement);


/************************************************************************
 * resources struct
 ************************************************************************/
typedef struct
{
    RvUint32      cur; /* Current used elements */
    RvUint32      maxUsage; /* Maximum number of elements used since initialization */
    RvUint32      max; /* Maximum number of elements that can be used */
} RvRaStatistics;






/************************************************************************
 * RAECompare
 * purpose: Definition of compare function for RA elements
 * input  : element1    - The element to compare
 *          param       - Parameter given to raCompare function as context
 * output : none
 * return : RV_TRUE if elements are the same
 *          RV_FALSE otherwise
 ************************************************************************/
typedef RvBool (*RAECompare)(IN RAElement element1, IN void* param);


/************************************************************************
 * RAEFunc
 * purpose: Definition of a general function on an RA element
 * input  : elem    - Element to function on
 *          param   - Context to use for it
 * output : none
 * return : Pointer for the context to use on the next call to this
 *          RAEFunc.
 ************************************************************************/
typedef void*(*RAEFunc)(IN RAElement elem, IN void* param);



/************************************************************************
 * raHeader struct
 * This struct holds an RA object's main information.
 * This struct is declared in the header file for the macro support.
 *
 * This struct should not be accessed directly from outside ra.h and ra.c!
 ************************************************************************/
typedef struct
{
    RvChar      name[32]; /* Name of allocation */
    RvUint8*    arrayLocation; /* Pointer to the location of the actual data elements */
    RAElement   firstVacantElement; /* First vacant element in the array's free list
                                       This is the element we'll return when we want
                                       to allocate new elements */

#if defined(RV_RA_SUPPORT_WORKING_SET)
    RAElement   workingSetElement; /* The working set element in the array's free list.
                                      This is the element in the array's free list
                                      the we use to add deallocated elements just before it
                                      We use such a mechanism to enable better uses of the
                                      machine's cache. */
    int         workingSetSize; /* Desired size of the working set.
                                   This is the amount of elements we use for our working
                                   set. It is actually the desired distance between
                                   firstVacantElement and workingSetElement. */
    int         workingSetDistance; /* The current distance between firstVacantElement
                                       and workingSetElement. */
#else
    RAElement   lastVacantElement; /* Last vacant element in the array's free list */
#endif

    int         maxNumOfElements; /* Maximum number of elements */
    int         curNumOfElements; /* Current number of elements */
    int         maxUsage; /* Peak value of curElems */
    RvSize_t    sizeofElement; /* Size of a single element inside RA */
    RvSize_t    requestedSizeofElement; /* Size of a single element inside RA (as requested by user) */
    RAECompare  compare; /* Compare function used by RvRaFind() */
    RAEFunc     print; /* Print function used by raPrint() */

    /* Log */
    RvLogMgr*   logMgr; /* Log manager to use */
    RvLogSource log; /* Log handle to use for printouts */
    RvLogSource*pLog; /* Pointer to the log handle used (might be NULL if logMgr is NULL) */

    /* Thread safety */
    RvBool      threadSafe; /* RV_TRUE of RvRaAdd and RvRaDelete are thread-safe */
    RvLock      lock; /* Lock for RvRaAdd and RvRaDelete */
} raHeader;





/*********** array functions **************/

#define RV_RA_ELEM_DATA(ra, i) \
    ((char *) (((raHeader*)(ra))->arrayLocation + (i)*(((raHeader*)(ra))->sizeofElement)))






/************************************************************************
 * RvRaConstruct
 * purpose: Create an RA object.
 * input  : elemSize            - Size of elements in the RA in bytes.
 *          maxNumOfElements    - Number of elements in RA.
 *          threadSafe          - RV_TRUE to make RvRaAdd,RvRaDelete thread-safe.
 *          name                - Name of RA (used in log messages).
 *          logMgr              - Log manager used.
 * output : none
 * return : Handle to RA constructed on success.
 *          NULL on failure.
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvRaConstruct(
    IN int              elemSize,
    IN int              maxNumOfElements,
    IN RvBool           threadSafe,
    IN const RvChar*    name,
    IN RvLogMgr*        logMgr,
    OUT HRA*            hRa);


/************************************************************************
 * RvRaDestruct
 * purpose: Free an RA object, deallocating all of its used memory
 * input  : raH     - Handle of the RA object
 * output : none
 * return : none
 ************************************************************************/
RVCOREAPI void RVCALLCONV
RvRaDestruct(IN HRA raH);


/************************************************************************
 * RvRaClear
 * purpose: Clean an RA object from any used elements, bringing it back
 *          to the point it was when RvRaConstruct() was called.
 * input  : raH     - Handle of the RA object
 * output : none
 * return : none
 ************************************************************************/
RVCOREAPI void RVCALLCONV
RvRaClear(IN HRA raH);


/************************************************************************
 * RvRaSetCompareFunc
 * purpose: Set the compare function to use in RvRaFind()
 * input  : raH     - Handle of the RA object
 *          func    - Compare function to use
 * output : none
 * return : none
 ************************************************************************/
RVCOREAPI void RVCALLCONV
RvRaSetCompareFunc(IN HRA raH, IN RAECompare func);


/************************************************************************
 * RvRaSetPrintFunc
 * purpose: Set the print function to use in raPrint()
 * input  : raH     - Handle of the RA object
 *          func    - Print function to use
 * output : none
 * return : none
 ************************************************************************/
RVCOREAPI void RVCALLCONV
RvRaSetPrintFunc(IN HRA raH, IN RAEFunc func);


/************************************************************************
 * RvRaGetPrintFunc
 * purpose: Set the print function to use in raPrint()
 * input  : raH     - Handle of the RA object
 * output : none
 * return : Print function used by RA (given by RvRaSetPrintFunc)
 ************************************************************************/
RAEFunc RvRaGetPrintFunc(IN HRA raH);


/************************************************************************
 * RvRaAdd
 * purpose: Allocate an element in RA for use, without initializing its
 *          value.
 * input  : raH         - Handle of the RA object
 * output : pOutElem    - Pointer to the element added.
 *                        If given as NULL, it will not be set
 * return : Negative value on failure
 *          Non-negative value representing the location of the added
 *          element.
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvRaAdd(IN HRA raH, OUT RAElement *pOutElem, int* vLocation);


/************************************************************************
 * RvRaDelete
 * purpose: Delete an element from RA
 * input  : raH      - Handle of the RA object
 * output : delElem  - Element in RA to delete
 * return : Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvRaDelete(IN HRA raH, IN RAElement delElem);


/************************************************************************
 * RvRaDeleteLocation
 * purpose: Delete an element from RA by its location
 * input  : raH      - Handle of the RA object
 * output : location - Location of the element in RA
 * return : Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvRaDeleteLocation(IN HRA raH, IN int location);


/************************************************************************
 * RvRaGet
 * purpose: Get the pointer to an RA element by its location
 * input  : raH      - Handle of the RA object
 * output : location - Location of the element in RA
 * return : Pointer to the RA element
 *          In release mode, no checks are done for the validity or the
 *          vacancy of the location.
 ************************************************************************/
#ifdef RV_RA_DEBUG
RVCOREAPI RAElement RVCALLCONV
RvRaGet(IN HRA raH, IN int location);
#else
#define RvRaGet(raH, location) \
    (RAElement)(((RvUint)(location) >= (RvUint)(((raHeader*)raH)->maxNumOfElements)) ?  \
        NULL : RV_RA_ELEM_DATA((raH), (location)))
#endif


/************************************************************************
 * RvRaGetByPtr
 * purpose: Get the location of an RA element by its element pointer
 * input  : raH     - Handle of the RA object
 * output : ptr     - Pointer to the RA element's value
 * return : Location of the element on success
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvRaGetByPtr(IN HRA raH, IN const void *ptr, OUT int* position);


/************************************************************************
 * RvRaElemIsVacant
 * purpose: Check if an element is vacant inside RA or not
 * input  : raH         - Handle of the RA object
 *          location    - Location of RA element to check
 * output : none
 * return : RV_TRUE if element is vacant
 *          RV_FALSE if element is used
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI int RVCALLCONV
RvRaElemIsVacant(IN HRA raH, IN int location);


/************************************************************************
 * RvRaGetName
 * purpose: Get the name of the RA object
 * input  : raH         - Handle of the RA object
 * output : none
 * return : Name of the RA
 ************************************************************************/
RVCOREAPI const char* RVCALLCONV
RvRaGetName(IN HRA raH);


/************************************************************************
 * RvRaGetNext
 * purpose: Get the next used element in RA.
 *          This function can be used to implement search or "doall"
 *          functions on RA.
 * input  : raH - Handle of the RA object
 *          cur - Current RA location whose next we're looking for
 *                If negative, then RvRaGetNext() will return the first
 *                used element.
 * output : none
 * return : Location of the next used element on success
 *          Negative value when no more used elements are left
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvRaGetNext(IN HRA raH, IN int cur, OUT int* next);


/************************************************************************
 * RvRaGetStatistics
 * purpose: Get statistics information about RA.
 * input  : raH         - Handle of the RA object
 * output : stats       - Statistics information
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvRaGetStatistics(IN HRA raH, OUT RvRaStatistics* stats);



RVCOREAPI int RVCALLCONV
RvRaCurSize(HRA raH); /* returns current number of elements */

RVCOREAPI int RVCALLCONV
RvRaFreeSize(HRA raH); /* returns number of elements that can be added to array. */

RVCOREAPI int RVCALLCONV
RvRaMaxSize(HRA raH); /* returns maximum number of elements */

RVCOREAPI int RVCALLCONV
RvRaElemSize(HRA raH); /* returns size of element (with RA internal alignment) */

RVCOREAPI int RVCALLCONV
RvRaElemRequestedSize(HRA raH); /* returns size of element (without RA internal alignment) */

RVCOREAPI int RVCALLCONV
RvRaMaxUsage(HRA raH); /* Maximum usage of array */

RVCOREAPI RAECompare RVCALLCONV
RvRaFCompare(HRA raH);

RVCOREAPI int RVCALLCONV
RvRaFind(HRA raH, void *param);

RVCOREAPI int RVCALLCONV
RvRaCompare(HRA raH, RAECompare compare, void *param);



#ifdef __cplusplus
}
#endif

#endif  /* RV_RA_H */
