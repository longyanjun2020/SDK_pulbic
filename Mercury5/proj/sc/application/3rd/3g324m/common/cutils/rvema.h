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
  ema.h

  RADVISION static array implementation.

  The EMA module provides the Enhanced Memory Allocation services that RA provides, with
  several additional features:

  1. Knowledge about the type of handle in EMA.
     An EMA element can be checked for its type using RvEmaGetType()
  2. Reference counts
     Each element has a reference count that can be accessed through emaIncRefCount() and
     emaDefRefCount().
  3. Auto-lock
     EMA will automatically lock itself on functions that need thread-safety (such as
     RvEmaAdd).
  4. Explicit element locks

  EMA can also be used to link elements from different types to the same locks are reference
  counts. It is done in CM to link the channels of the call to the call, allowing easier
  locking and reference counting mechanisms.

  Written by Tsahi Levent-Levi

*/


#ifndef RV_EMA_H
#define RV_EMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rvra.h"

#if defined(RV_DEBUG)
#define RV_EMA_DEBUG
#endif


/* Handle to an EMA object */
RV_DECLARE_HANDLE(HEMA);


/* EMA element pointer declaration */
typedef void *EMAElement;



/************************************************************************
 * RvEmaStatistics struct
 * elems        - Statistics about the elements inside EMA
 * numMarked    - Number of items that are marked and deleted, not released
 *                yet.
 ************************************************************************/
typedef struct
{
    RvRaStatistics    elems;
    RvUint32            numMarked;
} RvEmaStatistics;


/************************************************************************
 * RvEmaLockType enum
 * emaNoLocks       - EMA is not using locks at all. It does use referece
 *                    counts. It will only use a general lock to lock when
 *                    adding and deleting elements
 * emaNormalLocks   - EMA uses locks and reference counts in a "normal" way
 * emaLinkedLocks   - EMA's locks and reference counts are linked to another
 *                    EMA object, which holds different types of information.
 ************************************************************************/
typedef enum
{
    RvEmaNoLocks,
    RvEmaNormalLocks,
    RvEmaLinkedLocks
} RvEmaLockType;


/************************************************************************
 * EMAFunc
 * purpose: Definition of a general function on an EMA element
 * input  : elem    - Element to function on
 *          param   - Context to use for it
 * output : none
 * return : Pointer for the context to use on the next call to this
 *          EMAFunc.
 ************************************************************************/
typedef void*(*EMAFunc)(EMAElement elem, void *param);




/************************************************************************
 * RvEmaConstruct
 * purpose: Create an EMA object
 * input  : elemSize            - Size of elements in the EMA in bytes
 *          maxNumOfElements    - Number of elements in EMA
 *          lockType            - Type of locking mechanism to use
 *          name                - Name of EMA (used in log messages)
 *          type                - Integer representing the type of objects
 *                                stored in this EMA.
 *          userData            - User related information associated with
 *                                this EMA object.
 *          instance            - Instance associated with this EMA object.
 *          logMgr              - Log manager to use.
 * output : none
 * return : Handle to RA constructed on success
 *          NULL on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaConstruct(
    IN RvInt            elemSize,
    IN RvInt            maxNumOfElements,
    IN RvEmaLockType    lockType,
    IN const char*      name,
    IN RvUint32         type,
    IN void*            userData,
    IN void const*      instance,
    IN RvLogMgr*        logMgr,
    OUT HEMA*           hEma);


/************************************************************************
 * RvEmaDestruct
 * purpose: Free an EMA object, deallocating all of its used memory
 * input  : emaH   - Handle of the EMA object
 * output : none
 * return : none
 ************************************************************************/
RVCOREAPI void RVCALLCONV
RvEmaDestruct(IN HEMA emaH);


/************************************************************************
 * RvEmaClear
 * purpose: Clear EMA from all used objects
 * input  : emaH   - Handle of the EMA object
 * output : none
 * return : none
 ************************************************************************/
RVCOREAPI void RVCALLCONV
RvEmaClear(IN HEMA emaH);


/************************************************************************
 * RvEmaAdd
 * purpose: Allocate an element in EMA for use, without initializing its
 *          value.
 *          This automatically locks the EMA object.
 * input  : emaH        - Handle of the EMA object
 *          appHandle   - Application's handle for the element
 * output : none
 * return : Pointer to element added on success
 *          NULL on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaAdd(IN HEMA emaH, IN void* appHandle, OUT EMAElement* emaElem);


/************************************************************************
 * RvEmaDelete
 * purpose: Delete an element from EMA
 * input  : elem    - Element to delete
 * return : Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaDelete(IN EMAElement elem);


/************************************************************************
 * RvEmaLinkToElement
 * purpose: Link an EMA element to another element, from a different
 *          EMA construct. This function should be used when the EMA we're
 *          dealing with was created with emaLinkedLocks. This function
 *          allows the element to use a different element's lock.
 *          This function will only work if the element has no reference
 *          count at present.
 * input  : elem        - Element to link
 *          otherElem   - Element we're linking to. Should be constructed
 *                        with emaNormalLocks or linked to such element.
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaLinkToElement(IN EMAElement elem, IN EMAElement otherElem);


/************************************************************************
 * RvEmaLock
 * purpose: Lock an element in EMA for use from the executing thread only
 *          This function will succeed only if the element exists
 * input  : elem    - Element to lock
 * output : none
 * return : RV_OK      - When the element exists and was locked
 *          RV_ERROR   - When the element doesn't exist (NULL are was deleted)
 *                       In this case, there's no need to call RvEmaUnlock().
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaLock(IN EMAElement elem);


/************************************************************************
 * RvEmaUnlock
 * purpose: Unlock an element in EMA that were previously locked by
 *          RvEmaLock() from the same thread
 * input  : elem    - Element to unlock
 * output : none
 * return : RV_TRUE    if element still exists
 *          RV_FALSE   if element was deleted and is not valid anymore
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI int RVCALLCONV
RvEmaUnlock(IN EMAElement elem);


/************************************************************************
 * RvEmaMark
 * purpose: Mark an element in EMA for use, not letting anyone delete
 *          this element until it is release.
 *          This automatically locks the EMA object.
 * input  : elem    - Element to mark
 * output : none
 * return : Negative value on failure
 ************************************************************************/
RVCOREAPI int RVCALLCONV
RvEmaMark(IN EMAElement elem);


/************************************************************************
 * RvEmaRelease
 * purpose: Release an element in EMA after it was marked using
 *          RvEmaMark(), returning an indication if this element
 *          still exists.
 *          This automatically locks the EMA object.
 * input  : elem    - Element to mark
 * output : none
 * return : RV_TRUE    if element still exists
 *          RV_FALSE   if element was deleted and is not valid anymore
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI int RVCALLCONV
RvEmaRelease(IN EMAElement elem);


/************************************************************************
 * RvEmaWasDeleted
 * purpose: Check if an element in EMA was deleted after a call to
 *          RvEmaMark().
 * input  : elem    - Element to mark
 * output : none
 * return : RV_TRUE    if element was deleted
 *          RV_FALSE   if element still exists
 ************************************************************************/
RVCOREAPI RvBool RVCALLCONV
RvEmaWasDeleted(IN EMAElement elem);


/************************************************************************
 * RvEmaPrepareForCallback
 * purpose: Prepare an element in EMA for use in a callback to the app.
 *          This function will make sure the element is unlocked the necessary
 *          number of times, and then marked once (so the app won't delete
 *          this element).
 *          RvEmaReturnFromCallback() should be called after the callback,
 *          with the return value of this function.
 * input  : elem    - Element to prepare
 * output : none
 * return : Number of times the element was locked on success
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI int RVCALLCONV
RvEmaPrepareForCallback(IN EMAElement elem);


/************************************************************************
 * RvEmaReturnFromCallback
 * purpose: Make sure the EMA element knows it has returned from a
 *          callback. This function will ensure that the element is
 *          locked again with the specified number of times. It will also
 *          release the element, and if timersLocked==0, and the element
 *          was deleted by the app in the callback, the element will also
 *          be permanently deleted.
 * input  : elem    - Element to prepare
 * output : none
 * return : RV_TRUE    if element still exists
 *          RV_FALSE   if element was deleted and is not valid anymore
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI int RVCALLCONV
RvEmaReturnFromCallback(IN EMAElement elem, IN int timesLocked);


/************************************************************************
 * RvEmaSetApplicationHandle
 * purpose: Set the application handle of an element in EMA
 * input  : elem        - Element in EMA
 *          appHandle   - Application's handle for the element
 * output : none
 * return : Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaSetApplicationHandle(IN EMAElement elem, IN void* appHandle);


 /************************************************************************
 * RvEmaGetApplicationHandle
 * purpose: Get the application's handle of an element in EMA
 * input  : elem        - Element in EMA
 * output : appHandle   - Application's handle for the element
 * return : Pointer to the application handle
 *          NULL on failure
 ************************************************************************/
RVCOREAPI void * RVCALLCONV
RvEmaGetApplicationHandle(IN EMAElement elem);


/************************************************************************
 * RvEmaGetType
 * purpose: Return the type of the element inside the EMA object.
 *          This is the type given in RvEmaConstruct().
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's type on success
 *          0 on failure
 ************************************************************************/
RVCOREAPI RvUint32 RVCALLCONV
RvEmaGetType(IN EMAElement elem);


/************************************************************************
 * RvEmaGetUserData
 * purpose: Return the user related data of the element inside the EMA
 *          object. This is the userData given in RvEmaConstruct().
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's user data pointer on success
 *          NULL on failure
 ************************************************************************/
RVCOREAPI void* RVCALLCONV
RvEmaGetUserData(IN EMAElement elem);

/************************************************************************
 * emaGetUserDataByInstance
 * purpose: Return the user related data inside the EMA object, by the
 *          EMA instance returned by RvEmaConstruct().
 *          This is the userData given in RvEmaConstruct().
 * input  : emaH   - handle to the EMA
 * output : none
 * return : The user data pointer on success
 *          NULL on failure
 ************************************************************************/
void* emaGetUserDataByInstance(IN HEMA emaH);

/************************************************************************
 * RvEmaGetInstance
 * purpose: Return the instance of this EMA element.
 *          This is the instance given in RvEmaConstruct().
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's instance on success
 *          NULL on failure
 ************************************************************************/
RVCOREAPI void const* RVCALLCONV
RvEmaGetInstance(IN EMAElement elem);


/************************************************************************
 * emaGetObject
 * purpose: Return the EMA object this element is in
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's EMA object on success
 *          NULL on failure
 ************************************************************************/
HEMA emaGetObject(IN EMAElement elem);


/************************************************************************
 * RvEmaDoAll
 * purpose: Call a function on all used elements in EMA
 * input  : emaH        - Handle of the EMA object
 *          func        - Function to execute on all elements
 *          param       - Context to use when executing the function
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaDoAll(
    IN HEMA     emaH,
    IN EMAFunc  func,
    IN void*    param);


/************************************************************************
 * RvEmaGetNext
 * purpose: Get the next used element in EMA.
 *          This function can be used to implement search or "doall"
 *          functions on EMA.
 * input  : emaH        - Handle of the EMA object
 *          cur         - Current EMA element whose next we're looking for
 *                        If NULL, then RvEmaGetNext() will return the first
 *                        used element.
 * output : none
 * return : Pointer to the next used element on success
 *          NULL when no more used elements are left
 ************************************************************************/
RVCOREAPI EMAElement RVCALLCONV
RvEmaGetNext(
    IN HEMA         emaH,
    IN EMAElement   cur);


/************************************************************************
 * RvEmaGetIndex
 * purpose: Returns the index of the element in the ema
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's index on success
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaGetIndex(IN EMAElement elem, OUT int* elemIndex);


/************************************************************************
 * RvEmaGetByIndex
 * purpose: Returns the ema element by its index.
 *          This function does not check if the element is vacant or not.
 * input  : emaH    - Handle of the EMA object
 *          index   - Index of element searched
 * output : none
 * return : Pointer to the element on success
 *          NULL on failure
 ************************************************************************/
RVCOREAPI EMAElement RVCALLCONV
RvEmaGetByIndex(
    IN HEMA emaH,
    IN int  index);


/************************************************************************
 * RvEmaGetStatistics
 * purpose: Get statistics information about EMA.
 *          The number of used items also includes those deleted, but still
 *          marked.
 * input  : emaH        - Handle of the EMA object
 * output : stats       - Statistics information
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVCOREAPI RvStatus RVCALLCONV
RvEmaGetStatistics(IN HEMA emaH, OUT RvEmaStatistics* stats);


/************************************************************************
 * RvEmaIsVacant
 * purpose: Returns whether the given object is free for allocation
 * input  : elem    - Element in EMA
 * output : none
 * return : RV_TRUE  - if the elemnt is not allocated
 *          RV_FALSE - otherwise
 ************************************************************************/
RVCOREAPI RvBool RVCALLCONV
RvEmaIsVacant(IN EMAElement elem);



#if defined(RV_EMA_DEBUG) && (RV_LOGMASK != RV_LOGLEVEL_NONE)

#define RvEmaLock(elem) RvEmaLockDebug(elem, __FILE__, __LINE__)
#define RvEmaUnlock(elem) RvEmaUnlockDebug(elem, __FILE__, __LINE__)
#define RvEmaMark(elem) RvEmaMarkDebug(elem, __FILE__, __LINE__)
#define RvEmaRelease(elem) RvEmaReleaseDebug(elem, __FILE__, __LINE__)
#define RvEmaPrepareForCallback(elem) RvEmaPrepareForCallbackDebug(elem, __FILE__, __LINE__)
#define RvEmaReturnFromCallback(elem, timesLocked) RvEmaReturnFromCallbackDebug(elem, timesLocked, __FILE__, __LINE__)
#define RvEmaDelete(elem) RvEmaDeleteDebug(elem, __FILE__, __LINE__)

RVCOREAPI RvStatus RVCALLCONV
RvEmaLockDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVCOREAPI RvStatus RVCALLCONV
RvEmaUnlockDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVCOREAPI RvStatus RVCALLCONV
RvEmaMarkDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVCOREAPI RvStatus RVCALLCONV
RvEmaReleaseDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVCOREAPI RvStatus RVCALLCONV
RvEmaPrepareForCallbackDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVCOREAPI RvStatus RVCALLCONV
RvEmaReturnFromCallbackDebug(IN EMAElement elem, IN int timesLocked, IN const char* filename, IN int lineno);

RVCOREAPI int RVCALLCONV
RvEmaDeleteDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

#endif  /* RV_EMA_DEBUG */



#ifdef __cplusplus
}
#endif

#endif  /* RV_EMA_H */
